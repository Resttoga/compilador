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
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE *yyin;
void yyerror(const char *s);
int yylex();

/* Constants*/
#define MAX_VAR 100
#define MAX_FUNC 50
#define MAX_PARAMS 10
#define MAX_STACK 100


struct Variable {
    char name[100];
    int type; 
    union {
        int ival;
        char strval[100];
    } value;
};


struct Function {
    char name[100];
    char param_names[MAX_PARAMS][100];
    int param_count;
    int (*func_body)(int *params);
};


struct Variable variables[MAX_VAR];
int var_count = 0;

struct Function functions[MAX_FUNC];
int func_count = 0;

int return_stack[MAX_STACK];
int execution_stack[MAX_STACK];
int stack_top = -1;

/* functions */

void some_predefined_function(int params[]) {
    printf("Ejecutando función con parámetros: ");
    for (int i = 0; i < MAX_PARAMS && params[i] != 0; i++) {
        printf("%d ", params[i]);
    }
    printf("\n");
}


int is_variable_declared(char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return 1;
        }
    }
    return 0;
}

int get_variable_value(char *name, int *type, char *strval) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            *type = variables[i].type;
            if (*type == 0) {
                return variables[i].value.ival;
            } else if (*type == 1) {
                strcpy(strval, variables[i].value.strval);
                return 0;
            }
        }
    }
    return -1;
}

void set_variable_value(char *name, int type, int ival, char *strval) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].type = type;
            if (type == 0) {
                variables[i].value.ival = ival;
            } else if (type == 1) {
                strcpy(variables[i].value.strval, strval);
            }
            return;
        }
    }
    strcpy(variables[var_count].name, name);
    variables[var_count].type = type;
    if (type == 0) {
        variables[var_count].value.ival = ival;
    } else if (type == 1) {
        strcpy(variables[var_count].value.strval, strval);
    }
    var_count++;
}


void push_return_value(int value) {
    if (stack_top < MAX_STACK - 1) {
        return_stack[++stack_top] = value;
    } else {
        yyerror("Error: Desbordamiento de pila de retorno.");
        exit(1);
    }
}

int pop_return_value() {
    if (stack_top >= 0) {
        return return_stack[stack_top--];
    } else {
        yyerror("Error: Pila de retorno vacía.");
        exit(1);
    }
}

struct Function *get_function(char *name) {
    for (int i = 0; i < func_count; i++) {
        if (strcmp(functions[i].name, name) == 0) {
            return &functions[i];
        }
    }
    return NULL;
}

void add_function(char *name, char param_names[MAX_PARAMS][100], int param_count, int (*func_body)(int *params)) {
    strcpy(functions[func_count].name, name);
    functions[func_count].param_count = param_count;
    for (int i = 0; i < param_count; i++) {
        strcpy(functions[func_count].param_names[i], param_names[i]);
        set_variable_value(param_names[i], 0, 0, NULL);
    }
    functions[func_count].func_body = func_body;
    func_count++;
}

/*stack*/

void push_execution_context(int value) {
    if (stack_top < MAX_STACK - 1) {
        execution_stack[++stack_top] = value;
    } else {
        yyerror("Error: Desbordamiento de pila de ejecución.");
        exit(1);
    }
}

int pop_execution_context() {
    if (stack_top >= 0) {
        return execution_stack[stack_top--];
    } else {
        yyerror("Error: Pila de ejecución vacía.");
        exit(1);
    }
}

int get_current_execution_context() {
    if (stack_top >= 0) {
        return execution_stack[stack_top];
    }
    return 1;
}


