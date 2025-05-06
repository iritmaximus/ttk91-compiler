#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "error.h"
#include "oper.h"


struct oper * oper_create(oper_t kind, char* oper_name)
{
    struct oper *o = malloc(sizeof(*o));

    o->kind = kind;
    o->oper_name = oper_name; // TODO rename to just name just like everyone else xd

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
        return VARIABLE_NULL;
    }

    printf("%s", o->oper_name);
    return 0;
}

int oper_print_intel_asm(struct oper *o)
{
    if (!o)
    {
        printf("ERROR: Null oper given.\n");
        return VARIABLE_NULL;
    }

    switch (o->kind)
    {
        case OPER_DATA:
        {
            if (strcasecmp("LOAD", o->oper_name) == 0)
                printf("mov");
            else if (strcasecmp("STORE", o->oper_name) == 0)
                printf("mov");
            else if (strcasecmp("IN", o->oper_name) == 0)
                printf("\"IN\"");
            else if (strcasecmp("OUT", o->oper_name) == 0)
                printf("\"OUT\"");
            break;
        }

        case OPER_AR:
        {
            if (strcasecmp("ADD", o->oper_name) == 0)
                printf("add");
            else if (strcasecmp("SUB", o->oper_name) == 0)
                printf("sub");
            else if (strcasecmp("MUL", o->oper_name) == 0)
                printf("mul");
            else if (strcasecmp("DIV", o->oper_name) == 0)
                printf("div");
            else
                printf("\"%s\"", o->oper_name);
            break;
        }

        case OPER_COMPILER:
        {
            if (strcasecmp("DEF", o->oper_name) == 0)
                printf("\"%s\"", o->oper_name);
            else
                printf("dw");
            break;
        }

        case OPER_LOGIC:
        {
            printf("\"%s\"", o->oper_name);
            break;
        }

        case OPER_BRANCH:
        {
            printf("\"%s\"", o->oper_name);
            break;
        }

        case OPER_STACK:
        {
            printf("\"%s\"", o->oper_name);
            break;
        }

        case OPER_SYS:
        {
            printf("\"%s\"", o->oper_name);
            break;
        }

        default:
        {
            return SWITCH_NOT_MATCHED;
        }
    }


    return 0;
}

void oper_free(struct oper *o)
{
    if (o->oper_name) free(o->oper_name);
    free(o);
}
