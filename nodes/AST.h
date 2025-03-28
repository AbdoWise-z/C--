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
}



#endif //AST_H
