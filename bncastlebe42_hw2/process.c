#include "process.h"
#include "stack.h"
#include "libos.h"

int spawn_process(int (*pfun)(void))
{
    uint64_t *stack_memory = Stack_alloc();
    if (stack_memory == 0) return -1;

    PCB_t *pcb = Pcb_alloc();
    if (pcb == 0) return -1;

    // Clear data for a new register starting at the top of the stack
    uint64_t *sp = stack_memory + _STACK_SIZE;
    for (int i = 0; i < 32; i++)
        *--sp = 0;
    sp[31] = (uint64_t)pfun;

    // Find the Stack_t object that owns the stack memory
    for (int i = 0; i < _MAX_PROCESSES; i++)
    {
        if (Stacks[i].stack == stack_memory)
        {
            pcb->stack = &Stacks[i];
            break;
        }
    }

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
    print_to(11, 4, "Process 1: ");

    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            putc_to(11, 15, (char)('0' + i));
            is_prime(i);
            dispatch();
        }
    }
}

int p2(void)
{
    print_to(13, 4, "Process 2: ");

    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            putc_to(13, 15, (char)('0' + i));
            is_prime(i);
            dispatch();
        }
    }
}

int p3(void)
{
    print_to(11, 26, "Process 3: ");

    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            putc_to(11, 37, (char)('0' + i));
            is_prime(i);
            dispatch();
        }
    }
}

int p4(void)
{
    print_to(13, 26, "Process 4: ");

    while (1)
    {
        for (int i = 0; i < 10; i++)
        {
            putc_to(13, 37, (char)('0' + i));
            is_prime(i);
            dispatch();
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
