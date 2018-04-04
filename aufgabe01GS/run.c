#include <stdio.h>
#include "TI_Lib.h"
#include "tft.h"
#include "keypad.h"
#include "stack.h"
#include "functions.h"
#include "run.h"



int inputCounter = 0;
char allInput[30];

/**
  * @brief  Output on screen.
  * @param  input varible
  * @retval none
  */
void
screen (char input){
	int i;
	if (inputCounter == 30){
		for (i = 0; i <= sizeof(allInput) - 1 ; i++){
			allInput[i] = NULL;
		}
		inputCounter = 0;
	}
		TFT_gotoxy(1, 1);
		TFT_puts("Eingabe: ");
		TFT_gotoxy(sizeof ("Eingabe: "), 1);
		allInput[inputCounter] = input;
		TFT_puts(allInput);
		inputCounter++;
	}

	/**
  * @brief  runs the program till an end
  * @param  none
  * @retval none
  */
void
run(){
	Init_TI_Board();
	TFT_Init();
	Make_Touch_Pad();
	TFT_set_window(GENEVA10, 1, 1, XPIXEL, 4);
	TFT_puts("Eingabe:");
	unsigned int status = TRUE;

	while(status == TRUE){
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
				printTopStack();
				break;
			case 'f':
				printf("case f");
				printStack();
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
				putOnStack();
				break;
			case 's':
				status = FALSE;
				TFT_cls();
				break;
			case 'e':
				inputCounter = 30;
				TFT_cls();
				break;
			default:
				continue;
		}
		
		if (eingabe != 'f' && eingabe != 'p') {
			TFT_cls();
		}
		
		screen(eingabe);
	}
}
