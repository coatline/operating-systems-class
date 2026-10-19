#ifndef STACK_H
#define STACK_H

#include <stdint.h>
#include <stdalign.h>

#define _MAX_PROCESSES 10
#define _STACK_SIZE 1024

struct Stack {
    struct Stack *next;
    alignas(16) uint64_t stack[_STACK_SIZE];
};

typedef struct Stack Stack_t;

extern Stack_t Stacks[_MAX_PROCESSES];
extern Stack_t *Stack_free_list;

void init_stack_heap(void);
uint64_t *Stack_alloc(void);

#endif
