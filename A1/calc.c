#include <stdio.h>
#include "calc.h"
#include "stack.h"
#include "tft.h"
#include "keypad.h"

int val=0;


void add(){
	val=pop()+getCurrentStack();
	setStack(val);
	push();
}

void sub(){
	val=pop()-getCurrentStack();
	setStack(val);
	push();
}

void mul(){
	val=pop()*getCurrentStack();
	setStack(val);
	push();
}

void div(){
	if(pop()==0){
	TFT_puts("Divison durch 0, was los");


	}else{	
	val=pop()/getCurrentStack();
	setStack(val);
	}
	push();
}



