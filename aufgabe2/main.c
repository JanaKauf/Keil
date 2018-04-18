#include <stdio.h>
#include <string.h> // Zeichenketten-Verarbeitung
#include <ctype.h> // Tests für Zeichenklassen
#include "TI_Lib.h"
#include "tft.h"
#include "timer.h"
#include "defines.h"
#include "steps.h"
#include "winkel.h"
#include <stdint.h> // int8_t, …


//#include "stm32f4xx.h"
//#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_rcc.h"



//switch
int main(void) {
	
	//for simulation
	Init_TI_Board();
	
	//char array for output on TI-TFT
	char out[12];
	
	// initialize TI-Board and TFT
	Init_TI_Board();
	
	timerinit();
	
	double time;
	
	//begin of super loop
	while (1) {
			setWinkel(GPIOE->IDR);
			
			printLEDsteps(getSteps());
		
			time = (double)getTimeStamp()/100000000;
			sprintf(out, "State: %d - Schritte: %d\n\rwinkel: %.2f\n\rtime:%.2f sec", getState(), getSteps(), getWinkel(), time);

			TFT_cls();
			TFT_gotoxy(1,1);
			TFT_puts(out);
	}
	// end of super loop
} // end of main
// EOF
