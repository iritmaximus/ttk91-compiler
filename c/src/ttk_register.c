#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ttk_register.h"

struct ttk_register * ttk_register_create(ttk_register_t kind, char* name, int value)
{
    struct ttk_register * r = malloc(sizeof(*r));

    r->kind = kind;
    r->id = parse_register_num(name, kind);
    r->value = value;

    return r;
}


struct ttk_register * ttk_register_create_register(char* name)
{
    return ttk_register_create(TTK_REGISTER, name, 0);
}

struct ttk_register * ttk_register_create_stack_register(char* name)
{
    return ttk_register_create(STACK_TTK_REGISTER, name, 0);
}

int parse_register_num(char* name, ttk_register_t kind)
{
    if (!name) {
        return -1;
    }

    int value;

    switch (kind)
    {
        case TTK_REGISTER:
            char num = name[1]; // registers have the format RX, 'R' + X 0-7
            value = num - '0';
            break;
        case STACK_TTK_REGISTER:
            if (strcasecmp("sp", name) == 0)
                value = 6;

            if (strcasecmp("fp", name) == 0)
                value = 7;
            break;

        default:
            free(name);
            return -1;
    }

    free(name);
    return value;
}

int ttk_register_print(struct ttk_register *ttk_reg)
{
    if (!ttk_reg || !ttk_reg->id)
    {
        printf("ERROR: No ttk_register exists.\n");
        return 1;
    }
    switch (ttk_reg->id)
    {
        case 6:
            printf("SP");
            return 0;
        case 7:
            printf("FP");
            return 0;
    }

    printf("R%d", ttk_reg->id);
    return 0;
}

void ttk_register_free(struct ttk_register *ttk_reg)
{
    free(ttk_reg);
}
