#include "spi_device.h"
#include <string.h>

volatile static spiMutex_t spiMutex;

void SPI_Init(void)
{
    // SPI I/O Ports Init
#ifdef SPI_MASTER
    SDI_DDR= PIN_INPUT;
    SDO_DDR= PIN_OUTPUT;
    SCK_DDR= PIN_OUTPUT;
#else
    SDI_DDR= PIN_OUTPUT;
    SDO_DDR= PIN_INPUT;
    SCK_DDR= PIN_OUTPUT;
#endif

    // SPI Control & Status Registers Init
    SPI_ENABLE= 1;
    SPI_MODE= 1;
    SPI_PHASE= 1;
    SPI_CLOCK_EDGE= 0;
}

spiDevice_t SPI_deviceInit(unsigned char devDdr, unsigned char csPin,  unsigned char * buffer, uint8_t pr) {
    devDdr= PIN_OUTPUT;
    spiDevice_t spd;
    spd.csPin= csPin;
    strcpy(spd.name, buffer);
    spd.priority= pr;
    return spd;
}

inline uint8_t chipSelect(spiDevice_t * spd){
    if (spiMutex == MUTEX_FREE) {
        spiMutex= MUTEX_CAPTURED;
        spd->activity= spiMutex;
        spd->csPin= CHIP_SELECTED;
        return 1;
    }
    else {
        return 0;
    }
}

inline uint8_t chipRelease(spiDevice_t * spd){
    if (spd->activity == MUTEX_CAPTURED) {
        spd->csPin= CHIP_NOT_SELECTED;
        spiMutex= MUTEX_FREE;
        spd->activity= spiMutex;
        return 1;
    }
    else {
        return 0;
    }
}

void SPI_WriteByte(spiDevice_t * spd, uint8_t data)
{
   chipSelect(spd);
   SPI_BUFFER = data;
   while(SPI_BUFFER_EMPTY);
   chipRelease(spd);
}

uint8_t SPI_ReadByte(spiDevice_t * spd, uint8_t addr)
{
   uint8_t report;
   chipSelect(spd);
   SPI_BUFFER = addr;
   while(SPI_BUFFER_EMPTY);
   report = SPI_BUFFER;
   chipRelease(spd);

   return report;
}

void SPI_WriteArray(spiDevice_t * spd, uint8_t command, uint8_t * buffer, uint8_t num)
{
   SPI_WriteByte(spd, command);
   chipSelect(spd);
   while(SPI_BUFFER_EMPTY);
   while(num--){
      SPI_BUFFER = *buffer++;
      while(SPI_BUFFER_EMPTY);
   }
   chipRelease(spd);
}

void SPI_ReadArray(spiDevice_t * spd, uint8_t command, uint8_t * buffer, uint8_t num)
{
   SPI_WriteByte(spd, command);
   chipSelect(spd);
   while(SPI_BUFFER_EMPTY);
   while(num--){
      //SPI_BUFFER = *buffer;
      while(SPI_BUFFER_EMPTY);
      *buffer++ = SPI_BUFFER;
   }
   chipRelease(spd);
}

inline void waitForSPI(){
    while(SPI_BUFFER_EMPTY);
}
