/* TODO support tags to jump to different sections */
%{
    #include <stdio.h>
    extern int yylineno;
%}

%define parse.error verbose

%token TOKEN_REGISTER
%token TOKEN_STACK_REGISTER
%token TOKEN_NUMBER
%token TOKEN_LABEL
%token TOKEN_ADDR_M
%token TOKEN_OPER_DATA
%token TOKEN_OPER_AR
%token TOKEN_OPER_LOGIC
%token TOKEN_OPER_BRANCH
%token TOKEN_OPER_STACK
%token TOKEN_OPER_SYS
%token TOKEN_SYS_NUM
%token TOKEN_COMP_OPER
%token TOKEN_SIGN
%token TOKEN_COMMA
%token TOKEN_PAREN_L
%token TOKEN_PAREN_R
%token TOKEN_COMMENT
%token TOKEN_ERROR

%%

program : expr
        | program expr
        ;

expr    : oper register TOKEN_COMMA second_arg
        | oper value
        | TOKEN_LABEL TOKEN_COMP_OPER num_value
        | TOKEN_LABEL expr
        | comment
        ;

oper    : TOKEN_OPER_DATA
        | TOKEN_OPER_AR
        | TOKEN_OPER_LOGIC
        | TOKEN_OPER_BRANCH
        | TOKEN_OPER_STACK
        | TOKEN_OPER_SYS
        ;

register    : TOKEN_REGISTER
            | TOKEN_STACK_REGISTER
            ;


second_arg  : value TOKEN_PAREN_L register TOKEN_PAREN_R
            | value
            | TOKEN_ADDR_M value TOKEN_PAREN_L register TOKEN_PAREN_R
            | TOKEN_ADDR_M value
            | TOKEN_PAREN_L register TOKEN_PAREN_R
            ;

value       : register
            | num_value
            | TOKEN_LABEL
            | TOKEN_SYS_NUM
            ;

num_value   : TOKEN_SIGN TOKEN_NUMBER
            | TOKEN_NUMBER
            ;

comment     : TOKEN_COMMENT
            ;

%%

int yyerror ( const char *s )
{
    printf("ERROR: Parser error: %s at line %d\n", s, yylineno);
    return 1;
}
