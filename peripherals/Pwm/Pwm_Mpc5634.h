/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Pwm_Mpc5634.h>
 *  @brief      <Abstract API of Pwm Module)>
 *  
 *  <Compiler: CodeWarrior V2.10    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/
#ifndef PWM_MPC5634_H_
#define PWM_MPC5634_H_

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

/*=======[I N C L U D E S]====================================================*/
#include "Pwm.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
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

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

/******************************************************************************/
/*
 * Brief               <Service for PWM initialization.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ConfigPtr: Pointer to configuration set>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Pwm_Init> 
 */
/******************************************************************************/
#define PWM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, PWM_CODE) Pwm_Mpc5634Init(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr);
#define PWM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service sets the duty cycle of the PWM channel.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ChannelNumber:Numeric identifier of the PWM  DutyCycle:Min=0x0000 Max=0x8000>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Pwm_SetDutyCycle> 
 */
/******************************************************************************/
#if (PwmSetDutyCycle == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
FUNC(void,PWM_CODE) Pwm_Mpc5634SetDutyCycle(Pwm_ChannelType Channel, Pwm_DutyCycleType DutyCycle);
#define PWM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/******************************************************************************/
/*
 * Brief               <Service sets the period and the duty cycle of a PWM channel.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ChannelNumber, Period , DutyCycle>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Pwm_SetPeriodAndDuty> 
 */
/******************************************************************************/
#if (PWM_SET_PERIOD_AND_DUTY == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
FUNC(void,PWM_CODE) Pwm_Mpc5634SetPeriodAndDuty(
    Pwm_ChannelType Channel, Pwm_PeriodType Period, Pwm_DutyCycleType DutyCycle);
#define PWM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/******************************************************************************/
/*
 * Brief               <Service to disable the PWM signal edge notification.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ChannelNumber>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Pwm_DisableNotification> 
 */
/******************************************************************************/
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON) 
#define PWM_START_SEC_CODE
#include "MemMap.h"
FUNC(void,PWM_CODE) Pwm_Mpc5634DisableNotification(Pwm_ChannelType Channel);
#define PWM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

#endif  

/*=======[E N D   O F   F I L E]==============================================*/

