//
// Created by xabdomo on 4/16/25.
//

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

#include <iostream>
#include <vector>

#include "../../../common.h"
#include "../../../Values.h"
#include "../../../primitives/Integer.h"
#include "../../../primitives/Real.h"
#include "../../../primitives/String.h"

void do_register(Cmm::NativeAddFunction);

extern "C" {
    EXPORT void init(Cmm::NativeAddFunction f) {
        do_register(f);
    }
}


Cmm::ValueObject m_system(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    std::string str = *(static_cast<Cmm::String*>(params[0].value));

    system(str.c_str());
    return {
        .type = Cmm::V_Void,
        .value = nullptr,
    };
}

void do_register(Cmm::NativeAddFunction add) {
    add({"system", {Cmm::V_String}}, reinterpret_cast<Cmm::NativeFunction>(m_system));
}
