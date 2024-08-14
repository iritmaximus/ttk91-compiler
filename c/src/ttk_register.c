#include <stdlib.h>
#include "ttk_register.h"

struct ttk_register * ttk_register_create(char* name, int value)
{
    struct ttk_register * r = malloc(sizeof(*r));

    r->id = parse_register_num(name);
    r->value = value;

    return r;
}

int parse_register_num(char* name)
{
    if (!name) {
        return -1;
    }

    char num = name[1]; // registers have the format RX, 'R' + X 0-7
    return num - '0';
}
