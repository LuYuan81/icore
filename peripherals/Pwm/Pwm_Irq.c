/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Pwm_Irq.c>
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
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */
/* MISRA-C:2004 Rule 17.4; Array subscripting applied to an object of pointer type */

/*=======[I N C L U D E S]====================================================*/
#include "Pwm.h"

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

#if ((PWM_SW_MAJOR_VERSION_C != PWM_SW_MAJOR_VERSION)\
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
FUNC(void,PWM_CODE) Pwm_Isr(void)

{
	Pwm_ChannelType channelIterator;
	Pwm_ChannelType channel;
	
	for (channelIterator = (uint8)0; channelIterator < numberOfChannels; channelIterator++)
	{
    	channel = Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmChannelId;
    	
    	if (TRUE == EMIOS.CH[channel].CCR.B.FEN)
    	{
    		EMIOS.CH[channel].CSR.B.FLAG = TRUE;
    		
            if (PWM_FALLING_EDGE == Pwm_Notification[channelIterator])
        	{
                if ((uint8)PWM_LOW == EMIOS.CH[channel].CSR.B.UCOUT)
                {
                    Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmNotification();
                }
        	}
            else if	(PWM_RISING_EDGE == Pwm_Notification[channelIterator])
        	{
                if ((uint8)PWM_HIGH == EMIOS.CH[channel].CSR.B.UCOUT)
                {
                    Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmNotification();
                }
        	}
            else if (PWM_BOTH_EDGES == Pwm_Notification[channelIterator])
        	{
            	Pwm_ConfigPtr->channelConfigPtr[channelIterator].PwmNotification();
        	}
            else
            {
                /** do nothing */
            }
    	}
	}
}

/*=======[E N D   O F   F I L E]==============================================*/


