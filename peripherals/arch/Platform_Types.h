/*===========================================================================
        Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.

        All rights reserved. This software is iSOFT property. Duplication 
        or disclosure without iSOFT written authorization is prohibited.

 ===========================================================================*/

#ifndef  PLATFORM_TYPES_H			// XXX means file name
#define  PLATFORM_TYPES_H

/*==========================================================================*/
/*		I N C L U D E S														*/
/*==========================================================================*/

//#include "headfile.h"

/*==========================================================================*/
/*      G L O B A L   D A T A   D E C L A R A T I O N S                     */
/*==========================================================================*/

/*==========================================================================*/
/*
	ITEM NAME:		<item name>
	SCOPE:			<APPLICATION/COMPONENT/PACKAGE>
	DESCRIPTION:
		Describe the purpose of this item.

	DEFINITION:
*/
//extern DATA_TYPE MEM_TYPE	<item name>;	
								// 1.) Add SPACE after DATA_TYPE.
								// 2.) Add TAB after MEM_TYPE.
								// 3.) DATA_TYPE could be Bool/Byte/Word/Dword
								// 4.) MEM_TYPE could be DATA/IDATA/XDATA/RDATA

/*==========================================================================*/
																			
/*==========================================================================*/
/*      G L O B A L   M A C R O   D E F I N I T I O N S                     */
/*==========================================================================*/

/*MPF=======================================================================*/
/*
    General:

    MACRO NAME:		<CPU_TYPE_8, CPU_TYPE_16, CPU_TYPE_32, MSB_FIRST, LSB_FIRST
    					  HIGH_BYTE_FIRST, LOW_BYTE_FIRST>
    COMPONENT:      	<Platform_Types>
    SCOPE:			<COMPONENT>
    DESCRIPTION:
		These macros define the general type definitions of symbols for all platforms 
*/

#define CPU_TYPE_8		8
#define CPU_TYPE_16		16
#define CPU_TYPE_32		32

#define MSB_FIRST		0
#define LSB_FIRST		1

#define HIGH_BYTE_FIRST	0
#define LOW_BYTE_FIRST	1
							/*	MPC563xM Specificable PlatForm	 */
/*
    Symbols:
    
    MACRO NAME:		<CPU_TYPE>
    COMPONENT:      	<Platform_Types>
    SCOPE:			<COMPONENT>
    DESCRIPTION:
		This macro defines the CPU_TYPE which indicated
		the register width of the CPU
*/
#define CPU_TYPE	CPU_TYPE_8



/*
    MACRO NAME:		<CPU_BIT_ORDER, CPU_BYTE_ORDER>
    DESCRIPTION:
		These macros define the endian
*/
#define CPU_BIT_ORDER	MSB_FIRST
#define CPU_BYTE_ORDER	HIGH_BYTE_FIRST



/*
    Types:
    
    MACRO NAME:		<boolean>
    DESCRIPTION:
		This macro defines the boolean data type 
*/
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

#ifndef FALSE
  #define FALSE		0
#endif

#ifndef TRUE
  #define TRUE		1
#endif

/* James, NULL_PTR is defined in complier.h and recommended */
#ifndef NULL
  #define NULL                   ((void *) 0)
#endif

/* James move the header here to exclude all inclusions from driver implementation */
/* mutongxin change here */
#define MPC5634m_MCU   

#ifdef MPC5633m_MCU
  #include "MPC5633M.h"
  #include "MPC5633M_HWInit.h"
#endif

#ifdef MPC5634m_MCU
  #include "MPC5634M_MLQB80.h"
  #include "MPC5634M_MLQB80_HWInit.h"
#endif

#endif

/*==========================================================================*/
/*		E N D   O F   F I L E												*/
/*==========================================================================*/


