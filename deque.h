#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

typedef struct Node {
	void *data;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
} Deque;

void initDeque(Deque *deque);

void pushback(Deque *deque, void *data);
void pushfront(Deque *deque, void *data);

void *popfront(Deque *deque);
void *popback(Deque *deque);

void deque_free(Deque *deque);

#endif
