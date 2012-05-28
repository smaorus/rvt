/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "rv_gram.y"

 /*
 ======================================================================

	CTool Library
	Copyright (C) 1995-2001	Shaun Flisakowski

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 1, or (at your option)
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

 ======================================================================
 */

/* grammar File for C - Shaun Flisakowski and Patrick Baudin */
/* Grammar was constructed with the assistance of:
	"C - A Reference Manual" (Fourth Edition),
	by Samuel P Harbison, and Guy L Steele Jr. */

/* Benny Godlin added hooks to process c programs for Regresion Verification checks */
	

#ifdef    NO_ALLOCA
#define   alloca  __builtin_alloca
#endif

#include <stdio.h>
#include <errno.h>
#include <setjmp.h>

#include <ctool/lexer.h>
#include <ctool/symbol.h>
#include <ctool/token.h>
#include <ctool/stemnt.h>
#include <ctool/location.h>
#include <ctool/project.h>

#include <rv_parse.h>
#include <rv_etc.h>

extern int errno;
int yylex(YYSTYPE *lvalp);

/* Cause the `yydebug' variable to be defined.  */
#define YYDEBUG 1

#undef HERE
#define HERE Location(gProject->Parse_TOS->yylineno, \
					  gProject->Parse_TOS->yycolno, \
					  gProject->Parse_TOS->filename)

/*  int  yydebug = 1;  */

/* ###################################################### */

/* Line 189 of yacc.c  */
#line 222 "rv_gram.y"

/* 1 if we explained undeclared var errors.  */
/*  static int undeclared_variable_notice = 0;  */