#line 240 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_TEXTO = 5,                      /* TEXTO  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_ELIF = 8,                       /* ELIF  */
  YYSYMBOL_LPAR = 9,                       /* LPAR  */
  YYSYMBOL_RPAR = 10,                      /* RPAR  */
  YYSYMBOL_LBRAC = 11,                     /* LBRAC  */
  YYSYMBOL_RBRAC = 12,                     /* RBRAC  */
  YYSYMBOL_IGUAL = 13,                     /* IGUAL  */
  YYSYMBOL_SUMA = 14,                      /* SUMA  */
  YYSYMBOL_RESTA = 15,                     /* RESTA  */
  YYSYMBOL_MULTIPLICACION = 16,            /* MULTIPLICACION  */
  YYSYMBOL_DIVISION = 17,                  /* DIVISION  */
  YYSYMBOL_GREATER = 18,                   /* GREATER  */
  YYSYMBOL_LESSER = 19,                    /* LESSER  */
  YYSYMBOL_GTEQ = 20,                      /* GTEQ  */
  YYSYMBOL_LSEQ = 21,                      /* LSEQ  */
  YYSYMBOL_EQ = 22,                        /* EQ  */
  YYSYMBOL_FOR = 23,                       /* FOR  */
  YYSYMBOL_SEMICOLON = 24,                 /* SEMICOLON  */
  YYSYMBOL_WHILE = 25,                     /* WHILE  */
  YYSYMBOL_PLUS = 26,                      /* PLUS  */
  YYSYMBOL_CALL = 27,                      /* CALL  */
  YYSYMBOL_RETURN = 28,                    /* RETURN  */
  YYSYMBOL_FUNCTION = 29,                  /* FUNCTION  */
  YYSYMBOL_COMA = 30,                      /* COMA  */
  YYSYMBOL_IMPRIMIR = 31,                  /* IMPRIMIR  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_PROGRAM = 33,                   /* PROGRAM  */
  YYSYMBOL_EXPRESSION = 34,                /* EXPRESSION  */
  YYSYMBOL_ASSIGNMENT = 35,                /* ASSIGNMENT  */
  YYSYMBOL_OPERATION = 36,                 /* OPERATION  */
  YYSYMBOL_LOGIC = 37,                     /* LOGIC  */
  YYSYMBOL_CONDITIONAL = 38,               /* CONDITIONAL  */
  YYSYMBOL_39_1 = 39,                      /* $@1  */
  YYSYMBOL_ELSEIF = 40,                    /* ELSEIF  */
  YYSYMBOL_41_2 = 41,                      /* $@2  */
  YYSYMBOL_THEN = 42,                      /* THEN  */
  YYSYMBOL_43_3 = 43,                      /* $@3  */
  YYSYMBOL_inCOND = 44,                    /* inCOND  */
  YYSYMBOL_LOOP = 45,                      /* LOOP  */
  YYSYMBOL_FOR_INC = 46,                   /* FOR_INC  */
  YYSYMBOL_FUNCTION_DECLARATION = 47,      /* FUNCTION_DECLARATION  */
  YYSYMBOL_PARAM_LIST = 48,                /* PARAM_LIST  */
  YYSYMBOL_FUNCTION_BODY = 49,             /* FUNCTION_BODY  */
  YYSYMBOL_FUNCTION_CALL = 50,             /* FUNCTION_CALL  */
  YYSYMBOL_PARAMS = 51                     /* PARAMS  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   123

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  49
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  114

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   205,   205,   207,   211,   216,   221,   222,   223,   224,
     225,   226,   227,   232,   238,   247,   248,   249,   250,   258,
     259,   276,   277,   278,   279,   280,   284,   284,   292,   293,
     293,   305,   306,   306,   318,   319,   323,   338,   350,   365,
     381,   394,   397,   401,   409,   414,   422,   444,   447,   451
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
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "ID",
  "TEXTO", "IF", "ELSE", "ELIF", "LPAR", "RPAR", "LBRAC", "RBRAC", "IGUAL",
  "SUMA", "RESTA", "MULTIPLICACION", "DIVISION", "GREATER", "LESSER",
  "GTEQ", "LSEQ", "EQ", "FOR", "SEMICOLON", "WHILE", "PLUS", "CALL",
  "RETURN", "FUNCTION", "COMA", "IMPRIMIR", "$accept", "PROGRAM",
  "EXPRESSION", "ASSIGNMENT", "OPERATION", "LOGIC", "CONDITIONAL", "$@1",
  "ELSEIF", "$@2", "THEN", "$@3", "inCOND", "LOOP", "FOR_INC",
  "FUNCTION_DECLARATION", "PARAM_LIST", "FUNCTION_BODY", "FUNCTION_CALL",
  "PARAMS", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-56)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -56,    30,   -56,   -56,     5,    18,    20,    26,    33,    41,
      43,   -56,   -56,    55,   -56,   -56,   -56,   -56,   -56,    44,
      19,    52,    19,    49,    54,    87,    19,    19,    19,    19,
      19,    19,    19,    19,    19,   -56,   -56,    72,    55,    57,
       5,    69,    71,    19,    90,    85,    68,    15,    15,   -56,
     -56,    72,    72,    72,    72,    72,    86,    19,    88,    72,
      -5,   -56,    16,   -56,   -56,   -56,    74,    37,   -56,    19,
      89,    92,    37,    97,    37,    91,    72,    76,   -56,    93,
       2,    96,   -56,   -56,    17,    95,    94,   105,    83,    99,
      72,   -56,   -56,   102,   106,   -56,   -56,    37,    19,   101,
     -56,   103,   104,   -56,   -56,   107,    37,   -56,   108,    37,
     -56,   109,    94,   -56
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,    19,    20,     0,     0,     0,     0,     0,
       0,     3,     6,     4,     5,     7,     8,     9,    10,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    20,    13,    14,     0,     0,
       0,     0,     0,    47,    41,     0,     0,    15,    16,    17,
      18,    21,    22,    23,    24,    25,     0,     0,     0,    48,
       0,    42,     0,    12,    11,    26,     0,    35,    46,     0,
       0,     0,    35,     0,    35,     0,    49,     0,    43,     0,
       0,     0,    34,    37,     0,     0,    28,     0,     0,     0,
      44,    45,    40,     0,    31,    39,    38,    35,     0,     0,
      27,     0,     0,    32,    36,     0,    35,    29,     0,    35,
      33,     0,    28,    30
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   115,    98,   -19,   -18,   -56,   -56,    10,   -56,
     -56,   -56,   -55,   -56,   -56,   -56,   -56,   -56,    39,   -56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,    74,    12,    13,    14,    15,    72,    94,   109,
     100,   106,    75,    16,    81,    17,    62,    85,    18,    60
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      37,    38,    39,    38,    42,    68,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    87,    79,    19,    82,
       3,    35,     3,    35,    59,    69,    70,    20,    88,    21,
       2,    28,    29,     3,     4,    22,     5,    23,    38,    66,
       3,     4,   101,     5,     8,    24,    71,     3,    35,    36,
      76,   108,    25,     6,   111,     7,    40,     8,    43,     9,
       6,    10,     7,    44,     8,    90,     9,    56,    10,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    64,    38,
     102,    58,    26,    27,    28,    29,    26,    27,    28,    29,
       3,    35,    45,    57,    61,    63,    78,    65,    73,    67,
      77,    80,    93,    83,    84,    86,    89,    92,    95,    96,
      97,    98,   103,    99,   105,   104,    11,     0,   107,    41,
     110,   112,   113,    91
};

static const yytype_int8 yycheck[] =
{
      19,    20,    20,    22,    22,    10,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    14,    72,    13,    74,
       3,     4,     3,     4,    43,    30,    10,     9,    26,     9,
       0,    16,    17,     3,     4,     9,     6,     4,    57,    57,
       3,     4,    97,     6,    27,     4,    30,     3,     4,     5,
      69,   106,     9,    23,   109,    25,     4,    27,     9,    29,
      23,    31,    25,     9,    27,    84,    29,    10,    31,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    10,    98,
      98,    10,    14,    15,    16,    17,    14,    15,    16,    17,
       3,     4,     5,    24,     4,    10,     4,    11,    24,    11,
      11,     4,     8,    12,    28,    12,    10,    12,     3,    26,
      11,     9,    11,     7,    10,    12,     1,    -1,    11,    21,
      12,    12,   112,    84
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    33,     0,     3,     4,     6,    23,    25,    27,    29,
      31,    34,    35,    36,    37,    38,    45,    47,    50,    13,
       9,     9,     9,     4,     4,     9,    14,    15,    16,    17,
      18,    19,    20,    21,    22,     4,     5,    36,    36,    37,
       4,    35,    37,     9,     9,     5,    36,    36,    36,    36,
      36,    36,    36,    36,    36,    36,    10,    24,    10,    36,
      51,     4,    48,    10,    10,    11,    37,    11,    10,    30,
      10,    30,    39,    24,    34,    44,    36,    11,     4,    44,
       4,    46,    44,    12,    28,    49,    12,    14,    26,    10,
      36,    50,    12,     8,    40,     3,    26,    11,     9,     7,
      42,    44,    37,    11,    12,    10,    43,    11,    44,    41,
      12,    44,    12,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    33,    34,    34,    34,    34,    34,    34,
      34,    34,    34,    35,    35,    36,    36,    36,    36,    36,
      36,    37,    37,    37,    37,    37,    39,    38,    40,    41,
      40,    42,    43,    42,    44,    44,    45,    45,    46,    46,
      47,    48,    48,    48,    49,    49,    50,    51,    51,    51
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     4,     4,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     3,     3,     3,     3,     0,    10,     0,     0,
       9,     0,     0,     5,     2,     0,    11,     7,     3,     3,
       8,     0,     1,     3,     2,     2,     5,     0,     1,     3
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
  case 4: /* EXPRESSION: OPERATION  */
