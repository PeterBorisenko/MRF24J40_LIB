/* 
 * File:   spi.h
 * Author: Disgust
 *
 * Created on 9 ???? 2015 ?., 22:42
 */

#ifndef SPI_DEVICE_H
#define	SPI_DEVICE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <stdint.h>


#if defined(_PIC12E)
#include "spi_16f1454.h"
#elif defined(_16F88)
#include "spi_16f88.h"
#endif

#define SPI_MASTER

#define MUTEX_CAPTURED   1
#define MUTEX_FREE  0

typedef uint8_t spiMutex_t;

typedef struct {
    unsigned char * name;
    unsigned char csPin;
    uint8_t priority;
    spiMutex_t activity;
}spiDevice_t;

#define CHIP_SELECTED 0
#define CHIP_NOT_SELECTED 1

    // SPI core functions
    void SPI_Init(void);
    spiDevice_t SPI_deviceInit(unsigned char, unsigned char, unsigned char *, uint8_t);
    
    void SPI_WriteByte(spiDevice_t *, uint8_t);
    uint8_t SPI_ReadByte(spiDevice_t *, uint8_t);
    void SPI_WriteArray(spiDevice_t *, uint8_t, uint8_t *, uint8_t);
    void SPI_ReadArray(spiDevice_t *, uint8_t, uint8_t *, uint8_t);

    inline uint8_t chipSelect(spiDevice_t *);
    inline uint8_t chipRelease(spiDevice_t *);
    inline void waitForSPI(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_DEVICE_H */

