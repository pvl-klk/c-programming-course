#pragma once

typedef struct StackStruct {
    void * value;
    struct StackStruct *previous;
} Stack;

Stack* stackNew();

void stackPush(Stack**, void*);

void stackPop(Stack**);

void stackFree(Stack**);
