/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <filename>
 *  @brief      <Briefly describe file(one line)>
 *  
 *  <Compiler: XXX    MCU:XXX>
 *  
 *  @author     <author name>
 *  @date       <dd-mm-yyyy>
 */
/*============================================================================*/
#ifndef ICU_H
#define ICU_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20081127  James       Initial version
 * 
 *  V1.1.0       20091012  Michael     As per ADC171, ADC_E_NO_DB is changed
 *                                     to ADC_E_INVALID_DATABASE.
 * 
 *  V2.0.0       20100210  Z.YX        As per SCR 186, Adc_Init and Adc_DeInit
 *                                     are updated to use IMRm register instead
 *                                     of xxICn register.
 */
/*============================================================================*/

/*=======[M I S R A  R U L E  V I O L A T I O N]==============================*/
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
#include "Icu_Cfg.h"

#if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
#include "EcuM_Cbk.h"
#endif /* STD_ON == ICU_REPORT_WAKEUP_SOURCE */

/* MISRA-C:2004 Rule 3.4; REFERENCE - ISO:C90-6.8.6 Pragma Directive */
#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define ICU_VENDOR_ID             0
#define ICU_MODULE_ID           122
#define ICU_VENDOR_API_INFIX      0
/* AUTOSAR specification version information */
#define ICU_H_AR_MAJOR_VERSION    3
#define ICU_H_AR_MINOR_VERSION    0
#define ICU_H_AR_PATCH_VERSION    2
/* File version information */
#define ICU_H_SW_MAJOR_VERSION    1
#define ICU_H_SW_MINOR_VERSION    0
#define ICU_H_SW_PATCH_VERSION    0

/*=======[M A C R O S]========================================================*/
#define CHANNEL_NUMBER         24

/* Service Id of Adc_Init */
#define ICU_INIT_ID                 	0x00
#define ICU_DEINIT_ID               	0x01
#define ICU_SETMODE_ID              	0x02
#define ICU_DISABLE_WAKEUP_ID       	0x03
#define ICU_ENABLE_WAKEUP_ID        	0x04
#define ICU_SET_ACTIVATION_CONDITION_ID 0x05
#define ICU_DISABLE_NOTIFICATION_ID     0x06
#define ICU_ENABLE_NOTIFICATION_ID      0x07
#define ICU_GET_INPUTSTATE_ID           0x08
#define ICU_START_TIMESTAMP_ID          0x09
#define	ICU_STOP_TIMESTAMP_ID           0x0A
#define ICU_GET_TIMESTAMP_INDEX_ID      0x0B
#define ICU_RESET_EDGE_COUNT_ID         0x0C
#define ICU_ENABLE_EDGE_COUNT_ID        0x0D
#define ICU_DISABLE_EDGE_COUNT_ID       0x0E
#define ICU_GET_EDGE_NUMBERS_ID         0x0F
#define ICU_START_SIGNAL_MEASUREMENT_ID 0x13
#define ICU_STOP_SIGNAL_MEASUREMENT_ID  0x14
#define	ICU_GET_TIME_ELAPED_ID          0x10
#define	ICU_GET_DUTYCYCLE_VALUES_ID     0x11
#define	ICU_GET_VERSION_INFO_ID         0x12

/* Det Error Codes */
/* API Icu_Init service called with wrong parameter */
#define ICU_E_PARAM_CONFIG              0x0A
/*
 * API service used with an invalid channel identifier or channel
 * was not configured for the functionality of the calling API
 */
#define	ICU_E_PARAM_CHANNEL             0x0B
/* API service used with an invalid or not feasible activation */
#define	ICU_E_PARAM_ACTIVATION          0x0C
/* API service used with an invalid application-buffer pointer */
#define	ICU_E_PARAM_BUFFER_PTR          0x0D
/* API service used with an invalid buffer size */
#define	ICU_E_PARAM_BUFFER_SIZE         0x0E
/* API service Icu_SetMode used with an invalid mode */
#define	ICU_E_PARAM_MODE              	0x0F
/* API service used without module initialization */
#define	ICU_E_UNINIT        		    0x14
/*
 * API service Icu_Stop Timestamp called on a channel
 * which was not started or already stopped
 */
#define	ICU_E_NOT_STARTED        		0x15
/* API service Icu_SetMode is called while a running operation */
#define	ICU_E_BUSY_OPERATION            0x16
/*
 * API Icu_Init service called when the ICU driver
 * and the Hardware are already initialized
 */
