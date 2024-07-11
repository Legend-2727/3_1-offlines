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
#line 1 "2005042.y"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <cmath>
//#include "2005042_SymbolTable.h"
#include "2005042_ICG.cpp"
#define BUCKET_SIZE 11
using namespace std;

int yylex(void);
int yyparse(void);

extern FILE *yyin;
extern int line_count;
extern int error_count;
ofstream parsetree_out, error_out,asm_out,opt_asm_out;
ifstream asm_in;
ofstream logout;
SymbolTable *symbolTable;
ScopeTable *scopetable;
void yyerror(string s)
{
    logout<<"Error at line no "<<line_count<<": syntax error"<<'\n';
	error_count++;
}

void free_s(SymbolInfo *s) {
    if (s != nullptr) {
        delete s;
		s=nullptr;
    }
}

void printInLog(string rule) {
	logout<< rule << " \n";
}
void insertAll(string type,SymbolInfo *sm){
	Parameter *temp=sm->getParameterList();
	while(temp!=NULL){
		symbolTable->insert(temp->getName(),type,"",line_count,error_out);
		temp=temp->getNext();
	}
}
void insertParameters(SymbolInfo *sm){
	cout<<"here\n";
	Parameter *temp=sm->getParameterList();
	while(temp!=NULL){
		symbolTable->insert(temp->getName(),temp->getType(),"",line_count,error_out);
		temp=temp->getNext();
	}
}
void printInParseTree(SymbolInfo *root,int height){
	for(int i=0;i<height;i++){
		parsetree_out<<" ";
	}
	//cout<<"eikhane\n";
	parsetree_out<<root->getRule()<<"\t";
	if(root->getEndLine()!=-1){
		parsetree_out<<"<Line: "<<root->getStartLine()<<"-"<<root->getEndLine()<<">\n";
	}
	else{
		parsetree_out<<"<Line: "<<root->getStartLine()<<">\n";
	}
	SymbolInfo *temp=root->getChild();
	while(temp!=NULL){
		printInParseTree(temp,height+1);
		temp=temp->getNext();
	}
}

void printError(string type,string state,string location,int lc){
	error_out<<"Line# "<<lc<<":"<<type<<" at "<<state<<" of "<<location<<"\n";
}

