#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
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
    if (!name || strcmp(name, "") == 0) {
        printf("ERROR: Name null or empty while parsing register name.\n");
        return -1;
    }

    int value;

    switch (kind)
    {
        case TTK_REGISTER:
            char num = name[1]; // registers have the format RX, 'R' + X 0-7
            value = num - '0';
            if (0 <= value && value <= 8)
                break;
            else
                assert(false && "Incorrect register name value");

        case STACK_TTK_REGISTER:
            value = -1;

            if (strcasecmp("sp", name) == 0) {
                value = 6;
                break;
            }

            else if (strcasecmp("fp", name) == 0) {
                value = 7;
                break;
            }
            else
                assert(false && "Stack register not 6 or 7");

        default:
            assert(false && "Register kind not matched while parsing register name.");
            break;
    }

    return value;
}

int ttk_register_to_string(char* buffer, size_t size, struct ttk_register *ttk_reg) {
    if (size < 3) {
        printf("ERROR: Buffer size too small (ttk_reg_to_string)\n");
        return -1;
    }

    if (!ttk_reg)
    {
        printf("ERROR: ttk_register missing while trying to print it.\n");
        return VARIABLE_NULL;
    }

    switch (ttk_reg->id)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            snprintf(buffer, size, "R%d", ttk_reg->id);
            break;
        case 6:
            snprintf(buffer, size, "SP");
            break;
        case 7:
            snprintf(buffer, size, "FP");
            break;
        default:
            assert(false && "No register id matched\n");
            break;
    }

    return 0;
}

int ttk_register_to_intel_asm_string(char* buffer, size_t size, struct ttk_register *ttk_reg)
{
    if (size < 5) {
        printf("ERROR: Buffer size too small (ttk_reg_to_string)\n");
        return -1;
    }

    if (!ttk_reg)
    {
        printf("ERROR: ttk_register missing while trying to print it.\n");
        return VARIABLE_NULL;
    }

    // TODO: this is possibly not correct
    // EAX, EBX, ECX, EDX, ESP, EBP, ESI, EDI
    switch (ttk_reg->id)
    {
        case 1:
            snprintf(buffer, size, "eax");
            break;
        case 2:
            snprintf(buffer, size, "ebx");
            break;
        case 3:
            snprintf(buffer, size, "ecx");
            break;
        case 4:
            snprintf(buffer, size, "edx");
            break;
        case 5:
            snprintf(buffer, size, "esp");
            break;
        case 6:
            snprintf(buffer, size, "ebp");
            break;
        case 7:
            snprintf(buffer, size, "esi");
            break;
        case 0:
            snprintf(buffer, size, "edi");
            break;
        default:
            assert(false && "No matching register");
            break;
    }

    return 0;
}

int ttk_register_print_intel_asm(struct ttk_register *ttk_reg)
{
    size_t size = 5;
    char buffer[size];

    ttk_register_to_intel_asm_string(buffer, size, ttk_reg);
    printf("%s", buffer);
    return 0;
}

int ttk_register_print(struct ttk_register *ttk_reg)
{
    size_t size = 3;
    char buffer[size];

    ttk_register_to_string(buffer, size, ttk_reg);
    printf("%s", buffer);
    return 0;
}

void ttk_register_free(struct ttk_register *ttk_reg)
{
    free(ttk_reg);
}
