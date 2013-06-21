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
 *  V1.0.0       20081127  James       Initial version
 * 
 *  V1.1.0       20091012  Michael     As per ADC171, ADC_E_NO_DB is changed
 *                                     to ADC_E_INVALID_DATABASE.
 * 
 *  V2.0.0       20100210  Z.YX        As per SCR 186, Adc_Init and Adc_DeInit
 *                                     are updated to use IMRm register instead
 *                                     of xxICn register.
 */
/*============================================================================*/

/*=======[M I S R A  R U L E  V I O L A T I O N]==============================*/
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */
/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 17.4; REFERENCE - ISO:C90-6.3.6 Additive Operators - Constraints */

/*=======[I N C L U D E S]====================================================*/
#include "MemMap.h"
#include "Det.h"
#include "Icu.h"
//#include "Icu_Cbk.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define ICU_C_AR_MAJOR_VERSION    3
#define ICU_C_AR_MINOR_VERSION    0
#define ICU_C_AR_PATCH_VERSION    2

#define ICU_C_SW_MAJOR_VERSION    1
#define ICU_C_SW_MINOR_VERSION    0
#define ICU_C_SW_PATCH_VERSION    0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (ICU_C_AR_MAJOR_VERSION != ICU_H_AR_MAJOR_VERSION)
  #error "ICU.c : Mismatch in Specification Major Version"
#endif
#if (ICU_C_AR_MINOR_VERSION != ICU_H_AR_MINOR_VERSION)
  #error "ICU.c : Mismatch in Specification Major Version"
#endif
#if (ICU_C_AR_PATCH_VERSION != ICU_H_AR_PATCH_VERSION)
  #error "ICU.c : Mismatch in Specification Major Version"
#endif
#if (ICU_C_SW_MAJOR_VERSION != ICU_H_SW_MAJOR_VERSION)
  #error "ICU.c : Mismatch in Specification Major Version"
#endif
#if (ICU_C_SW_MINOR_VERSION != ICU_H_SW_MINOR_VERSION)
  #error "ICU.c : Mismatch in Specification Major Version"
#endif
#if (ICU_C_SW_PATCH_VERSION != ICU_H_SW_PATCH_VERSION)
  #error "ICU.c : Mismatch in Specification Major Version"
#endif

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/
P2CONST(Icu_ConfigType, AUTOMATIC, ICU_CONST) Icu_GlobalConfig = NULL_PTR;

VAR(Icu_ChannelInfoType, ICU_VAR) Icu_GlobalChannelInfo =
{
    FALSE,
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

    {ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,
     ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,
     ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE,ICU_IDLE},

    {ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,
     ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,
     ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,
     ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,
     ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL,ICU_MODE_NORMAL},

    {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,
     FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE},

    {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,
     FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE},

    #if (STD_ON == ICU_EDGE_COUNT_API)
    {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,
     FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE},
    #endif /* STD_ON == ICU_EDGE_COUNT_API */

    #if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)
    {FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,
     FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE},
    #endif /* STD_ON == ICU_SIGNAL_MEASUREMENT_API */
};

VAR(Icu_GlobalParameterType, ICU_VAR) Icu_GlobalParameter =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
     NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},

    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

    #if (STD_ON == ICU_EDGE_COUNT_API)
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    #endif /* STD_ON == ICU_EDGE_COUNT_API */

    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

    {{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
     {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},
};

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#define ICU_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ICU_CODE) Icu_ConfigModuleClock(void);
STATIC FUNC(void, ICU_CODE) Icu_SetMeasurementMode(uint16 channelId, Icu_MeasurementModeType Mode);
STATIC FUNC(void, ICU_CODE) Icu_SetActEdge(uint16 channelId, Icu_ActivationType Edge);
STATIC FUNC(void, ICU_CODE) Icu_EnableChannel(uint16 channel);
STATIC FUNC(void, ICU_CODE) Icu_DisableChannel(uint16 channel);
STATIC FUNC(void, ICU_CODE) Icu_HwDeInit(uint16 channel);
STATIC FUNC(void, ICU_CODE) Icu_SetHwMode(Icu_ModeType Mode);
STATIC FUNC(void, ICU_CODE) Icu_SetHwActivation(P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel,\
                                                Icu_ActivationType Activation);
STATIC FUNC(void, ICU_CODE) Icu_EnableInt(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);
STATIC FUNC(void, ICU_CODE) Icu_DisableInt(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);
STATIC FUNC(void, ICU_CODE) Icu_StartInputCapture(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);
STATIC FUNC(void, ICU_CODE) Icu_StopInputCapture(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);
STATIC FUNC(void, ICU_CODE) Icu_ResetEdgeCounter(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);
STATIC FUNC(void, ICU_CODE) Icu_StartHwSigMeas(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/*
 * Brief               <This function initializes the driver.>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) Icu_Init(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST)ConfigPtr)
{
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;
    uint16 channelId;

    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    /** @req ICU023 */
    if (NULL == ConfigPtr)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_INIT_ID, ICU_E_PARAM_CONFIG);
        return;
    }
    /** @req ICU220 */
    if (TRUE == Icu_GlobalChannelInfo.initrun)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_INIT_ID, ICU_E_ALREADY_INITIALIZED);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    Icu_GlobalConfig = ConfigPtr;
    Icu_GlobalChannelInfo.initrun = TRUE;

    /** @req ICU051 @req ICU052 @req ICU053 @req ICU128 @req ICU129 */
    Icu_ConfigModuleClock();

    /** @req ICU006 @req ICU054 */
    maxChannel = Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel;
    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    while (maxChannel > ZERO)
    {
        /*Get the current channel ID.*/
        channelId = oneChannel->IcuChannelId;
        Icu_GlobalChannelInfo.IcuChannel[channelId] = channelId;

        /** @req ICU121 */
        Icu_GlobalChannelInfo.IcuWakeupCapability[channelId] = FALSE;

        Icu_GlobalChannelInfo.IcuEdgeCountSwitch[channelId] = FALSE;

        /* @req ICU061 */
        Icu_DisableNotification(channelId);

        /* @req ICU040 */
        Icu_GlobalChannelInfo.IcuInputStatus[channelId] = ICU_IDLE;

        /* @req ICU060 */
        Icu_GlobalChannelInfo.IcuMode[channelId] = ICU_MODE_NORMAL;

        Icu_SetMeasurementMode(oneChannel->IcuChannelId, oneChannel->IcuMeasurementMode);
        Icu_SetActEdge(oneChannel->IcuChannelId, oneChannel->IcuDefaultStartEdge);

        /* Enable the channelId Channel */
        Icu_EnableChannel(channelId);

        oneChannel++;
        maxChannel--;
    }

    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function de-initializes the ICU module.>
 * ServiceId           <0x01>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU092 */
