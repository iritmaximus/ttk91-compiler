#include <gtest/gtest.h>

extern "C" {
#include "ttk_register.h"
#include "error.h"
}

TEST(Test_ttk_registers, parse_register_num_fails_with_empty_name) {
    char empty_name[] = "";
    char* null_name = NULL;
    const ttk_register_t kind = TTK_REGISTER;

    int result_empty = parse_register_num(empty_name, kind);
    int result_null = parse_register_num(null_name, kind);

    EXPECT_EQ(-1, result_empty);
    EXPECT_EQ(-1, result_null);
}

TEST(Test_ttk_registers, parse_register_num_returns_correct_value_ttk_reg) {
    char name0[] = "R0";
    char name3[] = "R3";
    char name6[] = "R6"; // also SP
    const ttk_register_t kind = TTK_REGISTER;

    int result0 = parse_register_num(name0, kind);
    int result3 = parse_register_num(name3, kind);
    int result6 = parse_register_num(name6, kind);

    EXPECT_EQ(0, result0);
    EXPECT_EQ(3, result3);
    EXPECT_EQ(6, result6);
}

TEST(Test_ttk_registers, parse_register_num_returns_correct_value_stack_registers) {
    char name_sp[] = "SP";
    char name_fp[] = "FP";
    const ttk_register_t kind = STACK_TTK_REGISTER;

    int result_sp = parse_register_num(name_sp, kind);
    int result_fp = parse_register_num(name_fp, kind);

    EXPECT_EQ(result_sp, 6);
    EXPECT_EQ(result_fp, 7);
}


TEST(Test_ttk_registers, Test_ttk_register_to_string_valid_parameters) {
    const size_t size = 3;
    char buffer0[size];
    char buffer2[size];
    char buffer7[size];
    char reg_name0[] = "R0";
    char reg_name2[] = "R2";
    char reg_name7[] = "R7";

    struct ttk_register *ttk_reg0 = ttk_register_create_register(reg_name0);
    struct ttk_register *ttk_reg2 = ttk_register_create_register(reg_name2);
    struct ttk_register *ttk_reg7 = ttk_register_create_register(reg_name7);

    EXPECT_EQ(0, ttk_reg0->id);
    EXPECT_EQ(2, ttk_reg2->id);
    EXPECT_EQ(7, ttk_reg7->id);

    int res0 = ttk_register_to_string(buffer0, size, ttk_reg0);
    int res2 = ttk_register_to_string(buffer2, size, ttk_reg2);
    int res7 = ttk_register_to_string(buffer7, size, ttk_reg7);

    EXPECT_EQ(0, res0);
    EXPECT_EQ(0, res2);
    EXPECT_EQ(0, res7);

    EXPECT_STREQ("R0", buffer0);
    EXPECT_STREQ("R2", buffer2);
    EXPECT_STREQ("FP", buffer7);

    ttk_register_free(ttk_reg0);
    ttk_register_free(ttk_reg2);
    ttk_register_free(ttk_reg7);
}

TEST(Test_ttk_registers, Test_ttk_register_to_string_too_small_buffer_size) {
    const size_t size = 2;
    char buffer0[size];
    char reg_name0[] = "R0";

    struct ttk_register *ttk_reg0 = ttk_register_create_register(reg_name0);
    EXPECT_EQ(0, ttk_reg0->id);

    // size and buffer too small
    int res0 = ttk_register_to_string(buffer0, size, ttk_reg0); 
    EXPECT_EQ(-1, res0);

    ttk_register_free(ttk_reg0);
}

TEST(Test_ttk_registers, Test_ttk_register_to_intel_asm_string_too_small_buffer_size) {
    const size_t size = 4;
    char buffer[size];
    char reg_name[] = "R2";

    struct ttk_register *ttk_reg = ttk_register_create_register(reg_name);
    EXPECT_EQ(2, ttk_reg->id);

    int result = ttk_register_to_intel_asm_string(buffer, size, ttk_reg);
    EXPECT_EQ(-1, result);

    ttk_register_free(ttk_reg);
}
