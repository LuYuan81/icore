/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <filename>
 *  @brief      <Briefly describe file(one line)>
 *  
 *  <Compiler: XXX    MCU:XXX>
 *  
 *  @author     <author name>
 *  @date       <dd-mm-yyyy>
 */
/*============================================================================*/
#ifndef WDG_H_
#define WDG_H_

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
#include "Std_Types.h"
#include "Wdg_Cfg.h"

#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define WDG_VENDOR_ID                0
#define WDG_MODULE_ID              102
#define WDG_VENDOR_API_INFIX         0
/* AUTOSAR specification version information */
#define WDG_H_AR_MAJOR_VERSION       2
#define WDG_H_AR_MINOR_VERSION       2
#define WDG_H_AR_PATCH_VERSION       2
/* File version information */
#define WDG_H_SW_MAJOR_VERSION       1
#define WDG_H_SW_MINOR_VERSION       0
#define WDG_H_SW_PATCH_VERSION       0

/*=======[M A C R O S]========================================================*/
/* Service ID */
#define WDG_INIT_ID                 0x00
#define WDG_SET_MODE_ID             0x01
#define WDG_TRIGGER_ID              0x02
#define WDG_GET_VERSION_INFO_ID     0x04

/* DET Error Code */
/* API service used in wrong context */
#define WDG_E_DRIVER_STATE          0x10
/* API service called with wrong/inconsistent parameters */
#define WDG_E_PARAM_MODE            0x11
#define WDG_E_PARAM_CONFIG          0x12

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/* Configuration items for the different watchdog modes */
typedef enum
{
    WDGIF_FAST_MODE,
    WDGIF_SLOW_MODE,
    WDGIF_OFF_MODE

}WdgIf_ModeType;

/* Hareware dependent settings for the watchdog driver's "fast" mode */
typedef struct
{
    uint32 SettingsFastMode;

}Wdg_SettingsFastType;

/* Hardware dependent settings for the watchdog driver's "off" mode */
typedef struct
{
    uint32 SettingsOffMode;

}Wdg_SettingsOffType;

/* Hardware dependent settings for the watchdog driver's "slow" mode */
typedef struct
{
    uint32 SettingsSlowMode;

}Wdg_SettingsSlowType;

/* Configuration items for the different watchdog mode */
typedef struct
{
    /* Default mode for watchdog driver initialization */
    WdgIf_ModeType WdgDefaultMode;
    /* Hardware dependent settings for the watchdog driver's fast mode */
    Wdg_SettingsFastType WdgSettingsFast;
    /* Hardware dependent settings for the watchdog driver's slow mode */
    Wdg_SettingsSlowType WdgSettingsSlow;
    /* Hardware dependent settings for the watchdog driver's off mode */
    Wdg_SettingsOffType WdgSettingsOff;

}Wdg_ModeConfigType;

/* Watchdog trigger mode(toggle/window/both) */
typedef enum
{
    WDG_BOTH,
    WDG_TOGGLE,
    WDG_WINDOW

}WdgTriggerModeType;

/* List of selectable timeout periods in [s] */
typedef struct
{
    P2VAR(float32, AUTOMATIC, WDG_VAR) TimeoutPeriod;

}Wdg_TimeoutListType;

/* Container holding all Wdg specific published information parameters */
typedef struct
{
    /* Maximum timeout period in [s] */
    float32 WdgMaxTimeout;

    /* Minimum timeout period in [s] */
    float32 WdgMinTimeout;

    /*Resolution of Watchdog Timeout Period in [s] */
    float32 WdgResolution;

    /*Watchdog Trigger Mode (toggle/window/both) */
    WdgTriggerModeType WdgTriggerMode;

    /*List of Selectable Timeout Periods in [s] */
    Wdg_TimeoutListType WdgTimeoutList;

}Wdg_PublishedInfoType;

/* Configuration of the Wdg(Watchdog driver) module */
typedef struct
{
    /*Configration Items for the Different Watchdog Modes*/
    Wdg_ModeConfigType WdgModeConfig;

    /*Specifies all Wdg Specific Published Information Parameters*/
    Wdg_PublishedInfoType WdgPublishedInfo;

}Wdg_ConfigType;

/* The status used to describe this module */
typedef enum
{
    WDG_UNINIT,
    WDG_IDLE,
    WDG_BUSY

}Wdg_StateType;

#include "Wdg_Cfg.h"

/*=======[E X T E R N A L   D A T A]==========================================*/
extern const Wdg_ConfigType Wdg_ConfigData;
extern Wdg_StateType Wdg_State;

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

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
extern FUNC(void, WDG_PUBLIC_CODE) Wdg_Init(P2CONST(Wdg_ConfigType, AUTOMATIC, WDG_APPL_CONST) ConfigPtr);
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
extern FUNC(Std_ReturnType, WDG_PUBLIC_CODE) Wdg_SetMode(WdgIf_ModeType Mode);
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
extern FUNC(void, WDG_PUBLIC_CODE) Wdg_Trigger(void);
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
#if (STD_ON == WDG_VERSION_INFO_API)
#define WDG_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, WDG_PUBLIC_CODE) Wdg_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_APPL_DATA) versioninfo);
#define WDG_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == WDG_VERSION_INFO_API */

#endif/* end WDG_H_ */

/*=======[E N D   O F   F I L E]==============================================*/
