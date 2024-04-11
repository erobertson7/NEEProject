#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

token_t *get_next_token(FILE *input_stream) {
    token_t *token = (token_t *)malloc(sizeof(token_t));
    if (token == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    char buffer[100]; // Adjust the size according to your needs
    int c;
    int index = 0;

    // Skip whitespace characters
    while ((c = fgetc(input_stream)) != EOF && isspace(c));

    // Determine token type
    if (c == EOF) {
        token->type = TOKEN_TYPE_UNKNOWN;
        token->text = NULL;
        return token;
    }
    else if (isalpha(c)) {
        token->type = TOKEN_TYPE_IDENTIFIER;
    }
    else if (isdigit(c)) {
        token->type = TOKEN_TYPE_NUMBER;
    }
    else {
        token->type = TOKEN_TYPE_OPERATOR; // Assuming all non-alphanumeric characters are operators
    }

    // Read token text
    buffer[index++] = c;
    while ((c = fgetc(input_stream)) != EOF && !isspace(c)) {
        buffer[index++] = c;
    }
    buffer[index] = '\0';

    token->text = strdup(buffer);
    if (token->text == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    return token;
}

void free_token(token_t *token) {
    if (token != NULL) {
        free(token->text);
        free(token);
    }
}
