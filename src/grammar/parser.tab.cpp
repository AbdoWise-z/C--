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

#include "Store.h"
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
#include "../nodes/Macros.hpp"

#include "parser.tab.hpp"

// Declare yylex for Bison
extern int yylex();

extern char* yytext;
extern int yydebug;

extern int yyvlineno;
extern int yylineno;

void yyerror(const char* s);
extern Cmm::Program::ProgramNode* root;


#line 106 "parser.tab.cpp"

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
  YYSYMBOL_MISC_VAR = 69,                  /* MISC_VAR  */
  YYSYMBOL_MISC_CONST = 70,                /* MISC_CONST  */
  YYSYMBOL_MISC_NATIVE = 71,               /* MISC_NATIVE  */
  YYSYMBOL_MARCO_LINE = 72,                /* MARCO_LINE  */
  YYSYMBOL_MARCO_CLEAR = 73,               /* MARCO_CLEAR  */
  YYSYMBOL_OP_UNARY_MINUS = 74,            /* OP_UNARY_MINUS  */
  YYSYMBOL_LOWER_THAN_ELSE = 75,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 76,                  /* $accept  */
  YYSYMBOL_program = 77,                   /* program  */
  YYSYMBOL_statements_list = 78,           /* statements_list  */
  YYSYMBOL_statement = 79,                 /* statement  */
  YYSYMBOL_if_stmt = 80,                   /* if_stmt  */
  YYSYMBOL_unwrapped_stmt = 81,            /* unwrapped_stmt  */
  YYSYMBOL_for_stmt = 82,                  /* for_stmt  */
  YYSYMBOL_while_stmt = 83,                /* while_stmt  */
  YYSYMBOL_break_stmt = 84,                /* break_stmt  */
  YYSYMBOL_continue_stmt = 85,             /* continue_stmt  */
  YYSYMBOL_return_stmt = 86,               /* return_stmt  */
  YYSYMBOL_switch_stmt = 87,               /* switch_stmt  */
  YYSYMBOL_switch_body = 88,               /* switch_body  */
  YYSYMBOL_switch_case = 89,               /* switch_case  */
  YYSYMBOL_var_decl_stmt = 90,             /* var_decl_stmt  */
  YYSYMBOL_var_assign_stmt = 91,           /* var_assign_stmt  */
  YYSYMBOL_compoundable_operator = 92,     /* compoundable_operator  */
  YYSYMBOL_scope_stmt = 93,                /* scope_stmt  */
  YYSYMBOL_func_def = 94,                  /* func_def  */
  YYSYMBOL_func_arg = 95,                  /* func_arg  */
  YYSYMBOL_func_arg_list = 96,             /* func_arg_list  */
  YYSYMBOL_func_call = 97,                 /* func_call  */
  YYSYMBOL_func_param_list = 98,           /* func_param_list  */
  YYSYMBOL_func_param = 99,                /* func_param  */
  YYSYMBOL_expr = 100,                     /* expr  */
  YYSYMBOL_expr_casted_term = 101,         /* expr_casted_term  */
  YYSYMBOL_expr_term_l0 = 102,             /* expr_term_l0  */
  YYSYMBOL_expr_term_l1 = 103,             /* expr_term_l1  */
  YYSYMBOL_expr_term_l2 = 104,             /* expr_term_l2  */
  YYSYMBOL_expr_term_l3 = 105,             /* expr_term_l3  */
  YYSYMBOL_expr_term_l4 = 106,             /* expr_term_l4  */
  YYSYMBOL_expr_term_l5 = 107,             /* expr_term_l5  */
  YYSYMBOL_constant_value = 108,           /* constant_value  */
  YYSYMBOL_types_list = 109,               /* types_list  */
  YYSYMBOL_type_specifier = 110,           /* type_specifier  */
  YYSYMBOL_line_rule = 111                 /* line_rule  */
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
#define YYFINAL  97
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   609

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  235

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   330


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
      75
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   109,   109,   118,   119,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   137,   138,
     144,   146,   151,   152,   155,   156,   157,   158,   162,   163,
     167,   171,   176,   177,   181,   187,   188,   192,   193,   199,
     200,   201,   202,   206,   207,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   225,   228,   233,   241,   252,
     253,   257,   258,   259,   264,   265,   269,   270,   274,   281,
     285,   286,   290,   291,   292,   296,   297,   298,   299,   300,
     301,   302,   306,   307,   308,   313,   314,   315,   316,   320,
     321,   322,   323,   324,   325,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   345,   346,   347,
     348,   349,   358,   359,   363,   364,   365,   366,   367,   368,
     375
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
  "CONTROL_BREAK", "CONTROL_CONTINUE", "MISC_FUNC", "MISC_VAR",
  "MISC_CONST", "MISC_NATIVE", "MARCO_LINE", "MARCO_CLEAR",
  "OP_UNARY_MINUS", "LOWER_THAN_ELSE", "$accept", "program",
  "statements_list", "statement", "if_stmt", "unwrapped_stmt", "for_stmt",
  "while_stmt", "break_stmt", "continue_stmt", "return_stmt",
  "switch_stmt", "switch_body", "switch_case", "var_decl_stmt",
  "var_assign_stmt", "compoundable_operator", "scope_stmt", "func_def",
  "func_arg", "func_arg_list", "func_call", "func_param_list",
  "func_param", "expr", "expr_casted_term", "expr_term_l0", "expr_term_l1",
  "expr_term_l2", "expr_term_l3", "expr_term_l4", "expr_term_l5",
  "constant_value", "types_list", "type_specifier", "line_rule", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-146)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     386,  -146,  -146,  -146,  -146,  -146,    64,   392,   392,   392,
     392,     3,    32,  -146,   510,   176,   -32,    -7,    17,    23,
     386,   525,  -146,  -146,    84,   104,   118,   124,  -146,   149,
      22,  -146,  -146,  -146,  -146,   109,   111,   112,  -146,   120,
     121,  -146,  -146,  -146,   126,  -146,     9,   100,    30,   101,
     130,  -146,  -146,  -146,   525,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,  -146,   456,   525,    50,
     525,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,    99,   122,  -146,   246,   525,   525,   -35,
     525,   117,  -146,   138,    -8,    -5,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,  -146,  -146,  -146,   392,   392,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,  -146,  -146,    -1,  -146,  -146,  -146,
    -146,   392,  -146,   139,   141,    15,   128,   150,   153,   180,
     525,   127,   525,   127,   100,   100,    30,    30,    30,    30,
      30,    30,   101,   101,   130,   130,   130,  -146,  -146,  -146,
    -146,  -146,  -146,   525,     9,   386,   386,   156,   159,   525,
     160,   525,   157,  -146,     6,  -146,   199,  -146,   200,  -146,
     161,  -146,   386,   462,   168,    81,   167,   127,   164,   180,
     525,   525,   386,  -146,   386,   170,  -146,  -146,   559,   525,
     173,   -46,  -146,   181,   206,   127,  -146,  -146,  -146,  -146,
    -146,   386,   183,   177,   386,  -146,  -146,  -146,   191,    44,
    -146,  -146,   386,   386,   386,  -146,   185,   127,   386,  -146,
     386,  -146,  -146,   316,  -146
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,   107,   108,   111,   109,   110,    97,     0,     0,     0,
       0,     0,     0,    17,     0,     0,     0,     0,     0,     0,
       0,    33,    30,    31,     0,     0,     0,     0,    19,     0,
       0,     3,    11,    12,    13,     0,     0,     0,    14,     0,
       0,    10,     9,    96,     0,    69,    71,    74,    75,    82,
      85,    89,    95,    18,     0,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,   105,   106,     0,     0,    97,
       0,   100,    99,   101,   102,   103,   104,   115,   114,   116,
     117,   118,   119,     0,     0,    56,     0,     0,     0,     0,
       0,     0,    32,     0,     0,     0,   120,     1,     2,     4,
      16,    15,     8,     6,     7,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    43,    65,     0,    66,    68,    44,
      98,     0,    55,     0,     0,     0,     0,     0,     0,    63,
       0,     0,     0,     0,    72,    73,    76,    77,    78,    80,
      79,    81,    83,    84,    86,    87,    88,    90,    91,    92,
      93,    94,    64,     0,    70,     0,     0,     0,     0,     0,
       0,     0,     0,    61,     0,    41,     0,    42,     0,    67,
      20,    28,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,     0,     0,    22,    23,     0,     0,
       0,     0,    35,     0,    59,     0,    62,    39,    40,    21,
      25,     0,     0,     0,     0,    34,    36,    29,     0,     0,
     112,    27,     0,     0,    38,    60,     0,     0,     0,    24,
      37,    58,   113,     0,    57
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -146,  -146,   -14,   -20,  -146,    34,  -146,  -146,  -146,  -146,
    -146,  -146,  -146,    37,   158,  -145,  -146,  -146,  -146,    68,
    -146,  -146,  -146,    76,   -12,  -146,   129,   -22,    55,    33,
       8,    -4,    40,  -146,  -128,  -146
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    29,    30,    31,    32,   195,    33,    34,    35,    36,
      37,    38,   201,   202,    39,    40,    68,    41,    42,   173,
     174,    43,   126,   127,    44,    45,    46,    47,    48,    49,
      50,    51,    52,   219,    84,    53
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      91,    86,    83,    71,    72,    73,    74,   215,   140,    92,
      99,   142,    75,   176,   135,   178,   199,   200,    87,     1,
       2,     3,     4,     5,    69,    98,     1,     2,     3,     4,
       5,     6,     7,     8,    25,    26,   106,   107,   196,     7,
       8,    76,   124,    88,     9,    10,   141,   114,   115,   143,
     162,     9,    10,   196,   163,   128,   129,   188,    83,   204,
     226,   189,    11,    12,   167,    14,    99,    89,   227,    11,
      12,    13,    14,    90,    15,   133,   134,   220,   137,    16,
      54,    17,    18,    19,   144,   145,    20,    21,    22,    23,
      24,    25,    26,    93,    27,    28,   228,    65,    66,   232,
      67,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    94,    67,   157,   158,   159,   160,   161,
     116,   117,   118,   168,   154,   155,   156,    95,   175,    96,
     177,   108,   109,   110,   111,   112,   113,    77,    78,    79,
      80,    81,    82,   199,   200,   180,   181,   152,   153,    97,
     130,   128,   119,   120,   121,   122,   123,   184,   100,   186,
     101,   102,   193,   146,   147,   148,   149,   150,   151,   103,
     104,   197,   209,   131,   210,   105,   138,   169,   207,   208,
       1,     2,     3,     4,     5,     6,   197,   213,   139,   172,
     165,   221,   166,     7,     8,     1,     2,     3,     4,     5,
     224,   170,   229,   171,    99,     9,    10,   182,   183,   230,
      99,   187,   185,    99,   233,   190,   191,   198,   203,   192,
     205,   211,   218,    11,    12,    13,    14,   214,    15,    85,
     217,   223,   212,    16,   222,    17,    18,    19,   216,   179,
      20,    21,    22,    23,    24,    25,    26,   136,    27,    28,
       1,     2,     3,     4,     5,     6,   231,   206,   225,     0,
     164,     0,     0,     7,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    12,    13,    14,     0,    15,   132,
       0,     0,     0,    16,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,    27,    28,
       1,     2,     3,     4,     5,     6,     0,     0,     0,     0,
       0,     0,     0,     7,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     9,    10,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    12,    13,    14,     0,    15,   234,
       0,     0,     0,    16,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,    27,    28,
       1,     2,     3,     4,     5,     6,     1,     2,     3,     4,
       5,    69,     0,     7,     8,     0,     0,     0,     0,     7,
       8,     0,     0,     0,     0,     9,    10,     0,     0,     0,
       0,     9,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    12,    13,    14,     0,    15,    11,
      12,     0,    70,    16,     0,    17,    18,    19,     0,     0,
      20,    21,    22,    23,    24,    25,    26,     0,    27,    28,
       1,     2,     3,     4,     5,    69,     1,     2,     3,     4,
       5,     6,     0,     7,     8,     0,     0,     0,     0,     7,
       8,     0,     0,     0,     0,     9,    10,     0,     0,     0,
       0,     9,    10,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,    12,     0,    14,   125,     0,    11,
      12,     0,    14,   194,     1,     2,     3,     4,     5,    69,
      77,    78,    79,    80,    81,    82,     0,     7,     8,     1,
       2,     3,     4,     5,    69,     0,     0,     0,     0,     9,
      10,     0,     7,     8,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     9,    10,     0,    11,    12,     0,
      14,     0,     0,     1,     2,     3,     4,     5,     6,     0,
       0,     0,    11,    12,     0,    14,     7,     8,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     9,    10,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,    12,     0,    14
};

