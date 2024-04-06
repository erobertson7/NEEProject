#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"
#include "token.c"

void tokenize_input() {
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, stdin) != -1) {
        char *token_str = strtok(line, " \t\n");
        while (token_str != NULL) {
            token_type_t type;
            if (isdigit(token_str[0])) {
                type = NUMBER;
            } else if (strchr("+-*/", token_str[0]) != NULL) {
                type = OPERATOR;
            } else if (strchr(":;", token_str[0]) != NULL) {
                type = SYMBOL;
            } else {
                type = WORD;
            }

            token_t *token = create_token(type, token_str);
            printf("TYPE: %d\nINPUT: %s\n\n", token->type, token->text);

            token_str = strtok(NULL, " \t\n");
            free_token(token);
        }
    }

    free(line);
}

int main() {
    tokenize_input();

    return 0;
}

