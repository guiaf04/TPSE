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

#include	"hw_types.h"
#include	"soc_AM335x.h"
#include	"gpio.h"

/*****************************************************************************
**                INTERNAL MACRO DEFINITIONS
*****************************************************************************/
#define TIME													1000000
#define TOGGLE          										(0x01u)
#define WDT1												0x44E35000
#define WDT_WSPR											0x48
#define WDT_WWPS											0x34

#define CM_PER_GPIO1											0xAC
#define CM_PER_GPIO2											0xB0
#define CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE   				(0x2u)
#define CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE   				(0x2u)
#define CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK   			(0x00040000u)
#define CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK   			(0x00040000u)

#define CM_conf_gpmc_ben1      	 								0x0878
#define CM_conf_gpmc_a0                                         0x0840 //Button
#define CM_conf_gpmc_a5         								0x0854
#define CM_conf_gpmc_a6         								0x0818
#define CM_conf_gpmc_a7         								0x081C
#define CM_conf_gpmc_a8         								0x0820
#define CM_conf_gpmc_ad12         								0x0830
#define CM_conf_lcd_data0         								0x08A0
#define CM_conf_lcd_data1         								0x08A4




#define GPIO_OE                 								0x134
#define GPIO_CLEARDATAOUT       								0x190
#define GPIO_SETDATAOUT         								0x194
#define GPIO_DATAIN            								    0x138

unsigned int flagBlink;
unsigned int sequence;

/*****************************************************************************
**                INTERNAL FUNCTION PROTOTYPES
*****************************************************************************/
static void delay();
static void InitGPIO1();
static void ledInitGPIO2();
static void ledToggle();

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main(void){


	HWREG( WDT1 + WDT_WSPR ) = 0xAAAA;
	
	while ((HWREG(WDT1 + WDT_WWPS) & (1<<4)) != 0){
	}
	
	HWREG(WDT1 + WDT_WSPR) = 0x5555;
	
	while ((HWREG(WDT1 + WDT_WWPS) & (1<<4)) != 0){
	}

	flagBlink=0;	//init flag
	unsigned int flag2 = 0;
    	sequence=0;     //init sequence
  	
	/* Configure the green LED control pin. */
  	InitGPIO1();
	ledInitGPIO2();
  
  	while (1){
	
        if(HWREG(SOC_GPIO_1_REGS+GPIO_DATAIN) & (1<<16)){ //when button is pressed
            sequence ^= 1;                                //change sequence
        }                                                //pulling button

		if(!sequence){        //sequence 1
		    flagBlink ^= TOGGLE;
		    if(flagBlink){
			    gpioSetPinValue(GPIO1, 21, HIGH);
			    delay();
			    gpioSetPinValue(GPIO1, 22, HIGH);
			    delay();
			    gpioSetPinValue(GPIO1, 23, HIGH);
			    delay();
			    gpioSetPinValue(GPIO1, 24, HIGH);
			    delay();
			    gpioSetPinValue(GPIO2, 6, HIGH);
			    delay();
			    gpioSetPinValue(GPIO2, 7, HIGH);
		    }else{
	    		    gpioSetPinValue(GPIO1, 21, LOW);
			    delay();
			    gpioSetPinValue(GPIO1, 22, LOW);
			    delay();
			    gpioSetPinValue(GPIO1, 23, LOW);
			    delay();
			    gpioSetPinValue(GPIO1, 24, LOW);
			    delay();
			    gpioSetPinValue(GPIO2, 6, LOW);
			    delay();
			    gpioSetPinValue(GPIO2, 7, LOW);
			}
		}else{              //sequence 2
		    flag2 ^= TOGGLE;
		    if(flag2){
			    gpioSetPinValue(GPIO2, 6, HIGH);
			    delay();
			    gpioSetPinValue(GPIO1, 24, HIGH);
			    delay();
			    gpioSetPinValue(GPIO1, 21, HIGH);
			    delay();
			    gpioSetPinValue(GPIO1, 22, HIGH);
			    delay();
			    gpioSetPinValue(GPIO1, 23, HIGH);
			    delay();
			    gpioSetPinValue(GPIO2, 7, HIGH);
		    }else{
	    		    gpioSetPinValue(GPIO2, 6, LOW);
			    delay();
			    gpioSetPinValue(GPIO1, 24, LOW);
			    delay();
			    gpioSetPinValue(GPIO1, 21, LOW);
			    delay();
			    gpioSetPinValue(GPIO1, 22, LOW);
			    delay();
			    gpioSetPinValue(GPIO1, 23, LOW);
			    delay();
			    gpioSetPinValue(GPIO2, 7, LOW);
			}
		}	
	}

	return(0);
} /* ----------  end of function main  ---------- */