#line 150 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ASSIGNOP = 258,                /* ASSIGNOP  */
    LOGICOP = 259,                 /* LOGICOP  */
    RELOP = 260,                   /* RELOP  */
    ADDOP = 261,                   /* ADDOP  */
    MULOP = 262,                   /* MULOP  */
    NOT = 263,                     /* NOT  */
    INCOP = 264,                   /* INCOP  */
    DECOP = 265,                   /* DECOP  */
    RPAREN = 266,                  /* RPAREN  */
    ELSE = 267,                    /* ELSE  */
    IF = 268,                      /* IF  */
    FOR = 269,                     /* FOR  */
    WHILE = 270,                   /* WHILE  */
    RETURN = 271,                  /* RETURN  */
    PRINTLN = 272,                 /* PRINTLN  */
    SWITCH = 273,                  /* SWITCH  */
    CASE = 274,                    /* CASE  */
    BREAK = 275,                   /* BREAK  */
    DEFAULT = 276,                 /* DEFAULT  */
    COLON = 277,                   /* COLON  */
    LPAREN = 278,                  /* LPAREN  */
    LCURL = 279,                   /* LCURL  */
    RCURL = 280,                   /* RCURL  */
    LTHIRD = 281,                  /* LTHIRD  */
    RTHIRD = 282,                  /* RTHIRD  */
    COMMA = 283,                   /* COMMA  */
    SEMICOLON = 284,               /* SEMICOLON  */
    INT = 285,                     /* INT  */
    FLOAT = 286,                   /* FLOAT  */
    VOID = 287,                    /* VOID  */
    CONST_INT = 288,               /* CONST_INT  */
    CONST_FLOAT = 289,             /* CONST_FLOAT  */
    ID = 290                       /* ID  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ASSIGNOP 258
#define LOGICOP 259
#define RELOP 260
#define ADDOP 261
#define MULOP 262
#define NOT 263
#define INCOP 264
#define DECOP 265
#define RPAREN 266
#define ELSE 267
#define IF 268
#define FOR 269
#define WHILE 270
#define RETURN 271
#define PRINTLN 272
#define SWITCH 273
#define CASE 274
#define BREAK 275
#define DEFAULT 276
#define COLON 277
#define LPAREN 278
#define LCURL 279
#define RCURL 280
#define LTHIRD 281
#define RTHIRD 282
#define COMMA 283
#define SEMICOLON 284
#define INT 285
#define FLOAT 286
#define VOID 287
#define CONST_INT 288
#define CONST_FLOAT 289
#define ID 290

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 83 "2005042.y"

    SymbolInfo *symbolInfo;

#line 277 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ASSIGNOP = 3,                   /* ASSIGNOP  */
  YYSYMBOL_LOGICOP = 4,                    /* LOGICOP  */
  YYSYMBOL_RELOP = 5,                      /* RELOP  */
  YYSYMBOL_ADDOP = 6,                      /* ADDOP  */
  YYSYMBOL_MULOP = 7,                      /* MULOP  */
  YYSYMBOL_NOT = 8,                        /* NOT  */
  YYSYMBOL_INCOP = 9,                      /* INCOP  */
  YYSYMBOL_DECOP = 10,                     /* DECOP  */
  YYSYMBOL_RPAREN = 11,                    /* RPAREN  */
  YYSYMBOL_ELSE = 12,                      /* ELSE  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_RETURN = 16,                    /* RETURN  */
  YYSYMBOL_PRINTLN = 17,                   /* PRINTLN  */
  YYSYMBOL_SWITCH = 18,                    /* SWITCH  */
  YYSYMBOL_CASE = 19,                      /* CASE  */
  YYSYMBOL_BREAK = 20,                     /* BREAK  */
  YYSYMBOL_DEFAULT = 21,                   /* DEFAULT  */
  YYSYMBOL_COLON = 22,                     /* COLON  */
  YYSYMBOL_LPAREN = 23,                    /* LPAREN  */
  YYSYMBOL_LCURL = 24,                     /* LCURL  */
  YYSYMBOL_RCURL = 25,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 26,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 27,                    /* RTHIRD  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 29,                 /* SEMICOLON  */
  YYSYMBOL_INT = 30,                       /* INT  */
  YYSYMBOL_FLOAT = 31,                     /* FLOAT  */
  YYSYMBOL_VOID = 32,                      /* VOID  */
  YYSYMBOL_CONST_INT = 33,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 34,               /* CONST_FLOAT  */
  YYSYMBOL_ID = 35,                        /* ID  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_start = 37,                     /* start  */
  YYSYMBOL_program = 38,                   /* program  */
  YYSYMBOL_unit = 39,                      /* unit  */
  YYSYMBOL_switch_case_definition = 40,    /* switch_case_definition  */
  YYSYMBOL_case_handle = 41,               /* case_handle  */
  YYSYMBOL_default_part = 42,              /* default_part  */
  YYSYMBOL_func_declaration = 43,          /* func_declaration  */
  YYSYMBOL_func_definition = 44,           /* func_definition  */
  YYSYMBOL_parameter_list = 45,            /* parameter_list  */
  YYSYMBOL_compound_statement = 46,        /* compound_statement  */
  YYSYMBOL_var_declaration = 47,           /* var_declaration  */
  YYSYMBOL_type_specifier = 48,            /* type_specifier  */
  YYSYMBOL_declaration_list = 49,          /* declaration_list  */
  YYSYMBOL_statements = 50,                /* statements  */
  YYSYMBOL_statement = 51,                 /* statement  */
  YYSYMBOL_expression_statement = 52,      /* expression_statement  */
  YYSYMBOL_variable = 53,                  /* variable  */
  YYSYMBOL_expression = 54,                /* expression  */
  YYSYMBOL_logic_expression = 55,          /* logic_expression  */
  YYSYMBOL_rel_expression = 56,            /* rel_expression  */
  YYSYMBOL_simple_expression = 57,         /* simple_expression  */
  YYSYMBOL_term = 58,                      /* term  */
  YYSYMBOL_unary_expression = 59,          /* unary_expression  */
  YYSYMBOL_factor = 60,                    /* factor  */
  YYSYMBOL_argument_list = 61,             /* argument_list  */
  YYSYMBOL_arguments = 62                  /* arguments  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  15
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   301

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  155

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


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
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   110,   110,   131,   139,   148,   159,   166,   173,   180,
     188,   201,   215,   230,   243,   250,   262,   282,   296,   315,
     333,   343,   358,   371,   382,   392,   400,   413,   427,   437,
     445,   451,   457,   465,   479,   498,   509,   524,   534,   541,
     551,   558,   565,   572,   585,   596,   609,   620,   631,   642,
     649,   659,   667,   682,   689,   698,   707,   714,   725,   732,
     743,   750,   761,   768,   779,   787,   795,   804,   811,   821,
     830,   837,   844,   852,   862,   869,   877,   886,   895
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ASSIGNOP", "LOGICOP",
  "RELOP", "ADDOP", "MULOP", "NOT", "INCOP", "DECOP", "RPAREN", "ELSE",
  "IF", "FOR", "WHILE", "RETURN", "PRINTLN", "SWITCH", "CASE", "BREAK",
  "DEFAULT", "COLON", "LPAREN", "LCURL", "RCURL", "LTHIRD", "RTHIRD",
  "COMMA", "SEMICOLON", "INT", "FLOAT", "VOID", "CONST_INT", "CONST_FLOAT",
  "ID", "$accept", "start", "program", "unit", "switch_case_definition",
  "case_handle", "default_part", "func_declaration", "func_definition",
  "parameter_list", "compound_statement", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-107)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-76)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     100,  -107,    -4,  -107,  -107,  -107,    29,   269,  -107,  -107,
    -107,  -107,  -107,     6,    61,  -107,  -107,  -107,    33,    24,
    -107,   166,   166,    61,  -107,  -107,    53,   101,    46,  -107,
      79,    97,   122,  -107,  -107,   135,   112,   105,   113,  -107,
     103,  -107,  -107,   136,    16,    61,   166,  -107,  -107,   125,
     166,   166,   166,   166,  -107,   -11,    32,   117,   126,  -107,
     128,  -107,  -107,  -107,   144,   141,   137,  -107,    47,  -107,
     165,   122,  -107,    57,  -107,  -107,    90,   107,  -107,  -107,
     140,  -107,   166,  -107,   147,   159,    19,  -107,   160,   161,
     164,    61,   167,  -107,  -107,  -107,  -107,    10,    92,  -107,
    -107,   153,  -107,  -107,   169,   175,  -107,   184,   127,   155,
    -107,    61,   251,    61,   178,   173,   183,  -107,  -107,  -107,
    -107,  -107,   127,   162,   193,   205,   251,   206,  -107,   207,
     197,   199,   127,   127,    61,   127,   194,   202,   195,   232,
     213,   223,  -107,  -107,   208,  -107,   215,   127,   127,  -107,
     210,  -107,  -107,   220,  -107
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     9,     0,    30,    31,    32,     0,     0,     4,     8,
       6,     7,     5,     0,     0,     1,     3,    37,    35,     0,
      55,     0,     0,     0,    70,    71,    51,    67,     0,    53,
      56,    58,    60,    62,    66,     0,     0,     0,     0,    28,
      67,    64,    65,     0,     0,     0,     0,    72,    73,     0,
       0,     0,     0,     0,    25,     0,     0,    24,     0,    29,
      33,    69,    76,    78,     0,    74,     0,    54,     0,    57,
      59,    61,    63,     0,    17,    19,     0,     0,    23,    36,
       0,    68,     0,    52,     0,     0,     0,    14,     0,     0,
       0,     0,     0,    27,    49,    42,    40,     0,     0,    38,
      41,     0,    16,    18,    22,     0,    77,     0,     0,     0,
      10,     0,     0,     0,     0,     0,    35,    26,    39,    50,
      21,    34,     0,     0,     0,     0,     0,     0,    48,     0,
       0,    49,     0,     0,     0,     0,     0,    49,     0,     0,
      44,     0,    46,    47,     0,    15,    49,     0,     0,    13,
       0,    45,    43,    11,    12
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -107,  -107,  -107,   229,  -107,  -107,    89,  -107,  -107,  -107,
     -53,    14,     1,  -107,   -47,   -93,  -106,   -18,   -14,   -34,
     200,   192,   201,    -6,  -107,  -107,  -107
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     6,     7,     8,     9,    86,    87,    10,    11,    56,
      95,    96,    97,    19,    98,    99,   100,    27,   101,    29,
      30,    31,    32,    33,    34,    64,    65
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      28,    13,    75,    40,    40,   118,   126,    17,    13,    43,
      63,    17,    67,    73,    12,    41,    42,    62,    74,    14,
     134,    12,    21,   103,    22,    37,    40,   -75,    40,    15,
     118,    66,    40,    40,    40,    40,    57,   118,   109,    23,
     140,    18,   142,    76,   110,   116,   118,    72,   106,    24,
      25,    26,    38,    39,   151,   152,    35,    49,    20,    36,
      77,   123,    20,    21,    40,    22,    84,    21,    85,    22,
      88,    89,    90,    91,    92,   130,    44,   114,   104,    45,
      23,    73,    93,    50,    23,   139,    94,     3,     4,     5,
      24,    25,    26,    20,    24,    25,    26,   125,    21,   127,
      22,     1,    51,    52,    46,    88,    89,    90,    91,    92,
      47,    48,    47,    48,    73,    23,    73,   117,     2,   102,
     141,    94,     3,     4,     5,    24,    25,    26,    20,    53,
       3,     4,     5,    21,    59,    22,    54,     3,     4,     5,
      88,    89,    90,    91,    92,    58,    55,    61,    60,    68,
      23,    73,    78,    79,    80,    81,    94,     3,     4,     5,
      24,    25,    26,    20,    83,     3,     4,     5,    21,    82,
      22,    52,    21,   105,    22,    88,    89,    90,    91,    92,
     107,   108,   119,   111,   112,    23,    73,   113,   124,    23,
     115,   131,     3,     4,     5,    24,    25,    26,    20,    24,
      25,    26,   121,    21,   120,    22,   122,   128,   129,    36,
      88,    89,    90,    91,    92,   132,   133,   135,   136,   138,
      23,    73,   144,   143,   145,   147,   137,     3,     4,     5,
      24,    25,    26,    20,   148,   150,    16,   149,    21,   153,
      22,    85,   154,    70,     0,    88,    89,    90,    91,    92,
      69,     0,    20,    71,     0,    23,    73,    21,     0,    22,
       0,   146,     3,     4,     5,    24,    25,    26,     0,    -2,
       1,     0,     0,     0,    23,     0,     0,     0,     0,     0,
      94,     0,     0,     0,    24,    25,    26,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
       4,     5
};

static const yytype_int16 yycheck[] =
{
      14,     0,    55,    21,    22,    98,   112,     1,     7,    23,
      44,     1,    46,    24,     0,    21,    22,     1,    29,    23,
     126,     7,     6,    76,     8,     1,    44,    11,    46,     0,
     123,    45,    50,    51,    52,    53,    35,   130,    19,    23,
     133,    35,   135,    11,    25,    35,   139,    53,    82,    33,
      34,    35,    28,    29,   147,   148,    23,    11,     1,    26,
      28,   108,     1,     6,    82,     8,    19,     6,    21,     8,
      13,    14,    15,    16,    17,   122,    23,    91,    77,    26,
      23,    24,    25,     4,    23,   132,    29,    30,    31,    32,
      33,    34,    35,     1,    33,    34,    35,   111,     6,   113,
       8,     1,     5,     6,     3,    13,    14,    15,    16,    17,
       9,    10,     9,    10,    24,    23,    24,    25,    18,    29,
     134,    29,    30,    31,    32,    33,    34,    35,     1,     7,
      30,    31,    32,     6,    29,     8,     1,    30,    31,    32,
      13,    14,    15,    16,    17,    33,    11,    11,    35,    24,
      23,    24,    35,    27,    26,    11,    29,    30,    31,    32,
      33,    34,    35,     1,    27,    30,    31,    32,     6,    28,
       8,     6,     6,    33,     8,    13,    14,    15,    16,    17,
      33,    22,    29,    23,    23,    23,    24,    23,    33,    23,
      23,    29,    30,    31,    32,    33,    34,    35,     1,    33,
      34,    35,    27,     6,    35,     8,    22,    29,    35,    26,
      13,    14,    15,    16,    17,    22,    11,    11,    11,    20,
      23,    24,    20,    29,    29,    12,    29,    30,    31,    32,
      33,    34,    35,     1,    11,    20,     7,    29,     6,    29,
       8,    21,   153,    51,    -1,    13,    14,    15,    16,    17,
      50,    -1,     1,    52,    -1,    23,    24,     6,    -1,     8,
      -1,    29,    30,    31,    32,    33,    34,    35,    -1,     0,
       1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    -1,    -1,    33,    34,    35,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      31,    32
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    18,    30,    31,    32,    37,    38,    39,    40,
      43,    44,    47,    48,    23,     0,    39,     1,    35,    49,
       1,     6,     8,    23,    33,    34,    35,    53,    54,    55,
      56,    57,    58,    59,    60,    23,    26,     1,    28,    29,
      53,    59,    59,    54,    23,    26,     3,     9,    10,    11,
       4,     5,     6,     7,     1,    11,    45,    48,    33,    29,
      35,    11,     1,    55,    61,    62,    54,    55,    24,    56,
      57,    58,    59,    24,    29,    46,    11,    28,    35,    27,
      26,    11,    28,    27,    19,    21,    41,    42,    13,    14,
      15,    16,    17,    25,    29,    46,    47,    48,    50,    51,
      52,    54,    29,    46,    48,    33,    55,    33,    22,    19,
      25,    23,    23,    23,    54,    23,    35,    25,    51,    29,
      35,    27,    22,    50,    33,    54,    52,    54,    29,    35,
      50,    29,    22,    11,    52,    11,    11,    29,    20,    50,
      51,    54,    51,    29,    20,    29,    29,    12,    11,    29,
      20,    51,    51,    29,    42
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    39,    39,    39,
      40,    41,    41,    41,    41,    42,    43,    43,    44,    44,
      44,    45,    45,    45,    45,    45,    46,    46,    47,    47,
      48,    48,    48,    49,    49,    49,    49,    49,    50,    50,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    52,
      52,    53,    53,    54,    54,    54,    55,    55,    56,    56,
      57,    57,    58,    58,    59,    59,    59,    60,    60,    60,
      60,    60,    60,    60,    61,    61,    61,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       7,     8,     9,     7,     1,     6,     6,     5,     6,     5,
       1,     4,     3,     2,     1,     1,     3,     2,     3,     4,
       1,     1,     1,     3,     6,     1,     4,     1,     1,     2,
       1,     1,     1,     7,     5,     7,     5,     5,     3,     1,
       2,     1,     4,     1,     3,     1,     1,     3,     1,     3,
       1,     3,     1,     3,     2,     2,     1,     1,     4,     3,
       1,     1,     2,     2,     1,     0,     1,     3,     1
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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
  case 2: /* start: program  */
