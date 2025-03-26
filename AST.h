//
// Created by xabdomo on 3/25/25.
//

#ifndef AST_H
#define AST_H

#include "config.h"
#include "Values.h"

namespace Namespace {

    class ASTNode {
    public:
        virtual ~ASTNode() = default;
    };

    class EvaluableNode: public ASTNode {
    public:
        virtual ValueObject eval() = 0;
    };


}



#endif //AST_H
