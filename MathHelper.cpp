//
// Created by xabdomo on 3/25/25.
//

#include "MathHelper.h"

#include <map>

#include "primitives.h"

const static std::pmr::map<std::pair<Cmm::ValueType, Cmm::ValueType>, Cmm::ValueType> _cMap = {
    {{Cmm::V_Bool, Cmm::V_Bool}, Cmm::V_Bool},
    {{Cmm::V_Bool, Cmm::V_Integer}, Cmm::V_Integer},
    {{Cmm::V_Bool, Cmm::V_Real}, Cmm::V_Real},
    {{Cmm::V_Bool, Cmm::V_Complex}, Cmm::V_Complex},
    {{Cmm::V_Bool, Cmm::V_String}, Cmm::V_String},

    {{Cmm::V_Integer, Cmm::V_Bool}, Cmm::V_Integer},
    {{Cmm::V_Integer, Cmm::V_Integer}, Cmm::V_Integer},
    {{Cmm::V_Integer, Cmm::V_Real}, Cmm::V_Real},
    {{Cmm::V_Integer, Cmm::V_Complex}, Cmm::V_Complex},
    {{Cmm::V_Integer, Cmm::V_String}, Cmm::V_String},

    {{Cmm::V_Real, Cmm::V_Bool}, Cmm::V_Real},
    {{Cmm::V_Real, Cmm::V_Integer}, Cmm::V_Real},
    {{Cmm::V_Real, Cmm::V_Real}, Cmm::V_Real},
    {{Cmm::V_Real, Cmm::V_Complex}, Cmm::V_Complex},
    {{Cmm::V_Real, Cmm::V_String}, Cmm::V_String},

    {{Cmm::V_Complex, Cmm::V_Bool}, Cmm::V_Complex},
    {{Cmm::V_Complex, Cmm::V_Integer}, Cmm::V_Complex},
    {{Cmm::V_Complex, Cmm::V_Real}, Cmm::V_Complex},
    {{Cmm::V_Complex, Cmm::V_Complex}, Cmm::V_Complex},
    {{Cmm::V_Complex, Cmm::V_String}, Cmm::V_String},

    {{Cmm::V_String, Cmm::V_Bool}, Cmm::V_String},
    {{Cmm::V_String, Cmm::V_Integer}, Cmm::V_String},
    {{Cmm::V_String, Cmm::V_Real}, Cmm::V_String},
    {{Cmm::V_String, Cmm::V_Complex}, Cmm::V_String},
    {{Cmm::V_String, Cmm::V_String}, Cmm::V_String},

};


Cmm::MathHelper::OperationError::OperationError(ValueType a, ValueType b, const std::string& op) {
    this->from = a;
    this->to = b;
    this->op = op;
}

const char * Cmm::MathHelper::OperationError::what() const noexcept {
    static std::string str;
    str =  "Cannot perform operation ";
    str += op;
    str += " on type ";
    str += ValuesHelper::ValueTypeAsString(from);
    str += " and ";
    str += ValuesHelper::ValueTypeAsString(to);
    str += " : Types missmatch";

    return str.c_str();
}

Cmm::ValueObject Cmm::MathHelper::add(ValueObject &left, ValueObject &right) {
    auto cIt = _cMap.find({left.type, right.type});

    if (cIt == _cMap.end()) {
        throw MathHelper::OperationError(left.type, right.type, "\"+\"");
    }

    auto common = cIt->second;
    ValueObject* l_ptr;
    ValueObject* r_ptr;

    if (left.type != common) {
        l_ptr = new ValueObject{ ValuesHelper::castTo(left, common) };
    } else {
        l_ptr = &left;
    }

    if (right.type != common) {
        r_ptr = new ValueObject{ ValuesHelper::castTo(right, common) };
    } else {
        r_ptr = &right;
    }

    ValueObject result {
        .type = common,
        .value = nullptr,
    };

    switch (common) {
        case Cmm::V_Integer:
            result.value = new Integer(
                *static_cast<Integer*>(l_ptr->value) + *static_cast<Integer*>(r_ptr->value)
                );
            break;
        case Cmm::V_Real:
            result.value = new Real(
                *static_cast<Real*>(l_ptr->value) + *static_cast<Real*>(r_ptr->value)
                );
            break;
        case Cmm::V_Complex:
            result.value = new Complex(
                *static_cast<Complex*>(l_ptr->value) + *static_cast<Complex*>(r_ptr->value)
                );
        break;
        case Cmm::V_String:
            result.value = new String(
                *static_cast<String*>(l_ptr->value) + *static_cast<String*>(r_ptr->value)
                );
        break;
        case Cmm::V_Bool:
            result.value = new Bool(
                *static_cast<Bool*>(l_ptr->value) || *static_cast<Bool*>(r_ptr->value)
                );
        break;
        default: result.value = nullptr;
    }

    if (l_ptr != &left) {
        ValuesHelper::Delete(*l_ptr);
        delete l_ptr;
    }

    if (r_ptr != &right) {
        ValuesHelper::Delete(*r_ptr);
        delete r_ptr;
    }

    return result;
}


