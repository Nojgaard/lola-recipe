/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 1

/* Substitute the variable and function names.  */
#define yyparse ptformula_parse
#define yylex   ptformula_lex
#define yyerror ptformula_error
#define yylval  ptformula_lval
#define yychar  ptformula_char
#define yydebug ptformula_debug
#define yynerrs ptformula_nerrs
#define yylloc ptformula_lloc

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     END = 0,
     _CTLOPERATOR_ = 258,
     IDENTIFIER = 259,
     NUMBER = 260,
     _RELEASE_ = 261,
     _NEXTSTATE_ = 262,
     _INITIAL_ = 263,
     _DEADLOCK_ = 264,
     _FORMULA_ = 265,
     _AND_ = 266,
     _NOT_ = 267,
     _OR_ = 268,
     _XOR_ = 269,
     _iff_ = 270,
     _ALLPATH_ = 271,
     _ALWAYS_ = 272,
     _EVENTUALLY_ = 273,
     _EXPATH_ = 274,
     _UNTIL_ = 275,
     _REACHABLE_ = 276,
     _INVARIANT_ = 277,
     _IMPOSSIBLE_ = 278,
     _notequal_ = 279,
     _implies_ = 280,
     _equals_ = 281,
     _plus_ = 282,
     _minus_ = 283,
     _times_ = 284,
     _leftparenthesis_ = 285,
     _rightparenthesis_ = 286,
     _greaterthan_ = 287,
     _lessthan_ = 288,
     _greaterorequal_ = 289,
     _lessorequal_ = 290,
     _semicolon_ = 291,
     _TRUE_ = 292,
     _FALSE_ = 293,
     _FIREABLE_ = 294,
     _omega_ = 295
   };
#endif
/* Tokens.  */
#define END 0
#define _CTLOPERATOR_ 258
#define IDENTIFIER 259
#define NUMBER 260
#define _RELEASE_ 261
#define _NEXTSTATE_ 262
#define _INITIAL_ 263
#define _DEADLOCK_ 264
#define _FORMULA_ 265
#define _AND_ 266
#define _NOT_ 267
#define _OR_ 268
#define _XOR_ 269
#define _iff_ 270
#define _ALLPATH_ 271
#define _ALWAYS_ 272
#define _EVENTUALLY_ 273
#define _EXPATH_ 274
#define _UNTIL_ 275
#define _REACHABLE_ 276
#define _INVARIANT_ 277
#define _IMPOSSIBLE_ 278
#define _notequal_ 279
#define _implies_ 280
#define _equals_ 281
#define _plus_ 282
#define _minus_ 283
#define _times_ 284
#define _leftparenthesis_ 285
#define _rightparenthesis_ 286
#define _greaterthan_ 287
#define _lessthan_ 288
#define _greaterorequal_ 289
#define _lessorequal_ 290
#define _semicolon_ 291
#define _TRUE_ 292
#define _FALSE_ 293
#define _FIREABLE_ 294
#define _omega_ 295




/* Copy the first part of user declarations.  */
#line 28 "Frontend/Parser/ParserFormula.yy"

#include <config.h>
#include <Core/Dimensions.h>
#include <CoverGraph/CoverGraph.h>
#include <Frontend/SymbolTable/ArcList.h>
#include <Frontend/SymbolTable/PlaceSymbol.h>
#include <Frontend/SymbolTable/TransitionSymbol.h>
#include <Frontend/SymbolTable/SymbolTable.h>
#include <Frontend/Parser/ParserPTNet.h>
#include <Frontend/Parser/error.h>
#include <Frontend/Parser/ast-system-k.h>
#include <Frontend/Parser/ast-system-yystype.h>
#include <Net/Net.h>

#include <limits.h>
#include <libgen.h>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <set>


extern ParserPTNet* symbolTables;
#line 120 "Frontend/Parser/ParserFormula.yy"

// parser essentials
extern int ptformula_lex();
void ptformula_error(char const*);