static const yytype_int16 yycheck[] =
{
      20,    15,    14,     7,     8,     9,    10,    53,    16,    21,
      30,    16,     9,   141,    49,   143,    62,    63,    50,     4,
       5,     6,     7,     8,     9,     3,     4,     5,     6,     7,
       8,     9,    17,    18,    69,    70,    27,    28,   183,    17,
      18,     9,    54,    50,    29,    30,    54,    17,    18,    54,
      51,    29,    30,   198,    55,    67,    68,    51,    70,   187,
      16,    55,    47,    48,    49,    50,    86,    50,    24,    47,
      48,    49,    50,    50,    52,    87,    88,   205,    90,    57,
      16,    59,    60,    61,   106,   107,    64,    65,    66,    67,
      68,    69,    70,     9,    72,    73,    52,    47,    48,   227,
      50,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,     9,    50,   119,   120,   121,   122,   123,
      19,    20,    21,   135,   116,   117,   118,     9,   140,     5,
     142,    31,    32,    33,    34,    35,    36,    10,    11,    12,
      13,    14,    15,    62,    63,   165,   166,   114,   115,     0,
      51,   163,    22,    23,    24,    25,    26,   169,    49,   171,
      49,    49,   182,   108,   109,   110,   111,   112,   113,    49,
      49,   183,   192,    51,   194,    49,    59,    49,   190,   191,
       4,     5,     6,     7,     8,     9,   198,   199,    50,     9,
      51,   211,    51,    17,    18,     4,     5,     6,     7,     8,
     214,    51,   222,    50,   224,    29,    30,    51,    49,   223,
     230,    54,    52,   233,   228,    16,    16,    49,    51,    58,
      56,    51,    16,    47,    48,    49,    50,    54,    52,    53,
      49,    54,   198,    57,    51,    59,    60,    61,   201,   163,
      64,    65,    66,    67,    68,    69,    70,    89,    72,    73,
       4,     5,     6,     7,     8,     9,    71,   189,   218,    -1,
     131,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,    53,
      -1,    -1,    -1,    57,    -1,    59,    60,    61,    -1,    -1,
      64,    65,    66,    67,    68,    69,    70,    -1,    72,    73,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,    53,
      -1,    -1,    -1,    57,    -1,    59,    60,    61,    -1,    -1,
      64,    65,    66,    67,    68,    69,    70,    -1,    72,    73,
       4,     5,     6,     7,     8,     9,     4,     5,     6,     7,
       8,     9,    -1,    17,    18,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    49,    50,    -1,    52,    47,
      48,    -1,    50,    57,    -1,    59,    60,    61,    -1,    -1,
      64,    65,    66,    67,    68,    69,    70,    -1,    72,    73,
       4,     5,     6,     7,     8,     9,     4,     5,     6,     7,
       8,     9,    -1,    17,    18,    -1,    -1,    -1,    -1,    17,
      18,    -1,    -1,    -1,    -1,    29,    30,    -1,    -1,    -1,
      -1,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    48,    -1,    50,    51,    -1,    47,
      48,    -1,    50,    51,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    -1,    17,    18,     4,
       5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,    29,
      30,    -1,    17,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    29,    30,    -1,    47,    48,    -1,
      50,    -1,    -1,     4,     5,     6,     7,     8,     9,    -1,
      -1,    -1,    47,    48,    -1,    50,    17,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    -1,    50
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,     6,     7,     8,     9,    17,    18,    29,
      30,    47,    48,    49,    50,    52,    57,    59,    60,    61,
      64,    65,    66,    67,    68,    69,    70,    72,    73,    77,
      78,    79,    80,    82,    83,    84,    85,    86,    87,    90,
      91,    93,    94,    97,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   111,    16,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    50,    92,     9,
      50,   107,   107,   107,   107,     9,     9,    10,    11,    12,
      13,    14,    15,   100,   110,    53,    78,    50,    50,    50,
      50,    79,   100,     9,     9,     9,     5,     0,     3,    79,
      49,    49,    49,    49,    49,    49,    27,    28,    31,    32,
      33,    34,    35,    36,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,   100,    51,    98,    99,   100,   100,
      51,    51,    53,   100,   100,    49,    90,   100,    59,    50,
      16,    54,    16,    54,   103,   103,   104,   104,   104,   104,
     104,   104,   105,   105,   106,   106,   106,   107,   107,   107,
     107,   107,    51,    55,   102,    51,    51,    49,   100,    49,
      51,    50,     9,    95,    96,   100,   110,   100,   110,    99,
      79,    79,    51,    49,   100,    52,   100,    54,    51,    55,
      16,    16,    58,    79,    51,    81,    91,   100,    49,    62,
      63,    88,    89,    51,   110,    56,    95,   100,   100,    79,
      79,    51,    81,   100,    54,    53,    89,    49,    16,   109,
     110,    79,    51,    54,    78,   108,    16,    24,    52,    79,
      78,    71,   110,    78,    53
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    76,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      80,    80,    81,    81,    82,    82,    82,    82,    83,    83,
      84,    85,    86,    86,    87,    88,    88,    89,    89,    90,
      90,    90,    90,    91,    91,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    96,    97,    97,    98,    98,    99,   100,
     101,   101,   102,   102,   102,   103,   103,   103,   103,   103,
     103,   103,   104,   104,   104,   105,   105,   105,   105,   106,
     106,   106,   106,   106,   106,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   108,   108,   108,
     108,   108,   109,   109,   110,   110,   110,   110,   110,   110,
     111
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     2,     2,     1,     1,     1,
       5,     7,     1,     1,     9,     7,     6,     8,     5,     7,
       1,     1,     2,     1,     7,     1,     2,     4,     3,     6,
       6,     4,     4,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     2,    10,     9,     3,
       5,     1,     3,     0,     4,     3,     1,     3,     1,     1,
       4,     1,     3,     3,     1,     1,     3,     3,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     1,
       3,     3,     3,     3,     3,     1,     1,     1,     3,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       2
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
#line 109 "parser.ypp"
                          {
        (yyval.executable) = new Cmm::Program::ProgramNode((yyvsp[-1].executable));
        Cmm::Store::root = dynamic_cast<Cmm::Program::ProgramNode*>((yyval.executable));
        YYACCEPT;
      }
#line 1454 "parser.tab.cpp"
    break;

  case 3: /* statements_list: statement  */
#line 118 "parser.ypp"
                                { (yyval.executable) = new Cmm::Program::StatementListNode(nullptr, (yyvsp[0].executable)); }
#line 1460 "parser.tab.cpp"
    break;

  case 4: /* statements_list: statements_list statement  */
#line 119 "parser.ypp"
                                { (yyval.executable) = new Cmm::Program::StatementListNode(dynamic_cast<Cmm::Program::StatementListNode*>((yyvsp[-1].executable)), (yyvsp[0].executable)); }
#line 1466 "parser.tab.cpp"
    break;

  case 5: /* statement: expr D_SEMICOLON  */
#line 123 "parser.ypp"
                                     { (yyval.executable) = new Cmm::Program::ExpressionStatementNode((yyvsp[-1].evaluable));}
#line 1472 "parser.tab.cpp"
    break;

  case 6: /* statement: var_decl_stmt D_SEMICOLON  */
#line 124 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1478 "parser.tab.cpp"
    break;

  case 7: /* statement: var_assign_stmt D_SEMICOLON  */
#line 125 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1484 "parser.tab.cpp"
    break;

  case 8: /* statement: return_stmt D_SEMICOLON  */
#line 126 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1490 "parser.tab.cpp"
    break;

  case 9: /* statement: func_def  */
#line 127 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1496 "parser.tab.cpp"
    break;

  case 10: /* statement: scope_stmt  */
#line 128 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1502 "parser.tab.cpp"
    break;

  case 11: /* statement: if_stmt  */
#line 129 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1508 "parser.tab.cpp"
    break;

  case 12: /* statement: for_stmt  */
#line 130 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1514 "parser.tab.cpp"
    break;

  case 13: /* statement: while_stmt  */
#line 131 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1520 "parser.tab.cpp"
    break;

  case 14: /* statement: switch_stmt  */
#line 132 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[0].executable); }
#line 1526 "parser.tab.cpp"
    break;

  case 15: /* statement: continue_stmt D_SEMICOLON  */
#line 133 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1532 "parser.tab.cpp"
    break;

  case 16: /* statement: break_stmt D_SEMICOLON  */
#line 134 "parser.ypp"
                                     { (yyval.executable) = (yyvsp[-1].executable); }
#line 1538 "parser.tab.cpp"
    break;

  case 17: /* statement: D_SEMICOLON  */
#line 135 "parser.ypp"
                                     { (yyval.executable) = nullptr; }
#line 1544 "parser.tab.cpp"
    break;

  case 18: /* statement: line_rule  */
#line 137 "parser.ypp"
                                     { (yyval.executable) = nullptr; }
#line 1550 "parser.tab.cpp"
    break;

  case 19: /* statement: MARCO_CLEAR  */
#line 138 "parser.ypp"
                                     { (yyval.executable) = new Cmm::Macros::ClearMacro(); }
#line 1556 "parser.tab.cpp"
    break;

  case 20: /* if_stmt: CONTROL_IF D_LPAREN expr D_RPAREN statement  */
#line 145 "parser.ypp"
    { (yyval.executable) = new Cmm::Control::IFNode((yyvsp[-2].evaluable), (yyvsp[0].executable), nullptr); }
#line 1562 "parser.tab.cpp"
    break;

  case 21: /* if_stmt: CONTROL_IF D_LPAREN expr D_RPAREN statement CONTROL_ELSE statement  */
#line 147 "parser.ypp"
    { (yyval.executable) = new Cmm::Control::IFNode((yyvsp[-4].evaluable), (yyvsp[-2].executable), (yyvsp[0].executable)); }
#line 1568 "parser.tab.cpp"
    break;

  case 23: /* unwrapped_stmt: expr  */
#line 152 "parser.ypp"
                                     { (yyval.executable) = new Cmm::Program::ExpressionStatementNode((yyvsp[0].evaluable));}
#line 1574 "parser.tab.cpp"
    break;

  case 24: /* for_stmt: CONTROL_FOR D_LPAREN var_decl_stmt D_SEMICOLON expr D_SEMICOLON unwrapped_stmt D_RPAREN statement  */
#line 155 "parser.ypp"
                                                                                                      { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-4].evaluable), (yyvsp[-6].executable), (yyvsp[-2].executable), (yyvsp[0].executable)); }
