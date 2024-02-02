/*
 * 3X8E_UART_SerialConsole.c
 *
 * Created: 02.02.2024 13:21:20
 * Author : rottenCoriander
 */ 


#include "sam.h"
#include "delay.h"
#include "serialConsole.h"


int main(void)
{
    /* Initialize the SAM system */
	
	/*
	Run Main Clock (MAINCK) @ 12Mhz(from XTAL)
	Master Clock (MCK) divide by 2  -> MAINCK/2	
	*/
    SystemInit();
	
	initDelay(12000000UL);

	initSerialConsole(9600);

	/* Replace with your application code */
	while (1)
	{
		serialConsoleWriteln("ABC");
		delay_ms(200);
	}
}