#line 111 "2005042.y"
        {
		SymbolInfo *temp=new SymbolInfo("Root","Start");
		temp->setRule("start : program");
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo) = temp;
		printInLog(temp->getRule());
		cout<<"p\n";
		printInParseTree((yyval.symbolInfo),0);
		printInAssembly(asm_out,(yyval.symbolInfo));
		asm_out.close();
		asm_in.open("2005042_code.asm");
		opt_asm_out.open("2005042)_optimized_code.asm");
		generateOptimizedCode(opt_asm_out,asm_in);
		opt_asm_out.close();
		asm_in.close();
		//free_s($$);
		cout<<"he\n";
	}
#line 1735 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 131 "2005042.y"
                      {
		SymbolInfo *temp=new SymbolInfo("Node","program");
		temp->setRule("program : program unit");
		temp->addChild((yyvsp[-1].symbolInfo));
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo) = temp;
		printInLog(temp->getRule());
	}
#line 1748 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 139 "2005042.y"
              {
		SymbolInfo *temp=new SymbolInfo("Node","program");
		temp->setRule("program : unit");
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo) = temp;
		printInLog(temp->getRule());
	}
#line 1760 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 148 "2005042.y"
                      {
			SymbolInfo *temp=new SymbolInfo("Node","unit");
			temp->setRule("unit : var_declaration");
			// cout<<"here................\n";
			// cout<<$1->getStartLine()<<$1->getEndLine()<<'\n';
			// cout<<temp->getStartLine()<<temp->getEndLine()<<'\n';
			temp->addChild((yyvsp[0].symbolInfo));
			//cout<<temp->getStartLine()<<endl;
			(yyval.symbolInfo) = temp;
			printInLog(temp->getRule());
		}