#line 1580 "parser.tab.cpp"
    break;

  case 25: /* for_stmt: CONTROL_FOR D_LPAREN D_SEMICOLON expr D_SEMICOLON D_RPAREN statement  */
#line 156 "parser.ypp"
                                                                                                      { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-3].evaluable), nullptr, nullptr, (yyvsp[0].executable)); }
#line 1586 "parser.tab.cpp"
    break;

  case 26: /* for_stmt: CONTROL_FOR D_LPAREN D_SEMICOLON D_SEMICOLON D_RPAREN statement  */
#line 157 "parser.ypp"
                                                                                                      { (yyval.executable) = new Cmm::Control::ForNode(nullptr, nullptr, nullptr, (yyvsp[0].executable)); }
#line 1592 "parser.tab.cpp"
    break;

  case 27: /* for_stmt: CONTROL_FOR D_LPAREN D_SEMICOLON expr D_SEMICOLON unwrapped_stmt D_RPAREN statement  */
#line 158 "parser.ypp"
                                                                                                      { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-4].evaluable), nullptr, (yyvsp[-2].executable), (yyvsp[0].executable)); }
#line 1598 "parser.tab.cpp"
    break;

  case 28: /* while_stmt: CONTROL_WHILE D_LPAREN expr D_RPAREN statement  */
