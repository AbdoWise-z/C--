%{
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern YYSTYPE yylval;

%}

%%

\"([^\"]*)\"      {
    char *temp = strdup(yytext + 1);
    temp[strlen(temp) - 1] = '\0';
    yylval.str = strdup(temp);
    free(temp);
    return V_STRING;
}

[0-9]+   {
    yylval.str = yytext;
    return V_NUMBER;
}

[0-9]+i  {
    yylval.str = yytext;
    return V_COMPLEX;
}

[0-9]+\.[0-9]+ {
    yylval.str = yytext;
    return V_REAL;
}

"real"    { return TYPE_REAL; }
"int"     { return TYPE_INT; }
"str"     { return TYPE_STR; }
"complex" { return TYPE_COMPLEX; }
"bool"    { return TYPE_BOOL; }
"void"    { return TYPE_VOID; }

"="       { return OP_ASSIGN; }
"+"       { return OP_PLUS; }
"-"       { return OP_MINUS; }
"*"       { return OP_MULT; }
"/"       { return OP_DIV; }
"+="      { return OP_APLUS; }
"-="      { return OP_AMINUS; }
"*="      { return OP_AMULT; }
"/="      { return OP_ADIV; }
">>"      { return OP_LS; }
"<<"      { return OP_RS; }
"|"       { return OP_BOR; }
"&"       { return OP_BAND; }
"^"       { return OP_XOR; }
">>="     { return OP_ALS; }
"<<="     { return OP_ARL; }
"|="      { return OP_ABOR; }
"&="      { return OP_ABAND; }
"^="      { return OP_AXOR; }
"||"      { return OP_OR; }
"&&"      { return OP_AND; }
"!"       { return OP_NOT; }
"~"       { return OP_INVERT; }

";"       { return D_SEMICOLON; }
"("       { return D_LPAREN; }
")"       { return D_RPAREN; }
"{"       { return D_LBRACE; }
"}"       { return D_RBRACE; }
":"       { return D_COLON; }
","       { return D_COLON; }

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
"var"     { return MISC_VAR; }
"const"   { return MISC_CONST; }
"import"  { return MISC_IMPORT; }
"export"  { return MISC_EXPORT; }
"native"  { return MISC_NATIVE; }


[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }


[ \t\n]   { }

%%

int yywrap() { return 1; }

int main() {
    int token;
    while ((token = yylex())) {
        printf("Token: %d\n", token);
    }
    return 0;
}
