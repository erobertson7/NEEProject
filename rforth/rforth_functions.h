#ifndef RFORTH_H
#define RFORTH_H

#include <stdio.h>
#include <sys/queue.h>
#include <stdbool.h>

// ELLA'S

typedef enum {
    NUMBER,
    OPERATOR,
    SYMBOL,
    WORD,
    INTEGER,
    STRING,
    BOOLEAN,
    IF,
    DUP,
    COMPARISON_OPERATOR
} token_type_t;

typedef struct token {
    token_type_t type;
    char *text;
    struct token *next;
} token_t;

token_t* create_token(token_type_t type, const char *text);
void free_token(token_t *token);
token_t* duplicate_token(token_t* token);
token_t* handle_dup(token_t* tokens);
void repl_support();
void evaluate(token_t* tokens);
bool evaluate_condition(token_t* tokens);
int compare_values(token_t* token1, token_t* token2);
void free_tokens(token_t* tokens);

// ELLA'S


// NANCY'S

// int_stack.h - interface to the int_stack

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

// NANCY'S

#endif /* REPL_H */
