/*
* ----------------------------------------------------------------------------
* “THE COFFEEWARE LICENSE” (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
* This library is based on this library: 
*   https://github.com/aaronds/arduino-nrf24l01
* Which is based on this library: 
*   http://www.tinkerer.eu/AVRLib/nRF24L01
* -----------------------------------------------------------------------------
*/
#ifndef NRF24
#define NRF24

#include "nRF24L01.h"
#include <stdint.h>

#define LOW 0
#define HIGH 1


#define nrf24_ADDR_LEN 5
#define nrf24_SHORT_ADDR_LEN 1
#define nrf24_CONFIG ((1<<EN_CRC)|(0<<CRCO))

#define NRF24_TRANSMISSON_OK 0
#define NRF24_MESSAGE_LOST   1

#define NRF24_250 0
#define NRF24_1000 1
#define NRF24_2000 2

extern void    initInterrupts(void);

/* adjustment functions */
extern void    nrf24_init(void);
extern void    nrf24_rx_address(uint8_t* adr, uint8_t pipeNumber);
extern void    nrf24_tx_address(uint8_t* adr);
extern void    nrf24_config(uint8_t channel, uint8_t pay_length, uint8_t retry);

extern void    nrf24_speed(uint8_t speed);


/* state check functions */
extern uint8_t nrf24_dataReady(void);
extern uint8_t nrf24_isSending(void);
extern uint8_t nrf24_isSendingWithoutRetry(void);
extern uint8_t nrf24_getStatus(void);
extern uint8_t nrf24_rxFifoEmpty(void);

/* core TX / RX functions */
extern void    nrf24_send(uint8_t* value);
extern void    nrf24_getData(uint8_t* data);

/* use in dynamic length mode */
extern uint8_t nrf24_payloadLength(void);

/* post transmission analysis */
extern uint8_t nrf24_lastMessageStatus(void);
extern uint8_t nrf24_retransmissionCount(void);
extern uint8_t nrf24_totalLostPacketCount(void);

/* Returns the payload length */
extern uint8_t nrf24_payload_length(void);

/* power management */
extern void    nrf24_powerUpRx(void);
extern void    nrf24_powerUpTx(void);
extern void    nrf24_powerDown(void);

extern void zeroArray(uint8_t* arrayP, uint8_t len);
extern void printArray(uint8_t* arrayP, uint8_t len, uint8_t style);
extern void printRegister(const char* name, uint8_t registerN, uint8_t len, uint8_t style);

/* low level interface ... */
extern uint8_t spi_transfer(uint8_t tx);
extern void    nrf24_transmitSync(uint8_t* dataout,uint8_t len);
extern void    nrf24_transferSync(uint8_t* dataout,uint8_t* datain,uint8_t len);
extern void    nrf24_configRegister(uint8_t reg, uint8_t value);
extern void    nrf24_readRegister(uint8_t reg, uint8_t* value, uint8_t len);
extern void    nrf24_writeRegister(uint8_t reg, uint8_t* value, uint8_t len);

/* -------------------------------------------------------------------------- */
/* You should implement the platform spesific functions in your code */
/* -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- */
/* In this function you should do the following things:
 *    - Set MISO pin input
 *    - Set MOSI pin output
 *    - Set SCK pin output
 *    - Set CSN pin output
 *    - Set CE pin output     */
/* -------------------------------------------------------------------------- */
extern void nrf24_setupPins(void);

/* -------------------------------------------------------------------------- */
/* nrf24 CE pin control function
 *    - state:1 => Pin HIGH
 *    - state:0 => Pin LOW     */
/* -------------------------------------------------------------------------- */
extern void nrf24_ce_digitalWrite(uint8_t state);

/* -------------------------------------------------------------------------- */
/* nrf24 CE pin control function
 *    - state:1 => Pin HIGH
 *    - state:0 => Pin LOW     */
/* -------------------------------------------------------------------------- */
extern void nrf24_csn_digitalWrite(uint8_t state);

/* -------------------------------------------------------------------------- */
/* nrf24 SCK pin control function
 *    - state:1 => Pin HIGH
 *    - state:0 => Pin LOW     */
/* -------------------------------------------------------------------------- */
extern void nrf24_sck_digitalWrite(uint8_t state);

/* -------------------------------------------------------------------------- */
/* nrf24 MOSI pin control function
 *    - state:1 => Pin HIGH
 *    - state:0 => Pin LOW     */
/* -------------------------------------------------------------------------- */
extern void nrf24_mosi_digitalWrite(uint8_t state);

/* -------------------------------------------------------------------------- */
//nrf24 MISO pin read function
//- returns: Non-zero if the pin is high 
/* -------------------------------------------------------------------------- */
extern uint8_t nrf24_miso_digitalRead(void);

#endif
