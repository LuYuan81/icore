/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Gpt_Mpc5634.c>
 *  @brief      <Internal API of Gpt Module>
 *  
 *  <Compiler: CodeWarrior V2.8    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20120410  i-soft       Initial version
 */
/* MISRA-C:2004 Rule 17.4: 
 * Array subscripting applied to an object of pointer type. 
 */
/* MISRA-C:2004 Rule 19.1: 
 * #include statements in a file should only be preceded by other preprocessor directives or comments. 
 */

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define GPT_C_VENDOR_ID            0
#define GPT_C_MODULE_ID            100

#define GPT_C_AR_MAJOR_VERSION     2
#define GPT_C_AR_MINOR_VERSION     2
#define GPT_C_AR_PATCH_VERSION     2

#define GPT_C_SW_MAJOR_VERSION     1
#define GPT_C_SW_MINOR_VERSION     0
#define GPT_C_SW_PATCH_VERSION     0

#define GPT_C_VENDOR_API_INFIX     0

/*=======[I N C L U D E S]====================================================*/
#include "Gpt.h"

/*=======[V E R S I O N  C H E C K]===========================================*/
#if((GPT_C_AR_MAJOR_VERSION != GPT_C_AR_MAJOR_VERSION)    \
    ||(GPT_C_AR_MINOR_VERSION != GPT_C_AR_MINOR_VERSION)  \
    ||(GPT_C_AR_PATCH_VERSION != GPT_C_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Gpt.c and Gpt.h are different"
#endif

#if((GPT_C_AR_MAJOR_VERSION != GPT_C_AR_MAJOR_VERSION)    \
    ||(GPT_C_AR_MINOR_VERSION != GPT_C_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of Gpt.c and Gpt.h are different"
#endif

#define GPT_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Initializes the hardware timer module.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
FUNC(void,GPT_CODE) Gpt_Mpc5634Init(void)
{
	Gpt_ChannelType i;
	for (i = 0; i < (GPT_NUMBER_OF_CHANNELS - 1); i++)
	{
        if(Gpt_Global.config[i].GptChannelId == i) /* has been configured */
        {
            /** @req GPT107/1  @req GPT258/1 Disable interrupt */
            PIT.TIMER[i].TCTRL.B.TEN = 0;
            PIT.TIMER[i].TCTRL.B.TIE = 0;		
            Gpt_Unit[i] = GPT_STATE_STOPPED;
            Gpt_NotificationSwitch[i] = FALSE;
        }
	}

    if(Gpt_Global.config[i].GptChannelId == i) /* has been configured */
    {		
        /** @req GPT107/2 @req GPT258/1 Disable interrupt */
        PIT.RTI.TCTRL.B.TEN = 0;
        PIT.RTI.TCTRL.B.TIE = 0;		
        Gpt_Unit[i] = GPT_STATE_STOPPED;
        Gpt_NotificationSwitch[i] = FALSE;
    }
#if 0                                    /* should be done by OS */
	INTC.PSR[301].R = GPT_PIT0_PRIORITY;    /* PIT 0 interrupt has priority 1 */
    INTC.PSR[302].R = GPT_PIT1_PRIORITY;    /* PIT 1 interrupt has priority 1 */
    INTC.PSR[303].R = GPT_PIT2_PRIORITY;    /* PIT 2 interrupt has priority 1 */
    INTC.PSR[304].R = GPT_PIT3_PRIORITY;    /* PIT 3 interrupt has priority 1 */
    INTC.PSR[305].R = GPT_RTI_INT_PRIORITY; /* RTI interrupt has priority 1 */
#endif
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

#if GPT_DEINIT_API == STD_ON /** @req GPT194 */
#define GPT_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <De-Initializes the hardware timer module.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
FUNC(void,GPT_CODE) Gpt_Mpc5634DeInit(void)
{
	Gpt_ChannelType i;
	for (i = 0; i < (GPT_NUMBER_OF_CHANNELS - 1); i++)
   	{	
        if(Gpt_Global.config[i].GptChannelId == i) /* has been configured */
        {	   				   
            /** @req GPT008/1 Disable the timer */		   
            PIT.TIMER[i].TCTRL.B.TEN = 0;		
            /* Disable interrupt */
            PIT.TIMER[i].TCTRL.B.TIE = 0;	
        }
    } 

    if(Gpt_Global.config[i].GptChannelId == i) /* has been configured */
    {	   				   
        PIT.RTI.TCTRL.B.TEN = 0; /** @req GPT008/2 Disable the timer */
        PIT.RTI.TCTRL.B.TIE = 0; /* Disable interrupt */
    }
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"
#endif  /* GPT_DEINIT_API */

#if GPT_TIME_ELAPSED_API == STD_ON /** @req GPT195 */
#define GPT_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Get time elapsed>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Gpt_ValueType>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
FUNC(Gpt_ValueType,GPT_CODE) Gpt_Mpc5634GetTimeElapsed(Gpt_ChannelType channel)
{
	Gpt_ValueType valueElapsed;

	if (channel == GPT_CHANNEL_RTI)
	{
   		valueElapsed = (Gpt_ValueType)(PIT.RTI.LDVAL.R - PIT.RTI.CVAL.R);
        /*  Cast of complex expression of integral type to wider type. */
        /* MISRA-C:2004 Rule 10.3 */
	}
	else
	{
		/** @req GPT299 */
   		valueElapsed = (Gpt_ValueType)(PIT.TIMER[channel].LDVAL.R - PIT.TIMER[channel].CVAL.R); 
        /*  Cast of complex expression of integral type to wider type. */
        /* MISRA-C:2004 Rule 10.3 */
	}

	return 	valueElapsed;
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"
#endif  /* GPT_TIME_ELAPSED_API */

#if GPT_TIME_REMAINING_API == STD_ON /** @req GPT196 */
#define GPT_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Get time remaining>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Gpt_ValueType>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
FUNC(Gpt_ValueType,GPT_CODE) Gpt_Mpc5634GetTimeRemaining(Gpt_ChannelType channel)
{
	Gpt_ValueType valueRemain;

	if (channel == GPT_CHANNEL_RTI)
	{
   		valueRemain = (Gpt_ValueType)PIT.RTI.CVAL.R; 
        /* Msg(4:4121)Cast of complex expression of integral type to wider type. */
        /* MISRA-C:2004 Rule 10.3 */
	}
	else
	{
   		valueRemain = (Gpt_ValueType)PIT.TIMER[channel].CVAL.R;
        /* Msg(4:4121)Cast of complex expression of integral type to wider type. */
        /* MISRA-C:2004 Rule 10.3 */ 
	}

	return valueRemain;/** @req GPT083  @req GPT305*/
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"
#endif  /* GPT_TIME_REMAINING_API */

#define GPT_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <start a channel>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
FUNC(void,GPT_CODE) Gpt_Mpc5634StartTimer(Gpt_ChannelType channel, Gpt_ValueType value)
{	
	if (channel == GPT_CHANNEL_RTI)
   	{
       	PIT.RTI.LDVAL.R = (uint32)value; 
        /* Msg(4:3794)Implicit conversion: unsigned long to unsigned int. */
        /* MISRA-C:2004 Rule 10.1 */
	   	PIT.RTI.TCTRL.B.TEN = 1;
	   	PIT.RTI.TFLG.B.TIF  = 1;
	   	PIT.RTI.TCTRL.B.TIE = 1;
   	}
    else
    {
       	PIT.TIMER[channel].LDVAL.R = (uint32)value;
        /* Msg(4:3794)Implicit conversion: unsigned long to unsigned int. */
        /* MISRA-C:2004 Rule 10.1 */
	   	PIT.TIMER[channel].TCTRL.B.TEN = 1;
	   	PIT.TIMER[channel].TFLG.B.TIF = 1;
	   	PIT.TIMER[channel].TCTRL.B.TIE = 1; 	
	}
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

#define GPT_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <stop a channel>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
FUNC(void,GPT_CODE) Gpt_Mpc5634StopTimer(Gpt_ChannelType channel)
{
    if (channel == GPT_CHANNEL_RTI)
    {
    	PIT.RTI.TCTRL.B.TEN = 0;
	   	PIT.RTI.TCTRL.B.TIE = 0;	
    }
    else
    {
    	PIT.TIMER[channel].TCTRL.B.TEN = 0;
	   	PIT.TIMER[channel].TCTRL.B.TIE = 0;		
    }
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/

