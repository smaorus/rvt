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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         yyansi_cparse
#define yylex           yyansi_clex
#define yyerror         yyansi_cerror
#define yylval          yyansi_clval
#define yychar          yyansi_cchar
#define yydebug         yyansi_cdebug
#define yynerrs         yyansi_cnerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parser.y"


/*
 * This parser is based on:
 *
 * c5.y, a ANSI-C grammar written by James A. Roskind.
 * "Portions Copyright (c) 1989, 1990 James A. Roskind".
 * (http://www.idiom.com/free-compilers/,
 * ftp://ftp.infoseek.com/ftp/pub/c++grammar/,
 * ftp://ftp.sra.co.jp/.a/pub/cmd/c++grammar2.0.tar.gz)
 */

#define PARSER ansi_c_parser

#include "ansi_c_parser.h"
#include "concatenate_strings.h"

int yyansi_clex();
extern char *yyansi_ctext;

#include "parser_static.inc"

#include "y.tab.h"

/*** token declaration **************************************************/

/* Line 189 of yacc.c  */
#line 157 "parser.y"

/************************************************************************/
/*** rules **************************************************************/
/************************************************************************/


/* Line 189 of yacc.c  */
#line 115 "y.tab.cpp"

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
     TOK_AUTO = 258,
     TOK_BOOL = 259,
     TOK_COMPLEX = 260,
     TOK_BREAK = 261,
     TOK_CASE = 262,
     TOK_CHAR = 263,
     TOK_CONST = 264,
     TOK_CONTINUE = 265,
     TOK_DEFAULT = 266,
     TOK_DO = 267,
     TOK_DOUBLE = 268,
     TOK_ELSE = 269,
     TOK_ENUM = 270,
     TOK_EXTERN = 271,
     TOK_FLOAT = 272,
     TOK_FOR = 273,
     TOK_GOTO = 274,
     TOK_IF = 275,
     TOK_INLINE = 276,
     TOK_INT = 277,
     TOK_LONG = 278,
     TOK_REGISTER = 279,
     TOK_RETURN = 280,
     TOK_SHORT = 281,
     TOK_SIGNED = 282,
     TOK_SIZEOF = 283,
     TOK_STATIC = 284,
     TOK_STRUCT = 285,
     TOK_SWITCH = 286,
     TOK_TYPEDEF = 287,
     TOK_UNION = 288,
     TOK_UNSIGNED = 289,
     TOK_VOID = 290,
     TOK_VOLATILE = 291,
     TOK_WHILE = 292,
     TOK_ARROW = 293,
     TOK_INCR = 294,
     TOK_DECR = 295,
     TOK_SHIFTLEFT = 296,
     TOK_SHIFTRIGHT = 297,
     TOK_LE = 298,
     TOK_GE = 299,
     TOK_EQ = 300,
     TOK_NE = 301,
     TOK_ANDAND = 302,
     TOK_OROR = 303,
     TOK_ELLIPSIS = 304,
     TOK_MULTASSIGN = 305,
     TOK_DIVASSIGN = 306,
     TOK_MODASSIGN = 307,
     TOK_PLUSASSIGN = 308,
     TOK_MINUSASSIGN = 309,
     TOK_SLASSIGN = 310,
     TOK_SRASSIGN = 311,
     TOK_ANDASSIGN = 312,
     TOK_EORASSIGN = 313,
     TOK_ORASSIGN = 314,
     TOK_IDENTIFIER = 315,
     TOK_TYPEDEFNAME = 316,
     TOK_INTEGER = 317,
     TOK_FLOATING = 318,
     TOK_CHARACTER = 319,
     TOK_STRING = 320,
     TOK_ASM_STRING = 321,
     TOK_INT8 = 322,
     TOK_INT16 = 323,
     TOK_INT32 = 324,
     TOK_INT64 = 325,
     TOK_PTR32 = 326,
     TOK_PTR64 = 327,
     TOK_TYPEOF = 328,
     TOK_GCC_ASM = 329,
     TOK_GCC_ASM_PAREN = 330,
     TOK_GCC_ATTRIBUTE_ALIGNED = 331,
     TOK_GCC_ATTRIBUTE_TRANSPARENT_UNION = 332,
     TOK_GCC_ATTRIBUTE_PACKED = 333,
     TOK_GCC_ATTRIBUTE_VECTOR_SIZE = 334,
     TOK_GCC_ATTRIBUTE_END = 335,
     TOK_GCC_LABEL = 336,
     TOK_MSC_ASM = 337,
     TOK_BUILTIN_VA_ARG = 338,
     TOK_GCC_BUILTIN_TYPES_COMPATIBLE_P = 339,
     TOK_OFFSETOF = 340,
     TOK_ALIGNOF = 341,
     TOK_MSC_TRY = 342,
     TOK_MSC_FINALLY = 343,
     TOK_MSC_EXCEPT = 344,
     TOK_MSC_LEAVE = 345,
     TOK_FORALL = 346,
     TOK_EXISTS = 347,
     TOK_THREAD_LOCAL = 348,
     TOK_ARRAY_OF = 349,
     TOK_CPROVER_BITVECTOR = 350,
     TOK_REAL = 351,
     TOK_IMAG = 352,
     TOK_SCANNER_ERROR = 353,
     TOK_SCANNER_EOF = 354,
     TOK_PARSE_LANGUAGE = 355,
     TOK_PARSE_EXPRESSION = 356,
     TOK_PARSE_TYPE = 357
   };