#define	ICU_E_ALREADY_INITIALIZED       0x17

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/* Allow enabling/disabling of all interrupts which are not required for the ECU wakeup */
typedef enum
{
	ICU_MODE_NORMAL,
	ICU_MODE_SLEEP

}Icu_ModeType;

/* Numeric identifier of an ICU channel */
typedef uint16  Icu_ChannelType;

/* Input state of an ICU channel */
typedef enum
{
	ICU_IDLE = ZERO,
	ICU_ACTIVE

}Icu_InputStateType;

/* Definition of the type of activation of an ICU channel */
typedef enum
{
	ICU_FALLING_EDGE = ZERO,
	ICU_RISING_EDGE = ONE,
	ICU_BOTH_EDGE = TWO

}Icu_ActivationType;

/* Width of the buffer for timestamp ticks and measured elapsed timeticks */
typedef uint32 Icu_ValueType;

/* Type which shall contain the values, needed for calculating duty cycles */
typedef struct
{
	Icu_ValueType ActiveTime;
	Icu_ValueType PeriodTime;	

}Icu_DutyCycleType;

/* Type to abstract the return value of the service Icu_GetTimestampIndex() */
typedef uint32 Icu_IndexType;

/* Type to abstract the return value of the service Icu_GetEdgeNumbers() */
typedef uint32 Icu_EdgeNumberType;

/* Definition of the measurement mode type */
typedef enum
{
	ICU_MODE_SIGNAL_EDGE_DETECT,
	ICU_MODE_SIGNAL_MEASUREMENT,
	ICU_MODE_TIMESTAMP,
	ICU_MODE_EDGE_COUNTER

} Icu_MeasurementModeType;

/* Definition of the measurement property type */
typedef enum
{
	ICU_LOW_TIME,
	ICU_HIGH_TIME,
	ICU_PERIOD_TIME,
	ICU_DUTY_CYCLE

} Icu_SignalMeasurementPropertyType;

/* Definition of the timestamp measurement property type */
typedef enum
{
	ICU_LINEAR_BUFFER,
	ICU_CIRCULAR_BUFFER

} Icu_TimestampBufferType;

/* Configuration in case the easurement mode is "IcuEdgeCounter" */
typedef struct 
{   
	uint32 i;			

}Icu_EdgeCounterMeasurementType;

/* Configuration in case the measurement mode is "IcuSignalEdgeDetection" */
typedef struct
{
    /* Notificationi function for signal notification */
	void (*IcuSignalNotification)(void);

}Icu_SignalEdgeDetectionType;

/* Configuration in case the measurement mode is "IcuSignalMeasurement" */
typedef struct
{
    /* Configures the property that could be measured in case the mode is "IcuSignalMeasurement" */
	Icu_SignalMeasurementPropertyType  IcuSignalMeasurementProperty;

}Icu_SignalMeasurementType;

/* Configuration in case the measurement mode is "IcuTimestamp" */
typedef struct
{
    /* Configures the handling of the buffer in case the mode is "Timestamp" */
	Icu_TimestampBufferType IcuTimestampMeasurementProperty;
	
	/* Notification function if the number of requested timestamps are acquired */
	void (*IcuTimestampNotificaion)(void);

}Icu_TimestampMeasurementType;


#if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
/* Configuration needed to configure a wakeup capable channel */
typedef struct 
{
	EcuM_WakeupSourceType  IcuChannelWakeupInfo;
			
}Icu_WakeupType;
#endif /* STD_ON == ICU_REPORT_WAKEUP_SOURCE */

/* Configuration of an individual ICU channel. */
typedef struct 
{
	/* Channel Id of the ICU channel */
	uint16 IcuChannelId;
	
	/* Configures the default-activation-edge */
	Icu_ActivationType IcuDefaultStartEdge; 

    /* Configures the measurement mode of this channel */
	Icu_MeasurementModeType IcuMeasurementMode;
	
	/* Information about the wakeup-capability of this channel */
	boolean IcuWakeupCapability;
	
	/* Configuration in case the measurement mode is "IcuEdgeCounter" */
	Icu_EdgeCounterMeasurementType IcuEdgeCounterMeasurement;
	
	/* Configuration in case the measurement mode is "IcuSignalEdgeDetection" */
	Icu_SignalEdgeDetectionType IcuSignalEdgeDetection;
	
	/* Configuration in case the measurement mode is "IcuSignalMeasurement" */
	Icu_SignalMeasurementType  IcuSignalMeasurement;
	
	/* Configuration in case the measurement mode is "IcuTimestamp" */
	Icu_TimestampMeasurementType  IcuTimestampMeasurement;
	
	#if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
	/* Configuration needed to configure a wakeup capable channel */
	Icu_WakeupType  IcuWakeup;
	#endif /* STD_ON == ICU_REPORT_WAKEUP_SOURCE */

} Icu_ChannelSetType;