/* Line 189 of yacc.c  */
#line 145 "rv_gram.tab.c"

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
     IDENT = 258,
     TAG_NAME = 259,
     LABEL_NAME = 260,
     TYPEDEF_NAME = 261,
     STRING = 262,
     LSTRING = 263,
     CHAR_CONST = 264,
     LCHAR_CONST = 265,
     INUM = 266,
     RNUM = 267,
     PP_LINE = 268,
     INVALID = 269,
     CONST = 270,
     VOLATILE = 271,
     AUTO = 272,
     EXTRN = 273,
     REGISTR = 274,
     STATIC = 275,
     TYPEDEF = 276,
     VOID = 277,
     BOOL = 278,
     CHAR = 279,
     SHORT = 280,
     INT = 281,
     INT8 = 282,
     INT16 = 283,
     INT32 = 284,
     INT64 = 285,
     LONG = 286,
     FLOAT = 287,
     DOUBLE = 288,
     SGNED = 289,
     UNSGNED = 290,
     ENUM = 291,
     STRUCT = 292,
     UNION = 293,
     BREAK = 294,
     CASE = 295,
     CONT = 296,
     DEFLT = 297,
     DO = 298,
     ELSE = 299,
     IF = 300,
     FOR = 301,
     GOTO = 302,
     RETURN = 303,
     SWITCH = 304,
     WHILE = 305,
     PLUS_EQ = 306,
     MINUS_EQ = 307,
     STAR_EQ = 308,
     DIV_EQ = 309,
     MOD_EQ = 310,
     B_AND_EQ = 311,
     B_OR_EQ = 312,
     B_XOR_EQ = 313,
     L_SHIFT_EQ = 314,
     R_SHIFT_EQ = 315,
     EQUAL = 316,
     LESS_EQ = 317,
     GRTR_EQ = 318,
     NOT_EQ = 319,
     RPAREN = 320,
     RBRCKT = 321,
     LBRACE = 322,
     RBRACE = 323,
     SEMICOLON = 324,
     COMMA = 325,
     ELLIPSIS = 326,
     LB_SIGN = 327,
     DOUB_LB_SIGN = 328,
     BACKQUOTE = 329,
     AT = 330,
     ATTRIBUTE = 331,
     ALIGNED = 332,
     PACKED = 333,
     CDECL = 334,
     MODE = 335,
     FORMAT = 336,
     NORETURN = 337,
     MALLOC = 338,
     COMMA_OP = 339,
     ASSIGN = 340,
     EQ = 341,
     COMMA_SEP = 342,
     COLON = 343,
     QUESTMARK = 344,
     OR = 345,
     AND = 346,
     B_OR = 347,
     B_XOR = 348,
     B_AND = 349,
     COMP_EQ = 350,
     GRTR = 351,
     LESS = 352,
     COMP_ARITH = 353,
     R_SHIFT = 354,
     L_SHIFT = 355,
     MINUS = 356,
     PLUS = 357,
     MOD = 358,
     DIV = 359,
     STAR = 360,
     CAST = 361,
     DECR = 362,
     INCR = 363,
     SIZEOF = 364,
     B_NOT = 365,
     NOT = 366,
     UNARY = 367,
     HYPERUNARY = 368,
     LBRCKT = 369,
     LPAREN = 370,
     DOT = 371,
     ARROW = 372
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 303 "rv_gram.tab.c"

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

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1146

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  198
/* YYNRULES -- Number of rules.  */
#define YYNRULES  364
/* YYNRULES -- Number of states.  */
#define YYNSTATES  517

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   372

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    15,    16,    18,
      20,    22,    25,    29,    32,    36,    40,    41,    47,    50,
      51,    53,    55,    58,    61,    63,    68,    71,    72,    74,
      76,    79,    82,    84,    86,    88,    90,    92,    94,    96,
      98,   100,   102,   104,   107,   110,   111,   116,   118,   120,
     122,   124,   126,   132,   135,   138,   142,   146,   148,   154,
     162,   170,   176,   186,   188,   190,   192,   194,   197,   202,
     204,   206,   212,   214,   218,   219,   221,   223,   224,   226,
     228,   230,   234,   236,   240,   243,   245,   249,   251,   255,
     257,   261,   264,   266,   271,   273,   277,   279,   283,   285,
     289,   291,   295,   297,   301,   303,   305,   307,   309,   311,
     313,   315,   317,   319,   321,   326,   329,   332,   335,   338,
     341,   344,   347,   349,   353,   355,   357,   359,   363,   367,
     369,   371,   373,   375,   377,   379,   384,   386,   388,   391,
     394,   396,   400,   404,   409,   410,   412,   414,   418,   420,
     422,   424,   426,   428,   430,   432,   434,   436,   438,   440,
     442,   444,   446,   448,   450,   452,   453,   455,   456,   457,
     461,   462,   464,   465,   466,   470,   473,   477,   480,   483,
     486,   489,   490,   492,   494,   495,   498,   500,   503,   505,
     507,   509,   511,   513,   515,   517,   519,   521,   522,   524,
     527,   528,   532,   535,   536,   538,   539,   543,   546,   548,
     549,   553,   555,   559,   560,   562,   564,   566,   570,   572,
     574,   578,   580,   585,   586,   588,   590,   592,   594,   596,
     599,   600,   602,   604,   606,   608,   610,   612,   614,   616,
     618,   620,   622,   624,   626,   628,   630,   632,   634,   636,
     638,   640,   642,   644,   646,   648,   651,   654,   657,   660,
     661,   667,   668,   674,   677,   678,   684,   685,   691,   694,
     695,   701,   702,   708,   709,   711,   712,   715,   716,   718,
     720,   722,   726,   728,   732,   734,   735,   736,   740,   743,
     746,   750,   753,   755,   757,   758,   762,   763,   769,   771,
     773,   775,   776,   781,   783,   784,   786,   788,   790,   793,
     795,   797,   799,   803,   805,   810,   815,   819,   824,   827,
     829,   832,   834,   835,   838,   840,   844,   846,   848,   850,
     852,   853,   854,   857,   858,   861,   863,   867,   869,   873,
     874,   877,   880,   883,   885,   887,   889,   892,   894,   898,
     902,   907,   911,   916,   917,   919,   926,   927,   929,   931,
     933,   935,   940,   945,   954
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     119,     0,    -1,    -1,   120,    -1,     1,    -1,   122,   121,
      -1,   120,   122,   121,    -1,    -1,   211,    -1,   123,    -1,
      13,    -1,     1,    69,    -1,     1,    68,   121,    -1,   124,
     125,    -1,   215,   287,   202,    -1,   214,   286,   202,    -1,
      -1,    67,   126,   206,   127,    68,    -1,     1,    68,    -1,
      -1,   128,    -1,   129,    -1,   128,   129,    -1,   128,    13,
      -1,   133,    -1,    67,   206,   131,    68,    -1,     1,    68,
      -1,    -1,   132,    -1,   133,    -1,   132,   133,    -1,   132,
      13,    -1,   134,    -1,   135,    -1,   130,    -1,   137,    -1,
     138,    -1,   139,    -1,   140,    -1,   141,    -1,   142,    -1,
     143,    -1,   144,    -1,     1,    69,    -1,   159,    69,    -1,
      -1,   150,    88,   136,   133,    -1,   145,    -1,   146,    -1,
     147,    -1,   148,    -1,   149,    -1,    49,   115,   159,    65,
     133,    -1,    39,    69,    -1,    41,    69,    -1,    48,   158,
      69,    -1,    47,     5,    69,    -1,    69,    -1,    45,   115,
     159,    65,   133,    -1,    45,   115,   159,    65,   133,    44,
     133,    -1,    43,   133,    50,   115,   159,    65,    69,    -1,
      50,   115,   159,    65,   133,    -1,    46,   115,   158,    69,
     158,    69,   158,    65,   133,    -1,   151,    -1,   152,    -1,
     153,    -1,   298,    -1,    40,   157,    -1,    40,   157,    71,
     157,    -1,    42,    -1,   160,    -1,   160,    89,   159,    88,
     154,    -1,   154,    -1,   173,   200,   155,    -1,    -1,   157,
      -1,   159,    -1,    -1,   159,    -1,   181,    -1,   161,    -1,
     160,    90,   161,    -1,   163,    -1,   161,    91,   163,    -1,
     111,   167,    -1,   164,    -1,   163,    92,   164,    -1,   165,
      -1,   164,    93,   165,    -1,   168,    -1,   165,    94,   168,
      -1,   110,   167,    -1,   173,    -1,   115,   217,    65,   167,
      -1,   169,    -1,   168,   197,   169,    -1,   170,    -1,   169,
     198,   170,    -1,   171,    -1,   170,   199,   171,    -1,   172,
      -1,   171,   195,   172,    -1,   167,    -1,   172,   196,   167,
      -1,   184,    -1,   174,    -1,   175,    -1,   176,    -1,   162,
      -1,   166,    -1,   177,    -1,   178,    -1,   179,    -1,   180,
      -1,   109,   115,   217,    65,    -1,   109,   173,    -1,   101,
     167,    -1,   102,   167,    -1,    94,   167,    -1,   105,   167,
      -1,   108,   173,    -1,   107,   173,    -1,   155,    -1,   181,
      70,   155,    -1,   298,    -1,   183,    -1,   201,    -1,   115,
     159,    65,    -1,   115,     1,    65,    -1,   182,    -1,   185,
      -1,   186,    -1,   192,    -1,   187,    -1,   188,    -1,   184,
     114,   159,    66,    -1,   190,    -1,   191,    -1,   184,   108,
      -1,   184,   107,    -1,   300,    -1,   184,   116,   189,    -1,
     184,   117,   189,    -1,   184,   115,   193,    65,    -1,    -1,
     194,    -1,   155,    -1,   194,    70,   155,    -1,   102,    -1,
     101,    -1,   105,    -1,   104,    -1,   103,    -1,    95,    -1,
      98,    -1,   100,    -1,    99,    -1,    86,    -1,    85,    -1,
      11,    -1,    12,    -1,     9,    -1,    10,    -1,     7,    -1,
       8,    -1,    -1,   203,    -1,    -1,    -1,   204,   205,   210,
      -1,    -1,   207,    -1,    -1,    -1,   208,   209,   210,    -1,
     213,    69,    -1,   213,    69,   210,    -1,   212,    69,    -1,
     213,    69,    -1,   214,   235,    -1,   215,   235,    -1,    -1,
     220,    -1,   310,    -1,    -1,   218,   219,    -1,   220,    -1,
     220,   216,    -1,   226,    -1,    18,    -1,    20,    -1,    21,
      -1,    17,    -1,    19,    -1,   221,    -1,   222,    -1,   246,
      -1,    -1,   226,    -1,   223,   225,    -1,    -1,   224,   227,
     225,    -1,   242,   225,    -1,    -1,   229,    -1,    -1,   246,
     230,   228,    -1,   242,   228,    -1,   229,    -1,    -1,   286,
     233,   313,    -1,   232,    -1,   232,    86,   238,    -1,    -1,
     236,    -1,   237,    -1,   234,    -1,   237,    70,   234,    -1,
     240,    -1,   240,    -1,   239,    70,   240,    -1,   155,    -1,
      67,   239,   241,    68,    -1,    -1,    70,    -1,   243,    -1,
      15,    -1,    16,    -1,   243,    -1,   244,   243,    -1,    -1,
     244,    -1,   261,    -1,   253,    -1,   257,    -1,   251,    -1,
     249,    -1,   250,    -1,   247,    -1,    22,    -1,    23,    -1,
      24,    -1,    25,    -1,    26,    -1,    27,    -1,    28,    -1,
      29,    -1,    30,    -1,    31,    -1,    32,    -1,    33,    -1,
      34,    -1,    35,    -1,     6,    -1,     4,    -1,    37,   248,
      -1,    38,   248,    -1,    36,   248,    -1,    37,   248,    -1,
      -1,    37,   254,    67,   264,    68,    -1,    -1,   252,   255,
      67,   264,    68,    -1,    38,   248,    -1,    -1,    38,    67,
     258,   264,    68,    -1,    -1,   256,    67,   259,   264,    68,
      -1,    36,   248,    -1,    -1,    36,    67,   262,   265,    68,
      -1,    -1,   260,    67,   263,   265,    68,    -1,    -1,   271,
      -1,    -1,   267,   266,    -1,    -1,    70,    -1,   268,    -1,
     269,    -1,   267,    70,   269,    -1,   270,    -1,   270,    86,
     155,    -1,   300,    -1,    -1,    -1,   272,   273,   274,    -1,
     275,    69,    -1,   274,    69,    -1,   274,   275,    69,    -1,
     231,   276,    -1,   231,    -1,   277,    -1,    -1,   278,   280,
     313,    -1,    -1,   277,    70,   279,   280,   313,    -1,   281,
      -1,   282,    -1,   286,    -1,    -1,   285,    88,   283,   284,
      -1,   154,    -1,    -1,   286,    -1,   288,    -1,   288,    -1,
     294,   289,    -1,   289,    -1,   290,    -1,   298,    -1,   115,
     288,    65,    -1,   291,    -1,   290,   115,   303,    65,    -1,
     290,   115,   295,    65,    -1,   290,   115,    65,    -1,   290,
     114,   156,    66,    -1,   105,   245,    -1,   292,    -1,   293,
     292,    -1,   293,    -1,    -1,   296,   297,    -1,   298,    -1,
     297,    70,   298,    -1,     3,    -1,     6,    -1,   298,    -1,
     299,    -1,    -1,    -1,   302,   305,    -1,    -1,   304,   305,
      -1,   306,    -1,   306,    70,    71,    -1,   307,    -1,   306,
      70,   307,    -1,    -1,   308,   309,    -1,   220,   286,    -1,
     220,   310,    -1,   220,    -1,   294,    -1,   311,    -1,   294,
     311,    -1,   312,    -1,   115,   310,    65,    -1,   114,   156,
      66,    -1,   312,   114,   156,    66,    -1,   115,   301,    65,
      -1,   312,   115,   301,    65,    -1,    -1,   314,    -1,    76,
     115,   115,   315,    65,    65,    -1,    -1,    78,    -1,    79,
      -1,    15,    -1,    82,    -1,    77,   115,    11,    65,    -1,
      80,   115,   298,    65,    -1,    81,   115,   298,    70,    11,
      70,    11,    65,    -1,    83,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   234,   234,   241,   252,   260,   265,   272,   280,   286,
     292,   297,   301,   307,   338,   367,   401,   400,   418,   425,
     428,   431,   432,   441,   456,   459,   469,   476,   479,   482,
     483,   492,   503,   504,   505,   506,   507,   508,   509,   510,
     511,   512,   513,   514,   521,   529,   528,   549,   550,   553,
     554,   555,   558,   567,   575,   583,   591,   599,   606,   615,
     625,   636,   645,   657,   658,   659,   662,   670,   675,   683,
     699,   700,   708,   709,   718,   721,   724,   728,   731,   734,
     737,   738,   745,   746,   753,   760,   761,   768,   769,   776,
     777,   784,   791,   792,   800,   801,   807,   808,   814,   815,
     821,   822,   828,   829,   837,   838,   839,   840,   841,   842,
     843,   844,   845,   846,   849,   856,   863,   869,   876,   883,
     889,   896,   903,   904,   911,   920,   921,   927,   933,   941,
     942,   943,   944,   945,   946,   949,   957,   958,   961,   968,
     975,   978,  1001,  1024,  1038,  1041,  1044,  1045,  1054,  1055,
    1058,  1059,  1060,  1063,  1066,  1069,  1070,  1073,  1074,  1077,
    1078,  1079,  1080,  1081,  1082,  1091,  1091,  1102,  1107,  1102,
    1123,  1123,  1133,  1138,  1133,  1146,  1151,  1164,  1171,  1179,
    1197,  1218,  1224,  1233,  1237,  1237,  1248,  1258,  1286,  1292,
    1293,  1294,  1297,  1298,  1301,  1302,  1312,  1316,  1319,  1322,
    1341,  1341,  1373,  1394,  1397,  1400,  1400,  1410,  1425,  1435,
    1434,  1445,  1446,  1454,  1457,  1460,  1463,  1467,  1483,  1485,
    1490,  1498,  1499,  1508,  1511,  1523,  1526,  1527,  1530,  1531,
    1540,  1543,  1550,  1551,  1552,  1553,  1554,  1555,  1556,  1557,
    1558,  1559,  1560,  1561,  1562,  1563,  1564,  1565,  1566,  1567,
    1568,  1569,  1570,  1573,  1580,  1588,  1598,  1608,  1618,  1628,
    1628,  1637,  1637,  1663,  1674,  1673,  1685,  1684,  1711,  1722,
    1721,  1732,  1731,  1758,  1761,  1765,  1768,  1774,  1777,  1787,
    1790,  1795,  1803,  1818,  1835,  1842,  1847,  1842,  1861,  1867,
    1875,  1883,  1888,  1899,  1903,  1903,  1911,  1910,  1922,  1940,
    1957,  1961,  1960,  1980,  1984,  1987,  1994,  2000,  2006,  2011,
    2014,  2017,  2022,  2028,  2029,  2046,  2063,  2088,  2106,  2112,
    2113,  2120,  2127,  2127,  2142,  2147,  2159,  2163,  2175,  2176,
    2185,  2189,  2189,  2198,  2198,  2211,  2212,  2221,  2222,  2230,
    2230,  2240,  2262,  2285,  2299,  2303,  2307,  2314,  2317,  2321,
    2325,  2336,  2340,  2358,  2361,  2364,  2375,  2379,  2383,  2387,
    2391,  2395,  2409,  2418,  2441
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENT", "TAG_NAME", "LABEL_NAME",
  "TYPEDEF_NAME", "STRING", "LSTRING", "CHAR_CONST", "LCHAR_CONST", "INUM",
  "RNUM", "PP_LINE", "INVALID", "CONST", "VOLATILE", "AUTO", "EXTRN",
  "REGISTR", "STATIC", "TYPEDEF", "VOID", "BOOL", "CHAR", "SHORT", "INT",
  "INT8", "INT16", "INT32", "INT64", "LONG", "FLOAT", "DOUBLE", "SGNED",
  "UNSGNED", "ENUM", "STRUCT", "UNION", "BREAK", "CASE", "CONT", "DEFLT",
  "DO", "ELSE", "IF", "FOR", "GOTO", "RETURN", "SWITCH", "WHILE",
  "PLUS_EQ", "MINUS_EQ", "STAR_EQ", "DIV_EQ", "MOD_EQ", "B_AND_EQ",
  "B_OR_EQ", "B_XOR_EQ", "L_SHIFT_EQ", "R_SHIFT_EQ", "EQUAL", "LESS_EQ",
  "GRTR_EQ", "NOT_EQ", "RPAREN", "RBRCKT", "LBRACE", "RBRACE", "SEMICOLON",
  "COMMA", "ELLIPSIS", "LB_SIGN", "DOUB_LB_SIGN", "BACKQUOTE", "AT",
  "ATTRIBUTE", "ALIGNED", "PACKED", "CDECL", "MODE", "FORMAT", "NORETURN",
  "MALLOC", "COMMA_OP", "ASSIGN", "EQ", "COMMA_SEP", "COLON", "QUESTMARK",
  "OR", "AND", "B_OR", "B_XOR", "B_AND", "COMP_EQ", "GRTR", "LESS",
  "COMP_ARITH", "R_SHIFT", "L_SHIFT", "MINUS", "PLUS", "MOD", "DIV",
  "STAR", "CAST", "DECR", "INCR", "SIZEOF", "B_NOT", "NOT", "UNARY",
  "HYPERUNARY", "LBRCKT", "LPAREN", "DOT", "ARROW", "$accept", "program",
  "trans_unit", "top_level_exit", "top_level_decl", "func_def",
  "func_spec", "cmpnd_stemnt", "$@1", "opt_stemnt_list", "stemnt_list",
  "stemnt", "cmpnd_stemnt_reentrance", "opt_stemnt_list_reentrance",
  "stemnt_list_reentrance", "stemnt_reentrance", "expr_stemnt",
  "labeled_stemnt", "$@2", "cond_stemnt", "iter_stemnt", "switch_stemnt",
  "break_stemnt", "continue_stemnt", "return_stemnt", "goto_stemnt",
  "null_stemnt", "if_stemnt", "if_else_stemnt", "do_stemnt",
  "while_stemnt", "for_stemnt", "label", "named_label", "case_label",
  "deflt_label", "cond_expr", "assign_expr", "opt_const_expr",
  "const_expr", "opt_expr", "expr", "log_or_expr", "log_and_expr",
  "log_neg_expr", "bitwise_or_expr", "bitwise_xor_expr",
  "bitwise_and_expr", "bitwise_neg_expr", "cast_expr", "equality_expr",
  "relational_expr", "shift_expr", "additive_expr", "mult_expr",
  "unary_expr", "sizeof_expr", "unary_minus_expr", "unary_plus_expr",
  "addr_expr", "indirection_expr", "preinc_expr", "predec_expr",
  "comma_expr", "prim_expr", "paren_expr", "postfix_expr",
  "subscript_expr", "comp_select_expr", "postinc_expr", "postdec_expr",
  "field_ident", "direct_comp_select", "indirect_comp_select", "func_call",
  "opt_expr_list", "expr_list", "add_op", "mult_op", "equality_op",
  "relation_op", "shift_op", "assign_op", "constant",
  "opt_KnR_declaration_list", "$@3", "$@4", "$@5", "opt_declaration_list",
  "$@6", "$@7", "$@8", "declaration_list", "decl_stemnt",
  "old_style_declaration", "declaration", "no_decl_specs", "decl_specs",
  "abs_decl", "type_name", "$@9", "type_name_bis",
  "decl_specs_reentrance_bis", "local_or_global_storage_class",
  "local_storage_class", "storage_class", "type_spec",
  "opt_decl_specs_reentrance", "decl_specs_reentrance", "$@10",
  "opt_comp_decl_specs", "comp_decl_specs_reentrance", "$@11",
  "comp_decl_specs", "decl", "$@12", "init_decl", "opt_init_decl_list",
  "init_decl_list", "init_decl_list_reentrance", "initializer",
  "initializer_list", "initializer_reentrance", "opt_comma", "type_qual",
  "type_qual_token", "type_qual_list", "opt_type_qual_list",
  "type_spec_reentrance", "typedef_name", "tag_ref", "struct_tag_ref",
  "union_tag_ref", "enum_tag_ref", "struct_tag_def", "struct_type_define",
  "$@13", "$@14", "union_tag_def", "union_type_define", "$@15", "$@16",
  "enum_tag_def", "enum_type_define", "$@17", "$@18",
  "struct_or_union_definition", "enum_definition", "opt_trailing_comma",
  "enum_def_list", "enum_def_list_reentrance", "enum_const_def",
  "enum_constant", "field_list", "$@19", "$@20", "field_list_reentrance",
  "comp_decl", "comp_decl_list", "comp_decl_list_reentrance", "$@21",
  "$@22", "comp_declarator", "simple_comp", "bit_field", "$@23", "width",
  "opt_declarator", "declarator", "func_declarator",
  "declarator_reentrance_bis", "direct_declarator_reentrance_bis",
  "direct_declarator_reentrance", "array_decl", "pointer_start",
  "pointer_reentrance", "pointer", "ident_list", "$@24",
  "ident_list_reentrance", "ident", "typename_as_ident", "any_ident",
  "opt_param_type_list", "$@25", "param_type_list", "$@26",
  "param_type_list_bis", "param_list", "param_decl", "$@27",
  "param_decl_bis", "abs_decl_reentrance",
  "direct_abs_decl_reentrance_bis", "direct_abs_decl_reentrance",
  "opt_gcc_attrib", "gcc_attrib", "gcc_inner", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   118,   119,   119,   119,   120,   120,   121,   122,   122,
     122,   122,   122,   123,   124,   124,   126,   125,   125,   127,
     127,   128,   128,   128,   129,   130,   130,   131,   131,   132,
     132,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   134,   136,   135,   137,   137,   138,
     138,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   150,   150,   151,   152,   152,   153,
     154,   154,   155,   155,   156,   156,   157,   158,   158,   159,
     160,   160,   161,   161,   162,   163,   163,   164,   164,   165,
     165,   166,   167,   167,   168,   168,   169,   169,   170,   170,
     171,   171,   172,   172,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   174,   174,   175,   176,   177,   178,
     179,   180,   181,   181,   182,   182,   182,   183,   183,   184,
     184,   184,   184,   184,   184,   185,   186,   186,   187,   188,
     189,   190,   191,   192,   193,   193,   194,   194,   195,   195,
     196,   196,   196,   197,   198,   199,   199,   200,   200,   201,
     201,   201,   201,   201,   201,   203,   202,   204,   205,   202,
     207,   206,   208,   209,   206,   210,   210,   211,   211,   212,
     213,   214,   215,   216,   218,   217,   219,   219,   220,   221,
     221,   221,   222,   222,   223,   223,   224,   225,   225,   226,
     227,   226,   226,   228,   228,   230,   229,   229,   231,   233,
     232,   234,   234,   235,   235,   236,   237,   237,   238,   239,
     239,   240,   240,   241,   241,   242,   243,   243,   244,   244,
     245,   245,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,   246,   247,   248,   249,   250,   251,   252,   254,
     253,   255,   253,   256,   258,   257,   259,   257,   260,   262,
     261,   263,   261,   264,   264,   265,   265,   266,   266,   267,
     268,   268,   269,   269,   270,   272,   273,   271,   274,   274,
     274,   275,   275,   276,   278,   277,   279,   277,   280,   280,
     281,   283,   282,   284,   285,   285,   286,   287,   288,   288,
     289,   290,   290,   290,   290,   290,   290,   291,   292,   293,
     293,   294,   296,   295,   297,   297,   298,   299,   300,   300,
     301,   302,   301,   304,   303,   305,   305,   306,   306,   308,
     307,   309,   309,   309,   310,   310,   310,   311,   312,   312,
     312,   312,   312,   313,   313,   314,   315,   315,   315,   315,
     315,   315,   315,   315,   315
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     3,     0,     1,     1,
       1,     2,     3,     2,     3,     3,     0,     5,     2,     0,
       1,     1,     2,     2,     1,     4,     2,     0,     1,     1,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     0,     4,     1,     1,     1,
       1,     1,     5,     2,     2,     3,     3,     1,     5,     7,
       7,     5,     9,     1,     1,     1,     1,     2,     4,     1,
       1,     5,     1,     3,     0,     1,     1,     0,     1,     1,
       1,     3,     1,     3,     2,     1,     3,     1,     3,     1,
       3,     2,     1,     4,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     2,     2,     2,     2,     2,
       2,     2,     1,     3,     1,     1,     1,     3,     3,     1,
       1,     1,     1,     1,     1,     4,     1,     1,     2,     2,
       1,     3,     3,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     1,     0,     0,     3,
       0,     1,     0,     0,     3,     2,     3,     2,     2,     2,
       2,     0,     1,     1,     0,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     1,     2,
       0,     3,     2,     0,     1,     0,     3,     2,     1,     0,
       3,     1,     3,     0,     1,     1,     1,     3,     1,     1,
       3,     1,     4,     0,     1,     1,     1,     1,     1,     2,
       0,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     0,
       5,     0,     5,     2,     0,     5,     0,     5,     2,     0,
       5,     0,     5,     0,     1,     0,     2,     0,     1,     1,
       1,     3,     1,     3,     1,     0,     0,     3,     2,     2,
       3,     2,     1,     1,     0,     3,     0,     5,     1,     1,
       1,     0,     4,     1,     0,     1,     1,     1,     2,     1,
       1,     1,     3,     1,     4,     4,     3,     4,     2,     1,
       2,     1,     0,     2,     1,     3,     1,     1,     1,     1,
       0,     0,     2,     0,     2,     1,     3,     1,     3,     0,
       2,     2,     2,     1,     1,     1,     2,     1,     3,     3,
       4,     3,     4,     0,     1,     6,     0,     1,     1,     1,
       1,     4,     4,     8,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     4,   253,    10,   226,   227,   192,   189,   193,   190,
     191,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,     0,   259,     0,     0,     0,
       7,     9,     0,     8,     0,     0,   213,   213,   182,   194,
     195,   197,   200,   188,   197,   225,   196,   238,   236,   237,
     235,   261,   233,     0,   234,     0,   232,     7,    11,   254,
     269,   257,   255,     0,   264,   256,     1,     0,     7,     5,
       0,    16,    13,   177,   178,   326,   230,     0,   211,   216,
     179,   214,   215,   167,   306,   309,   310,   313,   319,   321,
       0,   311,   180,   209,   167,   307,   199,   198,   197,   202,
       0,   266,   271,    12,   275,   285,   285,     6,    18,   170,
     228,   231,   318,     0,     0,     0,    15,   166,   168,   353,
      74,   333,   320,   308,    14,   201,   285,   285,   275,   327,
       0,   277,   279,   280,   282,   328,   329,   284,     0,   274,
     286,     0,     0,   171,   173,   229,   312,   163,   164,   161,
     162,   159,   160,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    72,   221,    70,    80,   108,    82,
      85,    87,   109,   102,    89,    94,    96,    98,   100,    92,
     105,   106,   107,   110,   111,   112,   113,   129,   125,   104,
     130,   131,   133,   134,   136,   137,   132,   126,   212,   218,
     124,   217,     0,     0,   210,   354,   122,     0,    75,    76,
      79,   316,     0,     0,     0,   339,     0,     0,     0,   270,
     278,   276,     0,   260,     0,   265,     0,     0,     0,     0,
      69,     0,     0,     0,     0,    77,     0,     0,   170,    57,
       0,     0,    21,    34,    24,    32,    33,    35,    36,    37,
      38,    39,    40,    41,    42,    47,    48,    49,    50,    51,
       0,    63,    64,    65,     0,   124,     0,   223,   219,   118,
      92,   116,   117,   119,     0,   121,   120,     0,   115,    91,
      84,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   153,     0,   154,     0,   156,   155,     0,   149,   148,
       0,   152,   151,   150,     0,   158,   157,     0,   139,   138,
       0,   144,     0,     0,   169,     0,   213,     0,   317,     0,
     315,   323,   324,   314,   334,   335,   337,     0,   262,   267,
     272,   281,   283,   208,   294,   203,   205,   287,     0,    26,
      43,    53,    67,    54,     0,     0,    77,     0,     0,    78,
       0,     0,     0,    17,    23,    22,    45,    44,   174,   224,
       0,     0,   128,   127,     0,   185,   186,     0,    81,    83,
      86,    88,    90,    95,    97,    99,   101,   103,    73,     0,
     146,     0,   145,   141,   140,   142,   175,   356,   123,     0,
     339,   343,   340,   291,   293,   304,   207,   204,   203,   289,
       0,   288,     0,     0,     0,     0,    56,    55,     0,     0,
       0,     0,    29,     0,   220,   222,   114,    93,    74,   331,
     187,   344,   183,   345,   347,     0,   135,   143,     0,   176,
     359,     0,   357,   358,     0,     0,   360,   364,     0,   325,
     336,   338,   331,   341,   344,   342,   296,   353,   298,   299,
       0,   300,   206,   290,    68,     0,     0,    77,     0,     0,
      25,    31,    30,    46,     0,     0,   339,     0,   346,    74,
     331,    71,   147,     0,     0,     0,     0,   304,   295,   301,
       0,    58,     0,    52,    61,   349,   351,   332,   348,     0,
       0,     0,     0,     0,   355,   353,     0,     0,     0,    77,
     350,   352,   361,   362,     0,   297,   303,   302,    60,    59,
       0,     0,     0,     0,    62,     0,   363
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,    29,    69,    30,    31,    32,    72,   109,   240,
     241,   242,   243,   410,   411,   244,   245,   246,   413,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   164,   206,   207,   208,
     348,   264,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   210,   187,   188,   189,   190,   191,   192,
     193,   383,   194,   195,   196,   381,   382,   300,   304,   292,
     294,   297,   307,   197,   116,   117,   118,   202,   142,   143,
     144,   266,   314,    33,    34,   315,    36,   316,   420,   283,
     284,   365,    38,    39,    40,    41,    42,    96,    43,    98,
     396,   333,   398,   334,    78,   119,    79,    92,    81,    82,
     198,   267,   199,   360,    44,    45,   111,   112,    46,    47,
      61,    48,    49,    50,    51,    52,    63,   100,    53,    54,
     106,   127,    55,    56,   104,   128,   138,   130,   221,   131,
     132,   133,   134,   139,   140,   224,   337,   338,   393,   394,
     395,   477,   447,   448,   449,   496,   507,   450,    93,    94,
      84,    85,    86,    87,    88,    89,    90,   212,   213,   321,
     200,   136,   137,   465,   466,   214,   215,   324,   325,   326,
     327,   392,   467,   423,   424,   204,   205,   438
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -403
static const yytype_int16 yypact[] =
{
     464,     5,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,  -403,  -403,    27,    57,    43,    63,   519,
    -403,  -403,    33,  -403,     8,    15,    32,    32,  -403,  -403,
    -403,  1075,  -403,  -403,  1075,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,    34,  -403,    40,  -403,  -403,  -403,  -403,
    -403,    61,    65,    68,  -403,    72,  -403,     5,  -403,  -403,
      41,  -403,  -403,  -403,  -403,  -403,   104,    32,    38,  -403,
    -403,  -403,    83,    29,  -403,  -403,     7,  -403,  -403,    51,
      35,  -403,  -403,  -403,    36,    -4,  -403,  -403,  1075,  -403,
      92,  -403,  -403,  -403,    64,    95,    95,  -403,  -403,  1108,
    -403,   104,  -403,   106,   896,    32,  -403,  -403,  -403,    93,
     908,    30,  -403,  -403,  -403,  -403,    95,    95,    64,  -403,
     112,   124,  -403,  -403,   123,  -403,  -403,  -403,   130,  -403,
    -403,   144,   778,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,   896,   908,   908,   908,   908,   957,   957,
     969,   908,   908,   574,  -403,  -403,    44,   122,  -403,   127,
     128,   121,  -403,  -403,   125,   129,    74,    77,   -16,    90,
    -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,   109,
    -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  1075,   116,  -403,  -403,  -403,   166,  -403,  -403,
     165,  -403,   171,   234,   173,  -403,   172,   174,   175,  -403,
      64,  -403,   908,  -403,   613,  -403,   114,   170,   908,   177,
    -403,   287,   126,   132,   239,   908,   133,   135,  1108,  -403,
     185,   651,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
     157,  -403,  -403,  -403,   186,   168,  1075,   184,  -403,  -403,
    -403,  -403,  -403,  -403,   847,  -403,  -403,   574,  -403,  -403,
    -403,   192,   193,   194,  1075,   908,   908,   908,   908,   908,
     908,  -403,   908,  -403,   908,  -403,  -403,   908,  -403,  -403,
     908,  -403,  -403,  -403,   908,  -403,  -403,   908,  -403,  -403,
     908,   908,    64,    64,  -403,   191,    32,   146,  -403,   908,
    -403,   195,  -403,  -403,  -403,   196,  -403,  1075,  -403,  -403,
    -403,  -403,  -403,  -403,   198,   613,  -403,  1006,   199,  -403,
    -403,  -403,   200,  -403,   213,   908,   908,   201,   203,  -403,
     908,   908,   828,  -403,  -403,  -403,  -403,  -403,  -403,   896,
     205,   204,  -403,  -403,   908,  -403,    12,   187,   122,   127,
     128,   121,   125,   129,    74,    77,   -16,  -403,  -403,   208,
    -403,   216,   212,  -403,  -403,  -403,  1075,   108,  -403,   234,
     207,    50,  -403,  -403,   214,    32,  -403,  -403,   613,  -403,
     217,  -403,   908,   149,   218,   220,  -403,  -403,   222,   227,
     225,   701,  -403,   287,  -403,  -403,  -403,  -403,   908,    -1,
    -403,    82,  -403,  -403,    86,   908,  -403,  -403,   908,  -403,
    -403,   188,  -403,  -403,   189,   197,  -403,  -403,   235,  -403,
    -403,  -403,    47,  -403,    52,  -403,  -403,    93,  -403,  -403,
     219,   221,  -403,  -403,  -403,   908,   287,   908,   287,   287,
    -403,  -403,  -403,  -403,   236,   241,  -403,   243,  -403,   908,
     245,  -403,  -403,   300,   234,   234,   248,    32,  -403,  -403,
     249,   271,   250,  -403,  -403,  -403,  -403,  -403,  -403,   251,
     253,   255,   256,   252,  -403,    93,   908,   254,   287,   908,
    -403,  -403,  -403,  -403,   313,  -403,  -403,  -403,  -403,  -403,
     260,   269,   287,   330,  -403,   277,  -403
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -403,  -403,  -403,     1,   314,  -403,  -403,  -403,  -403,  -403,
    -403,   103,  -403,  -403,  -403,  -207,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,  -403,  -403,  -403,  -399,   -97,  -378,  -221,
    -327,  -117,  -403,    59,  -403,    60,    58,    62,  -403,  -134,
      73,    56,    55,    67,    66,  -146,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,    45,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,  -403,   268,  -403,  -403,  -403,   131,  -403,
    -403,  -403,  -237,  -403,  -403,    42,  -403,    49,  -403,    88,
    -403,  -403,  -241,  -403,  -403,  -403,  -403,    -8,    18,  -403,
     -31,  -296,  -403,  -403,  -403,  -403,   257,   332,  -403,  -403,
    -403,  -403,  -148,  -403,  -206,   -28,  -403,  -403,  -199,  -403,
     176,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,  -403,
    -403,  -403,  -403,  -403,  -403,  -403,   -46,   242,  -403,  -403,
    -403,   151,  -403,  -403,  -403,  -403,  -403,    37,  -403,  -403,
    -403,  -403,  -104,  -403,  -403,  -403,  -403,  -403,   -34,  -403,
     -33,   -84,  -403,  -403,   289,  -403,  -334,  -403,  -403,  -403,
     -36,  -403,  -105,   -94,  -403,  -403,  -403,   -87,  -403,   -10,
    -403,  -403,  -315,  -369,  -403,  -402,  -403,  -403
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -331
static const yytype_int16 yytable[] =
{
      91,    91,    83,   209,    95,   268,   123,   342,   270,   270,
     270,   270,   275,   276,   278,   270,   270,   165,   335,   405,
     269,   271,   272,   273,   344,   336,   471,   279,   280,   358,
    -165,    59,   421,  -322,    70,    75,    99,  -165,    75,   397,
     464,    91,    35,   366,   113,   478,   282,    59,   110,    37,
      75,   422,   468,    75,    91,    75,   165,   444,   103,    97,
     141,    59,    97,    66,  -330,  -306,  -306,    75,   135,   107,
     129,    35,  -306,    57,    58,   468,   445,    73,    37,    91,
     216,   217,  -306,   145,    74,   421,   391,   301,   302,   303,
     125,   489,   135,   505,    60,   211,  -165,   506,  -209,  -209,
      71,   101,   397,  -165,    76,  -209,   265,   102,   444,   108,
      64,   209,  -330,   418,   419,  -209,    97,    76,   349,     4,
       5,   120,   121,   430,   114,   332,   418,   419,  -268,   335,
     482,   335,  -258,   285,   286,   105,   336,    76,   336,  -263,
     270,   270,   270,   270,   270,   412,   270,    77,   270,   429,
      77,   270,    76,   115,   270,    76,    76,   282,   270,   126,
     282,   418,   442,  -273,   418,   442,   418,   442,   367,   203,
     377,   146,   510,   295,   296,   305,   306,   322,   298,   299,
     219,   454,   339,   340,   135,   431,   432,   433,   434,   435,
     436,   437,   335,   379,   220,   265,   418,   419,   223,   336,
     469,   470,    62,    65,   462,   265,   463,   384,   384,   222,
     378,   414,   225,   287,   380,   290,   308,   309,   270,   288,
     291,   289,   388,   310,   311,   312,   313,   293,   404,   349,
     417,   317,   318,   408,   409,   319,   320,    75,   323,   341,
     328,   345,   329,   330,   347,   356,   343,   346,   350,   481,
     351,   483,   484,   353,   359,   357,   -66,   362,   363,   364,
     386,   387,   165,   403,   455,   389,   390,  -292,   401,   416,
     406,   402,   407,   415,   426,   425,   135,   135,   440,   270,
      91,   427,   428,   456,   446,   209,   453,   458,   226,   457,
      75,   509,   459,   460,   147,   148,   149,   150,   151,   152,
     476,   209,   485,   473,   474,   514,   486,   479,   488,  -305,
    -330,   491,   475,   494,   497,   498,   265,   500,   501,   499,
     502,   503,   504,   508,   511,   512,   227,   228,   229,   230,
     231,   472,   232,   233,   234,   235,   236,   237,   480,   513,
     349,   515,   516,    68,   355,   368,   370,   369,   373,   374,
     270,   371,   209,   439,   238,    91,   239,   443,   385,    91,
     123,   451,   124,   372,   375,   361,   376,   452,    80,   352,
     218,   331,   201,   495,   400,   265,   490,   265,   122,   487,
     441,   154,   349,     0,     0,     0,     0,     0,   155,   156,
       0,     0,   157,     0,   158,   159,   160,   161,   162,     0,
       0,     0,   163,     0,     0,     0,    91,     0,    91,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     265,     0,   265,   265,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   492,   493,
       0,    91,     0,   451,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   265,     0,    -2,     1,     0,  -181,     0,     0,
       2,     0,     0,     0,     0,     0,   265,     3,     0,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    -3,
      67,     0,  -181,     0,     0,     2,     0,     0,     0,     0,
       0,     0,     3,  -181,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -181,
       0,     0,     0,     0,     0,   281,     0,    75,     0,  -181,
    -184,   147,   148,   149,   150,   151,   152,     0,  -181,  -184,
    -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,  -184,
    -184,  -184,  -184,     0,     0,     0,     0,     0,     0,     2,
       0,     0,     0,     0,  -181,     0,     0,     0,     4,     5,
       0,     0,     0,     0,  -181,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,   226,     0,    75,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   354,     0,     0,     0,   154,     0,
       0,     0,     0,     0,     0,   155,   156,     0,     0,   157,
       0,   158,   159,   160,   161,   162,     0,     0,     0,   163,
     227,   228,   229,   230,   231,     0,   232,   233,   234,   235,
     236,   237,   226,     0,    75,     0,     0,     0,   147,   148,
     149,   150,   151,   152,   461,     0,     0,     0,   238,   -20,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     227,   228,   229,   230,   231,   154,   232,   233,   234,   235,
     236,   237,   155,   156,     0,     0,   157,     0,   158,   159,
     160,   161,   162,     0,     0,     0,   163,     0,   238,   -28,
     239,     0,     0,     0,     0,     0,     0,     0,     0,   226,
       0,    75,     0,     0,     0,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,   154,     0,     0,     0,     0,
       0,     0,   155,   156,     0,     0,   157,     0,   158,   159,
     160,   161,   162,     0,     0,     0,   163,   227,   228,   229,
     230,   231,     0,   232,   233,   234,   235,   236,   237,   226,
       0,    75,     0,     0,     0,   147,   148,   149,   150,   151,
     152,     0,     0,     0,     0,   238,   -19,   239,   281,     0,
      75,     0,     0,     0,   147,   148,   149,   150,   151,   152,
       0,     0,     0,     0,     0,     0,     0,   227,   228,   229,
     230,   231,   154,   232,   233,   234,   235,   236,   237,   155,
     156,     0,     0,   157,     0,   158,   159,   160,   161,   162,
       0,     0,     0,   163,     0,   238,   -27,   239,     0,    75,
       0,     0,     0,   147,   148,   149,   150,   151,   152,     0,
       0,    75,     0,     0,     0,   147,   148,   149,   150,   151,
     152,     0,   154,     0,     0,     0,     0,     0,     0,   155,
     156,     0,     0,   157,     0,   158,   159,   160,   161,   162,
       0,   154,     0,   163,     0,     0,     0,     0,   155,   156,
       0,     0,   157,     0,   158,   159,   160,   161,   162,     0,
      75,     0,   163,   153,   147,   148,   149,   150,   151,   152,
       0,     0,    75,     0,     0,     0,   147,   148,   149,   150,
     151,   152,     0,     0,     0,     0,     0,     0,     0,     0,
     154,     0,     0,     0,     0,     0,     0,   155,   156,     0,
       0,   157,   154,   158,   159,   160,   161,   162,     0,   155,
     156,   163,     2,   157,     0,   158,   159,   160,   161,   162,
       0,     4,     5,   163,     0,     0,     0,     0,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
       0,   154,     0,     0,     0,     0,     0,     0,   155,   156,
       0,     0,   157,   154,   158,   159,   160,   161,   162,     0,
     155,   156,   274,     0,   157,   399,   158,   159,   160,   161,
     162,     2,     0,     0,   277,     0,     0,     0,     0,     0,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,  -172,     0,     0,     0,     0,     0,
       0,     0,     0,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,  -172,
    -172,  -172,  -172,  -172,  -172,  -172,  -172
};

static const yytype_int16 yycheck[] =
{
      36,    37,    36,   120,    37,   153,    90,   228,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   114,   224,   346,
     154,   155,   156,   157,   231,   224,   425,   161,   162,   266,
       1,     4,   366,     3,     1,     3,    44,     1,     3,   335,
     418,    77,     0,   284,    77,   447,   163,     4,    76,     0,
       3,   366,   421,     3,    90,     3,   153,   391,    57,    41,
     106,     4,    44,     0,    65,    69,    70,     3,   104,    68,
       6,    29,    76,    68,    69,   444,   391,    69,    29,   115,
     126,   127,    86,   111,    69,   419,   327,   103,   104,   105,
      98,   469,   128,   495,    67,    65,    67,   496,    69,    70,
      67,    67,   398,    67,   105,    76,   142,    67,   442,    68,
      67,   228,    65,   114,   115,    86,    98,   105,   235,    15,
      16,   114,   115,    15,    86,   222,   114,   115,    67,   335,
     457,   337,    67,    89,    90,    67,   335,   105,   337,    67,
     286,   287,   288,   289,   290,   352,   292,   115,   294,   386,
     115,   297,   105,    70,   300,   105,   105,   274,   304,    67,
     277,   114,   115,    68,   114,   115,   114,   115,   285,    76,
     304,    65,   499,    99,   100,    85,    86,   213,   101,   102,
      68,   402,    68,    69,   220,    77,    78,    79,    80,    81,
      82,    83,   398,   310,    70,   231,   114,   115,    68,   398,
     114,   115,    26,    27,   411,   241,   413,   312,   313,    86,
     307,   359,    68,    91,   311,    94,   107,   108,   364,    92,
      95,    93,   319,   114,   115,   116,   117,    98,   345,   346,
     364,   115,    66,   350,   351,    70,    65,     3,    65,    69,
      68,   115,    68,    68,     5,    88,    69,   115,   115,   456,
     115,   458,   459,    68,    70,    69,    88,    65,    65,    65,
      69,   115,   359,    50,   115,    70,    70,    69,    69,    65,
      69,    71,    69,    68,    66,    88,   312,   313,    71,   425,
     316,    65,    70,    65,    70,   402,    69,    65,     1,    69,
       3,   498,    65,    68,     7,     8,     9,    10,    11,    12,
      65,   418,    66,   115,   115,   512,    65,    88,    65,    88,
      65,    11,   115,    65,    65,    44,   352,    66,    65,    69,
      65,    65,    70,    69,    11,    65,    39,    40,    41,    42,
      43,   428,    45,    46,    47,    48,    49,    50,   455,    70,
     457,    11,    65,    29,   241,   286,   288,   287,   292,   294,
     496,   289,   469,   389,    67,   391,    69,   391,   313,   395,
     444,   395,    94,   290,   297,   277,   300,   398,    36,   238,
     128,   220,   115,   477,   337,   411,   470,   413,    89,   466,
     390,    94,   499,    -1,    -1,    -1,    -1,    -1,   101,   102,
      -1,    -1,   105,    -1,   107,   108,   109,   110,   111,    -1,
      -1,    -1,   115,    -1,    -1,    -1,   442,    -1,   444,   442,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     456,    -1,   458,   459,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   474,   475,
      -1,   477,    -1,   477,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   498,    -1,     0,     1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    -1,   512,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     0,
       1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    13,    69,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     3,    -1,   115,
       6,     7,     8,     9,    10,    11,    12,    -1,    69,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,     6,
      -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    15,    16,
      -1,    -1,    -1,    -1,   115,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,     1,    -1,     3,    -1,    -1,    -1,     7,     8,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    94,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,   105,
      -1,   107,   108,   109,   110,   111,    -1,    -1,    -1,   115,
      39,    40,    41,    42,    43,    -1,    45,    46,    47,    48,
      49,    50,     1,    -1,     3,    -1,    -1,    -1,     7,     8,
       9,    10,    11,    12,    13,    -1,    -1,    -1,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    40,    41,    42,    43,    94,    45,    46,    47,    48,
      49,    50,   101,   102,    -1,    -1,   105,    -1,   107,   108,
     109,   110,   111,    -1,    -1,    -1,   115,    -1,    67,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,    -1,    -1,    -1,     7,     8,     9,    10,    11,
      12,    -1,    -1,    -1,    -1,    94,    -1,    -1,    -1,    -1,
      -1,    -1,   101,   102,    -1,    -1,   105,    -1,   107,   108,
     109,   110,   111,    -1,    -1,    -1,   115,    39,    40,    41,
      42,    43,    -1,    45,    46,    47,    48,    49,    50,     1,
      -1,     3,    -1,    -1,    -1,     7,     8,     9,    10,    11,
      12,    -1,    -1,    -1,    -1,    67,    68,    69,     1,    -1,
       3,    -1,    -1,    -1,     7,     8,     9,    10,    11,    12,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    43,    94,    45,    46,    47,    48,    49,    50,   101,
     102,    -1,    -1,   105,    -1,   107,   108,   109,   110,   111,
      -1,    -1,    -1,   115,    -1,    67,    68,    69,    -1,     3,
      -1,    -1,    -1,     7,     8,     9,    10,    11,    12,    -1,
      -1,     3,    -1,    -1,    -1,     7,     8,     9,    10,    11,
      12,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,    -1,    -1,   105,    -1,   107,   108,   109,   110,   111,
      -1,    94,    -1,   115,    -1,    -1,    -1,    -1,   101,   102,
      -1,    -1,   105,    -1,   107,   108,   109,   110,   111,    -1,
       3,    -1,   115,    67,     7,     8,     9,    10,    11,    12,
      -1,    -1,     3,    -1,    -1,    -1,     7,     8,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,    -1,
      -1,   105,    94,   107,   108,   109,   110,   111,    -1,   101,
     102,   115,     6,   105,    -1,   107,   108,   109,   110,   111,
      -1,    15,    16,   115,    -1,    -1,    -1,    -1,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
      -1,    -1,   105,    94,   107,   108,   109,   110,   111,    -1,
     101,   102,   115,    -1,   105,    69,   107,   108,   109,   110,
     111,     6,    -1,    -1,   115,    -1,    -1,    -1,    -1,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     6,    13,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,   119,   120,
     122,   123,   124,   211,   212,   213,   214,   215,   220,   221,
     222,   223,   224,   226,   242,   243,   246,   247,   249,   250,
     251,   252,   253,   256,   257,   260,   261,    68,    69,     4,
      67,   248,   248,   254,    67,   248,     0,     1,   122,   121,
       1,    67,   125,    69,    69,     3,   105,   115,   232,   234,
     235,   236,   237,   286,   288,   289,   290,   291,   292,   293,
     294,   298,   235,   286,   287,   288,   225,   226,   227,   225,
     255,    67,    67,   121,   262,    67,   258,   121,    68,   126,
     243,   244,   245,   288,    86,    70,   202,   203,   204,   233,
     114,   115,   292,   289,   202,   225,    67,   259,   263,     6,
     265,   267,   268,   269,   270,   298,   299,   300,   264,   271,
     272,   264,   206,   207,   208,   243,    65,     7,     8,     9,
      10,    11,    12,    67,    94,   101,   102,   105,   107,   108,
     109,   110,   111,   115,   154,   155,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   182,   183,   184,
     185,   186,   187,   188,   190,   191,   192,   201,   238,   240,
     298,   234,   205,    76,   313,   314,   155,   156,   157,   159,
     181,    65,   295,   296,   303,   304,   264,   264,   265,    68,
      70,   266,    86,    68,   273,    68,     1,    39,    40,    41,
      42,    43,    45,    46,    47,    48,    49,    50,    67,    69,
     127,   128,   129,   130,   133,   134,   135,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   159,   298,   209,   239,   240,   167,
     173,   167,   167,   167,   115,   173,   173,   115,   173,   167,
     167,     1,   159,   217,   218,    89,    90,    91,    92,    93,
      94,    95,   197,    98,   198,    99,   100,   199,   101,   102,
     195,   103,   104,   105,   196,    85,    86,   200,   107,   108,
     114,   115,   116,   117,   210,   213,   215,   115,    66,    70,
      65,   297,   298,    65,   305,   306,   307,   308,    68,    68,
      68,   269,   155,   229,   231,   242,   246,   274,   275,    68,
      69,    69,   157,    69,   133,   115,   115,     5,   158,   159,
     115,   115,   206,    68,    13,   129,    88,    69,   210,    70,
     241,   217,    65,    65,    65,   219,   220,   159,   161,   163,
     164,   165,   168,   169,   170,   171,   172,   167,   155,   159,
     155,   193,   194,   189,   300,   189,    69,   115,   155,    70,
      70,   220,   309,   276,   277,   278,   228,   229,   230,    69,
     275,    69,    71,    50,   159,   158,    69,    69,   159,   159,
     131,   132,   133,   136,   240,    68,    65,   167,   114,   115,
     216,   294,   310,   311,   312,    88,    66,    65,    70,   210,
      15,    77,    78,    79,    80,    81,    82,    83,   315,   298,
      71,   307,   115,   286,   294,   310,    70,   280,   281,   282,
     285,   286,   228,    69,   157,   115,    65,    69,    65,    65,
      68,    13,   133,   133,   156,   301,   302,   310,   311,   114,
     115,   154,   155,   115,   115,   115,    65,   279,   313,    88,
     159,   133,   158,   133,   133,    66,    65,   305,    65,   156,
     301,    11,   298,   298,    65,   280,   283,    65,    44,    69,
      66,    65,    65,    65,    70,   313,   154,   284,    69,   133,
     158,    11,    65,    70,   133,    11,    65
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval)
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





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

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
  if (yyn == YYPACT_NINF)
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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

/* Line 1464 of yacc.c  */
#line 234 "rv_gram.y"
    {
			if (gProject->Parse_TOS->err_cnt == 0)
			  *gProject->Parse_TOS->yyerrstream
			  << "Warning: ANSI/ISO C forbids an empty source file.\n";
			gProject->Parse_TOS->transUnit = (TransUnit*) NULL;
			(yyval.transunit) = (TransUnit*) NULL;
		;}
    break;

  case 3:

/* Line 1464 of yacc.c  */
#line 242 "rv_gram.y"
    {
			if (gProject->Parse_TOS->err_cnt)
			{
				*gProject->Parse_TOS->yyerrstream
				<< gProject->Parse_TOS->err_cnt << " errors found.\n";
				gProject->Parse_TOS->transUnit = (TransUnit*) NULL;
			} else {
				gProject->Parse_TOS->transUnit = (yyval.transunit);
			}
		;}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 253 "rv_gram.y"
    {
			*gProject->Parse_TOS->yyerrstream << "Errors - Aborting parse.\n";
			gProject->Parse_TOS->transUnit = (TransUnit*) NULL;
			YYACCEPT;
		;}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 261 "rv_gram.y"
    {
			(yyval.transunit) = gProject->Parse_TOS->transUnit;
			(yyval.transunit)->add((yyvsp[(1) - (2)].stemnt));
		;}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 266 "rv_gram.y"
    {
			(yyval.transunit)->add((yyvsp[(2) - (3)].stemnt));
		;}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 272 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->ReinitializeCtxt();
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScopes(FILE_SCOPE);
			gProject->Parse_TOS->err_top_level = 0;            
		;}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 281 "rv_gram.y"
    {
			(yyval.stemnt) = (yyvsp[(1) - (1)].declStemnt);

			prvhooks->flush_buffer((yyvsp[(1) - (1)].declStemnt));
		;}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 287 "rv_gram.y"
    {
			(yyval.stemnt) = (yyvsp[(1) - (1)].functionDef);

			prvhooks->flush_buffer((yyvsp[(1) - (1)].functionDef));
		;}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 293 "rv_gram.y"
    {
			(yyval.stemnt) = (yyvsp[(1) - (1)].stemnt);
			prvhooks->flush_buffer();
		;}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 298 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		;}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 302 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		;}
    break;

  case 13:

/* Line 1464 of yacc.c  */
#line 308 "rv_gram.y"
    {
			if ((yyvsp[(2) - (2)].stemnt) != NULL)
			{
				(yyval.functionDef) = new FunctionDef((yyvsp[(2) - (2)].stemnt)->location);
				Block *blk = (Block*) (yyvsp[(2) - (2)].stemnt);
	
				(yyval.functionDef)->decl = (yyvsp[(1) - (2)].decl);
				
				if ((yyvsp[(1) - (2)].decl)->name &&
					(yyvsp[(1) - (2)].decl)->name->entry)
					(yyvsp[(1) - (2)].decl)->name->entry->u2FunctionDef = (yyval.functionDef);
				
				// Steal internals of the compound statement
				(yyval.functionDef)->head = blk->head;
				(yyval.functionDef)->tail = blk->tail;
	
				blk->head = blk->tail = (Statement*) NULL;
				delete (yyvsp[(2) - (2)].stemnt);

		if( (yyvsp[(1) - (2)].decl)->name )
		  prvhooks->grab_scope( (yyvsp[(1) - (2)].decl)->name->name );
			}
			else
			{
				delete (yyvsp[(1) - (2)].decl);
				(yyval.functionDef) = (FunctionDef*) NULL;
			}
		;}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 339 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();
			
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = (yyvsp[(2) - (3)].decl);

			if ((yyval.decl)->form != NULL)
			{
				assert(gProject->Parse_TOS->err_top_level ||
					   (yyval.decl)->form->type == TT_Function );
	
				(yyval.decl)->extend((yyvsp[(1) - (3)].base));
	
				/* This is adding K&R-style declarations if $3 exists */
				if ((yyvsp[(3) - (3)].decl) != NULL)
				{
					FunctionType *fnc = (FunctionType*) ((yyval.decl)->form);
					fnc->KnR_decl = true;
					Decl *param = (yyvsp[(3) - (3)].decl);
					while (param != NULL)
					{
						Decl *next= param->next;
							delete param ;
						param = next;
					}
				}
			}
		;}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 368 "rv_gram.y"
    {

			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();
			
			(yyval.decl) = (yyvsp[(2) - (3)].decl);

			if ((yyval.decl)->form != NULL)
			{
				assert(gProject->Parse_TOS->err_top_level ||
					   (yyval.decl)->form->type == TT_Function );
				(yyval.decl)->extend((yyvsp[(1) - (3)].base));
	
				/* This is adding K&R-style declarations if $3 exists */
				if ((yyvsp[(3) - (3)].decl) != NULL)
				{
					FunctionType *fnc = (FunctionType*) ((yyval.decl)->form);
					fnc->KnR_decl = true;
					Decl *param = (yyvsp[(3) - (3)].decl);
					while (param != NULL)
					{
						Decl *next= param->next;
							delete param ;
						param = next;
					}
				}
			}
		;}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 401 "rv_gram.y"
    {  
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ReEnterScope();
		;}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 406 "rv_gram.y"
    {
			Block*    block = new Block(*(yyvsp[(1) - (5)].loc));
			(yyval.stemnt) = block;
			block->addDecls((yyvsp[(3) - (5)].decl));
			block->addStatements(ReverseList((yyvsp[(4) - (5)].stemnt)));
			if (gProject->Parse_TOS->transUnit)
			{
				yyCheckLabelsDefinition(gProject->Parse_TOS->transUnit->contxt.labels);
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
			}
		;}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 419 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		;}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 425 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		;}
    break;

  case 22:

