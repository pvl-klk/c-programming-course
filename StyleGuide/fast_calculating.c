#include <stdio.h>

int main(void)
{
    // x^4 + x^3 + x^2 + x + 1
    // (x^2 + x)(x^2 + 1) + 1
    int x;
    printf("Enter the x value: ");
    scanf("%d", &x);
    const int a = x * x;
    const int b = a + x;
    const int c = a + 1;
    const int d = b * c;
    const int result = d + 1;
    printf("Result: %d\n", result);

    return 0;
}
