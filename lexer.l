%{
#include "parser.tab.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

%}

%option noyywrap 

DIGIT [0-9]
ID    [a-zA-Z0-9]+
STRING '[a-zA-Z0-9_]+'

IF be|Be
ELSE sickin|Sickin
%%

"=\.="                      { return IGUAL;}
"\+_\+"                     { return SUMA; }
"-_-"                       { return RESTA; }
"\*-\*"                     { return MULTIPLICACION; }
"\/-\\"                     { return DIVISION; }

">.>"   { return GREATER; }
"<.<"   { return LESSER; }
"=>.>"   { return GTEQ; }
"<.<="   { return LSEQ; }
"=_="   { return EQ; }


{IF} { return IF; }
{ELSE} { return ELSE; }
"be sickin" {return ELIF; }
"(" {return LPAR;}
")" {return RPAR;}
"{" {return LBRAC;}
"}" {return RBRAC;}

";" {return SEMICOLON;}
"for" {return FOR;}
"while" {return WHILE;}
"+" {return PLUS;}

"def" {return FUNCTION;}
"return" {return RETURN;}
"call" {return CALL;}
"," {return COMA;}

"imprimir"     { return IMPRIMIR; }

{DIGIT}+                    { yylval.val = atoi(yytext); return NUMBER; }
{ID}                        { yylval.str = strdup(yytext); return ID; }
{STRING}                        { yylval.str = strdup(yytext + 1); yylval.str[strlen(yylval.str) - 1] = '\0'; return TEXTO; }
[ \t\r\n]+                     ;

.                           { printf("Error léxico: %s\n", yytext); exit(1); }
%%
