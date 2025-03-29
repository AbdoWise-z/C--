//
// Created by xabdomo on 3/26/25.
//

#include "Program.h"

#include <iostream>
#include <map>
#include <thread>
#include <shared_mutex>
#include <utility>
#include <vector>

#include "Control.h"
#include "Expressions.h"
#include "Functional.h"

namespace Namespace::Program {
    static std::map<std::thread::id, ProgramBlock> _programs;
    static std::shared_mutex _programs_mutex;

    std::vector<ValueType> conversionPriority = {
        V_String,
        V_Complex,
        V_Real,
        V_Integer,
        V_Bool
    };

    static std::string stringfy(FunctionSignature sig) {
        std::string args;
        for (int i = 0;i < sig.second.size();i++) {
            args += ValuesHelper::ValueTypeAsString(sig.second[i]);
            if (i != sig.second.size() - 1) {
                args += ", ";
            }
        }

        return sig.first + "(" + args + ")";
    }

    ProgramBlock& getCurrentProgram() {
        auto this_thread = std::this_thread::get_id();
        _programs_mutex.lock_shared();
        auto it = _programs.find(this_thread);
        if (it == _programs.end()) {
            _programs_mutex.unlock_shared();
            _programs_mutex.lock();
            it = _programs.find(this_thread);
            if (it != _programs.end()) return it->second;
            _programs[this_thread] = ProgramBlock();
            it = _programs.find(this_thread);
            _programs_mutex.unlock();
            return it->second;
        }

        _programs_mutex.unlock_shared();
        return it->second;
    }

    void pushModule(const std::string & m) {
        getCurrentProgram().moduleStack.push_back(m);
    }

    void popModule() {
        getCurrentProgram().moduleStack.pop_back();
    }

    std::string getModule() {
        return getCurrentProgram().moduleStack.back();
    }

    void beginScope(ASTNode *owner) {
        getCurrentProgram().stack.push_back({
            .variables = {},
            .functions = {},
            .owner = owner,
        });
    }

    void endScope() {
        getCurrentProgram().stack.pop_back();
    }

    template <typename T>
    T* getNearstScopeOwnerOfType() {
        ProgramBlock& block = getCurrentProgram();
        int scope = block.stack.size() - 1;
        while (scope >= 0) {
            auto owner = block.stack[scope].owner;
            scope --;

            if (owner == nullptr) continue;
            auto cast = dynamic_cast<T*>(owner);
            if (cast != nullptr) return cast;
        }

        return nullptr;
    }

    Control::BreakPointNode * getNearestBreakPointScopeOwner() {
        return getNearstScopeOwnerOfType<Control::BreakPointNode>();
    }

    Control::ContinuePointNode * getNearestContinuePointScopeOwner() {
        return getNearstScopeOwnerOfType<Control::ContinuePointNode>();
    }

    Control::ReturnPointNode * getNearestReturnPointScopeOwner() {
        return getNearstScopeOwnerOfType<Control::ReturnPointNode>();
    }


    void createVariable(const std::string& name, Cmm::ValueObject val, bool isConst) {
        ProgramBlock& block = getCurrentProgram();
        if (block.stack.empty()) {
            throw NoStackError();
        }

        Scope& scope = block.stack.back();
        auto it1 = scope.variables.find(name);
        if (it1 != scope.variables.end()) {
            throw AlreadyDefinedError(name);
        }

        scope.variables[name] = {
            .Value = val,
            .isConst = isConst
        };
    }

    static VariableBlock& resolveRef(int scope, ValueObject val) {
        ProgramBlock& block = getCurrentProgram();
        while (scope >= 0) {
            std::string next_target = *static_cast<std::string*>(val.value);
            Scope& _s = block.stack[scope];
            auto it = _s.variables.find(next_target);
            if (it != _s.variables.end()) {
                VariableBlock& block = it->second;
                ValueObject& obj = block.Value;

                if (obj.type != V_Ref) {
                    return block;  // found the target
                }
                val = obj;
            }

            scope --;
        }

        std::string next_target = *static_cast<std::string*>(val.value);

        throw VariableNotFoundError("[Ref: " + next_target + "]");
    }

    VariableBlock & getVariable(const std::string &name) {
        ProgramBlock& block = getCurrentProgram();

        // search scopes from bottom to top. and try to find the variable
        int scope = block.stack.size() - 1;
        while (scope >= 0) {
            auto it = block.stack[scope].variables.find(name);
            if (it != block.stack[scope].variables.end()) {
                VariableBlock& block = it->second;
                ValueObject& obj = block.Value;

                if (obj.type != V_Ref) {
                    return block;
                }
                return resolveRef(scope - 1, obj);
            }
            scope --;
        }

        throw VariableNotFoundError(name);
    }

    void createFunction(const FunctionSignature &signature, Functional::FunctionNode* node) {
        ProgramBlock& block = getCurrentProgram();
        if (block.stack.empty()) {
            throw NoStackError();
        }

        Scope& scope = block.stack.back();

        auto it1 = scope.functions.find(signature);
        if (it1 != scope.functions.end()) {
            throw AlreadyDefinedError(stringfy(signature));
        }

        auto it2 = block.native_functions.find(signature);
        if (it2 != block.native_functions.end()) {
            throw AlreadyDefinedError(stringfy(signature));
        }

        scope.functions[signature] = node;
    }

