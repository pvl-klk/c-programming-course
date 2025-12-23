#include <stdio.h>

void selectionSort(int array[], int length) {
    for (int index_1 = 0; index_1 < length - 1; ++index_1) {
        int min_index = index_1;
        
        for (int index_2 = index_1 + 1; index_2 < length; ++index_2) {
            if (array[index_2] < array[min_index]) {
                min_index = index_2;
            }
        }
        int temp = array[min_index];
        array[min_index] = array[index_1];
        array[index_1] = temp;
    }
}

void printArray(int array[], int length) {
    printf("{ ");
    for (int index_1 = 0; index_1 < length; ++index_1) {
        printf("%d ", array[index_1]);
    }
    printf("}\n");
}

int main() {
    int array[] = { 64, 25, 12, 22, 11 };
    int length = 5;
    
    printf("Originall array: ");
    printArray(array, length);
    
    selectionSort(array, length);
    
    printf("Sorted array: ");
    printArray(array, length); // { 11 12 22 25 64 }
    
    return 0;
}
