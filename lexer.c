#define _CRT_SECURE_NO_WARNINGS
#include "lexer.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)
static FILE* source_file;
static int current_char;
static int current_line = 1; // Initialize to the first line

void init_lexer(FILE* source) {
    source_file = source;
    current_char = fgetc(source_file);
}

static void advance() {
    current_char = fgetc(source_file);
    if (current_char == '\n') {
        current_line++; // Increments the line number when new line characters are encountered
    }
}

static Token create_token(TokenType type, char* value, int line) {
    Token token;
    token.type = type;
    token.value = strdup(value);
    token.line = line;
    return token;
}

LexerState transitionTable[NUM_STATES][NUM_CHAR_CLASSES] = {
    // Define transitions for each state and character class
    [STATE_START] = {
            [CHAR_LETTER] = STATE_IN_ID,
            [CHAR_DIGIT] = STATE_IN_NUM,
            [CHAR_OPERATOR] = STATE_IN_OP,
            [CHAR_WHITESPACE] = STATE_START,
            [CHAR_BOOLEAN] = STATE_IN_BOOLEAN
            //other transitions?
    }
    //This space is to define transitions for other states?
};

CharClass get_char_class(char c) {
    if (strchr("TF", c) != NULL) return CHAR_BOOLEAN;
    if (isalpha(c)) return CHAR_LETTER;
    if (isdigit(c)) return CHAR_DIGIT;
    if (strchr("+-&<?:;()[]>=,", c) != NULL) return CHAR_OPERATOR;
    if (isspace(c)) return CHAR_WHITESPACE;
    return CHAR_UNKNOWN;
}