#if (STD_ON == ICU_DEINIT_API)
FUNC(void, ICU_CODE) Icu_DeInit(void)
{
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;
    uint16 channelId;

    /** @req ICU091 @req ICU221 @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DEINIT_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    /** @req ICU036 @req ICU091 */
    maxChannel = Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel;
    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    while (maxChannel > ZERO)
    {
        /* Get the current channel ID */
        channelId = oneChannel->IcuChannelId;

        /** @req ICU152 */
        if (Icu_GlobalChannelInfo.IcuInputStatus[channelId] != ICU_IDLE)
        {
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DEINIT_ID, ICU_E_BUSY_OPERATION);
            return;
        }

        /** @req ICU037 */
        Icu_GlobalChannelInfo.IcuWakeupCapability[channelId] = FALSE;
        Icu_GlobalChannelInfo.IcuEdgeCountSwitch[channelId] = FALSE;
        Icu_DisableNotification(channelId);

        Icu_HwDeInit(channelId);

        oneChannel++;
        maxChannel--;
    }

    Icu_GlobalChannelInfo.initrun = FALSE;
    return;
}
#endif /* STD_ON == ICU_DEINIT_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function sets the ICU mode.>
 * ServiceId           <0x02>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU095 */
#if (STD_ON == ICU_SET_MODE_API)
FUNC(void, ICU_CODE) Icu_SetMode(Icu_ModeType Mode)
{
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    /** @req ICU022 */
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_SETMODE_ID, ICU_E_UNINIT);
        return;
    }
    /** @req ICU125 */
    if ((Mode < ICU_MODE_NORMAL) || (Mode > ICU_MODE_SLEEP))
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_SETMODE_ID, ICU_E_PARAM_MODE);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    Icu_SetHwMode(Mode);

    return;
}
#endif /* STD_ON == ICU_SET_MODE_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function disables the wakeup capability of a single ICU channel.>
 * ServiceId           <0x03>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU096 */
#if (STD_ON == ICU_DISABLE_WAKEUP_API)
FUNC(void, ICU_CODE) Icu_DisableWakeup(Icu_ChannelType Channel)
{
    Icu_ChannelType currentChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

   	/** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DISABLE_WAKEUP_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
   	maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != currentChannel)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU024 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DISABLE_WAKEUP_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    /** @req ICU013 @req ICU059 */
    if (TRUE == oneChannel->IcuWakeupCapability)
    {
        /* disable wakeup */
        Icu_GlobalChannelInfo.IcuWakeupCapability[currentChannel] = FALSE;
    }
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    else
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DISABLE_WAKEUP_ID, ICU_E_PARAM_CHANNEL);
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    return;
}
#endif /* STD_ON == ICU_DISABLE_WAKEUP_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function (re-)enables the wakeup capability of the given ICU channel.>
 * ServiceId           <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU097 */
