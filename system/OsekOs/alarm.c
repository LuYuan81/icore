/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <alarm.c>
 *  @brief      <support the function of timing>
 *  
 *  <The OSEK operating system provides services to activate tasks, set events or call an alarm-
callback routine  when an alarm expires. An alarm-callback routine  is a short function 
provided by the application. 
An alarm will expire when a predefined counter value is reached. This counter value can be 
defined relative to the actual counter value (relative alarm) or as an absolute value (absolute 
alarm). For example, alarms may expire upon receipt of a number of timer interrupts, when 
reaching a specific angular position, or when receiving a message. 
Alarms can be defined to be either single alarms or cyclic alarms. In addition the OS provides 
services to cancel alarms and to get the current state of an alarm. 
More than one alarm can be attached to a counter.>
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

#if (CFG_ALARM_MAX>0)
/******************************************************************************/
/**
 * @brief               <Init AlarmCB>
 * 
 * < > .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <AlarmID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void OSInitAlarmCB(AlarmType AlarmID)
{
	CounterType counter;

	osAlarmCB[AlarmID].alarmTime = 0;
	osAlarmCB[AlarmID].cycleTime = 0;
	osAlarmCB[AlarmID].pre = AlarmID;
	osAlarmCB[AlarmID].next = AlarmID;
	
#if (CFG_AUTO_ALARM_MAX>0)
	if( AlarmID < CFG_AUTO_ALARM_MAX)
	{
		if(( osAlarmAutoStart[AlarmID].mask&osActiveAppMode)!=0)
		{
			counter = osAlarm[AlarmID].counter;
			osAlarmCB[AlarmID].alarmTime = osAlarmAutoStart[AlarmID].start;
			osAlarmCB[AlarmID].cycleTime = osAlarmAutoStart[AlarmID].cycle;
			OSInsertAlarm(AlarmID, &osCounterCB[counter].almque, osCounterCB[counter].curval);
		}
	}
#endif
}

/******************************************************************************/
/**
 * @brief               <Insert alarm into the corresponding counter queue by ascending order>
 * 
 * < > .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <alarmid,almque,curTick>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void OSInsertAlarm(AlarmType alarmid, AlarmRefType almque, TickType curTick )
{
	TickType alarmTick;
	AlarmType pre, next;
	boolean done = FALSE;
	
	if(alarmid >=  CFG_ALARM_MAX)
	{
		return;
	}

	alarmTick = osAlarmCB[alarmid].alarmTime;
	pre =  INVALID_ALARM_ID;
	next = *almque;
	if(curTick < alarmTick)
	{
		while ( done != TRUE ) 
		{
			if( next == INVALID_ALARM_ID) 
			{
				done = TRUE;
			}
			else if(( osAlarmCB[next].alarmTime >= curTick) && ( osAlarmCB[next].alarmTime <= alarmTick ))
			{
				pre = next;
				next = osAlarmCB[next].next;
			}
			else 
			{
				done = TRUE;
			}
		}
	}
	else
	{
		while ( done != TRUE ) 
		{
			if( next == INVALID_ALARM_ID) 
			{
				done = TRUE;
			}
			else if(( osAlarmCB[next].alarmTime >= curTick) || ( osAlarmCB[next].alarmTime <= alarmTick ))
			{
				pre = next;
				next = osAlarmCB[next].next;
			}
			else 
			{
				done = TRUE;
			}
		}
	}
	
	osAlarmCB[alarmid].pre  =  pre;
	osAlarmCB[alarmid].next  =  next;
	if(pre != INVALID_ALARM_ID) 
	{
		osAlarmCB[pre].next = alarmid;
	}
	else
	{
		*almque = alarmid;
	}
	
	if(next != INVALID_ALARM_ID)
	{
		osAlarmCB[next].pre = alarmid;
	}
	
	return;		
}

/******************************************************************************/
/**
 * @brief               <Delete alarm from it's original queue>
 * 
 * < > .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <alarmid,almque>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void OSDeleteAlarm(AlarmType alarmid, AlarmRefType almque)
{
	AlarmType pre,next;

	if(alarmid >=  CFG_ALARM_MAX)
	{
		return;
	}

	pre = osAlarmCB[alarmid].pre;
	next = osAlarmCB[alarmid].next;

	if(pre != INVALID_ALARM_ID )
	{
		osAlarmCB[pre].next = next;
	}
	else 
	{
		*almque = next;
	}
	
	if(next != INVALID_ALARM_ID)
	{
		osAlarmCB[next].pre = pre;
	}
	
	osAlarmCB[alarmid].pre = alarmid;
	osAlarmCB[alarmid].next = alarmid;
	
	return;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * < The system service GetAlarm returns the relative value in ticks 
    before the alarm <AlarmID> expires. > .
 * Service ID   :       <OSServiceId_GetAlarm>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <AlarmID>
 * @param[out]          <Tick>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType GetAlarm(AlarmType AlarmID, TickRefType Tick)
{
#if (CFG_STATUS==STATUS_EXTENDED)
	if ( AlarmID>= CFG_ALARM_MAX )
	{
		Call_ErrorHook(OSError_Save_GetAlarm(AlarmID,Tick), OSServiceId_GetAlarm, E_OS_ID);
		return E_OS_ID;
	}
#endif

	if ( osAlarmCB[AlarmID].next == AlarmID)
	{
		Call_ErrorHook(OSError_Save_GetAlarm(AlarmID,Tick), OSServiceId_GetAlarm, E_OS_NOFUNC);
		return E_OS_NOFUNC;
	}

	*Tick = OSSubTicks(osAlarmCB[AlarmID].alarmTime, osCounterCB[osAlarm[AlarmID].counter].curval, 
	            osCounter[osAlarm[AlarmID].counter].maxticks);
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <Get information about alarm>
 * 
 * < The system service  GetAlarmBase  reads the alarm base 
    characteristics. The return value <Info> is a structure in which 
    the information of data type AlarmBaseType is stored. > .
 * Service ID   :       <OSServiceId_GetAlarmBase>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <AlarmID>
 * @param[out]          <Info>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info)
{
	CounterType counter;

#if (CFG_STATUS==STATUS_EXTENDED)
	if ( AlarmID>= CFG_ALARM_MAX )
	{
		Call_ErrorHook(OSError_Save_GetAlarmBase(AlarmID,Info), OSServiceId_GetAlarmBase, E_OS_ID);
		return E_OS_ID;
	}
#endif

	counter = osAlarm[AlarmID].counter;
	Info->maxallowedvalue = osCounter[counter].base.maxallowedvalue;
	Info->mincycle  = osCounter[counter].base.mincycle;
	Info->ticksperbase = osCounter[counter].base.ticksperbase;
	
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <Cancel the specified alarm>
 * 
 * <The system service cancels the alarm <AlarmID>.  > .
 * Service ID   :       <OSServiceId_CancelAlarm>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <AlarmID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType CancelAlarm(AlarmType AlarmID)
{

#if (CFG_STATUS==STATUS_EXTENDED)
	if ( AlarmID>= CFG_ALARM_MAX )
	{
		Call_ErrorHook(OSError_Save_CancelAlarm(AlarmID), OSServiceId_CancelAlarm, E_OS_ID);
		return E_OS_ID;
	}
#endif

	if ( osAlarmCB[AlarmID].next == AlarmID)
	{
		Call_ErrorHook(OSError_Save_CancelAlarm(AlarmID), OSServiceId_CancelAlarm, E_OS_NOFUNC);
		return E_OS_NOFUNC;
	}

	OSDeleteAlarm(AlarmID, &osCounterCB[osAlarm[AlarmID].counter].almque);
	
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <Set alarm's relative trigger time>
 * 
 * <The system service occupies the alarm <AlarmID> element. 
    After <increment> ticks have elapsed, the task assigned to the 
    alarm <AlarmID> is activated or the assigned event (only for 
    extended tasks) is set or the alarm-callback routine is called.  > .
 * Service ID   :       <OSServiceId_SetRelAlarm>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <AlarmID,increment,cycle>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType SetRelAlarm(AlarmType AlarmID, TickType increment,TickType cycle) 
{

#if (CFG_STATUS==STATUS_EXTENDED)
	if ( AlarmID>= CFG_ALARM_MAX )
	{
		Call_ErrorHook(OSError_Save_SetRelAlarm(AlarmID,increment,cycle), OSServiceId_SetRelAlarm, E_OS_ID);
		return E_OS_ID;
	}
	
	if( (increment<=0) || (increment>osCounter[osAlarm[AlarmID].counter].base.maxallowedvalue))
	{
		Call_ErrorHook(OSError_Save_SetRelAlarm(AlarmID,increment,cycle), OSServiceId_SetRelAlarm, E_OS_VALUE);
		return E_OS_VALUE;
	}
	
	if((cycle!=0)&&((cycle > osCounter[osAlarm[AlarmID].counter].base.maxallowedvalue)||(cycle < osCounter[osAlarm[AlarmID].counter].base.mincycle)))
	{
		Call_ErrorHook(OSError_Save_SetRelAlarm(AlarmID,increment,cycle), OSServiceId_SetRelAlarm, E_OS_VALUE);
		return E_OS_VALUE;
	}
#endif		

	if ( osAlarmCB[AlarmID].next != AlarmID)
	{
		Call_ErrorHook(OSError_Save_SetRelAlarm(AlarmID,increment,cycle), OSServiceId_SetRelAlarm, E_OS_STATE);
		return E_OS_STATE;
	}
	
	SuspendAllInterrupts();
	osAlarmCB[AlarmID].alarmTime = OSAddTicks(increment,  osCounterCB[osAlarm[AlarmID].counter].curval ,osCounter[osAlarm[AlarmID].counter].maxticks);
	osAlarmCB[AlarmID].cycleTime = cycle;
	OSInsertAlarm(AlarmID,  &osCounterCB[osAlarm[AlarmID].counter].almque,osCounterCB[osAlarm[AlarmID].counter].curval);
	ResumeAllInterrupts();
	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <Set alarm's absolute trigger time>
 * 
 * < The system service occupies the alarm <AlarmID> element. 
    When <start> ticks are reached, the task assigned to the alarm
    <AlarmID> is activated or the assigned event (only for extended 
    tasks) is set or the alarm-callback routine is called. > .
 * Service ID   :       <OSServiceId_SetAbsAlarm>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <AlarmID,start,cycle>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle)
{

#if (CFG_STATUS==STATUS_EXTENDED)
	if ( AlarmID>= CFG_ALARM_MAX )
	{
		Call_ErrorHook(OSError_Save_SetAbsAlarm(AlarmID,start,cycle), OSServiceId_SetAbsAlarm, E_OS_ID);
		return E_OS_ID;
	}
	
	if( (start<=0) || (start >osCounter[osAlarm[AlarmID].counter].base.maxallowedvalue))
	{
		Call_ErrorHook(OSError_Save_SetAbsAlarm(AlarmID,start,cycle), OSServiceId_SetAbsAlarm, E_OS_VALUE);
		return E_OS_VALUE;
	}
	
	if((cycle!=0)&&((cycle > osCounter[osAlarm[AlarmID].counter].base.maxallowedvalue)||(cycle < osCounter[osAlarm[AlarmID].counter].base.mincycle)))
	{
		Call_ErrorHook(OSError_Save_SetAbsAlarm(AlarmID,start,cycle), OSServiceId_SetAbsAlarm, E_OS_VALUE);
		return E_OS_VALUE;
	}
#endif
		
	if ( osAlarmCB[AlarmID].next != AlarmID)
	{
		Call_ErrorHook(OSError_Save_SetAbsAlarm(AlarmID,start,cycle), OSServiceId_SetAbsAlarm, E_OS_STATE);
		return E_OS_STATE;
	}
	
	SuspendAllInterrupts();
	
	if( OSSubTicks(start, osCounterCB[osAlarm[AlarmID].counter].curval, osCounter[osAlarm[AlarmID].counter].maxticks) <=  osCounter[osAlarm[AlarmID].counter].base.maxallowedvalue)
	{
		osAlarmCB[AlarmID].alarmTime = start ;
	}
	else 
	{
		osAlarmCB[AlarmID].alarmTime = start + osCounter[osAlarm[AlarmID].counter].base.maxallowedvalue +1;
	}
	
	osAlarmCB[AlarmID].cycleTime = cycle;
	OSInsertAlarm(AlarmID,  &osCounterCB[osAlarm[AlarmID].counter].almque,osCounterCB[osAlarm[AlarmID].counter].curval);
	ResumeAllInterrupts();
	
	return E_OK;
}

#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120914    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/