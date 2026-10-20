#include "libos.h"
#include "pcb.h"
#include "stack.h"
#include "queue.h"

PCB_t Pcbs[_MAX_PROCESSES];
PCB_t *Pcb_free_list;
Stack_t Stacks[_MAX_PROCESSES];
Stack_t *Stack_free_list;
PCB_Q_t Ready_q;
PCB_t *Running;
int next_pid = 1;

void init(void);
int spawn_process(int (*pfun)(void));
void ready_to_run(void);
void restore_context(void);
int p1(void), p2(void), p3(void), p4(void);
void boot_win(void);
void draw_process_boxes(void);
int print_progress(unsigned int, unsigned int, const char *, unsigned int, unsigned int);
int strlen(const char *s);

int main(void)
{
    init();
    draw_process_boxes();
    if (spawn_process(p1) || spawn_process(p2) || spawn_process(p3) || spawn_process(p4))
        while(1);

    ready_to_run();
    restore_context();

    while(1);
}

void draw_process_boxes(void)
{
    for (int process = 0; process < 4; process++)
    {
        int left = (process < 2) ? 3 : 25;
        int right = left + 15;
        int top = (process % 2 == 0) ? 10 : 12;
        int bottom = top + 2;

        for (int x = left; x <= right; x++)
        {
            print_to(top, x, (x == left || x == right) ? "+" : "-");
            print_to(bottom, x, (x == left || x == right) ? "+" : "-");
        }

        print_to(top + 1, left, "|");
        print_to(top + 1, right, "|");
    }

    print_to(11, 4, "Process 1: ");
    print_to(13, 4, "Process 2: ");
    print_to(11, 26, "Process 3: ");
    print_to(13, 26, "Process 4: ");
}

void boot_win(void)
{
    const int pivotY = 18, pivotX = 4;
    const int borderY = 22, borderX = 1, width = 56;
    const char *arr[] = {"Console", "Memory", "Kernel", "Interrupts", "Processes"};

    int length = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < length; i++)
    {
        print_to(pivotY - i, pivotX, "[-]");
        print_to(pivotY - i, pivotX + 5, arr[length - i - 1]);
    }

    for (int i = 0; i < 11; i++)
    {
        if (i == 0 || i == 10)
        {
            for (int x = 0; x < width; x++)
                print_to(borderY - i, borderX + x, (x == 0 || x == width - 1) ? "+" : "-");
        }
        else
        {
            print_to(borderY - i, borderX, "|");
            print_to(borderY - i, borderX + width - 1, "|");
        }
    }
}

int strlen(const char *s)
{
    int n = 0;

    while (s[n] != '\0')
    {
        n++;
    }

    return n;
}
