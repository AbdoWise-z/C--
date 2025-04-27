
#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include "../config.h"
#include "Program.h"

namespace Namespace::Functional {
    class FunctionDeclarationNode;
    class FunctionArgumentNode;
    class FunctionArgumentListNode;
    class FunctionCallNode;



    class FunctionDeclarationNode: public ExecutableNode, public Control::ReturnPointNode  {
    public:
        FunctionArgumentListNode* arguments;
        Program::StatementListNode* function;
        std::string id;
        Typing::TypeListNode* returnType;

        NativeFunction handler;

        explicit FunctionDeclarationNode(FunctionArgumentListNode* arguments, Program::StatementListNode* function, std::string id, Typing::TypeListNode* returnType);
        void exec() override;
        virtual ValueObject invoke(const std::vector<ValueObject>&);
        ~FunctionDeclarationNode() override;
    };

    // class NativeFunctionDeclarationNode: public ExecutableNode {
    // public:
    //     FunctionArgumentListNode* arguments;
    //     Typing::TypeListNode* returnType;
    //     std::string id;
    //
    //     explicit NativeFunctionDeclarationNode(FunctionArgumentListNode* arguments, Typing::TypeListNode* returnType, std::string id);
    //     void exec() override;
    //     ~NativeFunctionDeclarationNode() override;
    // };

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

    class FunctionCallNode: public EvaluableNode, public StepOverNodeWithResult {
    public:
        std::string id;
        FunctionParamListNode* funcParam;

        explicit FunctionCallNode(std::string id, FunctionParamListNode* funcParam);
        ~FunctionCallNode() override;
        ValueObject eval() override;

        // debugging
        std::stack<FunctionDeclarationNode*> _curr_func;
        std::stack<ASTNode*> _marker_node;
        std::stack<std::vector<ValueObject>> _curr_params;
        std::stack<int> _curr_step_pos;

        void enterStack() override;
        std::pair<ASTNode*, ValueObject> step(ValueObject) override;
        void exitStack() override;
    };

    // class FunctionNode: public Control::ReturnPointNode {
    // public:
    //     FunctionArgumentListNode* arguments;
    //     Program::StatementListNode* function;
    //     std::string id;
    //     Typing::TypeListNode* returnType;
    //
    //     FunctionNode(FunctionArgumentListNode* arguments, Program::StatementListNode* function, std::string id, Typing::TypeListNode* returnType);
    //
    //     virtual void decl();
    //     virtual ValueObject exec(const std::vector<ValueObject>&);
    //     ~FunctionNode() override;
    // };
};



#endif //FUNCTIONAL_H
