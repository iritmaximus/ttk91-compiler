#include <stdlib.h>
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

    switch (kind)
    {
        case TTK_REGISTER:
            char num = name[1]; // registers have the format RX, 'R' + X 0-7
            return num - '0';
        case STACK_TTK_REGISTER:
            if (strcasecmp("sp", name) == 0)
                return 6;
            if (strcasecmp("fp", name) == 0)
                return 7;

    }

    return -1; // error, shouldn't end up here.

}
