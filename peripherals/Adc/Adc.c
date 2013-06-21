/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <filename>
 *  @brief      <Briefly describe file(one line)>
 *  
 *  <Compiler: cw2.6   MCU:mpc5634>
 *  
 *  @author     <author name>
 *  @date       <yyyy-mm-dd>
 */
/*============================================================================*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20081127   XXX       Initial version
 * 
 *  V1.1.0       20091012   XXX     
 * 
 *  V2.0.0       20100210   XXX        
 */
/*============================================================================*/
/*=======[M I S R A  R U L E  V I O L A T I O N]==============================*/
/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 17.4; REFERENCE - ISO:C90-6.3.6 Additive Operators - Constraints */
/* MISRA-C:2004 Rule 1.1 */

/*=======[I N C L U D E S]====================================================*/
#include "Adc.h"
#include "irq_defines.h"
#include "Modules.h"
#include "Det.h"
#include "Dma.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/

/* AUTOSAR specification version information */
#define ADC_C_AR_MAJOR_VERSION    3
#define ADC_C_AR_MINOR_VERSION    0
#define ADC_C_AR_PATCH_VERSION    3

/* File version information */
#define ADC_C_SW_MAJOR_VERSION    1
#define ADC_C_SW_MINOR_VERSION    0
#define ADC_C_SW_PATCH_VERSION	  0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (ADC_AR_MAJOR_VERSION != ADC_C_AR_MAJOR_VERSION) 
#error "Adc.c : Mismatch in Specification Major Version"
#endif/* End the #if (ADC_AR_MAJOR_VERSION != ADC_C_AR_MAJOR_VERSION) */

#if (ADC_AR_MINOR_VERSION != ADC_C_AR_MINOR_VERSION)
#error "Adc.c : Mismatch in Specification Minor Version"
#endif/* End the #if (ADC_AR_MINOR_VERSION != ADC_C_AR_MINOR_VERSION) */

#if (ADC_AR_PATCH_VERSION != ADC_C_AR_PATCH_VERSION)
#error "Adc.c : Mismatch in Specification Patch Version"
#endif/* End the #if (ADC_AR_PATCH_VERSION != ADC_C_AR_PATCH_VERSION) */

#if (ADC_SW_MAJOR_VERSION != ADC_C_SW_MAJOR_VERSION)
#error "Adc.c : Mismatch in Major Version"
#endif/* End the #if (ADC_SW_MAJOR_VERSION != ADC_C_SW_MAJOR_VERSION) */

#if (ADC_SW_MINOR_VERSION != ADC_C_SW_MINOR_VERSION)
#error "Adc.c : Mismatch in Minor Version"
#endif/* End the #if (ADC_SW_MINOR_VERSION != ADC_C_SW_MINOR_VERSION) */

#if (ADC_SW_PATCH_VERSION != ADC_C_SW_PATCH_VERSION)
#error "Adc.c : Mismatch in Patch Version"
#endif/* End the #if (ADC_SW_PATCH_VERSION != ADC_C_SW_PATCH_VERSION) */
/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/
/* Not configurable data,which is used to record the attribute of
 * notification for all groups.
 */
VAR(uint8,ADC_APPL_DATA) Adc_NotifictionEnable[ADC_SUM_OF_GROUP]=
{
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE
};

/* Not configurable data,which is used to record the status value for
 * all groups.
 */
VAR(Adc_StatusType,ADC_APPL_DATA) Adc_GroupStatus[ADC_SUM_OF_GROUP]=
{
	ADC_IDLE,
	ADC_IDLE,
	ADC_IDLE,
	ADC_IDLE,
	ADC_IDLE,
	ADC_IDLE
};

/* Store the group buffer status */
VAR(Adc_StatusType,ADC_APPL_DATA) Adc_BufferStatus[ADC_SUM_OF_GROUP] =
{
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE	
};

VAR(uint8,ADC_APPL_DATA) Adc_GrpResult[ADC_SUM_OF_GROUP] =
{
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE	
};

/* In AutoSar specification,there is no this configurable data.	As a result,
 * the user could configure it in this source file.
 */
VAR(Adc_CalibrationType, ADC_APPL_DATA) Adc_ChannelCalibrationEnable[44]=
{
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,	
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED,
	ADC_CALIBRATION_DISABLED
};

/* Pointer to configuration structure. */
P2CONST(Adc_ConfigType,AUTOMATIC,ADC_APPL_CONST) Adc_ConfigPtr;

/* Not configurable data,which is used to record whether the conversion has been started 
 * for all groups.
 */
VAR(boolean,ADC_APPL_DATA) Adc_ConversionStarted[ADC_SUM_OF_GROUP];
/* Not configurable data,which is used to record whether the module has been initialised.*/
VAR(boolean,ADC_APPL_DATA) Adc_InitFlag = STD_OFF;
/* Not configurable data,which is used to point to the result buffer.*/
P2VAR(Adc_ValueGroupType,AUTOMATIC,ADC_APPL_DATA) Adc_ResultBufferPtr[ADC_SUM_OF_GROUP];
/* Not configurable data,which is used to signal whether hardware triggered occures.*/  
VAR(boolean,ADC_APPL_DATA) Adc_HWTriggered[ADC_SUM_OF_GROUP];
/* Store the group id */
VAR(Adc_GroupType,ADC_APPL_DATA) Adc_Group;
/*=======[I N T E R N A L   D A T A]==========================================*/
STATIC VAR(boolean,ADC_APPL_DATA) flag = FALSE;
	
