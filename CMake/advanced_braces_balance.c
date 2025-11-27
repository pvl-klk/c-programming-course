#include "advanced_braces_balance.h"

bool checkBalance(char* string) {
    Stack* stack = stackNew();
    if (stack == NULL) {
        return false;
    }

    for (int index = 0; index < strlen(string); ++index) {
        const char character = string[index];

        if (character == '{' || character == '[' || character == '(') {
            char* value = malloc(sizeof(char));
            if (value == NULL) {
                puts("Memory allocation error");
                stackFree(&stack);
                return false;
            }
            *value = character;
            stackPush(&stack, value);
        }

        else if (character == '}' || character == ']' || character == ')') {
            if (stack -> value == NULL) {
                stackFree(&stack);
                return false;
            }
            
            char* topValue = (char*) stack -> value;
            char topChar = (char)*topValue;
            
            if ((character == '}' && topChar != '{') ||
                (character == ']' && topChar != '[') ||
                (character == ')' && topChar != '(')) {
                stackFree(&stack);
                return false;
            }
            
            free(stack->value);
            stackPop(&stack);
        }
    }
    
    bool balanced = (stack->value == NULL);

    stackFree(&stack);

    return balanced;
}