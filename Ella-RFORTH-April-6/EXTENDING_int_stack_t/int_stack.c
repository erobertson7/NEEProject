#include "int_stack.h"

#include <stdlib.h>
#include <stdio.h>

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

// ADDITION (moved from George's source code)
int int_stack_add(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value + next_to_top_value);
}

// SUBTRACTION
int int_stack_subtract(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value - top_value);
}

// MULTIPLICATION
int int_stack_multiply(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value * top_value);
}

// DIVISION
int int_stack_div(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    if (top_value == 0) {
        printf("Cannot divide by 0.\n");
        return 0;
    }
    return int_stack_push(stk, next_to_top_value / top_value);
}

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

// OVER
int int_stack_over(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int second_value;
    int_stack_peek(stk, 1, &second_value);
    return int_stack_push(stk, second_value);
}

// ROT
int int_stack_rot(int_stack_t *stk) {
    if(stk->size < 3)
        return 0;
    int top_value, middle_value, bottom_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &middle_value);
    int_stack_pop(stk, &bottom_value);
    int_stack_push(stk, middle_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, bottom_value);
}

// DROP
int int_stack_drop(int_stack_t *stk) {
    int dummy;
    return int_stack_pop(stk, &dummy);
}

// 2SWAP
int int_stack_2swap(int_stack_t *stk) {
    if (stk->size < 4)
        return 0;
    int temp [4];
    for (int i = 0; i < 4; i++) {
        int_stack_pop(stk, &temp[i]);
    }
    int_stack_push(stk, temp[2]);
    int_stack_push(stk, temp[3]);
    int_stack_push(stk, temp[0]);
    int_stack_push(stk, temp[1]);
    return 1;
}

// 2DUP
int int_stack_2dup(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_top(stk, &top_value);
    int_stack_peek(stk, 1, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value) && int_stack_push(stk, top_value);
}

// 2OVER
int int_stack_2over(int_stack_t *stk) {
    if (stk->size < 3)
        return 0;
    int second_value, third_value;
    int_stack_peek(stk, 1, &second_value);
    int_stack_peek(stk, 2, &third_value);
    return int_stack_push(stk, third_value) && int_stack_push(stk, second_value);
}

// 2DROP
int int_stack_2drop(int_stack_t *stk) {
    int dummy1, dummy2;
    return int_stack_pop(stk, &dummy1) && int_stack_pop(stk, &dummy2);
}

/* Example of how to create a binary operator that works o top two elements (if present) */

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
