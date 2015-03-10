/* 
 * File:   MRF24J40.h
 * Author: Disgust
 *
 * Created on May 16, 2014, 2:17 AM
 */

#ifndef MRF24J40_H
#define	MRF24J40_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif
    
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
//#include <assert.h>

#include "spi_device.h"
#include "Macro.h"


// Pins Polarity
#ifndef W_POL
#define W_POL 1 //WAKEUP pin polarity
#endif
#ifndef R_POL
#define R_POL 1 //RESET pin polarity
#endif
#ifndef I_POL
#define I_POL 0 //INTEDGE polarity: 0 - Falling, 1 - Rising
#endif

#define DEVICE_ADDRESS  0x00

    typedef struct {
        volatile unsigned char tris;
        volatile unsigned char pin;
        uint8_t pol;
    }ctrlPin_t;

    typedef struct {
        ctrlPin_t wakeUp;
        ctrlPin_t reset;
        ctrlPin_t moduleInt;
    }ctrlPins_t;

    typedef struct {
        uint8_t devAddress;
        uint8_t devChannel;
        ctrlPins_t ctrl;
        spiDevice_t * spiMRF24J40;
    } MRF24J40_t;

#define PIN_HI  1
#define PIN_LO  0


// Transmit and Receive Storage registers
#define TX_FIFO         0x000   //  TX Normal
#define TXB_FIFO        0x080   //  TX Beacon
#define TXGTS1_FIFO     0x100   //
#define TXGTS2_FIFO     0x180   //
#define TX_DATA_SIZE    128
#define RX_FIFO         0x300
#define RX_DATA_SIZE    144

// Short Address Control Register Map
#define RXMCR       0x00    // Receive MAC Control
#define PANIDL      0x01    // PAN ID Low Byte
#define PANIDH      0x02    // PAN ID High Byte
#define SADRL       0x03    // SHORT ADDRESS LOW BYTE REGISTER
#define SADRH       0x04    // SHORT ADDRESS HIGH BYTE REGISTER
#define EADR0       0x05    // EXTENDED ADDRESS 0 REGISTER
#define EADR1       0x06    // EXTENDED ADDRESS 1 REGISTER
#define EADR2       0x07    // EXTENDED ADDRESS 2 REGISTER
#define EADR3       0x08    // EXTENDED ADDRESS 3 REGISTER
#define EARD4       0x09    // EXTENDED ADDRESS 4 REGISTER
#define EADR5       0x0A    // EXTENDED ADDRESS 5 REGISTER
#define EADR6       0x0B    // EXTENDED ADDRESS 6 REGISTER
#define EADR7       0x0C    // EXTENDED ADDRESS 7 REGISTER
#define RXFLUSH     0x0D    // RECEIVE FIFO FLUSH REGISTER
#define ORDER       0x10    // BEACON AND SUPERFRAME ORDER REGISTER
#define TXMCR       0x11    // CSMA-CA MODE CONTROL REGISTER
#define ACKTMOUT    0x12    // MAC ACK TIME-OUT DURATION REGISTER
#define ESLOTG1     0x13    // GTS1 AND CAP END SLOT REGISTER
#define SYMTICKL    0x14    // SYMBOL PERIOD TICK LOW BYTE REGISTER
#define SYMTICKH    0x15    // SYMBOL PERIOD TICK HIGH BYTE REGISTER
#define PACON0      0x16    // POWER AMPLIFIER CONTROL 0 REGISTER
#define PACON1      0x17    // POWER AMPLIFIER CONTROL 1 REGISTER
#define PACON2      0x18    // POWER AMPLIFIER CONTROL 2 REGISTER
#define TXBCON0     0x1A    // TRANSMIT BEACON FIFO CONTROL 0 REGISTER
#define TXNCON      0x1B    // TRANSMIT NORMAL FIFO CONTROL REGISTER
#define TXG1CON     0x1C    // GTS1 FIFOCONTROL REGISTER
#define TXG2CON     0x1D    // GTS2 FIFOCONTROL REGISTER
#define ESLOTG23    0x1E    // END SLOT OF GTS3 AND GTS2 REGISTER
#define ESLOTG45    0x1F    // END SLOT OF GTS5 AND GTS4 REGISTER
#define ESLOTG67    0x20    // END SLOT OF GTS6 REGISTER
#define TXPEND      0x21    // TX DATA PENDING REGISTER
#define WAKEXON     0x22    // WAKE CONTROL REGISTER
#define FRMOFFSET   0x23    // SUPERFRAME COUNTER OFFSET TO ALIGN BEACON REGISTER
#define TXSTAT      0x24    // TX MAC STATUS REGISTER
#define TXBCON1     0x25    // TRANSMIT BEACON CONTROL 1 REGISTER
#define GATECLK     0x26    // GATED CLOCK CONTROL REGISTER
#define TXTIME      0x27    // TX TURNAROUND TIME REGISTER
#define HSYMTMRL    0x28    // HALF SYMBOL TIMER LOW BYTE REGISTER
#define HSYMTMRH    0x29    // HALF SYMBOL TIMER HIGH BYTE REGISTER
#define SOFTRST     0x2A    // SOFTWARE RESET REGISTER
#define SECCON0     0x2C    // SECURITY CONTROL 0 REGISTER
#define SECCON1     0x2D    // SECURITY CONTROL 1 REGISTER
#define TXSTBL      0x2E    // TX STABILIZATION REGISTER
#define RXSR        0x30    // RX MAC STATUS REGISTER
#define INTSTAT     0x31    // INTERRUPT STATUS REGISTER
#define INTCON      0x32    // INTERRUPT CONTROL REGISTER
#define GPIO_PINS   0x33    // GPIO PORT REGISTER
#define TRISGPIO    0x34    // GPIO PIN DIRECTION REGISTER
#define SLPACK      0x35    // SLEEP ACKNOWLEDGEMENT AND WAKE-UP COUNTER REGISTER
#define RFCTL       0x36    // RF MODE CONTROL REGISTER
#define SECCR2      0x37    // SECURITY CONTROL 2 REGISTER
#define BBREG0      0x38    // BASEBAND 0 REGISTER
#define BBREG1      0x39    // BASEBAND 1 REGISTER
#define BBREG2      0x3A    // BASEBAND 2 REGISTER
#define BBREG3      0x3B    // BASEBAND 3 REGISTER
#define BBREG4      0x3C    // BASEBAND 4 REGISTER
#define BBREG6      0x3E    // BASEBAND 6 REGISTER
#define CCAEDTH     0x3F    // ENERGY DETECTION THRESHOLD FOR CCA REGISTER