#if (STD_ON == ICU_ENABLE_WAKEUP_API)
FUNC(void, ICU_CODE) Icu_EnableWakeup(Icu_ChannelType Channel)
{
    Icu_ChannelType currentChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_ENABLE_WAKEUP_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != currentChannel)
    {
        /* find the position of the current channel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU155 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_ENABLE_WAKEUP_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    /** @req ICU014 @req ICU156 */
    if (TRUE == oneChannel->IcuWakeupCapability)
    {
        /* enable wakeup */
        Icu_GlobalChannelInfo.IcuWakeupCapability[currentChannel] = TRUE;
    }
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    else
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_ENABLE_WAKEUP_ID, ICU_E_PARAM_CHANNEL);
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    return;
}
#endif /* STD_ON == ICU_ENABLE_WAKEUP_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function sets the activation-edge for the given channel.>
 * ServiceId           <0x05>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel, Activation>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) Icu_SetActivationCondition(Icu_ChannelType Channel, Icu_ActivationType Activation)
{
    Icu_ChannelType targetChannel = Channel;
    Icu_ActivationType targetActivation = Activation;

    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    /** @req ICU022 */
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_SET_ACTIVATION_CONDITION_ID, ICU_E_UNINIT);
        return;
    }
    /** @req ICU043 */
    if ((Activation < ICU_FALLING_EDGE) || (Activation > ICU_BOTH_EDGE))
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_SET_ACTIVATION_CONDITION_ID, ICU_E_PARAM_ACTIVATION);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        /* find the position of the current channel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU159 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_SET_ACTIVATION_CONDITION_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    /* change IcuDefaultStartEdge value */
    oneChannel->IcuDefaultStartEdge = targetActivation;

    /** @req ICU090 */
    if (ICU_MODE_SIGNAL_MEASUREMENT == oneChannel->IcuMeasurementMode)
    {
        return;
    }

    Icu_SetHwActivation(oneChannel, targetActivation);

    /** @req ICU139 */
    Icu_GlobalChannelInfo.IcuInputStatus[oneChannel->IcuChannelId] = ICU_IDLE;

    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function disables the notification of a channel.>
 * ServiceId           <0x06>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) Icu_DisableNotification(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DISABLE_NOTIFICATION_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        /* find the position of the current channel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU160 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DISABLE_NOTIFICATION_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    /** @req ICU009 */
    Icu_GlobalChannelInfo.IcuNotificationSwitch[targetChannel] = FALSE;

    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function enables the notification on the given channel.>
 * ServiceId           <0x07>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) Icu_EnableNotification(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_ENABLE_NOTIFICATION_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        /* find the position of the current channel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU161 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_ENABLE_NOTIFICATION_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */
            return;
        }
        maxChannel--;
    }

    /** @req ICU010 */
    Icu_GlobalChannelInfo.IcuNotificationSwitch[targetChannel] = TRUE;

    /** @req ICU127 */
    if (ICU_MODE_SIGNAL_EDGE_DETECT == oneChannel->IcuMeasurementMode)
    {
        /* disable the all interrupt */
        Icu_DisableInt(oneChannel);
        Icu_EnableInt(oneChannel);
    }

    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function returns the status of ICU input.>
 * ServiceId           <0x08>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Icu_InputStateType>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU122 */
#if (STD_ON == ICU_GET_INPUT_STATE_API)
FUNC(Icu_InputStateType, ICU_CODE) Icu_GetInputState(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    Icu_InputStateType stateType = ICU_IDLE;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 @req ICU049 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_INPUTSTATE_ID, ICU_E_UNINIT);
        return stateType;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU162 @req ICU049 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_INPUTSTATE_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return stateType;
        }
        maxChannel--;
    }

    /** @req ICU030 @req ICU162 @req ICU049 */
    if ((ICU_MODE_TIMESTAMP == oneChannel->IcuMeasurementMode) ||\
        (ICU_MODE_EDGE_COUNTER == oneChannel->IcuMeasurementMode))
    {
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_INPUTSTATE_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        return stateType;
    }

    /** @req ICU031 @req ICU033 */
    if (ICU_ACTIVE == Icu_GlobalChannelInfo.IcuInputStatus[oneChannel->IcuChannelId])
    {
        stateType = ICU_ACTIVE;
    }
    else
    {
        stateType = ICU_IDLE;
    }

    /** @req ICU032 */
    Icu_GlobalChannelInfo.IcuInputStatus[oneChannel->IcuChannelId] = ICU_IDLE;
    return stateType;
}
#endif /* STD_ON == ICU_GET_INPUT_STATE_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function starts the capturing of timer values on the edges.>
 * ServiceId           <0x09>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel, BufferPtr, BufferSize, NotifyInterval>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU098 */
