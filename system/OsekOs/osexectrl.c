/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <osexectrl.c>
 *  @brief      <Operating system execution control >
 *  
 *  <>
 *  
 *  @author     <ISOFT >
 *  @date       <2012-09-14>
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
 * <This service returns the current application mode. It may be 
    used to write mode dependent code. > .
 * Service ID   :       <OSServiceId_GetActiveApplicationMode>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <AppModeType>    
 */
/******************************************************************************/
AppModeType GetActiveApplicationMode(void)
{
	return osActiveAppMode;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <The user can call this  system service to start the operating 
    system in a specific mode, see chapter 5, Application modes.  > .
 * Service ID   :       <OSServiceId_StartOS>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <Mode>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void StartOS(AppModeType Mode)
{
	OSDisableInterrupts();
	osActiveAppMode = Mode;
	OSFillStack(osSystemStack);
	OSSwitch2System();
	osInSystemStack = TRUE;
	OSInitCPU();
	OSInitSystem();
	Call_StartupHook();
	OSDispatch();
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <The user can call this  system service to abort the overall 
    system (e.g. emergency off). The operating system also calls 
    this function internally, if it  has reached an undefined internal 
    state and is no longer ready to run. 
      If a ShutdownHook is configured the hook routine 
    ShutdownHook is always called (with <Error> as argument) 
    before shutting down the operating system. 
     If ShutdownHook returns, further behaviour of ShutdownOS is 
    implementation specific. 
      In case of a system where OSEK OS and  OSEKtime OS 
    coexist, ShutdownHook has to return. 
      <Error> needs to be a valid error code supported by OSEK OS. 
    In case of a system where OSEK OS and OSEKtime OS 
    coexist, <Error> might also be a value accepted by OSEKtime 
    OS. In this case, if enabled  by an OSEKtime configuration 
    parameter, OSEKtime OS will be  shut down after OSEK OS 
    shutdown. > .
 * Service ID   :       <OSServiceId_ShutdownOS>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <Error>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void ShutdownOS(StatusType Error)
{
	OSDisableInterrupts();
	Call_ShutdownHook(Error);
	
	for(;;){
	}
}

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/