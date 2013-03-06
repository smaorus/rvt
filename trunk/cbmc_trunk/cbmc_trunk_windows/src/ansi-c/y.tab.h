/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

extern YYSTYPE yyansi_clval;


