#include <stdio.h>

int calcQuotient(const int a, const int b) {
    if (b == 0) {
        puts("ERROR: DIVISION BY ZERO");
        return 0;
    }

    const int sign = (a < 0) ^ (b < 0) ? -1 : 1;

    int absoluteA = a < 0 ? -a : a;
    const int absoluteB = b < 0 ? -b : b;

    int quotient = 0;
    while (absoluteA >= absoluteB) {
        absoluteA -= absoluteB;
        quotient++;
    }
    const int result = quotient * sign;
    return result;
}

int main() {
    printf("%d\n", calcQuotient(-7, -2)); // 3
    printf("%d\n", calcQuotient(7, 2)); // 3
    printf("%d\n", calcQuotient(-7, 2)); // -3
    printf("%d\n", calcQuotient(7, -2)); // -3
    printf("%d\n", calcQuotient(-2, 2)); // -1
    printf("%d\n", calcQuotient(2, 7)); // 0

    return 0;
}