#line 211 "parser.y"
              {
        if (get_current_execution_context()) {
            
        }
    }
#line 1349 "parser.tab.c"
    break;

  case 5: /* EXPRESSION: LOGIC  */
#line 216 "parser.y"
            {
        if (get_current_execution_context()) {
            
        }
    }
#line 1359 "parser.tab.c"
    break;

  case 11: /* EXPRESSION: IMPRIMIR LPAR OPERATION RPAR  */
#line 226 "parser.y"
                                    { imprimir((void*)&(yyvsp[-1].val), 0); }
#line 1365 "parser.tab.c"
    break;

  case 12: /* EXPRESSION: IMPRIMIR LPAR TEXTO RPAR  */
#line 227 "parser.y"
                                { imprimir((void*)&(yyvsp[-1].str), 1); }
#line 1371 "parser.tab.c"
    break;

  case 13: /* ASSIGNMENT: ID IGUAL TEXTO  */
#line 232 "parser.y"
                   {
        if (get_current_execution_context()) {
            set_variable_value((yyvsp[-2].str), 1, 0, (yyvsp[0].str));
            printf("Variable %s asignada a %s\n", (yyvsp[-2].str), (yyvsp[0].str));
        }
    }
#line 1382 "parser.tab.c"
    break;

  case 14: /* ASSIGNMENT: ID IGUAL OPERATION  */
