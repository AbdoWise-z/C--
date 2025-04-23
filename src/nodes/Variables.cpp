
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

    VariableAssignmentNode::~VariableAssignmentNode() = default;

    CompoundAssignmentNode::CompoundAssignmentNode(const std::string& name, const std::string &op, EvaluableNode *value) {
        auto term = new Expressions::TermNode(new Expressions::VariableNode(name), value, op);
        this->_internal = new VariableAssignmentNode(name, term);
    }

    void CompoundAssignmentNode::exec() {
        this->_internal->exec();
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

    PostIncNode::~PostIncNode() {
        delete _internal;
    }
}
