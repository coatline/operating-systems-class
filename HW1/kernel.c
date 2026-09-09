#include <libos.h>
#define true 1
#define false 0


int main(void){
    boot_win();

    while(true){
        for(int i = 10; i < 100; i += 10){
            print_progress(19, 4, "Progress: ", i, 10);
            wait_msec(500000);
        }
    }

    return 0;
}

void boot_win(){
    print_to(10, 10, "Booting");
}

int print_progress(unsigned int row, unsigned int column, const char *message, unsigned int percent, unsigned int width);

int strlen(const char *s){
    int num = 0;
    
    while(s[num] != '\0'){
        num++;
    }
    
    return num;
}