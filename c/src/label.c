#include <stdlib.h>
#include "label.h"


struct label * label_create(label_t kind, char *name, int value)
{
    struct label *l = malloc(sizeof(*l));
    l->kind = kind;
    l->name = name;
    l->value = value;

    return l;
}
