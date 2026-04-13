#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char key[64];
    char data[256];
    int is_async;
} Event;

typedef struct{
    char key[64];
    char result[256];
} EventResult;

typedef struct Node{
    void *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Deque;

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

void popfront(Deque *deque) {
    if (deque->head) {
        Node *temp = deque->head;
        deque->head = deque->head->next;
        if (deque->head) {
            deque->head->prev = NULL;
        } else {
            deque->tail = NULL;
        }
        free(temp);
    }
}
void popback(Deque *deque) {
    if (deque->tail) {
        Node *temp = deque->tail;
        deque->tail = deque->tail->prev;
        if (deque->tail) {
            deque->tail->next = NULL;
        } else {
            deque->head = NULL;
        }
        free(temp);
    }
}
void free(Deque *deque) {
    while (deque->head) {
        popfront(deque);
    }
}

typedef char *(*handler_func)(char *);

typedef struct {
    char *key[64];
    handler_func handlerfn;
} HandlerEntry;

#define MAX_HANDLERS 100
typedef struct {
    HandlerEntry entries[MAX_HANDLERS];
    int size;
} HandlerMap;

typedef struct {
    Deque events;
    Deque processed_events;
    HandlerMap handlers;
} EventLoop;


void on(EventLoop *loop, char *key, handler_func fn) {
    strcpy(loop->handlers.entries[loop->handlers.size].key, key); 
    loop->handlers.entries[loop->handlers.size].handlerfn = fn;
    loop->handlers.size++;
}

void dispatch(EventLoop *loop, Event *event) {
    pushback(&loop->events, event);
}

int main() {
    return 0;
}