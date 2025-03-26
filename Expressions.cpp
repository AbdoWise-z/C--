//
// Created by xabdomo on 3/25/25.
//

#include "Expressions.h"

#include <ranges>

#include "MathHelper.h"
#include "Program.h"

Cmm::Expressions::ExpressionNode::ExpressionNode() = default;

Cmm::ValueObject Cmm::Expressions::ExpressionNode::eval() {
    ValueObject result{};
    result = children[0]->eval();
    for (int i = 1; i < children.size(); i++) {
        auto temp = children[i]->eval();
        auto temp2 = MathHelper::add(result, temp);
        ValuesHelper::Delete(result);
        result = temp2;
    }
    return result;
}

Cmm::Expressions::ExpressionNode::~ExpressionNode() {
    for (const auto & i : children) {
        delete i;
    }
}

Cmm::Expressions::TermNode::TermNode(EvaluableNode *left, EvaluableNode *right, const std::string& op) {
    this->left = left;
    this->right = right;
    this->op = op;
}

Cmm::ValueObject Cmm::Expressions::TermNode::eval() {
    auto left = this->left->eval();
    auto right = this->right->eval();
    ValueObject result{};

    if (op == "+") {
        result = MathHelper::add(left, right);
    } else if (op == "-") {
        result = MathHelper::sub(left, right);
    }
    else if (op == "*") {
        result = MathHelper::mul(left, right);
    }
    else if (op == "/") {
        result = MathHelper::div(left, right);
    }
    else {
        throw std::invalid_argument("Invalid operation");
    }

    ValuesHelper::Delete(left);
    ValuesHelper::Delete(right);

    return result;
}

Cmm::Expressions::TermNode::~TermNode() {
    delete left;
    delete right;
}

Cmm::Expressions::NegatedNode::NegatedNode(EvaluableNode *child) {
    this->child = child;
}

Cmm::ValueObject Cmm::Expressions::NegatedNode::eval() {
    auto val = child->eval();
    auto result = Cmm::ValueObject();
    result.type = val.type;
    switch (val.type) {
        case V_Integer:
            result.value = new Integer(-(*static_cast<Integer*>(val.value)));
            break;
        case V_Real:
            result.value = new Real(-(*static_cast<Real*>(val.value)));
            break;
        case V_Complex:
            result.value = new Complex(-(*static_cast<Complex*>(val.value)));
            break;
        case V_String:
            throw std::invalid_argument("Invalid operation: negation on a string value");
        case V_Bool:
            result.value = reinterpret_cast<void*>(val.value == 0);
            break;
        default:
            throw std::invalid_argument("Invalid operation: negation on a [Error / void] value");
    }

    return result;
}

Cmm::Expressions::NegatedNode::~NegatedNode() {
    delete child;
}


Cmm::Expressions::CastNode::CastNode(EvaluableNode *child, const std::string& type) {
    this->child = child;
    if (type == "int") targetType = V_Integer;
    if (type == "real") targetType = V_Real;
    if (type == "complex") targetType = V_Complex;
    if (type == "str") targetType = V_String;
    if (type == "bool") targetType = V_Bool;
    if (type == "void") targetType = V_Void; // will capture this in runtime instead of compile time since I want types to be runtime bound
}

Cmm::ValueObject Cmm::Expressions::CastNode::eval() {
    auto val = child->eval();
    return ValuesHelper::castTo(val, targetType);
}

Cmm::Expressions::CastNode::~CastNode() {
    delete child;
}

Cmm::Expressions::VariableNode::VariableNode(const std::string &n) {
    this->name = n;
}

Cmm::ValueObject Cmm::Expressions::VariableNode::eval() {
    return ValuesHelper::clone(Program::getVariable(name));
}

// nothing to do here
Cmm::Expressions::VariableNode::~VariableNode() = default;


Cmm::Expressions::ConstantValueNode::ConstantValueNode(const Real& v) {
    value = {
        .type = V_Real,
        .value = new Real(v),
    };
}

Cmm::Expressions::ConstantValueNode::ConstantValueNode(const Integer &v) {
    value = {
        .type = V_Integer,
        .value = new Integer(v),
    };
}

Cmm::Expressions::ConstantValueNode::ConstantValueNode(const Complex &v) {
    value = {
        .type = V_Complex,
        .value = new Complex(v),
    };
}

Cmm::Expressions::ConstantValueNode::ConstantValueNode(const Bool &v) {
    value = {
        .type = V_Bool,
        .value = reinterpret_cast<void*>(v != 0), // a little optimization :)
    };
}

Cmm::Expressions::ConstantValueNode::ConstantValueNode(const String &v) {
    value = {
        .type = V_String,
        .value = new String(v),
    };
}

Cmm::ValueObject Cmm::Expressions::ConstantValueNode::eval() {
    // each node assumes it's the owner of the value returned by eval, so we need to copy it, since it will always be deleted
    auto cpy = ValuesHelper::castTo(value, value.type);
    return cpy;
}

Cmm::Expressions::ConstantValueNode::~ConstantValueNode() {
    ValuesHelper::Delete(value);
}
