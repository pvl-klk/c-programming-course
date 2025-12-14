#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int length;
    unsigned short* digits;
} BinaryNumber;

BinaryNumber* toBinary(unsigned int number)
{
    unsigned int length;
    if (number == 0) {
        length = 1;
    } else {
        length = ceil(log2(number + 1));
    }

    unsigned short* digits = calloc(length, sizeof(unsigned short));
    if (digits == NULL) {
        puts("ERROR: MEMORY ALLOCATION DID NOT OCCUR");
        return NULL;
    }

    unsigned int index = 0;
    while (number) {
        digits[length - 1 - index] = number % 2;
        number /= 2;
        ++index;
    }

    BinaryNumber* result = malloc(sizeof(BinaryNumber));
    if (result == NULL) {
        puts("ERROR: MEMORY ALLOCATION DID NOT OCCUR");
        return NULL;
    }
    result->length = length;
    result->digits = digits;

    return result;
}

void destroyBinary(BinaryNumber** number)
{
    if (number == NULL || *number == NULL) {
        puts("ERROR: NULL POINTER PROVIDED");
        return;
    }
    free((*number)->digits);
    free(*number);
    *number = NULL;
}

char* binaryToString(BinaryNumber* number)
{
    if (number == NULL) {
        puts("ERROR: NULL POINTER PROVIDED");
        return NULL;
    }

    char* string = malloc((number->length + 1) * sizeof(char));
    if (string == NULL) {
        puts("ERROR: MEMORY ALLOCATION DID NOT OCCUR");
        return NULL;
    }

    for (unsigned int i = 0; i < number->length; i++) {
        string[i] = number->digits[i] + '0';
    }

    string[number->length] = '\0';
    return string;
}

unsigned int binaryToDecimal(BinaryNumber* number)
{
    if (number == NULL) {
        puts("ERROR: NULL POINTER PROVIDED");
        return 0;
    }
    unsigned int result = 0;
    for (unsigned int index = 0; index < number->length; ++index) {
        result = (result << 1) | number->digits[index];
    }
    return result;
}

BinaryNumber* addBinary(BinaryNumber* number_1, BinaryNumber* number_2)
{
    if (number_1 == NULL || number_2 == NULL) {
        puts("ERROR: NULL POINTER PROVIDED");
        return NULL;
    }

    unsigned int maxLength = (number_1->length > number_2->length) ? number_1->length : number_2->length;
    unsigned int sumLength = maxLength + 1;

    unsigned short* sumDigits = calloc(sumLength, sizeof(unsigned short));
    if (sumDigits == NULL) {
        puts("ERROR: MEMORY ALLOCATION DID NOT OCCUR");
        return NULL;
    }

    unsigned int carry = 0;
    int bitPosNumber_1 = number_1->length - 1;
    int bitPosNumber_2 = number_2->length - 1;
    int resultPos = sumLength - 1;

    while (bitPosNumber_1 >= 0 || bitPosNumber_2 >= 0 || carry) {
        unsigned int bitNumber_1 = (bitPosNumber_1 >= 0) ? number_1->digits[bitPosNumber_1] : 0;
        unsigned int bitNumber_2 = (bitPosNumber_2 >= 0) ? number_2->digits[bitPosNumber_2] : 0;

        unsigned int sum = bitNumber_1 + bitNumber_2 + carry;
        sumDigits[resultPos] = sum % 2;
        carry = sum / 2;

        bitPosNumber_1--;
        bitPosNumber_2--;
        resultPos--;
    }

    if (sumDigits[0] == 0) {
        for (unsigned int position = 0; position < sumLength - 1; position++) {
            sumDigits[position] = sumDigits[position + 1];
        }
        --sumLength;
    }

    BinaryNumber* result = malloc(sizeof(BinaryNumber));
    if (result == NULL) {
        puts("ERROR: MEMORY ALLOCATION DID NOT OCCUR");
        free(sumDigits);
        return NULL;
    }

    result->length = sumLength;
    result->digits = sumDigits;

    return result;
}

int main(void)
{
    unsigned int decimal_1;
    printf("Enter a first number: ");
    if (scanf("%u", &decimal_1) != 1) {
        puts("ERROR: INCORRECT INPUT");
        return 1;
    };

    unsigned int decimal_2;
    printf("Enter a second number: ");
    if (scanf("%u", &decimal_2) != 1) {
        puts("ERROR: INCORRECT INPUT");
        return 1;
    };

    BinaryNumber* binary_1 = toBinary(decimal_1);
    BinaryNumber* binary_2 = toBinary(decimal_2);
    if (!binary_1 || !binary_2) {
        return 1;
    }

    char* string_1 = binaryToString(binary_1);
    char* string_2 = binaryToString(binary_2);
    if (!string_1 || !string_2) {
        return 1;
    }

    printf("Number %u in binary form is %s\n", decimal_1, string_1);
    printf("Number %u in binary form is %s\n", decimal_2, string_2);

    BinaryNumber* binarySum = addBinary(binary_1, binary_2);
    if (!binarySum) {
        return 1;
    }
    char* sumAsString = binaryToString(binarySum);
    if (!sumAsString) {
        return 1;
    }

    printf("Sum of %s and %s is %s\n", string_1, string_2, sumAsString);

    unsigned int decimalSum = binaryToDecimal(binarySum);

    printf("Sum of %s and %s in decimal form is %u\n", string_1, string_2, decimalSum);

    destroyBinary(&binary_1);
    destroyBinary(&binary_2);
    destroyBinary(&binarySum);

    free(string_1);
    free(string_2);
    free(sumAsString);

    return 0;
}
