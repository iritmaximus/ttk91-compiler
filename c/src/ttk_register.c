#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "ttk_register.h"

struct ttk_register * ttk_register_create(ttk_register_t kind, char* name, int value)
{

    int id = parse_register_num(name, kind);

    if (id == -1)
    {
        printf("Register creation failed.\n");
        return NULL;
    }

    struct ttk_register * r = malloc(sizeof(*r));

    r->kind = kind;
    r->id = id;
    r->value = value;

    return r;
}


struct ttk_register * ttk_register_create_register(char* name)
{
    return ttk_register_create(TTK_REGISTER, name, 0);
}

struct ttk_register * ttk_register_create_stack_register(char* name)
{
    return ttk_register_create(STACK_TTK_REGISTER, name, 0);
}

int parse_register_num(char* name, ttk_register_t kind)
{
    if (!name) {
        printf("Name null while parsing register name.\n");
        return -1;
    }

    int value;

    switch (kind)
    {
        case TTK_REGISTER:
            char num = name[1]; // registers have the format RX, 'R' + X 0-7
            value = num - '0';
            break;
        case STACK_TTK_REGISTER:
            if (strcasecmp("sp", name) == 0)
                value = 6;

            if (strcasecmp("fp", name) == 0)
                value = 7;
            break;

        default:
            free(name);
            printf("Register type not matched while parsing register name.\n");
            return -1;
    }

    free(name);
    return value;
}

int ttk_register_print_intel_asm(struct ttk_register *ttk_reg)
{
    // EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI
    if (!ttk_reg || !ttk_reg->id)
    {
        printf("ttk_register missing while trying to print it.\n");
        return VARIABLE_NULL;
    }

    switch (ttk_reg->id)
    {
        case 1:
            printf("eax");
            break;
        case 2:
            printf("ebx");
            break;
        case 3:
            printf("ecx");
            break;
        case 4:
            printf("edx");
            break;
        case 5:
            printf("esp");
            break;
        case 6:
            printf("ebp");
            break;
        case 7:
            printf("esi");
            break;
        case 0:
            printf("edi"); // TODO: this is possibly not correct
            break;
        default:
            printf("ERROR: No matching register\n");
            return SWITCH_NOT_MATCHED;
    }
    return 0;
}

int ttk_register_print(struct ttk_register *ttk_reg)
{
    if (!ttk_reg || !ttk_reg->id)
    {
        printf("ttk_register missing while trying to print it.\n");
        return VARIABLE_NULL;
    }
    switch (ttk_reg->id)
    {
        case 6:
            printf("SP");
            return 0;
        case 7:
            printf("FP");
            return 0;
        default:
            break;
    }

    printf("R%d", ttk_reg->id);
    return 0;
}

void ttk_register_free(struct ttk_register *ttk_reg)
{
    free(ttk_reg);
}
