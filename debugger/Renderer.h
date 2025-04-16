//
// Created by xabdomo on 4/12/25.
//

#ifndef DEBUGGERRENDER_H
#define DEBUGGERRENDER_H

#include <string>

#include "../config.h"
#include "../nodes/AST.h"

#define DEBUGGER_STEP     0
#define DEBUGGER_STEP_IN  1
#define DEBUGGER_CONTINUE

namespace Namespace::debugger {
    void launch();
}

#endif //DEBUGGERRENDER_H
