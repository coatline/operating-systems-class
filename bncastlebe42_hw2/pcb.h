#ifndef PCB_H
#define PCB_H

#include <stdint.h>

struct Stack;

struct PCB {
    uint64_t *sp;
    int pid;
    int (*fun)(void);
    struct Stack *stack;
    struct PCB *next;
};

typedef struct PCB PCB_t;

extern PCB_t Pcbs[10];
extern PCB_t *Pcb_free_list;

PCB_t *Pcb_alloc(void);
void init_pcb_heap(void);

#endif
