//
// Created by xabdomo on 4/12/25.
//

#ifndef CMMDEBUGGER_H
#define CMMDEBUGGER_H

#include <string>

#include "../config.h"
#include "../nodes/Program.h"

namespace Namespace::CmmDebugger {
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
}

#endif //CMMDEBUGGER_H
