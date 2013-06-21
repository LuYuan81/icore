/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <ComStack_Types.h>
 *  @brief      <>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-14>
 */
/*============================================================================*/

#ifndef  COMSTACK_TYPES_H		
#define  COMSTACK_TYPES_H

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"

/*=======[M A C R O S]========================================================*/
#define  AUTOSAR_COMSTACKDATA
#define	NTFRSLT_OK                    	0x00
#define	NTFRSLT_E_NOT_OK              	0x01
#define	NTFRSLT_E_TIMEOUT_A           	0x02
#define	NTFRSLT_E_TIMEOUT_BS          	0x03
#define	NTFRSLT_E_TIMEOUT_CR          	0x04
#define	NTFRSLT_E_WRONG_SN            	0x05
#define	NTFRSLT_E_INVALID_FS          	0x06
#define	NTFRSLT_E_UNEXP_PDU           	0x07
#define	NTFRSLT_E_WFT_OVRN            	0x08
#define	NTFRSLT_E_NO_BUFFER           	0x09
#define	NTFRSLT_E_CANCELATION_OK      	0x0A
#define	NTFRSLT_E_CANCELATION_NOT_OK  	0x0B

#define	BUSTRCV_OK      			   	0x00
#define	BUSTRCV_E_ERROR 			   	0x01

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef uint16 PduIdType;
typedef uint16 PduLengthType;

typedef struct
{
	P2VAR(uint8,AUTOMATIC,AUTOSAR_COMSTACKDATA) SduDataPtr;
	PduLengthType   SduLength;
} PduInfoType;

typedef enum
{
	BUFREQ_OK = 0,
	BUFREQ_E_NOT_OK,
	BUFREQ_E_BUSY,
	BUFREQ_E_OVFL
} BufReq_ReturnType;

typedef uint8 NotifResultType;
typedef uint8 BusTrcvErrorType;
typedef uint8 NetworkHandleType;

#endif 

 /*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/

