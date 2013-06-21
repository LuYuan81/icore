
/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <Mcu.h>
 *  @brief      <This is Mcu header file>
 *  
 *  <Compiler: cw2.6    MCU:mpc5634>
 *  
 *  @author     <author name>
 *  @date       <dd-mm-yyyy>
 */
/*============================================================================*/

#ifndef MCU_H
#define MCU_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20081127  James       Initial version
 * 
 *  V1.1.0       20091012  XXX      
 * 
 *  V2.0.0       20100210  XXX         .
 */
/*============================================================================*/
/*=======[M I S R A  R U L E  V I O L A T I O N]==============================*/
/* MISRA-C:2004 Rule 3.4  */

#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"
/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/

/* Version identification */
#define MCU_VENDOR_ID              (0)
#define MCU_INSTANCE_ID            (0)

/* AUTOSAR specification version information */
#define MCU_AR_MAJOR_VERSION       2
#define MCU_AR_MINOR_VERSION       3
#define MCU_AR_PATCH_VERSION       0

/* File version information */
#define MCU_SW_MAJOR_VERSION       1
#define MCU_SW_MINOR_VERSION       0
#define MCU_SW_PATCH_VERSION       0

/*=======[I N C L U D E S]====================================================*/
#include "Mcu_Cfg.h"	/* MCU108/include Mcu_Cfg.h */
/* MCU152 */
#include "Std_Types.h"	/* MCU108/include Std_Types.h */
#include "Std_ExtTypes.h"
#include "MPC5634M_MLQB80.h"
#include "Modules.h"
/*=======[M A C R O S]========================================================*/
/* Service Id of Mcu_Init API */
#define MCU_INIT_SID                        (uint8)0x00
/* Service Id of Mcu_InitRamSection API */
#define MCU_INITRAMSECTION_SID              (uint8)0x01
/* Service Id of Mcu_InitClock API */
#define MCU_INITCLOCK_SID                   (uint8)0x02
/* Service Id of Mcu_DistributePllClock API */
#define MCU_DISTRIBUTEPLLCLOCK_SID          (uint8)0x03
/* Service Id of Mcu_GetPllStatus API */
#define MCU_GETPLLSTATUS_SID                (uint8)0x04
/* Service Id of Mcu_GetResetReason API */
#define MCU_GETRESETREASON_SID              (uint8)0x05
/* Service Id of Mcu_GetResetRawValue API */
#define MCU_GETRESETRAWVAULE_SID            (uint8)0x06
/* Service Id of Mcu_PerformReset API */
#define MCU_PERFORMRESET_SID                (uint8)0x07
/* Service Id of Mcu_SetMode API */
#define MCU_SETMODE_SID                     (uint8)0x08
/* Service Id of Mcu_GetVersionInfo API */
#define MCU_GETVERSIONINFO_SID              (uint8)0x09

#if 1
/* Definations of errors ID */
#define MCU_E_PARAM_CONFIG			0x0A
#define MCU_E_PARAM_CLOCK			0x0B
#define MCU_E_PARAM_MODE			0x0C
#define MCU_E_PARAM_RAMSECTION		0x0D
#define MCU_E_PLL_NOT_LOCKED		0x0E
#define MCU_E_UNINIT				0x0F
#define MCU_E_PARAM_POINTER         0xEE

/* Definations of service ID */
#define MCU_INIT_ID					0x00
#define MCU_INIT_RAM_SECTION_ID		0x01
#define MCU_INIT_CLOCK_ID			0x02
#define MCU_DISTRIBUTE_PLL_CLOCK_ID	0x03
#define MCU_GET_PLL_STATUS_ID		0x04
#define MCU_GET_RESET_REASON_ID		0x05
#define MCU_GET_RESET_RAW_VALUE_ID	0x06
#define MCU_PERFORM_RESET_ID		0x07
#define MCU_SET_MODE_ID				0x08
#define MCU_GET_VERSION_INFO		0x09
#endif

#define MCU_ASSERT 	1
#define MCU_ZERO    0
#define MCU_ONE		1
#define MCU_TWO		2
#define MCU_THREE	3
#define MCU_FOUR	4

#define MAX_EMFD    97
#define MIN_EMFD    32
#define MCU_UNINITIALIZED 0
#define MCU_INTO_PDOWN 0xFFFF
#define MCU_DISPLL_CLK 7

/* This is a enum which specifys the mode types.*/
typedef enum
{
	MCU_SLEEP_MODE,
	MCU_DISABLE_MODE,
	MCU_NORMAL_MODE
}Mcu_ModeEnumType;

/* This is a status value returnend by the fuction 
   Mcu_GetPllStatus of the MCU module.
*/
typedef enum
{
	MCU_PLL_LOCKED,
	MCU_PLL_UNLOCKED,
	MCU_PLL_STATUS_UNDEFINED
}Mcu_PllStatusType;

/* Specified the identification(ID) for a clock setting, 
   which is configured in the configuration structure.
*/
typedef uint32  Mcu_ClockType;

/* This is the type of the reset enumerator containing the subset of reset types. 
   It is nont required that all reset types are supported by hardware.
*/
typedef enum 
{
	MCU_POWER_ON_RESET,
	MCU_WAICHDOG_RESET,
	MCU_SW_RESET,
	MCU_SSR,
	MCU_SER,
	MCU_CRE,
	MCU_ERS_RESET,
	MCU_RESET_UNDEFINED
}Mcu_ResetType;/* MCU134 */

/* This type specifies the reset reason in raw register format read from 
   a reset status register.
*/
typedef  uint32  Mcu_RawResetType;

/* This type specifies the identification(ID) for a MCU mode, 
	which is configured in the configuration structure.		
*/
typedef uint32  Mcu_ModeType;

