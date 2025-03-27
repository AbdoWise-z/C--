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


namespace Namespace::Program {

    class FunctionNode;
    class FunctionArgumentListNode;
    class FunctionArgumentNode;
    class FunctionDeclarationNode;
    class StatementListNode;
    class VariableAssignmentNode;
    class ExpressionStatementNode;
    class VariableDeclarationNode;
    class FunctionCallNode;
    class ScopeNode;

    typedef std::pair<std::string, std::vector<ValueType>> function_sig;

    struct Scope {
        std::map<std::string, Cmm::ValueObject> variables;
        std::map<function_sig, FunctionNode*> functions;
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

    void createFunction(const function_sig &signature, FunctionNode*);
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
        explicit ExpressionStatementNode(EvaluableNode* value);
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
    public:
        FunctionNode* node;
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

    class FunctionParamListNode: public ASTNode {
    public:
        std::vector<EvaluableNode*> params;
        FunctionParamListNode(FunctionParamListNode* other, EvaluableNode* next);
        [[nodiscard]] std::vector<ValueObject> getParams() const;
        ~FunctionParamListNode() override;
    };

    class FunctionCallNode: public EvaluableNode {
    public:
        std::string id;
        FunctionParamListNode* funcParam;
        explicit FunctionCallNode(std::string id, FunctionParamListNode* funcParam);
        ~FunctionCallNode() override;
        ValueObject eval() override;
    };

    class FunctionNode: public Control::ReturnPointNode {
    public:
        FunctionArgumentListNode* arguments;
        StatementListNode* function;
        std::string id;
        Typing::TypeListNode* returnType;

        FunctionNode(FunctionArgumentListNode* arguments, StatementListNode* function, std::string id, Typing::TypeListNode* returnType);

        virtual void decl();
        virtual ValueObject exec(const std::vector<ValueObject>&);
        ~FunctionNode() override;
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
