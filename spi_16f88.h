/* 
 * File:   spi.h
 * Author: Disgust
 *
 * Created on 9 ???? 2015 ?., 22:29
 */

#ifndef SPI_16F88_H
#define	SPI_16F88_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

#define SPI_PORT            PORTB

#define SDI_DDR             TRISB1
#define SDO_DDR             TRISB2
#define SCK_DDR             TRISB4

#define PIN_OUTPUT          0
#define PIN_INPUT           1


#define SDI_PIN             PORTBbits.RB1
#define SDO_PIN             PORTBbits.RB2
#define SCK_PIN             PORTBbits.RB4

#define SS_PIN              PORTBbits.RB5

#define SPI_BUFFER          SSPBUF
#define SPI_BUFFER_EMPTY    SSPSTATbits.BF

#define SPI_ENABLE          SSPCONbits.SSPEN
#define SPI_MODE            SSPCONbits.SSPM0 // See modes in <spi.h>
#define SPI_PHASE           SSPSTATbits.SMP
#define SPI_CLOCK_EDGE      SSPSTATbits.CKE

#ifdef	__cplusplus
}
#endif

#endif	/* SPI_16F88_H */

