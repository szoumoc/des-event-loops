#include "handler.h"
#include <string.h>

void handler_map_init(HandlerMap *map) {
    map->size = 0;
}

int handler_on(HandlerMap *map, const char *key, handler_func fn) {
    if (map->size >= MAX_HANDLERS) return -1;
    strncpy(map->entries[map->size].key, key, sizeof(map->entries[map->size].key)-1);
    map->entries[map->size].key[sizeof(map->entries[map->size].key)-1] = '\0';
    map->entries[map->size].handlerfn = fn;
    map->size++;
    return 0;
}

handler_func handler_get(HandlerMap *map, const char *key) {
    for (int i = 0; i < map->size; ++i) {
        if (strcmp(map->entries[i].key, key) == 0) {
            return map->entries[i].handlerfn;
        }
    }
    return NULL;
}