// Long Address Control Register Map
#define RFCON0      0x200   // RF CONTROL 0 REGISTER
#define RFCON1      0x201   // RF CONTROL 1 REGISTER
#define RFCON2      0x202   // RF CONTROL 2 REGISTER
#define RFCON3      0x203   // RF CONTROL 3 REGISTER
#define RFCON5      0x205   // RF CONTROL 5 REGISTER
#define RFCON6      0x206   // RF CONTROL 6 REGISTER
#define RFCON7      0x207   // RF CONTROL 7 REGISTER
#define RFCON8      0x208   // RF CONTROL 8 REGISTER
#define SLPCAL0     0x209   // SLEEP CALIBRATION 0 REGISTER
#define SLPCAL1     0x20A   // SLEEP CALIBRATION 1 REGISTER
#define SLPCAL2     0x20B   // SLEEP CALIBRATION 2 REGISTER
#define RFSTATE     0x20F   // RF STATE REGISTER
#define RSSI        0x210   // AVERAGED RSSIVALUE REGISTER
#define SLPCON0     0x211   // SLEEP CLOCK CONTROL 0 REGISTER
#define SLPCON1     0x220   // SLEEP CLOCK CONTROL 1 REGISTER
#define WAKETIMEL   0x222   // WAKE-UP TIME MATCH VALUE LOW REGISTER
#define WAKETIMEH   0x223   // WAKE-UP TIME MATCH VALUE HIGH REGISTER
#define REMCNTL     0x224   // REMAIN COUNTER LOW REGISTER
#define REMCNTH     0x225   // REMAIN COUNTER HIGH REGISTER
#define MAINCNT0    0x226   // MAIN COUNTER 0 REGISTER
#define MAINCNT1    0x227   // MAIN COUNTER 1 REGISTER
#define MAINCNT2    0x228   // MAIN COUNTER 2 REGISTER
#define MAINCNT3    0x229   // MAIN COUNTER 3 REGISTER
#define TESTMODE    0x22F   // TEST MODE REGISTER
#define ASSOEADDR0  0x230   // 64-Bit Extended Address of Associated Coordinator regs
#define ASSOEADDR1  0x231
#define ASSOEADDR2  0x232
#define ASSOEADDR3  0x233
#define ASSOEADDR4  0x234
#define ASSOEADDR5  0x235
#define ASSOEADDR6  0x236
#define ASSOEADDR7  0x237
#define ASSOSADDR0  0x238   // 16-Bit Short Address of Associated Coordinator regs
#define ASSOSADDR1  0x239
#define UPNONCE0    0x240   // UPPER NONCE SECURITY 0 REGISTER
#define UPNONCE1    0x241   // UPPER NONCE SECURITY 1 REGISTER
#define UPNONCE2    0x242   // UPPER NONCE SECURITY 2 REGISTER
#define UPNONCE3    0x243   // UPPER NONCE SECURITY 3 REGISTER
#define UPNONCE4    0x244   // UPPER NONCE SECURITY 4 REGISTER
#define UPNONCE5    0x245   // UPPER NONCE SECURITY 5 REGISTER
#define UPNONCE6    0x246   // UPPER NONCE SECURITY 6 REGISTER
#define UPNONCE7    0x247   // UPPER NONCE SECURITY 7 REGISTER
#define UPNONCE8    0x248   // UPPER NONCE SECURITY 8 REGISTER
#define UPNONCE9    0x249   // UPPER NONCE SECURITY 9 REGISTER
#define UPNONCE10   0x24A   // UPPER NONCE SECURITY 10 REGISTER
#define UPNONCE11   0x24B   // UPPER NONCE SECURITY 11 REGISTER
#define UPNONCE12   0x24C   // UPPER NONCE SECURITY 12 REGISTER

// Control Bits Names   *   Type    *   Default * Description
// RXMCR
#define NOACKRSP    5   //  R/W 0   Automatic Acknowledgement Response bit
#define PANCOORD    3   //  R/W 0   PAN Coordinator bit
#define COORD       2   //  R/W 0   Coordinator bit
#define ERRPKT      1   //  R/W 0   Packet Error Mode bit
#define PROMI       0   //  R/W 0   Promiscuous Mode bit

// RXFLUSH
#define WAKEPOL     6   //  R/W 0   Wake Signal Polarity bit
#define WAKEPAD     5   //  R/W 0   Wake I/O Pin Enable bit
#define CMDONLY     3   //  R/W 0   Command Frame Receive bit
#define DATAONLY    2   //  R/W 0   Data Frame Receive bit
#define BCNONLY     1   //  R/W 0   Beacon Frame Receive bit
#define RXFL        0   //  W   0   Reset Receive FIFO Address Pointer bit

// ORDER
#define BO3         7   //  R/W 1   Beacon Order bits (0<=SO<=BO<=14)
#define BO2         6   //  R/W 1   (0x0...0xE)
#define BO1         5   //  R/W 1   0xF - Disable Beacons and SO
#define BO0         4   //  R/W 1
#define SO3         3   //  R/W 1   Superframe Order bits
#define SO2         2   //  R/W 1   (0x0...0xE)
#define SO1         1   //  R/W 1   0xF - Superframe portion is 0
#define SO0         0   //  R/W 1

