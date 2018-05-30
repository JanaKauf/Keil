#include "one_wire.h"
#include "cfg_DS18B20.h"
#include "DS18B20.h"
#include "delay.h"
#include <stm32f4xx.h>

uint8_t
ow_reset () {
	uint8_t status;
	
	OW_LOW;
	delay(480);
	OW_HIGH;
	delay(70);
	
	status = GPIOG->IDR & 1;
	delay(410);
	
	return status;
}

void
ow_write_bit (uint8_t bit) {
	if (bit) {
		OW_LOW;
		delay(6);
		OW_HIGH;
		delay(64);
	} else {
		OW_LOW;
		delay(60);
		OW_HIGH;
		delay(10);
	}

}

uint8_t
ow_read_bit () {
	uint8_t bit = 0;
	
	OW_LOW;
	delay(6);
	OW_HIGH;
	delay(9);
	
	if (GPIOG->IDR) {
		bit = 1;
	}
	
	delay(55);
	
	return bit;
}

void
ow_write_byte (uint8_t byte) {
	uint8_t i = 8;
	
	while (i--) {
		ow_write_bit(byte & 0x01);
		byte >>= 1;
	}
}

uint8_t
ow_read_byte(){
	uint8_t byte = 0;
	uint8_t i = 8;
	
	while (i--) {
		byte <<= 1;
		byte |= (ow_read_bit() << 0x07);
	}
	
	return byte;
}

void
ow_resetsearch (ow_t * ow_struct) {
	
	ow_struct->LastDiscrepancy = 0;
	ow_struct->LastDeviceFlag = false;
	ow_struct->LastFamilyDiscrepancy = 0;
}

uint8_t
ow_search (ow_t * ow_struct, uint8_t cmd) {
	uint8_t id_bit_number;
	uint8_t last_zero, ROM_byte_number, search_result;
	uint8_t id_bit, cmp_id_bit;
	uint8_t ROM_byte_mask, search_direction;
	
	/* Init for search */
	id_bit_number = 1;
	last_zero = 0;
	ROM_byte_number = 0;
	ROM_byte_mask = 1;
	search_result = 0;
	
	/* if recent call was not the last */
	if(!ow_struct->LastDeviceFlag){
		
		/* ONEWIRE Reset */
		if(ow_reset()){
			
			/* reset search */
			ow_resetsearch(ow_struct);
			
			return 0;
		}
		
		/* start search command */
		ow_write_byte(cmd);
		
		/* loop for search */
		do{
			id_bit = ow_read_bit();
			cmp_id_bit = ow_read_bit();
			
			/* check for sensors */
			if((id_bit == 1) && (cmp_id_bit == 1)){
				break;
			} else {
				/* all sensor have either 0 or 1 */
				if(id_bit != cmp_id_bit){
					search_direction = id_bit;
					
				} else{
					if(id_bit_number < ow_struct->LastDiscrepancy){
						search_direction = ((ow_struct->ROM_NR[ROM_byte_number] & ROM_byte_mask) > 0);
					} else{
						search_direction = (id_bit_number == ow_struct->LastDiscrepancy);
					}
					
					/* if zero was picked, save its index */
					if(search_direction == 0){
						last_zero = id_bit_number;
						
						/* check for last dicrepancy in family */
						if(last_zero < 9){
							ow_struct->LastFamilyDiscrepancy = last_zero;
						}
					}
				}
				
				/* set or clear the bit in ROM byte */
				if(search_direction == 1){
					ow_struct->ROM_NR[ROM_byte_number] |= ROM_byte_mask;
				} else{
					ow_struct->ROM_NR[ROM_byte_number] &= ~ROM_byte_mask;
				}
				
				/* serialnumber search direction */
				ow_write_bit(search_direction);
				
				/* increment the byte counter id_bit_number
				and shift the mask rom_byte_mask by 1 */
				id_bit_number++;
				ROM_byte_mask <<=1;
				
				/* if mask is 0, go to new SN and reset mask */
				if(ROM_byte_mask == 0){
					ROM_byte_number++;
					ROM_byte_mask = 1;
				}
			}
		} while(ROM_byte_number < 8); //loop until all Rom bits
		
		/* if search was a success */
		if(!(id_bit_number < 65)){
			ow_struct->LastDiscrepancy = last_zero;
			
			/* check for last sensor */
			if(ow_struct->LastDiscrepancy == 0){
				ow_struct->LastDeviceFlag = 1;
			}
			
			search_result = 1;
		}
	}
	
	/* if NO sensor found, reset counters for next clean search */
	if(!search_result || !ow_struct->ROM_NR[0]){
		ow_resetsearch(ow_struct);
		search_result = 0;
	}
	
	return search_result;
}

