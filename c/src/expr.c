#include <stdlib.h>
#include <stdio.h>
#include "expr.h"

#define PRINT_COMMENTS 1

struct expr * expr_create(expr_t kind, struct label *l, struct oper *o, struct ttk_register *f_arg, struct value *s_arg, struct comment *c, struct expr *n)
{
    struct expr *e = malloc(sizeof(*e));

    e->kind = kind;
    e->label = l;
    e->oper = o;
    e->first_arg = f_arg;
    e->second_arg = s_arg;
    e->comment = c;
    e->next = n;

    return e;
}

struct expr *expr_create_instruction(struct oper *o, struct ttk_register *ttk_reg, struct value *v)
{
    return expr_create(INSTRUCTION, NULL, o, ttk_reg, v, NULL, NULL);
}

struct expr *expr_create_instruction_one_arg(struct oper *o, struct value *v)
{
    return expr_create(INSTRUCTION_ONE_ARG, NULL, o, NULL, v, NULL, NULL);
}

struct expr *expr_create_labeled_instruction(struct label *l, struct oper *o, struct ttk_register *ttk_reg, struct value *v)
{
    return expr_create(INSTRUCTION, l, o, ttk_reg, v, NULL, NULL);
}

struct expr *expr_create_labeled_instruction_one_arg(struct label *l, struct oper *o, struct value *v)
{
    return expr_create(INSTRUCTION_ONE_ARG, l, o, NULL, v, NULL, NULL);
}

struct expr *expr_create_compiler_instruction(struct label *l, struct oper *o, struct value *v)
{
    return expr_create(LABEL_DEF, l, o, NULL, v, NULL, NULL);
}

struct expr *expr_create_compiler_instruction_raw_label_oper_value(char* label, char *oper, int value)
{
    struct label *l = label_create_const(label);
    struct oper *o = oper_create_compiler(oper);

    struct pure_value *p_v = pure_value_create_value(value);
    struct value *v = value_create_direct_value(p_v);

    return expr_create_compiler_instruction(l, o, v);
}

struct expr *expr_create_comment(struct comment *c)
{
    return expr_create(COMMENT, NULL, NULL, NULL, NULL, c, NULL);
}

int expr_print(struct expr *e)
{
    if (!e)
        return 1;

    switch (e->kind)
    {
        case INSTRUCTION:
            if (e->label)
            {
                if (label_print(e->label)!=0)
                    return 1;;
                printf(" ");
            }

            if (oper_print(e->oper)!=0)
                return 1;
            printf(" ");
            if (ttk_register_print(e->first_arg)!=0)
                return 1;
            printf(",");
            printf(" ");
            if (value_print(e->second_arg)!=0)
                return 1;
            printf("\n");
            return 0;

        case INSTRUCTION_ONE_ARG:
            if (e->label)
            {
                if (label_print(e->label)!=0)
                    return 1;
                printf(" ");
            }

            if (oper_print(e->oper)!=0)
                return 1;
            printf(" ");
            if (value_print(e->second_arg)!=0)
                return 1;
            printf("\n");
            return 0;

        case LABEL_DEF:
            if (label_print(e->label)!=0)
                return 1;
            printf(" ");
            if (oper_print(e->oper)!=0)
                return 1;
            printf(" ");
            if (value_print(e->second_arg)!=0)
                return 1;
            printf("\n");
            return 0;

        case COMMENT:
            if (PRINT_COMMENTS == 1)
                return 0;

            if (comment_print(e->comment)!=0)
                return 1;
            printf("\n");
            return 0;

        default:
            return 1;
    }

}

void expr_copy(struct expr *orig, struct expr *copy)
{
    orig->kind = copy->kind;
    orig->label = copy->label;
    orig->oper = copy->oper;
    orig->first_arg = copy->first_arg;
    orig->second_arg = copy->second_arg;
    orig->comment = copy->comment;
    orig->next = copy->next;
}
