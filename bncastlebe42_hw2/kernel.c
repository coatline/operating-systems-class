#include "libos.h"

#define true 1
#define false 0

void boot_win(void);
int print_progress(unsigned int row, unsigned int column, const char *message, unsigned int percent, unsigned int width);
int strlen(const char *s);

int main(void)
{
    init();
    
    int retval = spawn_process(p1);

    if (retval != 0){
        // Error

    }
    
    // Repeeat above for p2, p3, p4

    ready_to_run(); // Write in assembly
    restore_context(); // A function in assembler.
}

void init()
{
    boot_win();

    print_progress(19, 4, "Console: ", 0, 10);
    wait_msec(1000);
    uart_init();
    print_progress(19, 4, "Console: ", 50, 10);
    wait_msec(1000);
    lfb_init();
    print_progress(19, 4, "Console: ", 100, 10);
    wait_msec(1000);
    // print_progress(19, 4, "[OK] Console", 100, 10);

    print_progress(19, 4, "Memory: ", 0, 10);
    wait_msec(1000);
    init_pcb_heap();
    print_progress(19, 4, "Memory: ", 50, 10);
    wait_msec(1000);
    init_stack_heap();
    print_progress(19, 4, "Memory: ", 100, 10);
    wait_msec(1000);
    // print_progress(19, 4, "[OK] Memory", 100, 10);
    
    print_progress(19, 4, "Kernel: ", 0, 10);
    wait_msec(1000);
    q_init(Ready_q);
    print_progress(19, 4, "Kernel: ", 100, 10);
    wait_msec(1000);
}

void q_init(Queue_t *){
    
}

int spawn_process(int (*pfun)()){

}

void boot_win(void)
{
    const int pivotY = 17;
    const int pivotX = 4;

    const char *arr[] = {
        "Console",
        "Memory",
        "Kernel",
        "Interrupts",
        "Processes"
    };

    int length = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            print_to(pivotY - i, pivotX, "[OK]");
        }
        else
        {
            print_to(pivotY - i, pivotX, "[-]");
        }

        print_to(pivotY - i, pivotX + 5, arr[length - i - 1]);
    }

    const int borderPivotY = 21;
    const int borderPivotX = 1;
    const int borderWidth = 56;

    for (int i = 0; i < 11; i++)
    {
        if (i == 0 || i == 10)
        {
            for (int x = 0; x < borderWidth; x++)
            {
                if (x == 0 || x == 55)
                    print_to(borderPivotY - i, borderPivotX + x, "+");
                else
                    print_to(borderPivotY - i, borderPivotX + x, "-");
            }
        }
        else
        {
            print_to(borderPivotY - i, borderPivotX, "|");
            print_to(borderPivotY - i, borderPivotX + borderWidth - 1, "|");
        }
    }
}

int strlen(const char *s)
{
    int num = 0;

    while (s[num] != '\0')
    {
        num++;
    }

    return num;
}

struct Stack{
    struct Stack *next;
    alignas(16)uint64_t stack[_STACK_SIZE];
}

struct PCB{
    uint64_t *sp;
    int pid;
    struct PCB *next;
}
typedef struct PCB PCB_t;