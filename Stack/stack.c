#include <stdlib.h>
#include <stdio.h>

typedef struct StackStruct {
    void * value;
    struct StackStruct *previous;
} Stack;

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
    }
    Stack* stackTop = malloc(sizeof(Stack));
    if (stackTop == NULL) {
        puts("Memory allocation error");
    }
    stackTop -> value = value;
    stackTop -> previous = stack;

}

Stack* stackPop(Stack* stack) {
    if (stack == NULL) {
        puts("Incorrect arguments error");
        return NULL;
    }
    Stack* stackTop = stack -> previous;
    if (stackTop != NULL) {
        free(stack);
        return stackTop;
    }
    return stack;
}
