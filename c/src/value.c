#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
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
        default:
            return DIRECT;
    }

    printf("ERROR: How on earth you got here...\n");
    return -1;
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
    const size_t size = 20; // TODO: should this be a global flag?
    char buffer[size];

    pure_value_to_string(buffer, size, p_v); // TODO: match return value

    printf("%s", buffer);
    return 0;
}

int pure_value_to_string(char *buffer, size_t size, struct pure_value *p_v)
{
    if (size < 2) {
        printf("ERROR: Buffer size too small (pure_value_to_string)\n");
        return -1;
    }

    if (!p_v)
    {
        printf("ERROR: Pure value does not exist\n");
        return VARIABLE_NULL;
    }

    // TODO: Implement size checking for each kind
    switch (p_v->kind)
    {
        case NUMBER:
            snprintf(buffer, size, "%d", p_v->number);
            break;
        case REGISTER:
            ttk_register_to_string(buffer, size, p_v->ttk_register);
            break;
        case LABEL:
            label_to_string(buffer, size, p_v->label);
            break;
        default:
            assert(false && "Pure value kind not matched");
    }

    return 0;
}

int value_to_string(char *buffer, size_t size, struct value *v)
{
    // TODO: is this a proper limit?
    if (size < 2) {
        printf("ERROR: Buffer size too small (value_to_string)\n");
        return -1;
    }

    if (!v)
    {
        printf("ERROR: Value not defined.\n");
        return VARIABLE_NULL;
    }


    const size_t prefix_size = 2; // TODO: Should this be a global variable?
    char prefix[prefix_size];
    // add = or @ to the beginnig of value
    switch (v->addr_mode)
    {
        case IMMEDIATE:
            snprintf(prefix, prefix_size, "=");
            break;
        case INDIRECT:
            snprintf(prefix, prefix_size, "@");
            break;
        case DIRECT:
            snprintf(prefix, prefix_size, "");
            break;
        default:
            assert(false && "Value addressing mode not matched");
    }



    const size_t value_size = size*2; // FIXME: Better value for value_size
    char value_buffer[value_size];
    int err;
    switch (v->indexing_mode)
    {
        case NONE:
        {

            err = pure_value_to_string(value_buffer, value_size, v->value);
            if (err)
                return err;
            break;
        }

        case INDEXED:
        {
            err = pure_value_to_string(value_buffer, value_size, v->value);
            if (err)
                return err;

            strncat(value_buffer, "(", 2);

            const size_t ttk_reg_size = 5;
            char ttk_reg_buffer[ttk_reg_size];
            err = ttk_register_to_string(ttk_reg_buffer, ttk_reg_size, v->index_register); // is already defined
            if (err)
                return err;
            strncat(value_buffer, ttk_reg_buffer, value_size);

            strncat(value_buffer, ")", 2);
            break;
        }

        case INDEXED_ONLY_IREG:
        {
            strncat(value_buffer, "(", 2);

            const size_t ttk_reg_size = 5;
            char ttk_reg_buffer[ttk_reg_size];
            err = ttk_register_to_string(ttk_reg_buffer, ttk_reg_size, v->index_register);
            if (err)
                return err;

            strncat(value_buffer, ")", 2);
            break;
        }
        default:
            assert(false && "Value indexing mode not matched");
    }

    snprintf(buffer, size, "%s%s", prefix, value_buffer);
    
    /*
    strncat(buffer, prefix, prefix_size);
    strncat(buffer, value_buffer, size);
    */

    return 0;
}

int value_print(struct value *v)
{
    const size_t size = 20;
    char buffer[size];

    value_to_string(buffer, size, v);
    printf("%s", buffer);

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
