#include "queue.h"

void q_init(PCB_Q_t *q)
{
    q->head = 0;
    q->tail = 0;
}

void q_enqueue(PCB_Q_t *q, PCB_t *pcb)
{
    /* TODO: link pcb at the tail of the ready queue. */
    (void)q;
    (void)pcb;
}

PCB_t *q_dequeue(PCB_Q_t *q)
{
    /* TODO: remove and return the PCB at the head of the queue. */
    (void)q;
    return 0;
}
