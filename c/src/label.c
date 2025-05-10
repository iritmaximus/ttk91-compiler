#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "error.h"
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

int label_to_string(char* buffer, size_t size, struct label *l) {
    if (size < 2) {
        printf("ERROR: Buffer size too small (label)\n");
        return -1;
    }

    if (!l->name)
    {
        printf("ERROR: Label name doesn't exist.\n");
        snprintf(buffer, size, "???");
        return VARIABLE_NULL;
    }

    snprintf(buffer, size, "%s", l->name);
    return 0;
}

int label_print_intel_asm(struct label *l)
{
    return label_print(l);
}

int label_print(struct label *l)
{
    size_t size = 50;
    char buffer[size];

    label_to_string(buffer, size, l);
    printf("%s", buffer);
    return 0;
}

void label_free(struct label *l)
{
    // if (l->name) free(l->name);
    free(l);
}
