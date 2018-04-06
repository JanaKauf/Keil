#include <stdio.h>
#include <errno.h>
#include "screen.h"
#include "stack.h"
#include "TI_Lib.h"
#include "keypad.h"
#include "tft.h"

#define DELAYTIME		1000

int inputCounter = 0;
char allInput[30];

void
printStack() {
	int st[MAXSIZE];
	int t;
	int i;
	
	char out[100];
	
	copyStack(st, &t);
	
	TFT_gotoxy(1, 3);
	TFT_set_font_color(GREEN);
	TFT_puts("Stack: ");
	TFT_gotoxy(sizeof("Stack: "), 3);
	
	for (i = 0; i <= MAXSIZE - 1; i++) {
		printf("%d ", st[i]);
		sprintf(out, "%d ", st[i]);
		TFT_puts(out);
	}
	
	TFT_set_font_color(MINT);
}

void
printTopStack() {
	char out[100];
	
	TFT_gotoxy(1,2);
	TFT_set_font_color(BLUE);
	TFT_puts("Curr. Stack:");
	TFT_gotoxy(sizeof("Curr. Stack:") , 2); 
	
	sprintf(out, " %d", stackTop() );
	TFT_puts(out);
	TFT_set_font_color(MINT);
}

/**
  * @brief  Output on screen.
  * @param  input varible
  * @retval none
  */
void
output(char input) {
	int i;
	
	if (input == 'e') {
		inputCounter = 30;
		TFT_cls();
	}
	
	if (inputCounter == 30) {
		for (i = 0; i <= (sizeof(allInput) - 1) ; i++) {
			allInput[i] = NULL;
		}
		
		inputCounter = 0;
	}
	
	if (input != 'f' && input != 'p') {
			TFT_cls();
	}
	
	TFT_gotoxy(1, 1);
	TFT_puts("Eingabe: ");
	TFT_gotoxy(sizeof ("Eingabe: "), 1);
	allInput[inputCounter] = input;
	TFT_puts(allInput);
	inputCounter++;
	
	if (input == 'f') {
		printStack();
	} else if (input == 'p') {
		printTopStack();
	}
}

void
initScreen() {
		Init_TI_Board();
		TFT_Init();
		Make_Touch_Pad();
		TFT_set_window(GENEVA10, 1, 1, XPIXEL, 4);
		TFT_puts("Eingabe:");
}

void
errorMsg(int error) {
	switch	(error){
			case -1:
				TFT_gotoxy(1,4);
				TFT_set_font_color(RED);
				TFT_puts("Stack is Empty!");
				TFT_set_font_color(MINT);
				Delay(DELAYTIME);
				break;
			
			case -2:
				TFT_gotoxy(1,4);
				TFT_set_font_color(RED);
				TFT_puts("Stack Overflow");
				TFT_set_font_color(MINT);
				Delay(DELAYTIME);
				break;
			
			case -3:
				TFT_gotoxy(1,4);
				TFT_set_font_color(RED);
				TFT_puts("Stack Underflow");
				TFT_set_font_color(MINT);
				Delay(DELAYTIME);
				break;
			
			case -4:
				TFT_gotoxy(1,4);
				TFT_set_font_color(RED);
				TFT_puts("Division with 0");
				TFT_set_font_color(MINT);
				Delay(DELAYTIME);
				break;
			
			default:
				break;
	}
}
