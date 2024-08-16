/* TODO support tags to jump to different sections */
%{
#include <stdio.h>
#include "program.h"
#include "comment.h"
#include "expr.h"
#include "label.h"
#include "oper.h"
#include "value.h"

extern int yylineno;

// implicit declaration of function ‘yylex’
int yylex();

// implicit declaration of function ‘yyerror’
int yyerror(struct expr *e, const char*);
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
%type <name> TOKEN_OPER_DATA TOKEN_OPER_AR TOKEN_OPER_LOGIC TOKEN_OPER_BRANCH TOKEN_OPER_STACK TOKEN_OPER_SYS TOKEN_COMP_OPER
%type <name> TOKEN_LABEL TOKEN_SYS_NUM
%type <character> TOKEN_PAREN_L TOKEN_PAREN_R TOKEN_ADDR_M TOKEN_SIGN
%type <num>  TOKEN_NUMBER
%type <name> TOKEN_COMMENT

%%

program     : expr_list                         { expr_copy(parse_result, $1); }
            ;

expr_list   : expr expr_list                    { $$ = $1; $1->next = $2; }
            |                                   { $$ = NULL; }
            ;

expr        : oper ttk_register TOKEN_COMMA value               { $$ = expr_create_instruction($1, $2, $4); }
            | oper value                                        { $$ = expr_create_instruction_one_arg($1, $2); }
            | TOKEN_LABEL TOKEN_COMP_OPER num_value             { $$ = expr_create_compiler_instruction_raw_label_oper_value($1, $2, $3);  /* TODO implement this properly */ }
            | TOKEN_LABEL oper ttk_register TOKEN_COMMA value   { $$ = expr_create_labeled_instruction(label_create_tag($1), $2, $3, $5); /* TODO FIXME labels have always value 0 */ }
            | TOKEN_LABEL oper value                            { $$ = expr_create_labeled_instruction_one_arg(label_create_tag($1), $2, $3); /* TODO FIXME labels have always value 0 */ }
            | TOKEN_COMMENT                                     { $$ = expr_create_comment(comment_create($1)); }
            ;

oper        : TOKEN_OPER_DATA                   { $$ = oper_create_data($1); }
            | TOKEN_OPER_AR                     { $$ = oper_create_arithmetic($1); }
            | TOKEN_OPER_LOGIC                  { $$ = oper_create_logic($1); }
            | TOKEN_OPER_BRANCH                 { $$ = oper_create_branch($1); }
            | TOKEN_OPER_STACK                  { $$ = oper_create_stack($1); }
            | TOKEN_OPER_SYS                    { $$ = oper_create_sys($1); }
            ;

ttk_register: TOKEN_REGISTER                    { $$ = ttk_register_create_register($1); }
            | TOKEN_STACK_REGISTER              { $$ = ttk_register_create_stack_register($1); }
            ;


value       : pure_value TOKEN_PAREN_L ttk_register TOKEN_PAREN_R               { $$ = value_create_direct_indexed($1, $3); }
            | pure_value                                                        { $$ = value_create_direct_value($1); }
            | TOKEN_ADDR_M pure_value TOKEN_PAREN_L ttk_register TOKEN_PAREN_R  { $$ = value_create_address_mode_indexed($1, $2, $4); }
            | TOKEN_ADDR_M pure_value                                           { $$ = value_create_address_mode($1, $2); }
            | TOKEN_PAREN_L ttk_register TOKEN_PAREN_R                          { $$ = value_create_direct_register($2); }
            ;

pure_value  : ttk_register                      { $$ = pure_value_create_ttk_register($1); }
            | num_value                         { $$ = pure_value_create_value($1); }
            | label                             { $$ = pure_value_create_label($1); }
            ;

label       : TOKEN_LABEL                       { $$ = label_create_const($1); }
            | TOKEN_SYS_NUM                     { $$ = label_create_const_sys($1); /* TODO FIXME */ }
            ;


num_value   : TOKEN_SIGN TOKEN_NUMBER           { $$ = -$2; }
            | TOKEN_NUMBER                      { $$ = $1; }
            ;

%%

int yyerror ( struct expr *e, const char *s )
{
    printf("ERROR: Parser error: %s at line %d\n", s, yylineno);
    return 1;
}