#line 162 "parser.ypp"
                                                                                 { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-2].evaluable), nullptr, nullptr, (yyvsp[0].executable)); }
#line 1604 "parser.tab.cpp"
    break;

  case 29: /* while_stmt: CONTROL_DO statement CONTROL_WHILE D_LPAREN expr D_RPAREN D_SEMICOLON  */
#line 163 "parser.ypp"
                                                                                 { (yyval.executable) = new Cmm::Control::ForNode((yyvsp[-2].evaluable), nullptr, nullptr, (yyvsp[-5].executable), true); }
#line 1610 "parser.tab.cpp"
    break;

  case 30: /* break_stmt: CONTROL_BREAK  */
#line 167 "parser.ypp"
                                                          { (yyval.executable) = new Cmm::Control::BreakStatementNode(); }
#line 1616 "parser.tab.cpp"
    break;

  case 31: /* continue_stmt: CONTROL_CONTINUE  */
#line 171 "parser.ypp"
                                                          { (yyval.executable) = new Cmm::Control::ContinueStatementNode(); }
#line 1622 "parser.tab.cpp"
    break;

  case 32: /* return_stmt: CONTROL_RETURN expr  */
#line 176 "parser.ypp"
                                                          { (yyval.executable) = new Cmm::Control::ReturnStatementNode((yyvsp[0].evaluable)); }
