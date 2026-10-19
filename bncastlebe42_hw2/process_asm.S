.text

.global dispatch
.type dispatch, %function
dispatch:
    /* TODO: save x29/x30, save the remaining context, schedule, restore context. */
    ret

.global save_rest_of_context
.type save_rest_of_context, %function
save_rest_of_context:
    /* TODO: save x0-x28 and PSTATE and store sp in Running->sp. */
    ret

.global restore_context
.type restore_context, %function
restore_context:
    /* TODO: load Running->sp, restore PSTATE and x0-x30, then return. */
    ret
