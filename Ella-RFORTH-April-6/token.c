#include <stdlib.h>
#include <string.h>
#include "token.h"

token_t* create_token(token_type_t type, const char *text) {
    token_t *token = (token_t*)malloc(sizeof(token_t));
    if (token == NULL) {
        exit(EXIT_FAILURE);
    }

    token->type = type;
    token->text = strdup(text);
    if (token->text == NULL) {
        free(token);
        exit(EXIT_FAILURE);
    }

    return token;
}

void free_token(token_t *token) {
    free(token->text);
    free(token);
}
