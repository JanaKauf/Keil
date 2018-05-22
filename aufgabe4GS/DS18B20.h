#ifndef _DS18B20_H
#define _DS18B20_H
#include "TI_Lib.h"
//#include "stm32f10x.h"
#include "stm32f4xx_gpio.h"
#include "timer.h"

uint32_t time;

#define SEARCH_ROM		0xf0
#define READ_ROM			0x33
#define	MATCH_ROM			0x55
#define SKIP_ROM			0xcc
#define	ALARM_SEARCH	0xec



// Initiates temperature conversion.
// DS18B20 transmits conversion status to master
#define CONVERT_T 0x44

// Reads the entire scratchpad including the CRC byte.
// DS18B20 transmits up to 9 data bytes to master.
#define READ_SP		0xBE
// Writes data into scratchpad bytes 2, 3, and 4 (TH, TL, and configuration registers).
// Master transmits 3 data bytes to DS18B20.
#define WRITE_SP	0x4E
// Copies TH, TL, and configuration register data from the scratchpad to EEPROM.
#define CPY_SP		0x48
// Recalls TH, TL, and configuration register data from EEPROM to the scratchpad.
#define	READCALL	0xB8
// Signals DS18B20 power supply mode to the master
#define	READ_PS		0xB4


//Output PG0 send 0
//#define Tx_DS18B20 GPIOG->MODER = (GPIOG->MODER & ~(3 << (0 *2))) | (GPIO_Mode_OUT << (0 * 2));
#define Tx_DS18B20 GPIOG->BSRRH = (1 << 0);

//Input PG0 send 1
//#define Rx_DS18B20 GPIOG->MODER = (GPIOG->MODER & ~(3 << (0 *2))) | (GPIO_Mode_IN << (0 * 2));
#define Rx_DS18B20 GPIOG->BSRRL = (1 << 0);


//Open drain PG0
#define OPEN_DRAIN GPIOG->OTYPER |= (1 << 0);

//push-pull PG0
#define PUSH_PULL GPIOG->OTYPER &= ~(1 << 0);

#define DELAY(US) time = getTimeStamp(); while (1) {\
		if ((getTimeStamp() - time) == US) {\
			break;\
		}\
	}


#endif /* _DS18B20_H */