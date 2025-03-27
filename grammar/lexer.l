%{
#include <string>
#include <iostream>

#include "../config.h"
#include "../forward.h"
#include "../AST.h"
#include "../primitives.h"
#include "../MathHelper.h"
#include "../Values.h"
#include "../Expressions.h"
#include "../Program.h"
#include "../Typing.h"
#include "../Control.h"

#include "parser.tab.hpp"

void remove_first_and_last_char(std::string* str_ptr) {
    if (str_ptr == nullptr || str_ptr->length() < 2) {
        return;
    }
    str_ptr->erase(0, 1);
    str_ptr->pop_back();
}

%}

%option noyywrap

%%

\"([^\"]*)\"      {
    std::string* val = new std::string(yytext);
    remove_first_and_last_char(val);
    yylval.str = val;
    return V_STRING;
}

[0-9]+"\."[0-9]+ {
    std::string* val = new std::string(yytext);
    yylval.str = val;
    return V_REAL;
}

[0-9]+   {
    std::string* val = new std::string(yytext);
    yylval.str = val;
    return V_INTEGER;
}

[0-9]+i  {
    std::string* val = new std::string(yytext);
    yylval.str = val;
    return V_COMPLEX;
}

"true"|"false" {
    std::string* val = new std::string(yytext);
    yylval.str = val;
    return V_BOOLEAN;
}

";"       { return D_SEMICOLON; }
"("       { return D_LPAREN; }
")"       { return D_RPAREN; }
"{"       { return D_LBRACE; }
"}"       { return D_RBRACE; }
":"       { return D_COLON; }
","       { return D_COMMA; }
"->"      { return D_ARROW; }

"real"    { return TYPE_REAL; }
"int"     { return TYPE_INT; }
"str"     { return TYPE_STR; }
"complex" { return TYPE_COMPLEX; }
"bool"    { return TYPE_BOOL; }
"void"    { return TYPE_VOID; }

"+"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_PLUS; }
"-"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_MINUS; }
"*"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_MULT; }
"/"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_DIV; }
"%"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_MOD; }

"+="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_APLUS; }
"-="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_AMINUS; }
"*="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_AMULT; }
"/="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_ADIV; }

">>"      { std::string* val = new std::string(yytext); yylval.str = val; return OP_RS; }
"<<"      { std::string* val = new std::string(yytext); yylval.str = val; return OP_LS; }
"|"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_BOR; }
"&"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_BAND; }
"^"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_XOR; }

">>="     { std::string* val = new std::string(yytext); yylval.str = val; return OP_ARS; }
"<<="     { std::string* val = new std::string(yytext); yylval.str = val; return OP_ALS; }
"|="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_ABOR; }
"&="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_ABAND; }
"^="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_AXOR; }

"||"      { std::string* val = new std::string(yytext); yylval.str = val; return OP_OR; }
"&&"      { std::string* val = new std::string(yytext); yylval.str = val; return OP_AND; }
"=="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_EQUAL; }
"!="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_NEQUAL; }
"!"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_NOT; }
"~"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_INVERT; }

">="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_GE; }
"<="      { std::string* val = new std::string(yytext); yylval.str = val; return OP_LE; }
">"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_GREATER; }
"<"       { std::string* val = new std::string(yytext); yylval.str = val; return OP_LESS; }

"="       { std::string* val = new std::string(yytext); yylval.str = val; return OP_ASSIGN; }

"if"       { return CONTROL_IF; }
"else"     { return CONTROL_ELSE; }
"while"    { return CONTROL_WHILE; }
"for"      { return CONTROL_FOR; }
"switch"   { return CONTROL_SWITCH; }
"case"     { return CONTROL_CASE; }
"default"  { return CONTROL_DEFAULT; }
"do"       { return CONTROL_DO; }
"return"   { return CONTROL_RETURN; }
"break"    { return CONTROL_BREAK; }
"continue" { return CONTROL_CONTINUE; }

"func"    { return MISC_FUNC; }
"fun"     { return MISC_FUNC; }
"from"    { return MISC_FROM; }
"var"     { return MISC_VAR; }
"const"   { return MISC_CONST; }
"import"  { return MISC_IMPORT; }
"export"  { return MISC_EXPORT; }
"native"  { return MISC_NATIVE; }

[a-zA-Z_][a-zA-Z0-9_]*  { 
    std::string* val = new std::string(yytext);
    yylval.str = val;
    return ID;
}

[ \t\n]   { /* Skip whitespace */ }

<<EOF>>         { return END; }

.               { 
    std::cerr << "Unexpected character: " << yytext << std::endl; 
    return 0; 
}

%%