#line 1776 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 159 "2005042.y"
                       {
		SymbolInfo *temp=new SymbolInfo("Node","unit");
		temp->setRule("unit : func_declaration");
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo) = temp;
		printInLog(temp->getRule());
	 }
#line 1788 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 166 "2005042.y"
                      {
		SymbolInfo* temp= new SymbolInfo("Node","unit");
		temp->setRule("unit : func_definition");
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)=temp;
		printInLog(temp->getRule());
	 }
#line 1800 "y.tab.c"
    break;

  case 8: /* unit: switch_case_definition  */
#line 173 "2005042.y"
                                {
		SymbolInfo* temp= new SymbolInfo("Node","unit");
		temp->setRule("unit : switch_case_definition");
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)=temp;
		printInLog(temp->getRule());
	 }
#line 1812 "y.tab.c"
    break;

  case 9: /* unit: error  */
#line 180 "2005042.y"
               {
		SymbolInfo* temp= new SymbolInfo("Node","unit");
		temp->setRule("unit : error");
		//temp->addChild($1);
		(yyval.symbolInfo)=temp;
		printInLog(temp->getRule());
	 }
#line 1824 "y.tab.c"
    break;

  case 10: /* switch_case_definition: SWITCH LPAREN expression RPAREN LCURL case_handle RCURL  */
#line 188 "2005042.y"
                                                                                 {
	SymbolInfo *temp=new SymbolInfo("Node","switch_case_definition");
	temp->setRule("switch_case_definition  : SWITCH LPAREN expression RPAREN LCURL case_handle RCURL");
	temp->addChild((yyvsp[-6].symbolInfo));
	temp->addChild((yyvsp[-5].symbolInfo));
	temp->addChild((yyvsp[-4].symbolInfo));
	temp->addChild((yyvsp[-3].symbolInfo));
	temp->addChild((yyvsp[-2].symbolInfo));
	temp->addChild((yyvsp[-1].symbolInfo));
	temp->addChild((yyvsp[0].symbolInfo));
	(yyval.symbolInfo)=temp;
	printInLog(temp->getRule());
}
#line 1842 "y.tab.c"
    break;

  case 11: /* case_handle: case_handle CASE CONST_INT COLON statements SEMICOLON BREAK SEMICOLON  */
#line 201 "2005042.y"
                                                                                   {
	SymbolInfo *temp=new SymbolInfo("Node","case_handle");
	temp->setRule("case_handle : case handle CASE CONST_INT  COLON statement SEMICOLON BREAK SEMICOLON");
	temp->addChild((yyvsp[-7].symbolInfo));
	temp->addChild((yyvsp[-6].symbolInfo));
	temp->addChild((yyvsp[-5].symbolInfo));
	temp->addChild((yyvsp[-4].symbolInfo));
	temp->addChild((yyvsp[-3].symbolInfo));
	temp->addChild((yyvsp[-2].symbolInfo));
	temp->addChild((yyvsp[-1].symbolInfo));
	temp->addChild((yyvsp[0].symbolInfo));
	(yyval.symbolInfo)=temp;
	printInLog(temp->getRule());
}
#line 1861 "y.tab.c"
    break;

  case 12: /* case_handle: case_handle CASE CONST_INT COLON statements SEMICOLON BREAK SEMICOLON default_part  */
#line 215 "2005042.y"
                                                                                    {
	SymbolInfo *temp=new SymbolInfo("Node","case_handle");
	temp->setRule("case_handle : case handle CASE CONST_INT  COLON statement SEMICOLON BREAK SEMICOLON default_part");
	temp->addChild((yyvsp[-8].symbolInfo));
	temp->addChild((yyvsp[-7].symbolInfo));
	temp->addChild((yyvsp[-6].symbolInfo));
	temp->addChild((yyvsp[-5].symbolInfo));
	temp->addChild((yyvsp[-4].symbolInfo));
	temp->addChild((yyvsp[-3].symbolInfo));
	temp->addChild((yyvsp[-2].symbolInfo));
	temp->addChild((yyvsp[-1].symbolInfo));
	temp->addChild((yyvsp[0].symbolInfo));
	(yyval.symbolInfo)=temp;
	printInLog(temp->getRule());
}
#line 1881 "y.tab.c"
    break;

  case 13: /* case_handle: CASE CONST_INT COLON statements SEMICOLON BREAK SEMICOLON  */
#line 230 "2005042.y"
                                                                                            {
	SymbolInfo *temp=new SymbolInfo("Node","case_handle");
	temp->setRule("case_handle : CASE CONST_INT  COLON statement SEMICOLON BREAK SEMICOLON");
	temp->addChild((yyvsp[-6].symbolInfo));
	temp->addChild((yyvsp[-5].symbolInfo));
	temp->addChild((yyvsp[-4].symbolInfo));
	temp->addChild((yyvsp[-3].symbolInfo));
	temp->addChild((yyvsp[-2].symbolInfo));
	temp->addChild((yyvsp[-1].symbolInfo));
	temp->addChild((yyvsp[0].symbolInfo));
	(yyval.symbolInfo)=temp;
	printInLog(temp->getRule());
}
#line 1899 "y.tab.c"
    break;

  case 14: /* case_handle: default_part  */
#line 243 "2005042.y"
             {
	SymbolInfo *temp=new SymbolInfo("","case_handle");
	temp->setRule("case_handle : default_part");
	temp->addChild((yyvsp[0].symbolInfo));
	(yyval.symbolInfo)=temp;

}
#line 1911 "y.tab.c"
    break;

  case 15: /* default_part: DEFAULT COLON statements SEMICOLON BREAK SEMICOLON  */
