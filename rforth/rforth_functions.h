//this is an interface
#ifndef _RFORTHFUNCTIONS_H_
#define _RFORTHFUNCTIONS_H_

#include <stdio.h>
#include "int_stack_operators.h"

typedef enum token_type_t {
    NUMBER,
    OPERATOR,
    SYMBOL,
    WORD,
    BOOLEAN,
    PRINT_STK,
    IF,
    UNKOWN

} token_type_t;

typedef struct token_t {
    token_type_t type;
    char* text;
    //truct token *next;
} token_t;
/*
token_t* create_token(token_type_t type, const char *text);
void free_token(token_t *token);
token_t* duplicate_token(token_t* token);
token_t* handle_dup(token_t* tokens);
void repl_support();
void evaluate(token_t* tokens);
bool evaluate_condition(token_t* tokens);
int compare_values(token_t* token1, token_t* token2);
void free_tokens(token_t* tokens);

*/
extern void separate_token(int_stack_t *stk, char *text, char* stringList[], int *intList);
extern token_type_t get_token_type(const char* token);
extern token_t* intialize_token(token_type_t type, const char* text);
extern void print_forth(int_stack_t *stk);

#endif