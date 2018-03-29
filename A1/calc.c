#include <stdio.h>
#include "calc.h"
#include "stack.h"
#include "tft.h"
#include "keypad.h"
#include "TI_Lib.h"

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
	if(getCurrentStack()!=0){
		TFT_gotoxy(STATUS_POS);
		
		val=pop()/getCurrentStack();
		setStack(val);
		push();
	} else{
		TFT_gotoxy(STATUS_POS);
		TFT_puts("Status:");
		
//		char time[5];
//		sprintf(time, " (T: %d) ", get_uptime());
//		TFT_puts(time);
		
		TFT_puts(" ERR - Division durch 0");
	}
		

}



