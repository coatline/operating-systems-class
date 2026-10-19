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
int print_progress(unsigned int, unsigned int, const char *, unsigned int, unsigned int);
int strlen(const char *s);

int main(void)
{
    init();
    if (spawn_process(p1) || spawn_process(p2) || spawn_process(p3) || spawn_process(p4))
        for (;;) { }
    ready_to_run();
    restore_context();
    for (;;) { }
}

void boot_win(void)
{
    const int pivotY = 17, pivotX = 4;
    const char *arr[] = {"Console", "Memory", "Kernel", "Interrupts", "Processes"};
    int length = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < length; ++i) {
        print_to(pivotY - i, pivotX, "[-]");
        print_to(pivotY - i, pivotX + 5, arr[length - i - 1]);
    }
    const int borderY = 21, borderX = 1, width = 56;
    for (int i = 0; i < 11; ++i) {
        if (i == 0 || i == 10) {
            for (int x = 0; x < width; ++x)
                print_to(borderY-i, borderX+x, (x == 0 || x == width-1) ? "+" : "-");
        } else {
            print_to(borderY-i, borderX, "|");
            print_to(borderY-i, borderX+width-1, "|");
        }
    }
}

int strlen(const char *s)
{
    int n = 0;
    while (s[n] != '\0') ++n;
    return n;
}
