/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.ypp"

#include <iostream>
#include <string>

#include "../config.h"
#include "../forward.h"
#include "../nodes/AST.h"
#include "../primitives.h"
#include "../MathHelper.h"
#include "../Values.h"
#include "../nodes/Expressions.h"
#include "../nodes/Program.h"
#include "../nodes/Typing.h"
#include "../nodes/Control.h"
#include "../nodes/Variables.h"
#include "../nodes/Functional.h"

#include "parser.tab.hpp"

// Declare yylex for Bison
extern int yylex();

extern char* yytext;
extern int yylineno;
extern int yydebug;

void yyerror(const char* s) {
  std::cout << "\033[31m" << "Error at line " << yylineno << ": " << s 
              << " (unexpected token: '" << yytext << "')" 
              << "\033[0m" << std::endl;
}

extern Cmm::Program::ProgramNode* root;


#line 107 "parser.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_END = 3,                        /* END  */
  YYSYMBOL_V_STRING = 4,                   /* V_STRING  */
  YYSYMBOL_V_INTEGER = 5,                  /* V_INTEGER  */
  YYSYMBOL_V_COMPLEX = 6,                  /* V_COMPLEX  */
  YYSYMBOL_V_REAL = 7,                     /* V_REAL  */
  YYSYMBOL_V_BOOLEAN = 8,                  /* V_BOOLEAN  */
  YYSYMBOL_ID = 9,                         /* ID  */
  YYSYMBOL_TYPE_REAL = 10,                 /* TYPE_REAL  */
  YYSYMBOL_TYPE_INT = 11,                  /* TYPE_INT  */
  YYSYMBOL_TYPE_STR = 12,                  /* TYPE_STR  */
  YYSYMBOL_TYPE_COMPLEX = 13,              /* TYPE_COMPLEX  */
  YYSYMBOL_TYPE_BOOL = 14,                 /* TYPE_BOOL  */
  YYSYMBOL_TYPE_VOID = 15,                 /* TYPE_VOID  */
  YYSYMBOL_OP_ASSIGN = 16,                 /* OP_ASSIGN  */
  YYSYMBOL_OP_PLUS = 17,                   /* OP_PLUS  */
  YYSYMBOL_OP_MINUS = 18,                  /* OP_MINUS  */
  YYSYMBOL_OP_MULT = 19,                   /* OP_MULT  */
  YYSYMBOL_OP_DIV = 20,                    /* OP_DIV  */
  YYSYMBOL_OP_MOD = 21,                    /* OP_MOD  */
  YYSYMBOL_OP_LS = 22,                     /* OP_LS  */
  YYSYMBOL_OP_RS = 23,                     /* OP_RS  */
  YYSYMBOL_OP_BOR = 24,                    /* OP_BOR  */
  YYSYMBOL_OP_BAND = 25,                   /* OP_BAND  */
  YYSYMBOL_OP_XOR = 26,                    /* OP_XOR  */
  YYSYMBOL_OP_OR = 27,                     /* OP_OR  */
  YYSYMBOL_OP_AND = 28,                    /* OP_AND  */
  YYSYMBOL_OP_NOT = 29,                    /* OP_NOT  */
  YYSYMBOL_OP_INVERT = 30,                 /* OP_INVERT  */
  YYSYMBOL_OP_EQUAL = 31,                  /* OP_EQUAL  */
  YYSYMBOL_OP_GREATER = 32,                /* OP_GREATER  */
  YYSYMBOL_OP_LESS = 33,                   /* OP_LESS  */
  YYSYMBOL_OP_GE = 34,                     /* OP_GE  */
  YYSYMBOL_OP_LE = 35,                     /* OP_LE  */
  YYSYMBOL_OP_NEQUAL = 36,                 /* OP_NEQUAL  */
  YYSYMBOL_OP_APLUS = 37,                  /* OP_APLUS  */
  YYSYMBOL_OP_AMINUS = 38,                 /* OP_AMINUS  */
  YYSYMBOL_OP_AMULT = 39,                  /* OP_AMULT  */
  YYSYMBOL_OP_ADIV = 40,                   /* OP_ADIV  */
  YYSYMBOL_OP_AMOD = 41,                   /* OP_AMOD  */
  YYSYMBOL_OP_ARS = 42,                    /* OP_ARS  */
  YYSYMBOL_OP_ALS = 43,                    /* OP_ALS  */
  YYSYMBOL_OP_ABOR = 44,                   /* OP_ABOR  */
  YYSYMBOL_OP_ABAND = 45,                  /* OP_ABAND  */
  YYSYMBOL_OP_AXOR = 46,                   /* OP_AXOR  */
  YYSYMBOL_OP_INC = 47,                    /* OP_INC  */
  YYSYMBOL_OP_DEC = 48,                    /* OP_DEC  */
  YYSYMBOL_D_SEMICOLON = 49,               /* D_SEMICOLON  */
  YYSYMBOL_D_LPAREN = 50,                  /* D_LPAREN  */
  YYSYMBOL_D_RPAREN = 51,                  /* D_RPAREN  */
  YYSYMBOL_D_LBRACE = 52,                  /* D_LBRACE  */
  YYSYMBOL_D_RBRACE = 53,                  /* D_RBRACE  */
  YYSYMBOL_D_COLON = 54,                   /* D_COLON  */
  YYSYMBOL_D_COMMA = 55,                   /* D_COMMA  */
  YYSYMBOL_D_ARROW = 56,                   /* D_ARROW  */
  YYSYMBOL_CONTROL_IF = 57,                /* CONTROL_IF  */
  YYSYMBOL_CONTROL_ELSE = 58,              /* CONTROL_ELSE  */
  YYSYMBOL_CONTROL_WHILE = 59,             /* CONTROL_WHILE  */
  YYSYMBOL_CONTROL_FOR = 60,               /* CONTROL_FOR  */
  YYSYMBOL_CONTROL_SWITCH = 61,            /* CONTROL_SWITCH  */
  YYSYMBOL_CONTROL_CASE = 62,              /* CONTROL_CASE  */
  YYSYMBOL_CONTROL_DEFAULT = 63,           /* CONTROL_DEFAULT  */
  YYSYMBOL_CONTROL_DO = 64,                /* CONTROL_DO  */
  YYSYMBOL_CONTROL_RETURN = 65,            /* CONTROL_RETURN  */
  YYSYMBOL_CONTROL_BREAK = 66,             /* CONTROL_BREAK  */
  YYSYMBOL_CONTROL_CONTINUE = 67,          /* CONTROL_CONTINUE  */
  YYSYMBOL_MISC_FUNC = 68,                 /* MISC_FUNC  */
  YYSYMBOL_MISC_FROM = 69,                 /* MISC_FROM  */
  YYSYMBOL_MISC_VAR = 70,                  /* MISC_VAR  */
  YYSYMBOL_MISC_CONST = 71,                /* MISC_CONST  */
  YYSYMBOL_MISC_IMPORT = 72,               /* MISC_IMPORT  */
  YYSYMBOL_MISC_EXPORT = 73,               /* MISC_EXPORT  */
  YYSYMBOL_MISC_NATIVE = 74,               /* MISC_NATIVE  */
  YYSYMBOL_OP_UNARY_MINUS = 75,            /* OP_UNARY_MINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 76,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 77,                  /* $accept  */
  YYSYMBOL_program = 78,                   /* program  */
  YYSYMBOL_statements_list = 79,           /* statements_list  */
  YYSYMBOL_statement = 80,                 /* statement  */
  YYSYMBOL_if_stmt = 81,                   /* if_stmt  */
  YYSYMBOL_unwrapped_stmt = 82,            /* unwrapped_stmt  */
  YYSYMBOL_for_stmt = 83,                  /* for_stmt  */
  YYSYMBOL_while_stmt = 84,                /* while_stmt  */
  YYSYMBOL_break_stmt = 85,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 86,             /* continue_stmt  */
  YYSYMBOL_return_stmt = 87,               /* return_stmt  */
  YYSYMBOL_switch_stmt = 88,               /* switch_stmt  */
  YYSYMBOL_switch_body = 89,               /* switch_body  */
  YYSYMBOL_switch_case = 90,               /* switch_case  */
  YYSYMBOL_var_decl_stmt = 91,             /* var_decl_stmt  */
  YYSYMBOL_var_assign_stmt = 92,           /* var_assign_stmt  */
  YYSYMBOL_compoundable_operator = 93,     /* compoundable_operator  */
  YYSYMBOL_scope_stmt = 94,                /* scope_stmt  */
  YYSYMBOL_func_def = 95,                  /* func_def  */
  YYSYMBOL_func_arg = 96,                  /* func_arg  */
  YYSYMBOL_func_arg_list = 97,             /* func_arg_list  */
  YYSYMBOL_func_call = 98,                 /* func_call  */
  YYSYMBOL_func_param_list = 99,           /* func_param_list  */
  YYSYMBOL_func_param = 100,               /* func_param  */
  YYSYMBOL_expr = 101,                     /* expr  */
  YYSYMBOL_expr_casted_term = 102,         /* expr_casted_term  */
  YYSYMBOL_expr_term = 103,                /* expr_term  */
  YYSYMBOL_expr_value = 104,               /* expr_value  */
  YYSYMBOL_constant_value = 105,           /* constant_value  */
  YYSYMBOL_types_list = 106,               /* types_list  */
  YYSYMBOL_type_specifier = 107            /* type_specifier  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  89
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   638

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  113
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  227

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   125,   125,   134,   135,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,   149,   150,   151,   156,   158,
     163,   164,   167,   168,   169,   170,   174,   175,   179,   183,
     188,   189,   193,   199,   200,   204,   205,   211,   212,   213,
     214,   218,   219,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   237,   240,   246,   255,   265,   266,   270,
     271,   272,   277,   278,   282,   283,   287,   294,   295,   296,
     300,   301,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   340,   341,   342,   343,   344,   353,   354,   358,   359,
     360,   361,   362,   363
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "END", "V_STRING",
  "V_INTEGER", "V_COMPLEX", "V_REAL", "V_BOOLEAN", "ID", "TYPE_REAL",
  "TYPE_INT", "TYPE_STR", "TYPE_COMPLEX", "TYPE_BOOL", "TYPE_VOID",
  "OP_ASSIGN", "OP_PLUS", "OP_MINUS", "OP_MULT", "OP_DIV", "OP_MOD",
  "OP_LS", "OP_RS", "OP_BOR", "OP_BAND", "OP_XOR", "OP_OR", "OP_AND",
  "OP_NOT", "OP_INVERT", "OP_EQUAL", "OP_GREATER", "OP_LESS", "OP_GE",
  "OP_LE", "OP_NEQUAL", "OP_APLUS", "OP_AMINUS", "OP_AMULT", "OP_ADIV",
  "OP_AMOD", "OP_ARS", "OP_ALS", "OP_ABOR", "OP_ABAND", "OP_AXOR",
  "OP_INC", "OP_DEC", "D_SEMICOLON", "D_LPAREN", "D_RPAREN", "D_LBRACE",
  "D_RBRACE", "D_COLON", "D_COMMA", "D_ARROW", "CONTROL_IF",
  "CONTROL_ELSE", "CONTROL_WHILE", "CONTROL_FOR", "CONTROL_SWITCH",
  "CONTROL_CASE", "CONTROL_DEFAULT", "CONTROL_DO", "CONTROL_RETURN",
  "CONTROL_BREAK", "CONTROL_CONTINUE", "MISC_FUNC", "MISC_FROM",
  "MISC_VAR", "MISC_CONST", "MISC_IMPORT", "MISC_EXPORT", "MISC_NATIVE",
  "OP_UNARY_MINUS", "LOWER_THAN_ELSE", "$accept", "program",
  "statements_list", "statement", "if_stmt", "unwrapped_stmt", "for_stmt",
  "while_stmt", "break_stmt", "continue_stmt", "return_stmt",
  "switch_stmt", "switch_body", "switch_case", "var_decl_stmt",
  "var_assign_stmt", "compoundable_operator", "scope_stmt", "func_def",
  "func_arg", "func_arg_list", "func_call", "func_param_list",
  "func_param", "expr", "expr_casted_term", "expr_term", "expr_value",
  "constant_value", "types_list", "type_specifier", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-147)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     453,  -147,  -147,  -147,  -147,  -147,   175,   459,   459,   459,
     459,     1,    30,  -147,   521,   249,   -27,   -18,    -3,     0,
     453,   536,  -147,  -147,    47,    53,    57,    75,   181,  -147,
    -147,  -147,  -147,    24,    29,    40,  -147,    46,    68,  -147,
    -147,  -147,    74,  -147,   602,  -147,  -147,   536,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
       7,   536,   100,   536,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,    35,    63,  -147,   317,
     536,   536,    90,   536,    60,    23,    31,    -9,    11,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,   536,   536,  -147,
     459,   459,   459,   459,   459,   459,   459,   459,   459,   459,
     459,   459,   459,   459,   459,   459,    23,  -147,    73,  -147,
      23,    23,  -147,   459,  -147,    62,    65,   127,   103,    67,
     105,   144,   536,   250,   536,   250,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,   536,   602,   453,   453,   108,
      76,   536,   110,   536,   111,  -147,    91,    23,   151,    23,
     152,  -147,   114,  -147,   453,    13,   109,    78,    70,   250,
     113,   144,   536,   536,   453,  -147,   453,   122,  -147,    23,
     570,   536,   126,    14,  -147,   132,   166,   250,  -147,    23,
      23,  -147,  -147,   453,   142,    16,   453,  -147,  -147,  -147,
     264,    22,  -147,  -147,   453,   453,   453,  -147,   121,   250,
     453,  -147,   453,  -147,  -147,   385,  -147
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,   101,   102,   105,   103,   104,    91,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,    31,    28,    29,     0,     0,     0,     0,     0,     3,
      11,    12,    13,     0,     0,     0,    14,     0,     0,    10,
       9,    90,     0,    67,    71,    72,    89,     0,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    99,   100,
       0,     0,    91,     0,    94,    93,    95,    96,    97,    98,
     109,   108,   110,   111,   112,   113,     0,     0,    54,     0,
       0,     0,     0,     0,     0,    30,     0,     0,     0,     1,
       2,     4,    16,    15,     8,     6,     7,     0,     0,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    41,    63,     0,    64,
      66,    42,    92,     0,    53,     0,     0,     0,     0,     0,
       0,    61,     0,     0,     0,     0,    68,    69,    73,    74,
      88,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    86,    85,    87,    62,     0,    70,     0,     0,     0,
       0,     0,     0,     0,     0,    59,     0,    39,     0,    40,
       0,    65,    18,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,     0,     0,    20,    21,
       0,     0,     0,     0,    33,     0,    57,     0,    60,    37,
      38,    19,    23,     0,     0,     0,     0,    32,    34,    27,
       0,     0,   106,    25,     0,     0,    36,    58,     0,     0,
       0,    22,    35,    56,   107,     0,    55
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -147,  -147,   -14,   -20,  -147,    10,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,     4,   125,  -146,  -147,  -147,  -147,    27,
    -147,  -147,  -147,    48,   -12,    32,    81,    -4,    -1,  -147,
    -107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    27,    28,    29,    30,   187,    31,    32,    33,    34,
      35,    36,   193,   194,    37,    38,    61,    39,    40,   165,
     166,    41,   118,   119,    42,    43,    44,    45,    46,   211,
      77
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      84,    79,    76,    64,    65,    66,    67,   132,    91,    85,
      68,     1,     2,     3,     4,     5,    62,     1,     2,     3,
       4,     5,     6,    80,     7,     8,   168,   134,   170,   188,
       7,     8,    81,    97,    98,   116,     9,    10,   218,    69,
      97,    98,     9,    10,   188,   133,   219,    82,   120,   121,
      83,    76,    97,    98,    11,    12,    86,    14,   117,    91,
      11,    12,    87,    14,   186,   135,    88,   207,   125,   126,
     215,   129,   196,    92,   220,    89,   191,   192,    93,    97,
      98,   131,    97,    98,    97,    98,   122,    97,    98,    94,
     212,    97,    98,    97,    98,    95,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   224,   157,   123,   160,   158,    96,   162,   130,
     167,   195,   169,    99,   154,   175,    97,    98,   155,   136,
     137,     1,     2,     3,     4,     5,    62,   172,   173,   127,
     191,   192,   180,   120,     7,     8,   181,    58,    59,   176,
      60,   178,   161,   164,   185,   163,     9,    10,   190,   174,
      25,    26,   177,   189,   201,   179,   202,   182,   183,   197,
     199,   200,   184,   203,    11,    12,   159,    14,   189,   205,
     206,   209,   210,   213,    90,     1,     2,     3,     4,     5,
       6,    47,   216,   214,   221,   223,    91,   208,     7,     8,
     204,   222,    91,   171,   156,    91,   225,   128,   198,   217,
       9,    10,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,     0,    60,     0,     0,    11,    12,
      13,    14,     0,    15,     0,     0,     0,     0,    16,     0,
      17,    18,    19,     0,     0,    20,    21,    22,    23,    24,
       0,    25,    26,     1,     2,     3,     4,     5,     6,     0,
      70,    71,    72,    73,    74,    75,     7,     8,     1,     2,
       3,     4,     5,     0,     0,     0,     0,     0,     9,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,    12,    13,    14,
       0,    15,    78,     0,     0,     0,    16,     0,    17,    18,
      19,     0,     0,    20,    21,    22,    23,    24,     0,    25,
      26,     1,     2,     3,     4,     5,     6,     0,     0,     0,
       0,     0,     0,     0,     7,     8,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     9,    10,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    11,    12,    13,    14,     0,    15,
     124,     0,     0,     0,    16,     0,    17,    18,    19,     0,
       0,    20,    21,    22,    23,    24,     0,    25,    26,     1,
       2,     3,     4,     5,     6,     0,     0,     0,     0,     0,
       0,     0,     7,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     9,    10,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    11,    12,    13,    14,     0,    15,   226,     0,
       0,     0,    16,     0,    17,    18,    19,     0,     0,    20,
      21,    22,    23,    24,     0,    25,    26,     1,     2,     3,
       4,     5,     6,     1,     2,     3,     4,     5,    62,     0,
       7,     8,     0,     0,     0,     0,     7,     8,     0,     0,
       0,     0,     9,    10,     0,     0,     0,     0,     9,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      11,    12,    13,    14,     0,    15,    11,    12,     0,    63,
      16,     0,    17,    18,    19,     0,     0,    20,    21,    22,
      23,    24,     0,    25,    26,     1,     2,     3,     4,     5,
      62,    70,    71,    72,    73,    74,    75,     0,     7,     8,
       1,     2,     3,     4,     5,    62,     0,     0,     0,     0,
       9,    10,     0,     7,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,     0,    11,    12,
       0,    14,     0,     0,     1,     2,     3,     4,     5,     6,
       0,     0,     0,    11,    12,     0,    14,     7,     8,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
      10,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    11,    12,     0,
      14,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,     0,     0,   110,   111,   112,   113,   114,   115
};

static const yytype_int16 yycheck[] =
{
      20,    15,    14,     7,     8,     9,    10,    16,    28,    21,
       9,     4,     5,     6,     7,     8,     9,     4,     5,     6,
       7,     8,     9,    50,    17,    18,   133,    16,   135,   175,
      17,    18,    50,    17,    18,    47,    29,    30,    16,     9,
      17,    18,    29,    30,   190,    54,    24,    50,    60,    61,
      50,    63,    17,    18,    47,    48,     9,    50,    51,    79,
      47,    48,     9,    50,    51,    54,     9,    53,    80,    81,
      54,    83,   179,    49,    52,     0,    62,    63,    49,    17,
      18,    50,    17,    18,    17,    18,    51,    17,    18,    49,
     197,    17,    18,    17,    18,    49,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   219,    51,    51,   127,    51,    49,    51,    59,
     132,    51,   134,    49,    51,    49,    17,    18,    55,    97,
      98,     4,     5,     6,     7,     8,     9,   157,   158,    49,
      62,    63,    51,   155,    17,    18,    55,    47,    48,   161,
      50,   163,    49,     9,   174,    50,    29,    30,    49,    51,
      70,    71,    52,   175,   184,    54,   186,    16,    16,    56,
     182,   183,    58,    51,    47,    48,    49,    50,   190,   191,
      54,    49,    16,   203,     3,     4,     5,     6,     7,     8,
       9,    16,   206,    51,   214,    74,   216,   193,    17,    18,
     190,   215,   222,   155,   123,   225,   220,    82,   181,   210,
      29,    30,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    -1,    50,    -1,    -1,    47,    48,
      49,    50,    -1,    52,    -1,    -1,    -1,    -1,    57,    -1,
      59,    60,    61,    -1,    -1,    64,    65,    66,    67,    68,
      -1,    70,    71,     4,     5,     6,     7,     8,     9,    -1,
      10,    11,    12,    13,    14,    15,    17,    18,     4,     5,
       6,     7,     8,    -1,    -1,    -1,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    49,    50,
      -1,    52,    53,    -1,    -1,    -1,    57,    -1,    59,    60,
      61,    -1,    -1,    64,    65,    66,    67,    68,    -1,    70,
      71,     4,     5,     6,     7,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,
      53,    -1,    -1,    -1,    57,    -1,    59,    60,    61,    -1,
      -1,    64,    65,    66,    67,    68,    -1,    70,    71,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    48,    49,    50,    -1,    52,    53,    -1,
      -1,    -1,    57,    -1,    59,    60,    61,    -1,    -1,    64,
      65,    66,    67,    68,    -1,    70,    71,     4,     5,     6,
       7,     8,     9,     4,     5,     6,     7,     8,     9,    -1,
      17,    18,    -1,    -1,    -1,    -1,    17,    18,    -1,    -1,
      -1,    -1,    29,    30,    -1,    -1,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    49,    50,    -1,    52,    47,    48,    -1,    50,
      57,    -1,    59,    60,    61,    -1,    -1,    64,    65,    66,
      67,    68,    -1,    70,    71,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,    -1,    17,    18,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      29,    30,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    -1,    47,    48,
      -1,    50,    -1,    -1,     4,     5,     6,     7,     8,     9,
      -1,    -1,    -1,    47,    48,    -1,    50,    17,    18,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,
      50,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    31,    32,    33,    34,    35,    36
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    17,    18,    29,
      30,    47,    48,    49,    50,    52,    57,    59,    60,    61,
      64,    65,    66,    67,    68,    70,    71,    78,    79,    80,
      81,    83,    84,    85,    86,    87,    88,    91,    92,    94,
      95,    98,   101,   102,   103,   104,   105,    16,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      50,    93,     9,    50,   104,   104,   104,   104,     9,     9,
      10,    11,    12,    13,    14,    15,   101,   107,    53,    79,
      50,    50,    50,    50,    80,   101,     9,     9,     9,     0,
       3,    80,    49,    49,    49,    49,    49,    17,    18,    49,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      31,    32,    33,    34,    35,    36,   101,    51,    99,   100,
     101,   101,    51,    51,    53,   101,   101,    49,    91,   101,
      59,    50,    16,    54,    16,    54,   102,   102,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   104,    51,    55,   103,    51,    51,    49,
     101,    49,    51,    50,     9,    96,    97,   101,   107,   101,
     107,   100,    80,    80,    51,    49,   101,    52,   101,    54,
      51,    55,    16,    16,    58,    80,    51,    82,    92,   101,
      49,    62,    63,    89,    90,    51,   107,    56,    96,   101,
     101,    80,    80,    51,    82,   101,    54,    53,    90,    49,
      16,   106,   107,    80,    51,    54,    79,   105,    16,    24,
      52,    80,    79,    74,   107,    79,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    77,    78,    79,    79,    80,    80,    80,    80,    80,
      80,    80,    80,    80,    80,    80,    80,    80,    81,    81,
      82,    82,    83,    83,    83,    83,    84,    84,    85,    86,
      87,    87,    88,    89,    89,    90,    90,    91,    91,    91,
      91,    92,    92,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    94,    94,    95,    95,    96,    96,    97,
      97,    97,    98,    98,    99,    99,   100,   101,   101,   101,
     102,   102,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   105,   105,   105,   105,   105,   106,   106,   107,   107,
     107,   107,   107,   107
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     5,     7,
       1,     1,     9,     7,     6,     8,     5,     7,     1,     1,
       2,     1,     7,     1,     2,     4,     3,     6,     6,     4,
       4,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     2,    10,     9,     3,     5,     1,
       3,     0,     4,     3,     1,     3,     1,     1,     3,     3,
       4,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     3,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: statements_list END  */
