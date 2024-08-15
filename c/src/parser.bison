/* TODO support tags to jump to different sections */
%{
#include <stdio.h>
#include "comment.h"
#include "expr.h"
#include "label.h"
#include "oper.h"
#include "value.h"

extern int yylineno;
%}



%define parse.error verbose

%parse-param { struct expr *parse_result }

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


%union {
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
}

%type <expr> program expr_list expr
%type <oper> oper
%type <ttk_register> ttk_register
%type <value> value
%type <pure_value> pure_value
%type <label> label
%type <num> num_value

%type <name> TOKEN_REGISTER TOKEN_STACK_REGISTER
%type <name> TOKEN_OPER_DATA TOKEN_OPER_AR TOKEN_OPER_LOGIC TOKEN_OPER_BRANCH TOKEN_OPER_STACK TOKEN_OPER_SYS
%type <name> TOKEN_LABEL TOKEN_SYS_NUM
%type <character> TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_ADDR_M TOKEN_SIGN
%type <num>  TOKEN_NUMBER
%type <name> TOKEN_COMMENT

%%

program     : expr_list                         { expr_copy(parse_result, $1); }
            ;

expr_list   : expr_list expr                    { $$ = $2; $2->next = $1; }
            |                                   { $$ = NULL; }
            ;

expr        : oper ttk_register TOKEN_COMMA value               { $$ = expr_create(INSTRUCTION, NULL, $1, $2, $4, NULL, NULL); }
            | oper value                                        { $$ = expr_create(INSTRUCTION_ONE_ARG, NULL, $1, NULL, $2, NULL, NULL); }
            | TOKEN_LABEL TOKEN_COMP_OPER num_value             { $$ = expr_create(LABEL_DEF, label_create(LABEL_CONST, $1, 0), NULL, NULL, NULL, NULL, NULL); /* TODO implement this properly */ }
            | TOKEN_LABEL oper ttk_register TOKEN_COMMA value   { $$ = expr_create(INSTRUCTION, label_create(LABEL_TAG,$1, 0), $2, $3, $5, NULL, NULL); /* TODO FIXME labels have always value 0 */ }
            | TOKEN_LABEL oper value                            { $$ = expr_create(INSTRUCTION, label_create(LABEL_TAG,$1, 0), $2, NULL, $3, NULL, NULL); }
            | TOKEN_COMMENT                                     { $$ = expr_create(COMMENT, NULL, NULL, NULL, NULL, comment_create($1), NULL); }
            ;

oper        : TOKEN_OPER_DATA                   { $$ = oper_create(OPER_DATA, $1); }
            | TOKEN_OPER_AR                     { $$ = oper_create(OPER_AR, $1); }
            | TOKEN_OPER_LOGIC                  { $$ = oper_create(OPER_LOGIC, $1); }
            | TOKEN_OPER_BRANCH                 { $$ = oper_create(OPER_BRANCH, $1); }
            | TOKEN_OPER_STACK                  { $$ = oper_create(OPER_STACK, $1); }
            | TOKEN_OPER_SYS                    { $$ = oper_create(OPER_SYS, $1); }
            ;

ttk_register: TOKEN_REGISTER                    { $$ = ttk_register_create(TTK_REGISTER, $1, 0); }
            | TOKEN_STACK_REGISTER              { $$ = ttk_register_create(STACK_TTK_REGISTER, $1, 0); }
            ;


value       : pure_value TOKEN_PAREN_L ttk_register TOKEN_PAREN_R               { $$ = value_create(DIRECT, INDEXED, $1, $3); }
            | pure_value                                                        { $$ = value_create(DIRECT, NONE, $1, NULL); }
            | TOKEN_ADDR_M pure_value TOKEN_PAREN_L ttk_register TOKEN_PAREN_R  { $$ = value_create(parse_addr_mode($1), INDEXED, $2, $4); }
            | TOKEN_ADDR_M pure_value                                           { $$ = value_create(parse_addr_mode($1), NONE, $2, NULL); }
            | TOKEN_PAREN_L ttk_register TOKEN_PAREN_R                          { $$ = value_create(DIRECT, NONE, NULL, $2); }
            ;

pure_value  : ttk_register                      { $$ = pure_value_create(REGISTER, $1, 0, NULL); }
            | num_value                         { $$ = pure_value_create(NUMBER, NULL, $1, NULL); }
            | label                             { $$ = pure_value_create(LABEL, NULL, 0, $1); }
            ;

label       : TOKEN_LABEL                       { $$ = label_create(LABEL_CONST, $1, 0); }
            | TOKEN_SYS_NUM                     { $$ = label_create(LABEL_CONST, $1, 0); /* TODO FIXME */ }
            ;


num_value   : TOKEN_SIGN TOKEN_NUMBER           { $$ = -$2; }
            | TOKEN_NUMBER                      { $$ = $1; }
            ;

%%

int yyerror ( const char *s )
{
    printf("ERROR: Parser error: %s at line %d\n", s, yylineno);
    return 1;
}
