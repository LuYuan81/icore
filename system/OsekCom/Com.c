/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *
 *  All rights reserved. This software is iSOFT property. Duplication
 *  or disclosure without iSOFT written authorization is prohibited.
 *
 *  @file       <Com.c>
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
#define COM_C_AR_MAJOR_VERSION   3U
#define COM_C_AR_MINOR_VERSION   0U
#define COM_C_AR_PATCH_VERSION   3U
#define COM_C_SW_MAJOR_VERSION   1U
#define COM_C_SW_MINOR_VERSION   0U
#define COM_C_SW_PATCH_VERSION   0U

/*=======[I N C L U D E S]====================================================*/
#include "Com.h"
#include "Com_Ram.h"
#include "Com_Cbk.h"
#include "SchM_Com.h"
#include "PduR_Com.h"
#if (STD_ON == COM_CONFIGURATION_USE_DET)
#include "Det.h"
#endif

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (COM_C_AR_MAJOR_VERSION != COM_H_AR_MAJOR_VERSION)
    #error "Com.c : Mismatch in Specification Major Version"
#endif
#if (COM_C_AR_MINOR_VERSION != COM_H_AR_MINOR_VERSION)
    #error "Com.c : Mismatch in Specification Major Version"
#endif
#if (COM_C_AR_PATCH_VERSION != COM_H_AR_PATCH_VERSION)
    #error "Com.c : Mismatch in Specification Major Version"
#endif
#if (COM_C_SW_MAJOR_VERSION != COM_H_SW_MAJOR_VERSION)
    #error "Com.c : Mismatch in Specification Major Version"
#endif
#if (COM_C_SW_MINOR_VERSION != COM_H_SW_MINOR_VERSION)
    #error "Com.c : Mismatch in Specification Major Version"
#endif

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/* module status type */
typedef enum
{
    /* uninit status */
    COM_UNINIT,
    
    /* init status */
    COM_INIT
}Com_ModuleStatusType;

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   D A T A]==========================================*/

/* OSEK COM module status */
#define COM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#include "MemMap.h"
STATIC VAR(Com_ModuleStatusType, COM_VAR_POWER_ON_INIT)Com_ModuleStatus = COM_UNINIT;
#define COM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#include "MemMap.h"

#define COM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#include "MemMap.h"
/* Pointer to configuration structure */
STATIC P2CONST(Com_ConfigType, COM_VAR_POWER_ON_INIT, COM_CONST_PBCFG)Com_CfgPtr = NULL_PTR;
#define COM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#include "MemMap.h"

/* buffer number of COM module used currently */
#define COM_START_SEC_VAR_POWER_ON_INIT_16BIT
#include "MemMap.h"
STATIC VAR(uint16, COM_VAR_POWER_ON_INIT)Com_BufferUsed = 0u;
#define COM_STOP_SEC_VAR_POWER_ON_INIT_16BIT
#include "MemMap.h"

#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
/* OSEK COM I-PDU Group status */
#define COM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
STATIC VAR(boolean, COM_VAR_POWER_ON_INIT)Com_SendIpduGroupStartFlag = FALSE;
STATIC VAR(boolean, COM_VAR_POWER_ON_INIT)Com_ReceiveIpduGroupStartFlag = FALSE;
#define COM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
#endif

