#include <stdio.h>
#include "TI_Lib.h"
#include "defines.h"
#include "winkel.h"

//counts steps to a max. of 255, resets to 0 if max reached
uint8_t steps = 0;
	
//
double winkel = 0;
int winkelcounter;
	
//default state of IDR
int state;
	
//current state of IDR
int newstate;

void
setWinkel (int oldstate) {
	state = oldstate & 0x3;
	if (state != newstate) {
		steps++;
		switch(state){
			case 0:
				switch(newstate){								
					case 1: winkelcounter++;break ;
					case 2: winkelcounter--;break ;
					case 3: break ;//fehler
				}
			break ;		
			case 1: 
				switch(newstate){
					case 3: winkelcounter++;break ;
					case 0: winkelcounter--;break ;
					case 2:break ;//fehler
				}
			break ;		
			case 2: 
				switch(newstate){			
					case 0: winkelcounter++;break ;
					case 3: winkelcounter--;break ;
					case 1: break ;//fehler
				}
			break ;
			case 3: 
				switch(newstate){
					case 2: winkelcounter++;break ;
					case 1: winkelcounter--;break ;
					case 0: break ;//fehler
				}
			break ;	
		}
		newstate = state;
	}
	winkel = winkelcounter/3.333;
}
double
getWinkel (){
	
	return winkel;
}

uint8_t
getSteps () {
	return steps;
}


int
getState() {
	return state;
}
