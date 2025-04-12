//
// Created by xabdomo on 3/26/25.
//

#ifndef PROGRAM_H
#define PROGRAM_H

#include "../config.h"
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


    struct VariableBlock {
        Cmm::ValueObject Value;
        bool isConst;
    };

    struct Scope {
        std::map<std::string, VariableBlock> variables;
        std::map<FunctionSignature, Functional::FunctionNode*> functions;
        ASTNode* owner;
    };

    struct ProgramBlock {
        std::vector<Scope> stack;
        std::vector<std::string> moduleStack;
        ASTNode* programCode;
        std::map<FunctionSignature, NativeFunction> native_functions;
    };

    ProgramBlock& getCurrentProgram();

    void pushModule(const std::string&);
    void popModule();

    std::string getModule();
    std::string stringfy(FunctionSignature);

    void beginScope(ASTNode* owner = nullptr);
    void endScope();

    // todo: add other types
    Control::BreakPointNode* getNearestBreakPointScopeOwner();
    Control::ContinuePointNode* getNearestContinuePointScopeOwner();
    Control::ReturnPointNode* getNearestReturnPointScopeOwner();


    void createVariable(const std::string& name, Cmm::ValueObject, bool isConst = false);
    VariableBlock& getVariable(const std::string& name);

    void createFunction(const FunctionSignature &signature, Functional::FunctionNode*);
    void createFunction(const FunctionSignature &signature, NativeFunction handler);
    void validateNativeExists(const FunctionSignature& signature);
    ValueObject callFunction(const FunctionSignature& signature, const std::vector<ValueObject>&);

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

    class ConstantAssignmentError : public std::exception {
        std::string id;
    public:
        explicit ConstantAssignmentError(std::string  id);
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

    class NativeError : public std::exception {
        std::string msg;
    public:
        explicit NativeError(std::string  msg);
        [[nodiscard]] const char *what() const noexcept override;
    };

    // ========================= NODES =========================

    class ProgramNode: public ExecutableNode {
    public:

        std::vector<ExecutableNode*> source;
        explicit ProgramNode(ExecutableNode* source);
        explicit ProgramNode();

        void exec() override;
    };

    class ExpressionStatementNode: public ExecutableNode {
    public:
        EvaluableNode* expr;
        bool _silent = false;
        explicit ExpressionStatementNode(EvaluableNode* value);
        void exec() override;
    };

    class StatementListNode: public ExecutableNode, public StepOverNode {
    public:
        std::vector<ExecutableNode*> statements;
        int _curr_step_pos = 0;
        StatementListNode(StatementListNode* node, ExecutableNode* next);
        ~StatementListNode() override;
        void exec() override;
        ASTNode* step() override;
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
