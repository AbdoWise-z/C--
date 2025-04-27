
#include "Variables.h"

#include <iostream>

#include "Expressions.h"


namespace Cmm::Variables {
    VariableDeclarationNode::VariableDeclarationNode(bool isConst, std::string name, std::string type,
                                                     EvaluableNode *value) {
        this->isConst = isConst;
        this->name = std::move(name);
        this->type = std::move(type);
        this->value = value;
    }

    void VariableDeclarationNode::exec() {
        auto mType = ValuesHelper::StringToValueType(this->type);
        auto mValue = this->value->eval();
        if (mValue.type != mType) {
            // cast it
            auto temp = ValuesHelper::castTo(mValue, mType);
            ValuesHelper::Delete(mValue);
            mValue = temp;
        }

        // now that we have the name and value
        // we try to push it to the scope
        Program::createVariable(name, mValue, isConst);
#ifdef CMM_DEBUG
        std::cout << "[+]> " << name << "=" << ValuesHelper::toString(mValue) << std::endl;
#endif

    }

    VariableDeclarationNode::~VariableDeclarationNode() {
        delete value;
    }

    void VariableDeclarationNode::enterStack() {
        _curr_step_pos.push(0);
    }

    ASTNode * VariableDeclarationNode::step(ValueObject mValue) {
        int& curr_step = _curr_step_pos.top();
        if (curr_step == 0) {
            curr_step++;
            return this->value;
        }

        // seconds call: with value
        auto mType = ValuesHelper::StringToValueType(this->type);
        if (mValue.type != mType) {
            // cast it
            auto temp = ValuesHelper::castTo(mValue, mType);
            ValuesHelper::Delete(mValue);
            mValue = temp;
        }

        Program::createVariable(name, mValue, isConst);

#ifdef CMM_DEBUG
        std::cout << "[+]> " << name << "=" << ValuesHelper::toString(mValue) << std::endl;
#endif
        return nullptr;
    }


    void VariableDeclarationNode::exitStack() {
        _curr_step_pos.pop();
    }

    InferredVariableDeclarationNode::InferredVariableDeclarationNode(bool isConst, std::string name,
                                                                     EvaluableNode *value) {
        this->isConst = isConst;
        this->name = std::move(name);
        this->value = value;
    }

    void InferredVariableDeclarationNode::exec() {
        auto mValue = this->value->eval();
        Program::createVariable(name, mValue, isConst);
    }

    InferredVariableDeclarationNode::~InferredVariableDeclarationNode() {
        delete value;
    }

    void InferredVariableDeclarationNode::enterStack() {
        _curr_step_pos.push(0);
    }

    ASTNode * InferredVariableDeclarationNode::step(ValueObject mValue) {
        int& curr_step = _curr_step_pos.top();
        if (curr_step == 0) {
            curr_step++;
            return this->value;
        }

        Program::createVariable(name, mValue, isConst);

#ifdef CMM_DEBUG
        std::cout << "[+]> " << name << "=" << ValuesHelper::toString(mValue) << std::endl;
#endif
        return nullptr;
    }


    void InferredVariableDeclarationNode::exitStack() {
        _curr_step_pos.pop();
    }


    VariableAssignmentNode::VariableAssignmentNode(std::string name, EvaluableNode *value) {
        this->name = name;
        this->expr = value;
    }

    void VariableAssignmentNode::exec() {
        Program::VariableBlock& block = Program::getVariable(name);
        ValueObject& original = block.Value;
        if (block.isConst) {
            throw Program::ConstantAssignmentError(name);
        }

        auto mValue = this->expr->eval();
        if (mValue.type != original.type) {
            auto temp = ValuesHelper::castTo(mValue, original.type);
            ValuesHelper::Delete(mValue);
            mValue = temp;
        }

        ValuesHelper::Delete(original);
        original = mValue;
#ifdef CMM_DEBUG
        std::cout << "[u]> " << name << "=" << ValuesHelper::toString(mValue) << std::endl;
#endif
    }

    void VariableAssignmentNode::enterStack() {
        _curr_step_pos.push(0);
    }

    ASTNode * VariableAssignmentNode::step(ValueObject mValue) {
        Program::VariableBlock& block = Program::getVariable(name);
        ValueObject& original = block.Value;
        if (block.isConst) {
            throw Program::ConstantAssignmentError(name);
        }

        int& curr_step = _curr_step_pos.top();
        if (curr_step == 0) {
            curr_step++;
            return this->expr;
        }

        if (mValue.type != original.type) {
            auto temp = ValuesHelper::castTo(mValue, original.type);
            ValuesHelper::Delete(mValue);
            mValue = temp;
        }

        ValuesHelper::Delete(original);
        original = mValue;

#ifdef CMM_DEBUG
        std::cout << "[u]> " << name << "=" << ValuesHelper::toString(mValue) << std::endl;
#endif
        return nullptr;
    }

    void VariableAssignmentNode::exitStack() {
        _curr_step_pos.pop();
    }

    VariableAssignmentNode::~VariableAssignmentNode() = default;

    CompoundAssignmentNode::CompoundAssignmentNode(const std::string& name, const std::string &op, EvaluableNode *value) {
        auto term = new Expressions::TermNode(new Expressions::VariableNode(name), value, op);
        this->_internal = new VariableAssignmentNode(name, term);
    }

    void CompoundAssignmentNode::exec() {
        this->_internal->exec();
    }

    void CompoundAssignmentNode::enterStack() {
        _curr_step_pos.push(0);
    }

