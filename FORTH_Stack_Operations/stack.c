// int_stack.c

#include "int_stack.h"

#include <stdlib.h>
#include <stdio.h>

int varCount 0;
void int_stack_init(int_stack_t *stk, int capacity) {
    SLIST_INIT(&stk->head);
    stk->size = 0;
    stk->capacity = capacity;
}

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

int int_stack_over(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_push(stk, next_to_top_value);
    return int_stack_push(stk, top_value);
}

int int_stack_rot(int_stack_t *stk){
    if(stk->size < 2)
        return 0;
    int temp, top_value, next_to_top_value, third_to_top_value;
    temp = top_value;
    top_value = next_to_top_value;
    next_to_top_value = third_to_top_value;
    third_to_top_value = temp;
    int_stack_push(stk, third_to_top_value);
    int_stack_push(stk, next_to_top_value);
    return int_stack_push(stk, top_value);
}

int int_stack_drop(int_stack_t *stk){
    int top_value;
    int_stack_pop(stk, &top_value);
}

int int_stack_2swap(int_stack_t *stk){
    if (stk->size < 3)
        return 0;
    int temp, top_value, next_to_top_value, third_to_top_value, forth_to_top_value;
    temp = top_value;
    top_value = third_to_top_value;
    third_to_top_value = temp;
    temp = next_to_top_value;
    next_to_top_value = forth_to_top_value;
    forth_to_top_value = temp;
    int_stack_push(stk, forth_to_top_value);
    int_stack_push(stk, third_to_top_value);
    int_stack_push(stk, next_to_top_value);
    return int_stack_push(stk, top_value);
}

int int_stack_2dup(int_stack_t *stk){
    if(stk->size > 1)
        return 0;
    int top_value, next_to_top_value;
    int_stack_push(stk, next_to_top_value);
    return int_stack_push(stk, top_value;)
}

int int_stack_2over(int_stack_t *stk){
    if(stk->size < 4)
        return 0;
    int third_to_top_value, forth_to_top_value;
    int_stack_push(stk,third_to_top_value);
    return int_stack_push(stk,forth_to_top_value);
}

int int_stack_2drop(int_stack_t *stk){
    if(stk->size < 2)
        return 0;
    int_stack_pop(stk,&top_value);
    int_stack_pop(stk,&top_value);
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

int int_stack_sub(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value - top_value);
}

int int_stack_mul(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value * next_to_top_value);
}

int int_stack_div(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    if (top_value == 0) {
        return 0;
    }
    return int_stack_push(stk, next_to_top_value / top_value);
}

int int_stack_divmod(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int divisor, dividend;
    int_stack_pop(stk, &divisor);
    int_stack_pop(stk, &dividend);
    if (divisor == 0) {
        return 0;
    }
    int quotient = dividend / divisor;
    int remainder = dividend % divisor;
    int_stack_push(stk, remainder);
    return int_stack_push(stk, quotient);
}

int int_stack_mod(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int divisor, dividend;
    int_stack_pop(stk, &divisor);
    int_stack_pop(stk, &dividend);
    if (divisor == 0) {
        return 0;
    }
    return int_stack_push(stk, dividend % divisor);
}

int int_stack_less_than(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value < top_value);
}

int int_stack_equals(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value == top_value);
}

int int_stack_greater_than(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value > top_value);
}

int int_stack_less_than_equal_to(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value <= top_value);
}

int int_stack_greater_than_equal_to(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value >= top_value);
}

int int_stack_set_var(const char* name, int value, int isConstant) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            if (vars[i].isConstant) {
                return 0;
            }
            vars[i].value = value;
            return 1;
        }
    }
    if (varCount >= MAX_VARS) {
        return 0;
    }
    strcpy(vars[varCount].name, name);
    vars[varCount].value = value;
    vars[varCount].isConstant = isConstant;
    varCount++;
    return 1;
}

int int_stack_get_var(const char* name, int* value) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            *value = vars[i].value;
            return 1;
        }
    }
    return 0;
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

int int_stack_size(int_stack_t* stk) {
    return stk->size;
}

int int_stack_capacity(int_stack_t* stk) {
    return stk->capacity;
}