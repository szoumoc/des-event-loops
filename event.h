#ifndef EVENT_H
#define EVENT_H

#include <stdlib.h>

typedef struct {
    char key[64];
    char data[256];
    int is_async;
} Event;

typedef struct{
    char key[64];
    char result[256];
} EventResult;

#endif /* EVENT_H */
