//
// Created by xabdomo on 3/27/25.
//

#ifndef CONTROL_H
#define CONTROL_H

#include <vector>

#include "../config.h"
#include "AST.h"

namespace Namespace::Control {
    class IFNode: public virtual ExecutableNode, public virtual StepOverNode {
    public:
        ExecutableNode* if_true;
        ExecutableNode* if_false;
        EvaluableNode* condition;
        int _curr_step_pos = 0;

        IFNode(EvaluableNode* condition, ExecutableNode* if_true, ExecutableNode* if_false);
        void exec() override;
        ASTNode *step() override;
        void prepare() override;
        ~IFNode() override;
    };

    class ReturnPointNode: virtual public ASTNode {
    public:
        bool _shouldReturn;
        ValueObject _returnValue;
    };

    class BreakPointNode: virtual public ASTNode {
    public:
        bool _shouldBreak;
    };

    class ContinuePointNode: virtual public ASTNode {
    public:
        bool _shouldContinue;
    };

    class ForNode: public ExecutableNode, ContinuePointNode, BreakPointNode, StepOverNode {
    public:
        ExecutableNode* init;
        ExecutableNode* inc;
        EvaluableNode* condition;
        ExecutableNode* body;
        bool _executeOnce = false;
        int _curr_step_pos = 0;

        ForNode(EvaluableNode* condition, ExecutableNode* init, ExecutableNode* inc, ExecutableNode* body);
        ForNode(EvaluableNode* condition, ExecutableNode* init, ExecutableNode* inc, ExecutableNode* body, bool _executeOnce);
        void exec() override;
        ~ForNode() override;

        ASTNode *step() override;
        void prepare() override;
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

    class SwitchNode: public ExecutableNode, BreakPointNode {
    public:
        EvaluableNode* value;
        SwitchBodyNode* body;
        SwitchNode(EvaluableNode* value, SwitchBodyNode* body);
        void exec() override;
        ~SwitchNode() override;
    };

    class SwitchCaseNode;

    class SwitchBodyNode: public ASTNode {
    public:
        std::vector<SwitchCaseNode*> cases;
        SwitchBodyNode(SwitchBodyNode* prev, SwitchCaseNode* next);
        void exec(ValueObject) const;
        ~SwitchBodyNode() override;
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
