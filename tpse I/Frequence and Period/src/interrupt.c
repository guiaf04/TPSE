#include "interrupt.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ISR_Handler
 *  Description:  
 * =====================================================================================
 */
void ISR_Handler(void){

	uartPutString(UART0, "Interrupt Processed!\n\r", 22);

	/* Verifica se é interrupção do RTC */
	unsigned int irq_number = HWREG(INTCPS + INTC_SIR_IRQ) & 0x7f;
	
	if(irq_number == 95)
		timerIrqHandler();
    else if(irq_number == 98)
        gpioIsrHandler();    
    
	/* Reconhece a IRQ */
	HWREG(INTCPS + INTC_CONTROL) = 0x1;
}

void interrupt_setup(unsigned int mod){
	unsigned int MIR_CLEAR = mod / 32;
	unsigned int mask = mod % 32;

	switch (MIR_CLEAR) {
			case 0:
				HWREG(INTCPS + INTC_MIR_CLEAR0) |= (1<<mask);
			break;
			case 1:	
				HWREG(INTCPS + INTC_MIR_CLEAR1) |= (1<<mask);
			break;
			case 2:	
				HWREG(INTCPS + INTC_MIR_CLEAR2) |= (1<<mask);
			break;
			case 3:	
				HWREG(INTCPS + INTC_MIR_CLEAR3) |= (1<<mask);
			break;
			default:	
			break;
		}


}

