/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <Os.h>
 *  @brief      <>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-14>
 */
/*============================================================================*/
#ifndef OS_H
#define OS_H

/*=======[I N C L U D E S]====================================================*/
#include "config.h"
#include "Std_Types.h"
#include "Os_Types.h"
#include "arch.h"
#include "option.h"
#include "structs.h"
#include "error.h"

/*=======[M A C R O S]========================================================*/
#define TASK(name) void OSEK_TASK_##name(void)
#define ISR(name) void name(void)
#define ALARMCALLBACK(name) void name(void)
#define DeclareAlarmCallback(name) extern void name(void)
#define DeclareTask(TaskId)     extern void OSEK_TASK_##TaskId(void)
#define DeclareISR(name)	extern void name(void)
#define DeclareAlarm(AlarmId) 
#define DeclareEvent(EventId)
#define DeclareResource(ResourceId)  
#define DeclareCounter(CounterId) 

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
StatusType ActivateTask(TaskType TaskID);
StatusType TerminateTask(void);
StatusType ChainTask(TaskType TaskID);
StatusType Schedule(void);
StatusType GetTaskID(TaskRefType TaskID);
StatusType GetTaskState(TaskType TaskID, TaskStateRefType State);

StatusType GetResource(ResourceType ResID);
StatusType ReleaseResource(ResourceType ResID);

void DisableAllInterrupts(void);
void EnableAllInterrupts(void);
void ResumeAllInterrupts(void);
void SuspendAllInterrupts(void);
void ResumeOSInterrupts(void);
void SuspendOSInterrupts(void);

StatusType SetEvent(TaskType TaskID, EventMaskType Mask);
StatusType ClearEvent (EventMaskType Mask);
StatusType GetEvent(TaskType TaskID, EventMaskRefType Event);
StatusType WaitEvent(EventMaskType Mask);

StatusType GetAlarm(AlarmType AlarmID, TickRefType Tick);  
StatusType GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info);
StatusType CancelAlarm(AlarmType AlarmID);
StatusType SetRelAlarm(AlarmType AlarmID, TickType increment,TickType cycle);   
StatusType SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle);  

AppModeType GetActiveApplicationMode(void);
void StartOS(AppModeType Mode);
void ShutdownOS(StatusType Error);

StatusType IncrementCounter(CounterType CounterID);
StatusType GetCounterValue(CounterType CounterID, TickRefType Value);
StatusType GetElapsedCounterValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue);

void ErrorHook(StatusType Error);
void PreTaskHook(void);
void PostTaskHook(void);
void StartupHook(void);
void ShutdownHook(StatusType Error);

#endif

 /*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/