/*
 * 3X8E_EXAMPLE_Blink.c
 *
 * Created: 01.02.2024 00:58:04
 * Author : rottenCoriander
 */ 


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

    initDelay(6000000ul);//void initDelay(unsigned long F_MCK)

	
    PMC->PMC_PCER0 |= (1 << 12); //Enable Peripheral PIOB
    
    PIOB->PIO_WPMR = (0x50494F << PIO_WPMR_WPKEY_Pos); //Disable Write Protect See with KEY,see Datasheet p. 674
	PIOB->PIO_PER = (1 << 27);	//PIO Enable Register
    PIOB->PIO_PUER = (1 << 27); //Pull-Up Resistor Enable Register
    PIOB->PIO_OER = (1 << 27);	//Output Enable Register    
    PIOB->PIO_OWER = (1 << 27);	//Output Write Enable Register


    /* Replace with your application code */
    while (1)
    {
	    
	    PIOB->PIO_ODSR &= ~(1 << 27);// Output Data Status Register
	    delay_ms(500);
	    PIOB->PIO_ODSR |= (1 << 27);
	    delay_ms(500);
	    
    }
}
