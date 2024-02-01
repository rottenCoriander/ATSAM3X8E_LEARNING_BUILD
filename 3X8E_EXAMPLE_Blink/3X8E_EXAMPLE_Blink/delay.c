/*
 * delay.c
 *
 * Created: 27.01.2024 14:37:37
 *  Author: ss201040303
 */ 
#include "delay.h"
#include "sam3x8e.h"
#include "component/pmc.h"
#include "component/tc.h"


//unsigned long F_MCK;
unsigned long clockConstant;


void initDelay(unsigned long F_MCK){
//Enable TC0 Peripheral
PMC->PMC_PCER0 |= PMC_PCER0_PID27;
TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN;
//TC0->TC_CHANNEL[0].TC_CCR = 0x01;
TC0->TC_CHANNEL[0].TC_CMR = 0;
TC0->TC_CHANNEL[0].TC_CMR |= TC_CMR_WAVE;
//TC0->TC_CHANNEL[0].TC_CMR |=  (1 << 15) ;

clockConstant = F_MCK/1000000UL;




}

void delay_us(int us){
	TC0->TC_CHANNEL[0].TC_CCR |=TC_CCR_SWTRG;
	//TC0->TC_CHANNEL[0].TC_CCR |=  (1 << 2) ;
	
	while( (TC0->TC_CHANNEL[0].TC_CV/clockConstant) < us );
	
}

void delay_ms(int ms){
	for(int i=0; i < ms; i++){
		delay_us(1000);
	}
}
