#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef enum {
    TOKEN_KEYWORD,      // Keywords: bool, nat, 
    TOKEN_KEYWORD_bool, // Keywords: bool
    TOKEN_KEYWORD_nat,  // Keywords: nat
    TOKEN_KEYWORD_fun,   // Keywords: fun
    TOKEN_IDENTIFIER,   // Identifiers: variables and function names
    TOKEN_NUMBER,       // Natural numbers
    TOKEN_OPERATOR,     // Operators: +, &, <, =, ?, :
    TOKEN_DELIMITER,    // Delimiters: ;, (, )
    TOKEN_LITARAL,      // Litarals: T,F
    TOKEN_BRACKET,
    TOKEN_BOOLEAN,
    TOKEN_ERROR,        // Error token
    TOKEN_EOF          // End of file token
} TokenType;

typedef struct {
    TokenType type;
    char *value;
    int line;
} Token;


void init_lexer(FILE *source);
Token next_token();
void print_token(Token token);

#endif // LEXER_H
typedef enum {
    STATE_START,
    STATE_IN_COMMENT,
    STATE_IN_NUM,
    STATE_IN_ID,
    STATE_IN_OP,
    STATE_DONE,
    STATE_ERROR,
    STATE_IN_BOOLEAN
} LexerState;

typedef enum {
    CHAR_LETTER,
    CHAR_DIGIT,
    CHAR_OPERATOR,
    CHAR_DELIMITER,
    CHAR_WHITESPACE,
    CHAR_UNKNOWN,
    CHAR_BOOLEAN
} CharClass;

#define NUM_STATES 7
#define NUM_CHAR_CLASSES 8

extern LexerState transitionTable[NUM_STATES][NUM_CHAR_CLASSES];