    void createFunction(const FunctionSignature &signature, NativeFunction handler) {
        ProgramBlock& block = getCurrentProgram();
        if (block.stack.empty()) {
            throw NoStackError();
        }

        Scope& scope = block.stack.back();

        auto it1 = block.native_functions.find(signature);
        if (it1 != block.native_functions.end()) {
            throw AlreadyDefinedError(stringfy(signature));
        }

        auto it2 = scope.functions.find(signature);
        if (it2 != scope.functions.end()) {
            throw AlreadyDefinedError(stringfy(signature));
        }

        block.native_functions[signature] = handler;
    }

    void validateNativeExists(const FunctionSignature &signature) {
        ProgramBlock& block = getCurrentProgram();
        if (block.stack.size() > 1) {
            // not in the top level
            throw NativeError("Native functions can only be created on the top level of the program.");
        }

        auto it = block.native_functions.find(signature);
        if (it == block.native_functions.end()) {
            throw FunctionNotFoundError(stringfy(signature) + ":native");
        }
    }

    static ValueObject callFunctionNative(const FunctionSignature& signature, const std::vector<ValueObject>& params) {
        ProgramBlock& block = getCurrentProgram();

        auto it = block.native_functions.find(signature);
        if (it != block.native_functions.end()) {
            const NativeFunction obj = it->second;
            // do the actual calling
            const ValueObject result = obj(signature, params);
            return result;
        }

        throw FunctionNotFoundError(stringfy(signature));
    }


    ValueObject callFunction(const FunctionSignature& signature, const std::vector<ValueObject>& params) {

        try {
            return callFunctionNative(signature, params);
        } catch (FunctionNotFoundError& e) {
            // do nothing
        }

        // bottom up search the function signature
        ProgramBlock& block = getCurrentProgram();
        int scope = block.stack.size() - 1;
        while (scope >= 0) {
            auto it = block.stack[scope].functions.find(signature);
            if (it != block.stack[scope].functions.end()) {
                Functional::FunctionNode* obj = it->second;
                // do the actual calling
                ValueObject result = obj->exec(params);
                return result;
            }
            scope --;
        }

        throw FunctionNotFoundError(stringfy(signature));
    }

    NoStackError::NoStackError() = default;

    const char * NoStackError::what() const noexcept {
        return "No stack found while trying to create a variable or a function";
    }

    AlreadyDefinedError::AlreadyDefinedError(std::string id) : id(std::move(id)) {}

    const char * AlreadyDefinedError::what() const noexcept {
        static std::string err = "Object with id: " + id + " already defined.";
        return err.c_str();
    }

    ConstantAssignmentError::ConstantAssignmentError(std::string id) : id(std::move(id)) {}

    const char * ConstantAssignmentError::what() const noexcept {
        static std::string err = "Object with id: " + id + " is constant, unable to re-assign.";
        return err.c_str();
    }

    VariableNotFoundError::VariableNotFoundError(std::string id) : id(std::move(id)) {}

    const char * VariableNotFoundError::what() const noexcept {
        static std::string err = "Object with id: " + id + " not found.";
        return err.c_str();
    }

    FunctionNotFoundError::FunctionNotFoundError(std::string id) : id(std::move(id)) {}

    const char * FunctionNotFoundError::what() const noexcept {
        static std::string err = "Function with signature: " + id + " not found.";
        return err.c_str();
    }

    ControlError::ControlError(std::string msg) {
        this->msg = std::move(msg);
    }

    const char * ControlError::what() const noexcept {
        return msg.c_str();
    }

    NativeError::NativeError(std::string msg) {
        this->msg = std::move(msg);
    }

    const char * NativeError::what() const noexcept {
        return msg.c_str();
    }


    ProgramNode::ProgramNode(ExecutableNode *source) {
        this->source = source;
    }

    void ProgramNode::exec() {
        beginScope();

        source->exec();

        endScope();
    }



    ExpressionStatementNode::ExpressionStatementNode(EvaluableNode *value) {
        expr = value;
    }

    void ExpressionStatementNode::exec() {
        auto mValue = this->expr->eval();
        if (mValue.type != V_Void && mValue.type != V_Ref && mValue.type != V_Error)
            std::cout << "[e]> expr[" << ValuesHelper::ValueTypeAsString(mValue.type) << "]" << "=" << ValuesHelper::toString(mValue) << std::endl;
        ValuesHelper::Delete(mValue);
    }

    StatementListNode::StatementListNode(StatementListNode *other, ExecutableNode *next) {
        this->statements.clear();
        if (other) {
            this->statements = other->statements;
            other->statements.clear();
            delete other;
        }

        if (next)
            statements.push_back(next);
    }

    StatementListNode::~StatementListNode() {
        for (auto item: statements) {
            delete item;
        }
    }

    void StatementListNode::exec() {
        auto ret = getNearestReturnPointScopeOwner();
        auto brk = getNearestBreakPointScopeOwner();
        auto cnt = getNearestContinuePointScopeOwner();

        for (auto item: statements) {
            if (ret && ret->_shouldReturn)   break;
            if (brk && brk->_shouldBreak)    break;
            if (cnt && cnt->_shouldContinue) break;
            item->exec();
        }
    }

    ScopeNode::ScopeNode(ExecutableNode *node) {
        this->statements = node;
    }

    void ScopeNode::exec() {
        beginScope(nullptr);
        if (statements) statements->exec();
        endScope();
    }

    ScopeNode::~ScopeNode() {
        delete statements;
    }
}
