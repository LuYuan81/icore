/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <event.c>
 *  @brief      <>
 *  
 *  <Events are objects managed by the operating system. They are not independent objects, but 
assigned to extended tasks. Each extended task has a definite number of events. This task is 
called the owner of these events. An individual event is identified by its owner and its name 
(or mask).  When activating an extended task, these events are cleared by the operating 
system. Events can be used to communicate binary information to the extended task to which 
they are assigned. The meaning of events is defined by the application, e.g. signalling of an 
expiring timer, the availability of a resource, the reception of a message, etc. >
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
#if (CFG_EXTENDED_TASK_MAX>0)
/******************************************************************************/
/**
 * @brief               <>
 * 
 * <The service may be called from an interrupt service routine and 
    from the task level, but not from hook routines. 
    The events of task <TaskID> are set according to the event 
    mask <Mask>. Calling SetEvent causes the task <TaskID> to 
    be transferred to the  ready state, if it was waiting for at least 
    one of the events specified in <Mask> > .
 * Service ID   :       <OSServiceId_SetEvent>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <TaskID,Mask>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType SetEvent(TaskType TaskID, EventMaskType Mask)
{
	PriorityType prio;

#if (CFG_STATUS==STATUS_EXTENDED)
	if((TaskID<0)||(TaskID>=CFG_TASK_MAX))
	{
		Call_ErrorHook(OSError_Save_SetEvent(TaskID,Mask), OSServiceId_SetEvent, E_OS_ID);
		return E_OS_ID;
	}
	
	if(TaskID>=CFG_EXTENDED_TASK_MAX)
	{
		Call_ErrorHook(OSError_Save_SetEvent(TaskID,Mask), OSServiceId_SetEvent, E_OS_ACCESS);
		return E_OS_ACCESS;
	}
	
	if(osTcb[TaskID].state == SUSPENDED)
	{
		Call_ErrorHook(OSError_Save_SetEvent(TaskID,Mask), OSServiceId_SetEvent, E_OS_STATE);
		return E_OS_STATE;
	}
#endif
	
	osTaskEvent[TaskID] |= Mask;

	if (osTcb[TaskID].state == WAITING)
	{
		if ((osTaskEvent[TaskID]&osTaskWaitEvent[TaskID]) !=0)
		{
			osTcb[TaskID].state = READY;
			prio = osTask[TaskID].initPrio;
			OSReadyQueueAppend(TaskID, prio);
			if ((osHighPriTask==INVALID_TASK)||(prio > osHighPrio)) 
			{
				osHighPriTask = TaskID;
				osHighPrio = prio;
#if ( CFG_SCHEDULE != PREEMPTIVE_NON)
				if(osDispatchLocker==0)
				{
		
		
					OSDispatch();
				}
#endif
			}	
		}
	}       

	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <The events of the extended task calling ClearEvent are cleared 
  according to the event mask <Mask> > .
 * Service ID   :       <OSServiceId_ClearEvent>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <Mask>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType ClearEvent (EventMaskType Mask)
{
#if (CFG_STATUS==STATUS_EXTENDED)
	if(osLevel != LEVEL_TASK)
	{
		Call_ErrorHook(OSError_Save_ClearEvent(Mask), OSServiceId_ClearEvent, E_OS_CALLEVEL);
		return E_OS_CALLEVEL;
	}
	
	if(osRunningTask>=CFG_EXTENDED_TASK_MAX)
	{
		Call_ErrorHook(OSError_Save_ClearEvent(Mask), OSServiceId_ClearEvent, E_OS_ACCESS);
		return E_OS_ACCESS;
	}
#endif

	osTaskEvent[osRunningTask] &= (~Mask);
	
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <This service returns the current state of all event bits of the task 
    <TaskID>, not the events that the task is waiting for. 
      The service may be called from  interrupt service routines, task 
      level and some hook routines . 
      The current status of the event mask of task <TaskID> is copied 
       to <Event> . >.         
 * Service ID   :       <OSServiceId_GetEvent>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <TaskID>
 * @param[out]          <Event>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType GetEvent(TaskType TaskID, EventMaskRefType Event)
{
	
#if (CFG_STATUS==STATUS_EXTENDED)
	if((TaskID<0)||(TaskID>=CFG_TASK_MAX))
	{
		Call_ErrorHook(OSError_Save_GetEvent(TaskID,Event), OSServiceId_GetEvent, E_OS_ID);
		return E_OS_ID;
	}
	
	if(TaskID>=CFG_EXTENDED_TASK_MAX)
	{
		Call_ErrorHook(OSError_Save_GetEvent(TaskID,Event), OSServiceId_GetEvent, E_OS_ACCESS);
		return E_OS_ACCESS;
	}
	
	if(osTcb[TaskID].state == SUSPENDED)
	{
		Call_ErrorHook(OSError_Save_GetEvent(TaskID,Event), OSServiceId_GetEvent, E_OS_STATE);
		return E_OS_STATE;
	}
#endif

	*Event = osTaskEvent[TaskID];
	
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <The state of the calling task is set to waiting, unless at least one 
     of the events specified in <Mask> has already been set. > .
 * Service ID   :       <OSServiceId_WaitEvent>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <Mask>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType WaitEvent(EventMaskType Mask)
{
	PriorityType prio;
	TaskType TaskID;
	
#if (CFG_STATUS==STATUS_EXTENDED)
	if(osLevel != LEVEL_TASK)
	{
		Call_ErrorHook(OSError_Save_WaitEvent(Mask), OSServiceId_WaitEvent, E_OS_CALLEVEL);
		return E_OS_CALLEVEL;
	}
	
	if(osRunningTask>=CFG_EXTENDED_TASK_MAX)
	{
		Call_ErrorHook(OSError_Save_WaitEvent(Mask), OSServiceId_WaitEvent, E_OS_ACCESS);
		return E_OS_ACCESS;
	}
	
	if(osTcb[osRunningTask].resCount>0)
	{
		Call_ErrorHook(OSError_Save_WaitEvent(Mask), OSServiceId_WaitEvent, E_OS_RESOURCE);
		return E_OS_RESOURCE;
	}
#endif

	DisableAllInterrupts();
	TaskID = osRunningTask;
	prio = osTcb[TaskID].runPrio;
	osTaskWaitEvent[TaskID]  = Mask;
	
	if((osTaskEvent[TaskID] & Mask) == 0)
	{
		Call_PostTaskHook();
		osTcb[TaskID].state = WAITING;
		OSReadyQueueRemoveFirst(prio);
	
	 	osTcb[TaskID].runPrio = osTask[TaskID].initPrio;

		prio = OSGetHighPrio();
		osHighPrio = prio;
		osHighPriTask = OSReadyQueueGetFirst(prio);
		osDispatchLocker = 0;
		OSDispatch();
	}
	
	EnableAllInterrupts();
	
	return E_OK;
}

#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/