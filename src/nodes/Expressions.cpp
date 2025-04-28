
#include "Expressions.h"

#include <ranges>

#include "../MathHelper.h"
#include "Program.h"
#include "utils/string_utils.hpp"

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

Cmm::ValueObject Cmm::Expressions::TermNode::internal_eval(ValueObject left, ValueObject right) {
    ValueObject result{};

    if      (op == "+") {
        result = MathHelper::add(left, right);
    }
    else if (op == "-") {
        result = MathHelper::sub(left, right);
    }
    else if (op == "*") {
        result = MathHelper::mul(left, right);
    }
    else if (op == "/") {
        result = MathHelper::div(left, right);
    }
    else if (op == ">>") {
        result = MathHelper::rshift(left, right);
    }
    else if (op == "<<") {
        result = MathHelper::lshift(left, right);
    }
    else if (op == "|") {
        result = MathHelper::bitwise_or(left, right);
    }
    else if (op == "&") {
        result = MathHelper::bitwise_and(left, right);
    }
    else if (op == "^") {
        result = MathHelper::bitwise_xor(left, right);
    }
    else if (op == "||") {
        result = MathHelper::logical_or(left, right);
    }
    else if (op == "&&") {
        result = MathHelper::logical_and(left, right);
    }
    else if (op == "==") {
        result = MathHelper::equal(left, right);
    }
    else if (op == ">=") {
        result = MathHelper::greater_equal(left, right);
    }
    else if (op == "<=") {
        result = MathHelper::less_equal(left, right);
    }
    else if (op == ">") {
        result = MathHelper::greater(left, right);
    }
    else if (op == "<") {
        result = MathHelper::less(left, right);
    }
    else if (op == "!=") {
        result = MathHelper::not_equal(left, right);
    }
    else if (op == "%") {
        result = MathHelper::mod(left, right);
    }
    else {
        throw std::invalid_argument("Invalid operation");
    }

    return result;
}

Cmm::ValueObject Cmm::Expressions::TermNode::eval() {
    auto left = this->left->eval();
    auto right = this->right->eval();

    auto result = internal_eval(left, right);

    ValuesHelper::Delete(left);
    ValuesHelper::Delete(right);

    return result;
}

Cmm::Expressions::TermNode::~TermNode() {
    delete left;
    delete right;
}

void Cmm::Expressions::TermNode::enterStack() {
    _curr_step_pos.push(0);
}

std::pair<Cmm::ASTNode *, Cmm::ValueObject> Cmm::Expressions::TermNode::step(ValueObject v) {
    int& curr_step = _curr_step_pos.top();
    if (curr_step == 0) {
        curr_step = 1;
        return {left, ValueObject::Void() };
    }

    if (curr_step == 1) {
        curr_step = 2;
        _curr_val.push(v);
        return {right, ValueObject::Void() };;
    }

    auto left = _curr_val.top();
    _curr_val.pop();
    auto right = v;

    auto result = internal_eval(left, right);

    ValuesHelper::Delete(left);
    ValuesHelper::Delete(right);

    return {nullptr, result};
}


void Cmm::Expressions::TermNode::exitStack() {
    _curr_step_pos.pop();
}

Cmm::Expressions::NegatedNode::NegatedNode(EvaluableNode *child) {
    this->child = child;
}

Cmm::ValueObject Cmm::Expressions::NegatedNode::eval() {
    auto val = child->eval();
    return internal_eval(val);
}

Cmm::ValueObject Cmm::Expressions::NegatedNode::internal_eval(ValueObject val) {
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
            throw std::invalid_argument("Invalid operation: negation on a [void] value");
    }

    return result;
}

Cmm::Expressions::NegatedNode::~NegatedNode() {
    delete child;
}

void Cmm::Expressions::NegatedNode::enterStack() {
    _curr_step_pos.push(0);
}

std::pair<Cmm::ASTNode *, Cmm::ValueObject> Cmm::Expressions::NegatedNode::step(ValueObject v) {
    int& curr_step = _curr_step_pos.top();
    if (curr_step == 0) {
        curr_step = 1;
        return {child, ValueObject::Void()};
    }

    return {nullptr, internal_eval(v)};
}

void Cmm::Expressions::NegatedNode::exitStack() {
    _curr_step_pos.pop();
}

Cmm::Expressions::NotNode::NotNode(EvaluableNode *child) {
    this->child = child;
}

