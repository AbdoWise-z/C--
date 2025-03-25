%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern char *yytext;
void yyerror(const char *s);

%}

%union {
    char *str;
}

/* Tokens from the lexer */
%token <str> V_STRING V_NUMBER V_COMPLEX V_REAL

%token TYPE_REAL TYPE_INT TYPE_STR TYPE_COMPLEX TYPE_BOOL TYPE_VOID

%token OP_ASSIGN OP_PLUS OP_MINUS OP_MULT OP_DIV
%token OP_APLUS OP_AMINUS OP_AMULT OP_ADIV
%token OP_LS OP_RS OP_BOR OP_BAND OP_XOR
%token OP_ALS OP_ARL OP_ABOR OP_ABAND OP_AXOR
%token OP_OR OP_AND OP_NOT OP_INVERT

%token D_SEMICOLON D_LPAREN D_RPAREN D_LBRACE D_RBRACE D_COLON D_COMMA

%token CONTROL_IF CONTROL_ELSE CONTROL_WHILE CONTROL_FOR CONTROL_SWITCH
%token CONTROL_CASE CONTROL_DEFAULT CONTROL_DO CONTROL_RETURN CONTROL_BREAK CONTROL_CONTINUE

%token MISC_FUNC MISC_VAR MISC_CONST MISC_IMPORT MISC_EXPORT MISC_NATIVE

%token <str> ID

%start program

%%

program:
    /* empty */
    | program statement
    ;

statement:
    expression D_SEMICOLON
    | variable_declaration D_SEMICOLON
    | function_declaration
    | control_structure
    ;

expression:
    ID
    | V_STRING
    | V_NUMBER
    | V_COMPLEX
    | V_REAL
    | expression OP_PLUS expression
    | expression OP_MINUS expression
    | expression OP_MULT expression
    | expression OP_DIV expression
    | D_LPAREN expression D_RPAREN
    ;

variable_declaration:
    MISC_VAR ID D_COLON type_specifier OP_ASSIGN expression
    | MISC_CONST ID D_COLON type_specifier OP_ASSIGN expression
    ;

type_specifier:
    TYPE_INT
    | TYPE_REAL
    | TYPE_STR
    | TYPE_COMPLEX
    | TYPE_BOOL
    | TYPE_VOID
    ;

function_declaration:
    MISC_FUNC ID D_LPAREN parameters D_RPAREN D_COLON type_specifier D_LBRACE statements D_RBRACE
    ;

parameters:
    /* empty */
    | parameter_list
    ;

parameter_list:
    parameter
    | parameter_list D_COMMA parameter
    ;

parameter:
    ID D_COLON type_specifier
    ;

control_structure:
    CONTROL_IF D_LPAREN expression D_RPAREN D_LBRACE statements D_RBRACE
    | CONTROL_IF D_LPAREN expression D_RPAREN D_LBRACE statements D_RBRACE CONTROL_ELSE D_LBRACE statements D_RBRACE
    | CONTROL_WHILE D_LPAREN expression D_RPAREN D_LBRACE statements D_RBRACE
    | CONTROL_FOR D_LPAREN expression D_SEMICOLON expression D_SEMICOLON expression D_RPAREN D_LBRACE statements D_RBRACE
    ;

statements:
    /* empty */
    | statements statement
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    yyparse();
    return 0;
}