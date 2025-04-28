//
// Created by xabdomo on 3/28/25.
//

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <iostream>
#include <vector>

#include "common.h"
#include "Values.h"
#include "primitives/Complex.h"
#include "primitives/Integer.h"
#include "primitives/Real.h"
#include "primitives/String.h"

void do_register(Cmm::NativeAddFunction);

extern "C" {
    EXPORT void init(Cmm::NativeAddFunction f) {
        do_register(f);
    }
}


Cmm::ValueObject getLine(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::ValueObject result = {
        .type = Cmm::V_Void,
        .value = nullptr,
    };

    std::string value;
    std::getline(std::cin, value);

    result.type = Cmm::V_String;
    result.value = new Cmm::String(value);

    return result;
}

Cmm::ValueObject sqrt_i(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Integer i = *static_cast<Cmm::Integer*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(i.sqrt()),
    };

    return result;
}

Cmm::ValueObject sqrt_r(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Real i = *static_cast<Cmm::Real*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Real,
        .value = new Cmm::Real(i.sqrt()),
    };

    return result;
}

Cmm::ValueObject abs_r(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Real i = *static_cast<Cmm::Real*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Real,
        .value = new Cmm::Real(i < 0.0 ? -i : i),
    };

    return result;
}

Cmm::ValueObject abs_i(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Integer i = *static_cast<Cmm::Integer*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(i < 0 ? -i : i),
    };

    return result;
}

Cmm::ValueObject abs_c(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Complex i = *static_cast<Cmm::Complex*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Complex,
        .value = new Cmm::Complex(i.getRealPart().abs(), i.getImagPart().abs()),
    };

    return result;
}


Cmm::ValueObject mag_r(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Real i = *static_cast<Cmm::Real*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Real,
        .value = new Cmm::Real(i < 0.0 ? -i : i),
    };

    return result;
}

Cmm::ValueObject mag_i(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Integer i = *static_cast<Cmm::Integer*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(i < 0 ? -i : i),
    };

    return result;
}


Cmm::ValueObject mag_c(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Complex i = *static_cast<Cmm::Complex*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Complex,
        .value = new Cmm::Complex(i.mag2(), Cmm::Real(0.0)),
    };

    return result;
}

Cmm::ValueObject rel(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Complex i = *static_cast<Cmm::Complex*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Real,
        .value = new Cmm::Real(i.getRealPart()),
    };

    return result;
}

Cmm::ValueObject img(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Complex i = *static_cast<Cmm::Complex*>(params[0].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Real,
        .value = new Cmm::Real(i.getImagPart()),
    };

    return result;
}

Cmm::ValueObject pow_r(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Real a = *static_cast<Cmm::Real*>(params[0].value);
    Cmm::Real b = *static_cast<Cmm::Real*>(params[1].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Real,
        .value = new Cmm::Real(a ^ b),
    };

    return result;
}

Cmm::ValueObject pow_i(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::Integer a = *static_cast<Cmm::Integer*>(params[0].value);
    Cmm::Integer b = *static_cast<Cmm::Integer*>(params[1].value);

    Cmm::ValueObject result = {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(a.pow(b)),
    };

    return result;
}

Cmm::ValueObject m_rand_r(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {

    Cmm::ValueObject result = {
        .type = Cmm::V_Real,
        .value = new Cmm::Real(Cmm::Real::rand())
    };

    return result;
}


void do_register(Cmm::NativeAddFunction add) {
    add("sqrt", {{Cmm::V_Real}, {false}}, reinterpret_cast<Cmm::NativeFunction>(sqrt_r));
    add("sqrt", {{Cmm::V_Integer}, {false}}, reinterpret_cast<Cmm::NativeFunction>(sqrt_i));

    add("abs", {{Cmm::V_Real}, {false}}, reinterpret_cast<Cmm::NativeFunction>(abs_r));
    add("abs", {{Cmm::V_Integer}, {false}}, reinterpret_cast<Cmm::NativeFunction>(abs_i));
    add("abs", {{Cmm::V_Complex}, {false}}, reinterpret_cast<Cmm::NativeFunction>(abs_c));

    add("mag", {{Cmm::V_Real}, {false}}, reinterpret_cast<Cmm::NativeFunction>(mag_r));
    add("mag", {{Cmm::V_Integer}, {false}}, reinterpret_cast<Cmm::NativeFunction>(mag_i));
    add("mag", {{Cmm::V_Complex}, {false}}, reinterpret_cast<Cmm::NativeFunction>(mag_c));

    add("rel", {{Cmm::V_Complex}, {false}}, reinterpret_cast<Cmm::NativeFunction>(rel));
    add("img", {{Cmm::V_Complex}, {false}}, reinterpret_cast<Cmm::NativeFunction>(img));

    add("pow", {{Cmm::V_Real, Cmm::V_Real}, {false}}, reinterpret_cast<Cmm::NativeFunction>(pow_r));
    add("pow", {{Cmm::V_Integer, Cmm::V_Integer}, {false}}, reinterpret_cast<Cmm::NativeFunction>(pow_i));

    add("rand", {{}, {}}, reinterpret_cast<Cmm::NativeFunction>(m_rand_r));
}