#endif
/* Tokens.  */
#define TOK_AUTO 258
#define TOK_BOOL 259
#define TOK_COMPLEX 260
#define TOK_BREAK 261
#define TOK_CASE 262
#define TOK_CHAR 263
#define TOK_CONST 264
#define TOK_CONTINUE 265
#define TOK_DEFAULT 266
#define TOK_DO 267
#define TOK_DOUBLE 268
#define TOK_ELSE 269
#define TOK_ENUM 270
#define TOK_EXTERN 271
#define TOK_FLOAT 272
#define TOK_FOR 273
#define TOK_GOTO 274
#define TOK_IF 275
#define TOK_INLINE 276
#define TOK_INT 277
#define TOK_LONG 278
#define TOK_REGISTER 279
#define TOK_RETURN 280
#define TOK_SHORT 281
#define TOK_SIGNED 282
#define TOK_SIZEOF 283
#define TOK_STATIC 284
#define TOK_STRUCT 285
#define TOK_SWITCH 286
#define TOK_TYPEDEF 287
#define TOK_UNION 288
#define TOK_UNSIGNED 289
#define TOK_VOID 290
#define TOK_VOLATILE 291
#define TOK_WHILE 292
#define TOK_ARROW 293
#define TOK_INCR 294
#define TOK_DECR 295
#define TOK_SHIFTLEFT 296
#define TOK_SHIFTRIGHT 297
#define TOK_LE 298
#define TOK_GE 299
#define TOK_EQ 300
#define TOK_NE 301
#define TOK_ANDAND 302
#define TOK_OROR 303
#define TOK_ELLIPSIS 304
#define TOK_MULTASSIGN 305
#define TOK_DIVASSIGN 306
#define TOK_MODASSIGN 307
#define TOK_PLUSASSIGN 308
#define TOK_MINUSASSIGN 309
#define TOK_SLASSIGN 310
#define TOK_SRASSIGN 311
#define TOK_ANDASSIGN 312
#define TOK_EORASSIGN 313
#define TOK_ORASSIGN 314
#define TOK_IDENTIFIER 315
#define TOK_TYPEDEFNAME 316
#define TOK_INTEGER 317
#define TOK_FLOATING 318
#define TOK_CHARACTER 319
#define TOK_STRING 320
#define TOK_ASM_STRING 321
#define TOK_INT8 322
#define TOK_INT16 323
#define TOK_INT32 324
#define TOK_INT64 325
#define TOK_PTR32 326
#define TOK_PTR64 327
#define TOK_TYPEOF 328
#define TOK_GCC_ASM 329
#define TOK_GCC_ASM_PAREN 330
#define TOK_GCC_ATTRIBUTE_ALIGNED 331
#define TOK_GCC_ATTRIBUTE_TRANSPARENT_UNION 332
#define TOK_GCC_ATTRIBUTE_PACKED 333
#define TOK_GCC_ATTRIBUTE_VECTOR_SIZE 334
#define TOK_GCC_ATTRIBUTE_END 335
#define TOK_GCC_LABEL 336
#define TOK_MSC_ASM 337
#define TOK_BUILTIN_VA_ARG 338
#define TOK_GCC_BUILTIN_TYPES_COMPATIBLE_P 339
#define TOK_OFFSETOF 340
#define TOK_ALIGNOF 341
#define TOK_MSC_TRY 342
#define TOK_MSC_FINALLY 343
#define TOK_MSC_EXCEPT 344
#define TOK_MSC_LEAVE 345
#define TOK_FORALL 346
#define TOK_EXISTS 347
#define TOK_THREAD_LOCAL 348
#define TOK_ARRAY_OF 349
#define TOK_CPROVER_BITVECTOR 350
#define TOK_REAL 351
#define TOK_IMAG 352
#define TOK_SCANNER_ERROR 353
#define TOK_SCANNER_EOF 354
#define TOK_PARSE_LANGUAGE 355
#define TOK_PARSE_EXPRESSION 356
#define TOK_PARSE_TYPE 357




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 361 "y.tab.cpp"

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
#define YYFINAL  145
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   3734

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  127
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  167
/* YYNRULES -- Number of rules.  */
#define YYNRULES  462
/* YYNRULES -- Number of states.  */
#define YYNSTATES  816

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   357

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   117,     2,     2,     2,   119,   112,     2,
     103,   104,   113,   114,   105,   115,   106,   118,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   125,   110,
     120,   126,   121,   124,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   107,     2,   108,   122,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   109,   123,   111,   116,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    37,    39,    41,
      45,    47,    49,    51,    53,    55,    62,    69,    76,    78,
      82,    87,    92,    97,   106,   115,   119,   121,   126,   130,
     135,   139,   143,   146,   149,   151,   153,   155,   159,   161,
     164,   167,   170,   173,   176,   179,   182,   185,   188,   191,
     196,   199,   202,   204,   209,   216,   224,   226,   230,   234,
     238,   240,   244,   248,   250,   254,   258,   260,   264,   268,
     272,   276,   278,   282,   286,   288,   292,   294,   298,   300,
     304,   306,   310,   312,   316,   318,   324,   329,   331,   335,
     339,   343,   347,   351,   355,   359,   363,   367,   371,   375,
     377,   381,   383,   384,   386,   389,   392,   395,   398,   399,
     404,   405,   410,   411,   417,   423,   424,   426,   427,   434,
     435,   442,   443,   451,   453,   455,   457,   459,   461,   463,
     465,   467,   469,   472,   474,   477,   480,   482,   485,   488,
     490,   492,   494,   496,   498,   500,   504,   508,   512,   516,
     519,   523,   526,   530,   533,   536,   539,   541,   544,   547,
     551,   555,   559,   563,   567,   571,   574,   578,   582,   587,
     592,   594,   597,   599,   601,   603,   605,   607,   609,   611,
     613,   615,   617,   619,   621,   623,   625,   627,   629,   631,
     633,   635,   637,   639,   641,   643,   648,   650,   652,   654,
     659,   660,   668,   669,   678,   683,   685,   687,   688,   690,
     692,   695,   698,   701,   707,   710,   716,   717,   719,   721,
     724,   727,   730,   732,   736,   740,   744,   748,   752,   753,
     756,   760,   763,   764,   766,   769,   770,   778,   779,   788,
     792,   794,   796,   800,   803,   806,   807,   810,   812,   816,
     818,   822,   824,   826,   830,   832,   835,   838,   841,   843,
     846,   849,   851,   854,   857,   860,   862,   865,   868,   870,
     872,   874,   877,   879,   882,   883,   886,   888,   890,   894,
     899,   901,   905,   907,   908,   912,   916,   919,   923,   929,
     934,   941,   945,   947,   949,   951,   953,   955,   957,   959,
     961,   963,   965,   967,   969,   973,   978,   985,   989,   993,
     998,  1003,  1004,  1006,  1009,  1012,  1018,  1026,  1032,  1034,
    1036,  1042,  1050,  1059,  1063,  1066,  1069,  1072,  1076,  1080,
    1082,  1086,  1093,  1098,  1103,  1106,  1114,  1119,  1121,  1122,
    1124,  1126,  1129,  1133,  1138,  1140,  1143,  1145,  1150,  1158,
    1160,  1164,  1167,  1169,  1174,  1182,  1184,  1188,  1191,  1193,
    1195,  1197,  1201,  1202,  1204,  1206,  1209,  1211,  1213,  1215,
    1217,  1223,  1224,  1228,  1230,  1231,  1233,  1235,  1238,  1241,
    1244,  1248,  1250,  1253,  1256,  1259,  1262,  1264,  1266,  1268,
    1270,  1272,  1275,  1277,  1279,  1282,  1286,  1290,  1295,  1297,
    1302,  1308,  1311,  1315,  1319,  1324,  1329,  1331,  1335,  1337,
    1339,  1341,  1344,  1348,  1351,  1355,  1360,  1362,  1366,  1368,
    1370,  1372,  1374,  1376,  1378,  1381,  1382,  1387,  1388,  1394,
    1396,  1399,  1400,  1405,  1408,  1412,  1416,  1421,  1423,  1426,
    1429,  1433,  1435,  1438,  1441,  1445,  1449,  1453,  1457,  1462,
    1466,  1470,  1472
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     128,     0,    -1,   100,   258,    -1,   101,   161,    -1,   102,
     223,    -1,    60,    -1,    61,    -1,    62,    -1,    63,    -1,
      64,    -1,    65,    -1,   131,    -1,   132,    -1,   133,    -1,
     136,    -1,   134,    -1,   136,   134,    -1,   129,    -1,   135,
      -1,   103,   161,   104,    -1,   143,    -1,   138,    -1,   139,
      -1,   141,    -1,   142,    -1,    83,   103,   160,   105,   223,
     104,    -1,    84,   103,   223,   105,   223,   104,    -1,    85,
     103,   223,   105,   140,   104,    -1,   145,    -1,   140,   106,
     145,    -1,   140,   107,   161,   108,    -1,    86,   103,   147,
     104,    -1,    86,   103,   223,   104,    -1,    91,   234,   109,
     223,   129,   110,   161,   111,    -1,    92,   234,   109,   223,
     129,   110,   161,   111,    -1,   103,   233,   104,    -1,   137,
      -1,   144,   107,   161,   108,    -1,   144,   103,   104,    -1,
     144,   103,   146,   104,    -1,   144,   106,   145,    -1,   144,
      38,   145,    -1,   144,    39,    -1,   144,    40,    -1,   129,
      -1,   130,    -1,   160,    -1,   146,   105,   160,    -1,   144,
      -1,    39,   147,    -1,    40,   147,    -1,   112,   148,    -1,
      47,   222,    -1,   113,   148,    -1,   114,   148,    -1,   115,
     148,    -1,   116,   148,    -1,   117,   148,    -1,    28,   147,
      -1,    28,   103,   223,   104,    -1,    96,   147,    -1,    97,
     147,    -1,   147,    -1,   103,   223,   104,   148,    -1,   103,
     223,   104,   109,   227,   111,    -1,   103,   223,   104,   109,
     226,   105,   111,    -1,   148,    -1,   149,   113,   148,    -1,
     149,   118,   148,    -1,   149,   119,   148,    -1,   149,    -1,
     150,   114,   149,    -1,   150,   115,   149,    -1,   150,    -1,
     151,    41,   150,    -1,   151,    42,   150,    -1,   151,    -1,
     152,   120,   151,    -1,   152,   121,   151,    -1,   152,    43,
     151,    -1,   152,    44,   151,    -1,   152,    -1,   153,    45,
     152,    -1,   153,    46,   152,    -1,   153,    -1,   154,   112,
     153,    -1,   154,    -1,   155,   122,   154,    -1,   155,    -1,
     156,   123,   155,    -1,   156,    -1,   157,    47,   156,    -1,
     157,    -1,   158,    48,   157,    -1,   158,    -1,   158,   124,
     161,   125,   159,    -1,   158,   124,   125,   159,    -1,   159,
      -1,   148,   126,   160,    -1,   148,    50,   160,    -1,   148,
      51,   160,    -1,   148,    52,   160,    -1,   148,    53,   160,
      -1,   148,    54,   160,    -1,   148,    55,   160,    -1,   148,
      56,   160,    -1,   148,    57,   160,    -1,   148,    58,   160,
      -1,   148,    59,   160,    -1,   160,    -1,   161,   105,   160,
      -1,   160,    -1,    -1,   161,    -1,   175,   110,    -1,   176,
     110,    -1,   171,   110,    -1,   165,   110,    -1,    -1,   177,
     278,   166,   224,    -1,    -1,   178,   278,   167,   224,    -1,
      -1,   165,   105,   278,   168,   224,    -1,    75,   246,   103,
     247,   104,    -1,    -1,   169,    -1,    -1,   175,   270,   198,
     170,   172,   224,    -1,    -1,   176,   270,   198,   170,   173,
     224,    -1,    -1,   171,   105,   270,   198,   170,   174,   224,
      -1,   181,    -1,   183,    -1,   185,    -1,   186,    -1,   182,
      -1,   184,    -1,   187,    -1,   189,    -1,   190,    -1,   178,
     190,    -1,   200,    -1,   177,   200,    -1,   177,   179,    -1,
     180,    -1,   178,   180,    -1,   178,   200,    -1,   190,    -1,
     180,    -1,     9,    -1,    36,    -1,    71,    -1,    72,    -1,
     177,   191,   198,    -1,   182,   190,   198,    -1,   181,   179,
     198,    -1,   181,   191,   198,    -1,   191,   198,    -1,   178,
     191,   198,    -1,   182,   180,    -1,   182,   191,   198,    -1,
     177,   192,    -1,   184,   190,    -1,   183,   179,    -1,   192,
      -1,   178,   192,    -1,   184,   180,    -1,   187,   190,   198,
      -1,   177,   130,   198,    -1,   185,   179,   198,    -1,   189,
     190,   198,    -1,   177,   188,   198,    -1,   186,   179,   198,
      -1,   130,   198,    -1,   178,   130,   198,    -1,   187,   180,
     198,    -1,    73,   103,   161,   104,    -1,    73,   103,   223,
     104,    -1,   188,    -1,   178,   188,    -1,    32,    -1,    16,
      -1,    29,    -1,     3,    -1,    24,    -1,    21,    -1,    93,
      -1,    74,    -1,    22,    -1,    67,    -1,    68,    -1,    69,
      -1,    70,    -1,     8,    -1,    26,    -1,    23,    -1,    17,
      -1,    13,    -1,    27,    -1,    34,    -1,    35,    -1,     4,
      -1,     5,    -1,    95,   107,   161,   108,    -1,   194,    -1,
     210,    -1,   193,    -1,    94,   120,   223,   121,    -1,    -1,
     197,   198,   195,   109,   201,   111,   198,    -1,    -1,   197,
     198,   222,   196,   109,   201,   111,   198,    -1,   197,   198,
     222,   198,    -1,    30,    -1,    33,    -1,    -1,   199,    -1,
     200,    -1,   199,   200,    -1,    78,    80,    -1,    77,    80,
      -1,    79,   103,   161,   104,    80,    -1,    76,    80,    -1,
      76,   103,   161,   104,    80,    -1,    -1,   202,    -1,   203,
      -1,   202,   203,    -1,   205,   110,    -1,   204,   110,    -1,
     110,    -1,   198,   178,   207,    -1,   204,   105,   207,    -1,
     198,   176,   206,    -1,   205,   105,   206,    -1,   270,   208,
     198,    -1,    -1,   209,   198,    -1,   278,   208,   198,    -1,
     209,   198,    -1,    -1,   209,    -1,   125,   162,    -1,    -1,
     213,   198,   211,   109,   214,   111,   198,    -1,    -1,   213,
     198,   222,   212,   109,   214,   111,   198,    -1,   213,   198,
     222,    -1,    15,    -1,   215,    -1,   214,   105,   215,    -1,
     214,   105,    -1,   222,   216,    -1,    -1,   126,   162,    -1,
     220,    -1,   220,   105,    49,    -1,   219,    -1,   218,   105,
     219,    -1,   129,    -1,   221,    -1,   220,   105,   221,    -1,
     175,    -1,   175,   283,    -1,   175,   278,    -1,   175,   272,
      -1,   177,    -1,   177,   283,    -1,   177,   278,    -1,   176,
      -1,   176,   283,    -1,   176,   278,    -1,   176,   272,    -1,
     178,    -1,   178,   283,    -1,   178,   278,    -1,   129,    -1,
     130,    -1,   176,    -1,   176,   282,    -1,   178,    -1,   178,
     282,    -1,    -1,   126,   225,    -1,   162,    -1,   228,    -1,
     109,   227,   111,    -1,   109,   226,   105,   111,    -1,   225,
      -1,   226,   105,   225,    -1,   226,    -1,    -1,   229,   126,
     225,    -1,   145,   125,   225,    -1,   106,   145,    -1,   107,
     161,   108,    -1,   107,   161,    49,   161,   108,    -1,   229,
     107,   161,   108,    -1,   229,   107,   161,    49,   161,   108,
      -1,   229,   106,   145,    -1,   232,    -1,   233,    -1,   231,
      -1,   236,    -1,   237,    -1,   239,    -1,   240,    -1,   243,
      -1,   241,    -1,   244,    -1,   245,    -1,   164,    -1,   222,
     125,   230,    -1,     7,   162,   125,   230,    -1,     7,   162,
      49,   162,   125,   230,    -1,    11,   125,   230,    -1,   234,
     109,   111,    -1,   234,   109,   235,   111,    -1,   234,   109,
      66,   111,    -1,    -1,   230,    -1,   235,   230,    -1,   163,
     110,    -1,    20,   103,   161,   104,   230,    -1,    20,   103,
     161,   104,   230,    14,   230,    -1,    31,   103,   161,   104,
     230,    -1,   231,    -1,   236,    -1,    37,   103,   163,   104,
     230,    -1,    12,   230,    37,   103,   161,   104,   110,    -1,
      18,   103,   238,   163,   110,   163,   104,   230,    -1,    19,
     161,   110,    -1,    10,   110,    -1,     6,   110,    -1,    25,
     110,    -1,    25,   161,   110,    -1,    81,   242,   110,    -1,
     222,    -1,   242,   105,   222,    -1,    75,   246,   103,   247,
     104,   110,    -1,    75,   109,    66,   111,    -1,    82,   109,
      66,   111,    -1,    82,    66,    -1,    87,   233,    89,   103,
     161,   104,   233,    -1,    87,   233,    88,   233,    -1,    90,
      -1,    -1,    36,    -1,   248,    -1,   248,   249,    -1,   248,
     249,   252,    -1,   248,   249,   252,   255,    -1,   136,    -1,
     125,   251,    -1,   125,    -1,   136,   103,   161,   104,    -1,
     107,   222,   108,   136,   103,   161,   104,    -1,   250,    -1,
     251,   105,   250,    -1,   125,   254,    -1,   125,    -1,   136,
     103,   161,   104,    -1,   107,   222,   108,   136,   103,   161,
     104,    -1,   253,    -1,   254,   105,   253,    -1,   125,   257,
      -1,   125,    -1,   136,    -1,   256,    -1,   257,   105,   256,
      -1,    -1,   259,    -1,   260,    -1,   259,   260,    -1,   262,
      -1,   164,    -1,   261,    -1,   110,    -1,    75,   103,   136,
     104,   110,    -1,    -1,   269,   263,   264,    -1,   233,    -1,
      -1,   266,    -1,   267,    -1,   266,   267,    -1,   268,   110,
      -1,   176,   270,    -1,   268,   105,   270,    -1,   278,    -1,
     175,   270,    -1,   176,   270,    -1,   177,   278,    -1,   178,
     278,    -1,   278,    -1,   271,    -1,   275,    -1,   272,    -1,
     130,    -1,   130,   284,    -1,   273,    -1,   274,    -1,   113,
     272,    -1,   113,   178,   272,    -1,   103,   273,   104,    -1,
     103,   273,   104,   284,    -1,   276,    -1,   113,   103,   277,
     104,    -1,   113,   178,   103,   277,   104,    -1,   113,   275,
      -1,   113,   178,   275,    -1,   103,   275,   104,    -1,   103,
     277,   284,   104,    -1,   103,   275,   104,   284,    -1,   130,
      -1,   103,   277,   104,    -1,   279,    -1,   281,    -1,   280,
      -1,   113,   278,    -1,   113,   178,   278,    -1,   281,   284,
      -1,   103,   279,   104,    -1,   103,   279,   104,   284,    -1,
     129,    -1,   103,   281,   104,    -1,   290,    -1,   292,    -1,
     284,    -1,   291,    -1,   293,    -1,   289,    -1,   103,   104,
      -1,    -1,   103,   285,   217,   104,    -1,    -1,   103,   286,
     218,   104,   265,    -1,   289,    -1,   103,   104,    -1,    -1,
     103,   288,   217,   104,    -1,   107,   108,    -1,   107,   113,
     108,    -1,   107,   162,   108,    -1,   289,   107,   162,   108,
      -1,   113,    -1,   113,   178,    -1,   113,   282,    -1,   113,
     178,   282,    -1,   113,    -1,   113,   178,    -1,   113,   283,
      -1,   113,   178,   283,    -1,   103,   290,   104,    -1,   103,
     292,   104,    -1,   103,   284,   104,    -1,   103,   290,   104,
     284,    -1,   103,   291,   104,    -1,   103,   293,   104,    -1,
     287,    -1,   103,   291,   104,   287,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   167,   167,   168,   174,   187,   191,   195,   199,   203,
     207,   215,   216,   217,   218,   222,   223,   233,   234,   235,
     237,   238,   239,   240,   241,   245,   252,   265,   275,   283,
     290,   299,   304,   313,   326,   338,   347,   348,   350,   359,
     370,   376,   382,   390,   401,   402,   406,   411,   419,   420,
     426,   432,   437,   445,   450,   455,   460,   465,   470,   475,
     480,   485,   493,   494,   504,   514,   528,   529,   531,   533,
     538,   539,   541,   546,   547,   549,   554,   555,   557,   559,
     561,   566,   567,   569,   574,   575,   580,   581,   586,   587,
     592,   593,   598,   599,   604,   605,   612,   622,   623,   625,
     627,   629,   631,   633,   635,   637,   639,   641,   643,   648,
     649,   654,   659,   660,   666,   674,   682,   683,   688,   687,
     700,   699,   712,   711,   726,   731,   733,   740,   737,   756,
     753,   772,   769,   787,   788,   789,   790,   794,   795,   796,
     797,   801,   802,   807,   808,   813,   821,   822,   829,   837,
     838,   842,   843,   844,   845,   849,   854,   859,   864,   872,
     876,   881,   886,   895,   900,   905,   914,   915,   920,   928,
     934,   940,   949,   955,   961,   970,   975,   981,   990,   995,
    1003,  1004,  1045,  1046,  1047,  1048,  1049,  1050,  1051,  1052,
    1056,  1057,  1058,  1059,  1060,  1061,  1062,  1063,  1064,  1065,
    1066,  1067,  1068,  1069,  1070,  1071,  1080,  1081,  1082,  1086,
    1093,  1091,  1121,  1118,  1149,  1162,  1164,  1170,  1173,  1177,
    1178,  1185,  1187,  1189,  1191,  1193,  1199,  1202,  1206,  1207,
    1219,  1220,  1221,  1228,  1238,  1249,  1262,  1275,  1283,  1286,
    1294,  1299,  1308,  1311,  1315,  1327,  1325,  1350,  1347,  1366,
    1375,  1383,  1388,  1393,  1400,  1412,  1416,  1423,  1424,  1433,
    1438,  1445,  1454,  1459,  1467,  1473,  1478,  1483,  1490,  1496,
    1501,  1506,  1512,  1517,  1523,  1530,  1536,  1541,  1549,  1550,
    1554,  1555,  1560,  1561,  1570,  1574,  1584,  1585,  1586,  1592,
    1601,  1609,  1617,  1619,  1628,  1635,  1650,  1657,  1664,  1672,
    1679,  1687,  1699,  1700,  1701,  1702,  1703,  1704,  1705,  1706,
    1707,  1708,  1709,  1713,  1722,  1729,  1737,  1747,  1761,  1768,
    1775,  1787,  1794,  1799,  1806,  1821,  1829,  1838,  1849,  1850,
    1854,  1862,  1870,  1884,  1900,  1902,  1904,  1906,  1911,  1920,
    1925,  1933,  1939,  1949,  1955,  1964,  1973,  1981,  1988,  1990,
    2001,  2006,  2011,  2016,  2023,  2027,  2028,  2032,  2033,  2038,
    2039,  2043,  2044,  2048,  2049,  2054,  2055,  2058,  2059,  2063,
    2067,  2068,  2077,  2079,  2083,  2084,  2088,  2089,  2090,  2091,
    2095,  2100,  2099,  2119,  2124,  2127,  2131,  2135,  2144,  2161,
    2169,  2181,  2188,  2194,  2200,  2206,  2215,  2216,  2220,  2221,
    2225,  2226,  2231,  2235,  2236,  2241,  2250,  2252,  2262,  2263,
    2268,  2275,  2280,  2289,  2291,  2296,  2306,  2307,  2312,  2313,
    2317,  2318,  2323,  2336,  2342,  2344,  2354,  2355,  2360,  2361,
    2362,  2366,  2367,  2371,  2372,  2380,  2379,  2396,  2395,  2415,
    2416,  2424,  2423,  2441,  2447,  2453,  2460,  2472,  2478,  2487,
    2492,  2503,  2509,  2518,  2523,  2534,  2536,  2538,  2540,  2550,
    2552,  2554,  2555
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"auto\"", "\"bool\"", "\"complex\"",
  "\"break\"", "\"case\"", "\"char\"", "\"const\"", "\"continue\"",
  "\"default\"", "\"do\"", "\"double\"", "\"else\"", "\"enum\"",
  "\"extern\"", "\"float\"", "\"for\"", "\"goto\"", "\"if\"", "\"inline\"",
  "\"int\"", "\"long\"", "\"register\"", "\"return\"", "\"short\"",
  "\"signed\"", "\"sizeof\"", "\"static\"", "\"struct\"", "\"switch\"",
  "\"typedef\"", "\"union\"", "\"unsigned\"", "\"void\"", "\"volatile\"",
  "\"while\"", "\"->\"", "\"++\"", "\"--\"", "\"<<\"", "\">>\"", "\"<=\"",
  "\">=\"", "\"==\"", "\"!=\"", "\"&&\"", "\"||\"", "\"...\"", "\"*=\"",
  "\"/=\"", "\"%=\"", "\"+=\"", "\"-=\"", "\"<<=\"", "\">>=\"", "\"&=\"",
  "\"^=\"", "\"|=\"", "TOK_IDENTIFIER", "TOK_TYPEDEFNAME", "TOK_INTEGER",
  "TOK_FLOATING", "TOK_CHARACTER", "TOK_STRING", "TOK_ASM_STRING",
  "\"__int8\"", "\"__int16\"", "\"__int32\"", "\"__int64\"", "\"__ptr32\"",
  "\"__ptr64\"", "\"typeof\"", "\"__asm__\"",
  "\"__asm__ (with parentheses)\"", "\"aligned\"", "\"transparent_union\"",
  "\"packed\"", "\"vector_size\"", "\")\"", "\"__label__\"", "\"__asm\"",
  "\"__builtin_va_arg\"", "\"__builtin_types_compatible_p\"",
  "\"__offsetof\"", "\"__alignof__\"", "\"try\"", "\"finally\"",
  "\"except\"", "\"leave\"", "\"forall\"", "\"exists\"",
  "\"thread_local\"", "\"array_of\"", "\"__CPROVER_bitvector\"",
  "\"__real__\"", "\"__imag__\"", "TOK_SCANNER_ERROR", "TOK_SCANNER_EOF",
  "TOK_PARSE_LANGUAGE", "TOK_PARSE_EXPRESSION", "TOK_PARSE_TYPE", "'('",
  "')'", "','", "'.'", "'['", "']'", "'{'", "';'", "'}'", "'&'", "'*'",
  "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'", "'^'", "'|'",
  "'?'", "':'", "'='", "$accept", "grammar", "identifier", "typedef_name",
  "integer", "floating", "character", "string", "constant",
  "string_literal_list", "primary_expression", "gcc_builtin_expressions",
  "offsetof", "offsetof_member_designator", "alignof",
  "quantifier_expression", "statement_expression", "postfix_expression",
  "member_name", "argument_expression_list", "unary_expression",
  "cast_expression", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "and_expression", "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "comma_expression",
  "constant_expression", "comma_expression_opt", "declaration",
  "default_declaring_list", "@1", "@2", "@3", "post_declarator_attributes",
  "post_declarator_attributes_opt", "declaring_list", "@4", "@5", "@6",
  "declaration_specifier", "type_specifier", "declaration_qualifier_list",
  "type_qualifier_list", "declaration_qualifier", "type_qualifier",
  "basic_declaration_specifier", "basic_type_specifier",
  "sue_declaration_specifier", "sue_type_specifier",
  "typedef_declaration_specifier", "typeof_declaration_specifier",
  "typedef_type_specifier", "typeof_specifier", "typeof_type_specifier",
  "storage_class", "basic_type_name", "elaborated_type_name",
  "array_of_construct", "aggregate_name", "@7", "@8", "aggregate_key",
  "gcc_type_attribute_opt", "gcc_type_attribute_list",
  "gcc_type_attribute", "member_declaration_list_opt",
  "member_declaration_list", "member_declaration",
  "member_default_declaring_list", "member_declaring_list",
  "member_declarator", "member_identifier_declarator",
  "bit_field_size_opt", "bit_field_size", "enum_name", "@9", "@10",
  "enum_key", "enumerator_list", "enumerator_declaration",
  "enumerator_value_opt", "parameter_type_list", "KnR_parameter_list",
  "KnR_parameter", "parameter_list", "parameter_declaration",
  "identifier_or_typedef_name", "type_name", "initializer_opt",
  "initializer", "initializer_list", "initializer_list_opt",
  "designated_initializer", "designated_initializer_designator",
  "statement", "declaration_statement", "labeled_statement",
  "compound_statement", "compound_scope", "statement_list",
  "expression_statement", "selection_statement",
  "declaration_or_expression_statement", "iteration_statement",
  "jump_statement", "gcc_local_label_statement", "label_list",
  "gcc_asm_statement", "msc_asm_statement", "msc_seh_statement",
  "volatile_opt", "gcc_asm_commands", "gcc_asm_assembler_template",
  "gcc_asm_outputs", "gcc_asm_output", "gcc_asm_output_list",
  "gcc_asm_inputs", "gcc_asm_input", "gcc_asm_input_list",
  "gcc_asm_clobbered_registers", "gcc_asm_clobbered_register",
  "gcc_asm_clobbered_registers_list", "translation_unit",
  "external_definition_list", "external_definition", "asm_definition",
  "function_definition", "$@11", "function_body",
  "KnR_parameter_header_opt", "KnR_parameter_header",
  "KnR_parameter_declaration", "KnR_parameter_declaring_list",
  "function_head", "declarator", "typedef_declarator",
  "parameter_typedef_declarator", "clean_typedef_declarator",
  "clean_postfix_typedef_declarator", "paren_typedef_declarator",
  "paren_postfix_typedef_declarator", "simple_paren_typedef_declarator",
  "identifier_declarator", "unary_identifier_declarator",
  "postfix_identifier_declarator", "paren_identifier_declarator",
  "abstract_declarator", "parameter_abstract_declarator",
  "postfixing_abstract_declarator", "$@12", "$@13",
  "parameter_postfixing_abstract_declarator", "$@14",
  "array_abstract_declarator", "unary_abstract_declarator",
  "parameter_unary_abstract_declarator", "postfix_abstract_declarator",
  "parameter_postfix_abstract_declarator", 0
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
     355,   356,   357,    40,    41,    44,    46,    91,    93,   123,
      59,   125,    38,    42,    43,    45,   126,    33,    47,    37,
      60,    62,    94,   124,    63,    58,    61
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   127,   128,   128,   128,   129,   130,   131,   132,   133,
     134,   135,   135,   135,   135,   136,   136,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   138,   139,   140,   140,
     140,   141,   141,   142,   142,   143,   144,   144,   144,   144,
     144,   144,   144,   144,   145,   145,   146,   146,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   148,   148,   148,   148,   149,   149,   149,   149,
     150,   150,   150,   151,   151,   151,   152,   152,   152,   152,
     152,   153,   153,   153,   154,   154,   155,   155,   156,   156,
     157,   157,   158,   158,   159,   159,   159,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   160,   160,   161,
     161,   162,   163,   163,   164,   164,   164,   164,   166,   165,
     167,   165,   168,   165,   169,   170,   170,   172,   171,   173,
     171,   174,   171,   175,   175,   175,   175,   176,   176,   176,
     176,   177,   177,   177,   177,   177,   178,   178,   178,   179,
     179,   180,   180,   180,   180,   181,   181,   181,   181,   182,
     182,   182,   182,   183,   183,   183,   184,   184,   184,   185,
     185,   185,   186,   186,   186,   187,   187,   187,   188,   188,
     189,   189,   190,   190,   190,   190,   190,   190,   190,   190,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   191,   191,   191,   192,   192,   192,   193,
     195,   194,   196,   194,   194,   197,   197,   198,   198,   199,
     199,   200,   200,   200,   200,   200,   201,   201,   202,   202,
     203,   203,   203,   204,   204,   205,   205,   206,   206,   206,
     207,   207,   208,   208,   209,   211,   210,   212,   210,   210,
     213,   214,   214,   214,   215,   216,   216,   217,   217,   218,
     218,   219,   220,   220,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   222,   222,
     223,   223,   223,   223,   224,   224,   225,   225,   225,   225,
     226,   226,   227,   227,   228,   228,   229,   229,   229,   229,
     229,   229,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   231,   232,   232,   232,   232,   233,   233,
     233,   234,   235,   235,   236,   237,   237,   237,   238,   238,
     239,   239,   239,   240,   240,   240,   240,   240,   241,   242,
     242,   243,   243,   244,   244,   245,   245,   245,   246,   246,
     247,   247,   247,   247,   248,   249,   249,   250,   250,   251,
     251,   252,   252,   253,   253,   254,   254,   255,   255,   256,
     257,   257,   258,   258,   259,   259,   260,   260,   260,   260,
     261,   263,   262,   264,   265,   265,   266,   266,   267,   268,
     268,   269,   269,   269,   269,   269,   270,   270,   271,   271,
     272,   272,   272,   273,   273,   273,   274,   274,   275,   275,
     275,   275,   275,   276,   276,   276,   277,   277,   278,   278,
     279,   279,   279,   280,   280,   280,   281,   281,   282,   282,
     282,   283,   283,   284,   284,   285,   284,   286,   284,   287,
     287,   288,   287,   289,   289,   289,   289,   290,   290,   290,
     290,   291,   291,   291,   291,   292,   292,   292,   292,   293,
     293,   293,   293
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     3,
       1,     1,     1,     1,     1,     6,     6,     6,     1,     3,
       4,     4,     4,     8,     8,     3,     1,     4,     3,     4,
       3,     3,     2,     2,     1,     1,     1,     3,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       2,     2,     1,     4,     6,     7,     1,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     5,     4,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     1,     0,     1,     2,     2,     2,     2,     0,     4,
       0,     4,     0,     5,     5,     0,     1,     0,     6,     0,
       6,     0,     7,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     2,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     2,
       3,     2,     3,     2,     2,     2,     1,     2,     2,     3,
       3,     3,     3,     3,     3,     2,     3,     3,     4,     4,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     1,     1,     4,
       0,     7,     0,     8,     4,     1,     1,     0,     1,     1,
       2,     2,     2,     5,     2,     5,     0,     1,     1,     2,
       2,     2,     1,     3,     3,     3,     3,     3,     0,     2,
       3,     2,     0,     1,     2,     0,     7,     0,     8,     3,
       1,     1,     3,     2,     2,     0,     2,     1,     3,     1,
       3,     1,     1,     3,     1,     2,     2,     2,     1,     2,
       2,     1,     2,     2,     2,     1,     2,     2,     1,     1,
       1,     2,     1,     2,     0,     2,     1,     1,     3,     4,
       1,     3,     1,     0,     3,     3,     2,     3,     5,     4,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     4,     6,     3,     3,     4,
       4,     0,     1,     2,     2,     5,     7,     5,     1,     1,
       5,     7,     8,     3,     2,     2,     2,     3,     3,     1,
       3,     6,     4,     4,     2,     7,     4,     1,     0,     1,
       1,     2,     3,     4,     1,     2,     1,     4,     7,     1,
       3,     2,     1,     4,     7,     1,     3,     2,     1,     1,
       1,     3,     0,     1,     1,     2,     1,     1,     1,     1,
       5,     0,     3,     1,     0,     1,     1,     2,     2,     2,
       3,     1,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     2,     1,     1,     2,     3,     3,     4,     1,     4,
       5,     2,     3,     3,     4,     4,     1,     3,     1,     1,
       1,     2,     3,     2,     3,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     2,     0,     4,     0,     5,     1,
       2,     0,     4,     2,     3,     3,     4,     1,     2,     2,
       3,     1,     2,     2,     3,     3,     3,     3,     4,     3,
       3,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   372,     0,     0,     0,   185,   203,   204,   195,   151,
     199,   250,   183,   198,   187,   190,   197,   186,   196,   200,
     184,   215,   182,   216,   201,   202,   152,     5,     6,   191,
     192,   193,   194,   153,   154,     0,   189,     0,     0,     0,
       0,     0,   188,     0,     0,     0,   379,     0,   426,   217,
     377,     0,     0,     0,     0,     0,     0,   146,   133,   137,
     134,   138,   135,   136,   139,   180,   140,   141,   217,   166,
     208,   206,   217,   143,   207,   217,     2,   373,   374,   378,
     376,   381,   391,   418,   420,   419,     0,     0,     0,     0,
       7,     8,     9,    10,     0,     0,     0,     0,   321,   321,
       0,     0,   321,     0,     0,     0,     0,     0,     0,    17,
      11,    12,    13,    15,    18,    14,    36,    21,    22,    23,
      24,    20,    48,    62,    66,    70,    73,    76,    81,    84,
      86,    88,    90,    92,    94,    97,   109,     3,   280,   282,
     137,   138,   139,   140,     4,     1,     0,     0,   224,     0,
     222,   221,     0,     0,     0,     0,     0,     0,   421,   175,
     218,   219,     0,   117,     0,   116,     0,   114,     0,   400,
     217,   397,   399,   402,   403,   398,   408,   396,   115,   217,
     217,   145,   150,   217,   149,   217,   163,   144,   118,   217,
     147,   181,   142,   217,   167,   148,   120,   217,   217,   161,
     217,   217,   165,   168,   164,   217,   217,   217,   217,   217,
     159,   210,   245,   375,   321,   435,     0,   423,   433,   321,
      58,   321,    49,    50,   278,   279,    52,     0,     0,     0,
       0,     0,     0,    60,    61,     0,     0,     0,     0,    51,
      53,    54,    55,    56,    57,    16,     0,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   435,   447,   281,   430,   428,   429,   283,
       0,     0,     0,     0,     0,     0,     0,   424,   427,   422,
     220,   122,   217,     0,   416,     0,     0,     0,     0,     0,
     404,   411,   401,   125,   125,   170,   173,   155,   284,   176,
     160,   284,   157,   158,   156,   162,   171,   174,   177,   169,
     172,     0,   217,     0,   249,   383,   382,   434,     0,     0,
     443,     0,   111,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,    35,   112,    44,    45,    41,
      38,     0,    46,    40,     0,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,    98,    67,    68,    69,    66,
      71,    72,    74,    75,    79,    80,    77,    78,    82,    83,
      85,    87,    89,    91,    93,     0,     0,   110,     0,     0,
       0,   448,   449,   178,   179,     0,     0,     0,   209,   205,
     425,   284,   125,     0,   406,   413,     0,     0,     0,   405,
     412,   348,   126,   127,   129,     0,   119,   121,   217,     0,
     214,     0,     0,   264,   271,   268,   275,     0,   257,   262,
     261,     0,   259,   444,   445,     0,    59,     0,     0,     0,
      31,    32,     0,     0,   293,    63,     0,     0,     0,     0,
     112,     0,     0,     0,     0,     0,     0,     0,   348,     0,
       0,   321,   347,   318,    17,   217,   113,     0,   313,     0,
       0,     0,     0,     0,   322,   304,   302,   303,   112,   305,
     306,   307,   308,   310,   309,   311,   312,    39,     0,    37,
      96,     0,   457,   455,   456,   450,   380,   225,   223,   123,
     131,   417,   407,   415,   414,   409,     0,   349,     0,   284,
     284,     0,     0,   293,    17,     0,   286,   285,   287,     0,
     232,     0,     0,   217,   228,     0,     0,   217,     0,   251,
     255,     0,   441,   451,   267,   266,   265,   461,   439,   431,
     432,   274,   273,   272,   441,   451,   270,   269,   277,   276,
     436,     0,   384,     0,   446,     0,     0,     0,    28,     0,
       0,   290,   292,     0,   335,     0,   334,   112,     0,   112,
       0,     0,   336,     0,     0,   112,   320,     0,     0,   339,
       0,   344,     0,     0,   324,   217,   217,   118,   120,   112,
     319,   323,    47,    95,   458,   284,   410,     0,   128,   130,
     296,     0,   292,     0,     0,     0,     0,     0,   238,     0,
     217,   229,     0,   231,   238,   230,     0,   253,   217,     0,
     254,     0,   440,     0,     0,     0,   452,   453,   452,   258,
     263,     0,     0,   438,   385,   386,     0,   260,    25,    26,
      27,     0,     0,     0,     0,     0,    64,     0,   112,   317,
       0,   328,   329,   112,   333,     0,   337,     0,     0,     0,
       0,     0,   338,     0,   321,     0,   314,   132,   354,     0,
     350,     0,   297,     0,   288,   295,   301,     0,   294,     0,
     235,   217,   242,   233,   217,   242,   211,   234,   236,   217,
     252,   246,   256,   217,     0,   459,   460,   454,   389,   387,
       0,   388,    29,     0,     0,     0,    65,   291,     0,   315,
       0,     0,   112,   112,   112,   342,     0,   340,   343,   346,
       0,   124,   356,   351,     0,   289,     0,   299,   244,   239,
     217,   243,   241,   217,   213,   248,   442,   441,   462,   390,
      30,    33,    34,   112,     0,   112,   325,   327,   330,     0,
       0,     0,     0,   359,   355,   362,   352,   298,     0,   237,
     240,   316,     0,     0,   112,   341,   321,     0,     0,     0,
       0,     0,   365,   361,   368,   353,   300,   331,   112,   326,
     345,     0,     0,   360,     0,     0,     0,   369,   370,   367,
     332,     0,   357,     0,     0,   366,     0,     0,     0,   363,
     371,     0,     0,   358,     0,   364
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,   109,    49,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   567,   119,   120,   121,   122,   525,   361,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   476,   526,   477,   478,    51,   318,
     321,   411,   422,   423,    52,   519,   520,   605,   479,   480,
     481,   482,   181,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,   331,   429,
      72,   531,   160,   161,   532,   533,   534,   535,   536,   690,
     693,   740,   691,    74,   333,   432,    75,   538,   539,   630,
     437,   441,   442,   438,   439,   483,   144,   426,   571,   572,
     573,   528,   529,   484,   485,   486,   487,   238,   488,   489,
     490,   663,   491,   492,   493,   590,   494,   495,   496,   518,
     679,   680,   733,   763,   764,   766,   782,   783,   785,   798,
     799,    76,    77,    78,    79,    80,   214,   336,   643,   644,
     645,   646,    81,   692,   171,   172,   173,   174,   175,   176,
     307,   177,    83,    84,    85,   285,   637,   286,   338,   339,
     547,   633,   218,   287,   549,   288,   550
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -585
static const yytype_int16 yypact[] =
{
     458,  2309,  3516,  3006,    64,  -585,  -585,  -585,  -585,  -585,
    -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,
    -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,
    -585,  -585,  -585,  -585,  -585,   -73,  -585,    10,   -52,    58,
      66,   125,  -585,    41,    98,   235,  -585,    63,  -585,   419,
    -585,   222,   232,   231,   247,  2505,  2505,  -585,  2856,  2856,
    3034,  3034,  3034,  3034,  3034,  -585,   227,  -585,   419,  -585,
    -585,  -585,   419,  -585,  -585,   419,  -585,  2309,  -585,  -585,
    -585,  -585,  -585,  -585,  -585,    13,  3575,  3617,  3617,   335,
    -585,  -585,  -585,  -585,   132,   141,   150,   158,  -585,  -585,
    3617,  3617,  2080,  3516,  3516,  3516,  3516,  3516,  3516,  -585,
    -585,  -585,  -585,  -585,  -585,   233,  -585,  -585,  -585,  -585,
    -585,  -585,   119,  -585,   990,   186,   328,   440,    -6,   468,
     194,   180,   203,   266,   -46,  -585,  -585,   212,   -44,  2597,
    3076,    46,    46,  -585,  -585,  -585,  2080,   233,  -585,  3516,
    -585,  -585,  3516,  3006,  3516,   251,   372,  1263,  -585,  -585,
     419,  -585,   235,  -585,    88,  -585,   261,  -585,   696,    13,
     608,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,   661,
     419,  -585,  -585,   419,  -585,   419,  -585,  -585,   242,   419,
    -585,  -585,  -585,   419,  -585,  -585,   258,   419,   419,  -585,
     419,   419,  -585,  -585,  -585,   419,   419,   419,   419,   419,
    -585,   335,   335,  -585,  -585,   -17,  3272,  -585,   277,  2080,
    -585,  3516,  -585,  -585,  -585,  -585,  -585,  3516,  3006,  3006,
    2194,   264,   306,  -585,  -585,   441,   320,   324,   321,  -585,
    -585,  -585,  -585,  -585,  -585,  -585,   335,  -585,  -585,  3314,
     335,  3516,  3516,  3516,  3516,  3516,  3516,  3516,  3516,  3516,
    3516,  3516,  3516,  3516,  3516,  3516,  3516,  3516,  3516,  3516,
    3516,  3516,  3516,  3516,  3516,  3516,  3516,  3516,  3516,  3516,
    3516,  1468,  3516,   190,   316,  -585,  -585,  -585,  -585,  -585,
     506,   330,   102,   520,   526,   315,   228,    13,  -585,  -585,
    -585,  -585,   419,   261,  -585,   346,   355,    13,   261,  1137,
    -585,  -585,  -585,   402,   402,  -585,  -585,  -585,   362,  -585,
    -585,   362,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,
    -585,   384,   769,   412,   414,  -585,  -585,  -585,  2773,   473,
    -585,  3373,  -585,   417,  3516,   436,   447,   449,   472,   466,
     476,  3006,  3006,  -585,  3415,  -585,  1621,  -585,  -585,  -585,
    -585,   528,  -585,  -585,   309,  -585,  -585,  -585,  -585,  -585,
    -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,
     186,   186,   328,   328,   440,   440,   440,   440,    -6,    -6,
     468,   194,   180,   203,   266,  3516,    68,  -585,   482,   489,
     492,   334,  -585,  -585,  -585,   505,   519,   547,  -585,  -585,
    -585,   362,   402,   465,    13,    13,   549,   491,   261,  -585,
    -585,   621,  -585,  -585,  -585,  3211,  -585,  -585,   685,   556,
    -585,   335,   580,   423,   423,  2412,  2412,   595,   599,  -585,
    -585,   536,  -585,  -585,  -585,   598,  -585,  3006,  3006,   335,
    -585,  -585,   473,   473,  3211,  -585,   614,  3516,   619,   583,
    1851,   638,  3516,   652,  3474,   657,   666,   663,     3,   335,
       2,  -585,  -585,  -585,   647,   488,   212,   667,  -585,   231,
     247,  2505,  2505,   660,  -585,  -585,  -585,  -585,  1736,  -585,
    -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  3516,  -585,
    -585,  3516,  -585,    13,  -585,  -585,  -585,  -585,  -585,  -585,
    -585,  -585,  -585,  -585,  -585,  -585,   514,  -585,   679,   362,
     362,   335,  3516,  3211,   678,   681,  -585,  -585,  -585,   209,
    -585,  3006,   700,   762,  -585,   297,   298,   685,   -82,  -585,
     687,   335,   431,   211,  -585,  -585,  -585,  -585,   277,  -585,
    -585,  -585,  -585,  -585,   444,   513,  -585,  -585,  -585,  -585,
    -585,  2690,  3006,   473,  -585,   688,   711,   399,  -585,   697,
     706,  -585,   716,   714,  -585,   -29,  -585,  1851,   780,  1966,
     299,  3516,  -585,   339,  3516,  3516,  -585,   756,   720,  -585,
     347,  -585,   761,   557,  -585,   419,   419,  -585,  -585,  1851,
    -585,  -585,  -585,  -585,  -585,   362,  -585,   233,  -585,  -585,
    -585,   -25,   723,   718,  3211,   335,  3516,  3211,   120,  1410,
     419,  -585,    91,  -585,   120,  -585,   721,   335,   419,  3516,
    -585,    67,  -585,  2773,   727,   732,   851,  -585,  1225,  -585,
    -585,    88,  2930,  -585,  3006,  -585,   353,  -585,  -585,  -585,
    -585,   335,  3516,  3516,  3516,  3089,  -585,  3516,  1851,  -585,
     746,  -585,  -585,  3516,  -585,   555,  -585,   576,   747,   739,
     233,   335,  -585,   745,  -585,   754,  -585,  -585,   233,   755,
     741,  3516,  -585,  3150,  -585,  -585,  -585,   172,  -585,  3516,
    -585,   419,   742,  -585,   419,   742,  -585,  -585,  -585,   419,
    -585,  -585,  -585,   419,   760,    61,  -585,  -585,  -585,  -585,
      88,  -585,  -585,   356,   107,   147,  -585,  -585,   743,  -585,
    3516,   759,  1851,  1851,  1851,  -585,   766,  -585,  -585,  -585,
    3516,  -585,   -12,   749,   434,  -585,  3516,  -585,  -585,  -585,
     419,  -585,  -585,   419,  -585,  -585,  -585,   767,  -585,  -585,
    -585,  -585,  -585,  1851,   592,  3516,   861,  -585,  -585,   771,
     606,   335,    24,  -585,   772,    -4,   757,  -585,   445,  -585,
    -585,  -585,   778,   775,  1851,  -585,  -585,   781,  3516,   -12,
     335,    33,  -585,   788,   233,  -585,  -585,  -585,  1851,  -585,
    -585,   233,   615,  -585,   786,  3516,    -4,   233,  -585,   791,
    -585,    76,  -585,   233,   618,  -585,   233,  3516,   175,  -585,
    -585,   643,  3516,  -585,   645,  -585
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -585,  -585,    20,   534,  -585,  -585,  -585,  -107,  -585,   -70,
    -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -235,  -585,
     -30,  1122,   499,   522,   332,   523,   622,   620,   626,   628,
     629,  -585,  -391,   835,    -2,  -211,  -584,    65,  -585,  -585,
    -585,  -585,  -585,  -308,  -585,  -585,  -585,  -585,    15,   605,
      31,   712,   303,   973,  -585,    81,  -585,   625,  -585,  -585,
     633,    50,   673,   -14,    35,    74,  -585,  -585,  -585,  -585,
    -585,   192,  -585,    30,   363,  -585,   366,  -585,  -585,   281,
     286,   215,  -500,  -585,  -585,  -585,  -585,   373,   288,  -585,
     280,  -585,   354,  -585,   357,   -49,   -21,  -309,  -418,   393,
     396,  -585,  -585,  -434,   341,  -585,   -93,   703,  -585,   342,
    -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,  -585,   456,
     255,  -585,  -585,   154,  -585,  -585,   130,  -585,  -585,   128,
    -585,  -585,  -585,   859,  -585,  -585,  -585,  -585,  -585,  -585,
     293,  -585,  -585,   -40,  -585,  -149,  -163,  -585,  -106,  -585,
    -281,   829,   -35,  -585,   -27,  -114,  -400,   -68,  -585,  -585,
     234,  -585,  -280,   655,  -300,   662,  -285
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -438
static const yytype_int16 yytable[] =
{
     137,   668,   280,   305,   500,   343,   424,   527,   245,   237,
     155,   359,   427,   170,   179,   363,    53,   217,   156,   310,
     657,    48,   413,   627,   681,   289,   578,   417,   148,   628,
     146,    73,    55,   546,   553,   557,   559,   270,   271,   517,
     226,   184,   192,  -437,   184,   200,   184,   204,   184,   184,
     208,   149,   209,    93,   601,     9,   220,   222,   223,   283,
     306,    93,   311,   216,   145,    48,    50,    48,   591,   284,
     233,   234,     9,    48,    48,    48,    48,   292,   281,   721,
     282,   236,    26,   682,   140,   187,   195,   337,   217,    93,
     185,   193,    53,   198,   201,   761,   658,    48,    93,    26,
     235,   312,   509,   780,   510,   183,   191,    73,    55,   224,
     603,   592,   587,   147,   272,   273,   215,    33,    34,   694,
     216,   335,   694,    27,   302,   291,   237,   778,   237,   186,
     194,   155,   295,   445,    33,    34,   795,   516,   150,   156,
     305,    93,    50,   659,   290,   305,   151,   293,    27,    28,
     294,    27,   296,   548,   548,   548,   548,   246,   247,   248,
     419,   153,   332,   334,   747,   676,    45,    93,   216,   195,
     402,   773,   627,   282,   193,   201,    47,    48,   703,   807,
      27,    28,    48,   140,    48,   245,    48,   195,    48,   191,
     300,   166,   741,   501,    45,   741,   685,   306,   345,   688,
     349,   168,   306,   420,    47,   154,   405,   347,   348,   350,
     608,   609,   282,   194,   568,   398,   689,   235,   751,   235,
       9,   736,   249,   166,   719,   250,   251,   140,   152,   410,
       5,   224,   224,   168,   140,   227,   707,   717,   707,   416,
      93,   159,   634,    12,   228,   689,   575,    26,    14,   364,
    -437,    17,   282,   229,   634,   305,    20,   635,   752,    22,
     210,   230,   548,   548,   211,   717,   357,   212,   155,   635,
     357,    27,    28,   155,   548,   548,   156,   282,   812,   396,
     737,   156,    33,    34,   544,   551,   610,   505,   756,   757,
     758,    27,    28,   283,   337,    27,   677,   216,    93,   263,
     140,    36,   277,   284,   264,   265,   276,    27,    28,   140,
     140,   140,   306,   279,   542,   615,   616,   282,   216,   771,
      42,    27,    28,    48,   543,     9,   278,   162,    48,    48,
     452,   453,   163,   282,   166,   617,   409,   164,    45,   195,
     789,   167,   165,     9,   168,   416,   512,   513,    47,   416,
     166,  -394,    26,   433,   800,   297,   548,   178,   548,   440,
     168,   197,   313,   202,   303,   205,   206,  -395,    73,   435,
      26,   314,   315,   351,   168,   316,   474,   317,   593,   305,
     686,   319,   540,   155,   344,   320,    73,    33,    34,   322,
     323,   156,   324,   325,   310,    27,    28,   326,   327,   328,
     329,   330,   622,   624,   282,    33,    34,   623,   625,   664,
      38,    39,    40,    41,   282,   352,   712,   499,   702,   283,
     589,   184,   192,   216,   354,   548,   565,   566,   355,   284,
     356,   195,   140,   140,   404,   604,   408,   283,    48,   595,
     596,   216,   266,   267,   282,   524,   718,   284,   416,   666,
     414,   224,   671,    48,    48,    48,    48,   672,   710,   415,
     580,   282,   583,   711,   750,   187,   195,   184,   192,   357,
     185,   193,   569,   570,   524,   215,   298,   421,   738,   216,
     474,   268,   269,    27,    28,   183,   191,   419,   425,   224,
      73,    27,   540,   428,   412,    38,    39,    40,    41,    48,
      48,    48,    48,   650,    27,   651,   652,   155,   474,   186,
     194,   187,   195,   274,   275,   156,   185,   193,    73,   155,
     611,   431,     9,  -247,   430,   444,   542,   156,   140,   140,
     216,   183,   191,    27,   542,   632,   543,   678,   216,   282,
     446,   357,   767,   524,   543,   353,   282,   554,   632,    26,
     282,   216,   447,   786,   448,   186,   194,   555,     1,     2,
       3,   224,    48,    48,    38,    39,    40,    41,   215,   511,
     450,   245,   216,    27,    48,    48,   433,   449,   540,   665,
     451,   729,   667,   440,    33,    34,   502,   169,   169,   180,
     189,    73,   435,   503,   215,   515,   504,   474,   216,   507,
     678,   708,   384,   385,   386,   387,    54,    73,   138,    73,
     403,   282,   140,  -279,   687,   506,   554,   215,   606,   474,
     216,   216,   727,   225,   406,   282,   555,   508,   141,    73,
     407,   282,   497,   498,   524,   357,   142,   524,    48,    48,
     562,   563,    48,   140,    48,   674,   675,   224,   433,   195,
     713,   714,   715,   514,   193,   245,    48,   517,    48,   722,
     282,    48,   762,    73,   435,   537,   195,   159,   195,   191,
     749,   357,   195,   189,   245,   524,   143,   193,   474,   734,
     723,   282,    54,   790,    38,    39,    40,    41,    73,   541,
     245,   224,   191,   194,   245,   781,   772,   282,   169,   560,
     304,   245,   169,   524,   561,     9,   564,   138,   577,   762,
     776,   282,   777,    56,   797,   139,   194,  -392,   754,   802,
     282,   801,   809,   282,   574,   140,   781,   141,   760,   576,
      48,   794,    26,   808,   768,   142,   797,    38,    39,    40,
      41,   579,   474,   474,   474,   225,   225,   813,   282,   815,
     282,   138,    73,    73,    73,   581,    27,    28,   138,   157,
     584,    38,    39,    40,    41,   380,   381,    33,    34,   585,
    -393,   141,  -278,   474,   586,   143,   792,   594,   141,   142,
     358,   224,   607,    73,   358,   599,   142,   313,   314,    56,
     382,   383,   648,   804,   474,   530,  -226,   388,   389,   308,
     224,   231,   232,   -44,    73,   811,   614,   653,   474,   168,
     814,   620,   696,   629,   139,   649,   654,   660,    73,   143,
     701,   655,   669,   670,   138,   656,   143,   673,   683,   684,
      82,   705,   699,   138,   138,   138,   706,   304,    38,    39,
      40,    41,   304,   169,   141,    38,    39,    40,    41,   720,
     725,   724,   142,   141,   141,   141,   728,   730,   139,   731,
       9,   142,   142,   142,   746,   139,   732,   689,   753,   755,
     759,   632,   530,  -227,   765,   774,   158,   779,  -212,   788,
     309,   775,   784,   739,   188,   196,   742,    26,   787,   791,
     475,   744,   143,   796,   803,   745,   806,   391,   390,   621,
     626,   143,   143,   143,   392,   698,    82,   393,   697,   394,
     743,    27,    28,   704,   631,   700,   612,   647,   640,   613,
     661,   662,    33,    34,   588,   726,   805,    38,    39,    40,
      41,   139,   769,   793,   810,   770,   213,   709,   399,   748,
     139,   139,   139,   434,     0,   400,     0,     0,     0,     0,
       0,     0,   304,     0,   542,     0,   138,   138,   216,   358,
       0,     0,     0,     0,   543,   225,     0,   169,   169,   180,
     189,     0,     0,     0,     0,     0,   141,   141,     0,     0,
       0,     0,     0,   358,   142,   142,   299,     0,   358,     0,
       0,   301,     0,     0,   475,     0,   401,   158,     0,     0,
       0,     0,     0,   225,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   169,   169,   180,   189,     0,     0,     0,
       0,     0,   475,     0,   143,   143,     0,     0,   182,   190,
       0,   182,   199,   182,   203,   182,   182,   207,     0,     0,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     436,   342,   138,   138,     0,   358,     0,   358,     0,     0,
       0,     0,   346,   139,   139,     0,     0,     0,     0,     0,
       0,     0,   141,   141,     0,   225,     0,   169,     0,     0,
     142,   142,     0,     0,   362,     0,     0,   365,   366,   367,
     368,   369,   370,   371,   372,   373,   374,   375,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   475,   190,   199,   203,   207,   262,   397,     0,     0,
     143,   143,     0,     0,     0,     0,     0,     0,     0,     0,
     190,     0,     0,   475,     0,     0,   618,     0,   299,     0,
       0,     0,     0,     0,     0,     0,     9,     0,   358,   358,
       0,   358,   169,   189,     0,     0,   141,     0,   169,   139,
     139,   225,     0,     0,   142,     0,   434,   641,     0,     0,
     169,     0,     0,    26,     0,   169,   189,     0,     0,   342,
       0,     0,     0,     0,     0,   358,     0,   141,     0,   358,
       0,     0,   475,     0,     0,   142,     0,    27,    28,     0,
       0,     0,     0,     0,   143,   225,     0,     0,    33,    34,
       0,     0,     0,    38,    39,    40,    41,   358,     0,     0,
       0,     0,     0,     0,     0,   239,   240,   241,   242,   243,
     244,     0,     0,     0,     9,   143,     0,     0,   434,     0,
     418,     0,     0,   619,   169,     0,     0,     0,     0,   641,
     168,     0,     0,     0,     0,   636,   475,   475,   475,     0,
     342,    26,   545,   552,   556,   558,     0,   638,     0,   141,
       0,     0,     9,   436,   642,     0,     0,   142,     0,     0,
       0,     0,   190,     0,     0,    27,     0,   475,     0,   342,
       0,     0,   342,     0,     0,   225,    33,    34,     0,    26,
       0,    38,    39,    40,    41,     0,     0,     0,   475,     0,
     597,   598,     0,     0,   225,     0,     0,   143,     0,     0,
       0,     0,   475,    27,     0,     0,     0,     0,   554,     0,
       0,     0,   216,   602,    33,    34,     0,     0,   555,    38,
      39,    40,    41,     0,     0,   436,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   642,     0,   342,     0,
       0,     0,     0,     0,     0,     0,    45,     0,     0,     0,
       0,     0,   158,     0,   190,     0,    47,     0,     0,     0,
       0,     0,     0,     0,   158,   376,   377,   378,   379,   379,
     379,   379,   379,   379,   379,   379,   379,   379,   379,   379,
     379,   379,   379,     0,     0,     0,     0,     0,   182,   190,
       0,     0,     0,     0,     6,     7,     0,     0,     8,     9,
       0,     0,     0,    10,     0,    11,     0,    13,     0,     0,
       0,     0,    15,    16,     0,     0,    18,    19,     0,     0,
      21,     0,     0,    23,    24,    25,    26,     0,   695,   342,
       0,   695,   342,     0,   182,   190,     0,     0,     0,     0,
       0,     0,     0,   240,   342,   299,     0,   299,     0,     0,
      27,    28,     0,     0,     0,     0,   455,    29,    30,    31,
      32,    33,    34,    35,     0,     0,    38,    39,    40,    41,
     342,     0,   342,     0,     0,     0,    86,     0,     0,     0,
       0,     0,     0,     0,    43,    44,     0,    87,    88,     0,
       0,     0,     0,    45,     0,    89,     0,   379,   342,     0,
       0,     0,     0,    47,   342,     0,     0,     0,    27,     0,
      90,    91,    92,    93,     0,   689,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,    95,    96,    97,     0,     0,     0,     0,    98,
      99,     0,     0,     0,   100,   101,     0,     0,     0,     0,
       0,   102,     0,     0,     0,     0,     0,     0,     0,     0,
     103,   104,   105,   106,   107,   108,     0,     0,     0,     0,
       0,     0,   190,   395,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   190,
       0,   190,     0,     0,     0,   190,     0,     0,     0,     0,
       0,     0,     0,   379,     5,     6,     7,   456,   457,     8,
       9,   458,   459,   460,    10,     0,    11,    12,    13,   461,
     462,   463,    14,    15,    16,    17,   464,    18,    19,    86,
      20,    21,   465,    22,    23,    24,    25,    26,   466,     0,
      87,    88,     0,     0,     0,     0,     0,     0,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,    28,    90,    91,    92,    93,   467,    29,    30,
      31,    32,    33,    34,    35,    36,   468,    38,    39,    40,
      41,     0,   469,   470,    94,    95,    96,    97,   471,     0,
       0,   472,    98,    99,    42,    43,    44,   100,   101,     0,
       0,     0,     0,     0,   102,     0,     0,     0,     0,     0,
    -321,     0,   473,   103,   104,   105,   106,   107,   108,     5,
       6,     7,   456,   457,     8,     9,   458,   459,   460,    10,
       0,    11,    12,    13,   461,   462,   463,    14,    15,    16,
      17,   464,    18,    19,    86,    20,    21,   465,    22,    23,
      24,    25,    26,   466,     0,    87,    88,     0,     0,     0,
       0,     0,     0,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,    28,    90,    91,
      92,    93,     0,    29,    30,    31,    32,    33,    34,    35,
      36,   468,    38,    39,    40,    41,     0,   469,   470,    94,
      95,    96,    97,   471,     0,     0,   472,    98,    99,    42,
      43,    44,   100,   101,     0,     0,     0,     0,     0,   102,
       0,     0,     0,     0,     0,  -321,     0,   600,   103,   104,
     105,   106,   107,   108,     5,     6,     7,   456,   457,     8,
       9,   458,   459,   460,    10,     0,    11,    12,    13,   461,
     462,   463,    14,    15,    16,    17,   464,    18,    19,    86,
      20,    21,   465,    22,    23,    24,    25,    26,   466,     0,
      87,    88,     0,     0,     0,     0,     0,     0,    89,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    27,    28,    90,    91,    92,    93,     0,    29,    30,
      31,    32,    33,    34,    35,    36,   468,    38,    39,    40,
      41,     0,   469,   470,    94,    95,    96,    97,   471,     0,
       0,   472,    98,    99,    42,    43,    44,   100,   101,     0,
       0,     0,     0,     0,   102,     0,     0,     0,     0,     0,
    -321,     0,     0,   103,   104,   105,   106,   107,   108,     5,
       6,     7,     0,     0,     8,     9,     0,     0,     0,    10,
       0,    11,    12,    13,     0,     0,     0,    14,    15,    16,
      17,     0,    18,    19,    86,    20,    21,     0,    22,    23,
      24,    25,    26,     0,     0,    87,    88,     0,     0,     0,
       0,     0,     0,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,    28,    90,    91,
      92,    93,     0,    29,    30,    31,    32,    33,    34,    35,
      36,     0,    38,    39,    40,    41,     0,     0,     0,    94,
      95,    96,    97,     0,     0,     0,     0,    98,    99,    42,
      43,    44,   100,   101,     0,     0,     0,     0,     0,   102,
       0,     0,     0,     0,     0,     0,     0,     0,   103,   104,
     105,   106,   107,   108,     6,     7,     0,     0,     8,     9,
       0,     0,     0,    10,     0,    11,     0,    13,     0,     0,
       0,     0,    15,    16,     0,     0,    18,    19,    86,     0,
      21,     0,     0,    23,    24,    25,    26,     0,     0,    87,
      88,     0,     0,     0,     0,     0,     0,    89,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,    28,    90,    91,    92,    93,     0,    29,    30,    31,
      32,    33,    34,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,    95,    96,    97,     0,     0,     0,
       0,    98,    99,     0,    43,    44,   100,   101,     0,     0,
       0,     0,     0,   102,     0,     0,     0,     0,     0,     0,
       0,     0,   103,   104,   105,   106,   107,   108,     6,     7,
       0,     0,     8,     9,     0,     0,     0,    10,     0,    11,
       0,    13,     0,     0,     0,     0,    15,    16,     0,     0,
      18,    19,    86,     0,    21,     0,     0,    23,    24,    25,
      26,     0,     0,    87,    88,     0,     0,     0,     0,     0,
       0,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,    28,    90,    91,    92,    93,
       0,    29,    30,    31,    32,    33,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,    96,
      97,     0,     0,     0,     0,    98,    99,     0,    43,    44,
     100,   101,     0,     0,     0,     0,     0,   221,     0,     0,
       0,     0,     0,     0,     0,     0,   103,   104,   105,   106,
     107,   108,     5,     6,     7,     0,     0,     8,     9,     0,
       0,     0,    10,     0,    11,    12,    13,     0,     0,     0,
      14,    15,    16,    17,     0,    18,    19,     0,    20,    21,
       0,    22,    23,    24,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      28,     0,     0,     0,     0,     0,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    43,    44,     0,     0,     0,     0,     0,
       0,     0,    45,     0,     0,     5,     6,     7,     0,    46,
       8,     9,    47,     0,     0,    10,     0,    11,    12,    13,
       0,     0,     0,    14,    15,    16,    17,     0,    18,    19,
       0,    20,    21,     0,    22,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,    28,     0,     0,     0,     0,     0,    29,
      30,    31,    32,    33,    34,    35,    36,     0,    38,    39,
      40,    41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    43,    44,     5,     6,
       7,     0,     0,     8,     9,   554,     0,     0,    10,   216,
      11,    12,    13,     0,     0,   555,    14,    15,    16,    17,
       0,    18,    19,     0,    20,    21,     0,    22,    23,    24,
      25,    26,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,    28,     0,     0,     0,
       0,     0,    29,    30,    31,    32,    33,    34,    35,    36,
       0,    38,    39,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    43,
      44,     6,     7,     0,     0,     8,     9,     0,    45,     0,
      10,     0,    11,     0,    13,     0,     0,     0,    47,    15,
      16,     0,     0,    18,    19,     0,     0,    21,     0,     0,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,     0,
       0,     0,     0,     0,    29,    30,    31,    32,    33,    34,
      35,     0,     0,    38,    39,    40,    41,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    43,    44,     5,     6,     7,     0,     0,     8,     9,
     283,     0,     0,    10,   216,    11,    12,    13,     0,     0,
     284,    14,    15,    16,    17,     0,    18,    19,     0,    20,
      21,     0,    22,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   639,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,     0,     0,     0,     0,     0,    29,    30,    31,
      32,    33,    34,    35,    36,     0,    38,    39,    40,    41,
       0,     0,     0,     0,     0,     0,     5,     6,     7,     0,
       0,     8,     9,    42,    43,    44,    10,     0,    11,    12,
      13,     0,     0,     0,    14,    15,    16,    17,     0,    18,
      19,     0,    20,    21,     0,    22,    23,    24,    25,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,     0,     0,     0,     0,     0,
      29,    30,    31,    32,    33,    34,    35,    36,     0,    38,
      39,    40,    41,     0,     0,     0,     0,     0,     0,     5,
       6,     7,     0,     0,     8,     9,    42,    43,    44,    10,
       0,     0,    12,    13,     0,     0,     0,    14,    15,    16,
      17,     0,    18,    19,     0,    20,     0,     0,    22,     0,
      24,    25,    26,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,    30,    31,    32,    33,    34,     0,
      36,     0,     0,     0,     6,     7,     0,     0,     8,     9,
       0,     0,     0,    10,     0,    11,     0,    13,     0,    42,
       0,    44,    15,    16,     0,     0,    18,    19,     0,     0,
      21,     0,     0,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,     0,     0,     0,     0,     0,    29,    30,    31,
      32,    33,    34,    35,     0,     0,    38,    39,    40,    41,
       6,     7,     0,     0,     8,     9,     0,     0,     0,    10,
       0,    11,     0,    13,    43,    44,     0,     0,    15,    16,
       0,     0,    18,    19,     0,     0,    21,     5,     0,    23,
      24,    25,    26,     9,     0,     0,     0,     0,     0,     0,
      12,     0,     0,     0,     0,    14,     0,     0,    17,     0,
       0,     0,     0,    20,     0,     0,    22,    28,     0,     0,
      26,     0,     0,    29,    30,    31,    32,    33,    34,    35,
       6,     7,     0,     0,     8,     9,     0,     0,     0,    10,
       0,     0,     0,    13,     0,     0,     0,     0,    15,    16,
      43,    44,    18,    19,     0,    33,    34,     0,    36,     0,
      24,    25,    26,     0,     0,     0,     0,    86,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    87,    88,
       0,     0,     0,     0,     0,     0,    89,     0,     0,     0,
       0,     0,     0,    29,    30,    31,    32,    33,    34,    27,
      28,    90,    91,    92,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    44,    94,    95,    96,    97,     0,     0,    86,     0,
      98,    99,     0,     0,     0,   100,   101,     0,     0,    87,
      88,     0,   102,     0,     0,   521,   522,    89,   523,     0,
     716,   103,   104,   105,   106,   107,   108,     0,     0,     0,
      27,    28,    90,    91,    92,    93,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    94,    95,    96,    97,     0,     0,    86,
       0,    98,    99,     0,     0,     0,   100,   101,     0,     0,
      87,    88,     0,   102,     0,     0,   521,   522,    89,   523,
       0,   735,   103,   104,   105,   106,   107,   108,     0,     0,
       0,    27,    28,    90,    91,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    94,    95,    96,    97,     0,     0,
      86,     0,    98,    99,     0,     0,     0,   100,   101,     0,
       0,    87,    88,     0,   102,     0,     0,   521,   522,    89,
     523,     0,     0,   103,   104,   105,   106,   107,   108,     0,
       0,     0,    27,     0,    90,    91,    92,    93,     0,     0,
       0,     0,    86,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    87,    88,    94,    95,    96,    97,     0,
       0,    89,     0,    98,    99,     0,     0,     0,   100,   101,
       0,     0,     0,     0,    27,   102,    90,    91,    92,    93,
     340,     0,     0,     0,   103,   341,   105,   106,   107,   108,
       0,     0,     0,     0,     0,     0,     0,    94,    95,    96,
      97,    86,     0,     0,     0,    98,    99,     0,     0,     0,
     100,   101,    87,    88,     0,     0,     0,   102,   360,     0,
      89,     0,     0,     0,     0,     0,   103,   104,   105,   106,
     107,   108,     0,    27,     0,    90,    91,    92,    93,     0,
       0,     0,     0,    86,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    87,    88,    94,    95,    96,    97,
       0,     0,    89,     0,    98,    99,     0,     0,     0,   100,
     101,     0,     0,     0,     0,    27,   102,    90,    91,    92,
      93,   443,     0,     0,     0,   103,   104,   105,   106,   107,
     108,     0,     0,     0,     0,     0,     0,     0,    94,    95,
      96,    97,    86,     0,     0,     0,    98,    99,     0,     0,
       0,   100,   101,    87,    88,     0,     0,     0,   102,     0,
       0,    89,     0,     0,   454,     0,     0,   103,   104,   105,
     106,   107,   108,     0,    27,     0,    90,    91,    92,    93,
       0,     0,     0,     0,    86,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    87,    88,    94,    95,    96,
      97,     0,     0,    89,     0,    98,    99,     0,     0,     0,
     100,   101,     0,     0,     0,     0,    27,   102,    90,    91,
      92,    93,     0,     0,   582,     0,   103,   104,   105,   106,
     107,   108,     0,     0,     0,     0,     0,     0,     0,    94,
      95,    96,    97,    86,     0,     0,     0,    98,    99,     0,
       0,     0,   100,   101,    87,    88,     0,     0,     0,   102,
       0,     0,    89,     0,     0,     0,     0,     0,   103,   104,
     105,   106,   107,   108,     0,    27,     0,    90,    91,    92,
      93,     0,     0,     0,     0,    86,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    87,    88,    94,    95,
      96,    97,     0,     0,    89,     0,    98,    99,     0,     0,
       0,   100,   101,     0,     0,     0,     0,    27,   219,    90,
      91,    92,    93,     0,     0,     0,     0,   103,   104,   105,
     106,   107,   108,     0,     0,     0,     0,     0,     0,     0,
      94,    95,    96,    97,     0,     0,     0,     0,    98,    99,
       0,     0,     0,   100,   101,     0,     0,     0,     0,     0,
     221,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   107,   108
};

static const yytype_int16 yycheck[] =
{
       2,   585,    48,   166,   395,   216,   314,   425,   115,   102,
      45,   246,   321,    53,    54,   250,     1,    85,    45,   168,
      49,     1,   303,   105,    49,   139,   460,   308,    80,   111,
     103,     1,     1,   433,   434,   435,   436,    43,    44,    36,
      89,    55,    56,    60,    58,    59,    60,    61,    62,    63,
      64,   103,    66,    65,   488,     9,    86,    87,    88,   103,
     166,    65,   168,   107,     0,    45,     1,    47,    66,   113,
     100,   101,     9,    53,    54,    55,    56,   147,   124,   663,
     105,   102,    36,   108,     3,    55,    56,   104,   156,    65,
      55,    56,    77,    58,    59,   107,   125,    77,    65,    36,
     102,   169,   411,   107,   412,    55,    56,    77,    77,    89,
     501,   109,   109,   103,   120,   121,   103,    71,    72,   619,
     107,   214,   622,    60,   164,   146,   219,   103,   221,    55,
      56,   166,   153,   344,    71,    72,   103,   418,    80,   166,
     303,    65,    77,   577,   146,   308,    80,   149,    60,    61,
     152,    60,   154,   433,   434,   435,   436,    38,    39,    40,
     309,   120,   211,   212,   103,   599,   103,    65,   107,   139,
     284,   755,   105,   105,   139,   140,   113,   157,   111,   103,
      60,    61,   162,   102,   164,   292,   166,   157,   168,   139,
     160,   103,   692,   125,   103,   695,   614,   303,   219,   617,
     230,   113,   308,   309,   113,   107,   104,   228,   229,   230,
     519,   520,   105,   139,   449,   283,   125,   219,   111,   221,
       9,    49,   103,   103,   658,   106,   107,   146,   103,   297,
       3,   211,   212,   113,   153,   103,   636,   655,   638,   307,
      65,    49,   542,    16,   103,   125,   457,    36,    21,   251,
      60,    24,   105,   103,   554,   418,    29,   542,   111,    32,
      68,   103,   542,   543,    72,   683,   246,    75,   303,   554,
     250,    60,    61,   308,   554,   555,   303,   105,   103,   281,
     108,   308,    71,    72,   433,   434,   521,   401,   722,   723,
     724,    60,    61,   103,   104,    60,   605,   107,    65,   113,
     219,    74,   122,   113,   118,   119,   112,    60,    61,   228,
     229,   230,   418,    47,   103,   106,   107,   105,   107,   753,
      93,    60,    61,   303,   113,     9,   123,   105,   308,   309,
     351,   352,   110,   105,   103,   126,   108,   105,   103,   309,
     774,   110,   110,     9,   113,   413,   414,   415,   113,   417,
     103,   109,    36,   338,   788,   104,   636,   110,   638,   339,
     113,    58,   170,    60,   103,    62,    63,   109,   338,   338,
      36,   179,   180,   109,   113,   183,   356,   185,   471,   542,
     615,   189,   431,   418,   107,   193,   356,    71,    72,   197,
     198,   418,   200,   201,   543,    60,    61,   205,   206,   207,
     208,   209,   105,   105,   105,    71,    72,   110,   110,   110,
      76,    77,    78,    79,   105,   109,   651,   108,   629,   103,
     469,   435,   436,   107,   104,   705,   447,   448,   104,   113,
     109,   401,   351,   352,   104,   503,   121,   103,   418,   479,
     480,   107,   114,   115,   105,   425,   657,   113,   516,   110,
     104,   431,   105,   433,   434,   435,   436,   110,   105,   104,
     462,   105,   464,   110,   108,   435,   436,   481,   482,   449,
     435,   436,   452,   453,   454,   103,   104,    75,   689,   107,
     460,    41,    42,    60,    61,   435,   436,   636,   126,   469,
     460,    60,   541,   109,   302,    76,    77,    78,    79,   479,
     480,   481,   482,   104,    60,   106,   107,   542,   488,   435,
     436,   481,   482,    45,    46,   542,   481,   482,   488,   554,
     522,   109,     9,   109,   332,   108,   103,   554,   447,   448,
     107,   481,   482,    60,   103,   104,   113,   607,   107,   105,
     104,   521,   108,   523,   113,   104,   105,   103,   104,    36,
     105,   107,   105,   108,   105,   481,   482,   113,   100,   101,
     102,   541,   542,   543,    76,    77,    78,    79,   103,   104,
     104,   678,   107,    60,   554,   555,   561,   105,   627,   581,
     104,   674,   584,   563,    71,    72,   104,    53,    54,    55,
      56,   561,   561,   104,   103,   104,   104,   577,   107,    80,
     670,   641,   270,   271,   272,   273,     1,   577,     3,   579,
     104,   105,   531,   125,   616,   110,   103,   103,   104,   599,
     107,   107,   671,    89,   104,   105,   113,    80,     3,   599,
     104,   105,   104,   105,   614,   615,     3,   617,   618,   619,
     104,   105,   622,   562,   624,    88,    89,   627,   633,   619,
     652,   653,   654,   104,   619,   762,   636,    36,   638,   104,
     105,   641,   732,   633,   633,   109,   636,   475,   638,   619,
     710,   651,   642,   139,   781,   655,     3,   642,   658,   681,
     104,   105,    77,   776,    76,    77,    78,    79,   658,   109,
     797,   671,   642,   619,   801,   765,   104,   105,   164,   104,
     166,   808,   168,   683,   105,     9,   108,   102,   125,   779,
     104,   105,   761,     1,   784,     3,   642,   109,   720,   104,
     105,   791,   104,   105,   110,   644,   796,   102,   730,   110,
     710,   780,    36,   803,   736,   102,   806,    76,    77,    78,
      79,   103,   722,   723,   724,   211,   212,   104,   105,   104,
     105,   146,   722,   723,   724,   103,    60,    61,   153,    47,
     103,    76,    77,    78,    79,   266,   267,    71,    72,   103,
     109,   146,   125,   753,   111,   102,   778,   110,   153,   146,
     246,   761,   103,   753,   250,   125,   153,   595,   596,    77,
     268,   269,   104,   795,   774,   110,   111,   274,   275,   103,
     780,    98,    99,   125,   774,   807,   125,   110,   788,   113,
     812,   111,   620,   126,   102,   104,   110,    37,   788,   146,
     628,   105,    66,   103,   219,   111,   153,    66,   105,   111,
       1,   104,   111,   228,   229,   230,   104,   303,    76,    77,
      78,    79,   308,   309,   219,    76,    77,    78,    79,   103,
     111,   104,   219,   228,   229,   230,   111,   103,   146,   104,
       9,   228,   229,   230,   104,   153,   125,   125,   125,   110,
     104,   104,   110,   111,   125,    14,    47,   105,   109,   104,
     168,   110,   125,   691,    55,    56,   694,    36,   110,   108,
     356,   699,   219,   105,   108,   703,   105,   277,   276,   533,
     537,   228,   229,   230,   278,   624,    77,   279,   622,   280,
     695,    60,    61,   633,   541,   627,   523,   563,   561,   523,
     579,   579,    71,    72,   468,   670,   796,    76,    77,    78,
      79,   219,   740,   779,   806,   743,    77,   644,   283,   705,
     228,   229,   230,   338,    -1,   283,    -1,    -1,    -1,    -1,
      -1,    -1,   418,    -1,   103,    -1,   351,   352,   107,   425,
      -1,    -1,    -1,    -1,   113,   431,    -1,   433,   434,   435,
     436,    -1,    -1,    -1,    -1,    -1,   351,   352,    -1,    -1,
      -1,    -1,    -1,   449,   351,   352,   157,    -1,   454,    -1,
      -1,   162,    -1,    -1,   460,    -1,   284,   168,    -1,    -1,
      -1,    -1,    -1,   469,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   479,   480,   481,   482,    -1,    -1,    -1,
      -1,    -1,   488,    -1,   351,   352,    -1,    -1,    55,    56,
      -1,    58,    59,    60,    61,    62,    63,    64,    -1,    -1,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
     338,   216,   447,   448,    -1,   521,    -1,   523,    -1,    -1,
      -1,    -1,   227,   351,   352,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   447,   448,    -1,   541,    -1,   543,    -1,    -1,
     447,   448,    -1,    -1,   249,    -1,    -1,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   577,   139,   140,   141,   142,   126,   282,    -1,    -1,
     447,   448,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     157,    -1,    -1,   599,    -1,    -1,   531,    -1,   309,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     9,    -1,   614,   615,
      -1,   617,   618,   619,    -1,    -1,   531,    -1,   624,   447,
     448,   627,    -1,    -1,   531,    -1,   561,   562,    -1,    -1,
     636,    -1,    -1,    36,    -1,   641,   642,    -1,    -1,   344,
      -1,    -1,    -1,    -1,    -1,   651,    -1,   562,    -1,   655,
      -1,    -1,   658,    -1,    -1,   562,    -1,    60,    61,    -1,
      -1,    -1,    -1,    -1,   531,   671,    -1,    -1,    71,    72,
      -1,    -1,    -1,    76,    77,    78,    79,   683,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   103,   104,   105,   106,   107,
     108,    -1,    -1,    -1,     9,   562,    -1,    -1,   633,    -1,
     103,    -1,    -1,   531,   710,    -1,    -1,    -1,    -1,   644,
     113,    -1,    -1,    -1,    -1,   543,   722,   723,   724,    -1,
     425,    36,   433,   434,   435,   436,    -1,   555,    -1,   644,
      -1,    -1,     9,   561,   562,    -1,    -1,   644,    -1,    -1,
      -1,    -1,   309,    -1,    -1,    60,    -1,   753,    -1,   454,
      -1,    -1,   457,    -1,    -1,   761,    71,    72,    -1,    36,
      -1,    76,    77,    78,    79,    -1,    -1,    -1,   774,    -1,
     481,   482,    -1,    -1,   780,    -1,    -1,   644,    -1,    -1,
      -1,    -1,   788,    60,    -1,    -1,    -1,    -1,   103,    -1,
      -1,    -1,   107,   498,    71,    72,    -1,    -1,   113,    76,
      77,    78,    79,    -1,    -1,   633,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   644,    -1,   523,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,    -1,
      -1,    -1,   543,    -1,   401,    -1,   113,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   555,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,    -1,    -1,    -1,    -1,    -1,   435,   436,
      -1,    -1,    -1,    -1,     4,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    13,    -1,    15,    -1,    17,    -1,    -1,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    -1,    -1,
      30,    -1,    -1,    33,    34,    35,    36,    -1,   619,   614,
      -1,   622,   617,    -1,   481,   482,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   341,   629,   636,    -1,   638,    -1,    -1,
      60,    61,    -1,    -1,    -1,    -1,   354,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    76,    77,    78,    79,
     655,    -1,   657,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    -1,    39,    40,    -1,
      -1,    -1,    -1,   103,    -1,    47,    -1,   395,   683,    -1,
      -1,    -1,    -1,   113,   689,    -1,    -1,    -1,    60,    -1,
      62,    63,    64,    65,    -1,   125,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    91,
      92,    -1,    -1,    -1,    96,    97,    -1,    -1,    -1,    -1,
      -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     112,   113,   114,   115,   116,   117,    -1,    -1,    -1,    -1,
      -1,    -1,   619,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   636,
      -1,   638,    -1,    -1,    -1,   642,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   501,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    83,    84,    85,    86,    87,    -1,
      -1,    90,    91,    92,    93,    94,    95,    96,    97,    -1,
      -1,    -1,    -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,
     109,    -1,   111,   112,   113,   114,   115,   116,   117,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    -1,    -1,    90,    91,    92,    93,
      94,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,   103,
      -1,    -1,    -1,    -1,    -1,   109,    -1,   111,   112,   113,
     114,   115,   116,   117,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    -1,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    -1,    81,    82,    83,    84,    85,    86,    87,    -1,
      -1,    90,    91,    92,    93,    94,    95,    96,    97,    -1,
      -1,    -1,    -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,
     109,    -1,    -1,   112,   113,   114,   115,   116,   117,     3,
       4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,
      -1,    15,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    -1,    26,    27,    28,    29,    30,    -1,    32,    33,
      34,    35,    36,    -1,    -1,    39,    40,    -1,    -1,    -1,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,    63,
      64,    65,    -1,    67,    68,    69,    70,    71,    72,    73,
      74,    -1,    76,    77,    78,    79,    -1,    -1,    -1,    83,
      84,    85,    86,    -1,    -1,    -1,    -1,    91,    92,    93,
      94,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,   103,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,   113,
     114,   115,   116,   117,     4,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    13,    -1,    15,    -1,    17,    -1,    -1,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    39,
      40,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    -1,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    84,    85,    86,    -1,    -1,    -1,
      -1,    91,    92,    -1,    94,    95,    96,    97,    -1,    -1,
      -1,    -1,    -1,   103,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   112,   113,   114,   115,   116,   117,     4,     5,
      -1,    -1,     8,     9,    -1,    -1,    -1,    13,    -1,    15,
      -1,    17,    -1,    -1,    -1,    -1,    22,    23,    -1,    -1,
      26,    27,    28,    -1,    30,    -1,    -1,    33,    34,    35,
      36,    -1,    -1,    39,    40,    -1,    -1,    -1,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    62,    63,    64,    65,
      -1,    67,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,
      86,    -1,    -1,    -1,    -1,    91,    92,    -1,    94,    95,
      96,    97,    -1,    -1,    -1,    -1,    -1,   103,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,   115,
     116,   117,     3,     4,     5,    -1,    -1,     8,     9,    -1,
      -1,    -1,    13,    -1,    15,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    -1,    26,    27,    -1,    29,    30,
      -1,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   103,    -1,    -1,     3,     4,     5,    -1,   110,
       8,     9,   113,    -1,    -1,    13,    -1,    15,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    -1,    26,    27,
      -1,    29,    30,    -1,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    67,
      68,    69,    70,    71,    72,    73,    74,    -1,    76,    77,
      78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    93,    94,    95,     3,     4,
       5,    -1,    -1,     8,     9,   103,    -1,    -1,    13,   107,
      15,    16,    17,    -1,    -1,   113,    21,    22,    23,    24,
      -1,    26,    27,    -1,    29,    30,    -1,    32,    33,    34,
      35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    76,    77,    78,    79,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    94,
      95,     4,     5,    -1,    -1,     8,     9,    -1,   103,    -1,
      13,    -1,    15,    -1,    17,    -1,    -1,    -1,   113,    22,
      23,    -1,    -1,    26,    27,    -1,    -1,    30,    -1,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    76,    77,    78,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    94,    95,     3,     4,     5,    -1,    -1,     8,     9,
     103,    -1,    -1,    13,   107,    15,    16,    17,    -1,    -1,
     113,    21,    22,    23,    24,    -1,    26,    27,    -1,    29,
      30,    -1,    32,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    74,    -1,    76,    77,    78,    79,
      -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,
      -1,     8,     9,    93,    94,    95,    13,    -1,    15,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    -1,    26,
      27,    -1,    29,    30,    -1,    32,    33,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    74,    -1,    76,
      77,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,    -1,    -1,     8,     9,    93,    94,    95,    13,
      -1,    -1,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    -1,    26,    27,    -1,    29,    -1,    -1,    32,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    -1,
      74,    -1,    -1,    -1,     4,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    13,    -1,    15,    -1,    17,    -1,    93,
      -1,    95,    22,    23,    -1,    -1,    26,    27,    -1,    -1,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    -1,    -1,    76,    77,    78,    79,
       4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,
      -1,    15,    -1,    17,    94,    95,    -1,    -1,    22,    23,
      -1,    -1,    26,    27,    -1,    -1,    30,     3,    -1,    33,
      34,    35,    36,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      16,    -1,    -1,    -1,    -1,    21,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    -1,    -1,    32,    61,    -1,    -1,
      36,    -1,    -1,    67,    68,    69,    70,    71,    72,    73,
       4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,
      -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,    22,    23,
      94,    95,    26,    27,    -1,    71,    72,    -1,    74,    -1,
      34,    35,    36,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    93,    39,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69,    70,    71,    72,    60,
      61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    95,    83,    84,    85,    86,    -1,    -1,    28,    -1,
      91,    92,    -1,    -1,    -1,    96,    97,    -1,    -1,    39,
      40,    -1,   103,    -1,    -1,   106,   107,    47,   109,    -1,
     111,   112,   113,   114,   115,   116,   117,    -1,    -1,    -1,
      60,    61,    62,    63,    64,    65,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,    84,    85,    86,    -1,    -1,    28,
      -1,    91,    92,    -1,    -1,    -1,    96,    97,    -1,    -1,
      39,    40,    -1,   103,    -1,    -1,   106,   107,    47,   109,
      -1,   111,   112,   113,   114,   115,   116,   117,    -1,    -1,
      -1,    60,    61,    62,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    84,    85,    86,    -1,    -1,
      28,    -1,    91,    92,    -1,    -1,    -1,    96,    97,    -1,
      -1,    39,    40,    -1,   103,    -1,    -1,   106,   107,    47,
     109,    -1,    -1,   112,   113,   114,   115,   116,   117,    -1,
      -1,    -1,    60,    -1,    62,    63,    64,    65,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    83,    84,    85,    86,    -1,
      -1,    47,    -1,    91,    92,    -1,    -1,    -1,    96,    97,
      -1,    -1,    -1,    -1,    60,   103,    62,    63,    64,    65,
     108,    -1,    -1,    -1,   112,   113,   114,   115,   116,   117,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,
      86,    28,    -1,    -1,    -1,    91,    92,    -1,    -1,    -1,
      96,    97,    39,    40,    -1,    -1,    -1,   103,   104,    -1,
      47,    -1,    -1,    -1,    -1,    -1,   112,   113,   114,   115,
     116,   117,    -1,    60,    -1,    62,    63,    64,    65,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    83,    84,    85,    86,
      -1,    -1,    47,    -1,    91,    92,    -1,    -1,    -1,    96,
      97,    -1,    -1,    -1,    -1,    60,   103,    62,    63,    64,
      65,   108,    -1,    -1,    -1,   112,   113,   114,   115,   116,
     117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    84,
      85,    86,    28,    -1,    -1,    -1,    91,    92,    -1,    -1,
      -1,    96,    97,    39,    40,    -1,    -1,    -1,   103,    -1,
      -1,    47,    -1,    -1,   109,    -1,    -1,   112,   113,   114,
     115,   116,   117,    -1,    60,    -1,    62,    63,    64,    65,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    83,    84,    85,
      86,    -1,    -1,    47,    -1,    91,    92,    -1,    -1,    -1,
      96,    97,    -1,    -1,    -1,    -1,    60,   103,    62,    63,
      64,    65,    -1,    -1,   110,    -1,   112,   113,   114,   115,
     116,   117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      84,    85,    86,    28,    -1,    -1,    -1,    91,    92,    -1,
      -1,    -1,    96,    97,    39,    40,    -1,    -1,    -1,   103,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,   112,   113,
     114,   115,   116,   117,    -1,    60,    -1,    62,    63,    64,
      65,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    83,    84,
      85,    86,    -1,    -1,    47,    -1,    91,    92,    -1,    -1,
      -1,    96,    97,    -1,    -1,    -1,    -1,    60,   103,    62,
      63,    64,    65,    -1,    -1,    -1,    -1,   112,   113,   114,
     115,   116,   117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      83,    84,    85,    86,    -1,    -1,    -1,    -1,    91,    92,
      -1,    -1,    -1,    96,    97,    -1,    -1,    -1,    -1,    -1,
     103,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   112,
     113,   114,   115,   116,   117
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   100,   101,   102,   128,     3,     4,     5,     8,     9,
      13,    15,    16,    17,    21,    22,    23,    24,    26,    27,
      29,    30,    32,    33,    34,    35,    36,    60,    61,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    93,    94,    95,   103,   110,   113,   129,   130,
     164,   165,   171,   175,   176,   177,   178,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   197,   200,   210,   213,   258,   259,   260,   261,
     262,   269,   278,   279,   280,   281,    28,    39,    40,    47,
      62,    63,    64,    65,    83,    84,    85,    86,    91,    92,
      96,    97,   103,   112,   113,   114,   115,   116,   117,   129,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   141,
     142,   143,   144,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   176,   178,
     182,   184,   187,   189,   223,     0,   103,   103,    80,   103,
      80,    80,   103,   120,   107,   279,   281,   178,   278,   198,
     199,   200,   105,   110,   105,   110,   103,   110,   113,   130,
     270,   271,   272,   273,   274,   275,   276,   278,   110,   270,
     130,   179,   180,   188,   190,   191,   192,   200,   278,   130,
     180,   188,   190,   191,   192,   200,   278,   179,   191,   180,
     190,   191,   179,   180,   190,   179,   179,   180,   190,   190,
     198,   198,   198,   260,   263,   103,   107,   284,   289,   103,
     147,   103,   147,   147,   129,   130,   222,   103,   103,   103,
     103,   234,   234,   147,   147,   161,   223,   233,   234,   148,
     148,   148,   148,   148,   148,   134,    38,    39,    40,   103,
     106,   107,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,   126,   113,   118,   119,   114,   115,    41,    42,
      43,    44,   120,   121,    45,    46,   112,   122,   123,    47,
      48,   124,   105,   103,   113,   282,   284,   290,   292,   282,
     161,   223,   136,   161,   161,   223,   161,   104,   104,   278,
     200,   278,   270,   103,   130,   273,   275,   277,   103,   178,
     272,   275,   284,   198,   198,   198,   198,   198,   166,   198,
     198,   167,   198,   198,   198,   198,   198,   198,   198,   198,
     198,   195,   222,   211,   222,   233,   264,   104,   285,   286,
     108,   113,   160,   162,   107,   223,   160,   223,   223,   147,
     223,   109,   109,   104,   104,   104,   109,   129,   130,   145,
     104,   146,   160,   145,   161,   160,   160,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   148,   148,   148,   148,
     149,   149,   150,   150,   151,   151,   151,   151,   152,   152,
     153,   154,   155,   156,   157,   125,   161,   160,   284,   290,
     292,   178,   282,   104,   104,   104,   104,   104,   121,   108,
     284,   168,   198,   277,   104,   104,   284,   277,   103,   272,
     275,    75,   169,   170,   170,   126,   224,   224,   109,   196,
     198,   109,   212,   175,   176,   177,   178,   217,   220,   221,
     129,   218,   219,   108,   108,   162,   104,   105,   105,   105,
     104,   104,   223,   223,   109,   148,     6,     7,    10,    11,
      12,    18,    19,    20,    25,    31,    37,    66,    75,    81,
      82,    87,    90,   111,   129,   130,   161,   163,   164,   175,
     176,   177,   178,   222,   230,   231,   232,   233,   235,   236,
     237,   239,   240,   241,   243,   244,   245,   104,   105,   108,
     159,   125,   104,   104,   104,   282,   110,    80,    80,   224,
     170,   104,   284,   284,   104,   104,   277,    36,   246,   172,
     173,   106,   107,   109,   129,   145,   162,   225,   228,   229,
     110,   198,   201,   202,   203,   204,   205,   109,   214,   215,
     222,   109,   103,   113,   272,   278,   283,   287,   289,   291,
     293,   272,   278,   283,   103,   113,   278,   283,   278,   283,
     104,   105,   104,   105,   108,   223,   223,   140,   145,   129,
     129,   225,   226,   227,   110,   162,   110,   125,   230,   103,
     161,   103,   110,   161,   103,   103,   111,   109,   246,   222,
     242,    66,   109,   233,   110,   270,   270,   278,   278,   125,
     111,   230,   160,   159,   284,   174,   104,   103,   224,   224,
     145,   161,   226,   227,   125,   106,   107,   126,   176,   178,
     111,   203,   105,   110,   105,   110,   201,   105,   111,   126,
     216,   214,   104,   288,   291,   293,   178,   283,   178,    49,
     221,   176,   178,   265,   266,   267,   268,   219,   104,   104,
     104,   106,   107,   110,   110,   105,   111,    49,   125,   230,
      37,   231,   236,   238,   110,   161,   110,   161,   163,    66,
     103,   105,   110,    66,    88,    89,   230,   224,   136,   247,
     248,    49,   108,   105,   111,   225,   145,   161,   225,   125,
     206,   209,   270,   207,   209,   278,   198,   207,   206,   111,
     215,   198,   162,   111,   217,   104,   104,   283,   270,   267,
     105,   110,   145,   161,   161,   161,   111,   225,   162,   230,
     103,   163,   104,   104,   104,   111,   247,   222,   111,   233,
     103,   104,   125,   249,   161,   111,    49,   108,   162,   198,
     208,   209,   198,   208,   198,   198,   104,   103,   287,   270,
     108,   111,   111,   125,   161,   110,   230,   230,   230,   104,
     161,   107,   136,   250,   251,   125,   252,   108,   161,   198,
     198,   230,   104,   163,    14,   110,   104,   222,   103,   105,
     107,   136,   253,   254,   125,   255,   108,   110,   104,   230,
     233,   108,   161,   250,   222,   103,   105,   136,   256,   257,
     230,   136,   104,   108,   161,   253,   105,   103,   136,   104,
     256,   161,   103,   104,   161,   104
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


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



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
        case 3:

/* Line 1464 of yacc.c  */
#line 169 "parser.y"
    {
	  ansi_c_declarationt ansi_c_declaration;
	  ansi_c_declaration.value()=stack((yyvsp[(2) - (2)]));
	  PARSER.copy_item(ansi_c_declaration);
	}
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 175 "parser.y"
    {
	  ansi_c_declarationt ansi_c_declaration;
	  ansi_c_declaration.type()=
	    static_cast<const typet &>(static_cast<const irept &>(stack((yyvsp[(2) - (2)]))));
	  ansi_c_declaration.set_is_type(true);
	  PARSER.copy_item(ansi_c_declaration);
	}
    break;

  case 16:

/* Line 1464 of yacc.c  */
#line 224 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]);
	  // do concatenation
	  concatenate_strings(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])));
	}
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 236 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 25:

/* Line 1464 of yacc.c  */
#line 246 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (6)]);
	  stack((yyval)).id(ID_gcc_builtin_va_arg);
	  mto((yyval), (yyvsp[(3) - (6)]));
	  stack((yyval)).type().swap(stack((yyvsp[(5) - (6)])));
	}
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 254 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyval)).id(ID_gcc_builtin_types_compatible_p);
          irept::subt &subtypes=stack((yyval)).add(ID_subtypes).get_sub();
          subtypes.resize(2);
          subtypes[0].swap(stack((yyvsp[(3) - (6)])));
          subtypes[1].swap(stack((yyvsp[(5) - (6)])));
        }
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 266 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (6)]);
	  stack((yyval)).id(ID_builtin_offsetof);
	  stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (6)])));
	  stack((yyval)).add(ID_designator).swap(stack((yyvsp[(5) - (6)])));
	}
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 276 "parser.y"
    {
          init((yyval), ID_designated_initializer);
          stack((yyval)).operands().resize(1);
          stack((yyval)).op0().id(ID_member);
          stack((yyval)).op0().location()=stack((yyvsp[(1) - (1)])).location();
	  stack((yyval)).op0().set(ID_component_name, stack((yyvsp[(1) - (1)])).get(ID_C_base_name));
        }
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 284 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
	  set((yyvsp[(2) - (3)]), ID_member);
          stack((yyvsp[(2) - (3)])).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
	  mto((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 291 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
	  set((yyvsp[(2) - (4)]), ID_index);
	  mto((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]));
	  mto((yyval), (yyvsp[(2) - (4)]));
        }
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 300 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]);
	  set((yyval), ID_builtin_alignof);
	  mto((yyval), (yyvsp[(3) - (4)]));
	}
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 305 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          stack((yyval)).id(ID_builtin_alignof);
	  stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 314 "parser.y"
    {
          //unsigned prefix=PARSER.current_scope().compound_counter;
          init((yyval));
          exprt s=stack((yyvsp[(5) - (8)])); // save
          PARSER.new_declaration(stack((yyvsp[(4) - (8)])), stack((yyvsp[(5) - (8)])), stack((yyval)));
          stack((yyval)).id(ID_forall);
	  stack((yyval)).location()=stack((yyvsp[(1) - (8)])).location();
          stack((yyval)).move_to_operands(s);
          mto((yyval), (yyvsp[(7) - (8)]));
          exprt blah=stack((yyval));
          PARSER.pop_scope();
        }
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 327 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (8)]);
          stack((yyval)).id(ID_exists);     
	  stack((yyval)).location()=stack((yyvsp[(1) - (8)])).location();
          mto((yyval), (yyvsp[(4) - (8)]));
          stack((yyval)).operands()[0].type() = stack((yyvsp[(3) - (8)])).type();
          mto((yyval), (yyvsp[(6) - (8)])); 
          PARSER.pop_scope();
        }
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 339 "parser.y"
    { init((yyval), ID_sideeffect);
	  stack((yyval)).set(ID_statement, ID_statement_expression);
	  stack((yyval)).location()=stack((yyvsp[(1) - (3)])).location();
          mto((yyval), (yyvsp[(2) - (3)]));
	}
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 349 "parser.y"
    { binary((yyval), (yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), ID_index, (yyvsp[(3) - (4)])); }
    break;

  case 38:

/* Line 1464 of yacc.c  */
#line 351 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]);
	  set((yyval), ID_sideeffect);
	  stack((yyval)).operands().resize(2);
	  stack((yyval)).op0().swap(stack((yyvsp[(1) - (3)])));
	  stack((yyval)).op1().clear();
	  stack((yyval)).op1().id(ID_arguments);
	  stack((yyval)).set(ID_statement, ID_function_call);
	}
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 360 "parser.y"
    { (yyval)=(yyvsp[(2) - (4)]);
	  locationt location=stack((yyvsp[(2) - (4)])).location();
	  init((yyval), ID_sideeffect);
	  stack((yyval)).set(ID_statement, ID_function_call);
	  stack((yyval)).operands().resize(2);
	  stack((yyval)).op0().swap(stack((yyvsp[(1) - (4)])));
	  stack((yyval)).op1().swap(stack((yyvsp[(3) - (4)])));
	  stack((yyval)).op1().id(ID_arguments);
	  stack((yyval)).location()=location;
	}
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 371 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]);
	  set((yyval), ID_member);
	  mto((yyval), (yyvsp[(1) - (3)]));
	  stack((yyval)).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
	}
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 377 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]);
	  set((yyval), ID_ptrmember);
	  mto((yyval), (yyvsp[(1) - (3)]));
	  stack((yyval)).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
	}
    break;

  case 42:

/* Line 1464 of yacc.c  */
#line 383 "parser.y"
    { (yyval)=(yyvsp[(2) - (2)]);
	  locationt location=stack((yyvsp[(2) - (2)])).location();
	  init((yyval), ID_sideeffect);
	  mto((yyval), (yyvsp[(1) - (2)]));
	  stack((yyval)).set(ID_statement, ID_postincrement);
	  stack((yyval)).location()=location;
	}
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 391 "parser.y"
    { (yyval)=(yyvsp[(2) - (2)]);
	  locationt location=stack((yyvsp[(2) - (2)])).location();
	  init((yyval), ID_sideeffect);
	  mto((yyval), (yyvsp[(1) - (2)]));
	  stack((yyval)).set(ID_statement, ID_postdecrement);
	  stack((yyval)).location()=location;
	}
    break;

  case 46:

/* Line 1464 of yacc.c  */
#line 407 "parser.y"
    {
	  init((yyval), ID_expression_list);
	  mto((yyval), (yyvsp[(1) - (1)]));
	}
    break;

  case 47:

/* Line 1464 of yacc.c  */
#line 412 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  mto((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 421 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_sideeffect);
	  stack((yyval)).set(ID_statement, ID_preincrement);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 50:

/* Line 1464 of yacc.c  */
#line 427 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_sideeffect);
	  stack((yyval)).set(ID_statement, ID_predecrement);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 433 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_address_of);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 438 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_address_of);
	  stack((yyval)).operands().resize(1);
	  stack((yyval)).op0()=stack((yyvsp[(2) - (2)]));
	  stack((yyval)).op0().id(ID_label);
	  stack((yyval)).op0().set(ID_identifier, stack((yyvsp[(2) - (2)])).get(ID_C_base_name));
	}
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 446 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_dereference);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 451 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_unary_plus);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 456 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_unary_minus);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 461 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_bitnot);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 466 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_not);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 471 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_sizeof);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 476 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]);
	  set((yyval), ID_sizeof);
	  stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (4)])));
	}
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 481 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_complex_real);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 486 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_complex_imag);
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 495 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (4)]);
	  set((yyval), ID_typecast);
	  mto((yyval), (yyvsp[(4) - (4)]));
	  stack((yyval)).type().swap(stack((yyvsp[(2) - (4)])));
	}
    break;

  case 64:

/* Line 1464 of yacc.c  */
#line 505 "parser.y"
    {
	  exprt tmp(ID_initializer_list);
	  tmp.location()=stack((yyvsp[(4) - (6)])).location();
	  tmp.operands().swap(stack((yyvsp[(5) - (6)])).operands());
	  (yyval)=(yyvsp[(1) - (6)]);
	  set((yyval), ID_typecast);
	  stack((yyval)).move_to_operands(tmp);
	  stack((yyval)).type().swap(stack((yyvsp[(2) - (6)])));
	}
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 515 "parser.y"
    {
	  // same as above
	  exprt tmp(ID_initializer_list);
	  tmp.location()=stack((yyvsp[(4) - (7)])).location();
	  tmp.operands().swap(stack((yyvsp[(5) - (7)])).operands());
	  (yyval)=(yyvsp[(1) - (7)]);
	  set((yyval), ID_typecast);
	  stack((yyval)).move_to_operands(tmp);
	  stack((yyval)).type().swap(stack((yyvsp[(2) - (7)])));
	}
    break;

  case 67:

/* Line 1464 of yacc.c  */
#line 530 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_mult, (yyvsp[(3) - (3)])); }
    break;

  case 68:

/* Line 1464 of yacc.c  */
#line 532 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_div, (yyvsp[(3) - (3)])); }
    break;

  case 69:

/* Line 1464 of yacc.c  */
#line 534 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_mod, (yyvsp[(3) - (3)])); }
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 540 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_plus, (yyvsp[(3) - (3)])); }
    break;

  case 72:

/* Line 1464 of yacc.c  */
#line 542 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_minus, (yyvsp[(3) - (3)])); }
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 548 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_shl, (yyvsp[(3) - (3)])); }
    break;

  case 75:

/* Line 1464 of yacc.c  */
#line 550 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_shr, (yyvsp[(3) - (3)])); }
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 556 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_lt, (yyvsp[(3) - (3)])); }
    break;

  case 78:

/* Line 1464 of yacc.c  */
#line 558 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_gt, (yyvsp[(3) - (3)])); }
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 560 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_le, (yyvsp[(3) - (3)])); }
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 562 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_ge, (yyvsp[(3) - (3)])); }
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 568 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_equal, (yyvsp[(3) - (3)])); }
    break;

  case 83:

/* Line 1464 of yacc.c  */
#line 570 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_notequal, (yyvsp[(3) - (3)])); }
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 576 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_bitand, (yyvsp[(3) - (3)])); }
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 582 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_bitxor, (yyvsp[(3) - (3)])); }
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 588 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_bitor, (yyvsp[(3) - (3)])); }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 594 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_and, (yyvsp[(3) - (3)])); }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 600 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_or, (yyvsp[(3) - (3)])); }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 606 "parser.y"
    { (yyval)=(yyvsp[(2) - (5)]);
	  stack((yyval)).id(ID_if);
	  mto((yyval), (yyvsp[(1) - (5)]));
	  mto((yyval), (yyvsp[(3) - (5)]));
	  mto((yyval), (yyvsp[(5) - (5)]));
	}
    break;

  case 96:

/* Line 1464 of yacc.c  */
#line 613 "parser.y"
    { (yyval)=(yyvsp[(2) - (4)]);
	  stack((yyval)).id(ID_sideeffect);
	  stack((yyval)).set(ID_statement, ID_gcc_conditional_expression);
	  mto((yyval), (yyvsp[(1) - (4)]));
	  mto((yyval), (yyvsp[(4) - (4)]));
	}
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 624 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign); }
    break;

  case 99:

/* Line 1464 of yacc.c  */
#line 626 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_mult); }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 628 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_div); }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 630 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_mod); }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 632 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_plus); }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 634 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_minus); }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 636 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_shl); }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 638 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_shr); }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 640 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_bitand); }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 642 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_bitxor); }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 644 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_bitor); }
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 650 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_comma, (yyvsp[(3) - (3)])); }
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 659 "parser.y"
    { init((yyval)); stack((yyval)).make_nil(); }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 667 "parser.y"
    {
	  // type only, no identifier!
	  codet decl(ID_decl_type);
	  decl.add(ID_type_arg).swap(stack((yyvsp[(1) - (2)])));
	  init((yyval));
	  stack((yyval)).move_to_operands(decl);
	}
    break;

  case 115:

/* Line 1464 of yacc.c  */
#line 675 "parser.y"
    {
	  // type only, no identifier!
	  codet decl(ID_decl_type);
	  decl.add(ID_type_arg).swap(stack((yyvsp[(1) - (2)])));
	  init((yyval));
	  stack((yyval)).move_to_operands(decl);
	}
    break;

  case 118:

