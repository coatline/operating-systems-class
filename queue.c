#include "queue.h"

void q_init(PCB_Q_t *q)
{
    if (q == 0) return;
    q->head = 0;
    q->tail = 0;
}

void q_enqueue(PCB_Q_t *q, PCB_t *pcb)
{
    if (q == 0 || pcb == 0) return;

    pcb->next = 0;

    if (q->tail != 0)
        q->tail->next = pcb;
    else
        q->head = pcb;
    q->tail = pcb;
}

PCB_t *q_dequeue(PCB_Q_t *q)
{
    if (q == 0 || q->head == 0) return 0;

    PCB_t *pcb = q->head;
    q->head = pcb->next;
    if (q->head == 0)
        q->tail = 0;
    pcb->next = 0;
    return pcb;
}
