#ifndef LABEL_H
#define LABEL_H

#include "expr.h"

typedef enum {
    LABEL_CONST,
    LABEL_TAG
} label_t;

struct label {
    label_t kind;
    char *name;
    int value;
};

struct label * label_create(label_t kind, char* name, int value);
int label_print(struct label *l);

struct label * label_create_const(char* name);
struct label * label_create_const_sys(char* name);
struct label * label_create_tag(char* name);

#endif
