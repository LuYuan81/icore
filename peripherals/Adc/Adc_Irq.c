/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <filename>
 *  @brief      <Briefly describe file(one line)>
 *  
 *  <Compiler: XXX    MCU:XXX>
 *  
 *  @author     <author name>
 *  @date       <yyyy-mm-dd>
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
/* MISRA-C:2004 Rule 17.4; REFERENCE - ISO:C90-6.3.6 Additive Operators - Constraints */
/* MISRA-C:2004 Rule 20.2*/
/*=======[I N C L U D E S]====================================================*/
#include "Adc.h"
#include "Adc_Irq.h"
#include "Modules.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
/* AUTOSAR specification version information */
#define ADC_IRQ_C__AR_MAJOR_VERSION    3
#define ADC_IRQ_C_AR_MINOR_VERSION    0
#define ADC_IRQ_C_AR_PATCH_VERSION    3

/* File version information */
#define ADC_IRQ_C_SW_MAJOR_VERSION    1
#define ADC_IRQ_C_SW_MINOR_VERSION    0
#define ADC_IRQ_C_SW_PATCH_VERSION	0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (ADC_IRQ_AR_MAJOR_VERSION != ADC_IRQ_C__AR_MAJOR_VERSION)
#error "Adc.c : Mismatch in Specification Major Version"
#endif/* End the #if (ADC_IRQ_AR_MAJOR_VERSION != ADC_IRQ_C__AR_MAJOR_VERSION) */

#if (ADC_IRQ_AR_MINOR_VERSION != ADC_IRQ_C_AR_MINOR_VERSION)
#error "Adc.c : Mismatch in Specification Minor Version"
#endif/* End the #if (ADC_IRQ_AR_MINOR_VERSION != ADC_IRQ_C_AR_MINOR_VERSION) */

#if (ADC_IRQ_AR_PATCH_VERSION != ADC_IRQ_C_AR_PATCH_VERSION)
#error "Adc.c : Mismatch in Specification Patch Version"
#endif/* End the #if (ADC_IRQ_AR_PATCH_VERSION != ADC_IRQ_C_AR_PATCH_VERSION) */

#if (ADC_IRQ_SW_MAJOR_VERSION != ADC_IRQ_C_SW_MAJOR_VERSION)
#error "Adc.c : Mismatch in Major Version"
#endif/* End the #if (ADC_IRQ_SW_MAJOR_VERSION != ADC_IRQ_C_SW_MAJOR_VERSION) */

#if (ADC_IRQ_SW_MINOR_VERSION != ADC_IRQ_C_SW_MINOR_VERSION)
#error "Adc.c : Mismatch in Minor Version"
#endif/* End the #if (ADC_IRQ_SW_MINOR_VERSION != ADC_IRQ_C_SW_MINOR_VERSION) */

#if (ADC_IRQ_SW_PATCH_VERSION != ADC_IRQ_C_SW_PATCH_VERSION)
#error "Adc.c : Mismatch in Minor Version"
#endif/* End the #if (ADC_IRQ_SW_PATCH_VERSION != ADC_IRQ_C_SW_PATCH_VERSION) */

#if (ADC_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif/* End the #if (ADC_DEV_ERROR_DETECT == STD_ON) */

/*=======[M A C R O S]========================================================*/
#define	HARDWARE_MAX_CHANNEL	40

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/
VAR(uint32,ADC_APPL_DATA) ReceiveIsr_index = ZERO;
VAR(uint8,ADC_APPL_DATA) sampleNumber[ADC_SUM_OF_GROUP] = {ZERO};
VAR(uint8,ADC_APPL_DATA) channelSum[ADC_SUM_OF_GROUP] = {ZERO};
VAR(uint8,ADC_APPL_DATA) Lo_finish_sample = ZERO;
VAR(uint32,ADC_APPL_DATA) Final_EndOfQueue_Times[ADC_SUM_OF_GROUP] = {ZERO};
VAR(uint16,ADC_APPL_DATA) Re_EndOfQueue_Times[ADC_SUM_OF_GROUP] = {ZERO};
VAR(boolean,ADC_APPL_DATA) Finish_Load_CFIFO[ADC_SUM_OF_GROUP] = { FALSE };

/*=======[I N T E R N A L   D A T A]==========================================*/


