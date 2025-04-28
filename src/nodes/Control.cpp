
#include "Control.h"
#include "Program.h"

#include <iostream>

#include "Variables.h"
#include "../MathHelper.h"

Cmm::Control::IFNode::IFNode(EvaluableNode *condition, ExecutableNode *if_true, ExecutableNode *if_false) {
    this->condition = condition;
    this->if_true = if_true;
    this->if_false = if_false;

    _lineNumber = condition->_lineNumber;
    _virtualLineNumber = condition->_virtualLineNumber;

    if (this->condition) this->condition->_parent = this;
    if (this->if_true) this->if_true->_parent = this;
    if (this->if_false) this->if_false->_parent = this;

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

Cmm::ASTNode* Cmm::Control::IFNode::step(ValueObject v) {
    int& curr_step = _curr_step_pos.top();

    if (curr_step == 0) {
        curr_step++;
        return this->condition;
    }

    if (curr_step > 1) return nullptr;

    auto result = v;
    auto bool_result = ValuesHelper::castTo(result, V_Bool);
    ValuesHelper::Delete(result);

    curr_step++;

    if (bool_result.value)
        return if_true;

    return if_false;
}

void Cmm::Control::IFNode::enterStack() {
    _curr_step_pos.push(0);
}

void Cmm::Control::IFNode::exitStack() {
    _curr_step_pos.pop();
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
    this->_executeOnce = false;

    if (this->condition) {
        _lineNumber = condition->_lineNumber;
        _virtualLineNumber = condition->_virtualLineNumber;
    }

    if (this->condition) this->condition->_parent = this;
    if (this->init)      this->init->_parent = this;
    if (this->body)      this->body->_parent = this;
    if (this->inc)       this->inc->_parent = this;
}

Cmm::Control::ForNode::ForNode(EvaluableNode *condition, ExecutableNode *init, ExecutableNode *inc,
    ExecutableNode *body, bool _executeOnce) {

    this->condition = condition;
    this->inc = inc;
    this->init = init;
    this->body = body;
    this->_executeOnce = _executeOnce;

    if (this->condition) {
        _lineNumber = condition->_lineNumber;
        _virtualLineNumber = condition->_virtualLineNumber;
    }

    if (this->condition) this->condition->_parent = this;
    if (this->init) this->init->_parent = this;
    if (this->body) this->body->_parent = this;
    if (this->inc)  this->inc->_parent = this;
}

void Cmm::Control::ForNode::exec() {
    // empty scope to capture any initialization variables
    // they shouldn't be accessible outsize the for loop
    Program::beginScope(nullptr);

    this->_shouldBreak.push(false);
    this->_shouldContinue.push(false);

    auto _inc = dynamic_cast<Program::ExpressionStatementNode*>(this->inc);
    if (_inc) _inc->_silent = true; // if it's an expression node make it silent because I hate spamming :)

    if (init) init->exec();

    bool cond = false;

    if (_executeOnce) { // basically a do-while loop
        Program::beginScope(this);

        this->_shouldBreak.top()    = false;
        this->_shouldContinue.top() = false;

        body->exec();
        Program::endScope();

        if (this->_shouldBreak.top()) {
            this->_shouldBreak.pop();
            this->_shouldContinue.pop();
            Program::endScope();
            return;
        }
    }

    if (condition) {
        auto result = condition->eval();
        auto bool_result = ValuesHelper::castTo(result, V_Bool);
        ValuesHelper::Delete(result);
        cond = bool_result.value;
    } else {
        cond = true;
    }

    while (cond) {
        Program::beginScope(this);  // begin the internal for-loop scope

        this->_shouldBreak.top()    = false;
        this->_shouldContinue.top() = false;

        body->exec();

        if (this->_shouldBreak.top()) break;
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

    this->_shouldBreak.pop();
    this->_shouldContinue.pop();
    Program::endScope();
}

Cmm::Control::ForNode::~ForNode() {
    delete condition;
    delete init;
    delete inc;
}

Cmm::ASTNode * Cmm::Control::ForNode::step(ValueObject v) {
    int& curr_step = _curr_step_pos.top();
    if (curr_step == 0) {
        // first we initialize the for-loop

        Program::beginScope(nullptr, "For-wrapper (external)");
        auto _inc = dynamic_cast<Program::ExpressionStatementNode*>(this->inc);
        if (_inc) _inc->_silent = true;
        curr_step = 1;

        if (init) {
            return init;
        }
    }

    if (curr_step == 1) {
        curr_step = 2;
        if (_executeOnce) { // basically a do-while loop
            Program::beginScope(this, "For-wrapper (internal)");
            this->_shouldBreak.top()    = false;
            this->_shouldContinue.top() = false;
            return body;
        } else {
            curr_step = 3;
        }
    }

    if (curr_step == 2) {
        // we did a do-while first loop, now close the scope
        Program::endScope();
        if (this->_shouldBreak.top()) {
            curr_step = 999;
            Program::endScope();
            return nullptr;
        }
        curr_step = 3;
    }

    before:
    if (curr_step == 3) {
        curr_step = 4;
        return condition;
    }

    if (curr_step == 4) {
        // now actually check the condition
        bool cond = false;

        if (condition) {
            auto result = v;
            auto bool_result = ValuesHelper::castTo(result, V_Bool);
            ValuesHelper::Delete(result);
            cond = bool_result.value;
        } else {
            cond = true;
        }

        if (!cond) {
            curr_step = 999;
            Program::endScope();
            return nullptr;
        }

        curr_step = 5;
        Program::beginScope(this, "For-wrapper (internal)");
        this->_shouldBreak.top()    = false;
        this->_shouldContinue.top() = false;
        return body;
    }

    if (curr_step == 5) {
        Program::endScope();
        if (this->_shouldBreak.top()) {
            curr_step = 999;
            Program::endScope();
            return nullptr;
        }
        curr_step = 3;
        if (this->inc) {
            return this->inc; // apply the increment
        } else {
            curr_step = 3;
            goto before;
        }
    }

    return nullptr;
}

void Cmm::Control::ForNode::enterStack() {
    _curr_step_pos.push(0);
    this->_shouldBreak.push(false);
    this->_shouldContinue.push(false);
}

void Cmm::Control::ForNode::exitStack() {
    _curr_step_pos.pop();

    _shouldBreak.pop();
    _shouldContinue.pop();
}

namespace Cmm::Control {
    ReturnStatementNode::ReturnStatementNode(EvaluableNode *expr) {
        this->expr = expr;
        if (this->expr) this->expr->_parent = this;
    }

    void ReturnStatementNode::exec() {
        auto func = Program::getNearestReturnPointScopeOwner();
        if (func == nullptr) {
            throw Program::ControlError("Return cannot be used outside a function scope");
        }

        if (expr) {
            auto result = expr->eval();
            func->_returnValue.top() = result;
        } else {
            func->_returnValue.top().type = V_Void;
        }

        func->_shouldReturn.top() = true;
    }

    ReturnStatementNode::~ReturnStatementNode() {
        delete expr;
    }

    BreakStatementNode::BreakStatementNode() = default;

    void BreakStatementNode::exec() {
        auto looper = Program::getNearestBreakPointScopeOwner();
        if (looper == nullptr) {
            throw Program::ControlError("break cannot be used outside a looper / switch scope");
        }

        looper->_shouldBreak.top() = true;
    }

    BreakStatementNode::~BreakStatementNode() = default;

    ContinueStatementNode::ContinueStatementNode() = default;

    void ContinueStatementNode::exec() {
        auto looper = Program::getNearestContinuePointScopeOwner();
        if (looper == nullptr) {
            throw Program::ControlError("break cannot be used outside a looper scope");
        }

        looper->_shouldContinue.top() = true;
    }

    ContinueStatementNode::~ContinueStatementNode() = default;

    SwitchNode::SwitchNode(EvaluableNode *value, SwitchBodyNode *body) {
        this->body = body;
        this->value = value;

        _lineNumber = value->_lineNumber;
        _virtualLineNumber = value->_virtualLineNumber;

        body->_parent  = this;
        value->_parent = this;
    }

    void SwitchNode::exec() {
        auto val = value->eval();
        Program::beginScope(this);

        this->_shouldBreak.push(false);

        body->exec(val);

        this->_shouldBreak.pop();

        Program::endScope();
        ValuesHelper::Delete(val);
    }

    SwitchNode::~SwitchNode() {
        delete body;
        delete value;
    }

    void SwitchNode::enterStack() {
        _curr_step_pos.push(0);
        _shouldBreak.push(false);
    }

    ASTNode * SwitchNode::step(ValueObject v) {
        int& curr_step = _curr_step_pos.top();
        if (curr_step == 0) {
            Program::beginScope(this);
            curr_step = 1;
            return value;
        }

        if (curr_step == 1) {
            curr_step = 2;
            body->_curr_value.push(v);
            return body;
        }

        auto val = body->_curr_value.top();
        ValuesHelper::Delete(val);
        body->_curr_value.pop();
        Program::endScope();

        return nullptr;
    }

    void SwitchNode::exitStack() {
        _shouldBreak.pop();
        _curr_step_pos.pop();
    }

    SwitchBodyNode::SwitchBodyNode(SwitchBodyNode *prev, SwitchCaseNode *next) {
        cases.clear();

        if (prev) {
            cases = prev->cases;
            prev->cases.clear();
            delete prev;
        }

        if (next) cases.push_back(next);

        for (auto& _case: cases) {
            _case->_parent = this;
        }
    }

    void SwitchBodyNode::exec(ValueObject v) const {
        bool found_match = false;
        auto break_point = Program::getNearestBreakPointScopeOwner();

        if (break_point == nullptr) {
            throw Program::ControlError("Switch body cannot be used outside a switch scope");
        }

        for (const auto _c : cases) {
            if (break_point->_shouldBreak.top()) break;
            found_match = _c->exec(v, found_match);
        }
    }

    SwitchBodyNode::~SwitchBodyNode() {
        for (const auto _c : cases) {
            delete _c;
        }
    }

    void SwitchBodyNode::enterStack() {
        _curr_step_pos.push(0);
        _curr_step_pos_internal.push(0);
        _curr_matched.push(false);
        _created_nodes.push({});
    }

    ASTNode * SwitchBodyNode::step(ValueObject v) {
        int& curr_step = _curr_step_pos.top();
        if (curr_step >= cases.size()) {
            return nullptr;
        }

        auto break_point = Program::getNearestBreakPointScopeOwner();
        auto& curr_case = cases[curr_step];

        if (!_curr_matched.top()) {
            int& curr_step_internal = _curr_step_pos_internal.top();

            if (!curr_case->value) { // default case
                _curr_matched.top() = true;
                return step(v);
            }

            if (curr_step_internal == 0) {
                curr_step_internal = 1;
                auto _n = new Variables::DebuggerWaitEvalNode(cases[curr_step]->value);
                _created_nodes.top().push_back(_n);
                return _n;
            }

            if (curr_step_internal == 1) {
                if (MathHelper::equal(v, _curr_value.top()).value) {
                    ValuesHelper::Delete(v);
                    _curr_matched.top() = true;
                    return step(v);
                }
                ValuesHelper::Delete(v);
                curr_step_internal = 0;
                curr_step ++;
                return step(v);
            }
        } else {

            if (break_point->_shouldBreak.top()) {
                return nullptr;
            }
            curr_step ++;
            return curr_case->body;
        }

        return nullptr;
    }

    void SwitchBodyNode::exitStack() {
        _curr_step_pos.pop();
        _curr_step_pos_internal.pop();
        _curr_matched.pop();

        for (auto n: _created_nodes.top()) {
            delete n;
        }
        _created_nodes.pop();
    }

    SwitchCaseNode::SwitchCaseNode(ExecutableNode *body, EvaluableNode *value) {
        this->body = body;
        this->value = value;

        if (body)  body->_parent  = this;
        if (value) value->_parent = this;
    }

    bool SwitchCaseNode::exec(ValueObject v, bool b) const {
        if (!b && this->value) { // if no other case above us has matched, and we are not the default case
            // then we must check
            auto val = this->value->eval();
            if (!MathHelper::equal(v, val).value) {
                // not this case .. sadge
                ValuesHelper::Delete(val);
                return false;
            }

            ValuesHelper::Delete(val);
        }

        body->exec();
        return true;
    }

    SwitchCaseNode::~SwitchCaseNode() {
        delete body;
        delete value;
    }
}
