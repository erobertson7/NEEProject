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
/* Used this to debug issues
TEST(IntStackTests, int_stack_max){
    int_stack_t stack;
    int minimum_value;
    int_stack_init(&stack, 5); //initialize stack
    int_stack_push(&stack, 20);
    int_stack_push(&stack, 600);
    int_stack_push(&stack, 80);
    int_stack_push(&stack, 10);
    int_stack_print(&stack, stdout);//stack before
    ASSERT_TRUE(int_stack_min(&stack));
    int_stack_pop(&stack, &minimum_value);
    ASSERT_EQ(minimum_value, 20);
    int_stack_push(&stack, minimum_value);
    int_stack_print(&stack, stdout); //stack after
}
*/


//Test for min
TEST(IntStackTests, int_stack_min){
    int_stack_t stack;
    int min_value;
    int_stack_init(&stack, 5);
    int_stack_push(&stack, 3);
    int_stack_push(&stack, -4);
    int_stack_push(&stack, 11);
    int_stack_push(&stack, 6);
    ASSERT_TRUE(int_stack_min(&stack));
    int_stack_pop(&stack, &min_value);
    ASSERT_EQ(min_value, -4);
    int_stack_push(&stack, min_value);
    int_stack_print(&stack, stdout);
}

//Test for max
TEST(IntStackTests, int_stack_max){
    int_stack_t stack;
    int max_value;
    int_stack_init(&stack, 6);
    int_stack_push(&stack, 1);
    int_stack_push(&stack, -7);
    int_stack_push(&stack, 3);
    int_stack_push(&stack, 9);
    int_stack_push(&stack, 4);
    printf("Before max function\n");
    int_stack_print(&stack, stdout);
    ASSERT_TRUE(int_stack_max(&stack));
    int_stack_pop(&stack, &max_value);
    ASSERT_EQ(max_value, 9);
    int_stack_push(&stack, max_value);
    printf("After max function\n");
    int_stack_print(&stack, stdout);
}    

TEST(IntStackTests, int_stack_abs){
    int_stack_t stack;
    int top_value;
    int_stack_init(&stack, 3);
    int_stack_push(&stack, 1);
    int_stack_push(&stack, 3);
    int_stack_push(&stack, -9);
    printf("Before absolute function\n");
    int_stack_print(&stack, stdout);
    ASSERT_TRUE(int_stack_abs(&stack));
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 9);
    int_stack_push(&stack, top_value);
    printf("After absolute function\n");
    int_stack_print(&stack, stdout);
}

//Test for floor
/*
TEST(IntStackTests, int_stack_floor){
    int_stack_t stack;
    int top_value;
    int_stack_init(&stack, 3);
    int_stack_push(&stack, 2.1);
    int_stack_push(&stack, -4.6);
    int_stack_push(&stack, 5);
    ASSERT_TRUE(int_stack_floor(&stack));
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 5);
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, -5);
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 2);
}
*/

//Test for ceil
/*
TEST(IntStackTests, int_stack_ceil){
    int_stack_t stack;
    int top_value;
    int_stack_init(&stack, 3);
    int_stack_push(&stack, 2.1);
    int_stack_push(&stack, -4.6);
    int_stack_push(&stack, 5);
    ASSERT_TRUE(int_stack_ceil(&stack));
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 5);
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, -4);
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 3);
}
*/

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
