/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <option.h>
 *  @brief      <>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-19>
 */
/*============================================================================*/

#ifndef _OPTION_H
#define _OPTION_H

/*=======[M A C R O S]========================================================*/
#define SUSPENDED 				0x00u
#define READY 					0x01u	
#define RUNNING 				0x02u	
#define WAITING 				0x03u
#define STATE_START 			0x04u
#define IVALID_ID 				0xFFu 
#define INVALID_TASK 			((TaskType)0xFFu)
#define INVALID_ALARM_ID 		((AlarmType)0xFFu)
#define INVALID_PRIORITY 		((PriorityType)0xFFu )
#define NULL_APPMODE 			((AppModeType)0x00u)
#define TASK_BASIC 				0x00u	
#define TASK_EXTENDED 			0x01u		
#define STATUS_STANDARD 		0x00u
#define STATUS_EXTENDED 		0x01u
#define BCC1   					1
#define BCC2   					2
#define ECC1  					3
#define ECC2   					4
#define PREEMPTIVE_NON 			0
#define PREEMPTIVE_FULL 		1
#define PREEMPTIVE_MIXED 		2
#define LEVEL_TASK 				((CallLevelType)0)
#define LEVEL_ISR 				((CallLevelType)1)
#define LEVEL_ERRORHOOK 		((CallLevelType)2)
#define LEVEL_PRETASKHOOK 		((CallLevelType)3)
#define LEVEL_POSTTASKHOOK 		((CallLevelType)4)
#define LEVEL_STARTUPHOOK 		((CallLevelType)5)
#define LEVEL_SHUTDOWNHOOK 		((CallLevelType)6)
#define TASK_PRIORITY_MAX 		((PriorityType) 64)
#define STACK_FILL_PATTERN 		0xCC

#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/