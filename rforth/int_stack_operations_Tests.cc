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
TEST(IntStackTests, PushToCapacityAndOverflow)
{
    // create stack that can hold 10 items
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // ensure it's full
    ASSERT_EQ(int_stack_size(&stack1), capacity);

    // try to add one more
    int result = int_stack_push(&stack1, capacity+1);

    // and make sure it is an overflow (error)
    ASSERT_FALSE(result);
}
TEST(IntStackTests, PushToCapcacityPopUntilUnderflow
)
{
    // create stack that can hold 10 items [similar to previous test]
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    // fill it
    for (int i=0; i < capacity; i++) {
        int result = int_stack_push(&stack1, i);
        ASSERT_TRUE(result);
    }

    // now drain it one item at a time, ensuring each item is the value expected
    for (int i=capacity-1; i >= 0; i--) {
        int top_value;
        int result = int_stack_pop(&stack1, &top_value);
        ASSERT_EQ(i, top_value);
    }

    // try to remove from empty stack and ensure it fails
    int top_value;
    int result = int_stack_pop(&stack1, &top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, TwoOver)
{
    int_stack_t stack1;
    int_stack_init(&stack1, 10);
    int_stack_push(&stack1, 20);
    int_stack_push(&stack1, 30);
    int_stack_push(&stack1, 40);
    int_stack_push(&stack1, 50);
    //int_stack_print(&stack1, stdout);
    ASSERT_TRUE(int_stack_2over(&stack1));
    //int_stack_print(&stack1, stdout);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 30);
    //int_stack_print(&stack1, stdout);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 20);
    //int_stack_print(&stack1, stdout);
}

TEST(IntStackTests, Addition){
    int_stack_t stack1;
    int_stack_init(&stack1, 3);
    int_stack_push(&stack1, 2);
    int_stack_push(&stack1, 5);
    int_stack_push(&stack1, 5);
    //int_stack_print(&stack1, stdout); What the stack looks like originally
    ASSERT_TRUE(int_stack_add(&stack1));
    //int_stack_print(&stack1, stdout); The stack after the operation performed
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 10);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);

}

TEST(IntStackTests, Subtraction){
    int_stack_t stack1;
    int_stack_init(&stack1, 3);
    int_stack_push(&stack1, 2);
    int_stack_push(&stack1, 10);
    int_stack_push(&stack1, 4);
    //int_stack_print(&stack1, stdout); //What the stack looks like originally
    ASSERT_TRUE(int_stack_subtract(&stack1));
    //int_stack_print(&stack1, stdout); //The stack after the operation performed
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 6);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);

}
TEST(IntStackTests, Multiplication){
    int_stack_t stack1;
    int_stack_init(&stack1, 3);
    int_stack_push(&stack1, 1);
    int_stack_push(&stack1, 2);
    int_stack_push(&stack1, 3);
    //should be 6
    //int_stack_print(&stack1, stdout);
    ASSERT_TRUE(int_stack_multiply(&stack1));
    //int_stack_print(&stack1, stdout);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 6);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 1);

}
TEST(IntStackTests, Division){
    int_stack_t stack1;
    int_stack_init(&stack1, 3);
    int_stack_push(&stack1, 1);
    int_stack_push(&stack1, 6);
    int_stack_push(&stack1, 2);
    //should be 3
    //int_stack_print(&stack1, stdout);
    ASSERT_TRUE(int_stack_div(&stack1));
    //int_stack_print(&stack1, stdout);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 3);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 1);
}
TEST(IntStackTests, DivideMod){
    int_stack_t stack1;
    int_stack_init(&stack1, 2);
    int_stack_push(&stack1, 7);
    int_stack_push(&stack1, 3);
    //int_stack_print(&stack1, stdout);
    ASSERT_TRUE(int_stack_dividemod(&stack1));
    //int_stack_print(&stack1, stdout);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 1);
}
TEST(IntStackTests, MOD){
    int_stack_t stack1;
    int_stack_init(&stack1, 2);
    int_stack_push(&stack1, 10);
    int_stack_push(&stack1, 4);
    //int_stack_print(&stack1, stdout);
    ASSERT_TRUE(int_stack_mod(&stack1));
    //int_stack_print(&stack1, stdout);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);
}
TEST(IntStackTests, SWAP){
    int_stack_t stack1;
    int_stack_init(&stack1, 3);
    int_stack_push(&stack1, 1);
    int_stack_push(&stack1, 2);
    int_stack_push(&stack1, 3);
    //int_stack_print(&stack1, stdout);
    ASSERT_TRUE(int_stack_swap(&stack1));
    //int_stack_print(&stack1, stdout);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 3);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 1);
}
TEST(IntStackTests, DUP){
    int_stack_t stack1;
    int_stack_init(&stack1, 3);
    int_stack_push(&stack1, 1);
    int_stack_push(&stack1, 5);
    //int_stack_print(&stack1, stdout);
    ASSERT_TRUE(int_stack_dup(&stack1));
    //int_stack_print(&stack1, stdout);
    int top_value;
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 5);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 5);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 1);
}
TEST(IntStackTests, OVER){
    int_stack_t stack;
    int_stack_init(&stack, 6);
    int_stack_push(&stack, 1);
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 3);
    int_stack_push(&stack, 4);
    int_stack_push(&stack, 5);
    ASSERT_TRUE(int_stack_over(&stack));
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 4); 
}
TEST(IntStackTests, ROT){
    int_stack_t stack;
    int_stack_init(&stack, 3);
    int_stack_push(&stack, 1);
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 3);
    ASSERT_TRUE(int_stack_rot(&stack));
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 1);
}
TEST(IntStackTests, DROP){
    int_stack_t stack;
    int_stack_init(&stack, 2);
    int_stack_push(&stack, 10);
    int_stack_push(&stack, 20);
    ASSERT_TRUE(int_stack_drop(&stack));
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 10);
}
TEST(IntStackTests, TWOSWAP){
    int_stack_t stack;
    int_stack_init(&stack, 4);
    int_stack_push(&stack, 10);
    int_stack_push(&stack, 20);
    int_stack_push(&stack, 30);
    int_stack_push(&stack, 40);
    ASSERT_TRUE(int_stack_2swap(&stack));
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 20);
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 10);
}
TEST(IntStackTests, TwoDup){
    int_stack_t stack;
    int_stack_init(&stack, 4);
    int_stack_push(&stack, 10);
    int_stack_push(&stack, 20);
    ASSERT_TRUE(int_stack_2dup(&stack));
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 20);
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 10);
}
TEST(IntStackTests, TwoDrop){
    int_stack_t stack;
    int_stack_init(&stack, 4);
    int_stack_push(&stack, 10);
    int_stack_push(&stack, 20);
    int_stack_push(&stack, 30);
    int_stack_push(&stack, 40);
    ASSERT_TRUE(int_stack_2drop(&stack));
    ASSERT_EQ(int_stack_size(&stack), 2);
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 20);
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 10);
    
}
// Tests for Conditions Boolean Expressions
TEST(IntStackTests, Equal){ //equal 5 = 5 
    int_stack_t stack;
    int_stack_init(&stack, 2);
    int_stack_push(&stack, 5);
    int_stack_push(&stack, 5);
    //int_stack_print(&stack, stdout);
    ASSERT_TRUE(int_stack_equal(&stack));
    ASSERT_EQ(int_stack_size(&stack), 1);
    //int_stack_print(&stack, stdout);
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, -1);

} //NOTE TO SELF: I think i don't need to do this not sure yet *nevermind i got it to work! Originally wasn't working bc it was just return -1/0 and wasn't getting added to the stack but figured it out.

