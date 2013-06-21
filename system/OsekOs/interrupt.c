/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <interrupt.c>
 *  @brief      <Fast Disable/Enable API-functions>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-19>
 */
/*============================================================================*/

/*=======[I N C L U D E S]====================================================*/
#include "Os.h"
#include "cfgobj.h"
#include "kernel.h"

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This service restores the state saved by DisableAllInterrupts. > .
 * Service ID   :       <OSServiceId_DisableAllInterrupts>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void DisableAllInterrupts(void)
{
	arch_disable_int();
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This service disables  all interrupts for which the hardware 
    supports disabling. The state before is saved for the 
    EnableAllInterrupts call. > .
 * Service ID   :       <OSServiceId_EnableAllInterrupts>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void EnableAllInterrupts(void)
{
	arch_enable_int();
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This service restores the recognition status of all interrupts 
    saved by the SuspendAllInterrupts service.  > .
 * Service ID   :       <OSServiceId_ResumeAllInterrupts>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void ResumeAllInterrupts(void)
{
	suspend_all_count--;
	if(suspend_all_count == 0)
	{
		arch_restore_int();
	}
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This service saves the recognition status of all interrupts and 
    disables all interrupts for  which the hardware supports 
    disabling. > .
 * Service ID   :       <OSServiceId_SuspendAllInterrupts>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void SuspendAllInterrupts(void)
{
	if(suspend_all_count==0)
	{
		arch_suspend_int();
	}
	
	suspend_all_count++;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This service restores the  recognition status of interrupts saved 
    by the SuspendOSInterrupts service.> .
 * Service ID   :       <OSServiceId_ResumeOSInterrupts>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void ResumeOSInterrupts(void)
{
	suspend_os_count--;
	
	if(suspend_os_count == 0)
	{
		arch_set_ipl(osSaveIPL);
	}
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This service saves the  recognition status of interrupts of 
    category 2 and disables the recognition of these interrupts. > .
 * Service ID   :       <OSServiceId_SuspendOSInterrupts>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void SuspendOSInterrupts(void)
{
	if(suspend_os_count==0)
	{
		osSaveIPL = arch_get_ipl();
		arch_set_ipl(CFG_ISR2_IPL_MAX);
	}
	
	suspend_os_count++;
}

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/