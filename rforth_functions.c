// Ella's Existing Code
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

// Erin's Existing Code
// int_stack.c

#include "int_stack.h"

#include <stdlib.h>
#include <stdio.h>

int varCount 0;
void int_stack_init(int_stack_t *stk, int capacity) {
    SLIST_INIT(&stk->head);
    stk->size = 0;
    stk->capacity = capacity;
}

int int_stack_push(int_stack_t *stk, int value) {
    if (stk->size >= stk->capacity) {
        printf("Stack is at full capacity.\n");
        return 0; // fail
    }

    int_entry_t *newEntry = malloc(sizeof(int_entry_t));
    if (newEntry) {
        newEntry->value = value;
        SLIST_INSERT_HEAD(&stk->head, newEntry, entries);
        stk->size++;
        return 1; //success
    }
    return 0; // fail
}

int int_stack_pop(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        int value = entry->value;
        SLIST_REMOVE_HEAD(&stk->head, entries);
        free(entry);
        stk->size--;
        *top_value = value;
        return 1; // success
    }
    return 0; // fail
}

int int_stack_top(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        *top_value = entry->value;
        return 1; // success
    }
    return 0; // fail
}

/* Functions for FORTH langauge stack operators */

int int_stack_dup(int_stack_t *stk) {
    if (stk->size < 1)
        return 0;
    int top_value;
    int_stack_top(stk, &top_value);
    return int_stack_push(stk, top_value); // success only if last operation succeeds
}

int int_stack_swap(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value); // success only if last operation succeeds
}

int int_stack_over(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_push(stk, next_to_top_value);
    return int_stack_push(stk, top_value);
}

int int_stack_rot(int_stack_t *stk){
    if(stk->size < 2)
        return 0;
    int temp, top_value, next_to_top_value, third_to_top_value;
    temp = top_value;
    top_value = next_to_top_value;
    next_to_top_value = third_to_top_value;
    third_to_top_value = temp;
    int_stack_push(stk, third_to_top_value);
    int_stack_push(stk, next_to_top_value);
    return int_stack_push(stk, top_value);
}

int int_stack_drop(int_stack_t *stk){
    int top_value;
    int_stack_pop(stk, &top_value);
}

int int_stack_2swap(int_stack_t *stk){
    if (stk->size < 3)
        return 0;
    int temp, top_value, next_to_top_value, third_to_top_value, forth_to_top_value;
    temp = top_value;
    top_value = third_to_top_value;
    third_to_top_value = temp;
    temp = next_to_top_value;
    next_to_top_value = forth_to_top_value;
    forth_to_top_value = temp;
    int_stack_push(stk, forth_to_top_value);
    int_stack_push(stk, third_to_top_value);
    int_stack_push(stk, next_to_top_value);
    return int_stack_push(stk, top_value);
}

int int_stack_2dup(int_stack_t *stk){
    if(stk->size > 1)
        return 0;
    int top_value, next_to_top_value;
    int_stack_push(stk, next_to_top_value);
    return int_stack_push(stk, top_value;)
}

int int_stack_2over(int_stack_t *stk){
    if(stk->size < 4)
        return 0;
    int third_to_top_value, forth_to_top_value;
    int_stack_push(stk,third_to_top_value);
    return int_stack_push(stk,forth_to_top_value);
}

int int_stack_2drop(int_stack_t *stk){
    if(stk->size < 2)
        return 0;
    int_stack_pop(stk,&top_value);
    int_stack_pop(stk,&top_value);
}

/* Example of how to create a binary operator that works o top two elements (if present) */

int int_stack_add(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value + next_to_top_value);
}

int int_stack_sub(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, next_to_top_value - top_value);
}

int int_stack_mul(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value * next_to_top_value);
}

int int_stack_div(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    if (top_value == 0) {
        return 0;
    }
    return int_stack_push(stk, next_to_top_value / top_value);
}

int int_stack_divmod(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int divisor, dividend;
    int_stack_pop(stk, &divisor);
    int_stack_pop(stk, &dividend);
    if (divisor == 0) {
        return 0;
    }
    int quotient = dividend / divisor;
    int remainder = dividend % divisor;
    int_stack_push(stk, remainder);
    return int_stack_push(stk, quotient);
}

int int_stack_mod(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int divisor, dividend;
    int_stack_pop(stk, &divisor);
    int_stack_pop(stk, &dividend);
    if (divisor == 0) {
        return 0;
    }
    return int_stack_push(stk, dividend % divisor);
}

int int_stack_less_than(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value < top_value);
}

int int_stack_equals(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value == top_value);
}

int int_stack_greater_than(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value > top_value);
}

int int_stack_less_than_equal_to(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value <= top_value);
}

int int_stack_greater_than_equal_to(int_stack_t *stk){
    if (stk->size < 2)
        return 0;
    int top_value, second_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &second_value);

    return int_stack_push(stk, second_value >= top_value);
}

int int_stack_set_var(const char* name, int value, int isConstant) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            if (vars[i].isConstant) {
                return 0;
            }
            vars[i].value = value;
            return 1;
        }
    }
    if (varCount >= MAX_VARS) {
        return 0;
    }
    strcpy(vars[varCount].name, name);
    vars[varCount].value = value;
    vars[varCount].isConstant = isConstant;
    varCount++;
    return 1;
}

int int_stack_get_var(const char* name, int* value) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(vars[i].name, name) == 0) {
            *value = vars[i].value;
            return 1;
        }
    }
    return 0;
}

void int_stack_print(int_stack_t *stk, FILE *file) {
    int_entry_t *entry;
    int pos = 0;
    if (stk->size == 0) {
        fprintf(file, "empty stack\n");
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        fprintf(file, "%d: %d\n", pos, entry->value);
        pos++;
    }
    printf("\n");
}

int int_stack_size(int_stack_t* stk) {
    return stk->size;
}

int int_stack_capacity(int_stack_t* stk) {
    return stk->capacity;
}

// Nancy's Existing Code
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "int_stack.h"
#include <string.h>

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