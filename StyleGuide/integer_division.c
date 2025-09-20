#include <stdio.h>
#include <math.h>

int integerDivision(int, int);

int main(void) {
    printf("%d", integerDivision(101, 4));

    return 1;
}

int integerDivision(const int a, const int b) {
    const int sign = a * b < 0 ? -1 : 1;

    int absoluteA = abs(a);
    const int absoluteB = abs(b);

    int quotient = 0;
    while (absoluteA >= absoluteB) {
        absoluteA -= absoluteB;
        quotient++;
    }
    const int result = quotient * sign;
    return result;
}
