#ifndef STACK_H_INCLUDE
#define STACK_H_INCLUDE

#include "List.h"

typedef List Stack;
#define stack_init list_init
#define stack_destroy list_destroy

int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void **data);

#define stack_size list_size
#define stack_peek(stack) (NULL == (stack)->head ? NULL : (stack)->head->data)

#endif
