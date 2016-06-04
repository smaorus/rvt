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
#include <rv_glob.h>

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
#line 145 "./generated/rv_gram.cpp"

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
/* Tokens.  */
#define IDENT 258
#define TAG_NAME 259
#define LABEL_NAME 260
#define TYPEDEF_NAME 261
#define STRING 262
#define LSTRING 263
#define CHAR_CONST 264
#define LCHAR_CONST 265
#define INUM 266
#define RNUM 267
#define PP_LINE 268
#define INVALID 269
#define CONST 270
#define VOLATILE 271
#define AUTO 272
#define EXTRN 273
#define REGISTR 274
#define STATIC 275
#define TYPEDEF 276
#define VOID 277
#define BOOL 278
#define CHAR 279
#define SHORT 280
#define INT 281
#define INT8 282
#define INT16 283
#define INT32 284
#define INT64 285
#define LONG 286
#define FLOAT 287
#define DOUBLE 288
#define SGNED 289
#define UNSGNED 290
#define ENUM 291
#define STRUCT 292
#define UNION 293
#define BREAK 294
#define CASE 295
#define CONT 296
#define DEFLT 297
#define DO 298
#define ELSE 299
#define IF 300
#define FOR 301
#define GOTO 302
#define RETURN 303
#define SWITCH 304
#define WHILE 305
#define PLUS_EQ 306
#define MINUS_EQ 307
#define STAR_EQ 308
#define DIV_EQ 309
#define MOD_EQ 310
#define B_AND_EQ 311
#define B_OR_EQ 312
#define B_XOR_EQ 313
#define L_SHIFT_EQ 314
#define R_SHIFT_EQ 315
#define EQUAL 316
#define LESS_EQ 317
#define GRTR_EQ 318
#define NOT_EQ 319
#define RPAREN 320
#define RBRCKT 321
#define LBRACE 322
#define RBRACE 323
#define SEMICOLON 324
#define COMMA 325
#define ELLIPSIS 326
#define LB_SIGN 327
#define DOUB_LB_SIGN 328
#define BACKQUOTE 329
#define AT 330
#define ATTRIBUTE 331
#define ALIGNED 332
#define PACKED 333
#define CDECL 334
#define MODE 335
#define FORMAT 336
#define NORETURN 337
#define MALLOC 338
#define COMMA_OP 339
#define ASSIGN 340
#define EQ 341
#define COMMA_SEP 342
#define COLON 343
#define QUESTMARK 344
#define OR 345
#define AND 346
#define B_OR 347
#define B_XOR 348
#define B_AND 349
#define COMP_EQ 350
#define GRTR 351
#define LESS 352
#define COMP_ARITH 353
#define R_SHIFT 354
#define L_SHIFT 355
#define MINUS 356
#define PLUS 357
#define MOD 358
#define DIV 359
#define STAR 360
#define CAST 361
#define DECR 362
#define INCR 363
#define SIZEOF 364
#define B_NOT 365
#define NOT 366
#define UNARY 367
#define HYPERUNARY 368
#define LBRCKT 369
#define LPAREN 370
#define DOT 371
#define ARROW 372




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 420 "./generated/rv_gram.cpp"

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
#define YYLAST   1353

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  118
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  200
/* YYNRULES -- Number of rules.  */
#define YYNRULES  369
/* YYNRULES -- Number of states.  */
#define YYNSTATES  532

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
      20,    22,    25,    29,    32,    36,    40,    41,    48,    51,
      52,    56,    57,    59,    61,    64,    67,    69,    75,    78,
      79,    81,    83,    86,    89,    91,    93,    95,    97,    99,
     101,   103,   105,   107,   109,   111,   114,   115,   119,   122,
     123,   128,   130,   132,   134,   136,   138,   144,   147,   150,
     154,   158,   160,   166,   174,   182,   188,   198,   208,   210,
     212,   214,   216,   219,   224,   226,   228,   234,   236,   240,
     241,   243,   245,   246,   248,   250,   252,   256,   258,   262,
     265,   267,   271,   273,   277,   279,   283,   286,   288,   293,
     295,   299,   301,   305,   307,   311,   313,   317,   319,   323,
     325,   327,   329,   331,   333,   335,   337,   339,   341,   343,
     348,   351,   354,   357,   360,   363,   366,   369,   371,   375,
     377,   379,   381,   385,   389,   391,   393,   395,   397,   399,
     401,   406,   408,   410,   413,   416,   418,   422,   426,   431,
     432,   434,   436,   440,   442,   444,   446,   448,   450,   452,
     454,   456,   458,   460,   462,   464,   466,   468,   470,   472,
     474,   475,   477,   478,   479,   483,   484,   486,   487,   488,
     492,   495,   499,   502,   505,   508,   511,   512,   514,   516,
     517,   520,   522,   525,   527,   529,   531,   533,   535,   537,
     539,   541,   543,   544,   546,   549,   550,   554,   557,   558,
     560,   561,   565,   568,   570,   571,   575,   577,   581,   582,
     584,   586,   588,   592,   594,   596,   600,   602,   607,   608,
     610,   612,   614,   616,   618,   621,   622,   624,   626,   628,
     630,   632,   634,   636,   638,   640,   642,   644,   646,   648,
     650,   652,   654,   656,   658,   660,   662,   664,   666,   668,
     670,   673,   676,   679,   682,   683,   689,   690,   696,   699,
     700,   706,   707,   713,   716,   717,   723,   724,   730,   731,
     733,   734,   737,   738,   740,   742,   744,   748,   750,   754,
     756,   757,   758,   762,   765,   768,   772,   775,   777,   779,
     780,   784,   785,   791,   793,   795,   797,   798,   803,   805,
     806,   808,   810,   812,   815,   817,   819,   821,   825,   827,
     832,   837,   841,   846,   849,   851,   854,   856,   857,   860,
     862,   866,   868,   870,   872,   874,   875,   876,   879,   880,
     883,   885,   889,   891,   895,   896,   899,   902,   905,   907,
     909,   911,   914,   916,   920,   924,   929,   933,   938,   939,
     941,   948,   949,   951,   953,   955,   957,   962,   967,   976
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     119,     0,    -1,    -1,   120,    -1,     1,    -1,   122,   121,
      -1,   120,   122,   121,    -1,    -1,   213,    -1,   123,    -1,
      13,    -1,     1,    69,    -1,     1,    68,   121,    -1,   124,
     125,    -1,   217,   289,   204,    -1,   216,   288,   204,    -1,
      -1,    67,   126,   208,   128,   127,    68,    -1,     1,    68,
      -1,    -1,   212,   128,   127,    -1,    -1,   129,    -1,   130,
      -1,   129,   130,    -1,   129,    13,    -1,   134,    -1,    67,
     208,   132,   135,    68,    -1,     1,    68,    -1,    -1,   133,
      -1,   134,    -1,   133,   134,    -1,   133,    13,    -1,   136,
      -1,   137,    -1,   131,    -1,   139,    -1,   140,    -1,   141,
      -1,   142,    -1,   143,    -1,   144,    -1,   145,    -1,   146,
      -1,     1,    69,    -1,    -1,   212,   132,   135,    -1,   161,
      69,    -1,    -1,   152,    88,   138,   134,    -1,   147,    -1,
     148,    -1,   149,    -1,   150,    -1,   151,    -1,    49,   115,
     161,    65,   134,    -1,    39,    69,    -1,    41,    69,    -1,
      48,   160,    69,    -1,    47,     5,    69,    -1,    69,    -1,
      45,   115,   161,    65,   134,    -1,    45,   115,   161,    65,
     134,    44,   134,    -1,    43,   134,    50,   115,   161,    65,
      69,    -1,    50,   115,   161,    65,   134,    -1,    46,   115,
     160,    69,   160,    69,   160,    65,   134,    -1,    46,   115,
     215,    69,   160,    69,   160,    65,   134,    -1,   153,    -1,
     154,    -1,   155,    -1,   300,    -1,    40,   159,    -1,    40,
     159,    71,   159,    -1,    42,    -1,   162,    -1,   162,    89,
     161,    88,   156,    -1,   156,    -1,   175,   202,   157,    -1,
      -1,   159,    -1,   161,    -1,    -1,   161,    -1,   183,    -1,
     163,    -1,   162,    90,   163,    -1,   165,    -1,   163,    91,
     165,    -1,   111,   169,    -1,   166,    -1,   165,    92,   166,
      -1,   167,    -1,   166,    93,   167,    -1,   170,    -1,   167,
      94,   170,    -1,   110,   169,    -1,   175,    -1,   115,   219,
      65,   169,    -1,   171,    -1,   170,   199,   171,    -1,   172,
      -1,   171,   200,   172,    -1,   173,    -1,   172,   201,   173,
      -1,   174,    -1,   173,   197,   174,    -1,   169,    -1,   174,
     198,   169,    -1,   186,    -1,   176,    -1,   177,    -1,   178,
      -1,   164,    -1,   168,    -1,   179,    -1,   180,    -1,   181,
      -1,   182,    -1,   109,   115,   219,    65,    -1,   109,   175,
      -1,   101,   169,    -1,   102,   169,    -1,    94,   169,    -1,
     105,   169,    -1,   108,   175,    -1,   107,   175,    -1,   157,
      -1,   183,    70,   157,    -1,   300,    -1,   185,    -1,   203,
      -1,   115,   161,    65,    -1,   115,     1,    65,    -1,   184,
      -1,   187,    -1,   188,    -1,   194,    -1,   189,    -1,   190,
      -1,   186,   114,   161,    66,    -1,   192,    -1,   193,    -1,
     186,   108,    -1,   186,   107,    -1,   302,    -1,   186,   116,
     191,    -1,   186,   117,   191,    -1,   186,   115,   195,    65,
      -1,    -1,   196,    -1,   157,    -1,   196,    70,   157,    -1,
     102,    -1,   101,    -1,   105,    -1,   104,    -1,   103,    -1,
      95,    -1,    98,    -1,   100,    -1,    99,    -1,    86,    -1,
      85,    -1,    11,    -1,    12,    -1,     9,    -1,    10,    -1,
       7,    -1,     8,    -1,    -1,   205,    -1,    -1,    -1,   206,
     207,   212,    -1,    -1,   209,    -1,    -1,    -1,   210,   211,
     212,    -1,   215,    69,    -1,   215,    69,   212,    -1,   214,
      69,    -1,   215,    69,    -1,   216,   237,    -1,   217,   237,
      -1,    -1,   222,    -1,   312,    -1,    -1,   220,   221,    -1,
     222,    -1,   222,   218,    -1,   228,    -1,    18,    -1,    20,
      -1,    21,    -1,    17,    -1,    19,    -1,   223,    -1,   224,
      -1,   248,    -1,    -1,   228,    -1,   225,   227,    -1,    -1,
     226,   229,   227,    -1,   244,   227,    -1,    -1,   231,    -1,
      -1,   248,   232,   230,    -1,   244,   230,    -1,   231,    -1,
      -1,   288,   235,   315,    -1,   234,    -1,   234,    86,   240,
      -1,    -1,   238,    -1,   239,    -1,   236,    -1,   239,    70,
     236,    -1,   242,    -1,   242,    -1,   241,    70,   242,    -1,
     157,    -1,    67,   241,   243,    68,    -1,    -1,    70,    -1,
     245,    -1,    15,    -1,    16,    -1,   245,    -1,   246,   245,
      -1,    -1,   246,    -1,   263,    -1,   255,    -1,   259,    -1,
     253,    -1,   251,    -1,   252,    -1,   249,    -1,    22,    -1,
      23,    -1,    24,    -1,    25,    -1,    26,    -1,    27,    -1,
      28,    -1,    29,    -1,    30,    -1,    31,    -1,    32,    -1,
      33,    -1,    34,    -1,    35,    -1,     6,    -1,     4,    -1,
      37,   250,    -1,    38,   250,    -1,    36,   250,    -1,    37,
     250,    -1,    -1,    37,   256,    67,   266,    68,    -1,    -1,
     254,   257,    67,   266,    68,    -1,    38,   250,    -1,    -1,
      38,    67,   260,   266,    68,    -1,    -1,   258,    67,   261,
     266,    68,    -1,    36,   250,    -1,    -1,    36,    67,   264,
     267,    68,    -1,    -1,   262,    67,   265,   267,    68,    -1,
      -1,   273,    -1,    -1,   269,   268,    -1,    -1,    70,    -1,
     270,    -1,   271,    -1,   269,    70,   271,    -1,   272,    -1,
     272,    86,   157,    -1,   302,    -1,    -1,    -1,   274,   275,
     276,    -1,   277,    69,    -1,   276,    69,    -1,   276,   277,
      69,    -1,   233,   278,    -1,   233,    -1,   279,    -1,    -1,
     280,   282,   315,    -1,    -1,   279,    70,   281,   282,   315,
      -1,   283,    -1,   284,    -1,   288,    -1,    -1,   287,    88,
     285,   286,    -1,   156,    -1,    -1,   288,    -1,   290,    -1,
     290,    -1,   296,   291,    -1,   291,    -1,   292,    -1,   300,
      -1,   115,   290,    65,    -1,   293,    -1,   292,   115,   305,
      65,    -1,   292,   115,   297,    65,    -1,   292,   115,    65,
      -1,   292,   114,   158,    66,    -1,   105,   247,    -1,   294,
      -1,   295,   294,    -1,   295,    -1,    -1,   298,   299,    -1,
     300,    -1,   299,    70,   300,    -1,     3,    -1,     6,    -1,
     300,    -1,   301,    -1,    -1,    -1,   304,   307,    -1,    -1,
     306,   307,    -1,   308,    -1,   308,    70,    71,    -1,   309,
      -1,   308,    70,   309,    -1,    -1,   310,   311,    -1,   222,
     288,    -1,   222,   312,    -1,   222,    -1,   296,    -1,   313,
      -1,   296,   313,    -1,   314,    -1,   115,   312,    65,    -1,
     114,   158,    66,    -1,   314,   114,   158,    66,    -1,   115,
     303,    65,    -1,   314,   115,   303,    65,    -1,    -1,   316,
      -1,    76,   115,   115,   317,    65,    65,    -1,    -1,    78,
      -1,    79,    -1,    15,    -1,    82,    -1,    77,   115,    11,
      65,    -1,    80,   115,   300,    65,    -1,    81,   115,   300,
      70,    11,    70,    11,    65,    -1,    83,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   234,   234,   241,   252,   260,   265,   272,   280,   286,
     292,   297,   301,   307,   334,   363,   397,   396,   415,   422,
     425,   436,   439,   442,   443,   452,   467,   470,   481,   488,
     491,   494,   495,   504,   515,   516,   517,   518,   519,   520,
     521,   522,   523,   524,   525,   526,   534,   537,   547,   555,
     554,   575,   576,   579,   580,   581,   584,   593,   601,   609,
     617,   625,   632,   641,   651,   662,   671,   681,   697,   698,
     699,   702,   710,   715,   723,   739,   740,   748,   749,   758,
     761,   764,   768,   771,   774,   777,   778,   785,   786,   793,
     800,   801,   808,   809,   816,   817,   824,   831,   832,   840,
     841,   847,   848,   854,   855,   861,   862,   868,   869,   877,
     878,   879,   880,   881,   882,   883,   884,   885,   886,   889,
     896,   903,   909,   916,   923,   929,   936,   943,   944,   951,
     960,   961,   967,   973,   981,   982,   983,   984,   985,   986,
     989,   997,   998,  1001,  1008,  1015,  1018,  1041,  1064,  1078,
    1081,  1084,  1085,  1094,  1095,  1098,  1099,  1100,  1103,  1106,
    1109,  1110,  1113,  1114,  1117,  1118,  1119,  1120,  1121,  1122,
    1131,  1131,  1142,  1147,  1142,  1163,  1163,  1173,  1178,  1173,
    1186,  1191,  1204,  1211,  1219,  1237,  1258,  1264,  1273,  1277,
    1277,  1288,  1298,  1326,  1332,  1333,  1334,  1337,  1338,  1341,
    1342,  1352,  1356,  1359,  1362,  1381,  1381,  1413,  1434,  1437,
    1440,  1440,  1450,  1465,  1475,  1474,  1485,  1486,  1494,  1497,
    1500,  1503,  1507,  1523,  1525,  1530,  1538,  1539,  1548,  1551,
    1563,  1566,  1567,  1570,  1571,  1580,  1583,  1590,  1591,  1592,
    1593,  1594,  1595,  1596,  1597,  1598,  1599,  1600,  1601,  1602,
    1603,  1604,  1605,  1606,  1607,  1608,  1609,  1610,  1613,  1620,
    1628,  1638,  1648,  1658,  1668,  1668,  1677,  1677,  1703,  1714,
    1713,  1725,  1724,  1751,  1762,  1761,  1772,  1771,  1798,  1801,
    1805,  1808,  1814,  1817,  1827,  1830,  1835,  1843,  1858,  1875,
    1882,  1887,  1882,  1901,  1907,  1915,  1923,  1928,  1939,  1943,
    1943,  1951,  1950,  1962,  1980,  1997,  2001,  2000,  2020,  2024,
    2027,  2034,  2040,  2046,  2051,  2054,  2057,  2062,  2068,  2069,
    2086,  2103,  2128,  2146,  2152,  2153,  2160,  2167,  2167,  2182,
    2187,  2199,  2203,  2215,  2216,  2225,  2229,  2229,  2238,  2238,
    2251,  2252,  2261,  2262,  2270,  2270,  2280,  2302,  2325,  2339,
    2343,  2347,  2354,  2357,  2361,  2365,  2376,  2380,  2398,  2401,
    2404,  2415,  2419,  2423,  2427,  2431,  2435,  2449,  2458,  2481
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
  "func_spec", "block_stemnt", "$@1", "cmpnd_stemnt_list",
  "opt_stemnt_list", "stemnt_list", "stemnt", "block_stemnt_reentrance",
  "opt_stemnt_list_reentrance", "stemnt_list_reentrance",
  "stemnt_reentrance", "cmpnd_stemnt_list_reentrance", "expr_stemnt",
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
     127,   128,   128,   129,   129,   129,   130,   131,   131,   132,
     132,   133,   133,   133,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   135,   135,   136,   138,
     137,   139,   139,   140,   140,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   151,   152,   152,
     152,   153,   154,   154,   155,   156,   156,   157,   157,   158,
     158,   159,   160,   160,   161,   162,   162,   163,   163,   164,
     165,   165,   166,   166,   167,   167,   168,   169,   169,   170,
     170,   171,   171,   172,   172,   173,   173,   174,   174,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   176,
     176,   177,   178,   179,   180,   181,   182,   183,   183,   184,
     184,   184,   185,   185,   186,   186,   186,   186,   186,   186,
     187,   188,   188,   189,   190,   191,   192,   193,   194,   195,
     195,   196,   196,   197,   197,   198,   198,   198,   199,   200,
     201,   201,   202,   202,   203,   203,   203,   203,   203,   203,
     205,   204,   206,   207,   204,   209,   208,   210,   211,   208,
     212,   212,   213,   213,   214,   215,   216,   217,   218,   220,
     219,   221,   221,   222,   223,   223,   223,   224,   224,   225,
     225,   226,   227,   227,   228,   229,   228,   228,   230,   230,
     232,   231,   231,   233,   235,   234,   236,   236,   237,   237,
     238,   239,   239,   240,   241,   241,   242,   242,   243,   243,
     244,   245,   245,   246,   246,   247,   247,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   249,   250,
     251,   252,   253,   254,   256,   255,   257,   255,   258,   260,
     259,   261,   259,   262,   264,   263,   265,   263,   266,   266,
     267,   267,   268,   268,   269,   270,   270,   271,   271,   272,
     274,   275,   273,   276,   276,   276,   277,   277,   278,   280,
     279,   281,   279,   282,   282,   283,   285,   284,   286,   287,
     287,   288,   289,   290,   290,   291,   292,   292,   292,   292,
     292,   292,   293,   294,   295,   295,   296,   298,   297,   299,
     299,   300,   301,   302,   302,   303,   304,   303,   306,   305,
     307,   307,   308,   308,   310,   309,   311,   311,   311,   312,
     312,   312,   313,   314,   314,   314,   314,   314,   315,   315,
     316,   317,   317,   317,   317,   317,   317,   317,   317,   317
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     3,     0,     1,     1,
       1,     2,     3,     2,     3,     3,     0,     6,     2,     0,
       3,     0,     1,     1,     2,     2,     1,     5,     2,     0,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     0,     3,     2,     0,
       4,     1,     1,     1,     1,     1,     5,     2,     2,     3,
       3,     1,     5,     7,     7,     5,     9,     9,     1,     1,
       1,     1,     2,     4,     1,     1,     5,     1,     3,     0,
       1,     1,     0,     1,     1,     1,     3,     1,     3,     2,
       1,     3,     1,     3,     1,     3,     2,     1,     4,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       2,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       4,     1,     1,     2,     2,     1,     3,     3,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     1,     0,     0,     3,     0,     1,     0,     0,     3,
       2,     3,     2,     2,     2,     2,     0,     1,     1,     0,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     2,     0,     3,     2,     0,     1,
       0,     3,     2,     1,     0,     3,     1,     3,     0,     1,
       1,     1,     3,     1,     1,     3,     1,     4,     0,     1,
       1,     1,     1,     1,     2,     0,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     2,     0,     5,     0,     5,     2,     0,
       5,     0,     5,     2,     0,     5,     0,     5,     0,     1,
       0,     2,     0,     1,     1,     1,     3,     1,     3,     1,
       0,     0,     3,     2,     2,     3,     2,     1,     1,     0,
       3,     0,     5,     1,     1,     1,     0,     4,     1,     0,
       1,     1,     1,     2,     1,     1,     1,     3,     1,     4,
       4,     3,     4,     2,     1,     2,     1,     0,     2,     1,
       3,     1,     1,     1,     1,     0,     0,     2,     0,     2,
       1,     3,     1,     3,     0,     2,     2,     2,     1,     1,
       1,     2,     1,     3,     3,     4,     3,     4,     0,     1,
       6,     0,     1,     1,     1,     1,     4,     4,     8,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,     4,   258,    10,   231,   232,   197,   194,   198,   195,
     196,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,     0,   264,     0,     0,     0,
       7,     9,     0,     8,     0,     0,   218,   218,   187,   199,
     200,   202,   205,   193,   202,   230,   201,   243,   241,   242,
     240,   266,   238,     0,   239,     0,   237,     7,    11,   259,
     274,   262,   260,     0,   269,   261,     1,     0,     7,     5,
       0,    16,    13,   182,   183,   331,   235,     0,   216,   221,
     184,   219,   220,   172,   311,   314,   315,   318,   324,   326,
       0,   316,   185,   214,   172,   312,   204,   203,   202,   207,
       0,   271,   276,    12,   280,   290,   290,     6,    18,   175,
     233,   236,   323,     0,     0,     0,    15,   171,   173,   358,
      79,   338,   325,   313,    14,   206,   290,   290,   280,   332,
       0,   282,   284,   285,   287,   333,   334,   289,     0,   279,
     291,     0,     0,   176,   178,   234,   317,   168,   169,   166,
     167,   164,   165,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    77,   226,    75,    85,   113,    87,
      90,    92,   114,   107,    94,    99,   101,   103,   105,    97,
     110,   111,   112,   115,   116,   117,   118,   134,   130,   109,
     135,   136,   138,   139,   141,   142,   137,   131,   217,   223,
     129,   222,     0,     0,   215,   359,   127,     0,    80,    81,
      84,   321,     0,     0,     0,   344,     0,     0,     0,   275,
     283,   281,     0,   265,     0,   270,     0,     0,     0,     0,
      74,     0,     0,     0,     0,    82,     0,     0,   175,    61,
      19,     0,    23,    36,    26,    34,    35,    37,    38,    39,
      40,    41,    42,    43,    44,    51,    52,    53,    54,    55,
       0,    68,    69,    70,     0,   129,     0,   228,   224,   123,
      97,   121,   122,   124,     0,   126,   125,     0,   120,    96,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   158,     0,   159,     0,   161,   160,     0,   154,   153,
       0,   157,   156,   155,     0,   163,   162,     0,   144,   143,
       0,   149,     0,     0,   174,     0,   218,     0,   322,     0,
     320,   328,   329,   319,   339,   340,   342,     0,   267,   272,
     277,   286,   288,   213,   299,   208,   210,   292,     0,    28,
      45,    57,    72,    58,     0,     0,    82,     0,     0,    83,
       0,     0,     0,     0,     0,    25,    24,    49,    48,   179,
     229,     0,     0,   133,   132,     0,   190,   191,     0,    86,
      88,    91,    93,    95,   100,   102,   104,   106,   108,    78,
       0,   151,     0,   150,   146,   145,   147,   180,   361,   128,
       0,   344,   348,   345,   296,   298,   309,   212,   209,   208,
     294,     0,   293,     0,     0,     0,     0,     0,    60,    59,
       0,     0,    46,     0,    31,    17,    19,     0,   225,   227,
     119,    98,    79,   336,   192,   349,   188,   350,   352,     0,
     140,   148,     0,   181,   364,     0,   362,   363,     0,     0,
     365,   369,     0,   330,   341,   343,   336,   346,   349,   347,
     301,   358,   303,   304,     0,   305,   211,   295,    73,     0,
       0,    82,    82,     0,     0,     0,     0,    33,    32,    20,
      50,     0,     0,   344,     0,   351,    79,   336,    76,   152,
       0,     0,     0,     0,   309,   300,   306,     0,    62,     0,
       0,    56,    65,    27,    46,   354,   356,   337,   353,     0,
       0,     0,     0,     0,   360,   358,     0,     0,     0,    82,
      82,    47,   355,   357,   366,   367,     0,   302,   308,   307,
      64,    63,     0,     0,     0,     0,     0,     0,    66,    67,
       0,   368
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,    29,    69,    30,    31,    32,    72,   109,   353,
     240,   241,   242,   243,   412,   413,   244,   465,   245,   246,
     417,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   164,   206,
     207,   208,   348,   264,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   210,   187,   188,   189,   190,
     191,   192,   193,   384,   194,   195,   196,   382,   383,   300,
     304,   292,   294,   297,   307,   197,   116,   117,   118,   202,
     142,   143,   144,   266,   354,    33,    34,   315,    36,   316,
     424,   283,   284,   366,    38,    39,    40,    41,    42,    96,
      43,    98,   397,   333,   399,   334,    78,   119,    79,    92,
      81,    82,   198,   267,   199,   361,    44,    45,   111,   112,
      46,    47,    61,    48,    49,    50,    51,    52,    63,   100,
      53,    54,   106,   127,    55,    56,   104,   128,   138,   130,
     221,   131,   132,   133,   134,   139,   140,   224,   337,   338,
     394,   395,   396,   484,   451,   452,   453,   506,   519,   454,
      93,    94,    84,    85,    86,    87,    88,    89,    90,   212,
     213,   321,   200,   136,   137,   472,   473,   214,   215,   324,
     325,   326,   327,   393,   474,   427,   428,   204,   205,   442
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -399
static const yytype_int16 yypact[] =
{
     478,    -2,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,    36,    57,    38,    63,   533,
    -399,  -399,    32,  -399,     9,    50,    46,    46,  -399,  -399,
    -399,  1271,  -399,  -399,  1271,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,    27,  -399,    61,  -399,  -399,  -399,  -399,
    -399,    64,    68,    71,  -399,    91,  -399,    -2,  -399,  -399,
      49,  -399,  -399,  -399,  -399,  -399,    54,    46,    14,  -399,
    -399,  -399,    86,    28,  -399,  -399,     1,  -399,  -399,    65,
      31,  -399,  -399,  -399,    35,    51,  -399,  -399,  1271,  -399,
      97,  -399,  -399,  -399,    59,    98,    98,  -399,  -399,  -399,
    -399,    54,  -399,   116,   514,    46,  -399,  -399,  -399,   107,
     714,    42,  -399,  -399,  -399,  -399,    98,    98,    59,  -399,
     121,   129,  -399,  -399,   105,  -399,  -399,  -399,   142,  -399,
    -399,   148,   856,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,   514,   714,   714,   714,   714,   825,   825,
     936,   714,   714,  1078,  -399,  -399,    90,   127,  -399,   130,
     126,   131,  -399,  -399,   132,   123,    33,    23,   -16,   100,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   145,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  1271,   109,  -399,  -399,  -399,   160,  -399,  -399,
     162,  -399,   170,   233,   173,  -399,   171,   174,   183,  -399,
      59,  -399,   714,  -399,  1176,  -399,   128,   185,   714,   186,
    -399,  1128,   141,   152,   252,   714,   153,   155,  -399,  -399,
    1271,   634,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
     175,  -399,  -399,  -399,   209,   193,  1271,   212,  -399,  -399,
    -399,  -399,  -399,  -399,   164,  -399,  -399,  1078,  -399,  -399,
    -399,   218,   222,   223,  1271,   714,   714,   714,   714,   714,
     714,  -399,   714,  -399,   714,  -399,  -399,   714,  -399,  -399,
     714,  -399,  -399,  -399,   714,  -399,  -399,   714,  -399,  -399,
     714,   714,    59,    59,  -399,   220,    46,   176,  -399,   714,
    -399,   224,  -399,  -399,  -399,   225,  -399,  1271,  -399,  -399,
    -399,  -399,  -399,  -399,   221,  1176,  -399,  1127,   227,  -399,
    -399,  -399,   226,  -399,   242,   714,  1238,   229,   231,  -399,
     714,   714,   967,   236,   856,  -399,  -399,  -399,  -399,  -399,
     514,   238,   228,  -399,  -399,   714,  -399,   -31,   213,   127,
     130,   126,   131,   132,   123,    33,    23,   -16,  -399,  -399,
     241,  -399,   243,   239,  -399,  -399,  -399,  1271,   167,  -399,
     233,   240,    73,  -399,  -399,   244,    46,  -399,  -399,  1176,
    -399,   246,  -399,   714,   195,   247,   248,   250,  -399,  -399,
     255,   256,  1271,   745,  -399,  -399,  1271,  1128,  -399,  -399,
    -399,  -399,   714,     8,  -399,    89,  -399,  -399,    92,   714,
    -399,  -399,   714,  -399,  -399,   198,  -399,  -399,   207,   208,
    -399,  -399,   259,  -399,  -399,  -399,    25,  -399,    48,  -399,
    -399,   107,  -399,  -399,   237,   245,  -399,  -399,  -399,   714,
    1128,   714,   714,  1128,  1128,   258,   967,  -399,  -399,  -399,
    -399,   261,   263,  -399,   264,  -399,   714,   265,  -399,  -399,
     320,   233,   233,   267,    46,  -399,  -399,   269,   291,   268,
     270,  -399,  -399,  -399,  1271,  -399,  -399,  -399,  -399,   272,
     275,   276,   278,   277,  -399,   107,   714,   279,  1128,   714,
     714,  -399,  -399,  -399,  -399,  -399,   335,  -399,  -399,  -399,
    -399,  -399,   284,   285,   281,  1128,  1128,   342,  -399,  -399,
     290,  -399
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -399,  -399,  -399,     7,   328,  -399,  -399,  -399,  -399,   -52,
      11,  -399,   125,  -399,   -98,  -399,  -223,  -127,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -398,   -96,
    -383,  -203,  -308,  -117,  -399,    83,  -399,    84,    82,    85,
    -399,  -135,    88,    80,    79,    78,    76,  -145,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,    66,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,   286,  -399,  -399,  -399,
     144,  -399,  -399,  -399,  -195,  -399,  -399,     6,  -399,    43,
    -399,   106,  -399,  -399,  -236,  -399,  -399,  -399,  -399,     3,
      12,  -399,   -15,  -303,  -399,  -399,  -399,  -399,   271,   349,
    -399,  -399,  -399,  -399,  -129,  -399,  -201,   -26,  -399,  -399,
    -187,  -399,   182,  -399,  -399,  -399,  -399,  -399,  -399,  -399,
    -399,  -399,  -399,  -399,  -399,  -399,  -399,  -399,   -46,   260,
    -399,  -399,  -399,   169,  -399,  -399,  -399,  -399,  -399,    53,
    -399,  -399,  -399,  -399,   -97,  -399,  -399,  -399,  -399,  -399,
     -34,  -399,   -33,   -85,  -399,  -399,   302,  -399,  -337,  -399,
    -399,  -399,   -36,  -399,   -99,   -83,  -399,  -399,  -399,   -78,
    -399,     5,  -399,  -399,  -315,  -366,  -399,  -393,  -399,  -399
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -336
static const yytype_int16 yytable[] =
{
      91,    91,    83,   209,    95,   123,    35,   314,   344,   270,
     270,   270,   270,   275,   276,   278,   270,   270,   165,   269,
     271,   272,   273,   335,   268,   342,   279,   280,    75,  -170,
     425,   478,   398,    70,    75,    35,  -170,   336,   406,   471,
      59,    91,    59,    37,   113,  -327,   282,    99,   367,    75,
     110,    75,   426,    97,    91,   448,    97,   165,   485,   475,
     141,    59,    75,    66,   103,   129,    57,    58,   135,     4,
       5,   359,    37,  -335,    76,   107,    75,   449,    73,    91,
     216,   217,   475,   422,   423,   145,   425,   301,   302,   303,
    -335,   392,   135,   499,   101,  -170,   398,  -214,  -214,    71,
     114,   125,  -170,    60,  -214,    64,   265,   211,   518,   448,
      97,   209,   517,    76,  -214,   120,   121,   108,   349,    74,
    -311,  -311,   422,   423,   298,   299,   332,  -311,   102,   414,
      76,  -273,   295,   296,   335,  -263,   335,  -311,   105,   422,
     446,   270,   270,   270,   270,   270,    77,   270,   336,   270,
     336,    76,   270,   489,   490,   270,   115,   282,  -268,   270,
     282,    77,   422,   446,   126,   281,  -278,    75,   368,   378,
      76,   147,   148,   149,   150,   151,   152,   322,    76,   285,
     286,   146,   434,   203,   135,   305,   306,   422,   446,   219,
     468,   222,   433,   380,   470,   265,   339,   340,   335,   220,
     458,   522,   523,   422,   423,   265,   476,   477,    62,    65,
     223,   379,   336,   385,   385,   381,   225,   466,   287,   289,
     270,   293,   288,   389,   317,   290,   318,   291,   405,   349,
     421,   418,   319,   410,   411,   320,    75,   488,   323,   328,
     491,   492,   329,   414,   435,   436,   437,   438,   439,   440,
     441,   330,   308,   309,   341,   343,   345,   347,   154,   310,
     311,   312,   313,   357,   165,   155,   156,   346,   350,   157,
     351,   158,   159,   160,   161,   162,   135,   135,   358,   163,
      91,   -71,   360,   363,   270,   521,   209,   364,   365,   387,
    -297,   388,   404,   420,   390,   391,   402,   403,   408,   466,
     409,   429,   528,   529,   415,   209,   419,   430,   431,   432,
     459,   444,   460,   480,   450,   457,   265,   461,   265,   462,
     463,   464,   481,   482,   483,   486,   493,   495,   496,   498,
    -335,   501,   504,  -310,   507,   508,   479,   509,   512,   510,
     513,   514,   487,   515,   349,   349,   524,   516,   520,   525,
     526,   527,   407,   530,   443,   531,    91,    68,   447,   209,
      91,   270,   455,   123,   469,   416,   356,   511,   494,   369,
     371,   370,   374,   375,   372,   376,   377,   265,   373,   386,
     124,   265,   352,   362,   456,    80,   201,   505,   218,   331,
     401,   122,   349,   349,   500,   497,   445,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      91,     0,    91,   113,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   265,     0,     0,   265,   265,     0,
     265,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   502,   503,     0,    91,     0,
     455,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   265,     0,     0,     0,     0,     0,    -2,     1,
       0,  -186,     0,     0,     2,     0,     0,     0,     0,   265,
     265,     3,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    75,     0,     0,
       0,   147,   148,   149,   150,   151,   152,     0,     0,     0,
       0,     0,     0,    -3,    67,     0,  -186,     0,     0,     2,
       0,     0,     0,     0,     0,     0,     3,  -186,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   153,     0,  -186,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -186,     0,     0,     0,     0,     0,     0,
       0,     0,  -186,     0,     0,     0,     0,     0,   154,     0,
       0,     0,     0,     0,     0,   155,   156,     0,     0,   157,
       0,   158,   159,   160,   161,   162,     0,     0,     0,   163,
       0,     0,     0,     0,     0,   226,     0,    75,  -186,     0,
     -22,   147,   148,   149,   150,   151,   152,   355,  -186,   -22,
     -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,
     -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,   -22,
     -22,   -22,   -22,   227,   228,   229,   230,   231,     0,   232,
     233,   234,   235,   236,   237,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   238,   -22,   239,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    75,     0,     0,
       0,   147,   148,   149,   150,   151,   152,     0,   154,     0,
       0,     0,     0,     0,     0,   155,   156,     0,     0,   157,
       0,   158,   159,   160,   161,   162,   226,     0,    75,   163,
       0,   -30,   147,   148,   149,   150,   151,   152,   467,     0,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,   -30,
     -30,   -30,   -30,   -30,   227,   228,   229,   230,   231,     0,
     232,   233,   234,   235,   236,   237,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   154,     0,
       0,     0,   238,   -30,   239,   155,   156,     0,     0,   157,
       0,   158,   159,   160,   161,   162,     0,     0,    75,   163,
       0,     0,   147,   148,   149,   150,   151,   152,     0,   154,
       0,     0,     0,     0,     0,     0,   155,   156,     0,     0,
     157,     0,   158,   159,   160,   161,   162,   226,     0,    75,
     163,     0,   -21,   147,   148,   149,   150,   151,   152,     0,
       0,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,
     -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,   -21,
     -21,   -21,   -21,   -21,   -21,   227,   228,   229,   230,   231,
       0,   232,   233,   234,   235,   236,   237,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   154,
       0,     0,     0,   238,   -21,   239,   155,   156,     0,     0,
     157,     0,   158,   159,   160,   161,   162,     0,     0,    75,
     274,     0,     0,   147,   148,   149,   150,   151,   152,     0,
     154,     0,     0,     0,     0,     0,     0,   155,   156,     0,
       0,   157,     0,   158,   159,   160,   161,   162,   226,     0,
      75,   163,     0,   -29,   147,   148,   149,   150,   151,   152,
       0,     0,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,   -29,
     -29,   -29,   -29,   -29,   -29,   -29,   227,   228,   229,   230,
     231,     0,   232,   233,   234,   235,   236,   237,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     154,     0,     0,     0,   238,   -29,   239,   155,   156,     0,
       0,   157,     0,   158,   159,   160,   161,   162,     0,     0,
       0,   277,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   154,     0,     0,     0,     0,     0,     0,   155,   156,
       0,     0,   157,     0,   158,   159,   160,   161,   162,   281,
       0,    75,   163,     0,  -189,   147,   148,   149,   150,   151,
     152,     0,     0,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,  -189,
    -189,  -189,  -189,  -189,  -189,  -189,  -189,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   226,
       0,    75,     0,     2,     0,   147,   148,   149,   150,   151,
     152,     0,     4,     5,     0,     0,     0,     0,     0,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,     0,   227,   228,   229,
     230,   231,   154,   232,   233,   234,   235,   236,   237,   155,
     156,     0,     2,   157,     0,   158,   159,   160,   161,   162,
       0,     4,     5,   163,     0,   238,   400,   239,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,     0,     0,     0,     0,     0,
       0,     0,   154,     0,     0,     0,     0,     0,     0,   155,
     156,     0,     0,   157,     0,   158,   159,   160,   161,   162,
       0,    75,     0,   163,     2,   147,   148,   149,   150,   151,
     152,     0,     0,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,     2,     0,     0,
       0,     0,     0,     0,     0,     0,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,     0,     0,     0,     0,     0,     0,   155,
     156,     0,     0,   157,     0,   158,   159,   160,   161,   162,
       0,     0,     0,   163
};

static const yytype_int16 yycheck[] =
{
      36,    37,    36,   120,    37,    90,     0,   202,   231,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   114,   154,
     155,   156,   157,   224,   153,   228,   161,   162,     3,     1,
     367,   429,   335,     1,     3,    29,     1,   224,   346,   422,
       4,    77,     4,     0,    77,     3,   163,    44,   284,     3,
      76,     3,   367,    41,    90,   392,    44,   153,   451,   425,
     106,     4,     3,     0,    57,     6,    68,    69,   104,    15,
      16,   266,    29,    65,   105,    68,     3,   392,    69,   115,
     126,   127,   448,   114,   115,   111,   423,   103,   104,   105,
      65,   327,   128,   476,    67,    67,   399,    69,    70,    67,
      86,    98,    67,    67,    76,    67,   142,    65,   506,   446,
      98,   228,   505,   105,    86,   114,   115,    68,   235,    69,
      69,    70,   114,   115,   101,   102,   222,    76,    67,   352,
     105,    67,    99,   100,   335,    67,   337,    86,    67,   114,
     115,   286,   287,   288,   289,   290,   115,   292,   335,   294,
     337,   105,   297,   461,   462,   300,    70,   274,    67,   304,
     277,   115,   114,   115,    67,     1,    68,     3,   285,   304,
     105,     7,     8,     9,    10,    11,    12,   213,   105,    89,
      90,    65,    15,    76,   220,    85,    86,   114,   115,    68,
     413,    86,   387,   310,   417,   231,    68,    69,   399,    70,
     403,   509,   510,   114,   115,   241,   114,   115,    26,    27,
      68,   307,   399,   312,   313,   311,    68,   412,    91,    93,
     365,    98,    92,   319,   115,    94,    66,    95,   345,   346,
     365,   360,    70,   350,   351,    65,     3,   460,    65,    68,
     463,   464,    68,   466,    77,    78,    79,    80,    81,    82,
      83,    68,   107,   108,    69,    69,   115,     5,    94,   114,
     115,   116,   117,    88,   360,   101,   102,   115,   115,   105,
     115,   107,   108,   109,   110,   111,   312,   313,    69,   115,
     316,    88,    70,    65,   429,   508,   403,    65,    65,    69,
      69,   115,    50,    65,    70,    70,    69,    71,    69,   494,
      69,    88,   525,   526,    68,   422,    68,    66,    65,    70,
     115,    71,    65,   115,    70,    69,   352,    69,   354,    69,
      65,    65,   115,   115,    65,    88,    68,    66,    65,    65,
      65,    11,    65,    88,    65,    44,   432,    69,    66,    69,
      65,    65,   459,    65,   461,   462,    11,    70,    69,    65,
      65,    70,   346,    11,   390,    65,   392,    29,   392,   476,
     396,   506,   396,   448,   416,   354,   241,   494,   466,   286,
     288,   287,   292,   294,   289,   297,   300,   413,   290,   313,
      94,   417,   238,   277,   399,    36,   115,   484,   128,   220,
     337,    89,   509,   510,   477,   473,   391,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     446,    -1,   448,   446,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   460,    -1,    -1,   463,   464,    -1,
     466,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   481,   482,    -1,   484,    -1,
     484,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   508,    -1,    -1,    -1,    -1,    -1,     0,     1,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,   525,
     526,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,     3,    -1,    -1,
      -1,     7,     8,     9,    10,    11,    12,    -1,    -1,    -1,
      -1,    -1,    -1,     0,     1,    -1,     3,    -1,    -1,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    13,    69,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    -1,   105,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    94,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,   105,
      -1,   107,   108,   109,   110,   111,    -1,    -1,    -1,   115,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     3,   105,    -1,
       6,     7,     8,     9,    10,    11,    12,    13,   115,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    -1,    45,
      46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,
      -1,     7,     8,     9,    10,    11,    12,    -1,    94,    -1,
      -1,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,   105,
      -1,   107,   108,   109,   110,   111,     1,    -1,     3,   115,
      -1,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      45,    46,    47,    48,    49,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,    -1,
      -1,    -1,    67,    68,    69,   101,   102,    -1,    -1,   105,
      -1,   107,   108,   109,   110,   111,    -1,    -1,     3,   115,
      -1,    -1,     7,     8,     9,    10,    11,    12,    -1,    94,
      -1,    -1,    -1,    -1,    -1,    -1,   101,   102,    -1,    -1,
     105,    -1,   107,   108,   109,   110,   111,     1,    -1,     3,
     115,    -1,     6,     7,     8,     9,    10,    11,    12,    -1,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      -1,    45,    46,    47,    48,    49,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    94,
      -1,    -1,    -1,    67,    68,    69,   101,   102,    -1,    -1,
     105,    -1,   107,   108,   109,   110,   111,    -1,    -1,     3,
     115,    -1,    -1,     7,     8,     9,    10,    11,    12,    -1,
      94,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,    -1,
      -1,   105,    -1,   107,   108,   109,   110,   111,     1,    -1,
       3,   115,    -1,     6,     7,     8,     9,    10,    11,    12,
      -1,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    -1,    45,    46,    47,    48,    49,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    -1,    -1,    -1,    67,    68,    69,   101,   102,    -1,
      -1,   105,    -1,   107,   108,   109,   110,   111,    -1,    -1,
      -1,   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,   101,   102,
      -1,    -1,   105,    -1,   107,   108,   109,   110,   111,     1,
      -1,     3,   115,    -1,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,     3,    -1,     6,    -1,     7,     8,     9,    10,    11,
      12,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    39,    40,    41,
      42,    43,    94,    45,    46,    47,    48,    49,    50,   101,
     102,    -1,     6,   105,    -1,   107,   108,   109,   110,   111,
      -1,    15,    16,   115,    -1,    67,    69,    69,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,    -1,    -1,   105,    -1,   107,   108,   109,   110,   111,
      -1,     3,    -1,   115,     6,     7,     8,     9,    10,    11,
      12,    -1,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    94,    -1,    -1,    -1,    -1,    -1,    -1,   101,
     102,    -1,    -1,   105,    -1,   107,   108,   109,   110,   111,
      -1,    -1,    -1,   115
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     1,     6,    13,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,   119,   120,
     122,   123,   124,   213,   214,   215,   216,   217,   222,   223,
     224,   225,   226,   228,   244,   245,   248,   249,   251,   252,
     253,   254,   255,   258,   259,   262,   263,    68,    69,     4,
      67,   250,   250,   256,    67,   250,     0,     1,   122,   121,
       1,    67,   125,    69,    69,     3,   105,   115,   234,   236,
     237,   238,   239,   288,   290,   291,   292,   293,   294,   295,
     296,   300,   237,   288,   289,   290,   227,   228,   229,   227,
     257,    67,    67,   121,   264,    67,   260,   121,    68,   126,
     245,   246,   247,   290,    86,    70,   204,   205,   206,   235,
     114,   115,   294,   291,   204,   227,    67,   261,   265,     6,
     267,   269,   270,   271,   272,   300,   301,   302,   266,   273,
     274,   266,   208,   209,   210,   245,    65,     7,     8,     9,
      10,    11,    12,    67,    94,   101,   102,   105,   107,   108,
     109,   110,   111,   115,   156,   157,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   184,   185,   186,
     187,   188,   189,   190,   192,   193,   194,   203,   240,   242,
     300,   236,   207,    76,   315,   316,   157,   158,   159,   161,
     183,    65,   297,   298,   305,   306,   266,   266,   267,    68,
      70,   268,    86,    68,   275,    68,     1,    39,    40,    41,
      42,    43,    45,    46,    47,    48,    49,    50,    67,    69,
     128,   129,   130,   131,   134,   136,   137,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   161,   300,   211,   241,   242,   169,
     175,   169,   169,   169,   115,   175,   175,   115,   175,   169,
     169,     1,   161,   219,   220,    89,    90,    91,    92,    93,
      94,    95,   199,    98,   200,    99,   100,   201,   101,   102,
     197,   103,   104,   105,   198,    85,    86,   202,   107,   108,
     114,   115,   116,   117,   212,   215,   217,   115,    66,    70,
      65,   299,   300,    65,   307,   308,   309,   310,    68,    68,
      68,   271,   157,   231,   233,   244,   248,   276,   277,    68,
      69,    69,   159,    69,   134,   115,   115,     5,   160,   161,
     115,   115,   208,   127,   212,    13,   130,    88,    69,   212,
      70,   243,   219,    65,    65,    65,   221,   222,   161,   163,
     165,   166,   167,   170,   171,   172,   173,   174,   169,   157,
     161,   157,   195,   196,   191,   302,   191,    69,   115,   157,
      70,    70,   222,   311,   278,   279,   280,   230,   231,   232,
      69,   277,    69,    71,    50,   161,   160,   215,    69,    69,
     161,   161,   132,   133,   134,    68,   128,   138,   242,    68,
      65,   169,   114,   115,   218,   296,   312,   313,   314,    88,
      66,    65,    70,   212,    15,    77,    78,    79,    80,    81,
      82,    83,   317,   300,    71,   309,   115,   288,   296,   312,
      70,   282,   283,   284,   287,   288,   230,    69,   159,   115,
      65,    69,    69,    65,    65,   135,   212,    13,   134,   127,
     134,   158,   303,   304,   312,   313,   114,   115,   156,   157,
     115,   115,   115,    65,   281,   315,    88,   161,   134,   160,
     160,   134,   134,    68,   132,    66,    65,   307,    65,   158,
     303,    11,   300,   300,    65,   282,   285,    65,    44,    69,
      69,   135,    66,    65,    65,    65,    70,   315,   156,   286,
      69,   134,   160,   160,    11,    65,    65,    70,   134,   134,
      11,    65
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
		}
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
		}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 253 "rv_gram.y"
    {
			*gProject->Parse_TOS->yyerrstream << "Errors - Aborting parse.\n";
			gProject->Parse_TOS->transUnit = (TransUnit*) NULL;
			YYACCEPT;
		}
    break;

  case 5:

/* Line 1464 of yacc.c  */
#line 261 "rv_gram.y"
    {
			(yyval.transunit) = gProject->Parse_TOS->transUnit;
			(yyval.transunit)->add((yyvsp[(1) - (2)].stemnt));
		}
    break;

  case 6:

/* Line 1464 of yacc.c  */
#line 266 "rv_gram.y"
    {
			(yyval.transunit)->add((yyvsp[(2) - (3)].stemnt));
		}
    break;

  case 7:

/* Line 1464 of yacc.c  */
#line 272 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->ReinitializeCtxt();
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScopes(FILE_SCOPE);
			gProject->Parse_TOS->err_top_level = 0;            
		}
    break;

  case 8:

/* Line 1464 of yacc.c  */
#line 281 "rv_gram.y"
    {
			(yyval.stemnt) = (yyvsp[(1) - (1)].declStemnt);

			prvhooks->flush_buffer((yyvsp[(1) - (1)].declStemnt));
		}
    break;

  case 9:

/* Line 1464 of yacc.c  */
#line 287 "rv_gram.y"
    {
			(yyval.stemnt) = (yyvsp[(1) - (1)].functionDef);

			prvhooks->flush_buffer((yyvsp[(1) - (1)].functionDef));
		}
    break;

  case 10:

