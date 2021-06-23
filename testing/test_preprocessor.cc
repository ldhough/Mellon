#include <gtest/gtest.h>
#include "../src/preprocessing.h"
#include "../src/levenshtein.h"

TEST(PasswordPreprocessorTest, TestSizeOne) {
    EXPECT_STRNE("hello", "world");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
