/* 
 * File:   main.c
 * Author: Peter
 *
 * Created on May 16, 2014, 2:14 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <xc.h>

//#include "spi.h"
#include "MRF24J40.h"
#define _XTAL_FREQ 8000000
/*
 * 
 */
#define SetBit(x,y) x|=(1<<y)
#define ClearBit(x,y) x&=~(1<<y)
#define WriteBit(x,y,z) (z?SetBit(x,y):ClearBit(x,y))



// Module Control Pins
#define WAKEUP
#define RES
#define MODULE_INT


void main() {
    SPI_Init();
    uint16_t addr= 0x333;
    unsigned char data= 0b01010111;
    uint16_t command= ADDR_TO_LONGCOM(addr, WRITE);
    SSPBUF= HI_16(command);
    waitForSPI();
    SSPBUF= LO_16(command);
    waitForSPI();
    SSPBUF= data;
    waitForSPI();
    //ei();
    while (1) {
        __delay_ms(1);
    }
}