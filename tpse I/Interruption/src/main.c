/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/02/2017 20:05:55
 *       Revision:  none
 *       Compiler:  arm-none-eabi-gcc
 *
 *         Author:  Francisco Helder (FHC), helderhdw@gmail.com
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include "uart.h"
#include "timer.h"
#include "gpio.h"

#define TOOGLE 0x01u

int main(void){
	unsigned int flagblink = 0;
	/*-----------------------------------------------------------------------------
	 *  initialize TIMER modules
	 *-----------------------------------------------------------------------------*/
    DMTimerSetUp();

	gpioInitModule(GPIO1);
	gpioInitModule(GPIO2);

	for(unsigned int i = 21; i <= 24; i++){
		gpioPinMuxSetup(GPIO1, i);
		gpioSetDirection(GPIO1, i, OUTPUT);
	}

	for(unsigned int i = 6; i <= 7; i++){
		gpioPinMuxSetup(GPIO2, i);
		gpioSetDirection(GPIO2, i, OUTPUT);
	}

	while(1){
		flagblink ^= TOOGLE;
		if(flagblink){
			gpioSetPinValue(GPIO1, 21, HIGH);
			gpioSetPinValue(GPIO1, 22, HIGH);
			gpioSetPinValue(GPIO1, 23, HIGH);
			gpioSetPinValue(GPIO1, 24, HIGH);
			gpioSetPinValue(GPIO2, 6, HIGH);
			gpioSetPinValue(GPIO2, 7, HIGH);
			Delay(25); //50 ms delay is equal to 20 Hz
		}else{
			gpioSetPinValue(GPIO1, 21, LOW);
			gpioSetPinValue(GPIO1, 22, LOW);
			gpioSetPinValue(GPIO1, 23, LOW);
			gpioSetPinValue(GPIO1, 24, LOW);
			gpioSetPinValue(GPIO2, 6, LOW);
			gpioSetPinValue(GPIO2, 7, LOW);
			Delay(25);
		}
		
	}
  	
	return(0);
} /* ----------  end of function main  ---------- */