#line 125 "parser.ypp"
                          {
        (yyval.executable) = new Cmm::Program::ProgramNode((yyvsp[-1].executable));
        root = dynamic_cast<Cmm::Program::ProgramNode*>((yyval.executable));
        YYACCEPT;
      }
#line 1450 "parser.tab.cpp"
    break;

  case 3: /* statements_list: statement  */
#line 134 "parser.ypp"
                                { (yyval.executable) = new Cmm::Program::StatementListNode(nullptr, (yyvsp[0].executable)); }
#line 1456 "parser.tab.cpp"
    break;

  case 4: /* statements_list: statements_list statement  */
#line 135 "parser.ypp"
                                { (yyval.executable) = new Cmm::Program::StatementListNode(dynamic_cast<Cmm::Program::StatementListNode*>((yyvsp[-1].executable)), (yyvsp[0].executable)); }
#line 1462 "parser.tab.cpp"
    break;

  case 5: /* statement: expr D_SEMICOLON  */
#line 139 "parser.ypp"
                                     { (yyval.executable) = new Cmm::Program::ExpressionStatementNode((yyvsp[-1].evaluable));}
#line 1468 "parser.tab.cpp"
    break;

  case 6: /* statement: var_decl_stmt D_SEMICOLON  */
#line 140 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1474 "parser.tab.cpp"
    break;

  case 7: /* statement: var_assign_stmt D_SEMICOLON  */
