/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Pwm.c>
 *  @brief      <Abstract API of Pwm Module)>
 *  
 *  <Compiler: CodeWarrior V2.10    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
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
/* MISRA-C:2004 Rule 3.1  */
/* MISRA-C:2004 Rule 17.4; Array subscripting applied to an object of pointer type */

/*=======[I N C L U D E S]====================================================*/
#include "Pwm.h"
#include "Det.h"
#include "irq_defines.h"
#include "Pwm_Mpc5634.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define PWM_AR_MAJOR_VERSION_C   2
#define PWM_AR_MINOR_VERSION_C   2
#define PWM_AR_PATCH_VERSION_C   2
#define PWM_SW_MAJOR_VERSION_C   1
#define PWM_SW_MINOR_VERSION_C   0
#define PWM_SW_PATCH_VERSION_C   0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if((PWM_AR_MAJOR_VERSION_C != PWM_AR_MAJOR_VERSION)\
  ||(PWM_AR_MINOR_VERSION_C != PWM_AR_MINOR_VERSION)\
  ||(PWM_AR_PATCH_VERSION_C != PWM_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Dio.c and Dio.h are different"
#endif

#if((PWM_SW_MAJOR_VERSION_C != PWM_SW_MAJOR_VERSION)\
  ||(PWM_SW_MINOR_VERSION_C != PWM_SW_MINOR_VERSION)\
  ||(PWM_SW_PATCH_VERSION_C != PWM_SW_PATCH_VERSION))
