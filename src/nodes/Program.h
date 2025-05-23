
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
    class FunctionDeclarationNode;
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
        std::map<std::string, std::map<FunctionDefinitionSignature, Functional::FunctionDeclarationNode*>> functions;
        ASTNode* owner;
        std::string name;
    };

    struct ProgramBlock {
        std::vector<Scope> stack;
        std::vector<std::string> moduleStack;
        ASTNode* programCode;
        std::map<std::string, std::map<FunctionDefinitionSignature, std::pair<NativeFunction, Functional::FunctionDeclarationNode*>>> native_functions;
    };

    ProgramBlock& getCurrentProgram();

    void pushModule(const std::string&);
    void popModule();

    std::string getModule();
    std::string stringfy(FunctionSignature);

    void beginScope(ASTNode* owner = nullptr, std::string name = "");
    void endScope();

    // todo: add other types
    Control::BreakPointNode* getNearestBreakPointScopeOwner();
    Control::ContinuePointNode* getNearestContinuePointScopeOwner();
    Control::ReturnPointNode* getNearestReturnPointScopeOwner();


    void createVariable(const std::string& name, Cmm::ValueObject, bool isConst = false);
    VariableBlock& getVariable(const std::string& name, ASTNode* _req);

    void createFunction(const std::string& name, const FunctionDefinitionSignature &signature, Functional::FunctionDeclarationNode*);
    void createFunction(const std::string& name, const FunctionDefinitionSignature &signature, NativeFunction handler);
    void attachNativeFunctionDefinition(const std::string& name, const FunctionDefinitionSignature& signature, Functional::FunctionDeclarationNode*);
    std::pair<Functional::FunctionDeclarationNode*, std::vector<bool>> getFunction(const FunctionSignature& signature, ASTNode* _req);

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

        ExecutableNode* source;
        explicit ProgramNode(ExecutableNode* source);
        explicit ProgramNode();
        ~ProgramNode() override;

        void exec() override;
    };

    class ExpressionStatementNode: public virtual ExecutableNode, public virtual StepOverNode, public virtual DebuggerWaitToStepNode  {
    public:
        EvaluableNode* expr;
        bool _silent = false;
        explicit ExpressionStatementNode(EvaluableNode* value);
        void exec() override;

        //debugging
        std::stack<int> _curr_step_pos;

        ASTNode* step(ValueObject) override;
        void enterStack() override;
        void exitStack() override;;
    };

    class StatementListNode: public ExecutableNode, public StepOverNode {
    public:
        std::vector<ExecutableNode*> statements;


        StatementListNode(StatementListNode* node, ExecutableNode* next);
        ~StatementListNode() override;
        void exec() override;

        //debugging
        std::stack<int> _curr_step_pos;
        ASTNode* step(ValueObject) override;
        void enterStack() override;
        void exitStack() override;;
    };

    class ScopeNode: public virtual ExecutableNode, public virtual StepOverNode {
    public:
        // debugging
        std::stack<int> _curr_step_pos;

        ExecutableNode* statements;
        explicit ScopeNode(ExecutableNode* node);
        void exec() override;
        ~ScopeNode() override;
        void enterStack() override;
        void exitStack() override;
        ASTNode *step(ValueObject) override;
    };
}

#endif //PROGRAM_H
