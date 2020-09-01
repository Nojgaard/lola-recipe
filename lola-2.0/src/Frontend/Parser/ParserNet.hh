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
     IDENTIFIER = 258,
     NUMBER = 259,
     KEY_CONSUME = 260,
     KEY_FAIR = 261,
     KEY_PLACE = 262,
     KEY_MARKING = 263,
     KEY_PRODUCE = 264,
     KEY_SAFE = 265,
     KEY_STRONG = 266,
     KEY_TRANSITION = 267,
     KEY_WEAK = 268,
     COLON = 269,
     COMMA = 270,
     SEMICOLON = 271
   };
#endif
/* Tokens.  */
#define END 0
#define IDENTIFIER 258
#define NUMBER 259
#define KEY_CONSUME 260
#define KEY_FAIR 261
#define KEY_PLACE 262
#define KEY_MARKING 263
#define KEY_PRODUCE 264
#define KEY_SAFE 265
#define KEY_STRONG 266
#define KEY_TRANSITION 267
#define KEY_WEAK 268
#define COLON 269
#define COMMA 270
#define SEMICOLON 271




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 47 "Frontend/Parser/ParserNet.yy"
{
    char* attributeString;
    fairnessAssumption_t attributeFairness;
    ArcList* attributeArcList;
}
/* Line 1529 of yacc.c.  */
#line 89 "Frontend/Parser/ParserNet.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE ptnetlola_lval;

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

extern YYLTYPE ptnetlola_lloc;
