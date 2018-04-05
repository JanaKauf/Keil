#include <stdio.h>
#include "functions.h"
#include "stack.h"
#include "tft.h"
#include "TI_Lib.h"
#include <errno.h>

int v1 = 0;
int v2 = 0;

void add(){
	v1 = take();
	v2 = stackTop();
	
	
	printf("v1 = %d, v2=%d", v1, v2);
	
	replaceOnStack(v1 + v2);
}

void sub(){
	v1 = take();
	v2 = stackTop();
	
	replaceOnStack(v1 - v2);
}

void mul(){
	v1 = take();
	v2 = stackTop();
	
	replaceOnStack(v1 * v2);
}

void div(){
	if(stackTop() != 0){	
		v1 = take();
		v2 = stackTop();

		replaceOnStack(v2/v1);

	} else {
		TFT_gotoxy(1,4);
		TFT_set_font_color(RED);
		TFT_puts("Division durch 0");
		TFT_set_font_color(MINT);
		Delay(5000);
	}
}

