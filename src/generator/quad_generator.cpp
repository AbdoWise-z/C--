//
// Created by xabdomo on 4/23/25.
//

#include "quad_generator.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <regex>
#include <stack>

#include "nodes/Functional.h"
#include "nodes/Macros.hpp"
#include "nodes/Variables.h"
#include "utils/string_utils.hpp"

namespace fs = std::filesystem;

using namespace Cmm::QuadGenerator;

static std::pair<Cmm::ValueType, bool> varTypeOrError(std::string name, CodeGenContext* context) {
    std::vector<CodeGenScope>& stack = context->stack;
    int scope = stack.size() - 1;
    while (scope >= 0) {
        auto it = stack[scope].variables.find(name);
        if (it != stack[scope].variables.end()) {
            // found it
            for (auto& i: context->symbolTable) {
                if (i.scope == scope && i.objectType == Variable && i.name == name) {
                    i.useCount++;
                    break;
                }
            }
            return it->second;
        }
        scope --;
    }

    throw Cmm::Program::VariableNotFoundError(name);
}

static std::pair<bool, std::vector<bool>> SignatureMatch(const Cmm::FunctionDefinitionSignature& signature, const std::vector<Cmm::ValueType>& params, int i = 0, int j = 0, std::vector<bool> set = {}) {
    if (i == signature.first.size() && j == params.size()) {
        return {true, set}; // both done
    }

    if (i == signature.first.size()) {
        return {false, {}}; // just one of them is done
    }

    if (j < params.size() && signature.first[i] != params[j]) { // param didn't match
        if (signature.second[i]) { // but it's optional
            std::vector<bool> newset = set;
            newset.push_back(false);
            return SignatureMatch(signature, params, i + 1, j, newset); // try to skip this param
        }
    } else { // param did match .. but we might actually also skip it
        // attempt 1: add it
        std::vector<bool> newset = set;
        newset.push_back(true);
        auto result = SignatureMatch(signature, params, i + 1, j + 1, newset);
        if (result.first) return result; // that worked

        // attempt 2: skip it
        if (signature.second[i]) {
            newset = set;
            newset.push_back(false);
            return SignatureMatch(signature, params, i + 1, j, newset);
        }
    }

    return {false, {}}; // everything failed
}

static Cmm::ValueType funcTypeOrError(Cmm::FunctionSignature s, CodeGenContext* context, bool one_scope_only = false) {
    std::vector<CodeGenScope>& stack = context->stack;
    int scope = stack.size() - 1;
    while (scope >= 0) {
        auto it = stack[scope].functions.find(s.first);
        if (it != stack[scope].functions.end()) {
            std::vector<Cmm::ValueType> Candidates;

            // auto func_obj = it->second.find(s.second);
            // if (func_obj != it->second.end()) {
            //     for (auto& i: context->symbolTable) {
            //         if (i.scope == scope && (i.objectType == Function || i.objectType == NativeFunction) && i.name == s.first && i.accept_type == s.second) {
            //             i.useCount++;
            //             break;
            //         }
            //     }
            //
            //     return func_obj->second;
            // }

            std::vector<Cmm::ValueType> matching_call;
            for (auto& [k, v]: it->second) {
                if (SignatureMatch(k, s.second).first) {
                    Candidates.push_back(v);
                    if (Candidates.size() == 1) {
                        matching_call = k.first;
                    }
                }
            }

            if (!Candidates.empty()) {
                if (Candidates.size() > 1) {
                    CodeGenWarn warn;
                    warn.exception = "Call to " + Cmm::Program::stringfy(s) + " is ambiguous, found more than one matching overload.";
                    warn.line = context->currentLine;
                    context->warnings.push_back(warn);
                }

                for (auto& i: context->symbolTable) {
                    if (i.scope == scope && (i.objectType == Function || i.objectType == NativeFunction) && i.name == s.first && i.accept_type == matching_call) {
                        i.useCount++;
                        break;
                    }
                }

                return Candidates.front();
            }
        }

        if (one_scope_only) {
            throw Cmm::Program::FunctionNotFoundError(Cmm::Program::stringfy(s));
        }
        scope --;
    }

    throw Cmm::Program::FunctionNotFoundError(Cmm::Program::stringfy(s));
}

