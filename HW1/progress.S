.global print_progress
.type print_progress, %function
.extern print_to // (row, column, label address)
.extern strlen // (const char *s)
.extern putc_to // (row, column, character)

.section .text
// unsigned int = 32 bits
// char * (address) = 64 bits
// int print_progress(unsigned int row, unsigned int column, const char *message, unsigned int percent, unsigned int width);  
print_progress:
    // Make room for 8 items to store on the stack
    sub sp, sp, #80

    // Save the return address that is stored in the link register
    str x30, [sp]
    // Save the frame pointer for debuggers
    str x29, [sp, #8]
    
    // Save the currently stored values of the preserved registers in the stack.
    // Registers x19 - x28 are preserved registers (every function should save their values first so that we can restore them)
    str x19, [sp, #16]
    str x20, [sp, #24]
    str x21, [sp, #32]
    str x22, [sp, #40]
    str x23, [sp, #48]
    str x24, [sp, #56]
    str x25, [sp, #64]
    str x26, [sp, #72]

    // Move incoming parameters into preserved registers
    mov w19, w0 // row (int)
    mov w20, w1 // column (int)
    mov x21, x2 // message (address - 64 bits so x register)
    mov w22, w3 // percent (int)
    mov w23, w4 // width (int)

    // row
    mov w0, w19
    // column
    mov w1, w20
    // label address
    mov x2, x21
    bl print_to

    // If percent > 100 return with error
    cmp w22, #100
    bhi .return_with_error

    // w24 = the number of '=' to draw
    // (percent * width) / 100
    mul w24, w22, w23
    mov w25, #100
    udiv w24, w24, w25

    // Get the length of the label string
    mov x0, x21 // message address parameter
    bl strlen
    mov w25, w0 // w25 = the length of the label string

    mov w26, #'='

    .loop:
        // If there are no more '=' characters to draw, use spaces
        cmp w24, #0
        bne .check_width        
        mov w26, #' '
    .check_width:
        // if width is 0
        cmp w23, #0
        // return success
        beq .return_okay

        // call putc_to(row, column + length, character)
        mov w0, w19
        add w1, w20, w25
        mov w2, w26
        bl putc_to

        // add 1 to column
        add w20, w20, #1

        // sub 1 from count of equal signs only if the number of equal signs is greater than 0
        cmp w24, #0
        beq .skip
        sub w24, w24, #1

    .skip:
        // Decrement width by 1
        sub w23, w23, #1

        b .loop

    .return_with_error:
        mov w0, 1
        b .done

    .return_okay:
        mov w0, 0
    
    .done:
        // Restore preserved registers from the stack
        ldr x26, [sp, #72]
        ldr x25, [sp, #64]
        ldr x24, [sp, #56]
        ldr x23, [sp, #48]
        ldr x22, [sp, #40]
        ldr x21, [sp, #32]
        ldr x20, [sp, #24]
        ldr x19, [sp, #16]

        ldr x29, [sp, #8]
        ldr x30, [sp]

        // Free the stack space
        add sp, sp, #64
        // Return to the address in x30
        ret