bool
ow_verify (ow_t * ow_struct) {
	uint8_t rom_backup[8];
	int i;
	bool result;
	int lstdisc_backup, lstdevflg_backup, lstfamdisc_backup;
	
	/* make backup of current state */
	for(i = 0; i < 8; i++){
		rom_backup[i] = ow_struct->ROM_NR[i];
	}
	
	lstdisc_backup = ow_struct->LastDiscrepancy;
	lstdevflg_backup = ow_struct->LastDeviceFlag;
	lstfamdisc_backup = ow_struct->LastFamilyDiscrepancy;
	
	/* start search to find same sensor */
	ow_struct->LastDiscrepancy = 64;
	ow_struct->LastDeviceFlag = 0;
	
	if(ow_search(ow_struct, CMD_SEARCH_ROM)){
			
		/* check if same sensor is found */
		result = true;
		for(i = 0; i < 8; i++){
			if(rom_backup[i] != ow_struct->ROM_NR[i]){
				result = true;
				break;
			}
		}
	} else {
		result = false;
	}
	
	/* restore search states */
	for( i = 0; i < 8; i++){
		ow_struct->ROM_NR[i] = rom_backup[i];
	}
	
	ow_struct->LastDiscrepancy = lstdisc_backup;
	ow_struct->LastDeviceFlag = lstdevflg_backup;
	ow_struct->LastFamilyDiscrepancy = lstfamdisc_backup;
	
	return result;
	
}

void
ow_target (ow_t * ow_struct) {
	uint8_t i;
	
	ow_struct->ROM_NR[i] = FAMILY_ROM;
	
	for(i = 1; i<8 ; i++){
		ow_struct->ROM_NR[i] = 0;
	}
	
	ow_struct->LastDiscrepancy = 64;
	ow_struct->LastFamilyDiscrepancy = 0;
	ow_struct->LastDeviceFlag = 0;
	
}

void
ow_familyskip(ow_t * ow_struct){
	/* set LastDiscrepanxy to LastFamilyDiscrepancy */
	ow_struct->LastDiscrepancy = ow_struct->LastFamilyDiscrepancy;
	ow_struct->LastFamilyDiscrepancy = 0;
	
	/* check for end of list */
	if(ow_struct->LastDiscrepancy == 0){
		ow_struct->LastDeviceFlag = false;
	}
}

uint8_t
ow_get_rom(ow_t *ow_struct, uint8_t index){
	return ow_struct->ROM_NR[index];
}

void
ow_select(ow_t *ow_struct, uint8_t* adress){
	uint8_t i;
	
	ow_write_byte(CMD_MATCH_ROM);
	
	for(i = 0; i < 8; i++){
		ow_write_byte(*(adress + i));
	}
}

void
ow_select_pointer(ow_t *ow_struct, uint8_t *ROM){
	uint8_t i;
	ow_write_byte(CMD_MATCH_ROM);
	for(i=0; i<8; i++){
		ow_write_byte(*(ROM + i));
	}
}

void
OW_GETFULLROM(ow_t *ow_struct, uint8_t *firstIndex){
	uint8_t i;
	
	for(i=0; i<8; i++){
		*(firstIndex + i) = ow_struct->ROM_NR[i];
	}
}

uint8_t
OW_CRC(uint8_t *adress, uint8_t lenght){
	uint8_t crc = 0, inbyte, i, mix;
	
	while(lenght--){
		inbyte = *adress++;
		for(i=8; i; i--){
			mix = (crc ^ inbyte) & 0x01;
			crc >>=1;
			if(mix){
				crc ^=0x8C;
			}
			inbyte >>=1;
		}
	}
	
	/* return calculated CRC */
	return crc;
}

uint8_t
ow_first(ow_t * ow_struct){
	ow_resetsearch(ow_struct);
	
	/* start search */
	return ow_search(ow_struct, CMD_SEARCH_ROM);
}

uint8_t
ow_next(ow_t *ow_struct){
	return ow_search(ow_struct, CMD_SEARCH_ROM);
}