/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Mcu.c>
 *  @brief      <This is Mcu C file>
 *  
 *  <Compiler: cw2.6    MCU:mpc5634>
 *  
 *  @author     <author name>
 *  @date       <yyyy-mm-dd>
 */
/*============================================================================*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20081127   xx       Initial version
 * 
 *  V1.1.0       20091012   xx       As per ADC171, ADC_E_NO_DB is changed
 *                                     to ADC_E_INVALID_DATABASE.
 * 
 *  V2.0.0       20100210   xx       As per SCR 186, Adc_Init and Adc_DeInit
 *                                   are updated to use IMRm register instead
 *                                   of xxICn register.
 */
/*============================================================================*/
/*=======[M I S R A  R U L E  V I O L A T I O N]==============================*/
/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 17.4;Additive Operators - Constraints 					  */

/*=======[I N C L U D E S]====================================================*/
#include "Mcu.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/

/* AUTOSAR Specification version information */
#define MCU_C_AR_MAJOR_VERSION     2
#define MCU_C_AR_MINOR_VERSION     3
#define MCU_C_AR_PATCH_VERSION     0

/* File version information */
#define MCU_C_SW_MAJOR_VERSION     1
#define MCU_C_SW_MINOR_VERSION     0
#define MCU_C_SW_PATCH_VERSION	   0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (MCU_AR_MAJOR_VERSION != MCU_C_AR_MAJOR_VERSION)
#error "Mcu.c : Mismatch in Specification Major Version"
#endif

#if (MCU_AR_MINOR_VERSION != MCU_C_AR_MINOR_VERSION)
#error "Mcu.c : Mismatch in Specification Minor Version"
#endif

#if (MCU_AR_PATCH_VERSION != MCU_C_AR_PATCH_VERSION)
#error "Mcu.c : Mismatch in Specification Patch Version"
#endif

#if (MCU_SW_MAJOR_VERSION != MCU_C_SW_MAJOR_VERSION)
#error "Mcu.c : Mismatch in Major Version"
#endif

#if (MCU_SW_MINOR_VERSION != MCU_C_SW_MINOR_VERSION)
#error "Mcu.c : Mismatch in Minor Version"
#endif

#if (MCU_SW_PATCH_VERSION != MCU_C_SW_PATCH_VERSION)
#error "Mcu.c : Mismatch in Minor Version"
#endif