Cmm::ValueObject Cmm::MathHelper::sub(ValueObject &left, ValueObject &right) {
    auto cIt = _cMap.find({left.type, right.type});

    if (cIt == _cMap.end()) {
        throw MathHelper::OperationError(left.type, right.type, "\"-\"");
    }

    auto common = cIt->second;
    ValueObject* l_ptr;
    ValueObject* r_ptr;

    if (common == V_String) {
        throw MathHelper::OperationError(left.type, right.type, "\"-\"");
    }

    if (left.type != common) {
        l_ptr = new ValueObject{ ValuesHelper::castTo(left, common) };
    } else {
        l_ptr = &left;
    }

    if (right.type != common) {
        r_ptr = new ValueObject{ ValuesHelper::castTo(right, common) };
    } else {
        r_ptr = &right;
    }

    ValueObject result {
        .type = common,
        .value = nullptr,
    };

    switch (common) {
        case Cmm::V_Integer:
            result.value = new Integer(
                *static_cast<Integer*>(l_ptr->value) + *static_cast<Integer*>(r_ptr->value)
                );
        break;
        case Cmm::V_Real:
            result.value = new Real(
                *static_cast<Real*>(l_ptr->value) + *static_cast<Real*>(r_ptr->value)
                );
        break;
        case Cmm::V_Complex:
            result.value = new Complex(
                *static_cast<Complex*>(l_ptr->value) + *static_cast<Complex*>(r_ptr->value)
                );
        break;
        case Cmm::V_String:
            result.value = new String(
                *static_cast<String*>(l_ptr->value) + *static_cast<String*>(r_ptr->value)
                );
        break;
        case Cmm::V_Bool:
            result.value = new Bool(
                *static_cast<Bool*>(l_ptr->value) || *static_cast<Bool*>(r_ptr->value)
                );
        break;
        default: result.value = nullptr;
    }

    if (l_ptr != &left) {
        ValuesHelper::Delete(*l_ptr);
        delete l_ptr;
    }

    if (r_ptr != &right) {
        ValuesHelper::Delete(*r_ptr);
        delete r_ptr;
    }

    return result;
}


Cmm::ValueObject Cmm::MathHelper::mul(ValueObject &left, ValueObject &right) {
    auto cIt = _cMap.find({left.type, right.type});

    if (cIt == _cMap.end()) {
        throw MathHelper::OperationError(left.type, right.type, "\"*\"");
    }

    auto common = cIt->second;
    ValueObject* l_ptr;
    ValueObject* r_ptr;

    if (common == V_String) {
        throw MathHelper::OperationError(left.type, right.type, "\"*\"");
    }

    if (left.type != common) {
        l_ptr = new ValueObject{ ValuesHelper::castTo(left, common) };
    } else {
        l_ptr = &left;
    }

    if (right.type != common) {
        r_ptr = new ValueObject{ ValuesHelper::castTo(right, common) };
    } else {
        r_ptr = &right;
    }

    ValueObject result {
        .type = common,
        .value = nullptr,
    };

    switch (common) {
        case Cmm::V_Integer:
            result.value = new Integer(
                *static_cast<Integer*>(l_ptr->value) + *static_cast<Integer*>(r_ptr->value)
                );
        break;
        case Cmm::V_Real:
            result.value = new Real(
                *static_cast<Real*>(l_ptr->value) + *static_cast<Real*>(r_ptr->value)
                );
        break;
        case Cmm::V_Complex:
            result.value = new Complex(
                *static_cast<Complex*>(l_ptr->value) + *static_cast<Complex*>(r_ptr->value)
                );
        break;
        case Cmm::V_String:
            result.value = new String(
                *static_cast<String*>(l_ptr->value) + *static_cast<String*>(r_ptr->value)
                );
        break;
        case Cmm::V_Bool:
            result.value = new Bool(
                *static_cast<Bool*>(l_ptr->value) || *static_cast<Bool*>(r_ptr->value)
                );
        break;
        default: result.value = nullptr;
    }

    if (l_ptr != &left) {
        ValuesHelper::Delete(*l_ptr);
        delete l_ptr;
    }

    if (r_ptr != &right) {
        ValuesHelper::Delete(*r_ptr);
        delete r_ptr;
    }

    return result;
}


Cmm::ValueObject Cmm::MathHelper::div(ValueObject &left, ValueObject &right) {
    auto cIt = _cMap.find({left.type, right.type});

    if (cIt == _cMap.end()) {
        throw MathHelper::OperationError(left.type, right.type, "\"/\"");
    }

    auto common = cIt->second;
    ValueObject* l_ptr;
    ValueObject* r_ptr;

    if (common == V_String) {
        throw MathHelper::OperationError(left.type, right.type, "\"/\"");
    }

    if (left.type != common) {
        l_ptr = new ValueObject{ ValuesHelper::castTo(left, common) };
    } else {
        l_ptr = &left;
    }

    if (right.type != common) {
        r_ptr = new ValueObject{ ValuesHelper::castTo(right, common) };
    } else {
        r_ptr = &right;
    }

    ValueObject result {
        .type = common,
        .value = nullptr,
    };

    switch (common) {
        case Cmm::V_Integer:
            result.value = new Integer(
                *static_cast<Integer*>(l_ptr->value) + *static_cast<Integer*>(r_ptr->value)
                );
        break;
        case Cmm::V_Real:
            result.value = new Real(
                *static_cast<Real*>(l_ptr->value) + *static_cast<Real*>(r_ptr->value)
                );
        break;
        case Cmm::V_Complex:
            result.value = new Complex(
                *static_cast<Complex*>(l_ptr->value) + *static_cast<Complex*>(r_ptr->value)
                );
        break;
        case Cmm::V_String:
            result.value = new String(
                *static_cast<String*>(l_ptr->value) + *static_cast<String*>(r_ptr->value)
                );
        break;
        case Cmm::V_Bool:
            result.value = new Bool(
                *static_cast<Bool*>(l_ptr->value) || *static_cast<Bool*>(r_ptr->value)
                );
        break;
        default: result.value = nullptr;
    }

    if (l_ptr != &left) {
        ValuesHelper::Delete(*l_ptr);
        delete l_ptr;
    }

    if (r_ptr != &right) {
        ValuesHelper::Delete(*r_ptr);
        delete r_ptr;
    }

    return result;
}