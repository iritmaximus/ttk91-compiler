#include <stdlib.h>
#include "comment.h"

struct comment * comment_create(char *text)
{
    struct comment *c = malloc(sizeof(*c));

    c->text = text;

    return c;
}
