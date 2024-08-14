#include <stdlib.h>
#include "oper.h"


struct oper * oper_create(oper_t kind, char* oper_name)
{
    struct oper *o = malloc(sizeof(*o));

    o->kind = kind;
    o->oper_name = oper_name;

    return o;
}
