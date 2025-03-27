//
// Created by xabdomo on 3/27/25.
//

#include "Variables.h"

#include <iostream>


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
        Program::createVariable(name, mValue);
        // fixme: constants are treated as normal values .. which is well .. wrong ..

        std::cout << "[+]> " << name << "=" << ValuesHelper::toString(mValue) << std::endl;
    }

    VariableDeclarationNode::~VariableDeclarationNode() = default;


    VariableAssignmentNode::VariableAssignmentNode(std::string name, EvaluableNode *value) {
        this->name = name;
        this->expr = value;
    }

    void VariableAssignmentNode::exec() {
        ValueObject& original = Program::getVariable(name);
        auto mValue = this->expr->eval();
        if (mValue.type != original.type) {
            auto temp = ValuesHelper::castTo(mValue, original.type);
            ValuesHelper::Delete(original);
            mValue = temp;
        }

        ValuesHelper::Delete(original);
        original = mValue;
        std::cout << "[u]> " << name << "=" << ValuesHelper::toString(mValue) << std::endl;
    }

    VariableAssignmentNode::~VariableAssignmentNode() = default;
}
