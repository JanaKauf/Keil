#include <stdio.h>
#include <string.h> // Zeichenketten-Verarbeitung
#include <ctype.h> // Tests für Zeichenklassen
#include <stdint.h> // int8_t, …
#include "TI_Lib.h"
#include "tft.h"
#include "timer.h"
#include "defines.h"
#include "encoder.h"


//#include "stm32f4xx.h"
//#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_rcc.h"



//switch
int main(void) {
	
	//for simulation
	Init_TI_Board();
	
	timerinit();
	
	//begin of super loop
	while (1) {
			encode();
	}
	// end of super loop
} // end of main
// EOF
