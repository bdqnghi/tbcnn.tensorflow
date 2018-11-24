
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/Stack.h"
// test code
// void main(){
	// Stack stack;
	// stack_init(&stack,2);
	// int a = 12;
	// int b = 123;
	// int c = 1234;
	// int d = 0;
	// d = *(int *)stack_push(&stack,&a,sizeof(int));
	// d = *(int *)stack_push(&stack,&b,sizeof(int));
	// d = *(int *)stack_push(&stack,&c,sizeof(int));
	// printf("first element  = %d\n",*(int *)stack_get_top(&stack));
	// stack_pop(&stack);
	// printf("second element = %d\n",*(int *)stack_get_top(&stack));
	// stack_pop(&stack);
	// printf("thired element = %d\n",*(int *)stack_get_top(&stack));
	// stack_pop(&stack);
	// stack_destory(&stack);
// }
// void error(char *s){
	// printf("%s\n",s);
	// exit(1);
// }

void stack_init(Stack *stack,int initsize){
	stack->base = (void **)malloc(sizeof(void **) * initsize);
	if(NULL == stack->base)
		error("memory allocation failed");
	else{
		stack->top = stack->base;
		stack->stacksize = initsize;
	}
}
/**

return top element
*/
void *stack_push(Stack *stack,void *element,int size){
	int newsize;
	if(stack->top >= stack->base + stack->stacksize){
		newsize = stack->stacksize * 2;
		stack->base = (void **)realloc(stack->base,sizeof(void **) * newsize);
		if(NULL == stack->base)
			return NULL;
		stack->top = stack->base + stack->stacksize;
		stack->stacksize = newsize;
	}
	*stack->top = (void *)malloc(size);						/// different from book
	memcpy(*stack->top,element,size);
	stack->top++;
	return *(stack->top - 1);
}

void stack_pop(Stack *stack){
	if(stack->top > stack->base)
		free(*(--stack->top));
}

void *stack_get_top(Stack *stack){
	void **element;
	if(stack->top > stack->base){
		element = stack->top - 1;
		return *element;
	}else
		return NULL;
}
int stack_is_empty(Stack *stack){
	if(stack->top == stack->base)
		return 1;
	return 0;
}
void stack_destory(Stack *stack){
	void **element;
	for(element = stack->base;element < stack->top;element++)
		free(*element);
	if(stack->base != NULL)
		free(stack->base);
	stack->base = NULL;
	stack->top = NULL;
	stack->stacksize = 0;
}


















