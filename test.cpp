#include "spreadsheet.hpp"
#include "gtest/gtest.h"

TEST(Select_Contains, True) {
    char* test_val[1]; test_val[0] = "./main";
    EXPECT_EQ(true, new Select_Contains(&sheet,"Last","Dole");
}
TEST(Select_Contains, False) {
    char* test_val[1]; test_val[0] = "./main";
    EXPECT_EQ(false, new Select_Contains(&sheet,"First","v"));
}
TEST(Select_Not, Not) {
    char* test_val[1]; test_val[0] = "./main";
    EXPECT_EQ(!(select_ptr->select(sheet1, row)), new Select_Not(new Select_Contains(&sheet,"First","v")));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
