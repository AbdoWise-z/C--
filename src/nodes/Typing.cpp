
#include "Typing.h"

Cmm::Typing::TypeListNode::TypeListNode(TypeListNode *prev, std::string next) {
    types.clear();
    if (prev) {
        types = prev->types;
        prev->types.clear();
        delete prev;
    }

    types.insert(ValuesHelper::StringToValueType(next));
}

Cmm::Typing::TypeListNode::~TypeListNode() = default;
