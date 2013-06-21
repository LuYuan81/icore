/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Pwm.h>
 *  @brief      <Abstract API of Pwm Module)>
 *  
 *  <Compiler: CodeWarrior V2.10    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/
#ifndef PWM_H_
#define PWM_H_

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
/* MISRA-C:2004 Rule 3.4; REFERENCE - ISO:C90-6.8.6 Pragma Directive */
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
#include "Std_ExtTypes.h"

#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
/** MISRA-C:2004 Rule 19.4 */
/** Macro defines an unrecognized code-fragment. */
#define	Pwm_Irq_Disable() 	asm volatile (" wrteei 0");
#define Pwm_Irq_Enable() 	asm volatile (" wrteei 1");

#define PWM_C_VENDOR_ID                 0
#define PWM_C_MODULE_ID                 121
#define PWM_AR_MAJOR_VERSION            2       
#define PWM_AR_MINOR_VERSION            2
#define PWM_AR_PATCH_VERSION            2
#define PWM_SW_MAJOR_VERSION            1
#define PWM_SW_MINOR_VERSION            0
#define PWM_SW_PATCH_VERSION            0
#define PWM_C_VENDOR_API_INFIX          0

/*=======[M A C R O S]========================================================*/
#define	Pwm_100_Procent 				0x8000
#define	Pwm_0_Procent					0
#define	PWM_E_PARAM_CONFIG 				0x10

/** PWM is not initialized yet */
#define PWM_E_UNINIT 					0x11

/** Invalid PWM channel identifier */
#define PWM_E_PARAM_CHANNEL 			0x12

/** Use of unauthorized service on PWM channel configured fixed period */
#define PWM_E_PERIOD_UNCHANGEABLE 		0x13

/** Pwm_Init called when already initialized */
#define PWM_E_ALREADY_INITIALIZED 		0x14

#define	PWM_INIT_ID						0x00
#define PWM_DEINIT_ID 					0x01
#define PWM_SETDUTYCYCLE_ID 			0x02
#define PWM_SETPERIODANDDUTY_ID 		0x03
#define PWM_SETOUTPUTTOIDLE_ID 			0x04
#define PWM_GETOUTPUTSTATE_ID 			0x05
#define PWM_DISABLENOTIFICATION_ID 		0x06
#define	PWM_ENABLENOTIFICATION_ID 		0x07
#define PWM_GETVERSIONINFO_ID 			0x08

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/* Define Pwm channel data type. */
typedef uint8 Pwm_ChannelType; /** @req PWM106 */

/* Define Pwm period data type */
typedef uint32 Pwm_PeriodType; /** @req PWM107 */

/* Define Pwm duty cycle data type. */
typedef uint16 Pwm_DutyCycleType;

/* Define Pwm prescale data type. */
typedef enum
{
    PWM_CHANNEL_PRESCALER_1=0,
    PWM_CHANNEL_PRESCALER_2,
    PWM_CHANNEL_PRESCALER_3,
    PWM_CHANNEL_PRESCALER_4
} Pwm_ChannelPrescalerType;

/* Define Pwm output state data type. */
typedef enum
{
    PWM_LOW,
    PWM_HIGH
} Pwm_OutputStateType; /** @req PWM108 */

/* Define Pwm edge notification type.	 */
typedef enum
{
    PWM_FALLING_EDGE,
    PWM_RISING_EDGE,
    PWM_BOTH_EDGES
} Pwm_EdgeNotificationType; /** @req PWM109 */		

/* Define Pwm channel class type. */
typedef enum
{
    PWM_VARIABLE_PERIOD,
    PWM_FIXED_PERIOD,
    PWM_FIXED_PERIOD_SHIFTED
} Pwm_ChannelClassType; /** @req PWM110 */

/* Define Pwm notification handler type. */
typedef P2FUNC(void, P2CONST, Pwm_NotificationHandlerType)(void);
 
/* 	Define Pwm channel type. */
typedef struct
{
    Pwm_ChannelClassType PwmChannelClass;	/** @req PWM119 */
	
    Pwm_ChannelType	PwmChannelId;			/** @req PWM120 */
	
    Pwm_DutyCycleType PwmDutycycleDefault;	/** @req PWM121 */
	
    Pwm_PeriodType	PwmPeriodDefault;		/** @req PWM124 */
	
    Pwm_OutputStateType	PwmIdleState;		/** @req PWM122 */
	
    Pwm_OutputStateType	PwmPolarity;		/** @req PWM125 */
	
	P2FUNC(void, P2CONST, PwmNotification)(); /** @req PWM123 */
	
} Pwm_ChannelDefType;/** @req PWM027 */

/* Define Pwm configration type. */
typedef struct
{	
    /** @req PWM061 */
    /** @req PWM118 */
    P2CONST(Pwm_ChannelDefType , PWM_VAR_POWER_ON_INIT, PWM_CONST) channelConfigPtr;
    
}Pwm_ConfigType; /** @req PWM111 */

/* Define Pwm module state type. */
typedef enum
{
    PWM_STATE_UNINITIALIZED,
    PWM_STATE_INITIALIZED
} Pwm_ModuleStateType;

#include "Pwm_Cfg.h"						
 
/*=======[E X T E R N A L   D A T A]==========================================*/
extern P2CONST(Pwm_ConfigType , PWM_VAR_POWER_ON_INIT, PWM_CONST) Pwm_ConfigPtr;
extern VAR(Pwm_EdgeNotificationType , PWM_VAR_POWER_ON_INIT) Pwm_Notification[PWM_NUMBER_OF_CHANNELS];

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

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
extern FUNC(void, PWM_CODE) Pwm_Init(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr);
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
#if (PWM_DEINIT_API == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,PWM_CODE) Pwm_DeInit(void);
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
#if (PwmSetDutyCycle == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,PWM_CODE) Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
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
#if (PWM_SET_PERIOD_AND_DUTY == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,PWM_CODE) Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber , Pwm_PeriodType Period, uint16 DutyCycle);
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
#if (PwmSetOutputToIdle == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,PWM_CODE) Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber);
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
#if (PWM_GET_OUTPUT_STATE == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Pwm_OutputStateType,DIO_CODE)Pwm_GetOutputState(Pwm_ChannelType ChannelNumber);
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
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,PWM_CODE) Pwm_DisableNotification(Pwm_ChannelType ChannelNumber);
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
extern FUNC(void,PWM_CODE) Pwm_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification);
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
#if (PWM_VERSION_INFO_API == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,PWM_CODE) Pwm_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC,PWM_APPL_DATA) VersioninfoPtr);
#define PWM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/******************************************************************************/
/*
 * Brief               <This function is  Pwm Isr.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define PWM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,PWM_CODE) Pwm_Isr(void);
#define PWM_STOP_SEC_CODE
#include "MemMap.h"

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

#endif  

/*=======[E N D   O F   F I L E]==============================================*/

