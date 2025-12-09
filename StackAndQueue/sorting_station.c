#include "Stack\stack.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getPriority(char operation) {
    return (operation == '+' || operation == '-') ? 1 : (operation == '*' || operation == '/') ? 2 : 0;
}

char* sortingStationAlgorithm(char* expression) {
    expression = strdup(expression);

    Stack* stack = stackNew();

    char* token = strtok(expression, " ");

    char* result = malloc(strlen(expression) * 2);
    result[0] = '\0';
    
    while (token != NULL) {
        if (isdigit(token[0])) {
            strcat(result, token);
            strcat(result, " ");
        }
        else if (token[0] == '(') {
            stackPush(&stack, strdup(token));
        }
        else if (token[0] == ')') {
            while (stack != NULL && stack -> value != NULL && 
                   ((char*) stack -> value)[0] != '(') {
                strcat(result, (char*) stack -> value);
                strcat(result, " ");
                stackPop(&stack);
            }
            if (stack && stack -> value) {
                stackPop(&stack);
            }
        }
        else if (token[0] == '*' || token[0] == '/' || token[0] == '+' || token[0] == '-') {
            while (stack != NULL && stack -> value != NULL && 
                   getPriority(((char*) stack -> value)[0]) >= getPriority(token[0])) {
                strcat(result, (char*) stack -> value);
                strcat(result, " ");
                stackPop(&stack);
            }
            stackPush(&stack, strdup(token));
        }
        token = strtok(NULL, " ");
    }
    
    while (stack != NULL && stack -> value != NULL) {
        strcat(result, (char*) stack -> value);
        strcat(result, " ");
        stackPop(&stack);
    }
    
    free(expression);
    stackFree(&stack);

    return result;
}
