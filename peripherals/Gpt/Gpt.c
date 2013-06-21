/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Gpt.c>
 *  @brief      <Abstract API of Gpt Module>
 *  
 *  <Compiler: CodeWarrior V2.8    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20120410  i-soft       Initial version
 */
/*============================================================================*/

/* MISRA-C:2004 Rule 17.4: 
 * Array subscripting applied to an object of pointer type. 
 */
/* MISRA-C:2004 Rule 19.1: 
 * #include statements in a file should only be preceded by other preprocessor directives or comments. 
 */

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define GPT_C_VENDOR_ID            0
#define GPT_C_MODULE_ID            100

#define GPT_C_AR_MAJOR_VERSION     2
#define GPT_C_AR_MINOR_VERSION     2
#define GPT_C_AR_PATCH_VERSION     2

#define GPT_C_SW_MAJOR_VERSION     1
#define GPT_C_SW_MINOR_VERSION     0
#define GPT_C_SW_PATCH_VERSION     0

#define GPT_C_VENDOR_API_INFIX     0

/*=======[I N C L U D E S]====================================================*/
#include "Gpt.h"
#include "Det.h"

/*=======[V E R S I O N  C H E C K]===========================================*/
#if((GPT_C_AR_MAJOR_VERSION != GPT_AR_MAJOR_VERSION)      \
    ||(GPT_C_AR_MINOR_VERSION != GPT_AR_MINOR_VERSION)    \
    ||(GPT_C_AR_PATCH_VERSION != GPT_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Gpt.c and Gpt.h are different"
#endif

#if((GPT_C_AR_MAJOR_VERSION != GPT_AR_MAJOR_VERSION)      \
    ||(GPT_C_AR_MINOR_VERSION != GPT_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of Gpt.c and Gpt.h are different"
#endif

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*Dependencies to other modules*/
/** @req GPT171 */
/** @req GPT259 */
/** @req GPT293 */
/** @req GPT262 */

/*Functional  specification*/
/** @req GPT127 */
/** @req GPT256 */
/** @req GPT174 */
/** @req GPT001 */
/** @req GPT004 */
/** @req GPT175 */
/** @req GPT176 */
/** @req GPT177 */
/** @req GPT204 */
/** @req GPT055 */

/*=======[E X T E R N A L   D A T A]==========================================*/
VAR(Gpt_StateType, GPT_VAR_POWER_ON_INIT) Gpt_Unit[GPT_NUMBER_OF_CHANNELS]=
{
	GPT_STATE_STOPPED,
	GPT_STATE_STOPPED,
	GPT_STATE_STOPPED,
	GPT_STATE_STOPPED,
	GPT_STATE_STOPPED
};

VAR(Gpt_GlobalType, GPT_VAR_POWER_ON_INIT) Gpt_Global=
{
	FALSE,                      /* initRun */
	NULL,                       /* config */
	FALSE,                      /* wakeupEnabled */
	0u,                         /* chlSumInRun */
	GPT_MODE_NORMAL             /* mode */
};

VAR(boolean,GPT_VAR_POWER_ON_INIT) Gpt_NotificationSwitch[GPT_NUMBER_OF_CHANNELS]=
{
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE
};

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/
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
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_Init(P2CONST(Gpt_ConfigType,AUTOMATIC,GPT_APPL_DATA)configPtr)
{
	/** @req GPT280 */ 
	/** @req GPT006 */
	/** @req GPT068 */
	/** @req GPT205 */
	/** @req GPT309 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT307 */
	if(TRUE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_INIT_SERVICE_ID,GPT_E_ALREADY_INITIALIZED);
		return;
	}
			   
	/** @req GPT294 */		   
	if(NULL == configPtr)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_INIT_SERVICE_ID,GPT_E_PARAM_CONFIG);
		return;
	}
