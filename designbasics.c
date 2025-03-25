
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
char* keywords[] = {"if", "else", "while", "for", "int", "float", "char"};
char* operators[] = {"+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">="};
int isKeyword(char* word) {
    for (int i = 0; i < 7; i++) {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
int isOperator(char c) {
    for (int i = 0; i < 11; i++) {
        if (c == operators[i][0])
            return 1;
    }
    return 0;
}
int isIdentifier(char* word) {
    if (isalpha(word[0]) || word[0] == '_')
        return 1;
    return 0;
}
void lexicalAnalysis(FILE* file) {
    char c;
    char word[100];

    while ((c = fgetc(file)) != EOF) {
        
        if (isalpha(c) || c == '_') {
            int i = 0;
            while ((c != ' ') && (c != '\n') && (c != EOF)) {
                word[i++] = c;
                c = fgetc(file);
            }
            word[i] = '\0';

            if (isKeyword(word))
                printf("Keyword: %s\n", word);
            else if (isIdentifier(word))
                printf("Identifier: %s\n", word);
            else
                printf("Unknown token: %s\n", word);

            ungetc(c, file); 
        } else if (isOperator(c))
            printf("Operator: %c\n", c);
        else if (isspace(c))
            continue;
        else
            printf("Unknown token: %c\n", c);
    }
}

int main() {
    FILE* file;
    

    file = fopen("test.txt", "r");
    if (file == NULL) {
        printf("Could not open ");
        return 1;
    }

    lexicalAnalysis(file);
    fclose(file);

    return 0;
}
