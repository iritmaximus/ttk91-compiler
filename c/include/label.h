#ifndef LABEL_H
#define LABEL_H

#include "expr.h"

typedef enum {
    LABEL_CONST,
    LABEL_TAG
} label_t;

struct label {
    label_t kind;
    const char *name;
    int value;
};

struct label * label_create(label_t kind, char *name, int value);

#endif
