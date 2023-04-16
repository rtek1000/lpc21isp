// Initialization and interrupt vectors for the LPC1114 microcontroller
// No claims are made as to the suitability of this code for any 
// purpose whatsoever.  Use at your own risk!
// Does not include initialization for C++ global/static objects
// so probably best to use this with C projects for now.
// Latest version of this code can be found by visiting
// http://eleceng.dit.ie/frank and follow the links
// Author: Frank Duignan

#include "lpc812.h"
void init(void);
void clock_init();
void Default_Handler(void);
void SysTick(void);
// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;

// the section "vectors" is placed at the beginning of flash 
// by the linker script
const void * Vectors[] __attribute__((section(".vectors"))) ={
	(void *)(RAM_START+RAM_SIZE), 	/* Top of stack */ 
	init,   						/* Reset Handler */
	Default_Handler,				/* NMI */
	Default_Handler,				/* Hard Fault */
	0,	                			/* Reserved */
	0,            			 	    /* Reserved */
	0,                  			/* Reserved */
	0,                  			/* Reserved */
	0,                  			/* Reserved */
	0,                  			/* Reserved */
	0,                  			/* Reserved */
	Default_Handler,				/* SVC */
	0,                 				/* Reserved */
	0,                 				/* Reserved */
	Default_Handler,   				/* PendSV */
	Default_Handler, 				/* SysTick */		
/* External interrupt handlers follow */
	Default_Handler,				/* 0 SPI0_IRQ */
	Default_Handler,				/* 1 SPI1_IRQ */
	Default_Handler,				/* 2 RESERVED */
	Default_Handler,				/* 3 UART0_IRQ */
	Default_Handler,				/* 4 UART1_IRQ */
	Default_Handler,				/* 5 UART2_IRQ */
	Default_Handler,				/* 6 RESERVED */
	Default_Handler,				/* 7 RESERVED */
	Default_Handler,				/* 8 I2C0_IRQ */
	Default_Handler,				/* 9 SCT_IRQ */
	Default_Handler,				/* 10 MRT_IRQ */
	Default_Handler,				/* 11 CMP_IRQ */
	Default_Handler,				/* 12 WDT_IRQ */
	Default_Handler,				/* 16 RESERVED */
	Default_Handler,				/* 17 RESERVED */
	Default_Handler,				/* 18 RESERVED */
	Default_Handler,				/* 19 RESERVED */
	Default_Handler,				/* 20 RESERVED */
	Default_Handler,				/* 21 RESERVED */
	Default_Handler,				/* 22 RESERVED */
	Default_Handler,				/* 23 RESERVED */
	Default_Handler,				/* 24 PININT0_IRQ */
	Default_Handler,				/* 25 PININT1_IRQ */
	Default_Handler,				/* 26 PININT2_IRQ */
	Default_Handler,				/* 27 PININT3_IRQ */
	Default_Handler,				/* 28 PININT4_IRQ */
	Default_Handler,				/* 29 PININT5_IRQ */
	Default_Handler,				/* 30 PININT6_IRQ */
	Default_Handler,				/* 31 PININT7_IRQ */
};
void clock_init()
{
	// This function sets the main clock to the PLL
	// The PLL input is the built in 12MHz RC oscillator
	// This is multiplied up to 48MHz for the main clock
	// MSEL = 3, PSEL = 1 see page 51 of UM10398 user manual
	SYSCON_SYSPLLCLKSEL = 0; // select internal RC oscillator
	SYSCON_SYSPLLCTRL = (3 << 0) | (1 << 5); // set divisors/multipliers
	SYSCON_PDRUNCFG &= ~BIT7; // Power up the PLL.
	SYSCON_SYSPLLCLKUEN = 1; // inform PLL of update	
	SYSCON_MAINCLKSEL = 3; // Use PLL as main clock
	SYSCON_MAINCLKUEN = 1; // Inform core of clock update
	
}
void init()
{
// do global/static data initialization
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
	clock_init(); // boost speed to 48MHz
	src= &INIT_DATA_VALUES;
	dest= &INIT_DATA_START;
	len= &INIT_DATA_END-&INIT_DATA_START;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &BSS_START;
	len = &BSS_END - &BSS_START;
	while (len--)
		*dest++=0;
	//clock_init();
	main();
}

void Default_Handler()
{
	while(1);
}
