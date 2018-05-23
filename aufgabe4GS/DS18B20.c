#include "DS18B20.h"

uint8_t
reset () {
	uint8_t status;
	
	Tx_DS18B20;
	Delay(480000);
	Rx_DS18B20;
	Delay(70000);
	
	status = GPIO_ReadInputDataBit(GPIOG, GPIOG->IDR);
	Delay(410000);
	
	return status;
}

void
writeONE () {
	Tx_DS18B20;
	Delay(6000);
	Rx_DS18B20;
	Delay(64000);
}

void
writeZERO () {
	Tx_DS18B20;
	Delay(60000);
	Rx_DS18B20;
	Delay(10000);
}

uint8_t
readBIT () {
	uint8_t bit;
	
	Tx_DS18B20;
	Delay(6000);
	Rx_DS18B20;
	Delay(9000);
	bit = GPIO_ReadInputDataBit(GPIOG, GPIOG->IDR);
	Delay(55000);
	
	return bit;
}

void
write (uint8_t CMD) {

}

void
read () {
	uint8_t CMD;
	
	
}