.text

.global dispatch
.type dispatch, %function
dispatch:
    # Save caller's frame pointer and return address
    sp = sp - 16
    [sp] = x29
    [sp + 8] = x30

    bl save_rest_of_context
    bl schedule
    bl restore_context

.global save_rest_of_context
.type save_rest_of_context, %function
save_rest_of_context:
    ps = ps - 16*15

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
    str x0, [sp, #250]

    mov x0, sp
    ldr x1, =Running
    ldr x1, [x1] 
    // this is why the first element in the PCB struct is sp
    str x0, [x1, #8]  // Running->sp = sp

    ret

.global restore_context
.type restore_context, %function
restore_context:
    adr x1, Running
    ldr x0, [x1]
    ldr x2, [x0] // x2 = Running->sp

    // move the stack pointer to the context of the running process
    mov sp, x2

    ldr x0, [sp, #250]
    msr SPSR_EL1, x0

    /* TODO: load Running->sp, restore PSTATE and x0-x30, then return. */
    ret