#if (STD_ON == MCU_DEV_ERROR_DETECT)
#include "Det.h"
#endif	

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/
VAR(boolean, MCU_VAR) Mcu_InitRun= FALSE;
/*=======[I N T E R N A L   D A T A]==========================================*/
STATIC P2CONST(Mcu_ConfigType, MCU_CONST, MCU_CONST_PBCFG) Mcu_GlobalConfig;
/* STATIC VAR(boolean, MCU_VAR) Mcu_InitRun= FALSE;*/
STATIC VAR(Mcu_ClockType,MCU_VAR) MCU_ClockConfigIndex = ZERO;

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/* Read the reset reason */
STATIC FUNC(void, MCU_PUBLIC_CODE) Mcu_ReadResetReason(P2VAR(Mcu_ResetType,AUTOMATIC, MCU_APPL_DATA) status);
/* Enter the set mode */
STATIC FUNC(void, MCU_PUBLIC_CODE) Mcu_EnterMode(Mcu_ModeEnumType McuMode); 
/* Set the reset register */
STATIC FUNC(void, MCU_PUBLIC_CODE) Mcu_SetResetReg(uint32 resettype);
/* Read the reset register */
STATIC FUNC(void, MCU_PUBLIC_CODE) Mcu_ReadResetReg(P2VAR(uint32,AUTOMATIC, MCU_APPL_DATA) status);
/* Enabel the irq */			  
STATIC FUNC(void, MCU_PUBLIC_CODE)  Enable_Irq(void);			

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

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
#define MCU_START_SEC_CODE
#include "MemMap.h"
FUNC(void, MCU_PUBLIC_CODE) Mcu_Init(P2CONST(Mcu_ConfigType, AUTOMATIC, MCU_APPL_CONST) ConfigPtr)
{	
	/* MCU129 MCU130 MCU126 MCU127 MCU153 MCU026 MCU116 */
	#if (STD_ON == MCU_DEV_ERROR_DETECT)
	
	/* Report to DET, if the config pointer is NULL pointer */
	if (NULL_PTR == ConfigPtr)
	{	
		if (MCU_PRECOMPILE_VARIANT == STD_OFF)
		{		
			/*Report Error to det*/
			Det_ReportError(MODULE_ID_MCU,MCU_INSTANCE_ID,MCU_INIT_ID,MCU_E_PARAM_CONFIG);
			return ;
		}
		else
		{
			/* Blank */;	
		}
	}
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */
	
	if ((STD_ON == MCU_PRECOMPILE_VARIANT)&&(NULL_PTR == ConfigPtr))
	{
		Mcu_GlobalConfig = &GlobalConfig_Data;
	}
	else
	{
		/* Record the global parameter */
		Mcu_GlobalConfig = ConfigPtr;	
	}

	if (ENABLED == Mcu_GlobalConfig->McuClockSrcFailureNotification)
	{
		Mcu_EnableClkFaileNotific();    
	}
	/* Indicate the Inited status */		
	Mcu_InitRun = TRUE;	
	return;
}
#define MCU_STOP_SEC_CODE
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
#define MCU_START_SEC_CODE
#include "MemMap.h"
 FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_InitRamSection(Mcu_RamSectionType RamSection)
{
	/* After discussion, this function need not implement */
	P2VAR(uint32, AUTOMATIC, MCU_APPL_DATA) temp;
	uint32 base ;
	uint32 size ;
	uint32 value ;
	
	#if(MCU_DEV_ERROR_DETECT == STD_ON)
	/* Report to DET, if the component is not initialized */
	if (MCU_UNINITIALIZED == Mcu_InitRun)
	{
		/* Report to DET */
		Det_ReportError(MODULE_ID_MCU, MCU_INSTANCE_ID, MCU_INIT_RAM_SECTION_ID,MCU_E_UNINIT);
		return E_NOT_OK;
	}
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */
	
	if (RamSection > Mcu_GlobalConfig->McuRamSectors)
	{
		return E_NOT_OK;
	}
	
	/* Get the ram base address */
	base = Mcu_GlobalConfig->McuRamSectorSettingConf[RamSection].McuRamSectionBaseAddress;
	/* Get the size to be inited */
	size = Mcu_GlobalConfig->McuRamSectorSettingConf[RamSection].McuRamSectionSize;
	/* Get the vaule to init the ram */
	value = Mcu_GlobalConfig->McuRamSectorSettingConf[RamSection].McuRamDefaultValue;
	
	temp = (uint32 *)base;
	
	/* Init the ram */
	while (size != ZERO)
	{
		*temp = value;
		temp++;
		size--;  
	}
	
	return E_OK;	
}
#define MCU_STOP_SEC_CODE
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
#define MCU_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, MCU_PUBLIC_CODE) Mcu_InitClock(Mcu_ClockType ClockSetting)
{
	/* MCU155 MCU137 MCU139 */
	float32 frequency = MCU_ZERO;
	
	#if (MCU_DEV_ERROR_DETECT == STD_ON)	
	if (MCU_UNINITIALIZED == Mcu_InitRun)
	{
	   /* Report to DET */
		Det_ReportError(MODULE_ID_MCU, MCU_INSTANCE_ID, MCU_INIT_CLOCK_ID,MCU_E_UNINIT);
		return E_NOT_OK;
	}
	
	if (ClockSetting > MAXNUMBER)
	{
	   /* Report to DET */
		Det_ReportError(MODULE_ID_MCU, MCU_INSTANCE_ID, MCU_INIT_CLOCK_ID,MCU_E_PARAM_CLOCK);
		return E_NOT_OK;			
	}
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */
	
	frequency = Mcu_GlobalConfig->McuClockSettingConfig.McuClockReferencePoint[ClockSetting].McuClockReferencePointFrequency;	
	Mcu_ConfigPllPara(frequency);
	
	/* Save the index of Clocksetting cofiguration */
	MCU_ClockConfigIndex = ClockSetting;
	
	/* Do not to wait the PLL to stop */
	/* MCU138 */	
	return  E_OK;
}
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
FUNC(void, MCU_PUBLIC_CODE) Mcu_DistributePllClock (void)
{	
	#if (MCU_DEV_ERROR_DETECT == STD_ON)
	if (MCU_UNINITIALIZED == Mcu_InitRun)
	{
		/* Report to DET */
		Det_ReportError(MODULE_ID_MCU, MCU_INSTANCE_ID, MCU_DISTRIBUTE_PLL_CLOCK_ID,MCU_E_UNINIT);
		return ;
	}
	
	if(MCU_PLL_UNLOCKED == Mcu_GetPllStatus())	
	{
	   /* Report to DET */
		Det_ReportError(MODULE_ID_MCU, MCU_INSTANCE_ID, MCU_DISTRIBUTE_PLL_CLOCK_ID,MCU_E_PLL_NOT_LOCKED);
		return ;			
	}
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */

	/* MCU140 MCU141 056 142 */
	Mcu_WriteDistributePllReg();
	
	return;
}
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
FUNC(Mcu_PllStatusType, MCU_PUBLIC_CODE) Mcu_GetPllStatus(void)
{
	/* MCU132 MCU157 MCU008 */
	Mcu_PllStatusType status = MCU_PLL_STATUS_UNDEFINED;
	
	/*if this function is called prior to Mcu_Init,then return MCU_PLL_STATUS_UNDEFINED*/
	#if (MCU_DEV_ERROR_DETECT == STD_ON)	
	if (FALSE == Mcu_InitRun)
	{
		/* Report to DET */
		Det_ReportError(MODULE_ID_MCU, MCU_INSTANCE_ID, MCU_GET_PLL_STATUS_ID,MCU_E_UNINIT);
		return E_NOT_OK;		
	}
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */
	
	/* Read the pll status from the register */
	Mcu_ReadPllStatus(&status);
	
	return status;	
}
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
FUNC(Mcu_ResetType, MCU_PUBLIC_CODE) Mcu_GetResetReason(void)
{
	/* MCU005 MCU158 */
	Mcu_ResetType status = MCU_RESET_UNDEFINED;
	
	#if (MCU_DEV_ERROR_DETECT == STD_ON)
	if (FALSE == Mcu_InitRun)
	{
		/* Report to DET */
		Det_ReportError(MODULE_ID_MCU,MCU_INSTANCE_ID,MCU_GET_RESET_REASON_ID,MCU_E_UNINIT);	
		return MCU_RESET_UNDEFINED;	
	}
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */		
	/* Read the reset reason from the register */
	Mcu_ReadResetReason(&status);
	/* MCU133 */
	return status;
}
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
FUNC(Mcu_RawResetType, MCU_PUBLIC_CODE) Mcu_GetResetRawValue(void)
{
	/* MCU159 MCU135 */
	uint32 status = ZERO;
	
	#if (MCU_DEV_ERROR_DETECT == STD_ON)
	if (FALSE == Mcu_InitRun)
	{
		/* Report to DET */
		Det_ReportError(MODULE_ID_MCU,MCU_INSTANCE_ID,MCU_GET_RESET_RAW_VALUE_ID,MCU_E_UNINIT);	
		return MCU_RESET_UNDEFINED;	
	}	
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */
	/* MCU006 */
	Mcu_ReadResetReg(&status);
	return status;
}
#define MCU_STOP_SEC_CODE
#include "MemMap.h"

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
/* MCU146 */
#if (MCU_PERFORM_RESET_API == STD_ON)
FUNC(void, MCU_PUBLIC_CODE) Mcu_PerformReset(void)
{
	/* Only this three type of reset could be performed in 5634m */
	/* MCU160 MCU143 MCU144 */
	uint32 resettype;
	/* MCU145 */
	#if (MCU_DEV_ERROR_DETECT == STD_ON)
	if (FALSE == Mcu_InitRun)
	{
		Det_ReportError(MODULE_ID_MCU,MCU_INSTANCE_ID,MCU_PERFORM_RESET_ID,MCU_E_UNINIT);
		return ;		
	}
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */
	
	resettype = Mcu_GlobalConfig->McuResetSetting;
	Mcu_SetResetReg(resettype);

	return;
}
#endif
#define MCU_STOP_SEC_CODE
#include "MemMap.h"

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
FUNC(void, MCU_PUBLIC_CODE) Mcu_SetMode(Mcu_ModeType McuMode)
{
	/* MCU161 MCU147 MCU148 */
	Mcu_ModeSettingConfigType modeArray;
	Mcu_ModeEnumType mode;
	
	#if (MCU_DEV_ERROR_DETECT == STD_ON)
	if (FALSE == Mcu_InitRun)
	{
		/* Report the error to the det */
		Det_ReportError(MODULE_ID_MCU,MCU_INSTANCE_ID,MCU_SET_MODE_ID,MCU_E_UNINIT);
		return ;		
	}

	if (McuMode > Mcu_GlobalConfig->McuNumberOfMcuModes)
	{
    	/* Reprot the error to the det */
    	Det_ReportError(MODULE_ID_MCU,MCU_INSTANCE_ID,MCU_SET_MODE_ID,MCU_E_PARAM_MODE);
		return ;		
    }
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */
	
	modeArray = Mcu_GlobalConfig->McuModeSettingConfig[McuMode];
	mode = modeArray.McuMode;
	/* Want to enter to power reduced mode */
	Mcu_EnterMode(mode);
	
	return;
}
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
#if(MCU_VERSION_INFO_API == STD_ON)
FUNC(void, MCU_PUBLIC_CODE)Mcu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, MCU_APPL_DATA)versioninfo)
{
	#if (MCU_DEV_ERROR_DETECT == STD_ON)
	/* Check whether Version Information is equal to Null Ptr */
	if (NULL_PTR == versioninfo)
	{
		/* Report to DET */
		Det_ReportError(MODULE_ID_MCU,MCU_INSTANCE_ID,MCU_GET_VERSION_INFO,MCU_E_PARAM_POINTER);
		return ;
	}
	else
	#endif/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = MCU_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = MODULE_ID_MCU;
		/* Copy the instance Id */
		versioninfo->instanceID = MCU_INSTANCE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = MCU_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = MCU_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = MCU_SW_PATCH_VERSION;	
	}
}
#endif
#define MCU_STOP_SEC_CODE
#include "MemMap.h"