/* Line 1464 of yacc.c  */
#line 433 "rv_gram.y"
    {
			/* Hook them up backwards, we'll reverse them later. */
			if ((yyvsp[(2) - (2)].stemnt))
			{
				(yyvsp[(2) - (2)].stemnt)->next = (yyvsp[(1) - (2)].stemnt);
				(yyval.stemnt) = (yyvsp[(2) - (2)].stemnt);
			}
		;}
    break;

  case 23:

/* Line 1464 of yacc.c  */
#line 442 "rv_gram.y"
    {    /* preprocessor #line directive */
			/* Hook them up backwards, we'll reverse them later. */
			if ((yyvsp[(2) - (2)].stemnt))
			{
				(yyvsp[(2) - (2)].stemnt)->next = (yyvsp[(1) - (2)].stemnt);
				(yyval.stemnt) = (yyvsp[(2) - (2)].stemnt);
			}
		;}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 460 "rv_gram.y"
    {
			Block*    block = new Block(*(yyvsp[(1) - (4)].loc));
			(yyval.stemnt) = block;
			block->addDecls((yyvsp[(2) - (4)].decl));
			block->addStatements(ReverseList((yyvsp[(3) - (4)].stemnt)));
			
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
		;}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 470 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		;}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 476 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		;}
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 484 "rv_gram.y"
    {
			/* Hook them up backwards, we'll reverse them later. */
			if ((yyvsp[(2) - (2)].stemnt))
			{
				(yyvsp[(2) - (2)].stemnt)->next = (yyvsp[(1) - (2)].stemnt);
				(yyval.stemnt) = (yyvsp[(2) - (2)].stemnt);
			}
		;}
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 493 "rv_gram.y"
    {    /* preprocessor #line directive */
			/* Hook them up backwards, we'll reverse them later. */
			if ((yyvsp[(2) - (2)].stemnt))
			{
				(yyvsp[(2) - (2)].stemnt)->next = (yyvsp[(1) - (2)].stemnt);
				(yyval.stemnt) = (yyvsp[(2) - (2)].stemnt);
			}
		;}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 515 "rv_gram.y"
    {
			delete (yyvsp[(2) - (2)].loc);
			(yyval.stemnt) = (Statement*) NULL;
		;}
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 522 "rv_gram.y"
    {
			(yyval.stemnt) = new ExpressionStemnt((yyvsp[(1) - (2)].value),*(yyvsp[(2) - (2)].loc));
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 529 "rv_gram.y"
    {
	  if( (yyvsp[(1) - (2)].label)->type == LT_Goto )
		prvhooks->process_label((yyvsp[(1) - (2)].label)->name->name); 
	;}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 534 "rv_gram.y"
    {
			(yyval.stemnt) = (yyvsp[(4) - (4)].stemnt);
			if ((yyval.stemnt) == NULL)
			{
			  /* Sorry, we must have a statement here. */
			  if(yyerr("Can't have a label at the end of a block! "))
				YYERROR;
				
			  (yyval.stemnt) = new Statement(ST_NullStemnt,*(yyvsp[(2) - (4)].loc));
			}
			(yyval.stemnt)->addHeadLabel((yyvsp[(1) - (4)].label));
			delete (yyvsp[(2) - (4)].loc);
		;}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 559 "rv_gram.y"
    {
			(yyval.stemnt) = new SwitchStemnt((yyvsp[(3) - (5)].value),(yyvsp[(5) - (5)].stemnt),*(yyvsp[(1) - (5)].loc));
			delete (yyvsp[(1) - (5)].loc);
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(4) - (5)].loc);
		;}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 568 "rv_gram.y"
    {
			(yyval.stemnt) = new Statement(ST_BreakStemnt,*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 576 "rv_gram.y"
    {
			(yyval.stemnt) = new Statement(ST_ContinueStemnt,*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 584 "rv_gram.y"
    {
			(yyval.stemnt) = new ReturnStemnt((yyvsp[(2) - (3)].value),*(yyvsp[(1) - (3)].loc));
			delete (yyvsp[(1) - (3)].loc);
			delete (yyvsp[(3) - (3)].loc);
		;}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 592 "rv_gram.y"
    {
			(yyval.stemnt) = new GotoStemnt((yyvsp[(2) - (3)].symbol),*(yyvsp[(1) - (3)].loc));
			delete (yyvsp[(1) - (3)].loc);
			delete (yyvsp[(3) - (3)].loc);
		;}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 600 "rv_gram.y"
    {
			(yyval.stemnt) = new Statement(ST_NullStemnt,*(yyvsp[(1) - (1)].loc));
			delete (yyvsp[(1) - (1)].loc);
		;}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 607 "rv_gram.y"
    {
			(yyval.stemnt) = new IfStemnt((yyvsp[(3) - (5)].value),(yyvsp[(5) - (5)].stemnt),*(yyvsp[(1) - (5)].loc));
			delete (yyvsp[(1) - (5)].loc);
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(4) - (5)].loc);
		;}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 616 "rv_gram.y"
    {
			(yyval.stemnt) = new IfStemnt((yyvsp[(3) - (7)].value),(yyvsp[(5) - (7)].stemnt),*(yyvsp[(1) - (7)].loc),(yyvsp[(7) - (7)].stemnt));
			delete (yyvsp[(1) - (7)].loc);
			delete (yyvsp[(2) - (7)].loc);
			delete (yyvsp[(4) - (7)].loc);
			delete (yyvsp[(6) - (7)].loc);
		;}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 626 "rv_gram.y"
    {
			(yyval.stemnt) = new DoWhileStemnt((yyvsp[(5) - (7)].value),(yyvsp[(2) - (7)].stemnt),*(yyvsp[(1) - (7)].loc));
			delete (yyvsp[(1) - (7)].loc);
			delete (yyvsp[(3) - (7)].loc);
			delete (yyvsp[(4) - (7)].loc);
			delete (yyvsp[(6) - (7)].loc);
			delete (yyvsp[(7) - (7)].loc);
		;}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 637 "rv_gram.y"
    {
			(yyval.stemnt) = new WhileStemnt((yyvsp[(3) - (5)].value),(yyvsp[(5) - (5)].stemnt),*(yyvsp[(1) - (5)].loc));
			delete (yyvsp[(1) - (5)].loc);
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(4) - (5)].loc);
		;}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 647 "rv_gram.y"
    {
			(yyval.stemnt) = new ForStemnt((yyvsp[(3) - (9)].value),(yyvsp[(5) - (9)].value),(yyvsp[(7) - (9)].value),*(yyvsp[(1) - (9)].loc),(yyvsp[(9) - (9)].stemnt));
			delete (yyvsp[(1) - (9)].loc);
			delete (yyvsp[(2) - (9)].loc);
			delete (yyvsp[(4) - (9)].loc);
			delete (yyvsp[(6) - (9)].loc);
			delete (yyvsp[(8) - (9)].loc);
		;}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 663 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.label) = gProject->Parse_TOS->parseCtxt->Mk_named_label((yyvsp[(1) - (1)].symbol),
								gProject->Parse_TOS->transUnit->contxt.labels);
		;}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 671 "rv_gram.y"
    {
			(yyval.label) = new Label((yyvsp[(2) - (2)].value));
			delete (yyvsp[(1) - (2)].loc);
		;}
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 676 "rv_gram.y"
    {
			(yyval.label) = new Label((yyvsp[(2) - (4)].value),(yyvsp[(4) - (4)].value));
			delete (yyvsp[(1) - (4)].loc);
			delete (yyvsp[(3) - (4)].loc);
		;}
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 684 "rv_gram.y"
    {
			(yyval.label) = new Label(LT_Default);
			delete (yyvsp[(1) - (1)].loc);
		;}
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 701 "rv_gram.y"
    {
			(yyval.value) = new TrinaryExpr((yyvsp[(1) - (5)].value),(yyvsp[(3) - (5)].value),(yyvsp[(5) - (5)].value),*(yyvsp[(2) - (5)].loc));
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(4) - (5)].loc);
		;}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 710 "rv_gram.y"
    {
			(yyval.value) = (Globals::flags(GLBL_OUTLINE_NOW) && ((yyvsp[(2) - (3)].assignOp) == AO_MultEql || (yyvsp[(2) - (3)].assignOp) == AO_DivEql || (yyvsp[(2) - (3)].assignOp) == AO_ModEql)) ?  // change tag: OUTLINE_FUNCS			
					rv_parser.outline_assignment((yyvsp[(2) - (3)].assignOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location) :  
					new AssignExpr((yyvsp[(2) - (3)].assignOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);			
		;}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 718 "rv_gram.y"
    {
			(yyval.value) = (Expression*) NULL;
		;}
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 728 "rv_gram.y"
    {
		   (yyval.value) = (Expression*) NULL;
		;}
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 739 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_Or,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 747 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_And,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 754 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_Not,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		;}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 762 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_BitOr,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 770 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_BitXor,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 90:

/* Line 1464 of yacc.c  */
#line 778 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_BitAnd,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 785 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_BitNot,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		;}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 793 "rv_gram.y"
    {
			(yyval.value) = new CastExpr((yyvsp[(2) - (4)].type),(yyvsp[(4) - (4)].value),*(yyvsp[(1) - (4)].loc));
			delete (yyvsp[(1) - (4)].loc);
			delete (yyvsp[(3) - (4)].loc);
		;}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 802 "rv_gram.y"
    {
			(yyval.value) = new RelExpr((yyvsp[(2) - (3)].relOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);
		;}
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 809 "rv_gram.y"
    {
			(yyval.value) = new RelExpr((yyvsp[(2) - (3)].relOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);
		;}
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 816 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr((yyvsp[(2) - (3)].binOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);
		;}
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 823 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr((yyvsp[(2) - (3)].binOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);			
		;}
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 830 "rv_gram.y"
    {			
			(yyval.value) = (Globals::flags(GLBL_OUTLINE_NOW)) ? 
				rv_parser.outline((yyvsp[(2) - (3)].binOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value) -> location): // ofer. change tag: OUTLINE_FUNCS
				new BinaryExpr((yyvsp[(2) - (3)].binOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value) -> location);
		;}
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 850 "rv_gram.y"
    {
			(yyval.value) = new SizeofExpr((yyvsp[(3) - (4)].type),*(yyvsp[(1) - (4)].loc));
			delete (yyvsp[(1) - (4)].loc);
			delete (yyvsp[(2) - (4)].loc);
			delete (yyvsp[(4) - (4)].loc);
		;}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 857 "rv_gram.y"
    {
			(yyval.value) = new SizeofExpr((yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		;}
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 864 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_Minus,(yyvsp[(2) - (2)].value),HERE);
		;}
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 870 "rv_gram.y"
    {
			/* Unary plus is an ISO addition (for symmetry) - ignore it */
			(yyval.value) = (yyvsp[(2) - (2)].value);
		;}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 877 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_AddrOf,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		;}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 884 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_Deref,(yyvsp[(2) - (2)].value),HERE);
		;}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 890 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_PreInc,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		;}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 897 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_PreDec,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		;}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 905 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_Comma,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 912 "rv_gram.y"
    {
			if ((yyvsp[(1) - (1)].symbol)->entry == NULL && gProject->warn_variable)
			{
				yywarn("Undeclared variable");
			}

			(yyval.value) = new Variable((yyvsp[(1) - (1)].symbol), HERE);
		;}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 922 "rv_gram.y"
    {
			(yyval.value) = (yyvsp[(1) - (1)].consValue);
		;}
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 928 "rv_gram.y"
    {
			(yyval.value) = (yyvsp[(2) - (3)].value);
			delete (yyvsp[(1) - (3)].loc);
			delete (yyvsp[(3) - (3)].loc);
		;}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 934 "rv_gram.y"
    {
			(yyval.value) = (Expression*) NULL;
			delete (yyvsp[(1) - (3)].loc);
			delete (yyvsp[(3) - (3)].loc);
		;}
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 950 "rv_gram.y"
    {
			(yyval.value) = new IndexExpr((yyvsp[(1) - (4)].value),(yyvsp[(3) - (4)].value),*(yyvsp[(2) - (4)].loc));
			delete (yyvsp[(2) - (4)].loc);
			delete (yyvsp[(4) - (4)].loc);
		;}
    break;

  case 138:

/* Line 1464 of yacc.c  */
#line 962 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_PostInc,(yyvsp[(1) - (2)].value),*(yyvsp[(2) - (2)].loc));
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 139:

/* Line 1464 of yacc.c  */
#line 969 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_PostDec,(yyvsp[(1) - (2)].value),*(yyvsp[(2) - (2)].loc));
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 141:

/* Line 1464 of yacc.c  */
#line 979 "rv_gram.y"
    {
			Variable *var = new Variable((yyvsp[(3) - (3)].symbol),*(yyvsp[(2) - (3)].loc));
			BinaryExpr *be = new BinaryExpr(BO_Member,(yyvsp[(1) - (3)].value),var,*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
			(yyval.value) = be;

			// Lookup the component in its struct
			// if possible.
			if ((yyvsp[(1) - (3)].value)->etype == ET_Variable)
			{
				Variable  *var = (Variable*) (yyvsp[(1) - (3)].value);
				Symbol    *varName = var->name;
				SymEntry  *entry = varName->entry;

				if (entry && entry->uVarDecl)
				{
					entry->uVarDecl->lookup((yyvsp[(3) - (3)].symbol));
				}
			}
		;}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 1002 "rv_gram.y"
    {
			Variable *var = new Variable((yyvsp[(3) - (3)].symbol),*(yyvsp[(2) - (3)].loc));
			BinaryExpr *be = new BinaryExpr(BO_PtrMember,(yyvsp[(1) - (3)].value),var,*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
			(yyval.value) = be;

			// Lookup the component in its struct
			// if possible.
			if ((yyvsp[(1) - (3)].value)->etype == ET_Variable)
			{
				Variable  *var = (Variable*) (yyvsp[(1) - (3)].value);
				Symbol    *varName = var->name;
				SymEntry  *entry = varName->entry;

				if (entry && entry->uVarDecl)
				{
					entry->uVarDecl->lookup((yyvsp[(3) - (3)].symbol));
				}
			}
		;}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 1025 "rv_gram.y"
    {
			FunctionCall* fc = new FunctionCall((yyvsp[(1) - (4)].value),*(yyvsp[(2) - (4)].loc));

			/* add function args */
			fc->addArgs(ReverseList((yyvsp[(3) - (4)].value)));

			delete (yyvsp[(2) - (4)].loc);
			delete (yyvsp[(4) - (4)].loc);
			(yyval.value) = fc;
		;}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 1038 "rv_gram.y"
    {
			(yyval.value) = (Expression*) NULL;
		;}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 1046 "rv_gram.y"
    {
			(yyval.value) = (yyvsp[(3) - (3)].value);
			(yyval.value)->next = (yyvsp[(1) - (3)].value);

			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 1091 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ReEnterScope();
		;}
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 1096 "rv_gram.y"
    {
			(yyval.decl) = (Decl*) NULL;
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
		;}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 1102 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ReEnterScope();
			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();
		;}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 1107 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetVarParam(1, !gProject->Parse_TOS->err_top_level, 0); 
			gProject->Parse_TOS->parseCtxt->SetIsKnR(true); 
		;}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 1111 "rv_gram.y"
    {   (yyval.decl) = (yyvsp[(3) - (3)].decl);
			gProject->Parse_TOS->parseCtxt->SetIsKnR(false); 
			gProject->Parse_TOS->parseCtxt->SetVarParam(0, !gProject->Parse_TOS->err_top_level, 1); 
			
			// Exit, but will allow re-enter for a function.
			// Hack, to handle parameters being in the function's scope.
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope(true);
		;}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 1123 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.EnterScope();
			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();
		;}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 1129 "rv_gram.y"
    {
			(yyval.decl) = (Decl*) NULL;
		;}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 1133 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.EnterScope();
			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();
		;}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 1138 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetVarParam(0, !gProject->Parse_TOS->err_top_level, 0); 
		;}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 1141 "rv_gram.y"
    {   (yyval.decl) = (yyvsp[(3) - (3)].decl);
			gProject->Parse_TOS->parseCtxt->SetVarParam(0, !gProject->Parse_TOS->err_top_level, 0);
		;}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 1147 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (2)].decl);
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 1152 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (3)].decl);

			Decl*	appendDecl = (yyvsp[(1) - (3)].decl);
			while (appendDecl->next != NULL)
				appendDecl = appendDecl->next;

			appendDecl->next = (yyvsp[(3) - (3)].decl);
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 1165 "rv_gram.y"
    {
			(yyval.declStemnt) = new DeclStemnt(*(yyvsp[(2) - (2)].loc));
			(yyval.declStemnt)->addDecls(ReverseList((yyvsp[(1) - (2)].decl)));
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 1172 "rv_gram.y"
    {
			(yyval.declStemnt) = new DeclStemnt(*(yyvsp[(2) - (2)].loc));
			(yyval.declStemnt)->addDecls(ReverseList((yyvsp[(1) - (2)].decl)));
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 1180 "rv_gram.y"
    {
			assert (gProject->Parse_TOS->err_top_level ||
					(yyvsp[(1) - (2)].base) == gProject->Parse_TOS->parseCtxt->curCtxt->decl_specs);
			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();
			
			yywarn("old-style declaration or incorrect type");

			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = (yyvsp[(2) - (2)].decl);

			if ((yyval.decl) == NULL)
			{
				(yyval.decl) = new Decl((yyvsp[(1) - (2)].base));
			}
		;}
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 1198 "rv_gram.y"
    {
			assert (gProject->Parse_TOS->err_top_level ||
					(yyvsp[(1) - (2)].base) == gProject->Parse_TOS->parseCtxt->curCtxt->decl_specs);
			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();            
			
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = (yyvsp[(2) - (2)].decl);
			
			if ((yyval.decl) == NULL)
			{
				(yyval.decl) = new Decl((yyvsp[(1) - (2)].base));
			}
		;}
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 1218 "rv_gram.y"
    {
			(yyval.base) = new BaseType(BT_Int);
			gProject->Parse_TOS->parseCtxt->SetDeclCtxt((yyval.base));
		;}
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 1237 "rv_gram.y"
    {   
			gProject->Parse_TOS->parseCtxt->PushCtxt();
			gProject->Parse_TOS->parseCtxt->ResetVarParam();
		;}
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 1242 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(2) - (2)].type);
			gProject->Parse_TOS->parseCtxt->PopCtxt(false);
		;}
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 1249 "rv_gram.y"
    {
			assert ((yyvsp[(1) - (1)].base) == gProject->Parse_TOS->parseCtxt->curCtxt->decl_specs);
			
			gProject->Parse_TOS->possibleType = true;
			(yyval.type) = (yyvsp[(1) - (1)].base);
			if ((yyval.type)->isFunction())
				if(yyerr ("Function type not allowed as type name"))
				  YYERROR;
		;}
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 1259 "rv_gram.y"
    {
			assert ((yyvsp[(1) - (2)].base) == gProject->Parse_TOS->parseCtxt->curCtxt->decl_specs);
			
			gProject->Parse_TOS->possibleType = true;
			(yyval.type) = (yyvsp[(2) - (2)].type);
			
			Type * extended = (yyval.type)->extend((yyvsp[(1) - (2)].base));
			if ((yyval.type)->isFunction())
			{
				if(yyerr ("Function type not allowed as type name"))
				  YYERROR;
			}
			else if (extended && 
				(yyvsp[(1) - (2)].base) && (yyvsp[(1) - (2)].base)->isFunction() && 
				! extended->isPointer())
			{
				if(yyerr ("Wrong type combination"))
				  YYERROR;
			}
		;}
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 1287 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->SetDeclCtxt((yyval.base));
		;}
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1303 "rv_gram.y"
    {
			if (! gProject->Parse_TOS->transUnit ||
				gProject->Parse_TOS->transUnit->contxt.syms->current->level >= FUNCTION_SCOPE)
				 (yyval.storage) = (yyvsp[(1) - (1)].storage) ;             
			 else
				 (yyval.storage) = ST_None ;              
		;}
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1316 "rv_gram.y"
    {
			(yyval.base) = (BaseType*) NULL;
		;}
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1323 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(2) - (2)].base);

			if (!(yyval.base))
			{
				(yyval.base) = new BaseType();
			}

			if ((yyvsp[(1) - (2)].storage) == ST_None)
			{
				 if(yyerr("Invalid use of local storage type"))
				   YYERROR;
			}
			else if ((yyval.base)->storage != ST_None)             
				 yywarn("Overloading previous storage type specification");
			else
				 (yyval.base)->storage = (yyvsp[(1) - (2)].storage);
		;}
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1341 "rv_gram.y"
    { gProject->Parse_TOS->possibleType = false; ;}
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1342 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(1) - (3)].base);

			if ((yyvsp[(3) - (3)].base))
			{
				if (((yyvsp[(3) - (3)].base)->typemask & BT_Long)
					&& ((yyval.base)->typemask & BT_Long))
				{
				   // long long : A likely C9X addition 
				   (yyval.base)->typemask &= ~BT_Long;
				   (yyvsp[(3) - (3)].base)->typemask &= ~BT_Long;
				   (yyval.base)->typemask |= (yyvsp[(3) - (3)].base)->typemask;
				   (yyval.base)->typemask |=  BT_LongLong;
				}
				else
					(yyval.base)->typemask |= (yyvsp[(3) - (3)].base)->typemask;

				if ((yyvsp[(3) - (3)].base)->storage != ST_None)
					(yyval.base)->storage = (yyvsp[(3) - (3)].base)->storage;

				// delete $3;
			}

			/*
			std::cout << "In decl_spec: ";
			$$->printBase(std::cout,0);
			if ($$->storage == ST_Typedef)
				std::cout << "(is a typedef)";
			std::cout << std::endl;
			*/
		;}
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1374 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(2) - (2)].base);

			if (!(yyval.base))
			{
				(yyval.base) = new BaseType();
			}

			if (((yyval.base)->qualifier & (yyvsp[(1) - (2)].typeQual)) != TQ_None)
				yywarn("qualifier already specified");  
							  
			(yyval.base)->qualifier |= (yyvsp[(1) - (2)].typeQual);

		;}
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1394 "rv_gram.y"
    {
		   (yyval.base) = (BaseType*) NULL;
		;}
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1400 "rv_gram.y"
    { gProject->Parse_TOS->possibleType = false; ;}
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1401 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(1) - (3)].base);

			if ((yyvsp[(3) - (3)].base))
			{
				(yyval.base)->typemask |= (yyvsp[(3) - (3)].base)->typemask;
				// delete $3;
			}
		;}
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1411 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(2) - (2)].base);

			if (!(yyval.base))
			{
				(yyval.base) = new BaseType();
			}

			if (((yyval.base)->qualifier & (yyvsp[(1) - (2)].typeQual)) != TQ_None)
				yywarn("qualifier already specified");
			(yyval.base)->qualifier |= (yyvsp[(1) - (2)].typeQual);
		;}
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1426 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->SetDeclCtxt((yyval.base));
		;}
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1435 "rv_gram.y"
    {
		   (yyvsp[(1) - (1)].decl)->extend(gProject->Parse_TOS->parseCtxt->UseDeclCtxt());
		;}
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1439 "rv_gram.y"
    {
		   (yyvsp[(1) - (3)].decl)->attrib = (yyvsp[(3) - (3)].gccAttrib);
		   (yyval.decl) = (yyvsp[(1) - (3)].decl);
		;}
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1447 "rv_gram.y"
    {
		   (yyvsp[(1) - (3)].decl)->initializer = (yyvsp[(3) - (3)].value);
		   (yyval.decl) = (yyvsp[(1) - (3)].decl);
		;}
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1454 "rv_gram.y"
    {
		  (yyval.decl) = (Decl*) NULL;
		;}
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1464 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (1)].decl);
		;}
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1468 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (3)].decl);

			Decl*	appendDecl = (yyvsp[(1) - (3)].decl);
			while (appendDecl->next != NULL)
				appendDecl = appendDecl->next;

			appendDecl->next = (yyvsp[(3) - (3)].decl);
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 219:

/* Line 1464 of yacc.c  */
#line 1486 "rv_gram.y"
    {
			(yyval.arrayConst) = new ArrayConstant(NoLocation);
			(yyval.arrayConst)->addElement((yyvsp[(1) - (1)].value));
		;}
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1491 "rv_gram.y"
    {
			(yyval.arrayConst) = (yyvsp[(1) - (3)].arrayConst);
			(yyval.arrayConst)->addElement((yyvsp[(3) - (3)].value));
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1500 "rv_gram.y"
    {
			(yyval.value) = (yyvsp[(2) - (4)].arrayConst);
			delete (yyvsp[(1) - (4)].loc);
			delete (yyvsp[(4) - (4)].loc);
		;}
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1508 "rv_gram.y"
    {
			(yyval.loc) = (Location*) NULL;
		;}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1512 "rv_gram.y"
    {
			delete (yyvsp[(1) - (1)].loc);
			(yyval.loc) = (Location*) NULL;
		;}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 1532 "rv_gram.y"
    {
			(yyval.typeQual) = (yyvsp[(1) - (2)].typeQual) | (yyvsp[(2) - (2)].typeQual);
			if (((yyvsp[(2) - (2)].typeQual) & (yyvsp[(1) - (2)].typeQual)) != TQ_None)
				yywarn("qualifier already specified");                               
		;}
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 1540 "rv_gram.y"
    {
			(yyval.typeQual) = TQ_None;
		;}
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 1574 "rv_gram.y"
    {
			(yyval.base) = new BaseType(BT_UserType);
			(yyval.base)->typeName = (yyvsp[(1) - (1)].symbol);
		;}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 1581 "rv_gram.y"
    {
			assert ((! (yyval.symbol)->entry) || 
					(yyval.symbol)->entry->IsTagDecl()) ;
		;}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 1589 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_ref((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
																gProject->Parse_TOS->transUnit->contxt.tags);
			else
				(yyval.base) = NULL;                                         
		;}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 1599 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_ref((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
																gProject->Parse_TOS->transUnit->contxt.tags);
			else
				(yyval.base) = NULL;                                         
		;}
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1609 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_ref((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
																gProject->Parse_TOS->transUnit->contxt.tags);
			else
				(yyval.base) = NULL;                                         
		;}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1619 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_def((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
															gProject->Parse_TOS->transUnit->contxt.tags);
			else
				(yyval.base) = NULL;                                         
		;}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1628 "rv_gram.y"
    { prvhooks->start_tag_def(); ;}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1630 "rv_gram.y"
    {
		(yyvsp[(4) - (5)].strDef)->_isUnion = false;  // benny fixed 
			(yyval.base) = new BaseType((yyvsp[(4) - (5)].strDef));
			delete (yyvsp[(3) - (5)].loc);
			delete (yyvsp[(5) - (5)].loc);
			prvhooks->end_tag_def();
		;}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1637 "rv_gram.y"
    { prvhooks->start_tag_def(); ;}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1639 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(1) - (5)].base);
			assert (! (yyval.base)->stDefn);
			(yyval.base)->stDefn = (yyvsp[(4) - (5)].strDef);
			(yyvsp[(4) - (5)].strDef)->tag = (yyvsp[(1) - (5)].base)->tag->dup();
			(yyvsp[(4) - (5)].strDef)->_isUnion = false;

			// Overload the incomplete definition
			(yyval.base)->tag->entry->uStructDef = (yyval.base) ;
			
