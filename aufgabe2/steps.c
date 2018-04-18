#include <stdio.h>
#include "TI_Lib.h"
#include "defines.h"

int bitPosition;
//reprents the counter value as one bit
int bit;

void
printLEDsteps (int steps) {

	for (bitPosition = 8; bitPosition >= 0; bitPosition--) {		
		//takes counter and shifts it by tmp.
		//ex: 2>>8=0, 2>>7=0, … , 2>>1=1, 2>>0=0 => 00000010
		bit = steps >> bitPosition;
		bit&=1;
		if ( bit ) {
			printf("%d",bit);
			//if current shifted bit is 1, light up led at tmp+8
			//low
			GPIOG->BSRRL = BSRRL_MASK_PIN_I(bitPosition + 8);
		} else {
			printf("%d",bit);
			//if shifted bit is anything else, turn off led
			//high
			GPIOG->BSRRH = BSRRH_MASK_PIN_I(bitPosition + 8);
		}
		//for test
		if(bitPosition == 0){
			printf("\n");
		}
	}
}