Cmm::ValueObject Cmm::Expressions::NotNode::eval() {
    auto val = child->eval();
    auto result = MathHelper::logical_not(val);
    ValuesHelper::Delete(val);
    return result;
}

Cmm::Expressions::NotNode::~NotNode() {
    delete child;
}

void Cmm::Expressions::NotNode::enterStack() {
    _curr_step_pos.push(0);
}

std::pair<Cmm::ASTNode *, Cmm::ValueObject> Cmm::Expressions::NotNode::step(ValueObject val) {
    int& curr_step = _curr_step_pos.top();
    if (curr_step == 0) {
        curr_step = 1;
        return {child, ValueObject::Void()};
    }

    auto result = MathHelper::logical_not(val);
    ValuesHelper::Delete(val);

    return {nullptr, result};
}

void Cmm::Expressions::NotNode::exitStack() {
    _curr_step_pos.pop();
}

Cmm::Expressions::InvertNode::InvertNode(EvaluableNode *child) {
    this->child = child;
}

Cmm::ValueObject Cmm::Expressions::InvertNode::eval() {
    auto val = child->eval();
    auto result = MathHelper::bitwise_not(val);
    ValuesHelper::Delete(val);
    return result;
}

Cmm::Expressions::InvertNode::~InvertNode() {
    delete child;
}

void Cmm::Expressions::InvertNode::enterStack() {
    _curr_step_pos.push(0);
}

std::pair<Cmm::ASTNode *, Cmm::ValueObject> Cmm::Expressions::InvertNode::step(ValueObject val) {
    int& curr_step = _curr_step_pos.top();
    if (curr_step == 0) {
        curr_step = 1;
        return {child, ValueObject::Void()};
    }

    auto result = MathHelper::bitwise_not(val);
    ValuesHelper::Delete(val);

    return {nullptr, result};
}

void Cmm::Expressions::InvertNode::exitStack() {
    _curr_step_pos.pop();
}


Cmm::Expressions::CastNode::CastNode(EvaluableNode *child, const std::string& type) {
    this->child = child;
    this->targetType = ValuesHelper::StringToValueType(type);
    this->_lineNumber = child->_lineNumber;
    this->_virtualLineNumber = child->_virtualLineNumber;
}

Cmm::ValueObject Cmm::Expressions::CastNode::eval() {
    auto val = child->eval();
    return ValuesHelper::castTo(val, targetType);
}

Cmm::Expressions::CastNode::~CastNode() {
    delete child;
}

void Cmm::Expressions::CastNode::enterStack() {
    _curr_step_pos.push(0);
}

std::pair<Cmm::ASTNode *, Cmm::ValueObject> Cmm::Expressions::CastNode::step(ValueObject val) {
    int& curr_step = _curr_step_pos.top();
    if (curr_step == 0) {
        curr_step = 1;
        return {child, ValueObject::Void()};
    }

    auto result = ValuesHelper::castTo(val, targetType);
    ValuesHelper::Delete(val);

    return {nullptr, result};
}

void Cmm::Expressions::CastNode::exitStack() {
    _curr_step_pos.pop();
}

Cmm::Expressions::VariableNode::VariableNode(const std::string &n) {
    this->name = n;
}

Cmm::ValueObject Cmm::Expressions::VariableNode::eval() {
    return ValuesHelper::clone(Program::getVariable(name).Value);
}

// nothing to do here
Cmm::Expressions::VariableNode::~VariableNode() = default;

void Cmm::Expressions::VariableNode::enterStack() {
    _curr_step_pos.push(0);
}

std::pair<Cmm::ASTNode *, Cmm::ValueObject> Cmm::Expressions::VariableNode::step(ValueObject) {
    return {nullptr, ValuesHelper::clone(Program::getVariable(name).Value)};
}

void Cmm::Expressions::VariableNode::exitStack() {
    _curr_step_pos.pop();
}


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
        .value = new String(StringUtils::unescapeString(v)),
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

void Cmm::Expressions::ConstantValueNode::enterStack() {
    _curr_step_pos.push(0);
}

std::pair<Cmm::ASTNode *, Cmm::ValueObject> Cmm::Expressions::ConstantValueNode::step(ValueObject) {
    return {nullptr, ValuesHelper::castTo(value, value.type)};
}

void Cmm::Expressions::ConstantValueNode::exitStack() {
    _curr_step_pos.pop();
}
