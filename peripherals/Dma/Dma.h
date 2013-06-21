/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <Dma.h>
 *  @brief      <This is Dma header file>
 *  
 *  <Compiler: cw2.6    MCU:mpc5634>
 *  
 *  @author     <author name>
 *  @date       <dd-mm-yyyy>
 */
/*============================================================================*/
#ifndef DMA_H
#define DMA_H

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
/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
#include "Std_ExtTypes.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define DMA_VENDOR_ID  62
#define DMA_MODULE_ID  0
#define DMA_H_AR_MAJOR_VERSION  1
#define DMA_H_AR_MINOR_VERSION  0
#define DMA_H_AR_PATCH_VERSION  0
#define DMA_H_SW_MAJOR_VERSION  2
#define DMA_H_SW_MINOR_VERSION  0
#define DMA_H_SW_PATCH_VERSION  0

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/*	Define the type for Dma TCD	*/
typedef struct tcd_t Dma_TCD_Type;

/*	Define the type for channel used state	*/
typedef struct
{
	uint32 HChState;
	uint32 LChState;	
}Dma_ChannelStateType;

/* Define the type for Dma channel.	*/
typedef enum
{
	DMA_ADC_GROUP0_FILLCOMMAND_CHANNEL = 0,
	DMA_ADC_GROUP0_READRESULT_CHANNEL,
	DMA_ADC_GROUP1_FILLCOMMAND_CHANNEL,
	DMA_ADC_GROUP1_READRESULT_CHANNEL,
	DMA_ADC_GROUP2_FILLCOMMAND_CHANNEL,
	DMA_ADC_GROUP2_READRESULT_CHANNEL,
	DMA_ADC_GROUP3_FILLCOMMAND_CHANNEL,
	DMA_ADC_GROUP3_READRESULT_CHANNEL,
	DMA_ADC_GROUP4_FILLCOMMAND_CHANNEL,
	DMA_ADC_GROUP4_READRESULT_CHANNEL,
	DMA_ADC_GROUP5_FILLCOMMAND_CHANNEL,
	DMA_ADC_GROUP5_READRESULT_CHANNEL	
			
}Dma_ChannelType;

/* Define the type for Dma data transfersize.*/
typedef enum
{
	DMA_TRANSFER_SIZE_1_BYTE = 0,	
	DMA_TRANSFER_SIZE_2_BYTE,
	DMA_TRANSFER_SIZE_4_BYTE,
	DMA_TRANSFER_SIZE_8_BYTE
}Dma_DataTransferSizeType;

/* Define the type for Dma interrupt*/
typedef enum
{
	DMA_CHANNELMAJORINTERRUPT_DISABLE = 0,
	DMA_CHANNELMAJORINTERRUPT_ENABLE = 1	
}Dma_SetChannelMajorInterruptType;

/*=======[E X T E R N A L   D A T A]=========================================*/
extern VAR(Dma_ChannelStateType, ADC_APPL_DATA) Dma_ChannelState;

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]=======*/
/******************************************************************************/
/*
 * Brief               <This service configure the Dma module initially.>
 * ServiceId           <ServiceIdNumber>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant/Non Reentrant>
 * Param-Name[in]      <Dma_ChannelType channel, Dma_TCD_Type* tcd>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void, DMA_PUBLIC_CODE) Dma_ConfigureChannel(Dma_ChannelType channel,P2CONST(Dma_TCD_Type,AUTOMATIC,DMA_APPL_CONST) tcd);
/******************************************************************************/
/*
 * Brief               <This service configure the Dma module transfering size.>
 * ServiceId           <ServiceIdNumber>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant/Non Reentrant>
 * Param-Name[in]      <Dma_ChannelType channel,uint32 numberofIterations>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void, DMA_PUBLIC_CODE) Dma_ConfigureChannelTransferSize(Dma_ChannelType channel,uint32 numberofIterations);
/******************************************************************************/
/*
 * Brief               <This service start Dma moudle.>
 * ServiceId           <ServiceIdNumber>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant/Non Reentrant>
 * Param-Name[in]      <Dma_ChannelType channel,uint32 numberofIterations>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void, DMA_PUBLIC_CODE) Dma_StartChannel(Dma_ChannelType channel);
/******************************************************************************/
/*
 * Brief               <This service configures whether to enable interrupt
 *						after major loop has been finished.>
 * ServiceId           <ServiceIdNumber>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant/Non Reentrant>
 * Param-Name[in]      <Dma_ChannelType channel, Dma_SetChannelMajorInterruptType 
 *						control>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void, DMA_PUBLIC_CODE) Dma_SetChannelMajorInterrupt(Dma_ChannelType channel, Dma_SetChannelMajorInterruptType control);
/******************************************************************************/
/*
 * Brief               <This service configures whether to disable interrupt
 *						after major loop has been finished.>
 * ServiceId           <ServiceIdNumber>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant/Non Reentrant>
 * Param-Name[in]      <Dma_ChannelType channel, Dma_SetChannelMajorInterruptType 
 *						control>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <None> 
 */
/******************************************************************************/
extern FUNC(void, DMA_PUBLIC_CODE) Dma_DeleteChannel(Dma_ChannelType channel);
/*=======[I N T E R N A L   D A T A]=========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]=======*/

#endif
/*=======[E N D   O F   F I L E]=============================================*/