/* Line 1464 of yacc.c  */
#line 293 "rv_gram.y"
    {
			(yyval.stemnt) = (yyvsp[(1) - (1)].stemnt);
			prvhooks->flush_buffer();
		}
    break;

  case 11:

/* Line 1464 of yacc.c  */
#line 298 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		}
    break;

  case 12:

/* Line 1464 of yacc.c  */
#line 302 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		}
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
				(yyval.functionDef)->inherit(blk);

		if( (yyvsp[(1) - (2)].decl)->name )
		  prvhooks->grab_scope( (yyvsp[(1) - (2)].decl)->name->name );
			}
			else
			{
				delete (yyvsp[(1) - (2)].decl);
				(yyval.functionDef) = (FunctionDef*) NULL;
			}
		}
    break;

  case 14:

/* Line 1464 of yacc.c  */
#line 335 "rv_gram.y"
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
		}
    break;

  case 15:

/* Line 1464 of yacc.c  */
#line 364 "rv_gram.y"
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
		}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 397 "rv_gram.y"
    {  
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ReEnterScope();
		}
    break;

  case 17:

/* Line 1464 of yacc.c  */
#line 402 "rv_gram.y"
    {
			Block*    block = new Block(*(yyvsp[(1) - (6)].loc));
			(yyval.stemnt) = block;
            block->addDecls((yyvsp[(3) - (6)].decl));
            block->addStatements(ReverseList((yyvsp[(4) - (6)].stemnt)));
			block->inherit(static_cast<Block*>((yyvsp[(5) - (6)].stemnt)));
			if (gProject->Parse_TOS->transUnit)
			{
				yyCheckLabelsDefinition(gProject->Parse_TOS->transUnit->contxt.labels);
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
			}
		}
    break;

  case 18:

