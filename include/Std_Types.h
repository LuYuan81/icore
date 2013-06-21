/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <Std_Types.h>
 *  @brief      <>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-14>
 */
/*============================================================================*/
#ifndef  STD_TYPES_H	
#define  STD_TYPES_H

/*=======[I N C L U D E S]====================================================*/
#include "Compiler.h"
#include "Platform_Types.h"

/*=======[M A C R O S]========================================================*/
#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  #define E_OK    				0x00
  typedef unsigned char StatusType;  
#endif

#define E_NOT_OK    			0x01

#define E_NO_DTC_AVAILABLE		2
#define E_SESSION_NOT_ALLOWED	4
#define E_PROTOCOL_NOT_ALLOWED	5
#define E_REQUEST_NOT_ACCEPTED	8
#define E_REQUEST_ENV_NOK		9
#define E_PENDING				10
#define E_COMPARE_KEY_FAILED	11
#define E_FORCE_RCRRP			12
#define STD_HIGH 				0x01 
#define STD_LOW 				0x00 
#define STD_ACTIVE 				0x01 
#define STD_IDLE   				0x00 
#define STD_ON    				0x01 
#define STD_OFF   				0x00

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef uint8 Std_ReturnType;
typedef uint16 u16;

typedef struct
{
	uint16 vendorID;
	uint16 moduleID;
	uint8  instanceID;
	uint8  sw_major_version;
	uint8  sw_minor_version;
	uint8  sw_patch_version;
} Std_VersionInfoType;

#endif  

 /*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/