    ASTNode * CompoundAssignmentNode::step(ValueObject mValue) {
        int& curr_step = _curr_step_pos.top();
        if (curr_step == 0) {
            curr_step++;
            return this->_internal;
        }

        return nullptr;
    }

    void CompoundAssignmentNode::exitStack() {
        _curr_step_pos.pop();
    }

    CompoundAssignmentNode::~CompoundAssignmentNode() {
        delete this->_internal;
    }

    PreIncNode::PreIncNode(const std::string &name, const std::string &op) {
        this->name = name;
        this->_internal = new Expressions::TermNode(
            new Expressions::VariableNode(name),
            new Expressions::ConstantValueNode(Integer(1)),
            op == "++" ? "+" : "-");

        this->op = op;
    }

    ValueObject PreIncNode::eval() {
        auto result = _internal->eval();
        Program::VariableBlock& block = Program::getVariable(name);
        ValueObject& original = block.Value;

        if (block.isConst) {
            throw Program::ConstantAssignmentError(name);
        }

        if (result.type != original.type) {
            auto temp = ValuesHelper::castTo(result, original.type);
            ValuesHelper::Delete(result);
            result = temp;
        }

        ValuesHelper::Delete(original);
        original = ValuesHelper::clone(result);
#ifdef CMM_DEBUG
        std::cout << "[u]> " << name << "=" << ValuesHelper::toString(result) << std::endl;
#endif
        return result;
    }

    void PreIncNode::enterStack() {
        _curr_step_pos.push(0);
    }

    std::pair<ASTNode*, ValueObject> PreIncNode::step(ValueObject mValue) {
        Program::VariableBlock& block = Program::getVariable(name);
        ValueObject& original = block.Value;
        if (block.isConst) {
            throw Program::ConstantAssignmentError(name);
        }

        int& curr_step = _curr_step_pos.top();
        if (curr_step == 0) {
            curr_step++;
            return {this->_internal, ValueObject::Void()};
        }

        if (mValue.type != original.type) {
            auto temp = ValuesHelper::castTo(mValue, original.type);
            ValuesHelper::Delete(mValue);
            mValue = temp;
        }

        ValuesHelper::Delete(original);
        original = mValue;

#ifdef CMM_DEBUG
        std::cout << "[u]> " << name << "=" << ValuesHelper::toString(mValue) << std::endl;
#endif
        return {nullptr, original};
    }

    void PreIncNode::exitStack() {
        _curr_step_pos.pop();
    }

    PreIncNode::~PreIncNode() {
        delete _internal;
    }

    PostIncNode::PostIncNode(const std::string &name, const std::string &op) {
        this->name = name;
        this->_internal = new Expressions::TermNode(
            new Expressions::VariableNode(name),
            new Expressions::ConstantValueNode(Integer(1)),
            op == "++" ? "+" : "-");
        this->op = op;
    }

    ValueObject PostIncNode::eval() {
        auto result = _internal->eval();
        Program::VariableBlock& block = Program::getVariable(name);
        ValueObject& original = block.Value;
        if (block.isConst) {
            throw Program::ConstantAssignmentError(name);
        }

        ValueObject _before = original;

        if (result.type != original.type) {
            auto temp = ValuesHelper::castTo(result, original.type);
            ValuesHelper::Delete(result);
            result = temp;
        }

        original = result;
#ifdef CMM_DEBUG
        std::cout << "[u]> " << name << "=" << ValuesHelper::toString(result) << std::endl;
#endif
        return _before;
    }


    void PostIncNode::enterStack() {
        _curr_step_pos.push(0);
    }

    std::pair<ASTNode*, ValueObject> PostIncNode::step(ValueObject mValue) {
        Program::VariableBlock& block = Program::getVariable(name);
        ValueObject& original = block.Value;
        if (block.isConst) {
            throw Program::ConstantAssignmentError(name);
        }

        int& curr_step = _curr_step_pos.top();
        if (curr_step == 0) {
            curr_step++;
            return {this->_internal, ValueObject::Void()};
        }

        if (mValue.type != original.type) {
            auto temp = ValuesHelper::castTo(mValue, original.type);
            ValuesHelper::Delete(mValue);
            mValue = temp;
        }

        ValueObject _before = original;

        original = mValue;

#ifdef CMM_DEBUG
        std::cout << "[u]> " << name << "=" << ValuesHelper::toString(mValue) << std::endl;
#endif
        return {nullptr, _before};
    }

    void PostIncNode::exitStack() {
        _curr_step_pos.pop();
    }

    PostIncNode::~PostIncNode() {
        delete _internal;
    }

    DebuggerWaitEvalNode::DebuggerWaitEvalNode(EvaluableNode *internal) {
        this->_internal = internal;
        this->_lineNumber = internal->_lineNumber;

    }

    ValueObject DebuggerWaitEvalNode::eval() {
        return _internal->eval();
    }

    DebuggerWaitEvalNode::~DebuggerWaitEvalNode() = default;

    void DebuggerWaitEvalNode::enterStack() {
        _curr_step_pos.push(0);
    }

    std::pair<ASTNode *, ValueObject> DebuggerWaitEvalNode::step(ValueObject v) {
        int& curr_step = _curr_step_pos.top();
        if (curr_step == 0) {
            curr_step++;
            return {this->_internal, ValueObject::Void()};
        }

        return {nullptr, v};
    }

    void DebuggerWaitEvalNode::exitStack() {
        _curr_step_pos.pop();
    }
}
