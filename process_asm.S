.text

.global dispatch
.type dispatch, %function
dispatch:
    # save caller's frame pointer and return address
    stp x29, x30, [sp, #-16]!

    bl save_rest_of_context
    ldp x29, x30, [sp], #16  // restore caller's frame pointer and return address
    bl schedule
    bl restore_context 

.global save_rest_of_context
.type save_rest_of_context, %function
save_rest_of_context:
    // xzr is the zero register, save x1 on the stack so we can use it to store the current OS stack pointer
    stp     xzr, x1, [sp, -16]!

    // put the current stack pointer into x1
    mrs x1, SP_EL0

    sub x1, x1, #272
    str x0, [x1]
    // Load the OS stack pointer into x0
    ldr x0, [sp, #8]

    str x0, [x1, #8]
    add sp, sp, #16

    stp x2, x3, [x1, #16]
    stp x4, x5, [x1, #32]
    stp x6, x7, [x1, #48]
    stp x8, x9, [x1, #64]
    stp x10, x11, [x1, #80]
    stp x12, x13, [x1, #96]
    stp x14, x15, [x1, #112]
    stp x16, x17, [x1, #128]
    stp x18, x19, [x1, #144]
    stp x20, x21, [x1, #160]
    stp x22, x23, [x1, #176]
    stp x24, x25, [x1, #192]
    stp x26, x27, [x1, #208]
    str x28, [x1, #224]

    ldr x0, [sp]
    str x0, [x1, #256]
    ldr x0, [sp, #8]
    str x0, [x1, #264]
    
    mrs x0, SPSR_EL1
    str x0, [x1, #232]
    
    mrs x0, ELR_EL1
    str x0, [x1, #240]
    
    // Store the process' top-of-stack pointer (x1) into the process PCB
    
    ldr x0, =Running
    ldr x0, [x0]
    // this is why the first element in the PCB struct is sp
    str x1, [x0] // Running->sp = sp

    ret

.global restore_context
.type restore_context, %function
restore_context:
    ldr x1, =Running
    ldr x1, [x1]
    ldr x1, [x1] // x1 = Running->sp

    // Load the PSTATE from x1+16*14+8 into x0
    ldr x0, [x1, #232]
    msr SPSR_EL1, x0
    // Load ELR_EL1 from x1+16*15 into x0
    ldr x0, [x1, #240]
    msr ELR_EL1, x0

    // Set the process stack pointer
    mov x0, x1
    add x0, x0, #272
    msr SP_EL0, x0

    ldp x2, x3, [x1, #16]
    ldp x4, x5, [x1, #32]
    ldp x6, x7, [x1, #48]
    ldp x8, x9, [x1, #64]
    ldp x10, x11, [x1, #80]
    ldp x12, x13, [x1, #96]
    ldp x14, x15, [x1, #112]
    ldp x16, x17, [x1, #128]
    ldp x18, x19, [x1, #144]
    ldp x20, x21, [x1, #160]
    ldp x22, x23, [x1, #176]
    ldp x24, x25, [x1, #192]
    ldp x26, x27, [x1, #208]

    ldr x28, [x1, #224]

    stp x0, x1, [sp, #-16]!
    bl clear_timer
    ldp x0, x1, [sp], #16

    ldp x29, x30, [x1, #256]

    ldr x0, [x1]
    ldr x1, [x1, #8]

    msr DAIFClr, #0x2       // Clear IRQ disable flag
    ret