// TXMCR
#define NOCSMA      7   //  R/W 0   No Carrier Sense Multiple Access (CSMA) Algorithm bits
#define BATLIFEXT   6   //  R/W 0   Battery Life Extension Mode bit
#define SLOTTED     5   //  R/W 0   Slotted CSMA-CA Mode bit
#define MACMINBE1   4   //  R/W 1   MAC Minimum Backoff Exponent bits
#define MACMINBE0   3   //  R/W 1   (collision avoidance)
#define CSMABF2     2   //  R/W 1   CSMA Backoff bits
#define CSMABF1     1   //  R/W 0   (0x0...0x5)
#define CSMABF0     0   //  R/W 0

// ACKTMOUT
#define DRPACK      7   //  R/W 0   Data Request Pending Acknowledgement bit
#define MAWD6       6   //  R/W 0   Wait Duration bits
#define MAWD5       5   //  R/W 1
#define MAWD4       4   //  R/W 1
#define MAWD3       3   //  R/W 1
#define MAWD2       2   //  R/W 0
#define MAWD1       1   //  R/W 0
#define MAWD0       0   //  R/W 1

// ESLOTG1
#define GTS1_3      7   //  R/W 0   EndSlot of 1st GTS bits
#define GTS1_2      6   //  R/W 0
#define GTS1_1      5   //  R/W 0
#define GTS1_0      4   //  R/W 0
#define CAP3        3   //  R/W 0   Contention Access Period (CAP) End Slot bits
#define CAP2        2   //  R/W 0
#define CAP1        1   //  R/W 0
#define CAP0        0   //  R/W 0

// SYMTYCKL
#define TICKP7      7   //  R/W 0   Symbol Period Tick bits
#define TICKP6      6   //  R/W 1   Units: tick (50 ns)
#define TICKP5      5   //  R/W 0   Default value = 0x140 (320 * 50 ns = 16 ?s)
#define TICKP4      4   //  R/W 0
#define TICKP3      3   //  R/W 0
#define TICKP2      2   //  R/W 0
#define TICKP1      1   //  R/W 0
#define TICKP0      0   //  R/W 0

// SYMTYCKH
#define TXONT6      7   //  R/W 0   Transmitter Enable On Time Tick bits
#define TXONT5      6   //  R/W 1   Units: tick (50 ns)
#define TXONT4      5   //  R/W 0   Default value = 0x028 (40 * 50 ns = 2 ?s)
#define TXONT3      4   //  R/W 1
#define TXONT2      3   //  R/W 0
#define TXONT1      2   //  R/W 0
#define TXONT0      1   //  R/W 0
#define TICKP8      0   //  R/W 1   Symbol Period Tick bit

// PACON0
#define PAONT7      7   //  R/W 0   Power Amplifier Enable On Time Tick bits
#define PAONT6      6   //  R/W 0   Units: tick (50 ns)
#define PAONT5      5   //  R/W 1   Default value = 0x029 (41 * 50 ns = 2.05 ?s)
#define PAONT4      4   //  R/W 0
#define PAONT3      3   //  R/W 1
#define PAONT2      2   //  R/W 0
#define PAONT1      1   //  R/W 0
#define PAONT0      0   //  R/W 1

// PACON1
#define PAONTS3     4   //  R/W 0   Power Amplifier Enable On Time Symbol bits
#define PAONTS2     3   //  R/W 0   Units: symbol period (16 ?s)
#define PAONTS1     2   //  R/W 0   Minimum value: 0x1 (default) (1 * 16 ?s = 16 ?s)
#define PAONTS0     1   //  R/W 1
#define PAONT8      0   //  R/W 0   Power Amplifier Enable On Time Tick bits

// PACON2
#define FIFOEND     7   //  R/W 1   FIFO Enable bit
#define TXONTS3     5   //  R/W 0   Transmitter Enable On Time Symbol bits
#define TXONTS2     4   //  R/W 0   Units: symbol period (16 ?s)
#define TXONTS1     3   //  R/W 1   Minimum value: 0x1
#define TXONTS0     2   //  R/W 0   Default value: 0x2 (2 * 16 ?s = 32 ?s)Recommended value: 0x6 (6 * 16 ?s = 96 ?s)
#define TXONT8      1   //  R/W 0   Transmitter Enable On Time Tick bits
#define TXONT7      0   //  R/W 0   Units: tick (50 ns) Default value = 0x028 (40 * 50 ns = 2 ?s)

// TXBCON0
#define TXBSECEN    1   //  R/W 0   TX BeaconFIFO Security Enabled bit
#define TXBTRIG     0   //  W   0   Transmit Frame in TX Beacon FIFO bit

// TXNCON
#define FPSTAT      4   //  R   0   Frame Pending Status bit
#define INDIRECT    3   //  R/W 0   Activate Indirect Transmission bit (coordinator only)
#define TXNACKREQ   2   //  R/W 0   TX Normal FIFO Acknowledgement Request bit
#define TXNSECEN    1   //  R/W 0   TX Normal FIFO Security Enabled bit
#define TXNTRIG     0   //  W   0   Transmit Frame in TX Normal FIFO bit

// TXG1CON
#define TXG1RETRY1  7   //  R/W 0   TX GTS1 FIFO Retry Times bits
#define TXG1RETRY0  6   //  R/W 0   Write: retry times of packet Read: number of retry times of the successfully transmitted packet
#define TXG1SLOT2   5   //  R/W 0   GTS Slot that TX GTS1 FIFO Occupies bits
#define TXG1SLOT1   4   //  R/W 0
#define TXG1SLOT0   3   //  R/W 0
#define TXG1ACKREQ  2   //  R/W 0   TX GTS1 FIFO Acknowledgement Request bit
#define TXG1SECEN   1   //  R/W 0   TX GTS1 FIFO Security Enabled bit
#define TXG1TRIG    0   //  W   0   Transmit Frame in TX GTS1 FIFO bit

// TXG2CON
#define TXG2RETRY1  7   //  R/W 0   TX GTS2 FIFO Retry Times bits
#define TXG2RETRY0  6   //  R/W 0
#define TXG2SLOT2   5   //  R/W 0   GTS Slot that TX GTS2 FIFO Occupies bits
#define TXG2SLOT1   4   //  R/W 0
#define TXG2SLOT0   3   //  R/W 0
#define TXG2ACKREQ  2   //  R/W 0   TX GTS2 FIFO Acknowledgement Request bit
#define TXG2SECEN   1   //  R/W 0   TX GTS2 FIFO Security Enabled bit
#define TXG2TRIG    0   //  W   0   Transmit Frame in TX GTS2 FIFO bit