#line 250 "2005042.y"
                                                                {
	SymbolInfo *temp=new SymbolInfo("Node","case_handle");
	temp->setRule("default_part : DEFAULT  COLON statements SEMICOLON BREAK SEMICOLON");
	temp->addChild((yyvsp[-5].symbolInfo));
	temp->addChild((yyvsp[-4].symbolInfo));
	temp->addChild((yyvsp[-3].symbolInfo));
	temp->addChild((yyvsp[-2].symbolInfo));
	temp->addChild((yyvsp[-1].symbolInfo));
	temp->addChild((yyvsp[0].symbolInfo));
	(yyval.symbolInfo)=temp;
	printInLog(temp->getRule());
}
#line 1928 "y.tab.c"
    break;

  case 16: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 262 "2005042.y"
                                                                           {
			//cout<<"here\n";
			SymbolInfo *temp=new SymbolInfo((yyvsp[-4].symbolInfo)->getName(),"func_declaration");
			temp->setRule("func_declaration :  type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
			temp->addChild((yyvsp[-5].symbolInfo));
			temp->addChild((yyvsp[-4].symbolInfo));
			temp->addChild((yyvsp[-3].symbolInfo));
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			if((yyvsp[-2].symbolInfo)->getName()=="error"){
				printError("Syntax error","parameter list","function declaration",line_count);
			}
			temp->addParameterList((yyvsp[-2].symbolInfo)->getParameterList());
			temp->setReturnType((yyvsp[-5].symbolInfo)->getDataType());
			//symbolTable->insert($2->getName(),"FUNCTION",$1->getDataType(),line_count,error_out);
			(yyval.symbolInfo) = temp;
			//symbolTable->insert()
			printInLog(temp->getRule());
		}
#line 1953 "y.tab.c"
    break;

  case 17: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 282 "2005042.y"
                                                           {
			SymbolInfo *temp=new SymbolInfo((yyvsp[-3].symbolInfo)->getName(),"func_declaration");
			temp->setRule("func_declaration :  type_specifier ID LPAREN RPAREN SEMICOLON");
			temp->addChild((yyvsp[-4].symbolInfo));
			temp->addChild((yyvsp[-3].symbolInfo));
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			temp->setReturnType((yyvsp[-4].symbolInfo)->getDataType());
			//symbolTable->insert($2->getName(),"FUNCTION",$1->getDataType(),line_count,error_out);
			(yyval.symbolInfo) = temp;
			printInLog(temp->getRule());
		}
#line 1971 "y.tab.c"
    break;

  case 18: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN compound_statement  */
#line 296 "2005042.y"
                                                                                   {
					SymbolInfo *temp=new SymbolInfo((yyvsp[-4].symbolInfo)->getName(),"func_definition");
					temp->setRule("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
					temp->addChild((yyvsp[-5].symbolInfo));
					temp->addChild((yyvsp[-4].symbolInfo));
					temp->addChild((yyvsp[-3].symbolInfo));
					temp->addChild((yyvsp[-2].symbolInfo));
					temp->addChild((yyvsp[-1].symbolInfo));
					temp->addChild((yyvsp[0].symbolInfo));
					temp->addParameterList((yyvsp[-2].symbolInfo)->getParameterList());
					temp->setReturnType((yyvsp[-5].symbolInfo)->getDataType());
					if((yyvsp[-2].symbolInfo)->getName()=="error"){
						printError("Syntax error","parameter list","function definition",(yyvsp[-2].symbolInfo)->getStartLine());
					}
					//symbolTable->insert($2->getName(),"FUNCTION",$1->getDataType(),line_count,error_out);
					(yyval.symbolInfo)=temp;
					printInLog(temp->getRule());
				}
#line 1994 "y.tab.c"
    break;

  case 19: /* func_definition: type_specifier ID LPAREN RPAREN compound_statement  */
#line 315 "2005042.y"
                                                                    {
					SymbolInfo *temp=new SymbolInfo((yyvsp[-3].symbolInfo)->getName(),"func_definition");
					temp->setRule("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
					temp->addChild((yyvsp[-4].symbolInfo));
					temp->addChild((yyvsp[-3].symbolInfo));
					temp->addChild((yyvsp[-2].symbolInfo));
					temp->addChild((yyvsp[-1].symbolInfo));
					temp->addChild((yyvsp[0].symbolInfo));
					cout<<"here"<<line_count<<"\n";
					temp->setReturnType((yyvsp[-4].symbolInfo)->getDataType());
					//symbolTable->insert($2->getName(),"FUNCTION",$1->getDataType(),line_count,error_out);
					//symbolTable->enterScope();
					//insertAll($1->getDataType(),$5);
					//symbolTable->printAllScope(logout);
					//symbolTable->exitScope();
					(yyval.symbolInfo)=temp;
					printInLog(temp->getRule());
				}
#line 2017 "y.tab.c"
    break;

  case 20: /* func_definition: error  */
#line 333 "2005042.y"
                      {
			yyclearin;
			SymbolInfo *temp=new SymbolInfo("error","func_definition");
			temp->setRule("func_definition : error");
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		}
#line 2029 "y.tab.c"
    break;

  case 21: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 343 "2005042.y"
                                                        {
			SymbolInfo *temp = new SymbolInfo("Node","parameter_list");
			temp->setRule("parameter_list : parameter_list COMMA type_specifier ID");
			temp->addChild((yyvsp[-3].symbolInfo));
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			temp->addParameterList((yyvsp[-3].symbolInfo)->getParameterList());
			Parameter *p=new Parameter((yyvsp[0].symbolInfo)->getName(),(yyvsp[-1].symbolInfo)->getType());
			temp->addParameterList(p);
			//func_parameters=temp;
			//logout<<"here\n";
			(yyval.symbolInfo) = temp;
			printInLog(temp->getRule());
		}
#line 2049 "y.tab.c"
    break;

  case 22: /* parameter_list: parameter_list COMMA type_specifier  */
#line 358 "2005042.y"
                                                     {
			SymbolInfo *temp = new SymbolInfo("Node","parameter_list");
			temp->setRule("parameter_list : parameter_list COMMA type_specifier");
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			temp->addParameterList((yyvsp[-2].symbolInfo)->getParameterList());
			Parameter *p=new Parameter((yyvsp[0].symbolInfo)->getName(),(yyvsp[0].symbolInfo)->getType());
			temp->addParameterList(p);
			//func_parameters=temp;
			(yyval.symbolInfo) = temp;
			printInLog(temp->getRule());
		}
#line 2067 "y.tab.c"
    break;

  case 23: /* parameter_list: type_specifier ID  */
#line 371 "2005042.y"
                                   {
			SymbolInfo *temp = new SymbolInfo("Node","parameter_list");
			temp->setRule("parameter_list : type_specifier ID");
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			Parameter *p=new Parameter((yyvsp[0].symbolInfo)->getName(),(yyvsp[-1].symbolInfo)->getType());
			temp->addParameterList(p);
			(yyval.symbolInfo) = temp;
			//func_parameters=temp;
			printInLog(temp->getRule());
		}
#line 2083 "y.tab.c"
    break;

  case 24: /* parameter_list: type_specifier  */
#line 382 "2005042.y"
                                {
			SymbolInfo *temp = new SymbolInfo("Node","parameter_list");
			temp->setRule("parameter_list : type_specifier");
			temp->addChild((yyvsp[0].symbolInfo));
			Parameter *p=new Parameter((yyvsp[0].symbolInfo)->getName(),(yyvsp[0].symbolInfo)->getType());
			temp->addParameterList(p);
			(yyval.symbolInfo) = temp;
			//func_parameters=temp;
			printInLog(temp->getRule());
		}
#line 2098 "y.tab.c"
    break;

  case 25: /* parameter_list: error  */
#line 392 "2005042.y"
                       {
			yyclearin;
			SymbolInfo *temp=new SymbolInfo("error","parameter_list",line_count);
			temp->setRule("parameter_list : error");
			(yyval.symbolInfo)=temp;
		}
#line 2109 "y.tab.c"
    break;

  case 26: /* compound_statement: LCURL statements RCURL  */
#line 400 "2005042.y"
                                           {
				SymbolInfo *temp = new SymbolInfo("Leaf","compound_statement");
				temp->setRule("compound_statement : LCURL statements RCURL");
				temp->addChild((yyvsp[-2].symbolInfo));
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo) = temp;
				// symbolTable->copyScope(scopetable,logout);
				//scopetable=new ScopeTable(BUCKET_SIZE,NULL);
				printInLog(temp->getRule());
				symbolTable->printAllScope(logout);
				symbolTable->exitScope();
			}
#line 2127 "y.tab.c"
    break;

  case 27: /* compound_statement: LCURL RCURL  */
#line 413 "2005042.y"
                                 {
				SymbolInfo *temp = new SymbolInfo("Leaf","compound_statement");
				//symbolTable->enterScope();
				symbolTable->insert("NN","INT","",line_count,logout);
				temp->setRule("compound_statement : LCURL RCURL");
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo) = temp;
				printInLog(temp->getRule());
				symbolTable->printAllScope(logout);
				symbolTable->exitScope();
			}
#line 2144 "y.tab.c"
    break;

  case 28: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 427 "2005042.y"
                                                           {
				SymbolInfo *temp=new SymbolInfo("Node","var_declaration",(yyvsp[-2].symbolInfo)->getType());
				temp->setRule("var_declaration : type_specifier declaration_list SEMICOLON");
				temp->addChild((yyvsp[-2].symbolInfo));
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				insertAll((yyvsp[-2].symbolInfo)->getDataType(),(yyvsp[-1].symbolInfo));
				(yyval.symbolInfo) = temp;
				printInLog(temp->getRule());
			}
#line 2159 "y.tab.c"
    break;

  case 29: /* var_declaration: type_specifier declaration_list error SEMICOLON  */
#line 437 "2005042.y"
                                                                        {
				SymbolInfo *temp=new SymbolInfo("error","var_declaration");
				temp->setRule("var_declaration : type_specifier declaration");
				(yyval.symbolInfo)=temp;
				printError("Syntax","declaration list","var_declaration",line_count);
			}
#line 2170 "y.tab.c"
    break;

  case 30: /* type_specifier: INT  */
#line 445 "2005042.y"
                     {
					(yyval.symbolInfo)=new SymbolInfo("Node","type_specifier","int");
					(yyval.symbolInfo)->setRule("type_specifier	: INT");
					(yyval.symbolInfo)->addChild((yyvsp[0].symbolInfo));
					printInLog((yyval.symbolInfo)->getRule());
				}
#line 2181 "y.tab.c"
    break;

  case 31: /* type_specifier: FLOAT  */
#line 451 "2005042.y"
                                       {
					(yyval.symbolInfo)=new SymbolInfo("Node","type_specifier","float");
					(yyval.symbolInfo)->setRule("type_specifier	: FLOAT");
					(yyval.symbolInfo)->addChild((yyvsp[0].symbolInfo));
					printInLog((yyval.symbolInfo)->getRule());
				}
#line 2192 "y.tab.c"
    break;

  case 32: /* type_specifier: VOID  */
#line 457 "2005042.y"
                                      {
					(yyval.symbolInfo)=new SymbolInfo("Node","type_specifier","VOID");
					(yyval.symbolInfo)->setRule("type_specifier	: VOID");
					(yyval.symbolInfo)->addChild((yyvsp[0].symbolInfo));
					printInLog((yyval.symbolInfo)->getRule());
				}
#line 2203 "y.tab.c"
    break;

  case 33: /* declaration_list: declaration_list COMMA ID  */
#line 465 "2005042.y"
                                            {
							SymbolInfo *temp=new SymbolInfo("Node","declaration_list");
							temp->setRule("declaration_list : declaration_list COMMA ID");
							temp->addParameterList((yyvsp[-2].symbolInfo)->getParameterList());
							Parameter *p=new Parameter((yyvsp[0].symbolInfo)->getName(),(yyvsp[0].symbolInfo)->getType());
							temp->addParameterList(p);
							//cout<<$3->getName()<<endl;
							//temp->printParameter(logout);
							temp->addChild((yyvsp[-2].symbolInfo));
							temp->addChild((yyvsp[-1].symbolInfo));
							temp->addChild((yyvsp[0].symbolInfo));
							(yyval.symbolInfo)=temp;
							printInLog((yyval.symbolInfo)->getRule());
						}
#line 2222 "y.tab.c"
    break;

  case 34: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 479 "2005042.y"
                                                                     {
				SymbolInfo *temp=new SymbolInfo("Node","declaration_list");
				temp->setRule("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
				temp->addParameterList((yyvsp[-5].symbolInfo)->getParameterList());
				Parameter *p=new Parameter((yyvsp[-3].symbolInfo)->getName(),(yyvsp[-3].symbolInfo)->getType());
				p->setIsArray();
				p->setArraySize(stoi((yyvsp[-1].symbolInfo)->getName()));
				//cout<<stoi($5->getName())<<"he2\n";

				temp->addParameterList(p);
				temp->addChild((yyvsp[-5].symbolInfo));
				temp->addChild((yyvsp[-4].symbolInfo));
				temp->addChild((yyvsp[-3].symbolInfo));
				temp->addChild((yyvsp[-2].symbolInfo));
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog((yyval.symbolInfo)->getRule());
		  }
#line 2246 "y.tab.c"
    break;

  case 35: /* declaration_list: ID  */
#line 498 "2005042.y"
                      {
				SymbolInfo *temp=new SymbolInfo("Node","declaration_list");
				//logout<<$1->getName()<<'\n';
				Parameter *p=new Parameter((yyvsp[0].symbolInfo)->getName(),(yyvsp[0].symbolInfo)->getType());
				temp->addParameterList(p);
				//logout<<"here\n";
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				(yyval.symbolInfo)->setRule("declaration_list : ID");
				printInLog((yyval.symbolInfo)->getRule());
		  }
#line 2262 "y.tab.c"
    break;

  case 36: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 509 "2005042.y"
                                              {
				SymbolInfo *s=new SymbolInfo("array","declaration_list");
				Parameter *temp=new Parameter((yyvsp[-3].symbolInfo)->getName(),(yyvsp[-3].symbolInfo)->getType());
				temp->setIsArray();
				//cout<<$3->getName()<<"he\n";
				temp->setArraySize(stoi((yyvsp[-1].symbolInfo)->getName()));
				s->addParameterList(temp);
				s->setRule("declaration_list : ID LTHIRD CONST_INT RTHIRD");
				s->addChild((yyvsp[-3].symbolInfo));
				s->addChild((yyvsp[-2].symbolInfo));
				s->addChild((yyvsp[-1].symbolInfo));
				s->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=s;
				printInLog(s->getRule());
		  }
#line 2282 "y.tab.c"
    break;

  case 37: /* declaration_list: error  */
#line 524 "2005042.y"
                        {
			yyclearin;
			SymbolInfo *temp=new SymbolInfo("error","declaration_list");
			temp->setRule("declaration_list : error");
			//temp->addChild($1);
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule()); 
		  }
#line 2295 "y.tab.c"
    break;

  case 38: /* statements: statement  */
#line 534 "2005042.y"
                      {
			SymbolInfo *temp=new SymbolInfo("Node","statements");
			temp->setRule("statements : statement");
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		}
#line 2307 "y.tab.c"
    break;

  case 39: /* statements: statements statement  */
#line 541 "2005042.y"
                                 {
			SymbolInfo *temp=new SymbolInfo("Node","statements");
			temp->setRule("statements : statements statement");
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		}
#line 2320 "y.tab.c"
    break;

  case 40: /* statement: var_declaration  */
#line 551 "2005042.y"
                           {
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement : var_declaration");
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
			}
#line 2332 "y.tab.c"
    break;

  case 41: /* statement: expression_statement  */
#line 558 "2005042.y"
                                {
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement : expression_statement");
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
			}
#line 2344 "y.tab.c"
    break;

  case 42: /* statement: compound_statement  */
#line 565 "2005042.y"
                              {
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement : compound_statement");
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
			}
#line 2356 "y.tab.c"
    break;

  case 43: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 572 "2005042.y"
                                                                                            {
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
				temp->addChild((yyvsp[-6].symbolInfo));
				temp->addChild((yyvsp[-5].symbolInfo));
				temp->addChild((yyvsp[-4].symbolInfo));
				temp->addChild((yyvsp[-3].symbolInfo));
				temp->addChild((yyvsp[-2].symbolInfo));
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
		}
#line 2374 "y.tab.c"
    break;

  case 44: /* statement: IF LPAREN expression RPAREN statement  */
#line 585 "2005042.y"
                                                 {
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement : IF LPAREN expression RPAREN statement");
				temp->addChild((yyvsp[-4].symbolInfo));
				temp->addChild((yyvsp[-3].symbolInfo));
				temp->addChild((yyvsp[-2].symbolInfo));
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
		}
#line 2390 "y.tab.c"
    break;

  case 45: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 596 "2005042.y"
                                                                {
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement : IF LPAREN expression RPAREN statement ELSE statement");
				temp->addChild((yyvsp[-6].symbolInfo));
				temp->addChild((yyvsp[-5].symbolInfo));
				temp->addChild((yyvsp[-4].symbolInfo));
				temp->addChild((yyvsp[-3].symbolInfo));
				temp->addChild((yyvsp[-2].symbolInfo));
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
		}
#line 2408 "y.tab.c"
    break;

  case 46: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 609 "2005042.y"
                                                    {
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement : WHILE LPAREN expression RPAREN statement");
				temp->addChild((yyvsp[-4].symbolInfo));
				temp->addChild((yyvsp[-3].symbolInfo));
				temp->addChild((yyvsp[-2].symbolInfo));
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
		}
#line 2424 "y.tab.c"
    break;

  case 47: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 620 "2005042.y"
                                              {
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
				temp->addChild((yyvsp[-4].symbolInfo));
				temp->addChild((yyvsp[-3].symbolInfo));
				temp->addChild((yyvsp[-2].symbolInfo));
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
		}
#line 2440 "y.tab.c"
    break;

  case 48: /* statement: RETURN expression SEMICOLON  */
#line 631 "2005042.y"
                                       {
				SymbolInfo *temp=new SymbolInfo("Node","statement");
				temp->setRule("statement : RETURN expression SEMICOLON");
				temp->addChild((yyvsp[-2].symbolInfo));
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
		}
#line 2454 "y.tab.c"
    break;

  case 49: /* expression_statement: SEMICOLON  */
#line 642 "2005042.y"
                                   {
				SymbolInfo *temp=new SymbolInfo("Leaf","expression_statement");
				temp->setRule("expression_statement : SEMICOLON");
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
			}
#line 2466 "y.tab.c"
    break;

  case 50: /* expression_statement: expression SEMICOLON  */
#line 649 "2005042.y"
                                               {
				SymbolInfo *temp=new SymbolInfo("Leaf","expression_statement");
				temp->setRule("expression_statement : expression SEMICOLON");
				temp->addChild((yyvsp[-1].symbolInfo));
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
			}
#line 2479 "y.tab.c"
    break;

  case 51: /* variable: ID  */
#line 659 "2005042.y"
              {
			SymbolInfo *temp=new SymbolInfo((yyvsp[0].symbolInfo)->getName(),"variable");
			temp->setRule("variable : ID");
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
			symbolTable->lookup((yyvsp[0].symbolInfo)->getName(),line_count,error_out);
		}
#line 2492 "y.tab.c"
    break;

  case 52: /* variable: ID LTHIRD expression RTHIRD  */
#line 667 "2005042.y"
                                       {
			SymbolInfo *temp=new SymbolInfo((yyvsp[-3].symbolInfo)->getName(),"variable","array");
			temp->setRule("variable : ID LTHIRD expression RTHIRD");
			temp->addChild((yyvsp[-3].symbolInfo));
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
			if((yyvsp[-1].symbolInfo)->getName()=="error"){
				printError("Invalid index","expression","array declaration",line_count);
			}
			symbolTable->lookup((yyvsp[-3].symbolInfo)->getName(),line_count,error_out);
		}
#line 2511 "y.tab.c"
    break;

  case 53: /* expression: logic_expression  */
#line 682 "2005042.y"
                              {
			SymbolInfo *temp=new SymbolInfo("Node","expression");
			temp->setRule("expression : logic_expression");
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		 }
#line 2523 "y.tab.c"
    break;

  case 54: /* expression: variable ASSIGNOP logic_expression  */
#line 689 "2005042.y"
                                               {
			SymbolInfo *temp=new SymbolInfo("Node","expression");
			temp->setRule("expression : variable ASSIGNOP logic_expression");
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		 }
#line 2537 "y.tab.c"
    break;

  case 55: /* expression: error  */
#line 698 "2005042.y"
                       {
			yyclearin;
			SymbolInfo *temp=new SymbolInfo("error","expression");
			temp->setRule("expression : error");
			temp->setStartLine(line_count);
			(yyval.symbolInfo)=temp;
		}
#line 2549 "y.tab.c"
    break;

  case 56: /* logic_expression: rel_expression  */
#line 707 "2005042.y"
                                 {
			SymbolInfo *temp=new SymbolInfo("Node","logic_expression");
			temp->setRule("logic_expression : rel_expression");
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		 }
#line 2561 "y.tab.c"
    break;

  case 57: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 714 "2005042.y"
                                                         {
			SymbolInfo *temp=new SymbolInfo("Node","logic_expression");
			temp->setRule("logic_expression : rel_expression LOGICOP rel_expression");
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		 }
#line 2575 "y.tab.c"
    break;

  case 58: /* rel_expression: simple_expression  */
#line 725 "2005042.y"
                                    {
			SymbolInfo *temp=new SymbolInfo("Node","simple_expression");
			temp->setRule("rel_expression : simple_expression");
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		}
#line 2587 "y.tab.c"
    break;

  case 59: /* rel_expression: simple_expression RELOP simple_expression  */
#line 732 "2005042.y"
                                                                {
			SymbolInfo *temp=new SymbolInfo("Node","simple_expression");
			temp->setRule("rel_expression : simple_expression RELOP simple_expression");
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		}
#line 2601 "y.tab.c"
    break;

  case 60: /* simple_expression: term  */
#line 743 "2005042.y"
                         {
			SymbolInfo *temp= new SymbolInfo("Node","simple_expression");
			temp->setRule("simple_expression : term");
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo) = temp;
			printInLog(temp->getRule());
		  }
