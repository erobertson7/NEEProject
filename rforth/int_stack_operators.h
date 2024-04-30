// int_stack.h - interface to the int_stack

#ifndef INT_STACK_H
#define INT_STACK_H

#include <stdio.h>
#include <sys/queue.h>

typedef struct int_entry {
    int value;
    SLIST_ENTRY(int_entry) entries;
} int_entry_t;

typedef struct int_stack {
    SLIST_HEAD(stackhead, int_entry) head;
    int size;
    int capacity;
} int_stack_t;

extern void int_stack_init(int_stack_t *stk, int capacity);
extern int int_stack_push(int_stack_t *stk, int value);
extern int int_stack_pop(int_stack_t *stk, int *top_value);
extern int int_stack_top(int_stack_t *stk, int *top_value);
extern int int_stack_dup(int_stack_t *stk);
extern int int_stack_swap(int_stack_t *stk);
extern int int_stack_add(int_stack_t *stk);
extern void int_stack_print(int_stack_t *stk, FILE *file);
extern int int_stack_size(int_stack_t* stk);
extern int int_stack_capacity(int_stack_t* stk);
//added new tests here
extern int int_stack_subtract(int_stack_t *stk);
extern int int_stack_multiply(int_stack_t *stk);
extern int int_stack_div(int_stack_t *stk);
extern int int_stack_mod(int_stack_t *stk);
extern int int_stack_dividemod(int_stack_t *stk);
extern int int_stack_over(int_stack_t *stk);
extern int int_stack_rot(int_stack_t *stk);
extern int int_stack_drop(int_stack_t *stk);
extern int int_stack_2swap(int_stack_t *stk);
extern int int_stack_2dup(int_stack_t *stk);
extern int int_stack_2drop(int_stack_t *stk);
extern int int_stack_2over(int_stack_t *stk);
//testing conditionals here (boolean expressions)
extern int int_stack_equal(int_stack_t *stk);
extern int int_stack_lessThan(int_stack_t *stk);
extern int int_stack_greaterThan(int_stack_t *stk);
extern int int_stack_and(int_stack_t *stk);
extern int int_stack_or(int_stack_t *stk);
extern int int_stack_invert(int_stack_t *stk);
extern int int_stack_negate(int_stack_t *stk);
extern int int_stack_depth(int_stack_t *stk);
//Working on Tests for those below currently!
extern int int_stack_min(int_stack_t *stk);
extern int int_stack_max(int_stack_t *stk);
extern int int_stack_floor(int_stack_t *stk);
extern int int_stack_ceil(int_stack_t *stk);
extern int int_stack_abs(int_stack_t *stk);
extern int int_stack_pickn(int_stack_t *stk, int n);
extern int int_stack_pick(int_stack_t *stk);
extern int int_stack_loop(int_stack_t *stk, int n);
extern int int_stack_repeat(int_stack_t *stk, int n);
#endif // INT_STACK_H
