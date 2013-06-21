/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Dma.c>
 *  @brief      <This is Dma C file>
 *  
 *  <Compiler: cw2.6    MCU:mpc5634>
 *  
 *  @author     <author name>
 *  @date       <yyyy-mm-dd>
 */
/*============================================================================*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0        xxx        name       Initial version
 * 
 *  V1.1.0        xxx        name       xxx version
 * 
 *  V2.0.0        xxx        name       xxx version.
 */
/*============================================================================*/
/*=======[M I S R A  R U L E  V I O L A T I O N]==============================*/
/* MISRA-C:2004 Rule 19.1 */

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define DMA_C_AR_MAJOR_VERSION  1
#define DMA_C_AR_MINOR_VERSION  0
#define DMA_C_AR_PATCH_VERSION  0
#define DMA_C_SW_MAJOR_VERSION  2
#define DMA_C_SW_MINOR_VERSION  0
#define DMA_C_SW_PATCH_VERSION  0

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
#include "Dma.h"

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (DMA_C_AR_MAJOR_VERSION != DMA_H_AR_MAJOR_VERSION)
#error "DMA.c : Mismatch in Specification Major Version"
#endif
#if (DMA_C_AR_MINOR_VERSION != DMA_H_AR_MINOR_VERSION)
#error "DMA.c : Mismatch in Specification Major Version"
#endif
#if (DMA_C_AR_PATCH_VERSION != DMA_H_AR_PATCH_VERSION)
#error "DMA.c : Mismatch in Specification Major Version"
#endif
#if (DMA_C_SW_MAJOR_VERSION != DMA_H_SW_MAJOR_VERSION)
#error "DMA.c : Mismatch in Specification Major Version"
#endif
#if (DMA_C_SW_MINOR_VERSION != DMA_H_SW_MINOR_VERSION)
#error "DMA.c : Mismatch in Specification Major Version"
#endif

