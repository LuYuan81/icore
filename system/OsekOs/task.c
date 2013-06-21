/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <task.c>
 *  @brief      <>
 *  
 *  <Complex control software can conveniently be subdivided in parts executed according to their 
real-time requirements. These parts can be implemented by the means of tasks. A task 
provides the framework for the execution of functions.  The operating system provides 
concurrent and asynchronous execution of tasks. The scheduler organises the sequence of task 
execution. 
The OSEK operating system provides a task  switching mechanism, including a mechanism which
 is active when no other system or application functionality is active. This mechanism is called 
 idle-mechanism. >
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
 * < The task <TaskID> is transferred from the suspended state into 
      the  ready state14 . The operating system ensures that the task 
      code is being executed from the first statement.> .
 * Service ID   :       <OSServiceId_ActivateTask>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <TaskID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType ActivateTask(TaskType TaskID)
{
	PriorityType prio;

#if (CFG_STATUS==STATUS_EXTENDED)
	if((TaskID<0)||(TaskID>=CFG_TASK_MAX))
	{
		Call_ErrorHook(OSError_Save_ActivateTask(TaskID),OSServiceId_ActivateTask, E_OS_ID);
		return E_OS_ID;
	}
#endif
	
#if ((CFG_CC == BCC1)||(CFG_CC == ECC1))
	if(osTcb[TaskID].state != SUSPENDED)
	{
#else
	if(osTcb[TaskID].actCount >= osTask[TaskID].maxAct)
	{
#endif
		Call_ErrorHook(OSError_Save_ActivateTask(TaskID),OSServiceId_ActivateTask, E_OS_LIMIT);
		return E_OS_LIMIT;
	}

#if ((CFG_CC == BCC2)||(CFG_CC == ECC2))
	osTcb[TaskID].actCount++;
	if(osTcb[TaskID].state == SUSPENDED)
	{
		osTcb[TaskID].state = STATE_START;
	}
#else
	osTcb[TaskID].state = STATE_START;
#endif

	prio = osTask[TaskID].initPrio;
	OSReadyQueueAppend(TaskID, prio);
	if ( (osHighPrio==INVALID_PRIORITY)||(prio > osHighPrio)) 
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
		
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * < This service causes the termination of the calling task. The 
      calling task is transferred from the  running state into the 
      suspended state> .
 * Service ID   :       <OSServiceId_TerminateTask>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
StatusType TerminateTask(void)
{
#if (CFG_STATUS==STATUS_EXTENDED)
	if(osLevel != LEVEL_TASK)
	{
		Call_ErrorHook(OSError_Save_TerminateTask() ,OSServiceId_TerminateTask, E_OS_CALLEVEL);
		return E_OS_CALLEVEL;
	}
	
	if(osTcb[osRunningTask].resCount>0)
	{
		Call_ErrorHook(OSError_Save_TerminateTask() ,OSServiceId_TerminateTask, E_OS_RESOURCE);
		return E_OS_RESOURCE;
	}
#endif

	Call_PostTaskHook();
	OSDisableInterrupts();
	
#if ((CFG_CC == BCC1)||(CFG_CC == ECC1))
	osRunningTcb->state = SUSPENDED;
#else
	osRunningTcb->actCount--;
	if ( osRunningTcb->actCount > 0) 
	{
		osRunningTcb->state = STATE_START;
	}
	else
	{
		osRunningTcb->state = SUSPENDED;
	}
#endif


	OSReadyQueueRemoveFirst(osRunningTcb->runPrio);

	osRunningTcb->sp = osTaskStack[osTask[osRunningTask].stackid].top;
	osRunningTcb->resCount=0;
	osRunningTcb->runPrio=osTask[osRunningTask].initPrio;
	
#if (CFG_EXTENDED_TASK_MAX>0)
	if(osRunningTask<CFG_EXTENDED_TASK_MAX)
	{
		osTaskEvent[osRunningTask] = 0u;
		osTaskWaitEvent[osRunningTask] = 0u;
	}
#endif

	if(osHighPriTask == osRunningTask)
	{
		osHighPrio = OSGetHighPrio();
		osHighPriTask = OSReadyQueueGetFirst(osHighPrio);
	}

	osRunningTcb = NULL;
	osRunningTask = INVALID_TASK;	
	osDispatchLocker = 0;	
	OSDispatch();
	
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * < This service causes the  termination of the calling task. After 
      termination of the calling task  a succeeding task <TaskID> is 
      activated. Using this service, it ensures that the succeeding task 
      starts to run at the earliest after the calling task has been 
      terminated.> .
 * Service ID   :       <OSServiceId_ChainTask>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <TaskID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType ChainTask(TaskType TaskID)
{
	PriorityType prio;
	
#if (CFG_STATUS==STATUS_EXTENDED)
	if((TaskID<0)||(TaskID>=CFG_TASK_MAX))
	{
		Call_ErrorHook(OSError_Save_ChainTask(TaskID),OSServiceId_ChainTask, E_OS_ID);
		return E_OS_ID;
	}
	
	if(osLevel != LEVEL_TASK)
	{ 
		Call_ErrorHook(OSError_Save_ChainTask(TaskID),OSServiceId_ChainTask, E_OS_CALLEVEL);
 		return E_OS_CALLEVEL;
	}
	
	if(osTcb[osRunningTask].resCount>0)
	{ 
		Call_ErrorHook(OSError_Save_ChainTask(TaskID),OSServiceId_ChainTask, E_OS_RESOURCE);
		return E_OS_RESOURCE;
	}
#endif


#if ((CFG_CC == BCC2) || (CFG_CC == ECC2))
	if((osTcb[TaskID].actCount >= osTask[TaskID].maxAct)&&(TaskID!=osRunningTask))
	{
#else
	if((osTcb[TaskID].state != SUSPENDED)&&(TaskID!=osRunningTask))
	{
#endif
		Call_ErrorHook(OSError_Save_ChainTask(TaskID),OSServiceId_ChainTask, E_OS_LIMIT);
		return E_OS_LIMIT;
	}

	Call_PostTaskHook();
	OSDisableInterrupts();
	
#if ((CFG_CC == BCC1)||(CFG_CC == ECC1))
	osRunningTcb->state = SUSPENDED;
#else
	osRunningTcb->actCount--;
	if ( osRunningTcb->actCount > 0) 
	{
		osRunningTcb->state = STATE_START;
	}
	else
	{
		osRunningTcb->state = SUSPENDED;
	}
#endif
	
	OSReadyQueueRemoveFirst(osRunningTcb->runPrio);

	osRunningTcb->sp = osTaskStack[osTask[osRunningTask].stackid].top;
	osRunningTcb->resCount=0;
	osRunningTcb->runPrio=osTask[osRunningTask].initPrio;
	
#if (CFG_EXTENDED_TASK_MAX>0)
	if(osRunningTask<CFG_EXTENDED_TASK_MAX)
	{
		osTaskEvent[osRunningTask] = 0u;
		osTaskWaitEvent[osRunningTask] = 0u;
	}
#endif

#if ((CFG_CC == BCC2)||(CFG_CC == ECC2))
	osTcb[TaskID].actCount++;
	
	if(osTcb[TaskID].state == SUSPENDED)
	{
		osTcb[TaskID].state = STATE_START;
	}
#else
	osTcb[TaskID].state = STATE_START;
#endif

	prio = osTask[TaskID].initPrio;
	OSReadyQueueAppend(TaskID, prio);

	if(osHighPriTask == osRunningTask)
	{
		osHighPrio = OSGetHighPrio();
		osHighPriTask = OSReadyQueueGetFirst(osHighPrio);
	}

	osRunningTcb = NULL;
	osRunningTask = INVALID_TASK;	
	osDispatchLocker = 0;	
	OSDispatch();
		
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * < If a higher-priority task is ready, the internal resource of the task 
      is released, the current task is put into the  ready state, its 
      context is saved and the higher-priority task is executed. 
      Otherwise the calling task is continued. > .
 * Service ID   :       <OSServiceId_Schedule>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType Schedule(void)
{
	
#if (CFG_STATUS==STATUS_EXTENDED)
	if(osLevel != LEVEL_TASK)
	{
		Call_ErrorHook(OSError_Save_Schedule(),OSServiceId_Schedule, E_OS_CALLEVEL);
		return E_OS_CALLEVEL;
	}
	
	if(osTcb[osRunningTask].resCount>0)
	{
		Call_ErrorHook(OSError_Save_Schedule(),OSServiceId_Schedule, E_OS_RESOURCE);
		return E_OS_RESOURCE;
	}
#endif

	OSDisableInterrupts();
#if (CFG_INTERNAL_RESOURCE_MAX >0 )
	if(osTaskCeiling[osRunningTask] != 0)
	{
		OSReadyQueueRemoveFirst(osRunningTcb->runPrio);
		osRunningTcb->runPrio = osTask[osRunningTask].initPrio;
		OSReadyQueueAppend(osRunningTask, osRunningTcb->runPrio);
	}
#endif

	osHighPrio = OSGetHighPrio();
	osHighPriTask = OSReadyQueueGetFirst(osHighPrio);
	if(osHighPriTask != osRunningTask)
	{	
		osDispatchLocker = 0;
		OSDispatch();
	}
	
#if (CFG_INTERNAL_RESOURCE_MAX >0 )
	OSGetInternalResource();
#endif

	OSEnableInterrupts();
	
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <GetTaskID returns the information about the TaskID of the task 
      which is currently running.  > .
 * Service ID   :       <OSServiceId_GetTaskID>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <TaskID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType GetTaskID(TaskRefType TaskID)
{
	*TaskID = osRunningTask;
	return E_OK;
}

StatusType GetTaskState(TaskType TaskID, TaskStateRefType State)
{
	
#if (CFG_STATUS==STATUS_EXTENDED)
	if((TaskID<0)||(TaskID>=CFG_TASK_MAX))
	{
		Call_ErrorHook(OSError_Save_GetTaskState(TaskID, State),OSServiceId_GetTaskState, E_OS_ID);
		return E_OS_ID;
	}
#endif

	if (osTcb[TaskID].state == STATE_START)
	{
		*State = READY;
	}
	else 
	{
		*State = osTcb[TaskID].state;
	}
	
	return E_OK;
}

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/