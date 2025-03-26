//
// Created by xabdomo on 3/25/25.
//

#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <vector>

#include "primitives.h"
#include "config.h"
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

        class TermNode final : public EvaluableNode {
        public:
            EvaluableNode* left;
            EvaluableNode* right;
            std::string op;
            TermNode(EvaluableNode* left, EvaluableNode* right, const std::string& op);
            ValueObject eval() override;
            ~TermNode() override;
        };

        class NegatedNode final : public EvaluableNode {
        public:
            EvaluableNode* child;
            explicit NegatedNode(EvaluableNode* child);
            ValueObject eval() override;
            ~NegatedNode() override;
        };


        class ConstantValueNode final : public EvaluableNode {
        public:
            ValueObject value{};
            explicit ConstantValueNode(const Real& value);
            explicit ConstantValueNode(const Integer& value);
            explicit ConstantValueNode(const Complex& value);
            explicit ConstantValueNode(const Bool& value);
            explicit ConstantValueNode(const String& value);

            ValueObject eval() override;
            ~ConstantValueNode() override;
        };
    }
}


#endif //EXPRESSIONS_H
