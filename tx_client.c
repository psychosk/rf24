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
#include <avr/interrupt.h>

//#define F_CPU 16000000UL // 16 MHz

// Calculate the value needed for 
// the CTC match value in OCR1A.
#define CTC_MATCH_OVERFLOW ((F_CPU / 1000) / 8) 


/* ------------------------------------------------------------------------- */
//uint8_t temp;
uint8_t q = 0;
uint8_t data_array[1];

uint8_t tx_address0[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t tx_address1[5] = {0xC2,0xC2,0xC2,0xC2,0xC2};
uint8_t tx_address2[5] = {0xC2,0xC2,0xC2,0xC2,0xD3};
uint8_t tx_address3[5] = {0xC2,0xC2,0xC2,0xC2,0xE4};
uint8_t tx_address4[5] = {0xC2,0xC2,0xC2,0xC2,0xF5};
uint8_t tx_address5[5] = {0xC2,0xC2,0xC2,0xC2,0xA6};

volatile uint16_t sent[10];
volatile uint16_t success[10];
volatile uint16_t fail[10];
volatile uint8_t latency[10];

volatile uint8_t ready = 1;

volatile unsigned long timer1_millis;
volatile unsigned long timeOfLastTransmission;

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

ISR (TIMER1_COMPA_vect)
{
    timer1_millis++;
	if (timer1_millis % 1000 == 0){
		printWord(sent[0]);printString(",");printWord(success[0]);printString(",");
		printWord(fail[0]);printString(",");printWord(latency[0]);printString(",");
		double avgLatency = latency[0]/success[0];
		printWord(avgLatency);
		printString("\r\n");
		//printString("Seconds:");printWord(timer1_millis/1000);printString("\r\n");
		sent[0]=0;
		fail[0]=0;
		success[0]=0;
		latency[0]=0;
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
		++success[0];
		latency[0] += (timer1_millis - timeOfLastTransmission);
		ready = 1;
    } else if (rv & (1 << MAX_RT)){
		//printString("[int]Max retries exceeded!\r\n");
		//uint8_t toWrite = _BV(MAX_RT);
		//reset
		//nrf24_writeRegister(STATUS, &toWrite, 1);
		++fail[0];
		//timeOfLastTransmission = 0;
		ready = 1;
	} else if (rv & (1 << RX_DR)){
		//printString("[int]Message received!\r\n");
		//uint8_t toWrite = _BV(RX_DR);
		//reset
		//nrf24_writeRegister(STATUS, &toWrite, 1);		
	}	
}

/* ------------------------------------------------------------------------- */
int main(void)
{

	int transmitterNumber = 0;

	initUSART();
	DDRB |= (1 << PB2); //enable writing on PB2 for LED

	// CTC mode, Clock/8
    TCCR1B |= (1 << WGM12) | (1 << CS11);

    // Load the high byte, then the low byte
    // into the output compare
    OCR1AH = (CTC_MATCH_OVERFLOW >> 8);
    OCR1AL = CTC_MATCH_OVERFLOW;

    // Enable the compare match interrupt
    TIMSK1 |= (1 << OCIE1A);
	
	initInterrupts();
	
    /* simple greeting message */
    printString("\r\n> TX device ready\r\n");
    
    /* init hardware pins */
    nrf24_init();
    
    /* Channel #2 , payload length: 4 */
    nrf24_config(2,1,1);

    /* Set the device addresses */

	if (transmitterNumber==0){
		nrf24_tx_address(tx_address0);
		nrf24_rx_address(tx_address0,0);
        //data_array[0] = 0x73;//data_array[1] = 0x00;data_array[2] = 0x00;data_array[3] = 0x02;                                    
	} else if (transmitterNumber==1){
		nrf24_tx_address(tx_address1);
		nrf24_rx_address(tx_address1,0);
        //data_array[0] = 0x00;//data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x03;                                    
	} else if (transmitterNumber==2){
		nrf24_tx_address(tx_address2);
		nrf24_rx_address(tx_address2,0);
        //data_array[0] = 0x00;//data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x04;                                    
	} else if (transmitterNumber==3){
		nrf24_tx_address(tx_address3);
		nrf24_rx_address(tx_address3,0);
        //data_array[0] = 0x00;//data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x05;                                    
	} else if (transmitterNumber==4){
		nrf24_tx_address(tx_address4);
		nrf24_rx_address(tx_address4,0);
        //data_array[0] = 0x00;//data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x06;                                    
	} else if (transmitterNumber==5){
		nrf24_tx_address(tx_address5);
		nrf24_rx_address(tx_address5,0);
        //data_array[0] = 0x00;//data_array[1] = 0x07;data_array[2] = 0x03;data_array[3] = 0x07;                                    
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

		//printString("About to send!\r\n");

		//flash(1,100);

		data_array[0]=q;

		q++;
	
		if (q==255){
			q=0;
		}

        /* Automatically goes to TX mode */
		while (!ready){};
        nrf24_send(data_array);
		timeOfLastTransmission = timer1_millis;
		++sent[0];
        ready = 0;
		
		//_delay_ms(10);
		
        /* Wait for transmission to end */
        //int i = 0;
		//while(nrf24_isSending())
		//{
				//if (i++>1000){
					//i=0;
					//flash(5,50);
					//printString("Giving up after 10000 still sendings\r\n");
				//}
		//}

		//printString("Gave up?");printByte(done);printString("\r\n");

        /* Make analysis on last tranmission attempt */
        //temp = nrf24_lastMessageStatus();

        //if(temp == NRF24_TRANSMISSON_OK)
        //{
			//flash(1,200);
            //printString("> Tranmission went OK\r\n");
        //}
        //else if(temp == NRF24_MESSAGE_LOST)
        //{
			//flash(3,50);
            //printString("> Message is lost ...\r\n");    
        //}
        
		/* Retranmission count indicates the tranmission quality */
		//temp = nrf24_retransmissionCount();
		//printString("> Retranmission count: ");printByte(nrf24_retransmissionCount());printString("\r\n");
		//printString("> Lost packet count: ");printByte(nrf24_totalLostPacketCount());printString("\r\n");
	

		/* Optionally, go back to RX mode ... */
		//nrf24_powerUpRx();

		/* Or you might want to power down after TX */
		//nrf24_powerDown();            

		/* Wait a little ... */
		
    }
}
/* ------------------------------------------------------------------------- */
