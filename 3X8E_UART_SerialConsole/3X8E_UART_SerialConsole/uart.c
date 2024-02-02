/*
 * uart.c
 *
 * Created: 02.02.2024 13:25:34
 *  Author: rottenCoriander
 */ 

#include "uart.h"
#include "sam3x8e.h"
#include "component/pmc.h"
#include "component/uart.h"

void initUart(unsigned long BAUD){
	/*
	This Initialization Config the UART in to 8 data bits, No Parity, 1 Stop bit.
	In Order to setup the UART, the corresponding PIO (PA8 -> RX, PA9- > TX) must be Disabled from the PIO peripheral, to release for UART
	*/
	PMC->PMC_PCER0 |= (1 << 11); //Enable Peripheral PIOA

	PIOA->PIO_WPMR = (0x50494F << PIO_WPMR_WPKEY_Pos); //Disable Write Protect See with KEY,see Datasheet p. 674
	PIOA->PIO_PDR = (1 << 9)|(1 << 8);	//PIO Disable Register
	PIOA->PIO_PUER = (1 << 9)|(1 << 8); //Pull-Up Resistor Enable Register
	
	PMC->PMC_PCER0 |= PMC_PCER0_PID8; //Enable Peripheral UART

	UART->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX; //Reset Receiver (bit 2), and Transmitter (bit 3)
	UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN; // Receiver Enable (bit 4), Transmitter Enable (bit 6)

	UART->UART_MR = UART_MR_PAR_NO; //NO Parity (4 << 9)
	UART->UART_BRGR = 12000000UL/(BAUD*16); //Baudrate Register, BAUD=MCK/(CD*16)

	while( !(UART->UART_SR & UART_SR_TXRDY) ); //Wait until transmitter is ready.
	
}


void uartWriteByte(char c){
	UART->UART_THR = c; //Transmit Holding Register
	while( !(UART->UART_SR & UART_SR_TXEMPTY) );// Wait until UART_THR is Empty.
}