/*==============================================================================*/
/*			L O C A L  	F U N C T I O N S					 					*/
/*==============================================================================*/

/******************************************************************************/
/*
 * Brief               <Mcu_GetPeripheralBusClock>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <uint32>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define MCU_START_SEC_CODE
#include "MemMap.h"
FUNC(uint32, MCU_PUBLIC_CODE)Mcu_GetPeripheralBusClock(void)
{
	uint32 peripheralBusClock = ZERO;
	
	#if (MCU_DEV_ERROR_DETECT == STD_ON)
	if (FALSE == Mcu_InitRun)
	{
		Det_ReportError(MODULE_ID_MCU,MCU_INSTANCE_ID,MCU_SET_MODE_ID,MCU_E_UNINIT);
		return E_NOT_OK;		
	}
	/* End the #if (MCU_DEV_ERROR_DETECT == STD_ON) */
	#endif
	
	if (MCU_PLL_LOCKED == Mcu_GetPllStatus())
	{
		/* Get the clock freq */
		peripheralBusClock= Mcu_GlobalConfig->McuClockSettingConfig.\
							McuClockReferencePoint[MCU_ClockConfigIndex].McuClockReferencePointFrequency;	
	}
	return peripheralBusClock;			
}

#define MCU_STOP_SEC_CODE
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
FUNC(void, MCU_PUBLIC_CODE)Mcu_ConfigPllPara(float32 frequency)
{
	uint8 eMFD;
	uint8 ePREDIV;
	uint8 eRFD;	
	uint8 i;
	uint8 j;
	uint8 k;
	boolean finish = FALSE;
	uint8 	index[4] = {0x02,0x04,0x08,0x10};
	
	/* Use Enhanced model */
	FMPLL.ESYNCR1.B.EMODE = ONE;
		
	/* Find the EMFD */
	for (i = MIN_EMFD; (i < MAX_EMFD) && (FALSE == finish); i++)
	{
		/* Find the EPRDDIV */
		for (j = ZERO; (j < THREE) && (FALSE == finish); j++)
		{
			/* Find the ERFD */
			for (k = ZERO; (k < FOUR) && (FALSE == finish); k++)
			{
				if (((float32)(OSCILLATOR * i) - (float32)(frequency*(float32)((j+1)*(index[k])))) <= 1.0)
				{
					if(((float32)(OSCILLATOR * i) - (float32)(frequency*(float32)((j+1)*(index[k])))) >= -1.0)
					{	
						eMFD =  i; 
						ePREDIV =  j;
						eRFD =  k;
						finish = TRUE;
						break;
					}
						
				}
				else
				{
					/* Blank */;
				}					
			}
		}
	}
	
	/* Set by passby mode with the PLL running */	
	FMPLL.ESYNCR1.B.CLKCFG = THREE; 
	
	/* Set the PLL registers */
	FMPLL.ESYNCR1.B.EPREDIV = ePREDIV;
	FMPLL.ESYNCR1.B.EMFD = eMFD;
	FMPLL.ESYNCR2.B.ERFD = eRFD;
	return ;

}
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
FUNC(void, MCU_PUBLIC_CODE) Mcu_ReadPllStatus(P2VAR(Mcu_PllStatusType,AUTOMATIC, MCU_APPL_DATA) status)
{
	if (ZERO == FMPLL.SYNSR.B.LOCK)
	{
		/* Get the pll status */
		*status = MCU_PLL_UNLOCKED;
	}
	else if (MCU_ASSERT == FMPLL.SYNSR.B.LOCK)
	{
		/* Get the pll status */
		*status = MCU_PLL_LOCKED;
	}
	else
	{ 
		/* Blank */;
	}
	
	return ;	
}
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
FUNC(void, MCU_PUBLIC_CODE) Mcu_WriteDistributePllReg(void)
{
	/* Distribute Pll Clock */
	/* MCU140 MCU141 056 142 */
	if (FMPLL.ESYNCR1.B.CLKCFG != MCU_DISPLL_CLK)
	{
		FMPLL.ESYNCR1.B.CLKCFG = MCU_DISPLL_CLK;
	}
}
#define MCU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Mcu_ReadResetReason>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
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
STATIC FUNC(void, MCU_PUBLIC_CODE) Mcu_ReadResetReason(P2VAR(Mcu_ResetType,AUTOMATIC, MCU_APPL_DATA) status)
{
	/* Power On Reset */
	if (MCU_ASSERT == SIU.RSR.B.PORS) 
	{
		*status = MCU_POWER_ON_RESET; 
	}
	/* WatchDog Reset */
	else if (MCU_ASSERT == SIU.RSR.B.SWTRS)
	{
		*status = MCU_WAICHDOG_RESET;
	}
	/* SoftWare Reset */
	else if (MCU_ASSERT == SIU.RSR.B.SSRS)	
	{
		*status = MCU_SW_RESET;
	}
	/* External reset occurred */
	else if(MCU_ASSERT == SIU.RSR.B.ERS)
	{
		*status = MCU_ERS_RESET;	
	}
	else
	{
		/* Blank */;	
	}
	return ;	
}
#define MCU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Mcu_ReadResetReg>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
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
STATIC FUNC(void, MCU_PUBLIC_CODE) Mcu_ReadResetReg(P2VAR(uint32,AUTOMATIC, MCU_APPL_DATA) status)
{
	/* Read the RSR */
	*status = SIU.RSR.R;
	return ;
}

