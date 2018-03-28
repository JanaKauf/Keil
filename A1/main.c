/**
  ******************************************************************************
  * @file    	main.c 
  * @author  	Alfred Lohmann
  *        	  	HAW-Hamburg
  *          	Labor für technische Informatik
  *          	Berliner Tor  7
  *          	D-20099 Hamburg
  * @version V1.0
  * @date    23.05.2013
  * @brief   Main program body
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "TI_Lib.h"
#include "tft.h"
#include "keypad.h"
#include "stack.h"
#include "calc.h"
#include "run.h"


//--- For GPIOs -----------------------------
//Include instead of "stm32f4xx.h" for
//compatibility between Simulation and Board
//#include "TI_memory_map.h"

//--- For Touch Keypad ----------------------
//#include "keypad.h"

//--- For Timer -----------------------------
//#include "timer.c"

/**
  * @brief  Main program
  * @param  None
  */
  

int auswahl=0;

void calculate(int auswahl){
	switch(auswahl){
		case 1: add();
		break;
		case 2: sub();
		break;
		case 3: mul();
		break;
		case 4: div();
	
}
}

int main()
 {

	
	 
	run();
	
}
// EOF