#line 1628 "parser.tab.cpp"
    break;

  case 33: /* return_stmt: CONTROL_RETURN  */
#line 177 "parser.ypp"
                                                          { (yyval.executable) = new Cmm::Control::ReturnStatementNode(nullptr); }
#line 1634 "parser.tab.cpp"
    break;

  case 34: /* switch_stmt: CONTROL_SWITCH D_LPAREN expr D_RPAREN D_LBRACE switch_body D_RBRACE  */
#line 181 "parser.ypp"
                                                                        {
      (yyval.executable) = new Cmm::Control::SwitchNode((yyvsp[-4].evaluable), (yyvsp[-1].sw_body_t));
    }
#line 1642 "parser.tab.cpp"
    break;

  case 35: /* switch_body: switch_case  */
#line 187 "parser.ypp"
                                                { (yyval.sw_body_t) = new Cmm::Control::SwitchBodyNode(nullptr, (yyvsp[0].sw_case_t)); }
#line 1648 "parser.tab.cpp"
    break;

  case 36: /* switch_body: switch_body switch_case  */
#line 188 "parser.ypp"
                                                { (yyval.sw_body_t) = new Cmm::Control::SwitchBodyNode((yyvsp[-1].sw_body_t), (yyvsp[0].sw_case_t)); }
#line 1654 "parser.tab.cpp"
    break;

  case 37: /* switch_case: CONTROL_CASE expr D_COLON statements_list  */
#line 192 "parser.ypp"
                                                { (yyval.sw_case_t) = new Cmm::Control::SwitchCaseNode((yyvsp[0].executable), (yyvsp[-2].evaluable)); }
#line 1660 "parser.tab.cpp"
    break;

  case 38: /* switch_case: CONTROL_DEFAULT D_COLON statements_list  */
#line 193 "parser.ypp"
                                                { (yyval.sw_case_t) = new Cmm::Control::SwitchCaseNode((yyvsp[0].executable), nullptr); }
#line 1666 "parser.tab.cpp"
    break;

  case 39: /* var_decl_stmt: MISC_VAR ID D_COLON type_specifier OP_ASSIGN expr  */
