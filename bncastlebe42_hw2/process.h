#ifndef PROCESS_H
#define PROCESS_H

#include "pcb.h"
#include "queue.h"

extern PCB_t *Running;
extern int next_pid;

int spawn_process(int (*pfun)(void));
void ready_to_run(void);
void schedule(void);
void restore_context(void);
void dispatch(void);
void save_rest_of_context(void);

int p1(void);
int p2(void);
int p3(void);
int p4(void);

#endif
