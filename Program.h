//
// Created by xabdomo on 3/26/25.
//

#ifndef PROGRAM_H
#define PROGRAM_H

#include "config.h"
#include "AST.h"

#include <map>
#include <vector>

#include "Control.h"
#include "Typing.h"

// forward declare function node since it's used in the scope type
namespace Namespace::Functional {
    class FunctionNode;
}

namespace Namespace::Program {

    class StatementListNode;
    class ExpressionStatementNode;
    class ScopeNode;

    extern std::vector<ValueType> conversionPriority;
    typedef std::pair<std::string, std::vector<ValueType>> function_sig;

    struct Scope {
        std::map<std::string, Cmm::ValueObject> variables;
        std::map<function_sig, Functional::FunctionNode*> functions;
        ASTNode* owner;
    };

    struct ProgramBlock {
        std::vector<Scope> stack;
        std::vector<std::string> moduleStack;
        ASTNode* programCode;
    };

    ProgramBlock& getCurrentProgram();

    void pushModule(const std::string&);
    void popModule();

    std::string getModule();

    void beginScope(ASTNode* owner = nullptr);
    void endScope();

    // todo: add other types
    Control::BreakPointNode* getNearestBreakPointScopeOwner();
    Control::ContinuePointNode* getNearestContinuePointScopeOwner();
    Control::ReturnPointNode* getNearestReturnPointScopeOwner();


    void createVariable(const std::string& name, Cmm::ValueObject);
    ValueObject& getVariable(const std::string& name);

    void createFunction(const function_sig &signature, Functional::FunctionNode*);
    ValueObject callFunction(const function_sig& signature, const std::vector<ValueObject>&);

    // ========================= ERRORS =========================

    class NoStackError : public std::exception {
    public:
        NoStackError();
        [[nodiscard]] const char *what() const noexcept override;
    };

    class AlreadyDefinedError : public std::exception {
        std::string id;
    public:
        explicit AlreadyDefinedError(std::string  id);
        [[nodiscard]] const char *what() const noexcept override;
    };

    class VariableNotFoundError : public std::exception {
        std::string id;
    public:
        explicit VariableNotFoundError(std::string  id);
        [[nodiscard]] const char *what() const noexcept override;
    };

    class FunctionNotFoundError : public std::exception {
        std::string id;
    public:
        explicit FunctionNotFoundError(std::string  id);
        [[nodiscard]] const char *what() const noexcept override;
    };

    class ControlError : public std::exception {
        std::string msg;
    public:
        explicit ControlError(std::string  msg);
        [[nodiscard]] const char *what() const noexcept override;
    };

    // ========================= NODES =========================

    class ProgramNode: public ExecutableNode {
    public:

        ExecutableNode* source;
        explicit ProgramNode(ExecutableNode* source);
        void exec() override;
    };

    class ExpressionStatementNode: public ExecutableNode {
    public:
        EvaluableNode* expr;
        explicit ExpressionStatementNode(EvaluableNode* value);
        void exec() override;
    };

    class StatementListNode: public ExecutableNode {
    public:
        std::vector<ExecutableNode*> statements;
        StatementListNode(StatementListNode* node, ExecutableNode* next);
        ~StatementListNode() override;
        void exec() override;
    };

    class ScopeNode: public ExecutableNode {
    public:
        ExecutableNode* statements;
        explicit ScopeNode(ExecutableNode* node);
        void exec() override;
        ~ScopeNode() override;
    };

}

#endif //PROGRAM_H
