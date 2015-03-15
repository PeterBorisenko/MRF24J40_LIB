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


#include "spi_device.h"
#include "MRF24J40.h"
#include "AppConfig.h"
//#include "ring_buffer.h"
/*
 * 
 */
#ifdef __DEBUG
#define test(x) (if(x){exception()})
#define DEBUG_PORT PORTB
#define DEBUG_DDR TRISB
#define DEBUG_LED 7
#define DEBUG_PIN 6

#define DEVICE_DDR  TRISBbits.TRISB3
#define DEVICE_CS   PORTBbits.RB3

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

MRF24J40_t  * pDevice;
ctrlPins_t ctrls;
spiDevice_t spiMRF24J40;

void sendBuffer(char * buf) {
    dataWriteLA(pDevice->spiMRF24J40, TX_FIFO, buf, 64);
}

void main() {

    ctrls.wakeUp.tris= TRISAbits.TRISA0; // TODO: define pins/ports in AppConfig.h
    ctrls.wakeUp.pin= PORTAbits.RA0;
    ctrls.wakeUp.pol= W_POL;

    ctrls.reset.tris= TRISAbits.TRISA1;
    ctrls.reset.pin= PORTAbits.RA1;
    ctrls.reset.pol= R_POL;

    ctrls.interrupt.tris= TRISBbits.TRISB0;
    ctrls.interrupt.pin= PORTBbits.RB0;
    ctrls.interrupt.pol= I_POL;

    unsigned char devName[]= "MRF_node01";
    spiMRF24J40= SPI_deviceInit(DEVICE_DDR, DEVICE_CS, devName, 0);

    MRF24J40_t device;
    device.devAddress= DEVICE_ADDRESS;
    device.ctrl= ctrls;
    device.spiMRF24J40= &spiMRF24J40;
    pDevice= &device;

    char rxBuffer[64];
    char * pRX= &rxBuffer;
    char txBuffer[64];
    char * pTX= &txBuffer;

    deviceStart(pDevice, Ch11);
    //rBuffer_t *H_queue= newRingBuffer(16);
    //uint16_t addr= 0x333;
    //unsigned char data= 0b01010111;
    
    uint8_t cnt= 64;
    //ei();
    while (1) {
        //deviceSleep();
        *pTX= readRSSI(pDevice);
        cnt--;
        pTX++;
        if (cnt == 0) {
            pTX= &txBuffer;
            sendBuffer(pTX);
        }
    }
}
