#include "gtest/gtest.h"
#include "repl_support.h"
#include "token.h"

// INTEGER

TEST(TokenTest, IntegerToken) {
    token_t *token = create_token(INTEGER, "29");
    ASSERT_NE(token, nullptr);
    EXPECT_EQ(token->type, INTEGER);
    EXPECT_STREQ(token->text, "29");
    EXPECT_EQ(token->next, nullptr);
    free_token(token);
}

// STRING
token_t* mock_tokenize(const char* buffer) {
  token_t* token = create_token(STRING, buffer);
  token->next = nullptr;
  return token;
}

TEST(TokenTest, StringToken) {
    const char* text = "Hello World!";
    token_t* token = mock_tokenize(text);
    ASSERT_NE(token, nullptr);
    EXPECT_EQ(token->type, STRING);
    EXPECT_STREQ(token->text, text);
    EXPECT_EQ(token->next, nullptr);
    free_token(token);
    text = "\"Hello World!\".";
    token = mock_tokenize(text);
    ASSERT_NE(token, nullptr);
    EXPECT_EQ(token->type, STRING);
    EXPECT_STREQ(token->text, text);
    EXPECT_EQ(token->next, nullptr);
    free_token(token);
}

// BOOLEAN
TEST(TokenTest, BooleanToken) {
    token_t *true_token = create_token(INTEGER, "true");
    token_t *false_token = create_token(INTEGER, "false");
    EXPECT_EQ(true_token->type, BOOLEAN);
    EXPECT_STREQ(true_token->text, "true");
    EXPECT_EQ(false_token->type, BOOLEAN);
    EXPECT_STREQ(false_token->text, "false");
    free_token(true_token);
    free_token(false_token);
}

// IF : true
void test_if_true_condition() {
    token_t *tokens = create_token(STRING, "10");
    tokens = create_token_list(tokens, COMPARISON_OPERATOR, ">");
    tokens = create_token_list(tokens, INTEGER, "5");
    tokens = create_token_list(tokens, IF, NULL);
    tokens = create_token_list(tokens, STRING, "This will print");
    evaluate(tokens);
    printf("Expected output: String: This will print\n");
    free_tokens(tokens);
}

// IF : false
void test_if_false_condition() {
    token_t *tokens = create_token(STRING, "5");
    tokens = create_token_list(tokens, COMPARISON_OPERATOR, "<");
    tokens = create_token_list(tokens, INTEGER, "10");
    tokens = create_token_list(tokens, IF, NULL);
    tokens = create_token_list(tokens, STRING, "This will print blank");
    evaluate(tokens);
    printf("Expected output: Blank\n");
    free_tokens(tokens);
}

// RUN TESTS
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}