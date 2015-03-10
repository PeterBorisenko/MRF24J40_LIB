#include "MRF24J40.h"

/******************************************************
 *  SPI R/W Interface Functions
 ******************************************************/
void addrWriteSA(uint8_t addr, uint8_t op) {
    //assert(addr < 0x3F);
    uint8_t command= ADDR_TO_SHORTCOM(addr, op);
    SPI_BUFFER= command;
    waitForSPI();
}
void addrWriteLA(uint16_t addr, uint8_t op) {
    //assert(addr < 0x38F);
    uint16_t command= ADDR_TO_LONGCOM(addr, op);
    SPI_BUFFER= HI_16(command);
    waitForSPI();
    SPI_BUFFER= LO_16(command);
    waitForSPI();
}
uint8_t byteReadSA(spiDevice_t * dev, uint8_t addr){
    uint8_t report;
    chipSelect(dev);
    addrWriteSA(addr, READ);
    report = SPI_BUFFER;
    chipRelease(dev);
    return report;
}
void byteWriteSA(spiDevice_t * dev, uint8_t addr, uint8_t data){
    chipSelect(dev);
    addrWriteSA(addr, WRITE);
    SPI_BUFFER= data;
    waitForSPI();
    chipRelease(dev);
}
void bitWriteSA(spiDevice_t * dev, uint8_t addr, uint8_t bitname, bool state) {
    uint8_t temp= byteReadSA(dev, addr);
    state?(temp|=(1<<bitname)):(temp&=~(1<<bitname));
    byteWriteSA(dev, addr, temp);
}
void dataReadSA(spiDevice_t * dev, uint8_t addr, uint8_t *buffer, uint8_t num) {
    //assert(addr < (0x3F - num*8));
    chipSelect(dev);
    //addrWriteSA(addr, READ);
    for(int i= num; i>0; i--){
        addrWriteSA(addr++, READ);
        //SPI_BUFFER = *buffer; //PENDING: ?????? ????? ??????? ????? ????????? ??????????????.
        *buffer++ = SPI_BUFFER;
        waitForSPI();
    }
    chipRelease(dev);
}
void dataWriteSA(spiDevice_t * dev, uint8_t addr, uint8_t *buffer, uint8_t num) {
    //assert(addr < (0x3F - num*8));
    chipSelect(dev);
    addrWriteSA(addr, WRITE);
    for(int i= num; i>0; i--){
        SPI_BUFFER= *buffer++;
        waitForSPI();
    }
    chipRelease(dev);
}
uint8_t byteReadLA(spiDevice_t * dev, uint16_t addr) {
    uint8_t report;
    chipSelect(dev);
    addrWriteLA(addr, READ);
    report= SPI_BUFFER;
    chipRelease(dev);
    return report;
}
void byteWriteLA(spiDevice_t * dev, uint16_t addr, uint8_t data){
    chipSelect(dev);
    addrWriteLA(addr, WRITE);
    SPI_BUFFER= data;
    waitForSPI();
    chipRelease(dev);
}
void bitWriteLA(spiDevice_t * dev, uint16_t addr, uint8_t bitname, bool state) {
    uint8_t temp= byteReadLA(dev, addr);
    state?(temp|=(1<<bitname)):(temp&=~(1<<bitname));
    byteWriteLA(dev, addr, temp);
}
void dataReadLA(spiDevice_t * dev, uint16_t addr, uint8_t *buffer, uint8_t num) {
    //assert(addr < (0x38F - num*8));
    chipSelect(dev);
    //addrWriteLA(addr, READ);
    for(int i= num; i>0; i--){
        addrWriteLA(addr++, READ);        //SSPBUF = *buffer; //PENDING: ?????? ?????? ??? ????? ??????? ????? ????????? ??????????????.
        *buffer++ = SPI_BUFFER;
        waitForSPI();
    }
    chipRelease(dev);
}
void dataWriteLA(spiDevice_t * dev, uint16_t addr, uint8_t *buffer, uint8_t num) {
    //assert(addr < (0x38F - num*8));
    chipSelect(dev);
    addrWriteLA(addr, WRITE);
    for(int i= num; i>0; i--){
        SPI_BUFFER= *buffer++;
        waitForSPI();
    }
    chipRelease(dev);
}
/******************************************************
 *  Device Control Functions
 ******************************************************/
