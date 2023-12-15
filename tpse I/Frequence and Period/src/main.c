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
#include "interrupt.h"

#define TOOGLE 0x01u

bool flag_gpio = false;
bool flag_timer = false;

int main(void){
	/*-----------------------------------------------------------------------------
	 *  initialize TIMER modules
	 *-----------------------------------------------------------------------------*/
	disableWdt();
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

	#ifdef INTERRUPT_GPIO
	interrupt_setup(98);
	interrupt_buttom(GPIO1, 28);
	#endif

	while(1){
		if(flag_gpio){
			uartPutString(UART0, "Buttom Press!\n\r", 15);
			gpioSetPinValue(GPIO1, 24, HIGH);
			delay(80);
			gpioSetPinValue(GPIO1, 22, HIGH);
			delay(80);
			gpioSetPinValue(GPIO2, 7, HIGH);
			delay(80);
			gpioSetPinValue(GPIO1, 21, HIGH);
			delay(80);
			gpioSetPinValue(GPIO2, 6, HIGH);
			delay(80);
			gpioSetPinValue(GPIO1, 23, HIGH);
			delay(80); //50 ms delay is equal to 20 Hz
			gpioSetPinValue(GPIO1, 24, LOW);
			delay(80);
			gpioSetPinValue(GPIO1, 22, LOW);
			delay(80);
			gpioSetPinValue(GPIO2, 7, LOW);
			delay(80);
			gpioSetPinValue(GPIO1, 21, LOW);
			delay(80);
			gpioSetPinValue(GPIO2, 6, LOW);
			delay(80);
			gpioSetPinValue(GPIO1, 23, LOW);
			delay(80);
			flag_gpio = false;
		}else{
			gpioSetPinValue(GPIO1, 21, HIGH);
			gpioSetPinValue(GPIO1, 22, HIGH);
			gpioSetPinValue(GPIO1, 23, HIGH);
			gpioSetPinValue(GPIO1, 24, HIGH);
			gpioSetPinValue(GPIO2, 6, HIGH);
			gpioSetPinValue(GPIO2, 7, HIGH);
			delay(500); //50 ms delay is equal to 20 Hz
			gpioSetPinValue(GPIO1, 21, LOW);
			gpioSetPinValue(GPIO1, 22, LOW);
			gpioSetPinValue(GPIO1, 23, LOW);
			gpioSetPinValue(GPIO1, 24, LOW);
			gpioSetPinValue(GPIO2, 6, LOW);
			gpioSetPinValue(GPIO2, 7, LOW);
			delay(500);
		}
		
	}
  	
	return(0);
} /* ----------  end of function main  ---------- */