/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/* Configure the adc for conversion */
STATIC FUNC(void,ADC_PUBLIC_CODE) Adc_ConfigureEQADC(P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr);
/* Write the adc register */
STATIC FUNC(void,ADC_PUBLIC_CODE) Adc_WriteEQADCRegister(uint32 hwUintId,Adc_EQADCRegisterType reg, Adc_EQADCRegister value);	
/* Enable irq */					
STATIC FUNC(void,ADC_PUBLIC_CODE) Adc_Enable_Irq(void);
/* Configure the int for DMA */
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_ConfigureInterruptORDMA(Adc_GroupType group);
/* Configure the queue */
STATIC FUNC(void,ADC_PUBLIC_CODE) Adc_Config_Queue(P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr);
/* Delete the hard setting */
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_DelHardConfig(void);
/* Enable the hw trigger */
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_EnableHwTriConfig(Adc_GroupType group);
/* Disable the hw trigger */
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_DisableHwTrConfig(Adc_GroupType group);
/* Set the hw for start conversion */
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_StartGpConvHwConfig(Adc_GroupType group);

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/*
 * Brief               <Adc_Init>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
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
FUNC(void,ADC_PUBLIC_CODE) Adc_Init(P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr) 
{	
	/* ADC250 ADC365 ADC054 ADC342 ADC056 */
	Adc_GroupType group;
	
	#if (STD_ON == ADC_DEV_ERROR_DETECT)
	/* ADC107 */
	if (STD_ON == Adc_InitFlag)
	{
		/* Report Error to Det */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_INIT_ID,ADC_E_ALREADY_INITIALIZED);
		return ;
	}		 
	/* ADC343 ADC344 */
	if (NULL_PTR == ConfigPtr)
	{
		/* Report Error to det */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_INIT_ID,ADC_E_PARAM_CONFIG);
		return ;
	}
	#endif /* End the #if (STD_ON == ADC_DEV_ERROR_DETECT) */
	/* Store the location of the configuration data */
	Adc_ConfigPtr = ConfigPtr;
	Adc_Config_Queue(ConfigPtr);
	/* Enable ADC.*/
	Adc_ConfigureEQADC(ConfigPtr);
	for (group = ADC_ZERO; group < ADC_SUM_OF_GROUP; group++)
	{
		Adc_HWTriggered[group] = FALSE; 	/* ADC077/1 */
		Adc_NotifictionEnable[group] = FALSE;	/* ADC077/2 */
		Adc_GroupStatus[group] = ADC_IDLE;	/* ADC307   */	
	}

	Adc_InitFlag = STD_ON;
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_SetupResultBuffer>
 * ServiceId           <0x0C>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group and DataBufferPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <returnValue>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_SetupResultBuffer
	(Adc_GroupType group,P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr)
{
	/* ADC419 */
	Std_ReturnType returnValue;
	
	#if (STD_ON == ADC_DEV_ERROR_DETECT)
	/* ADC421 */
	if ((STD_ON != Adc_InitFlag))
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_SETUPRESULTBUFFER_ID,ADC_E_UNINIT);
		return E_NOT_OK;
	}
	
	/* ADC423 */
	if (group >= ADC_SUM_OF_GROUP)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_SETUPRESULTBUFFER_ID,ADC_E_PARAM_GROUP);
		return E_NOT_OK;
	}
	
	if (NULL_PTR == DataBufferPtr)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_SETUPRESULTBUFFER_ID,ADC_E_PARAM_POINTER);
		return E_NOT_OK;			
	}	
	#endif/* end the #if(STD_ON == ADC_DEV_ERROR_DETECT) */
	
	/* ADC420 ADC423 */
	Adc_ResultBufferPtr[group] = DataBufferPtr;
	Adc_BufferStatus[group] = TRUE;
	returnValue = E_OK;

	return (returnValue);
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_GetStreamLastPointer>
 * ServiceId           <0x0B>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <PtrToSamplePtr (pointer of Adc_ValueGroupType)>
 * Param-Name[in/out]  <None>
 * Return              <Adc_StreamNumSampleType>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"                            
FUNC(Adc_StreamNumSampleType, ADC_PUBLIC_CODE) Adc_GetStreamLastPointer
	(Adc_GroupType group, P2VAR(P2VAR(Adc_ValueGroupType,AUTOMATIC, ADC_APPL_DATA), 
		AUTOMATIC,ADC_APPL_DATA) PtrToSamplePtr)                                
{
	/* ADC375 */
	if (ADC_BUSY == Adc_GroupStatus[group])
	{
		/* Report Error to DET */
		PtrToSamplePtr = NULL_PTR;      
		return ZERO;
	}

	#if (STD_ON == ADC_DEV_ERROR_DETECT)
	if (STD_OFF == Adc_InitFlag)
	{
		/* Report Error to DET */
		PtrToSamplePtr = NULL_PTR;          	
		Det_ReportError(MODULE_ID_ADC, ADC_INSTANCE_ID, ADC_GETSTREAMLASTPOINTER_ID, ADC_E_UNINIT);
		return ADC_ZERO;
	}
	else if (!(group < ADC_SUM_OF_GROUP))
	{
		/* Report Error to DET */
		PtrToSamplePtr = NULL_PTR;          	
		Det_ReportError(MODULE_ID_ADC, ADC_INSTANCE_ID, ADC_GETSTREAMLASTPOINTER_ID, ADC_E_PARAM_GROUP );    					
		return ADC_ZERO;
	}
	else if ((Adc_GroupStatus[group])&&((boolean)FALSE == Adc_ConversionStarted[group]))
	{
		/* Report Error to DET */
		PtrToSamplePtr = NULL_PTR;          	
		Det_ReportError(MODULE_ID_ADC, ADC_INSTANCE_ID, ADC_GETSTREAMLASTPOINTER_ID, ADC_E_IDLE);    					
		return ADC_ZERO;
	}  
	else
	{
		/* Blank */
	}
	#endif	/* End the	#if(STD_ON == ADC_DEV_ERROR_DETECT) */
	
	if ((((ADC_CONV_MODE_CONTINUOUS == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupConversionMode) 
	&&  (ADC_STREAM_BUFFER_CIRCULAR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcStreamingBufferMode)) 
	||  ((ADC_TRIGG_SRC_HW == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupTriggSrc) 
	&&  (ADC_STREAM_BUFFER_CIRCULAR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcStreamingBufferMode))) 
	&&  (ADC_STREAM_COMPLETED  == Adc_GroupStatus[group]))
	{
		/* ADC326 */
		Adc_GroupStatus[group] = ADC_BUSY;
	}
	else if ((ADC_STREAM_BUFFER_LINEAR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcStreamingBufferMode) 
	&& (ADC_STREAM_COMPLETED  == Adc_GroupStatus[group]))
	{
		/* ADC327 */
		Adc_GroupStatus[group] = ADC_IDLE;
	}
	else if	(ADC_COMPLETED == Adc_GroupStatus[group])
	{
		/* ADC328 */
		Adc_GroupStatus[group] = ADC_BUSY;
	}
	else
	{
		/* Blank */
	}

	/* ADC387 */
	*(Adc_ResultBufferPtr[group]) += (uint16)(Re_EndOfQueue_Times[group] - ADC_ONE);	
	/* ADC214 ADC418 */
	*PtrToSamplePtr = Adc_ResultBufferPtr[group];
	/* Return number of valid samples per channel.*/
	return (uint8)(Re_EndOfQueue_Times[group]); 
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ReadGroup>
 * ServiceId           <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group and DataBufferPtr>      
 * Param-Name[out]     <PtrToSamplePtr (pointer of Adc_ValueGroupType)>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/

#define ADC_START_SEC_CODE
#include "MemMap.h"
/* ADC359 */
#if (STD_ON == ADC_READ_GROUP_API) 
FUNC(Std_ReturnType, ADC_PUBLIC_CODE)Adc_ReadGroup (Adc_GroupType group,
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) dataBufferPtr) 
{
	/* ADC369 */
	P2VAR(Adc_ValueGroupType,AUTOMATIC,ADC_APPL_DATA) resultBufferForRead;
	Std_ReturnType returnValue;
	uint16 channel;
	uint8 i;
	
	#if (ADC_DEV_ERROR_DETECT == STD_ON)		
	/* ADC296 */
	if (STD_OFF == Adc_InitFlag)
	{  	
		Det_ReportError(MODULE_ID_ADC, ADC_INSTANCE_ID, ADC_READGROUP_ID, ADC_E_UNINIT);
		return E_NOT_OK;
	}	
	/* ADC152 */
	if(group >= ADC_SUM_OF_GROUP)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_READGROUP_ID,ADC_E_PARAM_GROUP);
		return E_NOT_OK;
	}
	/* ADC388 */ 								         
	if ((ADC_IDLE == Adc_GroupStatus[group]) 
		&& ((boolean)FALSE) == Adc_ConversionStarted[group])
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_READGROUP_ID,ADC_E_IDLE);  
		return E_NOT_OK;			
	}

	#endif /* End the #if (ADC_DEV_ERROR_DETECT == STD_ON) */
	
	
	/* ADC122 ADC075 ADC113 */
	if ((((ADC_CONV_MODE_CONTINUOUS == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupConversionMode) 
	&&  (ADC_STREAM_BUFFER_CIRCULAR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcStreamingBufferMode)) 
	||  ((ADC_TRIGG_SRC_HW == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupTriggSrc) 
	&&  (ADC_STREAM_BUFFER_CIRCULAR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcStreamingBufferMode ))) 
	&&  (ADC_STREAM_COMPLETED == Adc_GroupStatus[group]))
	{
		/* ADC329 */
		Adc_GroupStatus[group] = ADC_BUSY;
		returnValue = E_OK;
	}
	else if	(ADC_COMPLETED == Adc_GroupStatus[group])
	{
		/* ADC331. */
		Adc_GroupStatus[group] = ADC_BUSY;
		returnValue = E_OK;
	}
	else if ((ADC_STREAM_BUFFER_LINEAR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcStreamingBufferMode) 
	&& (ADC_STREAM_COMPLETED == Adc_GroupStatus[group]))
	{
		/* ADC330. */
		Adc_GroupStatus[group] = ADC_IDLE;
		returnValue = E_OK;
	}
	else
	{
		/* Keep status. */
		returnValue = E_OK;
	}
	
	if (E_OK == returnValue)
	{
		resultBufferForRead = Adc_ReadBuffer[group];
		if (ADC_ACCESS_MODE_SINGLE == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupAccessMode)
		{
			/* Copy the result to application buffer. */
			for (channel = ZERO;channel < Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupDefinition.Num_Of_Channel;channel++)
			{
				/* Copy the data */
				dataBufferPtr[channel] = resultBufferForRead[channel];
			}
		}
		else if (ADC_ACCESS_MODE_STREAMING == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupAccessMode)
		{

			
			/* Copy the result to application buffer. */
			for (channel = ZERO; channel < Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupDefinition.Num_Of_Channel; channel++)
			{
				if (ADC_DMA == Adc_GroupInterruptOrDma[group])
				{
					dataBufferPtr[channel] = resultBufferForRead[(channel + ADC_ONE) * Final_EndOfQueue_Times[group] - ADC_ONE];
				}
				else
				{
					dataBufferPtr[channel] = 
						AdcResultBufferPointer[group][(channel + ADC_ONE) * Final_EndOfQueue_Times[group] - ADC_ONE];	
				} 
			}
		}
		else
		{
			/* Blank */
		}
	}
	
	if ((ADC_DMA == Adc_GroupInterruptOrDma[group]) 
	&& (ADC_STREAM_BUFFER_CIRCULAR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcStreamingBufferMode))
	{
		/* Enable Major interrupt.*/
		Dma_SetChannelMajorInterrupt((Dma_ChannelType)(2*group +1), DMA_CHANNELMAJORINTERRUPT_ENABLE);
	}

	Adc_GrpResult[group] = TRUE;
	return (returnValue);
}
#endif/* End the #if (STD_ON == ADC_READ_GROUP_API) */
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_GetGroupStatus>
 * ServiceId           <0x09>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Adc_StatusType>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(Adc_StatusType,ADC_PUBLIC_CODE) Adc_GetGroupStatus(Adc_GroupType group)
{	
	/* ADC305 ADC374 */
	Adc_StatusType  returnValue;
	
	#if (STD_ON == ADC_DEV_ERROR_DETECT)
	/* ADC301 */
	if (STD_OFF == Adc_InitFlag)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_GETGROUPSTATUS_ID,ADC_E_UNINIT);
		return E_NOT_OK;
	}
	/* ADC225 */
	if (group >= ADC_SUM_OF_GROUP)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_GETGROUPSTATUS_ID,ADC_E_PARAM_GROUP);
		return E_NOT_OK;
	}	
	#endif/* end the #if(STD_ON == ADC_DEV_ERROR_DETECT) */

	/* ADC224 ADC325 ADC226 ADC220 ADC221 ADC222 */
	returnValue = Adc_GroupStatus[group];
	return (returnValue);
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_StartGroupConversion>
 * ServiceId           <0x02>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
