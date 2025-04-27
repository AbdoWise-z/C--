
#ifndef CONTROL_H
#define CONTROL_H

#include <stack>
#include <vector>

#include "../config.h"
#include "AST.h"

namespace Namespace::Control {
    class IFNode: public virtual ExecutableNode, public virtual StepOverNode, public virtual DebuggerWaitToStepNode {
    public:
        ExecutableNode* if_true;
        ExecutableNode* if_false;
        EvaluableNode* condition;

        // debugging
        std::stack<int> _curr_step_pos;

        IFNode(EvaluableNode* condition, ExecutableNode* if_true, ExecutableNode* if_false);
        void exec() override;
        ASTNode *step(ValueObject) override;
        void enterStack() override;
        void exitStack() override;
        ~IFNode() override;
    };

    class ReturnPointNode: virtual public ASTNode {
    public:
        std::stack<bool> _shouldReturn;
        std::stack<ValueObject> _returnValue;
    };

    class BreakPointNode: virtual public ASTNode {
    public:
        std::stack<bool> _shouldBreak;
    };

    class ContinuePointNode: virtual public ASTNode {
    public:
        std::stack<bool> _shouldContinue;
    };

    class ForNode: public ExecutableNode, ContinuePointNode, BreakPointNode, StepOverNode {
    public:
        // standard for loop stuff
        ExecutableNode* init;
        ExecutableNode* inc;
        EvaluableNode* condition;
        ExecutableNode* body;
        bool _executeOnce = false;

        // debugging
        std::stack<int> _curr_step_pos;

        ForNode(EvaluableNode* condition, ExecutableNode* init, ExecutableNode* inc, ExecutableNode* body);
        ForNode(EvaluableNode* condition, ExecutableNode* init, ExecutableNode* inc, ExecutableNode* body, bool _executeOnce);
        void exec() override;
        ~ForNode() override;

        ASTNode *step(ValueObject) override;
        void enterStack() override;
        void exitStack() override;
    };

    class ReturnStatementNode: public ExecutableNode {
    public:
        EvaluableNode* expr;
        explicit ReturnStatementNode(EvaluableNode* expr);
        void exec() override;
        ~ReturnStatementNode() override;
    };

    class BreakStatementNode: public ExecutableNode {
    public:
        BreakStatementNode();
        void exec() override;
        ~BreakStatementNode() override;
    };

    class ContinueStatementNode: public ExecutableNode {
    public:
        ContinueStatementNode();
        void exec() override;
        ~ContinueStatementNode() override;
    };

    class SwitchBodyNode;

    class SwitchNode: public ExecutableNode, BreakPointNode, StepOverNode {
    public:
        EvaluableNode* value;
        SwitchBodyNode* body;
        SwitchNode(EvaluableNode* value, SwitchBodyNode* body);
        void exec() override;
        ~SwitchNode() override;

        // debugging
        std::stack<int> _curr_step_pos;

        void enterStack() override;
        ASTNode* step(ValueObject) override;
        void exitStack() override;
    };

    class SwitchCaseNode;

    class SwitchBodyNode: virtual public StepOverNode {
    public:
        std::stack<ValueObject> _curr_value;
        std::vector<SwitchCaseNode*> cases;
        SwitchBodyNode(SwitchBodyNode* prev, SwitchCaseNode* next);
        void exec(ValueObject) const;
        ~SwitchBodyNode() override;

        // debugging
        std::stack<int> _curr_step_pos;
        std::stack<int> _curr_step_pos_internal;
        std::stack<bool> _curr_matched;
        std::stack<std::vector<ASTNode*>> _created_nodes;

        void enterStack() override;
        ASTNode* step(ValueObject) override;
        void exitStack() override;
    };

    class SwitchCaseNode: public ASTNode {
    public:
        ExecutableNode* body;
        EvaluableNode* value;
        SwitchCaseNode(ExecutableNode* body, EvaluableNode* value);
        bool exec(ValueObject, bool) const;
        ~SwitchCaseNode() override;
    };
}



#endif //CONTROL_H