TEST(IntStackTests, Equal2){ //not equal 5 = 4
    int_stack_t stack;
    int_stack_init(&stack, 2);
    int_stack_push(&stack, 5);
    int_stack_push(&stack, 4);
    //int_stack_print(&stack, stdout);
    ASSERT_TRUE(int_stack_equal(&stack));
    ASSERT_EQ(int_stack_size(&stack), 1);
    //int_stack_print(&stack, stdout);
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 0);

} 
TEST(IntStackTests, GreaterThan){ // 10 > 6 is true (-1)
    int_stack_t stack;
    int_stack_init(&stack, 3);
    int_stack_push(&stack, 12);
    int_stack_push(&stack, 10);
    int_stack_push(&stack, 6);
    //int_stack_print(&stack, stdout);
    ASSERT_TRUE(int_stack_greaterThan(&stack));
    ASSERT_EQ(int_stack_size(&stack), 2);
    //int_stack_print(&stack, stdout);
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, -1);

}
TEST(IntStackTests, GreaterThan2){ // 5 > 6 is false (0)
    int_stack_t stack;
    int_stack_init(&stack, 3);
    int_stack_push(&stack, 12);
    int_stack_push(&stack, 5);
    int_stack_push(&stack, 6);
    //int_stack_print(&stack, stdout);
    ASSERT_TRUE(int_stack_greaterThan(&stack));
    ASSERT_EQ(int_stack_size(&stack), 2);
    //int_stack_print(&stack, stdout);
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 0);
}
TEST(IntStackTests, LessThan){ //false (0) bc 100 < 9 not true -> forth output: 12 9 100 < . . -1 12  ok
    int_stack_t stack;
    int_stack_init(&stack, 3);
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 100);
    int_stack_push(&stack, 9);
    ASSERT_TRUE(int_stack_lessThan(&stack));
    ASSERT_EQ(int_stack_size(&stack), 2);
    //int_stack_print(&stack, stdout);
    int top_value;
    int_stack_pop(&stack, &top_value);
    ASSERT_EQ(top_value, 0);
    //int_stack_print(&stack, stdout);

}
TEST(IntStackTests, Invert){
    int_stack_t stack;
    int_stack_init(&stack, 3);
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 100);
    int_stack_push(&stack, 9);
    ASSERT_TRUE(int_stack_lessThan(&stack));
    //int_stack_print(&stack, stdout); //From lessThan the result is 0 (false)
    ASSERT_TRUE(int_stack_invert(&stack));
    //int_stack_print(&stack, stdout);//Result inverted to -1 (true)
}
TEST(IntStackTests, Invert2){
    int_stack_t stack;
    int_stack_init(&stack, 3);
    int_stack_push(&stack, 2);
    int_stack_push(&stack, 9);
    int_stack_push(&stack, 20);
    ASSERT_TRUE(int_stack_lessThan(&stack));
    //int_stack_print(&stack, stdout); //From lessThan the result is 1 (true)
    ASSERT_TRUE(int_stack_invert(&stack));
    //int_stack_print(&stack, stdout);//Result inverted to 0 (false)
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
    //int_stack_print(&stack, stdout); //prints stack, just so i can see how the tests working

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
    //int_stack_print(&stack, stdout);
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
    //int_stack_print(&stack, stdout);
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
TEST(IntStackTests, int_stack_pick){//pick

}
TEST(IntStackTests, int_stack_pickn){//pickn

}
TEST(IntStackTests, int_stack_loop){//loop

}
TEST(IntStackTests, int_stack_repeat){ //repeat

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
