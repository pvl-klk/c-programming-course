#include <stdio.h>
#include <math.h>


void calcDigit(int n) {
    if (n == 1) {
        puts("0");
    }
    if (n == 2) {
        puts("1");
    }
    unsigned int previous = 0;
    unsigned int current = 1;
    int digitNumber = 2;
    while (1) {
        int temp = previous;
        previous = current;
        current += temp;

        temp = current;
        int numberLength = (int) log10(temp) + 1;
        int remainders[numberLength];
        int index = 0;
        while (temp != 0) {
            int remainder = temp % 10;
            remainders[numberLength-index-1] = remainder;
            temp = (temp - remainder) / 10;
            ++index;
        }
        for (int index = 0; index < numberLength; ++index) {
            ++digitNumber;
            if (digitNumber == n) {
                printf("%d\n", remainders[index]);
                return;
            }
        }
    }
}

int main(void) {
    calcDigit(8);
    return 0;
}
