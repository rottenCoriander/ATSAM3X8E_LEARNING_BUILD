/*
 * 3X8E_TC_Delay.c
 *
 * Created: 27.01.2024 02:54:26
 * Author : rottenCoriander
 */ 


/* For Application Example, see EXAMPLE_Blink */

#include "sam.h"
#include "delay.h"


int main(void)
{
    /* Initialize the SAM system */
	
	/*
	Run Main Clock (MAINCK) @ 12Mhz(from XTAL)
	Master Clock (MCK) divide by 2  -> MAINCK/2	
	*/
    SystemInit();
	
	/*
	void initDelay(unsigned long F_MCK) in delay.h
	agr F_MCK = Clock of Master Clock
	*/
	initDelay(6000000ul);
	
	
	delay_ms(200);
	
	delay_us(200);

    /* Replace with your application code */
    while (1) 
    {
		 
    }
	
	
}
