
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
        this->_shouldReturn = {};

        this->handler = nullptr;

        this->_lineNumber = arguments->_lineNumber;
        this->_virtualLineNumber = arguments->_virtualLineNumber;

        if (this->arguments) this->arguments->_parent = this;
        if (this->function) this->function->_parent = this;
        if (this->returnType) this->returnType->_parent = this;

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
        _shouldReturn.push(false);
        _returnValue.push({
            V_Void,
            nullptr
        });

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
            _returnValue.top() = handler({id, args}, params);        // call native instead
        }

        Program::endScope();

        auto result = _returnValue.top();

        _returnValue.pop();
        _shouldReturn.pop();

        // now check the return value
        if (returnType->types.contains(result.type)) {
            // successful execution
            return result;
        } else {
            for (auto type : Program::conversionPriority) {
                if (returnType->types.contains(type)) {
                    // convert to this type and move on :)
                    ValueObject temp = ValuesHelper::castTo(result, type);
                    ValuesHelper::Delete(result);
                    result = temp;
                    return result;
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
            ): id(std::move(id)), type(std::move(type)), defaultValue(defaultValue) {
        if (this->defaultValue) this->defaultValue->_parent = this;
    }

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

        for (auto& _argument: arguments) {
            _argument->_parent = this;
        }
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

        for (auto& _param: params) {
            _param->_parent = this;
        }
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

        this->funcParam->_parent = this;
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

    void FunctionCallNode::enterStack() {
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

        _curr_params.push(params);
        _curr_func.push(func);
        _curr_step_pos.push(0);
        _marker_node.push(new ASTNode());

        _marker_node.top()->_parent = this;
        _marker_node.top()->_lineNumber = func->_lineNumber;
        _marker_node.top()->_virtualLineNumber = func->_virtualLineNumber;
    }

    std::pair<ASTNode *, ValueObject> FunctionCallNode::step(ValueObject) {
        int& curr_step = _curr_step_pos.top();
        auto func = _curr_func.top();
        auto& params = _curr_params.top();
        auto marker = _marker_node.top();

        if (curr_step == 0) {
            curr_step++;
            func->_shouldReturn.push(false);
            func->_returnValue.push(ValueObject::Void());

            return {marker, ValueObject::Void()};
        }

        if (curr_step == 1) {
            // now we need check the underlying function type
            // if it's a native function .. then we call it
            // and that's it, otherwise we iterate
            curr_step++;

            if (func->function) {
                // normal function
                Program::beginScope(func);
                for (int i = 0;i < func->arguments->arguments.size();i++) {
                    Program::createVariable(func->arguments->arguments[i]->id, params[i]);
                }

                return {func->function, ValueObject::Void()};
            } else {
                // native function
                Program::beginScope(func);
                for (int i = 0;i < func->arguments->arguments.size();i++) {
                    Program::createVariable(func->arguments->arguments[i]->id, params[i]);
                }

                std::vector<ValueType> args;
                for (auto item: func->arguments->arguments) {
                    args.push_back(ValuesHelper::StringToValueType(item->type));
                }

                func->_returnValue.top() = func->handler({id, args}, params);
                func->_shouldReturn.top() = true;
            }
        }

        // we are done
        Program::endScope();

        auto result = func->_returnValue.top();

        func->_returnValue.pop();
        func->_shouldReturn.pop();

        return {nullptr, result };
    }

    void FunctionCallNode::exitStack() {
        _curr_func.pop();
        _curr_params.pop();
        _curr_step_pos.pop();
        _marker_node.pop();
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