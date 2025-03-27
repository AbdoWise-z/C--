//
// Created by xabdomo on 3/27/25.
//

#ifndef TYPING_H
#define TYPING_H

#include <set>

#include "config.h"
#include "AST.h"


namespace Namespace::Typing {
    class TypeListNode final : public ASTNode {
    public:
        std::set<ValueType> types;
        TypeListNode(TypeListNode* prev, std::string next);
        ~TypeListNode() override;
    };
};



#endif //TYPING_H