extern YYSTYPE ptformula_lval;

std::set<arrayindex_t> target_place;
std::set<arrayindex_t> target_transition;
#line 131 "Frontend/Parser/ParserFormula.yy"

/* globals */
tFormula TheFormula;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 247 "Frontend/Parser/ParserFormula.cc"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
    YYLTYPE yyls;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   190

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  6
/* YYNRULES -- Number of rules.  */
#define YYNRULES  45
/* YYNRULES -- Number of states.  */
#define YYNSTATES  87

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     7,    10,    12,    15,    19,    21,    24,
      28,    32,    36,    40,    44,    47,    50,    53,    56,    59,
      65,    71,    77,    80,    83,    86,    89,    93,    97,   101,
     105,   109,   113,   115,   117,   122,   124,   126,   130,   132,
     134,   138,   142,   146,   148,   150
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    10,    43,    36,    -1,    10,    43,    -1,
      43,    -1,    43,    36,    -1,    30,    43,    31,    -1,    44,
      -1,    12,    43,    -1,    43,    11,    43,    -1,    43,    13,
      43,    -1,    43,    14,    43,    -1,    43,    25,    43,    -1,
      43,    15,    43,    -1,    16,    43,    -1,    19,    43,    -1,
      17,    43,    -1,    18,    43,    -1,     3,    43,    -1,    30,
      43,    20,    43,    31,    -1,    30,    43,     6,    43,    31,
      -1,    30,    43,     3,    43,    31,    -1,     7,    43,    -1,
      21,    43,    -1,    22,    43,    -1,    23,    43,    -1,    45,
      26,    45,    -1,    45,    24,    45,    -1,    45,    32,    45,
      -1,    45,    34,    45,    -1,    45,    33,    45,    -1,    45,
      35,    45,    -1,    37,    -1,    38,    -1,    39,    30,    46,
      31,    -1,     8,    -1,     9,    -1,    30,    45,    31,    -1,
      46,    -1,     5,    -1,    45,    27,    45,    -1,    45,    28,
      45,    -1,     5,    29,    45,    -1,    40,    -1,     4,    -1,
       3,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   139,   139,   141,   143,   145,   150,   152,   154,   156,
     158,   160,   162,   164,   166,   168,   170,   172,   174,   190,
     192,   194,   205,   207,   209,   211,   216,   218,   220,   222,
     224,   226,   228,   230,   232,   242,   244,   249,   251,   261,
     263,   265,   267,   269,   281,   282
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "\"CTL* operator\"",
  "\"identifier\"", "\"number\"", "\"temporal operator RELEASE\"",
  "\"temporal operator NEXTSTATE\"", "\"keyword INITIAL\"",
  "\"keyword DEADLOCK\"", "\"keyword FORMULA\"", "\"Boolean conjuction\"",
  "\"Boolean negation\"", "\"Boolean disjunction\"",
  "\"Boolean exclusive disjunction\"", "\"Boolean iff\"",
  "\"path quantifier ALLPATH\"", "\"temporal operator ALWAYS\"",
  "\"temporal operator EVENTUALLY\"", "\"path quantifier EXPATH\"",
  "\"temporal operator UNTIL\"", "\"keyword REACHABLE\"",
  "\"keyword INVARIANT\"", "\"keyword IMPOSSIBLE\"", "\"not-equals sign\"",
  "\"Boolean implication\"", "\"equals sign\"", "\"plus sign\"",
  "\"minus sign\"", "\"multiplication sign\"", "\"opening parenthesis\"",
  "\"closing parenthesis\"", "\"greater-than sign\"", "\"less-than sign\"",
  "\"greater-than-or-equal sign\"", "\"less-than-or-equal sign\"",
  "\"semicolon\"", "\"Boolean TRUE\"", "\"Boolean FALSE\"",
  "\"keyword FIREABLE\"", "\"omega\"", "$accept", "formula",
  "statepredicate", "atomic_proposition", "term", "identifier", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    42,    42,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    44,    44,    44,
      44,    44,    44,    44,    44,    44,    44,    45,    45,    45,
      45,    45,    45,    45,    46,    46
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     2,     1,     2,     3,     1,     2,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     2,     5,
       5,     5,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     1,     1,     4,     1,     1,     3,     1,     1,
       3,     3,     3,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    45,    44,    39,     0,    35,    36,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    32,    33,     0,
      43,     0,     4,     7,     0,    38,    18,     0,    22,     3,
       8,    14,    16,    17,    15,    23,    24,    25,     0,     0,
       0,     1,     0,     0,     0,     0,     0,     5,     0,     0,
       0,     0,     0,     0,     0,     0,    45,     0,    42,     2,
       0,     0,     0,     6,    37,     0,     9,    10,    11,    13,
      12,    27,    26,    40,    41,    28,    30,    29,    31,     0,
       0,     0,     0,    34,    21,    20,    19
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    21,    22,    23,    24,    25
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -27
static const yytype_int16 yypact[] =
{
      59,    97,   -27,   -25,    97,   -27,   -27,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,   -27,   -27,   -13,
     -27,    23,    11,   -27,     5,   -27,   -27,    16,   -27,   131,
     -27,   -27,   -27,   -27,   -27,   -27,   -27,   -27,   118,   154,
      31,   -27,    97,    97,    97,    97,    97,   -27,    16,    16,
      16,    16,    16,    16,    16,    16,   -27,    16,   -27,   -27,
      97,    97,    97,   -27,   -27,    27,     3,    68,    68,   -27,
      15,    45,    45,   -27,   -27,    45,    45,    45,    45,   -26,
     137,   144,   159,   -27,   -27,   -27,   -27
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -27,   -27,    -1,   -27,     0,    25
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      26,    50,    51,    28,    27,    64,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    45,    56,
       2,     3,    42,    41,    43,    44,    45,    58,    46,    48,
      45,    49,    50,    51,    56,     2,    46,    52,    53,    54,
      55,    66,    67,    68,    69,    70,    57,    47,    71,    72,
      73,    74,    75,    76,    77,    78,    20,    79,    83,    80,
      81,    82,     1,     2,     3,    65,     4,     5,     6,     7,
       0,     8,    50,    51,     0,     9,    10,    11,    12,    42,
      13,    14,    15,    45,     0,     0,     0,     0,     0,    16,
       0,     0,     0,    46,     0,     0,    17,    18,    19,    20,
       1,     2,     3,     0,     4,     5,     6,     0,     0,     8,
       0,     0,     0,     9,    10,    11,    12,     0,    13,    14,
      15,    60,     0,     0,    61,     0,     0,    16,     0,    42,
       0,    43,    44,    45,    17,    18,    19,    20,    62,     0,
       0,     0,    42,    46,    43,    44,    45,     0,    42,    63,
      43,    44,    45,     0,     0,    42,    46,    43,    44,    45,
       0,     0,    46,     0,     0,     0,     0,    59,    84,    46,
      42,     0,    43,    44,    45,    85,     0,     0,    48,     0,
      49,    50,    51,     0,    46,    64,    52,    53,    54,    55,
      86
};

