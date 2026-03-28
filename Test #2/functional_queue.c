#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* f;
    Node* r;
} Queue;

Node* reverseList(Node* list)
{
    Node* reversed = NULL;

    while (list != NULL) {
        Node* newNode = malloc(sizeof(Node));
        newNode->value = list->value;
        newNode->next = reversed;
        reversed = newNode;

        Node* toFree = list;
        list = list->next;
        free(toFree);
    }

    return reversed;
}

Queue* checkInvariant(Node* f, Node* r)
{
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

Queue* enqueue(Queue* queue, int value)
{
    if (queue == NULL) {
        return NULL;
    }

    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = queue->r;

    return checkInvariant(queue->f, newNode);
}

int dequeue(Queue* queue, Queue** resultQueue)
{
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

Queue* createEmptyQueue()
{
    Queue* queue = malloc(sizeof(Queue));
    queue->f = NULL;
    queue->r = NULL;
    return queue;
}

void freeQueue(Queue* queue)
{
    if (!queue)
        return;

    Node* current = queue->f;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    current = queue->r;
    while (current) {
        Node* next = current->next;
        free(current);
        current = next;
    }

    free(queue);
}

// TESTS

#include <assert.h>
#include <stdio.h>

void test_empty_queue()
{
    puts("Test 1: Empty queue");
    Queue* queue = createEmptyQueue();

    Queue* result;
    int value = dequeue(queue, &result);

    assert(value == 0);
    assert(result == NULL);
    puts("Empty queue test passed");

    freeQueue(queue);
}

void test_single_enqueue_dequeue()
{
    puts("Test 2: Single enqueue/dequeue");
    Queue* queue = createEmptyQueue();

    Queue* queue_1 = enqueue(queue, 42);
    assert(queue_1 != NULL);

    Queue* result;
    int value = dequeue(queue_1, &result);

    assert(value == 42);
    assert(result != NULL);

    int val2 = dequeue(result, &result);
    assert(val2 == 0);

    puts("Single enqueue/dequeue test passed");

    freeQueue(queue);
    freeQueue(queue_1);
    if (result) {
        freeQueue(result);
    }
}

void test_multiple_operations()
{
    puts("Test 3: Multiple enqueue/dequeue");
    Queue* queue = createEmptyQueue();

    Queue* queue_1 = enqueue(queue, 1);
    Queue* queue_2 = enqueue(queue_1, 2);
    Queue* queue_3 = enqueue(queue_2, 3);

    Queue* result;
    int value;

    value = dequeue(queue_3, &result);
    assert(value == 1);
    Queue* queue_4 = result;

    value = dequeue(queue_4, &result);
    assert(value == 2);
    Queue* queue_5 = result;

    value = dequeue(queue_5, &result);
    assert(value == 3);
    Queue* queue_6 = result;

    value = dequeue(queue_6, &result);
    assert(value == 0);

    puts("Multiple operations test passed");

    freeQueue(queue);
    freeQueue(queue_1);
    freeQueue(queue_2);
    freeQueue(queue_3);
    if (queue_4)
        freeQueue(queue_4);
    if (queue_5)
        freeQueue(queue_5);
    if (queue_6)
        freeQueue(queue_6);
    if (result)
        freeQueue(result);
}

void test_persistent_queue()
{
    puts("Test 4: Persistent queue");
    Queue* queue = createEmptyQueue();

    Queue* queue_1 = enqueue(queue, 10);
    Queue* queue_2 = enqueue(queue_1, 20);
    Queue* queue_3 = enqueue(queue_1, 30);

    Queue* result;
    int value_1, value_2;

    value_1 = dequeue(queue_2, &result);
    assert(value_1 == 10);
    freeQueue(result);

    value_2 = dequeue(queue_3, &result);
    assert(value_2 == 10);
    freeQueue(result);

    value_1 = dequeue(queue_1, &result);
    assert(value_1 == 10);
    freeQueue(result);

    puts("Persistent queue test passed");

    freeQueue(queue);
    freeQueue(queue_1);
    freeQueue(queue_2);
    freeQueue(queue_3);
}

void test_large_queue()
{
    puts("Test 5: Large queue (1000 elements)");
    Queue* queue = createEmptyQueue();
    Queue* current = queue;

    for (int index = 0; index < 1000; ++index) {
        current = enqueue(current, index);
        assert(current != NULL);
    }

    Queue* result;

    for (int index = 0; index < 1000; ++index) {
        int value = dequeue(current, &result);
        assert(value == index);
        freeQueue(current);
        current = result;
    }

    int value = dequeue(current, &result);
    assert(value == 0);

    puts("Large queue test passed");

    freeQueue(queue);
    if (current) {
        freeQueue(current);
    }
    if (result) {
        freeQueue(result);
    }
}

void test_queue_order()
{
    puts("Test 6: Queue order (FIFO)");
    Queue* queue = createEmptyQueue();
    Queue* current = queue;

    for (int index = 1; index <= 5; ++index) {
        current = enqueue(current, index);
    }

    Queue* result;
    int expected = 1;

    while (1) {
        int value = dequeue(current, &result);
        if (value == 0)
            break;

        assert(value == expected);
        expected++;

        freeQueue(current);
        current = result;
    }

    assert(expected == 6);

    puts("Queue order test passed");

    freeQueue(queue);
    if (current) {
        freeQueue(current);
    }
}

void test_balance_invariant()
{
    puts("Test 7: Balance invariant");
    Queue* queue = createEmptyQueue();
    Queue* current = queue;

    current = enqueue(current, 1);
    current = enqueue(current, 2);

    Queue* result;

    int value = dequeue(current, &result);
    assert(value == 1);
    freeQueue(current);
    current = result;

    value = dequeue(current, &result);
    assert(value == 2);
    freeQueue(current);
    current = result;

    assert(current->r == NULL);

    puts("Balance invariant test passed");

    freeQueue(queue);
    if (current) {
        freeQueue(current);
    }
}

void test_null_safety()
{
    puts("Test 8: Null safety");

    Queue* result_1 = enqueue(NULL, 42);
    assert(result_1 == NULL);

    Queue* result_2;
    int value = dequeue(NULL, &result_2);
    assert(value == 0);
    assert(result_2 == NULL);

    puts("Null safety test passed");
}

void test_memory_cleanup()
{
    puts("Test 9: Memory cleanup");
    Queue* queue = createEmptyQueue();

    for (int index = 0; index < 100; index++) {
        Queue* queue_1 = enqueue(queue, index);
        Queue* queue_2 = enqueue(queue_1, index * 2);

        Queue* result;
        dequeue(queue_2, &result);

        freeQueue(queue_1);
        freeQueue(queue_2);
        freeQueue(result);
    }

    freeQueue(queue);
    puts("Memory cleanup test passed (no crashes)");
}
