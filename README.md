# ATSAM3X8E_LEARNING_BUILD
This Repository is to build up my own lib and learning progress with Atmel ATSAM3X8E (Base on Arduino DUE)

## ATSAM3X8E
**System Core**

  ARM Cortex-M3 revision 2.0 running at up to 84 MHz

**Memories**

  256 to 512 Kbytes embedded Flash, 128-bit wide access, memory accelerator, dual bank

  32 to 100 Kbytes embedded SRAM with dual banks

  16 Kbytes ROM with embedded bootloader routines (UART, USB) and IAP routines

  Static Memory Controller (SMC): SRAM, NOR, NAND support. NFC with 4 Kbyte RAM buffer and ECC
| | |
|-|-|
|Flash                   |2*256 Kbytes|
|SRAM                    |64+32 Kbytes|
|NAN Flash Controller    |YES         |
|Number of PIOs          |103         |
|SHDN Pin                |YES         | 
|EMAC                    |MII/RMII    |
|External Bus Interface  |16-bit data, 8 chip selects, 23-bit address|
|SDRAM Controller        |-           |
|Central DMA             |6           |
|12-bit ADC              |16 ch.      |
|12-bit DAC              |2 ch.       |
|32-bit Timer            |9 ch.       |
|PDC Channels            |17          |
|UART/USART              |3/2         |
|SPI                     |1 SPI controller, 4 chip selects + 3 USART with SPI mode|
|HSMCI                   |1 slot, 8 bits|

## Changelog
27.01.23 - Repository Created

27.01.23 - PMC_SystemClock Uploaded

01.02.23 - EXAMPLE_Blink Uploaded

01.02.23 - TC_Delay Uploaded
