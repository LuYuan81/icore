/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Dio.h>
 *  @brief      <Abstract API of Dio Module)>
 *  
 *  <Compiler: CodeWarrior V2.10    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/
#ifndef DIO_H_
#define DIO_H_

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
/* MISRA-C:2004 Rule 3.4; REFERENCE - ISO:C90-6.8.6 Pragma Directive */
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h" /** @req DIO131 */
#include "Std_ExtTypes.h"
#include "Dio_Cfg.h"

#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define DIO_C_VENDOR_ID                 0
#define DIO_C_MODULE_ID                 120
#define DIO_C_VENDOR_API_INFIX          0
#define DIO_AR_MAJOR_VERSION            2       
#define DIO_AR_MINOR_VERSION            2
#define DIO_AR_PATCH_VERSION            2
#define DIO_SW_MAJOR_VERSION            1
#define DIO_SW_MINOR_VERSION            0
#define DIO_SW_PATCH_VERSION            0

/*=======[M A C R O S]========================================================*/
#define	DIO_E_PARAM_INVALID_CHANNEL_ID  10
#define DIO_E_PARAM_INVALID_PORT_ID		20
#define DIO_E_PARAM_INVALID_GROUP_ID	31

/** @req DIO103 */
#define DIO_READCHANNEL_ID				0x00
#define DIO_WRITECHANNEL_ID				0x01	
#define DIO_READPORT_ID					0x02
#define DIO_WRITEPORT_ID				0x03
#define DIO_READCHANNELGROUP_ID			0x04
#define DIO_WRITECHANNELGROUP_ID		0x05

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/* Define the type for Channels. */
typedef uint32 Dio_ChannelType; /** @req DIO015 @req DIO017 */

/* Define the type for Ports. */
typedef uint32 Dio_PortType;    /** @req DIO018 @req DIO020 */

/* Define the level data type for Dio channel. */
typedef uint32 Dio_LevelType;   /** @req DIO023 */

/* Define the level data type for Ports. */
typedef uint32 Dio_PortLevelType;/** @req DIO024 */

/* Define the type for channel group. */
typedef struct
{
    Dio_PortType port; 	/** @req DIO149 */
    uint8 offset; 		/** @req DIO151 */
    uint16 mask; 		/** @req DIO150 */
} Dio_ChannelGroupType; /** @req DIO021 @req DIO022 @req DIO148 */

/*=======[E X T E R N A L   D A T A]==========================================*/
extern CONST(Dio_ChannelType, DIO_CONST) DioChannelConfigData[NUMBER_OF_CHANNELS];
extern CONST(Dio_PortType,DIO_CONST)DioPortConfigData[NUMBER_OF_PORTS];
extern CONST(Dio_ChannelGroupType,DIO_CONST)DioConfigData[NUMBER_OF_CHANNELGROUPS];

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/******************************************************************************/
/*
 * Brief               <Returns the value of the specified DIO channel.>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ChannelId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Dio_LevelType:STD_HIGH STD_LOW>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Dio_LevelType,DIO_CODE) Dio_ReadChannel(Dio_ChannelType channelId);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to set a level of a channel.>
 * ServiceId           <0x01>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ChannelId , Level>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,DIO_CODE) Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Returns the level of all channels of that port.>
 * ServiceId           <0x02>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <PortId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Dio_PortLevelType:Level of all channels of that port>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Dio_PortLevelType,DIO_CODE) Dio_ReadPort(Dio_PortType portId);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to set a value of the port.>
 * ServiceId           <0x03>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <PortId, Level>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,DIO_CODE)Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This Service reads a subset of the adjoining bits of a port.>
 * ServiceId           <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ChannelGroupIdPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Dio_PortLevelType:>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Dio_PortLevelType,DIO_CODE) Dio_ReadChannelGroup(
    P2CONST(Dio_ChannelGroupType,AUTOMATIC,DIO_APPL_DATA)channelGroupIdPtr);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to set a subset of the adjoining bits of a port to a specified level.>
 * ServiceId           <0x05>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <ChannelGroupIdPtr , Level>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,DIO_CODE) Dio_WriteChannelGroup(
    P2CONST(Dio_ChannelGroupType,AUTOMATIC,DIO_APPL_DATA)channelGroupIdPtr,Dio_PortLevelType level);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to get the version information of this module.>
 * ServiceId           <0x12>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <VersionInfo>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <DIO_VERSION_INFO_API == STD_ON>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON) 
#define DIO_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,DIO_CODE) Dio_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC,DIO_APPL_DATA) VersioninfoPtr);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

#endif  

/*=======[E N D   O F   F I L E]==============================================*/