#line 199 "parser.ypp"
                                                        { (yyval.executable) = new Cmm::Variables::VariableDeclarationNode(false, *(yyvsp[-4].str), *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1672 "parser.tab.cpp"
    break;

  case 40: /* var_decl_stmt: MISC_CONST ID D_COLON type_specifier OP_ASSIGN expr  */
#line 200 "parser.ypp"
                                                        { (yyval.executable) = new Cmm::Variables::VariableDeclarationNode(true , *(yyvsp[-4].str), *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1678 "parser.tab.cpp"
    break;

  case 41: /* var_decl_stmt: MISC_VAR ID OP_ASSIGN expr  */
#line 201 "parser.ypp"
                                 { (yyval.executable) = new Cmm::Variables::InferredVariableDeclarationNode(false, *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1684 "parser.tab.cpp"
    break;

  case 42: /* var_decl_stmt: MISC_CONST ID OP_ASSIGN expr  */
#line 202 "parser.ypp"
                                 { (yyval.executable) = new Cmm::Variables::InferredVariableDeclarationNode(true , *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1690 "parser.tab.cpp"
    break;

  case 43: /* var_assign_stmt: ID OP_ASSIGN expr  */
#line 206 "parser.ypp"
                                                        { (yyval.executable) = new Cmm::Variables::VariableAssignmentNode(*(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1696 "parser.tab.cpp"
    break;

  case 44: /* var_assign_stmt: ID compoundable_operator expr  */
#line 207 "parser.ypp"
                                                        { (yyval.executable) = new Cmm::Variables::CompoundAssignmentNode(*(yyvsp[-2].str), *(yyvsp[-1].str), (yyvsp[0].evaluable)); }
#line 1702 "parser.tab.cpp"
    break;

  case 45: /* compoundable_operator: OP_APLUS  */
#line 211 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1708 "parser.tab.cpp"
    break;

  case 46: /* compoundable_operator: OP_AMINUS  */
#line 212 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1714 "parser.tab.cpp"
    break;

  case 47: /* compoundable_operator: OP_AMULT  */
#line 213 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1720 "parser.tab.cpp"
    break;

  case 48: /* compoundable_operator: OP_ADIV  */
#line 214 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1726 "parser.tab.cpp"
    break;

  case 49: /* compoundable_operator: OP_AMOD  */
#line 215 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1732 "parser.tab.cpp"
    break;

  case 50: /* compoundable_operator: OP_ARS  */
#line 216 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1738 "parser.tab.cpp"
    break;

  case 51: /* compoundable_operator: OP_ALS  */
#line 217 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1744 "parser.tab.cpp"
    break;

  case 52: /* compoundable_operator: OP_ABOR  */
#line 218 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1750 "parser.tab.cpp"
    break;

  case 53: /* compoundable_operator: OP_ABAND  */
#line 219 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1756 "parser.tab.cpp"
    break;

  case 54: /* compoundable_operator: OP_AXOR  */
#line 220 "parser.ypp"
              { (yyvsp[0].str)->pop_back(); (yyval.str) = (yyvsp[0].str); }
#line 1762 "parser.tab.cpp"
    break;

  case 55: /* scope_stmt: D_LBRACE statements_list D_RBRACE  */
#line 225 "parser.ypp"
                                      {
      (yyval.executable) = new Cmm::Program::ScopeNode((yyvsp[-1].executable));
    }
#line 1770 "parser.tab.cpp"
    break;

  case 56: /* scope_stmt: D_LBRACE D_RBRACE  */
#line 228 "parser.ypp"
                        {
      (yyval.executable) = new Cmm::Program::ScopeNode(nullptr); // empty scope
    }
#line 1778 "parser.tab.cpp"
    break;

  case 57: /* func_def: MISC_FUNC ID D_LPAREN func_arg_list D_RPAREN D_ARROW types_list D_LBRACE statements_list D_RBRACE  */
#line 233 "parser.ypp"
                                                                                                      {
      (yyval.executable) = new Cmm::Functional::FunctionDeclarationNode(
        dynamic_cast<Cmm::Functional::FunctionArgumentListNode*>((yyvsp[-6].node)),
        dynamic_cast<Cmm::Program::StatementListNode*>((yyvsp[-1].executable)),
        *(yyvsp[-8].str),
        (yyvsp[-3].tlist)
      );
  }
#line 1791 "parser.tab.cpp"
    break;

  case 58: /* func_def: MISC_FUNC ID D_LPAREN func_arg_list D_RPAREN D_ARROW types_list OP_ASSIGN MISC_NATIVE  */
#line 241 "parser.ypp"
                                                                                          {
      (yyval.executable) = new Cmm::Functional::FunctionDeclarationNode(
        dynamic_cast<Cmm::Functional::FunctionArgumentListNode*>((yyvsp[-5].node)),
        nullptr,
        *(yyvsp[-7].str),
        (yyvsp[-2].tlist)
      );
   }
#line 1804 "parser.tab.cpp"
    break;

  case 59: /* func_arg: ID D_COLON type_specifier  */
#line 252 "parser.ypp"
                                                         { (yyval.node) = new Cmm::Functional::FunctionArgumentNode(*(yyvsp[-2].str), *(yyvsp[0].str)); }
#line 1810 "parser.tab.cpp"
    break;

  case 60: /* func_arg: ID D_COLON type_specifier OP_ASSIGN constant_value  */
#line 253 "parser.ypp"
                                                         { (yyval.node) = new Cmm::Functional::FunctionArgumentNode(*(yyvsp[-4].str), *(yyvsp[-2].str), (yyvsp[0].evaluable)); }
#line 1816 "parser.tab.cpp"
    break;

  case 61: /* func_arg_list: func_arg  */
#line 257 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionArgumentListNode(nullptr, dynamic_cast<Cmm::Functional::FunctionArgumentNode*>((yyvsp[0].node))); }
#line 1822 "parser.tab.cpp"
    break;

  case 62: /* func_arg_list: func_arg_list D_COMMA func_arg  */
#line 258 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionArgumentListNode(dynamic_cast<Cmm::Functional::FunctionArgumentListNode*>((yyvsp[-2].node)), dynamic_cast<Cmm::Functional::FunctionArgumentNode*>((yyvsp[0].node))); }
#line 1828 "parser.tab.cpp"
    break;

  case 63: /* func_arg_list: %empty  */
#line 259 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionArgumentListNode(nullptr, nullptr); }
#line 1834 "parser.tab.cpp"
    break;

  case 64: /* func_call: ID D_LPAREN func_param_list D_RPAREN  */
#line 264 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Functional::FunctionCallNode(*(yyvsp[-3].str), dynamic_cast<Cmm::Functional::FunctionParamListNode*>((yyvsp[-1].node))); }
#line 1840 "parser.tab.cpp"
    break;

  case 65: /* func_call: ID D_LPAREN D_RPAREN  */
#line 265 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Functional::FunctionCallNode(*(yyvsp[-2].str), nullptr); }
#line 1846 "parser.tab.cpp"
    break;

  case 66: /* func_param_list: func_param  */
#line 269 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionParamListNode(nullptr, (yyvsp[0].evaluable)); }
#line 1852 "parser.tab.cpp"
    break;

  case 67: /* func_param_list: func_param_list D_COMMA func_param  */
#line 270 "parser.ypp"
                                               { (yyval.node) = new Cmm::Functional::FunctionParamListNode(dynamic_cast<Cmm::Functional::FunctionParamListNode*>((yyvsp[-2].node)), (yyvsp[0].evaluable)); }
#line 1858 "parser.tab.cpp"
    break;

  case 68: /* func_param: expr  */
#line 274 "parser.ypp"
                                               { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1864 "parser.tab.cpp"
    break;

  case 69: /* expr: expr_casted_term  */
#line 281 "parser.ypp"
                                                  { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1870 "parser.tab.cpp"
    break;

  case 70: /* expr_casted_term: D_LPAREN type_specifier D_RPAREN expr_term_l0  */
#line 285 "parser.ypp"
                                                  { (yyval.evaluable) = new Cmm::Expressions::CastNode((yyvsp[0].evaluable), *(yyvsp[-2].str)); }
#line 1876 "parser.tab.cpp"
    break;

  case 71: /* expr_casted_term: expr_term_l0  */
#line 286 "parser.ypp"
                                                  { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1882 "parser.tab.cpp"
    break;

  case 72: /* expr_term_l0: expr_term_l0 OP_OR expr_term_l1  */
#line 290 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1888 "parser.tab.cpp"
    break;

  case 73: /* expr_term_l0: expr_term_l0 OP_AND expr_term_l1  */
#line 291 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1894 "parser.tab.cpp"
    break;

  case 76: /* expr_term_l1: expr_term_l1 OP_EQUAL expr_term_l2  */
#line 297 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1900 "parser.tab.cpp"
    break;

  case 77: /* expr_term_l1: expr_term_l1 OP_GREATER expr_term_l2  */
#line 298 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1906 "parser.tab.cpp"
    break;

  case 78: /* expr_term_l1: expr_term_l1 OP_LESS expr_term_l2  */
#line 299 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1912 "parser.tab.cpp"
    break;

  case 79: /* expr_term_l1: expr_term_l1 OP_LE expr_term_l2  */
#line 300 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1918 "parser.tab.cpp"
    break;

  case 80: /* expr_term_l1: expr_term_l1 OP_GE expr_term_l2  */
#line 301 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1924 "parser.tab.cpp"
    break;

  case 81: /* expr_term_l1: expr_term_l1 OP_NEQUAL expr_term_l2  */
#line 302 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1930 "parser.tab.cpp"
    break;

  case 83: /* expr_term_l2: expr_term_l2 OP_PLUS expr_term_l3  */
#line 307 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1936 "parser.tab.cpp"
    break;

  case 84: /* expr_term_l2: expr_term_l2 OP_MINUS expr_term_l3  */
#line 308 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1942 "parser.tab.cpp"
    break;

  case 86: /* expr_term_l3: expr_term_l3 OP_MULT expr_term_l4  */
#line 314 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1948 "parser.tab.cpp"
    break;

  case 87: /* expr_term_l3: expr_term_l3 OP_DIV expr_term_l4  */
#line 315 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1954 "parser.tab.cpp"
    break;

  case 88: /* expr_term_l3: expr_term_l3 OP_MOD expr_term_l4  */
#line 316 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1960 "parser.tab.cpp"
    break;

  case 90: /* expr_term_l4: expr_term_l4 OP_LS expr_term_l5  */
#line 321 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1966 "parser.tab.cpp"
    break;

  case 91: /* expr_term_l4: expr_term_l4 OP_RS expr_term_l5  */
#line 322 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1972 "parser.tab.cpp"
    break;

  case 92: /* expr_term_l4: expr_term_l4 OP_BOR expr_term_l5  */
#line 323 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1978 "parser.tab.cpp"
    break;

  case 93: /* expr_term_l4: expr_term_l4 OP_BAND expr_term_l5  */
#line 324 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1984 "parser.tab.cpp"
    break;

  case 94: /* expr_term_l4: expr_term_l4 OP_XOR expr_term_l5  */
#line 325 "parser.ypp"
                                                     { (yyval.evaluable) = new Cmm::Expressions::TermNode((yyvsp[-2].evaluable), (yyvsp[0].evaluable), *(yyvsp[-1].str)); }
#line 1990 "parser.tab.cpp"
    break;

  case 95: /* expr_term_l5: constant_value  */
#line 330 "parser.ypp"
                                                 { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 1996 "parser.tab.cpp"
    break;

  case 96: /* expr_term_l5: func_call  */
#line 331 "parser.ypp"
                                                 { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 2002 "parser.tab.cpp"
    break;

  case 97: /* expr_term_l5: ID  */
#line 332 "parser.ypp"
                                                 { (yyval.evaluable) = new Cmm::Expressions::VariableNode(*(yyvsp[0].str)); }
#line 2008 "parser.tab.cpp"
    break;

  case 98: /* expr_term_l5: D_LPAREN expr D_RPAREN  */
#line 333 "parser.ypp"
                                                 { (yyval.evaluable) = (yyvsp[-1].evaluable); }
#line 2014 "parser.tab.cpp"
    break;

  case 99: /* expr_term_l5: OP_MINUS expr_term_l5  */
#line 334 "parser.ypp"
                                                 { (yyval.evaluable) = new Cmm::Expressions::NegatedNode((yyvsp[0].evaluable)); }
#line 2020 "parser.tab.cpp"
    break;

  case 100: /* expr_term_l5: OP_PLUS expr_term_l5  */
#line 335 "parser.ypp"
                                                 { (yyval.evaluable) = (yyvsp[0].evaluable); }
#line 2026 "parser.tab.cpp"
    break;

  case 101: /* expr_term_l5: OP_NOT expr_term_l5  */
#line 336 "parser.ypp"
                                                 { (yyval.evaluable) = new Cmm::Expressions::NotNode((yyvsp[0].evaluable)); }
#line 2032 "parser.tab.cpp"
    break;

  case 102: /* expr_term_l5: OP_INVERT expr_term_l5  */
#line 337 "parser.ypp"
                                                 { (yyval.evaluable) = new Cmm::Expressions::InvertNode((yyvsp[0].evaluable)); }
#line 2038 "parser.tab.cpp"
    break;

  case 103: /* expr_term_l5: OP_INC ID  */
#line 338 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Variables::PreIncNode(*(yyvsp[0].str), *(yyvsp[-1].str)); }
#line 2044 "parser.tab.cpp"
    break;

  case 104: /* expr_term_l5: OP_DEC ID  */
#line 339 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Variables::PreIncNode(*(yyvsp[0].str), *(yyvsp[-1].str)); }
#line 2050 "parser.tab.cpp"
    break;

  case 105: /* expr_term_l5: ID OP_INC  */
#line 340 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Variables::PostIncNode(*(yyvsp[-1].str), *(yyvsp[0].str)); }
#line 2056 "parser.tab.cpp"
    break;

  case 106: /* expr_term_l5: ID OP_DEC  */
#line 341 "parser.ypp"
                                               { (yyval.evaluable) = new Cmm::Variables::PostIncNode(*(yyvsp[-1].str), *(yyvsp[0].str)); }
#line 2062 "parser.tab.cpp"
    break;

  case 107: /* constant_value: V_STRING  */
#line 345 "parser.ypp"
                { (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::String(*(yyvsp[0].str))); }
#line 2068 "parser.tab.cpp"
    break;

  case 108: /* constant_value: V_INTEGER  */
#line 346 "parser.ypp"
                { (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::Integer((*(yyvsp[0].str)).c_str())); }
#line 2074 "parser.tab.cpp"
    break;

  case 109: /* constant_value: V_REAL  */
#line 347 "parser.ypp"
                { (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::Real((*(yyvsp[0].str)).c_str())); }
#line 2080 "parser.tab.cpp"
    break;

  case 110: /* constant_value: V_BOOLEAN  */
#line 348 "parser.ypp"
                { (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::Bool(*((yyvsp[0].str)) == "true")); }
#line 2086 "parser.tab.cpp"
    break;

  case 111: /* constant_value: V_COMPLEX  */
#line 349 "parser.ypp"
                { 
    (yyvsp[0].str)->pop_back(); // remove the "i"
    (yyval.evaluable) = new Cmm::Expressions::ConstantValueNode(Cmm::Complex(Cmm::Real(0.0), Cmm::Real((yyvsp[0].str)->c_str()))); 
  }
#line 2095 "parser.tab.cpp"
    break;

  case 112: /* types_list: type_specifier  */
#line 358 "parser.ypp"
                                        { (yyval.tlist) = new Cmm::Typing::TypeListNode(nullptr, *(yyvsp[0].str)); }
#line 2101 "parser.tab.cpp"
    break;

  case 113: /* types_list: types_list OP_BOR type_specifier  */
#line 359 "parser.ypp"
                                        { (yyval.tlist) = new Cmm::Typing::TypeListNode((yyvsp[-2].tlist), *(yyvsp[0].str)); }
#line 2107 "parser.tab.cpp"
    break;

  case 114: /* type_specifier: TYPE_INT  */
#line 363 "parser.ypp"
                  { (yyval.str) = new std::string("int"); }
#line 2113 "parser.tab.cpp"
    break;

  case 115: /* type_specifier: TYPE_REAL  */
#line 364 "parser.ypp"
                  { (yyval.str) = new std::string("real"); }
#line 2119 "parser.tab.cpp"
    break;

  case 116: /* type_specifier: TYPE_STR  */
#line 365 "parser.ypp"
                  { (yyval.str) = new std::string("str"); }
#line 2125 "parser.tab.cpp"
    break;

  case 117: /* type_specifier: TYPE_COMPLEX  */
#line 366 "parser.ypp"
                  { (yyval.str) = new std::string("complex"); }
#line 2131 "parser.tab.cpp"
    break;

  case 118: /* type_specifier: TYPE_BOOL  */
#line 367 "parser.ypp"
                  { (yyval.str) = new std::string("bool"); }
#line 2137 "parser.tab.cpp"
    break;

  case 119: /* type_specifier: TYPE_VOID  */
#line 368 "parser.ypp"
                  { (yyval.str) = new std::string("void"); }
#line 2143 "parser.tab.cpp"
    break;

  case 120: /* line_rule: MARCO_LINE V_INTEGER  */
#line 375 "parser.ypp"
                         {
        yyvlineno = std::stoi(*(yyvsp[0].str));
    }
#line 2151 "parser.tab.cpp"
    break;


#line 2155 "parser.tab.cpp"

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

#line 378 "parser.ypp"


void yyerror(const char* s) {
  std::cout  << "[Error] " << yyvlineno << " " << s
              << " (unexpected token: '" << yytext << "')" << std::endl;

  // if (!Cmm::Cfg::allowErrors) {
  //   YYABORT;
  // }
}