static const yytype_int8 yycheck[] =
{
       1,    27,    28,     4,    29,    31,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    16,    30,    15,     3,
       4,     5,    11,     0,    13,    14,    15,    27,    25,    24,
      15,    26,    27,    28,     3,     4,    25,    32,    33,    34,
      35,    42,    43,    44,    45,    46,    30,    36,    48,    49,
      50,    51,    52,    53,    54,    55,    40,    57,    31,    60,
      61,    62,     3,     4,     5,    40,     7,     8,     9,    10,
      -1,    12,    27,    28,    -1,    16,    17,    18,    19,    11,
      21,    22,    23,    15,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    -1,    25,    -1,    -1,    37,    38,    39,    40,
       3,     4,     5,    -1,     7,     8,     9,    -1,    -1,    12,
      -1,    -1,    -1,    16,    17,    18,    19,    -1,    21,    22,
      23,     3,    -1,    -1,     6,    -1,    -1,    30,    -1,    11,
      -1,    13,    14,    15,    37,    38,    39,    40,    20,    -1,
      -1,    -1,    11,    25,    13,    14,    15,    -1,    11,    31,
      13,    14,    15,    -1,    -1,    11,    25,    13,    14,    15,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    36,    31,    25,
      11,    -1,    13,    14,    15,    31,    -1,    -1,    24,    -1,
      26,    27,    28,    -1,    25,    31,    32,    33,    34,    35,
      31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     7,     8,     9,    10,    12,    16,
      17,    18,    19,    21,    22,    23,    30,    37,    38,    39,
      40,    42,    43,    44,    45,    46,    43,    29,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    45,
      30,     0,    11,    13,    14,    15,    25,    36,    24,    26,
      27,    28,    32,    33,    34,    35,     3,    30,    45,    36,
       3,     6,    20,    31,    31,    46,    43,    43,    43,    43,
      43,    45,    45,    45,    45,    45,    45,    45,    45,    45,
      43,    43,    43,    31,    31,    31,    31
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;
/* Location data for the look-ahead symbol.  */
YYLTYPE yylloc;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;

  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[2];

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;
#if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 0;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
	YYSTACK_RELOCATE (yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 140 "Frontend/Parser/ParserFormula.yy"
    { TheFormula = (yyval.yt_tFormula) = StatePredicateFormula((yyvsp[(2) - (3)].yt_tStatePredicate)); }
    break;

  case 3:
#line 142 "Frontend/Parser/ParserFormula.yy"
    { TheFormula = (yyval.yt_tFormula) = StatePredicateFormula((yyvsp[(2) - (2)].yt_tStatePredicate)); }
    break;

  case 4:
#line 144 "Frontend/Parser/ParserFormula.yy"
    { TheFormula = (yyval.yt_tFormula) = StatePredicateFormula((yyvsp[(1) - (1)].yt_tStatePredicate)); }
    break;

  case 5:
#line 146 "Frontend/Parser/ParserFormula.yy"
    { TheFormula = (yyval.yt_tFormula) = StatePredicateFormula((yyvsp[(1) - (2)].yt_tStatePredicate)); }
    break;

  case 6:
#line 151 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = (yyvsp[(2) - (3)].yt_tStatePredicate); }
    break;

  case 7:
#line 153 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = AtomicProposition((yyvsp[(1) - (1)].yt_tAtomicProposition)); }
    break;

  case 8:
#line 155 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = Negation((yyvsp[(2) - (2)].yt_tStatePredicate)); }
    break;

  case 9:
#line 157 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = Conjunction((yyvsp[(1) - (3)].yt_tStatePredicate), (yyvsp[(3) - (3)].yt_tStatePredicate)); }
    break;

  case 10:
#line 159 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = Disjunction((yyvsp[(1) - (3)].yt_tStatePredicate), (yyvsp[(3) - (3)].yt_tStatePredicate)); }
    break;

  case 11:
#line 161 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = ExclusiveDisjunction((yyvsp[(1) - (3)].yt_tStatePredicate), (yyvsp[(3) - (3)].yt_tStatePredicate)); }
    break;

  case 12:
#line 163 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = Implication((yyvsp[(1) - (3)].yt_tStatePredicate), (yyvsp[(3) - (3)].yt_tStatePredicate)); }
    break;

  case 13:
#line 165 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = Equivalence((yyvsp[(1) - (3)].yt_tStatePredicate), (yyvsp[(3) - (3)].yt_tStatePredicate)); }
    break;

  case 14:
#line 167 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = AllPath((yyvsp[(2) - (2)].yt_tStatePredicate)); }
    break;

  case 15:
#line 169 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = ExPath((yyvsp[(2) - (2)].yt_tStatePredicate)); }
    break;

  case 16:
#line 171 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = Always((yyvsp[(2) - (2)].yt_tStatePredicate)); }
    break;

  case 17:
#line 173 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = Eventually((yyvsp[(2) - (2)].yt_tStatePredicate)); }
    break;

  case 18:
#line 175 "Frontend/Parser/ParserFormula.yy"
    {
        kc::tStatePredicate result = (yyvsp[(2) - (2)].yt_tStatePredicate);
        std::string op((yyvsp[(1) - (2)].yt_casestring)->name);
        for (int i = op.size()-1; i >= 0; i--)
        {
            if (op[i] == 'A') result = AllPath(result);
            if (op[i] == 'E') result = ExPath(result);
            if (op[i] == 'F') result = Eventually(result);
            if (op[i] == 'G') result = Always(result);
            if (op[i] == 'X') result = NextState(result);
            if (op[i] == 'U') yyerrors((yyvsp[(1) - (2)].yt_casestring)->name, (yylsp[(1) - (2)]), "operator 'U' is not allowed here");
            if (op[i] == 'R') yyerrors((yyvsp[(1) - (2)].yt_casestring)->name, (yylsp[(1) - (2)]), "operator 'R' is not allowed here");
        }
        (yyval.yt_tStatePredicate) = result;
    }
    break;

  case 19:
#line 191 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = Until((yyvsp[(2) - (5)].yt_tStatePredicate), (yyvsp[(4) - (5)].yt_tStatePredicate)); }
    break;

  case 20:
#line 193 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = Release((yyvsp[(2) - (5)].yt_tStatePredicate), (yyvsp[(4) - (5)].yt_tStatePredicate)); }
    break;

  case 21:
#line 195 "Frontend/Parser/ParserFormula.yy"
    {
        std::string op((yyvsp[(3) - (5)].yt_casestring)->name);
        if (op == "R") {
            (yyval.yt_tStatePredicate) = Release((yyvsp[(2) - (5)].yt_tStatePredicate), (yyvsp[(4) - (5)].yt_tStatePredicate));
        } else if (op == "U") {
            (yyval.yt_tStatePredicate) = Until((yyvsp[(2) - (5)].yt_tStatePredicate), (yyvsp[(4) - (5)].yt_tStatePredicate));
        } else {
            yyerrors((yyvsp[(3) - (5)].yt_casestring)->name, (yylsp[(3) - (5)]), "operator '%s' is not allowed here", (yyvsp[(3) - (5)].yt_casestring)->name);
        }
    }
    break;

  case 22:
#line 206 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = NextState((yyvsp[(2) - (2)].yt_tStatePredicate)); }
    break;

  case 23:
#line 208 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = ExPath(Eventually((yyvsp[(2) - (2)].yt_tStatePredicate))); }
    break;

  case 24:
#line 210 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = AllPath(Always((yyvsp[(2) - (2)].yt_tStatePredicate))); }
    break;

  case 25:
#line 212 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tStatePredicate) = AllPath(Always(Negation((yyvsp[(2) - (2)].yt_tStatePredicate)))); }
    break;

  case 26:
#line 217 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = EqualsAtomicProposition((yyvsp[(1) - (3)].yt_tTerm), (yyvsp[(3) - (3)].yt_tTerm)); }
    break;

  case 27:
#line 219 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = NotEqualsAtomicProposition((yyvsp[(1) - (3)].yt_tTerm), (yyvsp[(3) - (3)].yt_tTerm)); }
    break;

  case 28:
#line 221 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = GreaterAtomicProposition((yyvsp[(1) - (3)].yt_tTerm), (yyvsp[(3) - (3)].yt_tTerm)); }
    break;

  case 29:
#line 223 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = GreaterEqualAtomicProposition((yyvsp[(1) - (3)].yt_tTerm), (yyvsp[(3) - (3)].yt_tTerm)); }
    break;

  case 30:
#line 225 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = LessAtomicProposition((yyvsp[(1) - (3)].yt_tTerm), (yyvsp[(3) - (3)].yt_tTerm)); }
    break;

  case 31:
#line 227 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = LessEqualAtomicProposition((yyvsp[(1) - (3)].yt_tTerm), (yyvsp[(3) - (3)].yt_tTerm)); }
    break;

  case 32:
#line 229 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = True(); }
    break;

  case 33:
#line 231 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = False(); }
    break;

  case 34:
#line 233 "Frontend/Parser/ParserFormula.yy"
    {
        Symbol *t = symbolTables->TransitionTable->lookup((yyvsp[(3) - (4)].yt_casestring)->name);
        if (UNLIKELY(t == NULL))
        {
            yyerrors((yyvsp[(3) - (4)].yt_casestring)->name, (yylsp[(3) - (4)]), "transition '%s' unknown", (yyvsp[(3) - (4)].yt_casestring)->name);
        }
        (yyval.yt_tAtomicProposition) = Fireable(mkinteger(t->getIndex()));
        target_transition.insert(t->getIndex());
    }
    break;

  case 35:
#line 243 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = Initial(); }
    break;

  case 36:
#line 245 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tAtomicProposition) = Deadlock(); }
    break;

  case 37:
#line 250 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tTerm) = (yyvsp[(2) - (3)].yt_tTerm); }
    break;

  case 38:
#line 252 "Frontend/Parser/ParserFormula.yy"
    {
        Symbol *p = symbolTables->PlaceTable->lookup((yyvsp[(1) - (1)].yt_casestring)->name);
        if (UNLIKELY(p == NULL))
        {
            yyerrors((yyvsp[(1) - (1)].yt_casestring)->name, (yylsp[(1) - (1)]), "place '%s' unknown", (yyvsp[(1) - (1)].yt_casestring)->name);
        }
        (yyval.yt_tTerm) = Node(mkinteger(p->getIndex()));
        target_place.insert(p->getIndex());
    }
    break;

  case 39:
#line 262 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tTerm) = Number((yyvsp[(1) - (1)].yt_integer)); }
    break;

  case 40:
#line 264 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tTerm) = Sum((yyvsp[(1) - (3)].yt_tTerm), (yyvsp[(3) - (3)].yt_tTerm)); }
    break;

  case 41:
#line 266 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tTerm) = Difference((yyvsp[(1) - (3)].yt_tTerm), (yyvsp[(3) - (3)].yt_tTerm)); }
    break;

  case 42:
#line 268 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tTerm) = Product((yyvsp[(1) - (3)].yt_integer), (yyvsp[(3) - (3)].yt_tTerm)); }
    break;

  case 43:
#line 270 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_tTerm) = Number(kc::mkinteger(OMEGA));
      if (RT::args.search_arg != search_arg_covergraph)
      {
          RT::rep->message("%s: omega markings used without %s",
              RT::rep->markup(MARKUP_WARNING, "warning").str(),
              RT::rep->markup(MARKUP_PARAMETER, "--search=cover").str());
      }
    }
    break;

  case 44:
#line 281 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_casestring) = (yyvsp[(1) - (1)].yt_casestring); }
    break;

  case 45:
#line 282 "Frontend/Parser/ParserFormula.yy"
    { (yyval.yt_casestring) = (yyvsp[(1) - (1)].yt_casestring); }
    break;


/* Line 1267 of yacc.c.  */
#line 1832 "Frontend/Parser/ParserFormula.cc"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the look-ahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 285 "Frontend/Parser/ParserFormula.yy"


/// display a parser error and exit
void ptformula_error(char const* mess) __attribute__((noreturn));
void ptformula_error(char const* mess)
{
    extern char* ptformula_text;  ///< the current token text from Flex
    yyerrors(ptformula_text, ptformula_lloc, mess);
}

