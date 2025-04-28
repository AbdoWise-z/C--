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

#include <chrono>
#include <thread>

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

Cmm::ValueObject m_sleep(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    long seconds = (long) *(static_cast<Cmm::Integer*>(params[0].value));
    long ms      = (long) *(static_cast<Cmm::Integer*>(params[1].value));
    long ns      = (long) *(static_cast<Cmm::Integer*>(params[2].value));

    std::this_thread::sleep_for(
        std::chrono::seconds(seconds) +
             std::chrono::milliseconds(ms) +
             std::chrono::nanoseconds(ns)
             );

    return {
        .type = Cmm::V_Void,
        .value = nullptr
    };
}

Cmm::ValueObject m_nano(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    auto now = std::chrono::system_clock::now();
    auto now_v = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()) % std::chrono::milliseconds(1);

    return {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(now_v.count())
    };
}

Cmm::ValueObject m_millis(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    auto now = std::chrono::system_clock::now();
    auto now_v = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % std::chrono::seconds(1);

    return {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(now_v.count())
    };
}

Cmm::ValueObject m_seconds(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&now_c);

    return {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(local_time.tm_sec)
    };
}

Cmm::ValueObject m_minute(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&now_c);

    return {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(local_time.tm_min)
    };
}

Cmm::ValueObject m_hour(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&now_c);

    return {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(local_time.tm_hour)
    };
}

Cmm::ValueObject m_day(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&now_c);

    return {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(local_time.tm_mday)
    };
}

Cmm::ValueObject m_month(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&now_c);

    return {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(local_time.tm_mon + 1)
    };
}

Cmm::ValueObject m_year(const Cmm::FunctionSignature& sig, std::vector<Cmm::ValueObject>& params) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_time = *std::localtime(&now_c);

    return {
        .type = Cmm::V_Integer,
        .value = new Cmm::Integer(local_time.tm_year + 1900)
    };
}

#define reg(name, f_name) add( name , { {}, {} }, reinterpret_cast<Cmm::NativeFunction>(f_name));

void do_register(Cmm::NativeAddFunction add) {
    add("sleep", {{Cmm::V_Integer, Cmm::V_Integer, Cmm::V_Integer},  {false, false, false}}, reinterpret_cast<Cmm::NativeFunction>(m_sleep));
    reg("nano", m_nano);
    reg("millis", m_millis);
    reg("second", m_seconds);
    reg("minute", m_minute);
    reg("hour", m_hour);
    reg("day", m_day);
    reg("month", m_month);
    reg("year", m_year);
}
