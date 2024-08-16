#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
        return 1;
    }

    printf("%s", c->text);

    return 0;

}
