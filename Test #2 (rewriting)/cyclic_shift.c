#include <stdbool.h>
#include <stdio.h>

unsigned int findMaxCyclicShift(unsigned int length, bool binaryNumber[])
{
    unsigned int maxValue = 0;

    for (unsigned int start = 0; start < length; ++start) {
        unsigned int currentValue = 0;

        for (unsigned int index = 0; index < length; ++index) {
            unsigned int newIndex = (start + index) % length;
            currentValue = currentValue * 2 + (binaryNumber[newIndex] ? 1 : 0);
        }
        if (currentValue > maxValue) {
            maxValue = currentValue;
        }
    }
    return maxValue;
}

int main(void)
{
    puts("Enter the numbers (Enter Ctrl+D/Ctrl+Z to exit): ");

    bool numbers[32];
    int length = 0;
    int number;
    while (scanf("%d", &number) == 1) {
        if (!(number == 0 || number == 1)) {
            puts("Binary type must include only 0 and 1 values");
            return 1;
        }
        numbers[length] = (bool)number;
        ++length;
    }

    unsigned int maxShiftedNumber = findMaxCyclicShift(length, numbers);
    printf("Max value after shifting is %u\n", maxShiftedNumber);
}