// ESLOTG23
#define GTS3_3      7   //  R/W 0
#define GTS3_2      6   //  R/W 0
#define GTS3_1      5   //  R/W 0
#define GTS3_0      4   //  R/W 0
#define GTS2_3      3   //  R/W 0
#define GTS2_2      2   //  R/W 0
#define GTS2_1      1   //  R/W 0
#define GTS2_0      0   //  R/W 0

// ESLOTG45
#define GTS5_3      7   //  R/W 0
#define GTS5_2      6   //  R/W 0
#define GTS5_1      5   //  R/W 0
#define GTS5_0      4   //  R/W 0
#define GTS4_3      3   //  R/W 0
#define GTS4_2      2   //  R/W 0
#define GTS4_1      1   //  R/W 0
#define GTS4_0      0   //  R/W 0

// ESLOTG67
#define GTS6_3      3   //  R/W 0
#define GTS6_2      2   //  R/W 0
#define GTS6_1      1   //  R/W 0
#define GTS6_0      0   //  R/W 0

// TXPEND
#define MLIFS5      7   //  R/W 1   Minimum Long Interframe Spacing bits
#define MLIFS4      6   //  R/W 0   MLIFS + RFSTBL = aMinLIFSPeriod= 40 symbols
#define MLIFS3      5   //  R/W 0   Units: symbol period (16 ?s)
#define MLIFS2      4   //  R/W 0   Default value: 0x21
#define MLIFS1      3   //  R/W 0   Recommended values: MLIFS = 0x1F and RFSTBL = 0x9
#define MLIFS0      2   //  R/W 1
#define GTSSWITCH   1   //  R/W 0   Continue TX GTS FIFO Switch in CFP bit
#define FPACK       0   //  R/W 0   Frame Pending bit in the Acknowledgement Frame bit

// WAKECON
#define IMMWAKE     7   //  R/W 0   Immediate Wake-up Mode Enable bit
#define REGWAKE     6   //  R/W 0   Register Wake-up Signal bit
#define INTL        0   //  R/W 0   Interval to Start Beacon (6 bits)

// FRMOFFSET
#define OFFSET7     7   //  R/W 0   Superframe Counter Offset for Align Air Slot Boundary bits
#define OFFSET6     6   //  R/W 0   For Beacon-Enabled mode device
#define OFFSET5     5   //  R/W 0   Default value: 0x00
#define OFFSET4     4   //  R/W 0   Recommended value: 0x15
#define OFFSET3     3   //  R/W 0
#define OFFSET2     2   //  R/W 0
#define OFFSET1     1   //  R/W 0
#define OFFSET0     0   //  R/W 0

// TXSTAT
#define TXNRETRY1   7   //  R   0   TX Normal FIFO Retry Times bits
#define TXNRETRY0   6   //  R   0
#define CCAFAIL     5   //  R   0   Clear Channel Assessment (CCA) Status of Last Transmission bit
#define TXG2FNT     4   //  R   0   TX GTS2 FIFO Transmission failed due to not enough time before the end of GTS bit
#define TXG1FNT     3   //  R   0   TX GTS1 FIFO Transmission failed due to not enough time before the end of GTS bit
#define TXG2STAT    2   //  R   0   TX GTS2 FIFO Release Status bit
#define TXG1STAT    1   //  R   0   TX GTS2 FIFO Release Status bit
#define TXNSTAT     0   //  R   0   TX Normal FIFO Release Status bit

// TXBCON1
#define TXBMSK      7   //  R/W 0   TX Beacon FIFO Interrupt Mask bit
#define WU_BCN      6   //  R   0   Wake-up/Beacon Interrupt Status bit
#define RSSINUM1    5   //  R/W 1   RSSI Average Symbols bits
#define RSSINUM0    4   //  R/W 1   (0b11 - 8, 0b10 - 4, 0b01 - 2, 0b00 - 1)

// GATECLK
#define GTSON       3   //  R/W 0   GTS FIFO Clock Enable bit

// TXTIME
#define TURNTIME3   7   //  R/W 0   Turnaround Time bits
#define TURNTIME2   6   //  R/W 1   Units: symbol period (16 ?s)
#define TURNTIME1   5   //  R/W 0   Default value: 0x4. Minimum value: 0x2
#define TURNTIME0   4   //  R/W 0   Recommended values: TURNTIME = 0x3 and RFSTBL = 0x9

// HSYMTMRL
#define HSYMTMR7    7   //  R/W 0   Half Symbol Timer Low Byte bits
#define HSYMTMR6    6   //  R/W 0
#define HSYMTMR5    5   //  R/W 0
#define HSYMTMR4    4   //  R/W 0
#define HSYMTMR3    3   //  R/W 0
#define HSYMTMR2    2   //  R/W 0
#define HSYMTMR1    1   //  R/W 0
#define HSYMTMR0    0   //  R/W 0

// HSYMTMRH
#define HSYMTMR15   7   //  R/W 0   Half Symbol Timer High Byte bits
#define HSYMTMR14   6   //  R/W 0
#define HSYMTMR13   5   //  R/W 0
#define HSYMTMR12   4   //  R/W 0
#define HSYMTMR11   3   //  R/W 0
#define HSYMTMR10   2   //  R/W 0
#define HSYMTMR9    1   //  R/W 0
#define HSYMTMR8    0   //  R/W 0

// SOFTRST
#define RSTPWR      2   //  W   0   Power Management Reset bit
#define RSTBB       1   //  W   0   Baseband Reset bit
#define RSTMAC      0   //  W   0   MAC Reset bit

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

