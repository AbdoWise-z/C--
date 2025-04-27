
#ifndef VARIABLES_H
#define VARIABLES_H

#include "../config.h"
#include "Expressions.h"
#include "Program.h"

namespace Namespace::Variables {
    class VariableDeclarationNode: public ExecutableNode, public StepOverNode, public DebuggerWaitToStepNode  {
    public:
        bool isConst;
        std::string name;
        std::string type;
        EvaluableNode* value;
        VariableDeclarationNode(bool isConst, std::string name, std::string type, EvaluableNode* value);
        void exec() override;
        ~VariableDeclarationNode() override;

        // debugging
        std::stack<int> _curr_step_pos;

        void enterStack() override;
        ASTNode* step(ValueObject) override;
        void exitStack() override;
    };

    class InferredVariableDeclarationNode: public ExecutableNode, public StepOverNode, public DebuggerWaitToStepNode  {
    public:
        bool isConst;
        std::string name;
        EvaluableNode* value;
        InferredVariableDeclarationNode(bool isConst, std::string name, EvaluableNode* value);
        void exec() override;
        ~InferredVariableDeclarationNode() override;

        // debugging
        std::stack<int> _curr_step_pos;

        void enterStack() override;
        ASTNode* step(ValueObject) override;
        void exitStack() override;
    };

    class VariableAssignmentNode: public ExecutableNode, public StepOverNode, public DebuggerWaitToStepNode  {
    public:
        std::string name;
        EvaluableNode* expr;
        VariableAssignmentNode(std::string name, EvaluableNode* value);
        void exec() override;
        ~VariableAssignmentNode() override;

        // debugging
        std::stack<int> _curr_step_pos;

        void enterStack() override;
        ASTNode* step(ValueObject) override;
        void exitStack() override;
    };

    class CompoundAssignmentNode: public ExecutableNode, public StepOverNode, public DebuggerWaitToStepNode {
    public:
        VariableAssignmentNode* _internal;
        CompoundAssignmentNode(const std::string& name, const std::string &op, EvaluableNode* value);
        void exec() override;
        ~CompoundAssignmentNode() override;

        // debugging
        std::stack<int> _curr_step_pos;

        void enterStack() override;
        ASTNode* step(ValueObject) override;
        void exitStack() override;
    };

    class PreIncNode: public EvaluableNode, public StepOverNodeWithResult {
    public:
        Expressions::TermNode* _internal;
        std::string name;
        std::string op;
        PreIncNode(const std::string& name, const std::string &op);
        ValueObject eval() override;
        ~PreIncNode() override;

        // debugging
        std::stack<int> _curr_step_pos;

        void enterStack() override;
        std::pair<ASTNode*, ValueObject> step(ValueObject) override;
        void exitStack() override;
    };

    class PostIncNode: public EvaluableNode, public StepOverNodeWithResult {
    public:
        Expressions::TermNode* _internal;
        std::string name;
        std::string op;
        PostIncNode(const std::string& name, const std::string &op);
        ValueObject eval() override;
        ~PostIncNode() override;

        // debugging
        std::stack<int> _curr_step_pos;

        void enterStack() override;
        std::pair<ASTNode*, ValueObject> step(ValueObject) override;
        void exitStack() override;
    };

    class DebuggerWaitEvalNode: public EvaluableNode, public StepOverNodeWithResult, public DebuggerWaitToStepNode {
    public:
        EvaluableNode* _internal;
        explicit DebuggerWaitEvalNode(EvaluableNode* internal);
        ValueObject eval() override;
        ~DebuggerWaitEvalNode() override;

        std::stack<int> _curr_step_pos;

        void enterStack() override;
        std::pair<ASTNode*, ValueObject> step(ValueObject) override;
        void exitStack() override;
    };

};



#endif //VARIABLES_H
