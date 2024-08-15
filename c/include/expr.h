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

#endif
