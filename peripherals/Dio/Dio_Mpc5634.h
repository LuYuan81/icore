/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Dio_Mpc5634.h>
 *  @brief      <Abstract API of Dio Module>
 *  
 *  <Compiler: CodeWarrior V2.10    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/
#ifndef Dio_MPC5634_H_
#define Dio_MPC5634_H_

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
#include "Dio.h" 

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

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/******************************************************************************/
/*
 * Brief               <Returns the value of the specified DIO channel.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ChannelId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Dio_LevelType:STD_HIGH STD_LOW>  
 * PreCondition        <>  
 * CallByAPI           <Dio_ReadChannel> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
FUNC(Dio_LevelType,DIO_CODE)Dio_Mpc5634ReadChannel(Dio_ChannelType channelId);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to set a level of a channel.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ChannelId , Level>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Dio_WriteChannel> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
FUNC(void,DIO_CODE)Dio_Mpc5634WriteChannel(Dio_ChannelType channelId, Dio_LevelType level);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Returns the level of all channels of that port.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <PortId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Dio_PortLevelType:Level of all channels of that port>  
 * PreCondition        <>  
 * CallByAPI           <Dio_ReadPort> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
FUNC(Dio_PortLevelType,DIO_CODE)Dio_Mpc5634ReadPort(Dio_PortType portId);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to set a value of the port.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <PortId, Level>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Dio_WritePort> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
FUNC(void,DIO_CODE)Dio_Mpc5634WritePort(Dio_PortType portId, Dio_PortLevelType levelPort);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to set a subset of the adjoining bits of a port to a specified level.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ChannelGroupIdPtr , Level>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Dio_WriteChannelGroup> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"
FUNC(void,DIO_CODE) Dio_Mpc5634WriteChannelGroup(
    P2CONST(Dio_ChannelGroupType,AUTOMATIC,DIO_APPL_DATA)channelGroupIdPtr,Dio_PortLevelType levelPort);
#define DIO_STOP_SEC_CODE
#include "MemMap.h"

#endif  

/*=======[E N D   O F   F I L E]==============================================*/