void deviceReset(MRF24J40_t * dev) {
    dev->ctrl.reset.pin= PIN_LO;
    __delay_us(5);
    dev->ctrl.reset.pin= PIN_HI;
    __delay_ms(2);
    
}
void resetPower(MRF24J40_t * dev) {
    bitWriteSA(dev->spiMRF24J40, SOFTRST, RSTPWR, 1);
}
void resetBBand(MRF24J40_t * dev) {
    bitWriteSA(dev->spiMRF24J40, SOFTRST, RSTBB, 1);
}
void resetMAC(MRF24J40_t * dev) {
    bitWriteSA(dev->spiMRF24J40, SOFTRST, RSTMAC, 1);
}
void deviceSoftReset(MRF24J40_t * dev) {
    byteWriteSA(dev->spiMRF24J40, SOFTRST, 0x07);
}
void resetRFStateMashine(MRF24J40_t * dev) {
    bitWriteSA(dev->spiMRF24J40, RFCTL, RFRST, 1);
    bitWriteSA(dev->spiMRF24J40, RFCTL, RFRST, 0);
    __delay_us(192);
}

void deviceInit(MRF24J40_t * dev, uint8_t chan) {
    byteWriteSA(dev->spiMRF24J40, SOFTRST, 0x07);
    byteWriteSA(dev->spiMRF24J40, PACON2, 0xB0); // Initialize FIFOEN = 1 and TXONTS = 0x6
    byteWriteSA(dev->spiMRF24J40, TXSTBL, 0x95); // TXSTBL (0x2E) = 0x95 ? Initialize RFSTBL = 0x9
    byteWriteLA(dev->spiMRF24J40, RFCON0, 0x03); // RFCON0 (0x200) = 0x03 ? Initialize RFOPT = 0x03
    byteWriteLA(dev->spiMRF24J40, RFCON1, 0x01); // RFCON1 (0x201) = 0x01 ? Initialize VCOOPT = 0x02
    byteWriteLA(dev->spiMRF24J40, RFCON2, 0x80); // RFCON2 (0x202) = 0x80 ? Enable PLL (PLLEN = 1)
    byteWriteLA(dev->spiMRF24J40, RFCON6, 0x90); // RFCON6 (0x206) = 0x90 ? Initialize TXFIL = 1and 20MRECVR = 1
    byteWriteLA(dev->spiMRF24J40, RFCON7, 0x80); // RFCON7 (0x207) = 0x80 ? Initialize SLPCLKSEL = 0x2 (100 kHz Internal oscillator)
    byteWriteLA(dev->spiMRF24J40, RFCON8, 0x10); // RFCON8 (0x208) = 0x10 ? Initialize RFVCO = 1
    byteWriteLA(dev->spiMRF24J40, SLPCON1, 0x21); // SLPCON1 (0x220) = 0x21 ? Initialize CLKOUTEN= 1and SLPCLKDIV = 0x01
    if(!BEACON_EN) {
        byteWriteSA(dev->spiMRF24J40, BBREG2, 0x80); // BBREG2 (0x3A) = 0x80 ? Set CCA mode to ED
        setCCAThreshold(dev, 0x60); // CCAEDTH = 0x60 ? Set CCA ED threshold
        byteWriteSA(dev->spiMRF24J40, BBREG6, 0x40); // BBREG6 (0x3E) = 0x40 ? Set appended RSSI value to RXFIFO
    }
    else {
        //TODO: Init for Beacon-enabled Device
    }
    deviceIntEnable(dev);
    //TODO: Set Transmitter Power function
    deviceChannelSelect(dev, chan);
}

void deviceStart(MRF24J40_t * dev, uint8_t chan) {
    dev->ctrl.reset.tris= PIN_INPUT;
    dev->ctrl.wakeUp.tris= PIN_INPUT;
    //SPI_DDR|= (1<<RESET_PIN)|(1<<WAKEUP_PIN);
    dev->ctrl.reset.pin= ((dev->ctrl.reset.pol)?(PIN_HI):(PIN_LO));
    dev->ctrl.wakeUp.pin= ((dev->ctrl.wakeUp.pol)?(PIN_HI):(PIN_LO));
    SPI_Init();
    deviceInit(dev, chan);
    __delay_ms(2);
}

