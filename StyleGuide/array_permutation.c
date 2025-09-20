#include <stdio.h>

void printArray(int, const int*);
void permutateSegments(int, int, int*);

int main(void) {
    // { 4 2 9 5 1 } + { 4 2 9 0 } => { 4 2 9 0 } + { 4 2 9 5 1 }
    // m = 5
    // n = 4

    int array[] = { 4, 2, 9, 5, 1, 4, 2, 9, 0 };
    const int m = 5;
    const int n = 4;
    const int length = m + n;

    permutateSegments(m, n, array);

    printf("Result: ");
    printArray(length, array);

    return 1;
}

void printArray(const int length, const int* array) {
    printf("{ ");
    for (int i = 0; i < length; ++i) {
        printf("%d ", array[i]);
    }
    printf("}\n");
}

void permutateSegments(const int m, const int n, int *array) {
    const int length = m + n;
    for (int iteration = 0; iteration < m; ++iteration) {
        for (int index = 0; index < length-1; ++index) {
            const int temp = array[index+1];
            array[index+1] = array[index];
            array[index] = temp;
        }
    }
}