#if (STD_ON == ICU_TIMESTAMP_API)
FUNC(void, ICU_CODE) Icu_StartTimestamp(Icu_ChannelType Channel, P2VAR(Icu_ValueType, AUTOMATIC, ICU_VAR) BufferPtr,\
                                        uint16 BufferSize, uint16 NotifyInterval)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ValueType, AUTOMATIC, ICU_VAR) targetBufferPtr = BufferPtr;
    uint16 targetBufferSize = BufferSize;
    uint16 targetNotifyInterval = NotifyInterval;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    /** @req ICU022 */
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_START_TIMESTAMP_ID, ICU_E_UNINIT);
        return;
    }
    /** @req ICU120 */
    if (NULL_PTR == targetBufferPtr)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_START_TIMESTAMP_ID, ICU_E_PARAM_BUFFER_PTR);
        return;
    }
    /** @req ICU108 */
    if (targetBufferSize <= ZERO)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_START_TIMESTAMP_ID, ICU_E_PARAM_BUFFER_SIZE);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        /* find the position of the current channel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU163 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_START_TIMESTAMP_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    Icu_GlobalParameter.TimestampBuffer[oneChannel->IcuChannelId] = targetBufferPtr;
    Icu_GlobalParameter.TimestampBufferSize[oneChannel->IcuChannelId] = targetBufferSize;
    Icu_GlobalParameter.TimestampNotifyInterval[oneChannel->IcuChannelId] = targetNotifyInterval;

    /** @req ICU066 */
    if (oneChannel->IcuMeasurementMode != ICU_MODE_TIMESTAMP)
    {
        /** @req ICU163 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_START_TIMESTAMP_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        return;
    }

    /** @req ICU063 */
    Icu_StartInputCapture(oneChannel);

    return;
}
#endif /* STD_ON == ICU_TIMESTAMP_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function stops the timestamp measurement of the given channel.>
 * ServiceId           <0x0a>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU099 */
#if (STD_ON == ICU_TIMESTAMP_API)
FUNC(void, ICU_CODE) Icu_StopTimestamp(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    /** @req ICU022 */
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_STOP_TIMESTAMP_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        /* find the position of the current channel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU164 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_STOP_TIMESTAMP_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    /** @req ICU166 */
    if (Icu_GlobalChannelInfo.IcuInputStatus[targetChannel] != ICU_ACTIVE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_STOP_TIMESTAMP_ID, ICU_E_NOT_STARTED);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    /** @req ICU165 */
    if (oneChannel->IcuMeasurementMode != ICU_MODE_TIMESTAMP)
    {
        /** @req ICU164 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_STOP_TIMESTAMP_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        return;
    }

    /** @req ICU067 */
    Icu_StopInputCapture(oneChannel);

    Icu_GlobalChannelInfo.IcuNotificationSwitch[targetChannel] = FALSE;
    Icu_GlobalChannelInfo.IcuInputStatus[targetChannel] = ICU_IDLE;

    return;
}
#endif /* STD_ON == ICU_TIMESTAMP_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function reads the timestamp index of the given channel.>
 * ServiceId           <0x0b>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Icu_IndexType>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU100 */
#if (STD_ON == ICU_TIMESTAMP_API)
FUNC(Icu_IndexType, ICU_CODE) Icu_GetTimestampIndex(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    Icu_IndexType indexType = ZERO;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    /** @req ICU022 @req ICU107 */
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_TIMESTAMP_INDEX_ID, ICU_E_UNINIT);
        return indexType;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        /* find the position of the current channel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU169 @req ICU107 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_TIMESTAMP_INDEX_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */
            return indexType;
        }
        maxChannel--;
    }

    /** @req ICU170 */
    if (oneChannel->IcuMeasurementMode != ICU_MODE_TIMESTAMP)
    {
        /** @req ICU169 @req ICU107 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_TIMESTAMP_INDEX_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        indexType = ZERO;
        return indexType;
    }

    /** @req ICU071 */
    indexType = Icu_GlobalParameter.TimestampBufferIndex[targetChannel];
    return indexType;
}
#endif /* STD_ON == ICU_TIMESTAMP_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function resets the value of the counted edges to zero.>
 * ServiceId           <0x0c>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU101 */