#error "Software Version Numbers of Dio.c and Dio.h are different"
#endif

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/
P2CONST(Pwm_ConfigType , PWM_VAR_POWER_ON_INIT, PWM_CONST)Pwm_ConfigPtr;
VAR(Pwm_EdgeNotificationType , PWM_VAR_POWER_ON_INIT) Pwm_Notification[PWM_NUMBER_OF_CHANNELS];
STATIC VAR(Pwm_ModuleStateType , PWM_VAR_POWER_ON_INIT)Pwm_ModuleState = PWM_STATE_UNINITIALIZED;

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#define PWM_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void,PWM_CODE) Pwm_DeInitChannel(Pwm_ChannelType Channel);
STATIC FUNC(uint8,PWM_CODE) Pwm_ValidChannel(Pwm_ChannelType Channel);
STATIC FUNC(Pwm_ChannelType ,PWM_CODE) Pwm_ChannelNum(Pwm_ChannelType Channel);
#define PWM_STOP_SEC_CODE
#include "MemMap.h"

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/*
 * Brief               <Service for PWM initialization.>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <ConfigPtr: Pointer to configuration set>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, PWM_CODE) Pwm_Init(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{	
    /** @req PWM095 */
    /** @req PWM062 */
    /** @req PWM116 */
    /** @req PWM121 */
    #if (PWM_DEV_ERROR_DETECT == STD_ON)
	
    /** @req PWM046 */
    /** @req PWM093 */
    /** @req PWM118 */
    if (PWM_STATE_INITIALIZED == Pwm_ModuleState) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_INIT_ID, PWM_E_ALREADY_INITIALIZED);
        return; 
    }
    if (NULL_PTR == ConfigPtr) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_INIT_ID, PWM_E_PARAM_CONFIG);
        return; 
    }
    
	Pwm_ConfigPtr = ConfigPtr;

    #else
    {
        Pwm_ConfigPtr = ConfigPtr;
    }
    #endif
		
    Pwm_Mpc5634Init(Pwm_ConfigPtr);
    
    /** MISRA-C:2004 Rule 1.1*/
    /** This in-line assembler construct is a language extension. The code has been ignored.*/
    /** MISRA-C:2004 Rule 14.3*/
    /** Null statement is located close to other code or comments.*/
    Pwm_Irq_Enable();
    
    Pwm_ModuleState = PWM_STATE_INITIALIZED;
      
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service for PWM De-Initialization.>
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
#if (PWM_DEINIT_API == STD_ON) /** @req PWM080 */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_DeInit(void)
{	
    /** @req PWM096 */
    Pwm_ChannelType channelIterator;
    
    #if (PWM_DEV_ERROR_DETECT == STD_ON)
    if (Pwm_ModuleState != PWM_STATE_INITIALIZED) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_DEINIT_ID, PWM_E_UNINIT);
        return; 
    }
    #endif
	
    for (channelIterator = 0; channelIterator < numberOfChannels; channelIterator++)
    {	
        /** @req PWM010 *//** @req PWM012 */
        Pwm_ChannelType channel = Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmChannelId;
        Pwm_DeInitChannel(channel);
    }

    Pwm_ModuleState = PWM_STATE_UNINITIALIZED;		/** @req PWM011 */
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/******************************************************************************/
/*
 * Brief               <Service sets the duty cycle of the PWM channel.>
 * ServiceId           <0x02>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant for different channel numbers>
 * Param-Name[in]      <ChannelNumber:Numeric identifier of the PWM  DutyCycle:Min=0x0000 Max=0x8000>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (PwmSetDutyCycle == STD_ON) /** @req PWM082 */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle)
{	
    /** @req PWM097 */
    /** @req PWM014 */
    /** @req PWM016 */
    #if (PWM_DEV_ERROR_DETECT == STD_ON)	/** @req PWM017 */
    if (Pwm_ModuleState != PWM_STATE_INITIALIZED) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_SETDUTYCYCLE_ID, PWM_E_UNINIT);
        return; 
    }
	 				
    if (E_NOT_OK == Pwm_ValidChannel(ChannelNumber)) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_SETDUTYCYCLE_ID, PWM_E_PARAM_CHANNEL);
        return; 
    }	
    #endif
		
    Pwm_Mpc5634SetDutyCycle( ChannelNumber,  DutyCycle);		/** @req PWM013 */
    
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/******************************************************************************/
/*
 * Brief               <Service sets the period and the duty cycle of a PWM channel.>
 * ServiceId           <0x03>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant for different channel numbers>
 * Param-Name[in]      <ChannelNumber, Period , DutyCycle>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (PWM_SET_PERIOD_AND_DUTY == STD_ON) /** @req PWM083 */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber , Pwm_PeriodType Period, uint16 DutyCycle)
{	
	/** @req PWM098 */
	/** @req PWM076 */
    Pwm_ChannelType channelIterator;
    
    channelIterator = Pwm_ChannelNum(ChannelNumber);

    #if (PWM_DEV_ERROR_DETECT == STD_ON)
    if (Pwm_ModuleState != PWM_STATE_INITIALIZED) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_SETPERIODANDDUTY_ID, PWM_E_UNINIT);
        return; 
    }/** @req PWM117 */
    
    /** @req PWM047 */
    if (E_NOT_OK == Pwm_ValidChannel(ChannelNumber)) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_SETPERIODANDDUTY_ID, PWM_E_PARAM_CHANNEL);
        return; 
    }
    
    /** @req PWM045 */ 
    if (Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmChannelClass != PWM_VARIABLE_PERIOD) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_SETPERIODANDDUTY_ID, PWM_E_PERIOD_UNCHANGEABLE);
        return; 
    }
	
    #endif
	
    Pwm_Mpc5634SetPeriodAndDuty(ChannelNumber,  Period,  DutyCycle);   
       
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/******************************************************************************/
/*
 * Brief               <Service sets the PWM output to the configured Idle state.>
 * ServiceId           <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant for different channel numbers>
 * Param-Name[in]      <ChannelNumber>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (PwmSetOutputToIdle == STD_ON) /** @req PWM084 */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber)
{	
    /** @req PWM099 */
    /** @req PWM086 */
    /** @req PWM119 */
    Pwm_ChannelType channelIterator;
    Pwm_ChannelType channel;
	
    #if (PWM_DEV_ERROR_DETECT == STD_ON)	/** @req PWM017 */
    if (Pwm_ModuleState != PWM_STATE_INITIALIZED) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_SETOUTPUTTOIDLE_ID, PWM_E_UNINIT);
        return; 
    }	 				
    if (E_NOT_OK == Pwm_ValidChannel(ChannelNumber)) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_SETOUTPUTTOIDLE_ID, PWM_E_PARAM_CHANNEL);
        return; 
    }	
    #endif
	
    for (channelIterator = 0; channelIterator < numberOfChannels; channelIterator++)
    {
        channel = Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmChannelId;
	    
        if (channel == ChannelNumber)
        {
            if (PWM_HIGH == Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmIdleState)
            {
                if (PWM_HIGH == Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmPolarity)
                {	
                    /** @req PWM021/1 */
                    EMIOS.CH[ChannelNumber].CADR.R = EMIOS.CH[ChannelNumber].CBDR.R;
                }
                else
                {
                    EMIOS.CH[ChannelNumber].CADR.R = 0;	/** @req PWM021/2 */
                }
            }
            else
            {
                if (PWM_HIGH == Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmPolarity)
                {
                    EMIOS.CH[ChannelNumber].CADR.R = 0;/** @req PWM021/3 */
                }
                else
                {
                    /** @req PWM021/4 */
                    EMIOS.CH[ChannelNumber].CADR.R = EMIOS.CH[ChannelNumber].CBDR.R;
                }
            }
        }
    }
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/******************************************************************************/
/*
 * Brief               <Service to read the internal state of the PWM output signal.>
 * ServiceId           <0x05>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant for different channel numbers>
 * Param-Name[in]      <ChannelNumber>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Pwm_OutputStateType : PWM_HIGH , PWM_LOW>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (PWM_GET_OUTPUT_STATE == STD_ON) /** @req PWM085 */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(Pwm_OutputStateType,DIO_CODE)Pwm_GetOutputState(Pwm_ChannelType ChannelNumber)
{	
    /** @req PWM100 */
    Pwm_ChannelType channelIterator;
    Pwm_ChannelType channel;
    Pwm_OutputStateType returnValue = PWM_LOW;	
	
    #if (PWM_DEV_ERROR_DETECT == STD_ON)	/** @req PWM017 */
    if (Pwm_ModuleState != PWM_STATE_INITIALIZED) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_GETOUTPUTSTATE_ID, PWM_E_UNINIT);
        return PWM_LOW; 
    }	 				
    if (E_NOT_OK == Pwm_ValidChannel(ChannelNumber)) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_GETOUTPUTSTATE_ID, PWM_E_PARAM_CHANNEL);
        return PWM_LOW; 
    }	
    #endif
	
    if (Pwm_ModuleState != PWM_STATE_INITIALIZED)
    {
        return PWM_LOW;
    }
	
    if (E_NOT_OK == Pwm_ValidChannel(ChannelNumber))
    {
        return PWM_LOW;
    }
	
    for (channelIterator = 0; channelIterator < numberOfChannels; channelIterator++)
    {
        channel = Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmChannelId;
    	
        if (channel == ChannelNumber)
        {
            returnValue = PWM_HIGH;
        }
    }
	
    if (returnValue != PWM_HIGH)
    {
        /** @req PWM051 Accordingly to PWM051,*/ 
        /*we should return PWM_LOW on failure.*/
        return returnValue;     
    }
	
    /** @req PWM022 */
    return (Pwm_OutputStateType)EMIOS.CH[ChannelNumber].CSR.B.UCOUT;
    
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/******************************************************************************/
/*
 * Brief               <Service to disable the PWM signal edge notification.>
 * ServiceId           <0x06>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant for different channel numbers>
 * Param-Name[in]      <ChannelNumber>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON) /** @req PWM112 @req PWM113  */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_DisableNotification(Pwm_ChannelType ChannelNumber)
{	
    /** @req PWM101 */
    #if (PWM_DEV_ERROR_DETECT == STD_ON)	
    if (Pwm_ModuleState != PWM_STATE_INITIALIZED) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_DISABLENOTIFICATION_ID, PWM_E_UNINIT);
        return; 
    }	 				
    if (E_NOT_OK == Pwm_ValidChannel(ChannelNumber)) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_DISABLENOTIFICATION_ID, PWM_E_PARAM_CHANNEL);
        return; 
    }	
    #endif

    Pwm_Mpc5634DisableNotification(ChannelNumber); /** @req PWM023 */
    
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to enable the PWM signal edge notification according to notification parameter.>
 * ServiceId           <0x07>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant for different channel numbers>
 * Param-Name[in]      <ChannelNumber , Notification>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification)
{	
    /** @req PWM102 */
    Pwm_ChannelType channelIterator;
    Pwm_ChannelType channel;
	
    #if (PWM_DEV_ERROR_DETECT == STD_ON)	
    if (Pwm_ModuleState != PWM_STATE_INITIALIZED) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_ENABLENOTIFICATION_ID, PWM_E_UNINIT);
        return; 
    }	 				
    if (E_NOT_OK == Pwm_ValidChannel(ChannelNumber)) 
    { 
        Det_ReportError(MODULE_ID_PWM, ZERO, (uint8)PWM_ENABLENOTIFICATION_ID, PWM_E_PARAM_CHANNEL);
        return; 
    }	
    #endif
	
    for (channelIterator = 0; channelIterator < numberOfChannels; channelIterator++)
    {
        channel = Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmChannelId;
    	
        if (channel == ChannelNumber)
        {
            Pwm_Notification[channelIterator] = Notification;
            
            switch(Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmChannelClass)
            {
                case PWM_VARIABLE_PERIOD:
                
                    if (PWM_BOTH_EDGES == Notification)
                    {
                        EMIOS.CH[ChannelNumber].CCR.B.MODE = 0x5A;/*both matches */
                    }
                    else
                    {
                        EMIOS.CH[ChannelNumber].CCR.B.MODE = 0x58;/*single matches */
                    }
                
                    break;
                    
                case PWM_FIXED_PERIOD:
                
                    if (PWM_BOTH_EDGES == Notification)
                    {
                        EMIOS.CH[ChannelNumber].CCR.B.MODE = 0x62;/*both matches */
                    }
                    else
                    {
                        EMIOS.CH[ChannelNumber].CCR.B.MODE = 0x60;/*single matches */
                    }
                    break;
                    
                default:
                    break;
            }  
        }
    }

    EMIOS.CH[ChannelNumber].CCR.B.FEN = 1;  /** @req PWM081 */
    
}
#define PWM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/******************************************************************************/
/*
 * Brief               <Service returns the version information of this module.>
 * ServiceId           <0x08>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <versioninfo:Pointer to where to store the version information of this module.>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (PWM_VERSION_INFO_API == STD_ON) /** @req PWM069 */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC,PWM_APPL_DATA) VersioninfoPtr)
{		
    /** @req PWM068 */
    VersioninfoPtr->vendorID = PWM_C_VENDOR_ID;
    VersioninfoPtr->moduleID = PWM_C_MODULE_ID;
    VersioninfoPtr->instanceID = 1;
    VersioninfoPtr->ar_major_version = PWM_AR_MAJOR_VERSION;
    VersioninfoPtr->ar_minor_version = PWM_AR_MINOR_VERSION;
    VersioninfoPtr->ar_patch_version = PWM_AR_PATCH_VERSION;
    VersioninfoPtr->sw_major_version = PWM_SW_MAJOR_VERSION;
    VersioninfoPtr->sw_minor_version = PWM_SW_MINOR_VERSION;
    VersioninfoPtr->sw_patch_version = PWM_SW_PATCH_VERSION;
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*=======[L O C A L   F U N C T I O N   I M P L E M E N T A T I O N S]=======*/

/******************************************************************************/
/*
 * Brief               <Service for a PWM channel De-Initialization.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Pwm_DeInit> 
 */
/******************************************************************************/
#define PWM_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void,PWM_CODE) Pwm_DeInitChannel(Pwm_ChannelType Channel)
{
    Pwm_SetOutputToIdle(Channel);

    /* PWM052: The function Pwm_DeInit shall disable all notifications. */
    #if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
    Pwm_DisableNotification(Channel);
    #endif
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This service valid channel.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Pwm_SetDutyCycle , Pwm_SetPeriodAndDuty , Pwm_SetOutputToIdle , 
 *                      Pwm_GetOutputState , Pwm_DisableNotification , Pwm_EnableNotification> 
 */
/******************************************************************************/
STATIC FUNC(uint8,PWM_CODE) Pwm_ValidChannel(Pwm_ChannelType Channel)
{
    uint8 returnValue = E_NOT_OK;
    Pwm_ChannelType channelIterator;

    if (Channel > (uint8)PWM_CHANNEL_23_65)
    {
        returnValue = E_NOT_OK;
    }
    else
	{
        for (channelIterator = 0; channelIterator < numberOfChannels; channelIterator++)
        {
            Pwm_ChannelType channel = Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmChannelId;
		    
            if (channel == Channel)
            {
                returnValue = E_OK;
            }
        }
    }
    
    return returnValue;
    
}

/******************************************************************************/
/*
 * Brief               <Pwm_channelNum.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           < Pwm_SetPeriodAndDuty > */ 
/******************************************************************************/
STATIC FUNC(Pwm_ChannelType ,PWM_CODE) Pwm_ChannelNum(Pwm_ChannelType Channel)
{
    Pwm_ChannelType channelIterator;
    
    for (channelIterator = 0; channelIterator < numberOfChannels; channelIterator++)
    {
        Pwm_ChannelType channel = Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmChannelId;
    	
        if (channel == Channel)
		{
            return channelIterator;
        }
    }
}

/*=======[E N D   O F   F I L E]==============================================*/

