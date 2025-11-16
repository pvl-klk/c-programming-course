#include "list_array.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int check_array_content(ListArray* list, int* expected, unsigned int expected_size) {
    if (list->size != expected_size) return 0;
    for (unsigned int i = 0; i < list->size; i++) {
        if (list->data[i] != expected[i]) return 0;
    }
    return 1;
}

void test_memory_management() {
    printf("Test: Memory management... ");
    
    ListArray* list = NULL;
    Status status = listArrayCreate(&list);
    assert(status == OK);
    assert(list != NULL);
    assert(list->size == 0);
    assert(list->data == NULL);
    
    assert(listArrayAdd(list, 10) == OK);
    assert(list->size == 1);
    assert(list->data != NULL);
    assert(list->data[0] == 10);
    
    assert(listArrayFree(list) == OK);
    printf("PASSED\n");
}

void test_add_remove_sequence() {
    printf("Test: Add/remove sequence... ");
    ListArray* list = NULL;
    listArrayCreate(&list);
    
    int values[] = {5, 3, 7, 1, 9};
    for (int i = 0; i < 5; i++) {
        assert(listArrayAdd(list, values[i]) == OK);
    }
    assert(list->size == 5);
    
    assert(listArraySort(list) == OK);
    int expected[] = {1, 3, 5, 7, 9};
    assert(check_array_content(list, expected, 5));
    
    assert(listArrayRemove(list, 5) == OK);
    assert(list->size == 4);
    
    assert(listArrayRemove(list, 1) == OK);
    assert(list->size == 3);
    
    assert(listArrayRemove(list, 9) == OK);
    assert(list->size == 2);
    
    int expected_remaining[] = {3, 7};
    assert(check_array_content(list, expected_remaining, 2));
    
    listArrayFree(list);
    printf("PASSED\n");
}

void test_sort_correctness() {
    printf("Test: Sort algorithm correctness... ");
    ListArray* list = NULL;
    listArrayCreate(&list);
    
    listArrayAdd(list, 1);
    listArrayAdd(list, 2);
    listArrayAdd(list, 3);
    assert(listArraySort(list) == OK);
    int expected1[] = {1, 2, 3};
    assert(check_array_content(list, expected1, 3));
    
    listArrayRemove(list, 1);
    listArrayRemove(list, 2);
    listArrayRemove(list, 3);
    
    listArrayAdd(list, 3);
    listArrayAdd(list, 2);
    listArrayAdd(list, 1);
    assert(listArraySort(list) == OK);
    int expected2[] = {1, 2, 3};
    assert(check_array_content(list, expected2, 3));
    
    listArrayRemove(list, 1);
    listArrayRemove(list, 2);
    listArrayRemove(list, 3);
    
    listArrayAdd(list, 4);
    listArrayAdd(list, 1);
    listArrayAdd(list, 3);
    listArrayAdd(list, 2);
    assert(listArraySort(list) == OK);
    int expected3[] = {1, 2, 3, 4};
    assert(check_array_content(list, expected3, 4));
    
    listArrayFree(list);
    printf("PASSED\n");
}

void test_edge_cases_detailed() {
    printf("Test: Detailed edge cases... ");
    
    ListArray* list = NULL;
    listArrayCreate(&list);
    listArrayAdd(list, 42);
    assert(listArrayRemove(list, 42) == OK);
    assert(list->size == 0);
    assert(list->data == NULL);
    
    listArrayAdd(list, 10);
    assert(listArrayRemove(list, 99) == NOT_INCLUDE_VALUE);
    assert(list->size == 1);
    
    ListArray* empty_list = NULL;
    listArrayCreate(&empty_list);
    assert(listArrayRemove(empty_list, 1) == EMPTY_LIST);
    
    listArrayAdd(empty_list, 100);
    assert(empty_list->size == 1);
    assert(empty_list->data[0] == 100);
    
    listArrayFree(list);
    listArrayFree(empty_list);
    printf("PASSED\n");
}

void test_error_conditions() {
    printf("Test: Error conditions... ");
    
    assert(listArrayCreate(NULL) == NULL_POINTER_ARGUMENT_ERROR);
    assert(listArrayAdd(NULL, 1) == NULL_POINTER_ARGUMENT_ERROR);
    assert(listArrayRemove(NULL, 1) == NULL_POINTER_ARGUMENT_ERROR);
    assert(listArrayFree(NULL) == NULL_POINTER_ARGUMENT_ERROR);
    assert(listArrayPrint(NULL) == NULL_POINTER_ARGUMENT_ERROR);
    assert(listArraySort(NULL) == NULL_POINTER_ARGUMENT_ERROR);
    
    ListArray* list = NULL;
    assert(listArrayCreate(&list) == OK);
    assert(listArrayAdd(list, 1) == OK);
    assert(listArraySort(list) == OK);

    FILE *original_stdout = stdout;
    freopen("/dev/null", "w", stdout);
    
    assert(listArrayPrint(list) == OK);

    freopen("/dev/tty", "w", stdout);

    assert(listArrayRemove(list, 1) == OK);
    assert(listArrayFree(list) == OK);
    
    printf("PASSED\n");
}

void test_large_sequence() {
    printf("Test: Large sequence operations... ");
    ListArray* list = NULL;
    listArrayCreate(&list);
    
    for (int i = 100; i >= 0; i--) {
        assert(listArrayAdd(list, i) == OK);
    }
    assert(list->size == 101);
    
    assert(listArraySort(list) == OK);
    
    for (unsigned int i = 0; i < list->size - 1; i++) {
        assert(list->data[i] <= list->data[i + 1]);
    }
    
    assert(list->data[0] == 0);
    assert(list->data[100] == 100);
    
    for (int i = 0; i <= 100; i++) {
        assert(listArrayRemove(list, i) == OK);
    }
    assert(list->size == 0);
    
    listArrayFree(list);
    printf("PASSED\n");
}

void test_duplicate_operations() {
    printf("Test: Duplicate value operations... ");
    ListArray* list = NULL;
    listArrayCreate(&list);
    
    for (int i = 0; i < 5; i++) {
        assert(listArrayAdd(list, 5) == OK);
    }
    assert(list->size == 5);
    
    assert(listArraySort(list) == OK);
    
    assert(listArrayRemove(list, 5) == OK);
    assert(list->size == 4);
    
    for (unsigned int i = 0; i < list->size; i++) {
        assert(list->data[i] == 5);
    }
    
    listArrayFree(list);
    printf("PASSED\n");
}

void run_all_tests(void) {
    printf("=== Running Comprehensive ListArray Tests ===\n\n");
    
    test_memory_management();
    test_add_remove_sequence();
    test_sort_correctness();
    test_edge_cases_detailed();
    test_error_conditions();
    test_large_sequence();
    test_duplicate_operations();
    
    printf("\n=== All tests PASSED! ===\n");
}

int run_main_program(void) {
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
            listArrayFree(numbers);
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

int main(int argc, char* argv[]) {
    if (argc == 2 && strcmp(argv[1], "--test") == 0) {
        run_all_tests();
        return 0;
    }
    else{
        return run_main_program();
    }
}