/* Line 1464 of yacc.c  */
#line 416 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 422 "rv_gram.y"
    {
            (yyval.stemnt) = (Statement*) NULL;        
        }
    break;

  case 20:

/* Line 1464 of yacc.c  */
#line 426 "rv_gram.y"
    {
		    /* C99 compliance */
            Block*    block = new Block(NoLocation);
            (yyval.stemnt) = block;
            block->addDecls((yyvsp[(1) - (3)].decl));
            block->addStatements(ReverseList((yyvsp[(2) - (3)].stemnt)));
            block->inherit(static_cast<Block*>((yyvsp[(3) - (3)].stemnt)));
        }
    break;

  case 21:

/* Line 1464 of yacc.c  */
#line 436 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		}
    break;

  case 24:

/* Line 1464 of yacc.c  */
#line 444 "rv_gram.y"
    {
			/* Hook them up backwards, we'll reverse them later. */
			if ((yyvsp[(2) - (2)].stemnt))
			{
				(yyvsp[(2) - (2)].stemnt)->next = (yyvsp[(1) - (2)].stemnt);
				(yyval.stemnt) = (yyvsp[(2) - (2)].stemnt);
			}
		}
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 453 "rv_gram.y"
    {    /* preprocessor #line directive */
			/* Hook them up backwards, we'll reverse them later. */
			if ((yyvsp[(2) - (2)].stemnt))
			{
				(yyvsp[(2) - (2)].stemnt)->next = (yyvsp[(1) - (2)].stemnt);
				(yyval.stemnt) = (yyvsp[(2) - (2)].stemnt);
			}
		}
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 471 "rv_gram.y"
    {
			Block*    block = new Block(*(yyvsp[(1) - (5)].loc));
			(yyval.stemnt) = block;
			block->addDecls((yyvsp[(2) - (5)].decl));
			block->addStatements(ReverseList((yyvsp[(3) - (5)].stemnt)));
			block->inherit(static_cast<Block*>((yyvsp[(4) - (5)].stemnt)));
			
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
		}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 482 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		}
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 488 "rv_gram.y"
    {
			(yyval.stemnt) = (Statement*) NULL;
		}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 496 "rv_gram.y"
    {
			/* Hook them up backwards, we'll reverse them later. */
			if ((yyvsp[(2) - (2)].stemnt))
			{
				(yyvsp[(2) - (2)].stemnt)->next = (yyvsp[(1) - (2)].stemnt);
				(yyval.stemnt) = (yyvsp[(2) - (2)].stemnt);
			}
		}
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 505 "rv_gram.y"
    {    /* preprocessor #line directive */
			/* Hook them up backwards, we'll reverse them later. */
			if ((yyvsp[(2) - (2)].stemnt))
			{
				(yyvsp[(2) - (2)].stemnt)->next = (yyvsp[(1) - (2)].stemnt);
				(yyval.stemnt) = (yyvsp[(2) - (2)].stemnt);
			}
		}
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 527 "rv_gram.y"
    {
			delete (yyvsp[(2) - (2)].loc);
			(yyval.stemnt) = (Statement*) NULL;
		}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 534 "rv_gram.y"
    {
            (yyval.stemnt) = (Statement*) NULL;        
        }
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 538 "rv_gram.y"
    {
		    /* C99 compliance */
            Block*    block = new Block(NoLocation);
            (yyval.stemnt) = block;
            block->addDecls((yyvsp[(1) - (3)].decl));
            block->addStatements(ReverseList((yyvsp[(2) - (3)].stemnt)));
            block->inherit(static_cast<Block*>((yyvsp[(3) - (3)].stemnt)));
        }
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 548 "rv_gram.y"
    {
			(yyval.stemnt) = new ExpressionStemnt((yyvsp[(1) - (2)].value),*(yyvsp[(2) - (2)].loc));
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 555 "rv_gram.y"
    {
	  if( (yyvsp[(1) - (2)].label)->type == LT_Goto )
		prvhooks->process_label((yyvsp[(1) - (2)].label)->name->name); 
	}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 560 "rv_gram.y"
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
		}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 585 "rv_gram.y"
    {
			(yyval.stemnt) = new SwitchStemnt((yyvsp[(3) - (5)].value),(yyvsp[(5) - (5)].stemnt),*(yyvsp[(1) - (5)].loc));
			delete (yyvsp[(1) - (5)].loc);
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(4) - (5)].loc);
		}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 594 "rv_gram.y"
    {
			(yyval.stemnt) = new Statement(ST_BreakStemnt,*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 602 "rv_gram.y"
    {
			(yyval.stemnt) = new Statement(ST_ContinueStemnt,*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 610 "rv_gram.y"
    {
			(yyval.stemnt) = new ReturnStemnt((yyvsp[(2) - (3)].value),*(yyvsp[(1) - (3)].loc));
			delete (yyvsp[(1) - (3)].loc);
			delete (yyvsp[(3) - (3)].loc);
		}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 618 "rv_gram.y"
    {
			(yyval.stemnt) = new GotoStemnt((yyvsp[(2) - (3)].symbol),*(yyvsp[(1) - (3)].loc));
			delete (yyvsp[(1) - (3)].loc);
			delete (yyvsp[(3) - (3)].loc);
		}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 626 "rv_gram.y"
    {
			(yyval.stemnt) = new Statement(ST_NullStemnt,*(yyvsp[(1) - (1)].loc));
			delete (yyvsp[(1) - (1)].loc);
		}
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 633 "rv_gram.y"
    {
			(yyval.stemnt) = new IfStemnt((yyvsp[(3) - (5)].value),(yyvsp[(5) - (5)].stemnt),*(yyvsp[(1) - (5)].loc));
			delete (yyvsp[(1) - (5)].loc);
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(4) - (5)].loc);
		}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 642 "rv_gram.y"
    {
			(yyval.stemnt) = new IfStemnt((yyvsp[(3) - (7)].value),(yyvsp[(5) - (7)].stemnt),*(yyvsp[(1) - (7)].loc),(yyvsp[(7) - (7)].stemnt));
			delete (yyvsp[(1) - (7)].loc);
			delete (yyvsp[(2) - (7)].loc);
			delete (yyvsp[(4) - (7)].loc);
			delete (yyvsp[(6) - (7)].loc);
		}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 652 "rv_gram.y"
    {
			(yyval.stemnt) = new DoWhileStemnt((yyvsp[(5) - (7)].value),(yyvsp[(2) - (7)].stemnt),*(yyvsp[(1) - (7)].loc));
			delete (yyvsp[(1) - (7)].loc);
			delete (yyvsp[(3) - (7)].loc);
			delete (yyvsp[(4) - (7)].loc);
			delete (yyvsp[(6) - (7)].loc);
			delete (yyvsp[(7) - (7)].loc);
		}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 663 "rv_gram.y"
    {
			(yyval.stemnt) = new WhileStemnt((yyvsp[(3) - (5)].value),(yyvsp[(5) - (5)].stemnt),*(yyvsp[(1) - (5)].loc));
			delete (yyvsp[(1) - (5)].loc);
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(4) - (5)].loc);
		}
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 673 "rv_gram.y"
    {
			(yyval.stemnt) = new ForStemnt((yyvsp[(3) - (9)].value),(yyvsp[(5) - (9)].value),(yyvsp[(7) - (9)].value),*(yyvsp[(1) - (9)].loc),(yyvsp[(9) - (9)].stemnt));
			delete (yyvsp[(1) - (9)].loc);
			delete (yyvsp[(2) - (9)].loc);
			delete (yyvsp[(4) - (9)].loc);
			delete (yyvsp[(6) - (9)].loc);
			delete (yyvsp[(8) - (9)].loc);
		}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 683 "rv_gram.y"
    {
            /* C99 compliance - loop iterators can be declared inside for(...) */
            Block *block = new Block(*(yyvsp[(1) - (9)].loc));
            (yyval.stemnt) = block;
            block->addDecls((yyvsp[(3) - (9)].decl));
            block->add(new ForStemnt(NULL,(yyvsp[(5) - (9)].value),(yyvsp[(7) - (9)].value),*(yyvsp[(1) - (9)].loc),(yyvsp[(9) - (9)].stemnt)));
            delete (yyvsp[(1) - (9)].loc);
            delete (yyvsp[(2) - (9)].loc);
            delete (yyvsp[(4) - (9)].loc);
            delete (yyvsp[(6) - (9)].loc);
            delete (yyvsp[(8) - (9)].loc);
        }
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 703 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.label) = gProject->Parse_TOS->parseCtxt->Mk_named_label((yyvsp[(1) - (1)].symbol),
								gProject->Parse_TOS->transUnit->contxt.labels);
		}
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 711 "rv_gram.y"
    {
			(yyval.label) = new Label((yyvsp[(2) - (2)].value));
			delete (yyvsp[(1) - (2)].loc);
		}
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 716 "rv_gram.y"
    {
			(yyval.label) = new Label((yyvsp[(2) - (4)].value),(yyvsp[(4) - (4)].value));
			delete (yyvsp[(1) - (4)].loc);
			delete (yyvsp[(3) - (4)].loc);
		}
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 724 "rv_gram.y"
    {
			(yyval.label) = new Label(LT_Default);
			delete (yyvsp[(1) - (1)].loc);
		}
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 741 "rv_gram.y"
    {
			(yyval.value) = new TrinaryExpr((yyvsp[(1) - (5)].value),(yyvsp[(3) - (5)].value),(yyvsp[(5) - (5)].value),*(yyvsp[(2) - (5)].loc));
			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(4) - (5)].loc);
		}
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 750 "rv_gram.y"
    {
			(yyval.value) = (RVGlob::flags(RVGlob::GLBL_OUTLINE_NOW) && ((yyvsp[(2) - (3)].assignOp) == AO_MultEql || (yyvsp[(2) - (3)].assignOp) == AO_DivEql || (yyvsp[(2) - (3)].assignOp) == AO_ModEql)) ?  // change tag: OUTLINE_FUNCS			
					rv_parser.outline_assignment((yyvsp[(2) - (3)].assignOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location) :  
					new AssignExpr((yyvsp[(2) - (3)].assignOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);			
		}
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 758 "rv_gram.y"
    {
			(yyval.value) = (Expression*) NULL;
		}
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 768 "rv_gram.y"
    {
		   (yyval.value) = (Expression*) NULL;
		}
    break;

  case 86:

/* Line 1464 of yacc.c  */
#line 779 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_Or,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 88:

/* Line 1464 of yacc.c  */
#line 787 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_And,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 794 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_Not,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		}
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 802 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_BitOr,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 810 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_BitXor,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 818 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_BitAnd,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 825 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_BitNot,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 833 "rv_gram.y"
    {
			(yyval.value) = new CastExpr((yyvsp[(2) - (4)].type),(yyvsp[(4) - (4)].value),*(yyvsp[(1) - (4)].loc));
			delete (yyvsp[(1) - (4)].loc);
			delete (yyvsp[(3) - (4)].loc);
		}
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 842 "rv_gram.y"
    {
			(yyval.value) = new RelExpr((yyvsp[(2) - (3)].relOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);
		}
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 849 "rv_gram.y"
    {
			(yyval.value) = new RelExpr((yyvsp[(2) - (3)].relOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);
		}
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 856 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr((yyvsp[(2) - (3)].binOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);
		}
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 863 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr((yyvsp[(2) - (3)].binOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value)->location);			
		}
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 870 "rv_gram.y"
    {			
			(yyval.value) = (RVGlob::flags(RVGlob::GLBL_OUTLINE_NOW)) ? 
				rv_parser.outline((yyvsp[(2) - (3)].binOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value) -> location): // ofer. change tag: OUTLINE_FUNCS
				new BinaryExpr((yyvsp[(2) - (3)].binOp),(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),(yyvsp[(1) - (3)].value) -> location);
		}
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 890 "rv_gram.y"
    {
			(yyval.value) = new SizeofExpr((yyvsp[(3) - (4)].type),*(yyvsp[(1) - (4)].loc));
			delete (yyvsp[(1) - (4)].loc);
			delete (yyvsp[(2) - (4)].loc);
			delete (yyvsp[(4) - (4)].loc);
		}
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 897 "rv_gram.y"
    {
			(yyval.value) = new SizeofExpr((yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		}
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 904 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_Minus,(yyvsp[(2) - (2)].value),HERE);
		}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 910 "rv_gram.y"
    {
			/* Unary plus is an ISO addition (for symmetry) - ignore it */
			(yyval.value) = (yyvsp[(2) - (2)].value);
		}
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 917 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_AddrOf,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 924 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_Deref,(yyvsp[(2) - (2)].value),HERE);
		}
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 930 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_PreInc,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		}
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 937 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_PreDec,(yyvsp[(2) - (2)].value),*(yyvsp[(1) - (2)].loc));
			delete (yyvsp[(1) - (2)].loc);
		}
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 945 "rv_gram.y"
    {
			(yyval.value) = new BinaryExpr(BO_Comma,(yyvsp[(1) - (3)].value),(yyvsp[(3) - (3)].value),*(yyvsp[(2) - (3)].loc));
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 952 "rv_gram.y"
    {
			if ((yyvsp[(1) - (1)].symbol)->entry == NULL && gProject->warn_variable)
			{
				yywarn("Undeclared variable");
			}

			(yyval.value) = new Variable((yyvsp[(1) - (1)].symbol), HERE);
		}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 962 "rv_gram.y"
    {
			(yyval.value) = (yyvsp[(1) - (1)].consValue);
		}
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 968 "rv_gram.y"
    {
			(yyval.value) = (yyvsp[(2) - (3)].value);
			delete (yyvsp[(1) - (3)].loc);
			delete (yyvsp[(3) - (3)].loc);
		}
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 974 "rv_gram.y"
    {
			(yyval.value) = (Expression*) NULL;
			delete (yyvsp[(1) - (3)].loc);
			delete (yyvsp[(3) - (3)].loc);
		}
    break;

  case 140:

/* Line 1464 of yacc.c  */
#line 990 "rv_gram.y"
    {
			(yyval.value) = new IndexExpr((yyvsp[(1) - (4)].value),(yyvsp[(3) - (4)].value),*(yyvsp[(2) - (4)].loc));
			delete (yyvsp[(2) - (4)].loc);
			delete (yyvsp[(4) - (4)].loc);
		}
    break;

  case 143:

/* Line 1464 of yacc.c  */
#line 1002 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_PostInc,(yyvsp[(1) - (2)].value),*(yyvsp[(2) - (2)].loc));
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 1009 "rv_gram.y"
    {
			(yyval.value) = new UnaryExpr(UO_PostDec,(yyvsp[(1) - (2)].value),*(yyvsp[(2) - (2)].loc));
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 1019 "rv_gram.y"
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
		}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 1042 "rv_gram.y"
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
		}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 1065 "rv_gram.y"
    {
			FunctionCall* fc = new FunctionCall((yyvsp[(1) - (4)].value),*(yyvsp[(2) - (4)].loc));

			/* add function args */
			fc->addArgs(ReverseList((yyvsp[(3) - (4)].value)));

			delete (yyvsp[(2) - (4)].loc);
			delete (yyvsp[(4) - (4)].loc);
			(yyval.value) = fc;
		}
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 1078 "rv_gram.y"
    {
			(yyval.value) = (Expression*) NULL;
		}
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 1086 "rv_gram.y"
    {
			(yyval.value) = (yyvsp[(3) - (3)].value);
			(yyval.value)->next = (yyvsp[(1) - (3)].value);

			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 1131 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ReEnterScope();
		}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 1136 "rv_gram.y"
    {
			(yyval.decl) = (Decl*) NULL;
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
		}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 1142 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ReEnterScope();
			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();
		}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 1147 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetVarParam(1, !gProject->Parse_TOS->err_top_level, 0); 
			gProject->Parse_TOS->parseCtxt->SetIsKnR(true); 
		}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 1151 "rv_gram.y"
    {   (yyval.decl) = (yyvsp[(3) - (3)].decl);
			gProject->Parse_TOS->parseCtxt->SetIsKnR(false); 
			gProject->Parse_TOS->parseCtxt->SetVarParam(0, !gProject->Parse_TOS->err_top_level, 1); 
			
			// Exit, but will allow re-enter for a function.
			// Hack, to handle parameters being in the function's scope.
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope(true);
		}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 1163 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.EnterScope();
			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();
		}
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 1169 "rv_gram.y"
    {
			(yyval.decl) = (Decl*) NULL;
		}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 1173 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.EnterScope();
			gProject->Parse_TOS->parseCtxt->ResetDeclCtxt();
		}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 1178 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetVarParam(0, !gProject->Parse_TOS->err_top_level, 0); 
		}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 1181 "rv_gram.y"
    {   (yyval.decl) = (yyvsp[(3) - (3)].decl);
			gProject->Parse_TOS->parseCtxt->SetVarParam(0, !gProject->Parse_TOS->err_top_level, 0);
		}
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 1187 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (2)].decl);
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 1192 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (3)].decl);

			Decl*	appendDecl = (yyvsp[(1) - (3)].decl);
			while (appendDecl->next != NULL)
				appendDecl = appendDecl->next;

			appendDecl->next = (yyvsp[(3) - (3)].decl);
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 1205 "rv_gram.y"
    {
			(yyval.declStemnt) = new DeclStemnt(*(yyvsp[(2) - (2)].loc));
			(yyval.declStemnt)->addDecls(ReverseList((yyvsp[(1) - (2)].decl)));
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 1212 "rv_gram.y"
    {
			(yyval.declStemnt) = new DeclStemnt(*(yyvsp[(2) - (2)].loc));
			(yyval.declStemnt)->addDecls(ReverseList((yyvsp[(1) - (2)].decl)));
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 1220 "rv_gram.y"
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
		}
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 1238 "rv_gram.y"
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
		}
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 1258 "rv_gram.y"
    {
			(yyval.base) = new BaseType(BT_Int);
			gProject->Parse_TOS->parseCtxt->SetDeclCtxt((yyval.base));
		}
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 1277 "rv_gram.y"
    {   
			gProject->Parse_TOS->parseCtxt->PushCtxt();
			gProject->Parse_TOS->parseCtxt->ResetVarParam();
		}
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 1282 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(2) - (2)].type);
			gProject->Parse_TOS->parseCtxt->PopCtxt(false);
		}
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 1289 "rv_gram.y"
    {
			assert ((yyvsp[(1) - (1)].base) == gProject->Parse_TOS->parseCtxt->curCtxt->decl_specs);
			
			gProject->Parse_TOS->possibleType = true;
			(yyval.type) = (yyvsp[(1) - (1)].base);
			if ((yyval.type)->isFunction())
				if(yyerr ("Function type not allowed as type name"))
				  YYERROR;
		}
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 1299 "rv_gram.y"
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
		}
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 1327 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->SetDeclCtxt((yyval.base));
		}
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1343 "rv_gram.y"
    {
			if (! gProject->Parse_TOS->transUnit ||
				gProject->Parse_TOS->transUnit->contxt.syms->current->level >= FUNCTION_SCOPE)
				 (yyval.storage) = (yyvsp[(1) - (1)].storage) ;             
			 else
				 (yyval.storage) = ST_None ;              
		}
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1356 "rv_gram.y"
    {
			(yyval.base) = (BaseType*) NULL;
		}
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 1363 "rv_gram.y"
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
		}
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1381 "rv_gram.y"
    { gProject->Parse_TOS->possibleType = false; }
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1382 "rv_gram.y"
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
		}
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1414 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(2) - (2)].base);

			if (!(yyval.base))
			{
				(yyval.base) = new BaseType();
			}

			if (((yyval.base)->qualifier & (yyvsp[(1) - (2)].typeQual)) != TQ_None)
				yywarn("qualifier already specified");  
							  
			(yyval.base)->qualifier |= (yyvsp[(1) - (2)].typeQual);

		}
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1434 "rv_gram.y"
    {
		   (yyval.base) = (BaseType*) NULL;
		}
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1440 "rv_gram.y"
    { gProject->Parse_TOS->possibleType = false; }
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1441 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(1) - (3)].base);

			if ((yyvsp[(3) - (3)].base))
			{
				(yyval.base)->typemask |= (yyvsp[(3) - (3)].base)->typemask;
				// delete $3;
			}
		}
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1451 "rv_gram.y"
    {
			(yyval.base) = (yyvsp[(2) - (2)].base);

			if (!(yyval.base))
			{
				(yyval.base) = new BaseType();
			}

			if (((yyval.base)->qualifier & (yyvsp[(1) - (2)].typeQual)) != TQ_None)
				yywarn("qualifier already specified");
			(yyval.base)->qualifier |= (yyvsp[(1) - (2)].typeQual);
		}
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1466 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->SetDeclCtxt((yyval.base));
		}
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1475 "rv_gram.y"
    {
		   (yyvsp[(1) - (1)].decl)->extend(gProject->Parse_TOS->parseCtxt->UseDeclCtxt());
		}
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1479 "rv_gram.y"
    {
		   (yyvsp[(1) - (3)].decl)->attrib = (yyvsp[(3) - (3)].gccAttrib);
		   (yyval.decl) = (yyvsp[(1) - (3)].decl);
		}
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1487 "rv_gram.y"
    {
		   (yyvsp[(1) - (3)].decl)->initializer = (yyvsp[(3) - (3)].value);
		   (yyval.decl) = (yyvsp[(1) - (3)].decl);
		}
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1494 "rv_gram.y"
    {
		  (yyval.decl) = (Decl*) NULL;
		}
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1504 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (1)].decl);
		}
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1508 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(1) - (3)].decl);

			Decl*	appendDecl = (yyvsp[(1) - (3)].decl);
			while (appendDecl->next != NULL)
				appendDecl = appendDecl->next;

			appendDecl->next = (yyvsp[(3) - (3)].decl);
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1526 "rv_gram.y"
    {
			(yyval.arrayConst) = new ArrayConstant(NoLocation);
			(yyval.arrayConst)->addElement((yyvsp[(1) - (1)].value));
		}
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1531 "rv_gram.y"
    {
			(yyval.arrayConst) = (yyvsp[(1) - (3)].arrayConst);
			(yyval.arrayConst)->addElement((yyvsp[(3) - (3)].value));
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 1540 "rv_gram.y"
    {
			(yyval.value) = (yyvsp[(2) - (4)].arrayConst);
			delete (yyvsp[(1) - (4)].loc);
			delete (yyvsp[(4) - (4)].loc);
		}
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 1548 "rv_gram.y"
    {
			(yyval.loc) = (Location*) NULL;
		}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 1552 "rv_gram.y"
    {
			delete (yyvsp[(1) - (1)].loc);
			(yyval.loc) = (Location*) NULL;
		}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 1572 "rv_gram.y"
    {
			(yyval.typeQual) = (yyvsp[(1) - (2)].typeQual) | (yyvsp[(2) - (2)].typeQual);
			if (((yyvsp[(2) - (2)].typeQual) & (yyvsp[(1) - (2)].typeQual)) != TQ_None)
				yywarn("qualifier already specified");                               
		}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 1580 "rv_gram.y"
    {
			(yyval.typeQual) = TQ_None;
		}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1614 "rv_gram.y"
    {
			(yyval.base) = new BaseType(BT_UserType);
			(yyval.base)->typeName = (yyvsp[(1) - (1)].symbol);
		}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1621 "rv_gram.y"
    {
			assert ((! (yyval.symbol)->entry) || 
					(yyval.symbol)->entry->IsTagDecl()) ;
		}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1629 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_ref((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
																gProject->Parse_TOS->transUnit->contxt.tags);
			else
				(yyval.base) = NULL;                                         
		}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1639 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_ref((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
																gProject->Parse_TOS->transUnit->contxt.tags);
			else
				(yyval.base) = NULL;                                         
		}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1649 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_ref((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
																gProject->Parse_TOS->transUnit->contxt.tags);
			else
				(yyval.base) = NULL;                                         
		}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1659 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_def((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
															gProject->Parse_TOS->transUnit->contxt.tags);
			else
				(yyval.base) = NULL;                                         
		}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1668 "rv_gram.y"
    { prvhooks->start_tag_def(); }
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1670 "rv_gram.y"
    {
		(yyvsp[(4) - (5)].strDef)->_isUnion = false;  // benny fixed 
			(yyval.base) = new BaseType((yyvsp[(4) - (5)].strDef));
			delete (yyvsp[(3) - (5)].loc);
			delete (yyvsp[(5) - (5)].loc);
			prvhooks->end_tag_def();
		}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1677 "rv_gram.y"
    { prvhooks->start_tag_def(); }
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1679 "rv_gram.y"
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
		}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1704 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_def((yyvsp[(1) - (2)].typeSpec), (yyvsp[(2) - (2)].symbol),
															gProject->Parse_TOS->transUnit->contxt.tags);
			else
			  (yyval.base) = NULL ;
		}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1714 "rv_gram.y"
    { prvhooks->start_tag_def(); }
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1716 "rv_gram.y"
    {
			(yyvsp[(4) - (5)].strDef)->_isUnion = true;  // benny fixed 
			(yyval.base) = new BaseType((yyvsp[(4) - (5)].strDef));

			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(5) - (5)].loc);
			prvhooks->end_tag_def();
		}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1725 "rv_gram.y"
    { prvhooks->start_tag_def(); }
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1727 "rv_gram.y"
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
		}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 1752 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				(yyval.base) = gProject->Parse_TOS->parseCtxt->Mk_tag_def((yyvsp[(1) - (2)].typeSpec),(yyvsp[(2) - (2)].symbol),
															gProject->Parse_TOS->transUnit->contxt.tags);
			else
			  (yyval.base) = NULL;
		}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 1762 "rv_gram.y"
    { prvhooks->start_tag_def(); }
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 1764 "rv_gram.y"
    {
			(yyval.base) = new BaseType((yyvsp[(4) - (5)].enDef));

			delete (yyvsp[(2) - (5)].loc);
			delete (yyvsp[(5) - (5)].loc);
			prvhooks->end_tag_def(); 
		}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 1772 "rv_gram.y"
    { prvhooks->start_tag_def(); }
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 1774 "rv_gram.y"
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
		}
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 1798 "rv_gram.y"
    {  (yyval.strDef) = new StructDef();
		   yywarn("ANSI/ISO C prohibits empty struct/union");
		}
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 1805 "rv_gram.y"
    {  (yyval.enDef) = new EnumDef();
		   yywarn("ANSI/ISO C prohibits empty enum");
		}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 1809 "rv_gram.y"
    {  (yyval.enDef) = (yyvsp[(1) - (2)].enDef);
		}
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 1814 "rv_gram.y"
    {
			(yyval.loc) = NULL;
		}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 1818 "rv_gram.y"
    {
		  yywarn("Trailing comma in enum type definition");
		}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 1831 "rv_gram.y"
    {
			(yyval.enDef) = new EnumDef();
			(yyval.enDef)->addElement((yyvsp[(1) - (1)].enConst));
		}
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 1836 "rv_gram.y"
    {
			(yyval.enDef) = (yyvsp[(1) - (3)].enDef);
			(yyval.enDef)->addElement((yyvsp[(3) - (3)].enConst));
			delete (yyvsp[(2) - (3)].loc);
		}
    break;

  case 287:

/* Line 1464 of yacc.c  */
#line 1844 "rv_gram.y"
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
		}
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 1859 "rv_gram.y"
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
		}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 1882 "rv_gram.y"
    {
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.EnterScope();
			gProject->Parse_TOS->parseCtxt->PushCtxt();
		}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 1887 "rv_gram.y"
    {
			assert (!gProject->Parse_TOS->err_top_level || gProject->Parse_TOS->possibleType);
			 /* Safety precaution! */
			 gProject->Parse_TOS->possibleType=true;
		}
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 1893 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->PopCtxt(false);
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.ExitScope();
			(yyval.strDef) = (yyvsp[(3) - (3)].strDef) ;
		}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 1902 "rv_gram.y"
    {
			(yyval.strDef) = new StructDef();
			(yyval.strDef)->addComponent(ReverseList((yyvsp[(1) - (2)].decl)));
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 1908 "rv_gram.y"
    {
			// A useful gcc extension:
			//   naked semicolons in struct/union definitions. 
			(yyval.strDef) = (yyvsp[(1) - (2)].strDef);
			yywarn ("Empty declaration");
			delete (yyvsp[(2) - (2)].loc);
		}
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 1916 "rv_gram.y"
    {
			(yyval.strDef) = (yyvsp[(1) - (3)].strDef);
			(yyval.strDef)->addComponent(ReverseList((yyvsp[(2) - (3)].decl)));
			delete (yyvsp[(3) - (3)].loc);
		}
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 1924 "rv_gram.y"
    {
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = (yyvsp[(2) - (2)].decl);
		}
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 1929 "rv_gram.y"
    {
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = new Decl ((yyvsp[(1) - (1)].base));
			yywarn ("No field declarator");
		}
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 1943 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetIsFieldId(true); 
		}
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 1946 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(2) - (3)].decl);
			(yyval.decl)->attrib = (yyvsp[(3) - (3)].gccAttrib);
		}
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 1951 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetIsFieldId(true); 
		}
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 1954 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(4) - (5)].decl);
			(yyval.decl)->attrib = (yyvsp[(5) - (5)].gccAttrib);
			(yyval.decl)->next = (yyvsp[(1) - (5)].decl);
			delete (yyvsp[(2) - (5)].loc);
		}
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 1963 "rv_gram.y"
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
				
		}
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 1981 "rv_gram.y"
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
		}
    break;

  case 306:

