#include "int_stack_operators.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// add main function. to be expanded out later.
/*
int main() {
    int_stack_t myStack;
    int_stack_init(&myStack, 10);
    int_stack_push(&myStack, 5);
    int_stack_negate(&myStack);
    return 0;
}
*/


//this initializes the stack
void int_stack_init(int_stack_t *stk, int capacity) {
    SLIST_INIT(&stk->head);
    stk->size = 0;
    stk->capacity = capacity;
}

//pushes the value onto the stack
int int_stack_push(int_stack_t *stk, int value) {
    if (stk->size >= stk->capacity) {
        printf("Stack is at full capacity.\n");
        return 0; // fail
    }

    int_entry_t *newEntry = malloc(sizeof(int_entry_t));
    if (newEntry) {
        newEntry->value = value;
        SLIST_INSERT_HEAD(&stk->head, newEntry, entries);
        stk->size++;
        return 1; //success
    }
    return 0; // fail
}

//removes a value from the stack
int int_stack_pop(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        int value = entry->value;
        SLIST_REMOVE_HEAD(&stk->head, entries);
        free(entry);
        stk->size--;
        *top_value = value;
        return 1; // success
    }
    return 0; // fail
}

int int_stack_top(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        *top_value = entry->value;
        return 1; // success
    }
    return 0; // fail
}

/* Functions for FORTH langauge stack operators */

int int_stack_dup(int_stack_t *stk) {
    if (stk->size < 1)
        return 0;
    int top_value;
    int_stack_top(stk, &top_value);
    return int_stack_push(stk, top_value); // success only if last operation succeeds
}

int int_stack_swap(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value); // success only if last operation succeeds
}

/* Example of how to create a binary operator that works o top two elements (if present) */

int int_stack_add(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value + next_to_top_value);
}

int int_stack_subtract(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    //return int_stack_push(stk, top_value - next_to_top_value);
    return int_stack_push(stk, next_to_top_value - top_value);
}

int int_stack_multiply(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value * next_to_top_value);
}

int int_stack_div(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    //return int_stack_push(stk, top_value / next_to_top_value);
    return int_stack_push(stk, next_to_top_value / top_value);
}

int int_stack_dividemod(int_stack_t *stk){ //return remainder and quotient
    if (stk->size < 2)
        return 0;
    int s1, s2;
    int_stack_pop(stk, &s1); 
    int_stack_pop(stk, &s2);
    int rem = s2 % s1;
    int quot = s2 / s1;
    int_stack_push(stk, rem);
    return int_stack_push(stk, quot);
}

int int_stack_mod(int_stack_t *stk){ //return remainder only
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    //return int_stack_push(stk, top_value % next_to_top_value);
    return int_stack_push(stk, next_to_top_value % top_value);

}

int int_stack_over(int_stack_t *stk){ //copies the second top value to the top of the stack
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value);
}

int int_stack_rot(int_stack_t *stk){ //3rd item in stack gets moved to the top
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value, val3;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_pop(stk, &val3);
    int_stack_push(stk, next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, val3);
}

int int_stack_drop(int_stack_t *stk){
    if (stk->size < 0)
        return 0;
    int top_value;
    return int_stack_pop(stk, &top_value);
}

int int_stack_2swap(int_stack_t *stk){
    if (stk->size < 4)
        return 0;
    int top_value, next_to_top_value, secondpair_topval, secondpair_next_to_topval;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_pop(stk, &secondpair_topval);
    int_stack_pop(stk, &secondpair_next_to_topval);
    int_stack_push(stk, next_to_top_value);
    int_stack_push(stk, top_value);
    int_stack_push(stk, secondpair_next_to_topval);
    return int_stack_push(stk, secondpair_topval);
}

int int_stack_2dup(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int s1, s2;
    int_stack_pop(stk, &s1);
    int_stack_pop(stk, &s2);
    int_stack_push(stk, s2);
    int_stack_push(stk, s1);
    int_stack_push(stk, s2);
    return int_stack_push(stk, s1);
}

int int_stack_2drop(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    return int_stack_pop(stk, &next_to_top_value);
}

int int_stack_2over(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int s1, s2, s3, s4;
    int_stack_pop(stk, &s1);
    int_stack_pop(stk, &s2);
    int_stack_pop(stk, &s3);
    int_stack_pop(stk, &s4);
    int_stack_push(stk, s4);
    int_stack_push(stk, s3);
    int_stack_push(stk, s2);
    int_stack_push(stk, s1);
    int_stack_push(stk, s4);
    return int_stack_push(stk, s3);
}