Token next_token() {
    LexerState state = STATE_START;
    char buffer[1024];
    int buf_len = 0;

    while (current_char != EOF && buf_len < 1023) {
        CharClass charClass = get_char_class(current_char);
        LexerState nextState = transitionTable[state][charClass];

        switch (state) {
        case STATE_START:
            if (charClass == CHAR_WHITESPACE) {
                advance();
                continue;
            }
            if (current_char == '[') {
                state = STATE_IN_COMMENT;
                advance();
                continue;
            }
            else if (charClass == CHAR_LETTER) {
                buffer[buf_len++] = current_char;
                state = STATE_IN_ID;
            }
            else if (charClass == CHAR_DIGIT) {
                buffer[buf_len++] = current_char;
                state = STATE_IN_NUM;
            }
            else if (charClass == CHAR_OPERATOR) {
                buffer[buf_len++] = current_char;
                state = STATE_IN_OP;
            }
            else if (charClass == CHAR_BOOLEAN) {
                buffer[buf_len++] = current_char;
                state = STATE_IN_BOOLEAN;
            }
            else if (charClass == CHAR_BOOLEAN) {
                buffer[buf_len++] = current_char;
                state = STATE_IN_BOOLEAN;
            }
            else if (charClass == CHAR_UNKNOWN) {
                //                    printf("Lexical error: '%c',error in %d line\n", current_char, current_line);
                //                    advance();
                //                    state = STATE_START;
                buffer[buf_len++] = current_char;
                state = STATE_IN_OP;
            }
            break;

        case STATE_IN_COMMENT:
            if (current_char == ']') {
                state = STATE_START;
            }
            advance();
            continue; // 跳过方括号内的所有内容

        case STATE_IN_ID:
            if (charClass != CHAR_LETTER && charClass != CHAR_DIGIT) {
                buffer[buf_len] = '\0';
                state = STATE_DONE;
                // Check if buffer is a keyword
                if (strcmp(buffer, "bool") == 0) {
                    return create_token(TOKEN_KEYWORD_bool, buffer, current_line);
                }
                else if (strcmp(buffer, "nat") == 0) {
                    return create_token(TOKEN_KEYWORD_nat, buffer, current_line);
                }
                else if (strcmp(buffer, "fun") == 0) {
                    return create_token(TOKEN_KEYWORD_fun, buffer, current_line);
                }
                else {
                    return create_token(TOKEN_IDENTIFIER, buffer, current_line);
                }
            }
            else {
                buffer[buf_len++] = current_char;
            }
            break;
        case STATE_IN_BOOLEAN:
            if (charClass != CHAR_LETTER && charClass != CHAR_DIGIT) {
                buffer[buf_len] = '\0';
                state = STATE_DONE;
                return create_token(TOKEN_BOOLEAN, buffer, current_line);
            }
            else {
                buffer[buf_len++] = current_char;
            }
            break;
        case STATE_IN_NUM:
            if (charClass != CHAR_DIGIT) {
                buffer[buf_len] = '\0';
                state = STATE_DONE;
                return create_token(TOKEN_NUMBER, buffer, current_line);
            }
            else {
                buffer[buf_len++] = current_char;
            }
            break;

            //Implement logic for other states?
        case STATE_IN_OP:
            if (buffer[0] == '-' && current_char == '>') {
                // Detecting '->' operator
                buffer[buf_len++] = current_char;
                buffer[buf_len] = '\0';
                state = STATE_DONE;
                advance();
                return create_token(TOKEN_OPERATOR, buffer, current_line);
            }
            //else if (charClass == CHAR_OPERATOR) {
            //    buffer[buf_len++] = current_char;
            //    // Assuming other operators are single characters
            //    buffer[buf_len] = '\0';
            //    state = STATE_DONE;
            //}
            else {
                buffer[buf_len] = '\0';
                // Check for valid single character operators
                if (strcmp(buffer, "+") == 0 || strcmp(buffer, "&") == 0 || strcmp(buffer, "<") == 0 || strcmp(buffer, "=") == 0 || strcmp(buffer, "?") == 0 || strcmp(buffer, ":") == 0 || strcmp(buffer, ";") == 0 || strcmp(buffer, ",") == 0) {
                    return create_token(TOKEN_OPERATOR, buffer, current_line);
                }
                else if (strcmp(buffer, "(") == 0 || strcmp(buffer, ")") == 0 || strcmp(buffer, "[") == 0 || strcmp(buffer, "]") == 0 || strcmp(buffer, "T") == 0) {
                    return create_token(TOKEN_BRACKET, buffer, current_line);
                }
                else {
                    if (current_char == '>') {
                        state = STATE_DONE;
                    }
                    return create_token(TOKEN_ERROR, buffer, current_line); /////////
                }
            }
            break;

            //            case STATE_ERROR:
            //                printf("Lexical error at line %d: Invalid token '%c'\n", current_line, current_char);
            //                buffer[buf_len] = '\0';
            //                advance();
            //                state = STATE_START;
            //                return create_token(TOKEN_ERROR, buffer, current_line);
            //                break;


        }
        advance();
    }

    buffer[buf_len] = '\0';
    if (state == STATE_ERROR) {
        return create_token(TOKEN_ERROR, "Lexical error", current_line);
    }
    return create_token(TOKEN_EOF, "", current_line);
}

void print_token(Token token) {
    switch (token.type) {
    case TOKEN_IDENTIFIER:
        printf("\"%s\" \t\t identifier\n", token.value);
        break;
    case TOKEN_NUMBER:
        printf("\"%s\" \t\t literal(natural)\n", token.value);
        break;
    case TOKEN_OPERATOR:
        printf("\"%s\" \t\t %s\n", token.value, token.value);
        break;
    case TOKEN_KEYWORD_bool:
        printf("\"%s\" \t\t Bool\n", token.value);
        break;
    case TOKEN_KEYWORD_nat:
        printf("\"%s\" \t\t nat\n", token.value);
        break;
    case TOKEN_KEYWORD_fun:
        printf("\"%s\" \t\t fun\n", token.value);
        break;
    case TOKEN_BRACKET:
        printf("\"%s\" \t\t %s\n", token.value, token.value);
        break;
    case TOKEN_BOOLEAN:
        printf("\"%s\" \t\t literal(Boolean)\n", token.value);
        break;
    case TOKEN_ERROR:
        printf("\"%s\" \t\t Lexical error\n", token.value);
        printf("Error: Invalid Token '%s' found at line: %d\n", token.value, token.line);
        break;
    default:
        printf("\"%s\" \t\t Token\n", token.value);
        break;
    }
}