#line 141 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1480 "parser.tab.cpp"
    break;

  case 8: /* statement: return_stmt D_SEMICOLON  */
#line 142 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1486 "parser.tab.cpp"
    break;

  case 9: /* statement: func_def  */
#line 143 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1492 "parser.tab.cpp"
    break;

  case 10: /* statement: scope_stmt  */
#line 144 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1498 "parser.tab.cpp"
    break;

  case 11: /* statement: if_stmt  */
#line 145 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1504 "parser.tab.cpp"
    break;

  case 12: /* statement: for_stmt  */
#line 146 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1510 "parser.tab.cpp"
    break;

  case 13: /* statement: while_stmt  */
#line 147 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1516 "parser.tab.cpp"
    break;

  case 14: /* statement: switch_stmt  */
#line 148 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1522 "parser.tab.cpp"
    break;

  case 15: /* statement: continue_stmt D_SEMICOLON  */
#line 149 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1528 "parser.tab.cpp"
    break;

  case 16: /* statement: break_stmt D_SEMICOLON  */
#line 150 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1534 "parser.tab.cpp"
    break;

  case 17: /* statement: D_SEMICOLON  */
#line 151 "parser.ypp"
                                     { (yyval.executable) = nullptr; }
#line 1540 "parser.tab.cpp"
    break;

  case 18: /* if_stmt: CONTROL_IF D_LPAREN expr D_RPAREN statement  */
