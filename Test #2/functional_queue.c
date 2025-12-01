#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* f;
    Node* r;
} Queue;

Node* reverseList(Node* list) {
    Node* reversed = NULL;
    
    while (list != NULL) {
        Node* newNode = malloc(sizeof(Node));
        newNode->value = list->value;
        newNode->next = reversed;
        reversed = newNode;
        
        Node* to_free = list;
        list = list->next;
        free(to_free);
    }
    
    return reversed;
}

Queue* checkInvariant(Node* f, Node* r) {
    Queue* newQueue = malloc(sizeof(Queue));
    
    if (f != NULL) {
        newQueue->f = f;
        newQueue->r = r;
    } else {
        newQueue->f = reverseList(r);
        newQueue->r = NULL;
    }
    
    return newQueue;
}

Queue* enqueue(Queue* queue, int value) {
    if (queue == NULL) {
        return NULL;
    }
    
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = queue->r;
    
    return checkInvariant(queue->f, newNode);
}

int dequeue(Queue* queue, Queue** resultQueue) {
    if (queue == NULL || (queue->f == NULL && queue->r == NULL)) {
        *resultQueue = NULL;
        return 0;
    }
    
    Node* currentF = queue->f;
    
    if (currentF == NULL) {
        *resultQueue = NULL;
        return 0;
    }
    
    Node* newF = currentF->next;
    Node* r = queue->r;
    
    int dequeuedValue = currentF->value;
    
    *resultQueue = checkInvariant(newF, r);
    
    return dequeuedValue;
}