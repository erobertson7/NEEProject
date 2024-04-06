#ifndef _FORTH_REPL_H_
#define _FORTH_REPL_H_
#include "token.h"

void repl_support();
void test_if_true_condition();
void test_if_false_condition();
void evaluate(token_t* tokens);
void free_tokens(token_t* tokens);

#endif