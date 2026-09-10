#include "libos.h"

#define true 1
#define false 0

void boot_win(void);
int print_progress(unsigned int row, unsigned int column, const char *message, unsigned int percent, unsigned int width);
int strlen(const char *s);

int main(void)
{
    boot_win();

    while (true)
    {
        for (int i = 10; i <= 100; i += 10)
        {
            print_progress(19, 4, "Progress: ", i, 10);
            wait_msec(500000);
        }
    }

    return 0;
}

void boot_win(void)
{
    int pivotY = 17;
    int pivotX = 4;

    const char *arr[] = {
        "Console",
        "Memory",
        "Kernel",
        "Interrupts",
        "Processes"
    };

    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
        {
            print_to(pivotY - i, pivotX, "[OK]");
        }
        else
        {
            print_to(pivotY - i, pivotX, "[-]");
        }

        print_to(pivotY - i, pivotX + 5, arr[i]);
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