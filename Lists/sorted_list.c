#include "list_array.h"
#include <stdio.h>

int main(void) {
    ListArray* numbers = NULL;
    Status status = listArrayCreate(&numbers);

    if (numbers == NULL || status != OK) {
        puts("Memory allocation error");
        return 1;
    }

    puts("Please enter one of the following commands: ");
    puts("0 - exit");
    puts("1 - add a value to the sorted array");
    puts("2 - remove a value from the sorted array");
    puts("3 - print the sorted array");
    puts("--------------------------------------------");

    while (1) {
        printf("Enter the command: ");
        int command = getchar();

        if (command == '\n') {
            puts("Invalid command!");
            continue;
        }

        int next = getchar();
        
        if (next == EOF || command == EOF) {
            puts("Input error occurred");
            return 1;
        }
        else if (next == '\n' && command == '0') {
            listArrayFree(numbers);
            return 0;
        }
        else if (next == '\n' && command == '1') {
            printf("Enter the value: ");
            int value;
            while (1) {
                if (scanf("%d", &value) == 1) {
                    while (getchar() != '\n');
                    break;
                } 
                else {
                    if (feof(stdin)) {
                        puts("\nInput terminated");
                        listArrayFree(numbers);
                        return 1;
                    }
                    printf("Incorrect value. Try again: ");
                    while (getchar() != '\n');
                }
            }   
            Status status_1 = listArrayAdd(numbers, value);
            Status status_2 = listArraySort(numbers);
            if (status_1 == OK && status_2 == OK) {
                printf("Value %d added successfully!\n", value);
            }
            else {
                puts("Failed to add value");
            }
        }
        else if (next == '\n' && command == '2') {
            printf("Enter the value: ");
            int value;
            while (1) {
                if (scanf("%d", &value) == 1) {
                    while (getchar() != '\n');
                    break;
                } 
                else {
                    if (feof(stdin)) {
                        puts("\nInput terminated");
                        listArrayFree(numbers);
                        return 1;
                    }
                    printf("Incorrect value. Try again: ");
                    while (getchar() != '\n');
                }
            }   
            Status status = listArrayRemove(numbers, value);
            if (status == OK) {
                printf("Value %d has been removed successfully!\n", value);
            }
            else if (status == EMPTY_LIST) {
                puts("List array is empty");
            }
            else if (status == NOT_INCLUDE_VALUE) {
                printf("List array does not include value %d\n", value);
            }
            else {
                puts("Something went wrong.");
            }
        }
        else if (next == '\n' && command == '3') {
            printf("Sorted list array: ");
            listArrayPrint(numbers);
        }
        else {
            puts("Invalid command");
            while (getchar() != '\n');
        }
    }
}
