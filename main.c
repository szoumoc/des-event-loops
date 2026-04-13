#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "event.h"
#include "event_loop.h"

/* Example handler used for a simple smoke test */
char *example_handler(char *data) {
    (void)data;
    return "handler-result";
}

int main(void) {
    EventLoop loop;
    event_loop_init(&loop);

    /* register a handler */
    handler_on(&loop.handlers, "test", example_handler);

    /* create an event and dispatch */
    Event *e = (Event *)malloc(sizeof(Event));
    strncpy(e->key, "test", sizeof(e->key)-1);
    e->key[sizeof(e->key)-1] = '\0';
    strncpy(e->data, "payload", sizeof(e->data)-1);
    e->data[sizeof(e->data)-1] = '\0';
    e->is_async = 0;

    event_loop_dispatch(&loop, e);
    event_loop_run(&loop);

    /* cleanup */
    free(e);
    event_loop_free(&loop);
    return 0;
}