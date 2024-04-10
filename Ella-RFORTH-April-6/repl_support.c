#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"
#include "repl_support.h"
#include <stdio.h>

// taken from token.c
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

// end of taken from token.c

// THIS IS NOT WORKING RIGHT NOW!!!!!!!!!!!!!!!!!!!!!

token_t* duplicate_token(token_t* token) {
  return create_token(token->type, token->text);
}

token_t* handle_dup(token_t* tokens) {
  if (tokens == NULL || tokens->next == NULL || tokens->next->type != DUP) {
    return tokens;
  }
  tokens = tokens->next;
  token_t* dup_token = duplicate_token(tokens->next);
  dup_token->next = tokens->next->next;
  tokens->next->next = dup_token;
  return tokens->next->next;
}

void repl_support() {
  while(1) {
    char buffer[1024];
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

bool evaluate_condition(token_t* tokens) {
  if (tokens == NULL) {
    return false;  
  }
  if (tokens->type == STRING) {
    token_t* next = tokens->next;
    if (next != NULL && next->type == COMPARISON_OPERATOR) {
      if (next->next != NULL) {
        int result = compare_values(tokens, next->next);
        if (strcmp(next->text, "<") == 0) {
          return result < 0;
        } else if (strcmp(next->text, ">") == 0) {
          return result > 0;
        } else if (strcmp(next->text, "==") == 0) {
          return result == 0;
        } else if (strcmp(next->text, "!=") == 0) {
          return result != 0;
        }
      }
    }
  }
}

int compare_values(token_t*