//
// Created by xabdomo on 3/27/25.
//

#ifndef CONTROL_H
#define CONTROL_H

#include "config.h"
#include "AST.h"
#include "Program.h"


namespace Namespace::Control {
    class IFNode: public ExecutableNode {
    public:
        ExecutableNode* if_true;
        ExecutableNode* if_false;
        EvaluableNode* condition;

        IFNode(EvaluableNode* condition, ExecutableNode* if_true, ExecutableNode* if_false);
        void exec() override;
        ~IFNode() override;
    };
}



#endif //CONTROL_H
