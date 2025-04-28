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

Cmm::ValueObject input(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    std::string type = *(static_cast<Cmm::String*>(params[0].value));
    Cmm::ValueObject result = {
        .type = Cmm::V_Void,
        .value = nullptr,
    };

    std::string value;
    std::cin >> value;

    if (type == "str") {
        result.type = Cmm::V_String;
        result.value = new Cmm::String(value);
    }

    if (type == "int") {
        result.type = Cmm::V_Integer;
        result.value = new Cmm::Integer(value.c_str());
    }

    if (type == "real") {
        result.type = Cmm::V_Real;
        result.value = new Cmm::Real(value.c_str());
    }

    if (type == "complex") {
        // fixme: need a str to complex number parser (which I'm too damn lazy to implement)
        result.type = Cmm::V_Void;
        result.value = nullptr;
    }

    if (type == "bool") {
        result.type = Cmm::V_Bool;
        result.value = reinterpret_cast<void*>(value == "true");
    }

    return result;
}

Cmm::ValueObject print(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    std::cout << Cmm::ValuesHelper::toString(params[0]);
    std::cout.flush();

    Cmm::ValueObject result = {
        .type = Cmm::V_Void,
        .value = nullptr,
    };

    return result;
}

Cmm::ValueObject _endl(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {

    Cmm::ValueObject result = {
        .type = Cmm::V_String,
        .value = new Cmm::String("\n"),
    };

    return result;
}


void do_register(Cmm::NativeAddFunction add) {
    add("input", {{Cmm::V_String}, {true}}, reinterpret_cast<Cmm::NativeFunction>(input));

    add("getLine", {{}, {}}, reinterpret_cast<Cmm::NativeFunction>(getLine));

    add("print", {{Cmm::V_String}, {false}}, reinterpret_cast<Cmm::NativeFunction>(print));
    add("print", {{Cmm::V_Integer}, {false}}, reinterpret_cast<Cmm::NativeFunction>(print));
    add("print", {{Cmm::V_Bool}, {false}}, reinterpret_cast<Cmm::NativeFunction>(print));
    add("print", {{Cmm::V_Complex}, {false}}, reinterpret_cast<Cmm::NativeFunction>(print));
    add("print", {{Cmm::V_Real}, {false}}, reinterpret_cast<Cmm::NativeFunction>(print));

    add("endl", {{},{}}, reinterpret_cast<Cmm::NativeFunction>(_endl));
}
