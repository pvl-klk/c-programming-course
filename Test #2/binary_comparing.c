#include <stdbool.h>
#include <stdio.h>

void binaryCompare(unsigned int digits_number_1, bool number_1[],
    unsigned int digits_number_2, bool number_2[])
{

    int index_1 = digits_number_1 - 1;
    int index_2 = digits_number_2 - 1;

    while (index_1 >= 0 && !number_1[index_1]) {
        --index_1;
    }
    while (index_2 >= 0 && !number_2[index_2]) {
        --index_2;
    }

    if (index_1 < 0 && index_2 < 0) {
        puts("Numbers are equal");
        return;
    }
    if (index_1 < 0) {
        puts("Second number is greater");
        return;
    }
    if (index_2 < 0) {
        puts("First number is greater");
        return;
    }

    if (index_1 > index_2) {
        puts("First number is greater");
        return;
    }
    if (index_1 < index_2) {
        puts("Second number is greater");
        return;
    }

    while (index_1 >= 0) {
        if (number_1[index_1] > number_2[index_1]) {
            puts("First number is greater");
            return;
        }
        if (number_1[index_1] < number_2[index_1]) {
            puts("Second number is greater");
            return;
        }
        --index_1;
    }
    puts("Numbers are equal");
}
