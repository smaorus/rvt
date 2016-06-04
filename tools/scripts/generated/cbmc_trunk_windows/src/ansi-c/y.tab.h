/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison interface for Yacc-like parsers in C
   
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