#line 2613 "y.tab.c"
    break;

  case 61: /* simple_expression: simple_expression ADDOP term  */
#line 750 "2005042.y"
                                                 {
			SymbolInfo *temp= new SymbolInfo("Node","simple_expression");
			temp->setRule("simple_expression : simple_expression ADDOP term");
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo) = temp;
			printInLog(temp->getRule());
		  }
#line 2627 "y.tab.c"
    break;

  case 62: /* term: unary_expression  */
#line 761 "2005042.y"
                        {
		SymbolInfo *temp=new SymbolInfo("Node","term");
		temp->setRule("term : unary_expression");
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)=temp;
		printInLog(temp->getRule());
	}
#line 2639 "y.tab.c"
    break;

  case 63: /* term: term MULOP unary_expression  */
#line 768 "2005042.y"
                                   {
		SymbolInfo *temp=new SymbolInfo("Node","term");
		temp->setRule("term : term MULOP unary_expression");
		temp->addChild((yyvsp[-2].symbolInfo));
		temp->addChild((yyvsp[-1].symbolInfo));
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)=temp;
		printInLog(temp->getRule());
	 }
#line 2653 "y.tab.c"
    break;

  case 64: /* unary_expression: ADDOP unary_expression  */
#line 779 "2005042.y"
                                         {
			SymbolInfo *temp=new SymbolInfo("Node","unary_expression");
			temp->setRule("unary_expression : ADDOP unary_expression");
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		 }
#line 2666 "y.tab.c"
    break;

  case 65: /* unary_expression: NOT unary_expression  */
