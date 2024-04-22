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
//Test for Depth
TEST(IntStackTests, int_stack_depth){
    int_stack_t stack;
    int_stack_init(&stack, 7); //initialize stack
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 5);
    int_stack_push(&stack, 26);
    int_stack_push(&stack, 30);
    int_stack_push(&stack, 100);
    int_stack_push(&stack, 72);
    ASSERT_TRUE(int_stack_depth(&stack)); //running depth function)
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value,int_stack_size(&stack));
    int_stack_push(&stack, top_value);//prints stack, just so i can see how the tests working
    int_stack_print(&stack, stdout); //prints stack, just so i can see how the tests working

}
//Test for Negate
TEST(IntStackTests, int_stack_negate){
    int_stack_t stack;
    int top_value;
    int_stack_init(&stack, 5); //initialize stack
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 10);
    ASSERT_TRUE(int_stack_negate(&stack));
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, -10);
    int_stack_push(&stack, top_value);
    int_stack_print(&stack, stdout);
}
//Test for 
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}