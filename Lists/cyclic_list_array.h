#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef enum StatusesEnum
{
    OK,
    MEMORY_ALLOCATION_ERROR,
    NULL_POINTER_ARGUMENT_ERROR,
    EMPTY_LIST,
    NOT_INCLUDE_VALUE
} Status;

typedef struct CyclicListArrayStruct
{
    int *data;
    int size;
    unsigned int position;
} CyclicListArray;

Status cyclicListArrayCreate(CyclicListArray **cyclicListArray);

Status cyclicListArrayAdd(CyclicListArray *cyclicListArray, const int value);

Status cyclicListArrayNext(CyclicListArray *cyclicListArray);

Status cyclicListArrayPrevious(CyclicListArray *cyclicListArray);

Status cyclicListArrayGetCurrent(const CyclicListArray *cyclicListArray, int *address);

Status cyclicListArrayRemoveCurrent(CyclicListArray *cyclicListArray);

Status cyclicListArrayFree(CyclicListArray **cyclicListArray);