/*=======[M A C R O S]========================================================*/
#define MaxChannel 64
#define USED       1
#define UNUSED     0
#define DMA_ONE	   1
#define DMA_ZERO   0

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   D A T A]==========================================*/
VAR(Dma_ChannelStateType,ADC_APPL_DATA) Dma_ChannelState;

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

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
#define DMA_START_SEC_CODE
#include "MemMap.h"
FUNC(void,DMA_PUBLIC_CODE) Dma_ConfigureChannel(Dma_ChannelType channel,P2CONST(Dma_TCD_Type,AUTOMATIC,DMA_APPL_CONST) tcd)
{
	uint8 channelState;
	uint8 statePostion;
	uint8 loopcnt;
	uint8 endLoop;
	
	/* Error channel */
	if(channel > MaxChannel)
	{
		return ;	
	}

	endLoop = ZERO;
	channelState = UNUSED;
	for (loopcnt = ZERO; ((loopcnt < MaxChannel)&&(endLoop == ZERO)); loopcnt++)
	{
		if (channel > 32)
		{	
			/* Get the channel status postion */
			statePostion = (uint8)(channel - 32);
			if(((Dma_ChannelState.HChState)&(uint32)(DMA_ONE<<statePostion)) == (uint32)USED)
			{
				/* Set the channel state */
				channelState = USED;
				/* Set the channel state */
				endLoop = ONE;
			}
			else
			{
				/* Set the channel state */
				Dma_ChannelState.HChState |= (uint32)(DMA_ONE<<statePostion);
				/* End loop */	
				endLoop = ONE;
			}
		}
		else
		{
			/* Set the channel state */	
			statePostion =  channel;
			if (((Dma_ChannelState.LChState)&(uint32)(DMA_ONE<<statePostion)) == (uint32)USED)
			{
				/* Set the channel state */
				channelState = USED;
				/* End loop*/
				endLoop = ONE;	
			}
			else
			{
				/* Set the channel state */
				Dma_ChannelState.LChState |= (uint32)(DMA_ONE<<statePostion);
				/* End loop */
				endLoop = ONE;
			}	
				
		}
	}
	
	/* The channel is used */	
	if (USED == channelState)
	{
		return;	
	}
	
	/* Reset the DMA channel configure */
	EDMA.TCD[channel].SADDR = tcd->SADDR;
	EDMA.TCD[channel].SSIZE = tcd->SSIZE;
	EDMA.TCD[channel].SOFF 	= tcd->SOFF;
	EDMA.TCD[channel].SLAST = tcd->SLAST;
	EDMA.TCD[channel].SMOD  = tcd->SMOD;
	EDMA.TCD[channel].DADDR = tcd->DADDR;
	EDMA.TCD[channel].DSIZE = tcd->DSIZE;
	EDMA.TCD[channel].DOFF = tcd->DOFF;
	
	EDMA.TCD[channel].DLAST_SGA = tcd->DLAST_SGA;
	EDMA.TCD[channel].DMOD = tcd->DMOD;
	EDMA.TCD[channel].NBYTES = tcd->NBYTES;
	EDMA.TCD[channel].BITER	= tcd->BITER;
	EDMA.TCD[channel].CITER	= tcd->CITER;
	EDMA.TCD[channel].D_REQ	= tcd->D_REQ;
	EDMA.TCD[channel].INT_HALF = tcd->INT_HALF;
	EDMA.TCD[channel].INT_MAJ = tcd->INT_MAJ;
	
	EDMA.TCD[channel].CITERE_LINK = tcd->CITERE_LINK;
	EDMA.TCD[channel].BITERE_LINK = tcd->BITERE_LINK;
	EDMA.TCD[channel].MAJORE_LINK = tcd->MAJORE_LINK;
	EDMA.TCD[channel].E_SG = tcd->E_SG;
	EDMA.TCD[channel].BWC = tcd->BWC;
	EDMA.TCD[channel].START	= tcd->START;
	EDMA.TCD[channel].DONE	= tcd->DONE;
	EDMA.TCD[channel].ACTIVE = tcd->ACTIVE;
	
	/*disable channel*/
	EDMA.CERQR.R = channel;
	
	return ;
	
}
#define DMA_STOP_SEC_CODE
#include "MemMap.h"
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
#define DMA_START_SEC_CODE
#include "MemMap.h"
FUNC(void, DMA_PUBLIC_CODE) Dma_ConfigureChannelTransferSize(Dma_ChannelType channel,uint32 numberofIterations)
{
	/* Set the biter */	
	EDMA.TCD[channel].BITER = numberofIterations;
	/* Set the citer */
	EDMA.TCD[channel].CITER = numberofIterations;
	return ;
}
#define DMA_STOP_SEC_CODE
#include "MemMap.h"

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
#define DMA_START_SEC_CODE
#include "MemMap.h"
FUNC(void, DMA_PUBLIC_CODE) Dma_StartChannel(Dma_ChannelType channel)
{
	/* Enable channel */	
	EDMA.SERQR.R = channel; 
	return ;
}
#define DMA_STOP_SEC_CODE
#include "MemMap.h"

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
#define DMA_START_SEC_CODE
#include "MemMap.h"
FUNC(void,DMA_PUBLIC_CODE)Dma_SetChannelMajorInterrupt(Dma_ChannelType channel,Dma_SetChannelMajorInterruptType control)
{
	/* Set the major */
	EDMA.TCD[channel].INT_MAJ = control;
	return ;
}
#define DMA_STOP_SEC_CODE
#include "MemMap.h"

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
#define DMA_START_SEC_CODE
#include "MemMap.h"
FUNC(void,DMA_PUBLIC_CODE) Dma_DeleteChannel(Dma_ChannelType channel)
{
	uint8  statePostion;
	uint8  loopcnt;
	
	/* Check the DMA channel */
	for(loopcnt = DMA_ZERO;loopcnt < MaxChannel;loopcnt++)
	{
		if(channel > 32)
		{	
			/* Get the channel status postion */
			statePostion =(uint8) (channel - 32);
			/* Set the channel status */
			Dma_ChannelState.HChState &= (uint32)(~((uint32)ONE<<statePostion));
			
		}
		else
		{	
			/* Get the channel status postion */
			statePostion = channel;
			/* Set the channel status */
			Dma_ChannelState.LChState &= (uint32)(~((uint32)ONE<<statePostion));	
		}
	}
	
	/* Reset the DMA channel configure */
	EDMA.TCD[channel].SADDR = ZERO;
	EDMA.TCD[channel].SSIZE = ZERO;
	EDMA.TCD[channel].SOFF 	= ZERO;
	EDMA.TCD[channel].SLAST = ZERO;
	EDMA.TCD[channel].SMOD  = ZERO;
	EDMA.TCD[channel].DADDR = ZERO;
	EDMA.TCD[channel].DSIZE = ZERO;
	EDMA.TCD[channel].DOFF = ZERO;
	
	EDMA.TCD[channel].DLAST_SGA = ZERO;
	EDMA.TCD[channel].DMOD = ZERO;
	EDMA.TCD[channel].NBYTES = ZERO;
	EDMA.TCD[channel].BITER	= ZERO;
	EDMA.TCD[channel].CITER	= ZERO;
	EDMA.TCD[channel].D_REQ	= ZERO;
	EDMA.TCD[channel].INT_HALF = ZERO;
	EDMA.TCD[channel].INT_MAJ = ZERO;
	
	EDMA.TCD[channel].CITERE_LINK = ZERO;
	EDMA.TCD[channel].BITERE_LINK = ZERO;
	EDMA.TCD[channel].MAJORE_LINK = ZERO;
	EDMA.TCD[channel].E_SG = ZERO;
	EDMA.TCD[channel].BWC = ZERO;
	EDMA.TCD[channel].START	= ZERO;
	EDMA.TCD[channel].DONE	= ZERO;
	EDMA.TCD[channel].ACTIVE = ZERO;
	
	return ;
	
}
#define DMA_STOP_SEC_CODE
#include "MemMap.h"

/*=======[L O C A L  	F U N C T I O N S]====================================*/

/*=======[E N D   O F   F I L E]==============================================*/











