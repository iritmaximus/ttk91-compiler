#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "oper.h"


struct oper * oper_create(oper_t kind, char* oper_name)
{
    struct oper *o = malloc(sizeof(*o));

    o->kind = kind;
    o->oper_name = oper_name;

    return o;
}

struct oper * oper_create_data(char* oper_name)         { return oper_create(OPER_DATA, oper_name); }
struct oper * oper_create_arithmetic(char* oper_name)   { return oper_create(OPER_AR, oper_name); }
struct oper * oper_create_logic(char* oper_name)        { return oper_create(OPER_LOGIC, oper_name); }
struct oper * oper_create_branch(char* oper_name)       { return oper_create(OPER_BRANCH, oper_name); }
struct oper * oper_create_stack(char* oper_name)        { return oper_create(OPER_STACK, oper_name); }
struct oper * oper_create_sys(char* oper_name)          { return oper_create(OPER_SYS, oper_name); }
struct oper * oper_create_compiler(char* oper_name)     { return oper_create(OPER_COMPILER, oper_name); }


int oper_print(struct oper *o)
{
    if (!o)
    {
        printf("\nERROR: Null oper given.\n");
        return 1;
    }

    printf("%s", o->oper_name);
    return 0;
}
