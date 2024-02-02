/*
 * serialConsole.c
 *
 * Created: 02.02.2024 13:25:53
 *  Author: rottenCoriander
 */ 

#include "serialConsole.h"

#include "uart.h"
#include "string.h"

void initSerialConsole(unsigned long BAUD){
	initUart(BAUD);
	
}

void serialConsoleWrite(char *s){
	for(int i = 0; i < strlen(s); i++){
		uartWriteByte(s[i]);
	}
}

void serialConsoleWriteln(char *s){
	for(int i = 0; i < strlen(s); i++){
		uartWriteByte(s[i]);
	}
	uartWriteByte('\n');
}