//
// Created by xabdomo on 3/27/25.
//

#include "Control.h"

#include <iostream>

Cmm::Control::IFNode::IFNode(EvaluableNode *condition, ExecutableNode *if_true, ExecutableNode *if_false) {
    this->condition = condition;
    this->if_true = if_true;
    this->if_false = if_false;
}

void Cmm::Control::IFNode::exec() {
    auto result = condition->eval();
    auto bool_result = ValuesHelper::castTo(result, V_Bool);
    ValuesHelper::Delete(result);

    if (bool_result.value) {
        this->if_true->exec();
    } else {
       if (if_false != nullptr) if_false->exec();
    }
}

Cmm::Control::IFNode::~IFNode() {
    delete condition;
    delete if_true;
    delete if_false;
}
