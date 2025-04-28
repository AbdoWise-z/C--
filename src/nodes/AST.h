
#ifndef AST_H
#define AST_H

#include <map>

#include "../config.h"
#include "../Values.h"

namespace Namespace {

    class ASTNode;
    class EvaluableNode;
    class ExecutableNode;


    class ASTNode {
    public:
        int _lineNumber;
        int _virtualLineNumber;
        ASTNode* _parent;
        ASTNode();
        virtual ~ASTNode() = default;
    };

    class EvaluableNode: virtual public ASTNode {
    public:
        virtual ValueObject eval() = 0;
    };

    class ExecutableNode: virtual public ASTNode {
    public:
        virtual void exec() = 0;
    };

    class StepOverNode: virtual public ASTNode {
    public:
        virtual ASTNode* step(ValueObject) = 0;
        virtual void enterStack() = 0;
        virtual void exitStack() = 0;
    };

    class StepOverNodeWithResult: virtual public ASTNode {
    public:
        virtual std::pair<ASTNode*, ValueObject> step(ValueObject) = 0;
        virtual void enterStack() = 0;
        virtual void exitStack() = 0;
    };

    class DebuggerWaitToStepNode : virtual public ASTNode {
    public:
        ~DebuggerWaitToStepNode() override = default;
    };
}



#endif //AST_H