//             std::cout << "struct/union/enum_type_define:"
//                          "The definition of:"
//                       << "(uStructDef:" << $1->tag->entry->uStructDef << ")"
//                       << "(uStructDef->stDefn:" << $1->tag->entry->uStructDef->stDefn << ")"
//                       << "(" << $1->tag->entry << ")" << $1->tag->name  << "$" ;
//             $1->tag->entry->scope->ShowScopeId(std::cout);
//             std::cout << " has been completed" << endl; 
			
			delete (yyvsp[(3) - (5)].loc);
			delete (yyvsp[(5) - (5)].loc);
			prvhooks->end_tag_def();
		;}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1664 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_def((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
															gProject->Parse_TOS->transUnit->contxt.tags);
			else
			  (yyval.base) = NULL ;
		;}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1674 "rv_gram.y"
    { prvhooks->start_tag_def(); ;}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1676 "rv_gram.y"
    {
			(yyvsp[(4) - (5)].strDef)->_isUnion = true;  // benny fixed 
			(yyval.base) = new BaseType((yyvsp[(4) - (5)].strDef));

			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(5) - (5)].loc);
			prvhooks->end_tag_def();
		;}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1685 "rv_gram.y"
    { prvhooks->start_tag_def(); ;}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1687 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(1) - (5)].base);
			assert (! (yyval.base)->stDefn);
			(yyval.base)->stDefn = (yyvsp[(4) - (5)].strDef);
			(yyvsp[(4) - (5)].strDef)->tag = (yyvsp[(1) - (5)].base)->tag->dup();
			(yyvsp[(4) - (5)].strDef)->_isUnion = true;

			// Overload the incomplete definition
			(yyval.base)->tag->entry->uStructDef = (yyval.base) ;
			
//             std::cout << "struct/union/enum_type_define:"
//                          "The definition of:"
//                       << "(uStructDef:" << $1->tag->entry->uStructDef << ")"
//                       << "(uStructDef->stDefn:" << $1->tag->entry->uStructDef->stDefn << ")"
//                       << "(" << $1->tag->entry << ")" << $1->tag->name  << "$" ;
//             $1->tag->entry->scope->ShowScopeId(std::cout);
//             std::cout << " has been completed" << endl; 
			
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(5) - (5)].loc);
			prvhooks->end_tag_def(); 
		;}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1712 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_def((yyvsp[(1) - (2)].typeSpec),(yyvsp[(2) - (2)].symbol),
															gProject->Parse_TOS->transUnit->contxt.tags);
			else
			  (yyval.base) = NULL;
		;}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1722 "rv_gram.y"
    { prvhooks->start_tag_def(); ;}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1724 "rv_gram.y"
    {
			(yyval.base) = new BaseType((yyvsp[(4) - (5)].enDef));

			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(5) - (5)].loc);
			prvhooks->end_tag_def(); 
		;}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1732 "rv_gram.y"
    { prvhooks->start_tag_def(); ;}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1734 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(1) - (5)].base);
			assert (! (yyval.base)->enDefn);
			(yyval.base)->enDefn = (yyvsp[(4) - (5)].enDef);
			(yyvsp[(4) - (5)].enDef)->tag = (yyvsp[(1) - (5)].base)->tag->dup();

			// Overload the incomplete definition
			(yyval.base)->tag->entry->uStructDef = (yyval.base) ;
			
//             std::cout << "struct/union/enum_type_define:"
//                          "The definition of:"
//                       << "(uStructDef:" << $1->tag->entry->uStructDef << ")"
//                       << "(uStructDef->stDefn:" << $1->tag->entry->uStructDef->stDefn << ")"
//                       << "(" << $1->tag->entry << ")" << $1->tag->name  << "$" ;
//             $1->tag->entry->scope->ShowScopeId(std::cout);
//             std::cout << " has been completed" << endl; 
			
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(5) - (5)].loc);
			prvhooks->end_tag_def(); 
		;}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 1758 "rv_gram.y"
    {  (yyval.strDef) = new StructDef();
		   yywarn("ANSI/ISO C prohibits empty struct/union");
		;}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 1765 "rv_gram.y"
    {  (yyval.enDef) = new EnumDef();
		   yywarn("ANSI/ISO C prohibits empty enum");
		;}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 1769 "rv_gram.y"
    {  (yyval.enDef) = (yyvsp[(1) - (2)].enDef);
		;}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 1774 "rv_gram.y"
    {
			(yyval.loc) = NULL;
		;}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 1778 "rv_gram.y"
    {
		  yywarn("Trailing comma in enum type definition");
		;}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 1791 "rv_gram.y"
    {
			(yyval.enDef) = new EnumDef();
			(yyval.enDef)->addElement((yyvsp[(1) - (1)].enConst));
		;}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 1796 "rv_gram.y"
    {
			(yyval.enDef) = (yyvsp[(1) - (3)].enDef);
			(yyval.enDef)->addElement((yyvsp[(3) - (3)].enConst));
			delete (yyvsp[(2) - (3)].loc);
		;}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 1804 "rv_gram.y"
    {
			(yyval.enConst) = new EnumConstant((yyvsp[(1) - (1)].symbol),NULL,HERE);
			if (gProject->Parse_TOS->transUnit)
			{
			  if (gProject->Parse_TOS->transUnit->contxt.syms->IsDefined((yyvsp[(1) - (1)].symbol)->name))
			  {
				 if(yyerr("Duplicate enumeration constant"))
				   YYERROR;
			  }
				 
			  (yyvsp[(1) - (1)].symbol)->entry = gProject->Parse_TOS->transUnit->contxt.syms->Insert(
								  mk_enum_const((yyvsp[(1) - (1)].symbol)->name, (yyval.enConst)));
			}
		;}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 1819 "rv_gram.y"
    {
			(yyval.enConst) = new EnumConstant((yyvsp[(1) - (3)].symbol),(yyvsp[(3) - (3)].value),HERE);
			if (gProject->Parse_TOS->transUnit)
			{
			  if (gProject->Parse_TOS->transUnit->contxt.syms->IsDefined((yyvsp[(1) - (3)].symbol)->name))
			  {
				 if(yyerr("Duplicate enumeration constant"))
				   YYERROR;
			  }
				 
			  (yyvsp[(1) - (3)].symbol)->entry = gProject->Parse_TOS->transUnit->contxt.syms->Insert(
								  mk_enum_const((yyvsp[(1) - (3)].symbol)->name, (yyval.enConst)));
			}
		;}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 1842 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.EnterScope();
			gProject->Parse_TOS->parseCtxt->PushCtxt();
		;}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 1847 "rv_gram.y"
    {
			assert (!gProject->Parse_TOS->err_top_level || gProject->Parse_TOS->possibleType);
			 /* Safety precaution! */
			 gProject->Parse_TOS->possibleType=true;
		;}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 1853 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->PopCtxt(false);
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
			(yyval.strDef) = (yyvsp[(3) - (3)].strDef) ;
		;}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 1862 "rv_gram.y"
    {
			(yyval.strDef) = new StructDef();
			(yyval.strDef)->addComponent(ReverseList((yyvsp[(1) - (2)].decl)));
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 289:

/* Line 1464 of yacc.c  */
#line 1868 "rv_gram.y"
    {
			// A useful gcc extension:
			//   naked semicolons in struct/union definitions. 
			(yyval.strDef) = (yyvsp[(1) - (2)].strDef);
			yywarn ("Empty declaration");
			delete (yyvsp[(2) - (2)].loc);
		;}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 1876 "rv_gram.y"
    {
			(yyval.strDef) = (yyvsp[(1) - (3)].strDef);
			(yyval.strDef)->addComponent(ReverseList((yyvsp[(2) - (3)].decl)));
			delete (yyvsp[(3) - (3)].loc);
		;}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 1884 "rv_gram.y"
    {
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = (yyvsp[(2) - (2)].decl);
		;}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 1889 "rv_gram.y"
    {
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = new Decl ((yyvsp[(1) - (1)].base));
			yywarn ("No field declarator");
		;}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 1903 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetIsFieldId(true); 
		;}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 1906 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(2) - (3)].decl);
			(yyval.decl)->attrib = (yyvsp[(3) - (3)].gccAttrib);
		;}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 1911 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetIsFieldId(true); 
		;}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 1914 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(4) - (5)].decl);
			(yyval.decl)->attrib = (yyvsp[(5) - (5)].gccAttrib);
			(yyval.decl)->next = (yyvsp[(1) - (5)].decl);
			delete (yyvsp[(2) - (5)].loc);
		;}
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 1923 "rv_gram.y"
    {
		   gProject->Parse_TOS->parseCtxt->SetIsFieldId(false); 
		   Type * decl = gProject->Parse_TOS->parseCtxt->UseDeclCtxt();
		   Type * extended = (yyval.decl)->extend(decl);
		   if ((yyval.decl)->form &&
			   (yyval.decl)->form->isFunction())
		   {
			   if(yyerr ("Function type not allowed as field"))
				 YYERROR;
		   }
		   else if (extended && 
			   decl && decl->isFunction() && 
			   ! extended->isPointer())
			   if(yyerr ("Wrong type combination"))
				 YYERROR;
				
		;}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 1941 "rv_gram.y"
    {
		   Type * decl = gProject->Parse_TOS->parseCtxt->UseDeclCtxt();
		   (yyval.decl)->extend(decl);
		   if (! decl)
		   {
			   if(yyerr ("No type specifier for bit field"))
				 YYERROR;
		   }
		   else if (!(yyval.decl)->form)
		   {
			   if(yyerr ("Wrong type combination"))
				 YYERROR;
		   }
		;}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 1961 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetIsFieldId(false); 
		;}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 1964 "rv_gram.y"
    {
			BitFieldType  *bf = new BitFieldType((yyvsp[(4) - (4)].value));
			(yyval.decl) = (yyvsp[(1) - (4)].decl);

			if ((yyval.decl) == NULL)
			{
				(yyval.decl) = new Decl(bf);
			}
			else
			{
				bf->subType = (yyval.decl)->form;
				(yyval.decl)->form = bf;
			}
		;}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 1984 "rv_gram.y"
    {
		   (yyval.decl) = (Decl*) NULL;
		;}
    break;

  case 306:

