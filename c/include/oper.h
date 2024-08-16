#ifndef OPER_H
#define OPER_H

#include "ttk_register.h"

typedef enum {
    OPER_DATA,
    OPER_AR,
    OPER_LOGIC,
    OPER_BRANCH,
    OPER_STACK,
    OPER_SYS,
    OPER_COMPILER
} oper_t;

struct oper {
    oper_t kind;
    char* oper_name;
};

struct oper * oper_create(oper_t kind, char* oper_name);
struct oper * oper_create_data(char* oper_name);
struct oper * oper_create_arithmetic(char* oper_name);
struct oper * oper_create_logic(char* oper_name);
struct oper * oper_create_branch(char* oper_name);
struct oper * oper_create_stack(char* oper_name);
struct oper * oper_create_sys(char* oper_name);
struct oper * oper_create_compiler(char* oper_name);

#endif
