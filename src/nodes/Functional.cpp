
#include "Functional.h"

#include <utility>


namespace Cmm::Functional {


    FunctionDeclarationNode::FunctionDeclarationNode(FunctionArgumentListNode *arguments,
        Program::StatementListNode *function, std::string id, Typing::TypeListNode *returnType) {

        this->arguments = arguments;
        this->function = function;
        this->id = std::move(id);
        this->returnType = returnType;

        this->_returnValue = {};
        this->_shouldReturn = false;
    }

    void FunctionDeclarationNode::exec() {
        std::vector<ValueType> arguments_t;
        std::vector<bool>      arguments_o;
        for (auto arg: arguments->arguments) {
            arguments_t.push_back(ValuesHelper::StringToValueType(arg->type));
            arguments_o.push_back(arg->defaultValue != nullptr);
        }

        if (this->function) { // an actual function
            Program::createFunction(id, {arguments_t, arguments_o}, this);
        } else { // a native function
            Program::attachNativeFunctionDefinition(id, {arguments_t, arguments_o}, this);
        }
    }

    ValueObject FunctionDeclarationNode::invoke(const std::vector<ValueObject> & params) {
        Program::beginScope(this);
        _shouldReturn = false;
        _returnValue = {
            V_Void,
            nullptr
        };

        // push in params into the stack;
        for (int i = 0;i < arguments->arguments.size();i++) {
            Program::createVariable(arguments->arguments[i]->id, params[i]);
        }

        if (this->function) {
            this->function->exec(); // will auto store in _returnValue
        } else {
            std::vector<ValueType> args;
            for (auto item: arguments->arguments) {
                args.push_back(ValuesHelper::StringToValueType(item->type));
            }
            _returnValue = handler({id, args}, params);        // call native instead
        }

        Program::endScope();


        // now check the return value
        if (returnType->types.contains(_returnValue.type)) {
            // successful execution
            return _returnValue;
        } else {
            for (auto type : Program::conversionPriority) {
                if (returnType->types.contains(type)) {
                    // convert to this type and move on :)
                    ValueObject temp = ValuesHelper::castTo(_returnValue, type);
                    ValuesHelper::Delete(_returnValue);
                    _returnValue = temp;
                    return _returnValue;
                }
            }
        }

        throw Program::ControlError("Function cannot return due to type missmatch");
    }

    FunctionDeclarationNode::~FunctionDeclarationNode() {
        delete this->function;
        delete this->returnType;
        delete this->arguments;
    }

    // NativeFunctionDeclarationNode::NativeFunctionDeclarationNode(FunctionArgumentListNode *arguments,
    //     Typing::TypeListNode *returnType, std::string id) {
    //     this->id = std::move(id);
    //     this->arguments = arguments;
    //     this->returnType = returnType;
    // }
    //
    // void NativeFunctionDeclarationNode::exec() {
    //     // validation only the actual binging happens on the c-code side
    //     std::vector<ValueType> args;
    //     for (auto item: arguments->arguments) {
    //         args.push_back(ValuesHelper::StringToValueType(item->type));
    //     }
    //
    //     std::pair sig = { id, args};
    //
    //     Program::validateNativeExists(sig);
    // }
    //
    // NativeFunctionDeclarationNode::~NativeFunctionDeclarationNode() {
    //     delete arguments;
    //     delete returnType;
    // }

    FunctionArgumentNode::FunctionArgumentNode(std::string id, std::string type) : id(std::move(id)), type(std::move(type)) {
        defaultValue = nullptr;
    }

    FunctionArgumentNode::FunctionArgumentNode
        (
            std::string id,
            std::string type,
            EvaluableNode* defaultValue
            ): id(std::move(id)), type(std::move(type)), defaultValue(defaultValue) {}

    ValueObject FunctionArgumentNode::getDefaultValue() const {
        return defaultValue->eval();
    }

    bool FunctionArgumentNode::hasDefaultValue() const {
        return defaultValue != nullptr;
    }

    FunctionArgumentNode::~FunctionArgumentNode() {
        delete defaultValue;
    }

