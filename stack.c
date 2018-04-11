#include <stdio.h>
#include <errno.h>
#include "stack.h"
#include "TFT.h"
#include "TI_Lib.h"
#include "input.h"

#define TRUE 				1
#define FALSE 			0

int stack[MAXSIZE];
int top = -1;

/**
  * @brief  Test if the Stack is Empty
  * @param  none
  * @retval 1 true or 0 false 
  */
unsigned int
Empty() {
	if (top < 0) {
		return TRUE;
	}
	
	return FALSE;
}

/**
  * @brief  Test if the Stack is Full
  * @param  none
  * @retval 1 true or 0 false 
  */
unsigned int
Full() {
	if (top == MAXSIZE - 1) {
		return TRUE;
	}
	
	return FALSE;
}

/**
  * @brief  Shows the top value from Stack 
  * @param  none
  * @retval top stack value
  */
int
stackTop() {
	if (!Empty() ) {
		return stack[top];
	}
	return FALSE;
}

/**
  * @brief  Takes the top value from Stack 
  * @param  none
  * @retval data from the top of the stack
  */
int
pop() {
	int data = 0;
	
	if (!Empty() ) {
		data = stackTop();
		stack[top] = 0;
		top--;
		return data;
		
	} else {
		return -3;
	} 
}

int
push() {
	if (!Full() ) {
		top++;
		stack[top] = getBuffer();
		setBuffer(0);
		setSet(TRUE);
		
		return TRUE;
		
	} else {
		
		return -2;
	}
}

int
clearStack() {
	if (!Empty() ) {
		int i;
		
		for (i = 0; i < MAXSIZE; i++) {
			stack[i] = 0;
		}
		
		top = -1;
		setBuffer(0);
		
		return TRUE;
		
	} else {
		return -1;
		
	}
}

void
copyStack(int * cStack, int * tStack) {
	int i;
	
	for (i = 0; i < MAXSIZE; i++) {
		*(cStack++) = stack[i];
	}
	
	*tStack = top;
}

void
swapPosition() {
	int value = stackTop();
	stack[top] = stack[top - 1];
	stack[top - 1] = value;
}

void
duplicate() {
	int value = stackTop();
	setBuffer(value);
	push();
}
