/*
 * 3X8E_PMC_SystemClock.c
 *
 * Created: 27.01.2024 01:27:56
 * Author : rottenCoriander
 */ 


#include "sam.h"


int main(void)
{
    /* Initialize the SAM system */
    SystemInit(); //from system_sam3a.c, see file for explanation.


    /* Replace with your application code */
    while (1) 
    {
    }
}

//Initialization System Clock to use External Oscillator, 12Mhz for Example Here
void SystemInit_Ext12Mhz_MckNoDivide(){
	/* Set FWS according to SYS_BOARD_MCKR configuration */

  //EFC0->EEFC_FMR = EEFC_FMR_FWS(4);
  //EFC0->EEFC_FMR = ( (0xfu << 8) & (4 << 8) )
  //EFC1->EEFC_FMR = EEFC_FMR_FWS(4);
  //EFC1->EEFC_FMR = ( (0xfu << 8) & (4 << 8) );

  /* Initialize main oscillator */
  if ( !(PMC->CKGR_MOR & CKGR_MOR_MOSCSEL   /*(0x1u << 24)*/) ){ //Check if The Main Crystal Oscillator is selected.
   //If The Main Crystal Oscillator is not selected:
    PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | (CKGR_MOR_MOSCXTST(0x8)) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN; 
	/*	
		PASSKEY| MOSCTXT| Main On-Chip RC Oscillator| Main Crystal Oscillator Enable	
		PASSKEY: Passkey for the Register	
		MOSCTXT: Specifies the number of Slow Clock cycles multiplied by 8 for the Main Crystal Oscillator start-up time.
		PMC->CKGR_MOR = (0x37u << 16) | ((0xffu << 8) & (0x8 << 8)) | (0x1u << 3) | (0x1u << 0); 
	*/

    while ( !(PMC->PMC_SR & PMC_SR_MOSCXTS   /*(0x1u << 0)*/) )  //Wait until Main XTAL oscillator is stabilized
    {
    }
  }

  /* Switch to 3-20MHz Xtal oscillator */
  
	PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | (CKGR_MOR_MOSCXTST(0x8)) | CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN | CKGR_MOR_MOSCSEL;	
    /*
	PASSKEY| MOSCTXT| Main On-Chip RC Oscillator| Main Crystal Oscillator Enable| Select the Main Crystal Oscillator
	PMC->CKGR_MOR = (0x37u << 16) | ((0xffu << 8) & (0x8 << 8)) | (0x1u << 3) | (0x1u << 0) | (0x1u << 24) ;
	*/
	
	
	/*
    MOSCSELS: Main Oscillator Selection Status
	 0 = Selection is done.
	 1 = Selection is in progress
    */
  while ( !(PMC->PMC_SR & PMC_SR_MOSCSELS /*(0x1u << 16)*/) ) //Wait until Main Oscillator Selection is in progress
  {
  }
 	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(uint32_t)PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
    
    /*
    CSS bit 0:1
		0 SLOW_CLK Slow Clock is selected
		1 MAIN_CLK Main Clock is selected
		2 PLLA_CLK PLLA Clock is selected
		3 UPLL_CLK UPLL Clock is selected
	//PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(3) | (0x1u << 0) ; 	
    */

  while (!(PMC->PMC_SR & PMC_SR_MCKRDY  /*(0x1u << 3)*/))//Wait until Master Clock is ready
  {
  }

  /* Initialize PLLA */
  PMC->CKGR_PLLAR = (CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(0xdUL) | CKGR_PLLAR_PLLACOUNT(0x3fUL) | CKGR_PLLAR_DIVA(0x1UL));
  /*
  
	ONE|PLLA Multiplier|PLLACOUNT: PLLA Counter|Divider Bypass
	ONE: Must Be Set to 1
	MULA: 1 up to 2047 = The PLLA Clock frequency is the PLLA input frequency multiplied by MULA + 1.
	PLLACOUNT: PLLA Counter Specifies the number of Slow Clock cycles x8 before the LOCKA bit is set in PMC_SR after CKGR_PLLAR is written.
	DIVA: Divider  
		0 Divider output is 0
		1 Divider is bypassed (DIVA=1)
		2 - 255 Divider output is DIVA
	
	PMC->CKGR_PLLAR = (0x1u << 29) |((0x7ffu << 16) & (0xdUL << 16))|((0x3fu << 8) & (0x3fUL << 8))|((0xffu << 0) & (0x1UL << 0));
*/
  while ( !(PMC->PMC_SR & PMC_SR_LOCKA  /*(0x1u << 1)*/) ) //Wait until PLLA is Locked
  {
  }

  /* Switch to main clock */
  PMC->PMC_MCKR = PMC_MCKR_CSS_MAIN_CLK ;//(0x1u << 0)
  /*
   PMC_MCKR_CSS_MAIN_CLK (0x1u << 0)
   CSS: Master Clock Source Selection 0:1
	0 SLOW_CLK Slow Clock is selected
	1 MAIN_CLK Main Clock is selected
	2 PLLA_CLK PLLA Clock is selected
	3 UPLL_CLK UPLL Clock is selected
  */
  
  while ( !(PMC->PMC_SR & PMC_SR_MCKRDY /*(0x1u << 3)*/) )//Wait until Master Clock is ready
  {
  }

  /* Switch to PLLA */
  /*
  PMC->PMC_MCKR = SYS_BOARD_MCKR;
  while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) )
  {
  }

  SystemCoreClock = CHIP_FREQ_CPU_MAX;
  */
}
