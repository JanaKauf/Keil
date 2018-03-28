#include <stdio.h>
#include "TI_Lib.h"
#include "tft.h"
#include "keypad.h"
#include "stack.h"
#include "calc.h"

int incounter=0;
char input[20];
void info(char eingabe){
	TFT_gotoxy(1,1);
	TFT_puts("Eingabe: ");
	TFT_gotoxy(sizeof ("Eingabe: "),1);
	input[incounter]=eingabe;
	TFT_puts(input);
	incounter++;
	}

void run(){
	Init_TI_Board();
	TFT_Init();
	Make_Touch_Pad();
	TFT_puts("Bereit.");

	while(1){
		char eingabe = Get_Touch_Pad_Input();
		
		switch(eingabe){
			case '0': addDigit(eingabe-'0'); 
			TFT_gotoxy(1,3); 
			info(eingabe); break;
			case '1': addDigit(eingabe-'0'); 
			info(eingabe); break;
			case '2': addDigit(eingabe-'0'); 
			info(eingabe); break;
			case '3': addDigit(eingabe-'0'); 
			info(eingabe); break;
			case '4': addDigit(eingabe-'0'); 
			info(eingabe); break;
			case '5': addDigit(eingabe-'0'); 
			info(eingabe); break;
			case '6': addDigit(eingabe-'0'); 
			info(eingabe); break;
			case '7': addDigit(eingabe-'0'); 
			info(eingabe); break;
			case '8': addDigit(eingabe-'0'); 
			info(eingabe); break;
			case '9': addDigit(eingabe-'0'); 
			info(eingabe); break;
			case '+': add(); 
			info(eingabe); break;
			case '-': sub(); 
			info(eingabe); break;
			case '*': mul(); 
			info(eingabe); break;
			case '/': div(); 
			info(eingabe); break;
			case 'e': push(); 
			info(eingabe); break;
			case 'c': clear(); 
			printStack(); info(eingabe); break;
			case 's': addDigit(eingabe); 
			info(eingabe); break;
			case 'r': swapPos(); 
			printStack(); info(eingabe); break;
			case 'd': duplicate(); 
			printStack(); info(eingabe); break;
			case ' ': push(); 
			info('_'); break;
			case 'p': printFirst(); 
			info(eingabe); break;
			case 'f': printStack(); 
			info(eingabe); break;
			default: continue;
		}
	}
}
