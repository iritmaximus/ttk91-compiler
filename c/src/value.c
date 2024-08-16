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

struct value * value_create_direct_value(struct pure_value *p_v)
{
    return value_create(DIRECT, NONE, p_v, NULL);
}

struct value * value_create_direct_register(struct ttk_register *ttk_reg)
{
    struct pure_value *p_v = pure_value_create_value(0);
    return value_create(DIRECT, NONE, p_v, ttk_reg);
}

struct value * value_create_direct_indexed(struct pure_value *p_v, struct ttk_register *ttk_reg)
{
    return value_create(DIRECT, INDEXED, p_v, ttk_reg);
}

struct value * value_create_address_mode_indexed(char addr_mode, struct pure_value *p_v, struct ttk_register *ttk_reg)
{
    return value_create(parse_addr_mode(addr_mode), INDEXED, p_v, ttk_reg);
}

struct value * value_create_address_mode(char addr_mode, struct pure_value *p_v)
{
    return value_create(parse_addr_mode(addr_mode), NONE, p_v, NULL);
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

struct pure_value * pure_value_create_ttk_register(struct ttk_register *ttk_reg)    { return pure_value_create(REGISTER, ttk_reg, 0, NULL); }
struct pure_value * pure_value_create_value(int value)                              { return pure_value_create(NUMBER, NULL, value, NULL); }
struct pure_value * pure_value_create_label(struct label *l)                        { return pure_value_create(LABEL, NULL, 0, l); }


addr_mode_t parse_addr_mode(char addr_mode)
{
    switch (addr_mode)
    {
        case '=':
            return IMMEDIATE;
        case '@':
            return INDIRECT;
    }

    return DIRECT;
}
    {
        return INDIRECT;
    } 
    else {
        return DIRECT;
    }
}
