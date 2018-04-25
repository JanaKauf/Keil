#include <stdio.h>
#include "TI_Lib.h"
#include "tft.h"
#include "timer.h"
#include "defines.h"
#include "encoder.h"
#include "timer.h"

//counts steps to a max. of 255, resets to 0 if max reached
uint8_t steps = 0;

//
int winkel = 0;
int winkelcounter;

int time = 0;
int gradSecCounter = 0;
double gradSec = 0;
	
//default state of IDR
uint8_t state;
	
//current state of IDR
uint8_t newstate = 0x0;

//char array for output on TI-TFT
	char out[12];
	
typedef
enum{
	A_P = 0,
	B_P = 1,
	C_P = 2,
	D_P = 3
} State_Type;

void (*state_table[]) () = {a_phase, b_phase, c_phase, d_phase};

void
a_phase(){
	if (newstate == B_P) {
		steps++;
		gradSecCounter++;
		newstate = state;
		winkelcounter++;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(7);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(6);
	} else if (newstate == C_P) {
		steps--;
		gradSecCounter++;
		newstate = state;
		winkelcounter--;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(6);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(7);
	} else {
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(5);
	}
}

void
b_phase(){
	if (newstate == D_P) {
		steps++;
		gradSecCounter++;
		newstate = state;
		winkelcounter++;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(7);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(6);
	} else if (newstate == A_P) {
		steps--;
		gradSecCounter++;
		newstate = state;
		winkelcounter--;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(6);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(7);
	} else {
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(5);
	}
}

void
c_phase(){
	if (newstate == A_P) {
		steps++;
		gradSecCounter++;
		newstate = state;
		winkelcounter++;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(7);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(6);
	} else if (newstate == D_P) {
		steps--;
		gradSecCounter++;
		newstate = state;
		winkelcounter--;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(6);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(7);
	} else {
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(5);
	}
}

void
d_phase(){
	if (newstate == C_P) {
		steps++;
		gradSecCounter++;
		newstate = state;
		winkelcounter++;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(7);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(6);
		
	} else if (newstate == B_P) {
		steps--;
		gradSecCounter++;
		newstate = state;
		winkelcounter--;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(6);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(7);
		
	} else {
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(5);
		
	}
}

void
printLEDsteps (){
	GPIOG->BSRRH = 0xff00;
	GPIOG->BSRRL = steps << 0x8;
}

void
encode () {
	state = GPIOE->IDR & 0x3;

	if (time + 1000 <= get_uptime()) {
		gradSec = gradSecCounter/3.333;
		gradSecCounter = 0;
		time = get_uptime();
	}
	
	if ((PORT->IDR & IDR_MASK_PIN_I(7)) == 0) {
		steps = 0;
	}
	
	if ((PORT->IDR & IDR_MASK_PIN_I(6)) == 0) {
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(5);
	}
	
	if (state != newstate) {
		
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(0);
		sprintf(out, "State: %d - Schritte: %d\n\rwinkel: %d\n\rGrad/sec:%.2f\n\r", state, steps, winkel, gradSec);
		TFT_cls();
		TFT_gotoxy(1,1);
		TFT_puts(out);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(0);
		
		state_table[state]();
		
		winkel = (int)winkelcounter/3.333;
		printLEDsteps();
	}
}
