/*
 * Defines.h
 *
 * Created: 4/25/2014 10:17:40 PM
 *  Author: Peter
 */ 


#ifndef MACRO_H_
#define MACRO_H_

#include <stdint.h>
///Macros///

#define bitSet(x,y) (x|=(1<<y))
#define bitClear(x,y) (x&=~(1<<y))
#define bitRead(x,y) (((x)>>(y))&0x01)
#define bitTgl(x,y) (x^=(1<<y))
#define bitWrite(x,y,z) ((z)?(BIT_set(x,y)):(BIT_clear(x,y)))
#define regSet8()
#define regSet16()
#define regSet32()
#define regGet()

#define HI(x) (x>>8)
#define LO(x) (x^0xFF)
#define BIT(x)	(x&0x01)

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MAP(x,in_min,in_max,out_min,out_max) ((x-in_min)*(out_max-out_min)/(in_max-in_min)+out_min)
#define CONSTRAIN(x, a, b) ((x)<(a)?(a):((x)>(b)?(b):(x)))
#define CIRCLE(amt, low, high) ((amt)<(low)?(high):((amt)>(high)?(low):(amt)))
#define ROUND(x) ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

#define DEC_TO_ASCII(x)	(x+0x30)
#define HEX_TO_ASCII(x)	((x<0x0F)?(DEC_TO_ASCII(x)):(x+0x37))

// constants
#define PI		(float)3.14159265359

#ifdef DSP_             
#define PI		3.1415926535897932384626433832795
#define HALF_PI		1.5707963267948966192313216916398
#define E               2.7182818284590452353602874713526
#endif

// Platform dependent
#ifdef __XC8

#elif defined IO_H
 #define DDR(x) ((x)-1)    // address of data direction register of port x
 #define PIN(x) ((x)-2)    // address of input register of port x
#endif

#endif /* MACRO_H_ */