// SECCON0
#define SECIGNORE   7   //  W   0   RX Security Decryption Ignore bit
#define SECSTART    6   //  W   0   RX Security Decryption Start bit
#define RXCIPHER2   5   //  R/W 0   RX FIFO Security Suite Select bits
#define RXCIPHER1   4   //  R/W 0
#define RXCIPHER0   3   //  R/W 0
#define TXNCIPHER2  2   //  R/W 0   TXNormal FIFO Security Suite Select bits
#define TXNCIPHER1  1   //  R/W 0
#define TXNCIPHER0  0   //  R/W 0

// SECCON1
#define TXBCIPHER2  6   //  R/W 0   TX Beacon FIFO Security Suite Select bits
#define TXBCIPHER1  5   //  R/W 0
#define TXBCIPHER0  4   //  R/W 0
#define DISDEC      1   //  R/W 0   Disable Decryption Function bit
#define DISENC      0   //  R/W 0   Disable Encryption Function bit

// TXSTBL
#define RFSTBL3     7   //  R/W 0   VCO Stabilization Period bits
#define RFSTBL2     6   //  R/W 1   Units: symbol period (16 ?s)
#define RFSTBL1     5   //  R/W 1   Default value: 0x7
#define RFSTBL0     4   //  R/W 1   Recommended value: 0x9
#define MSIF3       3   //  R/W 0   Minimum Short Interframe Spacing bits
#define MSIF2       2   //  R/W 1   MSIFS + RFSTBL = aMinSIFSPeriod= 12 symbols
#define MSIF1       1   //  R/W 0   Units: symbol period (16 ?s)
#define MSIF0       0   //  R/W 1   Default value: 0x5

// RXSR
#define UPSECERR    6   //  R/W 0   MIC Error in Upper Layer Security Mode bit
#define BATIND      5   //  R   0   Battery Low-Voltage Indicator bit
#define SECDECERR   2   //  R   0   Security Decryption Error

// INTSTAT
#define SLPIF       7   //  RC 0    Sleep Alert Interrupt bit
#define WAKEIF      6   //  RC 0    Wake-up Alert Interrupt bit
#define HSYMTMRIF   5   //  RC 0    Half Symbol Timer Interrupt bit
#define SECIF       4   //  RC 0    Security Key Request Interrupt bit
#define RXIF        3   //  RC 0    RX FIFO Reception Interrupt bit
#define TXG2IF      2   //  RC 0    TX GTS2 FIFO Transmission Interrupt bit
#define TXG1IF      1   //  RC 0    TX GTS1 FIFO Transmission Interrupt bit
#define TXNIF       0   //  RC 0    TX Normal FIFO Release Interrupt bit

// INTCON
#define SLPIE       7   //  R/W 1   Sleep Alert Interrupt Enable bit
#define WAKEIE      6   //  R/W 1   Wake-up Alert Interrupt Enable bit
#define HSYMTMRIE   5   //  R/W 1   Half Symbol Timer Interrupt Enable bit
#define SECIE       4   //  R/W 1   Security Key Request Interrupt Enable bit
#define RXIE        3   //  R/W 1   RX FIFO Reception Interrupt Enable bit
#define TXG2IE      2   //  R/W 1   TX GTS2 FIFO Transmission Interrupt Enable bit
#define TXG1IE      1   //  R/W 1   TX GTS1 FIFO Transmission Interrupt Enable bit
#define TXNIE       0   //  R/W 1   TX Normal FIFO Transmission Interrupt Enable bit

// GPIO_PIN
#define GPIO_PIN5   5   //  R/W 0   General Purpose I/O GPIO5 bit
#define GPIO_PIN4   4   //  R/W 0   General Purpose I/O GPIO4 bit
#define GPIO_PIN3   3   //  R/W 0   General Purpose I/O GPIO3 bit
#define GPIO_PIN2   2   //  R/W 0   General Purpose I/O GPIO2 bit
#define GPIO_PIN1   1   //  R/W 0   General Purpose I/O GPIO1 bit
#define GPIO_PIN0   0   //  R/W 0   General Purpose I/O GPIO0 bit

// TRISGPIO
#define TRISGP5     5   //  R/W 0   General Purpose I/O GPIO Direction bits
#define TRISGP4     4   //  R/W 0   1=Output
#define TRISGP3     3   //  R/W 0   0=Input (default)
#define TRISGP2     2   //  R/W 0
#define TRISGP1     1   //  R/W 0
#define TRISGP0     0   //  R/W 0

// SLPACK
#define SLPACK_BIT  7   //  W   0   Sleep Acknowledge bit
#define WAKECNT6    6   //  R/W 0   Wake Count bits
#define WAKECNT5    5   //  R/W 0   Units: Sleep clock (SLPCLK) period
#define WAKECNT4    4   //  R/W 0   Default value: 0x00
#define WAKECNT3    3   //  R/W 0   Recommended value: 0x05F
#define WAKECNT2    2   //  R/W 0
#define WAKECNT1    1   //  R/W 0
#define WAKECNT0    0   //  R/W 0

// RFCTL
#define WAKECNT8    4   //  R/W 0   Wake Count bits
#define WAKECNT7    3   //  R/W 0
#define RFRST       2   //  R/W 0   RF State Machine Reset bit
#define RFTXMODE    1   //  R/W 0   Forces RF Control State Machine to transmit State
#define RFRXMODE    0   //  R/W 0   Forces RF Control State Machine to receive State

// SECCR2
#define UPDEC       7   //  W   0   Upper Layer Security Decryption Mode bit
#define UPENC       6   //  W   0   Upper Layer Security Encryption Mode bit
#define TXG2CIPHER2 5   //  R/W 0   TX GTS2 FIFO Security Suite Select bits
#define TXG2CIPHER1 4   //  R/W 0
#define TXG2CIPHER0 3   //  R/W 0
#define TXG1CIPHER2 2   //  R/W 0   TX GTS1 FIFO Security Suite Select bits
#define TXG1CIPHER1 1   //  R/W 0
#define TXG1CIPHER0 0   //  R/W 0

// BBREG0
#define TURBO       0   //  R/W 0   Turbo Mode Enable bit (625 kbps)

