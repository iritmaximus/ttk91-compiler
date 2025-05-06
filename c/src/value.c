#include <stdlib.h>
#include <stdio.h>
#include "error.h"
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

struct value * value_create_address_mode_indexed(char* addr_mode, struct pure_value *p_v, struct ttk_register *ttk_reg)
{
    return value_create(parse_addr_mode(addr_mode), INDEXED, p_v, ttk_reg);
}

struct value * value_create_address_mode(char* addr_mode, struct pure_value *p_v)
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


addr_mode_t parse_addr_mode(char* addr_mode)
{
    if (!addr_mode)
        return -1;
    switch (addr_mode[0])
    {
        case '=':
            return IMMEDIATE;
        case '@':
            return INDIRECT;
    }

    return DIRECT;
}

int pure_value_print_intel_asm(struct pure_value *p_v)
{
    return pure_value_print(p_v);
}

int value_print_intel_asm(struct value *v)
{
    if (!v)
    {
        printf("ERROR: Value not defined.\n");
        return VARIABLE_NULL;
    }

    if (v->indexing_mode == NONE)
    {
        switch (v->addr_mode)
        {
            case IMMEDIATE:
            {
                int err = pure_value_print_intel_asm(v->value);
                if (err!=0)
                    return err;
                break;
            } 

            case DIRECT:
            case INDIRECT:
            {
                if (v->value && v->value->kind != NUMBER)
                {
                    int err = pure_value_print_intel_asm(v->value);
                    if (err!=0)
                        return err;
                }
                else {
                    printf("[");
                    int err = pure_value_print_intel_asm(v->value);
                    if (err!=0)
                        return err;
                    printf("]");
                }

                break;
            }
        }
    }
    else if (v->indexing_mode == INDEXED)
    {
        switch (v->addr_mode)
        {
            case IMMEDIATE:
            {
                printf("[");
                int err = ttk_register_print_intel_asm(v->index_register);
                if (err!=0)
                    return err;

                printf(" + ");

                err = pure_value_print_intel_asm(v->value);
                if (err!=0)
                    return err;
                printf("]");
            }
        }
    }
    else
        return SWITCH_NOT_MATCHED;

    return 0;
}

int pure_value_print(struct pure_value *p_v)
{
    if (!p_v)
    {
        printf("\nERROR: Pure_value does not exist\n");
        return VARIABLE_NULL;
    }

    switch (p_v->kind)
    {
        case REGISTER:
            ttk_register_print(p_v->ttk_register);
            break;
        case NUMBER:
            printf("%d", p_v->number);
            break;
        case LABEL:
            label_print(p_v->label);
            break;
        default:
            return SWITCH_NOT_MATCHED;
    }

    return 0;
}

int value_print(struct value *v)
{

    if (!v)
    {
        printf("ERROR: Value not defined.\n");
        return VARIABLE_NULL;
    }

    // add = or @ to the beginnig of value
    switch (v->addr_mode)
    {
        case IMMEDIATE:
            printf("=");
            break;
        case INDIRECT:
            printf("@");
            break;
        case DIRECT:
            break;
    }

    switch (v->indexing_mode)
    {
        case NONE:
        {
            int err = pure_value_print(v->value);
            if (err)
                return err;
            break;
        }
        case INDEXED:
        {
            int err = pure_value_print(v->value);
            if (err)
                return err;
            printf("(");
            err = ttk_register_print(v->index_register); // is already defined
            if (err)
                return err;
            printf(")");
            break;

        }
        case INDEXED_ONLY_IREG:
        {
            printf("(");
            int err = ttk_register_print(v->index_register);
            if (err)
                return err;
            printf(")");
            break;
        }
        default:
            return SWITCH_NOT_MATCHED;
    }

    return 0;
}

void pure_value_free(struct pure_value *p_v)
{
    switch (p_v->kind)
    {
        case REGISTER:
            if (p_v->ttk_register) ttk_register_free(p_v->ttk_register);
            break;
        case NUMBER:
            break;
        case LABEL:
            if (p_v->label) label_free(p_v->label);
            break;
    }
    free(p_v);
}

void value_free(struct value *v)
{
    switch (v->indexing_mode)
    {
        case NONE:
            if (v->value) pure_value_free(v->value);
            break;
        case INDEXED:
            if (v->value) pure_value_free(v->value);
            if (v->index_register) ttk_register_free(v->index_register);
            break;
        default:
            printf("ERROR: Indexing mode not matched while freeing value\n");
            break;
    }
    free(v);
}
