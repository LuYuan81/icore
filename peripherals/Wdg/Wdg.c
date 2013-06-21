/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Wdg.c>
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
/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */

/*=======[I N C L U D E S]====================================================*/
#include "MemMap.h"
#include "Wdg.h"
#include "Det.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define WDG_C_AR_MAJOR_VERSION    2
#define WDG_C_AR_MINOR_VERSION    2
#define WDG_C_AR_PATCH_VERSION    2
#define WDG_C_SW_MAJOR_VERSION    1
#define WDG_C_SW_MINOR_VERSION    0
#define WDG_C_SW_PATCH_VERSION    0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (WDG_C_AR_MAJOR_VERSION != WDG_H_AR_MAJOR_VERSION)
  #error "WDG.c : Mismatch in Specification Major Version"
#endif
#if (WDG_C_AR_MINOR_VERSION != WDG_H_AR_MINOR_VERSION)
  #error "WDG.c : Mismatch in Specification Major Version"
#endif
#if (WDG_C_AR_PATCH_VERSION != WDG_H_AR_PATCH_VERSION)
  #error "WDG.c : Mismatch in Specification Major Version"
#endif
#if (WDG_C_SW_MAJOR_VERSION != WDG_H_SW_MAJOR_VERSION)
  #error "WDG.c : Mismatch in Specification Major Version"
#endif
#if (WDG_C_SW_MINOR_VERSION != WDG_H_SW_MINOR_VERSION)
  #error "WDG.c : Mismatch in Specification Major Version"
#endif
#if (WDG_C_SW_PATCH_VERSION != WDG_H_SW_PATCH_VERSION)
  #error "WDG.c : Mismatch in Specification Major Version"
#endif

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/
Wdg_StateType Wdg_State = WDG_UNINIT;

/*=======[I N T E R N A L   D A T A]==========================================*/
STATIC P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_CONST) wdgGlobalconfig = NULL_PTR;

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#define WDG_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(Std_ReturnType, WDG_CODE) Wdg_SetHwMode(WdgIf_ModeType Mode, uint32 fastTime, uint32 slowTime);
STATIC FUNC(void, WDG_CODE) Wdg_ActivationCode(void);
#define WDG_STOP_SEC_CODE
#include "MemMap.h"

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/*
 * Brief               <Initializes the module.>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <ConfigPtr: Pointer to configuration set.>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define WDG_START_SEC_CODE
#include "MemMap.h"

/** @req WDG106 */
FUNC(void, WDG_CODE) Wdg_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr)
{
    uint32 fastMode;
    uint32 slowMode;

    #if (STD_ON == WDG_DEV_ERROR_DETECT)
    /** @reqWDG089 */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(MODULE_ID_WDG, ZERO, WDG_INIT_ID, WDG_E_PARAM_CONFIG);
        return;
    }
    /** @reqWDG090 */
    if ((ConfigPtr->WdgModeConfig.WdgDefaultMode < WDGIF_FAST_MODE) ||\
        (ConfigPtr->WdgModeConfig.WdgDefaultMode > WDGIF_OFF_MODE))
    {
        Det_ReportError(MODULE_ID_WDG, ZERO, WDG_INIT_ID, WDG_E_PARAM_CONFIG);
        return;
    }
    #endif /* STD_ON == WDG_DEV_ERROR_DETECT */

    wdgGlobalconfig = ConfigPtr;

    /** @req WDG025 */
    if ((STD_OFF == WDG_DISABLE_ALLOWED) && (WDGIF_OFF_MODE == wdgGlobalconfig ->WdgModeConfig.WdgDefaultMode))
    {
        return;
    }

    /** @req WDG100 */
    fastMode = wdgGlobalconfig ->WdgModeConfig.WdgSettingsFast.SettingsFastMode;
    slowMode = wdgGlobalconfig ->WdgModeConfig.WdgSettingsSlow.SettingsSlowMode;

    /** @req WDG001 @req WDG101 */
    (void)Wdg_SetHwMode(wdgGlobalconfig ->WdgModeConfig.WdgDefaultMode, fastMode, slowMode);

    /** @req WDG019 */
    Wdg_State = WDG_IDLE;
    return;
}

#define WDG_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Switches the watchdog into the mode Mode.>
 * ServiceId           <0x01>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <Mode: One of the following statically configured modes.>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define WDG_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, WDG_CODE) Wdg_SetMode(WdgIf_ModeType Mode)
{
    /** @req WDG102 */
    Std_ReturnType status = E_OK;
    uint32 fastMode;
    uint32 slowMode;
    WdgIf_ModeType tarMode = Mode;

    #if (STD_ON == WDG_DEV_ERROR_DETECT)
    /** @req WDG091 */
    if ((tarMode < WDGIF_FAST_MODE) || (tarMode > WDGIF_OFF_MODE))
    {
        Det_ReportError(MODULE_ID_WDG, ZERO, WDG_SET_MODE_ID, WDG_E_PARAM_MODE);
        return E_NOT_OK;
    }
    /** @req WDG017 */
    if (Wdg_State != WDG_IDLE)
    {
        Det_ReportError(MODULE_ID_WDG, ZERO, WDG_SET_MODE_ID, WDG_E_DRIVER_STATE);
        return E_NOT_OK;
    }

    Wdg_State = WDG_BUSY;
    #endif /* STD_ON == WDG_DEV_ERROR_DETECT */

    fastMode = wdgGlobalconfig ->WdgModeConfig.WdgSettingsFast.SettingsFastMode;
    slowMode = wdgGlobalconfig ->WdgModeConfig.WdgSettingsSlow.SettingsSlowMode;

    /** @req WDG051 */
    status = Wdg_SetHwMode(tarMode, fastMode, slowMode);

    /** @req WDG018 */
    #if (STD_ON == WDG_DEV_ERROR_DETECT)
    Wdg_State = WDG_IDLE;
    #endif /* STD_ON == WDG_DEV_ERROR_DETECT */

    /** @req WDG103 @req WDG016 */
    return status;
}

