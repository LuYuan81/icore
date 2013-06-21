/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *
 *  All rights reserved. This software is iSOFT property. Duplication
 *  or disclosure without iSOFT written authorization is prohibited.
 *
 *  @file       <Com_Ram.c>
 *  @brief      <Briefly describe file(one line)>
 *
 *  <Compiler: Cygwin C Compiler    MCU:--->
 *
 *  @author     <Gary Chen && zheng fang>
 *  @date       <2013-5-10>
 */
/*============================================================================*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>         <AUTHOR>                    <REVISION LOG>
 *  V1.0.0      20130510   Gary Chen && zheng fang        Initial version
 */
/*============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define COM_RAM_C_AR_MAJOR_VERSION   3U
#define COM_RAM_C_AR_MINOR_VERSION   0U
#define COM_RAM_C_AR_PATCH_VERSION   3U
#define COM_RAM_C_SW_MAJOR_VERSION   1U
#define COM_RAM_C_SW_MINOR_VERSION   0U
#define COM_RAM_C_SW_PATCH_VERSION   0U

/*=======[I N C L U D E S]====================================================*/
#include "Com_Ram.h"

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (COM_RAM_C_AR_MAJOR_VERSION != COM_RAM_H_AR_MAJOR_VERSION)
    #error "Com_Ram.c : Mismatch in Specification Major Version"
#endif
#if (COM_RAM_C_AR_MINOR_VERSION != COM_RAM_H_AR_MINOR_VERSION)
    #error "Com_Ram.c : Mismatch in Specification Major Version"
#endif
#if (COM_RAM_C_AR_PATCH_VERSION != COM_RAM_H_AR_PATCH_VERSION)
    #error "Com_Ram.c : Mismatch in Specification Major Version"
#endif
#if (COM_RAM_C_SW_MAJOR_VERSION != COM_RAM_H_SW_MAJOR_VERSION)
    #error "Com_Ram.c : Mismatch in Specification Major Version"
#endif
#if (COM_RAM_C_SW_MINOR_VERSION != COM_RAM_H_SW_MINOR_VERSION)
    #error "Com_Ram.c : Mismatch in Specification Major Version"
#endif


/*=======[I N T E R N A L   D A T A]==========================================*/
/* total buffer number of COM module */
#define COM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
VAR(uint8, COM_VAR) Com_MemoryBuffer[COM_BUFFER_SIZE];
#define COM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/* Message runtime structure array */
#define COM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
VAR(Com_MsgRunTimeType, COM_VAR) Com_PrivateMsg[COM_MSG_NUM];
#define COM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
/* IPdu runtime structure array */
#define COM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
VAR(Com_IPduRunTimeType, COM_VAR) Com_PrivateIPdu[COM_IPDU_NUM];
#define COM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif



/*=======[E N D   O F   F I L E]==============================================*/