#endif /* GPT_DEV_ERROR_DETECT */
		
	Gpt_Global.config = configPtr;
	Gpt_Mpc5634Init();
	Gpt_Global.wakeupEnabled = FALSE;
  	Gpt_Global.mode = GPT_MODE_NORMAL; 
	Gpt_Global.initRun = TRUE;
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

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
#if (GPT_DEINIT_API == STD_ON) /** @req GPT194 */
#define GPT_START_SEC_CODE
#include "MemMap.h"
/* void Gpt_DeInit(void) */
FUNC(void,GPT_CODE) Gpt_DeInit(void)
{
   	/** @req GPT281 */
  	/** @req GPT161 */
	/** @req GPT105 */
	/** @req GPT162 */
	/** @req GPT308 */
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT220 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_DEINIT_SERVICE_ID,GPT_E_UNINIT);
		return;
	}

	/** @req GPT234 */
	if(0u != Gpt_Global.chlSumInRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_DEINIT_SERVICE_ID,GPT_E_BUSY);
		return;
	}
    #endif /* GPT_DEV_ERROR_DETECT */		
   
    Gpt_Mpc5634DeInit();	
    Gpt_Global.chlSumInRun=0;    	
   	Gpt_Global.initRun = FALSE; 
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"
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
#if GPT_TIME_ELAPSED_API == STD_ON /** @req GPT195 */
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(Gpt_ValueType,GPT_CODE) Gpt_GetTimeElapsed(Gpt_ChannelType channel)
{	
	/** @req GPT282 */
	/** @req GPT010 */
	/** @req GPT113 */
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT222 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_GETTIMEELAPSED_SERVICE_ID,GPT_E_UNINIT);
		return 0;
	}

	/** @req GPT210 */				
    if((GPT_NUMBER_OF_CHANNELS <= channel)	
       ||(Gpt_Global.config[channel].GptChannelId == GPT_UNCONFIGURED))
    {
    	Det_ReportError(MODULE_ID_GPT,0,GPT_GETTIMEELAPSED_SERVICE_ID,GPT_E_PARAM_CHANNEL);
		return 0;
    } 
					
	/** @req GPT295 @req GPT296 @req GPT297 @req GPT298*/				
	if(GPT_STATE_STARTED != Gpt_Unit[channel])
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_GETTIMEELAPSED_SERVICE_ID,GPT_E_NOT_STARTED);
		return 0;
	}				                                                        
    #endif /* GPT_DEV_ERROR_DETECT */		

	return Gpt_Mpc5634GetTimeElapsed(channel);
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"
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
#if GPT_TIME_REMAINING_API == STD_ON /** @req GPT196 */
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(Gpt_ValueType,GPT_CODE) Gpt_GetTimeRemaining(Gpt_ChannelType channel)
{
	/** @req GPT283 */
	/** @req GPT114 */
	
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT223 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_GETTIMEREMAINING_SERVICE_ID,GPT_E_UNINIT);
		return 0;
	}

    /** @req GPT211 */		
    if((GPT_NUMBER_OF_CHANNELS <= channel) || (GPT_UNCONFIGURED == Gpt_Global.config[channel].GptChannelId))
    {
    	Det_ReportError(MODULE_ID_GPT,0,GPT_GETTIMEREMAINING_SERVICE_ID,GPT_E_PARAM_CHANNEL);
		return 0;
    } 
				
	/** @req GPT301 @req GPT302 @req GPT303 @req GPT304*/					
	if(GPT_STATE_STARTED != Gpt_Unit[channel])
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_GETTIMEREMAINING_SERVICE_ID,GPT_E_NOT_STARTED);
		return 0;
	}				                                                     
    #endif /* GPT_DEV_ERROR_DETECT */
	
	return Gpt_Mpc5634GetTimeRemaining(channel);/** @req GPT083  @req GPT305*/
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"
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
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_StartTimer(Gpt_ChannelType channel,Gpt_ValueType value)
{	
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT284 */
	/** @req GPT115 */
	/** @req GPT224 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_STARTTIMER_SERVICE_ID,GPT_E_UNINIT);
		return;
	}

	/** @req GPT212 */				
    if((GPT_NUMBER_OF_CHANNELS <= channel) || (GPT_UNCONFIGURED == Gpt_Global.config[channel].GptChannelId))	
    {
    	Det_ReportError(MODULE_ID_GPT,0,GPT_STARTTIMER_SERVICE_ID,GPT_E_PARAM_CHANNEL);
		return;
    } 
    					
	/** GPT084 */				
	if(GPT_STATE_STARTED == Gpt_Unit[channel])
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_STARTTIMER_SERVICE_ID,GPT_E_BUSY);
		return;
	}
	/** @req GPT218 */ 
	if(0u == value)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_STARTTIMER_SERVICE_ID,GPT_E_PARAM_VALUE);
		return;
	}					                                                        
    #endif /* GPT_DEV_ERROR_DETECT */
		
	/** @req GPT274 */
	Gpt_Mpc5634StartTimer(channel,value);
    Gpt_Global.chlSumInRun |= (1u<<channel);
  	
	Gpt_Unit[channel] = GPT_STATE_STARTED;
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

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
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_StopTimer(Gpt_ChannelType channel)
{
	/** @req GPT285 */
 	/** @req GPT099 */
 	/** @req GPT103 */
 	/** @req GPT116 */ 
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT225 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_STOPTIMER_SERVICE_ID,GPT_E_UNINIT);
		return;
	}

	/** @req GPT213 */				
    if((GPT_NUMBER_OF_CHANNELS <= channel) || (GPT_UNCONFIGURED == Gpt_Global.config[channel].GptChannelId))
    {
    	Det_ReportError(MODULE_ID_GPT,0,GPT_STOPTIMER_SERVICE_ID,GPT_E_PARAM_CHANNEL);
		return;
    }    					                   
    #endif /* GPT_DEV_ERROR_DETECT */ 
 
    Gpt_Mpc5634StopTimer(channel);
    Gpt_Global.chlSumInRun &= ~(1u<<channel);
	Gpt_Unit[channel] = GPT_STATE_STOPPED;
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

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
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /** @req GPT199 */
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_EnableNotification(Gpt_ChannelType channel)
{
	/** @req GPT286 */
	/** @req GPT014 */
	/** @req GPT117 */
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT226 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_ENABLENOTIFICATION_SERVICE_ID,GPT_E_UNINIT);
		return;
	}

	/** @req GPT214 */				
    if((GPT_NUMBER_OF_CHANNELS <= channel) || (GPT_UNCONFIGURED == Gpt_Global.config[channel].GptChannelId))	
    {
    	Det_ReportError(MODULE_ID_GPT,0,GPT_ENABLENOTIFICATION_SERVICE_ID,GPT_E_PARAM_CHANNEL);
		return;
    }    					                   
    #endif /* GPT_DEV_ERROR_DETECT */ 

	Gpt_NotificationSwitch[channel] = TRUE;
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"
#endif

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
#if GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON /** @req GPT200 */
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_DisableNotification(Gpt_ChannelType channel)
{	
	/** @req GPT287 */
	/** @req GPT015 */
	/** @req GPT118 */
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT227 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_DISABLENOTIFICATION_SERVICE_ID,GPT_E_UNINIT);
		return;
	}
	/** @req GPT217 */				
    if((GPT_NUMBER_OF_CHANNELS <= channel) || (GPT_UNCONFIGURED == Gpt_Global.config[channel].GptChannelId))	
    {
    	Det_ReportError(MODULE_ID_GPT,0,GPT_DISABLENOTIFICATION_SERVICE_ID,GPT_E_PARAM_CHANNEL);
		return;
    }    					                   
    #endif /* GPT_DEV_ERROR_DETECT */ 
	
	Gpt_NotificationSwitch[channel] = FALSE;
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"
#endif

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
/** @req GPT201  @req GPT202 @req GPT203 */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON) 
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_SetMode(Gpt_ModeType mode)
{	
    Gpt_ChannelType i;
	/** @req GPT288 */
	/** @req GPT255 */
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT228 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_SETMODE_SERVIVCE_ID,GPT_E_UNINIT);
		return;
	}			   

    /** @req GPT231 */
	if(GPT_MODE_SLEEP < mode)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_SETMODE_SERVIVCE_ID,GPT_E_PARAM_MODE);
		return;
	}
    #endif /* GPT_DEV_ERROR_DETECT */ 	
	
	if (GPT_MODE_SLEEP == mode) 
	{
		/** @req GPT153 */
		/** @req GPT164 */
		/** @req GPT341 */
        for (i = 0; i < (GPT_NUMBER_OF_CHANNELS - 1); i++)
        {
            if(Gpt_Global.config[i].GptChannelId == i) /* has been configured */
            {
                Gpt_Mpc5634StopTimer(i);
            }
        }

        if(Gpt_Global.wakeupEnabled != TRUE)
   		{
            if(Gpt_Global.config[i].GptChannelId == i) /* has been configured */
            {
                Gpt_Mpc5634StopTimer(GPT_CHANNEL_RTI);
            }
    	}
    	else
    	{
    		/* as by default Gpt_StartTimer() will start the timer and also
    		 * enable the interrupt.so has no need to enable it again.*/
    	}
	}
	else
	{
		/** @req GPT165 */
		/** @req GPT152 */
		/* do nothing */
	}

	Gpt_Global.mode = mode;
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

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
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_DisableWakeup(Gpt_ChannelType channel)
{	
	/** @req GPT289 */
	/** @req GPT157 */
	/** @req GPT155 */
	/** @req GPT229 */
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT229 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_DISABLEWAKEUP_SERVICE_ID,GPT_E_UNINIT);
		return;
	}

	/** @req GPT215 */				
    if((GPT_NUMBER_OF_CHANNELS <= channel)
       ||(GPT_UNCONFIGURED == Gpt_Global.config[channel].GptChannelId)
       ||(FALSE == Gpt_Global.config[channel].GptEnableWakeup))
    {
    	Det_ReportError(MODULE_ID_GPT,0,GPT_DISABLEWAKEUP_SERVICE_ID,GPT_E_PARAM_CHANNEL);
		return;
    }    					                   
    #endif /* GPT_DEV_ERROR_DETECT */ 
  	
  	if (GPT_CHANNEL_RTI == channel)		/* Only RTI have system wakeup */
  	{
    	Gpt_Global.wakeupEnabled = FALSE; /** @req GPT159 */
  	}
  	else
  	{
    	/* do nothing */
  	}
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

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
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_EnableWakeup(Gpt_ChannelType channel)
{	
	/** @req GPT290 */
	/** @req GPT158 */
	/** @req GPT156 */
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	/** @req GPT230 */
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_ENABLEWAKEUP_SERVICE_ID,GPT_E_UNINIT);
		return;
	}

	/** @req GPT216 */				
    if((GPT_NUMBER_OF_CHANNELS <= channel)
       ||(GPT_UNCONFIGURED == Gpt_Global.config[channel].GptChannelId)
       ||(FALSE == Gpt_Global.config[channel].GptEnableWakeup))	
    {
    	Det_ReportError(MODULE_ID_GPT,0,GPT_ENABLEWAKEUP_SERVICE_ID,GPT_E_PARAM_CHANNEL);
		return;
    }    					                   