#if (STD_ON == ICU_EDGE_COUNT_API)
FUNC(void, ICU_CODE) Icu_ResetEdgeCount(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_RESET_EDGE_COUNT_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU171 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_RESET_EDGE_COUNT_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    if (oneChannel->IcuMeasurementMode != ICU_MODE_EDGE_COUNTER)
    {
        /** @req ICU171 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_RESET_EDGE_COUNT_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        return;
    }

    /** @req ICU072 */
    Icu_ResetEdgeCounter(oneChannel);

    return;
}
#endif /* STD_ON == ICU_EDGE_COUNT_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function enables the counting of edges of the given channel.>
 * ServiceId           <0x0d>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU102 */
#if (STD_ON == ICU_EDGE_COUNT_API)
FUNC(void, ICU_CODE) Icu_EnableEdgeCount(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_ENABLE_EDGE_COUNT_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU172 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_ENABLE_EDGE_COUNT_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    /** @req ICU074 */
    if (oneChannel->IcuMeasurementMode != ICU_MODE_EDGE_COUNTER)
    {
        /** @req ICU172 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_ENABLE_EDGE_COUNT_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        return;
    }

    /** @req ICU078 @req ICU073 */
    Icu_GlobalParameter.EdgeCounterIndex[oneChannel->IcuChannelId] = ZERO;
    Icu_GlobalChannelInfo.IcuEdgeCountSwitch[oneChannel->IcuChannelId] = TRUE;
    Icu_StartInputCapture(oneChannel);

    return;
}
#endif /* STD_ON == ICU_EDGE_COUNT_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function disables the counting of edges of the given channel.>
 * ServiceId           <0x0e>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU103 */
#if (STD_ON == ICU_EDGE_COUNT_API)
FUNC(void, ICU_CODE) Icu_DisableEdgeCount(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DISABLE_EDGE_COUNT_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU173 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DISABLE_EDGE_COUNT_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    if (oneChannel->IcuMeasurementMode != ICU_MODE_EDGE_COUNTER)
    {
        /** @req ICU173 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DISABLE_EDGE_COUNT_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        return;
    }

    /** @req ICU079 */
    Icu_GlobalChannelInfo.IcuEdgeCountSwitch[oneChannel->IcuChannelId] = FALSE;

    return;
}
#endif /* STD_ON == ICU_EDGE_COUNT_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function reads the number of counted edges.>
 * ServiceId           <0x0f>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Icu_EdgeNumberType>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU104 */
#if (STD_ON == ICU_EDGE_COUNT_API)
FUNC(Icu_EdgeNumberType, ICU_CODE) Icu_GetEdgeNumbers(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 @req ICU175 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_EDGE_NUMBERS_ID, ICU_E_UNINIT);
        return ZERO;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU174 @req ICU175 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_EDGE_NUMBERS_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return ZERO;
        }
        maxChannel--;
    }

    if (oneChannel->IcuMeasurementMode != ICU_MODE_EDGE_COUNTER)
    {
        /** @req ICU174 @req ICU175 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_DISABLE_EDGE_COUNT_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        return ZERO;
    }

    /** @req ICU080 */
    return Icu_GlobalParameter.EdgeCounterIndex[oneChannel->IcuChannelId];
}
#endif /* STD_ON == ICU_EDGE_COUNT_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function starts the measurement of signals.>
 * ServiceId           <0x13>
 * Sync/Async          <ASynchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU142 */
#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)
FUNC(void, ICU_CODE) Icu_StartSignalMeasurement(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_START_SIGNAL_MEASUREMENT_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU176 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_START_SIGNAL_MEASUREMENT_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    /** @req ICU141 */
    if (oneChannel->IcuMeasurementMode != ICU_MODE_SIGNAL_MEASUREMENT)
    {
        /** @req ICU176 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_START_SIGNAL_MEASUREMENT_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        return;
    }

    /** @req ICU140 */
    Icu_StartHwSigMeas(oneChannel);
    Icu_GlobalChannelInfo.IcuSignalMeasurementSwitch[oneChannel->IcuChannelId] = TRUE;

    /** @req ICU146 */
    Icu_GlobalChannelInfo.IcuInputStatus[oneChannel->IcuChannelId] = ICU_IDLE;

    return;

}
#endif /* STD_ON == ICU_SIGNAL_MEASUREMENT_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function stops the measurement of signals of the given channel.>
 * ServiceId           <0x14>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU145 */
#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)
FUNC(void, ICU_CODE) Icu_StopSignalMeasurement(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_STOP_SIGNAL_MEASUREMENT_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU177 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_STOP_SIGNAL_MEASUREMENT_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    /** @req ICU144 */
    if (oneChannel->IcuMeasurementMode != ICU_MODE_SIGNAL_MEASUREMENT)
    {
        /** @req ICU177 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_STOP_SIGNAL_MEASUREMENT_ID, ICU_E_PARAM_CHANNEL);
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        return;
    }

    Icu_GlobalChannelInfo.IcuNotificationSwitch[targetChannel] = FALSE;

    /** @req ICU143 */
    Icu_GlobalChannelInfo.IcuSignalMeasurementSwitch[oneChannel->IcuChannelId] = FALSE;
    Icu_GlobalChannelInfo.IcuInputStatus[oneChannel->IcuChannelId] = ICU_IDLE;

    return;
}
#endif /* STD_ON == ICU_SIGNAL_MEASUREMENT_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function reads the elapsed Signal Low Time for the given channel.>
 * ServiceId           <0x10>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Icu_ValueType>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU105 */
#if (STD_ON == ICU_GET_TIME_ELAPSED_API)
FUNC(Icu_ValueType, ICU_CODE) Icu_GetTimeElapsed(Icu_ChannelType Channel)
{
    Icu_ChannelType targetChannel = Channel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;

    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_TIME_ELAPED_ID, ICU_E_UNINIT);
        return ZERO;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU178 @req ICU179 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_TIME_ELAPED_ID, ICU_E_PARAM_CHANNEL);
            #endif

            return ZERO;
        }
        maxChannel--;
    }

    if (oneChannel->IcuMeasurementMode != ICU_MODE_SIGNAL_MEASUREMENT)
    {
        /** @req ICU178 @req ICU179 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_TIME_ELAPED_ID, ICU_E_PARAM_CHANNEL);
        #endif

        return ZERO;
    }

    return Icu_GlobalParameter.TimeElaspedValue[oneChannel->IcuChannelId];
}
#endif /* STD_ON == ICU_GET_TIME_ELAPSED_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function reads the coherent active time and period time for the given ICU Channel.>
 * ServiceId           <0x11>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <DutyCycleValues>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU106 */
#if (STD_ON == ICU_GET_DUTYCYCLE_VALUES_API)
FUNC(void, ICU_CODE) Icu_GetDutyCycleValues(Icu_ChannelType Channel,\
                                            P2VAR(Icu_DutyCycleType, AUTOMATIC, ICU_VAR) DutyCycleValues)
{
    Icu_ChannelType targetChannel = Channel;

    Icu_SignalMeasurementPropertyType measurementProperty;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;
    Icu_ValueType activeTime = ZERO;
    Icu_ValueType periodTime = ZERO;

    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    /** @req ICU022 */
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_DUTYCYCLE_VALUES_ID, ICU_E_UNINIT);
        return;
    }
    /** @req ICU181 */
    if (NULL == DutyCycleValues)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_DUTYCYCLE_VALUES_ID, ICU_E_PARAM_BUFFER_PTR);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != targetChannel)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            /** @req ICU180 */
            #if (STD_ON == ICU_DEV_ERROR_DETECT)
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_DUTYCYCLE_VALUES_ID, ICU_E_PARAM_CHANNEL);
            #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

            return;
        }
        maxChannel--;
    }

    measurementProperty = oneChannel->IcuSignalMeasurement.IcuSignalMeasurementProperty;
    /** @req ICU084 */
    if ((oneChannel->IcuMeasurementMode != ICU_MODE_SIGNAL_MEASUREMENT) || (measurementProperty != ICU_DUTY_CYCLE))
    {
        /** @req ICU180 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_DUTYCYCLE_VALUES_ID, ICU_E_PARAM_CHANNEL);
        #endif

        return;
    }

    /** @req ICU137 */
    if (ZERO == Icu_GlobalParameter.DutyCycleBuffer[oneChannel->IcuChannelId].ActiveTime)
    {
        activeTime = ZERO;
    }
    else
    {
        activeTime = Icu_GlobalParameter.DutyCycleBuffer[oneChannel->IcuChannelId].ActiveTime;
        Icu_GlobalParameter.DutyCycleBuffer[oneChannel->IcuChannelId].ActiveTime = ZERO;
    }

    if (ZERO == Icu_GlobalParameter.DutyCycleBuffer[oneChannel->IcuChannelId].PeriodTime)
    {
        periodTime = ZERO;
    }
    else
    {
        periodTime = Icu_GlobalParameter.DutyCycleBuffer[oneChannel->IcuChannelId].PeriodTime;
        Icu_GlobalParameter.DutyCycleBuffer[oneChannel->IcuChannelId].PeriodTime = ZERO;
    }

    (*DutyCycleValues).ActiveTime = activeTime;
    (*DutyCycleValues).PeriodTime = periodTime;

    return;
}
#endif /* STD_ON == ICU_GET_DUTYCYCLE_VALUES_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function returns the version information of this module.>
 * ServiceId           <0x12>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <versioninfo>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