// BBREG1
#define RXDECINV    2   //  R/W 0   RX Decode Inversion bit

// BBREG2
#define CCAMODE1    7   //  R/W 0   Clear Channel Assessment (CCA) Mode bits
#define CCAMODE0    6   //  R/W 1
#define CCACSTH3    5   //  R/W 0
//11= CCA Mode 3: Carrier sense with energy above threshold. CCA shall report a busy medium only
//upon the detection of a signal with the modulation and spreading characteristics of IEEE 802.15.4?
//with energy above the Energy Detection (ED) threshold.
//10= CCA Mode 1: Energy above threshold. CCA shall report a busy medium upon detecting any
//energy above the Energy Detection (ED) threshold.
//01= CCA Mode 2: Carrier sense only. CCA shall report a busy medium only upon the detection of a
//signal with the modulation and spreading characteristics of IEEE 802.15.4. This signal may be
//above or below the Energy Detection (ED) threshold (default).
//00= Reserved
#define CCACSTH2    4   //  R/W 0   Clear Channel Assessment (CCA) Carrier Sense (CS) Threshold bits
#define CCACSTH1    3   //  R/W 1   1110= Recommended value
#define CCACSTH0    2   //  R/W 0   0010= (default)

// BBREG3
#define PREVALIDTH3 7   //  R/W 1   Preamble Search Energy Valid Threshold bits
#define PREVALIDTH2 6   //  R/W 1   1101 = IEEE 802.15.4? (250 kbps) optimized value (default)
#define PREVALIDTH1 5   //  R/W 0   0011= Turbo mode (625 kbps) optimized value
#define PREVALIDTH0 4   //  R/W 1
#define PREDETTH2   3   //  R/W 1   Preamble Search Energy Detection Threshold bits
#define PREDETTH1   2   //  R/W 0   Default value: 0x4
#define PREDETTH0   1   //  R/W 0

// BBREG4
#define CSTH2       7   //  R/W 1
#define CSTH1       6   //  R/W 0
#define CSTH0       5   //  R/W 0
#define PRECNT2     4   //  R/W 1
#define PRECNT1     3   //  R/W 1
#define PRECNT0     2   //  R/W 1

// BBREG6
#define RSSIMODE1   7   //  W   0   RSSI Mode 1 bit (1= Initiate RSSI calculation)
#define RSSIMODE2   6   //  R/W 0   RSSI Mode 2 bit
#define RSSIRDY     0   //  R   1   RSSI Ready Signal for RSSIMODE1 bit

// CCAEDTH
#define CCAEDTH7    7   //  R/W 0   Clear Channel Assessment (CCA) Energy Detection (ED) Mode bits
#define CCAEDTH6    6   //  R/W 0   Default value: 0x00
#define CCAEDTH5    5   //  R/W 0   Recommended value: 0x60 (approximately -69 dBm)
#define CCAEDTH4    4   //  R/W 0
#define CCAEDTH3    3   //  R/W 0
#define CCAEDTH2    2   //  R/W 0
#define CCAEDTH1    1   //  R/W 0
#define CCAEDTH0    0   //  R/W 0

// RFCON0
#define CHANNEL3    7   //  R/W 0   Channel Number bits
#define CHANNEL2    6   //  R/W 0   0000 = Channel 11 (2405 MHz) (default)
#define CHANNEL1    5   //  R/W 0   0001=Channel 12 (2410 MHz)...
#define CHANNEL0    4   //  R/W 0   ... 1111=Channel 26 (2480 MHz)
#define RFOPT3      3   //  R/W 0   RFOptimize Control bits
#define RFOPT2      2   //  R/W 0   Default value: 0x0
#define RFOPT1      1   //  R/W 0   Recommended value: 0x3
#define RFOPT0      0   //  R/W 0

// RFCON1
#define VCOOPT7     7   //  R/W 0   VCO Optimize Control bits
#define VCOOPT6     6   //  R/W 0   Default value: 0x0
#define VCOOPT5     5   //  R/W 0   Recommended value: 0x2
#define VCOOPT4     4   //  R/W 0
#define VCOOPT3     3   //  R/W 0
#define VCOOPT2     2   //  R/W 0
#define VCOOPT1     1   //  R/W 0
#define VCOOPT0     0   //  R/W 0

// RFCON2
#define PLLEN       7   //  R/W 0   PLL Enable bit

// RFCON3
#define TXPWRL1     7   //  R/W 0   LargeScale Control for TX Power bits
#define TXPWRL0     6   //  R/W 0
//11= -30 dB
//10= -20 dB
//01= -10 dB
//00= 0 dB
#define TXPWRS2     5   //  R/W 0   Small ScaleControl for TX Power bits
#define TXPWRS1     4   //  R/W 0
#define TXPWRS0     3   //  R/W 0
//111=-6.3 dB
//110=-4.9 dB
//101=-3.7 dB
//100=-2.8 dB
//011=-1.9 dB
//010=-1.2 dB
//001=-0.5 dB
//000 = 0 dB

// RFCON5
#define BATTH3      7   //  R/W 0   Battery Low-Voltage Threshold bits
#define BATTH2      6   //  R/W 0
#define BATTH1      5   //  R/W 0
#define BATTH0      4   //  R/W 0
//1110= 3.5V
//1101= 3.3V
//1100= 3.2V
//1011= 3.1V
//1010= 2.8V
//1001= 2.7V
//1000= 2.6V
//0111= 2.5V
//0110=Undefined
//...
//0000=Undefined

// RFCON6
#define TXFIL       7   //  R/W 0   TX Filter Control bit
#define _20MRECVR   4   //  R/W 0   20 MHz Clock Recovery Control bits
#define BATEN       3   //  R/W 0   Battery Monitor Enable bit

// RFCON7
#define SLPCLKSEL1  7   //  R/W 0   Sleep Clock Selection bits
#define SLPCLKSEL0  6   //  R/W 0   10= 100 kHz internal oscillator
                        //          01= 32kHz external crystal oscillator
#define CLKOUTMODE1 1   //  R/W 0
#define CLKOUTMODE0 0   //  R/W 0

