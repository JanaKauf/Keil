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
	if(!getSet()) {
		push();
	}
	value = pop();
	
	if (value > 0) {
		setBuffer(value + pop() );
		push();
	} else {
		errorMsg(value);
	}
}

void sub() {
	if(!getSet()) {
		push();
	}
	value = pop();
	
	if (value > 0) {
		setBuffer(pop() - value);
		push();
	} else {
		errorMsg(value);
	}
}

void mul(){
	if(!getSet()) {
		push();
	}
	value = pop();
	
	if (value > 0) {
		setBuffer(value * pop() );
		push();
	} else {
		errorMsg(value);
	}
}

void div() {
	if(!getSet()) {
		push();
	}
	value = pop();
	printf("%d", value);
	
	if(value == -3) {
		errorMsg(-3);
	
	}	else if(value != 0){	
		setBuffer(pop() / value);
		push();

	} else {
		errorMsg(-4);
	}
}

