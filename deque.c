#include "deque.h"
#include <stdlib.h>

void initDeque(Deque *deque) {
    deque->head = NULL;
    deque->tail = NULL;
}

void pushback(Deque *deque, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = deque->tail;
    newNode->next = NULL;

    if (deque->tail) {
        deque->tail->next = newNode;
    } else {
        deque->head = newNode;
    }
    deque->tail = newNode;
}

void pushfront(Deque *deque, void *data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = deque->head;

    if (deque->head) {
        deque->head->prev = newNode;
    } else {
        deque->tail = newNode;
    }
    deque->head = newNode;
}

void *popfront(Deque *deque) {
    if (!deque->head) return NULL;
    Node *temp = deque->head;
    void *data = temp->data;
    deque->head = deque->head->next;
    if (deque->head) {
        deque->head->prev = NULL;
    } else {
        deque->tail = NULL;
    }
    free(temp);
    return data;
}

void *popback(Deque *deque) {
    if (!deque->tail) return NULL;
    Node *temp = deque->tail;
    void *data = temp->data;
    deque->tail = deque->tail->prev;
    if (deque->tail) {
        deque->tail->next = NULL;
    } else {
        deque->head = NULL;
    }
    free(temp);
    return data;
}

void deque_free(Deque *deque) {
    while (deque->head) {
        void *p = popfront(deque);
        (void)p; /* caller is responsible for freeing stored data if needed */
    }
}