#line 157 "parser.ypp"
    { (yyval.executable) = new Cmm::Control::IFNode((yyvsp[-2].evaluable), (yyvsp[0].executable), nullptr); }
#line 1546 "parser.tab.cpp"
    break;

  case 19: /* if_stmt: CONTROL_IF D_LPAREN expr D_RPAREN statement CONTROL_ELSE statement  */
#line 159 "parser.ypp"
    { (yyval.executable) = new Cmm::Control::IFNode((yyvsp[-4].evaluable), (yyvsp[-2].executable), (yyvsp[0].executable)); }
#line 1552 "parser.tab.cpp"
    break;

  case 21: /* unwrapped_stmt: expr  */
#line 164 "parser.ypp"
                                     { (yyval.executable) = new Cmm::Program::ExpressionStatementNode((yyvsp[0].evaluable));}
#line 1558 "parser.tab.cpp"
    break;

  case 22: /* for_stmt: CONTROL_FOR D_LPAREN var_decl_stmt D_SEMICOLON expr D_SEMICOLON unwrapped_stmt D_RPAREN statement  */
#line 167 "parser.ypp"
                                                                                                      { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-4].evaluable), (yyvsp[-6].executable), (yyvsp[-2].executable), (yyvsp[0].executable)); }
#line 1564 "parser.tab.cpp"
    break;

  case 23: /* for_stmt: CONTROL_FOR D_LPAREN D_SEMICOLON expr D_SEMICOLON D_RPAREN statement  */
