#include <stdlib.h>
#include <string.h>
#include "oper.h"


struct oper * oper_create(oper_t kind, char* oper_name)
{
    struct oper *o = malloc(sizeof(*o));

    char *name_copy = malloc(sizeof(char) * (strlen(oper_name)+1));
    strcpy(name_copy, oper_name);

    o->kind = kind;
    o->oper_name = name_copy;

    return o;
}