/* ADC259 ADC260 */
#if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API) 
FUNC(void, ADC_PUBLIC_CODE) Adc_StartGroupConversion(Adc_GroupType group)
{   
	/* ADC146 ADC367 ADC156	*/
	#if (STD_ON == ADC_DEV_ERROR_DETECT)
	/* ADC294 */
	if (Adc_InitFlag != STD_ON)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_STARTGROUPCONVERSION_ID,ADC_E_UNINIT);
		return ;
	}
	/* ADC125 */
	if (group >= ADC_SUM_OF_GROUP)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_STARTGROUPCONVERSION_ID,ADC_E_PARAM_GROUP);
		return ;	
	}	
	
	if (FALSE == Adc_BufferStatus[group])
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_STARTGROUPCONVERSION_ID,ADC_E_BUFFER_UNINIT);
		return ;
	}
	/* ADC427 ADC351 ADC428 ADC346 ADC156 ADC348 */
	if (!((ADC_STREAM_COMPLETED == Adc_GroupStatus[group]) 
										|| (ADC_IDLE == Adc_GroupStatus[group])))
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_STARTGROUPCONVERSION_ID,ADC_E_BUSY);
		return ;
	}
	
	/* ADC146 ADC133 */
	if (ADC_TRIGG_SRC_SW != Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupTriggSrc)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_STARTGROUPCONVERSION_ID,ADC_E_WRONG_TRIGG_SRC);
		return ;	
	}	
	#endif /* End the #if(STD_ON == ADC_DEV_ERROR_DETECT) */
	Adc_Group = group;					                                        
	Adc_StartGpConvHwConfig(group);
  						                                        			
}
#define ADC_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_StopGroupConversion>
 * ServiceId           <0x03>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_StopGroupConversion(Adc_GroupType group)
{
	/* ADC368 */
	#if (STD_ON == ADC_DEV_ERROR_DETECT)
	/* ADC295 */
	if (STD_OFF == Adc_InitFlag)
	{
		/* Report Error to det */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_STOPGROUPCONVERSION_ID,ADC_E_UNINIT);
		return ;
	}
						   
	/* ADC126,Wrong group ID */
	if (group >= ADC_SUM_OF_GROUP)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_STOPGROUPCONVERSION_ID,ADC_E_PARAM_GROUP);
		return ;
	}
	
	/* ADC283 ADC164 */						                                   
	if (Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupTriggSrc!=ADC_TRIGG_SRC_SW)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_STOPGROUPCONVERSION_ID,ADC_E_WRONG_TRIGG_SRC);
		return ;	
	}
	
	/* ADC241 */
	if (ADC_IDLE == Adc_GroupStatus[group])
	{
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_STOPGROUPCONVERSION_ID,ADC_E_IDLE);
		return ;
	}	
	#endif/* End the #if(STD_ON == ADC_DEV_ERROR_DETECT) */
	
	/* ADC386 ADC360 ADC385 */
	Adc_GroupStatus[group] = ADC_IDLE;
	EQADC.IDCR[group].B.RFOIE = ADC_ZERO;
	EQADC.IDCR[group].B.RFDE = ADC_ZERO;
	#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	/* ADC155 */
	Adc_NotifictionEnable[group] = FALSE;
	#endif/* End the #if (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
	
}
#endif/*End the #if (STD_ON == ADC_ENABLE_START_STOP_GROUP_API) */
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_EnableGroupNotification>
 * ServiceId           <0x07>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
