
#ifndef CMMDEBUGGER_H
#define CMMDEBUGGER_H

#include <string>

#include "../config.h"
#include "../nodes/Program.h"

namespace Namespace::debugger {
    void enableDebugger();
    void disableDebugger();
    bool isEnabled();

    void beginSession(); // begins a new program
    void endSession();

    void exec(std::string code);
    void step();
    std::string getCode();
    int getCurrentLine();
    bool isDone();
    void reset();

    std::string getError();

    Program::ProgramNode* compileCode(std::string code);
}

#endif //CMMDEBUGGER_H
