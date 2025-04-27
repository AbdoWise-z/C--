
#include "Core.h"

#include <stack>
#include <stdexcept>

#include "Renderer.h"
#include "grammar/Store.h"


static bool debuggerEnabled = false;
static std::vector<Cmm::ExecutableNode*> code;
static bool started = false;
static std::string codeString;
static std::string currentCodeString;
static std::string currentError;

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
std::stack<Cmm::ValueObject>   evalStack;

static void do_step_once(bool exec = true, bool first = false, bool recursive = false) {
    try {
        auto node = executionStack.top();
        auto step_over = dynamic_cast<Cmm::StepOverNode*>(node);
        auto step_result = dynamic_cast<Cmm::StepOverNodeWithResult*>(node);

        auto wait_step = dynamic_cast<Cmm::DebuggerWaitToStepNode*>(node);

        if (!first && recursive && wait_step) return; // ignore

        if (step_over) {
            auto object = Cmm::ValueObject::Void();
            if (!evalStack.empty() && !first) {
                object = evalStack.top();
                evalStack.pop();
            }

            if (const auto nextNode = step_over->step(object)) {
                executionStack.push(nextNode);

                if (const auto step_ = dynamic_cast<Cmm::StepOverNode*>(nextNode)) {
                    step_->enterStack();
                }

                if (const auto step_ = dynamic_cast<Cmm::StepOverNodeWithResult*>(nextNode)) {
                    step_->enterStack();
                }

                do_step_once(false, true, true);
            } else {
                step_over->exitStack();
                executionStack.pop(); // done with this step over node

                if (!executionStack.empty()) {
                    do_step_once(false, false, true); // pop back to the nearest step node
                }
            }
        } else if (step_result) {
            auto object = Cmm::ValueObject::Void();
            if (!evalStack.empty() && !first) {
                object = evalStack.top();
                evalStack.pop();
            }

            auto nextNode = step_result->step(object);
            if (nextNode.first) {
                executionStack.push(nextNode.first);

                if (const auto step_ = dynamic_cast<Cmm::StepOverNode*>(nextNode.first)) {
                    step_->enterStack();
                }

                if (const auto step_ = dynamic_cast<Cmm::StepOverNodeWithResult*>(nextNode.first)) {
                    step_->enterStack();
                }

                do_step_once(false, true, true);
            } else {
                step_result->exitStack();
                executionStack.pop(); // done with this step over node

                evalStack.push(nextNode.second);

                if (!executionStack.empty()) {
                    do_step_once(false, false, true); // pop back to the nearest step node
                }
            }
        } else if (exec) {
            if (dynamic_cast<Cmm::ExecutableNode*>(node)) {
                dynamic_cast<Cmm::ExecutableNode*>(node)->exec();
            }

            executionStack.pop();
            if (!executionStack.empty()) {
                do_step_once();
            }
        }

        if (executionStack.empty()) {
            codeString += currentCodeString;
            currentCodeString = "";
        }
    } catch (const std::exception& e) {
        currentError = e.what();
    }
}

static void start_debugged(Cmm::ExecutableNode* exec) {
    executionStack.push(exec);

    if (const auto step_ = dynamic_cast<Cmm::StepOverNode*>(exec)) {
        step_->enterStack();
    }

    if (const auto step_ = dynamic_cast<Cmm::StepOverNodeWithResult*>(exec)) {
        step_->enterStack();
    }

    do_step_once(false);
    Cmm::debugger::launch();
}

void Cmm::debugger::exec(std::string code) {

    yy_scan_string(code.c_str());

    int parse_result = yyparse();

    if (parse_result == 0) {
        currentCodeString = code;
        auto program = Cmm::Store::root;

        ::code.push_back(program->source);

        if (debuggerEnabled) {
            start_debugged(program->source);
            program->source = nullptr;
            delete program;
        } else {
            try {
                program->source->exec();
                program->source = nullptr;
                delete program;

                codeString += currentCodeString;
                currentCodeString = "";
                currentError = "";
            } catch (const std::exception& e) {
                currentCodeString = "";
                currentError = "";
                throw;
            }

        }
    }
}

void Cmm::debugger::step() {
    if (executionStack.empty()) return;
    if (! currentError.empty()) return;
    do_step_once();
}

std::string Cmm::debugger::getCode() {
    return codeString + currentCodeString;
}

int Cmm::debugger::getCurrentLine() {
    if (executionStack.empty()) return -1;

    Cmm::ASTNode* curr = executionStack.top();
    return curr->_lineNumber - 1; // fixme: maybe start lines from zero like a sane person ? :)
}

bool Cmm::debugger::isDone() {
    return executionStack.empty();
}

void Cmm::debugger::reset() {
    if (!isDone()) {
        while (executionStack.size() > 0) {
            executionStack.pop();
        }

        while (evalStack.size() > 0) {
            evalStack.pop();
        }

        currentCodeString = "";
        currentError = "";
    }
}

std::string Cmm::debugger::getError() {
    return currentError;
}

Cmm::Program::ProgramNode * Cmm::debugger::compileCode(std::string code) {
    yy_scan_string(code.c_str());


    int parse_result = yyparse();

    if (parse_result == 0) {
        auto program = Cmm::Store::root;
        return program;
    }

    return nullptr;
}


