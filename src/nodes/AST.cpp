
#include "AST.h"

extern int yylineno;

Cmm::ASTNode::ASTNode() {
    _lineNumber = yylineno;
}
