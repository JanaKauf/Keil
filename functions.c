#include <stdio.h>
#include <errno.h>
#include "functions.h"
#include "stack.h"
#include "tft.h"
#include "TI_Lib.h"
#include "input.h"

void add() {
	setBuffer(pop() + getBuffer() );
	push();
}

void sub() {
	setBuffer(pop() - getBuffer() );
	push();
}

void mul(){
	setBuffer(pop() * getBuffer() );
	push();
}

void div() {
	if(stackTop() != 0){	
		setBuffer(getBuffer() / pop());
		push();

	} else {
		TFT_gotoxy(1,4);
		TFT_set_font_color(RED);
		TFT_puts("Division durch 0");
		TFT_set_font_color(MINT);
		Delay(5000);
	}
}