#line 168 "parser.ypp"
                                                                                                      { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-3].evaluable), nullptr, nullptr, (yyvsp[0].executable)); }
#line 1570 "parser.tab.cpp"
    break;

  case 24: /* for_stmt: CONTROL_FOR D_LPAREN D_SEMICOLON D_SEMICOLON D_RPAREN statement  */
#line 169 "parser.ypp"
                                                                                                      { (yyval.executable) = new Cmm::Control::ForNode(nullptr, nullptr, nullptr, (yyvsp[0].executable)); }
#line 1576 "parser.tab.cpp"
    break;

  case 25: /* for_stmt: CONTROL_FOR D_LPAREN D_SEMICOLON expr D_SEMICOLON unwrapped_stmt D_RPAREN statement  */
#line 170 "parser.ypp"
                                                                                                      { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-4].evaluable), nullptr, (yyvsp[-2].executable), (yyvsp[0].executable)); }
#line 1582 "parser.tab.cpp"
    break;

  case 26: /* while_stmt: CONTROL_WHILE D_LPAREN expr D_RPAREN statement  */
#line 174 "parser.ypp"
                                                                                 { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-2].evaluable), nullptr, nullptr, (yyvsp[0].executable)); }
#line 1588 "parser.tab.cpp"
    break;

  case 27: /* while_stmt: CONTROL_DO statement CONTROL_WHILE D_LPAREN expr D_RPAREN D_SEMICOLON  */
#line 175 "parser.ypp"
                                                                                 { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-2].evaluable), nullptr, nullptr, (yyvsp[-5].executable), true); }
#line 1594 "parser.tab.cpp"
    break;

  case 28: /* break_stmt: CONTROL_BREAK  */
#line 179 "parser.ypp"
                                                          { (yyval.executable) = new Cmm::Control::BreakStatementNode(); }
#line 1600 "parser.tab.cpp"
    break;

  case 29: /* continue_stmt: CONTROL_CONTINUE  */
