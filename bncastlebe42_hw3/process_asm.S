.text

.global dispatch
.type dispatch, %function
dispatch:
    # save caller's frame pointer and return address
    stp x29, x30, [sp, #-16]!

    bl save_rest_of_context
    bl schedule
    bl restore_context 

.global save_rest_of_context
.type save_rest_of_context, %function
save_rest_of_context:
    sub sp, sp, #240
    
    stp x0, x1, [sp, #0]
    stp x2, x3, [sp, #16]
    stp x4, x5, [sp, #32]
    stp x6, x7, [sp, #48]
    stp x8, x9, [sp, #64]
    stp x10, x11, [sp, #80]
    stp x12, x13, [sp, #96]
    stp x14, x15, [sp, #112]
    stp x16, x17, [sp, #128]
    stp x18, x19, [sp, #144]
    stp x20, x21, [sp, #160]
    stp x22, x23, [sp, #176]
    stp x24, x25, [sp, #192]
    stp x26, x27, [sp, #208]
    str x28, [sp, #224]
    
    mrs x0, SPSR_EL1
    str x0, [sp, #232]

    mov x0, sp
    ldr x1, =Running
    ldr x1, [x1] 
    // this is why the first element in the PCB struct is sp
    str x0, [x1] // Running->sp = sp

    ret

.global restore_context
.type restore_context, %function
restore_context:
    adr x1, Running
    ldr x0, [x1]
    ldr x2, [x0] // x2 = Running->sp

    // move the stack pointer to the context of the running process
    mov sp, x2

    // load the PSTATE
    ldr x0, [sp, #232]
    msr SPSR_EL1, x0

    ldp x0, x1, [sp, #0]
    ldp x2, x3, [sp, #16]
    ldp x4, x5, [sp, #32]
    ldp x6, x7, [sp, #48]
    ldp x8, x9, [sp, #64]
    ldp x10, x11, [sp, #80]
    ldp x12, x13, [sp, #96]
    ldp x14, x15, [sp, #112]
    ldp x16, x17, [sp, #128]
    ldp x18, x19, [sp, #144]
    ldp x20, x21, [sp, #160]
    ldp x22, x23, [sp, #176]
    ldp x24, x25, [sp, #192]
    ldp x26, x27, [sp, #208]
    ldr x28, [sp, #224]

    ldp x29, x30, [sp, #240] // restore frame pointer and return address

    // pop the context from the stack
    add sp, sp, 256
    ret
