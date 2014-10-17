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
     SUP = 258,
     INF = 259,
     SUP_EG = 260,
     INF_EG = 261,
     EG_EG = 262,
     WHILE = 263,
     ENDWHILE = 264,
     IF = 265,
     ENDIF = 266,
     AFFI = 267,
     TYPE = 268,
     NUM = 269,
     VARIABLE = 270,
     BOOL = 271,
     PLUS = 272,
     MIN = 273,
     MULT = 274,
     DIV = 275,
     POW = 276,
     MOD = 277,
     EGAL = 278,
     OP_PAR = 279,
     CL_PAR = 280,
     COLON = 281,
     EOL = 282,
     OR = 283,
     AND = 284,
     NEQ = 285,
     EQ = 286,
     LET = 287,
     GET = 288,
     LT = 289,
     GT = 290,
     NOT = 291,
     NEG = 292
   };
#endif
/* Tokens.  */
#define SUP 258
#define INF 259
#define SUP_EG 260
#define INF_EG 261
#define EG_EG 262
#define WHILE 263
#define ENDWHILE 264
#define IF 265
#define ENDIF 266
#define AFFI 267
#define TYPE 268
#define NUM 269
#define VARIABLE 270
#define BOOL 271
#define PLUS 272
#define MIN 273
#define MULT 274
#define DIV 275
#define POW 276
#define MOD 277
#define EGAL 278
#define OP_PAR 279
#define CL_PAR 280
#define COLON 281
#define EOL 282
#define OR 283
#define AND 284
#define NEQ 285
#define EQ 286
#define LET 287
#define GET 288
#define LT 289
#define GT 290
#define NOT 291
#define NEG 292




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 21 "language.y"
{
	struct Node *node;
}
/* Line 1529 of yacc.c.  */
#line 127 "language.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