#endif /* GPT_DEV_ERROR_DETECT */  	

  	if (GPT_CHANNEL_RTI == channel) /** @req GPT160 */
  	{
    	Gpt_Global.wakeupEnabled = TRUE;
  	}
  	else
  	{
    	/* do nothing */
  	}
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"

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
#if (GPT_REPORT_WAKEUP_SOURCE == STD_ON)
#define GPT_START_SEC_CODE
#include "MemMap.h"
FUNC(void,GPT_CODE) Gpt_Cbk_CheckWakeup(EcuM_WakeupSourceType wakeupSource)
{
    #if (GPT_DEV_ERROR_DETECT == STD_ON)	
	if(FALSE == Gpt_Global.initRun)
	{
		Det_ReportError(MODULE_ID_GPT,0,GPT_CBK_CHECKWAKEUP_SERVICE_ID,GPT_E_UNINIT);
		return;
	}  					                   
    #endif /* GPT_DEV_ERROR_DETECT */	

	if((*Gpt_Global.config[GPT_CHANNEL_RTI].GptWakeupSourceRef) == wakeupSource)
    {
    	(void)EcuM_SetWakeupEvent(wakeupSource);
	}
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h"
#endif

#endif

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
#if (GPT_VERSION_INFO_API == STD_ON) 
#define GPT_START_SEC_CODE
#include "MemMap.h" 
FUNC(void,GPT_CODE) Gpt_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC,GPT_APPL_DATA) VersioninfoPtr)
{	
    VersioninfoPtr->vendorID = 0;
    VersioninfoPtr->moduleID = MODULE_ID_GPT;
    VersioninfoPtr->instanceID = 1;
    VersioninfoPtr->ar_major_version = GPT_AR_MAJOR_VERSION;
    VersioninfoPtr->ar_minor_version = GPT_AR_MINOR_VERSION;
    VersioninfoPtr->ar_patch_version = GPT_AR_PATCH_VERSION;
    VersioninfoPtr->sw_major_version = GPT_SW_MAJOR_VERSION;
    VersioninfoPtr->sw_minor_version = GPT_SW_MINOR_VERSION;
    VersioninfoPtr->sw_patch_version = GPT_SW_PATCH_VERSION;
}
#define GPT_STOP_SEC_CODE
#include "MemMap.h" 
#endif

/*=======[E N D   O F   F I L E]==============================================*/

