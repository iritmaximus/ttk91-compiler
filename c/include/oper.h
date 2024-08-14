#ifndef OPER_H
#define OPER_H

#include "ttk_register.h"

typedef enum {
    OPER_DATA,
    OPER_AR,
    OPER_LOGIC,
    OPER_BRANCH,
    OPER_STACK,
    OPER_SYS
} oper_t;

struct oper {
    oper_t kind;
    char* oper_name;
};

struct oper * oper_create(oper_t kind, char* oper_name);

#endif
