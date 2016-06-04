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

extern YYSTYPE yyansi_clval;


