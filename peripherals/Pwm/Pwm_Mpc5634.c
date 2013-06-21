/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Pwm_Mpc5634.c>
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
/* MISRA-C:2004 Rule 3.1 */
/* MISRA-C:2004 Rule 10.1 ; Implicit conversion: unsigned long to unsigned int.*/
/* MISRA-C:2004 Rule 17.4;Array subscripting applied to an object of pointer type */
    
/*=======[I N C L U D E S]====================================================*/
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

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

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

FUNC(void, PWM_CODE) Pwm_Mpc5634Init(P2CONST(Pwm_ConfigType, AUTOMATIC, PWM_APPL_CONST) ConfigPtr)
{	
    /** @req PWM095 */
    /** @req PWM062 */
    /** @req PWM116 */
    /** @req PWM121 */
    Pwm_ChannelType channelIterator;
	
	/* 
	 * Clock scaler uses system clock (~64MHz) as source, 
	 * so prescaler 64 => 1MHz. 
	 */
    EMIOS.MCR.B.GPRE = PWM_PRESCALER - 1;
    EMIOS.MCR.B.GPREN = 1;	/* Enable eMIOS clock */
    EMIOS.MCR.B.FRZ = 0;	/* PWM_FREEZE_ENABLE */
    EMIOS.MCR.B.GTBE = 1;	/* Use global time base */
    EMIOS.MCR.B.ETB = 0; 
	
    for (channelIterator = 0; channelIterator < numberOfChannels; channelIterator++)
    {   
        /** @req PWM009 */
        Pwm_ChannelType channel ;
        uint64 period ;
        uint64 duty ;
        uint32 duty_cycle ;
        
        channel = ConfigPtr->channelConfigPtr[channelIterator].PwmChannelId;
        period = ConfigPtr->channelConfigPtr[channelIterator].PwmPeriodDefault;
        duty = ConfigPtr->channelConfigPtr[channelIterator].PwmDutycycleDefault;
        duty_cycle = (uint32) ((period * duty) >> 15);
		
        /** set mode */
        switch(ConfigPtr->channelConfigPtr[channelIterator].PwmChannelClass)
        {
            case PWM_VARIABLE_PERIOD:
            
                EMIOS.CH[channel].CADR.R = duty_cycle;
                EMIOS.CH[channel].CBDR.R = ConfigPtr->channelConfigPtr[channelIterator].PwmPeriodDefault;
                EMIOS.CH[channel].CCR.B.UCPRE = 0;
                EMIOS.CH[channel].CCR.B.UCPREN = 1;
                EMIOS.CH[channel].CCR.B.EDPOL = ~(ConfigPtr->channelConfigPtr[channelIterator].PwmPolarity);
                EMIOS.CH[channel].CCR.B.MODE = 0x58;
				/* disable notification */  /** @req PWM052 */
                EMIOS.CH[channel].CCR.B.FEN = 0; 
                break;
			
            case PWM_FIXED_PERIOD:
            
                EMIOS.CH[23].CADR.R = (uint32)period; /*Period will be period clocks */     
                EMIOS.CH[23].CCR.B.MODE = 0x50; /* MCB int clk */
                EMIOS.CH[23].CCR.B.BSL = 0x3;	  /* Use internal counter */
                EMIOS.CH[23].CCR.B.UCPRE=0;	  /* Set channel prescaler to divide by 1 */
                EMIOS.CH[23].CCR.B.FREN = 1; 	  /* Freeze channel counting when in debug mode */
                EMIOS.CH[23].CCR.B.UCPREN = 1;  /* Enable prescaler; uses default divide by 1 */	
				
                EMIOS.CH[channel].CADR.R = duty_cycle;
                EMIOS.CH[channel].CBDR.R = EMIOS.CH[23].CADR.R ;
                EMIOS.CH[channel].CCR.B.BSL = 0x0;
                EMIOS.CH[channel].CCR.B.EDPOL = ~(ConfigPtr->channelConfigPtr[channelIterator].PwmPolarity);
                EMIOS.CH[channel].CCR.B.MODE = 0x60;
                EMIOS.CH[channel].CCR.B.FEN = 0;
                break;
			
            default:
                break;
                
        }
    }
    
    INTC.CPR.B.PRI = 0;	/* Current Priority Register */
}

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
#if (PwmSetDutyCycle == STD_ON) /** @req PWM082 */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_Mpc5634SetDutyCycle(Pwm_ChannelType Channel, Pwm_DutyCycleType DutyCycle)
{	
    uint32 dutyCycle ;
    
	dutyCycle = (uint32)(((uint64) EMIOS.CH[Channel].CBDR.R * (uint64) DutyCycle) >> 15);
	
    EMIOS.CH[Channel].CADR.R = dutyCycle;					/** @req PWM013 */
}

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
#if (PWM_SET_PERIOD_AND_DUTY == STD_ON) /** @req PWM083 */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_Mpc5634SetPeriodAndDuty(
    Pwm_ChannelType Channel, Pwm_PeriodType Period, Pwm_DutyCycleType DutyCycle)
{	
    /** @req PWM098 */
    /** @req PWM076 */
    uint32 duty_cycle ;
	duty_cycle = (uint32) (((uint64) Period * (uint64) DutyCycle) >> 15);
	
    /** @req PWM019/dutycycle Timer instant for leading edge */
    EMIOS.CH[Channel].CADR.R = duty_cycle;		

    /** @req PWM019/period *//** @req PWM041 */
    EMIOS.CH[Channel].CBDR.R = Period - 1;      
}

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
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON) /** @req PWM112 @req PWM113  */

#define PWM_START_SEC_CODE
#include "MemMap.h"

FUNC(void,PWM_CODE) Pwm_Mpc5634DisableNotification(Pwm_ChannelType Channel)
{	
    EMIOS.CH[Channel].CCR.B.FEN = 0; /** @req PWM023 */
}

#define PWM_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*=======[E N D   O F   F I L E]==============================================*/


