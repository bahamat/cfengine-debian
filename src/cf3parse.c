/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 2 "cf3parse.y"


/*******************************************************************/
/*                                                                 */
/*  PARSER for cfengine 3                                          */
/*                                                                 */
/*******************************************************************/

#include "cf3.defs.h"
#include "cf3.extern.h"

extern char *yytext;

static void fatal_yyerror(const char *s);



/* Line 268 of yacc.c  */
#line 89 "cf3parse.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     ID = 258,
     QSTRING = 259,
     CLASS = 260,
     CATEGORY = 261,
     BUNDLE = 262,
     BODY = 263,
     ASSIGN = 264,
     ARROW = 265,
     NAKEDVAR = 266
   };
#endif
/* Tokens.  */
#define ID 258
#define QSTRING 259
#define CLASS 260
#define CATEGORY 261
#define BUNDLE 262
#define BODY 263
#define ASSIGN 264
#define ARROW 265
#define NAKEDVAR 266




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 153 "cf3parse.c"

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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
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
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   83

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  18
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  77
/* YYNRULES -- Number of states.  */
#define YYNSTATES  105

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   266

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      12,    13,     2,     2,    14,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    17,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    15,     2,    16,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    16,    22,    27,
      33,    35,    37,    39,    41,    45,    47,    51,    52,    54,
      55,    60,    62,    65,    67,    69,    70,    75,    77,    80,
      82,    84,    86,    89,    90,    96,    98,   101,   103,   105,
     107,   110,   112,   113,   120,   121,   126,   128,   132,   133,
     137,   139,   141,   143,   145,   147,   149,   151,   155,   157,
     161,   162,   164,   166,   168,   170,   172,   174,   176,   179,
     180,   185,   187,   191,   192,   194,   196,   198
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      19,     0,    -1,    -1,    20,    -1,    21,    -1,    20,    21,
      -1,    22,    24,    25,    29,    -1,    22,    24,    25,    26,
      29,    -1,    23,    24,    25,    33,    -1,    23,    24,    25,
      26,    33,    -1,     7,    -1,     8,    -1,     3,    -1,     3,
      -1,    12,    27,    13,    -1,    28,    -1,    28,    14,    27,
      -1,    -1,     3,    -1,    -1,    15,    30,    31,    16,    -1,
      32,    -1,    31,    32,    -1,    43,    -1,    40,    -1,    -1,
      15,    34,    35,    16,    -1,    36,    -1,    35,    36,    -1,
      49,    -1,    37,    -1,    38,    -1,    37,    38,    -1,    -1,
      50,     9,    51,    39,    17,    -1,    41,    -1,    40,    41,
      -1,    49,    -1,    42,    -1,    44,    -1,    42,    44,    -1,
       6,    -1,    -1,    56,    10,    51,    45,    47,    17,    -1,
      -1,    56,    46,    47,    17,    -1,    48,    -1,    47,    14,
      48,    -1,    -1,    50,     9,    51,    -1,     5,    -1,     3,
      -1,     3,    -1,     4,    -1,    11,    -1,    52,    -1,    57,
      -1,    15,    53,    16,    -1,    54,    -1,    54,    14,    53,
      -1,    -1,     3,    -1,     4,    -1,    11,    -1,    57,    -1,
       3,    -1,    11,    -1,     4,    -1,    55,    58,    -1,    -1,
      12,    59,    60,    13,    -1,    61,    -1,    60,    14,    61,
      -1,    -1,     3,    -1,     4,    -1,    11,    -1,    57,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    23,    23,    24,    28,    29,    33,    34,    35,    36,
      40,    53,    65,    73,    80,    86,    87,    88,    92,   100,
      99,   124,   125,   129,   130,   135,   134,   151,   152,   156,
     157,   161,   162,   169,   166,   220,   221,   225,   226,   230,
     231,   235,   253,   248,   283,   282,   315,   316,   317,   321,
     343,   350,   359,   366,   382,   390,   397,   406,   412,   413,
     414,   418,   423,   430,   437,   446,   450,   460,   469,   477,
     476,   501,   502,   503,   507,   513,   521,   529
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "QSTRING", "CLASS", "CATEGORY",
  "BUNDLE", "BODY", "ASSIGN", "ARROW", "NAKEDVAR", "'('", "')'", "','",
  "'{'", "'}'", "';'", "$accept", "specification", "blocks", "block",
  "bundle", "body", "typeid", "blockid", "usearglist", "aitems", "aitem",
  "bundlebody", "$@1", "statements", "statement", "bodybody", "$@2",
  "bodyattribs", "bodyattrib", "selections", "selection", "$@3",
  "classpromises", "classpromise", "promises", "category", "promise",
  "$@4", "$@5", "constraints", "constraint", "class", "id", "rval", "list",
  "litems", "litem", "functionid", "promiser", "usefunction",
  "givearglist", "$@6", "gaitems", "gaitem", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,    40,    41,    44,   123,   125,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    18,    19,    19,    20,    20,    21,    21,    21,    21,
      22,    23,    24,    25,    26,    27,    27,    27,    28,    30,
      29,    31,    31,    32,    32,    34,    33,    35,    35,    36,
      36,    37,    37,    39,    38,    40,    40,    41,    41,    42,
      42,    43,    45,    44,    46,    44,    47,    47,    47,    48,
      49,    50,    51,    51,    51,    51,    51,    52,    53,    53,
      53,    54,    54,    54,    54,    55,    55,    56,    57,    59,
      58,    60,    60,    60,    61,    61,    61,    61
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     4,     5,     4,     5,
       1,     1,     1,     1,     3,     1,     3,     0,     1,     0,
       4,     1,     2,     1,     1,     0,     4,     1,     2,     1,
       1,     1,     2,     0,     5,     1,     2,     1,     1,     1,
       2,     1,     0,     6,     0,     4,     1,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     3,
       0,     1,     1,     1,     1,     1,     1,     1,     2,     0,
       4,     1,     3,     0,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,    10,    11,     0,     3,     4,     0,     0,     1,     5,
      12,     0,     0,    13,     0,     0,    17,    19,     0,     6,
      25,     0,     8,    18,     0,    15,     0,     7,     0,     9,
      14,    17,    67,    50,    41,     0,    21,    24,    35,    38,
      23,    39,    37,    44,    51,     0,    27,    30,    31,    29,
       0,    16,    20,    22,    36,    40,     0,    48,    26,    28,
      32,     0,    52,    53,    54,    60,    42,    55,     0,    56,
       0,    46,     0,    33,    61,    62,    63,     0,    58,    64,
      48,    69,    68,     0,    45,     0,     0,    57,    60,     0,
      73,    47,    49,    34,    59,    43,    74,    75,    76,    77,
       0,    71,    70,     0,    72
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    11,    14,    18,    24,
      25,    19,    26,    35,    36,    22,    28,    45,    46,    47,
      48,    86,    37,    38,    39,    40,    41,    80,    57,    70,
      71,    42,    50,    66,    67,    77,    78,    68,    43,    69,
      82,    90,   100,   101
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -66
static const yytype_int8 yypact[] =
{
      40,   -66,   -66,     5,    40,   -66,    13,    13,   -66,   -66,
     -66,    29,    29,   -66,     0,    18,    32,   -66,    24,   -66,
     -66,    30,   -66,   -66,    42,    39,    37,   -66,    41,   -66,
     -66,    32,   -66,   -66,   -66,     3,   -66,    45,   -66,    50,
     -66,   -66,   -66,    46,   -66,     1,   -66,    54,   -66,   -66,
      49,   -66,   -66,   -66,   -66,   -66,     7,    54,   -66,   -66,
     -66,     7,    47,   -66,    48,    10,   -66,   -66,    51,   -66,
      17,   -66,    52,   -66,    47,   -66,    48,    53,    56,   -66,
      54,   -66,   -66,    54,   -66,     7,    55,   -66,    10,    23,
      25,   -66,   -66,   -66,   -66,   -66,    47,   -66,    48,   -66,
      38,   -66,   -66,    25,   -66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -66,   -66,   -66,    58,   -66,   -66,    57,    59,    60,    34,
     -66,    61,   -66,   -66,    31,    62,   -66,   -66,    22,   -66,
      21,   -66,   -66,    36,   -66,   -66,    35,   -66,   -66,    -4,
      -6,   -25,   -56,   -59,   -66,   -10,   -66,   -66,   -66,   -65,
     -66,   -66,   -66,   -23
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -67
static const yytype_int8 yytable[] =
{
      79,    72,    73,    49,    44,     8,    33,    32,    33,    34,
      62,    63,    16,    74,    75,    17,    10,    58,    64,    52,
      49,    76,    65,    79,    72,    99,    92,    72,    96,    97,
      16,    83,    13,    20,    84,    23,    98,    83,    99,    17,
      95,    32,    33,    34,    44,    20,    33,     1,     2,    32,
      33,   102,   103,    31,    32,    30,    56,    44,    61,   -65,
     -66,    85,     9,    81,    12,    51,    53,    59,    60,    87,
      88,    15,    93,    54,    55,    21,    89,    91,    94,    27,
     104,     0,     0,    29
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-66))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      65,    57,    61,    28,     3,     0,     5,     4,     5,     6,
       3,     4,    12,     3,     4,    15,     3,    16,    11,    16,
      45,    11,    15,    88,    80,    90,    85,    83,     3,     4,
      12,    14,     3,    15,    17,     3,    11,    14,   103,    15,
      17,     4,     5,     6,     3,    15,     5,     7,     8,     4,
       5,    13,    14,    14,     4,    13,    10,     3,     9,    12,
      12,     9,     4,    12,     7,    31,    35,    45,    47,    16,
      14,    12,    17,    37,    39,    15,    80,    83,    88,    18,
     103,    -1,    -1,    21
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,    19,    20,    21,    22,    23,     0,    21,
       3,    24,    24,     3,    25,    25,    12,    15,    26,    29,
      15,    26,    33,     3,    27,    28,    30,    29,    34,    33,
      13,    14,     4,     5,     6,    31,    32,    40,    41,    42,
      43,    44,    49,    56,     3,    35,    36,    37,    38,    49,
      50,    27,    16,    32,    41,    44,    10,    46,    16,    36,
      38,     9,     3,     4,    11,    15,    51,    52,    55,    57,
      47,    48,    50,    51,     3,     4,    11,    53,    54,    57,
      45,    12,    58,    14,    17,     9,    39,    16,    14,    47,
      59,    48,    51,    17,    53,    17,     3,     4,    11,    57,
      60,    61,    13,    14,    61
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
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


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
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
		  Type, Value); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


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
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 23 "cf3parse.y"
    { yyerror("Something defined outside of a block or missing punctuation in input"); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 41 "cf3parse.y"
    {
                          DebugBanner("Bundle");
                          P.block = "bundle";
                          P.rval = NULL;
                          P.currentRlist = NULL;
                          P.currentstring = NULL;
                          strcpy(P.blockid,"");
                          strcpy(P.blocktype,"");
                          }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 54 "cf3parse.y"
    {
                          DebugBanner("Body");
                          P.block = "body";
                          strcpy(P.blockid,"");
                          P.currentRlist = NULL;
                          P.currentstring = NULL;
                          strcpy(P.blocktype,"");
                          }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 65 "cf3parse.y"
    {
                          strncpy(P.blocktype,P.currentid,CF_MAXVARSIZE);
                          Debug("Found block type %s for %s\n",P.blocktype,P.block);
                          P.useargs = NULL;
                          }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 73 "cf3parse.y"
    {
                          strncpy(P.blockid,P.currentid,CF_MAXVARSIZE);
                          Debug("Found identifier %s for %s\n",P.currentid,P.block);
                          }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 93 "cf3parse.y"
    {
                          AppendRlist(&(P.useargs),P.currentid,CF_SCALAR);
                          }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 100 "cf3parse.y"
    {
                       if (RelevantBundle(THIS_AGENT,P.blocktype))
                          {
                          Debug("We a compiling everything here\n");
                          INSTALL_SKIP = false;                          
                          }
                       else if (strcmp(THIS_AGENT,P.blocktype) != 0)
                          {
                          Debug("This is for a different agent\n");
                          INSTALL_SKIP = true;
                          }
                       
                       P.currentbundle = AppendBundle(&BUNDLES,P.blockid,P.blocktype,P.useargs);
                       P.useargs = NULL;
                       }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 117 "cf3parse.y"
    {
                       INSTALL_SKIP = false;
                       Debug("End promise bundle\n\n");
                       }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 135 "cf3parse.y"
    {
                        P.currentbody = AppendBody(&BODIES,P.blockid,P.blocktype,P.useargs);
                        P.useargs = NULL;
                        strcpy(P.currentid,"");
                        Debug("Starting block\n");
                        }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 145 "cf3parse.y"
    {
                        Debug("End promise body\n");
                        }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 169 "cf3parse.y"
    {
 
                        CheckSelection(P.blocktype,P.blockid,P.lval,P.rval,P.rtype);

                        if (!INSTALL_SKIP)
                           {
                           if (P.currentclasses == NULL)
                              {
                              AppendConstraint(&((P.currentbody)->conlist),P.lval,P.rval,P.rtype,"any",P.isbody);
                              }
                           else
                              {
                              AppendConstraint(&((P.currentbody)->conlist),P.lval,P.rval,P.rtype,P.currentclasses,P.isbody);
                              }
                           }
                        else
                           {
                           DeleteRvalItem(P.rval,P.rtype);
                           }

                        if (strcmp(P.blockid,"control") == 0 && strcmp(P.blocktype,"common") == 0)
                           {
                           if (strcmp(P.lval,"inputs") == 0)
                              {
                              if (IsDefinedClass(P.currentclasses))
                                 {
                                 if (VINPUTLIST == NULL)
                                    {
                                    if (P.rtype == CF_LIST)
                                       {
                                       VINPUTLIST = P.rval;
                                       }
                                    else
                                       {
                                       yyerror("inputs promise must have a list as rvalue");
                                       }                                    
                                    }
                                 else
                                    {
                                    yyerror("Redefinition of input list (broken promise)");
                                    }
                                 }
                              }
                           }

                        P.rval = NULL;
                        }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 236 "cf3parse.y"
    {
                         Debug("\n* Begin new promise type category %s in function \n\n",P.currenttype);
                                                 
                         if (strcmp(P.block,"bundle") == 0)
                            {
                            CheckSubType(P.blocktype,P.currenttype); /* FIXME: unused? */
                            P.currentstype = AppendSubType(P.currentbundle,P.currenttype);
                            }
                         }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 253 "cf3parse.y"
    {
                        if (P.currentclasses == NULL)
                           {
                           P.currentpromise = AppendPromise(P.currentstype,P.promiser,P.rval,P.rtype,"any",P.blockid,P.blocktype);
                           }
                        else
                           {
                           P.currentpromise = AppendPromise(P.currentstype,P.promiser,P.rval,P.rtype,P.currentclasses,P.blockid,P.blocktype);
                           }
                        }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 265 "cf3parse.y"
    {
                        Debug("End implicit promise %s\n\n",P.promiser);
                        strcpy(P.currentid,"");
                        P.currentRlist = NULL;
                        free(P.promiser);
                        if (P.currentstring)
                           {
                           free(P.currentstring);
                           }
                        P.currentstring = NULL;
                        P.promiser = NULL;
                        P.promisee = NULL;
                        /* reset argptrs etc*/
                        }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 283 "cf3parse.y"
    {
                        if (P.currentclasses == NULL)
                           {                           
                           P.currentpromise = AppendPromise(P.currentstype,P.promiser,NULL,CF_NOPROMISEE,"any",P.blockid,P.blocktype);
                           }
                        else
                           {
                           P.currentpromise = AppendPromise(P.currentstype,P.promiser,NULL,CF_NOPROMISEE,P.currentclasses,P.blockid,P.blocktype);
                           }
                        }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 295 "cf3parse.y"
    {
                        Debug("End full promise with promisee %s\n\n",P.promiser);

                        /* Don't free these */
                        strcpy(P.currentid,"");
                        P.currentRlist = NULL;
                        free(P.promiser);
                        if (P.currentstring)
                           {
                           free(P.currentstring);
                           }
                        P.currentstring = NULL;
                        P.promiser = NULL;
                        P.promisee = NULL;
                         /* reset argptrs etc*/
                        }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 324 "cf3parse.y"
    {
                        if (!INSTALL_SKIP)
                           {
                           struct SubTypeSyntax ss = CheckSubType(P.blocktype,P.currenttype);                           
                           CheckConstraint(P.currenttype,P.blockid,P.lval,P.rval,P.rtype,ss);                           
                           AppendConstraint(&(P.currentpromise->conlist),P.lval,P.rval,P.rtype,"any",P.isbody);
                           
                           P.rval = NULL;
                           strcpy(P.lval,"no lval");
                           P.currentRlist = NULL;
                           }
                        else
                           {
                           DeleteRvalItem(P.rval,P.rtype);
                           }
                        }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 344 "cf3parse.y"
    {
                         Debug("  New class context \'%s\' :: \n\n",P.currentclasses);
                         }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 351 "cf3parse.y"
    {
                         strncpy(P.lval,P.currentid,CF_MAXVARSIZE);
                         P.currentRlist = NULL;
                         Debug("Recorded LVAL %s\n",P.lval);
                         }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 360 "cf3parse.y"
    {
                         P.rval = strdup(P.currentid);
                         P.rtype = CF_SCALAR;
                         P.isbody = true;
                         Debug("Recorded IDRVAL %s\n",P.rval);
                         }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 367 "cf3parse.y"
    {
                         P.rval = P.currentstring;
                         P.currentstring = NULL;
                         P.rtype = CF_SCALAR;
                         P.isbody = false;
                         Debug("Recorded scalarRVAL %s\n",P.rval);

                         if (P.currentpromise)
                            {
                            if (LvalWantsBody(P.currentpromise->agentsubtype,P.lval))
                               {
                               yyerror("An rvalue is quoted, but we expect an unquoted body identifier");
                               }
                            }
                         }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 383 "cf3parse.y"
    {
                         P.rval = P.currentstring;
                         P.currentstring = NULL;
                         P.rtype = CF_SCALAR;
                         P.isbody = false;
                         Debug("Recorded saclarvariableRVAL %s\n",P.rval);
                         }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 391 "cf3parse.y"
    {
                         P.rval = P.currentRlist;
                         P.currentRlist = NULL;
                         P.isbody = false;
                         P.rtype = CF_LIST;
                         }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 398 "cf3parse.y"
    {
                         P.isbody = false;
                         P.rval = P.currentfncall[P.arg_nesting+1];
                         P.rtype = CF_FNCALL;
                         }
    break;

  case 61:

/* Line 1806 of yacc.c  */
#line 419 "cf3parse.y"
    {
                          AppendRlist((struct Rlist **)&P.currentRlist,P.currentid,CF_SCALAR);
                          }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 424 "cf3parse.y"
    {
                          AppendRlist((struct Rlist **)&P.currentRlist,(void *)P.currentstring,CF_SCALAR);
                          free(P.currentstring);
                          P.currentstring = NULL;
                          }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 431 "cf3parse.y"
    {
                          AppendRlist((struct Rlist **)&P.currentRlist,(void *)P.currentstring,CF_SCALAR);
                          free(P.currentstring);
                          P.currentstring = NULL;
                          }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 438 "cf3parse.y"
    {
                          Debug("Install function call as list item from level %d\n",P.arg_nesting+1);
                          AppendRlist((struct Rlist **)&P.currentRlist,(void *)P.currentfncall[P.arg_nesting+1],CF_FNCALL);
                          DeleteFnCall(P.currentfncall[P.arg_nesting+1]);
                          }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 447 "cf3parse.y"
    {
                          Debug("Found function identifier %s\n",P.currentid);
                          }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 451 "cf3parse.y"
    {
                          strncpy(P.currentid,P.currentstring,CF_MAXVARSIZE); // Make a var look like an ID
                          free(P.currentstring);
                          P.currentstring = NULL;
                          Debug("Found variable in place of a function identifier %s\n",P.currentid);
                          }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 461 "cf3parse.y"
    {
                          P.promiser = P.currentstring;
                          P.currentstring = NULL;
                          Debug("Promising object name \'%s\'\n",P.promiser);
                          }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 470 "cf3parse.y"
    {
                         Debug("Finished with function call, now at level %d\n\n",P.arg_nesting);
                         }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 477 "cf3parse.y"
    {
                           if (++P.arg_nesting >= CF_MAX_NESTING)
                              {
                              fatal_yyerror("Nesting of functions is deeper than recommended");
                              }
                           P.currentfnid[P.arg_nesting] = strdup(P.currentid);
                           Debug("Start FnCall %s args level %d\n",P.currentfnid[P.arg_nesting],P.arg_nesting);
                           }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 488 "cf3parse.y"
    {
                           Debug("End args level %d\n",P.arg_nesting);
                           P.currentfncall[P.arg_nesting] = NewFnCall(P.currentfnid[P.arg_nesting],P.giveargs[P.arg_nesting]);
                           P.giveargs[P.arg_nesting] = NULL;                           
                           strcpy(P.currentid,"");
                           free(P.currentfnid[P.arg_nesting]);
                           P.currentfnid[P.arg_nesting] = NULL;
                           P.arg_nesting--;
                           }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 508 "cf3parse.y"
    {
                          /* currently inside a use function */
                          AppendRlist(&P.giveargs[P.arg_nesting],P.currentid,CF_SCALAR);
                          }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 514 "cf3parse.y"
    {
                          /* currently inside a use function */
                          AppendRlist(&P.giveargs[P.arg_nesting],P.currentstring,CF_SCALAR);
                          free(P.currentstring);
                          P.currentstring = NULL;
                          }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 522 "cf3parse.y"
    {
                          /* currently inside a use function */
                          AppendRlist(&P.giveargs[P.arg_nesting],P.currentstring,CF_SCALAR);
                          free(P.currentstring);
                          P.currentstring = NULL;
                          }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 530 "cf3parse.y"
    {
                          /* Careful about recursion */
                          AppendRlist(&P.giveargs[P.arg_nesting],(void *)P.currentfncall[P.arg_nesting+1],CF_FNCALL);
                          DeleteRvalItem(P.currentfncall[P.arg_nesting+1],CF_FNCALL);
                          }
    break;



/* Line 1806 of yacc.c  */
#line 2001 "cf3parse.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

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
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
      if (!yypact_value_is_default (yyn))
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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



/* Line 2067 of yacc.c  */
#line 536 "cf3parse.y"


/*****************************************************************/

void yyerror(const char *s)
{ char *sp = yytext;

if (sp == NULL)
   {
   fprintf (stderr, "%s> %s:%d,%d: %s, near token \'NULL\'\n",VPREFIX,P.filename,P.line_no,P.line_pos,s);
   }
else if (*sp == '\"' && strlen(sp) > 1)
   {
   sp++;
   }

fprintf (stderr, "%s> %s:%d,%d: %s, near token \'%.20s\'\n",VPREFIX,P.filename,P.line_no,P.line_pos,s,sp);

ERRORCOUNT++;

if (ERRORCOUNT > 10)
   {
   FatalError("Too many errors");
   }
}

static void fatal_yyerror(const char *s)
{
char *sp = yytext;
/* Skip quotation mark */
if (sp && *sp == '\"' && sp[1])
   {
   sp++;
   }

FatalError("%s> %s: %d,%d: Fatal error during parsing: %s, near token \'%.20s\'\n", VPREFIX, P.filename, P.line_no, P.line_pos, s, sp ? sp : "NULL");
}

/*****************************************************************/


/* EOF */

