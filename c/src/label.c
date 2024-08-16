#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "label.h"


struct label * label_create(label_t kind, char* name, int value)
{
    if (!name)
        return NULL;

    struct label *l = malloc(sizeof(*l));

    l->kind = kind;
    l->name = name;
    l->value = value;

    return l;
}

struct label * label_create_const(char* name)       { return label_create(LABEL_CONST, name,  0); }
struct label * label_create_const_sys(char* name)   { return label_create(LABEL_CONST, name,  0); } // FIXME value
struct label * label_create_tag(char* name)         { return label_create(LABEL_TAG, name, 0); } // FIXME also this
