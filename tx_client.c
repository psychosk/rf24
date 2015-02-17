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
uint8_t temp;
uint8_t q = 0;
uint8_t data_array[4];

uint8_t tx_address0[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t tx_address1[5] = {0xC2,0xC2,0xC2,0xC2,0xC2};
uint8_t tx_address2[5] = {0xC2,0xC2,0xC2,0xC2,0xD3};
uint8_t tx_address3[5] = {0xC2,0xC2,0xC2,0xC2,0xE4};
uint8_t tx_address4[5] = {0xC2,0xC2,0xC2,0xC2,0xF5};
uint8_t tx_address5[5] = {0xC2,0xC2,0xC2,0xC2,0xA6};
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

/* ------------------------------------------------------------------------- */
int main(void)
{

	int transmitterNumber = 2;

	initUSART();
	DDRB |= (1 << PB2); //enable writing on PB2 for LED


    /* simple greeting message */
    printString("\r\n> TX device ready\r\n");
    
    /* init hardware pins */
    nrf24_init();
    
    /* Channel #2 , payload length: 4 */
    nrf24_config(2,4);

    /* Set the device addresses */

	if (transmitterNumber==0){
		nrf24_tx_address(tx_address0);
		nrf24_rx_address(tx_address0,0);
        data_array[0] = 0x00;data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x02;                                    
	} else if (transmitterNumber==1){
		nrf24_tx_address(tx_address1);
		nrf24_rx_address(tx_address1,0);
        data_array[0] = 0x00;data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x03;                                    
	} else if (transmitterNumber==2){
		nrf24_tx_address(tx_address2);
		nrf24_rx_address(tx_address2,0);
        data_array[0] = 0x00;data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x04;                                    
	} else if (transmitterNumber==3){
		nrf24_tx_address(tx_address3);
		nrf24_rx_address(tx_address3,0);
        data_array[0] = 0x00;data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x05;                                    
	} else if (transmitterNumber==4){
		nrf24_tx_address(tx_address4);
		nrf24_rx_address(tx_address4,0);
        data_array[0] = 0x00;data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x06;                                    
	} else if (transmitterNumber==5){
		nrf24_tx_address(tx_address5);
		nrf24_rx_address(tx_address5,0);
        data_array[0] = 0x00;data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x07;                                    
	} 
	
	printRegister("TX_ADDR:",TX_ADDR,5,0);
	printRegister("RX_ADDR_P0:",RX_ADDR_P0,5,0);

	printRegister("RF_CH:",RF_CH,1,1);
	printRegister("EN_AA:",EN_AA,1,1);
	printRegister("EN_RXADDR:",EN_RXADDR,1,1);
	printRegister("STATUS:",STATUS,1,1);
	printRegister("CONFIG:",CONFIG,1,1);
	printRegister("RF_SETUP:",RF_SETUP,1,1);
	

    while(1)
    {                
        /* Fill the data buffer */

		printString("About to send!\r\n");

		//flash(1,100);

        /* Automatically goes to TX mode */
        nrf24_send(data_array);        
        
        /* Wait for transmission to end */
        int i = 0;
		while(nrf24_isSending())
		{
				if (i++>1000){
					i=0;
					//flash(5,50);
					//printString("Giving up after 10000 still sendings\r\n");
				}
		}

		//printString("Gave up?");printByte(done);printString("\r\n");

        /* Make analysis on last tranmission attempt */
        temp = nrf24_lastMessageStatus();

        if(temp == NRF24_TRANSMISSON_OK)
        {
			flash(1,200);
            printString("> Tranmission went OK\r\n");
        }
        else if(temp == NRF24_MESSAGE_LOST)
        {
			flash(3,50);
            printString("> Message is lost ...\r\n");    
        }
        
		/* Retranmission count indicates the tranmission quality */
		temp = nrf24_retransmissionCount();
		//printString("> Retranmission count: ");printByte(temp);printString("\r\n");

		/* Optionally, go back to RX mode ... */
		//nrf24_powerUpRx();

		/* Or you might want to power down after TX */
		//nrf24_powerDown();            

		/* Wait a little ... */
		_delay_ms(1000);
    }
}
/* ------------------------------------------------------------------------- */
