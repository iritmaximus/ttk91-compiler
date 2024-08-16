%{
#include "token.h"
#define YYSTYPE char *
%}

%option yylineno

%%
;.*$                            { yylval.name = yytext; return TOKEN_COMMENT; }
(" "|\t|\n)                     /* skip whitespace */

(@|=)                           { yylval.name = yytext; return TOKEN_ADDR_M; }
\(                              { return TOKEN_PAREN_L; }
\)                              { return TOKEN_PAREN_R; }
,                               { return TOKEN_COMMA; }


(?i:LOAD|STORE|IN|OUT)          { yylval.name = yytext; return TOKEN_OPER_DATA; } /* TODO, currently only in uppercase */
(?i:ADD|SUB|MUL|DIV|MOD)        { yylval.name = yytext; return TOKEN_OPER_AR; }
(?i:AND|OR|XOR|NOT|SHL|SHR|SHRA|COMP) { yylval.name = yytext; return TOKEN_OPER_LOGIC; }
(?i:JUMP|JNEG|JZER|JPOS|JNNEG|JNZER|JNPOS|JLES|JEQU|JGRE|JNLES|JNEQU|JNGRE) { yylval.name = yytext; return TOKEN_OPER_BRANCH; }
(?i:PUSH|POP|PUSHR|POPR)        { yylval.name = yytext; return TOKEN_OPER_STACK; }
(?i:CALL|EXIT|SVC|NOP)          { yylval.name = yytext; return TOKEN_OPER_SYS; }
(?i:HALT|TIME|DATE|READ|WRITE)  { yylval.name = yytext; return TOKEN_SYS_NUM; }
(?i:EQU|DC|DS|DEF)              { yylval.name = yytext; return TOKEN_COMP_OPER; }

(?i:SP|FP|PC)                   { yylval.name = yytext; return TOKEN_STACK_REGISTER; /* TODO possible unnecessary token PC */ }

(?i:R[0-8])                     { yylval.name = yytext; return TOKEN_REGISTER; }
[0-9]+                          { yylval.num = atoi(yytext); return TOKEN_NUMBER; }
([a-öA-Ö][a-öA-Ö0-9_]*)         { yylval.name = yytext; return TOKEN_LABEL; }
-                               { return TOKEN_SIGN; }

.                               { yylval.name = yytext; return TOKEN_ERROR; }


%%

int yywrap()                    { return 1; }
