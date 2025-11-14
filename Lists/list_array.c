#include "list_array.h"

Status listArrayCreate(ListArray** listArray) {
    if (listArray == NULL) {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    *listArray = malloc(sizeof(ListArray));
    if (*listArray == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    (*listArray) -> data = NULL;
    (*listArray) -> size = 0;
    return OK;
}

Status listArrayAdd(ListArray* listArray, const int value) {
    if (listArray == NULL) {
        return NULL_POINTER_ARGUMENT_ERROR;
    }

    int* data = malloc(sizeof(int)*(listArray -> size + 1));
    if (data == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (unsigned int index = 0; index < listArray -> size; ++index) {
        data[index] = listArray -> data[index];
    }
    data[listArray -> size] = value;

    free(listArray -> data);
    listArray -> data = data;
    listArray -> size++;
    return OK;
}

Status listArrayRemove(ListArray* listArray, const int value) {
    if (listArray == NULL) {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    if (listArray -> size == 0) {
        return EMPTY_LIST;
    }
    int foundIndex = -1;
    for (unsigned int index = 0; index < listArray -> size; ++index) {
        if (listArray -> data[index] == value) {
            foundIndex = (int) index;
            break;
        }
    }

    if (foundIndex == -1) {
        return NOT_INCLUDE_VALUE;
    }

    if (listArray -> size == 1) {
        free(listArray -> data);
        listArray -> data = NULL;
        listArray -> size = 0;
        return OK;
    }

    int* newData = malloc(sizeof(int) * (listArray -> size - 1));
    if (newData == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }

    int offset = 0;
    for (unsigned int index = 0; index < listArray -> size; ++index) {
        if (index == (unsigned int) foundIndex) {
            offset = 1;
        } else {
            newData[index - offset] = listArray -> data[index];
        }
    }

    free(listArray -> data);
    listArray -> data = newData;
    listArray -> size--;
    return OK;
}

Status listArrayFree(ListArray* listArray) {
    if (listArray == NULL) {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    free(listArray -> data);
    free(listArray);
    return OK;
}

Status listArrayPrint(const ListArray* listArray) {
    if (listArray == NULL) {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    printf("{ ", listArray -> size);
    for (unsigned int index = 0; index < listArray -> size; ++index) {
        printf("%d ", listArray -> data[index]);
    }
    printf("}\n");
    return OK;
}

Status listArraySort(ListArray* listArray) {
    if (listArray == NULL) {
        return NULL_POINTER_ARGUMENT_ERROR;
    }
    for (unsigned int index_1 = 0; index_1 < listArray -> size; ++index_1) {
        for (unsigned int index_2 = index_1 + 1; index_2 < listArray -> size; ++index_2) {
            if (listArray -> data[index_1] > listArray -> data[index_2]) {
                const int temp = listArray -> data[index_1];
                listArray -> data[index_1] = listArray -> data[index_2];
                listArray -> data[index_2] = temp;
            }
        }
    }
    return OK;
}
