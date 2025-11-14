#include "cyclic_list_array.h"

Status cyclicListArrayCreate(CyclicListArray **cyclicListArray)
{
    if (cyclicListArray == NULL)
    {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    *cyclicListArray = malloc(sizeof(CyclicListArray));
    if (*cyclicListArray == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    (*cyclicListArray)->size = 0;
    (*cyclicListArray)->position = 0;
    (*cyclicListArray)->data = NULL;
    return OK;
}

Status cyclicListArrayAdd(CyclicListArray *cyclicListArray, const int value)
{
    if (cyclicListArray == NULL)
    {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    int *data = malloc(sizeof(int) * (cyclicListArray->size + 1));
    if (data == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    for (unsigned int index = 0; index < cyclicListArray->size; ++index)
    {
        data[index] = cyclicListArray->data[index];
    }
    data[cyclicListArray->size] = value;

    free(cyclicListArray->data);
    cyclicListArray->data = data;
    cyclicListArray->size++;

    return OK;
}

Status cyclicListArrayNext(CyclicListArray *cyclicListArray)
{
    if (cyclicListArray == NULL)
    {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    if (cyclicListArray->size == 0)
    {
        return EMPTY_LIST;
    }
    cyclicListArray->position = (cyclicListArray->position + 1) % cyclicListArray->size;
    return OK;
}

Status cyclicListArrayPrevious(CyclicListArray *cyclicListArray)
{
    if (cyclicListArray == NULL)
    {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    if (cyclicListArray->size == 0)
    {
        return EMPTY_LIST;
    }
    cyclicListArray->position = (cyclicListArray->position - 1 + cyclicListArray->size) % cyclicListArray->size;
    return OK;
}

Status cyclicListArrayGetCurrent(const CyclicListArray *cyclicListArray, int *address)
{
    if (cyclicListArray == NULL)
    {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    if (cyclicListArray->size == 0)
    {
        return EMPTY_LIST;
    }
    *address = cyclicListArray->data[cyclicListArray->position];
    return OK;
}

Status cyclicListArrayRemoveCurrent(CyclicListArray *cyclicListArray)
{
    if (cyclicListArray == NULL)
    {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    if (cyclicListArray->size == 0)
    {
        return EMPTY_LIST;
    }

    int *data = malloc(sizeof(int) * (cyclicListArray->size - 1));
    if (data == NULL)
    {
        return MEMORY_ALLOCATION_ERROR;
    }
    int offset = 0;
    for (unsigned int index = 0; index < cyclicListArray->size; ++index)
    {
        if (offset == 0 && index == cyclicListArray->position)
        {
            offset = 1;
        }
        else
        {
            data[index - offset] = cyclicListArray->data[index];
        }
    }
    free(cyclicListArray->data);
    cyclicListArray->data = data;
    cyclicListArray->size--;
    if (cyclicListArray->size > 0)
    {
        cyclicListArray->position = cyclicListArray->position % cyclicListArray->size;
    }
    else
    {
        cyclicListArray->position = 0;
    }
    return OK;
}

Status cyclicListArrayFree(CyclicListArray **cyclicListArray)
{
    if (cyclicListArray == NULL || *cyclicListArray == NULL)
    {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    free((*cyclicListArray)->data);
    free(*cyclicListArray);
    *cyclicListArray = NULL;
    return OK;
}
