/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <filename>
 *  @brief      <Briefly describe file(one line)>
 *  
 *  <Compiler: XXX    MCU:XXX>
 *  
 *  @author     <author name>
 *  @date       <yyyy-mm-dd>
 */
/*============================================================================*/


/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20130427  James       Initial version
 */
/*============================================================================*/

/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#ifndef SCI_H_
#define SCI_H_

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
#include "Std_ExtTypes.h"
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "Mcu.h"

/*=======[M A C R O S]========================================================*/
#define CR_as_CRLF  TRUE

#define SCI_VERSION_INFO_API  STD_OFF

#define		SCI_TEN    (10)

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef  short	int16;
typedef  long	  int32;
typedef char *va_list_try;

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/*===========================================================================*/
/* Function Name        :Sci_Init                                            */
/* Service ID           :None                                                */
/* Description          :Initializes the module.                             */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :None                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
extern void Sci_Init(void);  

/*===========================================================================*/
/* Function Name        :Sci_SetBaudRate                                     */
/* Service ID           :None                                                */
/* Description          :Set the Sci Driver's BaudRate                       */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :Channel, BaudRate                                   */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
extern void Sci_SetBaudRate(uint8 Channel, uint32 BaudRate);  

/*===========================================================================*/
/* Function Name        :Sci_WriteChar                                       */
/* Service ID           :None                                                */
/* Description          :Write the uint8 data to the Sci port                */
/* Sync/Async           :None                                                */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :Ch                                                  */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
extern void Sci_WriteChar(uint8 ch);  

/*===========================================================================*/
/* Function Name        :Sci_WriteInt16                                      */
/* Service ID           :None                                                */
/* Description          :Write the uint16 data to the Sci port               */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :val                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
extern void Sci_WriteInt16(int16 val); 

/*===========================================================================*/
/* Function Name        :Sci_WriteUint32                                     */
/* Service ID           :None                                                */
/* Description          :Write the uint32 data to the Sci port               */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :val                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
extern void Sci_WriteInt32(int32 val);

/*===========================================================================*/
/* Function Name        :Sci_WriteString                                     */
/* Service ID           :None                                                */
/* Description          :Write the string data to the Sci port               */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :val                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/							
extern void Sci_WriteString(uint8 *szString);

/*===========================================================================*/
/* Function Name        :Sci_ReadByte                                        */
/* Service ID           :None                                                */
/* Description          :Read the byte data to the Sci port                  */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :val                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#if (SCI_VERSION_INFO_API == STD_ON )
extern void Sci_ReadByte(uint8 bytedata); 
#endif 


#endif/* end WDG_H_ */

/*=======[E N D   O F   F I L E]==============================================*/