#line 238 "parser.y"
                         {
        if (get_current_execution_context()) {
            set_variable_value((yyvsp[-2].str), 0, (yyvsp[0].val), NULL);
            printf("Variable %s asignada a %d\n", (yyvsp[-2].str), (yyvsp[0].val));
        }
    }
#line 1393 "parser.tab.c"
    break;

  case 15: /* OPERATION: OPERATION SUMA OPERATION  */
#line 247 "parser.y"
                             { (yyval.val) = (yyvsp[-2].val) + (yyvsp[0].val); }
#line 1399 "parser.tab.c"
    break;

  case 16: /* OPERATION: OPERATION RESTA OPERATION  */
#line 248 "parser.y"
                                { (yyval.val) = (yyvsp[-2].val) - (yyvsp[0].val); }
#line 1405 "parser.tab.c"
    break;

  case 17: /* OPERATION: OPERATION MULTIPLICACION OPERATION  */
#line 249 "parser.y"
                                         { (yyval.val) = (yyvsp[-2].val) * (yyvsp[0].val); }
#line 1411 "parser.tab.c"
    break;

  case 18: /* OPERATION: OPERATION DIVISION OPERATION  */
#line 250 "parser.y"
                                   {
        if ((yyvsp[0].val) == 0) {
            yyerror("Error: División por cero.");
            (yyval.val) = 0;
        } else {
            (yyval.val) = (yyvsp[-2].val) / (yyvsp[0].val);
        }
    }
