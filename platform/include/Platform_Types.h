/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <Platform_Types.h>
 *  @brief      <>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-14>
 */
/*============================================================================*/

#ifndef  PLATFORM_TYPES_H			
#define  PLATFORM_TYPES_H

/*=======[I N C L U D E S]====================================================*/
#include "derivative.h"

/*=======[M A C R O S]========================================================*/
#define CPU_TYPE_8		8
#define CPU_TYPE_16		16
#define CPU_TYPE_32		32

#define MSB_FIRST		0
#define LSB_FIRST		1

#define HIGH_BYTE_FIRST	0
#define LOW_BYTE_FIRST	1
					
#define CPU_TYPE	CPU_TYPE_16

#define CPU_BIT_ORDER	MSB_FIRST
#define CPU_BYTE_ORDER	HIGH_BYTE_FIRST

#ifndef FALSE
  #define FALSE		0
#endif

#ifndef TRUE
  #define TRUE		1
#endif

#ifndef NULL
  #define NULL  ((void *) 0)
#endif

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef unsigned char           boolean;

typedef signed char             sint8;
typedef unsigned char           uint8;
typedef signed short            sint16;
typedef unsigned short          uint16;
typedef signed long             sint32;
typedef unsigned long           uint32;
typedef unsigned long long      uint64;

typedef unsigned long           uint8_least;
typedef unsigned long           uint16_least;
typedef unsigned long           uint32_least;
typedef signed long             sint8_least;
typedef signed long             sint16_least;
typedef signed long             sint32_least;

typedef float                   float32;
typedef double                  float64;

typedef union uREG08    /*8 bit register with byte and bit access*/
{
	uint8  by;           /*access whole register e.g. var.byte   = 0xFF;*/
	struct                /*access bit at a time  e.g. var.bit._7 = 1;   */
	{
		uint8 _0 :1;
		uint8 _1 :1;
		uint8 _2 :1;
		uint8 _3 :1;
		uint8 _4 :1;
		uint8 _5 :1;
		uint8 _6 :1;
		uint8 _7 :1;  
	}bit;
}tREG08;

typedef union uREG16    /*16 bit register with word and byte access*/
{
	uint16  wo;           /*access whole word    */
	struct                /*access byte at a time*/
	{
		uint8  msb;
		uint8  lsb;
	}by;
}tREG16;

/* Carrier of 8 bits */
typedef struct 
{
	uint8	bit0:1;
	uint8	bit1:1;
	uint8	bit2:1;
	uint8	bit3:1;
	uint8	bit4:1;
	uint8	bit5:1;
	uint16	bit6:1;
	uint8	bit7:1;
}T_BITFLD8;
/* Carrier of 8 bits with byte */
typedef union 
{
	T_BITFLD8 bi;
	uint8 by;
}Flag8_Type;

#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/