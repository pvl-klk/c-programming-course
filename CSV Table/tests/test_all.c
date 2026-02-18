#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "../src/csv_processor.h"

int compareFiles(const char* pathToFile_1, const char* pathToFile_2) {
    FILE *file_1 = fopen(pathToFile_1, "r");
    FILE *file_2 = fopen(pathToFile_2, "r");
    
    if (!file_1 || !file_2) {
        puts("File opening error");
        if (file_1 != NULL) {
            fclose(file_1);
        }
        if (file_2 != NULL) {
            fclose(file_2);
        }
        return 0;
    }
    
    int result = 1;
    int char_1, char_2;
    
    while (1) {
        char_1 = fgetc(file_1);
        char_2 = fgetc(file_2);
        
        // Оба файла закончились одновременно
        if (char_1 == EOF && char_2 == EOF) {
            // Файлы идентичны
            break;
        }
        
        // Первый файл закончился
        if (char_1 == EOF && char_2 != EOF) {
            // Проверяем, не идут ли во втором только \n
            while (char_2 == '\n') {
                char_2 = fgetc(file_2);
            }
            if (char_2 == EOF) {
                // Только \n в конце - считаем одинаковыми
                break;
            } else {
                result = 0;
                break;
            }
        }
        
        // Второй файл закончился
        if (char_1 != EOF && char_2 == EOF) {
            // Проверяем, не идут ли в первом только \n
            while (char_1 == '\n') {
                char_1 = fgetc(file_1);
            }
            if (char_1 == EOF) {
                // Только \n в конце - считаем одинаковыми
                break;
            } else {
                result = 0;
                break;
            }
        }
        
        // Символы разные
        if (char_1 != char_2) {
            result = 0;
            break;
        }
        
        // Символы одинаковые - продолжаем цикл
    }
    
    fclose(file_1);
    fclose(file_2);
    return result;
}

// Тесты для вспомогательных функций
void testIsNumber(void) {
    puts("Testing isNumber function...");
    assert(isNumber("123") == 1);
    assert(isNumber("abc") == 0);
    assert(isNumber("") == 0);
    assert(isNumber(NULL) == 0);
    assert(isNumber("123.45") == 1);
    assert(isNumber("12.34.56") == 0);
    puts("Tests of isNumber function passed!\n");
}

void testCountCommas(void) {
    puts("Testing countCommas function...");
    assert(countCommas("") == 0);
    assert(countCommas("a,b,c") == 2);
    assert(countCommas("a,,c") == 2);
    assert(countCommas(",,,") == 3);
    puts("Tests of countCommas function passed!\n");
}

// Тесты для главной функции
void testProcessCSV(void) {
    puts("Testing processCSV function...\n");

    puts("Testing the basic case...");
    assert(!processCSV("fixtures/basic.csv", "out.txt"));
    assert(compareFiles("fixtures/basic.txt", "out.txt"));
    puts("Test passed!\n");

    puts("Testing the case with empty cells...");
    assert(!processCSV("fixtures/empty_cells.csv", "out.txt"));
    assert(compareFiles("fixtures/empty_cells.txt", "out.txt"));
    puts("Test passed!\n");

    puts("Testing the case with empty file...");
    assert(!processCSV("fixtures/empty.csv", "out.txt"));
    assert(compareFiles("fixtures/empty.txt", "out.txt"));
    puts("Test passed!\n");

    puts("Testing the case with header-only file...");
    assert(!processCSV("fixtures/header_only.csv", "out.txt"));
    assert(compareFiles("fixtures/header_only.txt", "out.txt"));
    puts("Test passed!\n");

    puts("Testing the case with varying columns...");
    assert(!processCSV("fixtures/varying_columns.csv", "out.txt"));
    assert(compareFiles("fixtures/varying_columns.txt", "out.txt"));
    puts("Test passed!\n");

    puts("Testing the case with varying columns...");
    assert(!processCSV("fixtures/whitespace.csv", "out.txt"));
    assert(compareFiles("fixtures/whitespace.txt", "out.txt"));
    puts("Test passed!\n");

    remove("out.txt");
    puts("Tests of processCSV function passed!\n");
}

int main(void) {
    puts("Running all tests...");
    puts("====================\n");
    
    testIsNumber();
    testCountCommas();
    testProcessCSV();
    
    puts("====================");
    puts("All tests passed!");
    
    return 0;
}
