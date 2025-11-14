#include "cyclic_list_array.h"

int main(void)
{
    const int n = 4;
    const int m = 7;

    CyclicListArray *cyclicListArray;
    Status status = cyclicListArrayCreate(&cyclicListArray);
    if (status != OK)
    {
        puts("Error creating list");
        return 1;
    }
    for (unsigned int number = 1; number <= n; ++number)
    {
        status = cyclicListArrayAdd(cyclicListArray, (int)number);
        if (status != OK)
        {
            puts("Error adding element");
            cyclicListArrayFree(&cyclicListArray);
            return 1;
        }
    }

    while (cyclicListArray->size > 1)
    {
        const unsigned int remove_index =
            (cyclicListArray->position + (unsigned int)(m - 1)) % (unsigned int)cyclicListArray->size;

        while (cyclicListArray->position != remove_index)
        {
            status = cyclicListArrayNext(cyclicListArray);
            if (status != OK)
            {
                puts("Error moving to next");
                cyclicListArrayFree(&cyclicListArray);
                return 1;
            }
        }

        status = cyclicListArrayRemoveCurrent(cyclicListArray);
        if (status != OK)
        {
            puts("Error removing element");
            cyclicListArrayFree(&cyclicListArray);
            return 1;
        }
    }

    int result;
    status = cyclicListArrayGetCurrent(cyclicListArray, &result);
    if (status != OK)
    {
        puts("Error getting result");
        cyclicListArrayFree(&cyclicListArray);
        return 1;
    }

    cyclicListArrayFree(&cyclicListArray);
    printf("%d", result);
    return 0;
}
