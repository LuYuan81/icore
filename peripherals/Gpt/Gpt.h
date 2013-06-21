/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Gpt.h>
 *  @brief      <Abstract API of Gpt Module>
 *  
 *  <Compiler: CodeWarrior V2.8    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/
#ifndef  GPT_H_		
#define  GPT_H_

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
#include "EcuM_Cbk.h"

#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"
/*  Unrecognized #pragma arguments 'section WX ".CFG_DATA"' This #pragma directive has been ignored.
    MISRA-C:2004 Rule 3.4; REFERENCE - ISO:C90-6.8.6 Pragma Directive */

/*=======[M A C R O S]========================================================*/
/* Version Info  */
#define GPT_SW_MAJOR_VERSION	1
#define GPT_SW_MINOR_VERSION   	0
#define GPT_SW_PATCH_VERSION	0

#define GPT_AR_MAJOR_VERSION     2
#define GPT_AR_MINOR_VERSION     2
#define GPT_AR_PATCH_VERSION     2

/** @name Error Codes */
#define GPT_E_UNINIT                        0x0a
#define GPT_E_BUSY 				        	0x0b
#define GPT_E_NOT_STARTED 			        0x0c
#define GPT_E_ALREADY_INITIALIZED           0x0d
#define GPT_E_PARAM_CHANNEL                 0x14
#define GPT_E_PARAM_VALUE 			        0x15
#define GPT_E_PARAM_MODE 			        0x1f
#define GPT_E_PARAM_CONFIG                  0x0e 

/** name Service id's */
#define GPT_INIT_SERVICE_ID                 0x01
#define GPT_DEINIT_SERVICE_ID               0x02
#define GPT_GETTIMEELAPSED_SERVICE_ID      	0x03
#define GPT_GETTIMEREMAINING_SERVICE_ID 	0x04
#define GPT_STARTTIMER_SERVICE_ID           0x05
#define GPT_STOPTIMER_SERVICE_ID            0x06
#define GPT_ENABLENOTIFICATION_SERVICE_ID   0x07
#define GPT_DISABLENOTIFICATION_SERVICE_ID  0x08
#define GPT_SETMODE_SERVIVCE_ID             0x09
#define GPT_DISABLEWAKEUP_SERVICE_ID        0x0a
#define GPT_ENABLEWAKEUP_SERVICE_ID         0x0b
#define GPT_CBK_CHECKWAKEUP_SERVICE_ID      0x0c


/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef uint16 Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

typedef enum
{
	GPT_CHANNEL_CLKSRC_SYS,
    GPT_EXTERNAL_CLOCK,
    GPT_PLL_CLOCK,
	GPT_CHANNEL_CLKSRC_EXT /* NOT SUPPORT */
}Gpt_ChannelClkSrcType;

typedef enum
{
   	GPT_MODE_NORMAL,
    GPT_MODE_SLEEP	
}Gpt_ModeType;

typedef enum 
{
    GPT_MODE_CONTINOUS,
    GPT_MODE_ONESHOT
} GPT_CHANNEL_MODE;


typedef enum
{
  	GPT_UNINITIALIZED,
  	GPT_INITIALIZED
} Gpt_ModuleStateType;

typedef struct 
{	
	uint32 GptChannelClkSrc; /** @req GPT307 */   
	
    Gpt_ChannelType GptChannelId;     /** @req GPT308 */   
    
    GPT_CHANNEL_MODE GptChannelMode;   /** @req GPT309 */    
    
    void (*GptNotification)();  /** @req GPT312 */  
    
    boolean GptEnableWakeup;       /** @req GPT311 */
    P2VAR(EcuM_WakeupSourceType,AUTOMATIC,GPT_APPL_DATA) GptWakeupSourceRef;
}Gpt_ConfigType; /** @req GPT184 @req GPT236 */

typedef enum
{
	GPT_STATE_STOPPED,
  	GPT_STATE_STARTED
} Gpt_StateType;

/* Type that holds all global data for Gpt */
typedef struct
{
  	boolean initRun;	/* Set if Gpt_Init() have been called */ 	
  	P2CONST(Gpt_ConfigType,AUTOMATIC,GPT_APPL_DATA) config; 	
  	boolean wakeupEnabled;
  	uint8 chlSumInRun;  /* sum of channels have been started,in running state */
  	Gpt_ModeType mode;
} Gpt_GlobalType;

