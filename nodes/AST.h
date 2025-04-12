//
// Created by xabdomo on 3/25/25.
//

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
        virtual ASTNode* step() = 0;
    };

    class StepInNode: virtual public ASTNode, virtual public StepOverNode {
    public:
        virtual ASTNode* step_in() = 0;
    };
}



#endif //AST_H
