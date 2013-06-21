/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <kernel.c>
 *  @brief      <some critical fuction and additional fuction to OS >
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

/*=======[M A C R O S]========================================================*/
#define READY_MAP_SIZE ((CFG_PRIORITY_MAX-1)/8+1)

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
uint8 volatile osReadyIndex;
uint8 volatile osReadyMap[READY_MAP_SIZE];

const uint8 osMapTable[] = {0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3}; 
TaskType volatile osHighPriTask;
PriorityType volatile osHighPrio;
TaskType volatile osRunningTask;
TCB * volatile osRunningTcb;
boolean volatile osInSystemStack;

uint8 volatile suspend_all_count;
uint8 volatile suspend_os_count;
IPLType volatile osSaveIPL;
CallLevelType volatile osLevel;
LockerType volatile osDispatchLocker;

AppModeType volatile osActiveAppMode;

OSSrvParamType volatile osSrvParam1,osSrvParam2,osSrvParam3;
OSServiceIdType volatile osServiceId;

 /*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/**
 * @brief               <Fill the stack with 0xcc>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSFillStack(StackType stack) 
{
	StackPtrType ptr;

	for (ptr = (uint8*)stack.bottom; ptr < (uint8*)stack.top; ptr++) 
	{
		*ptr = STACK_FILL_PATTERN;
	}
}

/******************************************************************************/
/**
 * @brief               <Init task control block>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <TaskID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSInitTcb(TaskType TaskID)
{
	osTcb[TaskID].sp = osTaskStack[osTask[TaskID].stackid].top;
	osTcb[TaskID].stackBottom = osTaskStack[osTask[TaskID].stackid].bottom;
	
#if ((CFG_CC == BCC2) || (CFG_CC == ECC2))
	osTcb[TaskID].actCount=0;
#endif
	osTcb[TaskID].resCount=0;
	osTcb[TaskID].runPrio=osTask[TaskID].initPrio;
	
	if((osTaskAutoStartMask[TaskID]&osActiveAppMode)!=0)
	{
#if ((CFG_CC == BCC2)||(CFG_CC == ECC2))
  		osTcb[TaskID].actCount++;
#endif
		osTcb[TaskID].state = STATE_START;
		OSReadyQueueAppend(TaskID, osTcb[TaskID].runPrio);
		
		if ( (osHighPrio==INVALID_PRIORITY)||(osTcb[TaskID].runPrio > osHighPrio)) 
		{
			osHighPriTask = TaskID;
			osHighPrio = osTcb[TaskID].runPrio;
		}
	}	
	else
	{
		osTcb[TaskID].state=SUSPENDED;
	}
}

/******************************************************************************/
/**
 * @brief               <Init system>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSInitSystem(void)
{
	uint8 i;
	
	for(i=0;i<CFG_TASK_STACK_MAX;i++)
	{
		OSFillStack(osTaskStack[i]);
	}
	
	OSInitReadyTable();
	osHighPriTask=INVALID_TASK;
	osHighPrio = INVALID_PRIORITY;
	osRunningTask=INVALID_TASK;
	
	for(i=0;i<CFG_TASK_MAX;i++)
	{
		OSInitTcb(i);
	}
	
	for(i=0;i<CFG_COUNTER_MAX;i++)
	{
		OSInitCounterCB(i);
	}
	
	for(i=0;i<CFG_ALARM_MAX;i++)
	{
		OSInitAlarmCB(i);
	}
	
#if (CFG_EXTENDED_TASK_MAX>0)
	for(i=0;i<CFG_EXTENDED_TASK_MAX;i++)
	{
		osTaskEvent[i] = 0u;
		osTaskWaitEvent[i] = 0u;
	}
#endif

#if (CFG_STD_RESOURCE_MAX>0) 
	for(i=0;i<CFG_STD_RESOURCE_MAX;i++)
	{
		OSInitResource(i);
	}
#endif
}

/******************************************************************************/
/**
 * @brief               <Set the ready state of priority to bit map>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <prio>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSSetPrioBit(PriorityType prio)
{
	osReadyIndex |= 1<<(prio>>3);
	osReadyMap[prio>>3] |= 1<<(prio&0x07);
}

/******************************************************************************/
/**
 * @brief               <Clear the ready state of the priority from bit map>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <prio>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSClrPrioBit(PriorityType prio)
{
	uint8 index;
	index = (uint8)(prio>>3);
	osReadyMap[index] &= ~(1<<(prio&0x07));
       
	if(osReadyMap[index] ==0)
	{
		osReadyIndex &= ~(1<<(prio>>3));
	}
}

/******************************************************************************/
/**
 * @brief               <Check the input priority is or not be set in bit map already>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <prio>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <boolean>    
 */