/* This type specifies the identification(ID) for a RAM section, 
	which is configured in the configuration structure.		
*/
typedef uint32 Mcu_RamSectionType;

/* This enum contains the switch for the notification type.	*/
typedef enum
{
	DISABLED,
	ENABLED
}Mcu_ClockSrcFailureNotificationType;

/* this container defines a reference point in the Mcu Clock tree.*/
typedef struct
{
	float32 McuClockReferencePointFrequency; /* MCU175 */
}McuClockReferencePointType;

/* This container contains the configuration(parameters)for the Clock settings of the MCU.*/
typedef struct
{
	McuClockReferencePointType *McuClockReferencePoint; /* MCU174 */	
}Mcu_ClockSettingConfigType;

/* This container contains the configuration(parameters)for the Mode settings of the MCU.*/
typedef struct
{	
	/*the number of mode:0 normal mode;1 halt mode*/
	uint32 McuMode; /* MCU176 */
		
}Mcu_ModeSettingConfigType;

/* This container contains the configuration(parameters)for the RAM settings of the MCU.*/
typedef struct
{
	uint32 McuRamDefaultValue; 		/* MCU177 */
	uint32 McuRamSectionBaseAddress;/* MCU178 */
	uint32 McuRamSectionSize;		/* MCU179 */
	
}Mcu_RamSectorSettingConfType;

/* This container contains the configuration of the MCU.*/
typedef struct
{
	/* Enable/disable clock failure notification */
	/* MCU170 */
	Mcu_ClockSrcFailureNotificationType McuClockSrcFailureNotification;
	/* number of configured mcu mode setting */
	uint32 McuNumberOfMcuModes;	/* MCU165 MCU171 */
	/* total number of configured ram */
	uint32 McuRamSectors; /* MCU172 */
	/* The ID of reset */
	uint32 McuResetSetting; /* MCU173 */
	/* it defines the frequency */
	Mcu_ClockSettingConfigType McuClockSettingConfig; /* MCU124 */
	/* mode configuration set*/
	P2CONST(Mcu_ModeSettingConfigType, AUTOMATIC, MCU_APPL_CONST) McuModeSettingConfig; /* MCU123 */
	/* RAM configuration set*/
	P2CONST(Mcu_RamSectorSettingConfType, AUTOMATIC, MCU_APPL_CONST) McuRamSectorSettingConf; /* MCU120 */
	
}Mcu_ConfigType;/* MCU131 MCU035 MCU031 MCU030*/

/*=======[E X T E R N A L   D A T A]==========================================*/
extern VAR(McuClockReferencePointType,MCU_APPL_DATA) McuClockSettingConfig_Data[3U];
extern VAR(Mcu_ModeSettingConfigType,MCU_APPL_DATA) Mcu_ModeSettinConf_Data[2U];
extern VAR(Mcu_RamSectorSettingConfType,MCU_APPL_DATA) McuRamSectorSettingConf_Data[1U];
extern VAR(Mcu_ConfigType,MCU_APPL_DATA)  GlobalConfig_Data;

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/******************************************************************************/
/*
 * Brief               <Mcu_Init>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_Init(P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_APPL_CONST) ConfigPtr);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_InitRamSection>
 * ServiceId           <0x01>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <RamSection>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_InitRamSection(const Mcu_RamSectionType RamSection);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_InitClock>
 * ServiceId           <0x02>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ClockSetting>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_InitClock(const Mcu_ClockType ClockSetting);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_ConfigPllPara>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <frequency>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, MCU_PUBLIC_CODE)Mcu_ConfigPllPara(float32 frequency);
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_DistributePllClock>
 * ServiceId           <0x03>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_DistributePllClock(void);
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_WriteDistributePllReg>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_WriteDistributePllReg(void);
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_GetPllStatus>
 * ServiceId           <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Mcu_PllStatusType>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Mcu_PllStatusType, MCU_PUBLIC_CODE) Mcu_GetPllStatus(void);
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_ReadPllStatus>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <status>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_ReadPllStatus (P2VAR(Mcu_PllStatusType,AUTOMATIC, MCU_APPL_DATA) status);
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_GetResetReason>
 * ServiceId           <0x05>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Mcu_ResetType>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Mcu_ResetType,MCU_PUBLIC_CODE) Mcu_GetResetReason(void); 
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_GetResetRawValue>
 * ServiceId           <0x06>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Mcu_RawResetType>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Mcu_RawResetType,MCU_PUBLIC_CODE) Mcu_GetResetRawValue(void);
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_GetVersionInfo>
 * ServiceId           <0x09>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <McuMode>      
 * Param-Name[out]     <versioninfo>
 * Param-Name[in/out]  <None>
 * Return              <void>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MCU_APPL_DATA)versioninfo);
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_LoseOfClock_ISR>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <void>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,MCU_PUBLIC_CODE) Mcu_LoseOfClock_ISR(void);
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/* MCU055 */
#if (STD_ON == MCU_PERFORM_RESET_API)
/******************************************************************************/
/*
 * Brief               <Mcu_PerformReset>
 * ServiceId           <0x07>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_PerformReset(void);
#define MCU_START_SEC_CODE
#include "MemMap.h"
#endif  
/******************************************************************************/
/*
 * Brief               <Mcu_SetMode>
 * ServiceId           <0x08>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <McuMode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_SetMode(Mcu_ModeType McuMode );
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_EnableClkFaileNotific>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <resettype>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, MCU_PUBLIC_CODE) Mcu_EnableClkFaileNotific(void);
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_GetPeripheralBusClock>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint32, MCU_PUBLIC_CODE) Mcu_GetPeripheralBusClock(void); 
#define MCU_STOP_SEC_CODE
#include "MemMap.h"

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#endif
/*=======[E N D   O F   F I L E]==============================================*/