/* ADC100 ADC101 */
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY) 
FUNC(void, ADC_PUBLIC_CODE) Adc_EnableGroupNotification(Adc_GroupType group)
{	
	/* ADC372 */
	#if (STD_ON == ADC_DEV_ERROR_DETECT)
	/* ADC299*/
 	if (STD_OFF == Adc_InitFlag)
	{
		/* Report Error to det */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_ENABLEGROUPNOTIFICATION_ID,ADC_E_UNINIT);
		return ;
	}
 
	/* ADC130*/
	if (group >= ADC_SUM_OF_GROUP)
	{
		/* Report Error */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_ENABLEGROUPNOTIFICATION_ID,ADC_E_PARAM_GROUP);
		return ;
	}

	/* ADC165 */
	if (NULL_PTR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcNotification)
	{
		/* Report error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_ENABLEGROUPNOTIFICATION_ID,ADC_E_NOTIF_CAPABILITY);
		return ;
	}	
	#endif /* End the #if(STD_ON == ADC_DEV_ERROR_DETECT) */
	/* ADC057 */  
	Adc_NotifictionEnable[group] = FALSE; 

}
#endif/* End the #if (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DisableGroupNotification>
 * ServiceId           <0x08>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
FUNC(void, ADC_PUBLIC_CODE) Adc_DisableGroupNotification(Adc_GroupType group)
{
	/* ADC373 */
	#if (STD_ON == ADC_DEV_ERROR_DETECT)	
	if (STD_OFF == Adc_InitFlag)
	{
		/* Report Error to det */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DISABLEGROUPNOTIFICATION_ID,ADC_E_UNINIT);
		return ;
	}	  
	/* ADC300*/
	if (group >= ADC_SUM_OF_GROUP)
	{
		/* Report Error */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DISABLEGROUPNOTIFICATION_ID,ADC_E_PARAM_GROUP);
		return ;
	}
	/* ADC166 */
	if (NULL_PTR == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcNotification)
	{
		/* Report error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DISABLEGROUPNOTIFICATION_ID,ADC_E_NOTIF_CAPABILITY);
		return ;	
	}	
	#endif/* End the #if(STD_ON == ADC_DEV_ERROR_DETECT) */
	 
	/* ADC058 */				
	Adc_NotifictionEnable[group] = FALSE;   
}
#endif/*End the #if (STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_EnableHardwareTrigger>
 * ServiceId           <0x05>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
#if (STD_ON == ADC_HW_TRIGGER_API) /* ADC265 ADC266 */
FUNC(void, ADC_PUBLIC_CODE) Adc_EnableHardwareTrigger(Adc_GroupType group) 
{	
	#if (ADC_DEV_ERROR_DETECT == STD_ON)	
	/* ADC297 */
 	if (STD_OFF == Adc_InitFlag)
	{
		/* Report Error to det */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_ENABLEHARDWARETRIGGER_ID,ADC_E_UNINIT);
		return ;
	}
	
	/* ADC128 */
	if (group >= ADC_SUM_OF_GROUP)
	{
		/* Report Error */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_ENABLEHARDWARETRIGGER_ID,ADC_E_PARAM_GROUP);
		return ;
	}

	/* ADC136 */
	if (ADC_TRIGG_SRC_HW != Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupTriggSrc)
	{
		/* Report Error to DET */
		Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID,ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_WRONG_CONV_MODE);
		return;	
	}
		   	
	/* ADC321 */					   
	if (!((ADC_STREAM_COMPLETED == Adc_GroupStatus[group])|| \
								(ADC_IDLE == Adc_GroupStatus[group])))
	{
		/* Report Error to DET */
		Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID,	ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUSY);
		return ;	
	}
	
	/* ADC425 */							
	if (E_OK != Adc_SetupResultBuffer (group, AdcResultBufferPointer[group]))
	{
		/* Report Error to DET */
		Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID,	ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUFFER_UNINIT);
		return ;
	}

	/* ADC349 */							   
	if ((boolean)TRUE == Adc_HWTriggered[group])
	{
		/* Report Error to DET */
		Det_ReportError(ADC_MODULE_ID, ADC_INSTANCE_ID,	ADC_ENABLEHARDWARETRIGGER_ID, ADC_E_BUSY);
		return ;		
	}	
	#endif /* End the #if(STD_ON == ADC_DEV_ERROR_DETECT) */

	if (ADC_TRIGG_SRC_SW == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupTriggSrc)     
	{
		/* ADC120 */
		return;
	}
	
	Adc_Group = group;
	Adc_EnableHwTriConfig(group);	
	Adc_ConversionStarted[group] = TRUE;
	Adc_HWTriggered[group] = TRUE;
}
#endif/* End the #if (STD_ON == ADC_HW_TRIGGER_API) */
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DisableHardwareTrigger>
 * ServiceId           <0x06>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_DisableHardwareTrigger(Adc_GroupType group) 
{
	/* ADC371 */
	#if (STD_ON == ADC_DEV_ERROR_DETECT)	 
	/* ADC298*/
 	if (STD_OFF == Adc_InitFlag)
	{
		/* Report Error to det */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DISBALEHARDWARETRIGGER_ID,ADC_E_UNINIT);
		return ;
	}

	/* ADC129*/
	if (group >= ADC_SUM_OF_GROUP)
	{
		/* Report Error */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DISBALEHARDWARETRIGGER_ID,ADC_E_PARAM_GROUP);
		return ;
	}
	
	/* ADC137 */
	if (ADC_TRIGG_SRC_HW != Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupTriggSrc)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DISBALEHARDWARETRIGGER_ID,ADC_E_WRONG_TRIGG_SRC);
		return ;
	}
	
	/* ADC304 */ 
	if ((boolean)FALSE == Adc_HWTriggered[group])
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DISBALEHARDWARETRIGGER_ID,ADC_E_IDLE);
		return;
	}
			
	/* ADC282 */
	if (ADC_CONV_MODE_CONTINUOUS == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupConversionMode)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DISBALEHARDWARETRIGGER_ID,ADC_E_WRONG_CONV_MODE);
		return;	
	}	
	#endif/* End the #if(STD_ON == ADC_DEV_ERROR_DETECT) */
	
	/* ADC121 */
	if (ADC_TRIGG_SRC_SW == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupTriggSrc)
	{
		return;
	}
	
	Adc_DisableHwTrConfig(group);
	#if (STD_ON == ADC_GRP_NOTIF_CAPABILITY)
	Adc_NotifictionEnable[group] = FALSE;	/* ADC157 */
	#endif /* End the #if(STD_ON == ADC_GRP_NOTIF_CAPABILITY) */
	Adc_GroupStatus[group] = ADC_IDLE;  /* ADC361 */
	Adc_HWTriggered[group] = FALSE;
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DisableGroupNotification>
 * ServiceId           <0x08>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
