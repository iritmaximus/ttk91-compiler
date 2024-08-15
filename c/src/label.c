#include <stdlib.h>
#include "label.h"


struct label * label_create(label_t kind, char *name, int value)
{
    if (!name)
        return NULL;

    struct label *l = malloc(sizeof(*l));
    l->kind = kind;
    l->name = name;
    l->value = value;

    return l;
}