/* The base for a multiple configuration set */
typedef struct
{
	Icu_ChannelType IcuMaxChannel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) IcuChannel;

} Icu_ConfigSetType;

/* This type contains initialization data */
typedef struct
{
	const Icu_ConfigSetType  IcuConfigSet;

}Icu_ConfigType;


/* The followings don't belong to AUTOSAR */

/* Definition the name of a single channel */
typedef  enum 
{
	CHANNEL_0 = 0,
	CHANNEL_8 = 8,
	CHANNEL_9 = 9,
	CHANNEL_10 = 10,
	CHANNEL_12 = 12,
	CHANNEL_14 = 14,
	CHANNEL_23 = 23
}Icu_Channels;

/* Definition the attributes of a single channel */
typedef struct
{
	boolean initrun;
	
	/*to store the used channel ID*/
	Icu_ChannelType IcuChannel[CHANNEL_NUMBER];
	
	/*store the status:active or idle for a channel*/
	Icu_InputStateType IcuInputStatus[CHANNEL_NUMBER];
	
	/* store the mode type:normal or sleep for a channel*/
	Icu_ModeType IcuMode[CHANNEL_NUMBER];
	
	boolean IcuWakeupCapability[CHANNEL_NUMBER];
	
	/*store the swith of 8 channels for notification*/
	boolean IcuNotificationSwitch[CHANNEL_NUMBER];
	
	#if (STD_ON == ICU_EDGE_COUNT_API)
	boolean IcuEdgeCountSwitch[CHANNEL_NUMBER];
	#endif /* STD_ON == ICU_EDGE_COUNT_API */

	#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)
	boolean IcuSignalMeasurementSwitch[CHANNEL_NUMBER];
	#endif /* STD_ON == ICU_SIGNAL_MEASUREMENT_API */

}Icu_ChannelInfoType;

/* Definition the global parameter set of a single channel */
typedef struct
{
	uint32 TimestampBufferSize[CHANNEL_NUMBER];
	
	P2VAR(Icu_ValueType, AUTOMATIC, ICU_VAR) TimestampBuffer[CHANNEL_NUMBER];
	
	uint32 TimestampNotifyInterval[CHANNEL_NUMBER];
	
	uint32 TimestampBufferIndex[CHANNEL_NUMBER];
	
	#if (ICU_EDGE_COUNT_API == STD_ON)	
	Icu_EdgeNumberType EdgeCounterIndex[CHANNEL_NUMBER];	
	#endif /* ICU_EDGE_COUNT_API == STD_ON */
	
	uint32 TimeElaspedValue[CHANNEL_NUMBER];
	
	Icu_DutyCycleType DutyCycleBuffer[CHANNEL_NUMBER];
	
}Icu_GlobalParameterType;

/*=======[E X T E R N A L   D A T A]==========================================*/
extern P2CONST(Icu_ConfigType, AUTOMATIC, ICU_VAR) Icu_GlobalConfig;
extern VAR(Icu_ChannelInfoType, ICU_VAR) Icu_GlobalChannelInfo;
extern VAR(Icu_GlobalParameterType, ICU_VAR) Icu_GlobalParameter;
extern const Icu_ConfigType Icu_GlobalDefaultConfig[1];

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
 
/******************************************************************************/
/*
 * Brief               <This function initializes the driver.>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_Init(P2CONST(Icu_ConfigType, AUTOMATIC, ICU_APPL_CONST)ConfigPtr);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function de-initializes the ICU module.>
 * ServiceId           <0x01>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_DEINIT_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_DeInit(void);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_DEINIT_API */

/******************************************************************************/
/*
 * Brief               <This function sets the ICU mode.>
 * ServiceId           <0x02>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_SET_MODE_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_SetMode(Icu_ModeType Mode);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_SET_MODE_API */

/******************************************************************************/
/*
 * Brief               <This function disables the wakeup capability of a single ICU channel.>
 * ServiceId           <0x03>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_DISABLE_WAKEUP_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_DisableWakeup(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_DISABLE_WAKEUP_API */

/******************************************************************************/
/*
 * Brief               <This function (re-)enables the wakeup capability of the given ICU channel.>
 * ServiceId           <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_ENABLE_WAKEUP_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_EnableWakeup(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_ENABLE_WAKEUP_API */