#line 183 "parser.ypp"
                                                          { (yyval.executable) = new Cmm::Control::ContinueStatementNode(); }
#line 1606 "parser.tab.cpp"
    break;

  case 30: /* return_stmt: CONTROL_RETURN expr  */
#line 188 "parser.ypp"
                                                          { (yyval.executable) = new Cmm::Control::ReturnStatementNode((yyvsp[0].evaluable)); }
#line 1612 "parser.tab.cpp"
    break;

  case 31: /* return_stmt: CONTROL_RETURN  */
#line 189 "parser.ypp"
                                                          { (yyval.executable) = new Cmm::Control::ReturnStatementNode(nullptr); }
#line 1618 "parser.tab.cpp"
    break;

  case 32: /* switch_stmt: CONTROL_SWITCH D_LPAREN expr D_RPAREN D_LBRACE switch_body D_RBRACE  */
#line 193 "parser.ypp"
                                                                        {
      (yyval.executable) = new Cmm::Control::SwitchNode((yyvsp[-4].evaluable), (yyvsp[-1].sw_body_t));
    }
#line 1626 "parser.tab.cpp"
    break;

  case 33: /* switch_body: switch_case  */
#line 199 "parser.ypp"
                                                { (yyval.sw_body_t) = new Cmm::Control::SwitchBodyNode(nullptr, (yyvsp[0].sw_case_t)); }
#line 1632 "parser.tab.cpp"
    break;

  case 34: /* switch_body: switch_body switch_case  */
#line 200 "parser.ypp"
                                                { (yyval.sw_body_t) = new Cmm::Control::SwitchBodyNode((yyvsp[-1].sw_body_t), (yyvsp[0].sw_case_t)); }
#line 1638 "parser.tab.cpp"
    break;

  case 35: /* switch_case: CONTROL_CASE expr D_COLON statements_list  */
#line 204 "parser.ypp"
                                                { (yyval.sw_case_t) = new Cmm::Control::SwitchCaseNode((yyvsp[0].executable), (yyvsp[-2].evaluable)); }
#line 1644 "parser.tab.cpp"
    break;

  case 36: /* switch_case: CONTROL_DEFAULT D_COLON statements_list  */
#line 205 "parser.ypp"
                                                { (yyval.sw_case_t) = new Cmm::Control::SwitchCaseNode((yyvsp[0].executable), nullptr); }
#line 1650 "parser.tab.cpp"
    break;

  case 37: /* var_decl_stmt: MISC_VAR ID D_COLON type_specifier OP_ASSIGN expr  */
