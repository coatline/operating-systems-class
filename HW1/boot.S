.global boot_win
.type boot_win, %function

.section .text
// int print_progress(unsigned int row, unsigned int column, const char *message, unsigned int percent, unsigned int width);  
print_progress:
    sub sp, sp, 16
    str x30, [sp]
    loop:
        
        
        b loop

    end_loop:
    .return_with_with_error:
        mov w0, 1
        b done
    .return_okay:
        mov w0, 0
    .done:
        ldr x30, [sp]
        add sp, sp, 16
        ret