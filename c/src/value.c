#include <stdlib.h>
#include "value.h"


struct value * value_create(addr_mode_t a_m, index_t i_m, struct pure_value *p_v, struct ttk_register *i_reg)
{
    struct value *v = malloc(sizeof(*v));

    v->addr_mode = a_m;
    v->indexing_mode = i_m;
    v->value = p_v;
    v->index_register = i_reg;

    return v;
}

struct pure_value * pure_value_create(value_t kind, struct ttk_register *ttk_reg, int num, struct label *l)
{
    struct pure_value *v = malloc(sizeof(*v));

    v->kind = kind;
    v->ttk_register = ttk_reg;
    v->number = num;
    v->label = l;

    return v;
}

addr_mode_t parse_addr_mode(char addr_mode)
{
    if (addr_mode == '=') 
    {
        return IMMEDIATE;
    }
    if (addr_mode == '@') 
    {
        return INDIRECT;
    } 
    else {
        return DIRECT;
    }
}
