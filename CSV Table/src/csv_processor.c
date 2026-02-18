#include "csv_processor.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для проверки типа данных
int isNumber(const char* string)
{
    if (string == NULL || *string == '\0') {
        return 0;
    }

    int hasDecimal = 0;
    for (const char* pointer = string; *pointer; ++pointer) {
        if (*pointer == '.') {
            if (hasDecimal) {
                return 0;
            }
            hasDecimal = 1;
        } else if (!isdigit(*pointer)) {
            return 0;
        }
    }
    return 1;
}

// Функция для подсчета количества запятых в строке
int countCommas(const char* string)
{
    int count = 0;
    for (const char* pointer = string; *pointer; ++pointer) {
        if (*pointer == ',') {
            ++count;
        }
    }
    return count;
}

int processCSV(const char* pathToCSV, const char* pathToTextFile)
{
    // Открываем CSV файл
    FILE* csvFile = fopen(pathToCSV, "r");
    if (csvFile == NULL) {
        puts("File openning error");
        return 1;
    }

    // Читаем файл целиком
    fseek(csvFile, 0, SEEK_END);
    long fileSize = ftell(csvFile);
    fseek(csvFile, 0, SEEK_SET);

    char* buffer = malloc(fileSize + 1);
    if (buffer == NULL) {
        puts("Memory allocation error");
        fclose(csvFile);
        return 1;
    }

    size_t bytesRead = fread(buffer, 1, fileSize, csvFile);
    if (bytesRead != fileSize) {
        puts("File read error");
        free(buffer);
        fclose(csvFile);
        return 1;
    }
    buffer[fileSize] = '\0';

    fclose(csvFile);

    // Создаем копию буффера для подсчета количества строк и столбцов
    char* bufferForCount = malloc(fileSize + 1);
    if (bufferForCount == NULL) {
        puts("Memory allocation error");
        free(buffer);
        return 1;
    }
    strcpy(bufferForCount, buffer);

    // Подсчитываем количество строк и максимальное количество столбцов
    unsigned int rowsNumber = 0;
    unsigned int maxColumns = 0;

    char* context = NULL;
    char* line = strtok_r(bufferForCount, "\n", &context);

    while (line != NULL) {
        ++rowsNumber;

        // Подсчитываем количество столбцов в этой строке (запятые + 1)
        int commas = countCommas(line);
        int columnsInLine = commas + 1;

        if (columnsInLine > maxColumns) {
            maxColumns = columnsInLine;
        }

        line = strtok_r(NULL, "\n", &context);
    }

    // Проверяем, что файл не пустой
    if (rowsNumber == 0 || maxColumns == 0) {
        free(bufferForCount);
        free(buffer);
        FILE* textFile = fopen(pathToTextFile, "w");
        if (textFile == NULL) {
            puts("File openning error");
            return 1;
        } else {
            fclose(textFile);
            return 0;
        }
    }

    // Создаем таблицу
    char*** table = malloc(sizeof(char**) * rowsNumber);
    if (table == NULL) {
        puts("Memory allocation error");
        free(bufferForCount);
        free(buffer);
        return 1;
    }

    for (int rowIndex = 0; rowIndex < rowsNumber; ++rowIndex) {
        table[rowIndex] = calloc(maxColumns, sizeof(char*));
        if (table[rowIndex] == NULL) {
            puts("Memory allocation error");
            // Очищаем память в случае ошибки
            for (int index = 0; index < rowIndex; ++index) {
                free(table[index]);
            }
            free(table);
            free(bufferForCount);
            free(buffer);
            return 1;
        }
    }

    // Создаем массив с размерами столбцов
    unsigned int* columnsSizes = calloc(maxColumns, sizeof(unsigned int));
    if (columnsSizes == NULL) {
        puts("Memory allocation error");
        for (int index = 0; index < rowsNumber; ++index) {
            free(table[index]);
        }
        free(table);
        free(bufferForCount);
        free(buffer);
        return 1;
    }

    // Заполняем таблицу значениями, используя оригинальный буффер
    context = NULL;
    line = strtok_r(buffer, "\n", &context);
    unsigned int rowIndex = 0;

    while (line != NULL && rowIndex < rowsNumber) {
        // Создаем копию строки для обработки
        char* lineCopy = malloc(strlen(line) + 1);
        if (lineCopy == NULL) {
            puts("Memory allocation error");
            // Очищаем уже выделенную память
            for (int index_1 = 0; index_1 < rowIndex; ++index_1) {
                for (int index_2 = 0; index_2 < maxColumns; ++index_2) {
                    free(table[index_1][index_2]);
                }
                free(table[index_1]);
            }
            free(table);
            free(columnsSizes);
            free(bufferForCount);
            free(buffer);
            return 1;
        }
        strcpy(lineCopy, line);

        unsigned int columnIndex = 0;

        // Обрабатываем строку вручную, чтобы не пропускать пустые значения
        char* start = lineCopy;

        for (char* current = lineCopy; *current != '\0'; ++current) {
            if (*current == ',') {
                // Встретили запятую - извлекаем значение от start до current
                *current = '\0';

                // Удаляем пробелы в начале и конце
                char* value = start;
                while (isspace(*value)) {
                    ++value;
                }

                char* end = value + strlen(value) - 1;
                while (end > value && isspace(*end)) {
                    --end;
                }
                *(end + 1) = '\0';

                // Сохраняем значение (даже пустое)
                table[rowIndex][columnIndex] = strdup(value);

                size_t length = strlen(value);
                if (length > columnsSizes[columnIndex]) {
                    columnsSizes[columnIndex] = length;
                }

                ++columnIndex;
                // Следующее значение начинается после запятой
                start = current + 1;
            }
        }

        // Обрабатываем последнее значение (после последней запятой или единственное)
        if (columnIndex < maxColumns) {
            // Удаляем пробелы в начале и конце
            char* value = start;
            while (isspace(*value)) {
                ++value;
            }

            char* end = value + strlen(value) - 1;
            while (end > value && isspace(*end)) {
                --end;
            }
            *(end + 1) = '\0';

            table[rowIndex][columnIndex] = strdup(value);

            size_t length = strlen(value);
            if (length > columnsSizes[columnIndex]) {
                columnsSizes[columnIndex] = length;
            }

            ++columnIndex;
        }

        // Заполняем оставшиеся столбцы пустыми строками
        while (columnIndex < maxColumns) {
            table[rowIndex][columnIndex] = strdup("");
            ++columnIndex;
        }

        free(lineCopy);
        line = strtok_r(NULL, "\n", &context);
        ++rowIndex;
    }

    // Создаем файл для записи таблицы
    FILE* textFile = fopen(pathToTextFile, "w");
    if (textFile == NULL) {
        puts("File openning error");
        // Очищаем память в случае ошибки
        for (int rowIndex = 0; rowIndex < rowsNumber; ++rowIndex) {
            for (int columnIndex = 0; columnIndex < maxColumns; ++columnIndex) {
                free(table[rowIndex][columnIndex]);
            }
            free(table[rowIndex]);
        }
        free(table);
        free(columnsSizes);
        free(bufferForCount);
        free(buffer);
        return 1;
    }

    // Отрисовываем верхнюю границу
    fputs("╔", textFile);
    for (int columnIndex = 0; columnIndex < maxColumns; ++columnIndex) {
        for (int index = 0; index < columnsSizes[columnIndex] + 2; ++index) {
            fputs("═", textFile);
        }
        if (columnIndex < maxColumns - 1) {
            fputs("╦", textFile);
        }
    }
    fputs("╗\n", textFile);

    // Отрисовываем строки данных
    for (int rowIndex = 0; rowIndex < rowsNumber; ++rowIndex) {
        fputs("║", textFile);

        for (int columnIndex = 0; columnIndex < maxColumns; ++columnIndex) {
            char* value = table[rowIndex][columnIndex] ? table[rowIndex][columnIndex] : "";
            int width = columnsSizes[columnIndex];

            fputs(" ", textFile);

            // Определяем выравнивание
            if (rowIndex == 0) {
                // Заголовок (первая строка) - всегда влево
                fprintf(textFile, "%-*s", width, value);
            } else {
                // Данные - выравнивание по типу
                if (isNumber(value)) {
                    // Число - по правому краю
                    fprintf(textFile, "%*s", width, value);
                } else {
                    // Текст - по левому краю
                    fprintf(textFile, "%-*s", width, value);
                }
            }

            fputs(" ", textFile);

            // Для первой строки (заголовка) используем ║, для остальных │
            if (columnIndex < maxColumns - 1) {
                if (rowIndex == 0) {
                    fputs("║", textFile); // Двойная вертикальная черта для заголовка
                } else {
                    fputs("│", textFile); // Одинарная вертикальная черта для данных
                }
            }
        }
        fputs("║\n", textFile);

        // Разделитель (не после последней строки)
        if (rowIndex < rowsNumber - 1) {
            if (rowIndex == 0) {
                // После заголовка - двойная линия
                fputs("╠", textFile);
                for (int columnIndex = 0; columnIndex < maxColumns; ++columnIndex) {
                    for (int index = 0; index < columnsSizes[columnIndex] + 2; ++index) {
                        fputs("═", textFile);
                    }
                    if (columnIndex < maxColumns - 1) {
                        fputs("╬", textFile);
                    }
                }
                fputs("╣\n", textFile);
            } else {
                // Между строками данных - одинарная линия
                fputs("╠", textFile);
                for (int columnIndex = 0; columnIndex < maxColumns; ++columnIndex) {
                    for (int index = 0; index < columnsSizes[columnIndex] + 2; ++index) {
                        fputs("─", textFile);
                    }
                    if (columnIndex < maxColumns - 1) {
                        fputs("┼", textFile);
                    }
                }
                fputs("╣\n", textFile);
            }
        }
    }

    // Нижняя граница
    fputs("╚", textFile);
    for (int columnIndex = 0; columnIndex < maxColumns; columnIndex++) {
        for (int index = 0; index < columnsSizes[columnIndex] + 2; ++index) {
            fputs("═", textFile);
        }
        if (columnIndex < maxColumns - 1) {
            fputs("╧", textFile);
        }
    }
    fputs("╝\n", textFile);

    // Освобождение памяти
    for (int rowIndex = 0; rowIndex < rowsNumber; ++rowIndex) {
        for (int columnIndex = 0; columnIndex < maxColumns; ++columnIndex) {
            free(table[rowIndex][columnIndex]);
        }
        free(table[rowIndex]);
    }
    free(table);
    free(columnsSizes);
    free(bufferForCount);
    free(buffer);
    fclose(textFile);
    return 0;
}
