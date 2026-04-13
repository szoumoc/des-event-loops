/* deque.h
 * Minimal, stable interface for a simple double-ended queue (Deque).
 * The implementation stores opaque pointers (void*) and pop operations
 * return the stored pointer (or NULL when empty). Callers own the
 * pointed-to objects and are responsible for freeing them when needed.
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <stddef.h>

/* Node is intentionally exposed here for simplicity; it can be made
 * opaque later if desired. */
typedef struct Node {
	void *data;
	struct Node *prev;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
} Deque;

/* Initialize an empty deque. */
void initDeque(Deque *deque);

/* Push an element to the back/front (ownership remains with caller). */
void pushback(Deque *deque, void *data);
void pushfront(Deque *deque, void *data);

/* Pop an element from the front/back and return the stored data pointer,
 * or NULL if the deque is empty. Caller is responsible for freeing
 * the returned pointer if it was heap-allocated. */
void *popfront(Deque *deque);
void *popback(Deque *deque);

/* Drain the deque (frees internal nodes). This does NOT free the
 * stored data pointers; caller should free them if necessary. */
void deque_free(Deque *deque);

#endif /* DEQUE_H */
