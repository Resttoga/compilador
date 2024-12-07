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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    NUMBER = 258,                  /* NUMBER  */
    ID = 259,                      /* ID  */
    TEXTO = 260,                   /* TEXTO  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    ELIF = 263,                    /* ELIF  */
    LPAR = 264,                    /* LPAR  */
    RPAR = 265,                    /* RPAR  */
    LBRAC = 266,                   /* LBRAC  */
    RBRAC = 267,                   /* RBRAC  */
    IGUAL = 268,                   /* IGUAL  */
    SUMA = 269,                    /* SUMA  */
    RESTA = 270,                   /* RESTA  */
    MULTIPLICACION = 271,          /* MULTIPLICACION  */
    DIVISION = 272,                /* DIVISION  */
    GREATER = 273,                 /* GREATER  */
    LESSER = 274,                  /* LESSER  */
    GTEQ = 275,                    /* GTEQ  */
    LSEQ = 276,                    /* LSEQ  */
    EQ = 277,                      /* EQ  */
    FOR = 278,                     /* FOR  */
    SEMICOLON = 279,               /* SEMICOLON  */
    WHILE = 280,                   /* WHILE  */
    PLUS = 281,                    /* PLUS  */
    CALL = 282,                    /* CALL  */
    RETURN = 283,                  /* RETURN  */
    FUNCTION = 284,                /* FUNCTION  */
    COMA = 285,                    /* COMA  */
    IMPRIMIR = 286                 /* IMPRIMIR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 170 "parser.y"

    int val; 
    char *str;
    struct ParamList {
    int param_count;
    char param_names[10][100];
} param_list;


struct FunctionParams {
    int param_count;
    int params[10];
} function_params;


struct FuncBody {
    int (*func)(int *params); 
} func_body; 

#line 115 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