/** @req ICU094 */
#if (STD_ON == ICU_GET_VERSION_INFO_API)
FUNC(void, ICU_CODE) Icu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ICU_VAR) versioninfo)
{
    /** @req ICU022 */
    #if (STD_ON == ICU_DEV_ERROR_DETECT)
    if (Icu_GlobalChannelInfo.initrun != TRUE)
    {
        Det_ReportError(MODULE_ID_ICU, ZERO, ICU_GET_VERSION_INFO_ID, ICU_E_UNINIT);
        return;
    }
    #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

    versioninfo->vendorID = ICU_VENDOR_ID;
    versioninfo->moduleID = ICU_MODULE_ID;
    versioninfo->ar_major_version = ICU_H_AR_MAJOR_VERSION;
    versioninfo->ar_minor_version = ICU_H_AR_MINOR_VERSION;
    versioninfo->ar_patch_version = ICU_H_AR_PATCH_VERSION;
    versioninfo->sw_major_version = ICU_H_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = ICU_H_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = ICU_H_SW_PATCH_VERSION;
    versioninfo->instanceID = ICU_VENDOR_API_INFIX;

    return;
}
#endif /* STD_ON == ICU_GET_VERSION_INFO_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/*=======[L O C A L   F U N C T I O N   I M P L E M E N T A T I O N S]========*/

