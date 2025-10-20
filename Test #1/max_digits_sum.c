#include <stdio.h>

void printMaxBin(int* array, int length) {
    int sums[length];
    int max_sum = -1;
    for (int index = 0; index < length; ++index) {
        int number = array[index];
        int sum = 0;
        while (number != 0) {
            int remainder = number % 2;
            sum += remainder;
            number = (number - remainder) / 2;
        }
        sums[index] = sum;
        if (sum > max_sum) {
            max_sum = sum;
        }
    }
    printf("Numbers with the maximum sum of digits in binary notation: { ");
    for (int index = 0; index < length; ++index) {
        if (sums[index] == max_sum) {
            printf("%d ", array[index]);
        }
    }
    printf("}\n");
}

int main(void) {
    int numbers[] = { 1, 5, 2, 5, 6, 12, 7, 7 };
    printMaxBin(numbers, 8); // 7 7 
    return 0;
}
