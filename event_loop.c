#include "event_loop.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

/* Simple producer for EventResult */
void produce_output(EventResult *res) {
    if (!res) return;
    printf("[output] key=%s result=%s\n", res->key, res->result);
}

void event_loop_init(EventLoop *loop) {
    initDeque(&loop->events);
    initDeque(&loop->processed_events);
    handler_map_init(&loop->handlers);
}

void event_loop_dispatch(EventLoop *loop, Event *event) {
    pushback(&loop->events, event);
}

void event_loop_free(EventLoop *loop) {
    deque_free(&loop->events);
    deque_free(&loop->processed_events);
}

/* process synchronously: call handler and immediately produce output */
void processSync(EventLoop *loop, Event *event) {
    handler_func fn = handler_get(&loop->handlers, event->key);
    if (!fn) return;

    char *result = fn(event->data);

    EventResult res;

    strncpy(res.key, event->key, sizeof(res.key) - 1);
    res.key[sizeof(res.key) - 1] = '\0';

    strncpy(res.result, result ? result : "", sizeof(res.result) - 1);
    res.result[sizeof(res.result) - 1] = '\0';

    produce_output(&res);
}
typedef struct {
    EventLoop *loop;
    Event *event;
} AsyncArgs;
/* Worker function for async processing */
void* async_worker(void *arg) {
    AsyncArgs *args = (AsyncArgs*)arg;

    handler_func fn = handler_get(&args->loop->handlers, args->event->key);

    if (fn != NULL) {
        char *result = fn(args->event->data);

        EventResult *res = malloc(sizeof(EventResult));
        strcpy(res->key, args->event->key);
        strcpy(res->result, result);

        pushBack(&args->loop->processed_events, res);
    }

    free(args->event);
    free(args);

    return NULL;
}

/* process asynchronously: call handler and push result to processed_events */
void processAsync(EventLoop *loop, Event *event) {
    AsyncArgs *args = malloc(sizeof(AsyncArgs));
    args->loop = loop;
    args->event = event;

    pthread_t thread;
    pthread_create(&thread, NULL, async_worker, args);
    pthread_detach(thread);
    
}

/* restored run implementation with millisecond timing similar to the Java example */
void event_loop_run(EventLoop *loop) {
    Event *event = (Event *)popfront(&loop->events);
    if (event != NULL) {
        printf("\nReceived Event: %s\n", event->key);

        if (handler_get(&loop->handlers, event->key) != NULL) {
            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            if (event->is_async) {
                processAsync(loop, event);
            } else {
                processSync(loop, event);
            }

            clock_gettime(CLOCK_MONOTONIC, &end);
            long ms = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
            printf("\nEvent Loop was blocked for %ld ms due to this operation \n\n", ms);
        } else {
            printf("No handler found for %s\n\n", event->key);
        }
    }

    EventResult *processedEvent = (EventResult *)popfront(&loop->processed_events);
    if (processedEvent != NULL) {
        produce_output(processedEvent);
        free(processedEvent);
    }
}
void produce_output(EventResult *res) {
    if (!res) return;
    printf("[output] key=%s result=%s\n", res->key, res->result);
}