static Cmm::ValueType inferType(Cmm::EvaluableNode* node, CodeGenContext* context) {
    if (auto mNode = dynamic_cast<Cmm::Variables::PreIncNode*>(node)) {
        try {
            return varTypeOrError(mNode->name, context).first;
        } catch (Cmm::Program::VariableNotFoundError& e) {
            // CodeGenError err;
            // err.exception = e.what(),
            // err.line = node->_virtualLineNumber;
            // context->errors.push_back(err);
            return Cmm::V_Any;
        }
    }

    if (auto mNode = dynamic_cast<Cmm::Variables::PostIncNode*>(node)) {
        try {
            return varTypeOrError(mNode->name, context).first;
        } catch (Cmm::Program::VariableNotFoundError& e) {
            // CodeGenError err;
            // err.exception = e.what(),
            // err.line = node->_virtualLineNumber;
            // context->errors.push_back(err);
            return Cmm::V_Any;
        }
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::VariableNode*>(node)) {
        try {
            return varTypeOrError(mNode->name, context).first;
        } catch (Cmm::Program::VariableNotFoundError& e) {
            // CodeGenError err;
            // err.exception = e.what(),
            // err.line = node->_virtualLineNumber;
            // context->errors.push_back(err);
            return Cmm::V_Any;
        }
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::ExpressionNode*>(node)) {
        return inferType(mNode->children.back(), context); // I swear I have no idea why I created this node.
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::CastNode*>(node)) {
        auto _internalType = inferType(mNode->child, context);
        auto _cL = Cmm::CastConversionMap.find(_internalType);
        if (!_cL->second.contains(mNode->targetType)) {
            // CodeGenWarn err;
            // err.exception = std::string(Cmm::ValuesHelper::ConversionError(_internalType, mNode->targetType).what());
            // err.line = node->_virtualLineNumber;
            //
            // if (_internalType == Cmm::V_Any) {
            //     err.exception = "Conversions with type [Any] depends on runtime value.";
            // }
            // context->warnings.push_back(err);
        }

        return mNode->targetType;
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::ConstantValueNode*>(node)) {
        return mNode->value.type;
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::NotNode*>(node)) {
        return inferType(mNode->child, context);
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::InvertNode*>(node)) {
        return inferType(mNode->child, context);
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::NegatedNode*>(node)) {
        return inferType(mNode->child, context);
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::TermNode*>(node)) {
        return Cmm::TermConversionMap.find({
            inferType(mNode->left , context),
            inferType(mNode->right, context),
        })->second;
    }

    if (auto mNode = dynamic_cast<Cmm::Functional::FunctionCallNode*>(node)) {
        try {
            Cmm::FunctionSignature func = {mNode->id, {}};
            for (auto param: mNode->funcParam->params) {
                func.second.push_back(inferType(param, context));
            }
            return funcTypeOrError(func, context);
        } catch (Cmm::Program::FunctionNotFoundError& e) {
            // CodeGenError err;
            // err.exception = e.what(),
            // err.line = node->_virtualLineNumber;
            // context->errors.push_back(err);
            return Cmm::V_Any;
        }
    }

    CodeGenError err;
    err.exception = "Unknown Node Type";
    err.line = node->_virtualLineNumber;
    context->errors.push_back(err);
    return Cmm::V_Any;
}

static std::string IndentationAsString(size_t i) {
    std::stringstream str;

    for (int j = 0;j < i;j++) {
        str << "  ";
    }

    return str.str();
}

static inline void writeQuad(std::ostream&out, size_t indentation, std::string op, std::string arg1, std::string arg2, std::string res, CodeGenContext* context) {
    context->currentLine++;
    out << IndentationAsString(indentation)
            << std::setw(QUAD_SIZE) << std::left << op
            << std::setw(QUAD_SIZE) << std::left << arg1
            << std::setw(QUAD_SIZE) << std::left << arg2
            << std::setw(QUAD_SIZE) << std::left << res
            << std::endl;

    // std::cout << IndentationAsString(indentation)
    //         << std::setw(QUAD_SIZE) << std::left << op
    //         << std::setw(QUAD_SIZE) << std::left << arg1
    //         << std::setw(QUAD_SIZE) << std::left << arg2
    //         << std::setw(QUAD_SIZE) << std::left << res
    //         << std::endl;
}

static std::string getTempVarName(CodeGenContext* context) {
    return "t_" + std::to_string(context->tempVarCount++);
}

static std::string getIfLabel(CodeGenContext* context) {
    return "if_exit_" + std::to_string(context->ifLabelCount++);
}

static std::string getForCondLabel(CodeGenContext* context) {
    return "for_cond_" + std::to_string(context->forConditionLabelCount++);
}

static std::string getForExitLabel(CodeGenContext* context) {
    return "for_exit_" + std::to_string(context->forExitLabelCount++);
}

static std::string getForEnterLabel(CodeGenContext* context) {
    return "for_enter_" + std::to_string(context->forEnterLabelCount++);
}

static std::string getForIncLabel(CodeGenContext* context) {
    return "for_inc_" + std::to_string(context->forIncLabelCount++);
}

static std::string getSwitchCaseCondLabel(CodeGenContext* context) {
    return "switch_case_cond_" + std::to_string(context->switchCaseCondLabelCount++);
}

static std::string getSwitchCaseLabel(CodeGenContext* context) {
    return "switch_case_" + std::to_string(context->switchCaseLabelCount++);
}

static std::string getSwitchExitLabel(CodeGenContext* context) {
    return "switch_exit_" + std::to_string(context->switchExitLabelCount++);
}


static std::tuple<std::string, Cmm::ValueType, bool> quoteStrings(std::tuple<std::string, Cmm::ValueType, bool> in) {

    if (get<1>(in) == Cmm::V_String && !get<2>(in)) {
        return {"\"" + StringUtils::escapeString( get<0>(in) ) + "\"", get<1>(in), get<2>(in)};
    }

    return in;
}

static std::pair<std::string, Cmm::ValueType> asPair(std::tuple<std::string, Cmm::ValueType, bool> in) {
    return {get<0>(in), get<1>(in)};
}

