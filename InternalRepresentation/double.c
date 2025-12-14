/* 
    В C для типа double используется стандарт IEEE 754
    IEEE 754 - стандарт размещения вещественных чисел в памяти

    В соответствии с этим стандартом
    63 бит выделяется под знак (1 - минус, 0 - плюс)
    С 52 по 62 биты выделяются под экспоненту
    С 0 по 51 биты выделяются под мантиссу
*/

#include <stdio.h>

typedef union {
    // Размер типа double - 8 байт или 64 бита
    double value;
    // Размер типа unsigned long long - не меннее 8 байт или 64 бит
    unsigned long long bits;
} DoubleUnion;

int main(void) {
    DoubleUnion doubleUnion;
    printf("Enter a number: ");
    if (scanf("%lf", &doubleUnion.value) != 1) {
        return 1;
    }
    
    unsigned long long bits = doubleUnion.bits;
    
    // Берем 63 бит
    char sign = (bits >> 63) ? '-' : '+';
    // Берем с 62 по 52 биты
    unsigned long long exponent = (bits >> 52) & 0x7FFUL;
    // Берем последние 52 бита
    unsigned long long mantissa = bits & 0xFFFFFFFFFFFFFUL;
    
    double mantissa_value = 1.0 + (double) mantissa / (1ULL << 52);
    int real_exponent = (int) exponent - 1023;
    
    printf("Result: %c%.20g*2^%d\n", sign, mantissa_value, real_exponent);

    return 0;
}