/*=======[I N C L U D E S]====================================================*/
#include "Gpt_Mpc5634.h"
#include "Gpt_Cfg.h"

/*=======[E X T E R N A L   D A T A]==========================================*/
extern VAR(Gpt_StateType, GPT_VAR_POWER_ON_INIT) Gpt_Unit[GPT_NUMBER_OF_CHANNELS];
extern VAR(Gpt_GlobalType, GPT_VAR_POWER_ON_INIT) Gpt_Global;
extern VAR(boolean,GPT_VAR_POWER_ON_INIT) Gpt_NotificationSwitch[GPT_NUMBER_OF_CHANNELS];

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/******************************************************************************/
/*
 * Brief               <Initializes the hardware timer module.>
 * ServiceId           <0x01>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <configPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_Init(P2CONST(Gpt_ConfigType,AUTOMATIC,GPT_APPL_DATA)configPtr);

#if (GPT_VERSION_INFO_API == STD_ON)
/******************************************************************************/
/*
 * Brief               <Get the version information of this module.>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <VersioninfoPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC,GPT_APPL_DATA) VersioninfoPtr);
#endif

/******************************************************************************/
/*
 * Brief               <Deinitializes all hardware timer channels.>
 * ServiceId           <0x02>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
#if (GPT_DEINIT_API == STD_ON)
extern FUNC(void,GPT_CODE) Gpt_DeInit(void);
#endif

/******************************************************************************/
/*
 * Brief               <Gets the time already elapsed.>
 * ServiceId           <0x03>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Gpt_ValueType(in number of ticks)>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
#if (GPT_TIME_ELAPSED_API == STD_ON)
extern FUNC(Gpt_ValueType,GPT_CODE) Gpt_GetTimeElapsed(Gpt_ChannelType channel);
#endif

/******************************************************************************/
/*
 * Brief               <Gets the time remaining until the timeout period will expire.>
 * ServiceId           <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Gpt_ValueType(in number of ticks)>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
#if (GPT_TIME_REMAINING_API == STD_ON)
extern FUNC(Gpt_ValueType,GPT_CODE) Gpt_GetTimeRemaining(Gpt_ChannelType channel);
#endif

/******************************************************************************/
/*
 * Brief               <Starts a timer Channel.>
 * ServiceId           <0x05>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel,value>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_StartTimer(Gpt_ChannelType channel,Gpt_ValueType value);

/******************************************************************************/
/*
 * Brief               <Stops a timer Channel.>
 * ServiceId           <0x06>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel,value>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_StopTimer(Gpt_ChannelType channel);

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
/******************************************************************************/
/*
 * Brief               <Enables the notification for a Channel.>
 * ServiceId           <0x07>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_EnableNotification(Gpt_ChannelType channel);

/******************************************************************************/
/*
 * Brief               <Disables the notification for a Channel.>
 * ServiceId           <0x08>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_DisableNotification(Gpt_ChannelType channel);
#endif

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/******************************************************************************/
/*
 * Brief               <Sets the operation mode of the GPT.>
 * ServiceId           <0x09>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_SetMode(Gpt_ModeType mode);
/******************************************************************************/
/*
 * Brief               <Disables the wakeup interrupt invocation of a channel.>
 * ServiceId           <0x0a>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_DisableWakeup(Gpt_ChannelType channel);
/******************************************************************************/
/*
 * Brief               <Enables the wakeup interrupt invocation of a channel.>
 * ServiceId           <0x0b>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_EnableWakeup(Gpt_ChannelType channel);
#endif

#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
/******************************************************************************/
/*
 * Brief               <Callback function to check the valid wakeup event >
 * ServiceId           <0x0c>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <wakeupSource>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <EcuM_CheckWakeup> 
 */
/******************************************************************************/
extern FUNC(void,GPT_CODE) Gpt_Cbk_CheckWakeup(EcuM_WakeupSourceType wakeupSource);
#endif


#endif

/*=======[E N D   O F   F I L E]==============================================*/


