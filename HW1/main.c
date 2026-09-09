// #include <stdbool.h>
#define true 1
#define false 0

int main(void){
    boot_win();

    while(true){
        for(int i = 10; i < 100; i += 10){
            print_progress(19, 4, "Progress: ", i, 10)
            wait_msec(500000)
        }
    }

    return 0;
}

void boot_win(){

}

void print_progress(){

}

void wait_msec(){

}