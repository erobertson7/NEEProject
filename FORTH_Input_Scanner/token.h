#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_TYPE_UNKNOWN,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_DELIMITER
} token_type_t;

typedef struct {
    token_type_t type;
    char *text;
} token_t;

token_t *get_next_token(FILE *input_stream);
void free_token(token_t *token);

#endif /* TOKEN_H */