#line 787 "2005042.y"
                                        {
			SymbolInfo *temp=new SymbolInfo("Node","unary_expression");
			temp->setRule("unary_expression : NOT unary_expression");
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		 }
#line 2679 "y.tab.c"
    break;

  case 66: /* unary_expression: factor  */
#line 795 "2005042.y"
                          {
			SymbolInfo *temp=new SymbolInfo("Node","unary_expression");
			temp->setRule("unary_expression : factor");
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		 }
#line 2691 "y.tab.c"
    break;

  case 67: /* factor: variable  */
#line 804 "2005042.y"
                   {
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : variable");
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)=temp;
		printInLog(temp->getRule());
	}
#line 2703 "y.tab.c"
    break;

  case 68: /* factor: ID LPAREN argument_list RPAREN  */
#line 811 "2005042.y"
                                        {
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : ID LPAREN argument_list RPAREN");
		temp->addChild((yyvsp[-3].symbolInfo));
		temp->addChild((yyvsp[-2].symbolInfo));
		temp->addChild((yyvsp[-1].symbolInfo));
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo) = temp;
		printInLog(temp->getRule());
	}
#line 2718 "y.tab.c"
    break;

  case 69: /* factor: LPAREN expression RPAREN  */
#line 821 "2005042.y"
                                  {
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : LPAREN expression RPAREN")	;
		temp->addChild((yyvsp[-2].symbolInfo));
		temp->addChild((yyvsp[-1].symbolInfo));
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo) = temp;
		printInLog(temp->getRule());
	}
