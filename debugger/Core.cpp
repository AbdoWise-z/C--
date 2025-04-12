//
// Created by xabdomo on 4/12/25.
//

#include "Core.h"

#include <stack>
#include <stdexcept>

#include "Renderer.h"


static bool debuggerEnabled = false;
static std::vector<Cmm::ExecutableNode*> code;
static bool started = false;
static std::string codeString;

extern int yyparse();
extern void yy_scan_string(const char* str);
extern Cmm::Program::ProgramNode* root;

void Cmm::CmmDebugger::enableDebugger() {
    debuggerEnabled = true;
}

void Cmm::CmmDebugger::disableDebugger() {
    debuggerEnabled = false;
}

bool Cmm::CmmDebugger::isEnabled() {
    return debuggerEnabled;
}

void Cmm::CmmDebugger::beginSession() {
    if (started) {
        throw std::runtime_error("CmmDebugger::beginSession() called while in active session");
    }

    started = true;
    Program::beginScope();
}

void Cmm::CmmDebugger::endSession() {
    if (!started) {
        throw std::runtime_error("CmmDebugger::endSession() called while not in active session");
    }

    started = false;
    for (auto i: code) {
        delete i;
    }

    code.clear();
    codeString = "";

    Program::endScope();
}

std::stack<Cmm::ASTNode*> executionStack;


static void do_step_once(Cmm::ASTNode* node) {
    auto step = dynamic_cast<Cmm::StepOverNode*>(node);

    if (step) {
        auto exec = step->step();
        if (exec)
            executionStack.emplace(exec);
        else
            executionStack.pop(); // done with this step over node
    } else {
        if (dynamic_cast<Cmm::ExecutableNode*>(node)) {
            dynamic_cast<Cmm::ExecutableNode*>(node)->exec();
        }

        executionStack.pop();

        if (!executionStack.empty()) {
            do_step_once(executionStack.top());
        }
    }
}

static void start_debugged(Cmm::ExecutableNode* exec) {
    executionStack.push(exec);
    while (dynamic_cast<Cmm::StepOverNode*>(executionStack.top())) {
        executionStack.push(dynamic_cast<Cmm::StepOverNode*>(executionStack.top())->step());
    }
    Cmm::CmmDebugger::launch();
}

void Cmm::CmmDebugger::exec(std::string code) {
    codeString += code;

    yy_scan_string(code.c_str());

    int parse_result = yyparse();

    if (parse_result == 0) {
        auto program = root;
        ::code.push_back(root->source[0]);

        if (debuggerEnabled) {
            start_debugged(program->source[0]);
            program->source.clear();
            delete program;
        } else {
            // Program::beginScope();
            program->source[0]->exec();
            delete program;
            // Program::endScope();
        }
    }
}

void Cmm::CmmDebugger::step() {
    if (executionStack.empty()) return;

    do_step_once(executionStack.top());
}

std::string Cmm::CmmDebugger::getCode() {
    return codeString;
}

int Cmm::CmmDebugger::getCurrentLine() {
    if (executionStack.empty()) return -1;

    Cmm::ASTNode* curr = executionStack.top();
    return curr->_lineNumber - 1; // fixme: maybe start lines from zero like a sane person ? :)
}

bool Cmm::CmmDebugger::isDone() {
    return executionStack.empty();
}


