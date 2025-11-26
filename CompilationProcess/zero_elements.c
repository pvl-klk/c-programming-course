#include <stdio.h>

int main(void)
{
    const int array[] = { 1, 0, 4, 0, 0, 2, 0, 1, 0, 5 };
    const int length = 10;

    int counter = 0;
    for (int index = 0; index < length; ++index) {
        if (array[index] == 0) {
            ++counter;
        }
    }
    printf("Number of zero elements is %d\n", counter);

    return 0;
}