/* Line 1464 of yacc.c  */
#line 2001 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->SetIsFieldId(false); 
		}
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 2004 "rv_gram.y"
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
		}
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 2024 "rv_gram.y"
    {
		   (yyval.decl) = (Decl*) NULL;
		}
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 2035 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->Mk_declarator ((yyval.decl));
		}
    break;

  case 312:

/* Line 1464 of yacc.c  */
#line 2041 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->Mk_func_declarator ((yyval.decl));
		}
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 2047 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(2) - (2)].decl);
			(yyval.decl)->extend((yyvsp[(1) - (2)].ptr));
		}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 2058 "rv_gram.y"
    {  if (gProject->Parse_TOS->transUnit)
				(yyval.decl) = gProject->Parse_TOS->parseCtxt->Mk_direct_declarator_reentrance ((yyvsp[(1) - (1)].symbol),
				gProject->Parse_TOS->transUnit->contxt.syms);
		}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 2063 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(2) - (3)].decl);
			delete (yyvsp[(1) - (3)].loc) ;
			delete (yyvsp[(3) - (3)].loc) ;
		}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 2070 "rv_gram.y"
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

		}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 2087 "rv_gram.y"
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

		}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 2104 "rv_gram.y"
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
		}
    break;

  case 322:

/* Line 1464 of yacc.c  */
#line 2129 "rv_gram.y"
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
		}
    break;

  case 323:

