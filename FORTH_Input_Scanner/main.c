#include <stdio.h>
#include "token.h"

int main() {
    printf("Enter text (Ctrl+D to end):\n");

    token_t *token;
    while ((token = get_next_token(stdin))->type != TOKEN_TYPE_UNKNOWN) {
        const char *token_class;
        switch (token->type) {
            case TOKEN_TYPE_KEYWORD:
                token_class = "Keyword";
                break;
            case TOKEN_TYPE_IDENTIFIER:
                token_class = "Identifier";
                break;
            case TOKEN_TYPE_NUMBER:
                token_class = "Number";
                break;
            case TOKEN_TYPE_OPERATOR:
                token_class = "Operator";
                break;
            case TOKEN_TYPE_DELIMITER:
                token_class = "Delimiter";
                break;
            default:
                token_class = "Unknown";
        }

        printf("Class: %s, Text: %s\n", token_class, token->text);
        free_token(token);
    }

    return 0;
}
