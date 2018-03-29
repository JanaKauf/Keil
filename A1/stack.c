#include <stdio.h>
#include "stack.h"
#include "run.h"
#include "tft.h"


int stack[STACK_SIZE];
int pointer=0;


void addDigit(int digit){
	stack[pointer]=stack[pointer]*10+digit;
}

int getCurrentStack(){
return stack[pointer];
}

int getPointer(){
	return pointer;
}

void setStack(float value){
	stack[pointer]=value;
	printStack();
}

void push(){
		if(pointer<=STACK_SIZE-1){
		++pointer;
		stack[pointer]=0;
		}else{
			TFT_gotoxy(INPUT_POS); 
			TFT_puts("Overflow");
		}
		printStack();
}

int pop(){
	int spVal=stack[pointer];
	stack[pointer] = 0;
	if(pointer>=0){
	--pointer;
	}else{
	TFT_gotoxy(INPUT_POS); 
	TFT_puts("Underflow");
	}
	printStack();
	return spVal;
}

void printFirst(){
	char out[100];
	TFT_gotoxy(CURR_STACK); 
	TFT_puts("Curr. Stack:");
	sprintf(out, " %d", getCurrentStack());
	TFT_gotoxy(sizeof("Curr. Stack:"),2); 
	TFT_puts(out);
}

void printStack(){
	
	char out1[100];
	TFT_gotoxy(COMP_STACK);
	TFT_puts("Stack: ");
	TFT_gotoxy(sizeof("Stack: "),3); 
	for(int i=0;i<=STACK_SIZE-1;i++){
		sprintf(out1, "%d ", stack[i]);
		TFT_puts(out1);
	}


}


void clear(){
	for(int i=0;i<=STACK_SIZE-1;i++){
	stack[i]=0;
	}
	pointer=0;
	printStack();
}

void duplicate(){
	int stcopy = stack[pointer-1];
	stack[pointer]=stcopy;
	push();
	printStack();
}

void swapPos(){
	if(pointer>=0){
	int first=stack[pointer];
	int second =stack[pointer-1];
	stack[pointer-1]=first;
	push();
	stack[pointer]=second;
	
	
	
	
	}else{
		TFT_gotoxy(INPUT_POS); 
		TFT_puts("Underflow");
	}
	printStack();
}