void deviceSleep(MRF24J40_t * dev);

void deviceIntEnable(MRF24J40_t * dev) {
    deviceIntPolarity(dev);
    deviceSetInterrupt(dev, ALL);
}
void deviceSetInterrupt(MRF24J40_t * dev, uint8_t interrupts) {
    byteWriteSA(dev->spiMRF24J40, INTCON, interrupts);
}
uint8_t deviceCheckInterrupts(MRF24J40_t * dev) {
    return byteReadSA(dev->spiMRF24J40, INTSTAT);
}
void deviceIntPolarity(MRF24J40_t * dev) {
    bitWriteLA(dev->spiMRF24J40, SLPCON0, INTEDGE, I_POL);
}

void deviceChannelSelect(MRF24J40_t * dev, uint8_t chan) {
    dev->devChannel= chan;
    byteWriteLA(dev->spiMRF24J40, RFCON0, (chan|RF_OPTIMISE));
    resetRFStateMashine(dev);
}

void clearChannelAssesstment(uint8_t val);


void deviceSetAddress(uint32_t addr_H, uint32_t addr_L);
void deviceSetShortAddress(uint8_t addr);

void setBattThreshold(uint8_t);
void battLifeExt();
void noBattLifeExt();

/* CIPHER SELECTION BITS
 *  111=AES-CBC-MAC-32
 *  110=AES-CBC-MAC-64
 *  101=AES-CBC-MAC-128
 *  100=AES-CCM-32
 *  011=AES-CCM-64
 *  010=AES-CCM-128
 *  001=AES-CTR
 *  000=None(default)
 */
void setSecurityChipher(uint8_t chipher){
    //assert(chipher < 8);
    //TODO: security chipher set function operations
}
/******************************************************
 *  MAC Level Functions
 ******************************************************/
void macBeaconOrder(uint8_t val);
void macSuperframeOrder(uint8_t val);
void macMinBE(uint8_t val);
void macMaxCSMABackoff(uint8_t val);
void macAckWaitDuration(uint8_t val);
void promiscEnable();
void promiscDisable();

void setCCAThreshold(MRF24J40_t * dev, uint8_t val) {
    byteWriteSA(dev->spiMRF24J40, CCAEDTH, val);
}
void setCCAMode(MRF24J40_t * dev, uint8_t mode, uint8_t edthr, uint8_t csthr) {
    switch(mode){
        case CCA_MODE_1:
            byteWriteSA(dev->spiMRF24J40, BBREG2, (mode << CCAMODE0));
            setCCAThreshold(dev, edthr);
            break;
        case CCA_MODE_2:
            byteWriteSA(dev->spiMRF24J40, BBREG2, (mode << CCAMODE0)|(csthr << CCACSTH0));
            break;
        case CCA_MODE_3:
            byteWriteSA(dev->spiMRF24J40, BBREG2, (mode << CCAMODE0)|(csthr << CCACSTH0));
            setCCAThreshold(dev, edthr);
            break;
    }
}

void setRSSIMode(MRF24J40_t * dev, uint8_t val, bool state) {
    bitWriteSA(dev->spiMRF24J40, BBREG6, val, state);
}
void setRSSIAverage(MRF24J40_t * dev, uint8_t val){
    uint8_t temp= byteReadSA(dev->spiMRF24J40, TXBCON1);
    byteWriteSA(dev->spiMRF24J40, TXBCON1, (temp&(0b1100<<RSSINUM0)|(val<<RSSINUM0)));
}
uint8_t readRSSI(MRF24J40_t * dev) {
    bitWriteSA(dev->spiMRF24J40, BBREG6, RSSIMODE1, 1);
    while(!(byteReadSA(dev->spiMRF24J40, BBREG6)&RSSIRDY));
    return byteReadLA(dev->spiMRF24J40, RSSI);
}
int8_t RSSItoDBM(uint8_t rssi) {
    return (int8_t)(((int16_t)rssi*55)/((int16_t)255)-35);
}