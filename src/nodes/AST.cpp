
#include "AST.h"

extern int yylineno;
extern int yyvlineno;

int yyvlineno = 0;

Cmm::ASTNode::ASTNode() {
    _lineNumber = yylineno;
    _virtualLineNumber = yyvlineno;
}
