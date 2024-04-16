#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "rforth_functions.h"

// ELLA'S
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

    if (strcmp(text, "true") == 0) {
      type = BOOLEAN;
      } else if (strcmp(text, "false") == 0) {
        type = BOOLEAN;
      }

    return token;
}


void free_token(token_t *token) {
    free(token->text);
    free(token);
}


token_t* duplicate_token(token_t* token) {
    return create_token(token->type, token->text);
}

token_t* handle_dup(token_t* tokens) {
    if (tokens == NULL || tokens->next == NULL || tokens->next->type != DUP) {
        return tokens;
    }

    token_t* dup_token = duplicate_token(tokens->next->next);
    dup_token->next = tokens->next->next;
    tokens->next->next = dup_token;

    return tokens;
}


void repl_support() {
    while (1) {
        char buffer[1024];
        printf("> ");
        fgets(buffer, sizeof(buffer), stdin);
        if (buffer[0] == 'q') {
            return;
        }
        token_t* tokens = tokenize(buffer);
        evaluate(tokens);
        free_tokens(tokens);
    }
}



void evaluate(token_t* tokens) {
  while (tokens != NULL) {
    switch (tokens->type) {
      case INTEGER:
        printf("Integer: %s\n", tokens->text);
        break;
      case STRING:
        printf("String: %s\n", tokens->text);
        break;
      case BOOLEAN:
        break;
      case IF:
        tokens = tokens->next; 
        if (evaluate_condition(tokens)) { 
          tokens = tokens->next;
          evaluate(tokens);
        } else {
          while (tokens != NULL && tokens->type != IF) {
            tokens = tokens->next;
          }
        }
        break;
        
      default:
          printf("Try again.\n");
      }
      tokens = tokens->next;
    }
    printf("> ");
    char buffer[1024];
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] == 'q') {
        return;
    }
    tokens = tokenize(buffer);
}

void evaluate(token_t* tokens) {
    while (tokens != NULL) {
        switch (tokens->type) {
            case INTEGER:
                printf("Integer: %s\n", tokens->text);
                break;
            case STRING:
                printf("String: %s\n", tokens->text);
                break;
            case BOOLEAN:
                break;
            case IF:
                tokens = tokens->next; 
                if (evaluate_condition(tokens)) { 
                    tokens = tokens->next;
                    evaluate(tokens);
                } else {
                    while (tokens != NULL && tokens->type != IF) {
                        tokens = tokens->next;
                    }
                }
                break;
            default:
                printf("Try again.\n");
        }
        tokens = tokens->next;
    }
}

int compare_values(token_t* token1, token_t* token2) {
  if (token1->type == INTEGER && token2->type == INTEGER) {
    return atoi(token1->text) - atoi(token2->text);
  } else if (token1->type == STRING && token2->type == STRING) {
    return strcmp(token1->text, token2->text);
  }
  return 0;
}


void free_tokens(token_t* tokens) {
  while (tokens != NULL) {
    token_t* next = tokens->next;
    free_token(tokens);
    tokens = next;
  }
}

int main() {
  repl_support();
  return EXIT_SUCCESS;
}

// ELLA'S


// NANCY'S

int_stack_t myStack;
const int capacity = 30;
const int var_capacity = 100;

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int_stack_init(&myStack, capacity);

    char* stringList[var_capacity];
    int intList[var_capacity];
    for (int i = 0; i < var_capacity; i++) {
        stringList[i] = NULL;
        intList[i] = 0;
    }

    printf("Type 'bye' to exit\n");

    while ((read = getline(&line, &len, stdin)) != -1) {
        
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }
        
        if (strcmp(line, "bye") == 0) {
            break;
        }

        separate_token(&myStack, line, stringList, intList); 
        print_forth(&myStack);
    }

    

    free(line);
    return 0;
}

// NANCY'S