/******************************************************************************/
boolean OSCheckPrioBit(PriorityType prio)
{
	boolean ret;
	
	if((osReadyMap[prio>>3]&(1<<(prio&0x07u)))!=0)
	{
		ret = TRUE;
	}
	else
	{
		ret = FALSE;
	}
	
	return ret;
}

/******************************************************************************/
/**
 * @brief               <Get the highest priority of the ready task>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <Priority>    
 */
/******************************************************************************/
PriorityType OSGetHighPrio(void)
{
	PriorityType highprio;
	
	if (osReadyIndex == 0) 
	{
		return INVALID_PRIORITY;
	}
	else if ((osReadyIndex & 0xF0u) != 0)
	{
		highprio = (uint8)(osMapTable[osReadyIndex>>4] + 4);
	}
	else 
	{
		highprio = osMapTable[osReadyIndex&0x0F];
	}

	if ((osReadyMap[highprio]& 0xF0u)!= 0)
	{
		highprio = (uint8)((highprio<<3)+osMapTable[osReadyMap[highprio]>>4] + 4);
	}
	else
	{
		highprio = (uint8)((highprio<<3)+osMapTable[osReadyMap[highprio]&0x0F]);
	}
			
	return highprio;
}

/******************************************************************************/
/**
 * @brief               <Init the array and variable which control task's priority>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSInitReadyTable(void)
{
	int i;
	int j;
	osReadyIndex = 0x00u;
	
	for ( i=0; i<READY_MAP_SIZE; i++)
	{
		osReadyMap[i] = 0x00u;
	}

	for ( i=0; i<CFG_PRIORITY_MAX; i++)
	{
#if ((CFG_CC == BCC1)||(CFG_CC == ECC1))
		osReadyTable[i] = INVALID_TASK;
#else
		osReadyQueueMark[i].head = 0;
		osReadyQueueMark[i].tail = 0;
		
		for ( j=0; j< osActivateQueueSize[i]; j++)
		{
			osReadyQueue[i][j] = INVALID_TASK;
		}
#endif
	}
}

/******************************************************************************/
/**
 * @brief               <Check the array which priority support tasks or resource is or not full>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <prio>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <boolean>    
 */
