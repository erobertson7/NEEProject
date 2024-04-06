#include "gtest/gtest.h"
#include "int_stack.c"
#include "int_stack.h"

class IntStackTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    int_stack_t stack;
};

TEST_F(IntStackTest, Initialization) {
    int_stack_init(&stack, 5);
    EXPECT_EQ(int_stack_size(&stack), 0);
    EXPECT_EQ(int_stack_capacity(&stack), 5);
}

TEST_F(IntStackTest, PushAndPop) {
    int_stack_init(&stack, 3);
    EXPECT_EQ(int_stack_push(&stack, 1), 1);
    EXPECT_EQ(int_stack_push(&stack, 2), 1);
    EXPECT_EQ(int_stack_push(&stack, 3), 1);
    EXPECT_EQ(int_stack_size(&stack), 3);
    EXPECT_EQ(int_stack_capacity(&stack), 3);
    int value;
    EXPECT_EQ(int_stack_pop(&stack, &value), 1);
    EXPECT_EQ(value, 3);
    EXPECT_EQ(int_stack_pop(&stack, &value), 1);
    EXPECT_EQ(value, 2);
    EXPECT_EQ(int_stack_pop(&stack, &value), 1);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(int_stack_size(&stack), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
