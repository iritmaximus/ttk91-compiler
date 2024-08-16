#ifndef EXPR_H
#define EXPR_H

#include "oper.h"
#include "ttk_register.h"
#include "value.h"
#include "label.h"
#include "comment.h"

typedef enum {
    INSTRUCTION,
    INSTRUCTION_ONE_ARG,
    LABEL_DEF,
    COMMENT
} expr_t;

struct expr {
    expr_t kind;
    struct label *label;
    struct oper *oper;
    struct ttk_register *first_arg;
    struct value *second_arg;
    struct comment *comment;
    struct expr *next;
};

struct expr * expr_create(expr_t kind, struct label *l, struct oper *o, struct ttk_register *f_arg, struct value *s_arg, struct comment *c, struct expr *n);
int expr_print(struct expr *e);

void expr_copy(struct expr *orig, struct expr *copy);

struct expr *expr_create_instruction(struct oper *o, struct ttk_register *ttk_reg, struct value *v);
struct expr *expr_create_instruction_one_arg(struct oper *o, struct value *v);
struct expr *expr_create_labeled_instruction(struct label *l, struct oper *o, struct ttk_register *ttk_reg, struct value *v);
struct expr *expr_create_labeled_instruction_one_arg(struct label *l, struct oper *o, struct value *v);
struct expr *expr_create_compiler_instruction(struct label *l, struct oper *o, struct value *v);
struct expr *expr_create_compiler_instruction_raw_label_oper_value(char* label, char *o, int value);
struct expr *expr_create_comment(struct comment *c);

#endif
