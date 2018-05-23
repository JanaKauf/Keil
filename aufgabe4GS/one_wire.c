#include "one_wire.h"

uint8_t
reset () {
	uint8_t status;
	
	LOW;
	Tx_DS18B20;
	Delay(480000);
	Rx_DS18B20;
	Delay(70000);
	
	status = GPIO_ReadInputDataBit(GPIOG, GPIOG->IDR);
	Delay(410000);
	
	return status;
}

void
write_1_0 (uint8_t bit) {
	if (bit) {
		LOW;
		Tx_DS18B20;
		Delay(6000);
		Rx_DS18B20;
		Delay(64000);
	} else {
		LOW;
		Tx_DS18B20;
		Delay(60000);
		Rx_DS18B20;
		Delay(10000);
	}
}

uint8_t
readBIT () {
	uint8_t bit = 0;
	
	LOW;
	Tx_DS18B20;
	Delay(6000);
	Rx_DS18B20;
	Delay(9000);
	
	if (GPIO_ReadInputDataBit(GPIOG, GPIOG->IDR)) {
		bit = 1;
	}
	
	Delay(55000);
	
	return bit;
}