#if (OSEK_COM_CCC == OSEK_COM_CCC1)
/* Deadline Monitor enable flag */
#define COM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
STATIC VAR(boolean, COM_VAR_POWER_ON_INIT)Com_IpduGroupRepDMEnable = FALSE;
#define COM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
#include "MemMap.h"
#endif

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#if (OSEK_COM_CCC == OSEK_COM_CCC1)
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FMaskedNewEqualsX
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FMaskedNewDiffersX
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsEqual
(
    const uint32 newMsg,
    P2CONST(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsDifferent
(
    const uint32 newMsg,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FMaskedNewEqualsMaskedOld
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
 );
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FMaskedNewDiffersMaskedOld
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsWithin
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsOutside
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsGreater
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsLessOrEqual
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsLess
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
 );
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsGreaterOrEqual
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FOneEveryN
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
 );
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecDynamicLink
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_NWOrderCallout
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_IpduCallout
(
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_CPUOrderCallout
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint32, COM_CODE)
Com_InitValueToU32
(
    const Com_MsgCDataType dataType,
    P2CONST(void, AUTOMATIC, AUTOMATIC)dataPtr
);
#define COM_START_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_Filter
(
    P2CONST(void, AUTOMATIC, AUTOMATIC)msgDataPtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_START_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduPeriodicTX
(
    P2VAR(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)ipduPrivatePtr,
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduDirectTX
(
    P2VAR(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)ipduPrivatePtr,
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduMixedTX
(
    P2VAR(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)ipduPrivatePtr,
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint32, COM_CODE)
Com_FindDynamicMsgMinBit
(
    P2CONST(Com_NWMsgType, AUTOMATIC, COM_CONST_PBCFG)NWMsgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecQueuedExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecDynamicExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgSendDynamicExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValRecDynamicExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValSendDynamicExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef,
    boolean initFinished
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendDynamicExternel
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataPtr,
    const uint16 length
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecDynamicExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)iPduPrivatePtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_NotifDM
(
    const uint32 u4PduId
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecZeroInternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecZeroExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgSendZeroExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendZeroInternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendZeroExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecZeroExternal
(
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)iPduCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(Com_MsgBitOrderingType, COM_CODE)
Com_GetLocalCpuEndian(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint16, COM_CODE)
Com_GetBitToByteSize
(
    const uint32 bitSize
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitIpdu(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_SendIpdu
(
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint16, COM_CODE)
Com_FindIpduIndex
(
    const uint32 pduId
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_CopyBit
(
    P2CONST(Com_MsgType, AUTOMATIC, CODE_CONST_PBCFG)msgCfgPtr,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC)sourceData,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)destData,
    uint32 copyBitNum
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint32, COM_CODE)
Com_GetMsgStartPostion
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_SetBit
(
    uint32 sourceStartPos,
    uint32 destStartPos,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC)sourceData,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)destData
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint32, COM_CODE)
Com_IndexCopyBit
(
    const uint32 startPos,
    P2CONST(Com_NWMsgType, AUTOMATIC, COM_CONST_PBCFG)NWMsgCfgPtr
 );
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgReceive
(
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr,
    P2CONST(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)iPduPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecUnQueuedExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgSendStaticExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValRecUnQueuedExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValSendStaticExternal
(
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    boolean initFinished,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    #endif
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecStaticLink
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, AUTOMATIC)appDataPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendStaticExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    #endif
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecStaticExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)iPduPrivatePtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint16, COM_CODE)
Com_GetStaticExternelMsgLength
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_NotifTxConfirm
(
    const uint32 u4PduId
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_OrderChange
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)dataPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_BitExtension
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(void, AUTOMATIC, AUTOMATIC)recDataPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_QueueBufInc
(
    P2CONST(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr,
    P2VAR(P2VAR(uint8, AUTOMATIC, COM_VAR),AUTOMATIC, COM_VAR)bufferPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_QueueBufFull
(
    P2CONST(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecQueuedInternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_QueueBufInsert
(
    P2VAR(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr,
    P2CONST(uint8, AUTOMATIC, COM_VAR)dataPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_QueueBufGet
(
    P2VAR(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr,
    P2VAR(uint8, AUTOMATIC, COM_VAR)dataPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Queue_BufferFlush
(
    P2VAR(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_Memcpy
(
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)destPtr,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC)sourcePtr,
    uint16 length
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_Memset
(
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)destPtr,
    const uint8 source,
    uint16 length
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(P2VAR(void, AUTOMATIC, COM_VAR), COM_CODE)
Com_Malloc
(
    const uint16 length
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint16, COM_CODE)
Com_GetCDataByteSize
(
    const Com_MsgCDataType dataType
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsg
(
    void
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitVal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecUnQueuedInternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValRecUnQueuedInternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendStaticInternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgRecStaticInternel
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#if (OSEK_COM_CCC == OSEK_COM_CCC1)
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduGroupStart_TX
(
    boolean Initialize
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduGroupStart_RX
(
    boolean Initialize
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_RepDMHandle(uint16 loop);
#define COM_STOP_SEC_CODE
#include "MemMap.h" 
#endif

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/
/*
 * @req COM151 , @req COM174, @req COM175, @req COM176, @req COM178, @req COM179,
 * @req COM180, @req COM 014, @req COM 015
 */
/******************************************************************************/
/*
 * Brief                 <This service initializes internal and external interfaces
 *                       and variables of the AUTOSAR COM layer for the further
 *                       processing. After calling this function the inter-ECU
 *                       communication is still disabled.>
 * Service ID            <SERVICE_ID_COM_INIT>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Non Reentrant>
 * Param-Name[in]        <configPtr:Pointer to the COM configuration data.>
 * Param-Name[out]:      <None>
 * Param-Name[in/out]:   <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/*
 * @req COM156, @req COM158, @req COM159, @req COM168, @req COM153,@req COM166,
 * @req COM181, @req COM181-1, @req COM181-3, @req COM181-4
 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_Init
(
    P2CONST(Com_ConfigType, AUTOMATIC, COM_CONST_PBCFG)configPtr
)
{
    StatusType status = E_OK;
    /* @req COM169 */
    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    /* null pointer check */  
    if (NULL_PTR == configPtr)
    {
        status = E_COM_POINTER;
        /* @req COM170 */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_INIT, E_COM_POINTER);
    }
   
    /* module status check, if initialized, exit init function */
    if ((COM_INIT == Com_ModuleStatus)
        && (E_OK == status))
    {
        status = COM_E_UNINIT;
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_INIT, COM_E_UNINIT);
    }

    if (E_OK == status)
    #endif
    {
        /* save configuration data into global variable */
        Com_CfgPtr = configPtr;
        /* module is uninitialized */
        Com_BufferUsed = 0u;
        Com_Memset(Com_MemoryBuffer, 0x00u, Com_CfgPtr->bufferLength);
        
        #if (OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0)
        /* set OSEK COM I-PDU Group start status */
        Com_SendIpduGroupStartFlag = FALSE;
        Com_ReceiveIpduGroupStartFlag = FALSE;
        #endif

        /* set OSEK COM I-PDU Group reception deadline monitoring enable flag */
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        Com_IpduGroupRepDMEnable = FALSE;
        #endif

        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
        /* initialize I-PDU runtime structure array */
        status = Com_InitIpdu();

        #if (STD_ON == COM_CONFIGURATION_USE_DET)
        if (E_COM_LENGTH == status)
        {
            /* buffer is not enough, det report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_INIT, E_COM_LENGTH);
        }

        if (E_COM_ID == status)
        {
            /* some message identifier is invalid, det report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_INIT, E_COM_ID);
        }
        #endif
        #endif
    }
    
    if (E_OK == status)
    {
        /* initialize Message runtime structure array */
        status = Com_InitMsg();

        #if (STD_ON == COM_CONFIGURATION_USE_DET)
        if (E_COM_LENGTH == status)
        {
            /* buffer is not enough,det report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_INIT, E_COM_LENGTH);
        }

        if (E_COM_ID == status)
        {
            /* some message identifier is invalid, det report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_INIT, E_COM_ID);
        }
        #endif
    }

    if (E_OK == status)
    {
        /* change module status */
        Com_ModuleStatus = COM_INIT;

        /* @req COM155 */
        if (NULL_PTR != Com_CfgPtr->startCOMExtension)
        {
            /* @req COM181-2 */
            Com_CfgPtr->startCOMExtension();
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This service stops the inter-ECU communication. All
 *                       started I-PDU groups are stopped and have to be started
 *                       again, if needed, after Com_Init is called. By a call
 *                       to ComDeInit COM is put into an not initialized state.>
 * Service ID            <SERVICE_ID_COM_DEINIT>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Non Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]:   <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/* @req COM154, @req COM167, @req COM182, @req COM182-1, @req COM182-2 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_DeInit(void)
{
    uint16 loop;

    if (COM_INIT == Com_ModuleStatus)
    {
        Com_BufferUsed = 0u;
        /* IPdu runtime structure array */
        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
        /* set OSEK COM I-PDU Group start status */
        Com_SendIpduGroupStartFlag = FALSE;
        Com_ReceiveIpduGroupStartFlag = FALSE;
        #endif
        
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        /* set I-PDU Group Deadline Monitor enable flag */
        Com_IpduGroupRepDMEnable = FALSE;
        #endif

        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
        /* deinit I-PDU runtime structure variable */
        for (loop = 0u; loop < Com_CfgPtr->ipduUsedNum; loop++)
        {
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            Com_PrivateIPdu[loop].DMTimer = 0u;
            Com_PrivateIPdu[loop].mdtTimer = 0u;
            Com_PrivateIPdu[loop].periodTimer = 0u;
            #endif
            Com_PrivateIPdu[loop].dataPtr = NULL_PTR;
            Com_PrivateIPdu[loop].directSend = FALSE;
        }
        #endif

        /* deinit message queue buffer pointer */
        for (loop = 0u; loop < Com_CfgPtr->msgUsedNum; loop++)
        {
            Com_PrivateMsg[loop].queue.bufPtr = NULL_PTR;
            Com_PrivateMsg[loop].queue.firstPtr = NULL_PTR;
            Com_PrivateMsg[loop].queue.lastPtr = NULL_PTR;
        }
        /* OSEK COM module status */
        Com_ModuleStatus = COM_UNINIT;
    }
    return;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The service InitMessage initializes the message object
 *                       identified by <Message> with the application data referenced
 *                       by the <DataRef> parameter.>
 * Service ID            <SERVICE_ID_COM_INITMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <MessageIdentifier: message identifier(C identifier).>
 *                       <ApplicationDataRef: Reference to the initial message data
 *                                            of application>
 * Param-Name[out]       <None>
 * Param-Name[in/out]:   <None>
 * Return                <E_OK: the initialization of the message object completed
 *                             successfully
 *                       E_COM_ID:the parameter <Message> is out of range or refers
 *                                to a zero-length message or to an internal transmit
 *                                message>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/* @req COM157, @req COM160, @req COM183, @req COM183-1, @req COM183-2 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, COM_CODE)
Com_InitMessage
(
    uint16 MessageIdentifier,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef
)
{
    StatusType ret = E_OK;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_INITMESSAGE, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
        if (Com_CfgPtr->msgUsedNum <= MessageIdentifier)
        {
            /* message id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_INITMESSAGE, E_COM_ID);
            ret = E_COM_ID;
        }
        
        if (NULL_PTR == ApplicationDataRef)
        {
            /* parameter pointer is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_INITMESSAGE, E_COM_POINTER);
            ret = E_COM_POINTER;
        }
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        /* call message initialization function */
        ret = Com_InitVal(&Com_PrivateMsg[MessageIdentifier],
                          &Com_CfgPtr->messagePtr[MessageIdentifier],
                          ApplicationDataRef);
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The service SendMessage updates the message object
 *                       identified by <Message> with the application message
 *                       referenced by the <DataRef> parameter.>
 * Service ID            <SERVICE_ID_COM_SENDMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier).
 *                        DataRef: Reference to the application's message data to
 *                                 be transmitted>
 * Param-Name[out]       <None>
 * Param-Name[in/out]:   <None>
 * Return                <E_OK: the service operation completed successfully
 *                        E_COM_ID: the parameter <Message> is out of range or
 *                                 if it refers to a message that is received
 *                                 or to a dynamic-length or zero-length message>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/*
 * @req COM056, @req COM041, @req COM069, @req COM070, @req COM080, @req COM082,
 * @req COM083, @req COM086, @req COM094, @req COM095, @req COM113, @req COM188,
 * @req COM188-1, @req COM188-2, @req COM188-3, @req COM188-4,@req COM188-5,
 * @req COM188-6
 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, COM_CODE)
Com_SendMessage
(
    uint16 MessageIdentifier,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef
)
{
    StatusType ret = E_OK;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_SENDMESSAGE, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    {
        if (Com_CfgPtr->msgUsedNum <= MessageIdentifier)
        {
            /* message id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_SENDMESSAGE, E_COM_ID);
            ret = E_COM_ID;
        }

        if (NULL_PTR == ApplicationDataRef)
        {
            /* parameter pointer is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_SENDMESSAGE, E_COM_POINTER);
            ret = E_COM_POINTER;
        }
    }

    if (E_OK == ret)
    #endif
    {
        switch(Com_CfgPtr->messagePtr[MessageIdentifier].property)
        {
            case COM_MSG_SEND_STATIC_INTERNAL:
                /* call static internal sending message processing function */
                /* @req COM071 */
                ret = Com_MsgSendStaticInternal(&Com_CfgPtr->messagePtr[MessageIdentifier],
                                                 ApplicationDataRef);
                break;

            #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
            case COM_MSG_SEND_STATIC_EXTERNAL:
                /**@req COM008*/
                /* call static internal sending message processing function */
                ret = Com_MsgSendStaticInternal(&Com_CfgPtr->messagePtr[MessageIdentifier],
                                                ApplicationDataRef);
                if (E_OK == ret)
                {
                    /* call static external sending message processing function */
                    /**@req COM071 */
                    ret = Com_MsgSendStaticExternal(&Com_CfgPtr->messagePtr[MessageIdentifier],
                                                    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
                                                    &Com_PrivateMsg[MessageIdentifier],
                                                    #endif
                                                    ApplicationDataRef);
                }
           #endif
                break;

            default:
                ret = E_COM_ID;
                break;
        }

        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
        if ((E_OK == ret) && (FALSE == Com_SendIpduGroupStartFlag)
           && (COM_MSG_SEND_STATIC_INTERNAL != Com_CfgPtr->messagePtr[MessageIdentifier].property))
        {
            ret = COM_SERVICE_NOT_AVAILABLE;
        }
        #endif
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The service ReceiveMessage updates the application message
 *                       referenced by DataRef with the data in the message object
 *                       identified by Message.>
 * Service ID            <SERVICE_ID_COM_RECEIVEMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier).>
 * Param-Name[out]       <DataRef: Reference to the application's message area in
 *                                 which to store the received data.>
 * Param-Name[in/out]:   <None>
 * Return                <E_OK:data in the queued or unqueued message identified
 *                            by <Message> are available and returned to
 *                            the application successfully.
 *                       E_COM_NOMSG:the queued message identified by <Message>
 *                                   is empty
 *                       E_COM_LIMIT:an overflow of the message queue identified
 *                                   by <Message> occurred since the last call to
 *                                   ReceiveMessage for <Message>.
 *                       E_COM_ID:the parameter <Message> is out of range or if
 *                                it refers to message that is sent or to a
 *                                dynamic length or zero-length message.>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/*
 * @req COM056, @req COM068, @req COM074,@req COM189,@req COM189-1,@req COM189-2,
 * @req COM189-3, @req COM189-4, @req COM189-5, @req COM189-6
 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, COM_CODE)
Com_ReceiveMessage
(
    uint16 MessageIdentifier,
    P2VAR(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef
)
{
    StatusType ret = E_OK;
    uint16 msgLength = 0u;
    #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
    boolean queueResult = TRUE;
    #endif

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit, DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_RECEIVEMESSAGE, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    {
        if (Com_CfgPtr->msgUsedNum <= MessageIdentifier)
        {
            /* message id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_RECEIVEMESSAGE, E_COM_ID);
            ret = E_COM_ID;
        }

        if (NULL_PTR == ApplicationDataRef)
        {
            /* parameter pointer is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_RECEIVEMESSAGE, E_COM_POINTER);
            ret = E_COM_POINTER;
        }
    }

    if (E_OK == ret)
    #endif
    {
        /* @req COM051 */
        switch (Com_CfgPtr->messagePtr[MessageIdentifier].property)
        {
            case COM_MSG_RECEIVE_UNQUEUED_INTERNAL:
                /* copy message from message reception buffer to application buffer directly */
                msgLength = Com_GetCDataByteSize(Com_CfgPtr->messagePtr[MessageIdentifier].cData);
                Com_Memcpy((uint8*)ApplicationDataRef, Com_PrivateMsg[MessageIdentifier].queue.bufPtr, msgLength);
                break;

            #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
            case COM_MSG_RECEIVE_UNQUEUED_EXTERNAL:
                /* copy message from message reception buffer to application buffer directly */
                msgLength = Com_GetStaticExternelMsgLength(&Com_CfgPtr->messagePtr[MessageIdentifier]);
                Com_Memcpy((uint8*)ApplicationDataRef, Com_PrivateMsg[MessageIdentifier].queue.bufPtr, msgLength);

                if (FALSE == Com_ReceiveIpduGroupStartFlag)
                {
                    ret = COM_SERVICE_NOT_AVAILABLE;
                }
                break;
            #endif

            #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
            case COM_MSG_RECEIVE_QUEUED_INTERNAL:
                /*
                 * copy oldest message from external message reception queue to application buffer
                 * and delete the oldest message from the message queue
                 */
                queueResult = Com_QueueBufGet(&Com_PrivateMsg[MessageIdentifier].queue, (uint8*)ApplicationDataRef);
                if (FALSE == queueResult)
                {
                    /* internal message queue is empty, set message status as "no message" */
                    Com_PrivateMsg[MessageIdentifier].messageStatus = E_COM_NOMSG;
                    ret = E_COM_NOMSG;
                }
                else
                {
                    /* return last saved message status, set new message status */
                    ret = Com_PrivateMsg[MessageIdentifier].messageStatus;
                    Com_PrivateMsg[MessageIdentifier].messageStatus = E_OK;
                }
                break;
            #endif

            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            case COM_MSG_RECEIVE_QUEUED_EXTERNAL:
                /*
                 * copy oldest message from external message reception queue to application buffer
                 * and delete the oldest message from the message queue
                 */
                queueResult = Com_QueueBufGet(&Com_PrivateMsg[MessageIdentifier].queue, (uint8*)ApplicationDataRef);
                if (FALSE == queueResult)
                {
                    /* external message queue is empty, set message status as "no message" */
                    Com_PrivateMsg[MessageIdentifier].messageStatus = E_COM_NOMSG;
                    ret = E_COM_NOMSG;
                }
                else
                {
                   /* return last saved message status, set new message status */
                    ret = Com_PrivateMsg[MessageIdentifier].messageStatus;
                    Com_PrivateMsg[MessageIdentifier].messageStatus = E_OK;
                }

                /* if corresponding I-PDU group is not started, return service not available status */
                if ((E_OK == ret) && (FALSE == Com_ReceiveIpduGroupStartFlag))
                {
                    ret = COM_SERVICE_NOT_AVAILABLE;
                }
                break;
            #endif

            default:
                ret = E_COM_ID;
                break;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/*                          Conformance Classes:  1                           */
/*                                                                            */
/******************************************************************************/
#if (OSEK_COM_CCC == OSEK_COM_CCC1)
/******************************************************************************/
/*
 * Brief                <The service StartPeriodic starts periodic transmission
 *                       of all messages using either the Periodic or the Mixed
 *                       Transmission Modes, unless periodic transmission is
 *                       already started for these messages.>
 * Service ID            <SERVICE_ID_COM_STARTPERIODIC>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK:periodic transmission was started successfully>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/* @req COM104, @req COM184, @req COM184-1 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, COM_CODE)
Com_StartPeriodic(void)
{
    uint16 loop = 0u;
    StatusType ret = E_OK;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit, DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_STARTPERIODIC, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        if (TRUE == Com_SendIpduGroupStartFlag)
        {
            /* initialize corresponding runtime variables of every I-PDU */
            for (loop = 0u; loop < Com_CfgPtr->ipduUsedNum; loop++)
            {
                /* sending I-PDU only and not direct transmit mode only */
                /* @req COM105 */
                if ((COM_IPDU_SENT == Com_CfgPtr->ipduPtr[loop].direction)
                     && (COM_IPDU_TRANSMIT_DIRECT != Com_CfgPtr->ipduPtr[loop].transmitMode))
                {
                    /* set periodic I-PDU transmit timer */
                    /* @req COM106 */
                    Com_PrivateIPdu[loop].periodTimer = Com_CfgPtr->ipduPtr[loop].timeOffset / Com_CfgPtr->timeBase;
                }
            }
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief        :        <The service StopPeriodic stops periodic transmission of
 *                       all messages using either the Periodic or the Mixed
 *                       Transmission Modes, unless periodic transmission is
 *                       already stopped for these messages.>
 * Service ID            <SERVICE_ID_COM_STOPPERIODIC>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK:periodic transmission was stopped successfully>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/* @req COM107, @req COM185, @req COM185-1, @req COM185-2 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, COM_CODE)
Com_StopPeriodic(void)
{
    uint16 loop = 0u;
    StatusType ret = E_OK;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit, DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_STOPPERIODIC, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        if (TRUE == Com_SendIpduGroupStartFlag)
        {
            /* de-initialize corresponding runtime variables of every I-PDU */
            for (loop = 0u; loop < Com_CfgPtr->ipduUsedNum; loop++)
            {
                /* not direct transmit mode only */
                if ((COM_IPDU_SENT == Com_CfgPtr->ipduPtr[loop].direction)
                   && (COM_IPDU_TRANSMIT_DIRECT != Com_CfgPtr->ipduPtr[loop].transmitMode))
                {
                    /* clear periodic I-PDU transmit timer */
                    Com_PrivateIPdu[loop].periodTimer = 0u;
                }
            }
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                <The service SendDynamicMessage updates the message object
 *                       identified by <Message> with the application data referenced
 *                       by the<DataRef> parameter.>
 * Service ID            <SERVICE_ID_COM_SENDDYNAMICMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier).
 *                        DataRef: Reference to the application's message data to be
 *                                transmitted
 *                       LengthRef:Reference to a value containing the length of
 *                       the data in the message>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK:the service operation completed successfully
 *                        E_COM_ID:the parameter <Message> is out of range or if
 *                                 it refers to a received message, a static-length
 *                                 message or a zero-length message.
 *                        E_COM_LENGTH:the value to which <LengthRef> points is not
 *                                     within the range 0 to the maximum length
 *                                     defined for <Message>. >
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/*
 * @req COM190, @req COM190-1, @req COM190-2, @req COM190-3, @req COM190-4, @req COM190-5,
 * @req COM190-6
 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, COM_CODE)
Com_SendDynamicMessage
(
    uint16 MessageIdentifier,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef,
    P2CONST(Com_LengthType, AUTOMATIC, COM_APPL_DATA)LengthRef
)
{
    StatusType ret = E_OK;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_SENDDYNAMICMESSAGE, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
        if (Com_CfgPtr->msgUsedNum <= MessageIdentifier)
        {
            /* message id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_SENDDYNAMICMESSAGE, E_COM_ID);
            ret = E_COM_ID;
        }

        if ((E_OK == ret) && ((NULL_PTR == ApplicationDataRef) || (NULL_PTR == LengthRef)))
        {
            /* parameter pointer is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_SENDDYNAMICMESSAGE, E_COM_POINTER);
            ret = E_COM_POINTER;
        }
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        if (COM_MSG_SEND_DYNAMIC_EXTERNAL == Com_CfgPtr->messagePtr[MessageIdentifier].property)
        {
            /* call dynamic external sending message processing function */
            ret = Com_MsgSendDynamicExternel(&Com_CfgPtr->messagePtr[MessageIdentifier],
                                            ApplicationDataRef,
                                            *LengthRef);
        }
        else
        {
            /* not dynamic message, return error code */
            ret = E_COM_ID;
        }

        /* if corresponding I-PDU group is not started, return service not available status */
        if ((E_OK == ret) && (FALSE == Com_SendIpduGroupStartFlag))
        {
            ret = COM_SERVICE_NOT_AVAILABLE;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The service ReceiveDynamicMessage updates the application
 *                       message referenced by <DataRef> with the data in the message
 *                       object identified by <Message>.>
 * Service ID            <SERVICE_ID_COM_SENDDYNAMICMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier).>
 * Param-Name[out]       <DataRef: Reference to the application's message area in
 *                                which to store the received data.
 *                       LengthRef:Reference to an application variable in which
 *                                 to store the message length. >
 * Param-Name[in/out]    <None>
 * Return                <E_OK:data in the unqueued message identified by <Message>
 *                            is returned to the application successfully.
 *                       E_COM_ID:the parameter <Message> is out of range or if
 *                                it refers to a message that is sent, a queued
 *                                message, a static-length message or a zero-length
 *                                message>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/* @req COM191, @req COM191-1, @req COM191-2, @req COM191-3, @req COM191-4 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, COM_CODE)
Com_ReceiveDynamicMessage
(
    uint16 MessageIdentifier,
    P2VAR(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef,
    P2VAR(Com_LengthType, AUTOMATIC, COM_APPL_DATA)LengthRef
)
{
    StatusType ret = E_OK;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_RECEIVEDYNAMICMESSAGE, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
        if (Com_CfgPtr->msgUsedNum <= MessageIdentifier)
        {
            /* message id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_RECEIVEDYNAMICMESSAGE, E_COM_ID);
            ret = E_COM_ID;
        }

        if ((E_OK == ret) && ((NULL_PTR == ApplicationDataRef) || (NULL_PTR == LengthRef)))
        {
            /* parameter pointer is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_RECEIVEDYNAMICMESSAGE, E_COM_POINTER);
            ret = E_COM_POINTER;
        }
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        /* only for dynamic external receive message*/
        if (COM_MSG_RECEIVE_DYNAMIC_EXTERNAL == Com_CfgPtr->messagePtr[MessageIdentifier].property)
        {
            /* the network message of dynamic message corresponding to is not null*/
            if (Com_CfgPtr->messagePtr[MessageIdentifier].NWMsgPtr != NULL_PTR)
            {
                *LengthRef = (Com_LengthType)(Com_GetBitToByteSize(Com_CfgPtr->messagePtr[MessageIdentifier].NWMsgPtr->maximumSizeInBits));
            }
            else   /* the dynamic message is a link message */
            {
                *LengthRef = (Com_LengthType)(Com_GetBitToByteSize(Com_CfgPtr->messagePtr[MessageIdentifier].linkMsgPtr->NWMsgPtr->maximumSizeInBits));
            }

            /* copy message from dynamic message reception buffer to application buffer directly */
            Com_Memcpy((uint8*)ApplicationDataRef, Com_PrivateMsg[MessageIdentifier].queue.bufPtr, *LengthRef);
        }
        else
        {
            ret = E_COM_ID;
        }
        
        /* if corresponding I-PDU group is not started, return service not available status */
        if ((E_OK == ret) && (FALSE == Com_ReceiveIpduGroupStartFlag))
        {
            ret = COM_SERVICE_NOT_AVAILABLE;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <External communication:
 *                       The service SendZeroMessage causes immediate transmission
 *                       of the I-PDU associated with the zero-length message <Message>
 *                       except when this message is associated with an I-PDU with
 *                       Periodic Transmission Mode; in this case, no transmission
 *                       is initiated by the call to this service.
 *                       Internal communication:
 *                       The message <Message> is routed to the receiving part of
 *                       the IL for notification >
 * Service ID            <SERVICE_ID_COM_SENDZEROMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]            <MessageIdentifier(IN)>
 * Param-Name[out]           <None>
 * Param-Name[in/out]        <None>
 * Return               <None>
 */
/******************************************************************************/
/* @req COM073, @req COM128, @req COM192, @req COM192-1, @req COM191-2, @req COM191-3 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, COM_CODE)
Com_SendZeroMessage
(
    uint16 MessageIdentifier
)
{
    StatusType ret = E_OK;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit, DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_SENDZEROMESSAGE, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
        if (Com_CfgPtr->msgUsedNum <= MessageIdentifier)
        {
            /* message id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_SENDZEROMESSAGE, E_COM_ID);
            ret = E_COM_ID;
        }
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        switch (Com_CfgPtr->messagePtr[MessageIdentifier].property)
        {
            case COM_MSG_SEND_ZERO_INTERNAL:
                /* call zero-length internal sending message processing function */
                ret = Com_MsgSendZeroInternal(&Com_CfgPtr->messagePtr[MessageIdentifier]);
                break;

            case COM_MSG_SEND_ZERO_EXTERNAL:
                /* call zero-length internal sending message processing function */
                ret = Com_MsgSendZeroInternal(&Com_CfgPtr->messagePtr[MessageIdentifier]);

                if (E_OK == ret)
                {
                    /* call zero-length external sending message processing function */
                    ret = Com_MsgSendZeroExternal(&Com_CfgPtr->messagePtr[MessageIdentifier]);
                }

                /* if corresponding I-PDU group is not started, return service not available status */
                if ((E_OK == ret) && (FALSE == Com_SendIpduGroupStartFlag))
                {
                    ret = COM_SERVICE_NOT_AVAILABLE;
                }
                break;

            default:
                ret =  E_COM_ID;
                break;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <Disables the reception deadline monitoring for the I-PDUs
 *                       within the given I-PDU group.>
 * Service ID            <SERVICE_ID_COM_DISABLERECEPTIONDM>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different I-PDU groups,Non Reentrant:same I-PDU group>
 * Param-Name[in]        <IpduGroupId: Id of I-PDU group where reception DM shall be disabled.>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <CANSM>
 */
/******************************************************************************/
/* @req COM201 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_DisableReceptionDM
(
    Com_PduGroupIdType IpduGroupId
    /*
	 * MISRA RULE MISRA-C:2004 Rule 14.1 VIOLATION: because in current version, 
     * all I-PDUs belong to a same I-PDU group, and only one global variable for 
     * the I-PDU group, so the parameter is unused in this function and exsit only
     * for consistent with AUTOSAR
	 */
)
{
    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    StatusType ret = E_OK;

    if (COM_INIT != Com_ModuleStatus)
    {
        ret = COM_E_UNINIT;
        /* OSEK COM uninit, DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_DISABLERECEPTIONDM, COM_E_UNINIT);
    }

    if (E_OK == ret)
    {
        if (Com_CfgPtr->receivePduGroupId != IpduGroupId)
        {
            ret = E_COM_ID;
            /* I-PDU group id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_DISABLERECEPTIONDM, E_COM_ID);
        }
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        Com_IpduGroupRepDMEnable = FALSE;
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <Enables the reception deadline monitoring for the I-PDUs
 *                       within the given I-PDU group.>
 * Service ID            <SERVICE_ID_COM_ENABLERECEPTIONDM>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different I-PDU groups,Non Reentrant:same I-PDU group>
 * Param-Name[in]        <IpduGroupId: Id of I-PDU group where reception DM shall be enabled>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <CANSM>
 */
/******************************************************************************/
/* @req COM202 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_EnableReceptionDM
(
    Com_PduGroupIdType IpduGroupId
    /* 
	 *MISRA RULE MISRA-C:2004 Rule 14.1 VIOLATION: because in current version, 
     * all I-PDUs belong to a same I-PDU group, and only one global variable for 
     * the I-PDU group, so the parameter is unused in this function and exsit only
     * for consistent with AUTOSAR
	 */
)
{
    uint8 ipduLoop = 0u;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    StatusType ret = E_OK;

    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_ENABLERECEPTIONDM, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
        if (Com_CfgPtr->receivePduGroupId != IpduGroupId)
        {
            /* I-PDU group id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_ENABLERECEPTIONDM, E_COM_ID);
            ret = E_COM_ID;
        }
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        /* @req COM486, @req COM224 */
       if (FALSE == Com_IpduGroupRepDMEnable)
       {
           /* set I-PDU group reception deadline monitor flag */
           Com_IpduGroupRepDMEnable = TRUE;

           for (ipduLoop = 0u; ipduLoop < Com_CfgPtr->ipduUsedNum; ipduLoop++)
           {
               /* start all reception I-PDU deadline monitor timer */
               if (COM_IPDU_RECEIVE == Com_CfgPtr->ipduPtr[ipduLoop].direction)
               {
                   Com_PrivateIPdu[ipduLoop].DMTimer = Com_CfgPtr->ipduPtr[ipduLoop].firstTimeOut / Com_CfgPtr->timeBase;
               }
           }
       }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/******************************************************************************/
/*                                                                            */
/*                         Conformance Classes:  1/B                          */
/*                                                                            */
/******************************************************************************/
#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
/******************************************************************************/
/*
 * Brief                 <The service GetMessageStatus returns the current status
 *                       of the message object <Message>.>
 * Service ID            <SERVICE_ID_COM_GETMESSAGESTATUS>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier).>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_COM_NOMSG: the message queue identified by <Message>
 *                                    is empty
 *                       E_COM_LIMIT: an overflow of the message queue identified
 *                                    by <Message> occurred since the last call to
 *                                    ReceiveMessage for <Message>.
 *                       E_OK: none of the conditions specified above is applicable
 *                             or fulfilled and no error indication is present
 *                       E_COM_ID:the parameter <Message> is out of range or if
 *                                it does not refer to a queued message >
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/* @req COM193, @req COM193-1, @req COM193-2, @req COM193-3, @req COM193-4 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(StatusType, COM_CODE)
Com_GetMessageStatus
(
    uint16 MessageIdentifier
)
{
    StatusType ret = E_OK;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_GETMESSAGESTATUS, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    {
        if (Com_CfgPtr->msgUsedNum <= MessageIdentifier)
        {
            /* message id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_GETMESSAGESTATUS, E_COM_ID);
            ret = E_COM_ID;
        }
    }

    if (E_OK == ret)
    #endif
    {
        switch (Com_CfgPtr->messagePtr[MessageIdentifier].property)
        {
            /* message status only used for queue message */
            case COM_MSG_RECEIVE_QUEUED_INTERNAL:
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            case COM_MSG_RECEIVE_QUEUED_EXTERNAL:
            #endif
                ret = Com_PrivateMsg[MessageIdentifier].messageStatus;
                break;

            default:
                ret = E_COM_ID;
                break;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/******************************************************************************/
/*                                                                            */
/*                        Conformance Classes:  1/0                           */
/*                                                                            */
/******************************************************************************/
#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
/******************************************************************************/
/*
 * Brief                 <Start a pre-configured I-PDU group.>
 * Service ID            <SERVICE_ID_COM_IPDUGROUPSTART>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different I-PDU groups,Non Reentrant:same I-PDU group>
 * Param-Name[in]        <IpduGroupId: Id of I-PDU group to be started
 *                        Initialize: flag to request initialization of the data in the
 *                                   I-PDUs of this I-PDU group >
 * Param-Name[out]       <None>
 * Param-Name[in/out]:   <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <CANSM>
 */
/******************************************************************************/
/* @req COM199 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_IpduGroupStart
(
    Com_PduGroupIdType IpduGroupId ,
    boolean Initialize
)
{
    #if  (STD_ON == COM_CONFIGURATION_USE_DET)
    StatusType ret = E_OK;

    if (COM_INIT != Com_ModuleStatus)
    {
        /* Com module is not initialized */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_IPDUGROUPSTART, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
        /* I-PDU group id is invalid, DET report */
        if (((Com_CfgPtr->receivePduGroupId != IpduGroupId)
            && (Com_CfgPtr->sendPduGroupId != IpduGroupId)))
        {
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_IPDUGROUPSTART, E_COM_ID);
            ret = E_COM_ID;
        }
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        if ((IpduGroupId == Com_CfgPtr->sendPduGroupId)
            && (FALSE == Com_SendIpduGroupStartFlag))
        {
            /* call I-PDU group start TX handle function */
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            Com_IpduGroupStart_TX(Initialize);
            #endif
            /* set I-PDU group start flag */
            Com_SendIpduGroupStartFlag = TRUE;
        }

        if ((IpduGroupId == Com_CfgPtr->receivePduGroupId)
            && (FALSE == Com_ReceiveIpduGroupStartFlag))
        {
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            /* enable I-PDU group reception deadline monitor flag */
            Com_IpduGroupRepDMEnable = TRUE;
            /* call I-PDU group start RX handle function */
            Com_IpduGroupStart_RX(Initialize);
            #endif          
            /* set I-PDU group start flag */
            Com_ReceiveIpduGroupStartFlag = TRUE;
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <Stops a pre-configured I-PDU group.>
 * Service ID            <SERVICE_ID_COM_IPDUGROUPSTOP>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different I-PDU groups,Non Reentrant:same I-PDU group>
 * Param-Name[in]        <IpduGroupId: Id of I-PDU group to be stopped>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized and corresponding group is started>
 * CallByAPI             <CANSM>
 */
/******************************************************************************/
/* @req COM200 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_IpduGroupStop
(
    Com_PduGroupIdType IpduGroupId
)
{
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    uint32  loop = 0u;
    #endif

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    StatusType ret = E_OK;

    if (COM_INIT != Com_ModuleStatus)
    {
        /* com module is not initialized */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_IPDUGROUPSTOP, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
        if ((Com_CfgPtr->receivePduGroupId != IpduGroupId)
            && (Com_CfgPtr->sendPduGroupId != IpduGroupId))
        {
            /* I-PDU group id is invalid, DET report */
              Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_IPDUGROUPSTOP, E_COM_ID);
            ret = E_COM_ID;
        }
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        if ((IpduGroupId == Com_CfgPtr->sendPduGroupId)
          && (TRUE == Com_SendIpduGroupStartFlag))
        {
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            /* deinit for every I-PDU */
            for (loop = 0u;
                (loop < Com_CfgPtr->ipduUsedNum) && (COM_IPDU_SENT == Com_CfgPtr->ipduPtr[loop].direction);
                loop++)
            {
                /* deinit I-PDU minimum delay timer and period timer */
                if (COM_IPDU_SENT == Com_CfgPtr->ipduPtr[loop].direction)
                {
                    Com_PrivateIPdu[loop].directSend = FALSE;
                    Com_PrivateIPdu[loop].mdtTimer = 0u;
                    Com_PrivateIPdu[loop].periodTimer = 0u;

                    /* @req COM115 */
                    /* if deadline monitor timer of I-DPU is bigger than 0, deadline monitor notification */
                    if (Com_PrivateIPdu[loop].DMTimer > 0x00u)
                    {
                        Com_PrivateIPdu[loop].DMTimer = 0u;
                        Com_NotifDM(Com_CfgPtr->ipduPtr[loop].pduId);
                    }
                }
            }
            #endif

            /* set I-PDU group start flag */
            Com_SendIpduGroupStartFlag = FALSE;
        }

        if ((IpduGroupId == Com_CfgPtr->receivePduGroupId)
            && (FALSE != Com_ReceiveIpduGroupStartFlag))
        {
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            /* deinit for every I-PDU */
            for (loop = 0u;
                (loop < Com_CfgPtr->ipduUsedNum) && (COM_IPDU_SENT == Com_CfgPtr->ipduPtr[loop].direction);
                loop++)
            {
                if (COM_IPDU_RECEIVE == Com_CfgPtr->ipduPtr[loop].direction)
                {
                    /* deinit I-PDU minimum delay timer and period timer */
                    Com_PrivateIPdu[loop].mdtTimer = 0u;
                    Com_PrivateIPdu[loop].periodTimer = 0u;

                    /* @req COM115 */
                    /* if deadline monitor timer of I-DPU is bigger than 0, deadline monitor notification */
                    if ((TRUE == Com_IpduGroupRepDMEnable) && (Com_PrivateIPdu[loop].DMTimer > 0x00u))
                    {
                        Com_NotifDM(Com_CfgPtr->ipduPtr[loop].pduId);
                    }
                    Com_PrivateIPdu[loop].DMTimer = 0u;
                }
            }
            /* close I-PDU group reception deadline monitor flag */
            Com_IpduGroupRepDMEnable = FALSE;
            #endif
            /* set I-PDU group start flag */
            Com_ReceiveIpduGroupStartFlag = FALSE;
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function shall perform the processing of the AUTOSAR
 *                       COM transmission activities that are not directly initiated
 *                       by the calls from the RTE and PDU-R. A call to Com_MainFunctionTx
 *                       shall simply return if COM was not previously initialized
 *                       with a call to Com_Init.>
 * Service ID            <SERVICE_ID_COM_MAINFUNCTIONTX>
 * Sync/Async            <Asynchronous>
 * Reentrancy            <Non Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <SchM>
 */
/******************************************************************************/
/* @req COM038, @req COM039, @req COM125, @req COM127 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_MainFunctionTx(void)
{
    uint16 ipduloop = 0u;
    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    StatusType ret = E_OK;
    #endif

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_MAINFUNCTIONTX, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        if (TRUE == Com_SendIpduGroupStartFlag)
        {
            for (ipduloop = 0u; ipduloop < Com_CfgPtr->ipduUsedNum; ipduloop++)
            {
                /* only handle for send I-PDU */
                if (COM_IPDU_SENT == (Com_CfgPtr->ipduPtr[ipduloop]).direction)
                {
                    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
                    /* @req COM146 */
                    switch ((Com_CfgPtr->ipduPtr[ipduloop]).transmitMode)
                    {
                        /* @req COM033 */
                        case COM_IPDU_TRANSMIT_PERIODIC:
                            /* call I-PDU periodic transmission handle function */
                            Com_IpduPeriodicTX(&Com_PrivateIPdu[ipduloop], &Com_CfgPtr->ipduPtr[ipduloop]);
                            break;

                        case COM_IPDU_TRANSMIT_DIRECT:
                            /* call I-PDU direct transmission handle function */
                            Com_IpduDirectTX(&Com_PrivateIPdu[ipduloop], &Com_CfgPtr->ipduPtr[ipduloop]);
                            break;

                        /* @req COM034 */
                        case COM_IPDU_TRANSMIT_MIXED:
                            /* call I-PDU mixed transmission handle function */
                            Com_IpduMixedTX(&Com_PrivateIPdu[ipduloop], &Com_CfgPtr->ipduPtr[ipduloop]);
                            break;

                        default:
                            break;
                    }
                    #endif
                }
            }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function shall perform the processing of the AUTOSAR
 *                       COM receive processing that are not directly initiated by
 *                       the calls from the RTE and PDU-R. A call to Com_MainFunctionRx
 *                       shall simply return if COM was not previously initialized
 *                       with a call to Com_Init.>
 * Service ID            <SERVICE_ID_COM_MAINFUNCTIONRX>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Non Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <SchM>
 */
/******************************************************************************/
/* @req COM047, @req COM124 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_MainFunctionRx(void)
{
    uint16 loop = 0u;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    StatusType ret = E_OK;

    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_MAINFUNCTIONRX, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        if  (TRUE == Com_ReceiveIpduGroupStartFlag)
        {
            for (loop = 0u; loop < Com_CfgPtr->ipduUsedNum; loop++)
            {
                /* only handle for receive I-PDU */
                if (COM_IPDU_RECEIVE == (Com_CfgPtr->ipduPtr[loop].direction))
                {
                    #if (STD_OFF == COM_MSGUNPACK_IMMEDIATE)
                    if (TRUE == Com_PrivateIPdu[loop].updateFlag)
                    {
                        /* receive message from I-PDU */
                        Com_MsgReceive(&Com_CfgPtr->ipduPtr[loop],
                                       &Com_PrivateIPdu[loop]);
                        /* update I-PDU reception flag */
                        Com_PrivateIPdu[loop].updateFlag = FALSE;
                    }
                    #endif

                    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
                    Com_RepDMHandle(loop);
                    #endif
                }
            }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is called by the lower layer when an COM
 *                       I-PDU shall be transmitted. Within this function,AUTOSAR
 *                       COM shall copy the contents of its I-PDU transmit buffer
 *                       to the L-PDU buffer given by SduPtr.>
 * Service ID            <SERVICE_ID_COM_TRIGGERTRANSMIT>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different PDU-ID groups,Non Reentrant:same PDU-ID>
 * Param-Name[in]        <ComTxPduId:ID of AUTOSAR COM I-PDU that is requested to
 *                                  be transmitted by AUTOSAR COM.>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <PduInfoPtr: Contains a pointer to a buffer(SduDataPtr) to
 *                       where the SDU shall be copied to.On return,the service will
 *                       indicated the length of the copied SDU data in SduLength.>
 * Return                <E_OK: SDU has been copied and SduLength indicates the
                                number of copied bytes. 
                          E_NOT_OK: No SDU has been copied. SduLength has not been set.>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <LIN/FlexRay>
 */
/******************************************************************************/
/* @req COM196, @req COM196-1 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, COM_CODE)
Com_TriggerTransmit
(
    PduIdType ComTxPduId,
    P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA)PduInfoPtr
)
{
    uint16 ipduIndex = 0x00u;
    Std_ReturnType ret = E_OK;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_TRIGGERTRANSMIT, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
        if ((NULL_PTR == PduInfoPtr) || (NULL_PTR == PduInfoPtr->SduDataPtr))
        {
            /* input pointer is illegal */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_TRIGGERTRANSMIT, E_COM_POINTER);
            ret = E_COM_POINTER;
        }

        if (E_OK == ret)
        {
    #endif
            ipduIndex = Com_FindIpduIndex(ComTxPduId);
    #if (STD_ON == COM_CONFIGURATION_USE_DET)
            if (ipduIndex >= Com_CfgPtr->ipduUsedNum)
            {
                /* I-PDU id is illegal */
                Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_TRIGGERTRANSMIT, E_COM_ID);
                ret = E_COM_ID;
            }
        }
    }

    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        ipduIndex = Com_FindIpduIndex(ComTxPduId);

        SchM_Enter_Com(WRITE_PROTECTION_AREA);
        /* copy I-PDU data from com space to assigned data space */
        Com_Memcpy(PduInfoPtr->SduDataPtr,
                   Com_PrivateIPdu[ipduIndex].dataPtr,
                   PduInfoPtr->SduLength);
        SchM_Exit_Com(WRITE_PROTECTION_AREA);
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                <This function is called by the lower layer after an I-PDU
 *                       has been received.>
 * Service ID            <SERVICE_ID_COM_RXINDICATION>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different PDU-ID groups,Non Reentrant:same PDU-ID>
 * Param-Name[in]        <ComRxPduId:ID of AUTOSAR COM I-PDU that has been received.
 *                                  Identifies the data that has been received.>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <PduR>
 */
/******************************************************************************/
/* @req COM044, @req COM197 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_RxIndication
(
    PduIdType ComRxPduId,
    P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA)PduInfoPtr
)
{
    uint16 ipduIndex = 0x00u;

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    StatusType ret = E_OK;

    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_RXINDICATION, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
    #endif
        ipduIndex = Com_FindIpduIndex(ComRxPduId);
    #if (STD_ON == COM_CONFIGURATION_USE_DET)
        if (ipduIndex >= Com_CfgPtr->ipduUsedNum)
        {
            /* I-PDU id is invalid, DET report */
            Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_RXINDICATION, E_COM_ID);
            ret = E_COM_ID;
        }

        if (E_OK == ret)
        {
            if ((NULL_PTR == PduInfoPtr) || (NULL_PTR == PduInfoPtr->SduDataPtr))
            {
                /* input pointer is invalid, DET report */
                Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_RXINDICATION, E_COM_POINTER);
                ret = E_COM_POINTER;
            }
        }
    }
    /* OSEK COM has been initialized */
    if (E_OK == ret)
    #endif
    {
        if (TRUE == Com_ReceiveIpduGroupStartFlag)
        {
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            /* run I-PDU call-out function */
            if (TRUE == Com_IpduCallout(&Com_CfgPtr->ipduPtr[ipduIndex]))
            #endif
            {
                uint16 copyLength = Com_GetBitToByteSize(Com_CfgPtr->ipduPtr[ipduIndex].sizeInBits);
                
                if (PduInfoPtr->SduLength >= copyLength)
                {
                    SchM_Enter_Com(WRITE_PROTECTION_AREA);
                    /* copy reception I-PDU data */
                    Com_Memcpy(Com_PrivateIPdu[ipduIndex].dataPtr,
                               PduInfoPtr->SduDataPtr,
                               copyLength);
                    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
                    /* reset reception deadline monitor timer */
                    /**@req COM120*/
                    Com_PrivateIPdu[ipduIndex].DMTimer = (Com_CfgPtr->ipduPtr[ipduIndex]).timeOut;
                    #endif
                    SchM_Exit_Com(WRITE_PROTECTION_AREA);

                #if (STD_ON == COM_MSGUNPACK_IMMEDIATE)
                /* receive message from I-PDU */
                Com_MsgReceive(&Com_CfgPtr->ipduPtr[ipduIndex],
                               &Com_PrivateIPdu[ipduIndex]);
                #else
                /* update I-PDU reception flag */
                Com_PrivateIPdu[ipduIndex].updateFlag = TRUE;
                #endif
                }
            }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is called by the lower layer after the PDU
 *                       has been transmitted on the network. A confirmation that
 *                       is received for an I-PDU that does not require a confirmation
 *                       is silently discarded.>
 * Service ID            <SERVICE_ID_COM_TXCONFIRMATION>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different PDU-ID groups,Non Reentrant:same PDU-ID>
 * Param-Name[in]        <ComTxPduId:ID of AUTOSAR COM I-PDU that has been transmitted>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <PduR>
 */
/******************************************************************************/
/* @req COM132, @req COM136, @req COM198 */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE)
Com_TxConfirmation
(
    PduIdType ComTxPduId
)
{
    #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (STD_ON == COM_CONFIGURATION_USE_DET))
    /* get I-PDU index */
    uint16 ipduIndex = 0x00u;
    #endif

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
    StatusType ret = E_OK;

    if (COM_INIT != Com_ModuleStatus)
    {
        /* OSEK COM uninit,DET report */
        Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_TXCONFIRMATION, COM_E_UNINIT);
        ret = COM_E_UNINIT;
    }

    if (E_OK == ret)
    {
    #endif

    #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (STD_ON == COM_CONFIGURATION_USE_DET))
    ipduIndex = Com_FindIpduIndex(ComTxPduId);
    #endif

    #if (STD_ON == COM_CONFIGURATION_USE_DET)
        if (Com_CfgPtr->ipduUsedNum <= ipduIndex)
        {
           /* I-PDU id is invalid, DET report */
           Det_ReportError(COM_MODULE_ID, COM_INSTANCE_ID, SERVICE_ID_COM_TXCONFIRMATION, E_COM_ID);
           ret = E_COM_ID;
        }
    }

   /* OSEK COM has been initialized */
   if (E_OK == ret)
   #endif
   {
       if (TRUE == Com_SendIpduGroupStartFlag)
       {
           #if (OSEK_COM_CCC == OSEK_COM_CCC1)
           /* deadline monitor not expired */
           /* @req COM129 */
           Com_PrivateIPdu[ipduIndex].DMTimer = 0u;
           if (COM_IPDU_TRANSMIT_PERIODIC != Com_CfgPtr->ipduPtr[ipduIndex].transmitMode)
           {
               /* start I-PDU minimum delay timer */
               /** @req COM091, @req COM101,*/
               Com_PrivateIPdu[ipduIndex].mdtTimer = (Com_CfgPtr->ipduPtr[ipduIndex]).minimumDelayTime;
           }
           #endif
           /* call I-PDU transmit confirmation function */
           /* @req COM143, @req COM079 */
           Com_NotifTxConfirm(ComTxPduId);
       }
   }
   return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*=======[I N T E R N A L  F U N C T I O N   I M P L E M E N T A T I O N S]===*/
/******************************************************************************/
/*                                                                            */
/*                          Conformance Classes:  1                           */
/*                                                                            */
/******************************************************************************/
#if (OSEK_COM_CCC == OSEK_COM_CCC1)
/*******************************************************************************/
/*
 * Brief                 <This function is used to deal with  network order call out
 *                       function if configured.>
 * Param-Name[in]        <msgCfgPtr:message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgSendDynamicExternel, Com_MsgRecDynamicExternal,
 *                       Com_InitValSendStaticExternal, Com_MsgSendStaticExternal,
 *                       Com_MsgRecStaticExternal, Com_MsgSendZeroExternal,
 *                       Com_MsgRecZeroExternal.>
 */
/******************************************************************************/
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_NWOrderCallout
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    boolean ret = TRUE;

    if (msgCfgPtr->netWorkOrderCallout != NULL_PTR)
    {
        /* call network order call out function configured in configuration */
        ret = msgCfgPtr->netWorkOrderCallout();
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to deal with I-PDU order call out
 *                       function if configured.>
 * Param-Name[in]        <ipduCfgPtr: I-PDU configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_IpduPeriodicTX, Com_IpduDirectTX,
 *                       Com_IpduMixedTX, Com_SendIpdu>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_IpduCallout
(
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
)
{
    boolean ret = TRUE;

    if (ipduCfgPtr->ipduCallOut != NULL_PTR)
    {
        /* call I-PDU order call out function configured in configuration */
        ret = ipduCfgPtr->ipduCallOut();
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to deal with  CPU order call out
 *                       function if configured.>
 * Param-Name[in]        <msgCfgPtr:message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgSendDynamicExternel, Com_MsgRecDynamicExternal,
 *                       Com_InitValSendStaticExternal, Com_MsgSendStaticExternal,
 *                       Com_MsgRecStaticExternal, Com_MsgSendZeroExternal,
 *                       Com_MsgRecZeroExternal>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_CPUOrderCallout
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    boolean ret = TRUE;

    if (msgCfgPtr->cpuOrderCallout != NULL_PTR)
    {
        /* call CPU order call out function configured in configuration */
        ret = msgCfgPtr->cpuOrderCallout();
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to convert 8 bits/16bits/32bits
 *                       data to unsigned 32 bits data.>
 * Param-Name[in]        <dataType : data type which would be converted
 *                        dataPtr  : data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <uint32 : converted data>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter, Com_InitMsgRecUnQueuedInternal,
 *                       Com_InitMsgRecQueuedInternal, Com_InitMsgRecQueuedExternal,
 *                       Com_InitMsgRecUnQueuedExternal, Com_InitValRecUnQueuedInternal,
 *                       Com_InitValRecUnQueuedExternal, Com_InitValSendStaticExternal >
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint32, COM_CODE)
Com_InitValueToU32
(
    const Com_MsgCDataType dataType,
    P2CONST(void, AUTOMATIC, AUTOMATIC)dataPtr
)
{
    uint32 u32Value = 0x00uL;

    switch(dataType)
    {
        case COM_MSG_BOOLEAN:
        case COM_MSG_UINT8:
            u32Value = (uint32)(*(uint8*)dataPtr);
            break;

        case COM_MSG_UINT16:
            u32Value = (uint32)(*(uint16 *)dataPtr);
            break;

        case COM_MSG_UINT32:
        case COM_MSG_SINT32:
            u32Value = *(uint32 *)dataPtr;
            break;

        case COM_MSG_SINT8:
            u32Value = (uint32)((sint32)(*(sint8 *)dataPtr));
            break;

        case COM_MSG_SINT16:
            u32Value = (uint32)((sint32)(*(sint16 *)dataPtr));
            break;
        default:
            break;
    }
    return u32Value;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM compares the new message value to the last sent
 *                       message value and only transfers(receives) the message
 *                       if the filtering condition is met. All other message
 *                       values are discarded.>
 * Param-Name[in]        <msgDataPtr : message data pointer which point to filter data
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer >
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgSendStaticInternal, Com_MsgSendStaticExternal,
 *                       Com_MsgRecStaticExternal, Com_MsgRecStaticLink>
 */
/******************************************************************************/
/* @req COM109 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_Filter
(
    P2CONST(void, AUTOMATIC, AUTOMATIC)msgDataPtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret;
    uint32 newValue = Com_InitValueToU32(msgCfgPtr->cData,msgDataPtr);

    switch(msgCfgPtr->filterPtr->filterAlgorithm)
    {
        /* No filtering is performed so that the message always passes */
        case COM_F_Always:
            msgPrivatePtr->msgOldValue = newValue;
            ret = TRUE;
            break;

        /* The filter removes all messages */
        case COM_F_Never:
            ret = FALSE;
            break;
        
        /* Pass messages whose masked value is equal to a specific value*/    
        case COM_F_MaskedNewEqualsX:
            ret = Com_FMaskedNewEqualsX(newValue,msgCfgPtr,msgPrivatePtr);
            break;

        /* Pass messages whose masked value is not equal to a specific value */
        case COM_F_MaskedNewDiffersX:
            ret = Com_FMaskedNewDiffersX(newValue,msgCfgPtr,msgPrivatePtr);
            break;

        /* Pass messages which have not changed */
        case COM_F_NewIsEqual:
            ret = Com_FNewIsEqual(newValue,msgPrivatePtr);
            break;

        /* Pass messages which have changed */
        case COM_F_NewIsDifferent:
            ret = Com_FNewIsDifferent(newValue,msgPrivatePtr);
            break;

        /* Pass messages where the masked value has not changed */
        case COM_F_MaskedNewEqualsMaskedOld:
            ret = Com_FMaskedNewEqualsMaskedOld(newValue,msgCfgPtr,msgPrivatePtr);
            break;

        /* Pass messages where the masked value has changed */
        case COM_F_MaskedNewDiffersMaskedOld:
            ret = Com_FMaskedNewDiffersMaskedOld(newValue,msgCfgPtr,msgPrivatePtr);
            break;

        /* Pass a message if its value is within a predefined boundary */
        case COM_F_NewIsWithin:
            ret = Com_FNewIsWithin(newValue,msgCfgPtr,msgPrivatePtr);
            break;

        /* Pass a message if its value is outside a predefined boundary */
        case COM_F_NewIsOutside:
            ret = Com_FNewIsOutside(newValue,msgCfgPtr,msgPrivatePtr);
            break;
        
        /* Pass a message if its value has increased */
        case COM_F_NewIsGreater:
            ret = Com_FNewIsGreater(newValue,msgCfgPtr,msgPrivatePtr);
            break;
        
        /* Pass a message if its value has not increased */
        case COM_F_NewIsLessOrEqual:
            ret = Com_FNewIsLessOrEqual(newValue,msgCfgPtr,msgPrivatePtr);
            break;
        
        /* Pass a message if its value has decreased */
        case COM_F_NewIsLess:
            ret = Com_FNewIsLess(newValue,msgCfgPtr,msgPrivatePtr);
            break;
        
        /* Pass a message if its value has not decreased */
        case COM_F_NewIsGreaterOrEqual:
            ret = Com_FNewIsGreaterOrEqual(newValue,msgCfgPtr,msgPrivatePtr);
            break;
        
        /* Pass a message once every N message occurrences */
        case COM_F_OneEveryN:
            ret = Com_FOneEveryN(newValue,msgCfgPtr,msgPrivatePtr);
            break;
        
        /* invalid filter algorithm */
        default:
            ret = FALSE;
            break;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass messages whose masked value is equal
 *                       to a specific value >
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                        msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FMaskedNewEqualsX
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* (new_value & mask) == x */
    if ((msgCfgPtr->filterPtr->filterMask & newMsg) == msgCfgPtr->filterPtr->filterX)
    {
        msgPrivatePtr->msgOldValue = newMsg;
        ret = TRUE;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass messages whose masked value is not
 *                       equal to a specific value>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FMaskedNewDiffersX
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* (new_value & mask) != x */
    if ((msgCfgPtr->filterPtr->filterMask & newMsg) != msgCfgPtr->filterPtr->filterX)
    {
        msgPrivatePtr->msgOldValue = newMsg;
        ret = TRUE;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass messages which have not changed>
 * Param-Name[in]        <newMsg : message data which would be filtered>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsEqual
(
    const uint32 newMsg,
    P2CONST(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* new_value == old_value */
    if (newMsg == msgPrivatePtr->msgOldValue)
    {
        ret = TRUE;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass messages which have changed >
 * Param-Name[in]        <newMsg : message data which would be filtered>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsDifferent
(
    const uint32 newMsg,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* new_value != old_value */
    if (newMsg != msgPrivatePtr->msgOldValue)
    {
        msgPrivatePtr->msgOldValue = newMsg;
        ret = TRUE;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass messages where the masked value has
 *                       not changed>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer >
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FMaskedNewEqualsMaskedOld
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
 )
{
    boolean ret = FALSE;

    /* (new_value&mask) == (old_value&mask) */
    if ((msgCfgPtr->filterPtr->filterMask & newMsg) 
       == (msgCfgPtr->filterPtr->filterMask & msgPrivatePtr->msgOldValue))
    {
        msgPrivatePtr->msgOldValue = newMsg;
        ret = TRUE;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass messages where the masked value has
 *                       changed>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FMaskedNewDiffersMaskedOld
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* (new_value&mask) != (old_value&mask) */
    if ((msgCfgPtr->filterPtr->filterMask & newMsg)
        != (msgCfgPtr->filterPtr->filterMask & msgPrivatePtr->msgOldValue))
    {
        msgPrivatePtr->msgOldValue = newMsg;
        ret = TRUE;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass a message if its value is within a
 *                       predefined boundary>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsWithin
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* min <= new_value <= max */
    if ((COM_MSG_SINT8 == msgCfgPtr->cData)
       || (COM_MSG_SINT16 == msgCfgPtr->cData)
       || (COM_MSG_SINT32 == msgCfgPtr->cData))
    {
        if (((sint32)newMsg <= (sint32)msgCfgPtr->filterPtr->filterMax)
            && ((sint32)newMsg >= (sint32)msgCfgPtr->filterPtr->filterMin))
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    else
    {
        if ((newMsg <= msgCfgPtr->filterPtr->filterMax)
            && (newMsg >= msgCfgPtr->filterPtr->filterMin))
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass a message if its value is outside a
 *                       predefined boundary>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsOutside
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* (min > new_value) OR (new_value > max) */
    if ((COM_MSG_SINT8 == msgCfgPtr->cData)
       || (COM_MSG_SINT16 == msgCfgPtr->cData)
       || (COM_MSG_SINT32 == msgCfgPtr->cData))
    {
        if (((sint32)newMsg > (sint32)msgCfgPtr->filterPtr->filterMax)
           || ((sint32)newMsg < (sint32)msgCfgPtr->filterPtr->filterMin))
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    else
    {
        if ((newMsg > msgCfgPtr->filterPtr->filterMax)
           || (newMsg < msgCfgPtr->filterPtr->filterMin))
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass a message if its value has increased>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsGreater
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* new_value > old_value */
    if ((COM_MSG_SINT8 == msgCfgPtr->cData)
       || (COM_MSG_SINT16 == msgCfgPtr->cData)
       || (COM_MSG_SINT32 == msgCfgPtr->cData))
    {
        if ((sint32)newMsg > (sint32)msgPrivatePtr->msgOldValue)
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    else
    {
        if (newMsg > msgPrivatePtr->msgOldValue)
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass a message if its value has not increased>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsLessOrEqual
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* new_value <= old_value */
    if ((COM_MSG_SINT8 == msgCfgPtr->cData)
       || (COM_MSG_SINT16 == msgCfgPtr->cData)
       || (COM_MSG_SINT32 == msgCfgPtr->cData))
    {
        if ((sint32)newMsg <= (sint32)msgPrivatePtr->msgOldValue)
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    else
    {
        if (newMsg <= msgPrivatePtr->msgOldValue)
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass a message if its value has decreased>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsLess
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
 )
{
    boolean ret = FALSE;

    /* new_value < old_value */
    if ((COM_MSG_SINT8 == msgCfgPtr->cData)
       || (COM_MSG_SINT16 == msgCfgPtr->cData)
       || (COM_MSG_SINT32 == msgCfgPtr->cData))
    {
        if ((sint32)newMsg < (sint32)msgPrivatePtr->msgOldValue)
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    else
    {
        if (newMsg < msgPrivatePtr->msgOldValue)
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <OSEK COM would pass a message if its value has not decreased>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FNewIsGreaterOrEqual
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean ret = FALSE;

    /* new_value >= old_value */
    if ((COM_MSG_SINT8 == msgCfgPtr->cData)
       || (COM_MSG_SINT16 == msgCfgPtr->cData)
       || (COM_MSG_SINT32 == msgCfgPtr->cData))
    {
        if ((sint32)newMsg >= (sint32)msgPrivatePtr->msgOldValue)
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    else
    {
        if (newMsg >= msgPrivatePtr->msgOldValue)
        {
            msgPrivatePtr->msgOldValue = newMsg;
            ret = TRUE;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                       
 * Brief                 <OSEK COM would pass a message once every N message
 *                       occurrences.>
 * Param-Name[in]        <newMsg : message data which would be filtered
 *                       msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Filter>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_FOneEveryN
(
    const uint32 newMsg,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
 )
{
    boolean ret = FALSE;
    uint32 curOffset;
    curOffset = msgPrivatePtr->occurrence % msgCfgPtr->filterPtr->filterPeriodFactor;

    /* occurrence % period == offset */
    if (curOffset == msgCfgPtr->filterPtr->filterOffset)
    {
        msgPrivatePtr->msgOldValue = newMsg;
        ret = TRUE;
    }

    if (msgCfgPtr->filterPtr->filterPeriodFactor == msgPrivatePtr->occurrence)
    {
        msgPrivatePtr->occurrence = 0u;
    }
    msgPrivatePtr->occurrence += 0x01u;
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to handle periodic I-PDU transmission.>
 * Param-Name[in]        <ipduCfgPtr : I-PDU configuration pointer
 *                       ipduPrivatePtr : I-PDU run time structure pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MainFunctionTx>
 */
/******************************************************************************/
/* @req COM093 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduPeriodicTX
(
    P2VAR(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)ipduPrivatePtr,
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
)
{
    PduInfoType pduInfo = {NULL_PTR, 0u};

    /* decrease deadline monitor timer */
    /* @req COM133 */
    if (0u < ipduPrivatePtr->DMTimer)
    {
        ipduPrivatePtr->DMTimer--;

        /* deadline timer expired, notification */
        if (0u == ipduPrivatePtr->DMTimer)
        {
            /* @req COM145,@req COM134 */
            Com_NotifDM(ipduCfgPtr->pduId);
        }
    }

    /* handle period Timer */
    if (0u < ipduPrivatePtr->periodTimer)
    {
        ipduPrivatePtr->periodTimer--;

        if (0u == ipduPrivatePtr->periodTimer)
        {
             /* reset period timer */
             ipduPrivatePtr->periodTimer = ipduCfgPtr->timePeriod / Com_CfgPtr->timeBase;

             /* @req COM131, @req COM135 */
             /* for transmission, reset DM timer only when DM timer is 0 */
             if (0u == ipduPrivatePtr->DMTimer)
             {
                 ipduPrivatePtr->DMTimer = ipduCfgPtr->timeOut / Com_CfgPtr->timeBase;
             }

             /* @req COM195-1 */
             /* transmission only when I-PDU callout return true */
             if (TRUE == Com_IpduCallout(ipduCfgPtr))
             {
                 pduInfo.SduLength = Com_GetBitToByteSize(ipduCfgPtr->sizeInBits);
                 pduInfo.SduDataPtr = ipduPrivatePtr->dataPtr;
                 /* @req COM003 */
                 (void)PduR_ComTransmit(ipduCfgPtr->pduId, &pduInfo);
             }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to handle direct I-PDU transmission.>
 * Param-Name[in]        <ipduCfgPtr : I-PDU configuration pointer
 *                       ipduPrivatePtr : I-PDU run time structure pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MainFunctionTx>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduDirectTX
(
    P2VAR(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)ipduPrivatePtr,
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
)
{
    /* decrease deadline timer */
    if (0u < ipduPrivatePtr->DMTimer)
    {
        ipduPrivatePtr->DMTimer--;

        /* deadline timer expired, notification */
        /* @req COM130 */
        if (0u == ipduPrivatePtr->DMTimer)
        {
            /* @req COM137 */
            Com_NotifDM(ipduCfgPtr->pduId);
        }
    }
    /* decrease minimum delay timer */
    if (0u < ipduPrivatePtr->mdtTimer)
    {
        ipduPrivatePtr->mdtTimer--;
    }

    /* exist direct send I-PDU */
    if (TRUE == ipduPrivatePtr->directSend)
    {
        Com_SendIpdu(ipduCfgPtr);
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to handle mixed I-PDU transmission.>
 * Param-Name[in]        <ipduCfgPtr : I-PDU configuration pointer
 *                       ipduPrivatePtr : I-PDU run time structure pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MainFunctionTx>
 */
/******************************************************************************/
/* @req COM096, @req COM097, @req COM098, @req COM099, @req COM102, @req COM103 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduMixedTX
(
    P2VAR(Com_IPduRunTimeType, AUTOMATIC, CODE_VAR)ipduPrivatePtr,
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
)
{
    PduInfoType pduInfo = {NULL_PTR, 0u};

    /* decrease deadline timer */
    if (0u < ipduPrivatePtr->DMTimer)
    {
        ipduPrivatePtr->DMTimer--;

        /* deadline timer expired, notification */
        if (0u == ipduPrivatePtr->DMTimer)
        {
            Com_NotifDM(ipduCfgPtr->pduId);
        }
    }
    /* decrease minimum delay timer */
    if (0u < ipduPrivatePtr->mdtTimer)
    {
        ipduPrivatePtr->mdtTimer--;
    }

    /* handle period Timer */
    if (0u < ipduPrivatePtr->periodTimer)
    {
        ipduPrivatePtr->periodTimer--;

        if (0u == ipduPrivatePtr->periodTimer)
        {
            /* reset period Timer */
            ipduPrivatePtr->periodTimer = ipduCfgPtr->timePeriod / Com_CfgPtr->timeBase;

            /* @req COM100 */
            if (0u == ipduPrivatePtr->mdtTimer)
            {
                /* @req COM135 */
                /* for transmission, reset DM timer only when DM timer is 0 */
                if (0u == ipduPrivatePtr->DMTimer)
                {
                     ipduPrivatePtr->DMTimer = ipduCfgPtr->timeOut / Com_CfgPtr->timeBase;
                }

                /* transmission only when I-PDU callout return true */
                if (TRUE == Com_IpduCallout(ipduCfgPtr))
                {
                    /* periodic transmission */
                    pduInfo.SduLength = Com_GetBitToByteSize(ipduCfgPtr->sizeInBits);
                    pduInfo.SduDataPtr = ipduPrivatePtr->dataPtr;
                    /* @req COM003 */
                    (void)PduR_ComTransmit(ipduCfgPtr->pduId, &pduInfo);
                }
            }
            else
            {
                /* set transmission flag */
                ipduPrivatePtr->directSend = TRUE;
            }
        }
        else
        {
            if (TRUE == ipduPrivatePtr->directSend)
            {
                Com_SendIpdu(ipduCfgPtr);
            }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to find dynamic message minimum bit
 *                       position.>
 * Param-Name[in]        <NWMsgCfgPtr : network message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <uint32: minimum bit position>
 * PreCondition          <None>
 * CallByAPI             <Com_CopyBit>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint32, COM_CODE)
Com_FindDynamicMsgMinBit
(
    P2CONST(Com_NWMsgType, AUTOMATIC, COM_CONST_PBCFG)NWMsgCfgPtr
)
{
    uint16 msgIndex = 0;
    uint32 dynamicMinBitPos = 0xFFFFFFFFuL;

    if (COM_MSG_STATIC == NWMsgCfgPtr->msgClass)
    {
        while(msgIndex < Com_CfgPtr->msgUsedNum)
        {
            if ((Com_CfgPtr->messagePtr[msgIndex].NWMsgPtr != NULL_PTR)
                && (COM_MSG_DYNAMIC == Com_CfgPtr->messagePtr[msgIndex].NWMsgPtr->msgClass)
                && (Com_CfgPtr->messagePtr[msgIndex].NWMsgPtr->ipduPtr->pduId 
                    == NWMsgCfgPtr->ipduPtr->pduId))
            {
                dynamicMinBitPos = Com_CfgPtr->messagePtr[msgIndex].NWMsgPtr->bitPosition;
                break;
            }
            else
            {
                msgIndex++;
            }
        }
    }
    return dynamicMinBitPos;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize dynamic receive message.>
 * Param-Name[in]        <msgCfgPtr : dynamic receive message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsg>
 */
/******************************************************************************/
/* @req COM111 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecDynamicExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;
    uint16 msgLength;

    /* get dynamic message byte length */
    if ((msgCfgPtr->NWMsgPtr != NULL_PTR)
        && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR)
        && (msgCfgPtr->NWMsgPtr->maximumSizeInBits != 0x00u)
        && (COM_MSG_DYNAMIC == msgCfgPtr->NWMsgPtr->msgClass)
        && (COM_MSG_RECEIVED == msgCfgPtr->NWMsgPtr->direction)
        && (COM_IPDU_RECEIVE == msgCfgPtr->NWMsgPtr->ipduPtr->direction))
    {
        msgLength = Com_GetBitToByteSize(msgCfgPtr->NWMsgPtr->maximumSizeInBits);
    }
    else if ((msgCfgPtr->linkMsgPtr != NULL_PTR)
             && (msgCfgPtr->linkMsgPtr->NWMsgPtr != NULL_PTR)
             && (COM_MSG_RECEIVE_DYNAMIC_EXTERNAL == msgCfgPtr->linkMsgPtr->property))
    {
        msgLength = Com_GetBitToByteSize(msgCfgPtr->linkMsgPtr->NWMsgPtr->maximumSizeInBits);
    }
    else
    {
        ret = E_COM_ID;
    }

    if (E_OK == ret)
    {
        /* apply message buffer */  
        msgPrivatePtr->queue.bufPtr = (uint8*)Com_Malloc(msgLength);
        
        /* copy init value to message buffer */
        if (msgPrivatePtr->queue.bufPtr != NULL_PTR)
        {
            SchM_Enter_Com(WRITE_PROTECTION_AREA);
            Com_Memcpy(msgPrivatePtr->queue.bufPtr,
                       msgCfgPtr->initialValue,
                       msgLength);
            SchM_Exit_Com(WRITE_PROTECTION_AREA);
        }
        else
        {
            ret = E_COM_LENGTH;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize dynamic send message.>
 * Param-Name[in]        <msgCfgPtr : dynamic receive message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer >
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsg>
 */
/******************************************************************************/
/* @req COM054 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgSendDynamicExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;

    if ((msgCfgPtr->NWMsgPtr != NULL_PTR)
        && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR)
        && (msgCfgPtr->NWMsgPtr->maximumSizeInBits != 0x00uL)
        && (COM_MSG_DYNAMIC == msgCfgPtr->NWMsgPtr->msgClass)
        && (COM_MSG_SENT == msgCfgPtr->NWMsgPtr->direction)
        && (COM_IPDU_SENT == msgCfgPtr->NWMsgPtr->ipduPtr->direction))
    {
        msgPrivatePtr->queue.bufPtr = NULL_PTR;
        Com_InitValSendDynamicExternal(msgCfgPtr,
                                       (const void *)msgCfgPtr->initialValue,
                                       FALSE);
    }
    else
    {
        ret = E_COM_ID;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize dynamic receive message value.>
 * Param-Name[in]        <msgCfgPtr : dynamic receive message configuration pointer
 *                       appDataRef : application data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsg>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValRecDynamicExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
)
{
    /* assign externel receive message initial value */
    uint16 msgLength;

    if (msgCfgPtr->NWMsgPtr != NULL_PTR)
    {
        msgLength = Com_GetBitToByteSize(msgCfgPtr->NWMsgPtr->maximumSizeInBits);
    }
    else
    {
        msgLength = Com_GetBitToByteSize(msgCfgPtr->linkMsgPtr->NWMsgPtr->maximumSizeInBits);
    }
    SchM_Enter_Com(WRITE_PROTECTION_AREA);
    Com_Memcpy(msgPrivatePtr->queue.bufPtr,
               (const uint8 *)appDataRef,
               msgLength);
    SchM_Exit_Com(WRITE_PROTECTION_AREA);
    
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize dynamic send message value.>
 * Param-Name[in]        <msgCfgPtr : dynamic receive message configuration pointer
 *                       appDataRef : application data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsg>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValSendDynamicExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef,
    boolean initFinished
)
{
    /* assign external send message initial value to Ipdu */
    uint16 ipduIndex;
    boolean processCondition = TRUE;

    if (TRUE == initFinished)
    {
        processCondition = Com_CPUOrderCallout(msgCfgPtr);

        if (TRUE == processCondition)
        {
            processCondition = Com_NWOrderCallout(msgCfgPtr);
        }
    }

    if (TRUE == processCondition)
    {
        ipduIndex = Com_FindIpduIndex(msgCfgPtr->NWMsgPtr->ipduPtr->pduId);

        /* copy initial message value to Ipdu */
        SchM_Enter_Com(WRITE_PROTECTION_AREA);
        Com_CopyBit(msgCfgPtr,
                    (const uint8 *)appDataRef,
                    Com_PrivateIPdu[ipduIndex].dataPtr,
                    msgCfgPtr->NWMsgPtr->maximumSizeInBits);
        SchM_Exit_Com(WRITE_PROTECTION_AREA);
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize dynamic send message value.>
 * Param-Name[in]        <msgCfgPtr : dynamic receive message configuration pointer
 *                       appDataRef : application data pointer
 *                       length : data length that dynamic message would to initialize >
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : send successfully>
 * PreCondition          <None>
 * CallByAPI             <Com_SendDynamicMessage>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendDynamicExternel
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataPtr,
    const uint16 length
)
{
    if (TRUE == Com_CPUOrderCallout(msgCfgPtr))
    {
        if (TRUE == Com_NWOrderCallout(msgCfgPtr))
        {
            uint32 copyBitNum = (uint32)length * 0x8u;
            uint16 ipduIndex = Com_FindIpduIndex(msgCfgPtr->NWMsgPtr->ipduPtr->pduId);

            if (copyBitNum > msgCfgPtr->NWMsgPtr->maximumSizeInBits)
            {
                copyBitNum = msgCfgPtr->NWMsgPtr->maximumSizeInBits;
            }
            SchM_Enter_Com(WRITE_PROTECTION_AREA);
            /* copy message to Ipdu */
            Com_CopyBit(msgCfgPtr,
                        (const uint8 *)appDataPtr,
                        Com_PrivateIPdu[ipduIndex].dataPtr,
                        copyBitNum);
            SchM_Exit_Com(WRITE_PROTECTION_AREA);
            
            if (COM_MSG_TRIGGERED == msgCfgPtr->transferProperty)
            {
                Com_SendIpdu(msgCfgPtr->NWMsgPtr->ipduPtr);
            }
        }
    }
    return E_OK;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to unpack dynamic message from I-PDU.>
 * Param-Name[in]        <msgCfgPtr : dynamic receive message configuration pointer
 *                       iPduPrivatePtr : I-PDU run time structure pointer
 *                       msgPrivatePtr : message run time structure pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgReceive>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecDynamicExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)iPduPrivatePtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    if (TRUE == Com_CPUOrderCallout(msgCfgPtr))
    {
        if (TRUE == Com_NWOrderCallout(msgCfgPtr))
        {
            SchM_Enter_Com(WRITE_PROTECTION_AREA);
            /* copy message to Ipdu */
            Com_CopyBit(msgCfgPtr,
                        (const uint8 *)iPduPrivatePtr->dataPtr,
                        msgPrivatePtr->queue.bufPtr,
                        msgCfgPtr->NWMsgPtr->maximumSizeInBits);
            SchM_Exit_Com(WRITE_PROTECTION_AREA);

            /* external zero message receive notification */
            if (msgCfgPtr->msgNotif != NULL_PTR)
            {
                msgCfgPtr->msgNotif();
            }
            Com_MsgRecDynamicLink(msgCfgPtr,msgPrivatePtr);
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to unpack dynamic link message from I-PDU.>
 * Param-Name[in]        <msgCfgPtr : receive message configuration pointer
 *                       msgPrivatePtr : message run time structure pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgRecDynamicExternal>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecDynamicLink
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    uint16 msgIndex;
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgLinkCfgPtr;

    for(msgIndex = 0;
        msgIndex < Com_CfgPtr->msgUsedNum;
        msgIndex++)
    {
        msgLinkCfgPtr = &Com_CfgPtr->messagePtr[msgIndex];

        if (msgLinkCfgPtr->linkMsgPtr == msgCfgPtr)
        {
            uint16 msgLength = Com_GetBitToByteSize(msgCfgPtr->NWMsgPtr->maximumSizeInBits);
            /* link dynamic message is received */
            SchM_Enter_Com(WRITE_PROTECTION_AREA);
            Com_Memcpy((uint8 * )Com_PrivateMsg[msgIndex].queue.bufPtr,
                    (const uint8 *)msgPrivatePtr->queue.bufPtr,
                    msgLength);
            SchM_Exit_Com(WRITE_PROTECTION_AREA);
            
            /* external zero msg receive notification */
            if (msgLinkCfgPtr->msgNotif != NULL_PTR)
            {
                msgLinkCfgPtr->msgNotif();
            }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize static external
 *                       queued received message.>
 * Param-Name[in]        <msgPrivatePtr : static internal queued receive
 *                                       message run time structure.
 *                       msgCfgPtr : static internal queued receive message
 *                                   configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : initialize successfully
 *                       E_COM_LENGTH : buffer not enough
 *                       E_COM_ID : configuration error>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsg>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecQueuedExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;
    uint16 msgLength = 0x00u;
    P2CONST(Com_NWMsgType, AUTOMATIC, COM_CONST_PBCFG)curNWMsgPtr;

    if ((msgCfgPtr->NWMsgPtr != NULL_PTR)
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        && (msgCfgPtr->filterPtr != NULL_PTR)
        #endif
        && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR)
        && (msgCfgPtr->NWMsgPtr->sizeInBits != 0x00u)
        && (COM_MSG_STATIC == msgCfgPtr->NWMsgPtr->msgClass)
        && (COM_MSG_RECEIVED == msgCfgPtr->NWMsgPtr->direction)
        && (COM_IPDU_RECEIVE == msgCfgPtr->NWMsgPtr->ipduPtr->direction))
    {
        curNWMsgPtr = msgCfgPtr->NWMsgPtr;
    }
    else if ((msgCfgPtr->linkMsgPtr != NULL_PTR)
             #if (OSEK_COM_CCC == OSEK_COM_CCC1)
             && (msgCfgPtr->filterPtr != NULL_PTR)
             #endif
             && (msgCfgPtr->linkMsgPtr->NWMsgPtr != NULL_PTR)
             && ((COM_MSG_RECEIVE_UNQUEUED_EXTERNAL == msgCfgPtr->linkMsgPtr->property)
             || (COM_MSG_RECEIVE_QUEUED_EXTERNAL == msgCfgPtr->linkMsgPtr->property)))
    {
        curNWMsgPtr = msgCfgPtr->linkMsgPtr->NWMsgPtr;
    }
    else
    {
        ret = E_COM_ID;
    }
    if (E_OK == ret)
    {
        msgLength = Com_GetStaticExternelMsgLength(msgCfgPtr);
        if (COM_MSG_UNSIGNEDINTEGER == curNWMsgPtr->dataInterpretation)
        {
            msgPrivatePtr->msgOldValue = Com_InitValueToU32(msgCfgPtr->cData,
                                                            (const void *)msgCfgPtr->initialValue);
        }
        msgPrivatePtr->occurrence = 0u;
        msgPrivatePtr->messageStatus = E_COM_NOMSG;
        msgPrivatePtr->queue.bufPtr = (uint8*)Com_Malloc(msgLength * (uint16)msgCfgPtr->queueSize);
        if (msgPrivatePtr->queue.bufPtr != NULL_PTR)
        {
            msgPrivatePtr->queue.depth = (uint8)msgCfgPtr->queueSize;
            msgPrivatePtr->queue.length = (uint8)msgLength;
            Queue_BufferFlush(&msgPrivatePtr->queue);
        }
        else
        {
            ret = E_COM_LENGTH;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to call message notification.>
 * Param-Name[in]        <configPtr : COM configuration data pointer
 *                       u4PduId : confirmation I-PDU id>
 *                       <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MainFunctionTx, Com_MainFunctionRx>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_NotifDM
(
    const uint32 u4PduId
)
{
    uint16 msgIndex;

    for(msgIndex = 0;
        (msgIndex < Com_CfgPtr->msgUsedNum);
        msgIndex++)
    {
        const Com_MsgType *msgCfgPtr = &Com_CfgPtr->messagePtr[msgIndex];
        if ((msgCfgPtr->NWMsgPtr != NULL_PTR) 
            && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR) 
            && (msgCfgPtr->NWMsgPtr->ipduPtr->pduId == u4PduId))
        {
            /* @req COM010 */
            if (msgCfgPtr->DMNotif != NULL_PTR)
            {
                /* @req COM009 */
                msgCfgPtr->DMNotif();
            }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to initialize zero-length receive
 *                       internal message.>
 * Param-Name[in]        <msgCfgPtr : message configuration data pointer >
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_SendZeroMessage>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecZeroInternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;

    if ((msgCfgPtr->sendMsgPtr != NULL_PTR)
        && ((COM_MSG_SEND_ZERO_INTERNAL == msgCfgPtr->sendMsgPtr->property)
        || (COM_MSG_SEND_ZERO_EXTERNAL == msgCfgPtr->sendMsgPtr->property)))
    {
        msgPrivatePtr->queue.bufPtr = NULL_PTR;
    }
    else
    {
        ret = E_COM_ID;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                  <This function is used to initialize zero-length receive
 *                       external message.>
 * Param-Name[in]        <msgCfgPtr : message configuration data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_SendZeroMessage>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecZeroExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;

    if ((msgCfgPtr->NWMsgPtr != NULL_PTR)
        && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR)
        && (COM_MSG_ZERO == msgCfgPtr->NWMsgPtr->msgClass)
        && (COM_MSG_RECEIVED == msgCfgPtr->NWMsgPtr->direction)
        && (COM_IPDU_RECEIVE == msgCfgPtr->NWMsgPtr->ipduPtr->direction))
    {
        msgPrivatePtr->queue.bufPtr = NULL_PTR;
    }
    else
    {
        ret = E_COM_ID;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to initialize zero-length send
 *                       external message. >
 * Param-Name[in]        <msgCfgPtr : message configuration data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_SendZeroMessage>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgSendZeroExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;

    if ((msgCfgPtr->NWMsgPtr != NULL_PTR)
        && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR)
        && (COM_MSG_ZERO == msgCfgPtr->NWMsgPtr->msgClass)
        && (COM_MSG_SENT== msgCfgPtr->NWMsgPtr->direction)
        && (COM_IPDU_SENT == msgCfgPtr->NWMsgPtr->ipduPtr->direction))
    {
        msgPrivatePtr->queue.bufPtr = NULL_PTR;
    }
    else
    {
        ret = E_COM_ID;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to handle zero-length send
 *                       internal message.>
 * Param-Name[in]        <msgCfgPtr : message configuration data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_SendZeroMessage>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendZeroInternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    uint16 msgIndex = 0u;
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgRecCfgPtr;

    for (msgIndex = 0u;
        msgIndex < Com_CfgPtr->msgUsedNum;
        msgIndex++)
    {
        msgRecCfgPtr = &Com_CfgPtr->messagePtr[msgIndex];
        if (msgRecCfgPtr->sendMsgPtr == msgCfgPtr)
        {
            /* internal zero msg receive notification */
            /* @req COM006, @req COM007,@req COM059 */
            if (msgRecCfgPtr->msgNotif != NULL_PTR)
            {
                msgRecCfgPtr->msgNotif();
            }
        }
    }
    return E_OK;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to handle zero-length send
 *                       external message. >
 * Param-Name[in]        <msgCfgPtr : message configuration data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_SendZeroMessage>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendZeroExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    if (TRUE == Com_CPUOrderCallout(msgCfgPtr))
    {
        if (TRUE == Com_NWOrderCallout(msgCfgPtr))
        {
            if (COM_MSG_TRIGGERED == msgCfgPtr->transferProperty)
            {
                /* @req COM006, @req COM008 */
                Com_SendIpdu(msgCfgPtr->NWMsgPtr->ipduPtr);
            }
        }
    }
    return E_OK;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to handle zero-length received
 *                       external message. >
 * Param-Name[in]        <iPduCfgPtr : I-PDU configuration data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgReceive>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecZeroExternal
(
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)iPduCfgPtr
)
{
    uint16 msgIndex;
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr;

    for(msgIndex = 0;
        msgIndex < Com_CfgPtr->msgUsedNum;
        msgIndex++)
    {
        msgCfgPtr = &Com_CfgPtr->messagePtr[msgIndex];

        /* find zero message in ipdu */
        if ((COM_MSG_RECEIVE_ZERO_EXTERNAL == msgCfgPtr->property)
             && (msgCfgPtr->NWMsgPtr != NULL_PTR)
             && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR)
             && (msgCfgPtr->NWMsgPtr->ipduPtr->pduId == iPduCfgPtr->pduId))
        {
            if (TRUE == Com_NWOrderCallout(msgCfgPtr))
            {
                if (TRUE == Com_CPUOrderCallout(msgCfgPtr))
                {
                    /* external zero message receive notification */
                    if (msgCfgPtr->msgNotif != NULL_PTR)
                    {
                        msgCfgPtr->msgNotif();
                    }
                }
            }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/******************************************************************************/
/*                                                                            */
/*                        Conformance Classes:  1/0                           */
/*                                                                            */
/******************************************************************************/
#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
/******************************************************************************/
/*
 * Brief                 <The function is used to convert bit number to byte size>
 * Param-Name[in]        <bitSize : bit size >
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <uint16: byte number>
 * PreCondition          <None>
 * CallByAPI             <Com_InitIpdu, Com_IpduPeriodicTX, Com_IpduDirectTX,
 *                       Com_IpduMixedTX, Com_IpduMixedTX, Com_SendIpdu,
 *                       Com_InitMsgRecDynamicExternal, Com_InitValRecDynamicExternal,
 *                       Com_MsgRecDynamicLink, Com_MsgRecStaticExternal,
 *                       Com_GetStaticExternelMsgLength, Com_ReceiveDynamicMessage >
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint16, COM_CODE)
Com_GetBitToByteSize
(
    const uint32 bitSize
)
{
    uint16 byteLength = (uint16)(bitSize >> 0x3u);/* u4BitSize/8 */
    
    if ((bitSize & 0x7u) > 0x00u)/* (u4BitSize%8) > 0 */
    {
        byteLength += 0x1u;
    }
    return byteLength;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to initialized I-PDU run time structure.>
 * Param-Name[in]        <cfgPtr : I-PDU configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <PrivateIPduPtr : I-PDU run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_Init>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitIpdu(void)
{
    uint16 ipduLoop = 0u;
    uint16 ipduLength = 0u;
    StatusType status = E_OK;

    for (ipduLoop = 0u; (ipduLoop < Com_CfgPtr->ipduUsedNum) && (E_OK == status); ipduLoop++)
    {
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        Com_PrivateIPdu[ipduLoop].mdtTimer = 0u;
        Com_PrivateIPdu[ipduLoop].periodTimer = 0u;
        /* @req COM122, @req COM123 */
        if (COM_IPDU_RECEIVE == Com_CfgPtr->ipduPtr[ipduLoop].direction)
        {
            Com_PrivateIPdu[ipduLoop].DMTimer = Com_CfgPtr->ipduPtr->firstTimeOut / Com_CfgPtr->timeBase;
        }
        else
        {
            Com_PrivateIPdu[ipduLoop].DMTimer = 0u;
        }
        #endif
        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
        Com_PrivateIPdu[ipduLoop].directSend = FALSE;
        #endif
        #if (STD_OFF == COM_MSGUNPACK_IMMEDIATE)
        /* initialize I-PDU receive update flag */
        Com_PrivateIPdu[ipduLoop].updateFlag = FALSE;
        #endif
        /* initialize I-PDU data space pointer */
        ipduLength = Com_GetBitToByteSize(Com_CfgPtr->ipduPtr[ipduLoop].sizeInBits);
        Com_PrivateIPdu[ipduLoop].dataPtr = (uint8*)Com_Malloc(ipduLength);

        if (NULL_PTR == Com_PrivateIPdu[ipduLoop].dataPtr)
        {
            status = E_COM_LENGTH;
        }
    }
    return status;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to handle I-PDU transmission which
 *                       is directly triggered by message.>
 * Param-Name[in]        <ipduCfgPtr : I-PDU configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgSendDynamicExternel, Com_MsgSendStaticExternal,
 *                       Com_MsgSendZeroExternal>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_SendIpdu
(
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr
)
{
    PduInfoType pduInfo;
    uint16 index = Com_FindIpduIndex(ipduCfgPtr->pduId);

    if ((TRUE == Com_SendIpduGroupStartFlag)
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        && (COM_IPDU_TRANSMIT_PERIODIC != ipduCfgPtr->transmitMode)
        #endif
       )
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    {
        /* @req COM090, @req COM092 */
        if ((0u == Com_PrivateIPdu[index].mdtTimer)
            && (0u == Com_PrivateIPdu[index].DMTimer))
        {
            Com_PrivateIPdu[index].directSend = FALSE;
            /* reset tx confirm timeout */
            /* @req COM126 */
            if (0u == Com_PrivateIPdu[index].DMTimer)
            {
                Com_PrivateIPdu[index].DMTimer = ipduCfgPtr->timeOut / Com_CfgPtr->timeBase;
            }
            
            /* @req COM078 */
            if (TRUE == Com_IpduCallout(ipduCfgPtr))
    #endif
            {
                /* if timeout is overflow ,allow send Ipdu */
                /* @req COM003, @req COM075 */
                pduInfo.SduLength = Com_GetBitToByteSize(ipduCfgPtr->sizeInBits);
                pduInfo.SduDataPtr = Com_PrivateIPdu[index].dataPtr;

                (void)PduR_ComTransmit(ipduCfgPtr->pduId, &pduInfo);
            }
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        }
        else
        {
            /* message has not sent,wait for next timeout */
            Com_PrivateIPdu[index].directSend = TRUE;
        }
    }
    #endif
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to find I-PDU configuration index
 *                       with assigned pdu id.>
 * Param-Name[in]        <pduId : pdu id>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <uint16: I-PDU configuration index>
 * PreCondition          <None>
 * CallByAPI             <Com_SendIpdu, Com_InitValSendDynamicExternal,
 *                       Com_MsgSendDynamicExternel, Com_InitValSendStaticExternal,
 *                       Com_MsgSendStaticExternal, Com_TriggerTransmit,
 *                       Com_RxIndication, Com_TxConfirmation.>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint16, COM_CODE)
Com_FindIpduIndex
(
    const uint32 pduId
)
{
    uint16 pduIndex = 0;

    while(pduIndex < Com_CfgPtr->ipduUsedNum)
    {
        if (Com_CfgPtr->ipduPtr[pduIndex].pduId == pduId)
        {
            break;
        }
        else
        {
            pduIndex++;
        }
    }
    return pduIndex;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief         :        <The function is used to copy assigned number bits from
 *                       source address to destined address.>
 * Param-Name[in]        <pduId : pdu id>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <uint16: I-PDU configuration index>
 * PreCondition          <None>
 * CallByAPI             <Com_InitValSendDynamicExternal, Com_MsgSendDynamicExternel,
 *                       Com_MsgRecDynamicExternal, Com_InitValSendStaticExternal,
 *                       Com_MsgSendStaticExternal, Com_MsgSendStaticExternal,
 *                       Com_MsgRecStaticExternal.>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_CopyBit
(
    P2CONST(Com_MsgType, CODAUTOMATICE_VAR, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC)sourceData,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)destData,
    uint32 copyBitNum
)
{
    uint32 sourceStartPosition = 0x00u;
    uint32 destStartPosition = 0x00u;
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    uint32 sourcePosMax = 0xFFFFFFFFuL;
    uint32 destPosMax = 0xFFFFFFFFuL;
    #endif

    if (COM_MSG_RECEIVED == msgCfgPtr->NWMsgPtr->direction)
    {
        sourceStartPosition = msgCfgPtr->NWMsgPtr->bitPosition;
        destStartPosition = Com_GetMsgStartPostion(msgCfgPtr);
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        sourcePosMax = Com_FindDynamicMsgMinBit(msgCfgPtr->NWMsgPtr);
        #endif
    }
    else
    {
        destStartPosition = msgCfgPtr->NWMsgPtr->bitPosition;
        sourceStartPosition = Com_GetMsgStartPostion(msgCfgPtr);
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        destPosMax = Com_FindDynamicMsgMinBit(msgCfgPtr->NWMsgPtr);
        #endif
    }

    while(copyBitNum > 0)
    {
        copyBitNum --;
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        if ((destStartPosition < destPosMax) 
            && (sourceStartPosition < sourcePosMax))
        #endif
        {
            Com_SetBit(sourceStartPosition,
                       destStartPosition,
                       sourceData,
                       destData);
        }

        sourceStartPosition = Com_IndexCopyBit(sourceStartPosition,
                                               msgCfgPtr->NWMsgPtr);
        destStartPosition = Com_IndexCopyBit(destStartPosition,
                                             msgCfgPtr->NWMsgPtr);
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to calculate start position of message
 *                       in I-PDU.>
 * Param-Name[in]        <msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <uint32: start position>
 * PreCondition          <None>
 * CallByAPI             <Com_CopyBit>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint32, COM_CODE)
Com_GetMsgStartPostion
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    uint32 msgStartPos = 0u;

    if ((COM_MSG_BIG_ENDIAN == msgCfgPtr->NWMsgPtr->bitOrdering)
        && (COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->NWMsgPtr->dataInterpretation)
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        && (COM_MSG_STATIC == msgCfgPtr->NWMsgPtr->msgClass)
        #endif
         )
    {
        uint32 totleBitSize = 8u * (uint32)Com_GetCDataByteSize(msgCfgPtr->cData);
        #if (COM_BIG_ORDER_START_BIT_POSITION == COM_BIT_MSB)
        msgStartPos = (totleBitSize - msgCfgPtr->NWMsgPtr->sizeInBits) & 0xFFFFFFF8uL;
        msgStartPos += 7u - ((totleBitSize - msgCfgPtr->NWMsgPtr->sizeInBits) & 0x7uL);
        #else
        msgStartPos = totleBitSize - 0x8uL;
        #endif
    }
    else
    {
        msgStartPos = 0x00u;
    }
    return msgStartPos;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to set assigned address assigned
 *                       position value as input value>
 * Param-Name[in]        <sourceStartPos: source start position
 *                       destStartPos: destination start position
 *                       sourceData: source data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <destData: destination data pointer>
 * Return                <uint32>
 * PreCondition          <None>
 * CallByAPI             <Com_CopyBit>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_SetBit
(
    uint32 sourceStartPos,
    uint32 destStartPos,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC)sourceData,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)destData
)
{
    uint8 sourceByte = 0x00u;
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)destBytePtr = destData;
    /* Get the source byte witch source copy bit belong */
    sourceByte = *(uint8 *)((uint32)sourceData + (sourceStartPos / 8uL));
    /* Get the dest byte witch dest set bit belong */
    destBytePtr = (uint8 *)((uint32)destData + (destStartPos / 8uL));
    /* Get the source copy bit value 0 or none 0 */
    sourceByte &= (uint8)(1 << (sourceStartPos % 8uL));

    if (sourceByte > 0)
    {
        /* Set the dest bit in the dest byte */
        *destBytePtr |= (uint8)(1 << (destStartPos % 8uL));
    }
    else
    {
        /* Clear the dest bit in the dest byte */
        *destBytePtr &= (uint8)(~(1uL << (destStartPos % 8uL)));
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to calculate start copy bit position>
 * Param-Name[in]        <NWMsgCfgPtr: network message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <uint32>
 * PreCondition          <None>
 * CallByAPI             <Com_CopyBit>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint32, COM_CODE)
Com_IndexCopyBit
(
    const uint32 startPos,
    P2CONST(Com_NWMsgType, AUTOMATIC, COM_CONST_PBCFG)NWMsgCfgPtr
)
{
    uint32 startPosRet = startPos;
    
    /* index the source and dest start bit position */
    if ((COM_MSG_BIG_ENDIAN == NWMsgCfgPtr->bitOrdering)
        && (COM_MSG_UNSIGNEDINTEGER == NWMsgCfgPtr->dataInterpretation)
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        && (COM_MSG_STATIC == NWMsgCfgPtr->msgClass)
        #endif
        )
    {
        #if (COM_BIG_ORDER_START_BIT_POSITION == COM_BIT_MSB)
        if ((startPosRet & 0x7uL) == 0)
        {
            startPosRet += (uint32)0xF;
        }
        else
        {
            startPosRet--;
        }
        #else
        if ((startPosRet & 0x7uL) == 0x7uL)
        {
            if (startPosRet >= 0xFu)
            {
                startPosRet -= (uint32)0xFu;
            }
        }
        else
        {
            startPosRet++;
        }
        #endif
    }
    else
    {
        startPosRet++;
    }
    return startPosRet;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to unpack message from assigned I-PDU.>
 * Param-Name[in]        <ipduCfgPtr : I-PDU configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <iPduPrivatePtr : I-PDU run time structure pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MainFunctionRx, Com_RxIndication>
 */
/******************************************************************************/
/*
 * @req COM048, @req COM055, @req COM067, @req COM114, @req COM115, @req COM116,
 * @req COM117
 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgReceive
(
    P2CONST(Com_IPduType, AUTOMATIC, COM_CONST_PBCFG)ipduCfgPtr,
    P2CONST(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)iPduPrivatePtr
)
{
    uint16 msgIndex;
    P2CONST(Com_MsgType, AUTOMATIC, COM__CONST_PBCFG)msgCfgPtr;

    for(msgIndex = 0;
        msgIndex < Com_CfgPtr->msgUsedNum;
        msgIndex++)
    {
        msgCfgPtr = &Com_CfgPtr->messagePtr[msgIndex];
        if ((msgCfgPtr->NWMsgPtr != NULL_PTR)
            && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR)
            && (msgCfgPtr->NWMsgPtr->ipduPtr->pduId == ipduCfgPtr->pduId))
        {
            /* @req COM147 */
            switch (msgCfgPtr->property)
            {
                case COM_MSG_RECEIVE_UNQUEUED_EXTERNAL:
                #if (OSEK_COM_CCC == OSEK_COM_CCC1)
                case COM_MSG_RECEIVE_QUEUED_EXTERNAL:
                #endif
                    /* receive static message from Ipdu */
                    /* @req COM053 */
                    Com_MsgRecStaticExternal(msgCfgPtr,
                                            iPduPrivatePtr,
                                            &Com_PrivateMsg[msgIndex]);
                    break;

                #if (OSEK_COM_CCC == OSEK_COM_CCC1)
                case COM_MSG_RECEIVE_DYNAMIC_EXTERNAL:
                    /* receive dynamic message from Ipdu */
                    Com_MsgRecDynamicExternal(msgCfgPtr,
                                            iPduPrivatePtr,
                                            &Com_PrivateMsg[msgIndex]);
                    break;
                #endif
                
                default:
                    break;
            }
        }
    }
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    /* receive zero message from Ipdu */
    /* @req COM046 */
    Com_MsgRecZeroExternal(ipduCfgPtr);
    #endif
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize static internal
 *                       unqueued received message.>
 * Param-Name[in]        <msgPrivatePtr : static internal unqueued receive
 *                                       message run time structure.
 *                       msgCfgPtr : static internal unqueued receive message
 *                                   configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : initialize successfully
 *                       E_COM_LENGTH : buffer not enough
 *                       E_COM_ID : configuration error>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsg>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecUnQueuedExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;
    uint16 msgLength = 0x00u;
    P2CONST(Com_NWMsgType, AUTOMATIC, COM_CONST_PBCFG)curNWMsgPtr;

    /* get message corresponding network message */
    if ((msgCfgPtr->NWMsgPtr != NULL_PTR)
         #if (OSEK_COM_CCC == OSEK_COM_CCC1)
         && (msgCfgPtr->filterPtr != NULL_PTR)
         #endif
         && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR)
         && (msgCfgPtr->NWMsgPtr->sizeInBits != 0x00u)
         #if (OSEK_COM_CCC == OSEK_COM_CCC1)
         && (COM_MSG_STATIC == msgCfgPtr->NWMsgPtr->msgClass)
         #endif
         && (COM_MSG_RECEIVED == msgCfgPtr->NWMsgPtr->direction)
         && (COM_IPDU_RECEIVE == msgCfgPtr->NWMsgPtr->ipduPtr->direction))
    {
        curNWMsgPtr = msgCfgPtr->NWMsgPtr;
    }
    else if ((msgCfgPtr->linkMsgPtr != NULL_PTR)
             #if (OSEK_COM_CCC == OSEK_COM_CCC1)
             && (msgCfgPtr->filterPtr != NULL_PTR)
             #endif
             && (msgCfgPtr->linkMsgPtr->NWMsgPtr != NULL_PTR)
             && ((COM_MSG_RECEIVE_UNQUEUED_EXTERNAL == msgCfgPtr->linkMsgPtr->property)
             #if (OSEK_COM_CCC == OSEK_COM_CCC1)
             || (COM_MSG_RECEIVE_QUEUED_EXTERNAL == msgCfgPtr->linkMsgPtr->property)
             #endif
            ))
    {
        curNWMsgPtr = msgCfgPtr->linkMsgPtr->NWMsgPtr;
    }
    else
    {
        ret = E_COM_ID;
    }
    if (E_OK == ret)
    {
        /* get message length */
        msgLength = Com_GetStaticExternelMsgLength(msgCfgPtr);
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        if (COM_MSG_UNSIGNEDINTEGER == curNWMsgPtr->dataInterpretation)
        {
            /* set init value as old value */
            msgPrivatePtr->msgOldValue = Com_InitValueToU32(msgCfgPtr->cData,
                                                            (const void *)msgCfgPtr->initialValue);
        }
        msgPrivatePtr->occurrence = 0u;
        #endif
        /* apply queue buffer */
        msgPrivatePtr->queue.bufPtr = (uint8*)Com_Malloc(msgLength);
        if (msgPrivatePtr->queue.bufPtr != NULL_PTR)
        {
            /* init message buffer value */
            SchM_Enter_Com(WRITE_PROTECTION_AREA);
            Com_Memcpy(msgPrivatePtr->queue.bufPtr,
                       msgCfgPtr->initialValue,
                       msgLength);
            SchM_Exit_Com(WRITE_PROTECTION_AREA);
        }
        else
        {
            ret = E_COM_LENGTH;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize static external
 *                       send message.>
 * Param-Name[in]        <msgPrivatePtr : static external send message run
 *                                       time structure.
 *                       msgCfgPtr : static external send message
 *                                   configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : initialize successfully
 *                       E_COM_ID : configuration error>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsg>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgSendStaticExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;

    if ((msgCfgPtr->NWMsgPtr != NULL_PTR)
         #if (OSEK_COM_CCC == OSEK_COM_CCC1)
         && (msgCfgPtr->filterPtr != NULL_PTR)
         #endif
         && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR)
         && (msgCfgPtr->NWMsgPtr->sizeInBits != 0x00uL)
         #if (OSEK_COM_CCC == OSEK_COM_CCC1)
         && (COM_MSG_STATIC == msgCfgPtr->NWMsgPtr->msgClass)
         #endif
         && (COM_MSG_SENT == msgCfgPtr->NWMsgPtr->direction)
         && (COM_IPDU_SENT == msgCfgPtr->NWMsgPtr->ipduPtr->direction))
    {
        /* for sending message, no message buffer */
        msgPrivatePtr->queue.bufPtr = NULL_PTR;
        Com_InitValSendStaticExternal(
                                      #if (OSEK_COM_CCC == OSEK_COM_CCC1)
                                      FALSE,
                                      msgPrivatePtr,
                                      #endif
                                      msgCfgPtr,
                                      (const void *)msgCfgPtr->initialValue
                                      );
    }
    else
    {
        ret = E_COM_ID;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to send static external message.>
 * Param-Name[in]        <msgCfgPtr : static external send message
 *                                   configuration pointer
 *                       msgPrivatePtr : message run time structure
 *                       appDataRef : application data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : initialize successfully>
 * PreCondition          <None>
 * CallByAPI             <Com_SendMessage>
 */
/******************************************************************************/
/**@req COM029*/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendStaticExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    #endif
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataPtr
)
{
    boolean runContinue = TRUE;
    uint16 ipduIndex = Com_FindIpduIndex(msgCfgPtr->NWMsgPtr->ipduPtr->pduId);

    if (COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->NWMsgPtr->dataInterpretation)
    {
        uint8 appData[4] = {0,0,0,0};
        uint16 msgLength = Com_GetCDataByteSize(msgCfgPtr->cData);

        /* copy app data to temporary array for later handle */
        SchM_Enter_Com(WRITE_PROTECTION_AREA);
        Com_Memcpy(appData,(const uint8 *)appDataPtr,msgLength);
        SchM_Exit_Com(WRITE_PROTECTION_AREA);

        /* message filter handle */
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        runContinue = Com_Filter(appDataPtr,
                                 msgCfgPtr,
                                 msgPrivatePtr);
        /* CPU Order Callout handle */
        if (TRUE == runContinue)
        {
            runContinue = Com_CPUOrderCallout(msgCfgPtr);
        }
        #endif
        
        if (TRUE == runContinue)
        {
            /* Order Change handle */
            Com_OrderChange(msgCfgPtr,appData);
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            /* network Order Callout handle */
            runContinue = Com_NWOrderCallout(msgCfgPtr);
            #endif
        }
        
        /* copy app data to corredponding I-PDU space */
        if (TRUE == runContinue)
        {
            SchM_Enter_Com(WRITE_PROTECTION_AREA);
            Com_CopyBit(msgCfgPtr,
                      (const uint8 *)appData,
                       Com_PrivateIPdu[ipduIndex].dataPtr,
                       msgCfgPtr->NWMsgPtr->sizeInBits);
            SchM_Exit_Com(WRITE_PROTECTION_AREA);
        }
    }
    else
    {
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        /* CPU Order Callout handle */
        runContinue = Com_CPUOrderCallout(msgCfgPtr);
        if (TRUE == runContinue)
        {
            /* network Order Callout handle */
            runContinue = Com_NWOrderCallout(msgCfgPtr);
        }
        #endif
        
        /* copy app data to corredponding I-PDU space */
        if (TRUE == runContinue)
        {
            SchM_Enter_Com(WRITE_PROTECTION_AREA);
            Com_CopyBit(msgCfgPtr,
                      (const uint8 *)appDataPtr,
                       Com_PrivateIPdu[ipduIndex].dataPtr,
                       msgCfgPtr->NWMsgPtr->sizeInBits);
            SchM_Exit_Com(WRITE_PROTECTION_AREA);
        }
    }

    if (TRUE == runContinue)
    {
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        /* @req COM028, @req COM032, @req COM089 */
        if (COM_MSG_TRIGGERED == msgCfgPtr->transferProperty)
        #endif
        {
            /* trigger message cause I-PDU transmission */
            Com_SendIpdu(msgCfgPtr->NWMsgPtr->ipduPtr);
        }
    }
    return E_OK;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to receive static external message.>
 * Param-Name[in]        <msgCfgPtr : static external receive message
 *                                   configuration pointer
 *                       msgPrivatePtr : message run time structure pointer
 *                       iPduPrivatePtr : I-PDU run time structure pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : initialize successfully>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgReceive>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecStaticExternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(Com_IPduRunTimeType, AUTOMATIC, COM_VAR)iPduPrivatePtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr
)
{
    boolean runContinue = TRUE;
    uint32 appData[2] = {0,0};
    uint16 msgLength = 0x00u;

    SchM_Enter_Com(WRITE_PROTECTION_AREA);
    /* copy app data to temporary array for later handle */
    Com_CopyBit(msgCfgPtr,
              (const uint8 *)iPduPrivatePtr->dataPtr,
               (uint8 *)appData,
               msgCfgPtr->NWMsgPtr->sizeInBits);
    SchM_Exit_Com(WRITE_PROTECTION_AREA);

    /* network Order Callout handle */
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    runContinue = Com_NWOrderCallout(msgCfgPtr);
    #endif
    
    if (COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->NWMsgPtr->dataInterpretation)
    {
        /* Order Change handle */
        Com_OrderChange(msgCfgPtr,(uint8 *)appData);
        /* signification Extension handle */
        Com_BitExtension(msgCfgPtr,(void *)appData);
        msgLength = Com_GetCDataByteSize(msgCfgPtr->cData);
    }
    else
    {
        msgLength = Com_GetBitToByteSize(msgCfgPtr->NWMsgPtr->sizeInBits);
    }
    
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    /* CPU Order Callout handle */
    if (TRUE == runContinue)
    {
        runContinue = Com_CPUOrderCallout(msgCfgPtr);
    }
    
    /* message filter handle */
    if ((COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->NWMsgPtr->dataInterpretation)
         && (TRUE == runContinue))
    {
        runContinue = Com_Filter((const void *)appData,
                                 msgCfgPtr,
                                 msgPrivatePtr);
    }
    #endif
    
    /* @req COM049 */
    if (TRUE == runContinue)
    {
        /* unqueue message reception handle */
        if (COM_MSG_RECEIVE_UNQUEUED_EXTERNAL == msgCfgPtr->property)
        {
            /* copy app data to corredponding message buffer space */
            SchM_Enter_Com(WRITE_PROTECTION_AREA);
            Com_Memcpy(msgPrivatePtr->queue.bufPtr,
                        (const uint8 *)appData,
                        msgLength);
            SchM_Exit_Com(WRITE_PROTECTION_AREA);
        }
        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
        else  /* queue message reception handle */
        {
            boolean queueStatus;
            queueStatus = Com_QueueBufInsert(&msgPrivatePtr->queue,
                                             (uint8 *)appData);
            /* @req COM026, @req COM064 */
            /* queue insert error */
            if (FALSE == queueStatus)
            {
                runContinue = FALSE;
                msgPrivatePtr->messageStatus = E_COM_LIMIT;
            }
            else   /* queue insert successful */
            {
                msgPrivatePtr->messageStatus = E_OK;
            }
        }
        #endif
        
        /* @req COM142,@req COM 050 */
        /* message notification handle */
        if ((TRUE == runContinue)
            && (msgCfgPtr->msgNotif != NULL_PTR))
        {
            /* @req COM141 */
            msgCfgPtr->msgNotif();
        }
        /* @req COM058 */
        /* link message handle */
        Com_MsgRecStaticLink(msgCfgPtr, (const void *)appData);
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize receive unqueued
 *                       external message value.>
 * Param-Name[in]        <msgPrivatePtr : receive unqueued external message run
 *                                       time structure.
 *                       msgCfgPtr : static external send message
 *                                   configuration pointer
 *                       appDataRef : application data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitVal>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValRecUnQueuedExternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
)
{
    /* assign externel receive message initial value */
    uint16 msgLength;
    P2CONST(Com_NWMsgType, AUTOMATIC, COM_CONST_PBCFG)curNWMsgPtr;

    /* get network message pointer of message corresponding to */
    if (msgCfgPtr->NWMsgPtr != NULL_PTR)
    {
        curNWMsgPtr = msgCfgPtr->NWMsgPtr;
    }
    else
    {
        curNWMsgPtr = msgCfgPtr->linkMsgPtr->NWMsgPtr;
    }
    
    /* get message length */
    msgLength = Com_GetStaticExternelMsgLength(msgCfgPtr);
    
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    if (COM_MSG_UNSIGNEDINTEGER == curNWMsgPtr->dataInterpretation)
    {

        msgPrivatePtr->msgOldValue = Com_InitValueToU32(msgCfgPtr->cData,
                                                        appDataRef);
    }
    #endif
    
    /* init message buffer space */
    SchM_Enter_Com(WRITE_PROTECTION_AREA);
    Com_Memcpy(msgPrivatePtr->queue.bufPtr,
               (const uint8 *)appDataRef,
               msgLength);
    SchM_Exit_Com(WRITE_PROTECTION_AREA);
    
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                <This function is used to initialize send static
 *                       external message value.>
 * Param-Name[in]        <msgPrivatePtr : static external send message run
 *                                       time structure.
 *                       msgCfgPtr : static external send message
 *                                   configuration pointer >
 *                       <appDataRef : application data pointer >
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitVal>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValSendStaticExternal
(
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    boolean initFinished,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    #endif
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
)
{
    /* assign externel send message initial value to Ipdu */
    boolean processCondition = TRUE;
    uint8 appData[4] = {0,0,0,0};

    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    if (TRUE == initFinished)
    {
        processCondition = Com_CPUOrderCallout(msgCfgPtr);
    }
    #endif
    
    if (TRUE == processCondition)
    {
        uint16 msgLength = Com_GetStaticExternelMsgLength(msgCfgPtr);
        SchM_Enter_Com(WRITE_PROTECTION_AREA);
        Com_Memcpy(appData,
                (const uint8 *)appDataRef,
                (uint16)msgLength);
        SchM_Exit_Com(WRITE_PROTECTION_AREA);
        
        if (COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->NWMsgPtr->dataInterpretation)
        {
            /* order change */
            Com_OrderChange(msgCfgPtr,appData);
        }
        
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        if (TRUE == initFinished)
        {
            processCondition = Com_NWOrderCallout(msgCfgPtr);
        }
        #endif
    }

    if (TRUE == processCondition)
    {
        uint16 ipduIndex;
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        if (COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->NWMsgPtr->dataInterpretation)
        {
            msgPrivatePtr->msgOldValue = Com_InitValueToU32(msgCfgPtr->cData,
                                                            appDataRef);
        }
        
        msgPrivatePtr->occurrence = 0x00uL;
        #endif
        
        ipduIndex = Com_FindIpduIndex(msgCfgPtr->NWMsgPtr->ipduPtr->pduId);

        SchM_Enter_Com(WRITE_PROTECTION_AREA);
        Com_CopyBit(msgCfgPtr,
                    (const uint8 *)appData,
                    Com_PrivateIPdu[ipduIndex].dataPtr,
                    msgCfgPtr->NWMsgPtr->sizeInBits);
        SchM_Exit_Com(WRITE_PROTECTION_AREA);
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to calculate static external message
 *                       length.>
 * Param-Name[in]        <msgCfgPtr : static external message configuration pointer>
 * Param-Name[out]        <None>
 * Param-Name[in/out]    <None>
 * Return                <uint16 : message type length>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgReceive>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint16, COM_CODE)
Com_GetStaticExternelMsgLength
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    uint16 msgLength = 0x00u;

    if (msgCfgPtr->NWMsgPtr != NULL_PTR)
    {
        if (COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->NWMsgPtr->dataInterpretation)
        {
            msgLength = Com_GetCDataByteSize(msgCfgPtr->cData);
        }
        else
        {
            msgLength = Com_GetBitToByteSize(msgCfgPtr->NWMsgPtr->sizeInBits);
        }
    }
    else
    {
        if (COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->linkMsgPtr->NWMsgPtr->dataInterpretation)
        {
            msgLength = Com_GetCDataByteSize(msgCfgPtr->linkMsgPtr->cData);
        }
        else
        {
            msgLength = Com_GetBitToByteSize(msgCfgPtr->linkMsgPtr->NWMsgPtr->sizeInBits);
        }
    }
    return msgLength;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to receive static link message.>
 * Param-Name[in]        <msgCfgPtr : receive message configuration pointer
 *                       appDataPtr : application data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgReceive>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_MsgRecStaticLink
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, AUTOMATIC)appDataPtr
)
{
    uint16 msgIndex;
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgLinkCfgPtr;

    for(msgIndex = 0;
        msgIndex < Com_CfgPtr->msgUsedNum;
        msgIndex++)
    {
        msgLinkCfgPtr = &Com_CfgPtr->messagePtr[msgIndex];

        if (msgLinkCfgPtr->linkMsgPtr == msgCfgPtr)
        {
            boolean runContinue = TRUE;
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            if (COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->NWMsgPtr->dataInterpretation)
            {
                runContinue = Com_Filter(appDataPtr,
                                        msgLinkCfgPtr,
                                        &Com_PrivateMsg[msgIndex]);
            }
            #endif
            if (TRUE == runContinue)
            {
                if (COM_MSG_RECEIVE_UNQUEUED_EXTERNAL == msgLinkCfgPtr->property)
                {
                    uint16 msgLength = Com_GetStaticExternelMsgLength(msgCfgPtr);

                    SchM_Enter_Com(WRITE_PROTECTION_AREA);
                    Com_Memcpy(Com_PrivateMsg[msgIndex].queue.bufPtr,
                                (const uint8 *)appDataPtr,
                                msgLength);
                    SchM_Exit_Com(WRITE_PROTECTION_AREA);
                }
                #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
                else
                {
                    boolean queueStatus;
                    queueStatus = Com_QueueBufInsert(&Com_PrivateMsg[msgIndex].queue,
                                                     (uint8*)appDataPtr);
                    if (FALSE == queueStatus)
                    {
                        runContinue = FALSE;
                        Com_PrivateMsg[msgIndex].messageStatus = E_COM_LIMIT;
                    }
                    else
                    {
                        Com_PrivateMsg[msgIndex].messageStatus = E_OK;
                    }
                }
                #endif
                
                if ((TRUE == runContinue)
                    && (msgCfgPtr->msgNotif != NULL_PTR))
                {
                    msgCfgPtr->msgNotif();
                }
            }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to call message notification.>
 * Param-Name[in]        <configPtr : COM configuration data pointer
 *                       u4PduId : confirmation I-PDU id>
 *                       <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_TxConfirmation>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_NotifTxConfirm
(
    const uint32 u4PduId
)
{
    uint16 msgIndex;

    for(msgIndex = 0;
        (msgIndex < Com_CfgPtr->msgUsedNum);
        msgIndex++)
    {
        const Com_MsgType *msgCfgPtr = &Com_CfgPtr->messagePtr[msgIndex];
        if ((msgCfgPtr->NWMsgPtr != NULL_PTR) 
            && (msgCfgPtr->NWMsgPtr->ipduPtr != NULL_PTR) 
            && (msgCfgPtr->NWMsgPtr->ipduPtr->pduId == u4PduId))
        {
            /** @req COM010 */
            if (msgCfgPtr->msgNotif != NULL_PTR)
            {
                /* @req COM009 */
                msgCfgPtr->msgNotif();
            }
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to get local CPU byte endianess.>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <COM_MSG_BIG_ENDIAN : big endianess
 *                       COM_MSG_LITTLE_ENDIAN : little endianess>
 * PreCondition          <None>
 * CallByAPI             <Com_OrderChange>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(Com_MsgBitOrderingType, COM_CODE)
Com_GetLocalCpuEndian(void)
{
    uint16 test = 0x1234u;
    Com_MsgBitOrderingType Com_MsgBitOrdering;

    if (0x12u == *((uint8*)&test))
    {
        Com_MsgBitOrdering = COM_MSG_BIG_ENDIAN;
    }
    else
    {
        Com_MsgBitOrdering = COM_MSG_LITTLE_ENDIAN;
    }
    return Com_MsgBitOrdering;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to handle data Byte ordering.>
 * Param-Name[in]        <msgCfgPtr : message configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <dataPtr : Byte ordering data pointer>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitValSendStaticExternal, Com_MsgSendStaticExternal,
 *                       Com_MsgRecStaticExternal.>
 */
/******************************************************************************/
/* @req COM013, @req COM110 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_OrderChange
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)dataPtr
)
{
    Com_MsgBitOrderingType cpuOrdering = Com_GetLocalCpuEndian();

    if ((msgCfgPtr->NWMsgPtr != NULL_PTR)
        && (cpuOrdering != msgCfgPtr->NWMsgPtr->bitOrdering)
        && (COM_MSG_UNSIGNEDINTEGER == msgCfgPtr->NWMsgPtr->dataInterpretation))
    {
        uint8 dataTemp = 0;

        switch(msgCfgPtr->cData)
        {
            case COM_MSG_SINT16:
            case COM_MSG_UINT16:
                dataTemp = dataPtr[0];
                 dataPtr[0] = dataPtr[1];
                 dataPtr[1] = dataTemp;
                 break;
                 
            case COM_MSG_SINT32:
            case COM_MSG_UINT32:
                dataTemp = dataPtr[0];
                 dataPtr[0] = dataPtr[3];
                 dataPtr[3] = dataTemp;
                 dataTemp = dataPtr[1];
                 dataPtr[1] = dataPtr[2];
                 dataPtr[2] = dataTemp;
                break;
                
            default:
                break;
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to message sign extension.>
 * Param-Name[in]        <None>
 *                       <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgRecStaticExternal>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_BitExtension
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(void, AUTOMATIC, AUTOMATIC)recDataPtr
)
{
    uint32 highBitVaule = 0x1uL << (uint8)(msgCfgPtr->NWMsgPtr->sizeInBits - 0x1uL);
    uint32 startSetBit = msgCfgPtr->NWMsgPtr->sizeInBits;

    switch(msgCfgPtr->cData)
    {
        case COM_MSG_SINT8:
            /* sign bit is 1, extend it */
            if ((*(uint8 *)recDataPtr & (uint8)highBitVaule) > 0x00u)
            {
                while(startSetBit < 8uL)
                {
                    *(uint8 *)recDataPtr |= (uint8)(0x1uL << startSetBit);
                    startSetBit++;
                }
            }
            break;
            
        case COM_MSG_SINT16:
            /* sign bit is 1, extend it */
            if ((*(uint16 *)recDataPtr & (uint16)highBitVaule) > 0x00u)
            {
                while(startSetBit < 16uL)
                {
                    *(uint16 *)recDataPtr |= (uint16)(0x1uL << (uint8)startSetBit);
                    startSetBit++;
                }
            }
            break;
            
        case COM_MSG_SINT32:
            /* sign bit is 1, extend it */
            if ((*(uint32 *)recDataPtr & (uint32)highBitVaule) > 0x00u)
            {
                while(startSetBit < 32uL)
                {
                    *(uint32 *)recDataPtr |= (uint32)(0x1uL << (uint8)startSetBit);
                    startSetBit++;
                }
            }
            break;
            
        default:
            break;
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/******************************************************************************/
/*                                                                            */
/*                          Conformance Classes:  1/B                         */
/*                                                                            */
/******************************************************************************/
#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
/******************************************************************************/
/*
 * Brief                 <This function is used to initialize static internal
 *                       queued received message.>
 * Param-Name[in]        <msgPrivatePtr : static internal queued receive
 *                                       message run time structure.
 *                       msgCfgPtr : static internal queued receive message
 *                                   configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : initialize successfully
 *                       E_COM_LENGTH : buffer not enough
 *                       E_COM_ID : configuration error >
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsg>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecQueuedInternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;

    if ((msgCfgPtr->sendMsgPtr != NULL_PTR)
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        && (msgCfgPtr->filterPtr != NULL_PTR)
        #endif
        && ((COM_MSG_SEND_STATIC_INTERNAL == msgCfgPtr->sendMsgPtr->property)
        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
        ||(COM_MSG_SEND_STATIC_EXTERNAL == msgCfgPtr->sendMsgPtr->property)
        #endif
        ))
    {
        uint16 msgLength;
        msgLength = Com_GetCDataByteSize(msgCfgPtr->sendMsgPtr->cData);
        msgPrivatePtr->queue.bufPtr = (uint8*)Com_Malloc(msgLength * (uint16)msgCfgPtr->queueSize);
        
        if (msgPrivatePtr->queue.bufPtr != NULL_PTR)
        {
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            msgPrivatePtr->msgOldValue = Com_InitValueToU32(msgCfgPtr->cData,
                                                            (void *)msgCfgPtr->initialValue);
            msgPrivatePtr->occurrence = 0;
            #endif
            msgPrivatePtr->messageStatus = E_COM_NOMSG;
            msgPrivatePtr->queue.depth = (uint8)msgCfgPtr->queueSize;
            msgPrivatePtr->queue.length = (uint8)msgLength;
            Queue_BufferFlush(&msgPrivatePtr->queue);
        }
        else
        {
            ret = E_COM_LENGTH;
        }
    }
    else
    {
        ret = E_COM_ID;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to insert a node into assigned queue.>
 * Param-Name[in]        <queuePtr : queue head pointer
 *                       dataPtr  : node data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <TRUE : queue insert successfully
 *                       FALSE: queue insert unsuccessfully>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgRecStaticExternal, Com_MsgRecStaticInternel,
 *                       Com_MsgRecStaticLink.>
 */
/******************************************************************************/
/* @req COM063,@req COM061 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_QueueBufInsert
(
    P2VAR(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr,
    P2CONST(uint8, AUTOMATIC, COM_VAR)dataPtr
)
{
    boolean ret = FALSE;

    SchM_Enter_Com(WRITE_PROTECTION_AREA);
    if (TRUE == Com_QueueBufFull(queuePtr))
    {
        /* Buffer is full*/
        ret = FALSE;
    }
    else
    {
        /* Copy data to last place in buffer */
        Com_Memcpy(queuePtr->lastPtr, dataPtr, (uint16)queuePtr->length);
        Com_QueueBufInc(queuePtr, &queuePtr->lastPtr);
        queuePtr->nrItems++;
        ret = TRUE;
    }
    SchM_Exit_Com(WRITE_PROTECTION_AREA);
    
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to insert a node into assigned queue. >
 * Param-Name[in]        <queuePtr : queue head pointer
 *                       dataPtr  : node data pointer >
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <TRUE : queue insert successfully
 *                       FALSE: queue insert unsuccessfully >
 * PreCondition          <None>
 * CallByAPI             <Com_MsgRecStaticExternal, Com_MsgRecStaticInternel,
 *                       Com_MsgRecStaticLink.>
 */
/******************************************************************************/
/* @req COM062 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_QueueBufGet
(
    P2VAR(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr,
    P2VAR(uint8, AUTOMATIC, COM_VAR)dataPtr
)
{
    boolean ret = FALSE;

    SchM_Enter_Com(WRITE_PROTECTION_AREA);
    if (queuePtr->nrItems > 0)
    {
        /* get queue message from message queue */
        Com_Memcpy(dataPtr, queuePtr->firstPtr, (uint16)queuePtr->length);
        /* queue message head pointer move */
        Com_QueueBufInc(queuePtr, &queuePtr->firstPtr);
        /* increase available queue message count */ 
        queuePtr->nrItems--;
        ret = TRUE;
    }
    else
    {
        Com_Memset(dataPtr, 0x00, (uint16)queuePtr->length);
        ret = FALSE;
    }
    SchM_Exit_Com(WRITE_PROTECTION_AREA);
    
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to free queue space.>
 * Param-Name[in]        <queuePtr : queue head pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitVal, Com_InitMsgRecQueuedInternal,>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Queue_BufferFlush
(
    P2VAR(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr
)
{
    queuePtr->nrItems = 0;
    queuePtr->firstPtr = queuePtr->bufPtr;
    queuePtr->lastPtr = queuePtr->bufPtr;
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to move to next queue node.>
 * Param-Name[in]        <queuePtr : queue head pointer
 *                       bufferPtr : queue space pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_QueueBufInsert, Com_QueueBufGet>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_QueueBufInc
(
    P2CONST(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr,
    P2VAR(P2VAR(uint8, AUTOMATIC, COM_VAR),AUTOMATIC, COM_VAR)bufferPtr
)
{
    uint32 newAddr = 0u;
    uint32 curAddr = 0u;

    *bufferPtr = *bufferPtr + queuePtr->length;
    newAddr = (uint32)(*bufferPtr);
    curAddr = (uint32)(queuePtr->bufPtr);
    curAddr += ((uint32)queuePtr->depth) * ((uint32)queuePtr->length);

    if (newAddr >= curAddr)
    {
        *bufferPtr = queuePtr->bufPtr;
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************/
/*
 * Brief                 <This function is used to check whether queue is full.>
 * Param-Name[in]        <queuePtr : queue head pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_QueueBufInsert>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(boolean, COM_CODE)
Com_QueueBufFull
(
    P2CONST(Com_QueueType, AUTOMATIC, COM_VAR)queuePtr
)
{
    boolean ret = FALSE;

    if (queuePtr->nrItems < queuePtr->depth)
    {
        ret = FALSE;
    }
    else
    {
        ret = TRUE;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/******************************************************************************/
/*                                                                            */
/*                          Conformance Classes:  none                        */
/*                                                                            */
/******************************************************************************/
/******************************************************************************/
/*
 * Brief                 <The function is used to copy byte data from source address
 *                       to destination.>
 * Param-Name[in]        <sourcePtr : source address pointer
 *                       length    : length of copy data >
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <destPtr : destination pointer of data copied to.>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsgRecDynamicExternal, Com_InitValRecDynamicExternal,
 *                       Com_MsgRecDynamicLink, Com_InitMsgRecUnQueuedInternal,
 *                       Com_InitMsgRecUnQueuedExternal, Com_InitValRecUnQueuedInternal,
 *                       Com_InitValRecUnQueuedExternal, Com_InitValSendStaticExternal,
 *                       Com_MsgSendStaticExternal, Com_MsgRecStaticExternal,
 *                       Com_MsgRecStaticInternel, Com_MsgRecStaticLink,
 *                       Com_QueueBufInsert, Com_QueueBufGet, Com_ReceiveMessage,
 *                       Com_ReceiveMessage, Com_ReceiveDynamicMessage>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_Memcpy
(
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)destPtr,
    P2CONST(uint8, AUTOMATIC, AUTOMATIC)sourcePtr,
    uint16 length
)
{
    while(length > 0x00u)
    {
        if ((destPtr != NULL_PTR) && (sourcePtr != NULL_PTR))
        {
            *destPtr = *sourcePtr;
            destPtr++;
            sourcePtr++;
            length--;
        }
        else
        {
            length = 0x00u;
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to set destination address byte data
 *                       with source data>
 * Param-Name[in]        <sourcePtr : source address pointer
 *                       length    : length of copy data>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <destPtr : destination pointer of set address.>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_QueueBufGet>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_Memset
(
    P2VAR(uint8, AUTOMATIC, AUTOMATIC)destPtr,
    const uint8 source,
    uint16 length
)
{
    while(length > 0x00u)
    {
        if (destPtr != NULL_PTR)
        {
            *destPtr = source;
            destPtr++;
            length--;
        }
        else
        {
            length = 0x00u;
        }
    }
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to apply assigned byte data >
 * Param-Name[in]        <length : length of applied space >
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitIpdu, Com_InitMsgRecDynamicExternal,
 *                       Com_InitMsgRecUnQueuedInternal, Com_InitMsgRecQueuedInternal,
 *                       Com_InitMsgRecQueuedExternal, Com_InitMsgRecUnQueuedExternal>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(P2VAR(void, AUTOMATIC, COM_VAR), COM_CODE)
Com_Malloc
(
    const uint16 length
)
{
    /* assign memory for com messages and IPDUs */
    P2VAR(void, AUTOMATIC, COM_VAR)memoryPtr = NULL_PTR;

    if ((Com_BufferUsed + length) <= Com_CfgPtr->bufferLength)
    {
        memoryPtr = &Com_MemoryBuffer[Com_BufferUsed];
        Com_BufferUsed += length;
    }
    return memoryPtr;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The function is used to calculate byte size of data type>
 * Param-Name[in]        <dataType : data type>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <uint16: byte number>
 * PreCondition          <None>
 * CallByAPI             <Com_GetMsgStartPostion, Com_ReceiveMessage,
 *                       Com_InitMsgRecUnQueuedInternal, Com_InitMsgRecQueuedInternal,
 *                       Com_InitValRecUnQueuedInternal, Com_InitValSendStaticExternal,
 *                       Com_MsgSendStaticExternal, Com_MsgRecStaticExternal,
 *                       Com_MsgRecStaticInternel, Com_GetStaticExternelMsgLength,
 *                       Com_GetStaticExternelMsgLength>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint16, COM_CODE)
Com_GetCDataByteSize
(
    const Com_MsgCDataType dataType
)
{
    uint16 dataLen = 0x00u;
    switch(dataType)
    {
        case COM_MSG_BOOLEAN:
        case COM_MSG_UINT8:
        case COM_MSG_SINT8:
            dataLen = 0x1u;
            break;

        case COM_MSG_UINT16:
        case COM_MSG_SINT16:
            dataLen = 0x2u;
            break;

        case COM_MSG_SINT32:
        case COM_MSG_UINT32:
            dataLen = 0x4u;
            break;

        default:
            dataLen = 0x00u;
            break;
    }
    return dataLen;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize message run time structure.>
 * Param-Name[in]        <cfgPtr : COM module configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <E_COM_ID : message configuration error
 *                       E_OK : initialize successfully
 *                       E_COM_LENGTH : buffer not enough>
 * PreCondition          <None>
 * CallByAPI             <Com_Init>
 */
/******************************************************************************/
/* @req COM066, @req COM161, @req COM162, @req COM163, @req COM164, @req COM165 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsg
(
    void
)
{
    StatusType ret = E_OK;
    uint16 msgIndex;

    for(msgIndex = 0x00u;
        (msgIndex < Com_CfgPtr->msgUsedNum) && (E_OK == ret);
        msgIndex++)
    {
        switch(Com_CfgPtr->messagePtr[msgIndex].property)
        {
            /* receive unqueued internal message initialization */
            case COM_MSG_RECEIVE_UNQUEUED_INTERNAL:
                ret = Com_InitMsgRecUnQueuedInternal(&Com_PrivateMsg[msgIndex],
                                                     &Com_CfgPtr->messagePtr[msgIndex]);
                break;
                
            #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
            /* receive queued internal message initialization */
            case COM_MSG_RECEIVE_QUEUED_INTERNAL:
                ret = Com_InitMsgRecQueuedInternal(&Com_PrivateMsg[msgIndex],
                                                   &Com_CfgPtr->messagePtr[msgIndex]);
                break;
            #endif
            
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            /* receive queued external message initialization */
            case COM_MSG_RECEIVE_QUEUED_EXTERNAL:
                ret = Com_InitMsgRecQueuedExternal(&Com_PrivateMsg[msgIndex],
                                                   &Com_CfgPtr->messagePtr[msgIndex]);
                break;
            #endif
            
            #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
            /* send static external message initialization */
            case COM_MSG_SEND_STATIC_EXTERNAL:
                ret = Com_InitMsgSendStaticExternal(&Com_PrivateMsg[msgIndex],
                                                    &Com_CfgPtr->messagePtr[msgIndex]);
                break;
            #endif
            
            #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
            case COM_MSG_RECEIVE_UNQUEUED_EXTERNAL:
                /* receive unqueued external message initialization */
                ret = Com_InitMsgRecUnQueuedExternal(&Com_PrivateMsg[msgIndex],
                                                     &Com_CfgPtr->messagePtr[msgIndex]);
                break;
            #endif
            
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            case COM_MSG_SEND_DYNAMIC_EXTERNAL:
                /* send dynamic external message initialization */
                ret = Com_InitMsgSendDynamicExternal(&Com_PrivateMsg[msgIndex],
                                                     &Com_CfgPtr->messagePtr[msgIndex]);
                break;
            #endif
            
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            case COM_MSG_RECEIVE_DYNAMIC_EXTERNAL:
                /* receive dynamic external message initialization */
                ret = Com_InitMsgRecDynamicExternal(&Com_PrivateMsg[msgIndex],
                                                     &Com_CfgPtr->messagePtr[msgIndex]);
                break;
            #endif
            
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            /* receive dynamic external message initialization */
            case COM_MSG_SEND_ZERO_INTERNAL:
                Com_PrivateMsg[msgIndex].queue.bufPtr = NULL_PTR;
                break;
            #endif
            
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
                /* send zero external message initialization */
            case COM_MSG_SEND_ZERO_EXTERNAL:
                ret = Com_InitMsgSendZeroExternal(&Com_PrivateMsg[msgIndex],
                                                  &Com_CfgPtr->messagePtr[msgIndex]);
                break;
            #endif
            
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
               /* receive zero internal message initialization */
            case COM_MSG_RECEIVE_ZERO_INTERNAL:
                ret = Com_InitMsgRecZeroInternal(&Com_PrivateMsg[msgIndex],
                                                 &Com_CfgPtr->messagePtr[msgIndex]);
                break;
            #endif
            
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
              /* receive zero external message initialization */
            case COM_MSG_RECEIVE_ZERO_EXTERNAL:
                ret = Com_InitMsgRecZeroExternal(&Com_PrivateMsg[msgIndex],
                                                 &Com_CfgPtr->messagePtr[msgIndex]);
                break;
            #endif
            
            case COM_MSG_SEND_STATIC_INTERNAL:
                /* receive zero external message initialization */
                Com_PrivateMsg[msgIndex].queue.bufPtr = NULL_PTR;
                break;
                
            case COM_MSG_RECEIVE_ZERO_SENDERS:
                break;
                
            default:
                ret = E_COM_ID;
                break;
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize message value in
 *                       run time structure with application data.>
 * Param-Name[in]        <msgCfgPtr : message configuration pointer
 *                       appDataRef : application data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <msgPrivatePtr : message run time structure pointer>
 * Return                <E_COM_ID : message configuration error
 *                       E_OK : initialize successfully>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMessage>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitVal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
)
{
    StatusType ret = E_OK;

    switch(msgCfgPtr->property)
    {
        /* receive unqueued internal message initialization */
        case COM_MSG_RECEIVE_UNQUEUED_INTERNAL:
            Com_InitValRecUnQueuedInternal(msgPrivatePtr,
                                           msgCfgPtr,
                                           appDataRef);
            break;
            
        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
        /* receive unqueued external message initialization */
        case COM_MSG_RECEIVE_UNQUEUED_EXTERNAL:
            Com_InitValRecUnQueuedExternal(msgPrivatePtr,
                                           msgCfgPtr,
                                           appDataRef);
            break;
        #endif
        
        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
        /* receive queued internal message initialization */
        case COM_MSG_RECEIVE_QUEUED_INTERNAL:
            msgPrivatePtr->messageStatus = E_COM_NOMSG;
            Queue_BufferFlush(&msgPrivatePtr->queue);
            break;
        #endif
        
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        /* receive queued external message initialization */
        case COM_MSG_RECEIVE_QUEUED_EXTERNAL:
            msgPrivatePtr->messageStatus = E_COM_NOMSG;
            Queue_BufferFlush(&msgPrivatePtr->queue);
            break;
        #endif
        
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        /* receive dynamic external message initialization */
        case COM_MSG_RECEIVE_DYNAMIC_EXTERNAL:
            Com_InitValRecDynamicExternal(msgPrivatePtr,
                                          msgCfgPtr,
                                          appDataRef);
            break;
        #endif

        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
        /* send static external message initialization */
        case COM_MSG_SEND_STATIC_EXTERNAL:
            Com_InitValSendStaticExternal(
                                          #if (OSEK_COM_CCC == OSEK_COM_CCC1)
                                          TRUE,
                                          msgPrivatePtr,
                                          #endif
                                          msgCfgPtr,
                                          appDataRef);
            break;
        #endif
        
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        /* send dynamic external message initialization */
        case COM_MSG_SEND_DYNAMIC_EXTERNAL:
            Com_InitValSendDynamicExternal(msgCfgPtr,
                                           appDataRef,
                                           TRUE);
            break;
        #endif
        
        default:
            ret = E_COM_ID;
            break;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize static internal
 *                       unqueued received message.>
 * Param-Name[in]        <msgPrivatePtr : static internal unqueued receive
 *                                       message run time structure.
 *                       msgCfgPtr : static internal unqueued receive message
 *                                   configuration pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : initialize successfully
 *                       E_COM_LENGTH : buffer not enough
 *                       E_COM_ID : configuration error>
 * PreCondition          <None>
 * CallByAPI             <Com_InitMsg>
 */
/******************************************************************************/
/* @req COM042 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_InitMsgRecUnQueuedInternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr
)
{
    StatusType ret = E_OK;

    if ((msgCfgPtr->sendMsgPtr != NULL_PTR)
        #if (OSEK_COM_CCC == OSEK_COM_CCC1)
        && (msgCfgPtr->filterPtr != NULL_PTR)
        #endif
        && ((COM_MSG_SEND_STATIC_INTERNAL == msgCfgPtr->sendMsgPtr->property)
        #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
        ||(COM_MSG_SEND_STATIC_EXTERNAL == msgCfgPtr->sendMsgPtr->property)
        #endif
        ))
    {
        uint16 msgLength;
        msgLength = Com_GetCDataByteSize(msgCfgPtr->sendMsgPtr->cData);
        msgPrivatePtr->queue.bufPtr = (uint8*)Com_Malloc(msgLength);
        
        if (msgPrivatePtr->queue.bufPtr != NULL_PTR)
        {
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            msgPrivatePtr->msgOldValue = Com_InitValueToU32(msgCfgPtr->cData,
                                                            (void *)msgCfgPtr->initialValue);
            msgPrivatePtr->occurrence = 0;
            #endif
            SchM_Enter_Com(WRITE_PROTECTION_AREA);
            Com_Memcpy(msgPrivatePtr->queue.bufPtr,
                       msgCfgPtr->initialValue,
                       msgLength);
            SchM_Exit_Com(WRITE_PROTECTION_AREA);
        }
        else
        {
            ret = E_COM_LENGTH;
        }
    }
    else
    {
        ret = E_COM_ID;
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to initialize receive unqueued
 *                       internal message value.>
 * Param-Name[in]        <msgPrivatePtr : static external send message run
 *                                       time structure.
 *                       msgCfgPtr : static external send message
 *                                   configuration pointer
 *                       appDataRef : application data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <Com_InitVal>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_InitValRecUnQueuedInternal
(
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataRef
)
{
    /* assign internel receive message initial value */
    uint16 msgLength;

    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    msgPrivatePtr->msgOldValue = Com_InitValueToU32(msgCfgPtr->cData,
                                                    appDataRef);
    #endif
    msgLength = Com_GetCDataByteSize(msgCfgPtr->sendMsgPtr->cData);
    SchM_Enter_Com(WRITE_PROTECTION_AREA);
    Com_Memcpy(msgPrivatePtr->queue.bufPtr,
               (const uint8 *)appDataRef,
                msgLength);
    SchM_Exit_Com(WRITE_PROTECTION_AREA);
    
    return;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to send static internal message.>
 * Param-Name[in]        <msgCfgPtr : static external send message
 *                                   configuration pointer
 *                       appDataRef : application data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : initialize successfully
 *                       E_COM_LIMIT : queue is full>
 * PreCondition          <None>
 * CallByAPI             <Com_SendMessage>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgSendStaticInternal
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataPtr
)
{
    StatusType ret = E_OK;
    uint16 msgIndex;
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgRecCfgPtr;

    for (msgIndex = 0u;
        msgIndex < Com_CfgPtr->msgUsedNum;
        msgIndex++)
    {
        msgRecCfgPtr = &Com_CfgPtr->messagePtr[msgIndex];
        
        if (msgRecCfgPtr->sendMsgPtr == msgCfgPtr)
        {
            /* the sent internel message is direct copy to message receiver */
            #if (OSEK_COM_CCC == OSEK_COM_CCC1)
            if (TRUE == Com_Filter(appDataPtr,
                                  msgRecCfgPtr,
                                  &Com_PrivateMsg[msgIndex]))
            #endif
            {
                ret = Com_MsgRecStaticInternel(msgRecCfgPtr,
                                               &Com_PrivateMsg[msgIndex],
                                               appDataPtr);
            }
        }
    }
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is used to receive static internal message.>
 * Param-Name[in]        <msgCfgPtr : static external receive message
 *                                   configuration pointer
 *                       msgPrivatePtr : message run time structure pointer
 *                       appDataPtr : application data pointer>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK : initialize successfully
 *                       E_COM_LIMIT : queue is full>
 * PreCondition          <None>
 * CallByAPI             <Com_MsgReceive>
 */
/******************************************************************************/
/* @req COM006 */
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(StatusType, COM_CODE)
Com_MsgRecStaticInternel
(
    P2CONST(Com_MsgType, AUTOMATIC, COM_CONST_PBCFG)msgCfgPtr,
    P2VAR(Com_MsgRunTimeType, AUTOMATIC, COM_VAR)msgPrivatePtr,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)appDataPtr
)
{
    StatusType ret = E_OK;

    if (COM_MSG_RECEIVE_UNQUEUED_INTERNAL == msgCfgPtr->property)
    {
        uint16 msgLength = Com_GetCDataByteSize(msgCfgPtr->sendMsgPtr->cData);

        SchM_Enter_Com(WRITE_PROTECTION_AREA);
        Com_Memcpy(msgPrivatePtr->queue.bufPtr,
                (const uint8 *)appDataPtr,
                msgLength);
        SchM_Exit_Com(WRITE_PROTECTION_AREA);

        if (msgCfgPtr->msgNotif != NULL_PTR)
        {
            msgCfgPtr->msgNotif();
        }
    }
    #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
    else
    {
        boolean queueStatus;
        queueStatus = Com_QueueBufInsert(&msgPrivatePtr->queue,
                                         (uint8*)appDataPtr);
        if (FALSE == queueStatus)
        {
            ret = E_COM_LIMIT;
            msgPrivatePtr->messageStatus = E_COM_LIMIT;
        }
        else
        {
            msgPrivatePtr->messageStatus = E_OK;
        }
        
        if ((E_OK == ret)
            && (msgCfgPtr->msgNotif != NULL_PTR))
        {
            msgCfgPtr->msgNotif();
        }
    }
    #endif
    return ret;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#if (OSEK_COM_CCC == OSEK_COM_CCC1)
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduGroupStart_TX
(
    boolean Initialize
)
{
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    uint16 loop;
    #endif

    /* @req COM231 */
    /* init filter variable for COM_F_OneEveryN */
    for (loop = 0u; loop < Com_CfgPtr->msgUsedNum; loop++)
    {
        if ((NULL_PTR != Com_CfgPtr->messagePtr[loop].filterPtr)
             && (COM_F_OneEveryN == Com_CfgPtr->messagePtr[loop].filterPtr->filterAlgorithm)
             && (Com_CfgPtr->messagePtr[loop].NWMsgPtr != NULL_PTR)
             && (COM_MSG_SENT == Com_CfgPtr->messagePtr[loop].NWMsgPtr->direction))
        {
            Com_PrivateMsg[loop].occurrence = 0u;
        }
    }

    for (loop = 0u; loop < Com_CfgPtr->ipduUsedNum; loop++)
    {
        if (COM_IPDU_SENT == Com_CfgPtr->ipduPtr[loop].direction)
        {
            if (COM_IPDU_TRANSMIT_PERIODIC != Com_CfgPtr->ipduPtr[loop].transmitMode)
            {
                Com_PrivateIPdu[loop].mdtTimer = 0u;
            }
            Com_PrivateIPdu[loop].DMTimer = 0;

            /* start period Timer for non direct transmission mode */
            if (COM_IPDU_TRANSMIT_DIRECT != Com_CfgPtr->ipduPtr[loop].transmitMode)
            {
                if (TRUE == Initialize)
                {
                    Com_PrivateIPdu[loop].periodTimer = Com_CfgPtr->ipduPtr[loop].timeOffset / Com_CfgPtr->timeBase;
                }
                else
                {
                    Com_PrivateIPdu[loop].periodTimer = Com_CfgPtr->ipduPtr[loop].timePeriod / Com_CfgPtr->timeBase;
                }
            }
        }
    }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_IpduGroupStart_RX
(
    boolean Initialize
)
{
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    uint16 loop;
    #endif

    /* @req COM231 */
    for (loop = 0u; loop < Com_CfgPtr->msgUsedNum; loop++)
    {
        /* init filter variable for COM_F_OneEveryN */
        if ((NULL_PTR != Com_CfgPtr->messagePtr[loop].filterPtr)
             && (COM_F_OneEveryN == Com_CfgPtr->messagePtr[loop].filterPtr->filterAlgorithm)
             && (Com_CfgPtr->messagePtr[loop].NWMsgPtr != NULL_PTR)
             && (COM_MSG_RECEIVED == Com_CfgPtr->messagePtr[loop].NWMsgPtr->direction))
        {
            Com_PrivateMsg[loop].occurrence = 0u;
        }
    }

    /* init deadline monitor timer for every I-PDU */
    for (loop = 0u; loop < Com_CfgPtr->ipduUsedNum; loop++)
    {
        if (COM_IPDU_RECEIVE == Com_CfgPtr->ipduPtr[loop].direction)
        {
            if (TRUE == Initialize)
            {
                Com_PrivateIPdu[loop].DMTimer = Com_CfgPtr->ipduPtr[loop].firstTimeOut / Com_CfgPtr->timeBase;
            }
            else
            {
                Com_PrivateIPdu[loop].DMTimer = Com_CfgPtr->ipduPtr[loop].timeOut / Com_CfgPtr->timeBase;
            }
        }
    }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (OSEK_COM_CCC == OSEK_COM_CCC1)
#define COM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, COM_CODE)
Com_RepDMHandle(uint16 loop) 
{ 
    /* reception deadline monitoring,if timeout,notify RTE for every signal,reset DM */
    /* @req COM118 */
    if ((TRUE == Com_IpduGroupRepDMEnable) && (Com_PrivateIPdu[loop].DMTimer > 0u))
    {
        Com_PrivateIPdu[loop].DMTimer--;

        /* @req COM121 */
        if (0u == Com_PrivateIPdu[loop].DMTimer)
        {
            /* I-PDU timeout notification */
            /* @req COM144 */
            Com_NotifDM(Com_CfgPtr->ipduPtr[loop].pduId);
            /* reset deadline monitor timer */
            Com_PrivateIPdu[loop].DMTimer = Com_CfgPtr->ipduPtr[loop].timeOut / Com_CfgPtr->timeBase;
        }
    }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*=======[E N D   O F   F I L E]==============================================*/
