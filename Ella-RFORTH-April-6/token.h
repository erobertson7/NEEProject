#ifndef _RFORTH_TOKEN_H_
#define _RFORTH_TOKEN_H_

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

typedef struct {
    token_type_t type;
    char* text;
    struct token_t* next;
} token_t;

token_t* create_token(token_type_t type, const char *text);
token_t* duplicate_token(token_t* tokens);
token_t* handle_dup(token_t* tokens);
void free_token(token_t *token);

void repl_support();
bool evaluate_condition(token_t* tokens);
int co