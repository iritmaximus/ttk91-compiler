%{
#include "token.h"
#define YYSTYPE char *
%}

%option yylineno

%%
(" "|\t|\n)                 /* skip whitespace */

(@|=)                       { yylval.character = yytext; return TOKEN_ADDR_M; }
\(                          { return TOKEN_PAREN_L; }
\)                          { return TOKEN_PAREN_R; }
,                           { return TOKEN_COMMA; }
;.*$                        { return TOKEN_COMMENT; }


(LOAD|STORE|IN|OUT)         { yylval.name = yytext; return TOKEN_OPER_DATA; } /* TODO, currently only in uppercase */
(ADD|SUB|MUL|DIV|MOD)       { yylval.name = yytext; return TOKEN_OPER_AR; }
(AND|OR|XOR|NOT|SHL|SHR|SHRA|COMP) { yylval.name = yytext; return TOKEN_OPER_LOGIC; }
(JUMP|JNEG|JZER|JPOS|JNNEG|JNZER|JNPOS|JLES|JEQU|JGRE|JNLES|JNEQU|JNGRE) { yylval.name = yytext; return TOKEN_OPER_BRANCH; }
(PUSH|POP|PUSHR|POPR)       { yylval.name = yytext; return TOKEN_OPER_STACK; }
(CALL|EXIT|SVC|NOP)         { yylval.name = yytext; return TOKEN_OPER_SYS; }
(HALT|TIME|DATE|READ|WRITE) { yylval.name = yytext; return TOKEN_SYS_NUM; }
(EQU|DC|DS|DEF)             { yylval.name = yytext; return TOKEN_COMP_OPER; }

(SP|FP|PC)                  { yylval.name = yytext; return TOKEN_STACK_REGISTER; /* TODO possible unnecessary token PC */ }

R[0-8]                      { yylval.name = yytext; return TOKEN_REGISTER; }
[0-9]+                      { yylval.num = atoi(yytext); return TOKEN_NUMBER; }
[a-öA-Ö]([a-öA-Ö0-9_])*     { yylval.name = yytext; return TOKEN_LABEL; }
-                           { return TOKEN_SIGN; }

.                           { yylval.name = yytext; return TOKEN_ERROR; }


%%

int yywrap()                { return 1; }