#line 1424 "parser.tab.c"
    break;

  case 19: /* OPERATION: NUMBER  */
#line 258 "parser.y"
             { (yyval.val) = (yyvsp[0].val); }
#line 1430 "parser.tab.c"
    break;

  case 20: /* OPERATION: ID  */
#line 259 "parser.y"
         {
        char strval[100];
        int type;
        int val = get_variable_value((yyvsp[0].str), &type, strval);
        if (val == -1) {
            yyerror("Error: Variable no declarada.");
            exit(1);
        } else if (type == 0) {
            (yyval.val) = val;
        } else if (type == 1) {
            yyerror("Error: No se pueden realizar operaciones numéricas con strings.");
            exit(1);
        }
    }
#line 1449 "parser.tab.c"
    break;

  case 21: /* LOGIC: OPERATION GREATER OPERATION  */
#line 276 "parser.y"
                                { (yyval.val) = (yyvsp[-2].val) > (yyvsp[0].val); }
#line 1455 "parser.tab.c"
    break;

  case 22: /* LOGIC: OPERATION LESSER OPERATION  */
#line 277 "parser.y"
                                 { (yyval.val) = (yyvsp[-2].val) < (yyvsp[0].val); }
#line 1461 "parser.tab.c"
    break;

  case 23: /* LOGIC: OPERATION GTEQ OPERATION  */
#line 278 "parser.y"
                               { (yyval.val) = (yyvsp[-2].val) >= (yyvsp[0].val); }
#line 1467 "parser.tab.c"
    break;

  case 24: /* LOGIC: OPERATION LSEQ OPERATION  */
#line 279 "parser.y"
                               { (yyval.val) = (yyvsp[-2].val) <= (yyvsp[0].val); }
#line 1473 "parser.tab.c"
    break;

  case 25: /* LOGIC: OPERATION EQ OPERATION  */
#line 280 "parser.y"
                             { (yyval.val) = (yyvsp[-2].val) == (yyvsp[0].val); }
#line 1479 "parser.tab.c"
    break;

  case 26: /* $@1: %empty  */
#line 284 "parser.y"
                             {
        push_execution_context((yyvsp[-2].val));
    }
#line 1487 "parser.tab.c"
    break;

  case 27: /* CONDITIONAL: IF LPAR LOGIC RPAR LBRAC $@1 inCOND RBRAC ELSEIF THEN  */
#line 286 "parser.y"
                               {
        pop_execution_context();
    }
#line 1495 "parser.tab.c"
    break;

  case 28: /* ELSEIF: %empty  */
#line 292 "parser.y"
                 {}
#line 1501 "parser.tab.c"
    break;

  case 29: /* $@2: %empty  */
#line 293 "parser.y"
                                 {
        if (get_current_execution_context() == 0 && (yyvsp[-2].val)) {
            push_execution_context(1);
        } else {
            push_execution_context(0);
        }
    }
#line 1513 "parser.tab.c"
    break;

  case 30: /* ELSEIF: ELIF LPAR LOGIC RPAR LBRAC $@2 inCOND RBRAC ELSEIF  */