/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_DelayTime(uint32 tim);
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_SetHwTrigEgde(Adc_GroupType groupId);
							
/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_0_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void,ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group0_Isr(void)
{
	Adc_LoadCommand_Hander(ADC_GROUP0);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_1_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void,ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group1_Isr(void)
{
	Adc_LoadCommand_Hander(ADC_GROUP1);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_2_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void,ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group2_Isr(void)
{
	Adc_LoadCommand_Hander(ADC_GROUP2);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_3_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group3_Isr(void)
{	
	Adc_LoadCommand_Hander(ADC_GROUP3);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_4_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group4_Isr(void)
{
	Adc_LoadCommand_Hander(ADC_GROUP4);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_5_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group5_Isr(void)
{
	Adc_LoadCommand_Hander(ADC_GROUP5);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group0_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group0_Isr(void)
{
	Adc_ReceiveEOQF_HandlerIsr(Adc_Group);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group1_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void,ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group1_Isr(void)
{
	Adc_ReceiveEOQF_HandlerIsr(ADC_GROUP1);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group2_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void,ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group2_Isr(void)
{
	Adc_ReceiveEOQF_HandlerIsr(ADC_GROUP2);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group3_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group3_Isr(void)
{
	Adc_ReceiveEOQF_HandlerIsr(ADC_GROUP3);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group4_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group4_Isr(void)
{
	Adc_ReceiveEOQF_HandlerIsr(ADC_GROUP4);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group5_Isr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group5_Isr(void)
{
	Adc_ReceiveEOQF_HandlerIsr(ADC_GROUP5);		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group0_ISR>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group0_ISR(void)
{
	EQADC.IDCR[1].B.PIE = ZERO;
	Adc_GroupStatus[ADC_GROUP0] = ADC_STREAM_COMPLETED;
	Adc_DMA_DataHandler(ADC_GROUP0);
	EQADC.IDCR[1].B.PIE = ONE;
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group1_ISR>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group1_ISR(void)
{
	EQADC.IDCR[0].B.PIE = ZERO;
	Adc_GroupStatus[ADC_GROUP1] = ADC_STREAM_COMPLETED;
	Adc_DMA_DataHandler(ADC_GROUP1);
	EQADC.IDCR[0].B.PIE = ONE;
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group2_ISR>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group2_ISR(void)
{
	Adc_DMA_DataHandler(ADC_GROUP2);
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group3_ISR>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group3_ISR(void)
{
	Adc_DMA_DataHandler(ADC_GROUP3);
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group4_ISR>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group4_ISR(void)
{
	Adc_DMA_DataHandler(ADC_GROUP4);
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group5_ISR>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group5_ISR(void)
{
	Adc_DMA_DataHandler(ADC_GROUP5);
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_LoadCommand_Hander>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <groupId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCommand_Hander(Adc_GroupType groupId)
{
	uint8 j = ZERO;
	Adc_TriggerSourceType triggerSource = ADC_TRIGG_SRC_HW;
	/* static uint8 loCurrentChShift = ADC_ZERO;*/
	uint8 loCurrentChShift = ZERO;
	triggerSource = Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupTriggSrc;						
	channelSum[groupId] =(uint8) (Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupDefinition.Num_Of_Channel);						  
	sampleNumber[groupId] = (uint8)(Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcStreamingNumSamples);

	if (ADC_ACCESS_MODE_SINGLE == Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupAccessMode)
	{
		/*If the mode is single, then run just once*/
		sampleNumber[groupId] = ONE;	
	}
	
	if (Lo_finish_sample < sampleNumber[groupId])
	{
		/*Both single mode and streaming mode are here*/
		if (((channelSum[groupId] - loCurrentChShift)/ONCE_MAX_ENTRY )!= ZERO)
		{
			/*Remaining channel is more than four*/
			for (j = ZERO; j < ONCE_MAX_ENTRY; j++)
			{
				EQADC.CFPR[groupId].R = Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].
				AdcGroupDefinition.AdcGroupCommandBuffer[loCurrentChShift + j].R;	
			}
			loCurrentChShift += ONCE_MAX_ENTRY;		
		}
		else
		{
			/* Remaining channel is no more than four */
			if (ZERO == (channelSum[groupId] - loCurrentChShift))
			{
				/* Only for channel number is Four */
				loCurrentChShift = ZERO;
				Lo_finish_sample++;
				
				/* Enable Fill command interrupt */
				EQADC.IDCR[groupId].B.CFFE = ONE;
				 	
				return;	
			}
			
			for (j = ZERO; j < ((channelSum[groupId] - loCurrentChShift)%ONCE_MAX_ENTRY); j++)	
			{
				EQADC.CFPR[groupId].R = Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].
				AdcGroupDefinition.AdcGroupCommandBuffer[loCurrentChShift + j].R;
			}
			
			if (ONE == sampleNumber[groupId])
			{	
				/* Only for single mode */
				Finish_Load_CFIFO[groupId] = TRUE;	
			}
			Lo_finish_sample++;		
			loCurrentChShift = ADC_ZERO;/*Reset it to zero*/
		}		
	}
	else
	{	
		/* All the command of the channel have been loaded */
		Lo_finish_sample = ADC_ZERO;
		Finish_Load_CFIFO[groupId] = TRUE;
		Adc_GroupStatus[groupId] = ADC_STREAM_COMPLETED;
		
		if ((TRUE == Adc_NotifictionEnable[groupId]) 
		&& (Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcNotification != NULL_PTR))
		{
			Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcNotification();
		}
		
		if (ADC_STREAM_BUFFER_LINEAR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcStreamingBufferMode)
		{
			/*
			 * If the buffer is linear,Stop transfer.If the buffer is circular,
			 * Continue transfer from the beginning
			 */
			EQADC.IDCR[groupId].B.CFFE = ZERO;		/*Stop Load command FIFO*/
			EQADC.IDCR[groupId].B.EOQIE = ZERO;	/*Stop Receive*/
			Final_EndOfQueue_Times[groupId] = Re_EndOfQueue_Times[groupId];
			return;
		}
		else
		{
			EQADC.IDCR[groupId].B.CFFE = ONE;
			Finish_Load_CFIFO[groupId] = FALSE;
			Adc_GroupStatus[groupId] = ADC_STREAM_COMPLETED;
			ReceiveIsr_index = ZERO;
			Final_EndOfQueue_Times[groupId] = Re_EndOfQueue_Times[groupId];
			Re_EndOfQueue_Times[groupId] = ZERO;
			return;		
		}	
		
	}
	
	if (ADC_TRIGG_SRC_SW == triggerSource)
	{
		/* 0x0410,Trigger the group using Single Scan SW mode */
		EQADC.CFCR[groupId].R = ADC_SSCAN;  	
	}
	else
	{ 	
		Adc_SetHwTrigEgde(groupId);    	
	}	
	
	EQADC.IDCR[groupId].R = ZERO;
	EQADC.IDCR[groupId].B.EOQIE = ONE;	/*Enable EOQ interrupt*/
	EQADC.IDCR[groupId].B.CFFE = ZERO; 	/*Disable Fill command interrupt*/		
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_HandlerIsr>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <groupId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/

#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_HandlerIsr(Adc_GroupType groupId)
{
	uint16 reCurrentChShift = ZERO;
	uint8  popIndex = ZERO;
	uint8  rfctrIndex = ZERO;
	uint32  j = ZERO;
	
	Adc_ResolutionType resolution = ADC_RESOLUTION_12BITS;
	/* Static uint16 stream_Data[HARDWARE_MAX_CHANNEL] = {ADC_ZERO};*/
	uint16 stream_Data[HARDWARE_MAX_CHANNEL] = {ZERO};
	/* Clear EOQ flag */
	EQADC.FISR[groupId].B.EOQF = ONE;

	Adc_DelayTime(500);
	/* Record this time valid channel amount arrived */
	rfctrIndex = EQADC.FISR[groupId].B.RFCTR;
	
	while (EQADC.FISR[groupId].B.RFCTR != ZERO)
	{
		/*
		 * RFCTR indicates the number of data stored in RFIFO,
		 * when RFIFO is read, it will be decremented by one
		 */
		resolution = Adc_ConfigPtr->AdcHwUnit->AdcChannel[Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].
			AdcGroupDefinition.AdcChannelIdList[reCurrentChShift + popIndex]].AdcChannelResolution;
		
		if (ADC_RESOLUTION_8BITS == resolution)
		{
			stream_Data[reCurrentChShift + popIndex] = (EQADC.RFPR[groupId].B.RFPOP)>>SIX;	
		}
		else if (ADC_RESOLUTION_10BITS == resolution)
		{
			stream_Data[reCurrentChShift + popIndex] = (EQADC.RFPR[groupId].B.RFPOP)>>FOUR;	
		}
		else
		{
			stream_Data[reCurrentChShift + popIndex] = (EQADC.RFPR[groupId].B.RFPOP)>>TWO;	
		}
		
		Adc_DelayTime(0x05);
		popIndex++;
	}
		
	if ((reCurrentChShift + rfctrIndex) >= channelSum[groupId])
	{
		/* All channels result have been transfered and saved successfullly */
		EQADC.IDCR[groupId].B.CFFE = ZERO; /*Disable Fill command interrupt*/			
		EQADC.IDCR[groupId].B.EOQIE = ZERO;/*Disable EOQ interrupt*/
		
		if (ADC_ACCESS_MODE_STREAMING == Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupAccessMode)
		{
			/* Streaming access mode,Copy received data to destiny Buffer */
			Re_EndOfQueue_Times[groupId]++;
			
			for (j = ADC_ZERO; j < channelSum[groupId]; j++)
			{	
				AdcResultBufferPointer[groupId][ReceiveIsr_index] = stream_Data[j];				
				ReceiveIsr_index+= sampleNumber[groupId];
			}
			
			ReceiveIsr_index = ZERO;
			ReceiveIsr_index += Re_EndOfQueue_Times[groupId];
			Adc_MemSet(stream_Data,0,HARDWARE_MAX_CHANNEL);	
		}
		else
		{
			/* Single access mode,Copy received data to destiny Buffer */
			for (j = ADC_ZERO; j < channelSum[groupId]; j++)
			{
				AdcResultBufferPointer[groupId][j] = stream_Data[j];			
			}
			Adc_MemSet(stream_Data,0,40);			
		}
		
		/* Reach the END of the channel queue, RESET it to ZERO */
		reCurrentChShift = ZERO;	
	}
	else
	{
		reCurrentChShift += rfctrIndex;
		Adc_LoadCommand_Hander(groupId);
		Adc_GroupStatus[groupId] = ADC_STREAM_COMPLETED;	
	}
			
	if (FALSE == Finish_Load_CFIFO[groupId])
	{
		/* Loading command has been finished */
		Adc_GroupStatus[groupId] = ADC_BUSY;		
		/* Enable Fill command interrupt */
		EQADC.IDCR[groupId].B.CFFE = ONE; 
		
	}
	
		EQADC.FISR[groupId].R = ZERO;//Clear int	
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DMA_DataHandler>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <groupId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
uint16 	Watch_Var;
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_DataHandler(Adc_GroupType groupId)
{
	/* Loop counter */
	uint16 i = ZERO; 
	/* Loop counter */
	uint16 j = ZERO;
	/* Space number */
	uint16 number = ZERO;
	/* Channel index */
	uint16 chIndex;
	/* List index */
	uint16 listIndex;
	P2VAR(uint16,AUTOMATIC,ADC_APPL_DATA) tempData;
	P2VAR(Adc_ValueGroupType,AUTOMATIC,ADC_APPL_DATA) resultBufferForRead;
	
	Adc_ValueGroupType resultBufferForTemp[50];
	
	Adc_ResolutionType resolution = ADC_RESOLUTION_12BITS;	
	
	EDMA.CERQR.R = groupId;
	
	channelSum[groupId] = (uint8)(Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupDefinition.Num_Of_Channel);						  
	sampleNumber[groupId] =(uint8)(Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcStreamingNumSamples);	
	resultBufferForRead = Adc_ReadBuffer[groupId];							
	number = channelSum[groupId] * sampleNumber[groupId];
	tempData = (uint16 *)malloc(number*sizeof(16));

	Adc_DelayTime(50);
	/* Generate DMA to move data from the system memory to CFIFOx. */  
	EQADC.IDCR[groupId].B.CFFS = ONE;
	/* Generate DMA to move data from RFIFOx to the system memory. */
	EQADC.IDCR[groupId].B.RFDS = ONE; 
	
	if (ADC_ACCESS_MODE_STREAMING == Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupAccessMode)
	{
		/* memcpy(temp_Data, AdcResultBufferPointer[groupId], Number*sizeof(uint16));*/
		Adc_MemCpy(tempData, AdcResultBufferPointer[groupId], number*sizeof(uint16));
		Adc_MemCpy(resultBufferForTemp, AdcResultBufferPointer[groupId], number*sizeof(uint16));
		for (j = ADC_ZERO; j < number; j++)
		{
			listIndex = number/sampleNumber[groupId];
			/* To store the data according to AutoSar requirement */
			chIndex = Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupDefinition.AdcChannelIdList[listIndex];
			
			if(chIndex > ADC_MIDCHNUM)
			{
				chIndex -= ADC_RSRVCHNUM;	
			}

			resolution = Adc_ConfigPtr->AdcHwUnit->AdcChannel[chIndex].AdcChannelResolution; 
			
			/* Adc_Group_0_ResultBufferForRead[i] = temp_Data[j] >> (14 - resolution);*/
			resultBufferForRead[i] = (uint16)(tempData[j] >> (14 - resolution));
			Watch_Var = resultBufferForRead[i];
		
			Watch_Var = Adc_Group_1_ResultBufferForRead[i];
			i += sampleNumber[groupId];
			
			if (j == (((Re_EndOfQueue_Times[groupId] + 1)*channelSum[groupId]) - ONE))
			{
				i = ADC_ZERO;
				Re_EndOfQueue_Times[groupId]++;
				i += Re_EndOfQueue_Times[groupId];
			}
		}
		Re_EndOfQueue_Times[groupId]++;	
	}
	else
	{
		/* memcpy(temp_Data, AdcResultBufferPointer[groupId], Number*sizeof(uint16));*/
		Adc_MemCpy(tempData, AdcResultBufferPointer[groupId], number*sizeof(uint16));
		Adc_MemCpy(resultBufferForTemp, AdcResultBufferPointer[groupId], number*sizeof(uint16));
		for (j = ADC_ZERO; j < number; j++)
		{
			listIndex = number/sampleNumber[groupId];
			/* To store the data according to AutoSar requirement */
			chIndex = Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupDefinition.AdcChannelIdList[listIndex];
			
			if(chIndex > ADC_MIDCHNUM)
			{
				chIndex -= ADC_RSRVCHNUM;	
			}

			resolution = Adc_ConfigPtr->AdcHwUnit->AdcChannel[chIndex].AdcChannelResolution; 
			
			/* Adc_Group_0_ResultBufferForRead[i] = temp_Data[j] >> (14 - resolution);*/
			resultBufferForRead[j] = (uint16)(tempData[j] >> (14 - resolution));
		}

	}
	
	Re_EndOfQueue_Times[groupId]--;
	Final_EndOfQueue_Times[groupId] = Re_EndOfQueue_Times[groupId];
	Adc_GroupStatus[groupId] = ADC_STREAM_COMPLETED;
	
	if ((TRUE == Adc_NotifictionEnable[groupId]) && (Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcNotification != NULL_PTR))
	{
		/* Call notification function */
		Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcNotification();
	}

	if (ADC_STREAM_BUFFER_LINEAR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcStreamingBufferMode)
	{
		/*
		 * If the buffer is linear,Stop transfer.If the buffer is circular,
		 * Continue transfer from the beginning
		 */
		Adc_GroupStatus[groupId] = ADC_STREAM_COMPLETED;

		if (tempData != NULL)
		{
			free(tempData);
			tempData = NULL;	
		}
		
		/* Disable Load command interrupt or DMA */
		EQADC.IDCR[groupId].B.CFFE = ZERO;		
		/* Disable DMA */
		EQADC.IDCR[groupId].B.RFDE = ZERO;		
		/* Clear flag interrupt for given DMA channel once */
		EDMA.CIRQR.R = 2*groupId + ONE;
		  
		return;
	}
	else
	{	
		if (ADC_CONV_MODE_ONESHOT != Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupConversionMode)
		{
			EDMA.SERQR.R = groupId*2;	
		}
	
		/* Generate DMA to move data from RFIFOx to the system memory.*/   			
		EQADC.IDCR[groupId].B.CFFS = ONE;	
		/* Generate DMA to move data from RFIFOx to the system memory.*/
		EQADC.IDCR[groupId].B.RFDS = ONE;		
		/* Enable Load command interrupt or DMA */
		EQADC.IDCR[groupId].B.CFFE = ONE;		
		/* Enable DMA */
		EQADC.IDCR[groupId].B.RFDE = ONE;
		Final_EndOfQueue_Times[groupId] = Re_EndOfQueue_Times[groupId];
		Adc_GroupStatus[groupId] = ADC_STREAM_COMPLETED;
	
		/* Disable Major interrupt.*/
		Dma_SetChannelMajorInterrupt((Dma_ChannelType)(2*groupId + ADC_ONE), DMA_CHANNELMAJORINTERRUPT_DISABLE);
		
		Final_EndOfQueue_Times[groupId] = Re_EndOfQueue_Times[groupId];
		Re_EndOfQueue_Times[groupId] = ZERO;			
	
		if (tempData != NULL)
		{
			free(tempData);
			tempData = NULL;	
		}
		
		/* Clear flag interrupt for given DMA channel once */	
		EDMA.CIRQR.R = 2*groupId + ONE;
		 
		return;
					
	}
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_SetHwTrigEgde>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <groupId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_SetHwTrigEgde(Adc_GroupType groupId)
{
	Adc_HwTriggerSignalType hwTrigSignal;
	
	hwTrigSignal = Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcHwTrigSignal;	
	
	/* For Hardware trigger */
	switch (hwTrigSignal)
	{
		case ADC_HW_TRIG_FALLING_EDGE:
			 
			if (ADC_CONV_MODE_ONESHOT == Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupConversionMode)
			{
				EQADC.CFCR[groupId].R = ADC_FEDGE_ONESHOT;
			}
			else	/* For continuous scan */
			{
				EQADC.CFCR[groupId].R = ADC_FEDGE_CONTINU;	
			}
			break;
		
		case ADC_HW_TRIG_RISING_EDGE:

			if (ADC_CONV_MODE_ONESHOT == Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupConversionMode) 
			{
				EQADC.CFCR[groupId].R = ADC_REDGE_ONESHOT;			
			}
			else	/* For continuous scan */
			{
				EQADC.CFCR[groupId].R = ADC_REDGE_CONTINU;
			}
			break;

		case ADC_HW_TRIG_BOTH_EDGES:
		
			if (ADC_CONV_MODE_ONESHOT == Adc_ConfigPtr->AdcHwUnit->AdcGroup[groupId].AdcGroupConversionMode)
			{
				EQADC.CFCR[groupId].R = ADC_BEDGE_ONESHOT;	
			}
			else	/* For continuous scan */
			{
				EQADC.CFCR[groupId].R = ADC_BEDGE_CONTINU;
			}
			break;
			
		default: 
			break;
	}

	return;
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_MemSet>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <tim>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void,ADC_PUBLIC_CODE)Adc_MemSet(P2VAR(uint16, AUTOMATIC, ADC_APPL_CONST) TargetAddr,uint16 Value,uint16 Length)
{
	uint8 loopCnt1;
	
	/* Set the memory use the Value */
	for(loopCnt1 = ZERO; loopCnt1 < Length; loopCnt1++)
	{
		*TargetAddr = ZERO;
		TargetAddr++;	
	}
	
	return;
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_MemCpy>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <tim>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void,ADC_PUBLIC_CODE)Adc_MemCpy(P2VAR(uint16, AUTOMATIC, ADC_APPL_CONST)TargetAddr,
							P2VAR(uint16, AUTOMATIC, ADC_APPL_CONST)SrcAddr,uint16 Length)
{
	uint16 loopCnt2;
	
	/* Copy the data from SrcAddr to the TargerAddr */
	for (loopCnt2 = ZERO; loopCnt2 < Length; loopCnt2++)
	{
		*TargetAddr = *SrcAddr;
		TargetAddr++;
		SrcAddr++;	
	}
	
	return;
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_DelayTime>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <tim>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_DelayTime(uint32 tim)
{
	uint32 loopCnt;
	for (loopCnt = ZERO; loopCnt <tim;loopCnt++)	
	{
		/* Wait a short moment */
		/* asm("nop"); */	
	}
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/*=======[E N D   O F   F I L E]==============================================*/