/******************************************************************************/
/*
 * Brief               <Set relative registers of clock.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_Init> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_ConfigModuleClock(void)
{
    /* Divide sysclk by 1 as the eMIOS clk*/
    EMIOS.MCR.B.GPRE = (BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0); //63

    /* Enable eMIOS clock */
    EMIOS.MCR.B.GPREN = BIT0;

    /* Enable global time base */
    EMIOS.MCR.B.GTBE = BIT0;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers of mode selection.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channelId, Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_Init> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_SetMeasurementMode(uint16 channelId, Icu_MeasurementModeType Mode)
{
    if(ICU_MODE_SIGNAL_EDGE_DETECT == Mode)
    {
        EMIOS.CH[channelId].CCR.B.MODE = BIT1;
    }
    else if(ICU_MODE_SIGNAL_MEASUREMENT == Mode)
    {
        EMIOS.CH[channelId].CCR.B.MODE = BIT1;
    }
    else if(ICU_MODE_TIMESTAMP == Mode)
    {
        EMIOS.CH[channelId].CCR.B.MODE = BIT1;
    }
    else if(ICU_MODE_EDGE_COUNTER == Mode)
    {
        EMIOS.CH[channelId].CCR.B.MODE = BIT1;
    }
    else
    {
        /* empty */
    }
    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers of edge selection.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channelId, Edge>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_Init> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_SetActEdge(uint16 channelId, Icu_ActivationType Edge)
{
    if(ICU_FALLING_EDGE == Edge)
    {
        EMIOS.CH[channelId].CCR.B.EDSEL = ZERO;
        EMIOS.CH[channelId].CCR.B.EDPOL = ZERO;
    }
    else if(ICU_RISING_EDGE == Edge)
    {
        EMIOS.CH[channelId].CCR.B.EDSEL = ZERO;
        EMIOS.CH[channelId].CCR.B.EDPOL = BIT0;
    }
    else if(ICU_BOTH_EDGE == Edge)
    {
        EMIOS.CH[channelId].CCR.B.EDSEL = BIT0;
    }
    else
    {
        /* empty */
    }
    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to enable channel.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_Init, Icu_StartHwSigMeas> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_EnableChannel(uint16 channel)
{
    EMIOS.CH[channel].CSR.B.FLAG = BIT0;
    EMIOS.CH[channel].CCR.B.FEN = BIT0;
    EMIOS.CH[channel].CCR.B.BSL = (BIT1 | BIT0);
    EMIOS.CH[channel].CCR.B.UCPREN = BIT0;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to disable channel.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_Init, Icu_StartHwSigMeas> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_DisableChannel(uint16 channel)
{
    switch (channel)
    {
        case CHANNEL_0:
            EMIOS.UCDIS.B.CHDIS0 = BIT0;
            break;
        case CHANNEL_8:
            EMIOS.UCDIS.B.CHDIS8 = BIT0;
            break;
        case CHANNEL_9:
            EMIOS.UCDIS.B.CHDIS9 = BIT0;
            break;
        case CHANNEL_10:
            EMIOS.UCDIS.B.CHDIS10 = BIT0;
            break;
        case CHANNEL_12:
            EMIOS.UCDIS.B.CHDIS12 = BIT0;
            break;
        case CHANNEL_14:
            EMIOS.UCDIS.B.CHDIS14 = BIT0;
            break;
        case CHANNEL_23:
            EMIOS.UCDIS.B.CHDIS23 = BIT0;
            break;
        default:
            break;
    }
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to disable this module.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_DeInit> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_HwDeInit(uint16 channel)
{
    EMIOS.CH[channel].CCR.B.FEN = ZERO;
    EMIOS.CH[channel].CCR.B.MODE = ZERO;
    EMIOS.CH[channel].CCR.B.EDSEL = ZERO;
    EMIOS.CH[channel].CCR.B.EDPOL = ZERO;
    Icu_GlobalParameter.TimeElaspedValue[channel] = ZERO;

    /* Disable the channelId Channel */
    Icu_DisableChannel(channel);
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to set mode>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_SetMode> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

#if (STD_ON == ICU_SET_MODE_API)
STATIC FUNC(void, ICU_CODE) Icu_SetHwMode(Icu_ModeType Mode)
{
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel;
    uint32 maxChannel;
    uint16 loopNum;
    uint16 channelId;

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel;

    for (loopNum = ZERO; loopNum < maxChannel; loopNum++)
    {
        channelId = oneChannel->IcuChannelId;

        /** @req ICU001 */
        #if (STD_ON == ICU_DEV_ERROR_DETECT)
        if (Icu_GlobalChannelInfo.IcuInputStatus[channelId] != ICU_IDLE)
        {
            Det_ReportError(MODULE_ID_ICU, ZERO, ICU_SETMODE_ID, ICU_E_BUSY_OPERATION);
            return;
        }
        #endif /* STD_ON == ICU_DEV_ERROR_DETECT */

        Icu_GlobalChannelInfo.IcuMode[channelId] = Mode;

        /*all used interrupts are enabled*/
        EMIOS.CH[channelId].CCR.B.FEN = ZERO;

        /** @req ICU008 */
        if (ICU_MODE_NORMAL == Mode)
        {
            /* set to the main timer to run on */
            EMIOS.MCR.B.MDIS = ZERO;
        }
        else if (ICU_MODE_SLEEP == Mode)
        {
            /* Reduced power mode */
            if (TRUE == oneChannel->IcuWakeupCapability)
            {
                /* enable notifications */
                Icu_EnableNotification(channelId);
            }
            else
            {
                /* disable notification */
                Icu_DisableNotification(channelId);
            }
            EMIOS.MCR.B.MDIS = BIT0;
        }
        else
        {
            /* empty */
        }
        oneChannel++;
    }
    return;
}
#endif /* STD_ON == ICU_SET_MODE_API */

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to set trigger edge>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel, Activation>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_SetActivationCondition> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_SetHwActivation(P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) channel,\
                                                Icu_ActivationType Activation)
{
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) currentChannel = channel;

    EMIOS.CH[currentChannel->IcuChannelId].CCR.B.UCPREN = BIT0;

    /* use the internal counter */
    EMIOS.CH[currentChannel->IcuChannelId].CCR.B.BSL = (BIT1 | BIT0);

    /* Flag assigned to a interrupt */
    EMIOS.CH[currentChannel->IcuChannelId].CCR.B.DMA = ZERO;

    if (ICU_MODE_SIGNAL_EDGE_DETECT == currentChannel->IcuMeasurementMode)
    {
        /* enable interrupt */
        EMIOS.CH[currentChannel->IcuChannelId].CCR.B.FEN = BIT0;

        /* set the SAIC mode */
        EMIOS.CH[currentChannel->IcuChannelId].CCR.B.MODE = BIT1;
    }

    /* in Icu_Init, that already enable the channel */
    if (ICU_BOTH_EDGE == Activation)
    {
        /* both edge */
        EMIOS.CH[currentChannel->IcuChannelId].CCR.B.EDSEL = BIT0;
    }
    else
    {
        /* a single edge */
        EMIOS.CH[currentChannel->IcuChannelId].CCR.B.EDSEL = ZERO;
        EMIOS.CH[currentChannel->IcuChannelId].CCR.B.EDPOL = (uint32)Activation;
    }

    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to disable interrupt>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_EnableNotification> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_DisableInt(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) channel)
{
    EMIOS.CH[channel->IcuChannelId].CCR.B.FEN = ZERO;
    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to enable interrupt>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_EnableNotification, Icu_StartHwSigMeas> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_EnableInt(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) channel)
{
    EMIOS.CH[channel->IcuChannelId].CCR.B.FEN = BIT0;
    EMIOS.CH[channel->IcuChannelId].CCR.B.UCPREN = BIT0;
    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to start input capture>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_StartTimestamp, Icu_EnableEdgeCount> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_StartInputCapture(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) channel)
{
    /* enable interrupt */
    EMIOS.CH[channel->IcuChannelId].CCR.B.FEN = BIT0;

    /* set the SAIC mode */
    EMIOS.CH[channel->IcuChannelId].CCR.B.MODE = BIT1;

    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to stop input capture>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_StopTimestamp> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_StopInputCapture(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) channel)
{
    /* disable capure */
    switch (channel->IcuChannelId)
    {
        case CHANNEL_0:
            EMIOS.UCDIS.B.CHDIS0 = BIT0;
            break;
        case CHANNEL_8:
            EMIOS.UCDIS.B.CHDIS8 = BIT0;
            break;
        case CHANNEL_9:
            EMIOS.UCDIS.B.CHDIS9 = BIT0;
            break;
        case CHANNEL_10:
            EMIOS.UCDIS.B.CHDIS10 = BIT0;
            break;
        case CHANNEL_12:
            EMIOS.UCDIS.B.CHDIS12 = BIT0;
            break;
        case CHANNEL_14:
            EMIOS.UCDIS.B.CHDIS14 = BIT0;
            break;
        case CHANNEL_23:
            EMIOS.UCDIS.B.CHDIS23 = BIT0;
            break;
        default:
            break;
    }

    /*Disable interrupt*/
    EMIOS.CH[channel->IcuChannelId].CCR.B.FEN = ZERO;

    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to reset edge counter>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_ResetEdgeCount> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_ResetEdgeCounter(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) channel)
{
    Icu_GlobalParameter.EdgeCounterIndex[channel->IcuChannelId] = ZERO;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to start measurement>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Icu_StartSignalMeasurement> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, ICU_CODE) Icu_StartHwSigMeas(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) channel)
{
    Icu_SignalMeasurementPropertyType measurementProperty;

    /* Enable the channelId Channel */
    Icu_EnableChannel(channel->IcuChannelId);
    /* enable interrupt */
    Icu_EnableInt(channel);

    /* use the internal counter */
    EMIOS.CH[channel->IcuChannelId].CCR.B.BSL = (BIT1 | BIT0);
    /* Flag assigned to a interrupt */
    EMIOS.CH[channel->IcuChannelId].CCR.B.DMA = ZERO;

    measurementProperty = channel->IcuSignalMeasurement.IcuSignalMeasurementProperty;
    switch (measurementProperty)
    {
        case ICU_LOW_TIME:
        case ICU_HIGH_TIME:
        case ICU_DUTY_CYCLE:
            /* set the SAIC mode */
            EMIOS.CH[channel->IcuChannelId].CCR.B.MODE = BIT1;
            /* set the trigering mode */
            EMIOS.CH[channel->IcuChannelId].CCR.B.EDSEL = BIT0;
            break;

        case ICU_PERIOD_TIME:
            /* set the IPM mode */
            EMIOS.CH[channel->IcuChannelId].CCR.B.MODE = (BIT2 | BIT0);
            /* set the trigering mode */
            EMIOS.CH[channel->IcuChannelId].CCR.B.EDSEL = ZERO;
            /* a single failing edge as the leading edge */
            EMIOS.CH[channel->IcuChannelId].CCR.B.EDPOL = ZERO;
            break;

        default:
            break;
    }

    return;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/