#line 299 "parser.y"
                          {
        pop_execution_context();
    }
#line 1521 "parser.tab.c"
    break;

  case 31: /* THEN: %empty  */
#line 305 "parser.y"
                {}
#line 1527 "parser.tab.c"
    break;

  case 32: /* $@3: %empty  */
#line 306 "parser.y"
                 {
        if (get_current_execution_context() == 0) {
            push_execution_context(1);
        } else {
            push_execution_context(0);
        }
    }
#line 1539 "parser.tab.c"
    break;

  case 33: /* THEN: ELSE LBRAC $@3 inCOND RBRAC  */
#line 312 "parser.y"
                   {
        pop_execution_context();
    }
#line 1547 "parser.tab.c"
    break;

  case 34: /* inCOND: EXPRESSION inCOND  */
#line 318 "parser.y"
                      {}
#line 1553 "parser.tab.c"
    break;

  case 35: /* inCOND: %empty  */
#line 319 "parser.y"
                  {}
#line 1559 "parser.tab.c"
    break;

  case 36: /* LOOP: FOR LPAR ASSIGNMENT SEMICOLON LOGIC SEMICOLON FOR_INC RPAR LBRAC inCOND RBRAC  */
#line 323 "parser.y"
                                                                                  {
        if (get_current_execution_context()) {

            int var= (yyvsp[-8].val);
            int lgc = (yyvsp[-6].val);
            int inc = (yyvsp[-1].val);

            
            for (int i=0;i<3;i++) {
                push_execution_context(1);
                (yyvsp[-1].val);
                pop_execution_context();
            }
        }
    }
#line 1579 "parser.tab.c"
    break;

  case 37: /* LOOP: WHILE LPAR LOGIC RPAR LBRAC inCOND RBRAC  */
#line 338 "parser.y"
                                               {
        if (get_current_execution_context()) {
            while ((yyvsp[-4].val)) {
                push_execution_context(1);
                (yyvsp[-1].val);
                pop_execution_context();
            }
        }
    }
#line 1593 "parser.tab.c"
    break;

  case 38: /* FOR_INC: ID PLUS PLUS  */
#line 350 "parser.y"
                 {
        if (get_current_execution_context()) {
            int type;
            char strval[100];
            int value = get_variable_value((yyvsp[-2].str), &type, strval);
            if (type != 0) {
                yyerror("Error: Solo se puede incrementar variables numéricas.");
                exit(1);
            }
            
            value++;
            set_variable_value((yyvsp[-2].str), 0, value, NULL);
            printf("Valor: %d",get_variable_value((yyvsp[-2].str), &type, strval));
        }
    }
#line 1613 "parser.tab.c"
    break;

  case 39: /* FOR_INC: ID SUMA NUMBER  */
#line 365 "parser.y"
                     {
        if (get_current_execution_context()) {
            int type;
            char strval[100];
            int value = get_variable_value((yyvsp[-2].str), &type, strval);
            if (type != 0) {
                yyerror("Error: Solo se puede incrementar variables numéricas.");
                exit(1);
            }
            value += (yyvsp[0].val);
            set_variable_value((yyvsp[-2].str), 0, value, NULL);
        }
    }
#line 1631 "parser.tab.c"
    break;

  case 40: /* FUNCTION_DECLARATION: FUNCTION ID LPAR PARAM_LIST RPAR LBRAC FUNCTION_BODY RBRAC  */
#line 381 "parser.y"
                                                               {
        char param_names[MAX_PARAMS][100];
        
        for (int i = 0; i < (yyvsp[-4].param_list).param_count; i++) {
            strcpy(param_names[i], (yyvsp[-4].param_list).param_names[i]);
        }

        add_function((yyvsp[-6].str), param_names, (yyvsp[-4].param_list).param_count, (yyvsp[-1].func_body).func);
        printf("Función %s declarada.\n", (yyvsp[-6].str));
    }
