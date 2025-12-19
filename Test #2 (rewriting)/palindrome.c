#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct NodeStruct {
    struct NodeStruct* next;
    int value;
} Node;

typedef struct {
    Node* first;
    Node* last;
} List;

void listCheckInvariant(List* list) {
    assert((list -> first == NULL) == (list -> last == NULL));
}

List* listCreate(void) {
    List* list = malloc(sizeof(List));
    if (list == NULL) {
        puts("Memory allocation error");
        exit(1);
    }

    list -> first = NULL;
    list -> last = NULL;
    return list;
}

void listAppend(List* list, int value) {
    if (list == NULL) {
        puts("NULL pointer provided");
        exit(1);
    }
    listCheckInvariant(list);

    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        puts("Memory allocation error");
        exit(1);
    }

    node -> value = value;
    node -> next = NULL;

    if (list -> first == NULL) {
        list -> first = node;
    }
    else {
        list -> last -> next = node;
    }
    list -> last = node;
}

int listGetValueByIndex(List* list, unsigned int index) {
    if (list == NULL) {
        puts("NULL pointer provided");
        exit(1);
    }
    listCheckInvariant(list);

    unsigned int currentIndex = 0;
    Node* current = list -> first;
    while (current -> next != NULL && currentIndex != index) {
        current = current -> next;
        ++currentIndex;
    }

    if (currentIndex == index) {
        return current -> value;
    }
    
    puts("Index out of range");
    exit(1);
}

void listDestroy(List* list) {
    if (list == NULL) {
        return;
    }

    Node* current = list->first;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

int main(void) {
    List* list = listCreate();
    puts("Enter the numbers (Enter Ctrl+D/Ctrl+Z to exit): ");

    int length = 0;
    int number;
    while (scanf("%d", &number) == 1) {
        listAppend(list, number);
        ++length;
    }

    for (int index = 0; index < length / 2; ++index) {
        if (listGetValueByIndex(list, index) != listGetValueByIndex(list, length-1-index)) {
            puts("List is not symmetric");
            return 0;
        }
    }
    puts("List is symmetric");

    listDestroy(list);

    return 0;
}