#define WDG_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Triggers the watchdog hardware.>
 * ServiceId           <0x02>
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
#define WDG_START_SEC_CODE
#include "MemMap.h"

FUNC(void, WDG_CODE) Wdg_Trigger(void)
{
    /** @req WDG041 @req WDG035 @req WDG105 */
    #if (STD_ON == WDG_DEV_ERROR_DETECT)
    if (Wdg_State != WDG_IDLE)
    {
        Det_ReportError(MODULE_ID_WDG, ZERO, WDG_TRIGGER_ID, WDG_E_DRIVER_STATE);
        return;
    }
    else
    {
        Wdg_State = WDG_BUSY;
    }
    #endif /* STD_ON == WDG_DEV_ERROR_DETECT */

    /** @req WDG036 @req WDG093 @req WDG094 @req WDG095 */
    Wdg_ActivationCode();

    /** @req WDG052 */
    #if (STD_ON == WDG_DEV_ERROR_DETECT)
    Wdg_State = WDG_IDLE;
    #endif /* STD_ON == WDG_DEV_ERROR_DETECT */

    return;
}

#define WDG_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Returns the version information of the module.>
 * ServiceId           <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <versioninfo: Pointer to where to store the version information of this module.>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define WDG_START_SEC_CODE
#include "MemMap.h"

/** @req WDG068 @req WDG099 */
#if (STD_ON == WDG_VERSION_INFO_API)
FUNC(void, WDG_CODE) Wdg_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) versioninfo)
{
    /** @req WDG067 */
    versioninfo->vendorID = WDG_VENDOR_ID;
    versioninfo->moduleID = WDG_MODULE_ID;
    versioninfo->ar_major_version = WDG_H_AR_MAJOR_VERSION;
    versioninfo->ar_minor_version = WDG_H_AR_MINOR_VERSION;
    versioninfo->ar_patch_version = WDG_H_AR_PATCH_VERSION;
    versioninfo->sw_major_version = WDG_H_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = WDG_H_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = WDG_H_SW_PATCH_VERSION;
    versioninfo->instanceID = WDG_VENDOR_API_INFIX;

    return;
}
#endif /* STD_ON == WDG_VERSION_INFO_API */

#define WDG_STOP_SEC_CODE
#include "MemMap.h"

/*=======[L O C A L   F U N C T I O N   I M P L E M E N T A T I O N S]========*/

/******************************************************************************/
/*
 * Brief               <Set registers relative to the selected mode.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <Mode, fastTime, slowTime>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <status: the result of setting mode.>  
 * PreCondition        <>  
 * CallByAPI           <Wdg_Init, Wdg_SetMode> 
 */
/******************************************************************************/
#define WDG_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(Std_ReturnType, WDG_CODE) Wdg_SetHwMode(WdgIf_ModeType Mode, uint32 fastTime, uint32 slowTime)
{
    Std_ReturnType hwStatus = E_OK;

    switch (Mode)
    {
        case WDGIF_FAST_MODE:
            /* SWT is disabled */
            SWT.MCR.B.WEN = ZERO;
            /* Watchdog time-out period in clock cycles. */
            SWT.TO.B.WTO = fastTime;
            /* Access for the master is enabled */
            SWT.MCR.B.MAP0 = BIT0;
            /* Invalid access to the SWT causes a system reset if WEN = 1 */
            SWT.MCR.B.RIA = BIT0;
            /* SWT counter is stopped in stop mode */
            SWT.MCR.B.STP = BIT0;
            /* SWT is enabled */
            SWT.MCR.B.WEN = BIT0;
            break;

        case WDGIF_SLOW_MODE:
            SWT.MCR.B.WEN = ZERO;
            SWT.TO.B.WTO = slowTime;
            SWT.MCR.B.MAP0 = BIT0;
            SWT.MCR.B.RIA = BIT0;
            SWT.MCR.B.STP = BIT0;
            SWT.MCR.B.WEN = BIT0;
            break;

        case WDGIF_OFF_MODE:
            /** @req WDG026 */
            #if (STD_ON == WDG_DEV_ERROR_DETECT)
            if (STD_OFF == WDG_DISABLE_ALLOWED)
            {
                hwStatus = E_NOT_OK;
            }
            else
            #endif /* STD_ON == WDG_DEV_ERROR_DETECT */
            {
                SWT.MCR.B.WEN = ZERO;
                SWT.MCR.B.MAP0 = BIT0;
                SWT.MCR.B.RIA = BIT0;
                SWT.MCR.B.STP = BIT0;
            }
            break;

        default:
            hwStatus = E_NOT_OK;
            break;
    }

    return hwStatus;
}

#define WDG_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <The code used to unlock watchdog.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Wdg_Trigger> 
 */
/******************************************************************************/
#define WDG_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, WDG_CODE) Wdg_ActivationCode(void)
{
    /* Watchdog Service Code */
    SWT.SR.R = 0x0000A602;
    SWT.SR.R = 0x0000B480;
}

#define WDG_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/
