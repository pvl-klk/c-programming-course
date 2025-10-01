#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool isBalanced(const char*);

int main(void) {
    const char* string = "()(())()()";

    const bool isStringBalanced = isBalanced(string);

    printf("String is%sbalanced\n", isStringBalanced ? " " : " not ");

    return 0;
}

bool isBalanced(const char* string) {
    int open_braces_number = 0;
    for (int index = 0; index < strlen(string); ++index) {
        const char symbol = string[index];
        if (symbol == '(') {
            ++open_braces_number;
        }
        else if (symbol == ')') {
            --open_braces_number;
        }
        if (open_braces_number < 0) {
            return false;
        }
    }
    if (open_braces_number == 0) {
        return true;
    }
    return false;
}

