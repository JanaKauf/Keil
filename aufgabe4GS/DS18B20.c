#include "DS18B20.h"

char
reset () {
	Tx_DS18B20;
	DELAY(480000);
	Rx_DS18B20;
	DELAY(70000);
	
	
}

void
write (char BLA) {

}

void
read () {

}