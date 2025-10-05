#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int bubbleSort(unsigned int, int[]);

int main(void) {
    char userInput[2048];
    scanf("%2047[^\n]", userInput);

    int numbers[100];

    unsigned short numbersLength = 0;
    const char* token = strtok(userInput, " ");
    while (token != NULL) {
        char* endPtr;
        numbers[numbersLength] = strtol(token, &endPtr, 10);
        ++numbersLength;
        token = strtok(NULL, " ");
    }


    printf("Original array: { ");
    for (int index = 0; index < numbersLength; ++index) {
        printf("%d ", numbers[index]);
    }
    printf("}\n");

    const int permutations = bubbleSort(numbersLength, numbers);

    printf("Sorted array: { ");
    for (int index = 0; index < numbersLength; ++index) {
        printf("%d ", numbers[index]);
    }
    printf("}\n");
    printf("Number of permutations: %d\n", permutations);

    return 0;
}