/******************************************************************************/
/*
 * Brief               <This function sets the activation-edge for the given channel.>
 * ServiceId           <0x05>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel, Activation>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_SetActivationCondition(Icu_ChannelType Channel, Icu_ActivationType Activation);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function disables the notification of a channel.>
 * ServiceId           <0x06>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_DisableNotification(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function enables the notification on the given channel.>
 * ServiceId           <0x07>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_EnableNotification(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function returns the status of ICU input.>
 * ServiceId           <0x08>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Icu_InputStateType>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_GET_INPUT_STATE_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Icu_InputStateType, ICU_CODE) Icu_GetInputState(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_GET_INPUT_STATE_API */

/******************************************************************************/
/*
 * Brief               <This function starts the capturing of timer values on the edges.>
 * ServiceId           <0x09>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel, BufferPtr, BufferSize, NotifyInterval>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_TIMESTAMP_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_StartTimestamp(Icu_ChannelType Channel,\
                                               P2VAR(Icu_ValueType, AUTOMATIC, ICU_VAR) BufferPtr,\
                                               uint16 BufferSize, uint16 NotifyInterval);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_TIMESTAMP_API */

/******************************************************************************/
/*
 * Brief               <This function stops the timestamp measurement of the given channel.>
 * ServiceId           <0x0a>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_TIMESTAMP_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_StopTimestamp(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_TIMESTAMP_API */

/******************************************************************************/
/*
 * Brief               <This function reads the timestamp index of the given channel.>
 * ServiceId           <0x0b>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Icu_IndexType>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_TIMESTAMP_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Icu_IndexType, ICU_CODE) Icu_GetTimestampIndex(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_TIMESTAMP_API */

/******************************************************************************/
/*
 * Brief               <This function resets the value of the counted edges to zero.>
 * ServiceId           <0x0c>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_EDGE_COUNT_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_ResetEdgeCount(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_EDGE_COUNT_API */

/******************************************************************************/
/*
 * Brief               <This function enables the counting of edges of the given channel.>
 * ServiceId           <0x0d>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_EDGE_COUNT_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_EnableEdgeCount(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_EDGE_COUNT_API */

/******************************************************************************/
/*
 * Brief               <This function disables the counting of edges of the given channel.>
 * ServiceId           <0x0e>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_EDGE_COUNT_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_DisableEdgeCount(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_EDGE_COUNT_API */

/******************************************************************************/
/*
 * Brief               <This function reads the number of counted edges.>
 * ServiceId           <0x0f>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Icu_EdgeNumberType>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_EDGE_COUNT_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Icu_EdgeNumberType, ICU_CODE) Icu_GetEdgeNumbers(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_EDGE_COUNT_API */

/******************************************************************************/
/*
 * Brief               <This function starts the measurement of signals.>
 * ServiceId           <0x13>
 * Sync/Async          <ASynchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_StartSignalMeasurement(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_SIGNAL_MEASUREMENT_API */

/******************************************************************************/
/*
 * Brief               <This function stops the measurement of signals of the given channel.>
 * ServiceId           <0x14>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_SIGNAL_MEASUREMENT_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_StopSignalMeasurement(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_SIGNAL_MEASUREMENT_API */

/******************************************************************************/
/*
 * Brief               <This function reads the elapsed Signal Low Time for the given channel.>
 * ServiceId           <0x10>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Icu_ValueType>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_GET_TIME_ELAPSED_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Icu_ValueType, ICU_CODE) Icu_GetTimeElapsed(Icu_ChannelType Channel);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_GET_TIME_ELAPSED_API */

/******************************************************************************/
/*
 * Brief               <This function reads the coherent active time and period time for the given ICU Channel.>
 * ServiceId           <0x11>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Channel>      
 * Param-Name[out]     <DutyCycleValues>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_GET_DUTYCYCLE_VALUES_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_GetDutyCycleValues(Icu_ChannelType Channel,\
                                                   P2VAR(Icu_DutyCycleType, AUTOMATIC, ICU_VAR) DutyCycleValues);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_GET_DUTYCYCLE_VALUES_API */

/******************************************************************************/
/*
 * Brief               <This function returns the version information of this module.>
 * ServiceId           <0x12>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <versioninfo>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (STD_ON == ICU_GET_VERSION_INFO_API)
#define ICU_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ICU_CODE) Icu_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, ICU_VAR) versioninfo);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == ICU_GET_VERSION_INFO_API */

#endif  /* ICU_H */

/*=======[E N D   O F   F I L E]==============================================*/
