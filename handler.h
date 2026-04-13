#ifndef HANDLER_H
#define HANDLER_H

#include "event.h"

typedef char *(*handler_func)(char *);

#define MAX_HANDLERS 100
typedef struct {
    char key[64];
    handler_func handlerfn;
} HandlerEntry;

typedef struct {
    HandlerEntry entries[MAX_HANDLERS];
    int size;
} HandlerMap;

void handler_map_init(HandlerMap *map);
int handler_on(HandlerMap *map, const char *key, handler_func fn);
handler_func handler_get(HandlerMap *map, const char *key);

#endif /* HANDLER_H */
