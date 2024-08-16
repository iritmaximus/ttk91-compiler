#ifndef COMMENT_H
#define COMMENT_H


struct comment {
    char *text;
};

struct comment * comment_create(char *text);
int comment_print(struct comment *c);

#endif
