#ifndef REGISTER_H
#define REGISTER_H

struct ttk_register {
    int id;
    int value;
};

struct ttk_register * ttk_register_create(char* id, int value);
int parse_register_num(char *name);

#endif
