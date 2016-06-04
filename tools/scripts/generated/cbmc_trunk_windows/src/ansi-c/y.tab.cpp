/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         yyansi_cparse
#define yylex           yyansi_clex
#define yyerror         yyansi_cerror
#define yylval          yyansi_clval
#define yychar          yyansi_cchar
#define yydebug         yyansi_cdebug
#define yynerrs         yyansi_cnerrs

/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
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

int yyansi_clex();
extern char *yyansi_ctext;

#include "parser_static.inc"

#include "y.tab.h"

/*** token declaration **************************************************/
/* Line 371 of yacc.c  */
#line 217 "parser.y"

/************************************************************************/
/*** rules **************************************************************/
/************************************************************************/

/* Line 371 of yacc.c  */
#line 107 "y.tab.cpp"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.hpp".  */
#ifndef YY_YYANSI_C_Y_TAB_HPP_INCLUDED
# define YY_YYANSI_C_Y_TAB_HPP_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yyansi_cdebug;
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
     TOK_RESTRICT = 280,
     TOK_RETURN = 281,
     TOK_SHORT = 282,
     TOK_SIGNED = 283,
     TOK_SIZEOF = 284,
     TOK_STATIC = 285,
     TOK_STRUCT = 286,
     TOK_SWITCH = 287,
     TOK_TYPEDEF = 288,
     TOK_UNION = 289,
     TOK_UNSIGNED = 290,
     TOK_VOID = 291,
     TOK_VOLATILE = 292,
     TOK_WCHAR_T = 293,
     TOK_WHILE = 294,
     TOK_ARROW = 295,
     TOK_INCR = 296,
     TOK_DECR = 297,
     TOK_SHIFTLEFT = 298,
     TOK_SHIFTRIGHT = 299,
     TOK_LE = 300,
     TOK_GE = 301,
     TOK_EQ = 302,
     TOK_NE = 303,
     TOK_ANDAND = 304,
     TOK_OROR = 305,
     TOK_ELLIPSIS = 306,
     TOK_MULTASSIGN = 307,
     TOK_DIVASSIGN = 308,
     TOK_MODASSIGN = 309,
     TOK_PLUSASSIGN = 310,
     TOK_MINUSASSIGN = 311,
     TOK_SHLASSIGN = 312,
     TOK_SHRASSIGN = 313,
     TOK_ANDASSIGN = 314,
     TOK_XORASSIGN = 315,
     TOK_ORASSIGN = 316,
     TOK_IDENTIFIER = 317,
     TOK_TYPEDEFNAME = 318,
     TOK_INTEGER = 319,
     TOK_FLOATING = 320,
     TOK_CHARACTER = 321,
     TOK_STRING = 322,
     TOK_ASM_STRING = 323,
     TOK_INT8 = 324,
     TOK_INT16 = 325,
     TOK_INT32 = 326,
     TOK_INT64 = 327,
     TOK_PTR32 = 328,
     TOK_PTR64 = 329,
     TOK_TYPEOF = 330,
     TOK_GCC_FLOAT128 = 331,
     TOK_GCC_INT128 = 332,
     TOK_GCC_DECIMAL32 = 333,
     TOK_GCC_DECIMAL64 = 334,
     TOK_GCC_DECIMAL128 = 335,
     TOK_GCC_ASM = 336,
     TOK_GCC_ASM_PAREN = 337,
     TOK_GCC_ATTRIBUTE_ALIGNED = 338,
     TOK_GCC_ATTRIBUTE_TRANSPARENT_UNION = 339,
     TOK_GCC_ATTRIBUTE_PACKED = 340,
     TOK_GCC_ATTRIBUTE_VECTOR_SIZE = 341,
     TOK_GCC_ATTRIBUTE_MODE = 342,
     TOK_GCC_ATTRIBUTE_END = 343,
     TOK_GCC_LABEL = 344,
     TOK_MSC_ASM = 345,
     TOK_CW_VAR_ARG_TYPEOF = 346,
     TOK_BUILTIN_VA_ARG = 347,
     TOK_GCC_BUILTIN_TYPES_COMPATIBLE_P = 348,
     TOK_OFFSETOF = 349,
     TOK_ALIGNOF = 350,
     TOK_MSC_FINALLY = 351,
     TOK_MSC_EXCEPT = 352,
     TOK_MSC_LEAVE = 353,
     TOK_INTERFACE = 354,
     TOK_CDECL = 355,
     TOK_STDCALL = 356,
     TOK_FASTCALL = 357,
     TOK_CLRCALL = 358,
     TOK_FORALL = 359,
     TOK_EXISTS = 360,
     TOK_ACSL_FORALL = 361,
     TOK_ACSL_EXISTS = 362,
     TOK_ARRAY_OF = 363,
     TOK_CPROVER_BITVECTOR = 364,
     TOK_CPROVER_ATOMIC = 365,
     TOK_CPROVER_BOOL = 366,
     TOK_IMPLIES = 367,
     TOK_EQUIVALENT = 368,
     TOK_TRUE = 369,
     TOK_FALSE = 370,
     TOK_REAL = 371,
     TOK_IMAG = 372,
     TOK_ALIGNAS = 373,
     TOK_ATOMIC = 374,
     TOK_GENERIC = 375,
     TOK_IMAGINARY = 376,
     TOK_NORETURN = 377,
     TOK_STATIC_ASSERT = 378,
     TOK_THREAD_LOCAL = 379,
     TOK_NULLPTR = 380,
     TOK_CONSTEXPR = 381,
     TOK_SCANNER_ERROR = 382,
     TOK_SCANNER_EOF = 383,
     TOK_CATCH = 384,
     TOK_CLASS = 385,
     TOK_DELETE = 386,
     TOK_DECLTYPE = 387,
     TOK_EXPLICIT = 388,
     TOK_FRIEND = 389,
     TOK_MUTABLE = 390,
     TOK_NAMESPACE = 391,
     TOK_NEW = 392,
     TOK_OPERATOR = 393,
     TOK_PRIVATE = 394,
     TOK_PROTECTED = 395,
     TOK_PUBLIC = 396,
     TOK_TEMPLATE = 397,
     TOK_THIS = 398,
     TOK_THROW = 399,
     TOK_TYPEID = 400,
     TOK_TYPENAME = 401,
     TOK_USING = 402,
     TOK_VIRTUAL = 403,
     TOK_TRY = 404,
     TOK_SCOPE = 405,
     TOK_DOTPM = 406,
     TOK_ARROWPM = 407,
     TOK_MSC_UNARY_TYPE_PREDICATE = 408,
     TOK_MSC_BINARY_TYPE_PREDICATE = 409,
     TOK_MSC_UUIDOF = 410,
     TOK_MSC_IF_EXISTS = 411,
     TOK_MSC_IF_NOT_EXISTS = 412,
     TOK_PARSE_LANGUAGE = 413,
     TOK_PARSE_EXPRESSION = 414,
     TOK_PARSE_TYPE = 415
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
#define TOK_RESTRICT 280
#define TOK_RETURN 281
#define TOK_SHORT 282
#define TOK_SIGNED 283
#define TOK_SIZEOF 284
#define TOK_STATIC 285
#define TOK_STRUCT 286
#define TOK_SWITCH 287
#define TOK_TYPEDEF 288
#define TOK_UNION 289
#define TOK_UNSIGNED 290
#define TOK_VOID 291
#define TOK_VOLATILE 292
#define TOK_WCHAR_T 293
#define TOK_WHILE 294
#define TOK_ARROW 295
#define TOK_INCR 296
#define TOK_DECR 297
#define TOK_SHIFTLEFT 298
#define TOK_SHIFTRIGHT 299
#define TOK_LE 300
#define TOK_GE 301
#define TOK_EQ 302
#define TOK_NE 303
#define TOK_ANDAND 304
#define TOK_OROR 305
#define TOK_ELLIPSIS 306
#define TOK_MULTASSIGN 307
#define TOK_DIVASSIGN 308
#define TOK_MODASSIGN 309
#define TOK_PLUSASSIGN 310
#define TOK_MINUSASSIGN 311
#define TOK_SHLASSIGN 312
#define TOK_SHRASSIGN 313
#define TOK_ANDASSIGN 314
#define TOK_XORASSIGN 315
#define TOK_ORASSIGN 316
#define TOK_IDENTIFIER 317
#define TOK_TYPEDEFNAME 318
#define TOK_INTEGER 319
#define TOK_FLOATING 320
#define TOK_CHARACTER 321
#define TOK_STRING 322
#define TOK_ASM_STRING 323
#define TOK_INT8 324
#define TOK_INT16 325
#define TOK_INT32 326
#define TOK_INT64 327
#define TOK_PTR32 328
#define TOK_PTR64 329
#define TOK_TYPEOF 330
#define TOK_GCC_FLOAT128 331
#define TOK_GCC_INT128 332
#define TOK_GCC_DECIMAL32 333
#define TOK_GCC_DECIMAL64 334
#define TOK_GCC_DECIMAL128 335
#define TOK_GCC_ASM 336
#define TOK_GCC_ASM_PAREN 337
#define TOK_GCC_ATTRIBUTE_ALIGNED 338
#define TOK_GCC_ATTRIBUTE_TRANSPARENT_UNION 339
#define TOK_GCC_ATTRIBUTE_PACKED 340
#define TOK_GCC_ATTRIBUTE_VECTOR_SIZE 341
#define TOK_GCC_ATTRIBUTE_MODE 342
#define TOK_GCC_ATTRIBUTE_END 343
#define TOK_GCC_LABEL 344
#define TOK_MSC_ASM 345
#define TOK_CW_VAR_ARG_TYPEOF 346
#define TOK_BUILTIN_VA_ARG 347
#define TOK_GCC_BUILTIN_TYPES_COMPATIBLE_P 348
#define TOK_OFFSETOF 349
#define TOK_ALIGNOF 350
#define TOK_MSC_FINALLY 351
#define TOK_MSC_EXCEPT 352
#define TOK_MSC_LEAVE 353
#define TOK_INTERFACE 354
#define TOK_CDECL 355
#define TOK_STDCALL 356
#define TOK_FASTCALL 357
#define TOK_CLRCALL 358
#define TOK_FORALL 359
#define TOK_EXISTS 360
#define TOK_ACSL_FORALL 361
#define TOK_ACSL_EXISTS 362
#define TOK_ARRAY_OF 363
#define TOK_CPROVER_BITVECTOR 364
#define TOK_CPROVER_ATOMIC 365
#define TOK_CPROVER_BOOL 366
#define TOK_IMPLIES 367
#define TOK_EQUIVALENT 368
#define TOK_TRUE 369
#define TOK_FALSE 370
#define TOK_REAL 371
#define TOK_IMAG 372
#define TOK_ALIGNAS 373
#define TOK_ATOMIC 374
#define TOK_GENERIC 375
#define TOK_IMAGINARY 376
#define TOK_NORETURN 377
#define TOK_STATIC_ASSERT 378
#define TOK_THREAD_LOCAL 379
#define TOK_NULLPTR 380
#define TOK_CONSTEXPR 381
#define TOK_SCANNER_ERROR 382
#define TOK_SCANNER_EOF 383
#define TOK_CATCH 384
#define TOK_CLASS 385
#define TOK_DELETE 386
#define TOK_DECLTYPE 387
#define TOK_EXPLICIT 388
#define TOK_FRIEND 389
#define TOK_MUTABLE 390
#define TOK_NAMESPACE 391
#define TOK_NEW 392
#define TOK_OPERATOR 393
#define TOK_PRIVATE 394
#define TOK_PROTECTED 395
#define TOK_PUBLIC 396
#define TOK_TEMPLATE 397
#define TOK_THIS 398
#define TOK_THROW 399
#define TOK_TYPEID 400
#define TOK_TYPENAME 401
#define TOK_USING 402
#define TOK_VIRTUAL 403
#define TOK_TRY 404
#define TOK_SCOPE 405
#define TOK_DOTPM 406
#define TOK_ARROWPM 407
#define TOK_MSC_UNARY_TYPE_PREDICATE 408
#define TOK_MSC_BINARY_TYPE_PREDICATE 409
#define TOK_MSC_UUIDOF 410
#define TOK_MSC_IF_EXISTS 411
#define TOK_MSC_IF_NOT_EXISTS 412
#define TOK_PARSE_LANGUAGE 413
#define TOK_PARSE_EXPRESSION 414
#define TOK_PARSE_TYPE 415



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yyansi_clval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyansi_cparse (void *YYPARSE_PARAM);
#else
int yyansi_cparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyansi_cparse (void);
#else
int yyansi_cparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YYANSI_C_Y_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 493 "y.tab.cpp"

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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
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
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
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
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  164
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5397

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  185
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  183
/* YYNRULES -- Number of rules.  */
#define YYNRULES  518
/* YYNRULES -- Number of states.  */
#define YYNSTATES  921

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   415

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   175,     2,     2,     2,   177,   170,     2,
     161,   162,   171,   172,   163,   173,   165,   176,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   164,   184,
     178,   183,   179,   182,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   166,     2,   167,   180,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   168,   181,   169,   174,     2,     2,     2,
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
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    14,    16,    18,    20,
      22,    24,    26,    28,    30,    32,    34,    36,    40,    42,
      44,    46,    48,    50,    52,    54,    61,    63,    67,    71,
      75,    82,    89,    94,   101,   103,   107,   112,   117,   122,
     129,   134,   141,   146,   150,   152,   157,   161,   166,   170,
     174,   177,   180,   187,   195,   197,   199,   201,   205,   207,
     210,   213,   216,   219,   222,   225,   228,   231,   234,   237,
     242,   245,   248,   250,   255,   257,   261,   265,   269,   271,
     275,   279,   281,   285,   289,   291,   295,   299,   303,   307,
     309,   313,   317,   319,   323,   325,   329,   331,   335,   337,
     341,   343,   347,   349,   353,   355,   359,   361,   367,   372,
     374,   378,   382,   386,   390,   394,   398,   402,   406,   410,
     414,   418,   420,   424,   426,   427,   429,   432,   435,   438,
     441,   444,   451,   452,   457,   458,   463,   464,   470,   476,
     478,   481,   483,   484,   486,   487,   493,   494,   500,   501,
     508,   510,   512,   514,   516,   518,   520,   522,   524,   526,
     529,   531,   534,   537,   539,   542,   545,   547,   550,   552,
     554,   556,   558,   560,   562,   564,   566,   568,   570,   572,
     576,   580,   584,   588,   591,   595,   598,   602,   605,   608,
     611,   613,   616,   619,   623,   627,   631,   635,   639,   643,
     646,   650,   654,   659,   664,   666,   669,   671,   673,   675,
     677,   679,   681,   683,   685,   687,   689,   691,   693,   695,
     697,   699,   701,   703,   705,   707,   709,   711,   713,   715,
     717,   719,   721,   723,   725,   730,   732,   734,   736,   738,
     743,   744,   752,   753,   762,   767,   769,   771,   772,   774,
     776,   779,   782,   785,   791,   794,   800,   806,   807,   809,
     811,   814,   817,   820,   822,   825,   829,   833,   837,   841,
     845,   846,   849,   853,   856,   857,   859,   862,   863,   871,
     872,   881,   885,   887,   889,   893,   896,   899,   900,   903,
     905,   909,   911,   915,   917,   919,   923,   925,   928,   932,
     935,   937,   940,   944,   946,   949,   953,   956,   958,   961,
     965,   967,   969,   971,   974,   976,   979,   980,   983,   985,
     989,   994,   996,  1000,  1002,  1003,  1005,  1009,  1012,  1016,
    1019,  1023,  1029,  1034,  1041,  1045,  1047,  1049,  1051,  1053,
    1055,  1057,  1059,  1061,  1063,  1065,  1067,  1069,  1073,  1078,
    1085,  1089,  1093,  1098,  1103,  1104,  1106,  1109,  1112,  1118,
    1126,  1132,  1134,  1136,  1142,  1150,  1151,  1161,  1165,  1168,
    1171,  1174,  1178,  1182,  1184,  1188,  1190,  1197,  1202,  1207,
    1210,  1218,  1223,  1225,  1226,  1228,  1230,  1233,  1236,  1238,
    1241,  1245,  1250,  1256,  1258,  1261,  1263,  1268,  1276,  1278,
    1282,  1285,  1287,  1292,  1300,  1302,  1306,  1309,  1311,  1313,
    1315,  1319,  1322,  1324,  1326,  1330,  1331,  1333,  1335,  1338,
    1340,  1342,  1344,  1346,  1352,  1353,  1357,  1359,  1360,  1362,
    1364,  1367,  1370,  1374,  1378,  1382,  1386,  1390,  1394,  1398,
    1400,  1402,  1405,  1408,  1412,  1414,  1417,  1420,  1423,  1426,
    1428,  1430,  1432,  1434,  1436,  1439,  1441,  1443,  1446,  1450,
    1454,  1459,  1461,  1466,  1472,  1475,  1479,  1483,  1488,  1493,
    1495,  1499,  1501,  1503,  1505,  1508,  1512,  1515,  1519,  1524,
    1526,  1530,  1532,  1534,  1536,  1538,  1540,  1542,  1545,  1546,
    1551,  1552,  1558,  1560,  1563,  1564,  1569,  1572,  1576,  1580,
    1585,  1590,  1592,  1595,  1598,  1602,  1604,  1606,  1609,  1612,
    1616,  1618,  1622,  1626,  1630,  1635,  1639,  1643,  1645
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     186,     0,    -1,   158,   329,    -1,   159,   224,    -1,   160,
     290,    -1,    62,    -1,    63,    -1,    64,    -1,    65,    -1,
      66,    -1,    67,    -1,   189,    -1,   190,    -1,   191,    -1,
     192,    -1,   187,    -1,   193,    -1,   161,   224,   162,    -1,
     204,    -1,   198,    -1,   199,    -1,   200,    -1,   202,    -1,
     203,    -1,   195,    -1,   120,   161,   223,   163,   196,   162,
      -1,   197,    -1,   196,   163,   197,    -1,   290,   164,   223,
      -1,    11,   164,   223,    -1,    92,   161,   223,   163,   290,
     162,    -1,    93,   161,   290,   163,   290,   162,    -1,    91,
     161,   290,   162,    -1,    94,   161,   290,   163,   201,   162,
      -1,   206,    -1,   201,   165,   206,    -1,   201,   166,   224,
     167,    -1,    95,   161,   208,   162,    -1,    95,   161,   290,
     162,    -1,   104,   301,   168,   227,   224,   169,    -1,   106,
     301,   227,   194,    -1,   105,   301,   168,   227,   224,   169,
      -1,   107,   301,   227,   194,    -1,   161,   300,   162,    -1,
     194,    -1,   205,   166,   224,   167,    -1,   205,   161,   162,
      -1,   205,   161,   207,   162,    -1,   205,   165,   206,    -1,
     205,    40,   206,    -1,   205,    41,    -1,   205,    42,    -1,
     161,   290,   162,   168,   294,   169,    -1,   161,   290,   162,
     168,   293,   163,   169,    -1,   187,    -1,   188,    -1,   223,
      -1,   207,   163,   223,    -1,   205,    -1,    41,   208,    -1,
      42,   208,    -1,   170,   209,    -1,    49,   289,    -1,   171,
     209,    -1,   172,   209,    -1,   173,   209,    -1,   174,   209,
      -1,   175,   209,    -1,    29,   208,    -1,    29,   161,   290,
     162,    -1,   116,   208,    -1,   117,   208,    -1,   208,    -1,
     161,   290,   162,   209,    -1,   209,    -1,   210,   171,   209,
      -1,   210,   176,   209,    -1,   210,   177,   209,    -1,   210,
      -1,   211,   172,   210,    -1,   211,   173,   210,    -1,   211,
      -1,   212,    43,   211,    -1,   212,    44,   211,    -1,   212,
      -1,   213,   178,   212,    -1,   213,   179,   212,    -1,   213,
      45,   212,    -1,   213,    46,   212,    -1,   213,    -1,   214,
      47,   213,    -1,   214,    48,   213,    -1,   214,    -1,   215,
     170,   214,    -1,   215,    -1,   216,   180,   215,    -1,   216,
      -1,   217,   181,   216,    -1,   217,    -1,   218,    49,   217,
      -1,   218,    -1,   219,    50,   218,    -1,   219,    -1,   219,
     112,   220,    -1,   220,    -1,   221,   113,   220,    -1,   221,
      -1,   221,   182,   224,   164,   222,    -1,   221,   182,   164,
     222,    -1,   222,    -1,   209,   183,   223,    -1,   209,    52,
     223,    -1,   209,    53,   223,    -1,   209,    54,   223,    -1,
     209,    55,   223,    -1,   209,    56,   223,    -1,   209,    57,
     223,    -1,   209,    58,   223,    -1,   209,    59,   223,    -1,
     209,    60,   223,    -1,   209,    61,   223,    -1,   223,    -1,
     224,   163,   223,    -1,   223,    -1,    -1,   224,    -1,   240,
     184,    -1,   241,   184,    -1,   236,   184,    -1,   229,   184,
      -1,   228,   184,    -1,   123,   161,   223,   163,   223,   162,
      -1,    -1,   242,   352,   230,   291,    -1,    -1,   243,   352,
     231,   291,    -1,    -1,   229,   163,   352,   232,   291,    -1,
      82,   315,   161,   316,   162,    -1,   267,    -1,   234,   233,
      -1,   233,    -1,    -1,   234,    -1,    -1,   240,   344,   235,
     237,   291,    -1,    -1,   241,   344,   235,   238,   291,    -1,
      -1,   236,   163,   344,   235,   239,   291,    -1,   248,    -1,
     250,    -1,   252,    -1,   253,    -1,   249,    -1,   251,    -1,
     254,    -1,   256,    -1,   257,    -1,   243,   257,    -1,   267,
      -1,   242,   267,    -1,   242,   245,    -1,   246,    -1,   243,
     246,    -1,   243,   267,    -1,   247,    -1,   243,   247,    -1,
     257,    -1,   246,    -1,   119,    -1,     9,    -1,    25,    -1,
      37,    -1,   110,    -1,    73,    -1,    74,    -1,   246,    -1,
     267,    -1,   242,   258,   265,    -1,   249,   257,   265,    -1,
     248,   245,   265,    -1,   248,   258,   265,    -1,   258,   265,
      -1,   243,   258,   265,    -1,   249,   246,    -1,   249,   258,
     265,    -1,   242,   259,    -1,   251,   257,    -1,   250,   245,
      -1,   259,    -1,   243,   259,    -1,   251,   246,    -1,   254,
     257,   265,    -1,   242,   188,   265,    -1,   252,   245,   265,
      -1,   256,   257,   265,    -1,   242,   255,   265,    -1,   253,
     245,   265,    -1,   188,   265,    -1,   243,   188,   265,    -1,
     254,   246,   265,    -1,    75,   161,   224,   162,    -1,    75,
     161,   290,   162,    -1,   255,    -1,   243,   255,    -1,    33,
      -1,    16,    -1,    30,    -1,     3,    -1,    24,    -1,    21,
      -1,   124,    -1,    81,    -1,    22,    -1,    69,    -1,    70,
      -1,    71,    -1,    72,    -1,     8,    -1,    27,    -1,    23,
      -1,    17,    -1,    76,    -1,    77,    -1,    78,    -1,    79,
      -1,    80,    -1,    13,    -1,    28,    -1,    35,    -1,    36,
      -1,     4,    -1,     5,    -1,   109,   166,   224,   167,    -1,
     111,    -1,   261,    -1,   277,    -1,   260,    -1,   108,   178,
     290,   179,    -1,    -1,   264,   265,   262,   168,   268,   169,
     265,    -1,    -1,   264,   265,   289,   263,   168,   268,   169,
     265,    -1,   264,   265,   289,   265,    -1,    31,    -1,    34,
      -1,    -1,   266,    -1,   267,    -1,   266,   267,    -1,    85,
      88,    -1,    84,    88,    -1,    86,   161,   224,   162,    88,
      -1,    83,    88,    -1,    83,   161,   224,   162,    88,    -1,
      87,   161,   187,   162,    88,    -1,    -1,   269,    -1,   270,
      -1,   269,   270,    -1,   272,   184,    -1,   271,   184,    -1,
     184,    -1,   228,   184,    -1,   265,   243,   274,    -1,   271,
     163,   274,    -1,   265,   241,   273,    -1,   272,   163,   273,
      -1,   344,   275,   265,    -1,    -1,   276,   265,    -1,   352,
     275,   265,    -1,   276,   265,    -1,    -1,   276,    -1,   164,
     225,    -1,    -1,   280,   265,   278,   168,   281,   169,   265,
      -1,    -1,   280,   265,   289,   279,   168,   281,   169,   265,
      -1,   280,   265,   289,    -1,    15,    -1,   282,    -1,   281,
     163,   282,    -1,   281,   163,    -1,   289,   283,    -1,    -1,
     183,   225,    -1,   287,    -1,   287,   163,    51,    -1,   286,
      -1,   285,   163,   286,    -1,   187,    -1,   288,    -1,   287,
     163,   288,    -1,   240,    -1,   240,   357,    -1,   240,   352,
     265,    -1,   240,   346,    -1,   242,    -1,   242,   357,    -1,
     242,   352,   265,    -1,   241,    -1,   241,   357,    -1,   241,
     352,   265,    -1,   241,   346,    -1,   243,    -1,   243,   357,
      -1,   243,   352,   265,    -1,   187,    -1,   188,    -1,   241,
      -1,   241,   356,    -1,   243,    -1,   243,   356,    -1,    -1,
     183,   292,    -1,   225,    -1,   168,   294,   169,    -1,   168,
     293,   163,   169,    -1,   295,    -1,   293,   163,   295,    -1,
     293,    -1,    -1,   292,    -1,   296,   183,   292,    -1,   296,
     292,    -1,   206,   164,   292,    -1,   165,   206,    -1,   166,
     224,   167,    -1,   166,   224,    51,   224,   167,    -1,   296,
     166,   224,   167,    -1,   296,   166,   224,    51,   224,   167,
      -1,   296,   165,   206,    -1,   299,    -1,   300,    -1,   298,
      -1,   303,    -1,   304,    -1,   306,    -1,   308,    -1,   312,
      -1,   309,    -1,   313,    -1,   314,    -1,   227,    -1,   289,
     164,   297,    -1,     7,   225,   164,   297,    -1,     7,   225,
      51,   225,   164,   297,    -1,    11,   164,   297,    -1,   301,
     168,   169,    -1,   301,   168,   302,   169,    -1,   301,   168,
      68,   169,    -1,    -1,   297,    -1,   302,   297,    -1,   226,
     184,    -1,    20,   161,   224,   162,   297,    -1,    20,   161,
     224,   162,   297,    14,   297,    -1,    32,   161,   224,   162,
     297,    -1,   298,    -1,   303,    -1,    39,   161,   226,   162,
     297,    -1,    12,   297,    39,   161,   224,   162,   184,    -1,
      -1,    18,   307,   161,   305,   226,   184,   226,   162,   297,
      -1,    19,   224,   184,    -1,    10,   184,    -1,     6,   184,
      -1,    26,   184,    -1,    26,   224,   184,    -1,    89,   310,
     184,    -1,   311,    -1,   310,   163,   311,    -1,   289,    -1,
      82,   315,   161,   316,   162,   184,    -1,    82,   168,    68,
     169,    -1,    90,   168,    68,   169,    -1,    90,    68,    -1,
     149,   300,    97,   161,   224,   162,   300,    -1,   149,   300,
      96,   300,    -1,    98,    -1,    -1,    37,    -1,    19,    -1,
      19,    37,    -1,    37,    19,    -1,   317,    -1,   317,   318,
      -1,   317,   318,   321,    -1,   317,   318,   321,   324,    -1,
     317,   318,   321,   324,   327,    -1,   192,    -1,   164,   320,
      -1,   164,    -1,   192,   161,   224,   162,    -1,   166,   289,
     167,   192,   161,   224,   162,    -1,   319,    -1,   320,   163,
     319,    -1,   164,   323,    -1,   164,    -1,   192,   161,   224,
     162,    -1,   166,   289,   167,   192,   161,   224,   162,    -1,
     322,    -1,   323,   163,   322,    -1,   164,   326,    -1,   164,
      -1,   192,    -1,   325,    -1,   326,   163,   325,    -1,   164,
     328,    -1,   164,    -1,   311,    -1,   328,   163,   311,    -1,
      -1,   330,    -1,   331,    -1,   330,   331,    -1,   333,    -1,
     227,    -1,   332,    -1,   184,    -1,    82,   161,   192,   162,
     184,    -1,    -1,   343,   334,   335,    -1,   300,    -1,    -1,
     337,    -1,   338,    -1,   337,   338,    -1,   342,   184,    -1,
     257,   258,   265,    -1,   249,   257,   265,    -1,   339,   245,
     265,    -1,   339,   258,   265,    -1,   254,   257,   265,    -1,
     257,   188,   265,    -1,   340,   245,   265,    -1,   339,    -1,
     340,    -1,   341,   344,    -1,   241,   344,    -1,   342,   163,
     344,    -1,   352,    -1,   240,   344,    -1,   241,   344,    -1,
     242,   352,    -1,   243,   352,    -1,   352,    -1,   345,    -1,
     349,    -1,   346,    -1,   188,    -1,   188,   358,    -1,   347,
      -1,   348,    -1,   171,   346,    -1,   171,   244,   346,    -1,
     161,   347,   162,    -1,   161,   347,   162,   358,    -1,   350,
      -1,   171,   161,   351,   162,    -1,   171,   244,   161,   351,
     162,    -1,   171,   349,    -1,   171,   244,   349,    -1,   161,
     349,   162,    -1,   161,   351,   358,   162,    -1,   161,   349,
     162,   358,    -1,   188,    -1,   161,   351,   162,    -1,   353,
      -1,   355,    -1,   354,    -1,   171,   352,    -1,   171,   244,
     352,    -1,   355,   358,    -1,   161,   353,   162,    -1,   161,
     353,   162,   358,    -1,   187,    -1,   161,   355,   162,    -1,
     364,    -1,   366,    -1,   358,    -1,   365,    -1,   367,    -1,
     363,    -1,   161,   162,    -1,    -1,   161,   359,   284,   162,
      -1,    -1,   161,   360,   285,   162,   336,    -1,   363,    -1,
     161,   162,    -1,    -1,   161,   362,   284,   162,    -1,   166,
     167,    -1,   166,   171,   167,    -1,   166,   225,   167,    -1,
     166,   244,   225,   167,    -1,   363,   166,   225,   167,    -1,
     171,    -1,   171,   244,    -1,   171,   356,    -1,   171,   244,
     356,    -1,   180,    -1,   171,    -1,   171,   244,    -1,   171,
     357,    -1,   171,   244,   357,    -1,   180,    -1,   161,   364,
     162,    -1,   161,   366,   162,    -1,   161,   358,   162,    -1,
     161,   364,   162,   358,    -1,   161,   365,   162,    -1,   161,
     367,   162,    -1,   361,    -1,   161,   365,   162,   361,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   227,   227,   228,   234,   247,   251,   255,   259,   263,
     267,   272,   273,   274,   275,   281,   282,   283,   285,   286,
     287,   288,   289,   290,   291,   295,   304,   308,   315,   322,
     332,   339,   352,   361,   371,   379,   386,   395,   400,   409,
     418,   427,   436,   447,   456,   457,   459,   468,   479,   485,
     491,   499,   508,   518,   532,   533,   537,   542,   550,   551,
     557,   563,   568,   577,   582,   587,   592,   597,   602,   607,
     612,   617,   625,   626,   636,   637,   639,   641,   646,   647,
     649,   654,   655,   657,   662,   663,   665,   667,   669,   674,
     675,   677,   682,   683,   688,   689,   694,   695,   700,   701,
     706,   707,   715,   716,   724,   725,   730,   731,   738,   748,
     749,   751,   753,   755,   757,   759,   761,   763,   765,   767,
     769,   774,   775,   780,   785,   786,   792,   800,   808,   809,
     810,   814,   827,   826,   839,   838,   851,   850,   865,   870,
     874,   879,   884,   887,   893,   891,   908,   906,   923,   921,
     938,   939,   940,   941,   945,   946,   947,   948,   952,   953,
     958,   959,   964,   972,   973,   981,   989,   990,   998,   999,
    1003,  1004,  1005,  1006,  1007,  1008,  1009,  1013,  1014,  1018,
    1024,  1030,  1036,  1045,  1050,  1056,  1061,  1071,  1076,  1081,
    1090,  1091,  1096,  1104,  1110,  1116,  1125,  1131,  1137,  1146,
    1151,  1157,  1166,  1171,  1179,  1180,  1221,  1222,  1223,  1224,
    1225,  1226,  1227,  1228,  1232,  1233,  1234,  1235,  1236,  1237,
    1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1250,  1251,  1252,  1258,  1262,  1263,  1264,  1268,
    1275,  1273,  1303,  1300,  1331,  1345,  1347,  1353,  1356,  1360,
    1361,  1368,  1370,  1372,  1374,  1376,  1378,  1384,  1387,  1391,
    1392,  1404,  1405,  1406,  1410,  1419,  1432,  1443,  1459,  1472,
    1486,  1489,  1503,  1515,  1530,  1533,  1537,  1549,  1547,  1576,
    1573,  1596,  1606,  1614,  1619,  1624,  1631,  1645,  1649,  1656,
    1657,  1666,  1671,  1678,  1687,  1692,  1700,  1706,  1711,  1716,
    1723,  1729,  1734,  1739,  1745,  1750,  1756,  1763,  1769,  1774,
    1782,  1783,  1787,  1788,  1793,  1794,  1803,  1807,  1817,  1818,
    1824,  1833,  1841,  1849,  1851,  1859,  1860,  1868,  1874,  1889,
    1896,  1903,  1911,  1918,  1926,  1938,  1939,  1940,  1941,  1942,
    1943,  1944,  1945,  1946,  1947,  1948,  1952,  1961,  1969,  1977,
    1987,  2001,  2008,  2015,  2027,  2034,  2039,  2046,  2061,  2070,
    2079,  2090,  2091,  2095,  2103,  2112,  2111,  2139,  2156,  2158,
    2160,  2162,  2167,  2188,  2193,  2200,  2204,  2210,  2220,  2226,
    2235,  2244,  2252,  2259,  2261,  2262,  2263,  2264,  2276,  2281,
    2286,  2291,  2296,  2303,  2307,  2308,  2312,  2313,  2318,  2319,
    2323,  2324,  2328,  2329,  2334,  2335,  2338,  2339,  2343,  2347,
    2348,  2352,  2353,  2357,  2358,  2367,  2369,  2373,  2374,  2378,
    2379,  2380,  2381,  2385,  2390,  2389,  2409,  2414,  2417,  2421,
    2425,  2434,  2439,  2445,  2451,  2457,  2467,  2473,  2479,  2489,
    2490,  2494,  2502,  2510,  2522,  2529,  2535,  2541,  2547,  2556,
    2557,  2561,  2562,  2566,  2567,  2572,  2576,  2577,  2582,  2591,
    2593,  2603,  2604,  2609,  2616,  2621,  2630,  2632,  2637,  2647,
    2648,  2653,  2654,  2658,  2659,  2664,  2677,  2683,  2685,  2695,
    2696,  2701,  2702,  2703,  2707,  2708,  2712,  2713,  2721,  2720,
    2737,  2736,  2757,  2758,  2766,  2765,  2783,  2790,  2797,  2804,
    2813,  2825,  2831,  2840,  2845,  2853,  2864,  2870,  2879,  2884,
    2892,  2903,  2905,  2907,  2909,  2918,  2920,  2922,  2923
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "\"auto\"", "\"bool\"", "\"complex\"",
  "\"break\"", "\"case\"", "\"char\"", "\"const\"", "\"continue\"",
  "\"default\"", "\"do\"", "\"double\"", "\"else\"", "\"enum\"",
  "\"extern\"", "\"float\"", "\"for\"", "\"goto\"", "\"if\"", "\"inline\"",
  "\"int\"", "\"long\"", "\"register\"", "\"restrict\"", "\"return\"",
  "\"short\"", "\"signed\"", "\"sizeof\"", "\"static\"", "\"struct\"",
  "\"switch\"", "\"typedef\"", "\"union\"", "\"unsigned\"", "\"void\"",
  "\"volatile\"", "\"wchar_t\"", "\"while\"", "\"->\"", "\"++\"", "\"--\"",
  "\"<<\"", "\">>\"", "\"<=\"", "\">=\"", "\"==\"", "\"!=\"", "\"&&\"",
  "\"||\"", "\"...\"", "\"*=\"", "\"/=\"", "\"%=\"", "\"+=\"", "\"-=\"",
  "\"<<=\"", "\">>=\"", "\"&=\"", "\"^=\"", "\"|=\"", "TOK_IDENTIFIER",
  "TOK_TYPEDEFNAME", "TOK_INTEGER", "TOK_FLOATING", "TOK_CHARACTER",
  "TOK_STRING", "TOK_ASM_STRING", "\"__int8\"", "\"__int16\"",
  "\"__int32\"", "\"__int64\"", "\"__ptr32\"", "\"__ptr64\"", "\"typeof\"",
  "\"__float128\"", "\"__int128\"", "\"_Decimal32\"", "\"_Decimal64\"",
  "\"_Decimal128\"", "\"__asm__\"", "\"__asm__ (with parentheses)\"",
  "\"aligned\"", "\"transparent_union\"", "\"packed\"", "\"vector_size\"",
  "\"mode\"", "\")\"", "\"__label__\"", "\"__asm\"", "\"_var_arg_typeof\"",
  "\"__builtin_va_arg\"", "\"__builtin_types_compatible_p\"",
  "\"__offsetof\"", "\"__alignof__\"", "\"finally\"", "\"except\"",
  "\"leave\"", "\"__interface\"", "\"__cdecl\"", "\"__stdcall\"",
  "\"__fastcall\"", "\"__clrcall\"", "\"forall\"", "\"exists\"",
  "\"\\\\forall\"", "\"\\\\exists\"", "\"array_of\"",
  "\"__CPROVER_bitvector\"", "\"__CPROVER_atomic\"", "\"__CPROVER_bool\"",
  "\"==>\"", "\"<==>\"", "\"TRUE\"", "\"FALSE\"", "\"__real__\"",
  "\"__imag__\"", "\"_Alignas\"", "\"_Atomic\"", "\"_Generic\"",
  "\"_Imaginary\"", "\"_Noreturn\"", "\"_Static_assert\"",
  "\"_Thread_local\"", "\"nullptr\"", "\"constexpr\"", "TOK_SCANNER_ERROR",
  "TOK_SCANNER_EOF", "\"catch\"", "\"class\"", "\"delete\"",
  "\"decltype\"", "\"explicit\"", "\"friend\"", "\"mutable\"",
  "\"namespace\"", "\"new\"", "\"operator\"", "\"private\"",
  "\"protected\"", "\"public\"", "\"template\"", "\"this\"", "\"throw\"",
  "\"typeid\"", "\"typename\"", "\"using\"", "\"virtual\"", "\"try\"",
  "\"::\"", "\".*\"", "\"->*\"", "TOK_MSC_UNARY_TYPE_PREDICATE",
  "TOK_MSC_BINARY_TYPE_PREDICATE", "\"__uuidof\"", "\"__if_exists\"",
  "\"__if_not_exists\"", "TOK_PARSE_LANGUAGE", "TOK_PARSE_EXPRESSION",
  "TOK_PARSE_TYPE", "'('", "')'", "','", "':'", "'.'", "'['", "']'", "'{'",
  "'}'", "'&'", "'*'", "'+'", "'-'", "'~'", "'!'", "'/'", "'%'", "'<'",
  "'>'", "'^'", "'|'", "'?'", "'='", "';'", "$accept", "grammar",
  "identifier", "typedef_name", "integer", "floating", "character",
  "string", "constant", "primary_expression", "generic_selection",
  "generic_assoc_list", "generic_association", "gcc_builtin_expressions",
  "cw_builtin_expressions", "offsetof", "offsetof_member_designator",
  "alignof", "quantifier_expression", "statement_expression",
  "postfix_expression", "member_name", "argument_expression_list",
  "unary_expression", "cast_expression", "multiplicative_expression",
  "additive_expression", "shift_expression", "relational_expression",
  "equality_expression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "logical_implication_expression",
  "logical_equivalence_expression", "conditional_expression",
  "assignment_expression", "comma_expression", "constant_expression",
  "comma_expression_opt", "declaration", "static_assert_declaration",
  "default_declaring_list", "@1", "@2", "@3", "post_declarator_attribute",
  "post_declarator_attributes", "post_declarator_attributes_opt",
  "declaring_list", "@4", "@5", "@6", "declaration_specifier",
  "type_specifier", "declaration_qualifier_list", "type_qualifier_list",
  "attribute_type_qualifier_list", "declaration_qualifier",
  "type_qualifier", "attribute_or_type_qualifier",
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
  "designated_initializer", "designator", "statement",
  "declaration_statement", "labeled_statement", "compound_statement",
  "compound_scope", "statement_list", "expression_statement",
  "selection_statement", "declaration_or_expression_statement",
  "iteration_statement", "$@11", "jump_statement",
  "gcc_local_label_statement", "gcc_local_label_list", "gcc_local_label",
  "gcc_asm_statement", "msc_asm_statement", "msc_seh_statement",
  "volatile_or_goto_opt", "gcc_asm_commands", "gcc_asm_assembler_template",
  "gcc_asm_outputs", "gcc_asm_output", "gcc_asm_output_list",
  "gcc_asm_inputs", "gcc_asm_input", "gcc_asm_input_list",
  "gcc_asm_clobbered_registers", "gcc_asm_clobbered_register",
  "gcc_asm_clobbered_registers_list", "gcc_asm_labels",
  "gcc_asm_labels_list", "translation_unit", "external_definition_list",
  "external_definition", "asm_definition", "function_definition", "$@12",
  "function_body", "KnR_parameter_header_opt", "KnR_parameter_header",
  "KnR_parameter_declaration", "KnR_basic_declaration_specifier",
  "KnR_typedef_declaration_specifier", "KnR_declaration_specifier",
  "KnR_parameter_declaring_list", "function_head", "declarator",
  "typedef_declarator", "parameter_typedef_declarator",
  "clean_typedef_declarator", "clean_postfix_typedef_declarator",
  "paren_typedef_declarator", "paren_postfix_typedef_declarator",
  "simple_paren_typedef_declarator", "identifier_declarator",
  "unary_identifier_declarator", "postfix_identifier_declarator",
  "paren_identifier_declarator", "abstract_declarator",
  "parameter_abstract_declarator", "postfixing_abstract_declarator",
  "$@13", "$@14", "parameter_postfixing_abstract_declarator", "$@15",
  "array_abstract_declarator", "unary_abstract_declarator",
  "parameter_unary_abstract_declarator", "postfix_abstract_declarator",
  "parameter_postfix_abstract_declarator", YY_NULL
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
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,    40,    41,    44,    58,    46,    91,    93,   123,   125,
      38,    42,    43,    45,   126,    33,    47,    37,    60,    62,
      94,   124,    63,    61,    59
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   185,   186,   186,   186,   187,   188,   189,   190,   191,
     192,   193,   193,   193,   193,   194,   194,   194,   194,   194,
     194,   194,   194,   194,   194,   195,   196,   196,   197,   197,
     198,   198,   199,   200,   201,   201,   201,   202,   202,   203,
     203,   203,   203,   204,   205,   205,   205,   205,   205,   205,
     205,   205,   205,   205,   206,   206,   207,   207,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   208,   208,   208,
     208,   208,   209,   209,   210,   210,   210,   210,   211,   211,
     211,   212,   212,   212,   213,   213,   213,   213,   213,   214,
     214,   214,   215,   215,   216,   216,   217,   217,   218,   218,
     219,   219,   220,   220,   221,   221,   222,   222,   222,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   224,   224,   225,   226,   226,   227,   227,   227,   227,
     227,   228,   230,   229,   231,   229,   232,   229,   233,   233,
     234,   234,   235,   235,   237,   236,   238,   236,   239,   236,
     240,   240,   240,   240,   241,   241,   241,   241,   242,   242,
     242,   242,   242,   243,   243,   243,   244,   244,   245,   245,
     246,   246,   246,   246,   246,   246,   246,   247,   247,   248,
     248,   248,   248,   249,   249,   249,   249,   250,   250,   250,
     251,   251,   251,   252,   252,   252,   253,   253,   253,   254,
     254,   254,   255,   255,   256,   256,   257,   257,   257,   257,
     257,   257,   257,   257,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   258,   258,   258,   258,
     258,   258,   258,   258,   258,   258,   259,   259,   259,   260,
     262,   261,   263,   261,   261,   264,   264,   265,   265,   266,
     266,   267,   267,   267,   267,   267,   267,   268,   268,   269,
     269,   270,   270,   270,   270,   271,   271,   272,   272,   273,
     273,   273,   274,   274,   275,   275,   276,   278,   277,   279,
     277,   277,   280,   281,   281,   281,   282,   283,   283,   284,
     284,   285,   285,   286,   287,   287,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     289,   289,   290,   290,   290,   290,   291,   291,   292,   292,
     292,   293,   293,   294,   294,   295,   295,   295,   295,   296,
     296,   296,   296,   296,   296,   297,   297,   297,   297,   297,
     297,   297,   297,   297,   297,   297,   298,   299,   299,   299,
     299,   300,   300,   300,   301,   302,   302,   303,   304,   304,
     304,   305,   305,   306,   306,   307,   306,   308,   308,   308,
     308,   308,   309,   310,   310,   311,   312,   312,   313,   313,
     314,   314,   314,   315,   315,   315,   315,   315,   316,   316,
     316,   316,   316,   317,   318,   318,   319,   319,   320,   320,
     321,   321,   322,   322,   323,   323,   324,   324,   325,   326,
     326,   327,   327,   328,   328,   329,   329,   330,   330,   331,
     331,   331,   331,   332,   334,   333,   335,   336,   336,   337,
     337,   338,   339,   339,   339,   339,   340,   340,   340,   341,
     341,   342,   342,   342,   343,   343,   343,   343,   343,   344,
     344,   345,   345,   346,   346,   346,   347,   347,   347,   348,
     348,   349,   349,   349,   349,   349,   350,   350,   350,   351,
     351,   352,   352,   353,   353,   353,   354,   354,   354,   355,
     355,   356,   356,   356,   357,   357,   358,   358,   359,   358,
     360,   358,   361,   361,   362,   361,   363,   363,   363,   363,
     363,   364,   364,   364,   364,   364,   365,   365,   365,   365,
     365,   366,   366,   366,   366,   367,   367,   367,   367
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     6,     1,     3,     3,     3,
       6,     6,     4,     6,     1,     3,     4,     4,     4,     6,
       4,     6,     4,     3,     1,     4,     3,     4,     3,     3,
       2,     2,     6,     7,     1,     1,     1,     3,     1,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
       2,     2,     1,     4,     1,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     5,     4,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     3,     1,     0,     1,     2,     2,     2,     2,
       2,     6,     0,     4,     0,     4,     0,     5,     5,     1,
       2,     1,     0,     1,     0,     5,     0,     5,     0,     6,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     2,     2,     1,     2,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     2,     3,     2,     3,     2,     2,     2,
       1,     2,     2,     3,     3,     3,     3,     3,     3,     2,
       3,     3,     4,     4,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     1,     1,     1,     1,     4,
       0,     7,     0,     8,     4,     1,     1,     0,     1,     1,
       2,     2,     2,     5,     2,     5,     5,     0,     1,     1,
       2,     2,     2,     1,     2,     3,     3,     3,     3,     3,
       0,     2,     3,     2,     0,     1,     2,     0,     7,     0,
       8,     3,     1,     1,     3,     2,     2,     0,     2,     1,
       3,     1,     3,     1,     1,     3,     1,     2,     3,     2,
       1,     2,     3,     1,     2,     3,     2,     1,     2,     3,
       1,     1,     1,     2,     1,     2,     0,     2,     1,     3,
       4,     1,     3,     1,     0,     1,     3,     2,     3,     2,
       3,     5,     4,     6,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     4,     6,
       3,     3,     4,     4,     0,     1,     2,     2,     5,     7,
       5,     1,     1,     5,     7,     0,     9,     3,     2,     2,
       2,     3,     3,     1,     3,     1,     6,     4,     4,     2,
       7,     4,     1,     0,     1,     1,     2,     2,     1,     2,
       3,     4,     5,     1,     2,     1,     4,     7,     1,     3,
       2,     1,     4,     7,     1,     3,     2,     1,     1,     1,
       3,     2,     1,     1,     3,     0,     1,     1,     2,     1,
       1,     1,     1,     5,     0,     3,     1,     0,     1,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     2,     2,     3,     1,     2,     2,     2,     2,     1,
       1,     1,     1,     1,     2,     1,     1,     2,     3,     3,
       4,     1,     4,     5,     2,     3,     3,     4,     4,     1,
       3,     1,     1,     1,     2,     3,     2,     3,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     2,     0,     4,
       0,     5,     1,     2,     0,     4,     2,     3,     3,     4,
       4,     1,     2,     2,     3,     1,     1,     2,     2,     3,
       1,     3,     3,     3,     4,     3,     3,     1,     4
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       0,   415,     0,     0,     0,   209,   232,   233,   219,   171,
     228,   282,   207,   222,   211,   214,   221,   210,   172,   220,
     229,   208,   245,   206,   246,   230,   231,   173,     5,     6,
     215,   216,   217,   218,   175,   176,     0,   223,   224,   225,
     226,   227,   213,     0,     0,     0,     0,     0,     0,     0,
       0,   174,   235,   170,     0,   212,     0,     0,   422,   479,
     247,   420,     0,     0,     0,     0,     0,     0,     0,   163,
     150,   154,   151,   155,   152,   153,   156,   204,   157,   158,
     247,   190,   238,   236,   247,   160,   237,   247,     2,   416,
     417,   421,   419,   424,   444,   471,   473,   472,     0,     0,
       0,     0,     7,     8,     9,    10,     0,     0,     0,     0,
       0,   354,   354,   354,   354,     0,     0,     0,   354,     0,
       0,     0,     0,     0,     0,    15,    11,    12,    13,    14,
      16,    44,    24,    19,    20,    21,    22,    23,    18,    58,
      72,    74,    78,    81,    84,    89,    92,    94,    96,    98,
     100,   102,   104,   106,   109,   121,     3,   312,   314,   154,
     155,   156,   157,     4,     1,     0,     0,   254,     0,   252,
     251,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     177,   166,   178,   474,   199,   248,   249,   130,     0,   129,
       0,   128,     0,     0,   126,   453,   142,   450,   452,   455,
     456,   451,   461,   449,   127,   142,   247,   162,   169,   247,
     168,   247,   187,   161,   132,   247,   164,   205,   159,   247,
     191,   165,   134,   247,   247,   185,   247,   247,   189,   192,
     188,   247,   247,   247,   247,   247,   183,   240,   277,   418,
     354,   488,     0,   476,   486,   354,    68,   354,    59,    60,
     310,   311,    62,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    70,    71,     0,     0,     0,     0,     0,    61,
      63,    64,    65,    66,    67,     0,    50,    51,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   488,   501,   505,   313,   483,   481,
     482,   315,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   477,   480,   177,   167,   178,   475,   250,   136,   142,
       0,   469,     0,     0,     0,     0,     0,   457,   464,   454,
     383,   141,   143,   144,   139,   146,   194,   197,   179,   316,
     200,   184,   316,   181,   182,   180,   186,   195,   198,   201,
     193,   196,     0,   247,     0,   281,   426,   425,   487,     0,
       0,   496,     0,   123,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    17,     0,    43,   124,    54,    55,
      49,    46,     0,    56,    48,     0,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   110,    75,    76,    77,
      74,    79,    80,    82,    83,    87,    88,    85,    86,    90,
      91,    93,    95,    97,    99,   101,   103,   105,     0,     0,
     122,     0,     0,     0,   502,   503,   202,   203,     0,     0,
       0,     0,   239,   234,     0,   478,   316,   148,     0,   459,
     466,     0,     0,     0,   458,   465,   385,   384,     0,   140,
     316,   316,     0,   133,   135,   247,     0,   244,     0,     0,
     296,   303,   300,   307,     0,   289,   294,   293,     0,   291,
     497,   498,     0,     0,    69,     0,    32,     0,     0,     0,
      37,    38,     0,     0,   354,    40,   142,   142,   132,   134,
      42,     0,   324,    73,     0,     0,     0,     0,   124,   365,
       0,     0,     0,     0,     0,     0,   383,     0,     0,   382,
     354,   351,    15,   247,   125,     0,   346,     0,   355,   337,
     335,   336,   124,   338,   339,   340,   341,   343,   342,   344,
     345,    47,     0,    45,   108,     0,   513,   511,   512,   504,
     423,   255,   253,   256,     0,   137,   316,   470,   460,   468,
     467,   462,     0,   386,   387,     0,   145,   147,   324,   318,
     317,   263,     0,     0,     0,   247,   259,     0,     0,   247,
       0,   283,   287,     0,   494,   506,   510,   299,   247,   297,
     517,   492,   484,   485,   306,   247,   304,   494,   506,   247,
     301,   247,   308,   489,     0,   427,     0,   499,   500,     0,
       0,     0,    34,     0,     0,     0,     0,    26,     0,     0,
       0,    15,     0,   325,   323,     0,   321,     0,   369,     0,
     368,   124,     0,     0,     0,     0,   370,     0,     0,   124,
     353,     0,     0,   375,     0,   373,   379,     0,     0,   357,
     124,   352,   356,    57,   107,   514,   131,   149,   463,   393,
       0,   388,   323,     0,   264,   270,     0,   247,   260,     0,
     262,   270,   261,     0,   285,   247,     0,   286,     0,   493,
       0,     0,     0,   507,   508,   298,   305,   507,   302,   309,
     290,   295,     0,     0,   154,   156,     0,   491,   428,   429,
     439,   440,     0,     0,   292,    30,    31,    33,     0,     0,
      39,    41,     0,    25,     0,     0,   329,     0,     0,     0,
      52,     0,     0,     0,   327,     0,   124,   350,     0,   124,
     367,     0,   371,     0,     0,     0,     0,     0,   372,     0,
     354,     0,   347,   138,   395,   389,     0,   319,     0,   267,
     247,   274,   265,   247,   274,   241,   266,   268,   247,   284,
     278,   288,   247,     0,   515,   516,   509,   442,   247,   247,
     247,   247,   430,   247,   247,   247,   441,     0,   431,    35,
       0,    29,    27,    28,     0,   330,   328,    53,   322,   334,
       0,   326,     0,   348,     0,   361,   362,   124,   124,   124,
     124,   377,     0,   374,   378,   381,     0,     0,     0,   398,
     394,   401,   390,   320,   276,   271,   247,   275,   273,   247,
     243,   280,   495,   494,   518,   433,   436,   437,   432,   434,
     435,   438,   443,    36,     0,     0,   332,   124,     0,     0,
     358,   360,   363,     0,     0,     0,     0,     0,     0,     0,
     404,   400,   407,   391,   269,   272,   331,     0,   349,     0,
     124,   124,   376,   354,     0,     0,   399,     0,     0,     0,
     408,   409,   406,   412,   392,   333,   364,     0,   359,   380,
       0,   396,     0,     0,   405,     0,   413,   411,   124,     0,
       0,   402,   410,     0,   366,     0,     0,   414,   397,     0,
     403
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,   125,    60,   126,   127,   128,   129,   130,   131,
     132,   636,   637,   133,   134,   135,   631,   136,   137,   138,
     139,   642,   412,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   544,
     589,   545,   546,    62,    63,   359,   362,   466,   351,   352,
     353,    64,   480,   481,   576,   398,   399,   400,   401,   179,
     207,    69,   181,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,   372,   486,    84,
     593,   185,   186,   594,   595,   596,   597,   598,   769,   772,
     836,   770,    86,   374,   489,    87,   600,   601,   697,   494,
     498,   499,   495,   496,   547,   638,   483,   643,   644,   645,
     646,   647,   548,   549,   550,   551,   268,   552,   553,   554,
     817,   555,   653,   556,   557,   664,   665,   558,   559,   560,
     478,   680,   681,   765,   829,   830,   832,   870,   871,   873,
     891,   892,   894,   907,    88,    89,    90,    91,    92,   240,
     377,   717,   718,   719,   720,   721,   722,   723,    93,   771,
     197,   198,   199,   200,   201,   202,   344,   203,    95,    96,
      97,   317,   704,   318,   379,   380,   610,   700,   244,   319,
     612,   320,   613
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -709
static const yytype_int16 yypact[] =
{
     186,  1916,  4193,  5201,    50,  -709,  -709,  -709,  -709,  -709,
    -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,
    -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,
    -709,  -709,  -709,  -709,  -709,  -709,   -89,  -709,  -709,  -709,
    -709,  -709,  -709,   -73,   -55,    16,    26,   -16,    25,    22,
      -7,  -709,  -709,  -709,    28,  -709,   122,  3189,  -709,  -709,
     660,  -709,   -54,  -105,   -79,    60,    78,  3096,  3096,  -709,
    4913,  4913,  1101,  1101,  1101,  1101,  1101,  -709,   463,  -709,
     660,  -709,  -709,  -709,   660,  -709,  -709,   660,  -709,  1916,
    -709,  -709,  -709,  -709,  -709,  -709,  -709,   -71,  4265,  4350,
    4350,   244,  -709,  -709,  -709,  -709,    62,    72,    79,    81,
      96,  -709,  -709,  -709,  -709,  4350,  4350,   105,  2804,  4193,
    4193,  4193,  4193,  4193,  4193,  -709,  -709,  -709,  -709,  -709,
    -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,    71,
    -709,   788,   -56,     3,   336,    17,   408,   126,   140,   146,
     289,    -3,  -709,   -43,  -709,  -709,   167,    45,  1734,  5278,
     527,   527,  -709,  -709,  -709,  2804,   291,  -709,  4193,  -709,
    -709,  4193,   294,  5201,  4193,  4193,   201,   220,  1199,   122,
    1763,  -709,  -709,  -709,  -709,   660,  -709,  -709,   122,  -709,
      63,  -709,   157,  1631,  -709,   -71,   345,  -709,  -709,  -709,
    -709,  -709,  -709,  -709,  -709,   377,   660,  -709,  -709,   660,
    -709,   660,  -709,  -709,   202,   660,  -709,  -709,  -709,   660,
    -709,  -709,   207,   660,   660,  -709,   660,   660,  -709,  -709,
    -709,   660,   660,   660,   660,   660,  -709,   244,   244,  -709,
    -709,    -8,  3297,  -709,   221,  2804,  -709,  2804,  -709,  -709,
    -709,  -709,  -709,  5201,  4193,  5201,  5201,  2921,   222,   225,
    4468,  4468,  -709,  -709,  4193,   318,   237,   242,   227,  -709,
    -709,  -709,  -709,  -709,  -709,   244,  -709,  -709,  3794,   244,
    4193,  4193,  4193,  4193,  4193,  4193,  4193,  4193,  4193,  4193,
    4193,  4193,  4193,  4193,  4193,  4193,  4193,  4193,  4193,  4193,
    4193,  4193,  4193,  4193,  4193,  4193,  4193,  4193,  4193,  4193,
    4193,  4193,  3866,  4193,   191,  2936,  -709,  -709,  -709,  -709,
    -709,  -709,   326,   249,   259,   329,   332,   263,   260,    59,
     285,   -71,  -709,  1897,  -709,  3453,  -709,  -709,  -709,   624,
     157,  -709,   288,   306,   -71,   157,   272,  -709,  -709,  -709,
      48,  -709,   624,  -709,  -709,  -709,  -709,  -709,  -709,   270,
    -709,  -709,   270,  -709,  -709,  -709,  -709,  -709,  -709,  -709,
    -709,  -709,   304,   795,   310,   330,  -709,  -709,  -709,  4692,
     294,  -709,  3951,  -709,   307,  4193,  4193,   341,   365,   386,
     369,   393,   397,   400,   403,  4468,  4468,  2983,    60,    78,
    3096,  3096,  2983,   404,  -709,  4036,  -709,  2168,  -709,  -709,
    -709,  -709,   354,  -709,  -709,   113,  -709,  -709,  -709,  -709,
    -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,
    -709,   -56,   -56,     3,     3,   336,   336,   336,   336,    17,
      17,   408,   126,   140,   146,   289,  -709,  -709,  4193,   344,
    -709,   409,   417,   420,    45,  -709,  -709,  -709,   351,   508,
     511,   536,  -709,  -709,  4193,  -709,   270,  -709,   252,   -71,
     -71,   469,   274,   157,  -709,  -709,   599,   628,   494,  -709,
     270,   270,  4108,  -709,  -709,   707,   493,  -709,   244,   505,
     235,   235,  2045,  2045,   520,   521,  -709,  -709,   380,  -709,
    -709,  -709,   516,   519,   523,   523,  -709,  5201,  5201,   244,
    -709,  -709,  4193,  4193,  4193,  -709,   624,   624,  -709,  -709,
    -709,  5111,  3709,  -709,   504,  4193,   509,   525,  2514,  -709,
    4193,   531,  3382,   535,   538,   528,    11,   244,    24,  -709,
    -709,  -709,   537,   281,   167,   518,  -709,   549,  -709,  -709,
    -709,  -709,  2341,  -709,  -709,  -709,  -709,  -709,  -709,  -709,
    -709,  -709,  4193,  -709,  -709,  4193,  -709,   -71,  -709,  -709,
    -709,  -709,  -709,  -709,   552,  -709,   270,  -709,  -709,  -709,
    -709,  -709,   372,  -709,  -709,   291,  -709,  -709,  3709,  -709,
    -709,  -709,   533,  5201,   546,   825,  -709,   -76,   -66,   707,
     -26,  -709,   539,   244,   343,  1375,  -709,  -709,   660,  -709,
    -709,   221,  -709,  -709,  -709,   660,  -709,   459,  1613,   660,
    -709,   660,  -709,  -709,  4580,  4804,   294,  -709,  -709,   557,
     558,   257,  -709,    91,    92,   559,   388,  -709,   560,   244,
    4193,   564,   568,  -709,   570,   565,  -709,  3454,  -709,   -13,
    -709,  2514,   696,   577,   -36,  4193,  -709,    14,  4193,  4193,
    -709,   673,   593,  -709,    46,  -709,  -709,   688,   423,  -709,
    2514,  -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,  -709,
     595,   596,   598,   590,  -709,   108,  3208,   660,  -709,   131,
    -709,   108,  -709,   594,   244,   660,  4193,  -709,   101,  -709,
    4692,   600,   602,   235,  -709,  -709,  -709,   128,  -709,  -709,
    -709,  -709,    63,  5021,  4913,  1101,  3233,  -709,  4804,  -709,
    4913,  1101,    63,    54,  -709,  -709,  -709,  -709,   244,  4193,
    -709,  -709,  4193,  -709,  5111,  4193,  -709,   -35,  4108,  3539,
    -709,   244,  4193,  4108,  -709,  4193,  2514,  -709,   607,  2687,
    -709,   391,  -709,   407,   609,   610,   291,   244,  -709,   612,
    -709,   608,  -709,  -709,   -10,   614,  3624,  -709,  4193,  -709,
     660,   619,  -709,   660,   619,  -709,  -709,  -709,   660,  -709,
    -709,  -709,   660,   622,    42,  -709,  -709,  -709,   660,   660,
     660,   660,  -709,   660,   660,   660,  -709,    63,  -709,  -709,
     124,  -709,  -709,  -709,  4193,  -709,  -709,  -709,  -709,  -709,
      -5,  -709,   621,  -709,  4193,  -709,  -709,  4193,  2514,  2514,
    2514,  -709,   626,  -709,  -709,  -709,  4193,   244,   625,  -709,
     632,    -6,   634,  -709,  -709,  -709,   660,  -709,  -709,   660,
    -709,  -709,  -709,   627,  -709,  -709,  -709,  -709,  -709,  -709,
    -709,  -709,  -709,  -709,   162,  4193,  -709,  2514,   412,   615,
     787,  -709,  -709,   620,   415,   644,  4193,   -10,   244,   652,
    -709,   651,   291,   654,  -709,  -709,  -709,   169,  -709,   631,
    4193,  2514,  -709,  -709,   291,   453,  -709,   649,  4193,    -6,
    -709,  -709,   656,   244,  -709,  -709,  -709,   658,  -709,  -709,
     665,  -709,   291,   455,  -709,   291,  -709,   668,  2514,  4193,
     672,  -709,  -709,   244,  -709,   460,  4193,  -709,  -709,   478,
    -709
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -709,  -709,     9,   584,  -709,  -709,  -709,  -102,  -709,  -120,
    -709,  -709,   100,  -709,  -709,  -709,  -709,  -709,  -709,  -709,
    -709,  -251,  -709,   -47,  1307,   370,   373,   303,   364,   530,
     532,   543,   529,   542,  -709,   367,  -709,  -413,  1276,    -2,
    -239,  -639,     7,  -442,  -709,  -709,  -709,  -709,   500,  -709,
    -201,  -709,  -709,  -709,  -709,     4,    18,     5,   750,  -171,
     -63,  1173,   676,  -709,   302,  -709,   755,  -709,  -709,   814,
     -41,   913,   866,   233,   -23,  -709,  -709,  -709,  -709,  -709,
     357,  -709,   280,   256,  -709,   261,  -709,  -709,   166,   171,
      84,  -606,  -709,  -709,  -709,  -709,   258,   168,  -709,   165,
    -709,   241,  -709,   245,   -88,    86,  -347,  -453,   282,   283,
    -684,  -709,  -496,   123,  -709,  -116,   496,  -709,   125,  -709,
    -709,  -709,  -709,  -709,  -709,  -709,  -708,  -709,  -709,  -709,
     339,   127,  -709,  -709,    20,  -709,  -709,    -1,  -709,  -709,
     -21,  -709,  -709,  -709,  -709,  -709,   800,  -709,  -709,  -709,
    -709,  -709,  -709,   174,  -709,  -709,  -709,  -709,  -709,   -48,
    -709,  -179,  -158,  -709,  -133,  -709,  -309,  1024,   -31,  -709,
     -19,  -135,  -451,   -96,  -709,  -709,   109,  -709,  -390,   580,
    -531,   582,  -526
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -491
static const yytype_int16 yytable[] =
{
     156,   243,   267,   384,   355,    65,    67,   223,    61,   228,
      59,   231,   232,   252,   347,   484,   804,   196,   205,    66,
     754,   157,   346,   321,   410,   176,   209,   217,   414,   590,
     476,   468,   652,   167,   342,   564,   472,   177,   745,   609,
     616,   620,   622,   592,   212,   220,   855,   309,   477,   823,
     164,   246,   248,   249,  -490,   808,   672,   105,   188,   343,
     348,   105,   299,   300,   324,    59,    59,   476,   262,   263,
     311,   385,   165,   701,    59,    59,    59,    59,   702,   189,
     773,   243,   808,   773,   190,   477,   701,   689,   166,   163,
     241,   702,   666,    65,    67,   242,    61,   691,    59,   349,
     611,   611,   611,   611,   169,   191,   168,    66,   690,   310,
     250,   275,   276,   277,   170,   292,   265,   217,   692,   575,
     293,   294,    28,    29,   376,    28,    29,   313,   313,   267,
     187,   267,   805,   586,   587,   220,   157,   694,   467,   312,
      28,    29,   339,   695,   454,   171,   502,   503,   750,   373,
     375,   746,   674,   592,   378,   747,   827,   592,   313,   174,
     868,   176,   856,   322,   582,   837,   325,   474,   837,   326,
      28,    29,   329,   177,   762,   295,   296,   313,   859,   661,
     455,   327,   342,   157,    28,   906,   172,   342,    59,   175,
      28,   157,   667,    28,   744,   301,   302,    59,   752,    59,
     173,    59,    59,   843,   266,   917,   314,   343,   242,   757,
     393,   242,   343,   475,   611,   611,   315,   797,   451,    28,
      29,   192,   313,   253,   192,   316,   463,   611,   611,   677,
     758,   193,   278,   254,   193,   465,   279,   280,   798,   192,
     255,   897,   256,   265,   194,   265,   250,   250,   471,   193,
     813,   323,   786,  -490,   313,   313,   786,   257,   632,   328,
     730,   731,   204,   157,   694,   157,   264,   397,   402,   192,
     782,   157,   768,   157,   157,   157,   313,   515,   415,   193,
     563,    85,   520,    56,   408,   806,   649,   313,   408,   617,
     811,   853,    56,    57,   242,   768,   305,    28,    29,   618,
     211,   219,    57,   224,   227,   159,    28,    29,   606,   176,
     449,   607,   614,   611,   176,   342,   355,   611,   340,   569,
     306,   177,   860,   861,   862,   313,   177,   307,   193,   876,
     313,   387,   313,   388,    28,    29,   895,   182,   308,   389,
     343,   391,   392,   394,     1,     2,     3,   213,   221,    59,
     516,   517,   314,   378,    59,    59,    28,   242,   105,   209,
     217,   878,   315,   331,    44,    45,    46,    47,    48,    85,
    -447,   316,   471,   578,   579,  -448,   471,   212,   220,   297,
     298,   241,   332,   490,   492,   898,   242,   386,   736,   497,
     395,   219,   227,   396,   611,   407,   604,   491,   267,   405,
     602,   242,   512,   513,   406,    28,   605,    59,    59,    59,
      59,   457,   914,   241,   577,   606,   542,   184,   242,   727,
     159,   458,   728,   729,   668,   461,   347,   350,    44,    45,
      46,    47,    48,   473,   703,   241,   581,   236,   221,   462,
     242,   237,   176,   193,   238,  -311,   342,   707,   464,   663,
     469,   209,   217,   482,   177,   303,   304,   781,   335,   350,
      44,    45,    46,    47,    48,   337,     5,   159,   470,   212,
     220,   675,   485,   182,   501,   159,   354,   799,   488,    12,
     404,   313,    59,   679,    14,   354,   471,    17,   456,   313,
     809,   459,   313,    21,   460,   313,    23,   250,  -279,    59,
      59,    59,    59,   504,   604,   699,   812,   313,   565,   242,
     633,   634,   265,  -445,   605,   602,   561,   562,   408,   760,
     761,    28,   182,   606,   474,   157,   157,   505,   654,   834,
     657,   641,   507,   241,   678,   570,     9,   542,   242,   157,
      85,    85,   625,   626,    42,  -446,   250,   159,   506,   159,
     733,   734,    18,   818,   313,   159,   508,   159,   159,   159,
     509,   542,   510,   356,    27,   511,   357,   521,   358,   819,
     313,   566,   360,   176,   879,   313,   361,   883,   313,   567,
     363,   364,   568,   365,   366,   177,   176,    55,   367,   368,
     369,   370,   371,   629,   630,   182,   571,   641,   177,   572,
      34,    35,   435,   436,   437,   438,   602,   258,   259,   260,
     261,   685,   250,    59,    59,   901,   313,   911,   313,   354,
     617,   699,   918,   313,   573,   242,    59,    59,   490,   492,
     618,   580,   354,   211,   219,   497,   583,    51,   737,   606,
     920,   313,   491,   712,   825,   217,    53,   584,   408,   195,
     195,   206,   215,   751,   679,   585,   753,   793,   795,    85,
     542,   599,   828,   220,   787,   431,   432,   439,   440,   663,
     433,   434,   217,   603,   796,    85,    85,   446,   447,   542,
     213,   221,   623,   627,   624,   251,   628,    85,   648,   651,
     220,   522,   655,   650,    59,    59,   658,   660,    59,   659,
      59,  -310,   669,   250,   490,   492,   350,    44,    45,    46,
      47,    48,    59,   670,   676,   687,    59,   684,   491,   725,
     726,    59,   696,   732,   735,   211,   219,   800,   -54,   869,
     487,    59,   738,   739,   740,   748,   712,   408,   749,   865,
     810,   755,   215,    44,    45,    46,    47,    48,   641,   852,
     408,    68,   157,   158,   756,   542,   759,   763,   160,   767,
     764,   766,   784,   778,   785,   828,   250,   899,   814,   826,
     890,   820,   213,   221,   195,   641,   341,   195,   831,   821,
     887,   824,   900,   768,   842,   857,   866,   869,   863,   699,
      44,    45,    46,    47,    48,   867,   354,   354,   872,   880,
     910,   881,   854,   890,   882,   663,    59,   178,    85,   159,
     159,   884,   858,   888,   889,   896,   902,   161,   893,   905,
     908,   251,   251,   159,   864,   663,   909,   542,   542,   542,
      54,   913,    85,   916,   802,   441,   250,   444,   442,    68,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     443,   445,   479,   877,   334,   693,   688,   777,   839,   409,
     776,   698,   779,   409,   885,   783,   542,   724,   158,   711,
     682,   683,   815,   160,   816,   662,  -257,   250,    44,    45,
      46,    47,    48,   822,   912,   182,   903,   886,   904,   239,
     542,   591,   792,   844,   452,   159,   453,     0,   182,     0,
     184,     0,   250,     0,    85,     0,     0,   915,    44,    45,
      46,    47,    48,     0,   919,   158,   162,   542,     0,   219,
     160,     0,   250,   158,   341,     0,     0,   714,   160,   341,
     195,    85,   161,   210,   218,     0,   210,   226,   210,   230,
     210,   210,   234,   178,   235,     0,   219,   227,    54,   791,
      85,     0,     0,   794,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  -242,     0,   705,   221,     0,     0,     0,
       0,   291,   706,     0,     0,     0,   708,     0,   709,   161,
      85,     0,   195,   195,   206,   215,     0,   161,     0,     0,
       0,   543,   178,   221,  -258,   158,     0,   158,     0,     0,
     160,     0,   160,   158,     0,   158,   158,   158,   160,   591,
     160,   160,   160,     0,     0,     0,     0,     0,     0,     0,
     714,     0,     0,     0,     0,    94,    85,     0,     0,    85,
       0,   162,     0,     0,     0,     0,   159,     0,     0,     0,
       0,     0,     0,     0,   775,     0,     0,     0,     0,     0,
       0,     0,   780,     0,     0,     0,     0,   341,     0,   161,
       0,   161,     0,     0,     0,   178,     0,   161,     0,   161,
     161,   161,   251,     0,   195,   195,   206,   215,   162,     0,
       0,   183,     0,     0,     0,     0,   162,     0,     0,     0,
       0,   214,   222,   409,     0,     0,     0,     0,    85,    85,
      85,     0,     0,     0,     5,     0,   409,     0,     0,     0,
       9,     0,   543,    94,     0,     0,     0,    12,     0,     0,
       0,   251,    14,     0,     0,    17,    18,   835,     0,   493,
     838,    21,     0,     0,    23,   840,   543,    85,    27,   841,
       0,     0,     0,     0,     0,   845,   846,   847,   848,     0,
     849,   850,   851,     0,     0,     0,     0,     0,   162,     0,
     162,    85,     0,     0,     0,     0,   162,     0,   162,   162,
     162,     0,   409,     0,    34,    35,     0,     0,     0,     0,
       0,     0,    42,     0,     0,     0,     0,   251,    85,   195,
       0,     0,     0,   874,     0,     0,   875,     0,     0,     0,
       0,     0,     0,   336,     0,     0,     0,     0,     9,     0,
       0,    51,   338,     0,     0,     0,     0,   183,     0,     0,
      53,     0,     0,   409,    18,    55,     0,     0,     0,     0,
     180,     0,     0,     0,     0,   543,    27,     0,     0,     0,
     208,   216,     0,   208,   225,   208,   229,   208,   208,   233,
       0,     0,     0,     0,   543,     0,     0,   158,   158,     0,
       0,     0,   160,   160,     0,     0,   210,   218,     0,   195,
     215,   158,    34,    35,     0,   195,   160,     0,   251,     0,
       0,     0,    44,    45,    46,    47,    48,   195,     0,     0,
       0,     0,     0,     0,     0,     0,   195,   215,     0,     0,
     790,     0,     0,     0,     0,     0,   195,     0,     0,    51,
       0,     0,   409,     0,     0,     0,     0,     0,    53,     0,
       0,   161,   161,   409,     0,   409,     0,     0,     0,     0,
     543,   216,   225,   229,   233,   161,     0,     0,     0,     0,
       0,   251,     0,   686,     0,     0,     0,     0,   160,     0,
     409,   333,     0,     0,     0,   178,     0,     0,   210,   218,
       0,     0,     0,     0,     0,     0,   180,     0,   178,     0,
     336,     0,     0,     0,   493,   713,     0,     0,     0,     0,
     160,   195,     0,     0,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,   543,   543,   543,     0,     0,   161,     0,     0,
       0,   251,    27,     0,     0,   180,     0,     0,     0,     0,
     162,   162,     0,     0,   518,   519,   269,   270,   271,   272,
     273,   274,     0,     0,   162,     0,     0,    28,    29,   715,
       0,   543,     0,     0,     0,     0,     0,     0,    34,    35,
     493,   330,   251,     0,     0,     0,     0,     0,    44,    45,
      46,    47,    48,     0,     0,   543,     0,     0,   713,     0,
       0,     0,     0,   160,     0,     0,     0,   251,     0,     0,
       0,     0,     0,     0,   158,    51,     0,     0,   180,   160,
       0,   716,   543,     0,    53,     0,     0,   251,     0,     0,
       0,     0,     0,     0,     0,     0,   162,     0,     0,     0,
       0,     0,     0,     0,   608,   615,   619,   621,   383,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     390,     0,   715,     0,     0,     0,   604,     0,   162,     0,
     403,   242,     0,     0,     0,     0,   605,     0,   161,     0,
       0,     0,     0,     0,   413,   606,     0,   416,   417,   418,
     419,   420,   421,   422,   423,   424,   425,   426,     0,     0,
       0,     0,     0,   208,   216,     0,     0,     0,     0,     0,
     788,   789,     0,     0,   716,     0,   210,   210,     0,   450,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   427,
     428,   429,   430,   430,   430,   430,   430,   430,   430,   430,
     430,   430,   430,   430,   430,   430,   430,   430,   430,     0,
       0,     0,     9,     0,     0,     0,     0,     0,     0,   183,
       0,   162,     0,     0,     0,     0,     0,     0,    18,     0,
       9,     0,   183,     0,     0,     0,     0,   162,     0,     0,
      27,     0,     0,     0,     0,     0,    18,     0,     0,     0,
       0,   383,   383,     0,     0,   208,   216,     0,    27,     0,
       0,     0,     0,     0,     0,    28,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,    35,     0,   270,
       0,     0,     0,    28,    29,     0,    44,    45,    46,    47,
      48,     0,     0,     0,    34,    35,     0,     0,     0,     0,
     774,     0,   523,   774,    44,    45,    46,    47,    48,     0,
       0,     0,     0,    51,     0,     0,     0,   336,     0,     0,
       0,   336,    53,     0,     0,     0,     0,     0,     6,     7,
     574,    51,     8,     9,     0,     0,     0,    10,     0,    11,
      53,    13,     0,     0,     0,   430,    15,    16,   383,    18,
       0,    19,    20,     0,     0,    22,     0,     0,    24,    25,
      26,    27,  -163,     0,   617,     0,     0,     0,   180,   242,
       0,     0,     0,     0,   618,     0,     0,     0,  -163,     0,
       0,   180,   345,   606,     0,     0,     0,    29,   383,     0,
    -163,   383,   193,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     0,     0,    44,    45,    46,
      47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -163,  -163,   673,     0,
       0,     0,    49,    50,    51,    52,  -163,  -163,  -163,  -163,
    -163,     0,     0,    53,     0,     0,     0,     0,     0,   216,
       0,     0,     0,     0,   383,     0,     0,     0,     0,     0,
       0,     0,   430,  -163,     0,     0,     0,     0,     0,     0,
       0,     0,  -163,     0,     0,     0,   216,   225,   233,     0,
       0,     0,     0,   208,   208,   314,     0,     0,     0,     0,
     242,     0,     0,     0,     0,   315,  -164,     0,     0,     0,
       0,     0,     0,     0,   316,     0,     0,     0,     0,     5,
       6,     7,  -164,   383,     8,     9,     0,     0,     0,    10,
       0,    11,    12,    13,  -164,     0,     0,    14,    15,    16,
      17,    18,     0,    19,    20,     0,    21,    22,     0,    23,
      24,    25,    26,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -164,  -164,   383,     0,     0,     0,     0,     0,    28,    29,
    -164,  -164,  -164,  -164,  -164,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     0,     0,     0,  -164,   801,     0,
       0,   803,     0,     0,   383,   383,  -164,     0,     0,   383,
       0,   383,     0,     0,    49,    50,    51,    52,     0,     0,
       0,     0,     0,     0,     0,    53,     0,     0,     0,    54,
      55,     0,   383,     0,   383,     0,     0,     0,     5,     6,
       7,     0,     0,     8,     9,     0,     0,     0,    10,     0,
      11,    12,    13,     0,     0,     0,    14,    15,    16,    17,
      18,     0,    19,    20,     0,    21,    22,    56,    23,    24,
      25,    26,    27,     0,     0,     0,     0,    57,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,    28,    29,     0,
       0,     0,     0,     0,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,     0,    44,    45,
      46,    47,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    49,    50,    51,    52,     0,     0,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,    55,
       0,     5,     6,     7,   524,   525,     8,     9,   526,   527,
     528,    10,     0,    11,    12,    13,   529,   530,   531,    14,
      15,    16,    17,    18,   532,    19,    20,    98,    21,    22,
     533,    23,    24,    25,    26,    27,   617,   534,     0,    99,
     100,   242,     0,     0,     0,     0,   618,   101,     0,     0,
       0,     0,     0,     0,     0,   606,     0,     0,     0,     0,
      28,    29,   102,   103,   104,   105,   535,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
     536,    44,    45,    46,    47,    48,     0,   537,   538,   106,
     107,   108,   109,   110,     0,     0,   539,     0,     0,     0,
       0,     0,   111,   112,   113,   114,    49,    50,    51,    52,
       0,     0,     0,     0,   115,   116,     0,    53,   117,     0,
       0,    54,    55,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   540,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   118,
       0,     0,     0,     0,     0,     0,  -354,   541,   119,   120,
     121,   122,   123,   124,     5,     6,     7,   524,   525,     8,
       9,   526,   527,   528,    10,     0,    11,    12,    13,   529,
     530,   531,    14,    15,    16,    17,    18,   532,    19,    20,
      98,    21,    22,   533,    23,    24,    25,    26,    27,     0,
     534,     0,    99,   100,     0,     0,     0,     0,     0,     0,
     101,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,    29,   102,   103,   104,   105,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,   536,    44,    45,    46,    47,    48,     0,
     537,   538,   106,   107,   108,   109,   110,     0,     0,   539,
       0,     0,     0,     0,     0,   111,   112,   113,   114,    49,
      50,    51,    52,     0,     0,     0,     0,   115,   116,     0,
      53,   117,     0,     0,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     540,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   118,     0,     0,     0,     0,     0,     0,  -354,
     671,   119,   120,   121,   122,   123,   124,     5,     6,     7,
     524,   525,     8,     9,   526,   527,   528,    10,     0,    11,
      12,    13,   529,   530,   531,    14,    15,    16,    17,    18,
     532,    19,    20,    98,    21,    22,   533,    23,    24,    25,
      26,    27,     0,   534,     0,    99,   100,     0,     0,     0,
       0,     0,     0,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,    29,   102,   103,
     104,   105,     0,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,   536,    44,    45,    46,
      47,    48,     0,   537,   538,   106,   107,   108,   109,   110,
       0,     0,   539,     0,     0,     0,     0,     0,   111,   112,
     113,   114,    49,    50,    51,    52,     0,     0,     0,     0,
     115,   116,     0,    53,   117,     0,     0,    54,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   540,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,     0,     0,     0,     0,
       0,     0,  -354,     0,   119,   120,   121,   122,   123,   124,
       5,     6,     7,     0,     0,     8,     9,     0,     0,     0,
      10,     0,    11,    12,    13,     0,     0,     0,    14,    15,
      16,    17,    18,     0,    19,    20,    98,    21,    22,     0,
      23,    24,    25,    26,    27,     0,     0,     0,    99,   100,
       0,     0,     0,     0,     0,     0,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      29,   102,   103,   104,   105,     0,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,     0,
      44,    45,    46,    47,    48,     0,     0,     0,   106,   107,
     108,   109,   110,     0,     0,     0,     0,     0,     0,     0,
       0,   111,   112,   113,   114,    49,    50,    51,    52,     0,
       0,     0,     0,   115,   116,     0,    53,   117,     6,     7,
      54,    55,     8,     9,     0,     0,     0,    10,     0,    11,
       0,    13,     0,     0,     0,     0,    15,    16,     0,    18,
       0,    19,    20,    98,     0,    22,     0,     0,    24,    25,
      26,    27,     0,     0,     0,    99,   100,     0,   118,     0,
       0,     0,     0,   101,     0,     0,     0,   119,   120,   121,
     122,   123,   124,     0,     0,     0,    28,    29,   102,   103,
     104,   105,     0,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,   111,   112,
     113,   114,    49,    50,    51,    52,     0,     0,     0,     0,
     115,   116,     0,    53,   117,     6,     7,     0,     0,     8,
       9,     0,     0,     0,    10,     0,    11,     0,    13,     0,
       0,     0,     0,    15,    16,     9,    18,     0,    19,    20,
      98,     0,    22,     0,     0,    24,    25,    26,    27,     0,
       0,    18,    99,   100,     0,   118,     0,     0,     0,     0,
     101,     0,     0,    27,   119,   120,   121,   122,   123,   124,
       0,     0,     0,    28,    29,   102,   103,   104,   105,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     0,     0,     0,     0,     0,     0,     0,    34,
      35,     0,   106,   107,   108,   109,   110,     0,     0,    44,
      45,    46,    47,    48,     0,   111,   112,   113,   114,    49,
      50,    51,    52,     0,     0,     0,     0,   115,   116,     0,
      53,   117,     0,     0,     0,    28,    51,   102,   103,   104,
     105,     0,     0,     0,     0,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   106,   107,   108,   109,   110,     0,
       0,     0,   247,     0,     0,     0,     0,   111,   112,   113,
     114,   119,   120,   121,   122,   123,   124,   314,     0,     5,
       6,     7,   242,   117,     8,     9,     0,   315,     0,    10,
       0,    11,    12,    13,     0,     0,   316,    14,    15,    16,
      17,    18,     0,    19,    20,     0,    21,    22,     0,    23,
      24,    25,    26,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   514,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,    29,
       0,     0,     0,     0,     0,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,     0,    44,
      45,    46,    47,    48,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     9,     0,
       0,     0,     0,     0,    49,    50,    51,    52,     0,     0,
       0,     0,     6,     7,    18,    53,     8,     9,     0,     0,
      55,    10,     0,    11,     0,    13,    27,     0,     0,     0,
      15,    16,     0,    18,     0,    19,    20,     6,     7,    22,
       0,     8,    24,    25,    26,    27,    10,     0,     0,     0,
      13,    28,     0,     0,     0,    15,    16,    56,     0,     0,
      19,    20,    34,    35,     0,     0,     0,    57,    25,    26,
      28,    29,    44,    45,    46,    47,    48,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,     0,
       0,    44,    45,    46,    47,    48,    29,     0,     0,    51,
       0,     0,    30,    31,    32,    33,     9,     0,    53,    37,
      38,    39,    40,    41,     0,     0,    49,    50,    51,    52,
       0,     0,    18,     0,     0,     0,    98,    53,     0,     0,
       0,     0,     0,     0,    27,     0,     0,     0,    99,   100,
       0,     0,    50,     0,    52,     0,   101,     0,     0,     0,
      56,     0,     0,     0,     0,     0,     0,     0,     0,    28,
      57,   102,   103,   104,   105,     0,     0,     0,     0,    56,
      34,    35,   768,     0,     0,     0,     0,     0,     0,    57,
      44,    45,    46,    47,    48,     0,     0,     0,   106,   107,
     108,   109,   110,     0,     0,     0,     0,     0,     0,     0,
       0,   111,   112,   113,   114,     0,     0,    51,     0,     0,
       0,    98,     0,   115,   116,     0,    53,   117,     0,     0,
       0,     0,     0,    99,   100,     0,     0,     0,     0,     0,
       0,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    28,     0,   102,   103,   104,   105,
       0,     0,     0,     0,     0,     0,     0,     0,   118,     0,
       0,     0,  -165,     0,   381,     0,     0,   119,   382,   121,
     122,   123,   124,   106,   107,   108,   109,   110,  -165,     0,
       0,     0,     0,    98,     0,     0,   111,   112,   113,   114,
    -165,     0,     0,     0,     0,    99,   100,     0,   115,   116,
       0,     0,   117,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,   102,   103,
     104,   105,     0,     0,     0,     0,  -165,  -165,     0,     0,
       0,     0,     0,     0,     0,     0,  -165,  -165,  -165,  -165,
    -165,     0,     0,   118,     0,   106,   107,   108,   109,   110,
       0,     0,   119,   120,   121,   122,   123,   124,   111,   112,
     113,   114,     0,  -165,     0,     0,   656,     0,    98,     0,
     115,   116,  -165,     0,   117,     0,     0,     0,     0,     0,
      99,   100,     0,     0,     0,     0,     0,     0,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,   118,     0,     0,     0,   741,
     742,     0,   588,     0,   119,   120,   121,   122,   123,   124,
     106,   107,   108,   109,   110,     0,     0,   743,     0,     0,
       0,     0,     0,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,    98,     0,   115,   116,     0,     0,   117,
       0,     0,     0,     0,     0,    99,   100,     0,     0,     0,
       0,     0,     0,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,    29,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
     118,     0,     0,     0,   639,   640,     0,   588,   807,   119,
     120,   121,   122,   123,   124,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,   111,   112,
     113,   114,     0,     0,     0,     0,     0,     0,    98,     0,
     115,   116,     0,     0,   117,     0,     0,     0,     0,     0,
      99,   100,     0,     0,     0,     0,     0,     0,   101,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    28,    29,   102,   103,   104,   105,     0,     0,     0,
       0,     0,     0,     0,     0,   118,     0,     0,     0,   639,
     640,     0,   588,   833,   119,   120,   121,   122,   123,   124,
     106,   107,   108,   109,   110,     0,     0,     0,     0,     0,
       0,     0,     0,   111,   112,   113,   114,     0,     0,     0,
       0,     0,     0,    98,     0,   115,   116,     0,     0,   117,
       0,     0,     0,     0,     0,    99,   100,     0,     0,     0,
       0,     0,     0,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,   102,   103,
     104,   105,     0,     0,     0,     0,     0,     0,     0,     0,
     118,     0,     0,     0,   639,   640,     0,   588,     0,   119,
     120,   121,   122,   123,   124,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,    98,     0,     0,   111,   112,
     113,   114,     0,     0,     0,     0,     0,    99,   100,     0,
     115,   116,     0,     0,   117,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   118,   411,   106,   107,   108,
     109,   110,     0,     0,   119,   120,   121,   122,   123,   124,
     111,   112,   113,   114,     0,     0,     0,     0,     0,     0,
      98,     0,   115,   116,     0,     0,   117,     0,     0,     0,
       0,     0,    99,   100,     0,     0,     0,     0,     0,     0,
     101,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    28,     0,   102,   103,   104,   105,     0,
       0,     0,     0,     0,     0,     0,     0,   118,     0,     0,
     448,     0,     0,     0,     0,     0,   119,   120,   121,   122,
     123,   124,   106,   107,   108,   109,   110,     0,     0,     0,
       0,     0,     0,     0,     0,   111,   112,   113,   114,     0,
       0,     0,     0,     0,     0,    98,     0,   115,   116,     0,
       0,   117,     0,     0,     0,     0,     0,    99,   100,     0,
       0,     0,     0,     0,     0,   101,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    28,     0,
     102,   103,   104,   105,     0,     0,     0,     0,     0,     0,
       0,     0,   118,     0,     0,     0,     0,     0,   500,     0,
       0,   119,   120,   121,   122,   123,   124,   106,   107,   108,
     109,   110,     0,     0,     0,     0,     0,    98,     0,     0,
     111,   112,   113,   114,     0,     0,     0,     0,     0,    99,
     100,     0,   115,   116,     0,     0,   117,   101,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      28,     0,   102,   103,   104,   105,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   118,     0,   106,
     107,   108,   109,   110,   522,     0,   119,   120,   121,   122,
     123,   124,   111,   112,   113,   114,     0,     0,     0,     0,
       0,     0,    98,     0,   115,   116,     0,     0,   117,     0,
       0,     0,     0,     0,    99,   100,     0,     0,     0,     0,
       0,     0,   101,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    28,     0,   102,   103,   104,
     105,     0,     0,     0,     0,     0,     0,     0,     0,   118,
       0,     0,     0,     0,     0,     0,   588,     0,   119,   120,
     121,   122,   123,   124,   106,   107,   108,   109,   110,     0,
       0,     0,     0,     0,    98,     0,     0,   111,   112,   113,
     114,     0,     0,     0,     0,     0,    99,   100,     0,   115,
     116,     0,     0,   117,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    28,     0,   102,
     103,   104,   105,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   118,     0,   106,   107,   108,   109,
     110,     0,     0,   119,   120,   121,   122,   123,   124,   111,
     112,   113,   114,     0,     0,     0,     0,     0,     0,    98,
       0,   115,   116,     0,     0,   117,     0,     0,     0,     0,
       0,    99,   100,     0,     0,     0,     0,     0,     0,   101,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,     0,   102,   103,   104,   105,     0,     0,
       0,     0,     0,     0,     0,     0,   245,     0,     0,     0,
       0,     0,     0,     0,     0,   119,   120,   121,   122,   123,
     124,   106,   107,   108,   109,   110,     0,     0,     0,     0,
       0,     0,     0,     0,   111,   112,   113,   114,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,     0,     0,
     117,     5,     6,     7,     0,     0,     8,     9,     0,     0,
       0,    10,     0,    11,    12,    13,     0,     0,     0,    14,
      15,    16,    17,    18,     0,    19,    20,     0,    21,    22,
       0,    23,    24,    25,    26,    27,     0,     0,     0,     0,
       0,   247,     0,     0,     0,     0,     0,     0,     0,     0,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,    29,     0,     0,     0,     0,     0,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
       0,    44,    45,    46,    47,    48,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
       0,     0,     0,     5,     6,     7,     0,    53,     8,     9,
       0,    54,    55,    10,     0,    11,    12,    13,     0,     0,
       0,    14,    15,    16,    17,    18,     0,    19,    20,     0,
      21,    22,     0,    23,    24,    25,    26,    27,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   710,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    29,     0,     0,     0,     0,     0,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,     0,    44,    45,    46,    47,    48,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
      51,    52,     0,     0,     0,     5,     6,     7,     0,    53,
       8,     9,     0,     0,    55,    10,     0,    11,    12,    13,
       0,     0,     0,    14,    15,    16,    17,    18,     0,    19,
      20,     0,    21,    22,     0,    23,    24,    25,    26,    27,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,     0,     0,     0,     0,
       0,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,     0,    44,    45,    46,    47,    48,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,     0,     0,     0,     5,     6,     7,
       0,    53,     8,     9,     0,     0,    55,    10,     0,    11,
      12,    13,     0,     0,     0,    14,    15,    16,    17,    18,
       0,    19,    20,     0,    21,    22,     0,    23,    24,    25,
      26,    27,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    29,     0,     0,
       0,     0,     0,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    49,    50,    51,    52,     5,     6,     7,     0,
       0,     8,     9,    53,     0,     0,    10,     0,    55,    12,
      13,     0,     0,     0,    14,    15,    16,    17,    18,     0,
      19,    20,     0,    21,     0,     0,    23,     0,    25,    26,
      27,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    31,    32,    33,    34,    35,     0,    37,
      38,    39,    40,    41,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,     6,     7,     0,     0,     8,
       9,     0,    53,     0,    10,     0,    11,    55,    13,     0,
       0,     0,     0,    15,    16,     0,    18,     0,    19,    20,
       0,     0,    22,     0,     0,    24,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     0,     0,    44,    45,    46,    47,    48,     0,
       0,     0,     0,     0,     0,     6,     7,     0,     0,     8,
       9,     0,   635,     0,    10,     0,    11,     0,    13,    49,
      50,    51,    52,    15,    16,     0,    18,     0,    19,    20,
      53,     0,    22,     0,     0,    24,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     6,     7,     0,     0,     8,
       9,     0,     0,     0,    10,     0,    11,     0,    13,    49,
      50,    51,    52,    15,    16,     0,    18,     0,    19,    20,
      53,     0,    22,     0,     0,    24,    25,    26,    27,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,     6,     7,     0,     0,     8,     9,     0,     0,
       0,    10,     0,     0,     0,    13,     0,     0,     0,     0,
      15,    16,     0,    18,     0,    19,    20,     0,     0,    49,
      50,    51,    52,    25,    26,    27,     0,     0,     0,     0,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    31,    32,
      33,    34,    35,     0,    37,    38,    39,    40,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    51,    52,
       0,     0,     0,     0,     0,     0,     0,    53
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-709)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       2,    97,   118,   242,   205,     1,     1,    70,     1,    72,
       1,    74,    75,   101,   193,   362,    51,    65,    66,     1,
     659,     3,   193,   158,   275,    56,    67,    68,   279,   482,
      19,   340,   528,    88,   192,   448,   345,    56,    51,   490,
     491,   492,   493,   485,    67,    68,    51,    50,    37,   757,
       0,    98,    99,   100,    62,   739,   552,    67,   163,   192,
     193,    67,    45,    46,   166,    56,    57,    19,   115,   116,
     113,   242,   161,   604,    65,    66,    67,    68,   604,   184,
     686,   177,   766,   689,   163,    37,   617,   163,   161,     3,
     161,   617,    68,    89,    89,   166,    89,   163,    89,   195,
     490,   491,   492,   493,    88,   184,   161,    89,   184,   112,
     101,    40,    41,    42,    88,   171,   118,   158,   184,   466,
     176,   177,    62,    63,   240,    62,    63,   163,   163,   245,
     184,   247,   167,   480,   481,   158,   118,   163,   339,   182,
      62,    63,   190,   169,   315,   161,   385,   386,   184,   237,
     238,   164,   565,   595,   162,   651,   166,   599,   163,   166,
     166,   192,   167,   165,   473,   771,   168,   346,   774,   171,
      62,    63,   174,   192,   670,   172,   173,   163,   817,   168,
     315,   172,   340,   165,    62,   893,   161,   345,   179,   161,
      62,   173,   168,    62,   647,   178,   179,   188,   184,   190,
     178,   192,   193,   161,   118,   913,   161,   340,   166,   163,
     257,   166,   345,   346,   604,   605,   171,   163,   314,    62,
      63,   161,   163,   161,   161,   180,   167,   617,   618,   576,
     184,   171,   161,   161,   171,   331,   165,   166,   184,   161,
     161,   880,   161,   245,   184,   247,   237,   238,   344,   171,
     746,   165,   703,    62,   163,   163,   707,   161,   509,   173,
     169,   169,   184,   245,   163,   247,   161,   260,   261,   161,
     169,   253,   164,   255,   256,   257,   163,   397,   280,   171,
     167,     1,   402,   161,   275,   738,   525,   163,   279,   161,
     743,   167,   161,   171,   166,   164,   170,    62,    63,   171,
      67,    68,   171,    70,    71,     3,    62,    63,   180,   340,
     312,   490,   491,   703,   345,   473,   517,   707,   161,   454,
     180,   340,   818,   819,   820,   163,   345,   181,   171,   167,
     163,   245,   163,   247,    62,    63,   167,    57,    49,   253,
     473,   255,   256,   257,   158,   159,   160,    67,    68,   340,
     398,   399,   161,   162,   345,   346,    62,   166,    67,   400,
     401,   857,   171,   162,    83,    84,    85,    86,    87,    89,
     168,   180,   468,   469,   470,   168,   472,   400,   401,    43,
      44,   161,   162,   379,   379,   881,   166,   166,   639,   380,
     168,   158,   159,   168,   784,   168,   161,   379,   514,   162,
     488,   166,   395,   396,   162,    62,   171,   398,   399,   400,
     401,   162,   908,   161,   162,   180,   407,    60,   166,   162,
     118,   162,   165,   166,   540,   162,   605,    82,    83,    84,
      85,    86,    87,   161,   605,   161,   162,    80,   158,   179,
     166,    84,   473,   171,    87,   164,   604,   618,   163,   537,
     162,   492,   493,   183,   473,    47,    48,   696,   178,    82,
      83,    84,    85,    86,    87,   185,     3,   165,   162,   492,
     493,   567,   168,   193,   167,   173,   196,   728,   168,    16,
     162,   163,   473,   585,    21,   205,   582,    24,   162,   163,
     741,   162,   163,    30,   162,   163,    33,   488,   168,   490,
     491,   492,   493,   162,   161,   162,   745,   163,   164,   166,
     512,   513,   514,   168,   171,   603,   162,   163,   509,    96,
      97,    62,   242,   180,   703,   507,   508,   162,   530,   768,
     532,   522,   163,   161,   162,   184,     9,   528,   166,   521,
     260,   261,   162,   163,    81,   168,   537,   245,   162,   247,
     162,   163,    25,   162,   163,   253,   163,   255,   256,   257,
     163,   552,   162,   206,    37,   162,   209,   163,   211,   162,
     163,   162,   215,   604,   162,   163,   219,   162,   163,   162,
     223,   224,   162,   226,   227,   604,   617,   124,   231,   232,
     233,   234,   235,   507,   508,   315,    88,   588,   617,    88,
      73,    74,   299,   300,   301,   302,   694,   111,   112,   113,
     114,   593,   603,   604,   605,   162,   163,   162,   163,   339,
     161,   162,   162,   163,    88,   166,   617,   618,   624,   624,
     171,   162,   352,   400,   401,   626,    37,   110,   640,   180,
     162,   163,   624,   625,   760,   686,   119,    19,   639,    65,
      66,    67,    68,   655,   756,   161,   658,   720,   721,   379,
     651,   168,   764,   686,   712,   295,   296,   303,   304,   757,
     297,   298,   713,   168,   722,   395,   396,   310,   311,   670,
     400,   401,   162,   167,   163,   101,   167,   407,   184,   164,
     713,   168,   161,   184,   685,   686,   161,   169,   689,   161,
     691,   164,   184,   694,   700,   700,    82,    83,    84,    85,
      86,    87,   703,   164,   162,   169,   707,   184,   700,   162,
     162,   712,   183,   164,   164,   492,   493,   729,   164,   831,
     373,   722,   164,   163,   169,    39,   718,   728,   161,   827,
     742,    68,   158,    83,    84,    85,    86,    87,   739,   797,
     741,     1,   734,     3,   161,   746,    68,   162,     3,   169,
     164,   163,   162,   169,   162,   867,   757,   883,   161,   161,
     872,   162,   492,   493,   190,   766,   192,   193,   164,   169,
     868,   169,   884,   164,   162,   164,   161,   889,   162,   162,
      83,    84,    85,    86,    87,   163,   516,   517,   164,   184,
     902,    14,   804,   905,   184,   893,   797,    57,   528,   507,
     508,   167,   814,   161,   163,   184,   167,     3,   164,   163,
     162,   237,   238,   521,   826,   913,   161,   818,   819,   820,
     123,   163,   552,   161,   734,   305,   827,   308,   306,    89,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
     307,   309,   352,   855,   178,   599,   595,   691,   774,   275,
     689,   603,   694,   279,   866,   700,   857,   626,   118,   624,
     588,   588,   749,   118,   749,   536,   169,   868,    83,    84,
      85,    86,    87,   756,   905,   605,   888,   867,   889,    89,
     881,   184,   718,   784,   314,   593,   314,    -1,   618,    -1,
     543,    -1,   893,    -1,   624,    -1,    -1,   909,    83,    84,
      85,    86,    87,    -1,   916,   165,     3,   908,    -1,   686,
     165,    -1,   913,   173,   340,    -1,    -1,   625,   173,   345,
     346,   651,   118,    67,    68,    -1,    70,    71,    72,    73,
      74,    75,    76,   193,    78,    -1,   713,   714,   123,   716,
     670,    -1,    -1,   720,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   168,    -1,   608,   686,    -1,    -1,    -1,
      -1,   183,   615,    -1,    -1,    -1,   619,    -1,   621,   165,
     700,    -1,   398,   399,   400,   401,    -1,   173,    -1,    -1,
      -1,   407,   242,   713,   169,   245,    -1,   247,    -1,    -1,
     245,    -1,   247,   253,    -1,   255,   256,   257,   253,   184,
     255,   256,   257,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     718,    -1,    -1,    -1,    -1,     1,   746,    -1,    -1,   749,
      -1,   118,    -1,    -1,    -1,    -1,   734,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   687,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   695,    -1,    -1,    -1,    -1,   473,    -1,   245,
      -1,   247,    -1,    -1,    -1,   315,    -1,   253,    -1,   255,
     256,   257,   488,    -1,   490,   491,   492,   493,   165,    -1,
      -1,    57,    -1,    -1,    -1,    -1,   173,    -1,    -1,    -1,
      -1,    67,    68,   509,    -1,    -1,    -1,    -1,   818,   819,
     820,    -1,    -1,    -1,     3,    -1,   522,    -1,    -1,    -1,
       9,    -1,   528,    89,    -1,    -1,    -1,    16,    -1,    -1,
      -1,   537,    21,    -1,    -1,    24,    25,   770,    -1,   379,
     773,    30,    -1,    -1,    33,   778,   552,   857,    37,   782,
      -1,    -1,    -1,    -1,    -1,   788,   789,   790,   791,    -1,
     793,   794,   795,    -1,    -1,    -1,    -1,    -1,   245,    -1,
     247,   881,    -1,    -1,    -1,    -1,   253,    -1,   255,   256,
     257,    -1,   588,    -1,    73,    74,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    -1,   603,   908,   605,
      -1,    -1,    -1,   836,    -1,    -1,   839,    -1,    -1,    -1,
      -1,    -1,    -1,   179,    -1,    -1,    -1,    -1,     9,    -1,
      -1,   110,   188,    -1,    -1,    -1,    -1,   193,    -1,    -1,
     119,    -1,    -1,   639,    25,   124,    -1,    -1,    -1,    -1,
      57,    -1,    -1,    -1,    -1,   651,    37,    -1,    -1,    -1,
      67,    68,    -1,    70,    71,    72,    73,    74,    75,    76,
      -1,    -1,    -1,    -1,   670,    -1,    -1,   507,   508,    -1,
      -1,    -1,   507,   508,    -1,    -1,   400,   401,    -1,   685,
     686,   521,    73,    74,    -1,   691,   521,    -1,   694,    -1,
      -1,    -1,    83,    84,    85,    86,    87,   703,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   712,   713,    -1,    -1,
     716,    -1,    -1,    -1,    -1,    -1,   722,    -1,    -1,   110,
      -1,    -1,   728,    -1,    -1,    -1,    -1,    -1,   119,    -1,
      -1,   507,   508,   739,    -1,   741,    -1,    -1,    -1,    -1,
     746,   158,   159,   160,   161,   521,    -1,    -1,    -1,    -1,
      -1,   757,    -1,   593,    -1,    -1,    -1,    -1,   593,    -1,
     766,   178,    -1,    -1,    -1,   605,    -1,    -1,   492,   493,
      -1,    -1,    -1,    -1,    -1,    -1,   193,    -1,   618,    -1,
     346,    -1,    -1,    -1,   624,   625,    -1,    -1,    -1,    -1,
     625,   797,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      25,    -1,   818,   819,   820,    -1,    -1,   593,    -1,    -1,
      -1,   827,    37,    -1,    -1,   242,    -1,    -1,    -1,    -1,
     507,   508,    -1,    -1,   400,   401,   119,   120,   121,   122,
     123,   124,    -1,    -1,   521,    -1,    -1,    62,    63,   625,
      -1,   857,    -1,    -1,    -1,    -1,    -1,    -1,    73,    74,
     700,   175,   868,    -1,    -1,    -1,    -1,    -1,    83,    84,
      85,    86,    87,    -1,    -1,   881,    -1,    -1,   718,    -1,
      -1,    -1,    -1,   718,    -1,    -1,    -1,   893,    -1,    -1,
      -1,    -1,    -1,    -1,   734,   110,    -1,    -1,   315,   734,
      -1,   625,   908,    -1,   119,    -1,    -1,   913,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   593,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   490,   491,   492,   493,   242,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     254,    -1,   718,    -1,    -1,    -1,   161,    -1,   625,    -1,
     264,   166,    -1,    -1,    -1,    -1,   171,    -1,   734,    -1,
      -1,    -1,    -1,    -1,   278,   180,    -1,   281,   282,   283,
     284,   285,   286,   287,   288,   289,   290,   291,    -1,    -1,
      -1,    -1,    -1,   400,   401,    -1,    -1,    -1,    -1,    -1,
     714,   715,    -1,    -1,   718,    -1,   720,   721,    -1,   313,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,    -1,
      -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,   605,
      -1,   718,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,
       9,    -1,   618,    -1,    -1,    -1,    -1,   734,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      -1,   385,   386,    -1,    -1,   492,   493,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,    -1,   382,
      -1,    -1,    -1,    62,    63,    -1,    83,    84,    85,    86,
      87,    -1,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,
     686,    -1,   405,   689,    83,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,   110,    -1,    -1,    -1,   703,    -1,    -1,
      -1,   707,   119,    -1,    -1,    -1,    -1,    -1,     4,     5,
     464,   110,     8,     9,    -1,    -1,    -1,    13,    -1,    15,
     119,    17,    -1,    -1,    -1,   448,    22,    23,   482,    25,
      -1,    27,    28,    -1,    -1,    31,    -1,    -1,    34,    35,
      36,    37,     9,    -1,   161,    -1,    -1,    -1,   605,   166,
      -1,    -1,    -1,    -1,   171,    -1,    -1,    -1,    25,    -1,
      -1,   618,   161,   180,    -1,    -1,    -1,    63,   522,    -1,
      37,   525,   171,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    -1,    -1,    83,    84,    85,
      86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    74,   562,    -1,
      -1,    -1,   108,   109,   110,   111,    83,    84,    85,    86,
      87,    -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,   686,
      -1,    -1,    -1,    -1,   588,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   565,   110,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,    -1,    -1,    -1,   713,   714,   715,    -1,
      -1,    -1,    -1,   720,   721,   161,    -1,    -1,    -1,    -1,
     166,    -1,    -1,    -1,    -1,   171,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,     3,
       4,     5,    25,   647,     8,     9,    -1,    -1,    -1,    13,
      -1,    15,    16,    17,    37,    -1,    -1,    21,    22,    23,
      24,    25,    -1,    27,    28,    -1,    30,    31,    -1,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    74,   696,    -1,    -1,    -1,    -1,    -1,    62,    63,
      83,    84,    85,    86,    87,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    -1,    -1,    -1,   110,   732,    -1,
      -1,   735,    -1,    -1,   738,   739,   119,    -1,    -1,   743,
      -1,   745,    -1,    -1,   108,   109,   110,   111,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,   123,
     124,    -1,   766,    -1,   768,    -1,    -1,    -1,     3,     4,
       5,    -1,    -1,     8,     9,    -1,    -1,    -1,    13,    -1,
      15,    16,    17,    -1,    -1,    -1,    21,    22,    23,    24,
      25,    -1,    27,    28,    -1,    30,    31,   161,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,   171,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    -1,
      -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    -1,    83,    84,
      85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   108,   109,   110,   111,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,    -1,   124,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,   161,    39,    -1,    41,
      42,   166,    -1,    -1,    -1,    -1,   171,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   180,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    -1,    89,    90,    91,
      92,    93,    94,    95,    -1,    -1,    98,    -1,    -1,    -1,
      -1,    -1,   104,   105,   106,   107,   108,   109,   110,   111,
      -1,    -1,    -1,    -1,   116,   117,    -1,   119,   120,    -1,
      -1,   123,   124,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,
      -1,    -1,    -1,    -1,    -1,    -1,   168,   169,   170,   171,
     172,   173,   174,   175,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    -1,
      39,    -1,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    67,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    -1,
      89,    90,    91,    92,    93,    94,    95,    -1,    -1,    98,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,   108,
     109,   110,   111,    -1,    -1,    -1,    -1,   116,   117,    -1,
     119,   120,    -1,    -1,   123,   124,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   161,    -1,    -1,    -1,    -1,    -1,    -1,   168,
     169,   170,   171,   172,   173,   174,   175,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    -1,    39,    -1,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    -1,    89,    90,    91,    92,    93,    94,    95,
      -1,    -1,    98,    -1,    -1,    -1,    -1,    -1,   104,   105,
     106,   107,   108,   109,   110,   111,    -1,    -1,    -1,    -1,
     116,   117,    -1,   119,   120,    -1,    -1,   123,   124,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   161,    -1,    -1,    -1,    -1,
      -1,    -1,   168,    -1,   170,   171,   172,   173,   174,   175,
       3,     4,     5,    -1,    -1,     8,     9,    -1,    -1,    -1,
      13,    -1,    15,    16,    17,    -1,    -1,    -1,    21,    22,
      23,    24,    25,    -1,    27,    28,    29,    30,    31,    -1,
      33,    34,    35,    36,    37,    -1,    -1,    -1,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    -1,
      83,    84,    85,    86,    87,    -1,    -1,    -1,    91,    92,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,   108,   109,   110,   111,    -1,
      -1,    -1,    -1,   116,   117,    -1,   119,   120,     4,     5,
     123,   124,     8,     9,    -1,    -1,    -1,    13,    -1,    15,
      -1,    17,    -1,    -1,    -1,    -1,    22,    23,    -1,    25,
      -1,    27,    28,    29,    -1,    31,    -1,    -1,    34,    35,
      36,    37,    -1,    -1,    -1,    41,    42,    -1,   161,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,   170,   171,   172,
     173,   174,   175,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,
     106,   107,   108,   109,   110,   111,    -1,    -1,    -1,    -1,
     116,   117,    -1,   119,   120,     4,     5,    -1,    -1,     8,
       9,    -1,    -1,    -1,    13,    -1,    15,    -1,    17,    -1,
      -1,    -1,    -1,    22,    23,     9,    25,    -1,    27,    28,
      29,    -1,    31,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    25,    41,    42,    -1,   161,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    37,   170,   171,   172,   173,   174,   175,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    67,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      74,    -1,    91,    92,    93,    94,    95,    -1,    -1,    83,
      84,    85,    86,    87,    -1,   104,   105,   106,   107,   108,
     109,   110,   111,    -1,    -1,    -1,    -1,   116,   117,    -1,
     119,   120,    -1,    -1,    -1,    62,   110,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    91,    92,    93,    94,    95,    -1,
      -1,    -1,   161,    -1,    -1,    -1,    -1,   104,   105,   106,
     107,   170,   171,   172,   173,   174,   175,   161,    -1,     3,
       4,     5,   166,   120,     8,     9,    -1,   171,    -1,    13,
      -1,    15,    16,    17,    -1,    -1,   180,    21,    22,    23,
      24,    25,    -1,    27,    28,    -1,    30,    31,    -1,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   161,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      -1,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    -1,    83,
      84,    85,    86,    87,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     9,    -1,
      -1,    -1,    -1,    -1,   108,   109,   110,   111,    -1,    -1,
      -1,    -1,     4,     5,    25,   119,     8,     9,    -1,    -1,
     124,    13,    -1,    15,    -1,    17,    37,    -1,    -1,    -1,
      22,    23,    -1,    25,    -1,    27,    28,     4,     5,    31,
      -1,     8,    34,    35,    36,    37,    13,    -1,    -1,    -1,
      17,    62,    -1,    -1,    -1,    22,    23,   161,    -1,    -1,
      27,    28,    73,    74,    -1,    -1,    -1,   171,    35,    36,
      62,    63,    83,    84,    85,    86,    87,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    -1,
      -1,    83,    84,    85,    86,    87,    63,    -1,    -1,   110,
      -1,    -1,    69,    70,    71,    72,     9,    -1,   119,    76,
      77,    78,    79,    80,    -1,    -1,   108,   109,   110,   111,
      -1,    -1,    25,    -1,    -1,    -1,    29,   119,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      -1,    -1,   109,    -1,   111,    -1,    49,    -1,    -1,    -1,
     161,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
     171,    64,    65,    66,    67,    -1,    -1,    -1,    -1,   161,
      73,    74,   164,    -1,    -1,    -1,    -1,    -1,    -1,   171,
      83,    84,    85,    86,    87,    -1,    -1,    -1,    91,    92,
      93,    94,    95,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   104,   105,   106,   107,    -1,    -1,   110,    -1,    -1,
      -1,    29,    -1,   116,   117,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,    -1,
      -1,    -1,     9,    -1,   167,    -1,    -1,   170,   171,   172,
     173,   174,   175,    91,    92,    93,    94,    95,    25,    -1,
      -1,    -1,    -1,    29,    -1,    -1,   104,   105,   106,   107,
      37,    -1,    -1,    -1,    -1,    41,    42,    -1,   116,   117,
      -1,    -1,   120,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    73,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,    86,
      87,    -1,    -1,   161,    -1,    91,    92,    93,    94,    95,
      -1,    -1,   170,   171,   172,   173,   174,   175,   104,   105,
     106,   107,    -1,   110,    -1,    -1,   184,    -1,    29,    -1,
     116,   117,   119,    -1,   120,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   161,    -1,    -1,    -1,   165,
     166,    -1,   168,    -1,   170,   171,   172,   173,   174,   175,
      91,    92,    93,    94,    95,    -1,    -1,   183,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,   116,   117,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     161,    -1,    -1,    -1,   165,   166,    -1,   168,   169,   170,
     171,   172,   173,   174,   175,    91,    92,    93,    94,    95,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   104,   105,
     106,   107,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
     116,   117,    -1,    -1,   120,    -1,    -1,    -1,    -1,    -1,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   161,    -1,    -1,    -1,   165,
     166,    -1,   168,   169,   170,   171,   172,   173,   174,   175,
      91,    92,    93,    94,    95,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,   116,   117,    -1,    -1,   120,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     161,    -1,    -1,    -1,   165,   166,    -1,   168,    -1,   170,
     171,   172,   173,   174,   175,    91,    92,    93,    94,    95,
      -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,   104,   105,
     106,   107,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
     116,   117,    -1,    -1,   120,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   161,   162,    91,    92,    93,
      94,    95,    -1,    -1,   170,   171,   172,   173,   174,   175,
     104,   105,   106,   107,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,   116,   117,    -1,    -1,   120,    -1,    -1,    -1,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    64,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,    -1,    -1,
     164,    -1,    -1,    -1,    -1,    -1,   170,   171,   172,   173,
     174,   175,    91,    92,    93,    94,    95,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    -1,   116,   117,    -1,
      -1,   120,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,
      64,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   161,    -1,    -1,    -1,    -1,    -1,   167,    -1,
      -1,   170,   171,   172,   173,   174,   175,    91,    92,    93,
      94,    95,    -1,    -1,    -1,    -1,    -1,    29,    -1,    -1,
     104,   105,   106,   107,    -1,    -1,    -1,    -1,    -1,    41,
      42,    -1,   116,   117,    -1,    -1,   120,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    64,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,    -1,    91,
      92,    93,    94,    95,   168,    -1,   170,   171,   172,   173,
     174,   175,   104,   105,   106,   107,    -1,    -1,    -1,    -1,
      -1,    -1,    29,    -1,   116,   117,    -1,    -1,   120,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    64,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   161,
      -1,    -1,    -1,    -1,    -1,    -1,   168,    -1,   170,   171,
     172,   173,   174,   175,    91,    92,    93,    94,    95,    -1,
      -1,    -1,    -1,    -1,    29,    -1,    -1,   104,   105,   106,
     107,    -1,    -1,    -1,    -1,    -1,    41,    42,    -1,   116,
     117,    -1,    -1,   120,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    -1,    64,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   161,    -1,    91,    92,    93,    94,
      95,    -1,    -1,   170,   171,   172,   173,   174,   175,   104,
     105,   106,   107,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,   116,   117,    -1,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    64,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   161,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   170,   171,   172,   173,   174,
     175,    91,    92,    93,    94,    95,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   104,   105,   106,   107,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   116,   117,    -1,    -1,
     120,     3,     4,     5,    -1,    -1,     8,     9,    -1,    -1,
      -1,    13,    -1,    15,    16,    17,    -1,    -1,    -1,    21,
      22,    23,    24,    25,    -1,    27,    28,    -1,    30,    31,
      -1,    33,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,   161,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     170,   171,   172,   173,   174,   175,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      -1,    83,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   109,   110,   111,
      -1,    -1,    -1,     3,     4,     5,    -1,   119,     8,     9,
      -1,   123,   124,    13,    -1,    15,    16,    17,    -1,    -1,
      -1,    21,    22,    23,    24,    25,    -1,    27,    28,    -1,
      30,    31,    -1,    33,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    -1,    83,    84,    85,    86,    87,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   108,   109,
     110,   111,    -1,    -1,    -1,     3,     4,     5,    -1,   119,
       8,     9,    -1,    -1,   124,    13,    -1,    15,    16,    17,
      -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,    27,
      28,    -1,    30,    31,    -1,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,
      -1,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    -1,    83,    84,    85,    86,    87,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     108,   109,   110,   111,    -1,    -1,    -1,     3,     4,     5,
      -1,   119,     8,     9,    -1,    -1,   124,    13,    -1,    15,
      16,    17,    -1,    -1,    -1,    21,    22,    23,    24,    25,
      -1,    27,    28,    -1,    30,    31,    -1,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,
      -1,    -1,    -1,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   108,   109,   110,   111,     3,     4,     5,    -1,
      -1,     8,     9,   119,    -1,    -1,    13,    -1,   124,    16,
      17,    -1,    -1,    -1,    21,    22,    23,    24,    25,    -1,
      27,    28,    -1,    30,    -1,    -1,    33,    -1,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    69,    70,    71,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   109,   110,   111,     4,     5,    -1,    -1,     8,
       9,    -1,   119,    -1,    13,    -1,    15,   124,    17,    -1,
      -1,    -1,    -1,    22,    23,    -1,    25,    -1,    27,    28,
      -1,    -1,    31,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    83,    84,    85,    86,    87,    -1,
      -1,    -1,    -1,    -1,    -1,     4,     5,    -1,    -1,     8,
       9,    -1,    11,    -1,    13,    -1,    15,    -1,    17,   108,
     109,   110,   111,    22,    23,    -1,    25,    -1,    27,    28,
     119,    -1,    31,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     4,     5,    -1,    -1,     8,
       9,    -1,    -1,    -1,    13,    -1,    15,    -1,    17,   108,
     109,   110,   111,    22,    23,    -1,    25,    -1,    27,    28,
     119,    -1,    31,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,     4,     5,    -1,    -1,     8,     9,    -1,    -1,
      -1,    13,    -1,    -1,    -1,    17,    -1,    -1,    -1,    -1,
      22,    23,    -1,    25,    -1,    27,    28,    -1,    -1,   108,
     109,   110,   111,    35,    36,    37,    -1,    -1,    -1,    -1,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    71,
      72,    73,    74,    -1,    76,    77,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,   110,   111,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   119
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,   158,   159,   160,   186,     3,     4,     5,     8,     9,
      13,    15,    16,    17,    21,    22,    23,    24,    25,    27,
      28,    30,    31,    33,    34,    35,    36,    37,    62,    63,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,   108,
     109,   110,   111,   119,   123,   124,   161,   171,   184,   187,
     188,   227,   228,   229,   236,   240,   241,   242,   243,   246,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   264,   267,   277,   280,   329,   330,
     331,   332,   333,   343,   352,   353,   354,   355,    29,    41,
      42,    49,    64,    65,    66,    67,    91,    92,    93,    94,
      95,   104,   105,   106,   107,   116,   117,   120,   161,   170,
     171,   172,   173,   174,   175,   187,   189,   190,   191,   192,
     193,   194,   195,   198,   199,   200,   202,   203,   204,   205,
     208,   209,   210,   211,   212,   213,   214,   215,   216,   217,
     218,   219,   220,   221,   222,   223,   224,   241,   243,   249,
     251,   254,   256,   290,     0,   161,   161,    88,   161,    88,
      88,   161,   161,   178,   166,   161,   353,   355,   243,   244,
     246,   247,   267,   352,   265,   266,   267,   184,   163,   184,
     163,   184,   161,   171,   184,   188,   344,   345,   346,   347,
     348,   349,   350,   352,   184,   344,   188,   245,   246,   255,
     257,   258,   259,   267,   352,   188,   246,   255,   257,   258,
     259,   267,   352,   245,   258,   246,   257,   258,   245,   246,
     257,   245,   245,   246,   257,   257,   265,   265,   265,   331,
     334,   161,   166,   358,   363,   161,   208,   161,   208,   208,
     187,   188,   289,   161,   161,   161,   161,   161,   301,   301,
     301,   301,   208,   208,   161,   224,   290,   300,   301,   209,
     209,   209,   209,   209,   209,    40,    41,    42,   161,   165,
     166,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,   183,   171,   176,   177,   172,   173,    43,    44,    45,
      46,   178,   179,    47,    48,   170,   180,   181,    49,    50,
     112,   113,   182,   163,   161,   171,   180,   356,   358,   364,
     366,   356,   224,   290,   192,   224,   224,   187,   290,   224,
     223,   162,   162,   246,   247,   267,   352,   267,   352,   344,
     161,   188,   347,   349,   351,   161,   244,   346,   349,   358,
      82,   233,   234,   235,   267,   235,   265,   265,   265,   230,
     265,   265,   231,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   262,   289,   278,   289,   300,   335,   162,   359,
     360,   167,   171,   223,   225,   244,   166,   290,   290,   290,
     223,   290,   290,   208,   290,   168,   168,   227,   240,   241,
     242,   243,   227,   223,   162,   162,   162,   168,   187,   188,
     206,   162,   207,   223,   206,   224,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   209,   209,   209,
     209,   210,   210,   211,   211,   212,   212,   212,   212,   213,
     213,   214,   215,   216,   217,   218,   220,   220,   164,   224,
     223,   358,   364,   366,   244,   356,   162,   162,   162,   162,
     162,   162,   179,   167,   163,   358,   232,   235,   351,   162,
     162,   358,   351,   161,   346,   349,    19,    37,   315,   233,
     237,   238,   183,   291,   291,   168,   263,   265,   168,   279,
     240,   241,   242,   243,   284,   287,   288,   187,   285,   286,
     167,   167,   225,   225,   162,   162,   162,   163,   163,   163,
     162,   162,   227,   227,   161,   194,   344,   344,   352,   352,
     194,   163,   168,   209,     6,     7,    10,    11,    12,    18,
      19,    20,    26,    32,    39,    68,    82,    89,    90,    98,
     149,   169,   187,   188,   224,   226,   227,   289,   297,   298,
     299,   300,   302,   303,   304,   306,   308,   309,   312,   313,
     314,   162,   163,   167,   222,   164,   162,   162,   162,   356,
     184,    88,    88,    88,   223,   291,   239,   162,   358,   358,
     162,   162,   351,    37,    19,   161,   291,   291,   168,   225,
     292,   184,   228,   265,   268,   269,   270,   271,   272,   168,
     281,   282,   289,   168,   161,   171,   180,   346,   352,   357,
     361,   363,   365,   367,   346,   352,   357,   161,   171,   352,
     357,   352,   357,   162,   163,   162,   163,   167,   167,   290,
     290,   201,   206,   224,   224,    11,   196,   197,   290,   165,
     166,   187,   206,   292,   293,   294,   295,   296,   184,   225,
     184,   164,   297,   307,   224,   161,   184,   224,   161,   161,
     169,   168,   315,   289,   310,   311,    68,   168,   300,   184,
     164,   169,   297,   223,   222,   358,   162,   291,   162,   192,
     316,   317,   293,   294,   184,   241,   243,   169,   270,   163,
     184,   163,   184,   268,   163,   169,   183,   283,   281,   162,
     362,   365,   367,   244,   357,   265,   265,   244,   265,   265,
      51,   288,   241,   243,   249,   254,   257,   336,   337,   338,
     339,   340,   341,   342,   286,   162,   162,   162,   165,   166,
     169,   169,   164,   162,   163,   164,   206,   224,   164,   163,
     169,   165,   166,   183,   292,    51,   164,   297,    39,   161,
     184,   224,   184,   224,   226,    68,   161,   163,   184,    68,
      96,    97,   297,   162,   164,   318,   163,   169,   164,   273,
     276,   344,   274,   276,   352,   265,   274,   273,   169,   282,
     265,   225,   169,   284,   162,   162,   357,   344,   257,   257,
     188,   258,   338,   245,   258,   245,   344,   163,   184,   206,
     224,   223,   197,   223,    51,   167,   292,   169,   295,   206,
     224,   292,   225,   297,   161,   298,   303,   305,   162,   162,
     162,   169,   316,   311,   169,   300,   161,   166,   192,   319,
     320,   164,   321,   169,   225,   265,   275,   276,   265,   275,
     265,   265,   162,   161,   361,   265,   265,   265,   265,   265,
     265,   265,   344,   167,   224,    51,   167,   164,   224,   226,
     297,   297,   297,   162,   224,   289,   161,   163,   166,   192,
     322,   323,   164,   324,   265,   265,   167,   224,   297,   162,
     184,    14,   184,   162,   167,   224,   319,   289,   161,   163,
     192,   325,   326,   164,   327,   167,   184,   226,   297,   300,
     192,   162,   167,   224,   322,   163,   311,   328,   162,   161,
     192,   162,   325,   163,   297,   224,   161,   311,   162,   224,
     162
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

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


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
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
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
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
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

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

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

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

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

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
/* Line 1787 of yacc.c  */
#line 229 "parser.y"
    {
          ansi_c_declarationt ansi_c_declaration;
          ansi_c_declaration.value()=stack((yyvsp[(2) - (2)]));
          PARSER.copy_item(ansi_c_declaration);
        }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 235 "parser.y"
    {
          ansi_c_declarationt ansi_c_declaration;
          ansi_c_declaration.type()=
            static_cast<const typet &>(static_cast<const irept &>(stack((yyvsp[(2) - (2)]))));
          ansi_c_declaration.set_is_type(true);
          PARSER.copy_item(ansi_c_declaration);
        }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 284 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 296 "parser.y"
    {
          init((yyval), ID_generic_selection);
          mto((yyval), (yyvsp[(3) - (6)]));
          stack((yyval)).add(ID_generic_associations).get_sub().swap(stack((yyvsp[(5) - (6)])).add(ID_operands).get_sub());
        }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 305 "parser.y"
    {
          init((yyval)); mto((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 309 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]); mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 316 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (3)]);
          stack((yyval)).id(ID_generic_association);
          stack((yyval)).set(ID_type_arg, stack((yyvsp[(1) - (3)])));
          stack((yyval)).set(ID_value, stack((yyvsp[(3) - (3)])));
        }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 323 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (3)]);
          stack((yyval)).id(ID_generic_association);
          stack((yyval)).set(ID_type_arg, irept(ID_default));
          stack((yyval)).set(ID_value, stack((yyvsp[(3) - (3)])));
        }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 333 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyval)).id(ID_gcc_builtin_va_arg);
          mto((yyval), (yyvsp[(3) - (6)]));
          stack((yyval)).type().swap(stack((yyvsp[(5) - (6)])));
        }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 341 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyval)).id(ID_gcc_builtin_types_compatible_p);
          irept::subt &subtypes=stack((yyval)).add(ID_subtypes).get_sub();
          subtypes.resize(2);
          subtypes[0].swap(stack((yyvsp[(3) - (6)])));
          subtypes[1].swap(stack((yyvsp[(5) - (6)])));
        }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 353 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          stack((yyval)).id(ID_cw_va_arg_typeof);
          stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 362 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyval)).id(ID_builtin_offsetof);
          stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (6)])));
          stack((yyval)).add(ID_designator).swap(stack((yyvsp[(5) - (6)])));
        }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 372 "parser.y"
    {
          init((yyval), ID_designated_initializer);
          stack((yyval)).operands().resize(1);
          stack((yyval)).op0().id(ID_member);
          stack((yyval)).op0().location()=stack((yyvsp[(1) - (1)])).location();
          stack((yyval)).op0().set(ID_component_name, stack((yyvsp[(1) - (1)])).get(ID_C_base_name));
        }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 380 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          set((yyvsp[(2) - (3)]), ID_member);
          stack((yyvsp[(2) - (3)])).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
          mto((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 387 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyvsp[(2) - (4)]), ID_index);
          mto((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]));
          mto((yyval), (yyvsp[(2) - (4)]));
        }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 396 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_alignof);
          mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 401 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          stack((yyval)).id(ID_alignof);
          stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 410 "parser.y"
    {
          init((yyval));
          stack((yyval)).id(ID_forall);
          stack((yyval)).location()=stack((yyvsp[(1) - (6)])).location();
          mto((yyval), (yyvsp[(4) - (6)]));
          mto((yyval), (yyvsp[(5) - (6)]));
          PARSER.pop_scope();
        }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 419 "parser.y"
    {
          init((yyval));
          stack((yyval)).id(ID_forall);
          stack((yyval)).location()=stack((yyvsp[(1) - (4)])).location();
          mto((yyval), (yyvsp[(3) - (4)]));
          mto((yyval), (yyvsp[(4) - (4)]));
          PARSER.pop_scope();
        }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 428 "parser.y"
    {
          init((yyval));
          stack((yyval)).id(ID_exists);
          stack((yyval)).location()=stack((yyvsp[(1) - (6)])).location();
          mto((yyval), (yyvsp[(4) - (6)]));
          mto((yyval), (yyvsp[(5) - (6)]));
          PARSER.pop_scope();
        }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 437 "parser.y"
    {
          init((yyval));
          stack((yyval)).id(ID_exists);
          stack((yyval)).location()=stack((yyvsp[(1) - (4)])).location();
          mto((yyval), (yyvsp[(3) - (4)]));
          mto((yyval), (yyvsp[(4) - (4)]));
          PARSER.pop_scope();
        }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 448 "parser.y"
    { init((yyval), ID_sideeffect);
          stack((yyval)).set(ID_statement, ID_statement_expression);
          stack((yyval)).location()=stack((yyvsp[(1) - (3)])).location();
          mto((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 458 "parser.y"
    { binary((yyval), (yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), ID_index, (yyvsp[(3) - (4)])); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 460 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]);
          set((yyval), ID_sideeffect);
          stack((yyval)).operands().resize(2);
          stack((yyval)).op0().swap(stack((yyvsp[(1) - (3)])));
          stack((yyval)).op1().clear();
          stack((yyval)).op1().id(ID_arguments);
          stack((yyval)).set(ID_statement, ID_function_call);
        }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 469 "parser.y"
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

  case 48:
/* Line 1787 of yacc.c  */
#line 480 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]);
          set((yyval), ID_member);
          mto((yyval), (yyvsp[(1) - (3)]));
          stack((yyval)).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
        }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 486 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]);
          set((yyval), ID_ptrmember);
          mto((yyval), (yyvsp[(1) - (3)]));
          stack((yyval)).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
        }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 492 "parser.y"
    { (yyval)=(yyvsp[(2) - (2)]);
          locationt location=stack((yyvsp[(2) - (2)])).location();
          init((yyval), ID_sideeffect);
          mto((yyval), (yyvsp[(1) - (2)]));
          stack((yyval)).set(ID_statement, ID_postincrement);
          stack((yyval)).location()=location;
        }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 500 "parser.y"
    { (yyval)=(yyvsp[(2) - (2)]);
          locationt location=stack((yyvsp[(2) - (2)])).location();
          init((yyval), ID_sideeffect);
          mto((yyval), (yyvsp[(1) - (2)]));
          stack((yyval)).set(ID_statement, ID_postdecrement);
          stack((yyval)).location()=location;
        }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 509 "parser.y"
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

  case 53:
/* Line 1787 of yacc.c  */
#line 519 "parser.y"
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

  case 56:
/* Line 1787 of yacc.c  */
#line 538 "parser.y"
    {
          init((yyval), ID_expression_list);
          mto((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 543 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 552 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_sideeffect);
          stack((yyval)).set(ID_statement, ID_preincrement);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 558 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_sideeffect);
          stack((yyval)).set(ID_statement, ID_predecrement);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 564 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_address_of);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 569 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          irep_idt identifier=PARSER.lookup_label(stack((yyvsp[(2) - (2)])).get(ID_C_base_name));
          set((yyval), ID_address_of);
          stack((yyval)).operands().resize(1);
          stack((yyval)).op0()=stack((yyvsp[(2) - (2)]));
          stack((yyval)).op0().id(ID_label);
          stack((yyval)).op0().set(ID_identifier, identifier);
        }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 578 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_dereference);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 583 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_unary_plus);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 588 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_unary_minus);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 593 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_bitnot);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 598 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_not);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 603 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_sizeof);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 608 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_sizeof);
          stack((yyval)).add(ID_type_arg).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 613 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_complex_real);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 618 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_complex_imag);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 627 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_typecast);
          mto((yyval), (yyvsp[(4) - (4)]));
          stack((yyval)).type().swap(stack((yyvsp[(2) - (4)])));
        }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 638 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_mult, (yyvsp[(3) - (3)])); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 640 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_div, (yyvsp[(3) - (3)])); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 642 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_mod, (yyvsp[(3) - (3)])); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 648 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_plus, (yyvsp[(3) - (3)])); }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 650 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_minus, (yyvsp[(3) - (3)])); }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 656 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_shl, (yyvsp[(3) - (3)])); }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 658 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_shr, (yyvsp[(3) - (3)])); }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 664 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_lt, (yyvsp[(3) - (3)])); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 666 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_gt, (yyvsp[(3) - (3)])); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 668 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_le, (yyvsp[(3) - (3)])); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 670 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_ge, (yyvsp[(3) - (3)])); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 676 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_equal, (yyvsp[(3) - (3)])); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 678 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_notequal, (yyvsp[(3) - (3)])); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 684 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_bitand, (yyvsp[(3) - (3)])); }
    break;

  case 95:
/* Line 1787 of yacc.c  */
#line 690 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_bitxor, (yyvsp[(3) - (3)])); }
    break;

  case 97:
/* Line 1787 of yacc.c  */
#line 696 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_bitor, (yyvsp[(3) - (3)])); }
    break;

  case 99:
/* Line 1787 of yacc.c  */
#line 702 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_and, (yyvsp[(3) - (3)])); }
    break;

  case 101:
/* Line 1787 of yacc.c  */
#line 708 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_or, (yyvsp[(3) - (3)])); }
    break;

  case 103:
/* Line 1787 of yacc.c  */
#line 717 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_implies, (yyvsp[(3) - (3)])); }
    break;

  case 105:
/* Line 1787 of yacc.c  */
#line 726 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_equal, (yyvsp[(3) - (3)])); }
    break;

  case 107:
/* Line 1787 of yacc.c  */
#line 732 "parser.y"
    { (yyval)=(yyvsp[(2) - (5)]);
          stack((yyval)).id(ID_if);
          mto((yyval), (yyvsp[(1) - (5)]));
          mto((yyval), (yyvsp[(3) - (5)]));
          mto((yyval), (yyvsp[(5) - (5)]));
        }
    break;

  case 108:
/* Line 1787 of yacc.c  */
#line 739 "parser.y"
    { (yyval)=(yyvsp[(2) - (4)]);
          stack((yyval)).id(ID_sideeffect);
          stack((yyval)).set(ID_statement, ID_gcc_conditional_expression);
          mto((yyval), (yyvsp[(1) - (4)]));
          mto((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 110:
/* Line 1787 of yacc.c  */
#line 750 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign); }
    break;

  case 111:
/* Line 1787 of yacc.c  */
#line 752 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_mult); }
    break;

  case 112:
/* Line 1787 of yacc.c  */
#line 754 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_div); }
    break;

  case 113:
/* Line 1787 of yacc.c  */
#line 756 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_mod); }
    break;

  case 114:
/* Line 1787 of yacc.c  */
#line 758 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_plus); }
    break;

  case 115:
/* Line 1787 of yacc.c  */
#line 760 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_minus); }
    break;

  case 116:
/* Line 1787 of yacc.c  */
#line 762 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_shl); }
    break;

  case 117:
/* Line 1787 of yacc.c  */
#line 764 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_shr); }
    break;

  case 118:
/* Line 1787 of yacc.c  */
#line 766 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_bitand); }
    break;

  case 119:
/* Line 1787 of yacc.c  */
#line 768 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_bitxor); }
    break;

  case 120:
/* Line 1787 of yacc.c  */
#line 770 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_sideeffect, (yyvsp[(3) - (3)])); stack((yyval)).set(ID_statement, ID_assign_bitor); }
    break;

  case 122:
/* Line 1787 of yacc.c  */
#line 776 "parser.y"
    { binary((yyval), (yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), ID_comma, (yyvsp[(3) - (3)])); }
    break;

  case 124:
/* Line 1787 of yacc.c  */
#line 785 "parser.y"
    { init((yyval)); stack((yyval)).make_nil(); }
    break;

  case 126:
/* Line 1787 of yacc.c  */
#line 793 "parser.y"
    {
          // type only, no identifier!
          codet decl(ID_decl_type);
          decl.add(ID_type_arg).swap(stack((yyvsp[(1) - (2)])));
          init((yyval));
          stack((yyval)).move_to_operands(decl);
        }
    break;

  case 127:
/* Line 1787 of yacc.c  */
#line 801 "parser.y"
    {
          // type only, no identifier!
          codet decl(ID_decl_type);
          decl.add(ID_type_arg).swap(stack((yyvsp[(1) - (2)])));
          init((yyval));
          stack((yyval)).move_to_operands(decl);
        }
    break;

  case 131:
/* Line 1787 of yacc.c  */
#line 815 "parser.y"
    {
          mto((yyvsp[(1) - (6)]), (yyvsp[(3) - (6)]));
          mto((yyvsp[(1) - (6)]), (yyvsp[(5) - (6)]));
          stack((yyvsp[(1) - (6)])).id(ID_code);
          stack((yyvsp[(1) - (6)])).set(ID_statement, ID_static_assert);
          init((yyval));
          mto((yyval), (yyvsp[(1) - (6)]));
        }
    break;

  case 132:
/* Line 1787 of yacc.c  */
#line 827 "parser.y"
    {
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 133:
/* Line 1787 of yacc.c  */
#line 833 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (4)]));
          decl_statement((yyval), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
        }
    break;

  case 134:
/* Line 1787 of yacc.c  */
#line 839 "parser.y"
    {
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 135:
/* Line 1787 of yacc.c  */
#line 845 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (4)]));
          decl_statement((yyval), (yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]));
        }
    break;

  case 136:
/* Line 1787 of yacc.c  */
#line 851 "parser.y"
    {
            init((yyval));
            const irept &t=stack((yyvsp[(1) - (3)])).find(ID_type);
            PARSER.new_declaration(t, stack((yyvsp[(3) - (3)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 137:
/* Line 1787 of yacc.c  */
#line 858 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          decl_statement((yyval), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
        }
    break;

  case 138:
/* Line 1787 of yacc.c  */
#line 866 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          stack((yyval)).id(ID_asm);
        }
    break;

  case 140:
/* Line 1787 of yacc.c  */
#line 875 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 142:
/* Line 1787 of yacc.c  */
#line 884 "parser.y"
    {
          init((yyval));
        }
    break;

  case 144:
/* Line 1787 of yacc.c  */
#line 893 "parser.y"
    {
            // the symbol has to be visible during initialization
            merge_types((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); // type attribute
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(2) - (3)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 145:
/* Line 1787 of yacc.c  */
#line 901 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (5)])); // save for later
          decl_statement((yyval), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
        }
    break;

  case 146:
/* Line 1787 of yacc.c  */
#line 908 "parser.y"
    {
            // the symbol has to be visible during initialization
            merge_types((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); // type attribute
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(2) - (3)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 147:
/* Line 1787 of yacc.c  */
#line 916 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (5)])); // save for later
          decl_statement((yyval), (yyvsp[(4) - (5)]), (yyvsp[(5) - (5)]));
        }
    break;

  case 148:
/* Line 1787 of yacc.c  */
#line 923 "parser.y"
    {
            init((yyval));
            irept t=stack((yyvsp[(1) - (4)])).find(ID_type);
            merge_types(t, stack((yyvsp[(4) - (4)]))); // type attribute
            PARSER.new_declaration(t, stack((yyvsp[(3) - (4)])), stack((yyval)));
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 149:
/* Line 1787 of yacc.c  */
#line 931 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (6)]);
          decl_statement((yyval), (yyvsp[(5) - (6)]), (yyvsp[(6) - (6)]));
        }
    break;

  case 159:
/* Line 1787 of yacc.c  */
#line 954 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 161:
/* Line 1787 of yacc.c  */
#line 960 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 162:
/* Line 1787 of yacc.c  */
#line 965 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 164:
/* Line 1787 of yacc.c  */
#line 974 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 165:
/* Line 1787 of yacc.c  */
#line 982 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 167:
/* Line 1787 of yacc.c  */
#line 991 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 170:
/* Line 1787 of yacc.c  */
#line 1003 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_atomic); }
    break;

  case 171:
/* Line 1787 of yacc.c  */
#line 1004 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_const); }
    break;

  case 172:
/* Line 1787 of yacc.c  */
#line 1005 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_restrict); }
    break;

  case 173:
/* Line 1787 of yacc.c  */
#line 1006 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_volatile); }
    break;

  case 174:
/* Line 1787 of yacc.c  */
#line 1007 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_cprover_atomic); }
    break;

  case 175:
/* Line 1787 of yacc.c  */
#line 1008 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_ptr32); }
    break;

  case 176:
/* Line 1787 of yacc.c  */
#line 1009 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_ptr64); }
    break;

  case 179:
/* Line 1787 of yacc.c  */
#line 1019 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 180:
/* Line 1787 of yacc.c  */
#line 1025 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 181:
/* Line 1787 of yacc.c  */
#line 1031 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 182:
/* Line 1787 of yacc.c  */
#line 1037 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 183:
/* Line 1787 of yacc.c  */
#line 1046 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)])); // type attribute
        }
    break;

  case 184:
/* Line 1787 of yacc.c  */
#line 1051 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 185:
/* Line 1787 of yacc.c  */
#line 1057 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 186:
/* Line 1787 of yacc.c  */
#line 1062 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 187:
/* Line 1787 of yacc.c  */
#line 1072 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 188:
/* Line 1787 of yacc.c  */
#line 1077 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 189:
/* Line 1787 of yacc.c  */
#line 1082 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 191:
/* Line 1787 of yacc.c  */
#line 1092 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 192:
/* Line 1787 of yacc.c  */
#line 1097 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 193:
/* Line 1787 of yacc.c  */
#line 1105 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 194:
/* Line 1787 of yacc.c  */
#line 1111 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 195:
/* Line 1787 of yacc.c  */
#line 1117 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 196:
/* Line 1787 of yacc.c  */
#line 1126 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 197:
/* Line 1787 of yacc.c  */
#line 1132 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 198:
/* Line 1787 of yacc.c  */
#line 1138 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 199:
/* Line 1787 of yacc.c  */
#line 1147 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)])); // type attribute
        }
    break;

  case 200:
/* Line 1787 of yacc.c  */
#line 1152 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 201:
/* Line 1787 of yacc.c  */
#line 1158 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 202:
/* Line 1787 of yacc.c  */
#line 1167 "parser.y"
    { (yyval) = (yyvsp[(1) - (4)]);
          stack((yyval)).id(ID_typeof);
          mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 203:
/* Line 1787 of yacc.c  */
#line 1172 "parser.y"
    { (yyval) = (yyvsp[(1) - (4)]);
          stack((yyval)).id(ID_typeof);
          stack((yyval)).set(ID_type_arg, stack((yyvsp[(3) - (4)])));
        }
    break;

  case 205:
/* Line 1787 of yacc.c  */
#line 1181 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          merge_types((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 206:
/* Line 1787 of yacc.c  */
#line 1221 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_typedef); }
    break;

  case 207:
/* Line 1787 of yacc.c  */
#line 1222 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_extern); }
    break;

  case 208:
/* Line 1787 of yacc.c  */
#line 1223 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_static); }
    break;

  case 209:
/* Line 1787 of yacc.c  */
#line 1224 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_auto); }
    break;

  case 210:
/* Line 1787 of yacc.c  */
#line 1225 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_register); }
    break;

  case 211:
/* Line 1787 of yacc.c  */
#line 1226 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_inline); }
    break;

  case 212:
/* Line 1787 of yacc.c  */
#line 1227 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_thread_local); }
    break;

  case 213:
/* Line 1787 of yacc.c  */
#line 1228 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_asm); }
    break;

  case 214:
/* Line 1787 of yacc.c  */
#line 1232 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int); }
    break;

  case 215:
/* Line 1787 of yacc.c  */
#line 1233 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int8); }
    break;

  case 216:
/* Line 1787 of yacc.c  */
#line 1234 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int16); }
    break;

  case 217:
/* Line 1787 of yacc.c  */
#line 1235 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int32); }
    break;

  case 218:
/* Line 1787 of yacc.c  */
#line 1236 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_int64); }
    break;

  case 219:
/* Line 1787 of yacc.c  */
#line 1237 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_char); }
    break;

  case 220:
/* Line 1787 of yacc.c  */
#line 1238 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_short); }
    break;

  case 221:
/* Line 1787 of yacc.c  */
#line 1239 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_long); }
    break;

  case 222:
/* Line 1787 of yacc.c  */
#line 1240 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_float); }
    break;

  case 223:
/* Line 1787 of yacc.c  */
#line 1241 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_gcc_float128); }
    break;

  case 224:
/* Line 1787 of yacc.c  */
#line 1242 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_gcc_int128); }
    break;

  case 225:
/* Line 1787 of yacc.c  */
#line 1243 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_gcc_decimal32); }
    break;

  case 226:
/* Line 1787 of yacc.c  */
#line 1244 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_gcc_decimal64); }
    break;

  case 227:
/* Line 1787 of yacc.c  */
#line 1245 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_gcc_decimal128); }
    break;

  case 228:
/* Line 1787 of yacc.c  */
#line 1246 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_double); }
    break;

  case 229:
/* Line 1787 of yacc.c  */
#line 1247 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_signed); }
    break;

  case 230:
/* Line 1787 of yacc.c  */
#line 1248 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_unsigned); }
    break;

  case 231:
/* Line 1787 of yacc.c  */
#line 1249 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_void); }
    break;

  case 232:
/* Line 1787 of yacc.c  */
#line 1250 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_bool); }
    break;

  case 233:
/* Line 1787 of yacc.c  */
#line 1251 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_complex); }
    break;

  case 234:
/* Line 1787 of yacc.c  */
#line 1253 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_bv);
          stack((yyval)).add(ID_size).swap(stack((yyvsp[(3) - (4)])));
        }
    break;

  case 235:
/* Line 1787 of yacc.c  */
#line 1258 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_proper_bool); }
    break;

  case 239:
/* Line 1787 of yacc.c  */
#line 1269 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]); ((typet &)stack((yyval))).subtype().swap(stack((yyvsp[(2) - (4)]))); }
    break;

  case 240:
/* Line 1787 of yacc.c  */
#line 1275 "parser.y"
    {
            // an anon struct/union
            exprt symbol(ID_symbol);
            symbol.set(ID_C_base_name, PARSER.get_anon_name());

            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (2)])), symbol, stack((yyval)), true);
          }
    break;

  case 241:
/* Line 1787 of yacc.c  */
#line 1285 "parser.y"
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

  case 242:
/* Line 1787 of yacc.c  */
#line 1303 "parser.y"
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

  case 243:
/* Line 1787 of yacc.c  */
#line 1316 "parser.y"
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

  case 244:
/* Line 1787 of yacc.c  */
#line 1335 "parser.y"
    {
          do_tag((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
          (yyval)=(yyvsp[(3) - (4)]);
          // type attributes
          merge_types((yyval), (yyvsp[(2) - (4)]));
          merge_types((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 245:
/* Line 1787 of yacc.c  */
#line 1346 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_struct); }
    break;

  case 246:
/* Line 1787 of yacc.c  */
#line 1348 "parser.y"
    { (yyval)=(yyvsp[(1) - (1)]); set((yyval), ID_union); }
    break;

  case 247:
/* Line 1787 of yacc.c  */
#line 1353 "parser.y"
    {
          init((yyval));
        }
    break;

  case 250:
/* Line 1787 of yacc.c  */
#line 1362 "parser.y"
    {
          merge_types((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 251:
/* Line 1787 of yacc.c  */
#line 1369 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); set((yyval), ID_packed); }
    break;

  case 252:
/* Line 1787 of yacc.c  */
#line 1371 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); set((yyval), ID_transparent_union); }
    break;

  case 253:
/* Line 1787 of yacc.c  */
#line 1373 "parser.y"
    { (yyval)=(yyvsp[(1) - (5)]); set((yyval), ID_vector); stack((yyval)).add(ID_size)=stack((yyvsp[(3) - (5)])); }
    break;

  case 254:
/* Line 1787 of yacc.c  */
#line 1375 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); set((yyval), ID_aligned); }
    break;

  case 255:
/* Line 1787 of yacc.c  */
#line 1377 "parser.y"
    { (yyval)=(yyvsp[(1) - (5)]); set((yyval), ID_aligned); stack((yyval)).set(ID_size, stack((yyvsp[(3) - (5)]))); }
    break;

  case 256:
/* Line 1787 of yacc.c  */
#line 1379 "parser.y"
    { (yyval)=(yyvsp[(1) - (5)]); set((yyval), ID_gcc_attribute_mode); stack((yyval)).set(ID_size, stack((yyvsp[(3) - (5)])).get(ID_identifier)); }
    break;

  case 257:
/* Line 1787 of yacc.c  */
#line 1384 "parser.y"
    {
          init((yyval), ID_declaration_list);
        }
    break;

  case 260:
/* Line 1787 of yacc.c  */
#line 1393 "parser.y"
    {
          assert(stack((yyvsp[(1) - (2)])).id()==ID_declaration_list);
          assert(stack((yyvsp[(2) - (2)])).id()==ID_declaration_list);
          (yyval)=(yyvsp[(1) - (2)]);
          Forall_operands(it, stack((yyvsp[(2) - (2)])))
            stack((yyval)).move_to_operands(*it);
          stack((yyvsp[(2) - (2)])).clear();
        }
    break;

  case 263:
/* Line 1787 of yacc.c  */
#line 1407 "parser.y"
    {
          init((yyval), ID_declaration_list);
        }
    break;

  case 264:
/* Line 1787 of yacc.c  */
#line 1411 "parser.y"
    {
          init((yyval), ID_declaration_list);
          assert(stack((yyvsp[(1) - (2)])).operands().size()==1);
          stack((yyval)).move_to_operands(stack((yyvsp[(1) - (2)])).op0());
        }
    break;

  case 265:
/* Line 1787 of yacc.c  */
#line 1422 "parser.y"
    {
          merge_types((yyvsp[(2) - (3)]), (yyvsp[(1) - (3)])); // type attribute

          init((yyval), ID_declaration_list);

          exprt declaration;
          PARSER.new_declaration(stack((yyvsp[(2) - (3)])), stack((yyvsp[(3) - (3)])), declaration, false, false);

          stack((yyval)).move_to_operands(declaration);
        }
    break;

  case 266:
/* Line 1787 of yacc.c  */
#line 1433 "parser.y"
    {
          exprt declaration;
          PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(3) - (3)])), declaration, false, false);

          (yyval)=(yyvsp[(1) - (3)]);
          stack((yyval)).move_to_operands(declaration);
        }
    break;

  case 267:
/* Line 1787 of yacc.c  */
#line 1446 "parser.y"
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

  case 268:
/* Line 1787 of yacc.c  */
#line 1460 "parser.y"
    {
          exprt declaration;

          irept declaration_type=stack((yyvsp[(1) - (3)])).find(ID_type);
          PARSER.new_declaration(declaration_type, stack((yyvsp[(3) - (3)])), declaration, false, false);

          (yyval)=(yyvsp[(1) - (3)]);
          stack((yyval)).move_to_operands(declaration);
        }
    break;

  case 269:
/* Line 1787 of yacc.c  */
#line 1473 "parser.y"
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

  case 270:
/* Line 1787 of yacc.c  */
#line 1486 "parser.y"
    {
          init((yyval), ID_abstract);
        }
    break;

  case 271:
/* Line 1787 of yacc.c  */
#line 1490 "parser.y"
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

  case 272:
/* Line 1787 of yacc.c  */
#line 1504 "parser.y"
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

  case 273:
/* Line 1787 of yacc.c  */
#line 1516 "parser.y"
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

  case 274:
/* Line 1787 of yacc.c  */
#line 1530 "parser.y"
    {
          init((yyval), ID_nil);
        }
    break;

  case 276:
/* Line 1787 of yacc.c  */
#line 1538 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_c_bitfield);
          stack((yyval)).set(ID_size, stack((yyvsp[(2) - (2)])));
          stack((yyval)).add(ID_subtype).id(ID_abstract);
        }
    break;

  case 277:
/* Line 1787 of yacc.c  */
#line 1549 "parser.y"
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

  case 278:
/* Line 1787 of yacc.c  */
#line 1561 "parser.y"
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

  case 279:
/* Line 1787 of yacc.c  */
#line 1576 "parser.y"
    {
            // we want the tag to be visible before the members
            init((yyval));
            PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(3) - (3)])), stack((yyval)), true);
            PARSER.copy_item(to_ansi_c_declaration(stack((yyval))));
          }
    break;

  case 280:
/* Line 1787 of yacc.c  */
#line 1584 "parser.y"
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

  case 281:
/* Line 1787 of yacc.c  */
#line 1599 "parser.y"
    {
          do_tag((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
          (yyval)=(yyvsp[(3) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 282:
/* Line 1787 of yacc.c  */
#line 1607 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          set((yyval), ID_c_enum);
        }
    break;

  case 283:
/* Line 1787 of yacc.c  */
#line 1615 "parser.y"
    {
          init((yyval));
          mto((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 284:
/* Line 1787 of yacc.c  */
#line 1620 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 285:
/* Line 1787 of yacc.c  */
#line 1625 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
        }
    break;

  case 286:
/* Line 1787 of yacc.c  */
#line 1632 "parser.y"
    {
          // enum constants in C have signed int type,
          // not the enum type!
          init((yyval));
          irept type(ID_int);
          PARSER.new_declaration(type, stack((yyvsp[(1) - (2)])), stack((yyval)));
          stack((yyval)).set(ID_is_macro, true);
          stack((yyval)).add(ID_value).swap(stack((yyvsp[(2) - (2)])));
        }
    break;

  case 287:
/* Line 1787 of yacc.c  */
#line 1645 "parser.y"
    {
          init((yyval));
          stack((yyval)).make_nil();
        }
    break;

  case 288:
/* Line 1787 of yacc.c  */
#line 1650 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
        }
    break;

  case 290:
/* Line 1787 of yacc.c  */
#line 1658 "parser.y"
    {
          typet tmp(ID_ellipsis);
          (yyval)=(yyvsp[(1) - (3)]);
          ((typet &)stack((yyval))).move_to_subtypes(tmp);
        }
    break;

  case 291:
/* Line 1787 of yacc.c  */
#line 1667 "parser.y"
    {
          init((yyval), ID_arguments);
          mts((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 292:
/* Line 1787 of yacc.c  */
#line 1672 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mts((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 293:
/* Line 1787 of yacc.c  */
#line 1679 "parser.y"
    {
          init((yyval));
          irept type(ID_KnR);
          PARSER.new_declaration(type, stack((yyvsp[(1) - (1)])), stack((yyval)));
        }
    break;

  case 294:
/* Line 1787 of yacc.c  */
#line 1688 "parser.y"
    {
          init((yyval), ID_arguments);
          mts((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 295:
/* Line 1787 of yacc.c  */
#line 1693 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mts((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 296:
/* Line 1787 of yacc.c  */
#line 1701 "parser.y"
    {
          init((yyval));
          exprt declarator=exprt(ID_abstract);
          PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
        }
    break;

  case 297:
/* Line 1787 of yacc.c  */
#line 1707 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 298:
/* Line 1787 of yacc.c  */
#line 1712 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(2) - (3)])), stack((yyval)));
        }
    break;

  case 299:
/* Line 1787 of yacc.c  */
#line 1717 "parser.y"
    {
          // the second tree is really the argument -- not part
          // of the type!
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 300:
/* Line 1787 of yacc.c  */
#line 1724 "parser.y"
    {
          init((yyval));
          exprt declarator=exprt(ID_abstract);
          PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
        }
    break;

  case 301:
/* Line 1787 of yacc.c  */
#line 1730 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 302:
/* Line 1787 of yacc.c  */
#line 1735 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(2) - (3)])), stack((yyval)));
        }
    break;

  case 303:
/* Line 1787 of yacc.c  */
#line 1740 "parser.y"
    {
          init((yyval));
          exprt declarator=exprt(ID_abstract);
          PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
        }
    break;

  case 304:
/* Line 1787 of yacc.c  */
#line 1746 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 305:
/* Line 1787 of yacc.c  */
#line 1751 "parser.y"
    {
          init((yyval));
          stack((yyvsp[(1) - (3)])), stack((yyvsp[(2) - (3)])), stack((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(2) - (3)])), stack((yyval)));
        }
    break;

  case 306:
/* Line 1787 of yacc.c  */
#line 1757 "parser.y"
    {
          // the second tree is really the argument -- not part
          // of the type!
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 307:
/* Line 1787 of yacc.c  */
#line 1764 "parser.y"
    {
          init((yyval));
          exprt declarator=exprt(ID_abstract);
          PARSER.new_declaration(stack((yyvsp[(1) - (1)])), declarator, stack((yyval)));
        }
    break;

  case 308:
/* Line 1787 of yacc.c  */
#line 1770 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
        }
    break;

  case 309:
/* Line 1787 of yacc.c  */
#line 1775 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (3)])), stack((yyvsp[(2) - (3)])), stack((yyval)));
        }
    break;

  case 313:
/* Line 1787 of yacc.c  */
#line 1789 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          make_subtype((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 315:
/* Line 1787 of yacc.c  */
#line 1795 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          make_subtype((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 316:
/* Line 1787 of yacc.c  */
#line 1803 "parser.y"
    {
          newstack((yyval));
          stack((yyval)).make_nil();
        }
    break;

  case 317:
/* Line 1787 of yacc.c  */
#line 1808 "parser.y"
    { (yyval) = (yyvsp[(2) - (2)]); }
    break;

  case 319:
/* Line 1787 of yacc.c  */
#line 1819 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          set((yyval), ID_initializer_list);
          stack((yyval)).operands().swap(stack((yyvsp[(2) - (3)])).operands());
        }
    break;

  case 320:
/* Line 1787 of yacc.c  */
#line 1825 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_initializer_list);
          stack((yyval)).operands().swap(stack((yyvsp[(2) - (4)])).operands());
        }
    break;

  case 321:
/* Line 1787 of yacc.c  */
#line 1834 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          exprt tmp;
          tmp.swap(stack((yyval)));
          stack((yyval)).clear();
          stack((yyval)).move_to_operands(tmp);
        }
    break;

  case 322:
/* Line 1787 of yacc.c  */
#line 1842 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 324:
/* Line 1787 of yacc.c  */
#line 1851 "parser.y"
    {
          init((yyval));
          set((yyval), ID_initializer_list);
          stack((yyval)).operands().clear();
        }
    break;

  case 326:
/* Line 1787 of yacc.c  */
#line 1861 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (3)]);
          stack((yyval)).id(ID_designated_initializer);
          stack((yyval)).add(ID_designator).swap(stack((yyvsp[(1) - (3)])));
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 327:
/* Line 1787 of yacc.c  */
#line 1869 "parser.y"
    {
          init((yyval), ID_designated_initializer);
          stack((yyval)).add(ID_designator).swap(stack((yyvsp[(1) - (2)])));
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 328:
/* Line 1787 of yacc.c  */
#line 1875 "parser.y"
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

  case 329:
/* Line 1787 of yacc.c  */
#line 1890 "parser.y"
    {
          init((yyval));
          stack((yyvsp[(1) - (2)])).id(ID_member);
          stack((yyvsp[(1) - (2)])).set(ID_component_name, stack((yyvsp[(2) - (2)])).get(ID_C_base_name));
          mto((yyval), (yyvsp[(1) - (2)]));
        }
    break;

  case 330:
/* Line 1787 of yacc.c  */
#line 1897 "parser.y"
    {
          init((yyval));
          stack((yyvsp[(1) - (3)])).id(ID_index);
          mto((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
          mto((yyval), (yyvsp[(1) - (3)]));
        }
    break;

  case 331:
/* Line 1787 of yacc.c  */
#line 1904 "parser.y"
    {
          // TODO
          init((yyval));
          stack((yyvsp[(1) - (5)])).id(ID_index);
          mto((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]));
          mto((yyval), (yyvsp[(1) - (5)]));
        }
    break;

  case 332:
/* Line 1787 of yacc.c  */
#line 1912 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          stack((yyvsp[(2) - (4)])).id(ID_index);
          mto((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)]));
          mto((yyval), (yyvsp[(2) - (4)]));
        }
    break;

  case 333:
/* Line 1787 of yacc.c  */
#line 1919 "parser.y"
    {
          // TODO
          (yyval)=(yyvsp[(1) - (6)]);
          stack((yyvsp[(2) - (6)])).id(ID_index);
          mto((yyvsp[(2) - (6)]), (yyvsp[(3) - (6)]));
          mto((yyval), (yyvsp[(2) - (6)]));
        }
    break;

  case 334:
/* Line 1787 of yacc.c  */
#line 1927 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          stack((yyvsp[(2) - (3)])).id(ID_member);
          stack((yyvsp[(2) - (3)])).set(ID_component_name, stack((yyvsp[(3) - (3)])).get(ID_C_base_name));
          mto((yyval), (yyvsp[(2) - (3)]));
        }
    break;

  case 346:
/* Line 1787 of yacc.c  */
#line 1953 "parser.y"
    {
          init((yyval));
          statement((yyval), ID_decl_block);
          stack((yyval)).operands().swap(stack((yyvsp[(1) - (1)])).operands());
        }
    break;

  case 347:
/* Line 1787 of yacc.c  */
#line 1962 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (3)]);
          statement((yyval), ID_label);
          irep_idt identifier=PARSER.lookup_label(stack((yyvsp[(1) - (3)])).get(ID_C_base_name));
          stack((yyval)).set(ID_label, identifier);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 348:
/* Line 1787 of yacc.c  */
#line 1970 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_label);
          mto((yyval), (yyvsp[(4) - (4)]));
          static_cast<exprt &>(stack((yyval)).add(ID_case)).
                move_to_operands(stack((yyvsp[(2) - (4)])));
        }
    break;

  case 349:
/* Line 1787 of yacc.c  */
#line 1978 "parser.y"
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

  case 350:
/* Line 1787 of yacc.c  */
#line 1988 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          statement((yyval), ID_label);
          mto((yyval), (yyvsp[(3) - (3)]));
          stack((yyval)).set(ID_default, true);
        }
    break;

  case 351:
/* Line 1787 of yacc.c  */
#line 2002 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (3)]);
          statement((yyval), ID_block);
          stack((yyval)).set(ID_C_end_location, stack((yyvsp[(3) - (3)])).location());
          PARSER.pop_scope();
        }
    break;

  case 352:
/* Line 1787 of yacc.c  */
#line 2009 "parser.y"
    {
          (yyval)=(yyvsp[(3) - (4)]);
          stack((yyval)).location()=stack((yyvsp[(2) - (4)])).location();
          stack((yyval)).set(ID_C_end_location, stack((yyvsp[(4) - (4)])).location());
          PARSER.pop_scope();
        }
    break;

  case 353:
/* Line 1787 of yacc.c  */
#line 2016 "parser.y"
    {
          init((yyval));
          stack((yyval)).location()=stack((yyvsp[(2) - (4)])).location();
          stack((yyval)).set(ID_statement, ID_asm);
          mto((yyval), (yyvsp[(3) - (4)]));
          PARSER.pop_scope();
        }
    break;

  case 354:
/* Line 1787 of yacc.c  */
#line 2027 "parser.y"
    {
          unsigned prefix=++PARSER.current_scope().compound_counter;
          PARSER.new_scope(i2string(prefix)+"::");
        }
    break;

  case 355:
/* Line 1787 of yacc.c  */
#line 2035 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          to_code(stack((yyval))).make_block();
        }
    break;

  case 356:
/* Line 1787 of yacc.c  */
#line 2040 "parser.y"
    {
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 357:
/* Line 1787 of yacc.c  */
#line 2047 "parser.y"
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

  case 358:
/* Line 1787 of yacc.c  */
#line 2062 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          statement((yyval), ID_ifthenelse);
          stack((yyval)).operands().reserve(3);
          mto((yyval), (yyvsp[(3) - (5)]));
          mto((yyval), (yyvsp[(5) - (5)]));
          stack((yyval)).copy_to_operands(nil_exprt());
        }
    break;

  case 359:
/* Line 1787 of yacc.c  */
#line 2071 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (7)]);
          statement((yyval), ID_ifthenelse);
          stack((yyval)).operands().reserve(3);
          mto((yyval), (yyvsp[(3) - (7)]));
          mto((yyval), (yyvsp[(5) - (7)]));
          mto((yyval), (yyvsp[(7) - (7)]));
        }
    break;

  case 360:
/* Line 1787 of yacc.c  */
#line 2080 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          statement((yyval), ID_switch);
          stack((yyval)).operands().reserve(2);
          mto((yyval), (yyvsp[(3) - (5)]));
          mto((yyval), (yyvsp[(5) - (5)]));
        }
    break;

  case 363:
/* Line 1787 of yacc.c  */
#line 2096 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (5)]);
          statement((yyval), ID_while);
          stack((yyval)).operands().reserve(2);
          mto((yyval), (yyvsp[(3) - (5)]));
          mto((yyval), (yyvsp[(5) - (5)]));
        }
    break;

  case 364:
/* Line 1787 of yacc.c  */
#line 2104 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (7)]);
          statement((yyval), ID_dowhile);
          stack((yyval)).operands().reserve(2);
          mto((yyval), (yyvsp[(5) - (7)]));
          mto((yyval), (yyvsp[(2) - (7)]));
        }
    break;

  case 365:
/* Line 1787 of yacc.c  */
#line 2112 "parser.y"
    {
            // In C99 and upwards, for(;;) has a scope
            if(PARSER.for_has_scope)
            {
              unsigned prefix=++PARSER.current_scope().compound_counter;
              PARSER.new_scope(i2string(prefix)+"::");
            }
          }
    break;

  case 366:
/* Line 1787 of yacc.c  */
#line 2124 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (9)]);
          statement((yyval), ID_for);
          stack((yyval)).operands().reserve(4);
          mto((yyval), (yyvsp[(4) - (9)]));
          mto((yyval), (yyvsp[(5) - (9)]));
          mto((yyval), (yyvsp[(7) - (9)]));
          mto((yyval), (yyvsp[(9) - (9)]));

          if(PARSER.for_has_scope)
            PARSER.pop_scope(); // remove the C99 for-scope
        }
    break;

  case 367:
/* Line 1787 of yacc.c  */
#line 2140 "parser.y"
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

  case 368:
/* Line 1787 of yacc.c  */
#line 2157 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); statement((yyval), ID_continue); }
    break;

  case 369:
/* Line 1787 of yacc.c  */
#line 2159 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); statement((yyval), ID_break); }
    break;

  case 370:
/* Line 1787 of yacc.c  */
#line 2161 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]); statement((yyval), ID_return); }
    break;

  case 371:
/* Line 1787 of yacc.c  */
#line 2163 "parser.y"
    { (yyval)=(yyvsp[(1) - (3)]); statement((yyval), ID_return); mto((yyval), (yyvsp[(2) - (3)])); }
    break;

  case 372:
/* Line 1787 of yacc.c  */
#line 2168 "parser.y"
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

  case 373:
/* Line 1787 of yacc.c  */
#line 2189 "parser.y"
    {
          init((yyval));
          mto((yyval), (yyvsp[(1) - (1)]));
        }
    break;

  case 374:
/* Line 1787 of yacc.c  */
#line 2194 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          mto((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 376:
/* Line 1787 of yacc.c  */
#line 2205 "parser.y"
    { (yyval)=(yyvsp[(1) - (6)]);
          statement((yyval), ID_asm);
          stack((yyval)).set(ID_flavor, ID_gcc);
          stack((yyval)).operands().swap(stack((yyvsp[(4) - (6)])).operands());
        }
    break;

  case 377:
/* Line 1787 of yacc.c  */
#line 2211 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_asm);
          stack((yyval)).set(ID_flavor, ID_gcc);
          mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 378:
/* Line 1787 of yacc.c  */
#line 2221 "parser.y"
    { (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_asm);
          stack((yyval)).set(ID_flavor, ID_msc);
          mto((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 379:
/* Line 1787 of yacc.c  */
#line 2227 "parser.y"
    { (yyval)=(yyvsp[(1) - (2)]);
          statement((yyval), ID_asm);
          stack((yyval)).set(ID_flavor, ID_msc);
          mto((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 380:
/* Line 1787 of yacc.c  */
#line 2237 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (7)]);
          statement((yyval), ID_msc_try_except);
          mto((yyval), (yyvsp[(2) - (7)]));
          mto((yyval), (yyvsp[(5) - (7)]));
          mto((yyval), (yyvsp[(7) - (7)]));
        }
    break;

  case 381:
/* Line 1787 of yacc.c  */
#line 2246 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          statement((yyval), ID_msc_try_finally);
          mto((yyval), (yyvsp[(2) - (4)]));
          mto((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 382:
/* Line 1787 of yacc.c  */
#line 2253 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          statement((yyval), ID_msc_leave);
        }
    break;

  case 388:
/* Line 1787 of yacc.c  */
#line 2277 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (1)]));
          }
    break;

  case 389:
/* Line 1787 of yacc.c  */
#line 2282 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (2)]));
          }
    break;

  case 390:
/* Line 1787 of yacc.c  */
#line 2287 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (3)]));
          }
    break;

  case 391:
/* Line 1787 of yacc.c  */
#line 2292 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (4)]));
          }
    break;

  case 392:
/* Line 1787 of yacc.c  */
#line 2297 "parser.y"
    {
            init((yyval));
            mto((yyval), (yyvsp[(1) - (5)]));
          }
    break;

  case 424:
/* Line 1787 of yacc.c  */
#line 2390 "parser.y"
    {
          // the function symbol needs to be visible before any declarations
          // in the body (the following compound_statement)
          to_ansi_c_declaration(stack((yyvsp[(1) - (1)]))).value().make_nil();
          PARSER.copy_item(to_ansi_c_declaration(stack((yyvsp[(1) - (1)]))));
        }
    break;

  case 425:
/* Line 1787 of yacc.c  */
#line 2397 "parser.y"
    {
          // we now present the body as initializer
          to_ansi_c_declaration(stack((yyvsp[(1) - (3)]))).value().swap(stack((yyvsp[(3) - (3)])));
          PARSER.copy_item(to_ansi_c_declaration(stack((yyvsp[(1) - (3)]))));
          
          // kill scope
          PARSER.pop_scope();
          PARSER.function=irep_idt();
        }
    break;

  case 427:
/* Line 1787 of yacc.c  */
#line 2414 "parser.y"
    {
          init((yyval));
        }
    break;

  case 429:
/* Line 1787 of yacc.c  */
#line 2422 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
        }
    break;

  case 430:
/* Line 1787 of yacc.c  */
#line 2426 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          Forall_irep(it, stack((yyvsp[(2) - (2)])).get_sub())
            stack((yyval)).move_to_sub(*it);
        }
    break;

  case 432:
/* Line 1787 of yacc.c  */
#line 2440 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 433:
/* Line 1787 of yacc.c  */
#line 2446 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 434:
/* Line 1787 of yacc.c  */
#line 2452 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 435:
/* Line 1787 of yacc.c  */
#line 2458 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 436:
/* Line 1787 of yacc.c  */
#line 2468 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 437:
/* Line 1787 of yacc.c  */
#line 2474 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 438:
/* Line 1787 of yacc.c  */
#line 2480 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          merge_types((yyval), (yyvsp[(2) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)])); // type attribute
        }
    break;

  case 441:
/* Line 1787 of yacc.c  */
#line 2495 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (2)])); // save for later
          exprt tmp;
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), tmp);
          stack((yyval)).move_to_sub(tmp);
        }
    break;

  case 442:
/* Line 1787 of yacc.c  */
#line 2503 "parser.y"
    {
          init((yyval));
          stack((yyval)).add(ID_type)=stack((yyvsp[(1) - (2)])); // save for later
          exprt tmp;
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), tmp);
          stack((yyval)).move_to_sub(tmp);
        }
    break;

  case 443:
/* Line 1787 of yacc.c  */
#line 2511 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          // need to get type from $1
          const irept &t=stack((yyvsp[(1) - (3)])).type();
          exprt tmp;
          PARSER.new_declaration(t, stack((yyvsp[(3) - (3)])), tmp);
          stack((yyval)).move_to_sub(tmp);
        }
    break;

  case 444:
/* Line 1787 of yacc.c  */
#line 2523 "parser.y"
    {
          init((yyval));
          irept return_type(ID_int);
          PARSER.new_declaration(return_type, stack((yyvsp[(1) - (1)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 445:
/* Line 1787 of yacc.c  */
#line 2530 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 446:
/* Line 1787 of yacc.c  */
#line 2536 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 447:
/* Line 1787 of yacc.c  */
#line 2542 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 448:
/* Line 1787 of yacc.c  */
#line 2548 "parser.y"
    {
          init((yyval));
          PARSER.new_declaration(stack((yyvsp[(1) - (2)])), stack((yyvsp[(2) - (2)])), stack((yyval)));
          create_function_scope(stack((yyval)));
        }
    break;

  case 454:
/* Line 1787 of yacc.c  */
#line 2568 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          make_subtype((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 457:
/* Line 1787 of yacc.c  */
#line 2578 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 458:
/* Line 1787 of yacc.c  */
#line 2583 "parser.y"
    {
          merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
          (yyval)=(yyvsp[(2) - (3)]);
          do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
        }
    break;

  case 459:
/* Line 1787 of yacc.c  */
#line 2592 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 460:
/* Line 1787 of yacc.c  */
#line 2594 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          /* or an array ($4)! */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 462:
/* Line 1787 of yacc.c  */
#line 2605 "parser.y"
    {
          (yyval)=(yyvsp[(3) - (4)]);
          do_pointer((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]));
        }
    break;

  case 463:
/* Line 1787 of yacc.c  */
#line 2610 "parser.y"
    {
          // not sure where the type qualifiers belong
          merge_types((yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]));
          (yyval)=(yyvsp[(2) - (5)]);
          do_pointer((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]));
        }
    break;

  case 464:
/* Line 1787 of yacc.c  */
#line 2617 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 465:
/* Line 1787 of yacc.c  */
#line 2622 "parser.y"
    {
          merge_types((yyvsp[(2) - (3)]), (yyvsp[(3) - (3)]));
          (yyval)=(yyvsp[(2) - (3)]);
          do_pointer((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]));
        }
    break;

  case 466:
/* Line 1787 of yacc.c  */
#line 2631 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 467:
/* Line 1787 of yacc.c  */
#line 2633 "parser.y"
    {        /* note: this is a function ($3) with a typedef name ($2) */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(3) - (4)]));
        }
    break;

  case 468:
/* Line 1787 of yacc.c  */
#line 2638 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          /* or an array ($4)! */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 470:
/* Line 1787 of yacc.c  */
#line 2649 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 474:
/* Line 1787 of yacc.c  */
#line 2660 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 475:
/* Line 1787 of yacc.c  */
#line 2665 "parser.y"
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

  case 476:
/* Line 1787 of yacc.c  */
#line 2678 "parser.y"
    {
          /* note: this is a function or array ($2) with name ($1) */
          (yyval)=(yyvsp[(1) - (2)]);
          make_subtype((yyval), (yyvsp[(2) - (2)]));
        }
    break;

  case 477:
/* Line 1787 of yacc.c  */
#line 2684 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 478:
/* Line 1787 of yacc.c  */
#line 2686 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          /* or an array ($4)! */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 480:
/* Line 1787 of yacc.c  */
#line 2697 "parser.y"
    { (yyval)=(yyvsp[(2) - (3)]); }
    break;

  case 487:
/* Line 1787 of yacc.c  */
#line 2714 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_code);
          stack((yyval)).add(ID_arguments);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 488:
/* Line 1787 of yacc.c  */
#line 2721 "parser.y"
    {
            unsigned prefix=++PARSER.current_scope().compound_counter;
            PARSER.new_scope(i2string(prefix)+"::");
          }
    break;

  case 489:
/* Line 1787 of yacc.c  */
#line 2727 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_code);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          stack((yyval)).add(ID_arguments).get_sub().
            swap(stack((yyvsp[(3) - (4)])).add(ID_subtypes).get_sub());
          PARSER.pop_scope();
        }
    break;

  case 490:
/* Line 1787 of yacc.c  */
#line 2737 "parser.y"
    {
            unsigned prefix=++PARSER.current_scope().compound_counter;
            PARSER.new_scope(i2string(prefix)+"::");
          }
    break;

  case 491:
/* Line 1787 of yacc.c  */
#line 2744 "parser.y"
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

  case 493:
/* Line 1787 of yacc.c  */
#line 2759 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_code);
          stack((yyval)).add(ID_arguments);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 494:
/* Line 1787 of yacc.c  */
#line 2766 "parser.y"
    {
            unsigned prefix=++PARSER.current_scope().compound_counter;
            PARSER.new_scope(i2string(prefix)+"::");
          }
    break;

  case 495:
/* Line 1787 of yacc.c  */
#line 2772 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_code);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          stack((yyval)).add(ID_arguments).get_sub().
            swap(stack((yyvsp[(3) - (4)])).add(ID_subtypes).get_sub());
          PARSER.pop_scope();
        }
    break;

  case 496:
/* Line 1787 of yacc.c  */
#line 2784 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (2)]);
          set((yyval), ID_array);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          stack((yyval)).add(ID_size).make_nil();
        }
    break;

  case 497:
/* Line 1787 of yacc.c  */
#line 2791 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          set((yyval), ID_array);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          stack((yyval)).add(ID_size).make_nil();
        }
    break;

  case 498:
/* Line 1787 of yacc.c  */
#line 2798 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (3)]);
          set((yyval), ID_array);
          stack((yyval)).add(ID_size).swap(stack((yyvsp[(2) - (3)])));
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 499:
/* Line 1787 of yacc.c  */
#line 2805 "parser.y"
    {
          // The type qualifier belongs to the array, not the
          // contents of the array, nor the size.
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyval), ID_array);
          stack((yyval)).add(ID_size).swap(stack((yyvsp[(3) - (4)])));
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 500:
/* Line 1787 of yacc.c  */
#line 2814 "parser.y"
    {
          // we need to push this down
          (yyval)=(yyvsp[(1) - (4)]);
          set((yyvsp[(2) - (4)]), ID_array);
          stack((yyvsp[(2) - (4)])).add(ID_size).swap(stack((yyvsp[(3) - (4)])));
          stack((yyvsp[(2) - (4)])).add(ID_subtype)=irept(ID_abstract);
          make_subtype((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]));
        }
    break;

  case 501:
/* Line 1787 of yacc.c  */
#line 2826 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          set((yyval), ID_pointer);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 502:
/* Line 1787 of yacc.c  */
#line 2832 "parser.y"
    {
          // The type_qualifier_list belongs to the pointer,
          // not to the (missing) abstract declarator.
          (yyval)=(yyvsp[(2) - (2)]);
          set((yyvsp[(1) - (2)]), ID_pointer);
          stack((yyvsp[(1) - (2)])).add(ID_subtype)=irept(ID_abstract);
          merge_types((yyval), (yyvsp[(1) - (2)]));
        }
    break;

  case 503:
/* Line 1787 of yacc.c  */
#line 2841 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 504:
/* Line 1787 of yacc.c  */
#line 2846 "parser.y"
    {
          // The type_qualifier_list belongs to the pointer,
          // not to the abstract declarator.
          (yyval)=(yyvsp[(2) - (3)]);
          do_pointer((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 505:
/* Line 1787 of yacc.c  */
#line 2854 "parser.y"
    {
          // This is an Apple extension to C/C++/Objective C.
          // http://en.wikipedia.org/wiki/Blocks_(C_language_extension)
          (yyval)=(yyvsp[(1) - (1)]);
          set((yyval), ID_block_pointer);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 506:
/* Line 1787 of yacc.c  */
#line 2865 "parser.y"
    {
          (yyval)=(yyvsp[(1) - (1)]);
          set((yyval), ID_pointer);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 507:
/* Line 1787 of yacc.c  */
#line 2871 "parser.y"
    {
          // The type_qualifier_list belongs to the pointer,
          // not to the (missing) abstract declarator.
          (yyval)=(yyvsp[(2) - (2)]);
          set((yyval), ID_pointer);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
          merge_types((yyval), (yyvsp[(1) - (2)]));
        }
    break;

  case 508:
/* Line 1787 of yacc.c  */
#line 2880 "parser.y"
    {
          (yyval)=(yyvsp[(2) - (2)]);
          do_pointer((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]));
        }
    break;

  case 509:
/* Line 1787 of yacc.c  */
#line 2885 "parser.y"
    {
          // The type_qualifier_list belongs to the pointer,
          // not to the (missing) abstract declarator.
          (yyval)=(yyvsp[(2) - (3)]);
          do_pointer((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
          merge_types((yyval), (yyvsp[(3) - (3)]));
        }
    break;

  case 510:
/* Line 1787 of yacc.c  */
#line 2893 "parser.y"
    {
          // This is an Apple extension to C/C++/Objective C.
          // http://en.wikipedia.org/wiki/Blocks_(C_language_extension)
          (yyval)=(yyvsp[(1) - (1)]);
          set((yyval), ID_block_pointer);
          stack((yyval)).add(ID_subtype)=irept(ID_abstract);
        }
    break;

  case 511:
/* Line 1787 of yacc.c  */
#line 2904 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 512:
/* Line 1787 of yacc.c  */
#line 2906 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 513:
/* Line 1787 of yacc.c  */
#line 2908 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 514:
/* Line 1787 of yacc.c  */
#line 2910 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;

  case 515:
/* Line 1787 of yacc.c  */
#line 2919 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 516:
/* Line 1787 of yacc.c  */
#line 2921 "parser.y"
    { (yyval) = (yyvsp[(2) - (3)]); }
    break;

  case 518:
/* Line 1787 of yacc.c  */
#line 2924 "parser.y"
    {
          /* note: this is a pointer ($2) to a function ($4) */
          (yyval)=(yyvsp[(2) - (4)]);
          make_subtype((yyval), (yyvsp[(4) - (4)]));
        }
    break;


/* Line 1787 of yacc.c  */
#line 6962 "y.tab.cpp"
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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


/* Line 2050 of yacc.c  */
#line 2931 "parser.y"

