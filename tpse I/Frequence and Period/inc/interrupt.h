#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "hw_types.h"
#include "soc_AM335x.h"
#include "timer.h"
#include "gpio.h"
#include "uart.h"

//#define INTERRUPT_TIMER
#define INTERRUPT_GPIO
#define INTCPS                          0x48200000
#define INTC_MIR_CLEAR0                 0x88
#define INTC_MIR_CLEAR1                 0xA8
#define INTC_MIR_CLEAR2                 0xC8
#define INTC_MIR_CLEAR3                 0xE8
#define INTC_SIR_IRQ                    0x40
#define INTC_CONTROL                    0x48


void ISR_Handler(void);
void interrupt_setup(unsigned int mod);

#endif
