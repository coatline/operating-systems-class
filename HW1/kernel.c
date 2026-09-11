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
            wait_msec(500);
        }
    }

    return 0;
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