// RFCON8
#define RFVCO       4   //  R/W 0   VCO Control bit

// SLPCAL0
#define _SLPCAL7    7   //  R   0   Sleep Calibration Counter bits
#define _SLPCAL6    6   //  R   0
#define _SLPCAL5    5   //  R   0
#define _SLPCAL4    4   //  R   0
#define _SLPCAL3    3   //  R   0
#define _SLPCAL2    2   //  R   0
#define _SLPCAL1    1   //  R   0
#define _SLPCAL0    0   //  R   0

// SLPCAL1
#define _SLPCAL15   7   //  R   0   Sleep Calibration Counter bits
#define _SLPCAL14   6   //  R   0   Units: tick (50 ns)
#define _SLPCAL13   5   //  R   0
#define _SLPCAL12   4   //  R   0
#define _SLPCAL11   3   //  R   0
#define _SLPCAL10   2   //  R   0
#define _SLPCAL9    1   //  R   0
#define _SLPCAL8    0   //  R   0

// SLPCAL2
#define SLPCALRDY   7   //  R   0   Sleep Calibration Ready bit
#define SLPCALEN    4   //  W   0   Sleep Calibration Enable bit
#define _SLPCAL19   3   //  R   0   Sleep Calibration Counter bits
#define _SLPCAL18   2   //  R   0
#define _SLPCAL17   1   //  R   0
#define _SLPCAL16   0   //  R   0

// RFSTATE
#define RFSTATE2    7   //  R   0   RF State Machine bits
#define RFSTATE1    6   //  R   0
#define RFSTATE0    5   //  R   0
//111= RTSEL2
//110= RTSEL1
//101= RX
//100= TX
//011= CALVCO
//010= SLEEP
//001= CALFIL
//000= RESET


// RSSI
#define RSSI7       7   //  R/W 0   Averaged RSSI Value bits
#define RSSI6       6   //  R/W 0
#define RSSI5       5   //  R/W 0
#define RSSI4       4   //  R/W 0
#define RSSI3       3   //  R/W 0
#define RSSI2       2   //  R/W 0
#define RSSI1       1   //  R/W 0
#define RSSI0       0   //  R/W 0

// SLPCON0
#define INTEDGE     1   //  R/W 0   Interrupt Edge Polarity bit
#define SLPCLKEN    0   //  R/W 0   Sleep Clock Enable bit

// SLPCON1
#define CLKOUTEN    5   //  R/W 0   CLKOUT Pin Enable bit
#define SLPCLKDIV4  4   //  R/W 0   Sleep Clock Divisor bits
#define SLPCLKDIV3  3   //  R/W 0   Sleep clock is divided by 2^n
#define SLPCLKDIV2  2   //  R/W 0   n = SLPCLKDIV
#define SLPCLKDIV1  1   //  R/W 0   Default value: 0x00
#define SLPCLKDIV0  0   //  R/W 0

// WAKETIMEL
#define WAKETIME7   7   //  R/W 0   Wake Time Match Value bits
#define WAKETIME6   6   //  R/W 0   Default value: 0x00A
#define WAKETIME5   5   //  R/W 0   Minimum value: 0x001
#define WAKETIME4   4   //  R/W 0
#define WAKETIME3   3   //  R/W 1
#define WAKETIME2   2   //  R/W 0
#define WAKETIME1   1   //  R/W 1
#define WAKETIME0   0   //  R/W 0

// WAKETIMEH
#define WAKETIME10  2   //  R/W 0   Wake-up Time Counted by SLPCLK bits
#define WAKETIME9   1   //  R/W 0   Rule: WAKETIME > WAKECNT
#define WAKETIME8   0   //  R/W 0

// REMCNTL
#define REMCNT7     7   //  R/W 0   Remain Counter bits
#define REMCNT6     6   //  R/W 0   Units: tick (50 ns)
#define REMCNT5     5   //  R/W 0
#define REMCNT4     4   //  R/W 0
#define REMCNT3     3   //  R/W 0
#define REMCNT2     2   //  R/W 0
#define REMCNT1     1   //  R/W 0
#define REMCNT0     0   //  R/W 0

// REMCNTH
#define REMCNT15    7   //  R/W 0   Remain Counter bits
#define REMCNT14    6   //  R/W 0
#define REMCNT13    5   //  R/W 0
#define REMCNT12    4   //  R/W 0
#define REMCNT11    3   //  R/W 0
#define REMCNT10    2   //  R/W 0
#define REMCNT9     1   //  R/W 0
#define REMCNT8     0   //  R/W 0

// MAINCNT0
#define _MAINCNT7   7   //  R/W 0   MainCounter bits
#define _MAINCNT6   6   //  R/W 0   Units: SLPCLK
#define _MAINCNT5   5   //  R/W 0
#define _MAINCNT4   4   //  R/W 0
#define _MAINCNT3   3   //  R/W 0
#define _MAINCNT2   2   //  R/W 0
#define _MAINCNT1   1   //  R/W 0
#define _MAINCNT0   0   //  R/W 0

// MAINCNT1
#define _MAINCNT15  7   //  R/W 0   MainCounter bits
#define _MAINCNT14  6   //  R/W 0
#define _MAINCNT13  5   //  R/W 0
#define _MAINCNT12  4   //  R/W 0
#define _MAINCNT11  3   //  R/W 0
#define _MAINCNT10  2   //  R/W 0
#define _MAINCNT9   1   //  R/W 0
#define _MAINCNT8   0   //  R/W 0

// MAINCNT2
#define _MAINCNT23  7   //  R/W 0   MainCounter bits
#define _MAINCNT22  6   //  R/W 0
#define _MAINCNT21  5   //  R/W 0
#define _MAINCNT20  4   //  R/W 0
#define _MAINCNT19  3   //  R/W 0
#define _MAINCNT18  2   //  R/W 0
#define _MAINCNT17  1   //  R/W 0
#define _MAINCNT16  0   //  R/W 0

