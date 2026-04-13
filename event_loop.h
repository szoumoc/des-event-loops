#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "deque.h"
#include "handler.h"
#include "event.h"

typedef struct {
    Deque events;
    Deque processed_events;
    HandlerMap handlers;
} EventLoop;

void event_loop_init(EventLoop *loop);
void event_loop_dispatch(EventLoop *loop, Event *event);
void event_loop_run(EventLoop *loop);
void event_loop_free(EventLoop *loop);

/* produce output from an EventResult (helper) */
void produce_output(EventResult *res);

/* restored names for compatibility */
void processSync(EventLoop *loop, Event *event);
void processAsync(EventLoop *loop, Event *event);

#endif /* EVENT_LOOP_H */