void int_stack_print(int_stack_t *stk, FILE *file) {
    int_entry_t *entry;
    int pos = 0;
    if (stk->size == 0) {
        fprintf(file, "empty stack\n");
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        fprintf(file, "%d: %d\n", pos, entry->value);
        pos++;
    }
    printf("\n");
}
//Added new Functions for Boolean!

int int_stack_equal(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    if (top_value == next_to_top_value){
        return int_stack_push(stk, -1); //means true, they are equal *according to forth logic
    }
    return int_stack_push(stk, 0); //means false, they aren't equal *according to forth logic
}

int int_stack_greaterThan(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    if ( next_to_top_value > top_value)
    {
        return int_stack_push(stk, -1);
    }
    return int_stack_push(stk, 0);

}
int int_stack_lessThan(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    if (next_to_top_value < top_value){
        return int_stack_push(stk, -1);
    }
    return int_stack_push(stk, 0);
}
int int_stack_and(int_stack_t *stk){
    if (stk->size < 2) {
        //return 0;
    }
    int result = 1; 
    int firstValue;
    int_stack_pop(stk, &firstValue);

    
    while (stk->size > 0) {
        int currentValue;
        int_stack_pop(stk, &currentValue);
        if (currentValue != firstValue) {
            result = 0; 
            break; 
        }
    }
    
    return int_stack_push(stk, result);
   
}
int int_stack_or(int_stack_t *stk){
    if (stk->size < 2) {
        return 0;
   }
   int result = 0; 
   int firstValue;
   int_stack_pop(stk, &firstValue);

   while (stk->size > 0) {
        int currentValue;
        int_stack_pop(stk, &currentValue);
        if (currentValue == -1 || firstValue == -1) {
            result = -1; 
            break; 
        }
   }
   return int_stack_push(stk, result);
}
int int_stack_invert(int_stack_t *stk){
   int stackValue;
    int_stack_pop(stk, &stackValue); //Top of the stack should be the result from past condition

   int FunctionResult = 0; //false
   if (stackValue == -1){ //if result from condition is true then return false
       return int_stack_push(stk, FunctionResult);
   } else {
       FunctionResult = -1; //if result from condition is false then return true
   }
   return int_stack_push(stk, FunctionResult);
}

int int_stack_size(int_stack_t* stk) {
    return stk->size;
}

int int_stack_capacity(int_stack_t* stk) {
    return stk->capacity;
}

// min with recursion - This was the recursive method that Ella had created but for somereason it wouldn't run anymore after I tried adding more tests and would say that it wasn't defined.
/*

int int_stack_min_recursive_helper(int_stack_t *stk, int_entry_t *entry, int min_value) {
    if (entry == NULL) {
        return int_stack_push(stk, min_value); // Push the minimum value back to the stack
    }

    if (entry->value < min_value) {
        min_value = entry->value; // Update the minimum value if a smaller value is found
    }

    return int_stack_min_recursive_helper(stk, SLIST_NEXT(entry, entries), min_value); // Recursive call
}

int int_stack_min(int_stack_t *stk) {
    if (stk->size < 1) {
        printf("Stack has less than 1 element.\n");
        return 0; // fail
    }

    int top_value;
    if (!int_stack_top(stk, &top_value)) {
        return 0; // fail
    }

    int_entry_t *entry = SLIST_FIRST(&stk->head);
    int min_value = entry->value;

    return parse_if(int_stack_min_recursive_helper(stk, SLIST_NEXT(entry, entries), min_value), stk->size > 0); // Call the recursive helper function with the initial values
}
*/

int find_min_recursively(int_entry_t *entry, int current_min) {
    if (entry == NULL) { //goes until null at end of list
        return current_min;
    }

    if (entry->value < current_min) { //checks to see if it is lower than current and will go off if else statment
        return find_min_recursively(SLIST_NEXT(entry, entries), entry->value);
    } else {
        return find_min_recursively(SLIST_NEXT(entry, entries), current_min);
    }
}

int int_stack_min(int_stack_t *stk) {
    if (stk->size < 1) {
        printf("Stack has less than 1 element.\n");
        return 0; // fail
    }

    int top_value;
    if (!int_stack_top(stk, &top_value)) {
        return 0; // fail
    }

    int_entry_t *entry = SLIST_FIRST(&stk->head);
    int min_value = find_min_recursively(SLIST_NEXT(entry, entries), entry->value); //made it so that the recursive method went into the variable and then got pushed in return

    return int_stack_push(stk, min_value); // success only if last operation succeeds
}

// max

