#include "process.h"
#include "stack.h"
#include "libos.h"

int spawn_process(int (*pfun)(void))
{
    Stack_t *stack = Stack_alloc();
    if (stack == 0) return -1;

    PCB_t *pcb = Pcb_alloc();
    if (pcb == 0) return -1;

    // Allocate space for process context (272 bytes)
    uint64_t *sp = stack->stack + _STACK_SIZE - 34;

    // initialize to 0
    for (int i = 0; i < 34; i++)
        sp[i] = 0;

    // Set ELR_EL1 to the function the process should run
    sp[30] = (uint64_t)pfun;

    pcb->stack = stack;
    pcb->sp = sp;
    pcb->pid = next_pid++;
    pcb->fun = pfun;

    q_enqueue(&Ready_q, pcb);

    return 0;
}

void ready_to_run(void)
{
    // if the queue is empty, return
    if(Ready_q.head == 0) return;

    Running = q_dequeue(&Ready_q);
}

void schedule(void)
{
    q_enqueue(&Ready_q, Running);
    Running = q_dequeue(&Ready_q);
}

int is_prime(int n);

int p1(void)
{
    print_to(16, 61, "Process 1: ");

    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            putc_to(16, 72, (char)('0' + i));
            is_prime(i);
        }
    }
}

int p2(void)
{
    print_to(18, 61, "Process 2: ");

    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            putc_to(18, 72, (char)('0' + i));
            is_prime(i);
        }
    }
}

int p3(void)
{
    print_to(16, 83, "Process 3: ");

    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            putc_to(16, 94, (char)('0' + i));
            is_prime(i);
        }
    }
}

int p4(void)
{
    print_to(18, 83, "Process 4: ");

    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            putc_to(18, 94, (char)('0' + i));
            is_prime(i);
        }
    }
}

int is_prime(int n)
{
    if (n <= 1) return 0;
    if (n == 2) return 1;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0) return 0;
    }
    return 1;
}
