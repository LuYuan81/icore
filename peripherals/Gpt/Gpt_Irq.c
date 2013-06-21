/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Gpt_Irq.c>
 *  @brief      <ISR Handler of Gpt Module>
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
#if((GPT_C_AR_MAJOR_VERSION != GPT_C_AR_MAJOR_VERSION)      \
    ||(GPT_C_AR_MINOR_VERSION != GPT_C_AR_MINOR_VERSION)    \
    ||(GPT_C_AR_PATCH_VERSION != GPT_C_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Gpt.c and Gpt.h are different"
#endif

#if((GPT_C_AR_MAJOR_VERSION != GPT_C_AR_MAJOR_VERSION)      \
    ||(GPT_C_AR_MINOR_VERSION != GPT_C_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of Gpt.c and Gpt.h are different"
#endif

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

#define GPT_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Gpt general ISR handler>
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
FUNC(void,GPT_CODE) Gpt_Isr_Handler(Gpt_ChannelType channel)
{
	if (GPT_CHANNEL_RTI == channel)
	{
		PIT.RTI.TFLG.B.TIF = 1;	/*Write 1 to clear RTI bit*/		
		/*You could add your own implement code here.Use RTI Timer*/	
	}
	else
	{
		PIT.TIMER[channel].TFLG.B.TIF = 1; /*Clear the flag*/		
		/*You could add your own implement code here.Use PITx Timer*/				
	}
	
	if (TRUE == Gpt_NotificationSwitch[channel])
	{
		Gpt_Global.config[channel].GptNotification();		
	}
	
	if (GPT_MODE_ONESHOT == Gpt_Global.config[channel].GptChannelMode)
	{
		Gpt_Mpc5634StopTimer(channel);		
		Gpt_Unit[channel] = GPT_STATE_STOPPED;		
	}	
	
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_PIT0_Isr(void)
{
	Gpt_Isr_Handler(GPT_CHANNEL_PIT_0);
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"


#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_PIT1_Isr(void)
{
	Gpt_Isr_Handler(GPT_CHANNEL_PIT_1);
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_PIT2_Isr(void)
{
	Gpt_Isr_Handler(GPT_CHANNEL_PIT_2);
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_PIT3_Isr(void)
{
	Gpt_Isr_Handler(GPT_CHANNEL_PIT_3);
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_RTI_Isr(void)
{	
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
	if((GPT_MODE_SLEEP == Gpt_Global.mode)
		&&(TRUE == Gpt_Global.wakeupEnabled))
	{
		(void)EcuM_CheckWakeup((*Gpt_Global.config[GPT_CHANNEL_RTI].GptWakeupSourceRef));
	}
#endif
	Gpt_Isr_Handler(GPT_CHANNEL_RTI);
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/

