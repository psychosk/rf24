/*
* ----------------------------------------------------------------------------
* “THE COFFEEWARE LICENSE” (Revision 1):
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
/* ------------------------------------------------------------------------- */
uint8_t rx_address1[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t rx_address2[5] = {0xC2,0xC2,0xC2,0xC2,0xC2};
uint8_t rx_address3[1] = {0xD3};
uint8_t rx_address4[1] = {0xE4};
uint8_t rx_address5[1] = {0xF5};
uint8_t rx_address6[1] = {0xA6};



/**

	

*/

/* ------------------------------------------------------------------------- */

void flash(int count, int delay)
{
	for (int i = 0; i < count; ++i)
	{
		PORTB |= (1 << PB2);
		_delay_ms(delay);
		PORTB &= ~(1 << PB2);
		if (i < (count-1))
		{
			_delay_ms(delay);
		}
	}

}



int main(void)
{
	initUSART();

	DDRB |= (1 << PB2); //enable writing on PB2 for LED

	printString("\r\n> RX device ready\r\n");
	/* init hardware pins */
	nrf24_init();
	/* Channel #2 , payload length: 4 */
	nrf24_config(2,4);


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

	uint8_t data_array[4];

	while(1)
	{
		if(nrf24_dataReady())
		{
			//count=0;
			nrf24_getData(data_array);
			flash(1,200);
			printString("> ");
			printByte(data_array[0]);printString(",");
			printByte(data_array[1]);printString(",");
			printByte(data_array[2]);printString(",");
			printByte(data_array[3]);printString("\r\n");
		}
		//_delay_ms(100);
	}
}
/* ------------------------------------------------------------------------- */