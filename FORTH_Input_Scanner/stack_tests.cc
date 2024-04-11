#include <gtest/gtest.h>

#include "stack.hh"

TEST(IntStackTests, Initialization)
{
    int_stack_t stack1;
    int_stack_init(&stack1, 10);
    ASSERT_EQ(int_stack_size(&stack1), 0);
    ASSERT_EQ(int_stack_capacity(&stack1), 10);
}

TEST(IntStackTests, CheckIfDuplicated){
    //check if output matches the first value AND that the first value has not changed
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);
    int top_value;
    int_stack_push(stack1,top_value);
    //check if capacity < 1
    ASSERT_TRUE(int_stack_size(&stack1)>=1);

   
    int_stack_dup(stack1);
    ASSERT_EQ(int_stack_push(stk, top_value),top_value);
}

TEST(IntStackTests, SwitchFirstTwoElements){
    //check if first element is now the second one, and vice versa
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int top_value, second_from_top_value;
    int_stack_push(stack1,top_value);
    int_stack_push(stack1,second_from_top_value);
    //check if capacity > 1
    ASSERT_TRUE(int_stack_size(&stack1)>1);

    int_stack_swap(stack1);
    ASSERT_EQ(int_stack_pop(stack1,top_value),second_from_top_value);
    ASSERT_EQ(int_stack_pop(stack1,top_value),top_value);
}

TEST(IntStackTests, CopySecondElementToTop){
    //check if the first element of the stack is = the old second element
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int top_value, second_from_top_value;
    int_stack_push(stack1,top_value);
    int_stack_push(stack1,second_from_top_value);

    ASSERT_TRUE(int_stack_size(stack1)>1)

    int_stack_over(stack1);
    ASSERT_EQ(int_stack_pop(stack1,top_value),second_from_top_value);

}

TEST(IntStackTests, RotateTopThreeElements){
    //check that 1 - 2 - 3 becomes 2 - 3 - 1
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int top_value, second_from_top_value, third_from_top_value;
    int_stack_push(stack1,top_value);
    int_stack_push(stack1,second_from_top_value);
    int_stack_push(stack1,third_from_top_value);

    ASSERT_TRUE(int_stack_size(stack1)>2);

    int_stack_rot(stack1);
    
    ASSERT_EQ(int_stack_pop(stack1,top_value),second_from_top_value);
    ASSERT_EQ(int_stack_pop(stack1,top_value),third_from_top_value);
    ASSERT_EQ(int_stack_pop(stack1,top_value),top_value);
}

TEST(IntStackTests, TopElementRemoved){
    //make sure the top element is = to the old second from top element
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int top_value, second_from_top_value;
    int_stack_push(stack1,top_value);
    int_stack_push(stack1,second_from_top_value);

    ASSERT_TRUE(int_stack_size(stack1)>0);

    int_stack_drop(stack1);

    ASSERT_EQ(int_stack_push(stack1,top_value),second_from_top_value);
}

TEST(IntStackTests, TwoPairsSwapped){
    //check that 1 - 2 - 3 - 4 becomes 3 - 4 - 1 - 2
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int top_value, second_from_top_value, third_from_top_value, fourth_from_top_value;
    int_stack_push(stack1,top_value);
    int_stack_push(stack1,second_from_top_value);
    int_stack_push(stack1,third_from_top_value);
    int_stack_push(stack1, fourth_from_top_value);

    ASSERT_TRUE(int_stack_size(stack1)>3);

    int_stack_2swap(stack1);

    ASSERT_EQ(int_stack_pop(stack1,top_value),third_from_top_value);
    ASSERT_EQ(int_stack_pop(stack1,top_value),fourth_from_top_value);
    ASSERT_EQ(int_stack_pop(stack1,top_value),top_value);
    ASSERT_EQ(int_stack_pop(stack1,top_value),second_from_top_value);

}

TEST(IntStackTests, DuplicateTopTwoElements){
    //check if the first two elements are returned
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int top_value, second_from_top_value;
    int_stack_push(stack1,top_value);
    int_stack_push(stack1,second_from_top_value);

    ASSERT_TRUE(int_stack_size(stack1)>1);

    int_stack_2dup(stack1);
    
    ASSERT_EQ(int_stack_push(stk, top_value),top_value);
    ASSERT_EQ(int_stack_push(stk, top_value),second_from_top_value);
}

TEST(IntStackTests, CopyThirdAndFourthElements){
    //check if third and fourth elements are returned
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int top_value, second_from_top_value, third_from_top_value, fourth_from_top_value;
    int_stack_push(stack1,top_value);
    int_stack_push(stack1,second_from_top_value);
    int_stack_push(stack1,third_from_top_value);
    int_stack_push(stack1, fourth_from_top_value);

    ASSERT_TRUE(int_stack_size(stack1)>3)

    int_stack_2over(stack1);
    ASSERT_EQ(int_stack_push(stk, top_value),third_from_top_value);
    ASSERT_EQ(int_stack_push(stk, top_value),fourth_from_top_value);

}

TEST(IntStackTests, TopTwoElementsRemoved){
    //check the top element now = third from top element
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int top_value, second_from_top_value, third_from_top_value;
    int_stack_push(stack1,top_value);
    int_stack_push(stack1,second_from_top_value);
    int_stack_push(stack1,third_from_top_value);

    ASSERT_TRUE(int_stack_size(stack1)>2);

    int_stack_2drop(stack1);
    ASSERT_EQ(int_stack_push(stack1,top_value),third_from_top_value);
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

TEST(IntStackTests, Addition){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int_stack_push(&stack, 2);
    int_stack_push(&stack, 5);

    int_stack_add(&stack);
    int result;
    int_stack_pop(&stack, &result);

    ASSERT_EQ(result, 7);
}

TEST(IntStackTests, Subtraction){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int_stack_push(&stack, 9);
    int_stack_push(&stack, 3);

    int_stack_sub(&stack);
    int result;
    int_stack_pop(&stack, &result);

    ASSERT_EQ(result, 6);
}

TEST(IntStackTests, Mulitiplication){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int_stack_push(&stack, 6);
    int_stack_push(&stack, 4);

    int_stack_mult(&stack);
    int result;
    int_stack_pop(&stack, &result);

    ASSERT_EQ(result, 24);
}

TEST(IntStackTests, Division){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int_stack_push(&stack, 12);
    int_stack_push(&stack, 2);

    int_stack_add(&stack);
    int result;
    int_stack_pop(&stack, &result);

    ASSERT_EQ(result, 6);
}

TEST(IntStackTests, Modulus){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int_stack_push(&stack, 5);
    int_stack_push(&stack, 3);

    int_stack_add(&stack);
    int result;
    int_stack_pop(&stack, &result);

    ASSERT_EQ(result, 2);
}

TEST(IntStackTests, DivisionModulus){
    int_stack_t stack1;
    const int capacity = 10;
    int_stack_init(&stack1, capacity);

    int_stack_push(&stack, 9);
    int_stack_push(&stack, 2);

    int_stack_divmod(&stack);
    int remainder, quotient;
    int_stack_pop(&stack, &remainder);
    int_stack_pop(&stack, &quotient);

    ASSERT_EQ(remainder, 1);
    ASSERT_EQ(quotient, 4);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}