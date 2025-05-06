#include <stdlib.h>
#include <stdio.h>
#include "expr.h"

int program_print(struct expr *program)
{
    struct expr *current = program;

    while (current != NULL)
    {
        int err = expr_print(current);
        if (err!=0)
            return err;
        current = current->next;
    }

    return 0;

}

int program_print_intel_asm(struct expr *program)
{
    struct expr *current = program;

    while (current != NULL)
    {
        int err = expr_print_intel_asm(current);
        if (err != 0)
            return err;
        current = current->next;
    }

    return 0;
}

void program_free(struct expr *program)
{
    struct expr *current = program;

    // TODO: Error checking
    while (current != NULL)
    {
        struct expr *next = current->next;
        expr_free(current);
        current = next;
    }
}
