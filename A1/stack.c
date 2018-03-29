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
}

void push(){
		if(pointer<=STACK_SIZE-1){
		++pointer;
		stack[pointer]=0;
		}else{
			TFT_gotoxy(INPUT_POS); 
			TFT_puts("Overflow");
		}
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
	return spVal;
}

void printFirst(){
	char out[100];
	TFT_gotoxy(STACK_POS); 
	sprintf(out, "Current Stack: \n\r%d\n\r", getCurrentStack());
	TFT_puts(out);
}

void printStack(){
	char out1[100];
	TFT_gotoxy(STACK_POS); 
	TFT_puts("Complete Stack:\n\r");
	for(int i=0;i<=STACK_SIZE-1;++i){
		sprintf(out1, "%d ", stack[i]);
		TFT_puts(out1);
	}
	
}

void clear(){
	for(int i=0;i<=STACK_SIZE-1;++i){
	stack[i]=0;
	}
	pointer=0;
	
}

void duplicate(){
	int stcopy = stack[pointer-1];
	stack[pointer]=stcopy;
	push();
}

void swapPos(){
	if(pointer>0){
	int first=stack[pointer];
	int second =stack[pointer-1];
	
	stack[pointer]=second;
	stack[pointer-1]=first;
	}else{
		TFT_gotoxy(INPUT_POS); 
		TFT_puts("Underflow\n\r");
	}
}