// MAINCNT3
#define STARTCNT    7   //  R/W 0   Start Sleep Mode Counters bits
#define _MAINCNT25  1   //  R/W 0   MainCounter bits
#define _MAINCNT24  0   //  R/W 0

// TESTMODE
#define RSSIWAIT1   4   //  R/W 0   RSSI State Machine Parameter bits
#define RSSIWAIT0   3   //  R/W 0   01= Optimized value (default)
#define TESTMODE2   2   //  R/W 0   Test Mode bits
#define TESTMODE1   1   //  R/W 0   111= GPIO0, GPIO1 andGPIO2 are configured to control an external PA and/or LNA
#define TESTMODE0   0   //  R/W 0   101= Single Tone Test mode, 000= Normaloperation (default)
/******************************************************
 *  Channels    RFCON0 <7>:<4>
 ******************************************************/
#define Ch11        0x00
#define Ch12        0x10
#define Ch13        0x20
#define Ch14        0x30
#define Ch15        0x40
#define Ch16        0x50
#define Ch17        0x60
#define Ch18        0x70
#define Ch19        0x80
#define Ch20        0x90
#define Ch21        0xA0
#define Ch22        0xB0
#define Ch23        0xC0
#define Ch24        0xD0
#define Ch25        0xE0
#define Ch26        0xF0
 /******************************************************
 *  CCA Modes
 ******************************************************/
#define CCA_MODE_1  0x00
#define CCA_MODE_2  0x01
#define CCA_MODE_3  0x02

/******************************************************
 *  Special Macro
 ******************************************************/
#define LO_16(x) (x&0xFF)
#define HI_16(x) (x>>8)

#define ALL 0xFF
// Address and command conversion
#define SHORT_ADDRESS   0b01111111  //  MASK!
#define SHORT_READ      0b00000001
#define SHORT_WRITE     0b11111110  // MASK!
#define LONG_ADDRESS    0b100000000000
#define LONG_READ       0b000000000001
#define LONG_WRITE      0b111111111110  // MASK!
#define ADDR_TO_SHORTCOM(x, y) (y?(((x<<1)/*&SHORT_ADDRESS*/)|SHORT_READ):(((x<<1)&SHORT_ADDRESS)&SHORT_WRITE))
#define ADDR_TO_LONGCOM(x, y) (y?(((x<<1)&LONG_ADDRESS)|LONG_READ):(((x<<1)|LONG_ADDRESS/*&LONG_WRITE*/)))
#define WRITE 0
#define READ  1
/******************************************************
 *  Global Variables
 ******************************************************/
    uint8_t aTurnaroundTime=    12;
    uint8_t aMinLIFSPeriod=     40;
    uint8_t aMinSIFSPeriod=     12;
    uint8_t BEACON_EN= 1;
    uint8_t RF_OPTIMISE= 0x03; // 0 to 7
/******************************************************
 *  Function Defenitions
 ******************************************************/
    
    // SPI R\W prothocol
    // Short address
    void addrWriteSA(uint8_t, uint8_t);
    uint8_t byteReadSA(spiDevice_t *, uint8_t);
    void byteWriteSA(spiDevice_t *, uint8_t, uint8_t);
    void bitWriteSA(spiDevice_t *, uint8_t, uint8_t, bool);
    void dataReadSA(spiDevice_t *, uint8_t, uint8_t *, uint8_t);
    void dataWriteSA(spiDevice_t *, uint8_t, uint8_t *, uint8_t);
    // Long Address
    void addrWriteLA(uint16_t, uint8_t);
    uint8_t byteReadLA(spiDevice_t *, uint16_t);
    void byteWriteLA(spiDevice_t *, uint16_t, uint8_t);
    void bitWriteLA(spiDevice_t *, uint16_t, uint8_t, bool);
    void dataReadLA(spiDevice_t *, uint16_t, uint8_t *, uint8_t);
    void dataWriteLA(spiDevice_t *, uint16_t, uint8_t *, uint8_t);

    // mac-level functions
    void macBeaconOrder(uint8_t);
    void macSuperframeOrder(uint8_t);
    void macMinBE(uint8_t);
    void macMaxCSMABackoff(uint8_t);
    void macAckWaitDuration(uint8_t);
    void setCCAThreshold(MRF24J40_t *, uint8_t);
    void setCCAMode(MRF24J40_t *, uint8_t, uint8_t, uint8_t);
    void promiscEnable();
    void promiscDisable();
    // device control functions
    void deviceReset(MRF24J40_t *);
    void resetPower(MRF24J40_t *);
    void resetBBand(MRF24J40_t *);
    void resetMAC(MRF24J40_t *);
    void deviceSoftReset(MRF24J40_t *);
    void resetRFStateMashine(MRF24J40_t *);

    void deviceStart(MRF24J40_t *, uint8_t);
    void deviceInit(MRF24J40_t *, uint8_t);

    void deviceSleep(MRF24J40_t *);
    void setSleepClock(uint8_t);
    void setWakeTime(uint8_t);
    void startSleepCalibration();

    void deviceIntEnable(MRF24J40_t *);
    void deviceIntPolarity(MRF24J40_t *);
    void deviceSetInterrupt(MRF24J40_t *, uint8_t);
    uint8_t deviceCheckInterrupts(MRF24J40_t *);

    void deviceChannelSelect(MRF24J40_t *, uint8_t);
    void clearChannelAssesstment(uint8_t);

    void setRSSIMode(MRF24J40_t *, uint8_t, bool);
    uint8_t readRSSI(MRF24J40_t *);
    int8_t RSSItoDBM(uint8_t);

    void deviceSetAddress(uint32_t, uint32_t);
    void deviceSetShortAddress(uint8_t);

    void setBattThreshold(uint8_t);
    void battLifeExt();
    void noBattLifeExt();
    void batMonEnable();
    void batMonDisable();

    void setSecurityChipher(uint8_t);
    void deviceEncription();
    void deviceNoEncription();

    uint8_t readRFState();
    void setSmallScaleTXPower(uint8_t);
    void setLargeScaleTXPower(uint8_t);

#ifdef	__cplusplus
}
#endif

#endif	/* MRF24J40_H */