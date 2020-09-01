/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     END = 0,
     _CTLOPERATOR_ = 258,
     IDENTIFIER = 259,
     NUMBER = 260,
     _RELEASE_ = 261,
     _NEXTSTATE_ = 262,
     _INITIAL_ = 263,
     _DEADLOCK_ = 264,
     _FORMULA_ = 265,
     _AND_ = 266,
     _NOT_ = 267,
     _OR_ = 268,
     _XOR_ = 269,
     _iff_ = 270,
     _ALLPATH_ = 271,
     _ALWAYS_ = 272,
     _EVENTUALLY_ = 273,
     _EXPATH_ = 274,
     _UNTIL_ = 275,
     _REACHABLE_ = 276,
     _INVARIANT_ = 277,
     _IMPOSSIBLE_ = 278,
     _notequal_ = 279,
     _implies_ = 280,
     _equals_ = 281,
     _plus_ = 282,
     _minus_ = 283,
     _times_ = 284,
     _leftparenthesis_ = 285,
     _rightparenthesis_ = 286,
     _greaterthan_ = 287,
     _lessthan_ = 288,
     _greaterorequal_ = 289,
     _lessorequal_ = 290,
     _semicolon_ = 291,
     _TRUE_ = 292,
     _FALSE_ = 293,
     _FIREABLE_ = 294,
     _omega_ = 295
   };
#endif
/* Tokens.  */
#define END 0
#define _CTLOPERATOR_ 258
#define IDENTIFIER 259
#define NUMBER 260
#define _RELEASE_ 261
#define _NEXTSTATE_ 262
#define _INITIAL_ 263
#define _DEADLOCK_ 264
#define _FORMULA_ 265
#define _AND_ 266
#define _NOT_ 267
#define _OR_ 268
#define _XOR_ 269
#define _iff_ 270
#define _ALLPATH_ 271
#define _ALWAYS_ 272
#define _EVENTUALLY_ 273
#define _EXPATH_ 274
#define _UNTIL_ 275
#define _REACHABLE_ 276
#define _INVARIANT_ 277
#define _IMPOSSIBLE_ 278
#define _notequal_ 279
#define _implies_ 280
#define _equals_ 281
#define _plus_ 282
#define _minus_ 283
#define _times_ 284
#define _leftparenthesis_ 285
#define _rightparenthesis_ 286
#define _greaterthan_ 287
#define _lessthan_ 288
#define _greaterorequal_ 289
#define _lessorequal_ 290
#define _semicolon_ 291
#define _TRUE_ 292
#define _FALSE_ 293
#define _FIREABLE_ 294
#define _omega_ 295




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE ptformula_lval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE ptformula_lloc;
