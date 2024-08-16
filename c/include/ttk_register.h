#ifndef REGISTER_H
#define REGISTER_H

typedef enum {
    TTK_REGISTER,
    STACK_TTK_REGISTER
} ttk_register_t;

struct ttk_register {
    ttk_register_t kind;
    int id;
    int value;
};

struct ttk_register * ttk_register_create(ttk_register_t kind, char* id, int value);
int parse_register_num(char *name, ttk_register_t kind);
struct ttk_register * ttk_register_create_register(char* name);
struct ttk_register * ttk_register_create_stack_register(char* name);

int ttk_register_print(struct ttk_register *ttk_reg);

#endif
