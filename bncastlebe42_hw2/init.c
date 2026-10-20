#include "libos.h"
#include "pcb.h"
#include "stack.h"
#include "queue.h"

extern PCB_Q_t Ready_q;
void boot_win(void);
int print_progress(unsigned int row, unsigned int column, const char *message, unsigned int percent, unsigned int width);

void init(void)
{
    int wait_time = 1000000;
    boot_win();

    print_progress(19, 4, "Console: ", 0, 20);
    wait_msec(wait_time);
    uart_init();
    print_progress(19, 4, "Console: ", 50, 20);
    wait_msec(wait_time);
    lfb_init();
    boot_win();
    print_progress(19, 4, "Console: ", 100, 20);
    wait_msec(wait_time);
    print_to(14, 4, "[OK]");
    
    print_progress(19, 4, "Memory: ", 0, 20);
    wait_msec(wait_time);
    init_pcb_heap();
    print_progress(19, 4, "Memory: ", 50, 20);
    wait_msec(wait_time);
    init_stack_heap();
    print_progress(19, 4, "Memory: ", 100, 20);
    wait_msec(wait_time);
    print_to(15, 4, "[OK]");
    
    print_progress(19, 4, "Kernel: ", 0, 20);
    wait_msec(wait_time);
    q_init(&Ready_q);
    print_progress(19, 4, "Kernel: ", 100, 20);
    wait_msec(wait_time);
    print_to(16, 4, "[OK]");
}


#include <stdint.h>

extern PCB_t Pcbs[_MAX_PROCESSES];
extern PCB_t *Pcb_free_list;
extern Stack_t Stacks[_MAX_PROCESSES];
extern Stack_t *Stack_free_list;

void init_pcb_heap(void)
{
    Pcb_free_list = &Pcbs[0];
    for (int i = 0; i < _MAX_PROCESSES; i++)
        Pcbs[i].next = (i + 1 < _MAX_PROCESSES) ? &Pcbs[i + 1] : 0;
}

PCB_t *Pcb_alloc(void)
{
    if (Pcb_free_list == 0) return 0;
    PCB_t *pcb = Pcb_free_list;
    Pcb_free_list = pcb->next;
    pcb->next = 0;
    return pcb;
}

void init_stack_heap(void)
{
    Stack_free_list = &Stacks[0];
    for (int i = 0; i < _MAX_PROCESSES; i++)
        Stacks[i].next = (i + 1 < _MAX_PROCESSES) ? &Stacks[i + 1] : 0;
}

uint64_t *Stack_alloc(void)
{
    if (Stack_free_list == 0) return 0;
    Stack_t *stack = Stack_free_list;
    Stack_free_list = stack->next;
    stack->next = 0;
    return stack->stack;
}
