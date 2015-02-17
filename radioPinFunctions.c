/*
* ----------------------------------------------------------------------------
* “THE COFFEEWARE LICENSE” (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
* Please define your platform spesific functions in this file ...
* -----------------------------------------------------------------------------
*/

#include <avr/io.h>

#define set_bit(reg,bit) reg |= (1<<bit)
#define clr_bit(reg,bit) reg &= ~(1<<bit)
#define check_bit(reg,bit) (reg&(1<<bit))

/* ------------------------------------------------------------------------- */
void nrf24_setupPins(void)
{
    set_bit(DDRB,PB0);//0); // CE output
    set_bit(DDRB,PB1);//1 // CSN output
    set_bit(DDRB,PB5); //2 SCK output
    set_bit(DDRB,PB3); //3 MOSI output
    clr_bit(DDRB,PB4); //4 MISO input
}
/* ------------------------------------------------------------------------- */
void nrf24_ce_digitalWrite(uint8_t state)
{
    if(state)
    {
        set_bit(PORTB,PB0);
    }
    else
    {
        clr_bit(PORTB,PB0);
    }
}
/* ------------------------------------------------------------------------- */
void nrf24_csn_digitalWrite(uint8_t state)
{
    if(state)
    {
        set_bit(PORTB,PB1);
    }
    else
    {
        clr_bit(PORTB,PB1);
    }
}
/* ------------------------------------------------------------------------- */
void nrf24_sck_digitalWrite(uint8_t state)
{
    if(state)
    {
        set_bit(PORTB,PB5);
    }
    else
    {
        clr_bit(PORTB,PB5);
    }
}
/* ------------------------------------------------------------------------- */
void nrf24_mosi_digitalWrite(uint8_t state)
{
    if(state)
    {
        set_bit(PORTB,PB3);
    }
    else
    {
        clr_bit(PORTB,PB3);
    }
}
/* ------------------------------------------------------------------------- */
uint8_t nrf24_miso_digitalRead(void)
{
    return check_bit(PINB,PB4);
}
/* ------------------------------------------------------------------------- */
