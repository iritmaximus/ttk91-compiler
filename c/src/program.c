#include <stdlib.h>
#include <stdio.h>
#include "expr.h"

int program_print(struct expr *program)
{
    struct expr *current = program;

    while (current != NULL)
    {
        if (expr_print(current)!=0)
            return 1;
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
