//Adding Tests here for functions
#include <gtest/gtest.h>

#include "int_stack_operators.hh"

TEST(IntStackTests, Initialization) //grabbed this to test if it worked and ran
{
    int_stack_t stack1;
    int_stack_init(&stack1, 10);
    ASSERT_EQ(int_stack_size(&stack1), 0);
    ASSERT_EQ(int_stack_capacity(&stack1), 10);
}
TEST(IntStackTests, int_stack_depth)
{
    int_stack_t stack;
    int_stack_init(&stack, 4);
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 5);
    int_stack_push(&stack, 26);
    int_stack_depth(&stack);
    int_stack_print(&stack, stdout);


}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}