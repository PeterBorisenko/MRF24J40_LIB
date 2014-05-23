/* 
 * File:   main.c
 * Author: Peter
 *
 * Created on May 16, 2014, 2:14 AM
 */

#define _XTAL_FREQ 8000000
#define __DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

//#include "spi.h"
#include "MRF24J40.h"
/*
 * 
 */
#ifdef __DEBUG
#define test(x) (if(x){exception()})
#define DEBUG_PORT PORTB
#define DEBUG_DDR TRISB
#define DEBUG_LED 7

void blink(uint8_t pin){
    PORTB^= (1 << pin);
    __delay_ms(500);
}

void exception() {
    DEBUG_DDR|= (1 << DEBUG_LED);
    while(1) {
        blink(DEBUG_LED);
    }
}
#endif

#define SetBit(x,y) x|=(1<<y)
#define ClearBit(x,y) x&=~(1<<y)
#define WriteBit(x,y,z) (z?SetBit(x,y):ClearBit(x,y))


void main() {
    deviceInit();
    //uint16_t addr= 0x333;
    //unsigned char data= 0b01010111;
    readRSSI();
    //ei();
    while (1) {
        //deviceSleep();
    }
}