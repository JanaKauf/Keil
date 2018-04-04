#include<stdio.h>
#include "stack.h"
#include "TFT.h"
#include "TI_Lib.h"
#include<errno.h>

int stack[MAXSIZE];
int top = -1;

/**
  * @brief  Test if the Stack is Empty
  * @param  none
  * @retval 1 true or 0 false 
  */
unsigned int
Empty(){
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
Full(){
	if (top == MAXSIZE) {
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
stackTop(){
	if (!Empty()) {
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
take(){
	int data = 0;
	
	if (!Empty()) {
		data = stackTop();
		stack[top] = 0;
		top--;
		return data;
	} else {
		TFT_gotoxy(1,4);
		TFT_set_font_color(RED);
		TFT_puts("Stack underflow");
		TFT_set_font_color(MINT);
		Delay(5000);
	}
	
	return FALSE; 
}

/**
  * @brief  Puts data on top of the Stack
  * @param  data that will be put on the stack
  * @retval none
  */
void
put(int data){
	if(Empty()){
		top++;
	}
	if(!Full()) {
		stack[top] = (stack[top] * 10) + data;
	}
}

void
clearStack (){
	int i;
	if (!Empty()) {
		for (i = 0; i < MAXSIZE; i++) {
			stack[i] = 0;
		}
		top = 0;
	}
}

void
putOnStack () {
	if (!Full()) {
		top++;
		stack[top] = 0;
	}	
}

void
replaceOnStack (int data) {
	stack[top] = data;
}

void
swapPosition (){
	int value = stackTop();
	stack[top] = stack[top - 1];
	stack[top - 1] = value;
}

void
printStack () {
	int i;
	char out[100];
	
	TFT_gotoxy(1, 3);
	TFT_set_font_color(GREEN);
	TFT_puts("Stack: ");
	TFT_gotoxy(sizeof("Stack: "), 3);
	
	for (i = 0; i <= MAXSIZE - 1; i++){
		printf("%d ", stack[i]);
		sprintf(out, "%d ", stack[i]);
		TFT_puts(out);
	}
	TFT_set_font_color(MINT);
}

void
printTopStack () {
	char out[100];
	TFT_gotoxy(1,2);
	TFT_set_font_color(BLUE);
	TFT_puts("Curr. Stack:");
	TFT_gotoxy(sizeof("Curr. Stack:"), 2); 
	sprintf(out, " %d", stackTop());
	TFT_puts(out);
	TFT_set_font_color(MINT);
}