#line 1646 "parser.tab.c"
    break;

  case 41: /* PARAM_LIST: %empty  */
#line 394 "parser.y"
                { 
        (yyval.param_list) = (struct ParamList){0, {{0}}}; 
    }
#line 1654 "parser.tab.c"
    break;

  case 42: /* PARAM_LIST: ID  */
#line 397 "parser.y"
         { 
        (yyval.param_list) = (struct ParamList){1, {{0}}}; 
        strcpy((yyval.param_list).param_names[0], (yyvsp[0].str)); 
    }
#line 1663 "parser.tab.c"
    break;

  case 43: /* PARAM_LIST: PARAM_LIST COMA ID  */
#line 401 "parser.y"
                         {
        (yyvsp[-2].param_list).param_count++;
        strcpy((yyvsp[-2].param_list).param_names[(yyvsp[-2].param_list).param_count - 1], (yyvsp[0].str));
        (yyval.param_list) = (yyvsp[-2].param_list);
    }
#line 1673 "parser.tab.c"
    break;

  case 44: /* FUNCTION_BODY: RETURN OPERATION  */
#line 409 "parser.y"
                     {
        struct FuncBody fb;
        fb.func = some_predefined_function;  
        (yyval.func_body) = fb;
    }
#line 1683 "parser.tab.c"
    break;

  case 45: /* FUNCTION_BODY: RETURN FUNCTION_CALL  */
#line 414 "parser.y"
                           { 
        struct FuncBody fb;
        fb.func = some_predefined_function; 
        (yyval.func_body) = fb;
    }
#line 1693 "parser.tab.c"
    break;

  case 46: /* FUNCTION_CALL: CALL ID LPAR PARAMS RPAR  */
#line 422 "parser.y"
                             {
        struct Function *func = get_function((yyvsp[-3].str));
        if (!func) {
            yyerror("Error: Función no definida.");
        } else {
            if ((yyvsp[-1].function_params).param_count != func->param_count) {
                yyerror("Error: Número incorrecto de parámetros.");
            } else {
                int params[MAX_PARAMS];
                for (int i = 0; i < (yyvsp[-1].function_params).param_count; i++) {
                    params[i] = (yyvsp[-1].function_params).params[i];
                }

                printf("Llamada a función %s\n", (yyvsp[-3].str));
                func->func_body(params); 
            }
        }
    }
#line 1716 "parser.tab.c"
    break;

  case 47: /* PARAMS: %empty  */
#line 444 "parser.y"
     { 
        (yyval.function_params) = (struct FunctionParams){0, {0}}; 
    }
#line 1724 "parser.tab.c"
    break;

  case 48: /* PARAMS: OPERATION  */
#line 447 "parser.y"
                {
        (yyval.function_params) = (struct FunctionParams){1, {0}};
        (yyval.function_params).params[0] = (yyvsp[0].val);
    }
#line 1733 "parser.tab.c"
    break;

  case 49: /* PARAMS: PARAMS COMA OPERATION  */
#line 451 "parser.y"
                            {
        (yyvsp[-2].function_params).param_count++;
        (yyvsp[-2].function_params).params[(yyvsp[-2].function_params).param_count - 1] = (yyvsp[0].val);
        (yyval.function_params) = (yyvsp[-2].function_params);
    }
#line 1743 "parser.tab.c"
    break;


#line 1747 "parser.tab.c"

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

#line 458 "parser.y"

void imprimir(void* value, int tipo) {
    if (tipo == 0) {  // Es un entero
        printf("%d\n", *(int*)value);
    } else if (tipo == 1) {  // Es una cadena
        printf("%s\n", (char*)value);
    }
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char **argv) {

    FILE *archivo = fopen(argv[1], "r");
    if (!archivo) {
        perror("Error al abrir el archivo");
        return 1;
    }

    yyin = archivo;
    yyparse();
    fclose(archivo);
    return 0;
}
