//
// Created by xabdomo on 4/28/25.
//

#ifndef MACROS_HPP
#define MACROS_HPP

#include "AST.h"
#include "../config.h"

namespace Namespace::Macros {
    class ClearMacro: public virtual ASTNode, public virtual ExecutableNode {
    public:
        ClearMacro();
        void exec() override;
        ~ClearMacro() override;
    };
};



#endif //MACROS_HPP
