//
// Created by xabdomo on 4/12/25.
//

#include "Core.h"

#include <stack>
#include <stdexcept>

#include "Renderer.h"
#include "grammar/Store.h"


static bool debuggerEnabled = false;
static std::vector<Cmm::ExecutableNode*> code;
static bool started = false;
static std::string codeString;

extern int yyparse();
extern void yy_scan_string(const char* str);
extern Cmm::Program::ProgramNode* root;

void Cmm::debugger::enableDebugger() {
    debuggerEnabled = true;
}

void Cmm::debugger::disableDebugger() {
    debuggerEnabled = false;
}

bool Cmm::debugger::isEnabled() {
    return debuggerEnabled;
}

void Cmm::debugger::beginSession() {
    if (started) {
        throw std::runtime_error("CmmDebugger::beginSession() called while in active session");
    }

    started = true;
    Program::beginScope(nullptr, "Global");
}

void Cmm::debugger::endSession() {
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
        if (exec) {

            executionStack.push(exec);
            while (dynamic_cast<Cmm::StepOverNode*>(executionStack.top())) {
                auto n = dynamic_cast<Cmm::StepOverNode*>(executionStack.top());
                n->prepare();
                executionStack.push(n->step());
            }

        } else {
            executionStack.pop(); // done with this step over node
            if (!executionStack.empty()) {
                do_step_once(executionStack.top());
            }
        }
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
        auto n = dynamic_cast<Cmm::StepOverNode*>(executionStack.top());
        n->prepare();
        executionStack.push(n->step());
    }
    Cmm::debugger::launch();
}

void Cmm::debugger::exec(std::string code) {

    yy_scan_string(code.c_str());

    int parse_result = yyparse();

    if (parse_result == 0) {
        codeString += code;
        auto program = Cmm::Store::root;

        ::code.push_back(program->source[0]);

        if (debuggerEnabled) {
            start_debugged(program->source[0]);
            program->source.clear();
            delete program;
        } else {
            program->source[0]->exec();
            program->source.clear();
            delete program;
        }
    }
}

void Cmm::debugger::step() {
    if (executionStack.empty()) return;

    do_step_once(executionStack.top());
}

std::string Cmm::debugger::getCode() {
    return codeString;
}

int Cmm::debugger::getCurrentLine() {
    if (executionStack.empty()) return -1;

    Cmm::ASTNode* curr = executionStack.top();
    return curr->_lineNumber - 1; // fixme: maybe start lines from zero like a sane person ? :)
}

bool Cmm::debugger::isDone() {
    return executionStack.empty();
}


