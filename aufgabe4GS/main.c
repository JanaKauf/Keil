/**
  ******************************************************************************
  * @file    	main.c 
  * @author  	Alfred Lohmann
  *        	  HAW-Hamburg
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
#include "DS18B20.h"
#include "one_wire.h"
#include "delay.h"

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
int main(void)
{
  Init_TI_Board();
	uint8_t rom;
	char out[100];
	timerinit();
	
	PUSH_PULL(1);
	OPEN_DRAIN(0);

	ow_reset();
	ow_write_byte(CMD_READ_ROM);
	rom = ow_read_byte();
	sprintf(out, "FAMILY: %#02x\n", rom);
	TFT_gotoxy(1,1);
	TFT_puts(out);
	
	rom = ow_read_byte();
	sprintf(out, "Serial Number: %#02x\n", rom);
	TFT_gotoxy(1,2);
	TFT_puts(out);
	
	rom = ow_read_byte();
	sprintf(out, "Serial Number: %#02x\n", rom);
	TFT_gotoxy(1,3);
	TFT_puts(out);
	
	rom = ow_read_byte();
	sprintf(out, "Serial Number: %#02x\n", rom);
	TFT_gotoxy(1,4);
	TFT_puts(out);
	
	rom = ow_read_byte();
	sprintf(out, "Serial Number: %#02x\n", rom);
	TFT_gotoxy(1,5);
	TFT_puts(out);
	
	rom = ow_read_byte();
	sprintf(out, "Serial Number: %#02x\n", rom);
	TFT_gotoxy(1,6);
	TFT_puts(out);
	
	rom = ow_read_byte();
	sprintf(out, "Serial Number: %#02x\n", rom);
	TFT_gotoxy(1,7);
	TFT_puts(out);
	
	rom = ow_read_byte();
	sprintf(out, "CRC: %#02x\n", rom);
	TFT_gotoxy(1,8);
	TFT_puts(out);
  return 0;

}
// EOF
