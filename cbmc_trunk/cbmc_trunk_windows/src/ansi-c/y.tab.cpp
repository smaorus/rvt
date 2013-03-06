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
#line 207 "parser.y"

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
     TOK_WCHAR_T = 292,
     TOK_WHILE = 293,
     TOK_ARROW = 294,
     TOK_INCR = 295,
     TOK_DECR = 296,
     TOK_SHIFTLEFT = 297,
     TOK_SHIFTRIGHT = 298,
     TOK_LE = 299,
     TOK_GE = 300,
     TOK_EQ = 301,
     TOK_NE = 302,
     TOK_ANDAND = 303,
     TOK_OROR = 304,
     TOK_ELLIPSIS = 305,
     TOK_MULTASSIGN = 306,
     TOK_DIVASSIGN = 307,
     TOK_MODASSIGN = 308,
     TOK_PLUSASSIGN = 309,
     TOK_MINUSASSIGN = 310,
     TOK_SHLASSIGN = 311,
     TOK_SHRASSIGN = 312,
     TOK_ANDASSIGN = 313,
     TOK_XORASSIGN = 314,
     TOK_ORASSIGN = 315,
     TOK_IDENTIFIER = 316,
     TOK_TYPEDEFNAME = 317,
     TOK_INTEGER = 318,
     TOK_FLOATING = 319,
     TOK_CHARACTER = 320,
     TOK_STRING = 321,
     TOK_ASM_STRING = 322,
     TOK_INT8 = 323,
     TOK_INT16 = 324,
     TOK_INT32 = 325,
     TOK_INT64 = 326,
     TOK_PTR32 = 327,
     TOK_PTR64 = 328,
     TOK_TYPEOF = 329,
     TOK_GCC_FLOAT128 = 330,
     TOK_GCC_ASM = 331,
     TOK_GCC_ASM_PAREN = 332,
     TOK_GCC_ATTRIBUTE_ALIGNED = 333,
     TOK_GCC_ATTRIBUTE_TRANSPARENT_UNION = 334,
     TOK_GCC_ATTRIBUTE_PACKED = 335,
     TOK_GCC_ATTRIBUTE_VECTOR_SIZE = 336,
     TOK_GCC_ATTRIBUTE_MODE = 337,
     TOK_GCC_ATTRIBUTE_END = 338,
     TOK_GCC_LABEL = 339,
     TOK_MSC_ASM = 340,
     TOK_CW_VAR_ARG_TYPEOF = 341,
     TOK_BUILTIN_VA_ARG = 342,
     TOK_GCC_BUILTIN_TYPES_COMPATIBLE_P = 343,
     TOK_OFFSETOF = 344,
     TOK_ALIGNOF = 345,
     TOK_MSC_TRY = 346,
     TOK_MSC_FINALLY = 347,
     TOK_MSC_EXCEPT = 348,
     TOK_MSC_LEAVE = 349,
     TOK_INTERFACE = 350,
     TOK_CDECL = 351,
     TOK_STDCALL = 352,
     TOK_FASTCALL = 353,
     TOK_CLRCALL = 354,
     TOK_FORALL = 355,
     TOK_EXISTS = 356,
     TOK_ARRAY_OF = 357,
     TOK_CPROVER_BITVECTOR = 358,
     TOK_CPROVER_BOOL = 359,
     TOK_REAL = 360,
     TOK_IMAG = 361,
     TOK_ALIGNAS = 362,
     TOK_ATOMIC = 363,
     TOK_GENERIC = 364,
     TOK_IMAGINARY = 365,
     TOK_NORETURN = 366,
     TOK_STATIC_ASSERT = 367,
     TOK_THREAD_LOCAL = 368,
     TOK_NULLPTR = 369,
     TOK_CONSTEXPR = 370,
     TOK_SCANNER_ERROR = 371,
     TOK_SCANNER_EOF = 372,
     TOK_CATCH = 373,
     TOK_CLASS = 374,
     TOK_DELETE = 375,
     TOK_DECLTYPE = 376,
     TOK_EXPLICIT = 377,
     TOK_FRIEND = 378,
     TOK_MUTABLE = 379,
     TOK_NAMESPACE = 380,
     TOK_NEW = 381,
     TOK_OPERATOR = 382,
     TOK_PRIVATE = 383,
     TOK_PROTECTED = 384,
     TOK_PUBLIC = 385,
     TOK_TEMPLATE = 386,
     TOK_THIS = 387,
     TOK_THROW = 388,
     TOK_TYPEID = 389,
     TOK_TYPENAME = 390,
     TOK_USING = 391,
     TOK_VIRTUAL = 392,
     TOK_TRY = 393,
     TOK_SCOPE = 394,
     TOK_DOTPM = 395,
     TOK_ARROWPM = 396,
     TOK_MSC_UNARY_TYPE_PREDICATE = 397,
     TOK_MSC_BINARY_TYPE_PREDICATE = 398,
     TOK_MSC_UUIDOF = 399,
     TOK_MSC_IF_EXISTS = 400,
     TOK_MSC_IF_NOT_EXISTS = 401,
     TOK_PARSE_LANGUAGE = 402,
     TOK_PARSE_EXPRESSION = 403,
     TOK_PARSE_TYPE = 404
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
#define TOK_WCHAR_T 292
#define TOK_WHILE 293
#define TOK_ARROW 294
#define TOK_INCR 295
#define TOK_DECR 296
#define TOK_SHIFTLEFT 297
#define TOK_SHIFTRIGHT 298
#define TOK_LE 299
#define TOK_GE 300
#define TOK_EQ 301
#define TOK_NE 302
#define TOK_ANDAND 303
#define TOK_OROR 304
#define TOK_ELLIPSIS 305
#define TOK_MULTASSIGN 306
#define TOK_DIVASSIGN 307
#define TOK_MODASSIGN 308
#define TOK_PLUSASSIGN 309
#define TOK_MINUSASSIGN 310
#define TOK_SHLASSIGN 311
#define TOK_SHRASSIGN 312
#define TOK_ANDASSIGN 313
#define TOK_XORASSIGN 314
#define TOK_ORASSIGN 315
#define TOK_IDENTIFIER 316
#define TOK_TYPEDEFNAME 317
#define TOK_INTEGER 318
#define TOK_FLOATING 319
#define TOK_CHARACTER 320
#define TOK_STRING 321
#define TOK_ASM_STRING 322
#define TOK_INT8 323
#define TOK_INT16 324
#define TOK_INT32 325
#define TOK_INT64 326
#define TOK_PTR32 327
#define TOK_PTR64 328
#define TOK_TYPEOF 329
#define TOK_GCC_FLOAT128 330
#define TOK_GCC_ASM 331
#define TOK_GCC_ASM_PAREN 332
#define TOK_GCC_ATTRIBUTE_ALIGNED 333
#define TOK_GCC_ATTRIBUTE_TRANSPARENT_UNION 334
#define TOK_GCC_ATTRIBUTE_PACKED 335
#define TOK_GCC_ATTRIBUTE_VECTOR_SIZE 336
#define TOK_GCC_ATTRIBUTE_MODE 337
#define TOK_GCC_ATTRIBUTE_END 338
#define TOK_GCC_LABEL 339
#define TOK_MSC_ASM 340
#define TOK_CW_VAR_ARG_TYPEOF 341
#define TOK_BUILTIN_VA_ARG 342
#define TOK_GCC_BUILTIN_TYPES_COMPATIBLE_P 343
#define TOK_OFFSETOF 344
#define TOK_ALIGNOF 345
#define TOK_MSC_TRY 346
#define TOK_MSC_FINALLY 347
#define TOK_MSC_EXCEPT 348
#define TOK_MSC_LEAVE 349
#define TOK_INTERFACE 350
#define TOK_CDECL 351
#define TOK_STDCALL 352
#define TOK_FASTCALL 353
#define TOK_CLRCALL 354
#define TOK_FORALL 355
#define TOK_EXISTS 356
#define TOK_ARRAY_OF 357
#define TOK_CPROVER_BITVECTOR 358
#define TOK_CPROVER_BOOL 359
#define TOK_REAL 360
#define TOK_IMAG 361
#define TOK_ALIGNAS 362
#define TOK_ATOMIC 363
#define TOK_GENERIC 364
#define TOK_IMAGINARY 365
#define TOK_NORETURN 366
#define TOK_STATIC_ASSERT 367
#define TOK_THREAD_LOCAL 368
#define TOK_NULLPTR 369
#define TOK_CONSTEXPR 370
#define TOK_SCANNER_ERROR 371
#define TOK_SCANNER_EOF 372
#define TOK_CATCH 373
#define TOK_CLASS 374
#define TOK_DELETE 375
#define TOK_DECLTYPE 376
#define TOK_EXPLICIT 377
#define TOK_FRIEND 378
#define TOK_MUTABLE 379
#define TOK_NAMESPACE 380
#define TOK_NEW 381
#define TOK_OPERATOR 382
#define TOK_PRIVATE 383
#define TOK_PROTECTED 384
#define TOK_PUBLIC 385
#define TOK_TEMPLATE 386
#define TOK_THIS 387
#define TOK_THROW 388
#define TOK_TYPEID 389
#define TOK_TYPENAME 390
#define TOK_USING 391
#define TOK_VIRTUAL 392
#define TOK_TRY 393
#define TOK_SCOPE 394
#define TOK_DOTPM 395
#define TOK_ARROWPM 396
#define TOK_MSC_UNARY_TYPE_PREDICATE 397
#define TOK_MSC_BINARY_TYPE_PREDICATE 398
#define TOK_MSC_UUIDOF 399
#define TOK_MSC_IF_EXISTS 400
#define TOK_MSC_IF_NOT_EXISTS 401
#define TOK_PARSE_LANGUAGE 402
#define TOK_PARSE_EXPRESSION 403
#define TOK_PARSE_TYPE 404




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 455 "y.tab.cpp"

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
#define YYFINAL  153
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   4231

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  174
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  172
/* YYNRULES -- Number of rules.  */
#define YYNRULES  479
/* YYNRULES -- Number of states.  */
#define YYNSTATES  843

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   404

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   163,     2,     2,     2,   165,   158,     2,
     150,   151,   159,   160,   152,   161,   153,   164,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   171,   173,
     166,   172,   167,   170,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   154,     2,   155,   168,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   156,   169,   157,   162,     2,     2,     2,
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
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    37,    39,    41,
      45,    47,    49,    51,    53,    55,    57,    64,    71,    76,
      83,    85,    89,    94,    99,   104,   111,   118,   122,   124,
     129,   133,   138,   142,   146,   149,   152,   154,   156,   158,
     162,   164,   167,   170,   173,   176,   179,   182,   185,   188,
     191,   194,   199,   202,   205,   207,   212,   219,   227,   229,
     233,   237,   241,   243,   247,   251,   253,   257,   261,   263,
     267,   271,   275,   279,   281,   285,   289,   291,   295,   297,
     301,   303,   307,   309,   313,   315,   319,   321,   327,   332,
     334,   338,   342,   346,   350,   354,   358,   362,   366,   370,
     374,   378,   380,   384,   386,   387,   389,   392,   395,   398,
     401,   403,   411,   412,   417,   418,   423,   424,   430,   436,
     437,   439,   440,   447,   448,   455,   456,   464,   466,   468,
     470,   472,   474,   476,   478,   480,   482,   485,   487,   490,
     493,   495,   498,   501,   503,   505,   507,   509,   511,   513,
     515,   519,   523,   527,   531,   534,   538,   541,   545,   548,
     551,   554,   556,   559,   562,   566,   570,   574,   578,   582,
     586,   589,   593,   597,   602,   607,   609,   612,   614,   616,
     618,   620,   622,   624,   626,   628,   630,   632,   634,   636,
     638,   640,   642,   644,   646,   648,   650,   652,   654,   656,
     658,   660,   665,   667,   669,   671,   673,   678,   679,   687,
     688,   697,   702,   704,   706,   707,   709,   711,   714,   717,
     720,   726,   729,   735,   741,   742,   744,   746,   749,   752,
     755,   757,   759,   763,   767,   771,   775,   779,   780,   783,
     787,   790,   791,   793,   796,   797,   805,   806,   815,   819,
     821,   823,   827,   830,   833,   834,   837,   839,   843,   845,
     849,   851,   853,   857,   859,   862,   865,   868,   870,   873,
     876,   878,   881,   884,   887,   889,   892,   895,   897,   899,
     901,   904,   906,   909,   910,   913,   915,   917,   921,   926,
     928,   932,   934,   935,   939,   942,   946,   949,   953,   959,
     964,   971,   975,   977,   979,   981,   983,   985,   987,   989,
     991,   993,   995,   997,   999,  1003,  1008,  1015,  1019,  1023,
    1028,  1033,  1034,  1036,  1039,  1042,  1048,  1056,  1062,  1064,
    1066,  1072,  1080,  1089,  1093,  1096,  1099,  1102,  1106,  1110,
    1112,  1116,  1118,  1125,  1130,  1135,  1138,  1146,  1151,  1153,
    1154,  1156,  1158,  1160,  1163,  1167,  1172,  1178,  1180,  1183,
    1185,  1190,  1198,  1200,  1204,  1207,  1209,  1214,  1222,  1224,
    1228,  1231,  1233,  1235,  1237,  1241,  1244,  1246,  1248,  1252,
    1253,  1255,  1257,  1260,  1262,  1264,  1266,  1268,  1274,  1275,
    1279,  1281,  1282,  1284,  1286,  1289,  1292,  1295,  1299,  1301,
    1304,  1307,  1310,  1313,  1315,  1317,  1319,  1321,  1323,  1326,
    1328,  1330,  1333,  1337,  1341,  1346,  1348,  1353,  1359,  1362,
    1366,  1370,  1375,  1380,  1382,  1386,  1388,  1390,  1392,  1395,
    1399,  1402,  1406,  1411,  1413,  1417,  1419,  1421,  1423,  1425,
    1427,  1429,  1432,  1433,  1438,  1439,  1445,  1447,  1450,  1451,
    1456,  1459,  1463,  1467,  1472,  1474,  1477,  1480,  1484,  1486,
    1489,  1492,  1496,  1500,  1504,  1508,  1513,  1517,  1521,  1523
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     175,     0,    -1,   147,   310,    -1,   148,   209,    -1,   149,
     272,    -1,    61,    -1,    62,    -1,    63,    -1,    64,    -1,
      65,    -1,    66,    -1,   178,    -1,   179,    -1,   180,    -1,
     183,    -1,   181,    -1,   183,   181,    -1,   176,    -1,   182,
      -1,   150,   209,   151,    -1,   191,    -1,   185,    -1,   186,
      -1,   187,    -1,   189,    -1,   190,    -1,    87,   150,   208,
     152,   272,   151,    -1,    88,   150,   272,   152,   272,   151,
      -1,    86,   150,   272,   151,    -1,    89,   150,   272,   152,
     188,   151,    -1,   193,    -1,   188,   153,   193,    -1,   188,
     154,   209,   155,    -1,    90,   150,   195,   151,    -1,    90,
     150,   272,   151,    -1,   100,   283,   156,   212,   209,   157,
      -1,   101,   283,   156,   212,   209,   157,    -1,   150,   282,
     151,    -1,   184,    -1,   192,   154,   209,   155,    -1,   192,
     150,   151,    -1,   192,   150,   194,   151,    -1,   192,   153,
     193,    -1,   192,    39,   193,    -1,   192,    40,    -1,   192,
      41,    -1,   176,    -1,   177,    -1,   208,    -1,   194,   152,
     208,    -1,   192,    -1,    40,   195,    -1,    41,   195,    -1,
     158,   196,    -1,    48,   271,    -1,   159,   196,    -1,   160,
     196,    -1,   161,   196,    -1,   162,   196,    -1,   163,   196,
      -1,    28,   195,    -1,    28,   150,   272,   151,    -1,   105,
     195,    -1,   106,   195,    -1,   195,    -1,   150,   272,   151,
     196,    -1,   150,   272,   151,   156,   276,   157,    -1,   150,
     272,   151,   156,   275,   152,   157,    -1,   196,    -1,   197,
     159,   196,    -1,   197,   164,   196,    -1,   197,   165,   196,
      -1,   197,    -1,   198,   160,   197,    -1,   198,   161,   197,
      -1,   198,    -1,   199,    42,   198,    -1,   199,    43,   198,
      -1,   199,    -1,   200,   166,   199,    -1,   200,   167,   199,
      -1,   200,    44,   199,    -1,   200,    45,   199,    -1,   200,
      -1,   201,    46,   200,    -1,   201,    47,   200,    -1,   201,
      -1,   202,   158,   201,    -1,   202,    -1,   203,   168,   202,
      -1,   203,    -1,   204,   169,   203,    -1,   204,    -1,   205,
      48,   204,    -1,   205,    -1,   206,    49,   205,    -1,   206,
      -1,   206,   170,   209,   171,   207,    -1,   206,   170,   171,
     207,    -1,   207,    -1,   196,   172,   208,    -1,   196,    51,
     208,    -1,   196,    52,   208,    -1,   196,    53,   208,    -1,
     196,    54,   208,    -1,   196,    55,   208,    -1,   196,    56,
     208,    -1,   196,    57,   208,    -1,   196,    58,   208,    -1,
     196,    59,   208,    -1,   196,    60,   208,    -1,   208,    -1,
     209,   152,   208,    -1,   208,    -1,    -1,   209,    -1,   224,
     173,    -1,   225,   173,    -1,   220,   173,    -1,   214,   173,
      -1,   213,    -1,   112,   150,   195,   152,   195,   151,   173,
      -1,    -1,   226,   330,   215,   273,    -1,    -1,   227,   330,
     216,   273,    -1,    -1,   214,   152,   330,   217,   273,    -1,
      77,   296,   150,   297,   151,    -1,    -1,   218,    -1,    -1,
     224,   322,   247,   219,   221,   273,    -1,    -1,   225,   322,
     247,   219,   222,   273,    -1,    -1,   220,   152,   322,   247,
     219,   223,   273,    -1,   230,    -1,   232,    -1,   234,    -1,
     235,    -1,   231,    -1,   233,    -1,   236,    -1,   238,    -1,
     239,    -1,   227,   239,    -1,   249,    -1,   226,   249,    -1,
     226,   228,    -1,   229,    -1,   227,   229,    -1,   227,   249,
      -1,   239,    -1,   229,    -1,     9,    -1,    36,    -1,   108,
      -1,    72,    -1,    73,    -1,   226,   240,   247,    -1,   231,
     239,   247,    -1,   230,   228,   247,    -1,   230,   240,   247,
      -1,   240,   247,    -1,   227,   240,   247,    -1,   231,   229,
      -1,   231,   240,   247,    -1,   226,   241,    -1,   233,   239,
      -1,   232,   228,    -1,   241,    -1,   227,   241,    -1,   233,
     229,    -1,   236,   239,   247,    -1,   226,   177,   247,    -1,
     234,   228,   247,    -1,   238,   239,   247,    -1,   226,   237,
     247,    -1,   235,   228,   247,    -1,   177,   247,    -1,   227,
     177,   247,    -1,   236,   229,   247,    -1,    74,   150,   209,
     151,    -1,    74,   150,   272,   151,    -1,   237,    -1,   227,
     237,    -1,    32,    -1,    16,    -1,    29,    -1,     3,    -1,
      24,    -1,    21,    -1,   113,    -1,    76,    -1,    22,    -1,
      68,    -1,    69,    -1,    70,    -1,    71,    -1,     8,    -1,
      26,    -1,    23,    -1,    17,    -1,    75,    -1,    13,    -1,
      27,    -1,    34,    -1,    35,    -1,     4,    -1,     5,    -1,
     103,   154,   209,   155,    -1,   104,    -1,   243,    -1,   259,
      -1,   242,    -1,   102,   166,   272,   167,    -1,    -1,   246,
     247,   244,   156,   250,   157,   247,    -1,    -1,   246,   247,
     271,   245,   156,   250,   157,   247,    -1,   246,   247,   271,
     247,    -1,    30,    -1,    33,    -1,    -1,   248,    -1,   249,
      -1,   248,   249,    -1,    80,    83,    -1,    79,    83,    -1,
      81,   150,   209,   151,    83,    -1,    78,    83,    -1,    78,
     150,   209,   151,    83,    -1,    82,   150,   176,   151,    83,
      -1,    -1,   251,    -1,   252,    -1,   251,   252,    -1,   254,
     173,    -1,   253,   173,    -1,   173,    -1,   213,    -1,   247,
     227,   256,    -1,   253,   152,   256,    -1,   247,   225,   255,
      -1,   254,   152,   255,    -1,   322,   257,   247,    -1,    -1,
     258,   247,    -1,   330,   257,   247,    -1,   258,   247,    -1,
      -1,   258,    -1,   171,   210,    -1,    -1,   262,   247,   260,
     156,   263,   157,   247,    -1,    -1,   262,   247,   271,   261,
     156,   263,   157,   247,    -1,   262,   247,   271,    -1,    15,
      -1,   264,    -1,   263,   152,   264,    -1,   263,   152,    -1,
     271,   265,    -1,    -1,   172,   210,    -1,   269,    -1,   269,
     152,    50,    -1,   268,    -1,   267,   152,   268,    -1,   176,
      -1,   270,    -1,   269,   152,   270,    -1,   224,    -1,   224,
     335,    -1,   224,   330,    -1,   224,   324,    -1,   226,    -1,
     226,   335,    -1,   226,   330,    -1,   225,    -1,   225,   335,
      -1,   225,   330,    -1,   225,   324,    -1,   227,    -1,   227,
     335,    -1,   227,   330,    -1,   176,    -1,   177,    -1,   225,
      -1,   225,   334,    -1,   227,    -1,   227,   334,    -1,    -1,
     172,   274,    -1,   210,    -1,   277,    -1,   156,   276,   157,
      -1,   156,   275,   152,   157,    -1,   274,    -1,   275,   152,
     274,    -1,   275,    -1,    -1,   278,   172,   274,    -1,   278,
     210,    -1,   193,   171,   274,    -1,   153,   193,    -1,   154,
     209,   155,    -1,   154,   209,    50,   209,   155,    -1,   278,
     154,   209,   155,    -1,   278,   154,   209,    50,   209,   155,
      -1,   278,   153,   193,    -1,   281,    -1,   282,    -1,   280,
      -1,   285,    -1,   286,    -1,   288,    -1,   289,    -1,   293,
      -1,   290,    -1,   294,    -1,   295,    -1,   212,    -1,   271,
     171,   279,    -1,     7,   210,   171,   279,    -1,     7,   210,
      50,   210,   171,   279,    -1,    11,   171,   279,    -1,   283,
     156,   157,    -1,   283,   156,   284,   157,    -1,   283,   156,
      67,   157,    -1,    -1,   279,    -1,   284,   279,    -1,   211,
     173,    -1,    20,   150,   209,   151,   279,    -1,    20,   150,
     209,   151,   279,    14,   279,    -1,    31,   150,   209,   151,
     279,    -1,   280,    -1,   285,    -1,    38,   150,   211,   151,
     279,    -1,    12,   279,    38,   150,   209,   151,   173,    -1,
      18,   150,   287,   211,   173,   211,   151,   279,    -1,    19,
     209,   173,    -1,    10,   173,    -1,     6,   173,    -1,    25,
     173,    -1,    25,   209,   173,    -1,    84,   291,   173,    -1,
     292,    -1,   291,   152,   292,    -1,   271,    -1,    77,   296,
     150,   297,   151,   173,    -1,    77,   156,    67,   157,    -1,
      85,   156,    67,   157,    -1,    85,    67,    -1,    91,   282,
      93,   150,   209,   151,   282,    -1,    91,   282,    92,   282,
      -1,    94,    -1,    -1,    36,    -1,    19,    -1,   298,    -1,
     298,   299,    -1,   298,   299,   302,    -1,   298,   299,   302,
     305,    -1,   298,   299,   302,   305,   308,    -1,   183,    -1,
     171,   301,    -1,   171,    -1,   183,   150,   209,   151,    -1,
     154,   271,   155,   183,   150,   209,   151,    -1,   300,    -1,
     301,   152,   300,    -1,   171,   304,    -1,   171,    -1,   183,
     150,   209,   151,    -1,   154,   271,   155,   183,   150,   209,
     151,    -1,   303,    -1,   304,   152,   303,    -1,   171,   307,
      -1,   171,    -1,   183,    -1,   306,    -1,   307,   152,   306,
      -1,   171,   309,    -1,   171,    -1,   292,    -1,   309,   152,
     292,    -1,    -1,   311,    -1,   312,    -1,   311,   312,    -1,
     314,    -1,   212,    -1,   313,    -1,   173,    -1,    77,   150,
     183,   151,   173,    -1,    -1,   321,   315,   316,    -1,   282,
      -1,    -1,   318,    -1,   319,    -1,   318,   319,    -1,   320,
     173,    -1,   225,   322,    -1,   320,   152,   322,    -1,   330,
      -1,   224,   322,    -1,   225,   322,    -1,   226,   330,    -1,
     227,   330,    -1,   330,    -1,   323,    -1,   327,    -1,   324,
      -1,   177,    -1,   177,   336,    -1,   325,    -1,   326,    -1,
     159,   324,    -1,   159,   227,   324,    -1,   150,   325,   151,
      -1,   150,   325,   151,   336,    -1,   328,    -1,   159,   150,
     329,   151,    -1,   159,   227,   150,   329,   151,    -1,   159,
     327,    -1,   159,   227,   327,    -1,   150,   327,   151,    -1,
     150,   329,   336,   151,    -1,   150,   327,   151,   336,    -1,
     177,    -1,   150,   329,   151,    -1,   331,    -1,   333,    -1,
     332,    -1,   159,   330,    -1,   159,   227,   330,    -1,   333,
     336,    -1,   150,   331,   151,    -1,   150,   331,   151,   336,
      -1,   176,    -1,   150,   333,   151,    -1,   342,    -1,   344,
      -1,   336,    -1,   343,    -1,   345,    -1,   341,    -1,   150,
     151,    -1,    -1,   150,   337,   266,   151,    -1,    -1,   150,
     338,   267,   151,   317,    -1,   341,    -1,   150,   151,    -1,
      -1,   150,   340,   266,   151,    -1,   154,   155,    -1,   154,
     159,   155,    -1,   154,   210,   155,    -1,   341,   154,   210,
     155,    -1,   159,    -1,   159,   227,    -1,   159,   334,    -1,
     159,   227,   334,    -1,   159,    -1,   159,   227,    -1,   159,
     335,    -1,   159,   227,   335,    -1,   150,   342,   151,    -1,
     150,   344,   151,    -1,   150,   336,   151,    -1,   150,   342,
     151,   336,    -1,   150,   343,   151,    -1,   150,   345,   151,
      -1,   339,    -1,   150,   343,   151,   339,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   217,   217,   218,   224,   237,   241,   245,   249,   253,
     257,   265,   266,   267,   268,   272,   273,   283,   284,   285,
     287,   288,   289,   290,   291,   292,   296,   303,   316,   325,
     335,   343,   350,   359,   364,   373,   382,   393,   402,   403,
     405,   414,   425,   431,   437,   445,   456,   457,   461,   466,
     474,   475,   481,   487,   492,   501,   506,   511,   516,   521,
     526,   531,   536,   541,   549,   550,   560,   570,   584,   585,
     587,   589,   594,   595,   597,   602,   603,   605,   610,   611,
     613,   615,   617,   622,   623,   625,   630,   631,   636,   637,
     642,   643,   648,   649,   654,   655,   660,   661,   668,   678,
     679,   681,   683,   685,   687,   689,   691,   693,   695,   697,
     699,   704,   705,   710,   715,   716,   722,   730,   738,   739,
     740,   744,   755,   754,   767,   766,   779,   778,   793,   798,
     800,   807,   804,   823,   820,   839,   836,   854,   855,   856,
     857,   861,   862,   863,   864,   868,   869,   874,   875,   880,
     888,   889,   896,   904,   905,   909,   910,   911,   912,   913,
     917,   923,   929,   935,   944,   949,   955,   960,   970,   975,
     980,   989,   990,   995,  1003,  1009,  1015,  1024,  1030,  1036,
    1045,  1050,  1056,  1065,  1070,  1078,  1079,  1120,  1121,  1122,
    1123,  1124,  1125,  1126,  1127,  1131,  1132,  1133,  1134,  1135,
    1136,  1137,  1138,  1139,  1140,  1141,  1142,  1143,  1144,  1145,
    1146,  1147,  1153,  1157,  1158,  1159,  1163,  1170,  1168,  1198,
    1195,  1226,  1240,  1242,  1248,  1251,  1255,  1256,  1263,  1265,
    1267,  1269,  1271,  1273,  1279,  1282,  1286,  1287,  1299,  1300,
    1301,  1305,  1313,  1326,  1337,  1353,  1366,  1380,  1383,  1397,
    1409,  1424,  1427,  1431,  1443,  1441,  1470,  1467,  1490,  1500,
    1508,  1513,  1518,  1525,  1537,  1541,  1548,  1549,  1558,  1563,
    1570,  1579,  1584,  1592,  1598,  1603,  1608,  1615,  1621,  1626,
    1631,  1637,  1642,  1648,  1655,  1661,  1666,  1674,  1675,  1679,
    1680,  1685,  1686,  1695,  1699,  1709,  1710,  1711,  1717,  1726,
    1734,  1742,  1744,  1753,  1761,  1767,  1782,  1789,  1796,  1804,
    1811,  1819,  1831,  1832,  1833,  1834,  1835,  1836,  1837,  1838,
    1839,  1840,  1841,  1845,  1854,  1862,  1870,  1880,  1894,  1901,
    1908,  1920,  1927,  1932,  1939,  1954,  1962,  1971,  1982,  1983,
    1987,  1995,  2003,  2017,  2034,  2036,  2038,  2040,  2045,  2066,
    2071,  2078,  2082,  2088,  2098,  2104,  2113,  2122,  2130,  2137,
    2139,  2140,  2152,  2157,  2162,  2167,  2172,  2179,  2183,  2184,
    2188,  2189,  2194,  2195,  2199,  2200,  2204,  2205,  2210,  2211,
    2214,  2215,  2219,  2223,  2224,  2228,  2229,  2233,  2234,  2243,
    2245,  2249,  2250,  2254,  2255,  2256,  2257,  2261,  2266,  2265,
    2285,  2290,  2293,  2297,  2301,  2310,  2327,  2335,  2347,  2354,
    2360,  2366,  2372,  2381,  2382,  2386,  2387,  2391,  2392,  2397,
    2401,  2402,  2407,  2416,  2418,  2428,  2429,  2434,  2441,  2446,
    2455,  2457,  2462,  2472,  2473,  2478,  2479,  2483,  2484,  2489,
    2502,  2508,  2510,  2520,  2521,  2526,  2527,  2528,  2532,  2533,
    2537,  2538,  2546,  2545,  2562,  2561,  2582,  2583,  2591,  2590,
    2608,  2615,  2622,  2629,  2641,  2647,  2656,  2661,  2672,  2678,
    2687,  2692,  2703,  2705,  2707,  2709,  2718,  2720,  2722,  2723
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
  "\"wchar_t\"", "\"while\"", "\"->\"", "\"++\"", "\"--\"", "\"<<\"",
  "\">>\"", "\"<=\"", "\">=\"", "\"==\"", "\"!=\"", "\"&&\"", "\"||\"",
  "\"...\"", "\"*=\"", "\"/=\"", "\"%=\"", "\"+=\"", "\"-=\"", "\"<<=\"",
  "\">>=\"", "\"&=\"", "\"^=\"", "\"|=\"", "TOK_IDENTIFIER",
  "TOK_TYPEDEFNAME", "TOK_INTEGER", "TOK_FLOATING", "TOK_CHARACTER",
  "TOK_STRING", "TOK_ASM_STRING", "\"__int8\"", "\"__int16\"",
  "\"__int32\"", "\"__int64\"", "\"__ptr32\"", "\"__ptr64\"", "\"typeof\"",
  "\"__float128\"", "\"__asm__\"", "\"__asm__ (with parentheses)\"",
  "\"aligned\"", "\"transparent_union\"", "\"packed\"", "\"vector_size\"",
  "\"mode\"", "\")\"", "\"__label__\"", "\"__asm\"", "\"_var_arg_typeof\"",
  "\"__builtin_va_arg\"", "\"__builtin_types_compatible_p\"",
  "\"__offsetof\"", "\"__alignof__\"", "\"try\"", "\"finally\"",
  "\"except\"", "\"leave\"", "\"__interface\"", "\"__cdecl\"",
  "\"__stdcall\"", "\"__fastcall\"", "\"__clrcall\"", "\"forall\"",
  "\"exists\"", "\"array_of\"", "\"__CPROVER_bitvector\"",
  "\"__CPROVER_bool\"", "\"__real__\"", "\"__imag__\"", "\"_Alignas\"",
  "\"_Atomic\"", "\"_Generic\"", "\"_Imaginary\"", "\"_Noreturn\"",
  "\"_Static_assert\"", "\"_Thread_local\"", "\"nullptr\"",
  "\"constexpr\"", "TOK_SCANNER_ERROR", "TOK_SCANNER_EOF", "TOK_CATCH",
  "TOK_CLASS", "TOK_DELETE", "TOK_DECLTYPE", "TOK_EXPLICIT", "TOK_FRIEND",
  "TOK_MUTABLE", "TOK_NAMESPACE", "TOK_NEW", "TOK_OPERATOR", "TOK_PRIVATE",
  "TOK_PROTECTED", "TOK_PUBLIC", "TOK_TEMPLATE", "TOK_THIS", "TOK_THROW",
  "TOK_TYPEID", "TOK_TYPENAME", "TOK_USING", "TOK_VIRTUAL", "TOK_TRY",
  "\"::\"", "\".*\"", "\"->*\"", "TOK_MSC_UNARY_TYPE_PREDICATE",
  "TOK_MSC_BINARY_TYPE_PREDICATE", "\"__uuidof\"", "\"__if_exists\"",
  "\"__if_not_exists\"", "TOK_PARSE_LANGUAGE", "TOK_PARSE_EXPRESSION",
  "TOK_PARSE_TYPE", "'('", "')'", "','", "'.'", "'['", "']'", "'{'", "'}'",
  "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", "'<'", "'>'",
  "'^'", "'|'", "'?'", "':'", "'='", "';'", "$accept", "grammar",
  "identifier", "typedef_name", "integer", "floating", "character",
  "string", "constant", "string_literal_list", "primary_expression",
  "gcc_builtin_expressions", "cw_builtin_expressions", "offsetof",
  "offsetof_member_designator", "alignof", "quantifier_expression",
  "statement_expression", "postfix_expression", "member_name",
  "argument_expression_list", "unary_expression", "cast_expression",
  "multiplicative_expression", "additive_expression", "shift_expression",
  "relational_expression", "equality_expression", "and_expression",
  "exclusive_or_expression", "inclusive_or_expression",
  "logical_and_expression", "logical_or_expression",
  "conditional_expression", "assignment_expression", "comma_expression",
  "constant_expression", "comma_expression_opt", "declaration",
  "static_assert_declaration", "default_declaring_list", "@1", "@2", "@3",
  "post_declarator_attributes", "post_declarator_attributes_opt",
  "declaring_list", "@4", "@5", "@6", "declaration_specifier",
  "type_specifier", "declaration_qualifier_list", "type_qualifier_list",
  "declaration_qualifier", "type_qualifier", "basic_declaration_specifier",
  "basic_type_specifier", "sue_declaration_specifier",
  "sue_type_specifier", "typedef_declaration_specifier",
  "typeof_declaration_specifier", "typedef_type_specifier",
  "typeof_specifier", "typeof_type_specifier", "storage_class",
  "basic_type_name", "elaborated_type_name", "array_of_construct",
  "aggregate_name", "@7", "@8", "aggregate_key", "gcc_type_attribute_opt",
  "gcc_type_attribute_list", "gcc_type_attribute",
  "member_declaration_list_opt", "member_declaration_list",
  "member_declaration", "member_default_declaring_list",
  "member_declaring_list", "member_declarator",
  "member_identifier_declarator", "bit_field_size_opt", "bit_field_size",
  "enum_name", "@9", "@10", "enum_key", "enumerator_list",
  "enumerator_declaration", "enumerator_value_opt", "parameter_type_list",
  "KnR_parameter_list", "KnR_parameter", "parameter_list",
  "parameter_declaration", "identifier_or_typedef_name", "type_name",
  "initializer_opt", "initializer", "initializer_list",
  "initializer_list_opt", "designated_initializer",
  "designated_initializer_designator", "statement",
  "declaration_statement", "labeled_statement", "compound_statement",
  "compound_scope", "statement_list", "expression_statement",
  "selection_statement", "declaration_or_expression_statement",
  "iteration_statement", "jump_statement", "gcc_local_label_statement",
  "gcc_local_label_list", "gcc_local_label", "gcc_asm_statement",
  "msc_asm_statement", "msc_seh_statement", "volatile_or_goto_opt",
  "gcc_asm_commands", "gcc_asm_assembler_template", "gcc_asm_outputs",
  "gcc_asm_output", "gcc_asm_output_list", "gcc_asm_inputs",
  "gcc_asm_input", "gcc_asm_input_list", "gcc_asm_clobbered_registers",
  "gcc_asm_clobbered_register", "gcc_asm_clobbered_registers_list",
  "gcc_asm_labels", "gcc_asm_labels_list", "translation_unit",
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
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
      40,    41,    44,    46,    91,    93,   123,   125,    38,    42,
      43,    45,   126,    33,    47,    37,    60,    62,    94,   124,
      63,    58,    61,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   174,   175,   175,   175,   176,   177,   178,   179,   180,
     181,   182,   182,   182,   182,   183,   183,   184,   184,   184,
     184,   184,   184,   184,   184,   184,   185,   185,   186,   187,
     188,   188,   188,   189,   189,   190,   190,   191,   192,   192,
     192,   192,   192,   192,   192,   192,   193,   193,   194,   194,
     195,   195,   195,   195,   195,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   196,   196,   196,   196,   197,   197,
     197,   197,   198,   198,   198,   199,   199,   199,   200,   200,
     200,   200,   200,   201,   201,   201,   202,   202,   203,   203,
     204,   204,   205,   205,   206,   206,   207,   207,   207,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   209,   209,   210,   211,   211,   212,   212,   212,   212,
     212,   213,   215,   214,   216,   214,   217,   214,   218,   219,
     219,   221,   220,   222,   220,   223,   220,   224,   224,   224,
     224,   225,   225,   225,   225,   226,   226,   226,   226,   226,
     227,   227,   227,   228,   228,   229,   229,   229,   229,   229,
     230,   230,   230,   230,   231,   231,   231,   231,   232,   232,
     232,   233,   233,   233,   234,   234,   234,   235,   235,   235,
     236,   236,   236,   237,   237,   238,   238,   239,   239,   239,
     239,   239,   239,   239,   239,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   241,   241,   241,   242,   244,   243,   245,
     243,   243,   246,   246,   247,   247,   248,   248,   249,   249,
     249,   249,   249,   249,   250,   250,   251,   251,   252,   252,
     252,   252,   253,   253,   254,   254,   255,   255,   255,   256,
     256,   257,   257,   258,   260,   259,   261,   259,   259,   262,
     263,   263,   263,   264,   265,   265,   266,   266,   267,   267,
     268,   269,   269,   270,   270,   270,   270,   270,   270,   270,
     270,   270,   270,   270,   270,   270,   270,   271,   271,   272,
     272,   272,   272,   273,   273,   274,   274,   274,   274,   275,
     275,   276,   276,   277,   277,   277,   278,   278,   278,   278,
     278,   278,   279,   279,   279,   279,   279,   279,   279,   279,
     279,   279,   279,   280,   281,   281,   281,   281,   282,   282,
     282,   283,   284,   284,   285,   286,   286,   286,   287,   287,
     288,   288,   288,   289,   289,   289,   289,   289,   290,   291,
     291,   292,   293,   293,   294,   294,   295,   295,   295,   296,
     296,   296,   297,   297,   297,   297,   297,   298,   299,   299,
     300,   300,   301,   301,   302,   302,   303,   303,   304,   304,
     305,   305,   306,   307,   307,   308,   308,   309,   309,   310,
     310,   311,   311,   312,   312,   312,   312,   313,   315,   314,
     316,   317,   317,   318,   318,   319,   320,   320,   321,   321,
     321,   321,   321,   322,   322,   323,   323,   324,   324,   324,
     325,   325,   325,   326,   326,   327,   327,   327,   327,   327,
     328,   328,   328,   329,   329,   330,   330,   331,   331,   331,
     332,   332,   332,   333,   333,   334,   334,   334,   335,   335,
     336,   336,   337,   336,   338,   336,   339,   339,   340,   339,
     341,   341,   341,   341,   342,   342,   342,   342,   343,   343,
     343,   343,   344,   344,   344,   344,   345,   345,   345,   345
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     6,     6,     4,     6,
       1,     3,     4,     4,     4,     6,     6,     3,     1,     4,
       3,     4,     3,     3,     2,     2,     1,     1,     1,     3,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     4,     2,     2,     1,     4,     6,     7,     1,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     5,     4,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     1,     0,     1,     2,     2,     2,     2,
       1,     7,     0,     4,     0,     4,     0,     5,     5,     0,
       1,     0,     6,     0,     6,     0,     7,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     2,     2,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     2,     3,     2,     3,     2,     2,
       2,     1,     2,     2,     3,     3,     3,     3,     3,     3,
       2,     3,     3,     4,     4,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     4,     1,     1,     1,     1,     4,     0,     7,     0,
       8,     4,     1,     1,     0,     1,     1,     2,     2,     2,
       5,     2,     5,     5,     0,     1,     1,     2,     2,     2,
       1,     1,     3,     3,     3,     3,     3,     0,     2,     3,
       2,     0,     1,     2,     0,     7,     0,     8,     3,     1,
       1,     3,     2,     2,     0,     2,     1,     3,     1,     3,
       1,     1,     3,     1,     2,     2,     2,     1,     2,     2,
       1,     2,     2,     2,     1,     2,     2,     1,     1,     1,
       2,     1,     2,     0,     2,     1,     1,     3,     4,     1,
       3,     1,     0,     3,     2,     3,     2,     3,     5,     4,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     4,     6,     3,     3,     4,
       4,     0,     1,     2,     2,     5,     7,     5,     1,     1,
       5,     7,     8,     3,     2,     2,     2,     3,     3,     1,
       3,     1,     6,     4,     4,     2,     7,     4,     1,     0,
       1,     1,     1,     2,     3,     4,     5,     1,     2,     1,
       4,     7,     1,     3,     2,     1,     4,     7,     1,     3,
       2,     1,     1,     1,     3,     2,     1,     1,     3,     0,
       1,     1,     2,     1,     1,     1,     1,     5,     0,     3,
       1,     0,     1,     1,     2,     2,     2,     3,     1,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     2,     1,
       1,     2,     3,     3,     4,     1,     4,     5,     2,     3,
       3,     4,     4,     1,     3,     1,     1,     1,     2,     3,
       2,     3,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     2,     0,     4,     0,     5,     1,     2,     0,     4,
       2,     3,     3,     4,     1,     2,     2,     3,     1,     2,
       2,     3,     3,     3,     3,     4,     3,     3,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   389,     0,     0,     0,   190,   209,   210,   200,   155,
     205,   259,   188,   203,   192,   195,   202,   191,   201,   206,
     189,   222,   187,   223,   207,   208,   156,     5,     6,   196,
     197,   198,   199,   158,   159,     0,   204,   194,     0,     0,
       0,     0,     0,     0,     0,     0,   212,   157,     0,   193,
       0,     0,   396,   443,   224,   394,   120,     0,     0,     0,
       0,     0,     0,   150,   137,   141,   138,   142,   139,   140,
     143,   185,   144,   145,   224,   171,   215,   213,   224,   147,
     214,   224,     2,   390,   391,   395,   393,   398,   408,   435,
     437,   436,     0,     0,     0,     0,     7,     8,     9,    10,
       0,     0,     0,     0,     0,   331,   331,     0,     0,   331,
       0,     0,     0,     0,     0,     0,    17,    11,    12,    13,
      15,    18,    14,    38,    21,    22,    23,    24,    25,    20,
      50,    64,    68,    72,    75,    78,    83,    86,    88,    90,
      92,    94,    96,    99,   111,     3,   289,   291,   141,   142,
     143,   144,     4,     1,     0,     0,   231,     0,   229,   228,
       0,     0,     0,     0,     0,     0,     0,     0,   438,   180,
     225,   226,     0,   119,     0,   118,     0,     0,   116,   417,
     224,   414,   416,   419,   420,   415,   425,   413,   117,   224,
     224,   149,   154,   224,   153,   224,   168,   148,   122,   224,
     151,   186,   146,   224,   172,   152,   124,   224,   224,   166,
     224,   224,   170,   173,   169,   224,   224,   224,   224,   224,
     164,   217,   254,   392,   331,   452,     0,   440,   450,   331,
      60,   331,    51,    52,   287,   288,    54,     0,     0,     0,
       0,     0,     0,     0,    62,    63,     0,     0,     0,     0,
      53,    55,    56,    57,    58,    59,    16,     0,    44,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   452,   464,   290,   447,   445,   446,
     292,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     441,   444,   439,   227,   126,   224,     0,   433,     0,     0,
       0,     0,     0,   421,   428,   418,   129,   129,   175,   178,
     160,   293,   181,   165,   293,   162,   163,   161,   167,   176,
     179,   182,   174,   177,     0,   224,     0,   258,   400,   399,
     451,     0,     0,   460,     0,   113,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,    37,
     114,    46,    47,    43,    40,     0,    48,    42,     0,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   100,
      69,    70,    71,    68,    73,    74,    76,    77,    81,    82,
      79,    80,    84,    85,    87,    89,    91,    93,    95,     0,
       0,   112,     0,     0,     0,   465,   466,   183,   184,     0,
       0,     0,     0,   216,   211,     0,   442,   293,   129,     0,
     423,   430,     0,     0,     0,   422,   429,   359,   130,   131,
     133,     0,   123,   125,   224,     0,   221,     0,     0,   273,
     280,   277,   284,     0,   266,   271,   270,     0,   268,   461,
     462,     0,    61,    28,     0,     0,     0,    33,    34,     0,
       0,     0,     0,     0,     0,   302,    65,     0,     0,     0,
       0,   114,     0,     0,     0,     0,     0,     0,     0,   359,
       0,     0,   331,   358,   328,    17,   224,   115,     0,   323,
       0,   332,   314,   312,   313,   114,   315,   316,   317,   318,
     320,   319,   321,   322,    41,     0,    39,    98,     0,   474,
     472,   473,   467,   397,   232,   230,   233,     0,   127,   135,
     434,   424,   432,   431,   426,     0,   361,   360,     0,   293,
     293,     0,     0,   302,    17,     0,   295,   294,   296,     0,
     240,   241,     0,     0,   224,   236,     0,     0,   224,     0,
     260,   264,     0,   458,   468,   276,   275,   274,   478,   456,
     448,   449,   283,   282,   281,   458,   468,   279,   278,   286,
     285,   453,     0,   401,     0,   463,     0,     0,     0,    30,
       0,   224,   224,   122,   124,     0,   299,   301,     0,   345,
       0,   344,   114,     0,   114,     0,     0,   346,     0,     0,
     114,   330,     0,     0,   351,     0,   349,   355,     0,     0,
     334,   114,   329,   333,    49,    97,   475,     0,   293,   427,
       0,   132,   134,   306,     0,   301,     0,     0,     0,     0,
       0,   304,   247,     0,   224,   237,     0,   239,   247,   238,
       0,   262,   224,     0,   263,     0,   457,     0,     0,     0,
     469,   470,   469,   267,   272,     0,     0,   455,   402,   403,
       0,   269,    26,    27,    29,     0,     0,    35,    36,     0,
      66,     0,   114,   327,     0,   338,   339,   114,   343,     0,
     347,     0,     0,     0,     0,     0,   348,     0,   331,     0,
     324,   121,   136,   367,     0,   362,     0,   307,     0,   297,
     305,   311,     0,   303,     0,   244,   224,   251,   242,   224,
     251,   218,   243,   245,   224,   261,   255,   265,   224,     0,
     476,   477,   471,   406,   404,     0,   405,    31,     0,    67,
     300,     0,   325,     0,     0,   114,   114,   114,   353,     0,
     350,   354,   357,     0,   128,   369,   363,     0,   298,     0,
     309,   253,   248,   224,   252,   250,   224,   220,   257,   459,
     458,   479,   407,    32,   114,     0,   114,   335,   337,   340,
       0,     0,     0,     0,   372,   368,   375,   364,   308,     0,
     246,   249,   326,     0,     0,   114,   352,   331,     0,     0,
       0,     0,     0,   378,   374,   381,   365,   310,   341,   114,
     336,   356,     0,     0,   373,     0,     0,     0,   382,   383,
     380,   386,   366,   342,     0,   370,     0,     0,   379,     0,
     387,   385,     0,     0,   376,   384,     0,     0,     0,   388,
     371,     0,   377
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,   116,    54,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   588,   127,   128,   129,   130,   545,
     375,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   497,   546,   498,   499,    56,
      57,   331,   334,   427,   438,   439,    58,   539,   540,   628,
     470,   471,   472,   473,   191,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
     344,   445,    78,   552,   170,   171,   553,   554,   555,   556,
     557,   715,   718,   763,   716,    80,   346,   448,    81,   559,
     560,   654,   453,   457,   458,   454,   455,   500,   152,   442,
     596,   597,   598,   548,   549,   501,   502,   503,   504,   249,
     505,   506,   507,   687,   508,   509,   510,   615,   616,   511,
     512,   513,   538,   704,   705,   756,   784,   785,   787,   803,
     804,   806,   819,   820,   822,   831,    82,    83,    84,    85,
      86,   224,   349,   667,   668,   669,   670,    87,   717,   181,
     182,   183,   184,   185,   186,   320,   187,    89,    90,    91,
     296,   661,   297,   351,   352,   568,   657,   228,   298,   570,
     299,   571
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -678
static const yytype_int16 yypact[] =
{
     384,  1512,  3270,  4040,   111,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,   -83,  -678,  -678,   -70,   -41,
      77,   102,    58,    66,    56,    88,  -678,  -678,    84,  -678,
     152,   277,  -678,  -678,   881,  -678,  -678,  -109,   -87,   255,
     261,  2578,  2578,  -678,  3873,  3873,  3211,  3211,  3211,  3211,
    3211,  -678,   818,  -678,   881,  -678,  -678,  -678,   881,  -678,
    -678,   881,  -678,  1512,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,   130,  3376,  3406,  3406,   217,  -678,  -678,  -678,  -678,
     101,   107,   117,   122,   145,  -678,  -678,  3406,  3406,  2265,
    3270,  3270,  3270,  3270,  3270,  3270,  -678,  -678,  -678,  -678,
    -678,  -678,   222,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
     165,  -678,  1262,   297,   272,   458,    31,   511,   146,   141,
     155,   278,   -13,  -678,  -678,   179,   171,  1344,  4123,   274,
     274,  -678,  -678,  -678,  2265,   222,  -678,  3270,  -678,  -678,
    3270,   281,  4040,  3270,  3406,   193,   336,  2660,  -678,  -678,
     881,  -678,   152,  -678,    21,  -678,   338,    42,  -678,   130,
     730,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,   745,
     881,  -678,  -678,   881,  -678,   881,  -678,  -678,   212,   881,
    -678,  -678,  -678,   881,  -678,  -678,   233,   881,   881,  -678,
     881,   881,  -678,  -678,  -678,   881,   881,   881,   881,   881,
    -678,   217,   217,  -678,  -678,   -55,  3047,  -678,   242,  2265,
    -678,  3270,  -678,  -678,  -678,  -678,  -678,  4040,  3270,  4040,
    4040,  2370,   245,   250,  -678,  -678,   421,   257,   284,   256,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,   217,  -678,  -678,
    3098,   217,  3270,  3270,  3270,  3270,  3270,  3270,  3270,  3270,
    3270,  3270,  3270,  3270,  3270,  3270,  3270,  3270,  3270,  3270,
    3270,  3270,  3270,  3270,  3270,  3270,  3270,  3270,  3270,  3270,
    3270,  3270,  2764,  3270,   204,   153,  -678,  -678,  -678,  -678,
    -678,   429,   288,    35,   442,   445,   303,   262,    55,   333,
     130,  -678,  -678,  -678,  -678,   881,   338,  -678,   306,   340,
     130,   338,   999,  -678,  -678,  -678,   430,   430,  -678,  -678,
    -678,   342,  -678,  -678,   342,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,   369,   809,   378,   383,  -678,  -678,
    -678,  3771,   281,  -678,  3189,  -678,   390,  3270,   396,   398,
     399,   402,   408,   417,   424,  3567,  3567,  -678,  3240,  -678,
    1731,  -678,  -678,  -678,  -678,   450,  -678,  -678,   196,  -678,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,   297,   297,   272,   272,   458,   458,
     458,   458,    31,    31,   511,   146,   141,   155,   278,  3270,
     -84,  -678,   434,   440,   452,  1116,  -678,  -678,  -678,   392,
     515,   522,   544,  -678,  -678,  3406,  -678,   342,   430,   359,
     130,   130,   465,   365,   338,  -678,  -678,   184,  -678,  -678,
    -678,  3017,  -678,  -678,   414,   476,  -678,   217,   485,   299,
     299,  2476,  2476,   498,   509,  -678,  -678,   469,  -678,  -678,
    -678,   512,  -678,  -678,  4040,  4040,   217,  -678,  -678,  3270,
     255,   261,  2578,  2578,  3270,  3017,  -678,   497,  3270,   523,
     517,  2053,   532,  3270,   536,  2683,   555,   557,   553,   -14,
     217,   -15,  -678,  -678,  -678,   550,   690,   179,   570,  -678,
     559,  -678,  -678,  -678,  -678,  1892,  -678,  -678,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,  3270,  -678,  -678,  3270,  -678,
     130,  -678,  -678,  -678,  -678,  -678,  -678,   564,  -678,  -678,
    -678,  -678,  -678,  -678,  -678,   416,  -678,  -678,   578,   342,
     342,   217,  3270,  3017,   574,   576,  -678,  -678,  -678,  2734,
    -678,  -678,  4040,   591,  1088,  -678,   -82,   -81,   414,  -111,
    -678,   580,   217,   405,   305,  -678,  -678,  -678,  -678,   242,
    -678,  -678,  -678,  -678,  -678,   518,  2560,  -678,  -678,  -678,
    -678,  -678,  3669,  4040,   281,  -678,   604,   607,   293,  -678,
      67,   881,   881,  -678,  -678,    98,  -678,   608,   605,  -678,
     -26,  -678,  2053,   723,  2159,   -79,  3270,  -678,   -78,  3270,
    3270,  -678,   697,   615,  -678,   -75,  -678,  -678,   700,   530,
    -678,  2053,  -678,  -678,  -678,  -678,  -678,   600,   342,  -678,
     222,  -678,  -678,  -678,    12,   622,   621,  3017,   217,  3270,
    3017,  -678,    87,  1618,   881,  -678,    52,  -678,    87,  -678,
     625,   217,   881,  3270,  -678,   112,  -678,  3771,   629,   632,
    2627,  -678,  1057,  -678,  -678,    21,  3957,  -678,  4040,  -678,
     -67,  -678,  -678,  -678,  -678,   217,  3270,  -678,  -678,  2880,
    -678,  3270,  2053,  -678,   636,  -678,  -678,  3270,  -678,   478,
    -678,   501,   641,   639,   222,   217,  -678,   642,  -678,   651,
    -678,  -678,  -678,   222,   654,   631,  3270,  -678,  2910,  -678,
    -678,  -678,    29,  -678,  3270,  -678,   881,   644,  -678,   881,
     644,  -678,  -678,  -678,   881,  -678,  -678,  -678,   881,   656,
     186,  -678,  -678,  -678,  -678,    21,  -678,  -678,   201,  -678,
    -678,   657,  -678,  3270,   640,  2053,  2053,  2053,  -678,   678,
    -678,  -678,  -678,  3270,  -678,   -18,   661,   229,  -678,  3270,
    -678,  -678,  -678,   881,  -678,  -678,   881,  -678,  -678,  -678,
     682,  -678,  -678,  -678,  2053,   505,  3270,   821,  -678,  -678,
     664,   513,   217,   -31,  -678,   688,    -7,   670,  -678,   239,
    -678,  -678,  -678,   671,   692,  2053,  -678,  -678,   691,  3270,
     -18,   217,    22,  -678,   696,   222,   683,  -678,  -678,  2053,
    -678,  -678,   222,   527,  -678,   694,  3270,    -7,   222,  -678,
     704,   217,  -678,  -678,    80,  -678,   222,   533,  -678,   222,
    -678,   705,  3270,    99,  -678,  -678,   217,   542,  3270,  -678,
    -678,   547,  -678
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -678,  -678,    71,   468,  -678,  -678,  -678,  -121,  -678,  -146,
    -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -678,  -212,
    -678,   -54,  1195,   446,   447,   187,   449,   572,   581,   582,
     575,   579,  -678,  -365,   752,    -2,  -179,  -606,    14,  -434,
    -678,  -678,  -678,  -678,  -678,  -293,  -678,  -678,  -678,  -678,
       1,   623,     6,   211,   167,   936,  -678,    34,  -678,   135,
    -678,  -678,   236,   -35,   713,   860,   -48,   -30,  -678,  -678,
    -678,  -678,  -678,   777,  -678,   138,   315,  -678,   320,  -678,
    -678,   228,   231,   158,   -69,  -678,  -678,  -678,  -678,   319,
     244,  -678,   225,  -678,   309,  -678,   314,   -45,   -46,  -322,
    -381,   354,   355,  -678,  -678,  -412,   296,  -678,  -106,   633,
    -678,   301,  -678,  -678,  -678,  -678,  -678,  -678,  -677,  -678,
    -678,  -678,   419,   209,  -678,  -678,   106,  -678,  -678,    93,
    -678,  -678,    82,  -678,  -678,  -678,  -678,  -678,   830,  -678,
    -678,  -678,  -678,  -678,  -678,   246,  -678,  -678,   -40,  -678,
    -149,  -153,  -678,  -147,  -678,  -255,   577,   -39,  -678,   -25,
    -139,  -394,    49,  -678,  -678,   205,  -678,  -323,   643,  -542,
     650,  -473
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -455
static const yytype_int16 yytable[] =
{
     145,   256,    59,   248,   692,   536,  -454,    61,   300,   303,
     551,   165,   443,   195,   203,    55,   208,   211,   750,   180,
     189,   658,   537,   318,   681,   166,   193,   201,   323,   319,
     324,   196,   204,   658,   440,    99,   291,   148,   230,   232,
     233,   651,   156,   172,   517,   373,   652,   356,    99,   377,
     236,     9,   617,   244,   245,   567,   574,   578,   580,    99,
     547,   429,   706,   247,   173,   174,   433,   154,   293,   603,
     646,   648,    53,   293,   293,   281,   282,   695,    26,   759,
     155,   744,    27,    28,    59,   735,   175,   518,    99,    61,
     659,   647,   649,   623,   688,   690,   350,    55,   696,   203,
     211,    99,   659,    27,    28,   528,   736,   246,   302,   157,
     309,   153,   201,    27,    33,    34,   307,   204,   348,   799,
     551,    53,    53,   248,   551,   248,   569,   569,   569,   569,
      53,    53,    53,    53,   315,   529,   782,   165,   149,    79,
     227,   618,   612,   148,   830,   682,    99,   801,    27,    28,
      47,   166,   301,   625,    53,   304,   416,   292,   305,   839,
     158,   308,     9,   318,   293,    99,   234,   707,   318,   319,
     794,   176,   816,   435,   319,   436,   345,   347,   461,   535,
     177,   293,   256,   358,   760,   159,   419,   363,   148,    26,
     683,   359,   321,   361,   362,   364,   148,   283,   284,   197,
     205,   177,    50,   536,   257,   258,   259,   293,   160,   700,
     424,    51,    62,    27,   147,   227,   161,   631,   632,   293,
     537,    79,   162,   714,   677,    33,    34,   246,   325,   246,
     832,   207,   306,   212,   164,   215,   216,   176,    53,   150,
     569,   569,   163,    53,   149,    53,   177,    53,    53,   838,
     293,   237,   569,   569,   589,   678,   710,   238,   714,   713,
     378,    47,   167,   148,   651,  -454,   732,   239,   732,   728,
     742,   148,   240,   148,   148,   148,   522,   165,    27,    28,
     225,   318,   165,     9,   226,   205,     9,   319,    99,   149,
     410,   166,   234,   234,    62,   241,   166,   149,   740,   600,
     565,   572,    50,   294,   287,   205,   702,   226,   313,   288,
      26,    51,   295,    26,     9,   260,    27,    28,   261,   262,
     147,   294,    27,    28,   289,   226,   290,   740,   371,   633,
     295,   293,   371,   777,   778,   779,   770,   569,    27,   569,
     226,    26,    27,   412,   310,   150,    33,    34,   293,    33,
      34,   516,   449,   293,   294,   350,   773,   451,   226,   426,
      27,    28,   792,   295,   149,   147,    27,    28,  -411,   432,
     641,   527,   149,   147,   149,   149,   149,    33,    34,   469,
     474,   293,    47,   810,   788,    47,   619,    53,   322,  -412,
     150,   293,    53,    53,   807,   165,   357,   823,   150,    27,
      28,   365,   561,   195,   203,   176,   366,   569,   368,   166,
     318,   176,   370,    47,   177,   323,   193,   201,   586,   587,
     177,   196,   204,   456,   195,   203,   711,    50,   178,   423,
     591,   592,   277,   278,   188,   369,    51,   193,   201,   418,
     147,   495,   196,   204,   674,   614,   675,   676,   147,   563,
     147,   147,   147,   226,   422,   563,   274,   430,   564,   226,
     205,   275,   276,   737,   564,   150,    27,   590,   398,   399,
     400,   401,   595,   150,   727,   150,   150,   150,   432,   531,
     532,   605,   432,   608,   703,   425,   225,   311,   316,    79,
     226,   431,    39,    40,    41,    42,    43,   177,   148,   148,
     279,   280,   741,    79,    79,    53,   415,   437,    79,   225,
     530,   435,   544,   226,   441,   225,   534,   561,   234,   226,
      53,    53,    53,    53,   165,   444,    48,   179,   179,   190,
     199,     1,     2,     3,   447,   761,   165,   371,   166,  -256,
     634,    53,    53,    53,    53,   460,   544,   462,   703,   463,
     166,   464,   495,   205,   465,   563,   656,   285,   286,   226,
     466,   234,   452,   235,   564,   523,   225,   629,   467,   626,
     226,  -234,   367,   293,   719,   468,   495,   719,    88,    27,
     417,   293,   256,   449,   432,   519,   148,   550,   451,   197,
     205,   520,   752,   420,   293,   203,   421,   293,   524,   149,
     149,   514,   515,   521,   689,   525,   561,   691,   201,   783,
     197,   205,   371,   204,   544,   199,   533,   148,   203,    79,
     583,   584,   698,   699,    60,   733,   146,   526,   168,   745,
     293,   201,   558,   234,    53,    53,   204,   712,   198,   206,
     802,   562,   179,    79,   317,   179,    53,    53,   764,   581,
     614,   764,   746,   293,   783,   456,   793,   293,   449,   818,
      88,   582,   256,   451,   797,   293,   824,   585,   575,   656,
     599,   802,   226,   495,   738,   147,   147,   576,   825,   293,
     833,   256,   604,   818,   834,   293,   606,   149,   602,   235,
     235,   811,   495,   840,   293,   772,   601,   256,   842,   293,
     150,   150,   148,   256,   757,   609,    60,   610,   544,   371,
     611,   544,   256,    53,    53,   627,   151,    53,   149,    53,
      79,  -287,   234,   394,   395,   372,   396,   397,   630,   372,
     621,    53,   146,    53,   402,   403,    53,   798,   242,   243,
      79,   775,    79,   620,   312,   -46,   371,   637,   644,   314,
     544,   781,   653,   495,   168,   672,   815,   789,   673,    79,
     679,   684,   680,   643,   693,   694,   234,   697,    39,    40,
      41,    42,    43,   701,   708,   660,   614,   146,   709,   544,
     730,   205,   724,   731,   317,   146,   743,   662,   150,   317,
     179,   614,   747,   452,   666,    79,   748,   813,   205,   751,
     205,   753,   755,   149,   205,   754,    53,   769,    39,    40,
      41,    42,    43,   776,   827,   714,   495,   495,   495,   150,
      79,     5,   151,    39,    40,    41,    42,    43,   774,   780,
     837,   169,   786,   656,    12,   795,   841,   796,   496,    14,
     800,   805,    17,   809,   808,   495,   812,    20,   817,   826,
      22,   220,   146,   234,   821,   221,   829,   836,   222,   404,
     146,  -288,   146,   146,   146,   407,   495,   151,   452,   405,
     408,   406,   234,   650,   645,   151,   723,   722,   766,   666,
     495,   655,   729,    79,    79,    79,  -409,    39,    40,    41,
      42,    43,   234,   671,    37,   725,   664,   635,   636,   312,
     685,  -410,   317,   749,   150,   686,   814,   234,   613,   372,
     828,   835,    79,   223,   734,   235,     0,   179,   179,   190,
     199,   194,   202,     0,   194,   210,   194,   214,   194,   194,
     218,    49,   219,    79,   372,   771,     0,   413,   179,   179,
     190,   199,   151,   372,   414,     0,     0,    79,     0,   496,
     151,     0,   151,   151,   151,     0,     0,   326,   235,    39,
      40,    41,    42,    43,     0,  -219,   327,   328,     0,     0,
     329,     0,   330,   496,   450,     0,   332,     0,   355,     0,
     333,     0,     0,     0,   335,   336,     0,   337,   338,     0,
     360,     0,   339,   340,   341,   342,   343,   192,   200,     0,
     192,   209,   192,   213,   192,   192,   217,     0,     9,   372,
       0,   372,   376,     0,     0,   379,   380,   381,   382,   383,
     384,   385,   386,   387,   388,   389,   566,   573,   577,   579,
     235,     0,   179,     0,     0,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   411,     0,     0,     0,   593,
     594,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,    28,     0,     0,     0,     0,     9,     0,     0,     0,
     496,    33,    34,     0,     0,     0,     0,    39,    40,    41,
      42,    43,     0,   200,   209,   213,   217,   146,   146,   496,
       0,     0,   428,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   200,     0,   372,   372,    47,   372,   355,
     179,   199,     0,     0,     0,     0,   179,     0,    27,   235,
       0,     0,   446,     0,     0,     9,     0,     0,   179,    33,
      34,     0,     0,   179,   199,    39,    40,    41,    42,    43,
       0,   168,     0,   372,     0,     0,     0,   372,     0,   434,
     496,     0,    26,   168,     0,     0,     0,     0,   177,     0,
       0,     0,     0,   235,     0,    47,    39,    40,    41,    42,
      43,     0,     0,     0,     0,   642,   372,   151,   151,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    33,    34,
       0,     0,     0,   355,    39,    40,    41,    42,    43,     0,
      48,     0,     0,   179,     0,   450,   665,   575,     0,     0,
       0,   226,     0,   496,   496,   496,   576,     0,     0,     0,
     720,     0,     0,   720,    47,     0,     0,   355,     0,     0,
     355,     0,     0,     0,     0,     0,     0,   312,     0,   312,
       0,     0,   496,     0,     0,  -235,     0,     0,     0,     0,
     235,     0,     0,     0,     0,     0,     0,     0,   200,     0,
       0,   550,     0,   496,     0,   151,   294,   624,     0,   235,
     226,     0,     0,   169,     0,   295,     0,   496,     0,     0,
     450,     0,     0,     0,     0,     0,     0,     0,     0,   235,
       0,   665,     0,     0,     0,   355,   151,     0,     0,     0,
       0,   355,     0,     0,   235,   250,   251,   252,   253,   254,
     255,   194,   202,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   194,   202,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     7,
       0,   200,     8,     9,     0,     0,     0,    10,     0,    11,
       0,    13,     0,     0,     0,     0,    15,    16,   326,   327,
      18,    19,     0,     0,    21,     0,     0,    23,    24,    25,
      26,   151,     0,     0,     0,     0,     0,   192,   200,   355,
       0,     0,   355,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   355,    28,     0,   192,   200,
       0,     0,    29,    30,    31,    32,    33,    34,    35,    36,
       0,   721,    39,    40,    41,    42,    43,     0,     0,   726,
       0,   355,     0,   355,   273,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    44,    45,    46,     0,
       0,     0,    47,     0,     0,     0,     0,     0,     0,     0,
     355,     0,     0,     0,     0,     0,   355,     0,     0,   390,
     391,   392,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   393,     0,     0,     0,
       0,     0,     0,   762,   294,     0,   765,     0,   226,     0,
       0,   767,     0,   295,     0,   768,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,     6,     7,     0,     0,
       8,     9,     0,     0,     0,    10,     0,    11,    12,    13,
       0,     0,     0,    14,    15,    16,    17,     0,    18,    19,
     790,    20,    21,   791,    22,    23,    24,    25,    26,   251,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   476,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    28,     0,     0,     0,     0,   200,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,     0,   200,     0,   200,     0,
       0,     0,   200,     0,   393,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,    45,    46,     0,     0,     0,
      47,     0,     6,     7,    48,    49,     8,     9,     0,     0,
       0,    10,     0,    11,     0,    13,     0,     0,     0,     0,
      15,    16,     0,     0,    18,    19,     0,     0,    21,     0,
       0,    23,    24,    25,    26,     0,     0,     0,     0,     0,
       0,     0,    50,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,    27,
      28,     0,     0,     0,     0,    52,    29,    30,    31,    32,
      33,    34,    35,    36,     0,     0,    39,    40,    41,    42,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   393,     0,     0,     0,     0,     0,     0,
      44,    45,    46,     0,     0,     0,    47,     0,     0,     0,
       0,     0,     0,     0,     5,     6,     7,   477,   478,     8,
       9,   479,   480,   481,    10,     0,    11,    12,    13,   482,
     483,   484,    14,    15,    16,    17,   485,    18,    19,    92,
      20,    21,   486,    22,    23,    24,    25,    26,    50,   487,
       0,    93,    94,     0,     0,     0,     0,    51,     0,    95,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   714,
       0,     0,    27,    28,    96,    97,    98,    99,   488,    29,
      30,    31,    32,    33,    34,    35,    36,    37,   489,    39,
      40,    41,    42,    43,     0,   490,   491,   100,   101,   102,
     103,   104,   492,     0,     0,   493,     0,     0,     0,     0,
       0,   105,   106,    44,    45,    46,   107,   108,     0,    47,
       0,     0,     0,    48,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   109,     0,     0,     0,     0,     0,  -331,   494,   110,
     111,   112,   113,   114,   115,     5,     6,     7,   477,   478,
       8,     9,   479,   480,   481,    10,     0,    11,    12,    13,
     482,   483,   484,    14,    15,    16,    17,   485,    18,    19,
      92,    20,    21,   486,    22,    23,    24,    25,    26,     0,
     487,     0,    93,    94,     0,     0,     0,     0,     0,     0,
      95,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    27,    28,    96,    97,    98,    99,     0,
      29,    30,    31,    32,    33,    34,    35,    36,    37,   489,
      39,    40,    41,    42,    43,     0,   490,   491,   100,   101,
     102,   103,   104,   492,     0,     0,   493,     0,     0,     0,
       0,     0,   105,   106,    44,    45,    46,   107,   108,     0,
      47,     0,     0,     0,    48,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   109,     0,     0,     0,     0,     0,  -331,   622,
     110,   111,   112,   113,   114,   115,     5,     6,     7,   477,
     478,     8,     9,   479,   480,   481,    10,     0,    11,    12,
      13,   482,   483,   484,    14,    15,    16,    17,   485,    18,
      19,    92,    20,    21,   486,    22,    23,    24,    25,    26,
       0,   487,     0,    93,    94,     0,     0,     0,     0,     0,
       0,    95,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    27,    28,    96,    97,    98,    99,
       0,    29,    30,    31,    32,    33,    34,    35,    36,    37,
     489,    39,    40,    41,    42,    43,     0,   490,   491,   100,
     101,   102,   103,   104,   492,     0,     0,   493,     0,     0,
       0,     0,     0,   105,   106,    44,    45,    46,   107,   108,
       0,    47,     5,     6,     7,    48,    49,     8,     9,     0,
       0,     0,    10,     0,    11,    12,    13,     0,     0,     0,
      14,    15,    16,    17,     0,    18,    19,    92,    20,    21,
       0,    22,    23,    24,    25,    26,     0,     0,     0,    93,
      94,     0,     0,   109,     0,     0,     0,    95,     0,  -331,
       0,   110,   111,   112,   113,   114,   115,     0,     0,     0,
      27,    28,    96,    97,    98,    99,     0,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     0,    39,    40,    41,
      42,    43,     0,     0,     0,   100,   101,   102,   103,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   105,
     106,    44,    45,    46,   107,   108,     0,    47,     0,     6,
       7,    48,    49,     8,     9,     0,     0,     0,    10,     0,
      11,     0,    13,     0,     0,     0,     0,    15,    16,     0,
       0,    18,    19,    92,     0,    21,     0,     0,    23,    24,
      25,    26,     0,     0,     0,    93,    94,     0,     0,   109,
       0,     0,     0,    95,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,     0,     0,    27,    28,    96,    97,
      98,    99,     0,    29,    30,    31,    32,    33,    34,    35,
      36,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   100,   101,   102,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,    44,    45,    46,
     107,   108,     0,    47,     6,     7,     0,     0,     8,     9,
       0,     0,     0,    10,     0,    11,     0,    13,     0,     0,
       0,     0,    15,    16,     0,     0,    18,    19,    92,     0,
      21,     0,     0,    23,    24,    25,    26,     0,     0,     0,
      93,    94,     0,     0,     0,   109,     0,     0,    95,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,     0,
       0,    27,    28,    96,    97,    98,    99,     0,    29,    30,
      31,    32,    33,    34,    35,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   100,   101,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   106,    44,    45,    46,   107,   108,     0,    47,     5,
       6,     7,     0,     0,     8,     9,     0,     0,     0,    10,
       0,    11,    12,    13,     0,     0,     0,    14,    15,    16,
      17,     0,    18,    19,     0,    20,    21,     0,    22,    23,
      24,    25,    26,     0,     0,     0,     0,     0,     0,     0,
     231,     0,     0,     0,     0,     0,     0,     0,   110,   111,
     112,   113,   114,   115,     0,     0,     0,    27,    28,     0,
       0,     0,     0,     0,    29,    30,    31,    32,    33,    34,
      35,    36,    37,     0,    39,    40,    41,    42,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     9,
       0,     0,     0,     0,     0,     0,     0,     0,    44,    45,
      46,     5,     6,     7,    47,     0,     8,     9,     0,    49,
       0,    10,     0,    11,    12,    13,    26,     0,     0,    14,
      15,    16,    17,     0,    18,    19,     0,    20,    21,     0,
      22,    23,    24,    25,    26,     0,     0,     0,     0,     0,
       0,    27,     0,     0,     0,     0,   575,     0,     0,     0,
     226,     0,    33,    34,     0,   576,     9,     0,     0,    27,
      28,     0,     0,     0,     0,     0,    29,    30,    31,    32,
      33,    34,    35,    36,    37,     0,    39,    40,    41,    42,
      43,     0,     0,    26,     0,     0,     0,     0,    47,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      44,    45,    46,     0,     0,     0,    47,     0,    27,    28,
       0,    49,     0,     0,     0,     0,    26,     0,     0,    33,
      34,     0,     0,     0,     0,    39,    40,    41,    42,    43,
     575,    92,     0,     0,   226,     0,     0,     0,     0,   576,
       0,    27,     0,    93,    94,     0,     0,     0,    50,     0,
       0,    95,    33,    34,     0,    47,     0,    51,    39,    40,
      41,    42,    43,     0,    27,     0,    96,    97,    98,    99,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    92,     0,     0,     0,     0,     0,    47,   100,
     101,   102,   103,   104,    93,    94,     0,   563,     0,     0,
       0,   226,    95,   105,   106,     0,   564,     0,   107,   108,
       0,     0,    92,     0,     0,    27,     0,    96,    97,    98,
      99,     0,     0,     0,    93,    94,     0,     0,     0,     0,
      50,     0,    95,     0,     0,     0,     0,     0,     0,    51,
     100,   101,   102,   103,   104,    27,     0,    96,    97,    98,
      99,     0,     0,   109,   105,   106,     0,     0,     0,   107,
     108,   110,   111,   112,   113,   114,   115,     0,     0,     0,
     100,   101,   102,   103,   104,     0,   607,     0,     0,     0,
       0,     0,     0,     0,   105,   106,     0,     0,     0,   107,
     108,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   109,     0,     0,   638,   639,     0,
       0,     0,   110,   111,   112,   113,   114,   115,     0,     0,
       0,     0,     0,     0,     0,     0,   640,     0,    92,     0,
       0,     0,     0,     0,   109,     0,     0,     0,     0,     0,
      93,    94,   110,   111,   112,   113,   114,   115,    95,     0,
       0,     0,     0,     0,     0,   409,     0,     0,    92,     0,
       0,    27,    28,    96,    97,    98,    99,     0,     0,     0,
      93,    94,     0,     0,     0,     0,     0,     0,    95,     0,
       0,     0,     0,     0,     0,     0,   100,   101,   102,   103,
     104,    27,    28,    96,    97,    98,    99,     0,     0,     0,
     105,   106,     0,     0,     0,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   100,   101,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   106,     0,     0,     0,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,     0,     0,   541,   542,     0,   543,   739,   110,   111,
     112,   113,   114,   115,     0,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    93,    94,     0,
     109,     0,     0,   541,   542,    95,   543,   758,   110,   111,
     112,   113,   114,   115,     0,    92,     0,     0,    27,    28,
      96,    97,    98,    99,     0,     0,     0,    93,    94,     0,
       0,     0,     0,     0,     0,    95,     0,     0,     0,     0,
       0,     0,     0,   100,   101,   102,   103,   104,    27,     0,
      96,    97,    98,    99,     0,     0,     0,   105,   106,     0,
       0,     0,   107,   108,     0,     0,    92,     0,     0,     0,
       0,     0,     0,   100,   101,   102,   103,   104,    93,    94,
       0,     0,     0,     0,     0,     0,    95,   105,   106,     0,
       0,     0,   107,   108,     0,     0,     0,     0,     0,    27,
       0,    96,    97,    98,    99,     0,     0,   109,     0,     0,
     541,   542,     0,   543,     0,   110,   111,   112,   113,   114,
     115,     0,     0,     0,   100,   101,   102,   103,   104,     0,
       0,     0,     0,     0,     0,     0,     0,   109,   105,   106,
       0,     0,   353,   107,   108,   110,   354,   112,   113,   114,
     115,     0,     0,     0,     5,     0,     0,    92,     0,     0,
       9,     0,     0,     0,     0,     0,     0,    12,     0,    93,
      94,     0,    14,     0,     0,    17,     0,    95,     0,     0,
      20,     0,     0,    22,     0,     0,     0,    26,   109,   374,
      27,     0,    96,    97,    98,    99,   110,   111,   112,   113,
     114,   115,     0,     0,     0,     0,     0,     0,    92,     0,
       0,     0,     0,     0,     0,   100,   101,   102,   103,   104,
      93,    94,     0,    33,    34,     0,     0,    37,    95,   105,
     106,     0,     0,     0,   107,   108,     0,     0,    92,     0,
       0,    27,     0,    96,    97,    98,    99,     0,     0,     0,
      93,    94,     0,     0,     0,     0,     0,     0,    95,    47,
       0,     0,     0,     0,    49,     0,   100,   101,   102,   103,
     104,    27,     0,    96,    97,    98,    99,     0,     0,   109,
     105,   106,     0,     0,   459,   107,   108,   110,   111,   112,
     113,   114,   115,     0,     0,     0,   100,   101,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   106,     0,     0,     0,   107,   108,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     109,     0,     0,     0,     0,     0,   475,     0,   110,   111,
     112,   113,   114,   115,    92,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    93,    94,     0,     0,
     109,     0,     0,     0,    95,     0,     0,     0,   110,   111,
     112,   113,   114,   115,    92,     0,     0,    27,     0,    96,
      97,    98,    99,     0,     0,     0,    93,    94,     0,     0,
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,     0,   100,   101,   102,   103,   104,    27,     0,    96,
      97,    98,    99,     0,     0,     0,   105,   106,     0,     0,
       0,   107,   108,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   100,   101,   102,   103,   104,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,     0,     0,
       0,   107,   108,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   229,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   231,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
       5,     6,     7,     0,     0,     8,     9,     0,     0,     0,
      10,     0,    11,    12,    13,     0,     0,     0,    14,    15,
      16,    17,     0,    18,    19,     0,    20,    21,     0,    22,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
       0,     0,     0,     0,     0,    29,    30,    31,    32,    33,
      34,    35,    36,    37,     0,    39,    40,    41,    42,    43,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    44,
      45,    46,     5,     6,     7,    47,     0,     8,     9,    48,
      49,     0,    10,     0,    11,    12,    13,     0,     0,     0,
      14,    15,    16,    17,     0,    18,    19,     0,    20,    21,
       0,    22,    23,    24,    25,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   663,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,     0,     0,     0,     0,     0,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     0,    39,    40,    41,
      42,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    44,    45,    46,     5,     6,     7,    47,     0,     8,
       9,     0,    49,     0,    10,     0,    11,    12,    13,     0,
       0,     0,    14,    15,    16,    17,     0,    18,    19,     0,
      20,    21,     0,    22,    23,    24,    25,    26,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,     0,     0,     0,     0,     0,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     0,    39,
      40,    41,    42,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,    45,    46,     5,     6,     7,    47,
       0,     8,     9,     0,    49,     0,    10,     0,     0,    12,
      13,     0,     0,     0,    14,    15,    16,    17,     0,    18,
      19,     0,    20,     0,     0,    22,     0,    24,    25,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    30,    31,    32,    33,    34,     0,    36,    37,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     6,     7,     0,     0,     8,     9,     0,     0,     0,
      10,     0,    11,     0,    13,     0,    45,    46,     0,    15,
      16,    47,     0,    18,    19,     0,    49,    21,     0,     0,
      23,    24,    25,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
       0,     0,     0,     0,     0,    29,    30,    31,    32,    33,
      34,    35,    36,     0,     0,    39,    40,    41,    42,    43,
       0,     0,     0,     0,     6,     7,     0,     0,     8,     9,
       0,     0,     0,    10,     0,    11,     0,    13,     0,    44,
      45,    46,    15,    16,     0,    47,    18,    19,     0,     0,
      21,     0,     0,    23,    24,    25,    26,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,     0,     0,     0,     0,    29,    30,
      31,    32,    33,    34,    35,    36,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     7,     0,
       0,     8,     9,     0,     0,     0,    10,     0,     0,     0,
      13,     0,    44,    45,    46,    15,    16,     0,    47,    18,
      19,     0,     0,     0,     0,     0,     0,    24,    25,    26,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    29,    30,    31,    32,    33,    34,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    45,    46,     0,     0,
       0,    47
};

static const yytype_int16 yycheck[] =
{
       2,   122,     1,   109,   610,    19,    61,     1,   147,   155,
     444,    50,   334,    61,    62,     1,    64,    65,   695,    59,
      60,   563,    36,   176,    50,    50,    61,    62,   177,   176,
     177,    61,    62,   575,   327,    66,    49,     3,    92,    93,
      94,   152,    83,   152,   409,   257,   157,   226,    66,   261,
      95,     9,    67,   107,   108,   449,   450,   451,   452,    66,
     441,   316,    50,   109,   173,   152,   321,   150,   152,   481,
     152,   152,     1,   152,   152,    44,    45,   152,    36,    50,
     150,   687,    61,    62,    83,   152,   173,   171,    66,    83,
     563,   173,   173,   505,   173,   173,   151,    83,   173,   147,
     148,    66,   575,    61,    62,   427,   173,   109,   154,   150,
     164,     0,   147,    61,    72,    73,   162,   147,   224,   150,
     554,    50,    51,   229,   558,   231,   449,   450,   451,   452,
      59,    60,    61,    62,   174,   428,   154,   176,     3,     1,
      91,   156,   156,   109,   821,   171,    66,   154,    61,    62,
     108,   176,   154,   518,    83,   157,   295,   170,   160,   836,
      83,   163,     9,   316,   152,    66,    95,   155,   321,   316,
     776,   150,   150,   322,   321,   322,   221,   222,   357,   434,
     159,   152,   303,   229,   155,    83,   151,   241,   154,    36,
     602,   237,   150,   239,   240,   241,   162,   166,   167,    61,
      62,   159,   150,    19,    39,    40,    41,   152,   150,   621,
     155,   159,     1,    61,     3,   166,   150,   539,   540,   152,
      36,    83,   166,   171,   157,    72,    73,   229,   179,   231,
     150,    64,   161,    66,   150,    68,    69,   150,   167,     3,
     563,   564,   154,   172,   109,   174,   159,   176,   177,   150,
     152,   150,   575,   576,   466,   157,   637,   150,   171,   640,
     262,   108,    51,   229,   152,    61,   660,   150,   662,   157,
     682,   237,   150,   239,   240,   241,   415,   316,    61,    62,
     150,   434,   321,     9,   154,   147,     9,   434,    66,   154,
     292,   316,   221,   222,    83,   150,   321,   162,   679,   478,
     449,   450,   150,   150,   158,   167,   628,   154,   170,   168,
      36,   159,   159,    36,     9,   150,    61,    62,   153,   154,
     109,   150,    61,    62,   169,   154,    48,   708,   257,   541,
     159,   152,   261,   745,   746,   747,   150,   660,    61,   662,
     154,    36,    61,   294,   151,   109,    72,    73,   152,    72,
      73,   155,   351,   152,   150,   151,   155,   351,   154,   310,
      61,    62,   774,   159,   229,   154,    61,    62,   156,   320,
     549,   425,   237,   162,   239,   240,   241,    72,    73,   365,
     366,   152,   108,   795,   155,   108,   492,   316,   177,   156,
     154,   152,   321,   322,   155,   434,   154,   809,   162,    61,
      62,   156,   447,   451,   452,   150,   156,   730,   151,   434,
     563,   150,   156,   108,   159,   564,   451,   452,   464,   465,
     159,   451,   452,   352,   472,   473,   638,   150,   173,   167,
     470,   471,   160,   161,   173,   151,   159,   472,   473,   151,
     229,   370,   472,   473,   151,   490,   153,   154,   237,   150,
     239,   240,   241,   154,   151,   150,   159,   151,   159,   154,
     322,   164,   165,   675,   159,   229,    61,   469,   281,   282,
     283,   284,   474,   237,   653,   239,   240,   241,   429,   430,
     431,   483,   433,   485,   630,   152,   150,   151,   150,   351,
     154,   151,    78,    79,    80,    81,    82,   159,   464,   465,
      42,    43,   681,   365,   366,   434,   295,    77,   370,   150,
     151,   660,   441,   154,   172,   150,   151,   562,   447,   154,
     449,   450,   451,   452,   563,   156,   112,    59,    60,    61,
      62,   147,   148,   149,   156,   714,   575,   466,   563,   156,
     542,   470,   471,   472,   473,   155,   475,   151,   694,   151,
     575,   152,   481,   415,   152,   150,   151,    46,    47,   154,
     152,   490,   351,    95,   159,   173,   150,   151,   151,   520,
     154,   157,   151,   152,   643,   151,   505,   646,     1,    61,
     151,   152,   703,   582,   535,   151,   552,   173,   582,   451,
     452,   151,   698,   151,   152,   643,   151,   152,    83,   464,
     465,   151,   152,   151,   606,    83,   651,   609,   643,   755,
     472,   473,   541,   643,   543,   147,   151,   583,   666,   481,
     151,   152,    92,    93,     1,   665,     3,    83,    51,   151,
     152,   666,   156,   562,   563,   564,   666,   639,    61,    62,
     786,   156,   174,   505,   176,   177,   575,   576,   717,   151,
     695,   720,   151,   152,   800,   584,   151,   152,   657,   805,
      83,   152,   783,   657,   151,   152,   812,   155,   150,   151,
     173,   817,   154,   602,   676,   464,   465,   159,   151,   152,
     826,   802,   150,   829,   151,   152,   150,   552,   171,   221,
     222,   797,   621,   151,   152,   735,   173,   818,   151,   152,
     464,   465,   668,   824,   706,   150,    83,   150,   637,   638,
     157,   640,   833,   642,   643,   151,     3,   646,   583,   648,
     582,   171,   651,   277,   278,   257,   279,   280,   150,   261,
     171,   660,   109,   662,   285,   286,   665,   782,   105,   106,
     602,   743,   604,   173,   167,   171,   675,   171,   157,   172,
     679,   753,   172,   682,   177,   151,   801,   759,   151,   621,
     152,    38,   157,   552,    67,   150,   695,    67,    78,    79,
      80,    81,    82,   173,   152,   564,   821,   154,   157,   708,
     151,   643,   157,   151,   316,   162,   150,   576,   552,   321,
     322,   836,   151,   582,   583,   657,   157,   799,   660,   157,
     662,   150,   171,   668,   666,   151,   735,   151,    78,    79,
      80,    81,    82,   173,   816,   171,   745,   746,   747,   583,
     682,     3,   109,    78,    79,    80,    81,    82,   171,   151,
     832,    54,   171,   151,    16,    14,   838,   173,   370,    21,
     152,   171,    24,   151,   173,   774,   155,    29,   152,   155,
      32,    74,   229,   782,   171,    78,   152,   152,    81,   287,
     237,   171,   239,   240,   241,   290,   795,   154,   657,   288,
     291,   289,   801,   558,   554,   162,   648,   646,   720,   668,
     809,   562,   657,   745,   746,   747,   156,    78,    79,    80,
      81,    82,   821,   584,    76,   651,   582,   543,   543,   322,
     604,   156,   434,   694,   668,   604,   800,   836,   489,   441,
     817,   829,   774,    83,   668,   447,    -1,   449,   450,   451,
     452,    61,    62,    -1,    64,    65,    66,    67,    68,    69,
      70,   113,    72,   795,   466,   730,    -1,   294,   470,   471,
     472,   473,   229,   475,   294,    -1,    -1,   809,    -1,   481,
     237,    -1,   239,   240,   241,    -1,    -1,   180,   490,    78,
      79,    80,    81,    82,    -1,   156,   189,   190,    -1,    -1,
     193,    -1,   195,   505,   351,    -1,   199,    -1,   226,    -1,
     203,    -1,    -1,    -1,   207,   208,    -1,   210,   211,    -1,
     238,    -1,   215,   216,   217,   218,   219,    61,    62,    -1,
      64,    65,    66,    67,    68,    69,    70,    -1,     9,   541,
      -1,   543,   260,    -1,    -1,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   449,   450,   451,   452,
     562,    -1,   564,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   293,    -1,    -1,    -1,   472,
     473,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,     9,    -1,    -1,    -1,
     602,    72,    73,    -1,    -1,    -1,    -1,    78,    79,    80,
      81,    82,    -1,   147,   148,   149,   150,   464,   465,   621,
      -1,    -1,   315,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   167,    -1,   637,   638,   108,   640,   357,
     642,   643,    -1,    -1,    -1,    -1,   648,    -1,    61,   651,
      -1,    -1,   345,    -1,    -1,     9,    -1,    -1,   660,    72,
      73,    -1,    -1,   665,   666,    78,    79,    80,    81,    82,
      -1,   564,    -1,   675,    -1,    -1,    -1,   679,    -1,   150,
     682,    -1,    36,   576,    -1,    -1,    -1,    -1,   159,    -1,
      -1,    -1,    -1,   695,    -1,   108,    78,    79,    80,    81,
      82,    -1,    -1,    -1,    -1,   552,   708,   464,   465,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      -1,    -1,    -1,   441,    78,    79,    80,    81,    82,    -1,
     112,    -1,    -1,   735,    -1,   582,   583,   150,    -1,    -1,
      -1,   154,    -1,   745,   746,   747,   159,    -1,    -1,    -1,
     643,    -1,    -1,   646,   108,    -1,    -1,   475,    -1,    -1,
     478,    -1,    -1,    -1,    -1,    -1,    -1,   660,    -1,   662,
      -1,    -1,   774,    -1,    -1,   157,    -1,    -1,    -1,    -1,
     782,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   322,    -1,
      -1,   173,    -1,   795,    -1,   552,   150,   515,    -1,   801,
     154,    -1,    -1,   496,    -1,   159,    -1,   809,    -1,    -1,
     657,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   821,
      -1,   668,    -1,    -1,    -1,   543,   583,    -1,    -1,    -1,
      -1,   549,    -1,    -1,   836,   110,   111,   112,   113,   114,
     115,   451,   452,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   472,   473,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,
      -1,   415,     8,     9,    -1,    -1,    -1,    13,    -1,    15,
      -1,    17,    -1,    -1,    -1,    -1,    22,    23,   591,   592,
      26,    27,    -1,    -1,    30,    -1,    -1,    33,    34,    35,
      36,   668,    -1,    -1,    -1,    -1,    -1,   451,   452,   637,
      -1,    -1,   640,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   653,    62,    -1,   472,   473,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    75,
      -1,   644,    78,    79,    80,    81,    82,    -1,    -1,   652,
      -1,   679,    -1,   681,   172,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   102,   103,   104,    -1,
      -1,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     708,    -1,    -1,    -1,    -1,    -1,   714,    -1,    -1,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,    -1,    -1,    -1,
      -1,    -1,    -1,   716,   150,    -1,   719,    -1,   154,    -1,
      -1,   724,    -1,   159,    -1,   728,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,    -1,    -1,
       8,     9,    -1,    -1,    -1,    13,    -1,    15,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    -1,    26,    27,
     763,    29,    30,   766,    32,    33,    34,    35,    36,   354,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,   643,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,   660,    -1,   662,    -1,
      -1,    -1,   666,    -1,   409,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   102,   103,   104,    -1,    -1,    -1,
     108,    -1,     4,     5,   112,   113,     8,     9,    -1,    -1,
      -1,    13,    -1,    15,    -1,    17,    -1,    -1,    -1,    -1,
      22,    23,    -1,    -1,    26,    27,    -1,    -1,    30,    -1,
      -1,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   150,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,   173,    68,    69,    70,    71,
      72,    73,    74,    75,    -1,    -1,    78,    79,    80,    81,
      82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   518,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,    -1,    -1,    -1,   108,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,   150,    38,
      -1,    40,    41,    -1,    -1,    -1,    -1,   159,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   171,
      -1,    -1,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    -1,    94,    -1,    -1,    -1,    -1,
      -1,   100,   101,   102,   103,   104,   105,   106,    -1,   108,
      -1,    -1,    -1,   112,   113,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   150,    -1,    -1,    -1,    -1,    -1,   156,   157,   158,
     159,   160,   161,   162,   163,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      38,    -1,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    63,    64,    65,    66,    -1,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    -1,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    -1,    94,    -1,    -1,    -1,
      -1,    -1,   100,   101,   102,   103,   104,   105,   106,    -1,
     108,    -1,    -1,    -1,   112,   113,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   150,    -1,    -1,    -1,    -1,    -1,   156,   157,
     158,   159,   160,   161,   162,   163,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    -1,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      -1,    38,    -1,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,    66,
      -1,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    -1,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    -1,    94,    -1,    -1,
      -1,    -1,    -1,   100,   101,   102,   103,   104,   105,   106,
      -1,   108,     3,     4,     5,   112,   113,     8,     9,    -1,
      -1,    -1,    13,    -1,    15,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    -1,    26,    27,    28,    29,    30,
      -1,    32,    33,    34,    35,    36,    -1,    -1,    -1,    40,
      41,    -1,    -1,   150,    -1,    -1,    -1,    48,    -1,   156,
      -1,   158,   159,   160,   161,   162,   163,    -1,    -1,    -1,
      61,    62,    63,    64,    65,    66,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    78,    79,    80,
      81,    82,    -1,    -1,    -1,    86,    87,    88,    89,    90,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   100,
     101,   102,   103,   104,   105,   106,    -1,   108,    -1,     4,
       5,   112,   113,     8,     9,    -1,    -1,    -1,    13,    -1,
      15,    -1,    17,    -1,    -1,    -1,    -1,    22,    23,    -1,
      -1,    26,    27,    28,    -1,    30,    -1,    -1,    33,    34,
      35,    36,    -1,    -1,    -1,    40,    41,    -1,    -1,   150,
      -1,    -1,    -1,    48,    -1,    -1,    -1,   158,   159,   160,
     161,   162,   163,    -1,    -1,    -1,    61,    62,    63,    64,
      65,    66,    -1,    68,    69,    70,    71,    72,    73,    74,
      75,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   100,   101,   102,   103,   104,
     105,   106,    -1,   108,     4,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    13,    -1,    15,    -1,    17,    -1,    -1,
      -1,    -1,    22,    23,    -1,    -1,    26,    27,    28,    -1,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      40,    41,    -1,    -1,    -1,   150,    -1,    -1,    48,    -1,
      -1,    -1,    -1,   158,   159,   160,   161,   162,   163,    -1,
      -1,    61,    62,    63,    64,    65,    66,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,   102,   103,   104,   105,   106,    -1,   108,     3,
       4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,
      -1,    15,    16,    17,    -1,    -1,    -1,    21,    22,    23,
      24,    -1,    26,    27,    -1,    29,    30,    -1,    32,    33,
      34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     150,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   158,   159,
     160,   161,   162,   163,    -1,    -1,    -1,    61,    62,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      74,    75,    76,    -1,    78,    79,    80,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,
     104,     3,     4,     5,   108,    -1,     8,     9,    -1,   113,
      -1,    13,    -1,    15,    16,    17,    36,    -1,    -1,    21,
      22,    23,    24,    -1,    26,    27,    -1,    29,    30,    -1,
      32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,
     154,    -1,    72,    73,    -1,   159,     9,    -1,    -1,    61,
      62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    -1,    78,    79,    80,    81,
      82,    -1,    -1,    36,    -1,    -1,    -1,    -1,   108,     9,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     102,   103,   104,    -1,    -1,    -1,   108,    -1,    61,    62,
      -1,   113,    -1,    -1,    -1,    -1,    36,    -1,    -1,    72,
      73,    -1,    -1,    -1,    -1,    78,    79,    80,    81,    82,
     150,    28,    -1,    -1,   154,    -1,    -1,    -1,    -1,   159,
      -1,    61,    -1,    40,    41,    -1,    -1,    -1,   150,    -1,
      -1,    48,    72,    73,    -1,   108,    -1,   159,    78,    79,
      80,    81,    82,    -1,    61,    -1,    63,    64,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,   108,    86,
      87,    88,    89,    90,    40,    41,    -1,   150,    -1,    -1,
      -1,   154,    48,   100,   101,    -1,   159,    -1,   105,   106,
      -1,    -1,    28,    -1,    -1,    61,    -1,    63,    64,    65,
      66,    -1,    -1,    -1,    40,    41,    -1,    -1,    -1,    -1,
     150,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,   159,
      86,    87,    88,    89,    90,    61,    -1,    63,    64,    65,
      66,    -1,    -1,   150,   100,   101,    -1,    -1,    -1,   105,
     106,   158,   159,   160,   161,   162,   163,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    -1,   173,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   100,   101,    -1,    -1,    -1,   105,
     106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   150,    -1,    -1,   153,   154,    -1,
      -1,    -1,   158,   159,   160,   161,   162,   163,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   172,    -1,    28,    -1,
      -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,    -1,
      40,    41,   158,   159,   160,   161,   162,   163,    48,    -1,
      -1,    -1,    -1,    -1,    -1,   171,    -1,    -1,    28,    -1,
      -1,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    61,    62,    63,    64,    65,    66,    -1,    -1,    -1,
     100,   101,    -1,    -1,    -1,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,    -1,    -1,    -1,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     150,    -1,    -1,   153,   154,    -1,   156,   157,   158,   159,
     160,   161,   162,   163,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,
     150,    -1,    -1,   153,   154,    48,   156,   157,   158,   159,
     160,   161,   162,   163,    -1,    28,    -1,    -1,    61,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    61,    -1,
      63,    64,    65,    66,    -1,    -1,    -1,   100,   101,    -1,
      -1,    -1,   105,   106,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    48,   100,   101,    -1,
      -1,    -1,   105,   106,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    63,    64,    65,    66,    -1,    -1,   150,    -1,    -1,
     153,   154,    -1,   156,    -1,   158,   159,   160,   161,   162,
     163,    -1,    -1,    -1,    86,    87,    88,    89,    90,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,   100,   101,
      -1,    -1,   155,   105,   106,   158,   159,   160,   161,   162,
     163,    -1,    -1,    -1,     3,    -1,    -1,    28,    -1,    -1,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    40,
      41,    -1,    21,    -1,    -1,    24,    -1,    48,    -1,    -1,
      29,    -1,    -1,    32,    -1,    -1,    -1,    36,   150,   151,
      61,    -1,    63,    64,    65,    66,   158,   159,   160,   161,
     162,   163,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,    90,
      40,    41,    -1,    72,    73,    -1,    -1,    76,    48,   100,
     101,    -1,    -1,    -1,   105,   106,    -1,    -1,    28,    -1,
      -1,    61,    -1,    63,    64,    65,    66,    -1,    -1,    -1,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    48,   108,
      -1,    -1,    -1,    -1,   113,    -1,    86,    87,    88,    89,
      90,    61,    -1,    63,    64,    65,    66,    -1,    -1,   150,
     100,   101,    -1,    -1,   155,   105,   106,   158,   159,   160,
     161,   162,   163,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     100,   101,    -1,    -1,    -1,   105,   106,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     150,    -1,    -1,    -1,    -1,    -1,   156,    -1,   158,   159,
     160,   161,   162,   163,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,
     150,    -1,    -1,    -1,    48,    -1,    -1,    -1,   158,   159,
     160,   161,   162,   163,    28,    -1,    -1,    61,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    61,    -1,    63,
      64,    65,    66,    -1,    -1,    -1,   100,   101,    -1,    -1,
      -1,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   100,   101,    -1,    -1,
      -1,   105,   106,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   158,   159,   160,   161,   162,   163,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   158,   159,   160,   161,   162,   163,
       3,     4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,
      13,    -1,    15,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    -1,    26,    27,    -1,    29,    30,    -1,    32,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    -1,    78,    79,    80,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,
     103,   104,     3,     4,     5,   108,    -1,     8,     9,   112,
     113,    -1,    13,    -1,    15,    16,    17,    -1,    -1,    -1,
      21,    22,    23,    24,    -1,    26,    27,    -1,    29,    30,
      -1,    32,    33,    34,    35,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    -1,    78,    79,    80,
      81,    82,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   102,   103,   104,     3,     4,     5,   108,    -1,     8,
       9,    -1,   113,    -1,    13,    -1,    15,    16,    17,    -1,
      -1,    -1,    21,    22,    23,    24,    -1,    26,    27,    -1,
      29,    30,    -1,    32,    33,    34,    35,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    -1,    78,
      79,    80,    81,    82,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   102,   103,   104,     3,     4,     5,   108,
      -1,     8,     9,    -1,   113,    -1,    13,    -1,    -1,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    -1,    26,
      27,    -1,    29,    -1,    -1,    32,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    -1,    75,    76,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,
      13,    -1,    15,    -1,    17,    -1,   103,   104,    -1,    22,
      23,   108,    -1,    26,    27,    -1,   113,    30,    -1,    -1,
      33,    34,    35,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    75,    -1,    -1,    78,    79,    80,    81,    82,
      -1,    -1,    -1,    -1,     4,     5,    -1,    -1,     8,     9,
      -1,    -1,    -1,    13,    -1,    15,    -1,    17,    -1,   102,
     103,   104,    22,    23,    -1,   108,    26,    27,    -1,    -1,
      30,    -1,    -1,    33,    34,    35,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    75,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     4,     5,    -1,
      -1,     8,     9,    -1,    -1,    -1,    13,    -1,    -1,    -1,
      17,    -1,   102,   103,   104,    22,    23,    -1,   108,    26,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    -1,    75,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   103,   104,    -1,    -1,
      -1,   108
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   147,   148,   149,   175,     3,     4,     5,     8,     9,
      13,    15,    16,    17,    21,    22,    23,    24,    26,    27,
      29,    30,    32,    33,    34,    35,    36,    61,    62,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,   102,   103,   104,   108,   112,   113,
     150,   159,   173,   176,   177,   212,   213,   214,   220,   224,
     225,   226,   227,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,   243,   246,   249,
     259,   262,   310,   311,   312,   313,   314,   321,   330,   331,
     332,   333,    28,    40,    41,    48,    63,    64,    65,    66,
      86,    87,    88,    89,    90,   100,   101,   105,   106,   150,
     158,   159,   160,   161,   162,   163,   176,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   189,   190,   191,
     192,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   225,   227,   231,   233,
     236,   238,   272,     0,   150,   150,    83,   150,    83,    83,
     150,   150,   166,   154,   150,   331,   333,   227,   330,   247,
     248,   249,   152,   173,   152,   173,   150,   159,   173,   177,
     322,   323,   324,   325,   326,   327,   328,   330,   173,   322,
     177,   228,   229,   237,   239,   240,   241,   249,   330,   177,
     229,   237,   239,   240,   241,   249,   330,   228,   240,   229,
     239,   240,   228,   229,   239,   228,   228,   229,   239,   239,
     247,   247,   247,   312,   315,   150,   154,   336,   341,   150,
     195,   150,   195,   195,   176,   177,   271,   150,   150,   150,
     150,   150,   283,   283,   195,   195,   209,   272,   282,   283,
     196,   196,   196,   196,   196,   196,   181,    39,    40,    41,
     150,   153,   154,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,   172,   159,   164,   165,   160,   161,    42,
      43,    44,    45,   166,   167,    46,    47,   158,   168,   169,
      48,    49,   170,   152,   150,   159,   334,   336,   342,   344,
     334,   209,   272,   183,   209,   209,   176,   272,   209,   195,
     151,   151,   330,   249,   330,   322,   150,   177,   325,   327,
     329,   150,   227,   324,   327,   336,   247,   247,   247,   247,
     247,   215,   247,   247,   216,   247,   247,   247,   247,   247,
     247,   247,   247,   247,   244,   271,   260,   271,   282,   316,
     151,   337,   338,   155,   159,   208,   210,   154,   272,   272,
     208,   272,   272,   195,   272,   156,   156,   151,   151,   151,
     156,   176,   177,   193,   151,   194,   208,   193,   209,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     196,   196,   196,   196,   197,   197,   198,   198,   199,   199,
     199,   199,   200,   200,   201,   202,   203,   204,   205,   171,
     209,   208,   336,   342,   344,   227,   334,   151,   151,   151,
     151,   151,   151,   167,   155,   152,   336,   217,   247,   329,
     151,   151,   336,   329,   150,   324,   327,    77,   218,   219,
     219,   172,   273,   273,   156,   245,   247,   156,   261,   224,
     225,   226,   227,   266,   269,   270,   176,   267,   268,   155,
     155,   210,   151,   151,   152,   152,   152,   151,   151,   212,
     224,   225,   226,   227,   212,   156,   196,     6,     7,    10,
      11,    12,    18,    19,    20,    25,    31,    38,    67,    77,
      84,    85,    91,    94,   157,   176,   177,   209,   211,   212,
     271,   279,   280,   281,   282,   284,   285,   286,   288,   289,
     290,   293,   294,   295,   151,   152,   155,   207,   171,   151,
     151,   151,   334,   173,    83,    83,    83,   195,   273,   219,
     151,   336,   336,   151,   151,   329,    19,    36,   296,   221,
     222,   153,   154,   156,   176,   193,   210,   274,   277,   278,
     173,   213,   247,   250,   251,   252,   253,   254,   156,   263,
     264,   271,   156,   150,   159,   324,   330,   335,   339,   341,
     343,   345,   324,   330,   335,   150,   159,   330,   335,   330,
     335,   151,   152,   151,   152,   155,   272,   272,   188,   193,
     209,   322,   322,   330,   330,   209,   274,   275,   276,   173,
     210,   173,   171,   279,   150,   209,   150,   173,   209,   150,
     150,   157,   156,   296,   271,   291,   292,    67,   156,   282,
     173,   171,   157,   279,   208,   207,   336,   151,   223,   151,
     150,   273,   273,   193,   209,   275,   276,   171,   153,   154,
     172,   210,   225,   227,   157,   252,   152,   173,   152,   173,
     250,   152,   157,   172,   265,   263,   151,   340,   343,   345,
     227,   335,   227,    50,   270,   225,   227,   317,   318,   319,
     320,   268,   151,   151,   151,   153,   154,   157,   157,   152,
     157,    50,   171,   279,    38,   280,   285,   287,   173,   209,
     173,   209,   211,    67,   150,   152,   173,    67,    92,    93,
     279,   173,   273,   183,   297,   298,    50,   155,   152,   157,
     274,   193,   209,   274,   171,   255,   258,   322,   256,   258,
     330,   247,   256,   255,   157,   264,   247,   210,   157,   266,
     151,   151,   335,   322,   319,   152,   173,   193,   209,   157,
     274,   210,   279,   150,   211,   151,   151,   151,   157,   297,
     292,   157,   282,   150,   151,   171,   299,   209,   157,    50,
     155,   210,   247,   257,   258,   247,   257,   247,   247,   151,
     150,   339,   322,   155,   171,   209,   173,   279,   279,   279,
     151,   209,   154,   183,   300,   301,   171,   302,   155,   209,
     247,   247,   279,   151,   211,    14,   173,   151,   271,   150,
     152,   154,   183,   303,   304,   171,   305,   155,   173,   151,
     279,   282,   155,   209,   300,   271,   150,   152,   183,   306,
     307,   171,   308,   279,   183,   151,   155,   209,   303,   152,
     292,   309,   150,   183,   151,   306,   152,   209,   150,   292,
     151,   209,   151
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
#line 219 "parser.y"
    {
          ansi_c_declarationt ansi_c_declaration;
          ansi_c_declaration.value()=stack((yyvsp[(2) - (2)]));
          PARSER.copy_item(ansi_c_declaration);
        }
    break;

  case 4:

/* Line 1464 of yacc.c  */
#line 225 "parser.y"
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
#line 274 "parser.y"
    { (yyval) = (yyvsp[(1) - (2)]);
          // do concatenation
          concatenate_strings(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])));
        }
    break;

  case 19:

/* Line 1464 of yacc.c  */
#line 286 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 26:

/* Line 1464 of yacc.c  */
#line 297 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyval)).id(ID_gcc_builtin_va_arg);
          mto((yyval), (yyvsp[(3) - (6)]));
          stack((yyval)).type().swap(stack((yyvsp[(5) - (6)])));
        }
    break;

  case 27:

/* Line 1464 of yacc.c  */
#line 305 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyval)).id(ID_gcc_builtin_types_compatible_p);
          irept::subt &subtypes=stack((yyval)).add(ID_subtypes).get_sub();
          subtypes.resize(2);
          subtypes[0].swap(stack((yyvsp[(3) - (6)])));
          subtypes[1].swap(stack((yyvsp[(5) - (6)])));
        }
    break;

  case 28:

/* Line 1464 of yacc.c  */
#line 317 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          stack((yyval)).id(ID_cw_va_arg_typeof);
          stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 29:

/* Line 1464 of yacc.c  */
#line 326 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyval)).id(ID_builtin_offsetof);
          stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (6)])));
          stack((yyval)).add(ID_designator).swap(stack((yyvsp[(5) - (6)])));
        }
    break;

  case 30:

/* Line 1464 of yacc.c  */
#line 336 "parser.y"
    {
          init((yyval), ID_designated_initializer);
          stack((yyval)).operands().resize(1);
          stack((yyval)).op0().id(ID_member);
          stack((yyval)).op0().location()=stack((yyvsp[(1) - (1)])).location();
          stack((yyval)).op0().set(ID_component_name, stack((yyvsp[(1) - (1)])).get(ID_C_base_name));
        }
    break;

  case 31:

/* Line 1464 of yacc.c  */
#line 344 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          set((yyvsp[(2) - (3)]), ID_member);
          stack((yyvsp[(2) - (3)])).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
          mto((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 32:

/* Line 1464 of yacc.c  */
#line 351 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyvsp[(2) - (4)]), ID_index);
          mto((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]));
          mto((yyval), (yyvsp[(2) - (4)]));
        }
    break;

  case 33:

/* Line 1464 of yacc.c  */
#line 360 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_builtin_alignof);
          mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 34:

/* Line 1464 of yacc.c  */
#line 365 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          stack((yyval)).id(ID_builtin_alignof);
          stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 35:

/* Line 1464 of yacc.c  */
#line 374 "parser.y"
    {
          init((yyval));
          stack((yyval)).id(ID_forall);
          stack((yyval)).location()=stack((yyvsp[(1) - (6)])).location();
          mto((yyval), (yyvsp[(4) - (6)]));
          mto((yyval), (yyvsp[(5) - (6)]));
          PARSER.pop_scope();
        }
    break;

  case 36:

/* Line 1464 of yacc.c  */
#line 383 "parser.y"
    {
          init((yyval));
          stack((yyval)).id(ID_exists);
          stack((yyval)).location()=stack((yyvsp[(1) - (6)])).location();
          mto((yyval), (yyvsp[(4) - (6)]));
          mto((yyval), (yyvsp[(5) - (6)]));
          PARSER.pop_scope();
        }
    break;

  case 37:

/* Line 1464 of yacc.c  */
#line 394 "parser.y"
    { init((yyval), ID_sideeffect);
          stack((yyval)).set(ID_statement, ID_statement_expression);
          stack((yyval)).location()=stack((yyvsp[(1) - (3)])).location();
          mto((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 39:

/* Line 1464 of yacc.c  */
#line 404 "parser.y"
    { binary((yyval), (yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), ID_index, (yyvsp[(3) - (4)])); }
    break;

  case 40:

/* Line 1464 of yacc.c  */
#line 406 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]);
          set((yyval), ID_sideeffect);
          stack((yyval)).operands().resize(2);
          stack((yyval)).op0().swap(stack((yyvsp[(1) - (3)])));
          stack((yyval)).op1().clear();
          stack((yyval)).op1().id(ID_arguments);
          stack((yyval)).set(ID_statement, ID_function_call);
        }
    break;

  case 41:

/* Line 1464 of yacc.c  */
#line 415 "parser.y"
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

  case 42:

/* Line 1464 of yacc.c  */
#line 426 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]);
          set((yyval), ID_member);
          mto((yyval), (yyvsp[(1) - (3)]));
          stack((yyval)).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
        }
    break;

  case 43:

/* Line 1464 of yacc.c  */
#line 432 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]);
          set((yyval), ID_ptrmember);
          mto((yyval), (yyvsp[(1) - (3)]));
          stack((yyval)).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
        }
    break;

  case 44:

/* Line 1464 of yacc.c  */
#line 438 "parser.y"
    { (yyval)=(yyvsp[(2) - (2)]);
          locationt location=stack((yyvsp[(2) - (2)])).location();
          init((yyval), ID_sideeffect);
          mto((yyval), (yyvsp[(1) - (2)]));
          stack((yyval)).set(ID_statement, ID_postincrement);
          stack((yyval)).location()=location;
        }
    break;

  case 45:

/* Line 1464 of yacc.c  */
#line 446 "parser.y"
    { (yyval)=(yyvsp[(2) - (2)]);
          locationt location=stack((yyvsp[(2) - (2)])).location();
          init((yyval), ID_sideeffect);
          mto((yyval), (yyvsp[(1) - (2)]));
          stack((yyval)).set(ID_statement, ID_postdecrement);
          stack((yyval)).location()=location;
        }
    break;

  case 48:

/* Line 1464 of yacc.c  */
#line 462 "parser.y"
    {
          init((yyval), ID_expression_list);
          mto((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 49:

/* Line 1464 of yacc.c  */
#line 467 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 51:

/* Line 1464 of yacc.c  */
#line 476 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_sideeffect);
          stack((yyval)).set(ID_statement, ID_preincrement);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 52:

/* Line 1464 of yacc.c  */
#line 482 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_sideeffect);
          stack((yyval)).set(ID_statement, ID_predecrement);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 53:

/* Line 1464 of yacc.c  */
#line 488 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_address_of);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 54:

/* Line 1464 of yacc.c  */
#line 493 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          irep_idt identifier=PARSER.lookup_label(stack((yyvsp[(2) - (2)])).get(ID_C_base_name));
          set((yyval), ID_address_of);
          stack((yyval)).operands().resize(1);
          stack((yyval)).op0()=stack((yyvsp[(2) - (2)]));
          stack((yyval)).op0().id(ID_label);
          stack((yyval)).op0().set(ID_identifier, identifier);
        }
    break;

  case 55:

/* Line 1464 of yacc.c  */
#line 502 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_dereference);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 56:

/* Line 1464 of yacc.c  */
#line 507 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_unary_plus);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 57:

/* Line 1464 of yacc.c  */
#line 512 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_unary_minus);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 58:

/* Line 1464 of yacc.c  */
#line 517 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_bitnot);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 59:

/* Line 1464 of yacc.c  */
#line 522 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_not);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 60:

/* Line 1464 of yacc.c  */
#line 527 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_sizeof);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 61:

/* Line 1464 of yacc.c  */
#line 532 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_sizeof);
          stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 62:

/* Line 1464 of yacc.c  */
#line 537 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_complex_real);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 63:

/* Line 1464 of yacc.c  */
#line 542 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_complex_imag);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 65:

/* Line 1464 of yacc.c  */
#line 551 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_typecast);
          mto((yyval), (yyvsp[(4) - (4)]));
          stack((yyval)).type().swap(stack((yyvsp[(2) - (4)])));
        }
    break;

  case 66:

/* Line 1464 of yacc.c  */
#line 561 "parser.y"
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

  case 67:

/* Line 1464 of yacc.c  */
#line 571 "parser.y"
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

  case 69:

/* Line 1464 of yacc.c  */
#line 586 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_mult, (yyvsp[(3) - (3)])); }
    break;

  case 70:

/* Line 1464 of yacc.c  */
#line 588 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_div, (yyvsp[(3) - (3)])); }
    break;

  case 71:

/* Line 1464 of yacc.c  */
#line 590 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_mod, (yyvsp[(3) - (3)])); }
    break;

  case 73:

/* Line 1464 of yacc.c  */
#line 596 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_plus, (yyvsp[(3) - (3)])); }
    break;

  case 74:

/* Line 1464 of yacc.c  */
#line 598 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_minus, (yyvsp[(3) - (3)])); }
    break;

  case 76:

/* Line 1464 of yacc.c  */
#line 604 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_shl, (yyvsp[(3) - (3)])); }
    break;

  case 77:

/* Line 1464 of yacc.c  */
#line 606 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_shr, (yyvsp[(3) - (3)])); }
    break;

  case 79:

/* Line 1464 of yacc.c  */
#line 612 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_lt, (yyvsp[(3) - (3)])); }
    break;

  case 80:

/* Line 1464 of yacc.c  */
#line 614 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_gt, (yyvsp[(3) - (3)])); }
    break;

  case 81:

/* Line 1464 of yacc.c  */
#line 616 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_le, (yyvsp[(3) - (3)])); }
    break;

  case 82:

/* Line 1464 of yacc.c  */
#line 618 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_ge, (yyvsp[(3) - (3)])); }
    break;

  case 84:

/* Line 1464 of yacc.c  */
#line 624 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_equal, (yyvsp[(3) - (3)])); }
    break;

  case 85:

/* Line 1464 of yacc.c  */
#line 626 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_notequal, (yyvsp[(3) - (3)])); }
    break;

  case 87:

/* Line 1464 of yacc.c  */
#line 632 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_bitand, (yyvsp[(3) - (3)])); }
    break;

  case 89:

/* Line 1464 of yacc.c  */
#line 638 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_bitxor, (yyvsp[(3) - (3)])); }
    break;

  case 91:

/* Line 1464 of yacc.c  */
#line 644 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_bitor, (yyvsp[(3) - (3)])); }
    break;

  case 93:

/* Line 1464 of yacc.c  */
#line 650 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_and, (yyvsp[(3) - (3)])); }
    break;

  case 95:

/* Line 1464 of yacc.c  */
#line 656 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_or, (yyvsp[(3) - (3)])); }
    break;

  case 97:

/* Line 1464 of yacc.c  */
#line 662 "parser.y"
    { (yyval)=(yyvsp[(2) - (5)]);
          stack((yyval)).id(ID_if);
          mto((yyval), (yyvsp[(1) - (5)]));
          mto((yyval), (yyvsp[(3) - (5)]));
          mto((yyval), (yyvsp[(5) - (5)]));
        }
    break;

  case 98:

/* Line 1464 of yacc.c  */
#line 669 "parser.y"
    { (yyval)=(yyvsp[(2) - (4)]);
          stack((yyval)).id(ID_sideeffect);
          stack((yyval)).set(ID_statement, ID_gcc_conditional_expression);
          mto((yyval), (yyvsp[(1) - (4)]));
          mto((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 100:

/* Line 1464 of yacc.c  */
#line 680 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign); }
    break;

  case 101:

/* Line 1464 of yacc.c  */
#line 682 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_mult); }
    break;

  case 102:

/* Line 1464 of yacc.c  */
#line 684 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_div); }
    break;

  case 103:

/* Line 1464 of yacc.c  */
#line 686 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_mod); }
    break;

  case 104:

/* Line 1464 of yacc.c  */
#line 688 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_plus); }
    break;

  case 105:

/* Line 1464 of yacc.c  */
#line 690 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_minus); }
    break;

  case 106:

/* Line 1464 of yacc.c  */
#line 692 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_shl); }
    break;

  case 107:

/* Line 1464 of yacc.c  */
#line 694 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_shr); }
    break;

  case 108:

/* Line 1464 of yacc.c  */
#line 696 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_bitand); }
    break;

  case 109:

/* Line 1464 of yacc.c  */
#line 698 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_bitxor); }
    break;

  case 110:

/* Line 1464 of yacc.c  */
#line 700 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_bitor); }
    break;

  case 112:

/* Line 1464 of yacc.c  */
#line 706 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_comma, (yyvsp[(3) - (3)])); }
    break;

  case 114:

/* Line 1464 of yacc.c  */
#line 715 "parser.y"
    { init((yyval)); stack((yyval)).make_nil(); }
    break;

  case 116:

/* Line 1464 of yacc.c  */
#line 723 "parser.y"
    {
          // type only, no identifier!
          codet decl(ID_decl_type);
          decl.add(ID_type_arg).swap(stack((yyvsp[(1) - (2)])));
          init((yyval));
          stack((yyval)).move_to_operands(decl);
        }
    break;

  case 117:

/* Line 1464 of yacc.c  */
#line 731 "parser.y"
    {
          // type only, no identifier!
          codet decl(ID_decl_type);
          decl.add(ID_type_arg).swap(stack((yyvsp[(1) - (2)])));
          init((yyval));
          stack((yyval)).move_to_operands(decl);
        }
    break;

  case 121:

/* Line 1464 of yacc.c  */
#line 745 "parser.y"
    {
          init((yyval), ID_declaration);
          stack((yyval)).set(ID_is_static_assert, true);
          stack((yyval)).set(ID_value, stack((yyvsp[(3) - (7)])));
          stack((yyval)).set(ID_comment, stack((yyvsp[(5) - (7)])));
        }
    break;

  case 122:

/* Line 1464 of yacc.c  */
#line 755 "parser.y"
    {
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 123:

/* Line 1464 of yacc.c  */
#line 761 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (4)]));
          decl_statement((yyval), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
        }
    break;

  case 124:

/* Line 1464 of yacc.c  */
#line 767 "parser.y"
    {
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 125:

/* Line 1464 of yacc.c  */
#line 773 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (4)]));
          decl_statement((yyval), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
        }
    break;

  case 126:

/* Line 1464 of yacc.c  */
#line 779 "parser.y"
    {
            init((yyval));
            const irept &t=stack((yyvsp[(1) - (3)])).find(ID_type);
            PARSER.new_declaration(t, stack((yyvsp[(3) - (3)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 127:

/* Line 1464 of yacc.c  */
#line 786 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          decl_statement((yyval), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
        }
    break;

  case 128:

/* Line 1464 of yacc.c  */
#line 794 "parser.y"
    {
        }
    break;

  case 131:

/* Line 1464 of yacc.c  */
#line 807 "parser.y"
    {
            // the symbol has to be visible during initialization
            merge_types((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); // type attribute
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (4)])), stack((yyvsp[(2) - (4)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 132:

/* Line 1464 of yacc.c  */
#line 815 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (6)])); // save for later
          decl_statement((yyval), (yyvsp[(5) - (6)]), (yyvsp[(6) - (6)]));
        }
    break;

  case 133:

/* Line 1464 of yacc.c  */
#line 823 "parser.y"
    {
            // the symbol has to be visible during initialization
            merge_types((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)])); // type attribute
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (4)])), stack((yyvsp[(2) - (4)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 134:

/* Line 1464 of yacc.c  */
#line 831 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (6)])); // save for later
          decl_statement((yyval), (yyvsp[(5) - (6)]), (yyvsp[(6) - (6)]));
        }
    break;

  case 135:

/* Line 1464 of yacc.c  */
#line 839 "parser.y"
    {
            init((yyval));
            irept t=stack((yyvsp[(1) - (5)])).find(ID_type);
            merge_types(t, stack((yyvsp[(4) - (5)]))); // type attribute
            PARSER.new_declaration(t, stack((yyvsp[(3) - (5)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 136:

/* Line 1464 of yacc.c  */
#line 847 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (7)]);
          decl_statement((yyval), (yyvsp[(6) - (7)]), (yyvsp[(7) - (7)]));
        }
    break;

  case 146:

/* Line 1464 of yacc.c  */
#line 870 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 148:

/* Line 1464 of yacc.c  */
#line 876 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 149:

/* Line 1464 of yacc.c  */
#line 881 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 151:

/* Line 1464 of yacc.c  */
#line 890 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 152:

/* Line 1464 of yacc.c  */
#line 897 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 155:

/* Line 1464 of yacc.c  */
#line 909 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_const); }
    break;

  case 156:

/* Line 1464 of yacc.c  */
#line 910 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_volatile); }
    break;

  case 157:

/* Line 1464 of yacc.c  */
#line 911 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_atomic); }
    break;

  case 158:

/* Line 1464 of yacc.c  */
#line 912 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_ptr32); }
    break;

  case 159:

/* Line 1464 of yacc.c  */
#line 913 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_ptr64); }
    break;

  case 160:

/* Line 1464 of yacc.c  */
#line 918 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 161:

/* Line 1464 of yacc.c  */
#line 924 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 162:

/* Line 1464 of yacc.c  */
#line 930 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 163:

/* Line 1464 of yacc.c  */
#line 936 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 164:

/* Line 1464 of yacc.c  */
#line 945 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)])); // type attribute
        }
    break;

  case 165:

/* Line 1464 of yacc.c  */
#line 950 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 166:

/* Line 1464 of yacc.c  */
#line 956 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 167:

/* Line 1464 of yacc.c  */
#line 961 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 168:

/* Line 1464 of yacc.c  */
#line 971 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 169:

/* Line 1464 of yacc.c  */
#line 976 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 170:

/* Line 1464 of yacc.c  */
#line 981 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 172:

/* Line 1464 of yacc.c  */
#line 991 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 173:

/* Line 1464 of yacc.c  */
#line 996 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 174:

/* Line 1464 of yacc.c  */
#line 1004 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 175:

/* Line 1464 of yacc.c  */
#line 1010 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 176:

/* Line 1464 of yacc.c  */
#line 1016 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 177:

/* Line 1464 of yacc.c  */
#line 1025 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 178:

/* Line 1464 of yacc.c  */
#line 1031 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 179:

/* Line 1464 of yacc.c  */
#line 1037 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 180:

/* Line 1464 of yacc.c  */
#line 1046 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)])); // type attribute
        }
    break;

  case 181:

/* Line 1464 of yacc.c  */
#line 1051 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 182:

/* Line 1464 of yacc.c  */
#line 1057 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 183:

/* Line 1464 of yacc.c  */
#line 1066 "parser.y"
    { (yyval) = (yyvsp[(1) - (4)]);
          stack((yyval)).id(ID_typeof);
          mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 184:

/* Line 1464 of yacc.c  */
#line 1071 "parser.y"
    { (yyval) = (yyvsp[(1) - (4)]);
          stack((yyval)).id(ID_typeof);
          stack((yyval)).set(ID_type_arg, stack((yyvsp[(3) - (4)])));
        }
    break;

  case 186:

/* Line 1464 of yacc.c  */
#line 1080 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 187:

/* Line 1464 of yacc.c  */
#line 1120 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_typedef); }
    break;

  case 188:

/* Line 1464 of yacc.c  */
#line 1121 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_extern); }
    break;

  case 189:

/* Line 1464 of yacc.c  */
#line 1122 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_static); }
    break;

  case 190:

/* Line 1464 of yacc.c  */
#line 1123 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_auto); }
    break;

  case 191:

/* Line 1464 of yacc.c  */
#line 1124 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_register); }
    break;

  case 192:

/* Line 1464 of yacc.c  */
#line 1125 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_inline); }
    break;

  case 193:

/* Line 1464 of yacc.c  */
#line 1126 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_thread_local); }
    break;

  case 194:

/* Line 1464 of yacc.c  */
#line 1127 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_asm); }
    break;

  case 195:

/* Line 1464 of yacc.c  */
#line 1131 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int); }
    break;

  case 196:

/* Line 1464 of yacc.c  */
#line 1132 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int8); }
    break;

  case 197:

/* Line 1464 of yacc.c  */
#line 1133 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int16); }
    break;

  case 198:

/* Line 1464 of yacc.c  */
#line 1134 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int32); }
    break;

  case 199:

/* Line 1464 of yacc.c  */
#line 1135 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int64); }
    break;

  case 200:

/* Line 1464 of yacc.c  */
#line 1136 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_char); }
    break;

  case 201:

/* Line 1464 of yacc.c  */
#line 1137 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_short); }
    break;

  case 202:

/* Line 1464 of yacc.c  */
#line 1138 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_long); }
    break;

  case 203:

/* Line 1464 of yacc.c  */
#line 1139 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_float); }
    break;

  case 204:

/* Line 1464 of yacc.c  */
#line 1140 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_gcc_float128); }
    break;

  case 205:

/* Line 1464 of yacc.c  */
#line 1141 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_double); }
    break;

  case 206:

/* Line 1464 of yacc.c  */
#line 1142 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_signed); }
    break;

  case 207:

/* Line 1464 of yacc.c  */
#line 1143 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_unsigned); }
    break;

  case 208:

/* Line 1464 of yacc.c  */
#line 1144 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_void); }
    break;

  case 209:

/* Line 1464 of yacc.c  */
#line 1145 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_bool); }
    break;

  case 210:

/* Line 1464 of yacc.c  */
#line 1146 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_complex); }
    break;

  case 211:

/* Line 1464 of yacc.c  */
#line 1148 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_bv);
          stack((yyval)).add(ID_size).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 212:

/* Line 1464 of yacc.c  */
#line 1153 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_proper_bool); }
    break;

  case 216:

/* Line 1464 of yacc.c  */
#line 1164 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]); ((typet &)stack((yyval))).subtype().swap(stack((yyvsp[(2) - (4)]))); }
    break;

  case 217:

/* Line 1464 of yacc.c  */
#line 1170 "parser.y"
    {
            // an anon struct/union
            exprt symbol(ID_symbol);
            symbol.set(ID_C_base_name, PARSER.get_anon_name());

            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), symbol, stack((yyval)), true);
          }
    break;

  case 218:

/* Line 1464 of yacc.c  */
#line 1180 "parser.y"
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

  case 219:

/* Line 1464 of yacc.c  */
#line 1198 "parser.y"
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

  case 220:

/* Line 1464 of yacc.c  */
#line 1211 "parser.y"
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

  case 221:

/* Line 1464 of yacc.c  */
#line 1230 "parser.y"
    {
          do_tag((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
          (yyval)=(yyvsp[(3) - (4)]);
          // type attributes
          merge_types((yyval), (yyvsp[(2) - (4)]));
          merge_types((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 222:

/* Line 1464 of yacc.c  */
#line 1241 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_struct); }
    break;

  case 223:

/* Line 1464 of yacc.c  */
#line 1243 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_union); }
    break;

  case 224:

/* Line 1464 of yacc.c  */
#line 1248 "parser.y"
    {
          init((yyval));
        }
    break;

  case 227:

/* Line 1464 of yacc.c  */
#line 1257 "parser.y"
    {
          merge_types((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 228:

/* Line 1464 of yacc.c  */
#line 1264 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); set((yyval), ID_packed); }
    break;

  case 229:

/* Line 1464 of yacc.c  */
#line 1266 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); set((yyval), ID_transparent_union); }
    break;

  case 230:

/* Line 1464 of yacc.c  */
#line 1268 "parser.y"
    { (yyval)=(yyvsp[(1) - (5)]); set((yyval), ID_vector); stack((yyval)).add(ID_size)=stack((yyvsp[(3) - (5)])); }
    break;

  case 231:

/* Line 1464 of yacc.c  */
#line 1270 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); set((yyval), ID_aligned); }
    break;

  case 232:

/* Line 1464 of yacc.c  */
#line 1272 "parser.y"
    { (yyval)=(yyvsp[(1) - (5)]); set((yyval), ID_aligned); stack((yyval)).set(ID_size, stack((yyvsp[(3) - (5)]))); }
    break;

  case 233:

/* Line 1464 of yacc.c  */
#line 1274 "parser.y"
    { (yyval)=(yyvsp[(1) - (5)]); set((yyval), ID_gcc_attribute_mode); stack((yyval)).set(ID_size, stack((yyvsp[(3) - (5)])).get(ID_identifier)); }
    break;

  case 234:

/* Line 1464 of yacc.c  */
#line 1279 "parser.y"
    {
          init((yyval), ID_declaration_list);
        }
    break;

  case 237:

/* Line 1464 of yacc.c  */
#line 1288 "parser.y"
    {
          assert(stack((yyvsp[(1) - (2)])).id()==ID_declaration_list);
          assert(stack((yyvsp[(2) - (2)])).id()==ID_declaration_list);
          (yyval)=(yyvsp[(1) - (2)]);
          Forall_operands(it, stack((yyvsp[(2) - (2)])))
            stack((yyval)).move_to_operands(*it);
          stack((yyvsp[(2) - (2)])).clear();
        }
    break;

  case 240:

/* Line 1464 of yacc.c  */
#line 1302 "parser.y"
    {
          init((yyval), ID_declaration_list);
        }
    break;

  case 241:

/* Line 1464 of yacc.c  */
#line 1306 "parser.y"
    {
          init((yyval), ID_declaration_list);
          mto((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 242:

/* Line 1464 of yacc.c  */
#line 1316 "parser.y"
    {
          merge_types((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)])); // type attribute

          init((yyval), ID_declaration_list);

          exprt declaration;
          PARSER.new_declaration(stack((yyvsp[(2) - (3)])), stack((yyvsp[(3) - (3)])), declaration, false, false);

          stack((yyval)).move_to_operands(declaration);
        }
    break;

  case 243:

/* Line 1464 of yacc.c  */
#line 1327 "parser.y"
    {
          exprt declaration;
          PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(3) - (3)])), declaration, false, false);

          (yyval)=(yyvsp[(1) - (3)]);
          stack((yyval)).move_to_operands(declaration);
        }
    break;

  case 244:

/* Line 1464 of yacc.c  */
#line 1340 "parser.y"
    {
          // TODO merge_types($2, $1); // type attribute

          init((yyval), ID_declaration_list);

          // save the type_specifier for later
          stack((yyval)).add(ID_type)=stack((yyvsp[(2) - (3)]));

          exprt declaration;
          PARSER.new_declaration(stack((yyvsp[(2) - (3)])), stack((yyvsp[(3) - (3)])), declaration, false, false);

          stack((yyval)).move_to_operands(declaration);
        }
    break;

  case 245:

/* Line 1464 of yacc.c  */
#line 1354 "parser.y"
    {
          exprt declaration;

          irept declaration_type=stack((yyvsp[(1) - (3)])).find(ID_type);
          PARSER.new_declaration(declaration_type, stack((yyvsp[(3) - (3)])), declaration, false, false);

          (yyval)=(yyvsp[(1) - (3)]);
          stack((yyval)).move_to_operands(declaration);
        }
    break;

  case 246:

/* Line 1464 of yacc.c  */
#line 1367 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);

          if(stack((yyvsp[(2) - (3)])).is_not_nil())
            make_subtype((yyval), (yyvsp[(2) - (3)]));

          if(stack((yyvsp[(3) - (3)])).is_not_nil()) // type attribute
          {
            merge_types(stack((yyvsp[(3) - (3)])), stack((yyval)));
            stack((yyval)).swap(stack((yyvsp[(3) - (3)])));
          }
        }
    break;

  case 247:

/* Line 1464 of yacc.c  */
#line 1380 "parser.y"
    {
          init((yyval), ID_abstract);
        }
    break;

  case 248:

/* Line 1464 of yacc.c  */
#line 1384 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);

          if(stack((yyvsp[(2) - (2)])).is_not_nil()) // type attribute
          {
            merge_types(stack((yyvsp[(2) - (2)])), stack((yyval)));
            stack((yyval)).swap(stack((yyvsp[(2) - (2)])));
          }
        }
    break;

  case 249:

/* Line 1464 of yacc.c  */
#line 1398 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          if(stack((yyvsp[(2) - (3)])).is_not_nil())
            make_subtype((yyval), (yyvsp[(2) - (3)]));
          
          if(stack((yyvsp[(3) - (3)])).is_not_nil()) // type attribute
          {
            merge_types(stack((yyvsp[(3) - (3)])), stack((yyval)));
            stack((yyval)).swap(stack((yyvsp[(3) - (3)])));
          }
        }
    break;

  case 250:

/* Line 1464 of yacc.c  */
#line 1410 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);

          if(stack((yyvsp[(2) - (2)])).is_not_nil()) // type attribute
          {
            merge_types(stack((yyvsp[(2) - (2)])), stack((yyval)));
            stack((yyval)).swap(stack((yyvsp[(2) - (2)])));
          }
        }
    break;

  case 251:

/* Line 1464 of yacc.c  */
#line 1424 "parser.y"
    {
          init((yyval), ID_nil);
        }
    break;

  case 253:

/* Line 1464 of yacc.c  */
#line 1432 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_c_bitfield);
          stack((yyval)).set(ID_size, stack((yyvsp[(2) - (2)])));
          stack((yyval)).add(ID_subtype).id(ID_abstract);
        }
    break;

  case 254:

/* Line 1464 of yacc.c  */
#line 1443 "parser.y"
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

  case 255:

/* Line 1464 of yacc.c  */
#line 1455 "parser.y"
    {
          // grab symbol
          init((yyval), ID_symbol);
          stack((yyval)).set(ID_identifier, stack((yyvsp[(3) - (7)])).get(ID_name));
          stack((yyval)).location()=stack((yyvsp[(3) - (7)])).location();

          // throw in the gcc attributes
          merge_types((yyval), (yyvsp[(2) - (7)]));
          merge_types((yyval), (yyvsp[(7) - (7)]));

          do_enum_members((const typet &)stack((yyval)), stack((yyvsp[(5) - (7)])));
        }
    break;

  case 256:

/* Line 1464 of yacc.c  */
#line 1470 "parser.y"
    {
            // we want the tag to be visible before the members
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(3) - (3)])), stack((yyval)), true);
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 257:

/* Line 1464 of yacc.c  */
#line 1478 "parser.y"
    {
          // grab symbol
          init((yyval), ID_symbol);
          stack((yyval)).set(ID_identifier, stack((yyvsp[(4) - (8)])).get(ID_name));
          stack((yyval)).location()=stack((yyvsp[(4) - (8)])).location();

          // throw in the gcc attributes
          merge_types((yyval), (yyvsp[(2) - (8)]));
          merge_types((yyval), (yyvsp[(8) - (8)]));

          do_enum_members((const typet &)stack((yyval)), stack((yyvsp[(6) - (8)])));
        }
    break;

  case 258:

/* Line 1464 of yacc.c  */
#line 1493 "parser.y"
    {
          do_tag((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
          (yyval)=(yyvsp[(3) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 259:

/* Line 1464 of yacc.c  */
#line 1501 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          set((yyval), ID_c_enum);
        }
    break;

  case 260:

/* Line 1464 of yacc.c  */
#line 1509 "parser.y"
    {
          init((yyval));
          mto((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 261:

/* Line 1464 of yacc.c  */
#line 1514 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 262:

/* Line 1464 of yacc.c  */
#line 1519 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
        }
    break;

  case 263:

/* Line 1464 of yacc.c  */
#line 1526 "parser.y"
    {
          init((yyval));
          irept type(ID_c_enum);
          PARSER.new_declaration(type, stack((yyvsp[(1) - (2)])), stack((yyval)));
          stack((yyval)).set(ID_is_macro, true);
          stack((yyval)).add(ID_value).swap(stack((yyvsp[(2) - (2)])));
        }
    break;

  case 264:

/* Line 1464 of yacc.c  */
#line 1537 "parser.y"
    {
          init((yyval));
          stack((yyval)).make_nil();
        }
    break;

  case 265:

/* Line 1464 of yacc.c  */
#line 1542 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
        }
    break;

  case 267:

/* Line 1464 of yacc.c  */
#line 1550 "parser.y"
    {
          typet tmp(ID_ellipsis);
          (yyval)=(yyvsp[(1) - (3)]);
          ((typet &)stack((yyval))).move_to_subtypes(tmp);
        }
    break;

  case 268:

/* Line 1464 of yacc.c  */
#line 1559 "parser.y"
    {
          init((yyval), ID_arguments);
          mts((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 269:

/* Line 1464 of yacc.c  */
#line 1564 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mts((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 270:

/* Line 1464 of yacc.c  */
#line 1571 "parser.y"
    {
          init((yyval));
          irept type(ID_KnR);
          PARSER.new_declaration(type, stack((yyvsp[(1) - (1)])), stack((yyval)));
        }
    break;

  case 271:

/* Line 1464 of yacc.c  */
#line 1580 "parser.y"
    {
          init((yyval), ID_arguments);
          mts((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 272:

/* Line 1464 of yacc.c  */
#line 1585 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mts((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 273:

/* Line 1464 of yacc.c  */
#line 1593 "parser.y"
    {
          init((yyval));
          exprt declarator=exprt(ID_abstract);
          PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
        }
    break;

  case 274:

/* Line 1464 of yacc.c  */
#line 1599 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 275:

/* Line 1464 of yacc.c  */
#line 1604 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 276:

/* Line 1464 of yacc.c  */
#line 1609 "parser.y"
    {
          // the second tree is really the argument -- not part
          // of the type!
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 277:

/* Line 1464 of yacc.c  */
#line 1616 "parser.y"
    {
          init((yyval));
          exprt declarator=exprt(ID_abstract);
          PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
        }
    break;

  case 278:

/* Line 1464 of yacc.c  */
#line 1622 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 279:

/* Line 1464 of yacc.c  */
#line 1627 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 280:

/* Line 1464 of yacc.c  */
#line 1632 "parser.y"
    {
          init((yyval));
          exprt declarator=exprt(ID_abstract);
          PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
        }
    break;

  case 281:

/* Line 1464 of yacc.c  */
#line 1638 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 282:

/* Line 1464 of yacc.c  */
#line 1643 "parser.y"
    {
          init((yyval));
          stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 283:

/* Line 1464 of yacc.c  */
#line 1649 "parser.y"
    {
          // the second tree is really the argument -- not part
          // of the type!
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 284:

/* Line 1464 of yacc.c  */
#line 1656 "parser.y"
    {
          init((yyval));
          exprt declarator=exprt(ID_abstract);
          PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
        }
    break;

  case 285:

/* Line 1464 of yacc.c  */
#line 1662 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 286:

/* Line 1464 of yacc.c  */
#line 1667 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 290:

/* Line 1464 of yacc.c  */
#line 1681 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          make_subtype((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 292:

/* Line 1464 of yacc.c  */
#line 1687 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          make_subtype((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 293:

/* Line 1464 of yacc.c  */
#line 1695 "parser.y"
    {
          newstack((yyval));
          stack((yyval)).make_nil();
        }
    break;

  case 294:

/* Line 1464 of yacc.c  */
#line 1700 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 297:

/* Line 1464 of yacc.c  */
#line 1712 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          set((yyval), ID_initializer_list);
          stack((yyval)).operands().swap(stack((yyvsp[(2) - (3)])).operands());
        }
    break;

  case 298:

/* Line 1464 of yacc.c  */
#line 1718 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_initializer_list);
          stack((yyval)).operands().swap(stack((yyvsp[(2) - (4)])).operands());
        }
    break;

  case 299:

/* Line 1464 of yacc.c  */
#line 1727 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          exprt tmp;
          tmp.swap(stack((yyval)));
          stack((yyval)).clear();
          stack((yyval)).move_to_operands(tmp);
        }
    break;

  case 300:

/* Line 1464 of yacc.c  */
#line 1735 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 302:

/* Line 1464 of yacc.c  */
#line 1744 "parser.y"
    {
          init((yyval));
          set((yyval), ID_initializer_list);
          stack((yyval)).operands().clear();
        }
    break;

  case 303:

/* Line 1464 of yacc.c  */
#line 1754 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (3)]);
          stack((yyval)).id(ID_designated_initializer);
          stack((yyval)).add(ID_designator).swap(stack((yyvsp[(1) - (3)])));
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 304:

/* Line 1464 of yacc.c  */
#line 1762 "parser.y"
    {
          init((yyval), ID_designated_initializer);
          stack((yyval)).add(ID_designator).swap(stack((yyvsp[(1) - (2)])));
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 305:

/* Line 1464 of yacc.c  */
#line 1768 "parser.y"
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

  case 306:

/* Line 1464 of yacc.c  */
#line 1783 "parser.y"
    {
          init((yyval));
          stack((yyvsp[(1) - (2)])).id(ID_member);
          stack((yyvsp[(1) - (2)])).set(ID_component_name, stack((yyvsp[(2) - (2)])).get(ID_C_base_name));
          mto((yyval), (yyvsp[(1) - (2)]));
        }
    break;

  case 307:

/* Line 1464 of yacc.c  */
#line 1790 "parser.y"
    {
          init((yyval));
          stack((yyvsp[(1) - (3)])).id(ID_index);
          mto((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
          mto((yyval), (yyvsp[(1) - (3)]));
        }
    break;

  case 308:

/* Line 1464 of yacc.c  */
#line 1797 "parser.y"
    {
          // TODO
          init((yyval));
          stack((yyvsp[(1) - (5)])).id(ID_index);
          mto((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]));
          mto((yyval), (yyvsp[(1) - (5)]));
        }
    break;

  case 309:

/* Line 1464 of yacc.c  */
#line 1805 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          stack((yyvsp[(2) - (4)])).id(ID_index);
          mto((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]));
          mto((yyval), (yyvsp[(2) - (4)]));
        }
    break;

  case 310:

/* Line 1464 of yacc.c  */
#line 1812 "parser.y"
    {
          // TODO
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyvsp[(2) - (6)])).id(ID_index);
          mto((yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]));
          mto((yyval), (yyvsp[(2) - (6)]));
        }
    break;

  case 311:

/* Line 1464 of yacc.c  */
#line 1820 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          stack((yyvsp[(2) - (3)])).id(ID_member);
          stack((yyvsp[(2) - (3)])).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
          mto((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 323:

/* Line 1464 of yacc.c  */
#line 1846 "parser.y"
    {
          init((yyval));
          statement((yyval), ID_decl_block);
          stack((yyval)).operands().swap(stack((yyvsp[(1) - (1)])).operands());
        }
    break;

  case 324:

/* Line 1464 of yacc.c  */
#line 1855 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (3)]);
          statement((yyval), ID_label);
          irep_idt identifier=PARSER.lookup_label(stack((yyvsp[(1) - (3)])).get(ID_C_base_name));
          stack((yyval)).set(ID_label, identifier);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 325:

/* Line 1464 of yacc.c  */
#line 1863 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_label);
          mto((yyval), (yyvsp[(4) - (4)]));
          static_cast<exprt &>(stack((yyval)).add(ID_case)).
                move_to_operands(stack((yyvsp[(2) - (4)])));
        }
    break;

  case 326:

/* Line 1464 of yacc.c  */
#line 1871 "parser.y"
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

  case 327:

/* Line 1464 of yacc.c  */
#line 1881 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          statement((yyval), ID_label);
          mto((yyval), (yyvsp[(3) - (3)]));
          stack((yyval)).set(ID_default, true);
        }
    break;

  case 328:

/* Line 1464 of yacc.c  */
#line 1895 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (3)]);
          statement((yyval), ID_block);
          stack((yyval)).set(ID_C_end_location, stack((yyvsp[(3) - (3)])).location());
          PARSER.pop_scope();
        }
    break;

  case 329:

/* Line 1464 of yacc.c  */
#line 1902 "parser.y"
    {
          (yyval)=(yyvsp[(3) - (4)]);
          stack((yyval)).location()=stack((yyvsp[(2) - (4)])).location();
          stack((yyval)).set(ID_C_end_location, stack((yyvsp[(4) - (4)])).location());
          PARSER.pop_scope();
        }
    break;

  case 330:

/* Line 1464 of yacc.c  */
#line 1909 "parser.y"
    {
          init((yyval));
          stack((yyval)).location()=stack((yyvsp[(2) - (4)])).location();
          stack((yyval)).set(ID_statement, ID_asm);
          mto((yyval), (yyvsp[(3) - (4)]));
          PARSER.pop_scope();
        }
    break;

  case 331:

/* Line 1464 of yacc.c  */
#line 1920 "parser.y"
    {
          unsigned prefix=++PARSER.current_scope().compound_counter;
          PARSER.new_scope(i2string(prefix)+"::");
        }
    break;

  case 332:

/* Line 1464 of yacc.c  */
#line 1928 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          to_code(stack((yyval))).make_block();
        }
    break;

  case 333:

/* Line 1464 of yacc.c  */
#line 1933 "parser.y"
    {
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 334:

/* Line 1464 of yacc.c  */
#line 1940 "parser.y"
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

  case 335:

/* Line 1464 of yacc.c  */
#line 1955 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          statement((yyval), ID_ifthenelse);
          stack((yyval)).operands().reserve(2);
          mto((yyval), (yyvsp[(3) - (5)]));
          mto((yyval), (yyvsp[(5) - (5)]));
        }
    break;

  case 336:

/* Line 1464 of yacc.c  */
#line 1963 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (7)]);
          statement((yyval), ID_ifthenelse);
          stack((yyval)).operands().reserve(3);
          mto((yyval), (yyvsp[(3) - (7)]));
          mto((yyval), (yyvsp[(5) - (7)]));
          mto((yyval), (yyvsp[(7) - (7)]));
        }
    break;

  case 337:

/* Line 1464 of yacc.c  */
#line 1972 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          statement((yyval), ID_switch);
          stack((yyval)).operands().reserve(2);
          mto((yyval), (yyvsp[(3) - (5)]));
          mto((yyval), (yyvsp[(5) - (5)]));
        }
    break;

  case 340:

/* Line 1464 of yacc.c  */
#line 1988 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          statement((yyval), ID_while);
          stack((yyval)).operands().reserve(2);
          mto((yyval), (yyvsp[(3) - (5)]));
          mto((yyval), (yyvsp[(5) - (5)]));
        }
    break;

  case 341:

/* Line 1464 of yacc.c  */
#line 1996 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (7)]);
          statement((yyval), ID_dowhile);
          stack((yyval)).operands().reserve(2);
          mto((yyval), (yyvsp[(5) - (7)]));
          mto((yyval), (yyvsp[(2) - (7)]));
        }
    break;

  case 342:

/* Line 1464 of yacc.c  */
#line 2005 "parser.y"
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

  case 343:

/* Line 1464 of yacc.c  */
#line 2018 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          if(stack((yyvsp[(2) - (3)])).id()==ID_symbol)
          {
            statement((yyval), ID_goto);
            irep_idt identifier=PARSER.lookup_label(stack((yyvsp[(2) - (3)])).get(ID_C_base_name));
            stack((yyval)).set(ID_destination, identifier);
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

  case 344:

/* Line 1464 of yacc.c  */
#line 2035 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); statement((yyval), ID_continue); }
    break;

  case 345:

/* Line 1464 of yacc.c  */
#line 2037 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); statement((yyval), ID_break); }
    break;

  case 346:

/* Line 1464 of yacc.c  */
#line 2039 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); statement((yyval), ID_return); }
    break;

  case 347:

/* Line 1464 of yacc.c  */
#line 2041 "parser.y"
    { (yyval)=(yyvsp[(1) - (3)]); statement((yyval), ID_return); mto((yyval), (yyvsp[(2) - (3)])); }
    break;

  case 348:

/* Line 1464 of yacc.c  */
#line 2046 "parser.y"
    { 
          (yyval)=(yyvsp[(1) - (3)]);
          statement((yyval), ID_gcc_local_label);
          
          // put these into the scope
          forall_operands(it, stack((yyvsp[(2) - (3)])))
          {
            // labels have a separate name space
            irep_idt base_name=it->get(ID_identifier);
            irep_idt id="label-"+id2string(base_name);
            ansi_c_parsert::identifiert &i=PARSER.current_scope().name_map[id];
            i.id_class=ANSI_C_LOCAL_LABEL;
            i.base_name=base_name;
          }

          stack((yyval)).add(ID_label).get_sub().swap(stack((yyvsp[(2) - (3)])).add(ID_operands).get_sub());
        }
    break;

  case 349:

/* Line 1464 of yacc.c  */
#line 2067 "parser.y"
    {
          init((yyval));
          mto((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 350:

/* Line 1464 of yacc.c  */
#line 2072 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 352:

/* Line 1464 of yacc.c  */
#line 2083 "parser.y"
    { (yyval)=(yyvsp[(1) - (6)]);
          statement((yyval), ID_asm);
          stack((yyval)).set(ID_flavor, ID_gcc);
          stack((yyval)).operands().swap(stack((yyvsp[(4) - (6)])).operands());
        }
    break;

  case 353:

/* Line 1464 of yacc.c  */
#line 2089 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_asm);
          stack((yyval)).set(ID_flavor, ID_gcc);
          mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 354:

/* Line 1464 of yacc.c  */
#line 2099 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_asm);
          stack((yyval)).set(ID_flavor, ID_msc);
          mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 355:

/* Line 1464 of yacc.c  */
#line 2105 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          statement((yyval), ID_asm);
          stack((yyval)).set(ID_flavor, ID_msc);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 356:

/* Line 1464 of yacc.c  */
#line 2115 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (7)]);
          statement((yyval), ID_msc_try_except);
          mto((yyval), (yyvsp[(2) - (7)]));
          mto((yyval), (yyvsp[(5) - (7)]));
          mto((yyval), (yyvsp[(7) - (7)]));
        }
    break;

  case 357:

/* Line 1464 of yacc.c  */
#line 2124 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_msc_try_finally);
          mto((yyval), (yyvsp[(2) - (4)]));
          mto((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 358:

/* Line 1464 of yacc.c  */
#line 2131 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          statement((yyval), ID_msc_leave);
        }
    break;

  case 362:

/* Line 1464 of yacc.c  */
#line 2153 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (1)]));
          }
    break;

  case 363:

/* Line 1464 of yacc.c  */
#line 2158 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (2)]));
          }
    break;

  case 364:

/* Line 1464 of yacc.c  */
#line 2163 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (3)]));
          }
    break;

  case 365:

/* Line 1464 of yacc.c  */
#line 2168 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (4)]));
          }
    break;

  case 366:

/* Line 1464 of yacc.c  */
#line 2173 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (5)]));
          }
    break;

  case 398:

/* Line 1464 of yacc.c  */
#line 2266 "parser.y"
    {
          // the function symbol needs to be visible before any declarations
          // in the body (the following compound_statement)
          to_ansi_c_declaration(stack((yyvsp[(1) - (1)]))).value().make_nil();
          PARSER.copy_item(to_ansi_c_declaration(stack((yyvsp[(1) - (1)]))));
        }
    break;

  case 399:

/* Line 1464 of yacc.c  */
#line 2273 "parser.y"
    {
          // we now present the body as initializer
          to_ansi_c_declaration(stack((yyvsp[(1) - (3)]))).value().swap(stack((yyvsp[(3) - (3)])));
          PARSER.copy_item(to_ansi_c_declaration(stack((yyvsp[(1) - (3)]))));
          
          // kill scope
          PARSER.pop_scope();
          PARSER.function=irep_idt();
        }
    break;

  case 401:

/* Line 1464 of yacc.c  */
#line 2290 "parser.y"
    {
          init((yyval));
        }
    break;

  case 403:

/* Line 1464 of yacc.c  */
#line 2298 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
        }
    break;

  case 404:

/* Line 1464 of yacc.c  */
#line 2302 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          Forall_irep(it, stack((yyvsp[(2) - (2)])).get_sub())
            stack((yyval)).move_to_sub(*it);
        }
    break;

  case 406:

/* Line 1464 of yacc.c  */
#line 2328 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (2)])); // save for later
          exprt tmp;
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), tmp);
          stack((yyval)).move_to_sub(tmp);
        }
    break;

  case 407:

/* Line 1464 of yacc.c  */
#line 2336 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          // need to get type from $1
          const irept &t=stack((yyvsp[(1) - (3)])).type();
          exprt tmp;
          PARSER.new_declaration(t, stack((yyvsp[(3) - (3)])), tmp);
          stack((yyval)).move_to_sub(tmp);
        }
    break;

  case 408:

/* Line 1464 of yacc.c  */
#line 2348 "parser.y"
    {
          init((yyval));
          irept return_type(ID_int);
          PARSER.new_declaration(return_type, stack((yyvsp[(1) - (1)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 409:

/* Line 1464 of yacc.c  */
#line 2355 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 410:

/* Line 1464 of yacc.c  */
#line 2361 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 411:

/* Line 1464 of yacc.c  */
#line 2367 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 412:

/* Line 1464 of yacc.c  */
#line 2373 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 418:

/* Line 1464 of yacc.c  */
#line 2393 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          make_subtype((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 421:

/* Line 1464 of yacc.c  */
#line 2403 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 422:

/* Line 1464 of yacc.c  */
#line 2408 "parser.y"
    {
          merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
          (yyval)=(yyvsp[(2) - (3)]);
          do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
        }
    break;

  case 423:

/* Line 1464 of yacc.c  */
#line 2417 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 424:

/* Line 1464 of yacc.c  */
#line 2419 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          /* or an array ($4)! */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 426:

/* Line 1464 of yacc.c  */
#line 2430 "parser.y"
    {
          (yyval)=(yyvsp[(3) - (4)]);
          do_pointer((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 427:

/* Line 1464 of yacc.c  */
#line 2435 "parser.y"
    {
          // not sure where the type qualifiers belong
          merge_types((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]));
          (yyval)=(yyvsp[(2) - (5)]);
          do_pointer((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]));
        }
    break;

  case 428:

/* Line 1464 of yacc.c  */
#line 2442 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 429:

/* Line 1464 of yacc.c  */
#line 2447 "parser.y"
    {
          merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
          (yyval)=(yyvsp[(2) - (3)]);
          do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
        }
    break;

  case 430:

/* Line 1464 of yacc.c  */
#line 2456 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 431:

/* Line 1464 of yacc.c  */
#line 2458 "parser.y"
    {        /* note: this is a function ($3) with a typedef name ($2) */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 432:

/* Line 1464 of yacc.c  */
#line 2463 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          /* or an array ($4)! */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 434:

/* Line 1464 of yacc.c  */
#line 2474 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 438:

/* Line 1464 of yacc.c  */
#line 2485 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 439:

/* Line 1464 of yacc.c  */
#line 2490 "parser.y"
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

  case 440:

/* Line 1464 of yacc.c  */
#line 2503 "parser.y"
    {
          /* note: this is a function or array ($2) with name ($1) */
          (yyval)=(yyvsp[(1) - (2)]);
          make_subtype((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 441:

/* Line 1464 of yacc.c  */
#line 2509 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 442:

/* Line 1464 of yacc.c  */
#line 2511 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          /* or an array ($4)! */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 444:

/* Line 1464 of yacc.c  */
#line 2522 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 451:

/* Line 1464 of yacc.c  */
#line 2539 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_code);
          stack((yyval)).add(ID_arguments);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 452:

/* Line 1464 of yacc.c  */
#line 2546 "parser.y"
    {
            unsigned prefix=++PARSER.current_scope().compound_counter;
            PARSER.new_scope(i2string(prefix)+"::");
          }
    break;

  case 453:

/* Line 1464 of yacc.c  */
#line 2552 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_code);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          stack((yyval)).add(ID_arguments).get_sub().
            swap(stack((yyvsp[(3) - (4)])).add(ID_subtypes).get_sub());
          PARSER.pop_scope();
        }
    break;

  case 454:

/* Line 1464 of yacc.c  */
#line 2562 "parser.y"
    {
            unsigned prefix=++PARSER.current_scope().compound_counter;
            PARSER.new_scope(i2string(prefix)+"::");
          }
    break;

  case 455:

/* Line 1464 of yacc.c  */
#line 2569 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          set((yyval), ID_code);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          stack((yyval)).add(ID_arguments).get_sub().
            swap(stack((yyvsp[(3) - (5)])).add(ID_subtypes).get_sub());
          PARSER.pop_scope();
          adjust_KnR_arguments(stack((yyval)).add(ID_arguments), stack((yyvsp[(5) - (5)])));
          stack((yyval)).set(ID_C_KnR, true);
        }
    break;

  case 457:

/* Line 1464 of yacc.c  */
#line 2584 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_code);
          stack((yyval)).add(ID_arguments);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 458:

/* Line 1464 of yacc.c  */
#line 2591 "parser.y"
    {
            unsigned prefix=++PARSER.current_scope().compound_counter;
            PARSER.new_scope(i2string(prefix)+"::");
          }
    break;

  case 459:

/* Line 1464 of yacc.c  */
#line 2597 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_code);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          stack((yyval)).add(ID_arguments).get_sub().
            swap(stack((yyvsp[(3) - (4)])).add(ID_subtypes).get_sub());
          PARSER.pop_scope();
        }
    break;

  case 460:

/* Line 1464 of yacc.c  */
#line 2609 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_array);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          stack((yyval)).add(ID_size).make_nil();
        }
    break;

  case 461:

/* Line 1464 of yacc.c  */
#line 2616 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          set((yyval), ID_array);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          stack((yyval)).add(ID_size).make_nil();
        }
    break;

  case 462:

/* Line 1464 of yacc.c  */
#line 2623 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          set((yyval), ID_array);
          stack((yyval)).add(ID_size).swap(stack((yyvsp[(2) - (3)])));
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 463:

/* Line 1464 of yacc.c  */
#line 2630 "parser.y"
    {
          // we need to push this down
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyvsp[(2) - (4)]), ID_array);
          stack((yyvsp[(2) - (4)])).add(ID_size).swap(stack((yyvsp[(3) - (4)])));
          stack((yyvsp[(2) - (4)])).add(ID_subtype)=irept(ID_abstract);
          make_subtype((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]));
        }
    break;

  case 464:

/* Line 1464 of yacc.c  */
#line 2642 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          set((yyval), ID_pointer);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 465:

/* Line 1464 of yacc.c  */
#line 2648 "parser.y"
    {
          // tye type_qualifier_list belongs to the pointer,
          // not to the (missing) abstract declarator
          (yyval)=(yyvsp[(2) - (2)]);
          exprt declarator=exprt(ID_abstract);
          merge_types(stack((yyvsp[(2) - (2)])), declarator);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 466:

/* Line 1464 of yacc.c  */
#line 2657 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 467:

/* Line 1464 of yacc.c  */
#line 2662 "parser.y"
    {
          // tye type_qualifier_list belongs to the pointer,
          // not to the abstract declarator
          (yyval)=(yyvsp[(2) - (3)]);
          merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
          do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
        }
    break;

  case 468:

/* Line 1464 of yacc.c  */
#line 2673 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          set((yyval), ID_pointer);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 469:

/* Line 1464 of yacc.c  */
#line 2679 "parser.y"
    {
          // tye type_qualifier_list belongs to the pointer,
          // not to the (missing) abstract declarator
          (yyval)=(yyvsp[(2) - (2)]);
          exprt declarator=exprt(ID_abstract);
          merge_types(stack((yyvsp[(2) - (2)])), declarator);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 470:

/* Line 1464 of yacc.c  */
#line 2688 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 471:

/* Line 1464 of yacc.c  */
#line 2693 "parser.y"
    {
          // tye type_qualifier_list belongs to the pointer,
          // not to the (missing) abstract declarator
          (yyval)=(yyvsp[(2) - (3)]);
          merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
          do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
        }
    break;

  case 472:

/* Line 1464 of yacc.c  */
#line 2704 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 473:

/* Line 1464 of yacc.c  */
#line 2706 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 474:

/* Line 1464 of yacc.c  */
#line 2708 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 475:

/* Line 1464 of yacc.c  */
#line 2710 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 476:

/* Line 1464 of yacc.c  */
#line 2719 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 477:

/* Line 1464 of yacc.c  */
#line 2721 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 479:

/* Line 1464 of yacc.c  */
#line 2724 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;



/* Line 1464 of yacc.c  */
#line 6686 "y.tab.cpp"
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
#line 2731 "parser.y"


