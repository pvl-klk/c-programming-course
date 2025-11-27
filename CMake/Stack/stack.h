#pragma once

// The StackStruct structure with the value and previous fields
// Defined as Stack
typedef struct StackStruct {
    void * value;
    struct StackStruct *previous;
} Stack;

// Create a new stack
Stack* stackNew();

// Add a new element to the top of the stack
void stackPush(Stack**, void*);

// Remove an element from the top of the stack
void stackPop(Stack**);

// Free the stack
void stackFree(Stack**);