/* Line 1464 of yacc.c  */
#line 2147 "rv_gram.y"
    {
			(yyval.ptr) = new PtrType((yyvsp[(2) - (2)].typeQual));    
		}
    break;

  case 325:

/* Line 1464 of yacc.c  */
#line 2154 "rv_gram.y"
    {
			(yyval.ptr) = (yyvsp[(2) - (2)].ptr);
			(yyval.ptr)->subType = (yyvsp[(1) - (2)].ptr);
		}
    break;

  case 327:

/* Line 1464 of yacc.c  */
#line 2167 "rv_gram.y"
    {  gProject->Parse_TOS->parseCtxt->IncrVarParam(1);
		  if (gProject->Parse_TOS->transUnit)
			  gProject->Parse_TOS->transUnit->contxt.EnterScope();
		  gProject->Parse_TOS->parseCtxt->PushCtxt();
		}
    break;

  case 328:

/* Line 1464 of yacc.c  */
#line 2173 "rv_gram.y"
    {
		  // Exit, but will allow re-enter for a function.
		  // Hack, to handle parameters being in the function's scope.
		  gProject->Parse_TOS->parseCtxt->PopCtxt(true);
		  gProject->Parse_TOS->parseCtxt->IncrVarParam(-1);
		  (yyval.decl) = (yyvsp[(2) - (2)].decl);
	   }
    break;

  case 329:

/* Line 1464 of yacc.c  */
#line 2183 "rv_gram.y"
    {  if (gProject->Parse_TOS->transUnit)
			   (yyval.decl) = gProject->Parse_TOS->parseCtxt->Mk_direct_declarator_reentrance ((yyvsp[(1) - (1)].symbol),
				gProject->Parse_TOS->transUnit->contxt.syms);
		}
    break;

  case 330:

/* Line 1464 of yacc.c  */
#line 2188 "rv_gram.y"
    {  (yyval.decl) = (yyvsp[(1) - (3)].decl);
		   if (gProject->Parse_TOS->transUnit)
		   {
			  (yyval.decl) = gProject->Parse_TOS->parseCtxt->Mk_direct_declarator_reentrance ((yyvsp[(3) - (3)].symbol),
				gProject->Parse_TOS->transUnit->contxt.syms);
			  (yyval.decl)->next = (yyvsp[(1) - (3)].decl);
		   }
		}
    break;

  case 332:

/* Line 1464 of yacc.c  */
#line 2204 "rv_gram.y"
    {
			/* Convert a TYPEDEF_NAME back into a normal IDENT */
			(yyval.symbol) = (yyvsp[(1) - (1)].symbol);
			(yyval.symbol)->entry = (SymEntry*) NULL;
		}
    break;

  case 335:

/* Line 1464 of yacc.c  */
#line 2225 "rv_gram.y"
    {
		   (yyval.decl) = (Decl*) NULL;
		}
    break;

  case 336:

/* Line 1464 of yacc.c  */
#line 2229 "rv_gram.y"
    { gProject->Parse_TOS->parseCtxt->IncrVarParam(1); 
		}
    break;

  case 337:

/* Line 1464 of yacc.c  */
#line 2232 "rv_gram.y"
    { gProject->Parse_TOS->parseCtxt->IncrVarParam(-1); 
		   (yyval.decl) = (yyvsp[(2) - (2)].decl);
		}
    break;

  case 338:

/* Line 1464 of yacc.c  */
#line 2238 "rv_gram.y"
    {   gProject->Parse_TOS->parseCtxt->IncrVarParam(1);
			if (gProject->Parse_TOS->transUnit)
				gProject->Parse_TOS->transUnit->contxt.EnterScope();
			gProject->Parse_TOS->parseCtxt->PushCtxt();
		}
    break;

  case 339:

/* Line 1464 of yacc.c  */
#line 2244 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->PopCtxt(true);
			gProject->Parse_TOS->parseCtxt->IncrVarParam(-1);
			(yyval.decl) = (yyvsp[(2) - (2)].decl) ;
		}
    break;

  case 341:

/* Line 1464 of yacc.c  */
#line 2253 "rv_gram.y"
    {
			BaseType *bt = new BaseType(BT_Ellipsis);

			(yyval.decl) = new Decl(bt);
			(yyval.decl)->next = (yyvsp[(1) - (3)].decl);
		}
    break;

  case 343:

/* Line 1464 of yacc.c  */
#line 2263 "rv_gram.y"
    {
			(yyval.decl) = (yyvsp[(3) - (3)].decl);
			(yyval.decl)->next = (yyvsp[(1) - (3)].decl);
		}
    break;

  case 344:

/* Line 1464 of yacc.c  */
#line 2270 "rv_gram.y"
    {   
			gProject->Parse_TOS->parseCtxt->PushCtxt();
		}
    break;

  case 345:

/* Line 1464 of yacc.c  */
#line 2274 "rv_gram.y"
    {
			gProject->Parse_TOS->parseCtxt->PopCtxt(true);
			(yyval.decl) = (yyvsp[(2) - (2)].decl);
		}
    break;

  case 346:

/* Line 1464 of yacc.c  */
#line 2281 "rv_gram.y"
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
		}
    break;

  case 347:

/* Line 1464 of yacc.c  */
#line 2303 "rv_gram.y"
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
		}
    break;

  case 348:

/* Line 1464 of yacc.c  */
#line 2326 "rv_gram.y"
    {
			gProject->Parse_TOS->possibleType = true;
			(yyval.decl) = new Decl((yyvsp[(1) - (1)].base));
			if ((yyval.decl)->form &&
				(yyval.decl)->form->isFunction())
				if(yyerr ("Function type not allowed for parameter"))
				  YYERROR;
		}
    break;

  case 349:

/* Line 1464 of yacc.c  */
#line 2340 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(1) - (1)].ptr);
		}
    break;

  case 350:

/* Line 1464 of yacc.c  */
#line 2344 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(1) - (1)].type);
		}
    break;

  case 351:

/* Line 1464 of yacc.c  */
#line 2348 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(2) - (2)].type);
			(yyval.type)->extend((yyvsp[(1) - (2)].ptr));
		}
    break;

  case 353:

/* Line 1464 of yacc.c  */
#line 2358 "rv_gram.y"
    {
			(yyval.type) = (yyvsp[(2) - (3)].type);
		}
    break;

  case 354:

/* Line 1464 of yacc.c  */
#line 2362 "rv_gram.y"
    {
			(yyval.type) = new ArrayType((yyvsp[(2) - (3)].value));
		}
    break;

  case 355:

/* Line 1464 of yacc.c  */
#line 2366 "rv_gram.y"
    {
			ArrayType *at = new ArrayType((yyvsp[(3) - (4)].value));
			(yyval.type) = (yyvsp[(1) - (4)].type);
			(yyval.type)->extend(at);
			Type * extended = (yyval.type)->extend(at) ;
			if (extended && 
				extended->isFunction())
				if(yyerr ("Wrong type combination"))
				  YYERROR;
		}
    break;

  case 356:

/* Line 1464 of yacc.c  */
#line 2377 "rv_gram.y"
    {
			(yyval.type) = new FunctionType(ReverseList((yyvsp[(2) - (3)].decl)));
		}
    break;

  case 357:

/* Line 1464 of yacc.c  */
#line 2381 "rv_gram.y"
    {
			FunctionType * ft = new FunctionType(ReverseList((yyvsp[(3) - (4)].decl)));
			(yyval.type) = (yyvsp[(1) - (4)].type);
			Type * extended = (yyval.type)->extend(ft) ;
			if (extended && 
				! extended->isPointer())
				if(yyerr ("Wrong type combination"))
				  YYERROR;
				
		}
    break;

  case 358:

/* Line 1464 of yacc.c  */
#line 2398 "rv_gram.y"
    {
			(yyval.gccAttrib) = (GccAttrib*) NULL;
		}
    break;

  case 360:

/* Line 1464 of yacc.c  */
#line 2405 "rv_gram.y"
    {
				(yyval.gccAttrib) = (yyvsp[(4) - (6)].gccAttrib);
				delete (yyvsp[(2) - (6)].loc);
				delete (yyvsp[(3) - (6)].loc);
				delete (yyvsp[(5) - (6)].loc);
				delete (yyvsp[(6) - (6)].loc);
			}
    break;

  case 361:

/* Line 1464 of yacc.c  */
#line 2415 "rv_gram.y"
    {
				/* The lexer ate some unsupported option. */
				(yyval.gccAttrib) = new GccAttrib( GCC_Unsupported);
			}
    break;

  case 362:

/* Line 1464 of yacc.c  */
#line 2420 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Packed );
			}
    break;

  case 363:

/* Line 1464 of yacc.c  */
#line 2424 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_CDecl );
			}
    break;

  case 364:

/* Line 1464 of yacc.c  */
#line 2428 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Const );
			}
    break;

  case 365:

/* Line 1464 of yacc.c  */
#line 2432 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_NoReturn );
			}
    break;

  case 366:

/* Line 1464 of yacc.c  */
#line 2436 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Aligned );

				if ((yyvsp[(3) - (4)].consValue)->ctype == CT_Int)
				{
					IntConstant    *iCons = (IntConstant*) (yyvsp[(3) - (4)].consValue);

					(yyval.gccAttrib)->value = iCons->lng;
				}

				delete (yyvsp[(2) - (4)].loc);
				delete (yyvsp[(4) - (4)].loc);
			}
    break;

  case 367:

/* Line 1464 of yacc.c  */
#line 2450 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Mode );

				(yyval.gccAttrib)->mode = (yyvsp[(3) - (4)].symbol);

				delete (yyvsp[(2) - (4)].loc);
				delete (yyvsp[(4) - (4)].loc);
			}
    break;

  case 368:

/* Line 1464 of yacc.c  */
#line 2459 "rv_gram.y"
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
			}
    break;

  case 369:

/* Line 1464 of yacc.c  */
#line 2482 "rv_gram.y"
    {
				(yyval.gccAttrib) = new GccAttrib( GCC_Malloc );
			}
    break;



/* Line 1464 of yacc.c  */
#line 5217 "./generated/rv_gram.cpp"
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
#line 2487 "rv_gram.y"


/*******************************************************/

