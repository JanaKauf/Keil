#include "delay.h"

//completed??
void delay(uint16_t u_sec){
	resetTimer();
	while(getTimeStamp() <= (u_sec * CONVERT2US)){
	}
}