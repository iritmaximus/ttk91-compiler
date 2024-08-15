/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_INCLUDE_TOKEN_H_INCLUDED
# define YY_YY_INCLUDE_TOKEN_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    TOKEN_REGISTER = 258,          /* TOKEN_REGISTER  */
    TOKEN_STACK_REGISTER = 259,    /* TOKEN_STACK_REGISTER  */
    TOKEN_NUMBER = 260,            /* TOKEN_NUMBER  */
    TOKEN_LABEL = 261,             /* TOKEN_LABEL  */
    TOKEN_ADDR_M = 262,            /* TOKEN_ADDR_M  */
    TOKEN_OPER_DATA = 263,         /* TOKEN_OPER_DATA  */
    TOKEN_OPER_AR = 264,           /* TOKEN_OPER_AR  */
    TOKEN_OPER_LOGIC = 265,        /* TOKEN_OPER_LOGIC  */
    TOKEN_OPER_BRANCH = 266,       /* TOKEN_OPER_BRANCH  */
    TOKEN_OPER_STACK = 267,        /* TOKEN_OPER_STACK  */
    TOKEN_OPER_SYS = 268,          /* TOKEN_OPER_SYS  */
    TOKEN_SYS_NUM = 269,           /* TOKEN_SYS_NUM  */
    TOKEN_COMP_OPER = 270,         /* TOKEN_COMP_OPER  */
    TOKEN_SIGN = 271,              /* TOKEN_SIGN  */
    TOKEN_COMMA = 272,             /* TOKEN_COMMA  */
    TOKEN_PAREN_L = 273,           /* TOKEN_PAREN_L  */
    TOKEN_PAREN_R = 274,           /* TOKEN_PAREN_R  */
    TOKEN_COMMENT = 275,           /* TOKEN_COMMENT  */
    TOKEN_ERROR = 276              /* TOKEN_ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "src/parser.bison"

    struct expr *expr;
    struct oper *oper;
    struct ttk_register *ttk_register;
    struct value *value;
    struct pure_value *pure_value;
    struct label *label;
    struct comment *comment;
    char* name;
    int num;
    char character;

#line 98 "include/token.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (struct expr *parse_result);


#endif /* !YY_YY_INCLUDE_TOKEN_H_INCLUDED  */
