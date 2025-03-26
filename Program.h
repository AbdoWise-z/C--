//
// Created by xabdomo on 3/26/25.
//

#ifndef PROGRAM_H
#define PROGRAM_H

#include "config.h"
#include "AST.h"

#include <map>
#include <vector>


namespace Cmm::Program {

    class FunctionNode;
    class FunctionArgumentListNode;
    class FunctionArgumentNode;
    class FunctionDeclarationNode;
    class StatementListNode;
    class VariableAssignmentNode;
    class ExpressionStatementNode;
    class VariableDeclarationNode;

    typedef std::pair<std::string, std::pmr::vector<ValueType>> function_sig;

    struct Scope {
        std::map<std::string, Cmm::ValueObject> variables;
        std::map<function_sig, FunctionNode*> functions;
    };

    struct ProgramBlock {
        std::vector<Scope> stack;
        ASTNode* programCode;
    };

    ProgramBlock& getCurrentProgram();

    void beginScope();
    void endScope();

    void createVariable(const std::string& name, Cmm::ValueObject);
    ValueObject& getVariable(const std::string& name);

    void createFunction(const function_sig &signature, FunctionNode*);
    ValueObject callFunction(const function_sig& signature, std::map<std::string, ValueObject>);

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

    // ========================= NODES =========================

    class ProgramNode: public ExecutableNode {
    public:

        ExecutableNode* source;
        ProgramNode(ExecutableNode* source);
        void exec() override;
    };

    class VariableDeclarationNode: public ExecutableNode {
    public:
        bool isConst;
        std::string name;
        std::string type;
        EvaluableNode* value;
        VariableDeclarationNode(bool isConst, std::string name, std::string type, EvaluableNode* value);
        void exec() override;
    };

    class ExpressionStatementNode: public ExecutableNode {
    public:
        EvaluableNode* expr;
        ExpressionStatementNode(EvaluableNode* value);
        void exec() override;
    };

    class VariableAssignmentNode: public ExecutableNode {
    public:
        std::string name;
        EvaluableNode* expr;
        VariableAssignmentNode(std::string name, EvaluableNode* value);
        void exec() override;
    };

    class StatementListNode: public ExecutableNode {
    public:
        std::vector<ExecutableNode*> statements;
        StatementListNode(StatementListNode* node, ExecutableNode* next);
        ~StatementListNode() override;
        void exec() override;
    };

    class FunctionDeclarationNode: public ExecutableNode {
    private:
        FunctionNode* node;
    public:
        explicit FunctionDeclarationNode(FunctionNode* node);
        void exec() override;
        ~FunctionDeclarationNode() override;
    };

    class FunctionArgumentNode: public ASTNode {
    public:
        std::string id;
        std::string type;
        EvaluableNode* defaultValue;
        FunctionArgumentNode(std::string id, std::string type);
        FunctionArgumentNode(std::string id, std::string type, EvaluableNode* defaultValue);
        [[nodiscard]] ValueObject getDefaultValue() const;
        [[nodiscard]] bool hasDefaultValue() const;
        ~FunctionArgumentNode() override;
    };

    class FunctionArgumentListNode: public ASTNode {
    public:
        std::vector<FunctionArgumentNode*> arguments;
        FunctionArgumentListNode(FunctionArgumentListNode* other, FunctionArgumentNode* next);
        ~FunctionArgumentListNode() override;
    };

    class FunctionNode: public ASTNode {

    public:
        virtual ValueObject decl();
        virtual ValueObject exec(std::map<std::string, ValueObject>);
        ~FunctionNode();
    };

}

#endif //PROGRAM_H
