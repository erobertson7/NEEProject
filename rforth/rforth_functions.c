#include <stdio.h>
#include <stdlib.h>
#include "rforth_functions.h"
#include <ctype.h>
#include <string.h>
#include "int_stack_operators.h"

token_t* intialize_token(token_type_t type, const char* text){
    token_t* newToken = (token_t*)malloc(sizeof(token_t));
    if (newToken == NULL) {
        return NULL;
    }
}

token_type_t get_token_type(const char* token){
    if (*token == '+' || *token == '-' || *token == '*' || *token == '/') {
        /*if (*token == '-') {
            const char* p = token + 1; 
            while (*p) {
                if (isdigit((unsigned char)*p)) {
                    return WORD;
                }
                p++;
            }
            return NEG_NUMBER;
        }*/
        return OPERATOR;
    }else if (*token == '.'){
        return PRINT_STK;
    } else if (*token == ';' || *token == ':'){
        return SYMBOL;
    } else if (*token == '=' || *token == '<' || *token == '>' || strcmp(token, "and") == 0 || strcmp(token, "or")==0 || strcmp(token, "invert")==0){
        return BOOLEAN;
    }else if (isdigit((unsigned char)*token)){
        const char* p = token + 1; 
        while (*p) {
            if (!isdigit((unsigned char)*p)) {
                
                return WORD;
            }
            p++;
        }
        return NUMBER;
    } else {
        return WORD;
    }
}

const char* token_type_to_string(token_type_t type) {
    switch (type) {
        case OPERATOR:
            return "OPERATOR";
        case NUMBER:
            return "NUMBER";
        case SYMBOL:
            return "SYMBOL";
        case WORD:
            return "WORD";
        case BOOLEAN:
            return "BOOLEAN";
        case PRINT_STK:
            return "PRINT_STK";
        case IF:
                return "IF";
        default:
            return "UNKOWN";
    }
}

void print_forth(int_stack_t *stk){
    int_entry_t *entry;
    int elements[stk->size]; 
    int i = 0;
    int pos = 0;
    if (stk->size == 0) { //if stack is empty then it's not printed and the message is only printed
        printf("  ok?\n"); //I have the question mark to distinguish it in testing it to make more like forth
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        if (i < stk->size) { 
            elements[i++] = entry->value;
        }
    }

    if (stk->size > 0) { //if at least 1 element is in the stack it gets printed
        printf("stack: ");
        for (i = stk->size - 1; i >= 0; i--) {
            printf("%d ", elements[i]);
        }
        printf("<- top\n");
    }
    
}



void separate_token(int_stack_t *stk, char *text, char* stringList[], int *intList) {
      
    const char *space = " ";
    char *token;
    char *rest = text;

    while ((token = strtok_r(rest, space, &rest))) {
        token_type_t type = get_token_type(token);
        
        if (type == NUMBER) {
            int_stack_push(stk, atoi(token)); //turns character into integer
            //use -> *token makes the stack print out the ASCII form of the digits
        }else if (type == PRINT_STK){ //This makes it so that when '.' is entered it pushes out the number
            int top_value;
            if(stk->size >= 1){
                 if (strcmp(token, ".")==0){
                    int_stack_pop(stk, &top_value);
                    printf(". %d", top_value); //prints . digit ok (ok is from print_forth)
                    printf("  ok\n");
                } //April 21: Trying to get this to print on the same line as input "."
            } else if (stk->size == 0){
                if (strcmp(token, ".")==0){
                    printf("Stack underflow?\n");
                }
            }
        }else if (type == OPERATOR) {
            int top_value;
            if (stk->size >= 2){     
                if (strcmp(token, "+") == 0) {        
                    int_stack_add(stk);
                } else if (strcmp(token, "-") == 0) {
                    int_stack_subtract(stk);
                } else if (strcmp(token, "*") == 0){
                    int_stack_multiply(stk);
                } else if (strcmp(token, "/mod")==0){
                    int_stack_dividemod(stk);
                }else {
                    int_stack_div(stk);
                } 
            }
            else {
                //int_stack_pop(stk, &top_value);
                printf("Stack underflow\n");
                
            } 
        } else if (type == WORD){
            int top_value;
            if (strcmp(token, "over")==0){
                int_stack_over(stk);
            } else if (strcmp(token, "drop")==0){
                int_stack_pop(stk, &top_value);
            } else if (strcmp(token, "rot")==0){
                int_stack_rot(stk);
            } else if (strcmp(token, "dup")==0){
                int_stack_dup(stk);
            } else if (strcmp(token, "swap")==0){
                int_stack_swap(stk);
            } else if (strcmp(token, "2swap")==0){
                int_stack_2swap(stk);
            } else if (strcmp(token, "2dup")==0){
                int_stack_2dup(stk);
            } else if (strcmp(token, "2over")==0){
                int_stack_2over(stk);
            } else if (strcmp(token, "2drop")==0){
                int_stack_pop(stk, &top_value);
                int_stack_pop(stk, &top_value);
            } else if (strcmp(token, "mod")==0){
                int_stack_mod(stk);
            } else if (strcmp(token, "variable")==0){
                //need to figure out
            } else if (strcmp(token, "negate")==0){
                int_stack_negate(stk);
            }
            else if (strcmp(token, "depth")==0){
                int_stack_depth(stk);
            }
            else if(strcmp(token, "min")==0){
                int_stack_min(stk);
            }
            else if(strcmp(token, "max")==0){
                int_stack_max(stk);
            }
            else if(strcmp(token, "ceil")==0){
                int_stack_ceil(stk);
            }
            else if(strcmp(token, "floor")==0){
                int_stack_floor(stk);
            }
            else if(strcmp(token, "abs")==0){
                //int_stack_abs(stk);
            }
        } else if (type == BOOLEAN){
            
            //char *next_token = strtok_r(rest, space, &rest);
            //char *third_token = strtok_r(rest, space, &rest);
            if (strcmp(token, "=")==0) {
                int_stack_push(stk, int_stack_equal(stk));
                //printf("%d\n", int_stack_equal(stk));
            } else if (strcmp(token, "<") == 0) {
                //printf("%d\n", int_stack_lessThan(stk));
                int_stack_push(stk, int_stack_lessThan(stk));
            } else if (strcmp(token, ">") == 0){
                int_stack_push(stk, int_stack_greaterThan(stk));
            }

            if (strcmp(token, "and") == 0){                
                int_stack_and(stk); //still figuring out 
            } else if (strcmp(token, "or")==0){
                int_stack_or(stk); //still figuring out 
            } else if (strcmp(token, "invert")==0){
                int_stack_invert(stk); //not working right
            }
        }
    }

}