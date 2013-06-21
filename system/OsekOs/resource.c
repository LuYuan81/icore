/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <resource.c>
 *  @brief      <>
 *  
 *  <The resource management is used to co-ordinate concurrent accesses of several tasks with 
different priorities to shared resources, e.g. management entities (scheduler), program 
sequences, memory or hardware areas. 
The resource management is mandatory for all conformance classes. 
The resource management can optionally be extended to co-ordinate concurrent accesses of 
tasks and interrupt service routines. >
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

#if (CFG_STD_RESOURCE_MAX>0) 
/******************************************************************************/
/**
 * @brief               <Init the resource control block>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <ResID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSInitResource(ResourceType ResID)
{
	osResourceCB[ResID].saveCount = 0;
	osResourceCB[ResID].savePrio = INVALID_PRIORITY;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This call serves to enter critical sections in the code that are 
    assigned to the resource referenced by <ResID>. A critical 
    section shall always be left using ReleaseResource. > .
 * Service ID   :       <OSServiceId_GetResource>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <ResID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <StatusType>    
 */
/******************************************************************************/
StatusType GetResource(ResourceType ResID)
{
	PriorityType prio,savePrio;
#if (CFG_STATUS==STATUS_EXTENDED)
	if((ResID<0)||(ResID >= CFG_STD_RESOURCE_MAX))
	{
		Call_ErrorHook(OSError_Save_GetResource(ResID), OSServiceId_GetResource, E_OS_ID);
		return E_OS_ID;
	}
	
	if(osResourceCB[ResID].savePrio != INVALID_PRIORITY)
	{
		Call_ErrorHook(OSError_Save_GetResource(ResID), OSServiceId_GetResource, E_OS_ACCESS);
		return E_OS_ACCESS;
	}
#endif

	prio = osResource[ResID].ceiling;
	
	if (osLevel == LEVEL_TASK)
	{
		if(osTask[osRunningTask].initPrio > prio)
		{
			Call_ErrorHook(OSError_Save_GetResource(ResID), OSServiceId_GetResource, E_OS_ACCESS);
			return E_OS_ACCESS;
		}
		
		osTcb[osRunningTask].resCount++;
		osResourceCB[ResID].saveCount = osTcb[osRunningTask].resCount;
		
		if(prio >=  TASK_PRIORITY_MAX)
		{
			savePrio = ipl_to_prio(arch_get_ipl());
			arch_set_ipl(prio_to_ipl(prio));
			osDispatchLocker++;
		}
		else 
		{
			savePrio = osTcb[osRunningTask].runPrio;
			if(prio > osTcb[osRunningTask].runPrio)
			{				
				OSReadyQueueRemoveFirst(osTcb[osRunningTask].runPrio);
				OSReadyQueueInsertFirst(osRunningTask, prio);
				osTcb[osRunningTask].runPrio = prio;			
			}
			if(prio > osHighPrio)
			{
				osHighPrio = prio;
				osHighPriTask = osRunningTask;
			}	
		}
	}
	else
	{
		if( prio < TASK_PRIORITY_MAX )
		{
			Call_ErrorHook(OSError_Save_GetResource(ResID), OSServiceId_GetResource, E_OS_ACCESS);
			return E_OS_ACCESS;
		}
		
		savePrio = ipl_to_prio(arch_get_ipl());
		
		if ( prio > savePrio)
		{
			arch_set_ipl(prio_to_ipl(prio));
		}
	}
	
	osResourceCB[ResID].savePrio = savePrio;
	return E_OK;
	
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <ReleaseResource is the counterpart of  GetResource and 
    serves to leave critical sections in the code that are assigned to 
    the resource referenced by <ResID>. > .
 * Service ID   :       <OSServiceId_ReleaseResource>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <ResID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <StatusType>    
 */
/******************************************************************************/
StatusType ReleaseResource(ResourceType ResID)
{
	PriorityType prio,savePrio;
	
#if (CFG_STATUS==STATUS_EXTENDED)
	if((ResID<0)||(ResID >= CFG_STD_RESOURCE_MAX))
	{
		Call_ErrorHook(OSError_Save_ReleaseResource(ResID), OSServiceId_ReleaseResource, E_OS_ID);
		return E_OS_ID;
	}
	
	if(osResourceCB[ResID].savePrio == INVALID_PRIORITY)
	{
		Call_ErrorHook(OSError_Save_ReleaseResource(ResID), OSServiceId_ReleaseResource, E_OS_NOFUNC);
		return E_OS_NOFUNC;
	}
#endif

	prio = osResource[ResID].ceiling;
	savePrio = osResourceCB[ResID].savePrio;
	
	if (osLevel == LEVEL_TASK)
	{
		if(osTask[osRunningTask].initPrio > prio)
		{
			Call_ErrorHook(OSError_Save_ReleaseResource(ResID), OSServiceId_ReleaseResource, E_OS_ACCESS);
			return E_OS_ACCESS;
		}
		
		if(osResourceCB[ResID].saveCount!=osTcb[osRunningTask].resCount)
		{
			Call_ErrorHook(OSError_Save_ReleaseResource(ResID), OSServiceId_ReleaseResource, E_OS_NOFUNC);
			return E_OS_NOFUNC;
		}
		
		osTcb[osRunningTask].resCount--;
		
		if(prio >=  TASK_PRIORITY_MAX)
		{
			arch_set_ipl(prio_to_ipl(savePrio));
			
			osDispatchLocker--;
		}
		else 
		{
			if(prio > savePrio)
			{				
				OSReadyQueueRemoveFirst(osTcb[osRunningTask].runPrio);
				OSReadyQueueInsertFirst(osRunningTask, savePrio);
			}
			
			osTcb[osRunningTask].runPrio = savePrio;		
		}
	}
	else
	{
		if( prio < TASK_PRIORITY_MAX )
		{
			Call_ErrorHook(OSError_Save_ReleaseResource(ResID), OSServiceId_ReleaseResource, E_OS_ACCESS);
			return E_OS_ACCESS;
		}
		
		if( prio > savePrio )
		{
			arch_set_ipl(prio_to_ipl(savePrio));
		}
	}
	
	osResourceCB[ResID].saveCount=0;
	osResourceCB[ResID].savePrio = INVALID_PRIORITY;
	
	osHighPrio = OSGetHighPrio();
	osHighPriTask = OSReadyQueueGetFirst(osHighPrio);
	
#if ( CFG_SCHEDULE != PREEMPTIVE_NON)	
	if(osHighPriTask != osRunningTask)
	{	
		if(osDispatchLocker == 0)
		{
		  OSDispatch();
		}
	}
#endif
	
	return E_OK;
}

#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/