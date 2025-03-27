//
// Created by xabdomo on 3/27/25.
//

#include "Control.h"
#include "Program.h"

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

Cmm::Control::ForNode::ForNode(EvaluableNode *condition, ExecutableNode *init, ExecutableNode *inc, ExecutableNode *body) {
    this->condition = condition;
    this->inc = inc;
    this->init = init;
    this->body = body;
}

Cmm::Control::ForNode::ForNode(EvaluableNode *condition, ExecutableNode *init, ExecutableNode *inc,
    ExecutableNode *body, bool _executeOnce) {

    this->condition = condition;
    this->inc = inc;
    this->init = init;
    this->body = body;
    this->_executeOnce = _executeOnce;

}

void Cmm::Control::ForNode::exec() {
    // empty scope to capture any initialization variables
    // they shouldn't be accessible outsize the for loop
    Program::beginScope(nullptr);

    if (init) init->exec();

    bool cond = false;

    if (condition) {
        auto result = condition->eval();
        auto bool_result = ValuesHelper::castTo(result, V_Bool);
        ValuesHelper::Delete(result);
        cond = bool_result.value;
    } else {
        cond = true;
    }

    if (_executeOnce) { // basically a do-while loop
        Program::beginScope(this);
        body->exec();
        Program::endScope();
    }

    while (cond) {
        Program::beginScope(this);  // begin the internal for-loop scope
        this->_shouldBreak = false;
        this->_shouldContinue = false;

        body->exec();

        if (this->_shouldBreak) break;
        if (inc) inc->exec();

        if (condition) {
            auto result = condition->eval();
            auto bool_result = ValuesHelper::castTo(result, V_Bool);
            ValuesHelper::Delete(result);
            cond = bool_result.value;
        } else {
            cond = true;
        }

        Program::endScope();
    }
    Program::endScope();
}

Cmm::Control::ForNode::~ForNode() {
    delete condition;
    delete init;
    delete inc;
}

namespace Cmm::Control {
    ReturnStatementNode::ReturnStatementNode(EvaluableNode *expr) {
        this->expr = expr;
    }

    void ReturnStatementNode::exec() {
        auto func = Program::getNearestReturnPointScopeOwner();
        if (func == nullptr) {
            throw Program::ControlError("Return cannot be used outside a function scope");
        }

        if (expr) {
            auto result = expr->eval();
            func->_returnValue = result;
        } else {
            func->_returnValue.type = V_Void;
        }

        func->_shouldReturn = true;
    }

    ReturnStatementNode::~ReturnStatementNode() {
        delete expr;
    }

    BreakStatementNode::BreakStatementNode() = default;

    void BreakStatementNode::exec() {
        auto looper = Program::getNearestBreakPointScopeOwner();
        if (looper == nullptr) {
            throw Program::ControlError("break cannot be used outside a looper scope");
        }

        looper->_shouldBreak = true;
    }

    BreakStatementNode::~BreakStatementNode() = default;

    ContinueStatementNode::ContinueStatementNode() = default;

    void ContinueStatementNode::exec() {
        auto looper = Program::getNearestContinuePointScopeOwner();
        if (looper == nullptr) {
            throw Program::ControlError("break cannot be used outside a looper scope");
        }

        looper->_shouldContinue = true;
    }

    ContinueStatementNode::~ContinueStatementNode() = default;
}
