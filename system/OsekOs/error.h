/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <error.h>
 *  @brief      <some macros of error and service id>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-14>
 */
/*============================================================================*/
#ifndef _ERROR_H
#define _ERROR_H

/*=======[M A C R O S]========================================================*/
#ifndef E_OK
	#define E_OK 0x00
#endif

#define E_OS_ACCESS 	0x01
#define E_OS_CALLEVEL 	0x02
#define E_OS_ID 		0x03
#define E_OS_LIMIT 		0x04
#define E_OS_NOFUNC 	0x05
#define E_OS_RESOURCE 	0x06
#define E_OS_STATE 		0x07
#define E_OS_VALUE 		0x08

#define OSServiceId_ActivateTask					((OSServiceIdType) 0)
#define OSServiceId_TerminateTask					((OSServiceIdType) 1)
#define OSServiceId_ChainTask						((OSServiceIdType) 2)
#define OSServiceId_Schedule						((OSServiceIdType) 3)
#define OSServiceId_GetTaskID						((OSServiceIdType) 4)
#define OSServiceId_GetTaskState					((OSServiceIdType) 5)
#define OSServiceId_EnableAllInterrupts				((OSServiceIdType) 6)
#define OSServiceId_DisableAllInterrupts			((OSServiceIdType) 7)
#define OSServiceId_ResumeAllInterrupts				((OSServiceIdType) 8)
#define OSServiceId_SuspendAllInterrupts			((OSServiceIdType) 9)
#define OSServiceId_ResumeOSInterrupts				((OSServiceIdType) 10)
#define OSServiceId_SuspendOSInterrupts				((OSServiceIdType) 11)
#define OSServiceId_GetResource						((OSServiceIdType) 12)
#define OSServiceId_ReleaseResource					((OSServiceIdType) 13)
#define OSServiceId_SetEvent						((OSServiceIdType) 14)
#define OSServiceId_ClearEvent						((OSServiceIdType) 15)
#define OSServiceId_GetEvent						((OSServiceIdType) 16)
#define OSServiceId_WaitEvent						((OSServiceIdType) 17)
#define OSServiceId_GetAlarmBase					((OSServiceIdType) 18)
#define OSServiceId_GetAlarm						((OSServiceIdType) 19)
#define OSServiceId_SetRelAlarm						((OSServiceIdType) 20)
#define OSServiceId_SetAbsAlarm						((OSServiceIdType) 21)
#define OSServiceId_CancelAlarm						((OSServiceIdType) 22)
#define OSServiceId_GetActiveApplicationMode		((OSServiceIdType) 23)
#define OSServiceId_StartOS							((OSServiceIdType) 24)
#define OSServiceId_ShutdownOS						((OSServiceIdType) 25)
#define OSServiceId_IncrementCounter				((OSServiceIdType) 26)
#define OSServiceId_GetCounterValue					((OSServiceIdType) 27)
#define OSServiceId_GetElapsedCounterValue			((OSServiceIdType) 28)

#define OSErrorGetServiceId()	 (osServiceId)

#define OSError_ActivateTask_TaskID()				(osSrvParam1.taskid)
#define OSError_ChainTask_TaskID()					(osSrvParam1.taskid)
#define OSError_GetTaskID_TaskID()					(osSrvParam1.taskref)
#define OSError_GetTaskState_TaskID()				(osSrvParam1.taskid)
#define OSError_GetTaskState_State()				(osSrvParam2.stateref)
#define OSError_GetResource_ResID()					(osSrvParam1.resourceid)
#define OSError_ReleaseResource_ResID()				(osSrvParam1.resourceid)
#define OSError_SetEvent_TaskID()					(osSrvParam1.taskid)
#define OSError_SetEvent_Mask()						(osSrvParam2.eventmask)
#define OSError_ClearEvent_Mask()					(osSrvParam1.eventmask)
#define OSError_GetEvent_TaskID()					(osSrvParam1.taskid)
#define OSError_GetEvent_Mask()						(osSrvParam2.eventref)
#define OSError_WaitEvent_Mask()					(osSrvParam1.eventmask)
#define OSError_GetAlarmBase_AlarmID()				(osSrvParam1.alarmid)
#define OSError_GetAlarmBase_Info()					(osSrvParam2.baseref)
#define OSError_GetAlarm_AlarmID()					(osSrvParam1.alarmid)
#define OSError_GetAlarm_Tick()						(osSrvParam2.tickref)
#define OSError_SetRelAlarm_AlarmID()				(osSrvParam1.alarmid)
#define OSError_SetRelAlarm_tickement()				(osSrvParam2.tick)
#define OSError_SetRelAlarm_tick()					(osSrvParam3.tick)
#define OSError_SetAbsAlarm_AlarmID()				(osSrvParam1.alarmid)
#define OSError_SetAbsAlarm_start()					(osSrvParam2.start)
#define OSError_SetAbsAlarm_tick()					(osSrvParam3.tick)
#define OSError_CancelAlarm_AlarmID()				(osSrvParam1.alarmid)

#define OSError_Save_ActivateTask(param1){osSrvParam1.taskid=(param1);}
#define OSError_Save_TerminateTask() 
#define OSError_Save_ChainTask(param1){osSrvParam1.taskid=(param1);}
#define OSError_Save_Schedule() 
#define OSError_Save_GetTaskID(param1){osSrvParam1.taskref=(param1);}
#define OSError_Save_GetTaskState(param1, param2){osSrvParam1.taskid=(param1); osSrvParam2.stateref=(param2);}
#define OSError_Save_GetResource(param1){osSrvParam1.resourceid=(param1);}
#define OSError_Save_ReleaseResource(param1){osSrvParam1.resourceid=(param1);}
#define OSError_Save_SetEvent(param1, param2){osSrvParam1.taskid=(param1);osSrvParam2.eventmask=(param2);}
#define OSError_Save_ClearEvent(param1){osSrvParam1.eventmask=(param1);}
#define OSError_Save_GetEvent(param1, param2){osSrvParam1.taskid=(param1);osSrvParam2.eventref=(param2);}
#define OSError_Save_WaitEvent(param1){osSrvParam1.eventmask=(param1);}
#define OSError_Save_GetAlarm(param1, param2){osSrvParam1.alarmid=(param1);osSrvParam2.tickref=(param2);}
#define OSError_Save_GetAlarmBase(param1,param2){osSrvParam1.alarmid=(param1);osSrvParam2.baseref=(param2);}
#define OSError_Save_CancelAlarm(param1){osSrvParam1.alarmid=(param1);}
#define OSError_Save_SetRelAlarm(param1,param2,param3){osSrvParam1.alarmid=(param1);osSrvParam2.tick=(param2);osSrvParam3.tick=(param3);}   
#define OSError_Save_SetAbsAlarm(param1, param2, param3){osSrvParam1.alarmid=(param1);osSrvParam2.tick=(param2);osSrvParam3.tick=(param3);}  
#define OSError_Save_IncrementCounter(param1){osSrvParam1.counterid=(param1);}
#define OSError_Save_GetCounterValue(param1, param2){osSrvParam1.counterid=(param1);osSrvParam2.tickref=(param2);}
#define OSError_Save_GetElapsedCounterValue(param1, param2, param3){osSrvParam1.counterid=(param1);osSrvParam2.tickref=(param2);osSrvParam3.tickref=(param3);}

#define error_lock() 
#define error_unlock() 

/*=======[E X T E R N A L   D A T A]==========================================*/
extern OSSrvParamType volatile osSrvParam1,osSrvParam2,osSrvParam3;
extern OSServiceIdType volatile osServiceId;

#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120914    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/