#line 211 "parser.ypp"
                                                        { (yyval.executable) = new Cmm::Variables::VariableDeclarationNode(false, *(yyvsp[-4].str), *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1656 "parser.tab.cpp"
    break;

  case 38: /* var_decl_stmt: MISC_CONST ID D_COLON type_specifier OP_ASSIGN expr  */
#line 212 "parser.ypp"
                                                        { (yyval.executable) = new Cmm::Variables::VariableDeclarationNode(true , *(yyvsp[-4].str), *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1662 "parser.tab.cpp"
    break;

  case 39: /* var_decl_stmt: MISC_VAR ID OP_ASSIGN expr  */
#line 213 "parser.ypp"
                                 { (yyval.executable) = new Cmm::Variables::InferredVariableDeclarationNode(false, *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1668 "parser.tab.cpp"
    break;

  case 40: /* var_decl_stmt: MISC_CONST ID OP_ASSIGN expr  */
#line 214 "parser.ypp"
                                 { (yyval.executable) = new Cmm::Variables::InferredVariableDeclarationNode(true , *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1674 "parser.tab.cpp"
    break;

  case 41: /* var_assign_stmt: ID OP_ASSIGN expr  */
#line 218 "parser.ypp"
                                                        { (yyval.executable) = new Cmm::Variables::VariableAssignmentNode(*(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1680 "parser.tab.cpp"
    break;

  case 42: /* var_assign_stmt: ID compoundable_operator expr  */
#line 219 "parser.ypp"
                                                        { (yyval.executable) = new Cmm::Variables::CompoundAssignmentNode(*(yyvsp[-2].str), *(yyvsp[-1].str), (yyvsp[0].evaluable)); }
#line 1686 "parser.tab.cpp"
    break;

  case 43: /* compoundable_operator: OP_APLUS  */
#line 223 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1692 "parser.tab.cpp"
    break;

  case 44: /* compoundable_operator: OP_AMINUS  */
#line 224 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1698 "parser.tab.cpp"
    break;

  case 45: /* compoundable_operator: OP_AMULT  */
#line 225 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1704 "parser.tab.cpp"
    break;

  case 46: /* compoundable_operator: OP_ADIV  */
#line 226 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1710 "parser.tab.cpp"
    break;

  case 47: /* compoundable_operator: OP_AMOD  */
#line 227 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1716 "parser.tab.cpp"
    break;

  case 48: /* compoundable_operator: OP_ARS  */
#line 228 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1722 "parser.tab.cpp"
    break;

  case 49: /* compoundable_operator: OP_ALS  */
#line 229 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1728 "parser.tab.cpp"
    break;

  case 50: /* compoundable_operator: OP_ABOR  */
#line 230 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1734 "parser.tab.cpp"
    break;

  case 51: /* compoundable_operator: OP_ABAND  */
#line 231 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1740 "parser.tab.cpp"
    break;

  case 52: /* compoundable_operator: OP_AXOR  */
#line 232 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1746 "parser.tab.cpp"
    break;

  case 53: /* scope_stmt: D_LBRACE statements_list D_RBRACE  */
#line 237 "parser.ypp"
                                      {
      (yyval.executable) = new Cmm::Program::ScopeNode((yyvsp[-1].executable));
    }
#line 1754 "parser.tab.cpp"
    break;

  case 54: /* scope_stmt: D_LBRACE D_RBRACE  */
#line 240 "parser.ypp"
                        {
      (yyval.executable) = new Cmm::Program::ScopeNode(nullptr); // empty scope
    }
#line 1762 "parser.tab.cpp"
    break;

  case 55: /* func_def: MISC_FUNC ID D_LPAREN func_arg_list D_RPAREN D_ARROW types_list D_LBRACE statements_list D_RBRACE  */
#line 246 "parser.ypp"
                                                                                                      { 
      (yyval.executable) = new Cmm::Functional::FunctionDeclarationNode(new Cmm::Functional::FunctionNode(
        dynamic_cast<Cmm::Functional::FunctionArgumentListNode*>((yyvsp[-6].node)),
        dynamic_cast<Cmm::Program::StatementListNode*>((yyvsp[-1].executable)),
        *(yyvsp[-8].str),
        (yyvsp[-3].tlist)
      ));
  }
#line 1775 "parser.tab.cpp"
    break;

  case 56: /* func_def: MISC_FUNC ID D_LPAREN func_arg_list D_RPAREN D_ARROW types_list OP_ASSIGN MISC_NATIVE  */
#line 255 "parser.ypp"
                                                                                          { 
      (yyval.executable) = new Cmm::Functional::NativeFunctionDeclarationNode(
        dynamic_cast<Cmm::Functional::FunctionArgumentListNode*>((yyvsp[-5].node)),
        (yyvsp[-2].tlist),
        *(yyvsp[-7].str)
      );
   }
#line 1787 "parser.tab.cpp"
    break;

  case 57: /* func_arg: ID D_COLON type_specifier  */
#line 265 "parser.ypp"
                                                         { (yyval.node) = new Cmm::Functional::FunctionArgumentNode(*(yyvsp[-2].str), *(yyvsp[0].str)); }
#line 1793 "parser.tab.cpp"
    break;

  case 58: /* func_arg: ID D_COLON type_specifier OP_ASSIGN constant_value  */
#line 266 "parser.ypp"
                                                         { (yyval.node) = new Cmm::Functional::FunctionArgumentNode(*(yyvsp[-4].str), *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1799 "parser.tab.cpp"
    break;

  case 59: /* func_arg_list: func_arg  */
#line 270 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionArgumentListNode(nullptr, dynamic_cast<Cmm::Functional::FunctionArgumentNode*>((yyvsp[0].node))); }
#line 1805 "parser.tab.cpp"
    break;

  case 60: /* func_arg_list: func_arg_list D_COMMA func_arg  */
#line 271 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionArgumentListNode(dynamic_cast<Cmm::Functional::FunctionArgumentListNode*>((yyvsp[-2].node)), dynamic_cast<Cmm::Functional::FunctionArgumentNode*>((yyvsp[0].node))); }
#line 1811 "parser.tab.cpp"
    break;

  case 61: /* func_arg_list: %empty  */
#line 272 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionArgumentListNode(nullptr, nullptr); }
#line 1817 "parser.tab.cpp"
    break;

  case 62: /* func_call: ID D_LPAREN func_param_list D_RPAREN  */
#line 277 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Functional::FunctionCallNode(*(yyvsp[-3].str), dynamic_cast<Cmm::Functional::FunctionParamListNode*>((yyvsp[-1].node))); }
#line 1823 "parser.tab.cpp"
    break;

  case 63: /* func_call: ID D_LPAREN D_RPAREN  */
#line 278 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Functional::FunctionCallNode(*(yyvsp[-2].str), nullptr); }
#line 1829 "parser.tab.cpp"
    break;

  case 64: /* func_param_list: func_param  */
#line 282 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionParamListNode(nullptr, (yyvsp[0].evaluable)); }
#line 1835 "parser.tab.cpp"
    break;

  case 65: /* func_param_list: func_param_list D_COMMA func_param  */
#line 283 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionParamListNode(dynamic_cast<Cmm::Functional::FunctionParamListNode*>((yyvsp[-2].node)), (yyvsp[0].evaluable)); }
#line 1841 "parser.tab.cpp"
    break;

  case 66: /* func_param: expr  */
#line 287 "parser.ypp"
                                               { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1847 "parser.tab.cpp"
    break;

  case 67: /* expr: expr_casted_term  */
#line 294 "parser.ypp"
                                          { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1853 "parser.tab.cpp"
    break;

  case 68: /* expr: expr OP_PLUS expr_casted_term  */
#line 295 "parser.ypp"
                                          { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1859 "parser.tab.cpp"
    break;

  case 69: /* expr: expr OP_MINUS expr_casted_term  */
#line 296 "parser.ypp"
                                          { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1865 "parser.tab.cpp"
    break;

  case 70: /* expr_casted_term: D_LPAREN type_specifier D_RPAREN expr_term  */
#line 300 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Expressions::CastNode((yyvsp[0].evaluable), *(yyvsp[-2].str)); }
#line 1871 "parser.tab.cpp"
    break;

  case 71: /* expr_casted_term: expr_term  */
#line 301 "parser.ypp"
                                               { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1877 "parser.tab.cpp"
    break;

  case 72: /* expr_term: expr_value  */
#line 305 "parser.ypp"
                                                { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1883 "parser.tab.cpp"
    break;

  case 73: /* expr_term: expr_term OP_MULT expr_value  */
#line 306 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1889 "parser.tab.cpp"
    break;

  case 74: /* expr_term: expr_term OP_DIV expr_value  */
#line 307 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1895 "parser.tab.cpp"
    break;

  case 75: /* expr_term: expr_term OP_LS expr_value  */
#line 308 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1901 "parser.tab.cpp"
    break;

  case 76: /* expr_term: expr_term OP_RS expr_value  */
#line 309 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1907 "parser.tab.cpp"
    break;

  case 77: /* expr_term: expr_term OP_BOR expr_value  */
#line 310 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1913 "parser.tab.cpp"
    break;

  case 78: /* expr_term: expr_term OP_BAND expr_value  */
#line 311 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1919 "parser.tab.cpp"
    break;

  case 79: /* expr_term: expr_term OP_XOR expr_value  */
#line 312 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1925 "parser.tab.cpp"
    break;

  case 80: /* expr_term: expr_term OP_OR expr_value  */
#line 313 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1931 "parser.tab.cpp"
    break;

  case 81: /* expr_term: expr_term OP_AND expr_value  */
#line 314 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1937 "parser.tab.cpp"
    break;

  case 82: /* expr_term: expr_term OP_EQUAL expr_value  */
#line 315 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1943 "parser.tab.cpp"
    break;

  case 83: /* expr_term: expr_term OP_GREATER expr_value  */
#line 316 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1949 "parser.tab.cpp"
    break;

  case 84: /* expr_term: expr_term OP_LESS expr_value  */
#line 317 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1955 "parser.tab.cpp"
    break;

  case 85: /* expr_term: expr_term OP_LE expr_value  */
#line 318 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1961 "parser.tab.cpp"
    break;

  case 86: /* expr_term: expr_term OP_GE expr_value  */
#line 319 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1967 "parser.tab.cpp"
    break;

  case 87: /* expr_term: expr_term OP_NEQUAL expr_value  */
#line 320 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1973 "parser.tab.cpp"
    break;

  case 88: /* expr_term: expr_term OP_MOD expr_value  */
#line 321 "parser.ypp"
                                                { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1979 "parser.tab.cpp"
    break;

  case 89: /* expr_value: constant_value  */
#line 325 "parser.ypp"
                                             { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1985 "parser.tab.cpp"
    break;

  case 90: /* expr_value: func_call  */
#line 326 "parser.ypp"
                                             { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1991 "parser.tab.cpp"
    break;

  case 91: /* expr_value: ID  */
#line 327 "parser.ypp"
                                             { (yyval.evaluable) = new Cmm::Expressions::VariableNode(*(yyvsp[0].str)); }
#line 1997 "parser.tab.cpp"
    break;

  case 92: /* expr_value: D_LPAREN expr D_RPAREN  */
#line 328 "parser.ypp"
                                             { (yyval.evaluable) = (yyvsp[-1].evaluable); }
#line 2003 "parser.tab.cpp"
    break;

  case 93: /* expr_value: OP_MINUS expr_value  */
#line 329 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Expressions::NegatedNode((yyvsp[0].evaluable)); }
#line 2009 "parser.tab.cpp"
    break;

  case 94: /* expr_value: OP_PLUS expr_value  */
#line 330 "parser.ypp"
                                               { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 2015 "parser.tab.cpp"
    break;

  case 95: /* expr_value: OP_NOT expr_value  */
#line 331 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Expressions::NotNode((yyvsp[0].evaluable)); }
#line 2021 "parser.tab.cpp"
    break;

  case 96: /* expr_value: OP_INVERT expr_value  */
#line 332 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Expressions::InvertNode((yyvsp[0].evaluable)); }
#line 2027 "parser.tab.cpp"
    break;

  case 97: /* expr_value: OP_INC ID  */
#line 333 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Variables::PreIncNode(*(yyvsp[0].str), *(yyvsp[-1].str)); }
#line 2033 "parser.tab.cpp"
    break;

  case 98: /* expr_value: OP_DEC ID  */
#line 334 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Variables::PreIncNode(*(yyvsp[0].str), *(yyvsp[-1].str)); }
#line 2039 "parser.tab.cpp"
    break;

  case 99: /* expr_value: ID OP_INC  */
#line 335 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Variables::PostIncNode(*(yyvsp[-1].str), *(yyvsp[0].str)); }
#line 2045 "parser.tab.cpp"
    break;

  case 100: /* expr_value: ID OP_DEC  */
#line 336 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Variables::PostIncNode(*(yyvsp[-1].str), *(yyvsp[0].str)); }
#line 2051 "parser.tab.cpp"
    break;

  case 101: /* constant_value: V_STRING  */
#line 340 "parser.ypp"
                { (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::String(*(yyvsp[0].str))); }
#line 2057 "parser.tab.cpp"
    break;

  case 102: /* constant_value: V_INTEGER  */
#line 341 "parser.ypp"
                { (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::Integer((*(yyvsp[0].str)).c_str())); }
#line 2063 "parser.tab.cpp"
    break;

  case 103: /* constant_value: V_REAL  */
#line 342 "parser.ypp"
                { (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::Real((*(yyvsp[0].str)).c_str())); }
#line 2069 "parser.tab.cpp"
    break;

  case 104: /* constant_value: V_BOOLEAN  */
#line 343 "parser.ypp"
                { (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::Bool(*((yyvsp[0].str)) == "true")); }
#line 2075 "parser.tab.cpp"
    break;

  case 105: /* constant_value: V_COMPLEX  */
#line 344 "parser.ypp"
                { 
    (yyvsp[0].str)->pop_back(); // remove the "i"
    (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::Complex(Cmm::Real(0.0), Cmm::Real((yyvsp[0].str)->c_str()))); 
  }
#line 2084 "parser.tab.cpp"
    break;

  case 106: /* types_list: type_specifier  */
#line 353 "parser.ypp"
                                        { (yyval.tlist) = new Cmm::Typing::TypeListNode(nullptr, *(yyvsp[0].str)); }
#line 2090 "parser.tab.cpp"
    break;

  case 107: /* types_list: types_list OP_BOR type_specifier  */
#line 354 "parser.ypp"
                                        { (yyval.tlist) = new Cmm::Typing::TypeListNode((yyvsp[-2].tlist), *(yyvsp[0].str)); }
#line 2096 "parser.tab.cpp"
    break;

  case 108: /* type_specifier: TYPE_INT  */
#line 358 "parser.ypp"
                  { (yyval.str) = new std::string("int"); }
#line 2102 "parser.tab.cpp"
    break;

  case 109: /* type_specifier: TYPE_REAL  */
#line 359 "parser.ypp"
                  { (yyval.str) = new std::string("real"); }
#line 2108 "parser.tab.cpp"
    break;

  case 110: /* type_specifier: TYPE_STR  */
#line 360 "parser.ypp"
                  { (yyval.str) = new std::string("str"); }
#line 2114 "parser.tab.cpp"
    break;

  case 111: /* type_specifier: TYPE_COMPLEX  */
#line 361 "parser.ypp"
                  { (yyval.str) = new std::string("complex"); }
#line 2120 "parser.tab.cpp"
    break;

  case 112: /* type_specifier: TYPE_BOOL  */
#line 362 "parser.ypp"
                  { (yyval.str) = new std::string("bool"); }
#line 2126 "parser.tab.cpp"
    break;

  case 113: /* type_specifier: TYPE_VOID  */
#line 363 "parser.ypp"
                  { (yyval.str) = new std::string("void"); }
#line 2132 "parser.tab.cpp"
    break;


#line 2136 "parser.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 366 "parser.ypp"
