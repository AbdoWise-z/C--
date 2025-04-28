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


Cmm::ValueObject m_strlen(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    std::string str = *(static_cast<Cmm::String*>(params[0].value));

    return {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(static_cast<int>(str.length()))
    };
}

Cmm::ValueObject charAt(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::String str = *(static_cast<Cmm::String*>(params[0].value));
    int i  = (int) *(static_cast<Cmm::Integer*>(params[1].value));

    std::string _ch = "";
    _ch += str.at(i);
    return {
        .type = Cmm::V_String,
        .value = new Cmm::String( _ch )
    };
}

Cmm::ValueObject slice(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::String str = *(static_cast<Cmm::String*>(params[0].value));
    int _s  = static_cast<int>(*(static_cast<Cmm::Integer *>(params[1].value)));
    int _e  = static_cast<int>(*(static_cast<Cmm::Integer *>(params[2].value)));

    return {
        .type = Cmm::V_String,
        .value = new Cmm::String( str.substr(_s, _e - _s + 1) )
    };
}

Cmm::ValueObject charAdd(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    Cmm::String str = *(static_cast<Cmm::String*>(params[0].value));
    int _s  = static_cast<int>(*(static_cast<Cmm::Integer *>(params[1].value)));

    for (auto& ch: str) {
      ch += _s;
    }

    return {
        .type = Cmm::V_String,
        .value = new Cmm::String( str )
    };
}


void do_register(Cmm::NativeAddFunction add) {
    add("strlen", {{Cmm::V_String}, {false}}, reinterpret_cast<Cmm::NativeFunction>(m_strlen));
    add("charAt", {{Cmm::V_String, Cmm::V_Integer}, {false, false}}, reinterpret_cast<Cmm::NativeFunction>(charAt));
    add("slice", {{Cmm::V_String, Cmm::V_Integer, Cmm::V_Integer}, {false, false, false}}, reinterpret_cast<Cmm::NativeFunction>(slice));
    add("charAdd", {{Cmm::V_String, Cmm::V_Integer}, {false, false}}, reinterpret_cast<Cmm::NativeFunction>(charAdd));
}
