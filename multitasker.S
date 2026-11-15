.text

.global setup_EVT
.type setup_EVT, %function
setup_EVT:
    


vector_table:
 .balign 128
    b unsupported
.balign 128
    b dispatch
.balign 128
    b unsupported
.balign 128
    b unsupported
.balign 128
    b unsupported
.balign 128
    b dispatch    // yes
.balign 128
    b unsupported
.balign 128
    b unsupported
.balign 128
    b unsupported
.balign 128
    b dispatch
.balign 128
    b unsupported
.balign 128
    b unsupported
.balign 128
    b unsupported
.balign 128
    b dispatch
.balign 128
    b unsupported
.balign 128
    b unsupported

unsupported:
    print_to(0, 0, "Unsupported exception");
    loop:
        b loop