/******************************************************************************/
boolean OSReadyTableCheckFull(PriorityType prio)
{
	boolean ret;
	
#if ((CFG_CC == BCC1)||(CFG_CC == ECC1))
	if(osReadyTable[prio] != INVALID_TASK)
	{
#else
	if ((osReadyQueueMark[prio].tail+1)%osActivateQueueSize[prio]==osReadyQueueMark[prio].head)
	{
#endif	
		ret = TRUE;
	}
	else
	{
		ret = FALSE;
	}
	
	return ret;
}

/******************************************************************************/
/**
 * @brief               <Insert task in front of the queue that priority supports>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <task,prio>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSReadyQueueInsertFirst(TaskType task, PriorityType prio)
{
	if(OSReadyTableCheckFull(prio))
	{
		return;
	}
	
#if ((CFG_CC == BCC1)||(CFG_CC == ECC1))
	osReadyTable[prio] = task;
#else
	if (osReadyQueueMark[prio].head == 0)
	{
		osReadyQueueMark[prio].head = osActivateQueueSize[prio] - 1;
	}
	else 
	{
		osReadyQueueMark[prio].head--;
	}
	
	osReadyQueue[prio][osReadyQueueMark[prio].head] = task;
#endif	

	OSSetPrioBit(prio);
	return;
}

/******************************************************************************/
/**
 * @brief               <Insert task in back of the queue that priority supports>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <task,prio>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSReadyQueueAppend(TaskType task, PriorityType prio)
{
	if(OSReadyTableCheckFull(prio))
	{
		return;
	}
	
#if ((CFG_CC == BCC1)||(CFG_CC == ECC1))
	osReadyTable[prio] = task;
#else
	osReadyQueue[prio][osReadyQueueMark[prio].tail] = task;
	osReadyQueueMark[prio].tail++;
	if(osReadyQueueMark[prio].tail == osActivateQueueSize[prio])
	{
		osReadyQueueMark[prio].tail = 0;
	}
#endif	

	OSSetPrioBit(prio);
	return ;
}

/******************************************************************************/
/**
 * @brief               <Get the queue's first task>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <prio>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <TaskType>    
 */
/******************************************************************************/
TaskType OSReadyQueueGetFirst(PriorityType prio) 
{
	if (prio > CFG_PRIORITY_MAX )
	{
		return INVALID_TASK;
	}
	
#if ((CFG_CC == BCC1)||(CFG_CC == ECC1))
	return osReadyTable[prio];
#else
	return osReadyQueue[prio][osReadyQueueMark[prio].head];
#endif
}

/******************************************************************************/
/**
 * @brief               <Remove the first task of the queue>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <prio>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSReadyQueueRemoveFirst(PriorityType prio)
{
	if(!OSCheckPrioBit(prio))
	{
		return;
	}
	
#if ((CFG_CC == BCC1)||(CFG_CC == ECC1))
	osReadyTable[prio] = INVALID_TASK;
	OSClrPrioBit(prio);
#else
	osReadyQueue[prio][osReadyQueueMark[prio].head] = INVALID_TASK;
	osReadyQueueMark[prio].head++;
	if(osReadyQueueMark[prio].head == osActivateQueueSize[prio])
	{
		osReadyQueueMark[prio].head = 0;
	}
	
	if(osReadyQueueMark[prio].head == osReadyQueueMark[prio].tail)
	{
		OSClrPrioBit(prio);
	}
#endif	

	return;
}

/******************************************************************************/
/**
 * @brief               <when priority greater than the max value, change to ipl>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <prio>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <IPLType>    
 */
/******************************************************************************/
IPLType prio_to_ipl(PriorityType prio)
{
	if(prio < TASK_PRIORITY_MAX) 
	{
		return 0;
	}
	
	return (IPLType) (prio - TASK_PRIORITY_MAX);
}

/******************************************************************************/
/**
 * @brief               <Change ipl back to priority>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <ipl>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <PriorityType>    
 */
/******************************************************************************/
PriorityType ipl_to_prio(IPLType ipl)
{
	return (PriorityType)(ipl + TASK_PRIORITY_MAX);
}

#if (CFG_INTERNAL_RESOURCE_MAX>0)
/******************************************************************************/
/**
 * @brief               <>
 * 
 * <When task has internal resource and the ceiling priority greater than the running task's
 priority, remove the running task from the front of ready queue and insert the task into the
 front of the ready queue.> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSGetInternalResource(void)
{
	if(osTaskCeiling[osRunningTask] > osTcb[osRunningTask].runPrio)
	{
		OSReadyQueueRemoveFirst(osTcb[osRunningTask].runPrio);
		osTcb[osRunningTask].runPrio = osTaskCeiling[osRunningTask];
		OSReadyQueueInsertFirst(osRunningTask, osTcb[osRunningTask].runPrio);
		
		if(osTcb[osRunningTask].runPrio>osHighPrio)
		{
			osHighPrio = osTcb[osRunningTask].runPrio;
			osHighPriTask = osRunningTask;
		}
	}
}
#endif

#if (CFG_ERRORHOOK == TRUE)
/******************************************************************************/
/**
 * @brief               <call the ErrorHook() function>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <OSSrvID,Error>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void call_errorhook(OSServiceIdType OSSrvID, StatusType Error)
{
	CallLevelType savelevel;
	savelevel = osLevel;
	osLevel = LEVEL_ERRORHOOK;
	osServiceId = OSSrvID;
	ErrorHook(Error);
	osLevel = savelevel;
}
#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/