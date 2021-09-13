#include "gtest/gtest.h"

TEST(ExampleTest, BasicTest) {
  // At some point this would actually test the functionality of the library
  EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
