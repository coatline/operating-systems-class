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

    PCB_t *node = Pcb_alloc();

    if (node != 0) {
        *node = *pcb;
        node->next = 0;

        pcb->next = Pcb_free_list;
        Pcb_free_list = pcb;
    } else {
        node = pcb;
        node->next = 0;
    }

    if (q->tail != 0)
        q->tail->next = node;
    else
        q->head = node;
    q->tail = node;
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
