#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

Stack* stackNew() {
    Stack* stack = malloc(sizeof(Stack));
    if (stack == NULL) {
        puts("Memory allocation error");
        return NULL;
    }
    stack -> previous = NULL;
    stack -> value = NULL;
    return stack;
}

void stackPush(Stack** stack, void* value) {
    if (stack == NULL || *stack == NULL) {
        puts("Incorrect arguments error");
        return;
    }
    Stack* stackTop = malloc(sizeof(Stack));
    if (stackTop == NULL) {
        puts("Memory allocation error");
        return;
    }
    stackTop -> value = value;
    stackTop -> previous = *stack;
    *stack = stackTop;
}

void stackPop(Stack** stack) {
    if (stack == NULL || *stack == NULL) {
        puts("Incorrect arguments error");
        return;
    }
    Stack* stackTop = (*stack) -> previous;
    if (stackTop != NULL) {
        free(*stack);
        *stack = stackTop;
    }
}

void stackFree(Stack** stack) {
    if (stack == NULL || *stack == NULL) {
        puts("Incorrect arguments error");
        return;
    }
    while ((*stack)->previous != NULL) {
        stackPop(stack);
    }
    free(*stack);
    *stack = NULL;
}