static std::tuple<std::string, Cmm::ValueType, bool> writeExpression(Cmm::EvaluableNode* node, CodeGenContext* context, size_t indentation, std::ostream& out) {
    if (auto mNode = dynamic_cast<Cmm::Variables::PreIncNode*>(node)) {
        auto type = Cmm::V_Any;

        try {
            auto var = varTypeOrError(mNode->name, context); // check the variable exists (throws error if not)
            if (var.second) {
                // this is a const
                CodeGenError err;
                err.exception = Cmm::Program::ConstantAssignmentError(mNode->name).what(),
                err.line = node->_virtualLineNumber;
                context->errors.push_back(err);
            }
            type = var.first;
        } catch (Cmm::Program::VariableNotFoundError& e) {
            CodeGenError err;
            err.exception = e.what(),
            err.line = node->_virtualLineNumber;
            context->errors.push_back(err);
        }

        writeQuad(out, indentation, (mNode->op == "++" ? OP_PLUS : OP_MINUS), mNode->name, "1", mNode->name, context);

        return {mNode->name, type, true};
    }

    if (auto mNode = dynamic_cast<Cmm::Variables::PostIncNode*>(node)) {
        auto type = Cmm::V_Any;

        try {
            auto var = varTypeOrError(mNode->name, context); // check the variable exists (throws error if not)
            if (var.second) {
                // this is a const
                CodeGenError err;
                err.exception = Cmm::Program::ConstantAssignmentError(mNode->name).what(),
                err.line = node->_virtualLineNumber;
                context->errors.push_back(err);
            }
            type = var.first;
        } catch (Cmm::Program::VariableNotFoundError& e) {
            CodeGenError err;
            err.exception = e.what(),
            err.line = node->_virtualLineNumber;
            context->errors.push_back(err);
        }


        auto tName = getTempVarName(context);

        writeQuad(out, indentation, OP_ASSIGN                               , mNode->name, "" , tName, context);
        writeQuad(out, indentation, (mNode->op == "++" ? OP_PLUS : OP_MINUS), mNode->name, "1", mNode->name, context);

        return {tName, type, true};
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::VariableNode*>(node)) {
        try {
            auto _val = varTypeOrError(mNode->name, context);
            return {mNode->name, _val.first, true};
        } catch (Cmm::Program::VariableNotFoundError& e) {
            CodeGenError err;
            err.exception = e.what(),
            err.line = node->_virtualLineNumber;
            context->errors.push_back(err);
            return {mNode->name, Cmm::V_Any, true};
        }
    }


    // if (auto mNode = dynamic_cast<Cmm::Expressions::ExpressionNode*>(node)) {
    //     return inferType(mNode->children.back(), context); // I swear I have no idea why I created this node.
    // }


    if (auto mNode = dynamic_cast<Cmm::Expressions::CastNode*>(node)) {
        auto _internalResult = writeExpression(mNode->child, context, indentation, out);
        auto _cL = Cmm::CastConversionMap.find(get<1>(_internalResult));
        if (!_cL->second.contains(mNode->targetType)) {
            CodeGenWarn err;
            err.exception = std::string(Cmm::ValuesHelper::ConversionError(get<1>(_internalResult), mNode->targetType).what());
            err.line = node->_virtualLineNumber;

            if (get<1>(_internalResult) == Cmm::V_Any) {
                err.exception = "Conversions with type [any] depends on runtime value.";
            }

            context->warnings.push_back(err);
        }

        auto tName = getTempVarName(context);

        writeQuad(
            out,
            indentation,
            std::string(OP_CAST) + " (" + Cmm::ValuesHelper::ValueTypeAsString(mNode->targetType) + ")",
            get<0>(_internalResult),
            "",
            tName,
            context
            );
        return {tName, mNode->targetType, true};
    }


    if (auto mNode = dynamic_cast<Cmm::Expressions::ConstantValueNode*>(node)) {
        //fixme: maybe add some quotes to strings ? idk
        return {Cmm::ValuesHelper::toString(mNode->value), mNode->value.type, false};
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::NotNode*>(node)) {
        auto _internalResult = writeExpression(mNode->child, context, indentation, out);
        auto _cL = Cmm::CastConversionMap.find(get<1>(_internalResult));
        if (!_cL->second.contains(Cmm::V_Bool)) {
            CodeGenWarn err;
            err.exception = std::string(Cmm::ValuesHelper::ConversionError(get<1>(_internalResult), Cmm::V_Bool).what());
            err.line = node->_virtualLineNumber;

            if (get<1>(_internalResult) == Cmm::V_Any) {
                err.exception = "Conversions with type [any] depends on runtime value.";
            }

            context->warnings.push_back(err);
        }

        auto tName = getTempVarName(context);

        writeQuad(
            out,
            indentation,
            OP_NOT,
            get<0>(_internalResult),
            "",
            tName,
            context
            );

        return {tName, Cmm::V_Bool, true};
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::InvertNode*>(node)) {
        auto _internalResult = writeExpression(mNode->child, context, indentation, out);
        auto _cL = Cmm::CastConversionMap.find(get<1>(_internalResult));
        if (!_cL->second.contains(Cmm::V_Integer)) {
            CodeGenWarn err;
            err.exception = std::string(Cmm::ValuesHelper::ConversionError(get<1>(_internalResult), Cmm::V_Integer).what());
            err.line = node->_virtualLineNumber;

            if (get<1>(_internalResult) == Cmm::V_Any) {
                err.exception = "Conversions with type [any] depends on runtime value.";
            }

            context->warnings.push_back(err);
        }

        auto tName = getTempVarName(context);

        writeQuad(
            out,
            indentation,
            OP_INVERT,
            get<0>(_internalResult),
            "",
            tName,
            context
            );

        return {tName, Cmm::V_Integer, false};
    }

    if (auto mNode = dynamic_cast<Cmm::Expressions::NegatedNode*>(node)) {
        auto _internalResult = writeExpression(mNode->child, context, indentation, out);
        if (get<1>(_internalResult) == Cmm::V_Any || get<1>(_internalResult) == Cmm::V_String) {
            CodeGenWarn err;
            err.exception = std::string(Cmm::ValuesHelper::ConversionError(get<1>(_internalResult), Cmm::V_Any).what());
            err.line = node->_virtualLineNumber;

            if (get<1>(_internalResult) == Cmm::V_Any) {
                err.exception = "Conversions with type [any] depends on runtime value.";
            }

            if (get<1>(_internalResult) == Cmm::V_String) {
                err.exception = "Type [str] doesn't support negation.";
            }

            context->warnings.push_back(err);
        }

        auto tName = getTempVarName(context);

        writeQuad(
            out,
            indentation,
            OP_MINUS,
            get<0>(_internalResult),
            "",
            tName,
            context
            );

        return {tName, Cmm::V_Integer, true};
    }



    if (auto mNode = dynamic_cast<Cmm::Expressions::TermNode*>(node)) {
        auto left = mNode->left;
        auto right = mNode->right;

        auto left_v = writeExpression(left, context, indentation, out);
        auto right_v = writeExpression(right, context, indentation, out);

        auto temp = getTempVarName(context);

        writeQuad(out, indentation, mNode->op, get<0>(left_v), get<0>(right_v), temp, context);
        auto it = Cmm::TermConversionMap.find({get<1>(left_v), get<1>(right_v)});
        auto result_type = Cmm::V_Any;
        if (it == Cmm::TermConversionMap.end()) {
            // one of them is V_void
            CodeGenError err;
            err.exception = "Tried to do an operation on a [void] type.",
            err.line = node->_virtualLineNumber;
            context->errors.push_back(err);
        } else result_type = it->second;
        return {temp, result_type, true};
    }

    if (auto mNode = dynamic_cast<Cmm::Functional::FunctionCallNode*>(node)) {
        auto func_t = Cmm::V_Any;
        auto param_count = 0;
        try {
            Cmm::FunctionSignature func = {mNode->id, {}};
            for (auto param: mNode->funcParam->params) {
                auto res = quoteStrings(writeExpression(param, context, indentation, out));
                func.second.push_back(get<1>(res));
                writeQuad(out, indentation, OP_PARAM, get<0>(res), "", "", context);
                param_count++;
            }
            func_t = funcTypeOrError(func, context);
        } catch (Cmm::Program::FunctionNotFoundError& e) {
            CodeGenError err;
            err.exception = e.what(),
            err.line = node->_virtualLineNumber;
            context->errors.push_back(err);
        }

        if (func_t == Cmm::V_Void) {
            writeQuad(out, indentation, OP_CALL, mNode->id, std::to_string(param_count), "", context);
            return {"void_type", func_t, true};
        }

        auto tVar = getTempVarName(context);
        writeQuad(out, indentation, OP_CALL, mNode->id, std::to_string(param_count), tVar, context);
        return {tVar, func_t, true};
    }

    return {"__THIS_SHOULD_NEVER_HAPPEN__", Cmm::V_String, true};
}

