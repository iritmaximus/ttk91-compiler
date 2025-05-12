#ifndef VALUE_H
#define VALUE_H

#include "ttk_register.h"
#include "label.h"

typedef enum {
    REGISTER,
    NUMBER,
    LABEL
} value_t;

typedef enum {
    NONE,
    INDEXED,
    INDEXED_ONLY_IREG
} index_t;

typedef enum {
    DIRECT,
    IMMEDIATE,
    INDIRECT
} addr_mode_t;

struct value {
    addr_mode_t addr_mode;
    index_t indexing_mode;
    struct pure_value *value;
    struct ttk_register *index_register;
};

struct pure_value {
    value_t kind;
    struct ttk_register *ttk_register;
    int number;
    struct label *label;
};

struct value * value_create(addr_mode_t addr_m, index_t i_m, struct pure_value *value, struct ttk_register *i_reg);
struct value * value_create_direct_value(struct pure_value *p_v);
struct value * value_create_direct_indexed(struct pure_value *p_v, struct ttk_register *ttk_reg);
struct value * value_create_address_mode_indexed(char* addr_mode, struct pure_value *p_v, struct ttk_register *ttk_reg);
struct value * value_create_address_mode(char* addr_mode, struct pure_value *p_v);
struct value * value_create_direct_register(struct ttk_register *ttk_reg);


struct pure_value * pure_value_create_ttk_register(struct ttk_register *ttk_reg);
struct pure_value * pure_value_create_value(int value);
struct pure_value * pure_value_create_label(struct label *l);

struct pure_value * pure_value_create(value_t kind, struct ttk_register *ttk_reg, int num, struct label *l);
addr_mode_t parse_addr_mode(char* addr_mode);
int pure_value_to_string(char *buffer, size_t size, struct pure_value *p_v);
int pure_value_print(struct pure_value *p_v);
int value_to_string(char *buffer, size_t size, struct value *v);
int value_print(struct value *v);
int pure_value_print_intel_asm(struct pure_value *p_v);
int value_print_intel_asm(struct value *v);


void value_free(struct value *v);
void pure_value_free(struct pure_value *p_v);

#endif
