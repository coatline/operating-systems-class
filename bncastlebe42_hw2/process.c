#include "process.h"
#include "stack.h"

int spawn_process(int (*pfun)(void))
{
    /* TODO: allocate and initialize a process stack and PCB, then enqueue it. */
    (void)pfun;
    return -1;
}

void ready_to_run(void)
{
    Running = q_dequeue(&Ready_q);
}

void schedule(void)
{
    /* TODO: enqueue Running and select the next PCB from Ready_q. */
}

int p1(void)
{
    /* TODO: print process 1's counter and yield with dispatch(). */
    for (;;) { }
}

int p2(void)
{
    /* TODO: print process 2's counter and yield with dispatch(). */
    for (;;) { }
}

int p3(void)
{
    /* TODO: print process 3's counter and yield with dispatch(). */
    for (;;) { }
}

int p4(void)
{
    /* TODO: print process 4's counter and yield with dispatch(). */
    for (;;) { }
}
