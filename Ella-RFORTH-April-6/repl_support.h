#ifndef REPL_H
#define REPL_H

#include <stdbool.h>
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

#endif /* REPL_H */