#if (STD_ON == ADC_DEINIT_API)	/*  ADC228 */
FUNC(void, ADC_PUBLIC_CODE) Adc_DeInit(void) 
{	
	/* ADC366 */
	Adc_GroupType group;
 	
	#if (STD_ON == ADC_DEV_ERROR_DETECT) 	
	/* ADC154 */
	if(STD_ON != Adc_InitFlag)
	{
		/* Report to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DEINIT_ID,ADC_E_UNINIT);
	
	}
	
	for (group = ADC_GROUP0; group < ADC_SUM_OF_GROUP; group++)
	{
		if((Adc_GroupStatus[group] != ADC_IDLE)&&\
			(Adc_GroupStatus[group] != ADC_STREAM_COMPLETED))
		{
			/* Report Error to DET */
			Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_DEINIT_ID,ADC_E_BUSY);
			return ;
		}
	}	
	#endif/* End the #if (STD_ON == ADC_DEV_ERROR_DETECT) */
	
	if (STD_ON == Adc_InitFlag) 
	{
		/* Delete the hard config */
		Adc_DelHardConfig();
	}
	
	for (group = ADC_GROUP0; group < ADC_SUM_OF_GROUP; group++)
	{
		/* ADC358 */
		Adc_GroupStatus[group] = ADC_IDLE;
		/* ADC111*/
		Adc_NotifictionEnable[group] = FALSE;	
		Adc_HWTriggered[group] = FALSE;
		Adc_ConversionStarted[group] = FALSE;
		Adc_BufferStatus[group] = FALSE;
	}
	
	/* Clean internal status. */   
	Adc_ConfigPtr = (Adc_ConfigType *)NULL_PTR;
	Adc_InitFlag = STD_OFF;
	
	return;
}
#endif/* End the #if (STD_ON == ADC_DEINIT_API) */
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

#if (STD_ON == ADC_VERSION_API)
/******************************************************************************/
/*
 * Brief               <Adc_GetVersionInfo>
 * ServiceId           <0x0A>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <Group>      
 * Param-Name[out]     <versioninfo>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ADC_PUBLIC_CODE) Adc_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC,ADC_APPL_DATA)versionInfo) 
{
	#if (STD_ON == ADC_DEV_ERROR_DETECT)
	if (NULL_PTR == versionInfo)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_GETVERSIONINFO_ID,ADC_E_PARAM_POINTER);
	}
	else if (FALSE == Adc_InitFlag)
	{
		/* Report Error to DET */
		Det_ReportError(MODULE_ID_ADC,ADC_INSTANCE_ID,ADC_GETVERSIONINFO_ID,ADC_E_UNINIT);
	}
	else	
	#endif/* End the #if(STD_ON == ADC_DEV_ERROR_DETECT) */
	{
		/* Copy the vendor Id */
		versionInfo->vendorID = ADC_VENDOR_ID;
		/* Copy the module Id */
		versionInfo->moduleID = ADC_MODULE_ID;
		/* Copy the instance Id */
		versionInfo->instanceID = ADC_INSTANCE_ID;
		/* Copy Software Major Version */
		versionInfo->sw_major_version = ADC_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versionInfo->sw_minor_version = ADC_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versionInfo->sw_patch_version = ADC_SW_PATCH_VERSION;
	}
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (ADC_VERSION_INFO_API == STD_ON) */

