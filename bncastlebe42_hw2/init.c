#include "libos.h"
#include "pcb.h"
#include "stack.h"
#include "queue.h"

extern PCB_Q_t Ready_q;
void boot_win(void);
int print_progress(unsigned int row, unsigned int column, const char *message, unsigned int percent, unsigned int width);

void init(void)
{
    boot_win();
    print_progress(19, 4, "Console: ", 0, 20);
    wait_msec(1000000);
    uart_init();
    print_progress(19, 4, "Console: ", 50, 20);
    wait_msec(1000000);
    lfb_init();
    print_progress(19, 4, "Console: ", 100, 20);
    wait_msec(1000000);
    print_to(13, 4, "[OK]");

    print_progress(19, 4, "Memory: ", 0, 20);
    wait_msec(1000000);
    init_pcb_heap();
    print_progress(19, 4, "Memory: ", 50, 20);
    wait_msec(1000000);
    init_stack_heap();
    print_progress(19, 4, "Memory: ", 100, 20);
    wait_msec(1000000);
    print_to(12, 4, "[OK]");

    print_progress(19, 4, "Kernel: ", 0, 20);
    wait_msec(1000000);
    q_init(&Ready_q);
    print_progress(19, 4, "Kernel: ", 100, 20);
    wait_msec(1000000);
    print_to(11, 4, "[OK]");
}


#include <stdint.h>

extern PCB_t Pcbs[10];
extern PCB_t *Pcb_free_list;
extern Stack_t Stacks[10];
extern Stack_t *Stack_free_list;

void init_pcb_heap(void)
{
    Pcb_free_list = &Pcbs[0];
    for (int i = 0; i < 10; i++) Pcbs[i].next = (i < 9) ? &Pcbs[i + 1] : 0;
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
    for (int i = 0; i < 10; i++) Stacks[i].next = (i < 9) ? &Stacks[i + 1] : 0;
}

uint64_t *Stack_alloc(void)
{
    if (Stack_free_list == 0) return 0;
    Stack_t *stack = Stack_free_list;
    Stack_free_list = stack->next;
    stack->next = 0;
    return stack->stack;
}
