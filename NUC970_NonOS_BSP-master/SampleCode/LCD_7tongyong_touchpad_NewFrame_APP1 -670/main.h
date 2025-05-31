#ifndef _MAIN_H
#define _MAIN_H

#include "nuc970.h"
#include "sys.h"
#include "lcd.h"
#include "gpio.h"
#include "i2c.h"

#include "io.h"
#include "pcf8563.h"

#include "spi.h"
#include "uart.h"
#include "etimer.h"
#include "sdh.h"
#include "mtp.h"



typedef double                Flo64;    // Double precision floating point
typedef double              * pFlo64;
typedef float                 Flo32;    // Single precision floating point
typedef float               * pFlo32;
typedef signed   long long    Int64S;   // Signed   64 bit quantity
typedef signed   long long  * pInt64S;
typedef unsigned long long    Int64U;   // Unsigned 64 bit quantity
typedef unsigned long long  * pInt64U;
typedef signed   int          Int32S;   // Signed   32 bit quantity
typedef signed   int        * pInt32S;
typedef unsigned int          Int32U;   // Unsigned 32 bit quantity
typedef unsigned int        * pInt32U;
typedef signed   short        Int16S;   // Signed   16 bit quantity
typedef signed   short      * pInt16S;
typedef unsigned short        Int16U;   // Unsigned 16 bit quantity
typedef unsigned short      * pInt16U;
typedef signed   char         Int8S;    // Signed    8 bit quantity
typedef signed   char       * pInt8S;
typedef unsigned char         Int8U;    // Unsigned  8 bit quantity
typedef unsigned char       * pInt8U;
typedef unsigned int          Boolean;  // Boolean
typedef unsigned int        * pBoolean;

#include "bmp.h"
#include "servo.h"
#include "word_lib.h"
#include "timer.h"
#include "pic.h"

extern Int32U uFlashID;

#endif