/*FUNCTION*-------------------------------------------------------
*
* Function Name : Delay
* Comments      :
*END*-----------------------------------------------------------*/
static void delay(){
	volatile unsigned int ra;
	for(ra = 0; ra < TIME; ra ++);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledInit
 *  Description:  
 * =====================================================================================
 */
void InitGPIO1( ){
	
	unsigned int val_temp; 	
	/*-----------------------------------------------------------------------------
	 *  configure clock GPIO in clock module
	 *-----------------------------------------------------------------------------*/
	HWREG(SOC_CM_PER_REGS+CM_PER_GPIO1) |= CM_PER_GPIO1_CLKCTRL_OPTFCLKEN_GPIO_1_GDBCLK | CM_PER_GPIO1_CLKCTRL_MODULEMODE_ENABLE;
	
	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/
 	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a5) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a6) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a7) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a8) |= 7;

    HWREG(SOC_CONTROL_REGS+CM_conf_gpmc_a0) |= 7;

	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	val_temp = HWREG(SOC_GPIO_1_REGS+GPIO_OE);
	val_temp &= ~(1<<21);
	val_temp &= ~(1<<22);
	val_temp &= ~(1<<23); // led was defined as output
	val_temp &= ~(1<<24);

    val_temp |= (1<<16); // button was defined as input
	HWREG(SOC_GPIO_1_REGS+GPIO_OE) = val_temp;
	
}/* -----  end of function ledInit  ----- */

void ledInitGPIO2(){
	unsigned int val_temp; 	
	/*-----------------------------------------------------------------------------
	 *  configure clock GPIO in clock module
	 *-----------------------------------------------------------------------------*/
	HWREG(SOC_CM_PER_REGS+CM_PER_GPIO2) |= CM_PER_GPIO2_CLKCTRL_OPTFCLKEN_GPIO_2_GDBCLK | CM_PER_GPIO2_CLKCTRL_MODULEMODE_ENABLE;
	
	/*-----------------------------------------------------------------------------
	 * configure mux pin in control module
	 *-----------------------------------------------------------------------------*/
 	HWREG(SOC_CONTROL_REGS+CM_conf_lcd_data0) |= 7;
	HWREG(SOC_CONTROL_REGS+CM_conf_lcd_data1) |= 7;

	/*-----------------------------------------------------------------------------
	 *  set pin direction 
	 *-----------------------------------------------------------------------------*/
	val_temp = HWREG(SOC_GPIO_2_REGS+GPIO_OE);
	val_temp &= ~(1<<6);
	val_temp &= ~(1<<7);
	HWREG(SOC_GPIO_2_REGS+GPIO_OE) = val_temp;
	
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ledToggle
 *  Description:  
 * =====================================================================================
 */


/*void ledToggle(unsigned int port, unsigned int pin){
    flagBlink ^= TOGGLE;

    if(port == 1){
        if(flagBlink){
            HWREG(SOC_GPIO_1_REGS+GPIO_SETDATAOUT) = 1<<pin;
        }else{
            HWREG(SOC_GPIO_1_REGS+GPIO_CLEARDATAOUT) = 1<<pin;
        }
    }else if(port == 2){
        if(flagBlink){
            HWREG(SOC_GPIO_2_REGS+GPIO_SETDATAOUT) = 1<<pin;
        }else{
            HWREG(SOC_GPIO_2_REGS+GPIO_CLEARDATAOUT) = 1<<pin;
        }
    }
}*/

