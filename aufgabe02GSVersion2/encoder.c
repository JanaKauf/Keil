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
	A_P =0,
	B_P = 1,
	C_P = 2,
	D_P = 3
}State_Type;


void a_p(uint8_t, uint8_t *);
void b_p(uint8_t, uint8_t *);
void c_p(uint8_t, uint8_t *);
void d_p(uint8_t, uint8_t *);

typedef void (*state_table) (uint8_t, uint8_t *);

state_table s_t;

void
a_p(uint8_t state, uint8_t * newstate){
	if (*newstate == 1) {
		steps++;
		gradSecCounter++;
		*newstate = state;
		winkelcounter++;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(7);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(6);
	} else if (*newstate == 2) {
		steps--;
		gradSecCounter++;
		*newstate = state;
		winkelcounter--;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(6);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(7);
	} else {
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(5);
	}
}

void
b_p(uint8_t state, uint8_t * newstate){
	if (*newstate == 3) {
		steps++;
		gradSecCounter++;
		*newstate = state;
		winkelcounter++;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(7);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(6);
	} else if (*newstate == 0) {
		steps--;
		gradSecCounter++;
		*newstate = state;
		winkelcounter--;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(6);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(7);
	} else {
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(5);
	}
}

void
c_p(uint8_t state, uint8_t * newstate){
	if (*newstate == 0) {
		steps++;
		gradSecCounter++;
		*newstate = state;
		winkelcounter++;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(7);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(6);
	} else if (*newstate == 3) {
		steps--;
		gradSecCounter++;
		*newstate = state;
		winkelcounter--;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(6);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(7);
	} else {
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(5);
	}
}

void
d_p(uint8_t state, uint8_t * newstate){
	if (*newstate == 2) {
		steps++;
		gradSecCounter++;
		*newstate = state;
		winkelcounter++;
		GPIOG->BSRRL = BSRRL_MASK_PIN_I(7);
		GPIOG->BSRRH = BSRRH_MASK_PIN_I(6);
	} else if (*newstate == 1) {
		steps--;
		gradSecCounter++;
		*newstate = state;
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
		
		if (state == A_P) {
			s_t = a_p;
		
		} else if(state == B_P) {
			s_t = b_p;
		
		} else if(state == C_P) {
			s_t = c_p;
		
		} else if(state == D_P) {
			s_t = d_p;
		}
		
		s_t(state, &newstate);
		
		winkel = (int)winkelcounter/3.333;
		printLEDsteps();
	}
}
