#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    OK,
    MEMORY_ALLOCATION_ERROR,
    NULL_POINTER_ARGUMENT_ERROR,
    EMPTY_LIST,
    NOT_INCLUDE_VALUE
} Status; 

typedef struct ListArrayStruct {
    int* data;
    unsigned int size;
} ListArray;

Status listArrayCreate(ListArray**);

Status listArrayAdd(ListArray*, const int);

Status listArrayRemove(ListArray*, const int);

Status listArrayFree(ListArray*);

Status listArrayPrint(const ListArray*);

Status listArraySort(ListArray*);
