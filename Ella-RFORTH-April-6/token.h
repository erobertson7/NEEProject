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
    COMPARISON_OPERATOR
} token_type_t;

typedef struct {
    token_type_t type;
    char* text;
    struct token_t* next;
} token_t;

token_t* create_token(token_type_t type, const char *text);
void free_token(token_t *token);

void repl_support();
bool evaluate_condition(token_t* tokens);
int compare_values(token_t* token1, token_t* token2);
void free_tokens(token_t* tokens);

#endif