//
// Created by George Thiruvathukal on 2/17/24.
//

#include <gtest/gtest.h>

#include "int_stack.hh"

TEST(IntStackTests, Initialization)
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


TEST(IntStackTests, PushToCapcacityPopUntilUnderflow){
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
    int top_value = 1;
    int result = int_stack_pop(&stack1, &top_value); //value in top_value should not change (becasue there is nothing in the stack)
    ASSERT_EQ(1, top_value);
    ASSERT_FALSE(result);
}

TEST(IntStackTests, arithmeticOperations){
    int_stack_t stack1;
    int top_value;
    int_stack_init(&stack1, 10);
    int_stack_push(&stack1, 6);
    int_stack_push(&stack1, 2);
    //add
    int_stack_add(&stack1);
    int_stack_top(&stack1,&top_value);
    ASSERT_EQ(top_value,8);
    //sub
    int_stack_push(&stack1, 2);
    int_stack_subtract(&stack1);
    int_stack_top(&stack1,&top_value);
    ASSERT_EQ(top_value,6);
    //mult
    int_stack_push(&stack1, 2);
    int_stack_multiply(&stack1);
    int_stack_top(&stack1,&top_value);
    ASSERT_EQ(top_value,12);
    //divide
    int_stack_push(&stack1, 4);
    int_stack_divide(&stack1);
    int_stack_top(&stack1,&top_value);
    ASSERT_EQ(top_value,3);
    int_stack_pop(&stack1,&top_value);
    //mod remainder only
    int_stack_push(&stack1, 4);
    int_stack_push(&stack1, 3);
    int_stack_mod_r(&stack1);
    int_stack_top(&stack1,&top_value);
    ASSERT_EQ(top_value,1);
    int_stack_pop(&stack1,&top_value);
    //mod remainder quotient 
    int_stack_push(&stack1, 4);
    int_stack_push(&stack1, 3);
    int_stack_mod_r(&stack1);
    int_stack_pop(&stack1,&top_value);
    ASSERT_EQ(top_value,1); //remainder 1
    int_stack_pop(&stack1,&top_value);
    ASSERT_EQ(top_value,1);//quotient 1
}

TEST(IntStackTests, singleFunctions){
    int_stack_t stack1; 
    int top_value, next_to_top_value;
    int_stack_init(&stack1, 10);
    int_stack_push(&stack1, 6);
    int_stack_push(&stack1, 2);
    //swap
    int_stack_swap(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 6);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 2);
    //dup
    int_stack_push(&stack1, 2);
    int_stack_dup(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 2);
    //over
    int_stack_push(&stack1, 2);
    int_stack_push(&stack1, 1); //stack now 2 1
    int_stack_over(&stack1); //should be 2 1 2
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 1);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(int_stack_size(&stack1), 0);
    //rot 
    int third_val; 
    int_stack_push(&stack1, 1);
    int_stack_push(&stack1, 2);
    int_stack_push(&stack1, 3);
    int_stack_rot(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 1);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 3);
    int_stack_pop(&stack1, &third_val);
    ASSERT_EQ(third_val, 2);
    //drop
    int_stack_push(&stack1, 1);
    int_stack_drop(&stack1);
    ASSERT_EQ(int_stack_size(&stack1), 0);
}

TEST(IntStackTests, doubleFunctions){
    int_stack_t stack1; 
    int top_value, next_to_top_value;
    int_stack_init(&stack1, 10);
    int_stack_push(&stack1, 3);
    int_stack_push(&stack1, 4);
    //2dup
    int_stack_2dup(&stack1);
    ASSERT_EQ(int_stack_size(&stack1), 4);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 4);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 3);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 4);
    int_stack_pop(&stack1, &next_to_top_value); 
    ASSERT_EQ(next_to_top_value, 3);
    //2swap
    int_stack_push(&stack1, 1);
    int_stack_push(&stack1, 2);
    int_stack_push(&stack1, 3);
    int_stack_push(&stack1, 4);
    int_stack_2swap(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 1);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 4);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 3);
    //2over
    int_stack_push(&stack1, 1);
    int_stack_push(&stack1, 2);
    int_stack_push(&stack1, 3);
    int_stack_push(&stack1, 4);
    int_stack_2over(&stack1);
    int_stack_pop(&stack1, &top_value);
    ASSERT_EQ(top_value, 2);
    int_stack_pop(&stack1, &next_to_top_value);
    ASSERT_EQ(next_to_top_value, 1);
    //2drop
    int_stack_2drop(&stack1);
    ASSERT_EQ(int_stack_size(&stack1), 2);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}