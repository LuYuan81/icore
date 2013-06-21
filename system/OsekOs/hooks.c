/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <hooks.c>
 *  @brief      <>
 *  
 *  <The OSEK operating system provides system specific hook routines to allow user-defined 
actions within the OS internal processing>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-19>
 */
/*============================================================================*/

/*=======[I N C L U D E S]====================================================*/
#include "Os.h"

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/**
 * @brief               <>
 * 
 * < This hook routine is called by the operating system at the end of 
      a system service which returns StatusType not equal E_OK. It 
      is called before returning to the task level. 
        This hook routine is called when an alarm expires and an error 
      is detected during task activation or event setting. 
        The ErrorHook is not called, if a system service called from 
      ErrorHook does not return E_OK as status value. Any error by 
      calling of system services from the  ErrorHook  can only be 
      detected by evaluating the status value. > .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <Error>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void ErrorHook(StatusType Error){

}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This hook routine is  called by the operating system before 
    executing a new task, but after the transition of the task to the 
    running state (to allow evaluation of the TaskID by GetTaskID).> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void PreTaskHook(void){

}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This hook routine is  called by the operating system after 
    executing the current task, but before leaving the task's running 
    state (to allow evaluation of the TaskID by GetTaskID).> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void PostTaskHook(void){
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This hook routine is called by the operating system at the end of 
      the operating system initialisation and before the scheduler is 
      running. At this time the application can initialise device drivers 
      etc.> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void StartupHook(void){
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This hook routine is called by the operating system when the 
      OS service ShutdownOS has been called. This routine is called 
      during the operating system shut down.> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <Error>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void ShutdownHook(StatusType Error){
}

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/