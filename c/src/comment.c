#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"
#include "comment.h"

struct comment * comment_create(char *text)
{
    struct comment *c = malloc(sizeof(*c));

    c->text = text;

    return c;
}

int comment_print(struct comment *c)
{
    if (!c || !c->text)
    {
        printf("\nERROR: Comment does not exist\n");
        return VARIABLE_NULL;
    }

    printf("%s", c->text);

    return 0;

}

void comment_free(struct comment *c)
{
    free(c->text);
    free(c);
}
