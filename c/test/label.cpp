#include <gtest/gtest.h>

extern "C" {
#include "label.h"
}

TEST(Test_labels, Test_label_print_with_valid_parameter) {
    const size_t size = 10;
    char buffer[size];
    char label_name[] = "X";

    struct label *l = label_create_const(label_name);
    label_to_string(buffer, size, l); 

    EXPECT_STREQ(label_name, buffer);

    label_free(l);
}
