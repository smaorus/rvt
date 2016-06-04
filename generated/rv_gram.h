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