    FunctionArgumentListNode::FunctionArgumentListNode(FunctionArgumentListNode *other, FunctionArgumentNode *next) {
        arguments.clear();
        if (other) {
            arguments = other->arguments;
            other->arguments.clear();
            delete other;
        }

        if (next)
            arguments.push_back(next);
    }

    FunctionArgumentListNode::~FunctionArgumentListNode() {
        for (auto item: this->arguments) {
            delete item;
        }
    }

    FunctionParamListNode::FunctionParamListNode(FunctionParamListNode *other, EvaluableNode *next) {
        params.clear();
        if (other) {
            params = other->params;
            other->params.clear();
            delete other;
        }

        if (next)
            params.push_back(next);
    }

    std::vector<ValueObject> FunctionParamListNode::getParams() const {
        std::vector<ValueObject> result;
        for (auto item: params) {
            result.push_back(item->eval());
        }
        return result;
    }

    FunctionParamListNode::~FunctionParamListNode() {
        for (auto item: this->params) {
            delete item;
        }
    }

    FunctionCallNode::FunctionCallNode(std::string id, FunctionParamListNode *funcParam) {
        this->id = std::move(id);
        this->funcParam = funcParam;
        if (!this->funcParam) {
            this->funcParam = new FunctionParamListNode(nullptr, nullptr);
        }
    }

    FunctionCallNode::~FunctionCallNode() {
        delete funcParam;
    }

    ValueObject FunctionCallNode::eval() {
        auto params = funcParam->getParams();
        std::vector<ValueType> types;
        for (auto item: params) {
            types.push_back(item.type);
        }

        std::pair sig = {id, types};
        auto func_pair = Program::getFunction(sig);
        auto func = func_pair.first;
        for (int i = 0; i < func_pair.second.size(); ++i) {
            if (!func_pair.second[i]) {
                // we need to set it
                auto value = func->arguments->arguments[i]->defaultValue->eval();
                params.insert(params.begin() + i, value);
            }
        }

        return func->invoke(params);
    }


    // FunctionNode::FunctionNode(FunctionArgumentListNode *arguments, Program::StatementListNode *function, std::string id, Typing::TypeListNode *returnType) {
    //     this->arguments = arguments;
    //     this->function = function;
    //     this->id = std::move(id);
    //     this->returnType = returnType;
    //
    //     this->_returnValue = {};
    //     this->_shouldReturn = false;
    // }
    //
    // void FunctionNode::decl() {
    //     // declare this function to the scope
    //     std::vector<ValueType> args;
    //     for (auto item: arguments->arguments) {
    //         args.push_back(ValuesHelper::StringToValueType(item->type));
    //     }
    //
    //     std::pair sig = { id, args};
    //     Program::createFunction(sig, this);
    // }
    //
    // ValueObject FunctionNode::exec(const std::vector<ValueObject>& params) {
    //     _shouldReturn = false;
    //     _returnValue = {
    //         V_Void,
    //         nullptr
    //     };
    //
    //     Program::beginScope(this);
    //
    //     // push in params into the stack;
    //     for (int i = 0;i < arguments->arguments.size();i++) {
    //         Program::createVariable(arguments->arguments[i]->id, params[i]);
    //     }
    //
    //     this->function->exec();
    //
    //     Program::endScope();
    //
    //     // now check the return value
    //     if (returnType->types.contains(_returnValue.type)) {
    //         // successful execution
    //         return _returnValue;
    //     } else {
    //         for (auto type : Program::conversionPriority) {
    //             if (returnType->types.contains(type)) {
    //                 // convert to this type and move on :)
    //                 ValueObject temp = ValuesHelper::castTo(_returnValue, type);
    //                 ValuesHelper::Delete(_returnValue);
    //                 _returnValue = temp;
    //                 return _returnValue;
    //             }
    //         }
    //     }
    //
    //     throw Program::ControlError("Function cannot return due to type missmatch");
    // }
    //
    // FunctionNode::~FunctionNode() {
    //     delete this->function;
    //     delete this->returnType;
    //     delete this->arguments;
    // }
}