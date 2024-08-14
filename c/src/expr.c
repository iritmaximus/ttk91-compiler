#include <stdlib.h>
#include "expr.h"

struct expr * expr_create(expr_t kind, struct label *l, struct oper *o, struct ttk_register *f_arg, struct value *s_arg, struct comment *c, struct expr *n)
{
    struct expr * e = malloc(sizeof(*e));

    e->kind = kind;
    e->label = l;
    e->oper = o;
    e->first_arg = f_arg;
    e->second_arg = s_arg;
    e->comment = c;
    e->next = n;

    return e;
}
