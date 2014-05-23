#include "MRF24J40.h"
#include "spi.h"

/******************************************************
 *  SPI Core Functions
 ******************************************************/
#ifdef CORE_SPI
void SPI_Init()
{
    // SPI I/O Ports Init
    SPI_DDR&= ~(1 << CS_PIN)&~(1<<SDO_PIN)&~(1<<SCK_PIN);
    SPI_DDR|= (1 << SDI_PIN);
    SPI_PORT|= (1 << CS_PIN);
    
    // SPI Control & Status Registers Init
    SSPCONbits.SSPEN= 1;
    SSPCONbits.SSPM0= 1;
    SSPSTATbits.SMP= 1;
    SSPSTATbits.CKE= 0;
}

inline void chipSelect(){
    SPI_PORT &= ~(1<<CS_PIN);
}

inline void chipRelease(){
    SPI_PORT |= (1<<CS_PIN);
}

void SPI_WriteByte(uint8_t data)
{
   chipSelect();
   SSPBUF = data;
   while(SSPSTATbits.BF);
   chipRelease();
}

uint8_t SPI_ReadByte(uint8_t addr)
{
   uint8_t report;
   chipSelect();
   SSPBUF = addr;
   while(SSPSTATbits.BF);
   report = SSPBUF;
   chipRelease();

   return report;
}

void SPI_WriteArray(uint8_t command, uint8_t num, uint8_t *buffer)
{
   chipSelect();
   SPI_WriteByte(command);
   while(SSPSTATbits.BF);
   while(num--){
      SSPBUF = *buffer++;
      while(SSPSTATbits.BF);
   }
   chipRelease();
}

void SPI_ReadArray(uint8_t command, uint8_t num, uint8_t *buffer)
{
   chipSelect();
   SPI_WriteByte(command);
   while(SSPSTATbits.BF);
   while(num--){
      //SSPBUF = *buffer;
      while(SSPSTATbits.BF);
      *buffer++ = SSPBUF;
   }
   chipRelease();
}
#endif
inline void waitForSPI(){
    while(SSPSTATbits.BF);
}
/******************************************************
 *  SPI R/W Interface Functions
 ******************************************************/
void addrWriteSA(uint8_t addr, uint8_t op) {
// byteWrite doesn't include chipEnable function, which must be called implicitly
    //assert(addr < 0x3F);
    uint8_t command= ADDR_TO_SHORTCOM(addr, op);
    SSPBUF= command;
    waitForSPI();
}
void addrWriteLA(uint16_t addr, uint8_t op) {
// byteWrite doesn't include chipEnable function, which must be called implicitly
    //assert(addr < 0x38F);
    uint16_t command= ADDR_TO_LONGCOM(addr, op);
    SSPBUF= HI_16(command);
    waitForSPI();
    SSPBUF= LO_16(command);
    waitForSPI();
}
uint8_t byteReadSA(uint8_t addr){
    uint8_t report;
    chipSelect();
    addrWriteSA(addr, READ);
    report = SSPBUF;
    chipRelease();
    return report;
}
void byteWriteSA(uint8_t addr, uint8_t data){
    chipSelect();
    addrWriteSA(addr, WRITE);
    SSPBUF= data;
    waitForSPI();
    chipRelease();
}
void bitWriteSA(uint8_t addr, uint8_t bitname, bool state) {
    uint8_t temp= byteReadSA(addr);
    state?(temp|=(1<<bitname)):(temp&=~(1<<bitname));
    byteWriteSA(addr, temp);
}
void dataReadSA(uint8_t addr, uint8_t num, uint8_t *buffer) {
    //assert(addr < (0x3F - num*8));
    chipSelect();
    //addrWriteSA(addr, READ);
    for(int i= num; i>0; i--){
        addrWriteSA(addr++, READ);
        //SSPBUF = *buffer; //PENDING: ?????? ????? ??????? ????? ????????? ??????????????.
        *buffer++ = SSPBUF;
        waitForSPI();
    }
    chipRelease();
}
void dataWriteSA(uint8_t addr, uint8_t num, uint8_t *buffer) {
    //assert(addr < (0x3F - num*8));
    chipSelect();
    addrWriteSA(addr, WRITE);
    for(int i= num; i>0; i--){
        SSPBUF= *buffer++;
        waitForSPI();
    }
    chipRelease();
}
uint8_t byteReadLA(uint16_t addr) {
    uint8_t report;
    chipSelect();
    addrWriteLA(addr, READ);
    report= SSPBUF;
    chipRelease();
    return report;
}
void byteWriteLA(uint16_t addr, uint8_t data){
    chipSelect();
    addrWriteLA(addr, WRITE);
    SSPBUF= data;
    waitForSPI();
    chipRelease();
}
void bitWriteLA(uint16_t addr, uint8_t bitname, bool state) {
    uint8_t temp= byteReadLA(addr);
    state?(temp|=(1<<bitname)):(temp&=~(1<<bitname));
    byteWriteLA(addr, temp);
}
void dataReadLA(uint16_t addr, uint8_t num, uint8_t *buffer) {
    //assert(addr < (0x38F - num*8));
    chipSelect();
    //addrWriteLA(addr, READ);
    for(int i= num; i>0; i--){
        addrWriteLA(addr++, READ);        //SSPBUF = *buffer; //PENDING: ?????? ?????? ??? ????? ??????? ????? ????????? ??????????????.
        *buffer++ = SSPBUF;
        waitForSPI();
    }
    chipRelease();
}
void dataWriteLA(uint16_t addr, uint8_t num, uint8_t *buffer) {
    //assert(addr < (0x38F - num*8));
    chipSelect();
    addrWriteLA(addr, WRITE);
    for(int i= num; i>0; i--){
        SSPBUF= *buffer++;
        waitForSPI();
    }
    chipRelease();
}
/******************************************************
 *  Device Control Functions
 ******************************************************/
