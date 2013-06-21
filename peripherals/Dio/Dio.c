/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Dio.c>
 *  @brief      <Abstract API of Dio Module)>
 *  
 *  <Compiler: CodeWarrior V2.10    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/

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
/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */

/*=======[I N C L U D E S]====================================================*/
#include "Dio.h"
#include "Det.h"
#include "Dio_Mpc5634.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define DIO_AR_MAJOR_VERSION_C   2
#define DIO_AR_MINOR_VERSION_C   2
#define DIO_AR_PATCH_VERSION_C   2
#define DIO_SW_MAJOR_VERSION_C   1
#define DIO_SW_MINOR_VERSION_C   0
#define DIO_SW_PATCH_VERSION_C   0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if((DIO_AR_MAJOR_VERSION_C != DIO_AR_MAJOR_VERSION)\
  ||(DIO_AR_MINOR_VERSION_C != DIO_AR_MINOR_VERSION)\
  ||(DIO_AR_PATCH_VERSION_C != DIO_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Dio.c and Dio.h are different"
#endif

#if ((DIO_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION)\
  ||(DIO_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION)\
  ||(DIO_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION))
#error "Software Version Numbers of Dio.c and Dio.h are different"
#endif

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#define DIO_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(uint8, DIO_CODE) Dio_ChannelConfigContains(Dio_ChannelType channelId );
STATIC FUNC(uint8, DIO_CODE) Dio_PortConfigContains(Dio_PortType portId );
STATIC FUNC(uint8, DIO_CODE) Dio_ChannelGroupConfigContains(P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) channelGroupIdPtr);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

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

FUNC(Dio_LevelType , DIO_CODE) Dio_ReadChannel(Dio_ChannelType channelId)
{   
    /** @req DIO083 @req DIO084 */
    Dio_LevelType level = STD_LOW;
	
    #if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (E_NOT_OK == Dio_ChannelConfigContains(channelId)) 
    { 
        Det_ReportError(MODULE_ID_DIO, ZERO, DIO_READCHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID); 
        return STD_LOW; /** @req DIO118 */
    }
    #endif	/* DIO_DEV_ERROR_DETECT == STD_ON */
	
    level = Dio_Mpc5634ReadChannel(channelId);
    return (level); 	/** @req DIO027 */
}

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

FUNC(void,DIO_CODE) Dio_WriteChannel(Dio_ChannelType channelId, Dio_LevelType level)
{
    /** @req DIO028 @req DIO029 @req DIO079 */
    #if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (E_NOT_OK == Dio_ChannelConfigContains(channelId)) 
    { 	
        Det_ReportError(MODULE_ID_DIO, ZERO, DIO_WRITECHANNEL_ID, DIO_E_PARAM_INVALID_CHANNEL_ID); 
        return; /** @req DIO119 */	
    }
    #endif	/* DIO_DEV_ERROR_DETECT == STD_ON */

    Dio_Mpc5634WriteChannel( channelId , level);
}

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

FUNC(Dio_PortLevelType,DIO_CODE) Dio_ReadPort(Dio_PortType portId)
{
    Dio_PortLevelType levelPort = STD_LOW;
	
    #if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (E_NOT_OK == Dio_PortConfigContains(portId)) 
    { 
        Det_ReportError(MODULE_ID_DIO, ZERO, DIO_READPORT_ID, DIO_E_PARAM_INVALID_PORT_ID); 
        return STD_LOW; /** @req DIO118 */
    }	
    #endif	/* DIO_DEV_ERROR_DETECT == STD_ON */
		
    levelPort = Dio_Mpc5634ReadPort(portId);
    return levelPort; /** @req DIO031 */
}

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

FUNC(void,DIO_CODE)Dio_WritePort(Dio_PortType portId, Dio_PortLevelType level)
{
    #if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (E_NOT_OK == Dio_PortConfigContains(portId)) 
    { 
        Det_ReportError(MODULE_ID_DIO, ZERO, DIO_WRITEPORT_ID, DIO_E_PARAM_INVALID_PORT_ID); 
        return; 
    }
    #endif	/* DIO_DEV_ERROR_DETECT == STD_ON */
		
    Dio_Mpc5634WritePort( portId, level);
}

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