#line 2732 "y.tab.c"
    break;

  case 70: /* factor: CONST_INT  */
#line 830 "2005042.y"
                    {
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : CONST_INT")	;
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo) = temp;
		printInLog(temp->getRule());
	}
#line 2744 "y.tab.c"
    break;

  case 71: /* factor: CONST_FLOAT  */
#line 837 "2005042.y"
                     {
		SymbolInfo *temp=new SymbolInfo("Node","factor");	
		temp->setRule("factor : CONST_FLOAT")	;
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo) = temp;
		printInLog(temp->getRule());
	}
#line 2756 "y.tab.c"
    break;

  case 72: /* factor: variable INCOP  */
#line 844 "2005042.y"
                        {
		SymbolInfo *temp = new SymbolInfo("Node", "factor");
		temp->setRule("factor : variable INCOP");
		temp->addChild((yyvsp[-1].symbolInfo));
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)=temp;
		printInLog(temp->getRule());
	}
#line 2769 "y.tab.c"
    break;

  case 73: /* factor: variable DECOP  */
#line 852 "2005042.y"
                        {
		SymbolInfo *temp = new SymbolInfo("Node", "factor");
		temp->setRule("factor : variable DECOP");
		temp->addChild((yyvsp[-1].symbolInfo));
		temp->addChild((yyvsp[0].symbolInfo));
		(yyval.symbolInfo)=temp;
		printInLog(temp->getRule());
	}
#line 2782 "y.tab.c"
    break;

  case 74: /* argument_list: arguments  */
#line 862 "2005042.y"
                         {
				SymbolInfo *temp=new SymbolInfo("Leaf","argument_list");
				temp->setRule("argument_list: arguments");
				temp->addChild((yyvsp[0].symbolInfo));
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
			  }
#line 2794 "y.tab.c"
    break;

  case 75: /* argument_list: %empty  */
#line 869 "2005042.y"
                           {
				SymbolInfo *temp=new SymbolInfo("Leaf","argument_list",line_count);
				temp->setEndLine(line_count);
				temp->setRule("argument_list: ");
				(yyval.symbolInfo)=temp;
				printInLog(temp->getRule());
				
			  }
#line 2807 "y.tab.c"
    break;

  case 76: /* argument_list: error  */
#line 877 "2005042.y"
                                {
				yyclearin;
				SymbolInfo *temp=new SymbolInfo("error","argument_list");
				temp->setRule("argument_list : error");
				(yyval.symbolInfo)=temp;

			  }
#line 2819 "y.tab.c"
    break;

  case 77: /* arguments: arguments COMMA logic_expression  */
#line 886 "2005042.y"
                                            {
			SymbolInfo *temp = new SymbolInfo("Node","arguments");
			temp->setRule("arguments : arguments COMMA logic_expression");
			temp->addChild((yyvsp[-2].symbolInfo));
			temp->addChild((yyvsp[-1].symbolInfo));
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		  }
#line 2833 "y.tab.c"
    break;

  case 78: /* arguments: logic_expression  */
#line 895 "2005042.y"
                                {
			SymbolInfo *temp = new SymbolInfo("Node","arguments");
			temp->setRule("arguments : logic_expression");
			temp->addChild((yyvsp[0].symbolInfo));
			(yyval.symbolInfo)=temp;
			printInLog(temp->getRule());
		  }
#line 2845 "y.tab.c"
    break;


#line 2849 "y.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 905 "2005042.y"

int main(int argc,char *argv[])
{
	FILE *fp;
	if((fp=fopen(argv[1],"r"))==NULL)
	{
		printf("Cannot Open Input File.\n");
		exit(1);
	}
	symbolTable=new SymbolTable(BUCKET_SIZE);
	parsetree_out.open("2005042_parseTree.txt");
	logout.open("2005042_log.txt");
	error_out.open("2005042_error.txt");
	asm_out.open("2005042_code.asm");
	scopetable=new ScopeTable(BUCKET_SIZE,NULL);
	yyin=fp;
	yyparse();
	cout<<"hello\n";
	//symbolTable->printAllScope(logout);
	delete symbolTable; 
	
	logout<< "Total Lines: " << line_count << '\n';
	logout<< "Total Errors: " << error_count << '\n';
	fclose(fp);
	parsetree_out.close();
	error_out.close();
	logout.close();
	return 0;
}