void deviceReset() {
    SPI_PORT&= ~(1<<RESET_PIN);
    __delay_us(5);
    SPI_PORT|= (1<<RESET_PIN);
    __delay_ms(2);
    
}
void resetPower() {
    bitWriteSA(SOFTRST, RSTPWR, 1);
}
void resetBBand() {
    bitWriteSA(SOFTRST, RSTBB, 1);
}
void resetMAC() {
    bitWriteSA(SOFTRST, RSTMAC, 1);
}
void deviceSoftReset() {
    byteWriteSA(SOFTRST, 0x07);
}
void resetRFStateMashine() {
    bitWriteSA(RFCTL, RFRST, 1);
    bitWriteSA(RFCTL, RFRST, 0);
    __delay_us(192);
}

void setCCAThreshold(uint8_t val) {
    byteWriteSA(CCAEDTH, val);
}
void deviceInit(uint8_t chan) {
    byteWriteSA(SOFTRST, 0x07);
    byteWriteSA(PACON2, 0xB0); // Initialize FIFOEN = 1 and TXONTS = 0x6
    byteWriteSA(TXSTBL, 0x95); // TXSTBL (0x2E) = 0x95 ? Initialize RFSTBL = 0x9
    byteWriteLA(RFCON0, 0x03); // RFCON0 (0x200) = 0x03 ? Initialize RFOPT = 0x03
    byteWriteLA(RFCON1, 0x01); // RFCON1 (0x201) = 0x01 ? Initialize VCOOPT = 0x02
    byteWriteLA(RFCON2, 0x80); // RFCON2 (0x202) = 0x80 ? Enable PLL (PLLEN = 1)
    byteWriteLA(RFCON6, 0x90); // RFCON6 (0x206) = 0x90 ? Initialize TXFIL = 1and 20MRECVR = 1
    byteWriteLA(RFCON7, 0x80); // RFCON7 (0x207) = 0x80 ? Initialize SLPCLKSEL = 0x2 (100 kHz Internal oscillator)
    byteWriteLA(RFCON8, 0x10); // RFCON8 (0x208) = 0x10 ? Initialize RFVCO = 1
    byteWriteLA(SLPCON1, 0x21); // SLPCON1 (0x220) = 0x21 ? Initialize CLKOUTEN= 1and SLPCLKDIV = 0x01
    if(!BEACON_EN) {
        byteWriteSA(BBREG2, 0x80); // BBREG2 (0x3A) = 0x80 ? Set CCA mode to ED
        setCCAThreshold(0x60); // CCAEDTH = 0x60 ? Set CCA ED threshold
        byteWriteSA(BBREG6, 0x40); // BBREG6 (0x3E) = 0x40 ? Set appended RSSI value to RXFIFO
    }
    else {
        //TODO: Init for Beacon-enabled Device
    }
    deviceIntEnable();
    //TODO: Set Transmitter Power function
    deviceChannelSelect(chan);
}
void deviceStart(uint8_t chan) {
    SPI_DDR|= (1<<RESET_PIN)|(1<<WAKEUP_PIN);
    R_POL?(SPI_PORT|= (1<<RESET_PIN)):(SPI_PORT&=~(1<<RESET_PIN));
    W_POL?(SPI_PORT|= (1<<WAKEUP_PIN)):(SPI_PORT&=~(1<<WAKEUP_PIN));
    SPI_Init();
    deviceInit(chan);
    __delay_ms(2);
}

void deviceSleep();

void deviceIntEnable() {
    deviceIntPolarity();
    deviceSetInterrupt(ALL);
}
void deviceSetInterrupt(uint8_t interrupts) {
    byteWriteSA(INTCON, interrupts);
}
uint8_t deviceCheckInterrupts() {
    return byteReadSA(INTSTAT);
}
void deviceIntPolarity() {
    bitWriteLA(SLPCON0, INTEDGE, I_POL);
}

void deviceChannelSelect(uint8_t chan) {
    byteWriteLA(RFCON0, (chan|RF_OPTIMISE));
    resetRFStateMashine();
}

void clearChannelAssesstment(uint8_t val);

void setRSSIMode(uint8_t val);

uint8_t readRSSI() {
    return byteReadLA(RSSI);
}

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