int int_stack_max_recursive_helper(int_stack_t *stk, int_entry_t *entry, int max_value) {
    if (entry == NULL) {
        return int_stack_push(stk, max_value); // success only if last operation succeeds
    }

    if (entry->value > max_value) {
        max_value = entry->value;
    }

    return int_stack_max_recursive_helper(stk, SLIST_NEXT(entry, entries), max_value);
}

int int_stack_max(int_stack_t *stk) {
    if (stk->size < 1) {
        printf("Stack has less than 1 element.\n");
        return 0; // fail
    }

    int top_value;
    if (!int_stack_top(stk, &top_value)) {
        return 0; // fail
    }

    int_entry_t *entry = SLIST_FIRST(&stk->head);
    int max_value = entry->value;

    return int_stack_max_recursive_helper(stk, SLIST_NEXT(entry, entries), max_value);
}

// abs

int int_stack_abs(int_stack_t *stk) {
    if (stk->size < 1) {
        printf("Stack has less than 1 element.\n");
        return 0; // fail
    }

    int top_value;
    if (!int_stack_top(stk, &top_value)) {
        return 0; // fail
    }

    int abs_value = abs(top_value);
    int_stack_pop(stk, &top_value);
    return int_stack_push(stk, abs_value); // success only if last operation succeeds
}

// negate

int int_stack_negate(int_stack_t *stk) {
    if (stk->size < 1) {
        printf("Stack has less than 1 element.\n");
        return 0; // fail
    }

    int top_value;
    if (!int_stack_top(stk, &top_value)) {
        return 0; // fail
    }

    int negated_value = -(top_value);
    int_stack_pop(stk, &top_value); //Remove the original top value from stack
    return int_stack_push(stk, negated_value); // success only if last operation succeeds
}

// floor
int int_stack_floor(int_stack_t *stk) {
    if (stk->size < 1) {
        printf("Stack has less than 1 element.\n");
        return 0; // fail
    }
    int top_value;
    if (!int_stack_top(stk, &top_value)) {
        return 0; // fail
    }
    int floor_value = floor(top_value);
    return int_stack_push(stk, floor_value); // success only if last operation succeeds
}

// ceil
int int_stack_ceil(int_stack_t *stk) {
    if (stk->size < 1) {
        printf("Stack has less than 1 element.\n");
        return 0; // fail
    }

    int top_value;
    if (!int_stack_top(stk, &top_value)) {
        return 0; // fail
    }

    int ceil_value = ceil(top_value);
    return int_stack_push(stk, ceil_value); // success only if last operation succeeds
}

// pick
int int_stack_pick(int_stack_t *stk) {
    if (stk->size < 1) {
        printf("Stack has less than 1 element.\n");
        return 0; // fail
    }

    int top_value;
    if (!int_stack_top(stk, &top_value)) {
        return 0; // fail
    }

    return int_stack_push(stk, top_value); // success only if last operation succeeds
}

// pickn 

int int_stack_pickn(int_stack_t *stk, int n) {
    if (stk->size < n + 1) {
        printf("Stack does not have enough elements for pickn.\n");
        return 0; // fail
    }

    int_entry_t *entry = SLIST_FIRST(&stk->head);
    for (int i = 0; i < n; i++) {
        entry = SLIST_NEXT(entry, entries);
        if(i==n){
                int picked_value = entry->value;
        }
    }

    int picked_value = entry->value;
    return int_stack_push(stk, picked_value); // success only if last operation succeeds
}

//depth

int int_stack_depth(int_stack_t* stk) {
    int depth = int_stack_size(stk); //gets size of stack even when stack is empty it adds 0 to stack like gforth
    return int_stack_push(stk, depth);
}

// repeat

int int_stack_repeat(int_stack_t *stk, int n) {
    if (stk->size < 1) {
        printf("Stack has less than 1 element.\n");
        return 0; // fail
    }

    int top_value;
    if (!int_stack_top(stk, &top_value)) {
        return 0; // fail
    }

    for (int i = 0; i < n; i++) {
        if (!int_stack_push(stk, top_value)) {
            return 0; // fail
        }
    }

    return 1; // success
}

// loop - with push n number of times

int int_stack_loop(int_stack_t *stk, int n) {
    if (n <= 0) {
        printf("Invalid loop count.\n");
        return 0; // fail
    }

    for (int i = 0; i < n; i++) {
        int top_value;
        if (!int_stack_top(stk, &top_value)) {
            return 0; // fail
        }
        if (!int_stack_push(stk, top_value)) {
            return 0; // fail
        }
    }

    return 1; // success
}