/* Line 1464 of yacc.c  */
#line 688 "parser.y"
    {
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 119:

/* Line 1464 of yacc.c  */
#line 694 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (4)]));
          decl_statement((yyval), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
        }
    break;

  case 120:

/* Line 1464 of yacc.c  */
#line 700 "parser.y"
    {
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 706 "parser.y"
    {
	  init((yyval));
	  stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (4)]));
	  decl_statement((yyval), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
	}
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 712 "parser.y"
    {
            init((yyval));
            const irept &t=stack((yyvsp[(1) - (3)])).find(ID_type);
            PARSER.new_declaration(t, stack((yyvsp[(3) - (3)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 719 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (5)]);
	  decl_statement((yyval), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
	}
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 727 "parser.y"
    {
        }
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 740 "parser.y"
    {
            // the symbol has to be visible during initialization
            merge_types((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (4)])), stack((yyvsp[(2) - (4)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 748 "parser.y"
    {
	  init((yyval));
	  stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (6)])); // save for later
	  decl_statement((yyval), (yyvsp[(5) - (6)]), (yyvsp[(6) - (6)]));
	}
    break;

  case 129:

/* Line 1464 of yacc.c  */
#line 756 "parser.y"
    {
            // the symbol has to be visible during initialization
            merge_types((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (4)])), stack((yyvsp[(2) - (4)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 130:

/* Line 1464 of yacc.c  */
#line 764 "parser.y"
    {
	  init((yyval));
	  stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (6)])); // save for later
	  decl_statement((yyval), (yyvsp[(5) - (6)]), (yyvsp[(6) - (6)]));
	}
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 772 "parser.y"
    {
            init((yyval));
            irept t=stack((yyvsp[(1) - (5)])).find(ID_type);
            merge_types(t, stack((yyvsp[(4) - (5)])));
            PARSER.new_declaration(t, stack((yyvsp[(3) - (5)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 780 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (7)]);
	  decl_statement((yyval), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
	}
    break;

  case 142:

/* Line 1464 of yacc.c  */
#line 803 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 144:

/* Line 1464 of yacc.c  */
#line 809 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 145:

/* Line 1464 of yacc.c  */
#line 814 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 147:

/* Line 1464 of yacc.c  */
#line 823 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 830 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 842 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_const); }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 843 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_volatile); }
    break;

  case 153:

/* Line 1464 of yacc.c  */
#line 844 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_ptr32); }
    break;

  case 154:

/* Line 1464 of yacc.c  */
#line 845 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_ptr64); }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 850 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	}
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 855 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	}
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 860 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	}
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 865 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	}
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 873 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
        }
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 877 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	}
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 882 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 887 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	}
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 896 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 901 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 906 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 916 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 921 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 929 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	  merge_types((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 935 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	  merge_types((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 171:

/* Line 1464 of yacc.c  */
#line 941 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	  merge_types((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 950 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	  merge_types((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 956 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	  merge_types((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 962 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	  merge_types((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 971 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 976 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	  merge_types((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 982 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  merge_types((yyval), (yyvsp[(2) - (3)]));
	  merge_types((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 991 "parser.y"
    { (yyval) = (yyvsp[(1) - (4)]);
	  stack((yyval)).id(ID_typeof);
	  mto((yyval), (yyvsp[(3) - (4)]));
	}
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 996 "parser.y"
    { (yyval) = (yyvsp[(1) - (4)]);
	  stack((yyval)).id(ID_typeof);
	  stack((yyval)).set(ID_type_arg, stack((yyvsp[(3) - (4)])));
	}
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 1005 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  merge_types((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 1045 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_typedef); }
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 1046 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_extern); }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 1047 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_static); }
    break;

  case 185:

/* Line 1464 of yacc.c  */
#line 1048 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_auto); }
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 1049 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_register); }
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 1050 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_inline); }
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 1051 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_thread_local); }
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 1052 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_asm); }
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 1056 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int); }
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 1057 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int8); }
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 1058 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int16); }
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 1059 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int32); }
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 1060 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int64); }
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1061 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_char); }
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1062 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_short); }
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1063 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_long); }
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1064 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_float); }
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1065 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_double); }
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1066 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_signed); }
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1067 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_unsigned); }
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1068 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_void); }
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1069 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_bool); }
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 1070 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_complex); }
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1072 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_bv);
          stack((yyval)).add(ID_size).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1087 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]); ((typet &)stack((yyval))).subtype().swap(stack((yyvsp[(2) - (4)]))); }
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1093 "parser.y"
    {
            // an anon struct/union
            exprt symbol(ID_symbol);
            symbol.set(ID_C_base_name, PARSER.get_anon_name());

            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), symbol, stack((yyval)), true);
          }
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1103 "parser.y"
    {
	  typet &type=to_ansi_c_declaration(stack((yyvsp[(3) - (7)]))).type();
	  type.add(ID_components).get_sub().swap(
	    stack((yyvsp[(5) - (7)])).add(ID_operands).get_sub());

          // throw in the gcc attributes
          merge_types(type, stack((yyvsp[(2) - (7)])));
          merge_types(type, stack((yyvsp[(7) - (7)])));

	  // grab symbol
	  init((yyval), ID_symbol);
	  stack((yyval)).set(ID_identifier, to_ansi_c_declaration(stack((yyvsp[(3) - (7)]))).get_name());
	  stack((yyval)).location()=to_ansi_c_declaration(stack((yyvsp[(3) - (7)]))).location();
	  PARSER.copy_item(to_ansi_c_declaration(stack((yyvsp[(3) - (7)]))));
	}
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1121 "parser.y"
    {
            // a struct/union with tag
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(3) - (3)])), stack((yyval)), true);
            
            // announce the tag before the members
            ansi_c_declarationt tmp=to_ansi_c_declaration(stack((yyval))); // copy!
            tmp.type().id("incomplete_"+stack((yyvsp[(1) - (3)])).id_string());
            assert(tmp.id()==ID_declaration);
            PARSER.copy_item(tmp);            
          }
    break;

  case 213:

/* Line 1464 of yacc.c  */
#line 1134 "parser.y"
    {
	  typet &type=stack((yyvsp[(4) - (8)])).type();
	  type.add(ID_components).get_sub().swap(
	    stack((yyvsp[(6) - (8)])).add(ID_operands).get_sub());

          // throw in the gcc attributes
          merge_types(type, stack((yyvsp[(2) - (8)])));
          merge_types(type, stack((yyvsp[(8) - (8)])));

	  // grab symbol
	  init((yyval), ID_symbol);
	  stack((yyval)).set(ID_identifier, stack((yyvsp[(4) - (8)])).get(ID_name));
	  stack((yyval)).location()=stack((yyvsp[(4) - (8)])).location();
	  PARSER.copy_item(to_ansi_c_declaration(stack((yyvsp[(4) - (8)]))));
	}
    break;

  case 214:

/* Line 1464 of yacc.c  */
#line 1153 "parser.y"
    {
	  do_tag((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
	  (yyval)=(yyvsp[(3) - (4)]);
	  merge_types((yyval), (yyvsp[(2) - (4)]));
	  merge_types((yyval), (yyvsp[(4) - (4)]));
	}
    break;

  case 215:

/* Line 1464 of yacc.c  */
#line 1163 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_struct); }
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1165 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_union); }
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1170 "parser.y"
    {
          init((yyval));
        }
    break;

  case 220:

/* Line 1464 of yacc.c  */
#line 1179 "parser.y"
    {
          merge_types((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 221:

/* Line 1464 of yacc.c  */
#line 1186 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); set((yyval), ID_packed); }
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1188 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); set((yyval), ID_transparent_union); }
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1190 "parser.y"
    { (yyval)=(yyvsp[(1) - (5)]); set((yyval), ID_vector); stack((yyval)).add(ID_size)=stack((yyvsp[(3) - (5)])); }
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1192 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); set((yyval), ID_aligned); }
    break;

  case 225:

/* Line 1464 of yacc.c  */
#line 1194 "parser.y"
    { (yyval)=(yyvsp[(1) - (5)]); set((yyval), ID_aligned); mto((yyval), (yyvsp[(3) - (5)])); }
    break;

  case 226:

/* Line 1464 of yacc.c  */
#line 1199 "parser.y"
    {
	  init((yyval), ID_declaration_list);
	}
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 1208 "parser.y"
    {
	  assert(stack((yyvsp[(1) - (2)])).id()==ID_declaration_list);
	  assert(stack((yyvsp[(2) - (2)])).id()==ID_declaration_list);
	  (yyval)=(yyvsp[(1) - (2)]);
	  Forall_operands(it, stack((yyvsp[(2) - (2)])))
	    stack((yyval)).move_to_operands(*it);
	  stack((yyvsp[(2) - (2)])).clear();
	}
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 1222 "parser.y"
    {
	  init((yyval), ID_declaration_list);
	}
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 1230 "parser.y"
    {
	  init((yyval), ID_declaration_list);

	  exprt declaration;
	  PARSER.new_declaration(stack((yyvsp[(2) - (3)])), stack((yyvsp[(3) - (3)])), declaration, false, false);

	  stack((yyval)).move_to_operands(declaration);
	}
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 1239 "parser.y"
    {
	  exprt declaration;
	  PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(3) - (3)])), declaration, false, false);

	  (yyval)=(yyvsp[(1) - (3)]);
	  stack((yyval)).move_to_operands(declaration);
	}
    break;

  case 235:

/* Line 1464 of yacc.c  */
#line 1251 "parser.y"
    {
	  init((yyval), ID_declaration_list);

	  // save the type_specifier for later
	  stack((yyval)).add(ID_type)=stack((yyvsp[(2) - (3)]));

	  exprt declaration;
	  PARSER.new_declaration(stack((yyvsp[(2) - (3)])), stack((yyvsp[(3) - (3)])), declaration, false, false);

	  stack((yyval)).move_to_operands(declaration);
	}
    break;

  case 236:

/* Line 1464 of yacc.c  */
#line 1263 "parser.y"
    {
	  exprt declaration;

	  irept declaration_type=stack((yyvsp[(1) - (3)])).find(ID_type);
	  PARSER.new_declaration(declaration_type, stack((yyvsp[(3) - (3)])), declaration, false, false);

	  (yyval)=(yyvsp[(1) - (3)]);
	  stack((yyval)).move_to_operands(declaration);
	}
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 1276 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);

	  if(stack((yyvsp[(2) - (3)])).is_not_nil())
	    make_subtype((yyval), (yyvsp[(2) - (3)]));
	}
    break;

  case 238:

/* Line 1464 of yacc.c  */
#line 1283 "parser.y"
    {
	  init((yyval), ID_abstract);
	}
    break;

  case 239:

/* Line 1464 of yacc.c  */
#line 1287 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	}
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 1295 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  make_subtype((yyval), (yyvsp[(2) - (3)]));
	}
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 1300 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	}
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 1308 "parser.y"
    {
	  init((yyval), ID_nil);
	}
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 1316 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_c_bitfield);
	  stack((yyval)).set(ID_size, stack((yyvsp[(2) - (2)])));
	  stack((yyval)).add(ID_subtype).id(ID_abstract);
	}
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 1327 "parser.y"
    {
            // an anon enum, we want that to be visible before the
            // members
            exprt symbol(ID_symbol);
            symbol.set(ID_C_base_name, PARSER.get_anon_name());

            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), symbol, stack((yyval)), true);
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 1339 "parser.y"
    {
	  // grab symbol
	  init((yyval), ID_symbol);
	  stack((yyval)).set(ID_identifier, stack((yyvsp[(3) - (7)])).get(ID_name));
	  stack((yyval)).location()=stack((yyvsp[(3) - (7)])).location();

	  do_enum_members((const typet &)stack((yyval)), stack((yyvsp[(5) - (7)])));
	}
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 1350 "parser.y"
    {
            // we want the tag to be visible before the members
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(3) - (3)])), stack((yyval)), true);
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 1358 "parser.y"
    {
	  // grab symbol
	  init((yyval), ID_symbol);
	  stack((yyval)).set(ID_identifier, stack((yyvsp[(4) - (8)])).get(ID_name));
	  stack((yyval)).location()=stack((yyvsp[(4) - (8)])).location();

	  do_enum_members((const typet &)stack((yyval)), stack((yyvsp[(6) - (8)])));
	}
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 1369 "parser.y"
    {
	  do_tag((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
	  (yyval)=(yyvsp[(3) - (3)]);
	}
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 1376 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (1)]);
	  set((yyval), ID_c_enum);
	}
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 1384 "parser.y"
    {
	  init((yyval));
	  mto((yyval), (yyvsp[(1) - (1)]));
	}
    break;

  case 252:

/* Line 1464 of yacc.c  */
#line 1389 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  mto((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 1394 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	}
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 1401 "parser.y"
    {
	  init((yyval));
	  irept type(ID_c_enum);
	  PARSER.new_declaration(type, stack((yyvsp[(1) - (2)])), stack((yyval)));
	  stack((yyval)).set(ID_is_macro, true);
	  stack((yyval)).add(ID_value).swap(stack((yyvsp[(2) - (2)])));
	}
    break;

  case 255:

/* Line 1464 of yacc.c  */
#line 1412 "parser.y"
    {
	  init((yyval));
	  stack((yyval)).make_nil();
	}
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 1417 "parser.y"
    {
	  (yyval)=(yyvsp[(2) - (2)]);
	}
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1425 "parser.y"
    {
	  typet tmp(ID_ellipsis);
	  (yyval)=(yyvsp[(1) - (3)]);
	  ((typet &)stack((yyval))).move_to_subtypes(tmp);
	}
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1434 "parser.y"
    {
          init((yyval), ID_arguments);
          mts((yyval), (yyvsp[(1) - (1)]));
	}
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1439 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mts((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1446 "parser.y"
    {
          init((yyval));
	  irept type(ID_KnR);
	  PARSER.new_declaration(type, stack((yyvsp[(1) - (1)])), stack((yyval)));
	}
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1455 "parser.y"
    {
	  init((yyval), ID_arguments);
	  mts((yyval), (yyvsp[(1) - (1)]));
	}
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1460 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  mts((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1468 "parser.y"
    {
	  init((yyval));
	  exprt declarator=exprt(ID_abstract);
	  PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
	}
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1474 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 266:

/* Line 1464 of yacc.c  */
#line 1479 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1484 "parser.y"
    {
          // the second tree is really the argument -- not part
          // of the type!
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1491 "parser.y"
    {
	  init((yyval));
	  exprt declarator=exprt(ID_abstract);
	  PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
	}
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1497 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1502 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1507 "parser.y"
    {
	  init((yyval));
	  exprt declarator=exprt(ID_abstract);
	  PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
	}
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1513 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 1518 "parser.y"
    {
	  init((yyval));
	  stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 1524 "parser.y"
    {
          // the second tree is really the argument -- not part
          // of the type!
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 1531 "parser.y"
    {
	  init((yyval));
	  exprt declarator=exprt(ID_abstract);
	  PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
	}
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 1537 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 1542 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	}
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 1556 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  make_subtype((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 1562 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  make_subtype((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 1570 "parser.y"
    {
	  newstack((yyval));
	  stack((yyval)).make_nil();
	}
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 1575 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 288:

/* Line 1464 of yacc.c  */
#line 1587 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  set((yyval), ID_initializer_list);
	  stack((yyval)).operands().swap(stack((yyvsp[(2) - (3)])).operands());
	}
    break;

  case 289:

/* Line 1464 of yacc.c  */
#line 1593 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (4)]);
	  set((yyval), ID_initializer_list);
	  stack((yyval)).operands().swap(stack((yyvsp[(2) - (4)])).operands());
	}
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 1602 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (1)]);
	  exprt tmp;
	  tmp.swap(stack((yyval)));
	  stack((yyval)).clear();
	  stack((yyval)).move_to_operands(tmp);
	}
    break;

  case 291:

/* Line 1464 of yacc.c  */
#line 1610 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  mto((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 1619 "parser.y"
    {
	  init((yyval));
	  set((yyval), ID_initializer_list);
	  stack((yyval)).operands().clear();
	}
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 1629 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (3)]);
          stack((yyval)).id(ID_designated_initializer);
          stack((yyval)).add(ID_designator).swap(stack((yyvsp[(1) - (3)])));
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 295:

/* Line 1464 of yacc.c  */
#line 1636 "parser.y"
    {
          // yet another GCC speciality
          (yyval)=(yyvsp[(2) - (3)]);
          stack((yyval)).id(ID_designated_initializer);
          exprt designator;
          exprt member(ID_member);
          member.set(ID_component_name, stack((yyvsp[(1) - (3)])).get(ID_C_base_name));
          designator.move_to_operands(member);
          stack((yyval)).add(ID_designator).swap(designator);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 296:

/* Line 1464 of yacc.c  */
#line 1651 "parser.y"
    {
          init((yyval));
          stack((yyvsp[(1) - (2)])).id(ID_member);
          stack((yyvsp[(1) - (2)])).set(ID_component_name, stack((yyvsp[(2) - (2)])).get(ID_C_base_name));
          mto((yyval), (yyvsp[(1) - (2)]));
        }
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 1658 "parser.y"
    {
          init((yyval));
          stack((yyvsp[(1) - (3)])).id(ID_index);
          mto((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
          mto((yyval), (yyvsp[(1) - (3)]));
        }
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 1665 "parser.y"
    {
          // TODO
          init((yyval));
          stack((yyvsp[(1) - (5)])).id(ID_index);
          mto((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]));
          mto((yyval), (yyvsp[(1) - (5)]));
        }
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 1673 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          stack((yyvsp[(2) - (4)])).id(ID_index);
          mto((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]));
          mto((yyval), (yyvsp[(2) - (4)]));
        }
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 1680 "parser.y"
    {
          // TODO
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyvsp[(2) - (6)])).id(ID_index);
          mto((yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]));
          mto((yyval), (yyvsp[(2) - (6)]));
        }
    break;

  case 301:

/* Line 1464 of yacc.c  */
#line 1688 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          stack((yyvsp[(2) - (3)])).id(ID_member);
          stack((yyvsp[(2) - (3)])).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
          mto((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 313:

/* Line 1464 of yacc.c  */
#line 1714 "parser.y"
    {
	  init((yyval));
	  statement((yyval), ID_decl_block);
	  stack((yyval)).operands().swap(stack((yyvsp[(1) - (1)])).operands());
	}
    break;

  case 314:

/* Line 1464 of yacc.c  */
#line 1723 "parser.y"
    {
	  (yyval)=(yyvsp[(2) - (3)]);
	  statement((yyval), ID_label);
	  stack((yyval)).set(ID_label, stack((yyvsp[(1) - (3)])).get(ID_C_base_name));
	  mto((yyval), (yyvsp[(3) - (3)]));
	}
    break;

  case 315:

/* Line 1464 of yacc.c  */
#line 1730 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (4)]);
	  statement((yyval), ID_label);
	  mto((yyval), (yyvsp[(4) - (4)]));
	  static_cast<exprt &>(stack((yyval)).add(ID_case)).
		move_to_operands(stack((yyvsp[(2) - (4)])));
	}
    break;

  case 316:

/* Line 1464 of yacc.c  */
#line 1738 "parser.y"
    {
	  // this is a GCC extension
	  (yyval)=(yyvsp[(1) - (6)]);
	  statement((yyval), ID_label);
	  mto((yyval), (yyvsp[(6) - (6)]));
	  static_cast<exprt &>(stack((yyval)).add(ID_case)).
		move_to_operands(stack((yyvsp[(2) - (6)])));
          // TODO -- the other one
	}
    break;

  case 317:

/* Line 1464 of yacc.c  */
#line 1748 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  statement((yyval), ID_label);
	  mto((yyval), (yyvsp[(3) - (3)]));
	  stack((yyval)).set(ID_default, true);
	}
    break;

  case 318:

/* Line 1464 of yacc.c  */
#line 1762 "parser.y"
    {
	  (yyval)=(yyvsp[(2) - (3)]);
	  statement((yyval), ID_block);
	  stack((yyval)).set(ID_C_end_location, stack((yyvsp[(3) - (3)])).location());
	  PARSER.pop_scope();
	}
    break;

  case 319:

/* Line 1464 of yacc.c  */
#line 1769 "parser.y"
    {
	  (yyval)=(yyvsp[(3) - (4)]);
	  stack((yyval)).location()=stack((yyvsp[(2) - (4)])).location();
	  stack((yyval)).set(ID_C_end_location, stack((yyvsp[(4) - (4)])).location());
	  PARSER.pop_scope();
	}
    break;

  case 320:

/* Line 1464 of yacc.c  */
#line 1776 "parser.y"
    {
	  init((yyval));
	  stack((yyval)).location()=stack((yyvsp[(2) - (4)])).location();
	  stack((yyval)).set(ID_statement, ID_asm);
	  mto((yyval), (yyvsp[(3) - (4)]));
	  PARSER.pop_scope();
	}
    break;

  case 321:

/* Line 1464 of yacc.c  */
#line 1787 "parser.y"
    {
	  unsigned prefix=++PARSER.current_scope().compound_counter;
	  PARSER.new_scope(i2string(prefix)+"::");
	}
    break;

  case 322:

/* Line 1464 of yacc.c  */
#line 1795 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (1)]);
	  to_code(stack((yyval))).make_block();
	}
    break;

  case 323:

/* Line 1464 of yacc.c  */
#line 1800 "parser.y"
    {
	  mto((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 324:

/* Line 1464 of yacc.c  */
#line 1807 "parser.y"
    {
	  (yyval)=(yyvsp[(2) - (2)]);

	  if(stack((yyvsp[(1) - (2)])).is_nil())
	    statement((yyval), ID_skip);
	  else
	  {
	    statement((yyval), ID_expression);
	    mto((yyval), (yyvsp[(1) - (2)]));
	  }
	}
    break;

  case 325:

/* Line 1464 of yacc.c  */
#line 1822 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (5)]);
	  statement((yyval), ID_ifthenelse);
	  stack((yyval)).operands().reserve(2);
	  mto((yyval), (yyvsp[(3) - (5)]));
	  mto((yyval), (yyvsp[(5) - (5)]));
	}
    break;

  case 326:

/* Line 1464 of yacc.c  */
#line 1830 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (7)]);
	  statement((yyval), ID_ifthenelse);
	  stack((yyval)).operands().reserve(3);
	  mto((yyval), (yyvsp[(3) - (7)]));
	  mto((yyval), (yyvsp[(5) - (7)]));
	  mto((yyval), (yyvsp[(7) - (7)]));
	}
    break;

  case 327:

/* Line 1464 of yacc.c  */
#line 1839 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (5)]);
	  statement((yyval), ID_switch);
	  stack((yyval)).operands().reserve(2);
	  mto((yyval), (yyvsp[(3) - (5)]));
	  mto((yyval), (yyvsp[(5) - (5)]));
	}
    break;

  case 330:

/* Line 1464 of yacc.c  */
#line 1855 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (5)]);
	  statement((yyval), ID_while);
	  stack((yyval)).operands().reserve(2);
	  mto((yyval), (yyvsp[(3) - (5)]));
	  mto((yyval), (yyvsp[(5) - (5)]));
	}
    break;

  case 331:

/* Line 1464 of yacc.c  */
#line 1863 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (7)]);
	  statement((yyval), ID_dowhile);
	  stack((yyval)).operands().reserve(2);
	  mto((yyval), (yyvsp[(5) - (7)]));
	  mto((yyval), (yyvsp[(2) - (7)]));
	}
    break;

  case 332:

/* Line 1464 of yacc.c  */
#line 1872 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (8)]);
	  statement((yyval), ID_for);
	  stack((yyval)).operands().reserve(4);
	  mto((yyval), (yyvsp[(3) - (8)]));
	  mto((yyval), (yyvsp[(4) - (8)]));
	  mto((yyval), (yyvsp[(6) - (8)]));
	  mto((yyval), (yyvsp[(8) - (8)]));
	}
    break;

  case 333:

/* Line 1464 of yacc.c  */
#line 1885 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  if(stack((yyvsp[(2) - (3)])).id()==ID_symbol)
	  {
	    statement((yyval), ID_goto);
	    stack((yyval)).set(ID_destination, stack((yyvsp[(2) - (3)])).get(ID_C_base_name));
          }
          else
          {
            // this is a gcc extension.
            // the original grammar uses identifier_or_typedef_name
	    statement((yyval), "computed-goto");
	    mto((yyval), (yyvsp[(2) - (3)]));
          }
	}
    break;

  case 334:

/* Line 1464 of yacc.c  */
#line 1901 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); statement((yyval), ID_continue); }
    break;

  case 335:

/* Line 1464 of yacc.c  */
#line 1903 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); statement((yyval), ID_break); }
    break;

  case 336:

/* Line 1464 of yacc.c  */
#line 1905 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); statement((yyval), ID_return); }
    break;

  case 337:

/* Line 1464 of yacc.c  */
#line 1907 "parser.y"
    { (yyval)=(yyvsp[(1) - (3)]); statement((yyval), ID_return); mto((yyval), (yyvsp[(2) - (3)])); }
    break;

  case 338:

/* Line 1464 of yacc.c  */
#line 1912 "parser.y"
    { 
	  (yyval)=(yyvsp[(1) - (3)]);
	  statement((yyval), ID_gcc_local_label);
	  stack((yyval)).operands().swap(stack((yyvsp[(2) - (3)])).operands());
        }
    break;

  case 339:

/* Line 1464 of yacc.c  */
#line 1921 "parser.y"
    {
          init((yyval));
          mto((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 340:

/* Line 1464 of yacc.c  */
#line 1926 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mto((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 341:

/* Line 1464 of yacc.c  */
#line 1934 "parser.y"
    { (yyval)=(yyvsp[(1) - (6)]);
	  statement((yyval), ID_asm);
	  stack((yyval)).set(ID_flavor, ID_gcc);
	  stack((yyval)).operands().swap(stack((yyvsp[(4) - (6)])).operands());
        }
    break;

  case 342:

/* Line 1464 of yacc.c  */
#line 1940 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_asm);
	  stack((yyval)).set(ID_flavor, ID_gcc);
	  mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 343:

/* Line 1464 of yacc.c  */
#line 1950 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]);
	  statement((yyval), ID_asm);
	  stack((yyval)).set(ID_flavor, ID_msc);
	  mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 344:

/* Line 1464 of yacc.c  */
#line 1956 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
	  statement((yyval), ID_asm);
	  stack((yyval)).set(ID_flavor, ID_msc);
	  mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 345:

/* Line 1464 of yacc.c  */
#line 1966 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (7)]);
          statement((yyval), ID_msc_try_except);
          mto((yyval), (yyvsp[(2) - (7)]));
          mto((yyval), (yyvsp[(5) - (7)]));
          mto((yyval), (yyvsp[(7) - (7)]));
        }
    break;

  case 346:

/* Line 1464 of yacc.c  */
#line 1975 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_msc_try_finally);
          mto((yyval), (yyvsp[(2) - (4)]));
          mto((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 347:

/* Line 1464 of yacc.c  */
#line 1982 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          statement((yyval), ID_msc_leave);
        }
    break;

  case 350:

/* Line 1464 of yacc.c  */
#line 2002 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (1)]));
          }
    break;

  case 351:

/* Line 1464 of yacc.c  */
#line 2007 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (2)]));
          }
    break;

  case 352:

/* Line 1464 of yacc.c  */
#line 2012 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (3)]));
          }
    break;

  case 353:

/* Line 1464 of yacc.c  */
#line 2017 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (4)]));
          }
    break;

  case 381:

/* Line 1464 of yacc.c  */
#line 2100 "parser.y"
    {
          // the function symbol needs to be visible before any declarations
          // in the body (the following compound_statement)
	  to_ansi_c_declaration(stack((yyvsp[(1) - (1)]))).value().make_nil();
          PARSER.copy_item(to_ansi_c_declaration(stack((yyvsp[(1) - (1)]))));
        }
    break;

  case 382:

/* Line 1464 of yacc.c  */
#line 2107 "parser.y"
    {
	  // we now present the body as initializer
          to_ansi_c_declaration(stack((yyvsp[(1) - (3)]))).value().swap(stack((yyvsp[(3) - (3)])));
          PARSER.copy_item(to_ansi_c_declaration(stack((yyvsp[(1) - (3)]))));
          
          // kill scope
          PARSER.pop_scope();
          PARSER.function=irep_idt();
	}
    break;

  case 384:

/* Line 1464 of yacc.c  */
#line 2124 "parser.y"
    {
          init((yyval));
        }
    break;

  case 386:

/* Line 1464 of yacc.c  */
#line 2132 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
        }
    break;

  case 387:

/* Line 1464 of yacc.c  */
#line 2136 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  Forall_irep(it, stack((yyvsp[(2) - (2)])).get_sub())
            stack((yyval)).move_to_sub(*it);
	}
    break;

  case 389:

/* Line 1464 of yacc.c  */
#line 2162 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (2)])); // save for later
          exprt tmp;
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), tmp);
          stack((yyval)).move_to_sub(tmp);
        }
    break;

  case 390:

/* Line 1464 of yacc.c  */
#line 2170 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          // need to get type from $1
          const irept &t=stack((yyvsp[(1) - (3)])).type();
          exprt tmp;
          PARSER.new_declaration(t, stack((yyvsp[(3) - (3)])), tmp);
          stack((yyval)).move_to_sub(tmp);
        }
    break;

  case 391:

/* Line 1464 of yacc.c  */
#line 2182 "parser.y"
    {
	  init((yyval));
	  irept return_type(ID_int);
	  PARSER.new_declaration(return_type, stack((yyvsp[(1) - (1)])), stack((yyval)));
	  create_function_scope(stack((yyval)));
	}
    break;

  case 392:

/* Line 1464 of yacc.c  */
#line 2189 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	  create_function_scope(stack((yyval)));
	}
    break;

  case 393:

/* Line 1464 of yacc.c  */
#line 2195 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	  create_function_scope(stack((yyval)));
	}
    break;

  case 394:

/* Line 1464 of yacc.c  */
#line 2201 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	  create_function_scope(stack((yyval)));
	}
    break;

  case 395:

/* Line 1464 of yacc.c  */
#line 2207 "parser.y"
    {
	  init((yyval));
	  PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
	  create_function_scope(stack((yyval)));
	}
    break;

  case 401:

/* Line 1464 of yacc.c  */
#line 2227 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  make_subtype((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 404:

/* Line 1464 of yacc.c  */
#line 2237 "parser.y"
    {
	  (yyval)=(yyvsp[(2) - (2)]);
	  do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	}
    break;

  case 405:

/* Line 1464 of yacc.c  */
#line 2242 "parser.y"
    {
	  merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	  (yyval)=(yyvsp[(2) - (3)]);
	  do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
	}
    break;

  case 406:

/* Line 1464 of yacc.c  */
#line 2251 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 407:

/* Line 1464 of yacc.c  */
#line 2253 "parser.y"
    {
	  /* note: this is a pointer ($2) to a function ($4) */
	  /* or an array ($4)! */
	  (yyval)=(yyvsp[(2) - (4)]);
	  make_subtype((yyval), (yyvsp[(4) - (4)]));
	}
    break;

  case 409:

/* Line 1464 of yacc.c  */
#line 2264 "parser.y"
    {
	  (yyval)=(yyvsp[(3) - (4)]);
	  do_pointer((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
	}
    break;

  case 410:

/* Line 1464 of yacc.c  */
#line 2269 "parser.y"
    {
	  // not sure where the type qualifiers belong
	  merge_types((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]));
	  (yyval)=(yyvsp[(2) - (5)]);
	  do_pointer((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]));
	}
    break;

  case 411:

/* Line 1464 of yacc.c  */
#line 2276 "parser.y"
    {
	  (yyval)=(yyvsp[(2) - (2)]);
	  do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	}
    break;

  case 412:

/* Line 1464 of yacc.c  */
#line 2281 "parser.y"
    {
	  merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	  (yyval)=(yyvsp[(2) - (3)]);
	  do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
	}
    break;

  case 413:

/* Line 1464 of yacc.c  */
#line 2290 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 414:

/* Line 1464 of yacc.c  */
#line 2292 "parser.y"
    {	/* note: this is a function ($3) with a typedef name ($2) */
	  (yyval)=(yyvsp[(2) - (4)]);
	  make_subtype((yyval), (yyvsp[(3) - (4)]));
	}
    break;

  case 415:

/* Line 1464 of yacc.c  */
#line 2297 "parser.y"
    {
	  /* note: this is a pointer ($2) to a function ($4) */
	  /* or an array ($4)! */
	  (yyval)=(yyvsp[(2) - (4)]);
	  make_subtype((yyval), (yyvsp[(4) - (4)]));
	}
    break;

  case 417:

/* Line 1464 of yacc.c  */
#line 2308 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 421:

/* Line 1464 of yacc.c  */
#line 2319 "parser.y"
    {
	  (yyval)=(yyvsp[(2) - (2)]);
	  do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	}
    break;

  case 422:

/* Line 1464 of yacc.c  */
#line 2324 "parser.y"
    {
	  // the type_qualifier_list is for the pointer,
	  // and not the identifier_declarator
	  stack((yyvsp[(1) - (3)])).id(ID_pointer);
	  stack((yyvsp[(1) - (3)])).add(ID_subtype)=irept(ID_abstract);
	  merge_types((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)])); // dest=$2
	  make_subtype((yyvsp[(3) - (3)]), (yyvsp[(2) - (3)])); // dest=$3
	  (yyval)=(yyvsp[(3) - (3)]);
	}
    break;

  case 423:

/* Line 1464 of yacc.c  */
#line 2337 "parser.y"
    {
	  /* note: this is a function or array ($2) with name ($1) */
	  (yyval)=(yyvsp[(1) - (2)]);
	  make_subtype((yyval), (yyvsp[(2) - (2)]));
	}
    break;

  case 424:

/* Line 1464 of yacc.c  */
#line 2343 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 425:

/* Line 1464 of yacc.c  */
#line 2345 "parser.y"
    {
	  /* note: this is a pointer ($2) to a function ($4) */
	  /* or an array ($4)! */
	  (yyval)=(yyvsp[(2) - (4)]);
	  make_subtype((yyval), (yyvsp[(4) - (4)]));
	}
    break;

  case 427:

/* Line 1464 of yacc.c  */
#line 2356 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 434:

/* Line 1464 of yacc.c  */
#line 2373 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_code);
	  stack((yyval)).add(ID_arguments);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	}
    break;

  case 435:

/* Line 1464 of yacc.c  */
#line 2380 "parser.y"
    {
            unsigned prefix=++PARSER.current_scope().compound_counter;
            PARSER.new_scope(i2string(prefix)+"::");
	  }
    break;

  case 436:

/* Line 1464 of yacc.c  */
#line 2386 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (4)]);
	  set((yyval), ID_code);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	  stack((yyval)).add(ID_arguments).get_sub().
	    swap(stack((yyvsp[(3) - (4)])).add(ID_subtypes).get_sub());
	  PARSER.pop_scope();
	}
    break;

  case 437:

/* Line 1464 of yacc.c  */
#line 2396 "parser.y"
    {
            unsigned prefix=++PARSER.current_scope().compound_counter;
            PARSER.new_scope(i2string(prefix)+"::");
	  }
    break;

  case 438:

/* Line 1464 of yacc.c  */
#line 2403 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (5)]);
	  set((yyval), ID_code);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	  stack((yyval)).add(ID_arguments).get_sub().
	    swap(stack((yyvsp[(3) - (5)])).add(ID_subtypes).get_sub());
	  PARSER.pop_scope();
	  adjust_KnR_arguments(stack((yyval)).add(ID_arguments), stack((yyvsp[(5) - (5)])));
        }
    break;

  case 440:

/* Line 1464 of yacc.c  */
#line 2417 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_code);
	  stack((yyval)).add(ID_arguments);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	}
    break;

  case 441:

/* Line 1464 of yacc.c  */
#line 2424 "parser.y"
    {
            unsigned prefix=++PARSER.current_scope().compound_counter;
            PARSER.new_scope(i2string(prefix)+"::");
	  }
    break;

  case 442:

/* Line 1464 of yacc.c  */
#line 2430 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (4)]);
	  set((yyval), ID_code);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	  stack((yyval)).add(ID_arguments).get_sub().
	    swap(stack((yyvsp[(3) - (4)])).add(ID_subtypes).get_sub());
	  PARSER.pop_scope();
	}
    break;

  case 443:

/* Line 1464 of yacc.c  */
#line 2442 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (2)]);
	  set((yyval), ID_incomplete_array);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	}
    break;

  case 444:

/* Line 1464 of yacc.c  */
#line 2448 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  set((yyval), ID_incomplete_array);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	}
    break;

  case 445:

/* Line 1464 of yacc.c  */
#line 2454 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (3)]);
	  set((yyval), ID_array);
	  stack((yyval)).add(ID_size).swap(stack((yyvsp[(2) - (3)])));
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	}
    break;

  case 446:

/* Line 1464 of yacc.c  */
#line 2461 "parser.y"
    {
	  // we need to push this down
	  (yyval)=(yyvsp[(1) - (4)]);
	  set((yyvsp[(2) - (4)]), ID_array);
	  stack((yyvsp[(2) - (4)])).add(ID_size).swap(stack((yyvsp[(3) - (4)])));
	  stack((yyvsp[(2) - (4)])).add(ID_subtype)=irept(ID_abstract);
	  make_subtype((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]));
	}
    break;

  case 447:

/* Line 1464 of yacc.c  */
#line 2473 "parser.y"
    {
	  (yyval)=(yyvsp[(1) - (1)]);
	  set((yyval), ID_pointer);
	  stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	}
    break;

  case 448:

/* Line 1464 of yacc.c  */
#line 2479 "parser.y"
    {
	  // tye type_qualifier_list belongs to the pointer,
	  // not to the (missing) abstract declarator
	  (yyval)=(yyvsp[(2) - (2)]);
	  exprt declarator=exprt(ID_abstract);
	  merge_types(stack((yyvsp[(2) - (2)])), declarator);
	  do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	}
    break;

  case 449:

/* Line 1464 of yacc.c  */
#line 2488 "parser.y"
    {
	  (yyval)=(yyvsp[(2) - (2)]);
	  do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	}
    break;

  case 450:

/* Line 1464 of yacc.c  */
#line 2493 "parser.y"
    {
	  // tye type_qualifier_list belongs to the pointer,
	  // not to the abstract declarator
	  (yyval)=(yyvsp[(2) - (3)]);
	  merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
	  do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
	}
    break;

  case 451:

/* Line 1464 of yacc.c  */
#line 2504 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          set((yyval), ID_pointer);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
	}
    break;

  case 452:

/* Line 1464 of yacc.c  */
#line 2510 "parser.y"
    {
	  // tye type_qualifier_list belongs to the pointer,
	  // not to the (missing) abstract declarator
          (yyval)=(yyvsp[(2) - (2)]);
          exprt declarator=exprt(ID_abstract);
          merge_types(stack((yyvsp[(2) - (2)])), declarator);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	}
    break;

  case 453:

/* Line 1464 of yacc.c  */
#line 2519 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
	}
    break;

  case 454:

/* Line 1464 of yacc.c  */
#line 2524 "parser.y"
    {
	  // tye type_qualifier_list belongs to the pointer,
	  // not to the (missing) abstract declarator
          (yyval)=(yyvsp[(2) - (3)]);
          merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
          do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
	}
    break;

  case 455:

/* Line 1464 of yacc.c  */
#line 2535 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 456:

/* Line 1464 of yacc.c  */
#line 2537 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 457:

/* Line 1464 of yacc.c  */
#line 2539 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 458:

/* Line 1464 of yacc.c  */
#line 2541 "parser.y"
    {
	  /* note: this is a pointer ($2) to a function ($4) */
	  /* or an array ($4) of pointers with name ($2)! */
	  (yyval)=(yyvsp[(2) - (4)]);
	  make_subtype((yyval), (yyvsp[(4) - (4)]));
	}
    break;

  case 459:

/* Line 1464 of yacc.c  */
#line 2551 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 460:

/* Line 1464 of yacc.c  */
#line 2553 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 462:

/* Line 1464 of yacc.c  */
#line 2556 "parser.y"
    {
	  /* note: this is a pointer ($2) to a function ($4) */
	  /* or an array ($4) of pointers with name ($2)! */
	  (yyval)=(yyvsp[(2) - (4)]);
	  make_subtype((yyval), (yyvsp[(4) - (4)]));
	}
    break;



/* Line 1464 of yacc.c  */
#line 6310 "y.tab.cpp"
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
#line 2564 "parser.y"


