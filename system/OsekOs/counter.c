/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <counter.c>
 *  @brief      <Counter abstract>
 *  
 *  <A counter is represented by a counter value, measured in ”ticks”, and some counter specific 
constants. 
The OSEK operating system does not provide a standardised API to manipulate counters 
directly. 
The OSEK operating system takes care of the necessary actions of managing alarms when a 
counter is advanced and how the counter is advanced. 
The OSEK operating system offers at least one counter that is derived from a (hardware or 
software) timer. >
 *  
 *  @author     <ISOFT>
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
 * @brief               <Init CounterCB>
 * 
 * < > .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <id>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void OSInitCounterCB(CounterType id)
{
	osCounterCB[id].curval = 0;
	osCounterCB[id].lastval = 0;
	osCounterCB[id].almque = INVALID_ALARM_ID;
}

/******************************************************************************/
/**
 * @brief               <The parameter value plus the parameter base>
 * 
 * < > .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <value,base,maxticks>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <TickType>    
 */
/******************************************************************************/
TickType OSAddTicks(TickType value, TickType base, TickType maxticks)
{
	if (base <= (maxticks - value)) 
	{
		return (value + base);
	}
	
	return (value + base - ( maxticks + 1));
}

/******************************************************************************/
/**
 * @brief               <Counter's new ticks subtract old ticks>
 * 
 * < > .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <newvalue,oldvalue,maxticks>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <TickType>    
 */
/******************************************************************************/
TickType OSSubTicks(TickType newvalue, TickType oldvalue , TickType maxticks)
{
	if( newvalue >= oldvalue )
	{
		return (newvalue - oldvalue);
	}
	
	return (newvalue - oldvalue + (maxticks +1));
}

#if (CFG_ALARM_MAX>0)
/******************************************************************************/
/**
 * @brief               <>
 * 
 * < OSWorkAlarm fuction to define if the Alarm should be callback or not> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <CounterID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <None>    
 */
/******************************************************************************/
void OSWorkAlarm(CounterType CounterID)
{
	TickType curval, maxticks,maxallowedvalue;
	boolean done = FALSE;
	AlarmType temp, next;
	
	curval = osCounterCB[CounterID].curval;
	next = osCounterCB[CounterID].almque;
	maxticks = osCounter[CounterID].maxticks;
	maxallowedvalue =  osCounter[CounterID].base.maxallowedvalue;
	
	while ( done == FALSE )
	{
		if(next == INVALID_ALARM_ID)
		{
			done = TRUE;
		}
		else if ( OSSubTicks(curval, osAlarmCB[next].alarmTime, maxticks) <= maxallowedvalue)
		{
			temp = next;
			next = osAlarmCB[next].next;
			osCounterCB[CounterID].almque = next;
			
			if (next != INVALID_ALARM_ID)
			{
				osAlarmCB[next].pre = INVALID_ALARM_ID;
			}
			
			osAlarmCB[temp].pre = temp;
			osAlarmCB[temp].next = temp;			

			osAlarm[temp].callback();
			
			if( osAlarmCB[temp].cycleTime > 0)
			{
				osAlarmCB[temp].alarmTime = OSAddTicks(osAlarmCB[temp].alarmTime, osAlarmCB[temp].cycleTime, maxticks);
				OSInsertAlarm( temp, &osCounterCB[CounterID].almque, osCounterCB[CounterID].lastval);
			}			
		}
		else 
		{
			done = TRUE;
		}		
	}	
}
#endif

/******************************************************************************/
/**
 * @brief               <make counter itself add Ticks and call API OSWorkAlarm()>
 * 
 * < > .
 * Service ID   :       <OSServiceId_IncrementCounter>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <CounterID>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType IncrementCounter(CounterType CounterID)
{
#if (CFG_STATUS == STATUS_EXTENDED)
	if(CounterID >=  CFG_COUNTER_MAX)
	{
		return E_OS_ID;
	}
#endif

	osCounterCB[CounterID].lastval = osCounterCB[CounterID].curval;
	osCounterCB[CounterID].curval = OSAddTicks( osCounterCB[CounterID].curval, 1, osCounter[CounterID].maxticks);

#if (CFG_ALARM_MAX>0)	
	OSWorkAlarm (CounterID);
#endif

	return E_OK;
}

/******************************************************************************/
/**
 * @brief      <Get the value of Counter that mod the Alarm's maxallowedvalue >
 * 
 * < > .
 * Service ID   :       <OSServiceId_GetCounterValue>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <CounterID>
 * @param[out]          <Value>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType GetCounterValue(CounterType CounterID, TickRefType Value)
{
#if (CFG_STATUS == STATUS_EXTENDED)
	if(CounterID >=  CFG_COUNTER_MAX)
	{
		return E_OS_ID;
	}
#endif

	*Value = osCounterCB[CounterID].curval % (osCounter[CounterID].base.maxallowedvalue+1);

	return E_OK;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <Get the value of elapsed ticks which between the curent tick and the tick that 
     pointer Value points> .
 * Service ID   :       <OSServiceId_GetElapsedCounterValue>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <CounterID>
 * @param[out]          <Value,ElapsedValue>
 * @param[in/out]       <None>
 * @return                    <StatusType>    
 */
/******************************************************************************/
StatusType GetElapsedCounterValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue)
{
	TickType curval;
#if (CFG_STATUS == STATUS_EXTENDED)
	if(CounterID >=  CFG_COUNTER_MAX)
	{
		return E_OS_ID;
	}
	
	if(*Value>osCounter[CounterID].base.maxallowedvalue)
	{
		return E_OS_VALUE;
	}
#endif	

	curval = osCounterCB[CounterID].curval;
	*ElapsedValue = (curval + osCounter[CounterID].base.maxallowedvalue - *Value) % osCounter[CounterID].base.maxallowedvalue;
	*Value = curval;
	
	return E_OK;
}

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120914    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/