static void generateQuads_recv(Cmm::ASTNode* node, CodeGenContext* context, size_t indentation, std::ostream& out) {
    if (auto mNode = dynamic_cast<Cmm::Variables::InferredVariableDeclarationNode*>(node)) {
        auto& stack = context->stack.back();
        if (stack.variables.find(mNode->name) != stack.variables.end()) {
            CodeGenError err;
            err.exception = Cmm::Program::AlreadyDefinedError(mNode->name).what();
            err.line = mNode->_virtualLineNumber;
            context->errors.push_back(err);
        } else {

            auto expr = asPair(quoteStrings(writeExpression(mNode->value, context, indentation, out)));
            writeQuad(out, indentation, OP_DECLARE, mNode->isConst ? "True" : "False", "", mNode->name, context);
            writeQuad(out, indentation, OP_ASSIGN, expr.first, "", mNode->name, context);

            if (expr.second == Cmm::V_Void) {
                CodeGenError err;
                err.exception = "Trying to assign an expression with void result to variable";
                err.line = mNode->_virtualLineNumber;
                context->errors.push_back(err);
            }

            std::string value = "(Runtime)";
            if (auto _const = dynamic_cast<Cmm::Expressions::ConstantValueNode*>(mNode->value)) {
                value = Cmm::ValuesHelper::toString(_const->value);
            }

            Symbol s = {
                .codeLine = (size_t) mNode->_virtualLineNumber,
                .quadLine = (size_t) context->currentLine,
                .scope = context->stack.size() - 1,
                .type = {expr.second},
                .accept_type = {},
                .objectType = SymbolType::Variable,
                .name = mNode->name,
                .value =value,
                .useCount = 0,
            };

            stack.variables[mNode->name] = {expr.second, mNode->isConst};
            context->symbolTable.push_back(s);
        }
    }

    if (auto mNode = dynamic_cast<Cmm::Variables::VariableDeclarationNode*>(node)) {
        auto& stack = context->stack.back();
        if (stack.variables.find(mNode->name) != stack.variables.end()) {
            CodeGenError err;
            err.exception = Cmm::Program::AlreadyDefinedError(mNode->name).what();
            err.line = mNode->_virtualLineNumber;
            context->errors.push_back(err);
        } else {

            auto _internalType = inferType(mNode->value, context);
            auto _externalType = Cmm::ValuesHelper::StringToValueType(mNode->type);


            if (_internalType != _externalType) {
                CodeGenWarn err;
                err.exception = "Implicit conversion from [" + Cmm::ValuesHelper::ValueTypeAsString(_internalType) + "] to [" + Cmm::ValuesHelper::ValueTypeAsString(_externalType) + "].";
                err.line = node->_virtualLineNumber;
                context->warnings.push_back(err);

                auto _shadowNode = new Cmm::Expressions::CastNode(mNode->value, Cmm::ValuesHelper::ValueTypeAsString(_externalType));
                auto expr = asPair(quoteStrings(writeExpression(_shadowNode, context, indentation + 1, out)));
                _shadowNode->child = nullptr;
                delete _shadowNode;

                writeQuad(out, indentation, OP_DECLARE, mNode->isConst ? "True" : "False", "", mNode->name, context);
                writeQuad(out, indentation, OP_ASSIGN, expr.first, "", mNode->name, context);
            } else {
                auto expr = asPair(quoteStrings(writeExpression(mNode->value, context, indentation, out)));
                writeQuad(out, indentation, OP_DECLARE, mNode->isConst ? "True" : "False", "", mNode->name, context);
                writeQuad(out, indentation, OP_ASSIGN, expr.first, "", mNode->name, context);
            }

            std::string value = "(Runtime)";
            if (auto _const = dynamic_cast<Cmm::Expressions::ConstantValueNode*>(mNode->value)) {
                value = Cmm::ValuesHelper::toString(_const->value);
            }

            Symbol s = {
                .codeLine = (size_t) mNode->_virtualLineNumber,
                .quadLine = (size_t) context->currentLine,
                .scope = context->stack.size() - 1,
                .type = {_externalType},
                .accept_type = {},
                .objectType = SymbolType::Variable,
                .name = mNode->name,
                .value =value,
                .useCount = 0,
            };

            stack.variables[mNode->name] = {_externalType, mNode->isConst};
            context->symbolTable.push_back(s);
        }
    }

    if (auto mNode = dynamic_cast<Cmm::Variables::VariableAssignmentNode*>(node)) {
        std::pair variable_params = {Cmm::V_Any, false};
        try {
            variable_params = varTypeOrError(mNode->name, context);

            if (variable_params.second) {
                // this is a const
                CodeGenError err;
                err.exception = Cmm::Program::ConstantAssignmentError(mNode->name).what(),
                err.line = node->_virtualLineNumber;
                context->errors.push_back(err);
            }

        } catch (std::exception& e) {
            CodeGenError err;
            err.exception = Cmm::Program::VariableNotFoundError(mNode->name).what();
            err.line = mNode->_virtualLineNumber;
            context->errors.push_back(err);
        }

        auto _internalType = inferType(mNode->expr, context);

        auto _externalType = variable_params.first;
        if (_internalType != _externalType) {
            CodeGenWarn err;
            err.exception = "Implicit conversion from [" + Cmm::ValuesHelper::ValueTypeAsString(_internalType) + "] to [" + Cmm::ValuesHelper::ValueTypeAsString(_externalType) + "].";
            err.line = node->_virtualLineNumber;
            context->warnings.push_back(err);

            auto _shadowNode = new Cmm::Expressions::CastNode(mNode->expr, Cmm::ValuesHelper::ValueTypeAsString(_externalType));
            auto expr = asPair(quoteStrings(writeExpression(_shadowNode, context, indentation + 1, out)));
            _shadowNode->child = nullptr;
            delete _shadowNode; // nobody saw anything ...

            writeQuad(out, indentation, OP_ASSIGN, expr.first, "", mNode->name, context);
        } else {
            auto expr = asPair(quoteStrings(writeExpression(mNode->expr, context, indentation, out)));
            writeQuad(out, indentation, OP_ASSIGN, expr.first, "", mNode->name, context);
        }
    }

    if (auto mNode = dynamic_cast<Cmm::Variables::CompoundAssignmentNode*>(node)) {
        generateQuads_recv(mNode->_internal, context, indentation, out);
    }

    if (auto mNode = dynamic_cast<Cmm::Program::StatementListNode*>(node)) {
        for (auto stmt: mNode->statements) {
            generateQuads_recv(stmt, context, indentation, out);
        }
    }

    if (auto mNode = dynamic_cast<Cmm::Program::ExpressionStatementNode*>(node)) {
        writeExpression(mNode->expr, context, indentation, out);
    }

    if (auto mNode = dynamic_cast<Cmm::Program::ScopeNode*>(node)) {
        context->stack.push_back({});
        generateQuads_recv(mNode->statements, context, indentation + 1, out);
        context->stack.pop_back();
    }

    if (auto mNode = dynamic_cast<Cmm::Program::ProgramNode*>(node)) {
        context->stack.push_back({});
        generateQuads_recv(mNode->source, context, indentation + 1, out);
        context->stack.pop_back();
    }

    if (auto mNode = dynamic_cast<Cmm::Functional::FunctionDeclarationNode*>(node)) {
        // check if the function already exists
        auto& stack = context->stack.back();
        auto it = stack.functions.find(mNode->id);

        std::vector<Cmm::ValueType> args;
        std::vector<bool> op_args;
        std::vector<std::string> argsNames;
        for (auto i: mNode->arguments->arguments) {
            args.push_back(Cmm::ValuesHelper::StringToValueType(i->type));
            argsNames.push_back(i->id);
            op_args.push_back(i->defaultValue != nullptr);
        }

        std::vector<Cmm::ValueType> retType;
        for (auto i : mNode->returnType->types) {
            retType.push_back(i);
        }

        if (mNode->function == nullptr) {
            if (context->stack.size() > 1) {
                CodeGenError err;
                err.exception = "Attempting to create a native function outside the global scope.";
                err.line = mNode->_virtualLineNumber;
                context->errors.push_back(err);
            }
        }

        bool alreadyDeclared = false;

        try {
            auto dummy = funcTypeOrError({mNode->id, args}, context, true);
            alreadyDeclared = true;

            CodeGenError err;
            err.exception = Cmm::Program::AlreadyDefinedError(Cmm::Program::stringfy({
                mNode->id,
                args
            })).what();
            err.line = mNode->_virtualLineNumber;
            context->errors.push_back(err);
        } catch (std::exception& e) {
            // we are good
        }

        if (it == stack.functions.end()) {
            // check if this specific overload exists
            stack.functions[mNode->id] = {};
            it = stack.functions.find(mNode->id);
        }

        if (!alreadyDeclared) {
            // write code to declare a function
            context->stack.push_back({});
            // push arguments first
            auto& scope = context->stack.back();
            std::vector<Cmm::ValueType> accept_types;
            for (auto i: mNode->arguments->arguments) {
                // add it to the scope
                auto type = Cmm::ValuesHelper::StringToValueType(i->type);

                if (scope.variables.contains(i->id)) {
                    CodeGenError err;
                    err.exception = "Function has repeated argument: " + i->id;
                    err.line = i->_virtualLineNumber;
                    context->errors.push_back(err);
                }

                scope.variables[i->id] = {type, false};

                // add it to the symbol table
                std::string value = "(None)";
                if (i->defaultValue) {
                    auto res_type = inferType(i->defaultValue, context);
                    if (res_type != type) {
                        auto _shadowNode = new Cmm::Expressions::CastNode(i->defaultValue, Cmm::ValuesHelper::ValueTypeAsString(type));
                        auto expr = asPair(quoteStrings(writeExpression(_shadowNode, context, indentation, out)));
                        _shadowNode->child = nullptr;
                        delete _shadowNode;
                        value = expr.first;
                    } else {
                        auto expr = asPair(quoteStrings(writeExpression(i->defaultValue, context, indentation, out)));
                        value = expr.first;
                    }
                }

                // add it to the symbol table
                Symbol s = {
                    .codeLine = (size_t) mNode->_virtualLineNumber,
                    .quadLine = (size_t) context->currentLine,
                    .scope = context->stack.size() - 1,
                    .type = {type},
                    .accept_type = {},
                    .objectType = SymbolType::Variable,
                    .name = i->id,
                    .value = value.starts_with("t") ? "(Runtime)" : value,
                    .useCount = 0,
                };

                context->symbolTable.push_back(s);
                writeQuad(out, indentation, "Arg", Cmm::ValuesHelper::ValueTypeAsString(type), value, i->id, context);

                accept_types.push_back(type);
            }

            writeQuad(out, indentation, mNode->function == nullptr  ? "NATIVE FUNC" : "FUNC", mNode->id, "", "", context);

            it->second[{args, op_args}] = mNode->returnType->types.size() == 1 ? (*mNode->returnType->types.begin()) : Cmm::V_Any;
            context->returnLabels.push_back(retType);

            // now push the function symbol itself
            std::vector<Cmm::ValueType> ret_type;
            for (auto t: mNode->returnType->types) {
                ret_type.push_back(t);
            }

            Symbol s = {
                .codeLine = (size_t) mNode->_virtualLineNumber,
                .quadLine = (size_t) context->currentLine,
                .scope = context->stack.size() - 2,
                .type = ret_type,
                .accept_type = accept_types,
                .objectType = mNode->function == nullptr ? SymbolType::NativeFunction : Function,
                .name = mNode->id,
                .value = "(Func)",
                .useCount = 0,
            };

            context->symbolTable.push_back(s);

            if (mNode->function) {
                generateQuads_recv(mNode->function, context, indentation + 1, out);
                writeQuad(out, indentation, "FUNC END", mNode->id, "", "", context);
            }

            context->stack.pop_back();
            context->returnLabels.pop_back();
        }
    }

    // if (auto mNode = dynamic_cast<Cmm::Functional::NativeFunctionDeclarationNode*>(node)) {
    //     // check if the function already exists
    //     auto& stack = context->stack.back();
    //     auto it = stack.functions.find(mNode->id);
    //
    //     std::vector<Cmm::ValueType> args;
    //     std::vector<bool> op_args;
    //     std::vector<std::string> argsNames;
    //     for (auto i: mNode->arguments->arguments) {
    //         args.push_back(Cmm::ValuesHelper::StringToValueType(i->type));
    //         argsNames.push_back(i->id);
    //         op_args.push_back(i->defaultValue != nullptr);
    //     }
    //
    //     bool alreadyDeclared = false;
    //
    //     try {
    //         auto dummy = funcTypeOrError({mNode->id, args}, context);
    //         alreadyDeclared = true;
    //     } catch (std::exception& e) {
    //         CodeGenError err;
    //         err.exception = Cmm::Program::AlreadyDefinedError(Cmm::Program::stringfy({
    //             mNode->id,
    //             args
    //         })).what();
    //         err.line = mNode->_virtualLineNumber;
    //         context->errors.push_back(err);
    //     }
    //
    //     if (it == stack.functions.end()) {
    //         // check if this specific overload exists
    //         stack.functions[mNode->id] = {};
    //         it = stack.functions.find(mNode->id);
    //     }
    //
    //     if (!alreadyDeclared) {
    //         // write code to declare a function
    //         context->stack.push_back({});
    //         // push arguments first
    //         auto& scope = context->stack.back();
    //         std::vector<Cmm::ValueType> accept_types;
    //         for (auto i: mNode->arguments->arguments) {
    //             // add it to the scope
    //             auto type = Cmm::ValuesHelper::StringToValueType(i->type);
    //
    //             if (scope.variables.contains(i->id)) {
    //                 CodeGenError err;
    //                 err.exception = "Function has repeated argument: " + i->id;
    //                 err.line = i->_virtualLineNumber;
    //                 context->errors.push_back(err);
    //             }
    //
    //             scope.variables[i->id] = {type, false};
    //
    //             std::string value = "(None)";
    //             if (i->defaultValue) {
    //                 auto res_type = inferType(i->defaultValue, context);
    //                 if (res_type != type) {
    //                     auto _shadowNode = new Cmm::Expressions::CastNode(i->defaultValue, Cmm::ValuesHelper::ValueTypeAsString(type));
    //                     auto expr = quoteStrings(writeExpression(_shadowNode, context, indentation, out));
    //                     _shadowNode->child = nullptr;
    //                     delete _shadowNode;
    //                     value = expr.first;
    //                 } else {
    //                     auto expr = quoteStrings(writeExpression(i->defaultValue, context, indentation, out));
    //                     value = expr.first;
    //                 }
    //             }
    //
    //             // add it to the symbol table
    //             Symbol s = {
    //                 .codeLine = (size_t) mNode->_virtualLineNumber,
    //                 .quadLine = (size_t) context->currentLine,
    //                 .scope = context->stack.size() - 1,
    //                 .type = {type},
    //                 .accept_type = {},
    //                 .objectType = SymbolType::Variable,
    //                 .name = i->id,
    //                 .value =value.starts_with("t") ? "(Runtime)" : value,
    //                 .useCount = 0,
    //             };
    //
    //             context->symbolTable.push_back(s);
    //             writeQuad(out, indentation, "Arg", Cmm::ValuesHelper::ValueTypeAsString(type), value, i->id, context);
    //             accept_types.push_back(type);
    //         }
    //
    //         writeQuad(out, indentation, "Native FUNC", mNode->id, "", "", context);
    //
    //         it->second[{args, op_args}] = mNode->returnType->types.size() == 1 ? (*mNode->returnType->types.begin()) : Cmm::V_Any;
    //         context->returnLabels.push_back(args);
    //
    //         // now push the function symbol itself
    //         std::vector<Cmm::ValueType> ret_type;
    //         for (auto t: mNode->returnType->types) {
    //             ret_type.push_back(t);
    //         }
    //
    //         Symbol s = {
    //             .codeLine = (size_t) mNode->_virtualLineNumber,
    //             .quadLine = (size_t) context->currentLine,
    //             .scope = context->stack.size() - 2,
    //             .type = ret_type,
    //             .accept_type = accept_types,
    //             .objectType = SymbolType::Function,
    //             .name = mNode->id,
    //             .value = "(Native Func)",
    //             .useCount = 0,
    //         };
    //
    //         context->symbolTable.push_back(s);
    //
    //         context->stack.pop_back();
    //         context->returnLabels.pop_back();
    //     }
    // }

    if (auto mNode = dynamic_cast<Cmm::Control::IFNode*>(node)) {
        auto result_type = inferType(mNode->condition, context);
        std::string cond_name;
        if (result_type != Cmm::V_Bool) {
            auto _shadowNode = new Cmm::Expressions::CastNode(mNode->condition, "bool");
            auto expr = asPair(quoteStrings(writeExpression(_shadowNode, context, indentation, out)));
            _shadowNode->child = nullptr;
            delete _shadowNode; // nobody saw anything ...
            cond_name = expr.first;
        } else {
            auto expr = asPair(quoteStrings(writeExpression(mNode->condition, context, indentation, out)));
            cond_name = expr.first;
        }

        auto label = getIfLabel(context);
        auto label2 = mNode->if_false ? getIfLabel(context) : "__none__";
        writeQuad(out, indentation, "IF_FALSE", cond_name, label, "", context);
        context->stack.push_back({});
        generateQuads_recv(mNode->if_true, context, indentation + 1, out);
        if (mNode->if_false) writeQuad(out, indentation + 1, "JMP", label2, "", "", context);
        context->stack.pop_back();
        writeQuad(out, indentation, "Label", label, "", "", context);
        if (mNode->if_false) {
            context->stack.push_back({});
            generateQuads_recv(mNode->if_false, context, indentation + 1, out);
            context->stack.pop_back();
            writeQuad(out, indentation, "Label", label2, "", "", context);
        }
    }


    if (auto mNode = dynamic_cast<Cmm::Control::ForNode*>(node)) {
        auto cond  = getForCondLabel(context);
        auto exit  = getForExitLabel(context);
        auto enter = getForEnterLabel(context);
        auto inc   = getForIncLabel(context);

        if (!mNode->condition) {
            cond = enter;
        }

        context->breakLabels.push_back(exit);
        context->continueLabels.push_back(inc);
        context->stack.push_back({});

        if (mNode->init) {
            generateQuads_recv(mNode->init, context, indentation + 1, out);
        }

        if (mNode->_executeOnce) {
            writeQuad(out, indentation + 1, "JMP", enter, "", "", context);
        }

        writeQuad(out, indentation + 1, "Label", cond, "", "", context);
        if (mNode->condition) {
            auto result_type = inferType(mNode->condition, context);
            std::string cond_name;
            if (result_type != Cmm::V_Bool) {
                auto _shadowNode = new Cmm::Expressions::CastNode(mNode->condition, "bool");
                auto expr = asPair(quoteStrings(writeExpression(_shadowNode, context, indentation + 1, out)));
                _shadowNode->child = nullptr;
                delete _shadowNode; // nobody saw anything ...
                cond_name = expr.first;
            } else {
                auto expr = asPair(quoteStrings(writeExpression(mNode->condition, context, indentation + 1, out)));
                cond_name = expr.first;
            }

            writeQuad(out, indentation + 1, "IF_FALSE", cond_name, exit, "", context);
        }

        // :SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance:
        // :SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance:
        // :SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance::SOnekodance:

        writeQuad(out, indentation + 1, "Label", enter, "", "", context);
        generateQuads_recv(mNode->body, context, indentation + 1, out);

        writeQuad(out, indentation + 1, "Label", inc, "", "", context);
        if (mNode->inc) {
            generateQuads_recv(mNode->inc, context, indentation + 1, out);
        }
        writeQuad(out, indentation + 1, "JMP", cond, "", "", context);
        writeQuad(out, indentation + 1, "Label", exit, "", "", context);
        context->stack.pop_back();
        context->breakLabels.pop_back();
        context->continueLabels.pop_back();
    }

    if (auto mNode = dynamic_cast<Cmm::Control::SwitchNode*>(node)) {
        auto expr = asPair(quoteStrings(writeExpression(mNode->value, context, indentation, out)));
        auto result_type = expr.second;

        auto exit = getSwitchExitLabel(context);
        context->breakLabels.push_back(exit);
        context->stack.push_back({});

        auto next_case_label = getSwitchCaseLabel(context);
        auto next_case_cond_label = getSwitchCaseCondLabel(context);

        for (int i = 0;i < mNode->body->cases.size();i++) {
            auto _case = mNode->body->cases[i];
            std::string cond_name;
            if (_case->value) {
                auto case_type = inferType(_case->value, context);
                if (result_type != case_type) {
                    auto _shadowNode = new Cmm::Expressions::CastNode(_case->value, Cmm::ValuesHelper::ValueTypeAsString(result_type));
                    auto sub_expr = asPair(quoteStrings(writeExpression(_shadowNode, context, indentation + 1, out)));
                    _shadowNode->child = nullptr;
                    delete _shadowNode;
                    cond_name = sub_expr.first;
                } else {
                    auto sub_expr = asPair(quoteStrings(writeExpression(_case->value, context, indentation + 1, out)));
                    cond_name = sub_expr.first;
                }
            }

            auto result = getTempVarName(context);

            if (i != 0) {
                writeQuad(out, indentation + 1, "Label", next_case_cond_label, "", "", context);
                next_case_cond_label = getSwitchCaseCondLabel(context);
            }

            if (!cond_name.empty()) {
                writeQuad(out, indentation + 1, "==", cond_name, expr.first, result, context);
                writeQuad(out, indentation + 1, "IF_FALSE", result, next_case_cond_label, "", context);
            }

            if (i != 0) {
                writeQuad(out, indentation + 1, "Label", next_case_label, "", "", context);
                next_case_label = getSwitchCaseLabel(context);
            }

            generateQuads_recv(_case->body, context, indentation + 1, out);

            if (i != mNode->body->cases.size() - 1) {
                writeQuad(out, indentation + 1, "JMP", next_case_label, "", "", context);
            }
        }

        context->stack.pop_back();
        context->breakLabels.pop_back();
        writeQuad(out, indentation + 1, "Label", exit, "", "", context);
    }

    if (auto mNode = dynamic_cast<Cmm::Control::ContinueStatementNode*>(node)) {
        std::string label = "_not_in_a_looper_scope_";
        if (context->continueLabels.empty()) {
            CodeGenError err;
            err.exception = Cmm::Program::ControlError("continue cannot be used outside a looper scope").what();
            err.line = mNode->_virtualLineNumber;
            context->errors.push_back(err);
        } else {
            label = context->continueLabels.back();
        }

        writeQuad(out, indentation, "JMP", label, "", "", context);
        context->stack.back().deadCode = true;
    }

    if (auto mNode = dynamic_cast<Cmm::Control::BreakStatementNode*>(node)) {
        std::string label = "_not_in_a_breakable_scope_";
        if (context->breakLabels.empty()) {
            CodeGenError err;
            err.exception = Cmm::Program::ControlError("break cannot be used outside a looper / switch scope").what();
            err.line = mNode->_virtualLineNumber;
            context->errors.push_back(err);
        } else {
            label = context->breakLabels.back();
        }

        writeQuad(out, indentation, "JMP", label, "", "", context);
        context->stack.back().deadCode = true;
    }


    if (auto mNode = dynamic_cast<Cmm::Control::ReturnStatementNode*>(node)) {
        auto func_ret_type = std::vector({Cmm::V_Any});
        if (context->returnLabels.empty()) {
            CodeGenError err;
            err.exception = Cmm::Program::ControlError("return cannot be used outside a function scope").what();
            err.line = mNode->_virtualLineNumber;
            context->errors.push_back(err);
        } else {
            func_ret_type = context->returnLabels.back();
        }

        if (func_ret_type[0] != Cmm::V_Void) {
            if (mNode->expr) {
                auto result_type = inferType(mNode->expr, context);
                auto in_returns = std::find(func_ret_type.begin(), func_ret_type.end(), result_type);
                if (in_returns == func_ret_type.end()) {
                    CodeGenWarn err;
                    err.exception = "Implicit conversion from [" + Cmm::ValuesHelper::ValueTypeAsString(result_type) + "] to [" + Cmm::ValuesHelper::ValueTypeAsString(func_ret_type[0]) + "].";
                    err.line = node->_virtualLineNumber;
                    context->warnings.push_back(err);

                    auto _shadowNode = new Cmm::Expressions::CastNode(mNode->expr, Cmm::ValuesHelper::ValueTypeAsString(func_ret_type[0]));
                    auto expr = asPair(quoteStrings(writeExpression(_shadowNode, context, indentation, out)));
                    _shadowNode->child = nullptr;
                    delete _shadowNode;
                    writeQuad(out, indentation, "RETURN", "", "", expr.first, context);
                } else {
                    auto expr = asPair(quoteStrings(writeExpression(mNode->expr, context, indentation, out)));
                    writeQuad(out, indentation, "RETURN", "", "", expr.first, context);
                }
            } else {
                CodeGenError err;
                err.exception = Cmm::Program::ControlError("function requires a return value.").what();
                err.line = mNode->_virtualLineNumber;
                context->errors.push_back(err);
                writeQuad(out, indentation, "RETURN", "", "", "", context); // auto correct
            }
        } else {
            if (mNode->expr) {
                CodeGenError err;
                err.exception = Cmm::Program::ControlError("returning a value in a void function.").what();
                err.line = mNode->_virtualLineNumber;
                context->errors.push_back(err);
            }

            writeQuad(out, indentation, "RETURN", "", "", "", context);
        }
        context->stack.back().deadCode = true;
    }

    // macros
    if (auto mNode = dynamic_cast<Cmm::Macros::ClearMacro*>(node)) {
        context->errors.clear();
        context->warnings.clear();
    }

}

CodeGenContext* Cmm::QuadGenerator::generate(ASTNode *root, const std::string& outputPath) {
    if (!fs::exists(fs::path(outputPath).parent_path())) {
        if (!fs::create_directory(fs::path(outputPath).parent_path())) return nullptr;
    }

    auto *context = new CodeGenContext();

    std::ofstream output(outputPath);
    generateQuads_recv(root, context, 0, output);
    output.flush();
    output.close();

    return context;
}

CodeGenContext * Cmm::QuadGenerator::generate(ASTNode *root, std::ostream &output) {
    auto *context = new CodeGenContext();
    generateQuads_recv(root, context, 0, output);
    return context;
}
