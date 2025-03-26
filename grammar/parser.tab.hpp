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
# define YYDEBUG 0
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
    OP_APLUS = 276,                /* OP_APLUS  */
    OP_AMINUS = 277,               /* OP_AMINUS  */
    OP_AMULT = 278,                /* OP_AMULT  */
    OP_ADIV = 279,                 /* OP_ADIV  */
    OP_LS = 280,                   /* OP_LS  */
    OP_RS = 281,                   /* OP_RS  */
    OP_BOR = 282,                  /* OP_BOR  */
    OP_BAND = 283,                 /* OP_BAND  */
    OP_XOR = 284,                  /* OP_XOR  */
    OP_ALS = 285,                  /* OP_ALS  */
    OP_ARL = 286,                  /* OP_ARL  */
    OP_ABOR = 287,                 /* OP_ABOR  */
    OP_ABAND = 288,                /* OP_ABAND  */
    OP_AXOR = 289,                 /* OP_AXOR  */
    OP_OR = 290,                   /* OP_OR  */
    OP_AND = 291,                  /* OP_AND  */
    OP_NOT = 292,                  /* OP_NOT  */
    OP_INVERT = 293,               /* OP_INVERT  */
    D_SEMICOLON = 294,             /* D_SEMICOLON  */
    D_LPAREN = 295,                /* D_LPAREN  */
    D_RPAREN = 296,                /* D_RPAREN  */
    D_LBRACE = 297,                /* D_LBRACE  */
    D_RBRACE = 298,                /* D_RBRACE  */
    D_COLON = 299,                 /* D_COLON  */
    D_COMMA = 300,                 /* D_COMMA  */
    CONTROL_IF = 301,              /* CONTROL_IF  */
    CONTROL_ELSE = 302,            /* CONTROL_ELSE  */
    CONTROL_WHILE = 303,           /* CONTROL_WHILE  */
    CONTROL_FOR = 304,             /* CONTROL_FOR  */
    CONTROL_SWITCH = 305,          /* CONTROL_SWITCH  */
    CONTROL_CASE = 306,            /* CONTROL_CASE  */
    CONTROL_DEFAULT = 307,         /* CONTROL_DEFAULT  */
    CONTROL_DO = 308,              /* CONTROL_DO  */
    CONTROL_RETURN = 309,          /* CONTROL_RETURN  */
    CONTROL_BREAK = 310,           /* CONTROL_BREAK  */
    CONTROL_CONTINUE = 311,        /* CONTROL_CONTINUE  */
    MISC_FUNC = 312,               /* MISC_FUNC  */
    MISC_VAR = 313,                /* MISC_VAR  */
    MISC_CONST = 314,              /* MISC_CONST  */
    MISC_IMPORT = 315,             /* MISC_IMPORT  */
    MISC_EXPORT = 316,             /* MISC_EXPORT  */
    MISC_NATIVE = 317,             /* MISC_NATIVE  */
    OP_UNARY_MINUS = 318           /* OP_UNARY_MINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 25 "parser.ypp"

    std::string* str;
    Cmm::EvaluableNode* evaluable;

#line 132 "parser.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_HPP_INCLUDED  */