FUNC(Dio_PortLevelType,DIO_CODE) Dio_ReadChannelGroup(
    P2CONST(Dio_ChannelGroupType,AUTOMATIC,DIO_APPL_DATA)channelGroupIdPtr)
{
    Dio_PortLevelType level;
	
    #if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (E_NOT_OK == Dio_ChannelGroupConfigContains(channelGroupIdPtr)) 
    { 
        Det_ReportError(MODULE_ID_DIO, ZERO, DIO_READCHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID); 
        return STD_LOW; 
    }
    #endif	/* DIO_DEV_ERROR_DETECT == STD_ON */
							  
    level = Dio_ReadPort(channelGroupIdPtr->port);
    level &= channelGroupIdPtr->mask;	/** @req DIO37  @req DIO92*/
    level >>= channelGroupIdPtr->offset;/** @req DIO93 */
  	
    return level;
}

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

FUNC(void,DIO_CODE) Dio_WriteChannelGroup(
    P2CONST(Dio_ChannelGroupType,AUTOMATIC,DIO_APPL_DATA)channelGroupIdPtr,Dio_PortLevelType level)
{
    #if (DIO_DEV_ERROR_DETECT == STD_ON)
    if (E_NOT_OK == Dio_ChannelGroupConfigContains(channelGroupIdPtr))  
    { 
        Det_ReportError(MODULE_ID_DIO, ZERO, DIO_WRITECHANNELGROUP_ID, DIO_E_PARAM_INVALID_GROUP_ID); 
        return; 
    }
    #endif		/* DIO_DEV_ERROR_DETECT == STD_ON */
	
    Dio_Mpc5634WriteChannelGroup(channelGroupIdPtr,  level);
}
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
#if (DIO_VERSION_INFO_API == STD_ON) /** @req DIO123*/

#define DIO_START_SEC_CODE
#include "MemMap.h"

FUNC(void,DIO_CODE) Dio_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC,DIO_APPL_DATA) VersioninfoPtr)
{	
    /** @req DIO126  @req DIO134*/
    VersioninfoPtr->vendorID = DIO_C_VENDOR_ID;
    VersioninfoPtr->moduleID = DIO_C_MODULE_ID;
    VersioninfoPtr->instanceID = 1;
    VersioninfoPtr->ar_major_version = DIO_AR_MAJOR_VERSION;
    VersioninfoPtr->ar_minor_version = DIO_AR_MINOR_VERSION;
    VersioninfoPtr->ar_patch_version = DIO_AR_PATCH_VERSION;
    VersioninfoPtr->sw_major_version = DIO_SW_MAJOR_VERSION;
    VersioninfoPtr->sw_minor_version = DIO_SW_MINOR_VERSION;
    VersioninfoPtr->sw_patch_version = DIO_SW_PATCH_VERSION;
}

#define DIO_STOP_SEC_CODE
#include "MemMap.h"

#endif

/*=======[L O C A L   F U N C T I O N   I M P L E M E N T A T I O N S]=======*/

/******************************************************************************/
/*
 * Brief               <Check the channelId .>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channelId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Dio_ReadChannel Dio_WriteChannel> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(uint8, DIO_CODE) Dio_ChannelConfigContains(Dio_ChannelType channelId )
{
    uint8 num=0;
    
    for(num=0 ; num<NUMBER_OF_CHANNELS ; num++)    
    {
        if(DioChannelConfigData[num] == channelId)
        {
            return E_OK;
        }
    }
    
    return E_NOT_OK;
}

#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Check the portId .>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <portId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Dio_ReadPort Dio_WritePort> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(uint8, DIO_CODE) Dio_PortConfigContains(Dio_PortType portId )
{
    uint8 num=0;
    
    for(num=0 ; num<NUMBER_OF_PORTS ; num++)    
    {
        if(DioPortConfigData[num] == portId)
        {
            return E_OK;
        }
    }
    
    return E_NOT_OK;
}

#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Check the ChannelGroup .>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channelGroupIdPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Dio_ReadChannelGroup Dio_WriteChannelGroup> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(uint8, DIO_CODE) Dio_ChannelGroupConfigContains(
            P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) channelGroupIdPtr)
{
    uint8 num=0;
    
    for(num=0 ; num<NUMBER_OF_CHANNELGROUPS ; num++)    
    {
        if((DioConfigData[num].port==channelGroupIdPtr->port)
        && (DioConfigData[num].offset==channelGroupIdPtr->offset)
        && (DioConfigData[num].mask==channelGroupIdPtr->mask))
        {
            return E_OK;
        }
    }
    
    return E_NOT_OK;   
}

#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/

