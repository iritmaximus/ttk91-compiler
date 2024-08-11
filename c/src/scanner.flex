%{
#include "token.h"
%}

%option yylineno

%%
(" "|\t|\n)                 /* skip whitespace */

(@|=)                       { return TOKEN_ADDR_M; }
\(                          { return TOKEN_PAREN_L; }
\)                          { return TOKEN_PAREN_R; }
,                           { return TOKEN_COMMA; }
;.*$                        { return TOKEN_COMMENT; }


(LOAD|STORE|IN|OUT)         { return TOKEN_OPER_DATA; } /* TODO, currently only in uppercase */
(ADD|SUB|MUL|DIV|MOD)       { return TOKEN_OPER_AR; }
(AND|OR|XOR|NOT|SHL|SHR|SHRA|COMP) { return TOKEN_OPER_LOGIC; }
(JUMP|JNEG|JZER|JPOS|JNNEG|JNZER|JNPOS|JLES|JEQU|JGRE|JNLES|JNEQU|JNGRE) { return TOKEN_OPER_BRANCH; }
(PUSH|POP|PUSHR|POPR)       { return TOKEN_OPER_STACK; }
(CALL|EXIT|SVC|NOP)         { return TOKEN_OPER_SYS; }
(HALT|TIME|DATE|READ|WRITE) { return TOKEN_SYS_NUM; }
(EQU|DC|DS|DEF)             { return TOKEN_COMP_OPER; }

(SP|FP|PC)                  { return TOKEN_STACK_REGISTER; }

R[0-8]                      { return TOKEN_REGISTER; }
[0-9]+                      { return TOKEN_NUMBER; }
[a-öA-Ö]([a-öA-Ö0-9_])*     { return TOKEN_LABEL; }
-                           { return TOKEN_SIGN; }

.                           { return TOKEN_ERROR; }


%%

int yywrap()                { return 1; }
