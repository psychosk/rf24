/*
* ----------------------------------------------------------------------------
* �THE COFFEEWARE LICENSE� (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
*/
#include <avr/io.h>
//#include <stdint.h>
#include "nrf24.h"
#include <util/delay.h>
#include "USART.h"
#include <avr/interrupt.h>
/* ------------------------------------------------------------------------- */
uint8_t rx_address1[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t rx_address2[5] = {0xC2,0xC2,0xC2,0xC2,0xC2};
uint8_t rx_address3[1] = {0xD3};
uint8_t rx_address4[1] = {0xE4};
uint8_t rx_address5[1] = {0xF5};
uint8_t rx_address6[1] = {0xA6};

volatile int received = 0;

/**

	

*/

/* ------------------------------------------------------------------------- */

void sleep(int delay) {
	for (int i = 0; i < delay; ++i)
		_delay_ms(1);
}


void flash(int count, int delay)
{
	for (int i = 0; i < count; ++i)
	{
		PORTB |= (1 << PB2);
		sleep(delay);
		PORTB &= ~(1 << PB2);
		if (i < (count-1))
		{
			sleep(delay);
		}
	}

}

ISR(INT0_vect){	

	uint8_t rv = nrf24_getStatus();
	
	//if (!rv){
	//printString("[int]Zero status received!\r\n");
	//}
    /* Transmission went OK */
    if((rv & ((1 << TX_DS))))
    {
		//printString("[int]Transmission ok!\r\n");
		//uint8_t toWrite = _BV(TX_DS);
		//reset
		//nrf24_writeRegister(STATUS, &toWrite, 1);
		//++success;
		//ready = 1;
    } else if (rv & (1 << MAX_RT)){
		//printString("[int]Max retries exceeded!\r\n");
		//uint8_t toWrite = _BV(MAX_RT);
		//reset
		//nrf24_writeRegister(STATUS, &toWrite, 1);
		//++fail;
		//ready = 1;
	} else if (rv & (1 << RX_DR)){
		//printString("[int]Message received!\r\n");
		//uint8_t toWrite = _BV(RX_DR);
		//reset
		//nrf24_writeRegister(STATUS, &toWrite, 1);
		//++received;
	}	
	//if (rv && received % 100 == 0){
		//printString(".");
	//}
}

int main(void)
{
	initUSART();

	DDRB |= (1 << PB2); //enable writing on PB2 for LED

	initInterrupts();
	
	printString("\r\n> RX device ready\r\n");
	/* init hardware pins */
	nrf24_init();

	nrf24_config(2,1,1);


	/* Set the device addresses */

	nrf24_rx_address(rx_address1,0); 
	nrf24_rx_address(rx_address2,1); 
	nrf24_rx_address(rx_address3,2); 
	nrf24_rx_address(rx_address4,3); 
	nrf24_rx_address(rx_address5,4); 
	nrf24_rx_address(rx_address6,5); 
	
	printRegister("RX_ADDR_P0:",RX_ADDR_P0,5,0);
	printRegister("RX_ADDR_P1:",RX_ADDR_P1,5,0);
	printRegister("RX_ADDR_P2:",RX_ADDR_P2,1,0);
	printRegister("RX_ADDR_P3:",RX_ADDR_P3,1,0);
	printRegister("RX_ADDR_P4:",RX_ADDR_P4,1,0);
	printRegister("RX_ADDR_P5:",RX_ADDR_P5,1,0);

	printRegister("RF_CH:",RF_CH,1,1);
	printRegister("EN_AA:",EN_AA,1,1);
	printRegister("EN_RXADDR:",EN_RXADDR,1,1);
	printRegister("STATUS:",STATUS,1,1);
	printRegister("CONFIG:",CONFIG,1,1);
	printRegister("RF_SETUP:",RF_SETUP,1,1);

	uint8_t data_array[1];

	while(1)
	{
		if(nrf24_dataReady())
		{
			//count=0;
			nrf24_getData(data_array);
			++received;
			//flash(1,200);
			//printString("> ");
			//printByte(data_array[0]);printString("\r\n");
			//printByte(data_array[1]);printString(",");
			//printByte(data_array[2]);printString(",");
			//printByte(data_array[3]);printString("\r\n");
			if (received % 10 == 0){
				printString(".");
			}
		}
		//_delay_ms(100);
	}
}
/* ------------------------------------------------------------------------- */
