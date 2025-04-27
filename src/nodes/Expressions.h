
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <stack>
#include <vector>

#include "../primitives.h"
#include "../config.h"
#include "AST.h"


namespace Namespace {
    namespace Expressions {
        class TermNode;
        class ExpressionNode;
        class NegatedNode;
        class ConstantValueNode;

        class ExpressionNode final : public EvaluableNode {
            // the only difference between a term and an expression is the operator
            // term is created to capture operations such as multiplication / division etc ..
            // but ExpressionNode is for addition (and it may one have one child)
        public:
            std::vector<EvaluableNode*> children;
            ExpressionNode();
            ValueObject eval() override;
            ~ExpressionNode() override;
        };

        class TermNode final : public EvaluableNode, public StepOverNodeWithResult {
        public:
            EvaluableNode* left;
            EvaluableNode* right;
            std::string op;


            TermNode(EvaluableNode* left, EvaluableNode* right, const std::string& op);
            ValueObject internal_eval(ValueObject, ValueObject);
            ValueObject eval() override;
            ~TermNode() override;

            // debugging
            std::stack<int> _curr_step_pos;
            std::stack<ValueObject> _curr_val;

            void enterStack() override;
            std::pair<ASTNode*, ValueObject> step(ValueObject) override;
            void exitStack() override;
        };

        class NegatedNode final : public EvaluableNode, public StepOverNodeWithResult {
        public:
            EvaluableNode* child;
            explicit NegatedNode(EvaluableNode* child);
            ValueObject eval() override;
            static ValueObject internal_eval(ValueObject);
            ~NegatedNode() override;

            // debugging
            std::stack<int> _curr_step_pos;

            void enterStack() override;
            std::pair<ASTNode*, ValueObject> step(ValueObject) override;
            void exitStack() override;
        };

        class NotNode final : public EvaluableNode, public StepOverNodeWithResult {
        public:
            EvaluableNode* child;
            explicit NotNode(EvaluableNode* child);
            ValueObject eval() override;
            ~NotNode() override;

            // debugging
            std::stack<int> _curr_step_pos;

            void enterStack() override;
            std::pair<ASTNode*, ValueObject> step(ValueObject) override;
            void exitStack() override;
        };

        class InvertNode final : public EvaluableNode, public StepOverNodeWithResult {
        public:
            EvaluableNode* child;
            explicit InvertNode(EvaluableNode* child);
            ValueObject eval() override;
            ~InvertNode() override;

            // debugging
            std::stack<int> _curr_step_pos;

            void enterStack() override;
            std::pair<ASTNode*, ValueObject> step(ValueObject) override;
            void exitStack() override;
        };

        class CastNode final : public EvaluableNode, public StepOverNodeWithResult {
        public:
            EvaluableNode* child;
            ValueType targetType;
            explicit CastNode(EvaluableNode* child, const std::string& type);
            ValueObject eval() override;
            ~CastNode() override;

            // debugging
            std::stack<int> _curr_step_pos;

            void enterStack() override;
            std::pair<ASTNode*, ValueObject> step(ValueObject) override;
            void exitStack() override;
        };

        class VariableNode final : public EvaluableNode, public StepOverNodeWithResult {
        public:
            std::string name;
            explicit VariableNode(const std::string& n);
            ValueObject eval() override;
            ~VariableNode() override;

            // debugging
            std::stack<int> _curr_step_pos;

            void enterStack() override;
            std::pair<ASTNode*, ValueObject> step(ValueObject) override;
            void exitStack() override;
        };


        class ConstantValueNode final : public EvaluableNode, public StepOverNodeWithResult {
        public:
            ValueObject value{};
            explicit ConstantValueNode(const Real& value);
            explicit ConstantValueNode(const Integer& value);
            explicit ConstantValueNode(const Complex& value);
            explicit ConstantValueNode(const Bool& value);
            explicit ConstantValueNode(const String& value);

            ValueObject eval() override;
            ~ConstantValueNode() override;

            // debugging
            std::stack<int> _curr_step_pos;

            void enterStack() override;
            std::pair<ASTNode*, ValueObject> step(ValueObject) override;
            void exitStack() override;
        };
    }
}


#endif //EXPRESSIONS_H
