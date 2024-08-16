#include <stdlib.h>
#include <stdio.h>
#include "error.h"
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
        return VARIABLE_NULL;

    switch (e->kind)
    {
        case INSTRUCTION:
        {
            if (e->label)
            {
                int err = label_print(e->label);
                if (err)
                    return err;
                printf(" ");
            }

            int err = oper_print(e->oper);
            if (err)
                return err;
            printf(" ");
            err = ttk_register_print(e->first_arg);
            if (err)
                return err;
            printf(",");
            printf(" ");
            err = value_print(e->second_arg);
            if (err)
                return err;
            printf("\n");
            return 0;
        }

        case INSTRUCTION_ONE_ARG:
        {
            if (e->label)
            {
                int err = label_print(e->label);
                if (err)
                    return err;
                printf(" ");
            }

            int err = oper_print(e->oper);
            if (err)
                return err;
            printf(" ");
            err = value_print(e->second_arg);
            if (err)
                return err;
            printf("\n");
            return 0;
        }

        case LABEL_DEF:
        {
            int err = label_print(e->label);
            if (err)
                return err;
            printf(" ");
            err = oper_print(e->oper);
            if (err)
                return err;
            printf(" ");
            err = value_print(e->second_arg);
            if (err)
                return err;
            printf("\n");
            return 0;
        }

        case COMMENT:
            if (PRINT_COMMENTS)
                return 0;

            int err = comment_print(e->comment);
            if (err)
                return err;
            printf("\n");
            return 0;

        default:
            return SWITCH_NOT_MATCHED;
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

int expr_free(struct expr *e)
{
    switch (e->kind)
    {
        case INSTRUCTION:
            if (e->label) label_free(e->label);
            if (e->oper) oper_free(e->oper);
            if (e->first_arg) ttk_register_free(e->first_arg);
            if (e->second_arg) value_free(e->second_arg);
            break;

        case INSTRUCTION_ONE_ARG:
            if (e->label) label_free(e->label);
            if (e->oper) oper_free(e->oper);
            if (e->second_arg) value_free(e->second_arg);
            break;

        case LABEL_DEF:
            if (e->label) label_free(e->label);
            if (e->oper) oper_free(e->oper);
            if (e->second_arg) value_free(e->second_arg);
            break;

        case COMMENT:
            if (e->comment) comment_free(e->comment);
            break;

        default:
            printf("ERROR: Expr kind not matched while freeing\n");
            return SWITCH_NOT_MATCHED;
    }

    return 0;
}
