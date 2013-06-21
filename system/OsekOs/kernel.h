/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <kernel.h>
 *  @brief      <>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-19>
 */
/*============================================================================*/

#ifndef _KERNEL_H
#define _KERNEL_H

/*=======[M A C R O S]========================================================*/
#define OSDispatch() arch_dispatch()
#define OSEnableInterrupts() arch_enable_int()
#define OSDisableInterrupts() arch_disable_int()

#if (CFG_ERRORHOOK == TRUE)
void call_errorhook(OSServiceIdType OSSrvID, StatusType Error);
#define Call_ErrorHook(x,OSSrvID,ecode) {if(osLevel !=LEVEL_ERRORHOOK){SuspendAllInterrupts();x;call_errorhook(OSSrvID,ecode);ResumeAllInterrupts();}}
#else
#define Call_ErrorHook(x,OSSrvID,ecode) 
#endif
#if (CFG_PRETASKHOOK== TRUE)
#define Call_PreTaskHook()  PreTaskHook()
#else
#define Call_PreTaskHook() 
#endif
#if (CFG_POSTTASKHOOK == TRUE)
#define Call_PostTaskHook() PostTaskHook()
#else
#define Call_PostTaskHook() 
#endif
#if (CFG_STARTUPHOOK == TRUE)
#define Call_StartupHook() StartupHook()
#else
#define Call_StartupHook() 
#endif
#if (CFG_SHUTDOWNHOOK == TRUE)
#define Call_ShutdownHook(ecode)  ShutdownHook(ecode)
#else
#define Call_ShutdownHook(ecode)  
#endif

/*=======[E X T E R N A L   D A T A]==========================================*/
extern TaskType volatile osHighPriTask;
extern PriorityType volatile osHighPrio;
extern TaskType volatile osRunningTask;
extern TCB * volatile osRunningTcb;
extern boolean volatile osInSystemStack;
extern uint8 volatile suspend_all_count;
extern uint8 volatile suspend_os_count;
extern CallLevelType volatile osLevel;
extern LockerType volatile osDispatchLocker;
extern IPLType volatile osSaveIPL;
extern AppModeType volatile osActiveAppMode;
extern OSSrvParamType volatile osSrvParam1,osSrvParam2,osSrvParam3;
extern OSServiceIdType volatile osServiceId;

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
void OSFillStack(StackType stack);
void OSInitTcb(TaskType id);
void OSInitSystem(void);

TickType OSAddTicks(TickType value, TickType base, TickType maxticks);
TickType OSSubTicks(TickType newvalue, TickType oldvalue , TickType maxticks);
void OSInitAlarmCB(AlarmType id);
void OSInitCounterCB(CounterType id);
void OSInsertAlarm(AlarmType alarmid, AlarmRefType almque, TickType curTick);
void OSDeleteAlarm(AlarmType alarmid, AlarmRefType almque);

void OSInitReadyTable(void);
void OSReadyQueueInsertFirst(TaskType task, PriorityType prio);
void OSReadyQueueAppend(TaskType task, PriorityType prio);
TaskType OSReadyQueueGetFirst(PriorityType prio) ;
void OSReadyQueueRemoveFirst(PriorityType prio);
PriorityType OSGetHighPrio(void);
IPLType prio_to_ipl(PriorityType prio);
PriorityType ipl_to_prio(IPLType ipl);

void OSGetInternalResource(void);
void OSInitResource(ResourceType ResID);

#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/