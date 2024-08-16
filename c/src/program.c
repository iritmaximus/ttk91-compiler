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

void program_free(struct expr *program)
{
    struct expr *current = program;

    while (current != NULL)
    {
        expr_free(current);
        current = current->next;
    }
}
