#include <gtest/gtest.h>

extern "C" {
#include "value.h"
#include "error.h"
}

TEST(Test_values, parse_addr_mode_missing_mode) {
    char *addr_mode_str = NULL;

    addr_mode_t addr_mode = parse_addr_mode(addr_mode_str);
    EXPECT_EQ(-1, addr_mode);
}

TEST(Test_values, parse_addr_mode_valid_parameters) {
    char direct[] = "";
    char immediate[] = "=";
    char immediate_value[] = "=100";
    char indirect[] = "@";
    char indirect_register[] = "@R2";

    addr_mode_t direct_res = parse_addr_mode(direct);
    addr_mode_t immediate_res = parse_addr_mode(immediate);
    addr_mode_t immediate_value_res = parse_addr_mode(immediate_value);
    addr_mode_t indirect_res = parse_addr_mode(indirect);
    addr_mode_t indirect_register_res = parse_addr_mode(indirect_register);

    EXPECT_EQ(DIRECT, direct_res);
    EXPECT_EQ(IMMEDIATE, immediate_res);
    EXPECT_EQ(IMMEDIATE, immediate_value_res);
    EXPECT_EQ(INDIRECT, indirect_res);
    EXPECT_EQ(INDIRECT, indirect_register_res);
}

TEST(Test_values, pure_value_to_string_too_small_buffer_size) {
    const size_t small_size = 1;
    char small_buffer[small_size];
    struct pure_value *p_v = pure_value_create_value(10);

    int small_res = pure_value_to_string(small_buffer, small_size, p_v);
    EXPECT_EQ(-1, small_res);

    pure_value_free(p_v);
}

TEST(Test_values, pure_value_to_string_missing_pure_value) {
    const size_t size = 20;
    char buffer[size];
    struct pure_value *missing = NULL;

    int res = pure_value_to_string(buffer, size, missing);
    EXPECT_EQ(VARIABLE_NULL, res);
}

TEST(Test_values, pure_value_to_string_valid_parameters) {
    const size_t size = 20;
    char buffer_value[size];
    char buffer_ttk_reg[size];
    char buffer_label[size];

    int num_value = 1034;
    char ttk_reg_name[] = "R2";
    char label_name[] = "X";
    struct pure_value *pure_value = pure_value_create_value(num_value);
    struct ttk_register *ttk_reg = ttk_register_create_register(ttk_reg_name);
    struct label *l = label_create_const(label_name);

    struct pure_value *pure_register = pure_value_create_ttk_register(ttk_reg);
    struct pure_value *pure_label = pure_value_create_label(l);

    int res_value = pure_value_to_string(buffer_value, size, pure_value);
    int res_ttk_reg = pure_value_to_string(buffer_ttk_reg, size, pure_register);
    int res_label = pure_value_to_string(buffer_label, size, pure_label);

    EXPECT_EQ(0, res_value);
    EXPECT_EQ(0, res_ttk_reg);
    EXPECT_EQ(0, res_label);

    EXPECT_STREQ("1034", buffer_value);
    EXPECT_STREQ("R2", buffer_ttk_reg);
    EXPECT_STREQ("X", buffer_label);

    pure_value_free(pure_value);
    pure_value_free(pure_register);
    pure_value_free(pure_label);
}

TEST(Test_values, value_to_string_too_small_buffer) {
    const size_t size = 1;
    char buffer[size];

    struct pure_value *p_v = pure_value_create_value(100);
    struct value *v = value_create_direct_value(p_v);

    int res = value_to_string(buffer, size, v);

    EXPECT_EQ(-1, res);

    value_free(v);
}

TEST(Test_values, value_to_string_missing_value) {
    const size_t size = 20;
    char buffer[size];
    struct value *v = NULL;

    int res = value_to_string(buffer, size, v);

    EXPECT_EQ(VARIABLE_NULL, res);
}

TEST(Test_values, value_to_string_valid_direct_none) {
    const size_t size = 20;
    char buffer_value[size];
    char buffer_ttk_reg[size];
    char buffer_label[size];

    int num_value = 4380;
    char ttk_reg_name[] = "R3";
    char label_name[] = "XYZ";
    struct ttk_register *ttk_reg = ttk_register_create_register(ttk_reg_name);
    struct label *l = label_create_const(label_name);

    struct pure_value *pure_value = pure_value_create_value(num_value);
    struct pure_value *pure_register = pure_value_create_ttk_register(ttk_reg);
    struct pure_value *pure_label = pure_value_create_label(l);

    struct value *value = value_create_direct_value(pure_value);
    struct value *value_ttk_register = value_create_direct_value(pure_register);
    struct value *value_label = value_create_direct_value(pure_label);
    
    int res_value = value_to_string(buffer_value, size, value);
    int res_register = value_to_string(buffer_ttk_reg, size, value_ttk_register);
    int res_label = value_to_string(buffer_label, size, value_label);

    EXPECT_EQ(0, res_value);
    EXPECT_EQ(0, res_register);
    EXPECT_EQ(0, res_label);

    EXPECT_STREQ("4380", buffer_value);
    EXPECT_STREQ("R3", buffer_ttk_reg);
    EXPECT_STREQ("XYZ", buffer_label);

    value_free(value);
    value_free(value_ttk_register);
    value_free(value_label);
}

TEST(Test_values, value_to_string_valid_direct_indexed) {
    const size_t size = 20;
    char buffer_value[size];
    char buffer_ttk_reg[size];
    char buffer_label[size];

    int num_value = 5949;
    char ttk_reg_name[] = "R1";
    char ttk_index_reg_name[] = "R4";
    char label_name[] = "HEYY";
    struct ttk_register *ttk_reg = ttk_register_create_register(ttk_reg_name);
    struct ttk_register *ttk_index_reg = ttk_register_create_register(ttk_index_reg_name);
    struct label *l = label_create_const(label_name);

    struct pure_value *pure_value = pure_value_create_value(num_value);
    struct pure_value *pure_register = pure_value_create_ttk_register(ttk_reg);
    struct pure_value *pure_label = pure_value_create_label(l);

    struct value *value = value_create_direct_indexed(pure_value, ttk_index_reg);
    struct value *value_ttk_register = value_create_direct_indexed(pure_register, ttk_index_reg);
    struct value *value_label = value_create_direct_indexed(pure_label, ttk_index_reg);
    
    int res_value = value_to_string(buffer_value, size, value);
    int res_register = value_to_string(buffer_ttk_reg, size, value_ttk_register);
    int res_label = value_to_string(buffer_label, size, value_label);

    /*
    EXPECT_EQ(0, res_value);
    EXPECT_EQ(0, res_register);
    EXPECT_EQ(0, res_label);

    EXPECT_STREQ("5949(R4)", buffer_value);
    EXPECT_STREQ("R1(R4)", buffer_ttk_reg);
    EXPECT_STREQ("HEYY(R4)", buffer_label);

    value_free(value);
    value_free(value_ttk_register);
    value_free(value_label);
    */
}
