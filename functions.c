#include <stdio.h>
#include <errno.h>
#include "functions.h"
#include "stack.h"
#include "tft.h"
#include "TI_Lib.h"
#include "input.h"
#include "screen.h"

int value;

void add() {
	value = pop();
	
	if (value > 0) {
		setBuffer(value + getBuffer() );
		push();
	} else {
		errorMsg(value);
	}
}

void sub() {
	value = pop();
	
	if (value > 0) {
		setBuffer(value - getBuffer() );
		push();
	} else {
		errorMsg(value);
	}
}

void mul(){
	value = pop();
	
	if (value > 0) {
		setBuffer(value * getBuffer() );
		push();
	} else {
		errorMsg(value);
	}
}

void div() {
	if(pop() == -3) {
		errorMsg(-3);
	
	}	else if(stackTop() != 0){	
		setBuffer(getBuffer() / pop());
		push();

	} else {
		errorMsg(-4);
	}
}

