/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <structs.h>
 *  @brief      <>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-14>
 */
/*============================================================================*/
#ifndef _STRUCTS_H
#define _STRUCTS_H

/*=======[I N C L U D E S]====================================================*/
#include "config.h"
#include "Std_Types.h"

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef void (* TaskEntry)(void);

typedef struct 
{
	uint8 head;
	uint8 tail;
} Queue;

typedef struct
{
	StackPtrType top;
	StackPtrType bottom;
} StackType;

typedef struct
{
	TaskEntry entry;	
	uint8 id;				
	PriorityType initPrio;		
	uint8 maxAct;			
	uint8 stackid;	
} TaskInfo;

typedef struct
{
	StackPtrType sp;			
	StackPtrType stackBottom;    
	uint8 state;			
	uint8 runPrio;			
#if ((CFG_CC == BCC2) || (CFG_CC == ECC2))
	uint8 actCount;		
#endif
	uint8 resCount;		
} TCB;

typedef struct
{
	PriorityType ceiling;
}ResourceInfo;

typedef struct
{
	uint8 saveCount;
	PriorityType savePrio;
}ResourceCB;

typedef struct 
{
	AlarmBaseType base;
	TickType maxticks;
} CounterInfo;

typedef struct 
{
	TickType curval;
	TickType lastval;
	AlarmType almque;
} CounterCB;

typedef enum 
{
	ALARM_SETEVENT,
	ALARM_ACTIVATETASK,
	ALARM_CALLBACK  
} AlarmActionType;

typedef struct 
{
	CounterType counter;
	AlarmCallbackType callback;
} AlarmInfo;

typedef struct 
{
	TickType alarmTime;               
	TickType cycleTime;              
	AlarmType pre;
	AlarmType next;
} AlarmCB;

typedef struct 
{
	AppModeType mask;
	TickType start;
	TickType cycle;
} AlarmAutostartType;

typedef union 
{
	TaskType	 	taskid;
	TaskRefType			taskref;
	TaskStateRefType	stateref;
	ResourceType		resourceid;
	EventMaskType		eventmask;
	EventMaskRefType	eventref;
	AlarmType			alarmid;
	AlarmBaseRefType	baseref;
	TickRefType			tickref;
	TickType			tick;
	AppModeType			mode;
	CounterType			counterid;
} OSSrvParamType;

#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/