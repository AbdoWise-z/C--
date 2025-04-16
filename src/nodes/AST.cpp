//
// Created by xabdomo on 3/25/25.
//

#include "AST.h"

extern int yylineno;

Cmm::ASTNode::ASTNode() {
    _lineNumber = yylineno;
}