/* Line 1464 of yacc.c  */
#line 1995 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->Mk_declarator ((yyval.decl));
		;}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 2001 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->Mk_func_declarator ((yyval.decl));
		;}
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 2007 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(2) - (2)].decl);
			(yyval.decl)->extend((yyvsp[(1) - (2)].ptr));
		;}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 2018 "rv_gram.y"
    {  if (gProject->Parse_TOS->transUnit)
				(yyval.decl) = gProject->Parse_TOS->parseCtxt->Mk_direct_declarator_reentrance ((yyvsp[(1) - (1)].symbol),
				gProject->Parse_TOS->transUnit->contxt.syms);
		;}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 2023 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(2) - (3)].decl);
			delete (yyvsp[(1) - (3)].loc) ;
			delete (yyvsp[(3) - (3)].loc) ;
		;}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 2030 "rv_gram.y"
    { // ofer: functions
			(yyval.decl) = (yyvsp[(1) - (4)].decl);
			FunctionType * ft = new FunctionType(ReverseList((yyvsp[(3) - (4)].decl)));
			Type * extended = (yyval.decl)->extend(ft);
			if (extended && ! extended->isPointer())
				if(yyerr ("Wrong type combination"))
				  YYERROR;
				
			delete (yyvsp[(2) - (4)].loc) ;
			delete (yyvsp[(4) - (4)].loc) ;
			// Exit, but will allow re-enter for a function.
			// Hack, to handle parameters being in the function's scope.
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope(true);

		;}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 2047 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (4)].decl);
			FunctionType * ft = new FunctionType(ReverseList((yyvsp[(3) - (4)].decl)));
			Type * extended = (yyval.decl)->extend(ft);
			if (extended && ! extended->isPointer())
				if(yyerr ("Wrong type combination"))
				  YYERROR;

			delete (yyvsp[(2) - (4)].loc) ;
			delete (yyvsp[(4) - (4)].loc) ;
			// Exit, but will allow re-enter for a function.
			// Hack, to handle parameters being in the function's scope.
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope(true);

		;}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 2064 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (3)].decl);

			if ((yyval.decl) != NULL)
			{
				FunctionType* ft = new FunctionType();
				Type* extended = (yyval.decl)->extend(ft);
				if (extended && ! extended->isPointer())
					if(yyerr ("Wrong type combination"))
							  YYERROR;
			}
			
			delete (yyvsp[(2) - (3)].loc) ;
			delete (yyvsp[(3) - (3)].loc) ;
			if (gProject->Parse_TOS->transUnit)
			{
				gProject->Parse_TOS->transUnit->contxt.EnterScope();
				// Exit, but will allow re-enter for a function.
				// Hack, to handle parameters being in the function's scope.
				gProject->Parse_TOS->transUnit->contxt.ExitScope(true);
			}
		;}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 2089 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (4)].decl);
			ArrayType * at = new ArrayType((yyvsp[(3) - (4)].value));
			Type * extended = (yyval.decl)->extend(at);
			if (extended && 
				extended->isFunction())
				if(yyerr ("Wrong type combination"))
				  YYERROR;
			  
			delete (yyvsp[(2) - (4)].loc) ;
			delete (yyvsp[(4) - (4)].loc) ;
		;}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 2107 "rv_gram.y"
    {
			(yyval.ptr) = new PtrType((yyvsp[(2) - (2)].typeQual));    
		;}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 2114 "rv_gram.y"
    {
			(yyval.ptr) = (yyvsp[(2) - (2)].ptr);
			(yyval.ptr)->subType = (yyvsp[(1) - (2)].ptr);
		;}
    break;

  case 322:

/* Line 1464 of yacc.c  */
#line 2127 "rv_gram.y"
    {  gProject->Parse_TOS->parseCtxt->IncrVarParam(1);
		  if (gProject->Parse_TOS->transUnit)
			  gProject->Parse_TOS->transUnit->contxt.EnterScope();
		  gProject->Parse_TOS->parseCtxt->PushCtxt();
		;}
    break;

  case 323:

/* Line 1464 of yacc.c  */
#line 2133 "rv_gram.y"
    {
		  // Exit, but will allow re-enter for a function.
		  // Hack, to handle parameters being in the function's scope.
		  gProject->Parse_TOS->parseCtxt->PopCtxt(true);
		  gProject->Parse_TOS->parseCtxt->IncrVarParam(-1);
		  (yyval.decl) = (yyvsp[(2) - (2)].decl);
	   ;}
    break;

  case 324:

/* Line 1464 of yacc.c  */
#line 2143 "rv_gram.y"
    {  if (gProject->Parse_TOS->transUnit)
			   (yyval.decl) = gProject->Parse_TOS->parseCtxt->Mk_direct_declarator_reentrance ((yyvsp[(1) - (1)].symbol),
				gProject->Parse_TOS->transUnit->contxt.syms);
		;}
    break;

  case 325:

/* Line 1464 of yacc.c  */
#line 2148 "rv_gram.y"
    {  (yyval.decl) = (yyvsp[(1) - (3)].decl);
		   if (gProject->Parse_TOS->transUnit)
		   {
			  (yyval.decl) = gProject->Parse_TOS->parseCtxt->Mk_direct_declarator_reentrance ((yyvsp[(3) - (3)].symbol),
				gProject->Parse_TOS->transUnit->contxt.syms);
			  (yyval.decl)->next = (yyvsp[(1) - (3)].decl);
		   }
		;}
    break;

  case 327:

/* Line 1464 of yacc.c  */
#line 2164 "rv_gram.y"
    {
			/* Convert a TYPEDEF_NAME back into a normal IDENT */
			(yyval.symbol) = (yyvsp[(1) - (1)].symbol);
			(yyval.symbol)->entry = (SymEntry*) NULL;
		;}
    break;

  case 330:

/* Line 1464 of yacc.c  */
#line 2185 "rv_gram.y"
    {
		   (yyval.decl) = (Decl*) NULL;
		;}
    break;

  case 331:

/* Line 1464 of yacc.c  */
#line 2189 "rv_gram.y"
    { gProject->Parse_TOS->parseCtxt->IncrVarParam(1); 
		;}
    break;

  case 332:

/* Line 1464 of yacc.c  */
#line 2192 "rv_gram.y"
    { gProject->Parse_TOS->parseCtxt->IncrVarParam(-1); 
		   (yyval.decl) = (yyvsp[(2) - (2)].decl);
		;}
    break;

  case 333:

/* Line 1464 of yacc.c  */
#line 2198 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->IncrVarParam(1);
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.EnterScope();
			gProject->Parse_TOS->parseCtxt->PushCtxt();
		;}
    break;

  case 334:

/* Line 1464 of yacc.c  */
#line 2204 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->PopCtxt(true);
			gProject->Parse_TOS->parseCtxt->IncrVarParam(-1);
			(yyval.decl) = (yyvsp[(2) - (2)].decl) ;
		;}
    break;

  case 336:

/* Line 1464 of yacc.c  */
#line 2213 "rv_gram.y"
    {
			BaseType *bt = new BaseType(BT_Ellipsis);

			(yyval.decl) = new Decl(bt);
			(yyval.decl)->next = (yyvsp[(1) - (3)].decl);
		;}
    break;

  case 338:

/* Line 1464 of yacc.c  */
#line 2223 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(3) - (3)].decl);
			(yyval.decl)->next = (yyvsp[(1) - (3)].decl);
		;}
    break;

  case 339:

/* Line 1464 of yacc.c  */
#line 2230 "rv_gram.y"
    {   
			gProject->Parse_TOS->parseCtxt->PushCtxt();
		;}
    break;

  case 340:

/* Line 1464 of yacc.c  */
#line 2234 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->PopCtxt(true);
			(yyval.decl) = (yyvsp[(2) - (2)].decl);
		;}
    break;

  case 341:

/* Line 1464 of yacc.c  */
#line 2241 "rv_gram.y"
    {
			assert (gProject->Parse_TOS->err_top_level ||
					(yyvsp[(1) - (2)].base) == gProject->Parse_TOS->parseCtxt->curCtxt->decl_specs);
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = (yyvsp[(2) - (2)].decl);
			Type * decl = gProject->Parse_TOS->parseCtxt->UseDeclCtxt();
			Type * extended = (yyval.decl)->extend(decl);             
			if ((yyval.decl)->form &&
				(yyval.decl)->form->isFunction())
			 {
				if(yyerr ("Function type not allowed"))
				  YYERROR;
			 }
			else if (extended && 
				decl && decl->isFunction() && 
				! extended->isPointer())
			 {
				if(yyerr ("Wrong type combination"))
				  YYERROR;
			 }
		;}
    break;

  case 342:

/* Line 1464 of yacc.c  */
#line 2263 "rv_gram.y"
    {
			assert (gProject->Parse_TOS->err_top_level ||
					(yyvsp[(1) - (2)].base) == gProject->Parse_TOS->parseCtxt->curCtxt->decl_specs);
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = new Decl((yyvsp[(2) - (2)].type));
			
			Type * decl = gProject->Parse_TOS->parseCtxt->UseDeclCtxt();
			Type * extended = (yyval.decl)->extend(decl);
			if ((yyval.decl)->form &&
				(yyval.decl)->form->isFunction())
			{
				if(yyerr ("Function type not allowed for parameter"))
				  YYERROR;
			}
			else if (extended && 
				decl && decl->isFunction() && 
				! extended->isPointer())
			{
				if(yyerr ("Wrong type combination"))
				  YYERROR;
			}
		;}
    break;

  case 343:

/* Line 1464 of yacc.c  */
#line 2286 "rv_gram.y"
    {
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = new Decl((yyvsp[(1) - (1)].base));
			if ((yyval.decl)->form &&
				(yyval.decl)->form->isFunction())
				if(yyerr ("Function type not allowed for parameter"))
				  YYERROR;
		;}
    break;

  case 344:

/* Line 1464 of yacc.c  */
#line 2300 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(1) - (1)].ptr);
		;}
    break;

  case 345:

/* Line 1464 of yacc.c  */
#line 2304 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(1) - (1)].type);
		;}
    break;

  case 346:

/* Line 1464 of yacc.c  */
#line 2308 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(2) - (2)].type);
			(yyval.type)->extend((yyvsp[(1) - (2)].ptr));
		;}
    break;

  case 348:

/* Line 1464 of yacc.c  */
#line 2318 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(2) - (3)].type);
		;}
    break;

  case 349:

/* Line 1464 of yacc.c  */
#line 2322 "rv_gram.y"
    {
			(yyval.type) = new ArrayType((yyvsp[(2) - (3)].value));
		;}
    break;

  case 350:

/* Line 1464 of yacc.c  */
#line 2326 "rv_gram.y"
    {
			ArrayType *at = new ArrayType((yyvsp[(3) - (4)].value));
			(yyval.type) = (yyvsp[(1) - (4)].type);
			(yyval.type)->extend(at);
			Type * extended = (yyval.type)->extend(at) ;
			if (extended && 
				extended->isFunction())
				if(yyerr ("Wrong type combination"))
				  YYERROR;
		;}
    break;

  case 351:

/* Line 1464 of yacc.c  */
#line 2337 "rv_gram.y"
    {
			(yyval.type) = new FunctionType(ReverseList((yyvsp[(2) - (3)].decl)));
		;}
    break;

  case 352:

/* Line 1464 of yacc.c  */
#line 2341 "rv_gram.y"
    {
			FunctionType * ft = new FunctionType(ReverseList((yyvsp[(3) - (4)].decl)));
			(yyval.type) = (yyvsp[(1) - (4)].type);
			Type * extended = (yyval.type)->extend(ft) ;
			if (extended && 
				! extended->isPointer())
				if(yyerr ("Wrong type combination"))
				  YYERROR;
				
		;}
    break;

  case 353:

/* Line 1464 of yacc.c  */
#line 2358 "rv_gram.y"
    {
			(yyval.gccAttrib) = (GccAttrib*) NULL;
		;}
    break;

  case 355:

/* Line 1464 of yacc.c  */
#line 2365 "rv_gram.y"
    {
				(yyval.gccAttrib) = (yyvsp[(4) - (6)].gccAttrib);
				delete (yyvsp[(2) - (6)].loc);
				delete (yyvsp[(3) - (6)].loc);
				delete (yyvsp[(5) - (6)].loc);
				delete (yyvsp[(6) - (6)].loc);
			;}
    break;

  case 356:

/* Line 1464 of yacc.c  */
#line 2375 "rv_gram.y"
    {
				/* The lexer ate some unsupported option. */
				(yyval.gccAttrib) = new GccAttrib( GCC_Unsupported);
			;}
    break;

  case 357:

/* Line 1464 of yacc.c  */
#line 2380 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Packed );
			;}
    break;

  case 358:

/* Line 1464 of yacc.c  */
#line 2384 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_CDecl );
			;}
    break;

  case 359:

/* Line 1464 of yacc.c  */
#line 2388 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Const );
			;}
    break;

  case 360:

/* Line 1464 of yacc.c  */
#line 2392 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_NoReturn );
			;}
    break;

  case 361:

/* Line 1464 of yacc.c  */
#line 2396 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Aligned );

				if ((yyvsp[(3) - (4)].consValue)->ctype == CT_Int)
				{
					IntConstant    *iCons = (IntConstant*) (yyvsp[(3) - (4)].consValue);

					(yyval.gccAttrib)->value = iCons->lng;
				}

				delete (yyvsp[(2) - (4)].loc);
				delete (yyvsp[(4) - (4)].loc);
			;}
    break;

  case 362:

/* Line 1464 of yacc.c  */
#line 2410 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Mode );

				(yyval.gccAttrib)->mode = (yyvsp[(3) - (4)].symbol);

				delete (yyvsp[(2) - (4)].loc);
				delete (yyvsp[(4) - (4)].loc);
			;}
    break;

  case 363:

/* Line 1464 of yacc.c  */
#line 2419 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Format );
	
				(yyval.gccAttrib)->mode = (yyvsp[(3) - (8)].symbol);

				if ((yyvsp[(5) - (8)].consValue)->ctype == CT_Int)
				{
					IntConstant    *iCons = (IntConstant*) (yyvsp[(5) - (8)].consValue);

					(yyval.gccAttrib)->strIdx = iCons->lng;
				}

				if ((yyvsp[(7) - (8)].consValue)->ctype == CT_Int)
				{
					IntConstant    *iCons = (IntConstant*) (yyvsp[(7) - (8)].consValue);

					(yyval.gccAttrib)->first = iCons->lng;
				}

				delete (yyvsp[(2) - (8)].loc);
				delete (yyvsp[(8) - (8)].loc);
			;}
    break;

  case 364:

/* Line 1464 of yacc.c  */
#line 2442 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Malloc );
			;}
    break;



/* Line 1464 of yacc.c  */
#line 4987 "rv_gram.tab.c"
      default: break;
    }
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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



/* Line 1684 of yacc.c  */
#line 2447 "rv_gram.y"


/*******************************************************/

