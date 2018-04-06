#include <stdio.h>
#include "input.h"
#include "keypad.h"
#include "tft.h"
#include "stack.h"
#include "functions.h"
#include "screen.h"

#define TRUE 				1
#define FALSE 			0

int buffer = 0;

/**
  * @brief  Puts data on top of the Stack
  * @param  data that will be put on the stack
  * @retval none
  */
void
put(int data) {
	buffer = (buffer * 10) + data;
}

int
getBuffer() {
	return buffer;
}

void
setBuffer(int value) {
	buffer = value;
}

void
getInput() {
	unsigned int status = TRUE;

	while (status == TRUE) {
		char eingabe = Get_Touch_Pad_Input();
		
		switch	(eingabe){
			case '0':
				put(eingabe - '0');
				break;
			
			case '1':
				put(eingabe - '0');
				break;
			
			case '2':
				put(eingabe - '0');
				break;
			
			case '3':
				put(eingabe - '0');
				break;
			
			case '4':
				put(eingabe - '0');
				break;
			
			case '5':
				put(eingabe - '0');
				break;
			
			case '6':
				put(eingabe - '0');
				break;
			
			case '7':
				put(eingabe - '0');
				break;
			
			case '8':
				put(eingabe - '0');
				break;
			
			case '9':
				put(eingabe - '0');
				break;
			
			case '+':
				add();
				break;
			
			case '-':
				sub();
			break;
			
			case '*':
				mul();
				break;
			
			case '/':
				div();
				break;
			
			case 'p':
				break;
			
			case 'f':
				break;
			
			case 'c':
				clearStack();
				break;
			
			case 'd':
				duplicate();
				break;
			
			case 'r':
				swapPosition();
				break;
			
			case ' ':
				eingabe = '_';
				push();
				break;
			
			case 'e':
				break;
			
			default:
				continue;
		}
		
		output(eingabe);
	}
}
