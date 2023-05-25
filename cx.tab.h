/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
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

#ifndef YY_YY_CX_TAB_H_INCLUDED
# define YY_YY_CX_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     BOOL = 259,
     IF = 260,
     ELSE = 261,
     WHILE = 262,
     WRITE = 263,
     READ = 264,
     CALL = 265,
     PROC = 266,
     PLUS = 267,
     MINUS = 268,
     TIMES = 269,
     SLASH = 270,
     LES = 271,
     LEQ = 272,
     GTR = 273,
     GEQ = 274,
     EQL = 275,
     NEQ = 276,
     BECOMES = 277,
     COMMA = 278,
     OR = 279,
     AND = 280,
     NOT = 281,
     SEMICOLON = 282,
     LPAREN = 283,
     RPAREN = 284,
     LBRACE = 285,
     RBRACE = 286,
     SYM_TRUE = 287,
     SYM_FALSE = 288,
     REPEAT = 289,
     UNTIL = 290,
     XOR = 291,
     CASE = 292,
     SWITCH = 293,
     DEFAULT = 294,
     BREAK = 295,
     COLON = 296,
     CONST = 297,
     EXIT = 298,
     CONTINUE = 299,
     FOR = 300,
     DO = 301,
     MOD = 302,
     ODD = 303,
     SELFADD = 304,
     SELFMINUS = 305,
     IDENT = 306,
     NUMBER = 307,
     CHARACTER = 308,
     IFX = 309
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2058 of yacc.c  */
#line 104 "src/cx.y"

    char *ident;
    int number;


/* Line 2058 of yacc.c  */
#line 117 "cx.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

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

#endif /* !YY_YY_CX_TAB_H_INCLUDED  */
