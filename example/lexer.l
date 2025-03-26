%{
#include <string>
#include <iostream>
#include "parser.tab.hpp"

// Macro to simplify token return
#define TOKEN(t) yylval.number = 0; return t
%}

%option noyywrap

%%

[ \t\n]         ; // Ignore whitespace
[0-9]+(\.[0-9]+)?   { 
    yylval.number = atof(yytext); 
    return NUMBER; 
}
"+"             { TOKEN(PLUS); }
"-"             { TOKEN(MINUS); }
"*"             { TOKEN(MULTIPLY); }
"/"             { TOKEN(DIVIDE); }
"("             { TOKEN(LPAREN); }
")"             { TOKEN(RPAREN); }
.               { 
    std::cerr << "Unexpected character: " << yytext << std::endl; 
    return 0; 
}

%%