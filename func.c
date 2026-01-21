#define _CRT_SECURE_NO_WARNINGS
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>


int main() {
    FILE* source_file = fopen("C:\\Users\\26078\\source\\repos\\final pj\\x64\\Debug\\sample.txt", "r");
    if (!source_file) {
        perror("Error opening file");
        return 1;
    }

    init_lexer(source_file);
    // init_symbol_table();

    Node* root = NULL;
    printf("Lexme \t\t Token\n");
    printf("-----------------------\n");
    while (1) {
        Token token = next_token();
        if (token.type == TOKEN_EOF) {
            break;
        }
        print_token(token);
        if (token.type == TOKEN_ERROR) {
            break;
        }
        // Add identifier tokens to symbol table
        if (token.type == TOKEN_IDENTIFIER) {
            // token.type == NULL_TOKEN;
            insertNode(&root, token);
        }
    }

    printf("\nSymbol Table:\n");
    printTable(root);
    destroyTree(root);

    fclose(source_file);
    return 0;
}