/*=======[	L O C A L  	F U N C T I O N S]====================================*/
/******************************************************************************/
/*
 * Brief               <Adc_Config_Queue>
 * ServiceId           <0x0A>
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
STATIC FUNC(void,ADC_PUBLIC_CODE) Adc_Config_Queue(P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr) 
{
	Adc_GroupType group;
	uint16 channel;
	Adc_ChannelType channelId;	
	uint32  hwUnitId;
	Adc_AlternateConfigType  cmd;
	uint16 adcGain;
	P2VAR(Adc_AlternateConfigType, AUTOMATIC, ADC_APPL_DATA) commandQueue; 

	hwUnitId =  ConfigPtr->AdcHwUnit->AdcHwUnitId;
	/* Start configuring the eQADC queues */
	for (group = ADC_ZERO; group < ADC_SUM_OF_GROUP; group++)
	{
		/* Loop through all channels and make the command queue. */
		for (channel = ZERO; channel < ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupDefinition.Num_Of_Channel; channel++)
		{
			/* Get physical channel. */
			channelId = ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupDefinition.AdcChannelIdList[channel];
			/* Pointer the commandbuffer */				
			commandQueue = ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupDefinition.AdcGroupCommandBuffer;			
			/* Begin with empty command. */
			cmd.R = ZERO;
			cmd.B.BN = hwUnitId;		
			/* Physical channel number. */
			cmd.B.ADC_CHANNEL_NUMBER = channelId;			
			/* Sample time. */
			cmd.B.LST = ConfigPtr->AdcHwUnit->AdcChannel[channel].AdcChannelSampTime;
			
			/*
			 * Result buffer FIFO. The number of groups must not be greater 
			 * than the number of queues. 
			 */
			cmd.B.MESSAGE_TAG = group;
			/*Alternate Cofiguration 1*/
			cmd.B.ALT_CONFIG_SEL = ADC_ACRSEL;	
			/* Write command to command queue. */
			commandQueue [channel].R = cmd.R;			
			/*Load data for AdcGroupCommandBuffer*/
			commandQueue [channel].B.EOQ = ZERO;	        

			adcGain = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupGain;

			if (adcGain > TWO)
			{
				cmd.B.CAL = ZERO;		
			}
			else
			{
				cmd.B.CAL = ONE;
			}
			
			if (ADC_INTERRUPT == Adc_GroupInterruptOrDma[group])
			{
				/*
				 * When channel number is 4's times or is the last channel in 
				 * group. Write EOQ and configure eQADC FIFO. 
				 */
				if ((channel ==(ConfigPtr->AdcHwUnit->AdcGroup[group]).AdcGroupDefinition.Num_Of_Channel - 1) 
				|| ((((channel+1) % ONCE_MAX_ENTRY) == ZERO) && (channel != ADC_ZERO)))	
				{
					commandQueue [channel].B.EOQ = ONE;
				}	
			}
			else
			{
				commandQueue [channel].B.EOQ = ONE;
				commandQueue [channel].B.FFMT = ZERO;	/*No flush signal is sent*/	
			}
			
		}		
		/* Disable interrupt or DMA request */
		EQADC.IDCR[group].B.RFDE = ZERO; 
		/* Disable hardware trigger */	
		SIU.ISEL3.B.ETSEL0 = ZERO; 		
		SIU.ISEL3.B.ETSEL1 = ZERO;
		SIU.ISEL3.B.ETSEL2 = ZERO;
		SIU.ISEL3.B.ETSEL3 = ZERO;
		SIU.ISEL3.B.ETSEL4 = ZERO;
		SIU.ISEL3.B.ETSEL5 = ZERO;
	}	
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ConfigureInterruptORDMA>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_ConfigureInterruptORDMA(Adc_GroupType group) 
{
	uint8 interruptOffset = FIVE;
	
	/* Configure DMA */
	if (ADC_DMA == Adc_GroupInterruptOrDma[group])	/*use DMA*/
	{
		Dma_ConfigureChannel((Dma_ChannelType)(2*group), &Adc_DMA_FillCommandCofig[group]);
		Dma_ConfigureChannel((Dma_ChannelType)(2*group + ADC_ONE), &Adc_DMA_ReadResultCofig[group]);
	
		if (ADC_ACCESS_MODE_SINGLE == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupAccessMode)
		{
			switch (group)
			{
				case ADC_GROUP0:
					/* Confgiure Dma for GROUP0 */
					(void)Dma_ConfigureChannelTransferSize(DMA_ADC_GROUP0_READRESULT_CHANNEL, 
						(uint32)(Adc_DMA_ReadResultCofig[ADC_GROUP0].BITER/ADC_GROUP_0_SAMPLE_NUMBER));		
					break;
				
				case ADC_GROUP1:
					/* Confgiure Dma for GROUP1 */
					(void)Dma_ConfigureChannelTransferSize(DMA_ADC_GROUP1_READRESULT_CHANNEL, 
						(uint32)(Adc_DMA_ReadResultCofig[ADC_GROUP1].BITER/ADC_GROUP_1_SAMPLE_NUMBER));		
					break;
					
				case ADC_GROUP2:
					/* Confgiure Dma for GROUP2 */
					(void)Dma_ConfigureChannelTransferSize(DMA_ADC_GROUP2_READRESULT_CHANNEL, 
						(uint32)(Adc_DMA_ReadResultCofig[ADC_GROUP2].BITER/ADC_GROUP_2_SAMPLE_NUMBER));		
					break;

				case ADC_GROUP3:
					/* Confgiure Dma for GROUP3 */
					(void)Dma_ConfigureChannelTransferSize(DMA_ADC_GROUP3_READRESULT_CHANNEL, 
						(uint32)(Adc_DMA_ReadResultCofig[ADC_GROUP3].BITER/ADC_GROUP_3_SAMPLE_NUMBER));		
					break;
	
				case ADC_GROUP4:
					/* Confgiure Dma for GROUP4 */
					(void)Dma_ConfigureChannelTransferSize(DMA_ADC_GROUP4_READRESULT_CHANNEL, 
						(uint32)(Adc_DMA_ReadResultCofig[ADC_GROUP4].BITER/ADC_GROUP_4_SAMPLE_NUMBER));		
					break;
					
				case ADC_GROUP5:
					/* Confgiure Dma for GROUP5 */
					(void)Dma_ConfigureChannelTransferSize(DMA_ADC_GROUP5_READRESULT_CHANNEL, 
						(uint32)(Adc_DMA_ReadResultCofig[ADC_GROUP5].BITER/ADC_GROUP_5_SAMPLE_NUMBER));		
					break;
			default:
				break;
			}	
		}
		
		/* Start the DMA channel */		
		(void)Dma_StartChannel((Dma_ChannelType)(TWO*group + ONE));
		Dma_SetChannelMajorInterrupt((Dma_ChannelType)(2*group + ADC_ONE), DMA_CHANNELMAJORINTERRUPT_ENABLE);
		(void)Dma_StartChannel((Dma_ChannelType)(TWO*group));
		/* Set the int. priority */
		INTC.PSR[EDMA_INTL_INT1].R = EQADC_FISR0_RFDF5_PRIORITY;
		INTC.PSR[EDMA_INTL_INT3].R = EQADC_FISR0_RFDF5_PRIORITY;
		INTC.PSR[EDMA_INTL_INT5].R = EQADC_FISR0_RFDF5_PRIORITY;
		INTC.PSR[EDMA_INTL_INT7].R = EQADC_FISR0_RFDF5_PRIORITY;
		INTC.PSR[EDMA_INTL_INT9].R = EQADC_FISR0_RFDF5_PRIORITY;
		INTC.PSR[EDMA_INTL_INT11].R = EQADC_FISR0_RFDF5_PRIORITY;
		/* Enable the interrupt */
		Adc_Enable_Irq();			
	}
	/* Configure Interrupt */	
	else	
	{
		INTC.PSR[EQADC_FISR0_CFFF0 + group*interruptOffset].R = EQADC_FIFO0_END_OF_QUEUE_PRIORITY;			
		INTC.PSR[EQADC_FISR0_EOQF0 + group*interruptOffset].R = EQADC_FIFO0_END_OF_QUEUE_PRIORITY;
		/* Enable irq */
		Adc_Enable_Irq();			
	}
	
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_ConfigureEQADC>
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
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_ConfigureEQADC
(P2CONST(Adc_ConfigType ,AUTOMATIC ,ADC_APPL_CONST) ConfigPtr)
{
	/* Store the group id */
	Adc_GroupType group;
	/* Store the hw id */
	uint32 hwUintId;	
	Adc_EQADCRegister adcEnable = ADC_EN;
	uint32 peripheralBusClock = ZERO;
	
	/* Get the hw id */
	hwUintId =	Adc_ConfigPtr->AdcHwUnit->AdcHwUnitId;
	/* Get the bus clock */
	peripheralBusClock = Mcu_GetPeripheralBusClock();
	
	if ((peripheralBusClock/(uint32)(((TWO*(ConfigPtr->AdcHwUnit->AdcPrescale)) + TWO))) > ADC_15M)
	{
		/* ADC module clock should not exceed 15MHz */
		return;
	}
	
	for (group = ADC_GROUP0; group < ADC_SUM_OF_GROUP; group++)
	{
		Adc_Group = group;
		/* Enable ADC0. */
		Adc_WriteEQADCRegister(hwUintId,ADC0_CR, (adcEnable |(uint32)(ConfigPtr->AdcHwUnit->AdcPrescale)));
		/* Disable time stamp timer. */
		Adc_WriteEQADCRegister(hwUintId,ADC0_TSCR, ZERO);
		/* Invalidate FIFO. */
		EQADC.CFCR[group].B.CFINV = ONE;
	}
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_StartGpConvHwConfig>
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
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_StartGpConvHwConfig(Adc_GroupType group) 
{
	/* Init the loop conter */
	uint8 loopCnt = ADC_ZERO;
	/* Store the channel index */
	uint8 channelIndex;
	/* Store the gain */
	uint16 adcGain;
	/* Store the hw id */
	uint32 hwUintId;
	/* Store the FMTA */
	Adc_ResultFmtType adcFmta;
	/* Store the acr1 */
	Adc_ACR_Type acr1Value;
	Adc_AGR_Type  agrValue;
	
	/* Set the acr1 */
	acr1Value.R = ADC_ZERO;
	acr1Value.B.DEST = ADC_ONE;
	/* Get the hw id */
	hwUintId =	Adc_ConfigPtr->AdcHwUnit->AdcHwUnitId;
	/* Get the channel index */
	channelIndex = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupDefinition.AdcChannelIdList[0];
	if (ADC_RESOLUTION_8BITS == Adc_ConfigPtr->AdcHwUnit->AdcChannel[channelIndex].AdcChannelResolution)
	{
		acr1Value.B.RESSEL = TWO;
	}
	else if (ADC_RESOLUTION_10BITS == Adc_ConfigPtr->AdcHwUnit->AdcChannel[channelIndex].AdcChannelResolution)
	{
		acr1Value.B.RESSEL = ONE;
	}
	else
	{
		acr1Value.B.RESSEL = ZERO;
	}
	
	/* Get the FMTA */
	adcFmta = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupFmta;
	
	/* Set the FMTA */
	if (ADC_UNSIGTYPE == adcFmta)
	{
		acr1Value.B.FMTA = ZERO;	
	}
	else
	{
		acr1Value.B.FMTA = ONE;		
	} 
	
	acr1Value.B.RESSEL = ZERO;
	agrValue.B.ALTGCC = ZERO;
	/* Get the gain */
	adcGain = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupGain;
	/* Set the gain */	
	if (adcGain > TWO)
	{
		agrValue.B.ALTGCC = adcGain;		
	}
	else
	{
		acr1Value.B.PREGAIN = adcGain;
	}
	
	if (FALSE == flag)
	{
		Adc_WriteEQADCRegister (hwUintId,ADC_ACR1,acr1Value.R);	
		Adc_WriteEQADCRegister (hwUintId,ADC_AGR,agrValue.R);	
		flag = TRUE;
	}
	
	Adc_ConfigureInterruptORDMA(group);
	
	/* 0x0410,Trigger the group using Single Scan SW mode */
	EQADC.CFCR[group].R = 0x0490; 
	
	if (ADC_DMA == Adc_GroupInterruptOrDma[group])/*use DMA*/
	{	
		/* Generate DMA to move data from the system memory to CFIFOx. */
		EQADC.IDCR[group].B.CFFS = ONE;
		
		/* Generate DMA to move data from RFIFOx to the system memory. */
		EQADC.IDCR[group].B.RFDS = ONE;	
		
		/* Generate DMA to move data from RFIFOx to the system memory.JQ */
		EQADC.IDCR[group].B.RFDE = ONE;	
	}
	else /*use interrupt*/
	{
		/* 
		 * Generate interrupt request to move data from the system memory to 
		 * CFIFOx.
		 */
		EQADC.IDCR[group].B.CFFS = ZERO;
		
		/* 
		 * Generate interrupt request to move data from RFIFOx to the system
		 * memory. 
		 */
		EQADC.IDCR[group].B.RFDS = ZERO;	
	}
	
	EQADC.IDCR[group].B.CFFE = ONE; /* Enable Fill command DMA or Interrupt *///jjq
 	if (ADC_DMA == Adc_GroupInterruptOrDma[group])
	{

		for (loopCnt = ZERO; loopCnt < 0x19; loopCnt++)
		{
			/* asm("nop");*/	
		}
	}
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_EnableHwTriConfig>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/

#define ADC_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_EnableHwTriConfig(Adc_GroupType group) 
{
	uint32 siuIsel3LastValue[6] = {0,0,0,0,0,0};
	Adc_ACR_Type acr1Value;	
	Adc_ResultFmtType adcFmta;
	Adc_AGR_Type  agrValue;
	uint8 channelIndex;
	uint16 adcGain;
	uint32 hwUintId;
	
	/* ADC273 ADC353*/
	/* Save remainning trigger source for each group */
	siuIsel3LastValue[0] = SIU.ISEL3.B.ETSEL0;
	siuIsel3LastValue[1] = SIU.ISEL3.B.ETSEL1;
	siuIsel3LastValue[2] = SIU.ISEL3.B.ETSEL2;
	siuIsel3LastValue[3] = SIU.ISEL3.B.ETSEL3;
	siuIsel3LastValue[4] = SIU.ISEL3.B.ETSEL4;
	siuIsel3LastValue[5] = SIU.ISEL3.B.ETSEL5;
	
	/* Get the HW id */
	hwUintId =	Adc_ConfigPtr->AdcHwUnit->AdcHwUnitId;
	/* Get the channel index */
	channelIndex = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupDefinition.AdcChannelIdList[0];
	
	if ((siuIsel3LastValue[group]!= ADC_ZERO) 
	&& ((uint32)(Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcHwTrigTimer) != siuIsel3LastValue[group]))
	{
		return;	
	}

	/* Reset acr1 */
	acr1Value.R = ZERO;
	acr1Value.B.DEST = ONE;
	
	/* Configure the interrupt for DMA */
	Adc_ConfigureInterruptORDMA(group);
	
	/* Set the resolution for adc */
	if (ADC_RESOLUTION_8BITS == Adc_ConfigPtr->AdcHwUnit->AdcChannel[channelIndex].AdcChannelResolution)
	{
		acr1Value.B.RESSEL = TWO;
	}
	else if (ADC_RESOLUTION_10BITS == Adc_ConfigPtr->AdcHwUnit->AdcChannel[channelIndex].AdcChannelResolution)
	{
		acr1Value.B.RESSEL = ONE;
	}
	else
	{
		acr1Value.B.RESSEL = ZERO;
	}
	
	/* Get the FMTA */
	adcFmta = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupFmta;
	
	/* Set the FMTA */
	if(ADC_UNSIGTYPE == adcFmta)
	{
		acr1Value.B.FMTA = ZERO;	
	}
	else
	{
		acr1Value.B.FMTA = ONE;		
	}
	
	acr1Value.B.RESSEL = ZERO;
	agrValue.B.ALTGCC = ZERO;
	/* Get the gain value */
	adcGain = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupGain;
	
	/* Set the gain */
	if (adcGain > TWO)
	{
		agrValue.B.ALTGCC = adcGain;		
	}
	else
	{
		acr1Value.B.PREGAIN = adcGain;
	}
	
	/* Write the register */
	if (FALSE == flag)
	{
		Adc_WriteEQADCRegister(hwUintId,ADC_ACR1, acr1Value.R);
		Adc_WriteEQADCRegister (hwUintId,ADC_AGR,agrValue.R);	
		flag = TRUE;
	}

	/* ADC144 ADC114 */
	/* Set trigger source */
	switch (group)
	{
		case ADC_GROUP0:
			/* Set the trigger source for GROUP0 */
			SIU.ISEL3.B.ETSEL0 = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcHwTrigTimer;			
			SIU.ETISR.B.TSEL0 = ZERO;
			break;
			
		case ADC_GROUP1:
			/* Set the trigger source for GROUP1 */
			SIU.ISEL3.B.ETSEL1 = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcHwTrigTimer;
			SIU.ETISR.B.TSEL1 = ZERO;
			break;

		case ADC_GROUP2:
			/* Set the trigger source for GROUP2 */
			SIU.ISEL3.B.ETSEL2 = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcHwTrigTimer;
			SIU.ETISR.B.TSEL2 = ZERO;
			break;
	
		case ADC_GROUP3:
			/* Set the trigger source for GROUP3 */
			SIU.ISEL3.B.ETSEL3 = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcHwTrigTimer;
			SIU.ETISR.B.TSEL3 = ZERO;
			break;

		case ADC_GROUP4:
			/* Set the trigger source for GROUP4 */
			SIU.ISEL3.B.ETSEL4 = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcHwTrigTimer;			
			SIU.ETISR.B.TSEL4 = ZERO;
			break;
			
		case ADC_GROUP5:
			/* Set the trigger source for GROUP5 */
			SIU.ISEL3.B.ETSEL5 = Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcHwTrigTimer;
			SIU.ETISR.B.TSEL5 = ZERO;
			break;
			
		default:
			break;
	}
	
	switch (Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcHwTrigSignal)
	{
		case ADC_HW_TRIG_FALLING_EDGE:
		
			if (ADC_CONV_MODE_ONESHOT == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupConversionMode)
			{
				EQADC.CFCR[group].R = ADC_FEDGE_CONTINU;
			}
			else/*For continuous scan*/
			{
				EQADC.CFCR[group].R = ADC_FEDGE_CONTINU;	
			}
			break;
			
		case ADC_HW_TRIG_RISING_EDGE:
			
			if (ADC_CONV_MODE_ONESHOT == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupConversionMode) 
			{ 
				EQADC.CFCR[group].R = ADC_FEDGE_CONTINU;			
			}
			else/*For continuous scan*/
			{
				EQADC.CFCR[group].R = ADC_REDGE_CONTINU;	
			}
			break;
	
		case ADC_HW_TRIG_BOTH_EDGES:
		
			if (ADC_CONV_MODE_ONESHOT == Adc_ConfigPtr->AdcHwUnit->AdcGroup[group].AdcGroupConversionMode)
			{
				EQADC.CFCR[group].R = ADC_FEDGE_CONTINU;		
			}
			else/*For continuous scan*/
			{
				EQADC.CFCR[group].R = ADC_BEDGE_CONTINU;	
			}
			break;
			
		default: 
			break;
	}
	 
	if (ADC_DMA == Adc_GroupInterruptOrDma[group])	/*use DMA*/
	{	
		/*Generate DMA to move data from RFIFOx to the system memory.*/
		EQADC.IDCR[group].B.CFFS = ADC_ONE;		
		/*Generate DMA to move data from RFIFOx to the system memory.*/
		EQADC.IDCR[group].B.RFDS = ADC_ONE;
		/* enable Load command interrupt or DMA */		
		EQADC.IDCR[group].B.CFFE = ADC_ONE;
		/*Enable DMA*/
		EQADC.IDCR[group].B.RFDE = ADC_ONE;	
	}
	else /*use interrupt*/
	{
		/* Enable Load command interrupt or DMA */
		EQADC.IDCR[group].B.CFFE = ADC_ONE;
		
		/*
		 * Generate interrupt request to move data from the system memory to
		 * CFIFOx.
		 */
		EQADC.IDCR[group].B.CFFS = ADC_ZERO;
	
		/*
		 * Generate interrupt request to move data from RFIFOx to the system 
		 * memory.
		 */
		EQADC.IDCR[group].B.RFDS = ADC_ZERO;		
	}	
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DisableHwTrConfig>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <group>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_DisableHwTrConfig(Adc_GroupType group) 
{
	/* ADC116 ADC145*/
	EQADC.IDCR[group].B.RFDE = ZERO; 
	/* Delete trigger source */
	switch (group)				  
	{
		case ADC_GROUP0: 
			/* Delete trigger source for GROUP0*/
			SIU.ISEL3.B.ETSEL0 = ZERO; 
			break;
			
		case ADC_GROUP1:
			/* Delete trigger source for GROUP1*/ 
			SIU.ISEL3.B.ETSEL1 = ZERO; 
			break;
			
		case ADC_GROUP2: 
			/* Delete trigger source for GROUP2*/
			SIU.ISEL3.B.ETSEL2 = ZERO; 
			break;
			
		case ADC_GROUP3: 
			/* Delete trigger source for GROUP3*/
			SIU.ISEL3.B.ETSEL3 = ZERO; 
			break;
			
		case ADC_GROUP4: 
			/* Delete trigger source for GROUP4*/
			SIU.ISEL3.B.ETSEL4 = ZERO; 
			break;
			
		case ADC_GROUP5: 
			/* Delete trigger source for GROUP5*/
			SIU.ISEL3.B.ETSEL5 = ZERO; 
			break;
			
		default: 
			break;
	}
	
	return ;
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_DelHardConfig>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_DelHardConfig(void) 
{
	boolean queueStopped;
	Adc_GroupType group;
	uint32 hwUnintId;
	
	/* Get the HW id*/
	hwUnintId = Adc_ConfigPtr->AdcHwUnit->AdcHwUnitId;	
	/* Stop all queues */
	for (group = ADC_GROUP0; group < ADC_SUM_OF_GROUP; group++)
	{
		/*Disable queue */
		EQADC.CFCR[group].B.MODE = ZERO;	
		queueStopped = FALSE;
		
		/* ADC110 */ 
		while ((boolean)FALSE == queueStopped  ) 
		{
			switch (group)
			{
				case ADC_GROUP0:
					/* Set group status for GROUP0 */
					queueStopped = (uint8)(EQADC.CFSR.B.CFS0 == EQADC_CFIFO_STATUS_IDLE);					
					break;
					
				case ADC_GROUP1:
					/* Set group status for GROUP1 */
					queueStopped = (uint8)(EQADC.CFSR.B.CFS1 == EQADC_CFIFO_STATUS_IDLE);						
					break;
	
				case ADC_GROUP2:
					/* Set group status for GROUP2 */
					queueStopped = (uint8)(EQADC.CFSR.B.CFS2 == EQADC_CFIFO_STATUS_IDLE);						
					break;
					
				case ADC_GROUP3:
					/* Set group status for GROUP3 */
					queueStopped = (uint8)(EQADC.CFSR.B.CFS3 == EQADC_CFIFO_STATUS_IDLE);						
					break;
						
				case ADC_GROUP4:
					/* Set group status for GROUP4 */
					queueStopped = (uint8)(EQADC.CFSR.B.CFS4 == EQADC_CFIFO_STATUS_IDLE);
					break;
					
				case ADC_GROUP5:
					/* Set group status for GROUP5 */
					queueStopped = (uint8)(EQADC.CFSR.B.CFS5 == EQADC_CFIFO_STATUS_IDLE);	         				          			
					break;
		
				default :
					queueStopped = TRUE;
					break;
				}
			}
			
			/* Disable FIFO fill requests */
			EQADC.IDCR[group].B.CFFE = ZERO;
			EQADC.IDCR[group].B.RFDE = ZERO;
			/* ADC111,Disable interrupts */
			EQADC.IDCR[group].B.RFDS = ZERO;
			EQADC.IDCR[group].B.RFOIE = ZERO;
			EQADC.IDCR[group].B.CFUIE = ZERO;
			EQADC.IDCR[group].B.TORIE = ZERO;
			EQADC.IDCR[group].B.EOQIE = ZERO;
	}
	/* Disable EQADC */   
	Adc_WriteEQADCRegister(hwUnintId,ADC0_CR, ZERO);	
	return;		

}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_WriteEQADCRegister>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <hwUintId, reg, value>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ADC_PUBLIC_CODE) Adc_WriteEQADCRegister(uint32 hwUintId,Adc_EQADCRegisterType reg, Adc_EQADCRegister value)
{
	volatile Adc_RegisterWriteType writeReg;
	uint32 temp, oldMode;

	writeReg.R = (uint32)ZERO;
	writeReg.B.ADC_REG = ZERO;
	writeReg.B.ADC_REG_ADDR = ZERO;	
	/* Write command. */
	writeReg.B.RW = ZERO;
	writeReg.B.EOQ = ONE;
	writeReg.B.ADC_REG = value;
	writeReg.B.ADC_REG_ADDR = reg;
	writeReg.B.BN = hwUintId;
	/* Invalidate queue. */
	EQADC.CFCR[Adc_Group].B.CFINV = ONE;
	/* Write command through FIFO. */
	EQADC.CFPR[Adc_Group].R = (vuint32_t)(writeReg.R);	
	/* Enable FIFO. */
	oldMode = EQADC.CFCR[Adc_Group].B.MODE;
	/* ADC_CONV_MODE_ONESHOT */
	EQADC.CFCR[Adc_Group].B.MODE = ONE;		
	EQADC.CFCR[Adc_Group].B.SSE = ONE;
	/* Wait for command to be executed. */
	WAIT_FOR_QUEUE_TO_FINISH(Adc_Group);	
	/* Flush result buffer. */
	temp = EQADC.RFPR[Adc_Group].R;
	EQADC.FISR[Adc_Group].B.EOQF = ONE;
	EQADC.CFCR[Adc_Group].B.MODE = oldMode;
	
} /*lint !e550*/
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_Enable_Irq>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void,ADC_PUBLIC_CODE) Adc_Enable_Irq(void) 	
{
	/* Current Priority Register */
	INTC.CPR.B.PRI = ZERO;
	/* MISRA Rule         : 1.1
		Message            : This in_line assember construct is a language extension
		Verification       : However, this part of the code is verified
							manually and it is not having any impact.
	*/  
	asm volatile (" wrteei 1 ");
}
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/