/******************************************************************************/
/*
 * Brief               <Mcu_EnterMode>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
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
STATIC FUNC(void, MCU_PUBLIC_CODE) Mcu_EnterMode(Mcu_ModeEnumType McuMode)
{
	if (((uint32)MCU_SLEEP_MODE) == McuMode)
	{
		/* Go into te power_down mode */
		SIU.HLT.R = 0x01;//MCU_INTO_PDOWN;
		/* MISRA Rule     : 1.1
		Message        : This in_line assember construct is a language extension
		Verification   : However, this part of the code is verified
                        manually and it is not having any impact.
		*/
		asm("wait");
	}
	else if (((uint32)MCU_DISABLE_MODE) == McuMode)
	{
		/* Go into the disable mode */
		DSPI_B.MCR.B.MDIS = ZERO;
		DSPI_C.MCR.B.MDIS = ZERO;	
		EBI.MCR.B.MDIS = ZERO;
		ETPU.ECR_A.B.MDIS = ZERO;
		CAN_A.MCR.B.MDIS = ZERO;
		CAN_C.MCR.B.MDIS = ZERO;
		EMIOS.MCR.B.MDIS = ZERO;
		ESCI_A.CR2.B.MDIS = ZERO;
		ESCI_B.CR2.B.MDIS = ZERO;
		DECFIL.MCR.B.MDIS = ZERO;
		SWT.MCR.B.WEN = ZERO;
		PIT.PITMCR.R = ZERO;						
	}
	else
	{
		/* Go into te Normal mode */
		SIU.HLT.R = ZERO;
	}
	return ;
}
#define MCU_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_SetResetReg>
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
STATIC FUNC(void, MCU_PUBLIC_CODE) Mcu_SetResetReg(uint32 resettype)
{
	/* Perform a software system reset */	
	if ((uint32)MCU_SSR == resettype) 
	{
		SIU.SRCR.B.SSR = MCU_ASSERT;
	}
    /* Perform a software external reset */
	else if ((uint32)MCU_SER == resettype)
	{
		SIU.SRCR.B.SER = (uint32)MCU_ASSERT;
	}
	else if ((uint32)MCU_CRE == resettype)
	{
		SIU.SRCR.B.CRE = (uint32)MCU_ASSERT;		
	}
	else
	{
		/* Blank */
	}
	
	return ;
}
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
FUNC(void, MCU_PUBLIC_CODE) Mcu_EnableClkFaileNotific(void)
{
	/*Lose of Clock enable*/
	FMPLL.ESYNCR2.B.LOCEN = MCU_ASSERT;  
	/*If lose of clock occurs,then generates a interrupt*/
	FMPLL.ESYNCR2.B.LOCIRQ = MCU_ASSERT;
	INTC.PSR[43].R = ONE;
	return ; 		
}

#define MCU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Enable_Irq>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
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
STATIC FUNC(void, MCU_PUBLIC_CODE)Enable_Irq(void)		
{
	/* Current Priority Register */
	INTC.CPR.B.PRI = ZERO;
	/* MISRA Rule     : 1.1
       Message        : This in_line assember construct is a language extension
       Verification   : However, this part of the code is verified
                        manually and it is not having any impact.
    */ 
	asm volatile (" wrteei 1");
}

#define MCU_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/
