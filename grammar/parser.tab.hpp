/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_HPP_INCLUDED
# define YY_YY_PARSER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    END = 258,                     /* END  */
    V_STRING = 259,                /* V_STRING  */
    V_INTEGER = 260,               /* V_INTEGER  */
    V_COMPLEX = 261,               /* V_COMPLEX  */
    V_REAL = 262,                  /* V_REAL  */
    V_BOOLEAN = 263,               /* V_BOOLEAN  */
    ID = 264,                      /* ID  */
    TYPE_REAL = 265,               /* TYPE_REAL  */
    TYPE_INT = 266,                /* TYPE_INT  */
    TYPE_STR = 267,                /* TYPE_STR  */
    TYPE_COMPLEX = 268,            /* TYPE_COMPLEX  */
    TYPE_BOOL = 269,               /* TYPE_BOOL  */
    TYPE_VOID = 270,               /* TYPE_VOID  */
    OP_ASSIGN = 271,               /* OP_ASSIGN  */
    OP_PLUS = 272,                 /* OP_PLUS  */
    OP_MINUS = 273,                /* OP_MINUS  */
    OP_MULT = 274,                 /* OP_MULT  */
    OP_DIV = 275,                  /* OP_DIV  */
    OP_MOD = 276,                  /* OP_MOD  */
    OP_APLUS = 277,                /* OP_APLUS  */
    OP_AMINUS = 278,               /* OP_AMINUS  */
    OP_AMULT = 279,                /* OP_AMULT  */
    OP_ADIV = 280,                 /* OP_ADIV  */
    OP_LS = 281,                   /* OP_LS  */
    OP_RS = 282,                   /* OP_RS  */
    OP_BOR = 283,                  /* OP_BOR  */
    OP_BAND = 284,                 /* OP_BAND  */
    OP_XOR = 285,                  /* OP_XOR  */
    OP_ALS = 286,                  /* OP_ALS  */
    OP_ARS = 287,                  /* OP_ARS  */
    OP_ABOR = 288,                 /* OP_ABOR  */
    OP_ABAND = 289,                /* OP_ABAND  */
    OP_AXOR = 290,                 /* OP_AXOR  */
    OP_OR = 291,                   /* OP_OR  */
    OP_AND = 292,                  /* OP_AND  */
    OP_NOT = 293,                  /* OP_NOT  */
    OP_INVERT = 294,               /* OP_INVERT  */
    OP_EQUAL = 295,                /* OP_EQUAL  */
    OP_GREATER = 296,              /* OP_GREATER  */
    OP_LESS = 297,                 /* OP_LESS  */
    OP_GE = 298,                   /* OP_GE  */
    OP_LE = 299,                   /* OP_LE  */
    OP_NEQUAL = 300,               /* OP_NEQUAL  */
    D_SEMICOLON = 301,             /* D_SEMICOLON  */
    D_LPAREN = 302,                /* D_LPAREN  */
    D_RPAREN = 303,                /* D_RPAREN  */
    D_LBRACE = 304,                /* D_LBRACE  */
    D_RBRACE = 305,                /* D_RBRACE  */
    D_COLON = 306,                 /* D_COLON  */
    D_COMMA = 307,                 /* D_COMMA  */
    D_ARROW = 308,                 /* D_ARROW  */
    CONTROL_IF = 309,              /* CONTROL_IF  */
    CONTROL_ELSE = 310,            /* CONTROL_ELSE  */
    CONTROL_WHILE = 311,           /* CONTROL_WHILE  */
    CONTROL_FOR = 312,             /* CONTROL_FOR  */
    CONTROL_SWITCH = 313,          /* CONTROL_SWITCH  */
    CONTROL_CASE = 314,            /* CONTROL_CASE  */
    CONTROL_DEFAULT = 315,         /* CONTROL_DEFAULT  */
    CONTROL_DO = 316,              /* CONTROL_DO  */
    CONTROL_RETURN = 317,          /* CONTROL_RETURN  */
    CONTROL_BREAK = 318,           /* CONTROL_BREAK  */
    CONTROL_CONTINUE = 319,        /* CONTROL_CONTINUE  */
    MISC_FUNC = 320,               /* MISC_FUNC  */
    MISC_FROM = 321,               /* MISC_FROM  */
    MISC_VAR = 322,                /* MISC_VAR  */
    MISC_CONST = 323,              /* MISC_CONST  */
    MISC_IMPORT = 324,             /* MISC_IMPORT  */
    MISC_EXPORT = 325,             /* MISC_EXPORT  */
    MISC_NATIVE = 326,             /* MISC_NATIVE  */
    OP_UNARY_MINUS = 327,          /* OP_UNARY_MINUS  */
    LOWER_THAN_ELSE = 328          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 37 "parser.ypp"

    std::string* str;
    Cmm::EvaluableNode* evaluable;
    Cmm::ExecutableNode* executable;
    Cmm::ASTNode* node;
    Cmm::Typing::TypeListNode* tlist;

#line 145 "parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
