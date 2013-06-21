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
 *  V1.0.0       20130427  James       Initial version
 */
/*============================================================================*/

/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define SPI_C_AR_MAJOR_VERSION  2
#define SPI_C_AR_MINOR_VERSION  2
#define SPI_C_AR_PATCH_VERSION  2
#define SPI_C_SW_MAJOR_VERSION  1
#define SPI_C_SW_MINOR_VERSION  0
#define SPI_C_SW_PATCH_VERSION  0

/*=======[I N C L U D E S]====================================================*/
#include "Spi.h"
#include "Modules.h"
#include "Mcu.h"

#if (SPI_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif


/*=======[V E R S I O N  C H E C K]===========================================*/
#if ((SPI_C_AR_MAJOR_VERSION != SPI_AR_MAJOR_VERSION) || \
     (SPI_C_AR_MINOR_VERSION != SPI_AR_MINOR_VERSION) || \
     (SPI_C_AR_PATCH_VERSION != SPI_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of SPI.c and SPI.h are different"
#endif

#if ((SPI_C_SW_MAJOR_VERSION != SPI_SW_MAJOR_VERSION) || \
     (SPI_C_SW_MINOR_VERSION != SPI_SW_MINOR_VERSION) || \
     (SPI_C_SW_PATCH_VERSION != SPI_SW_PATCH_VERSION))
#error "Software Version Numbers of SPI.c and SPI.h are different"
#endif


/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/
uint32 Spi_SysClock;
Spi_AsyncModeType Spi_Mode = SPI_POLLING_MODE;

/*=======[I N T E R N A L   D A T A]==========================================*/
STATIC Spi_DataType Spi_Tx_Buffer[SPI_MAX_CHANNEL][SPI_TX_RX_BUFFER_LEN] = {ZERO};
           
STATIC Spi_DataType Spi_Rx_Buffer[SPI_MAX_CHANNEL][SPI_TX_RX_BUFFER_LEN] = {ZERO};
           
Spi_GlobalType Spi_Global = {ZERO};
//STATIC Spi_GlobalType Spi_Global = {ZERO};

Spi_StatusType Spi_Status = SPI_UNINIT;
//STATIC Spi_StatusType Spi_Status = SPI_UNINIT;

SpiChannelUnitType Spi_ChannelUnit[SPI_MAX_CHANNEL];
//STATIC SpiChannelUnitType Spi_ChannelUnit[SPI_MAX_CHANNEL];

SpiJobUnitType Spi_JobUnit[SPI_MAX_JOB];
//STATIC SpiJobUnitType Spi_JobUnit[SPI_MAX_JOB];

SpiSequenceUnitType Spi_SequenceUnit[SPI_MAX_SEQUENCE];
//STATIC SpiSequenceUnitType Spi_SequenceUnit[SPI_MAX_SEQUENCE];

STATIC Spi_StatusType Spi_HWUnitStatus[SPI_CONTROLLER_NUM];

STATIC uint32 Spi_ClkTableAsc[] = {2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536 };

STATIC uint32 Spi_ClkTableCssck[] = {2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536 };

STATIC uint8 clk_table_pasc[] = {1,3,5,7};
STATIC uint32 Spi_PushrBuffer[SPI_EB_MAX_LENGTH * SPI_MAX_CHANNEL]={ZERO};
STATIC uint32 Spi_Count = ZERO;


/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
STATIC FUNC(void, SPI_CODE)Spi_InitController(uint8 unit);
STATIC FUNC(void, SPI_CODE)Spi_HWDeInit(void);
STATIC FUNC(void, SPI_CODE)Spi_SetSpiBusAttr(SpiJobConfigType jobconfig);
STATIC FUNC(Std_ReturnType, SPI_CODE)Spi_WriteChannel(Spi_ControllerUnitType HwUnit, uint8 channel);
STATIC FUNC(Std_ReturnType, SPI_CODE)Spi_WriteJob(P2CONST(SpiJobUnitType, AUTOMATIC, SPI_APPL_CONST)job);
STATIC FUNC(Std_ReturnType, SPI_CODE)Spi_WriteSeq(P2VAR(SpiSequenceUnitType, AUTOMATIC, SPI_VAR)seq);


/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/*===========================================================================*/
/* Function Name        :Spi_Init                                            */
/* Service ID           :0x00                                                */
/* Description          :Initializes the module.                             */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :const Spi_ConfigType *ConfigPtr.                    */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SPI_CODE)Spi_Init(P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_CONST) ConfigPtr)
{
    uint8 i,j;
	
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    boolean errorFlag;
    #endif

    P2CONST(SpiChannelConfigType, AUTOMATIC, SPI_CONST)channelConfig = ConfigPtr->spiChannelConfig;
                                                   
    P2CONST(SpiJobConfigType, AUTOMATIC, SPI_CONST)jobConfig = ConfigPtr->spiJobConfig;
                                                 
    P2CONST(SpiSequenceConfigType, AUTOMATIC, SPI_CONST)sequenceConfig = ConfigPtr->spiSeqConfig;
    
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    errorFlag = FALSE;
	
    /* Check if SPI configuration pointer is a NULL Pointer  */
    if(NULL_PTR == channelConfig)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                   SPI_INIT_ID, SPI_E_PARAM_CHANNEL);
        errorFlag = TRUE;
    }

    if((FALSE == errorFlag)  && (NULL_PTR == jobConfig))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                   SPI_INIT_ID, SPI_E_PARAM_JOB);
        errorFlag = TRUE;
    }

    if((FALSE == errorFlag)  && (NULL_PTR == sequenceConfig))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                   SPI_INIT_ID, SPI_E_PARAM_SEQ);
        errorFlag = TRUE;
    }
	
    if((FALSE == errorFlag)  && (SPI_UNINIT != Spi_Status))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_INIT_ID, SPI_E_ALREADY_INITIALIZED);
        errorFlag = TRUE;
    }
    /* If no DET errors, continue */
    if( FALSE == errorFlag)

    #endif /* (SPI_DEV_ERROR_DETECT == STD_ON) */
    {
	    /*Channel Unit Initial*/
	    for(i = 0; i < ConfigPtr->SpiMaxChannel; i++)
	    {
	        Spi_ChannelUnit[i].spichannel.SpiChannelId = channelConfig->SpiChannelId;
	        Spi_ChannelUnit[i].spichannel.SpiChannelTp = channelConfig->SpiChannelTp;
	        Spi_ChannelUnit[i].spichannel.SpiDataWidth = channelConfig->SpiDataWidth;
	        Spi_ChannelUnit[i].spichannel.SpiDefaultData = channelConfig->SpiDefaultData;
	        Spi_ChannelUnit[i].spichannel.SpiEbMaxLength = channelConfig->SpiEbMaxLength;
	        Spi_ChannelUnit[i].spichannel.SpiIbNBuffers = channelConfig->SpiIbNBuffers;
	        Spi_ChannelUnit[i].spichannel.SpiTransferStart = channelConfig->SpiTransferStart;
	        Spi_ChannelUnit[i].sendBufferPointer = NULL_PTR;
	        Spi_ChannelUnit[i].recvBufferPointer = NULL_PTR;
	        Spi_ChannelUnit[i].length = 0;
	        channelConfig++;
	    }

	    /*Job Initial*/
	    for(i = 0; i < ConfigPtr->SpiMaxJob ; i++)
	    {
	    	Spi_JobUnit[i].spijob.SpiJobId = jobConfig->SpiJobId;
	    	Spi_JobUnit[i].spijob.SpiHwUnit = jobConfig->SpiHwUnit;
	    	Spi_JobUnit[i].spijob.SpiJobEndNotification = jobConfig->SpiJobEndNotification;
	    	Spi_JobUnit[i].spijob.SpiJobPriority = jobConfig->SpiJobPriority;
	    	for(j = 0; j < (ConfigPtr->SpiMaxChannel + 1); j++)
	    	{
	    		Spi_JobUnit[i].spijob.ChannelAssignment[j] = jobConfig->ChannelAssignment[j];
	    	}
	    	
	    	Spi_JobUnit[i].spijob.DeviceAssignment.SpiBaudrate = jobConfig->DeviceAssignment.SpiBaudrate;
	    	Spi_JobUnit[i].spijob.DeviceAssignment.SpiCsIdentifier = jobConfig->DeviceAssignment.SpiCsIdentifier;
	    	Spi_JobUnit[i].spijob.DeviceAssignment.SpiCsPolarity = jobConfig->DeviceAssignment.SpiCsPolarity;
	    	Spi_JobUnit[i].spijob.DeviceAssignment.SpiDataShiftEdge = jobConfig->DeviceAssignment.SpiDataShiftEdge;
	    	Spi_JobUnit[i].spijob.DeviceAssignment.SpiEnableCs = jobConfig->DeviceAssignment.SpiEnableCs;
            Spi_JobUnit[i].spijob.DeviceAssignment.SpiShiftClockIdleLevel = jobConfig->DeviceAssignment.SpiShiftClockIdleLevel;
            Spi_JobUnit[i].spijob.DeviceAssignment.SpiTimeClk2Cs = jobConfig->DeviceAssignment.SpiTimeClk2Cs;
	    	Spi_JobUnit[i].SpiJobResult = SPI_JOB_OK;
	        jobConfig++;
	    }

	    /*Sequence Initial*/
	    for(i = 0; i < ConfigPtr->SpiMaxSequence; i++)
	    {
	    	Spi_SequenceUnit[i].spisequence.SpiSequenceId = sequenceConfig->SpiSequenceId;
	    	Spi_SequenceUnit[i].spisequence.SpiInterruptibleSequence = sequenceConfig->SpiInterruptibleSequence;
	    	Spi_SequenceUnit[i].spisequence.SpiSeqEndNotification = sequenceConfig->SpiSeqEndNotification;
	        
	        for(j = 0; j < (ConfigPtr->SpiMaxJob + 1); j++)
	        {
	            Spi_SequenceUnit[i].spisequence.JobAssignment[j] = sequenceConfig->JobAssignment[j];
	        }	
	        Spi_SequenceUnit[i].SpiSeqResult = SPI_SEQ_OK;
	        sequenceConfig++;
	    }

	    /*Get bus clock from Mcu Module*/
        Spi_SysClock = Mcu_GetPeripheralBusClock();
	    
	    #if (TWO == SPI_LEVEL_DELIVERED)
        Spi_Mode = SPI_POLLING_MODE;
	    #endif

	    Spi_Count = ZERO;

	    for(i = 0; i < (uint8)SPI_CONTROLLER_NUM; i++)
	    {
	        Spi_HWUnitStatus[i] = SPI_IDLE;
            
            /* Configure CTAR0  */
	        DSPI_B.CTAR[0].R = 0x78087727; 
	        DSPI_C.CTAR[0].R = 0x78087727;

            for(j = 0; j < SPI_TX_RX_BUFFER_LEN; j++)
            {
		        Spi_Tx_Buffer[i][j] = ZERO;
		        Spi_Rx_Buffer[i][j] = ZERO;
            }
			
	        /* Initial Controller */
	        Spi_InitController(i);
	    }

        Spi_Global.AsyncTransferNow = FALSE;
	    Spi_Global.SequenceId = (Spi_SequenceType)0;
	    Spi_Global.TransMode = SPI_SYNC;
		
	    Spi_Status = SPI_IDLE;
    }

}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Spi_DeInit                                          */
/* Service ID           :0x01                                                */
/* Description          :de-initialization the module.                       */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :None                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Std_ReturnType                                      */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, SPI_CODE)Spi_DeInit(void)
{
    Std_ReturnType returnValue = E_NOT_OK;

    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if(SPI_UNINIT  == Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_DEINIT_ID, SPI_E_UNINIT);
    }
    else
    #endif /* End of(SPI_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Check if Global status variable is SPI_BUSY */
        if(SPI_BUSY !=  Spi_Status)
        {
            Spi_HWDeInit();
            returnValue = E_OK;

            /*Update the SPI driver status as uninitialized */
            Spi_Status = SPI_UNINIT;
        }
    }

    return(returnValue);
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"

#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_ZERO) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO))
/*===========================================================================*/
/* Function Name        :Spi_WriteIB                                         */
/* Service ID           :0x02                                                */
/* Description          :writing one or more data to an IB SPI               */
/*            Handler/Driver Channel specified.                              */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :Channel, DataBufferPtr                              */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Std_ReturnType                                      */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, SPI_CODE)Spi_WriteIB(Spi_ChannelType Channel,
           P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_CONST) DataBufferPtr)
{
    Spi_NumberOfDataType i;
    Std_ReturnType returnValue = E_OK;
    P2VAR(SpiChannelUnitType, AUTOMATIC, SPI_VAR) currentChannel = &Spi_ChannelUnit[Channel];
    
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if( SPI_UNINIT== Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_WRITEIB_ID, SPI_E_UNINIT);
        returnValue = E_NOT_OK;
    }
    /* Check if the channel ID passed, is valid */
    if(( E_OK == returnValue) && (Channel >= SPI_MAX_CHANNEL))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_WRITEIB_ID, SPI_E_PARAM_CHANNEL);
        returnValue = E_NOT_OK;
    }
    #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO)
    /* If it is valid channel ID, check if the length passed is valid */
    else
    {
        if((returnValue == E_OK) && ((currentChannel->spichannel.SpiIbNBuffers) > SPI_TX_RX_BUFFER_LEN))
        {
            returnValue = E_NOT_OK;
        }
			
        /* If the requested channel configured for Internal Buffer */
        if((returnValue == E_OK) && ((currentChannel->spichannel.SpiChannelTp) == SPI_EB))
        {
            /* Report to DET */
            Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                       SPI_WRITEIB_ID, SPI_E_PARAM_CHANNEL);
            returnValue = E_NOT_OK;
        }
    }
    #endif /* SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO */
	
    /* Check if any DET error has occurred */
    if( E_OK == returnValue)
    #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    {   
        if( NULL_PTR == DataBufferPtr)
        {
            for(i = 0; i < currentChannel->spichannel.SpiIbNBuffers; i++)
            {
                Spi_Tx_Buffer[Channel][i] = currentChannel->spichannel.SpiDefaultData;
            }	
        }
        else
        {	
            for(i = 0; i < currentChannel->spichannel.SpiIbNBuffers; i++)
            {
                Spi_Tx_Buffer[Channel][i] = *(DataBufferPtr + i);
            }	
        }
    }

    return(returnValue);  
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((SPI_LEVEL_DELIVERED == SPI_ONE)|| (SPI_LEVEL_DELIVERED == SPI_TWO))
/*===========================================================================*/
/* Function Name        :Spi_AsyncTransmit                                   */
/* Service ID           :0x03                                                */
/* Description          :transmit data on the SPI bus by async mode          */
/* Sync/Async           :Asynchronous                                        */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :Sequence                                            */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Std_ReturnType                                      */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, SPI_PUBLIC_CODE)Spi_AsyncTransmit(Spi_SequenceType Sequence)
{
    Std_ReturnType returnValue = E_OK;
    P2VAR(SpiSequenceUnitType, AUTOMATIC, SPI_VAR) seqIndex = &Spi_SequenceUnit[Sequence];
	
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if(SPI_UNINIT  == Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_ASYNCTRANSMIT_ID, \
                                   SPI_E_UNINIT);
        returnValue = E_NOT_OK;
    }
    /* Check if the channel ID passed, is valid */
    if(Sequence >= SPI_MAX_SEQUENCE)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, \
                                   SPI_ASYNCTRANSMIT_ID, SPI_E_PARAM_SEQ);
        returnValue = E_NOT_OK;
    }  	
    /* Check if the sequence is pending */
    if(SPI_SEQ_PENDING ==  seqIndex->SpiSeqResult)
    {
        Det_ReportError(SPI_MODULE_ID, 0, SPI_ASYNCTRANSMIT_ID, SPI_E_SEQ_PENDING);
        returnValue = E_NOT_OK;
    }
    /* Check if any DET error has occurred */
    if( E_OK == returnValue)
    #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    {
        /** @req SPI020 */
        Spi_Status = SPI_BUSY;

        Spi_SequenceUnit[Sequence].SpiSeqResult = SPI_SEQ_PENDING;

        Spi_Global.AsyncTransferNow = TRUE;
        Spi_Global.SequenceId = Sequence;
        Spi_Global.TransMode = SPI_ASYNC;
    }

    return(returnValue);
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"
#endif


#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_ZERO)|| \
     (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO))
/*===========================================================================*/
/* Function Name        :Spi_ReadIB                                          */
/* Service ID           :0x03                                                */
/* Description          :Service for reading sychronously one or more data   */
/* from an IB SPI Handler/Driver Channel specified by parameter.             */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :Channel, DataBufferPointer                          */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Std_ReturnType                                      */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, SPI_CODE)Spi_ReadIB \
     (Spi_ChannelType Channel,   \
      P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DataBufferPointer)
{
    uint8 i,j;
    Std_ReturnType returnValue = E_OK;
    P2VAR(SpiChannelUnitType, AUTOMATIC, SPI_VAR)currentChannel = &Spi_ChannelUnit[Channel];
    Spi_NumberOfDataType ibLength = currentChannel->spichannel.SpiIbNBuffers;

    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if( SPI_UNINIT == Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_READIB_ID, SPI_E_UNINIT);
        returnValue = E_NOT_OK;
    }
    /* Check if the channel ID passed, is valid */
    if(( E_OK == returnValue) && (Channel >= SPI_MAX_CHANNEL))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_READIB_ID, SPI_E_PARAM_CHANNEL);
        returnValue = E_NOT_OK;
    }
    /* Check if the data buffer pointer passed, is NULL pointer */
    if((E_OK  == returnValue) && (NULL_PTR  == DataBufferPointer))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_READIB_ID, SPI_E_PARAM_CHANNEL);
        returnValue = E_NOT_OK;
    }
  
    #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO)
    /* If it is valid channel ID, check if the length passed is valid */
    else
    {		
        /* If the requested channel configured for Internal Buffer */
        if((E_OK  ==returnValue ) && (SPI_EB ==  (currentChannel->spichannel.SpiChannelTp)))
        {
            /* Report to DET */
            Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID,
                                       SPI_READIB_ID, SPI_E_PARAM_CHANNEL);
            returnValue = E_NOT_OK;
        }
    }
    #endif /* (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO) */
	
    /* Check if any DET error has occurred */
    if(E_OK  == returnValue)
    #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    {
        for(i = 0; i < ibLength; i++)
        {
            DataBufferPointer[i] = Spi_Rx_Buffer[Channel][i];  
        }

        /*memset(Spi_Rx_Buffer[Channel], 0 , SPI_TX_RX_BUFFER_LEN); */
	    for(j = 0; j < SPI_TX_RX_BUFFER_LEN; j++)
	    {
	        Spi_Rx_Buffer[Channel][j] = 0;
	    }
    }

    return(returnValue);
}

#define SPI_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_ONE) || (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO))
/*===========================================================================*/
/* Function Name        :Spi_SetupEB                                         */
/* Service ID           :0x05                                                */
/* Description          :Service to setup the buffers and the length of data */
/*  for the EB SPI Hander/Driver Channel specified.                          */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :Channel, SrcDataBufferPtr, DesDataBufferPtr, Length */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Std_ReturnType                                      */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, SPI_CODE)Spi_SetupEB(Spi_ChannelType Channel, \
     P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,  \
     P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr,  \
     Spi_NumberOfDataType Length)
{
    Std_ReturnType returnValue = E_OK;
    P2VAR(SpiChannelUnitType, AUTOMATIC, SPI_VAR) currentChannel = &Spi_ChannelUnit[Channel];
	
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if(SPI_UNINIT  == Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETUPEB_ID, SPI_E_UNINIT);
        returnValue = E_NOT_OK;
    }
    /* Check if the channel ID passed, is valid */
    if((E_OK  == returnValue) && (Channel >= SPI_MAX_CHANNEL))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETUPEB_ID, SPI_E_PARAM_CHANNEL);
        returnValue = E_NOT_OK;
    }
    /* If it is valid channel ID, check if the length passed is valid */
    else
    {
        /* Check if the 'length' parameter is greater than configured length */
        if((E_OK  == returnValue) && (Length > (currentChannel->spichannel.SpiEbMaxLength)))
        {
            /* Report to DET */
            Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETUPEB_ID, SPI_E_PARAM_LENGTH);
            returnValue = E_NOT_OK;
        }
		
        #if (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO)
        /* If the requested channel configured for Internal Buffer */
        if((E_OK  == returnValue) && ((currentChannel->spichannel.SpiChannelTp) == SPI_IB))
        {
            /* Report to DET */
            Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETUPEB_ID, SPI_E_PARAM_CHANNEL);
            returnValue = E_NOT_OK;
        }
	    #endif /*(SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO)*/

    }

    /* Check if any DET error has occurred */
    if(E_OK  == returnValue)
    #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    {
        Spi_ChannelUnit[Channel].length = Length;
        Spi_ChannelUnit[Channel].sendBufferPointer = SrcDataBufferPtr;
        Spi_ChannelUnit[Channel].recvBufferPointer = DesDataBufferPtr;
    }
  
    return(returnValue);
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*===========================================================================*/
/* Function Name        :Spi_GetStatus                                       */
/* Service ID           :0x06                                                */
/* Description          :returns the SPI Handler/Driver software module status*/
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :None                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Std_ReturnType                                      */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Spi_StatusType, SPI_CODE)Spi_GetStatus(void)
{
    /** @req SPI025 */
    return Spi_Status;
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Spi_GetJobResult                                    */
/* Service ID           :0x07                                                */
/* Description          :returns the SPI Handler/Driver software module status*/
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :Job                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Spi_JobResultType                                   */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Spi_JobResultType, SPI_CODE)Spi_GetJobResult(Spi_JobType Job)
{
    Std_ReturnType returnValue = E_OK;
    Spi_JobResultType jobResuleValue = SPI_JOB_FAILED;
    P2VAR(SpiJobUnitType, AUTOMATIC, SPI_VAR)jobIndex = &Spi_JobUnit[Job];
	
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if(SPI_UNINIT  == Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETJOBRESULT_ID, SPI_E_UNINIT);
        returnValue = E_NOT_OK;
    }
    /* Check if the channel ID passed, is valid */
    if((E_OK  == returnValue) && (Job >= SPI_MAX_JOB))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETJOBRESULT_ID, SPI_E_PARAM_JOB);
        returnValue = E_NOT_OK;
    }  	

    /* Check if any DET error has occurred */
    if(E_OK  == returnValue)
    #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    {
        jobResuleValue = jobIndex->SpiJobResult;
    }
	
    /** @req SPI026 SPI038 */
    return(jobResuleValue);
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"


/*===========================================================================*/
/* Function Name        :Spi_GetSequenceResult                               */
/* Service ID           :0x08                                                */
/* Description          :returns the SPI Handler/Driver software module status*/
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :Sequence                                            */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Spi_SeqResultType                                   */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Spi_SeqResultType, SPI_CODE)Spi_GetSequenceResult(Spi_SequenceType Sequence)
{
    Std_ReturnType returnValue = E_OK;
    Spi_SeqResultType seqResultValue = SPI_SEQ_FAILED;
    P2VAR(SpiSequenceUnitType, AUTOMATIC, SPI_VAR)seqIndex = &Spi_SequenceUnit[Sequence];
	
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if(SPI_UNINIT  == Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETSEQUENCERESULT_ID, SPI_E_UNINIT);
        returnValue = E_NOT_OK;
    }
    /* Check if the channel ID passed, is valid */
    if((E_OK  == returnValue) && (Sequence >= SPI_MAX_SEQUENCE))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETSEQUENCERESULT_ID, SPI_E_PARAM_SEQ);
        returnValue = E_NOT_OK;
    }  	
    /* Check if any DET error has occurred */
    if(E_OK  == returnValue)
    #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    {
        seqResultValue = seqIndex->SpiSeqResult;
    }
    
    /** @req SPI039 SPI042 */
    return(seqResultValue);
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"


#if ((SPI_LEVEL_DELIVERED == SPI_ZERO)|| (SPI_LEVEL_DELIVERED == SPI_TWO))
/*===========================================================================*/
/* Function Name        :Spi_SyncTransmit                                    */
/* Service ID           :0x0A                                                */
/* Description          :Service to transmit data on the SPI bus by sync mode*/
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :Sequence                                            */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Std_ReturnType                                      */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, SPI_CODE)Spi_SyncTransmit(Spi_SequenceType Sequence)
{
    Std_ReturnType rtVal = E_NOT_OK;
    Std_ReturnType returnValue = E_OK;
    P2VAR(SpiSequenceUnitType, AUTOMATIC, SPI_VAR) seqIndex = &Spi_SequenceUnit[Sequence];

    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if(SPI_UNINIT  == Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SYNCTRANSMIT_ID, SPI_E_UNINIT);
        returnValue = E_NOT_OK;
    }
    /* Check if the channel ID passed, is valid */
    if((E_OK  == returnValue) && (Sequence >= SPI_MAX_SEQUENCE))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SYNCTRANSMIT_ID, SPI_E_PARAM_SEQ);
        returnValue = E_NOT_OK;
    }  	
    if((E_OK  == returnValue) && (SPI_BUSY ==  Spi_Status))
    {
    	Det_ReportError(SPI_MODULE_ID, 0, SPI_SYNCTRANSMIT_ID, SPI_E_SEQ_IN_PROCESS);
    	returnValue = E_NOT_OK;
    }
    
    /* Check if any DET error has occurred */
    if(E_OK  == returnValue)
    #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    {
         /** @req SPI134 */
         Spi_Status = SPI_BUSY;
     
         rtVal = Spi_WriteSeq(seqIndex);
     
         if(E_OK == rtVal)
         {
             Spi_Status = SPI_IDLE;
	         returnValue = E_OK;
         }
         else
         {
             Spi_Status = SPI_BUSY;
	         returnValue = E_NOT_OK;
         }
 	
    }
    return(returnValue);
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (SPI_HW_STATUS_API == STD_ON)
/*===========================================================================*/
/* Function Name        :Spi_GetHWUnitStatus                                 */
/* Service ID           :0x0b                                                */
/* Description          :This service returns the status of the specified    */
/*   SPI Hardware  microcontroller peripheral.                               */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :HWUnit                                              */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :Spi_StatusType                                      */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Spi_StatusType, SPI_CODE)Spi_GetHWUnitStatus(Spi_HWUnitType HWUnit)
{
    Std_ReturnType returnValue = E_OK;
    Spi_StatusType hwUnitStatusValue = SPI_UNINIT;

    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if(SPI_UNINIT  == Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETHWUNITSTATUS_ID, SPI_E_UNINIT);
        returnValue = E_NOT_OK;
    }
    /* Check if the channel ID passed, is valid */
    if((E_OK  == returnValue) && (HWUnit >= SPI_CONTROLLER_NUM))
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_GETHWUNITSTATUS_ID, SPI_E_PAPAM_UNIT);
        returnValue = E_NOT_OK;
    }  	
    /* Check if any DET error has occurred */
    if(E_OK  == returnValue)
    #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    {
        hwUnitStatusValue = Spi_HWUnitStatus[HWUnit];
    }

    return(hwUnitStatusValue);
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (SPI_CANCEL_API == STD_ON)
/*===========================================================================*/
/* Function Name        :Spi_Cancel                                          */
/* Service ID           :0x0c                                                */
/* Description          :Service to cancel SPI Sequence.                     */
/* Sync/Async           :Asynchronous                                        */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :Sequence                                            */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SPI_CODE) Spi_Cancel(Spi_SequenceType Sequence)
{
    P2VAR(SpiSequenceUnitType, AUTOMATIC, SPI_VAR)seqIndex = &Spi_SequenceUnit[Sequence];

    if(seqIndex->SpiSeqResult== SPI_SEQ_PENDING)
    {
        seqIndex->SpiSeqResult = SPI_SEQ_CANCELLED;
    }
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"

#endif

#if (SPI_LEVEL_DELIVERED == SPI_TWO)
/*===========================================================================*/
/* Function Name        :Spi_SetAsyncMode                                    */
/* Service ID           :0x0d                                                */
/* Description          :Service to set the asynchronous mechanism mode for  */
/*   SPI busses handled asynchronously.                                      */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :Mode                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, SPI_CODE) Spi_SetAsyncMode(Spi_AsyncModeType Mode)
{
    Std_ReturnType returnValue = E_OK;
	
    #if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* Check if SPI Driver is initialized */
    if(SPI_UNINIT  == Spi_Status)
    {
        /* Report to DET */
        Det_ReportError(SPI_MODULE_ID, SPI_INSTANCE_ID, SPI_SETASYNCMODE_ID, SPI_E_UNINIT);
        returnValue = E_NOT_OK;
    }
    else
    #endif /* SPI_DEV_ERROR_DETECT == STD_ON */
    {
	    if(Spi_Mode == SPI_INTERRUPT_MODE)
	    {
	        /** @req SPI171 */
	        if(Spi_Status != SPI_IDLE)
	        {
	            returnValue = E_NOT_OK;
	        }
	        else
	        {
	            /** @req SPI152 */
	            Spi_Mode = Mode;
	        }
	    }
	    else
	    {
	         Spi_Mode = Mode;
	    }
    }

    return(returnValue);
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*===========================================================================*/
/* Function Name        :Spi_MainFunction_Driving                            */
/* Service ID           :0x11                                                */
/* Description          :Service to handling SPI Sequence.                   */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :None                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SPI_CODE)Spi_MainFunction_Driving (void)
{
    Std_ReturnType rtVal = E_NOT_OK;
    P2VAR(SpiSequenceUnitType, AUTOMATIC, SPI_VAR)seqIndex = &Spi_SequenceUnit[Spi_Global.SequenceId];
    
    if((Spi_Global.AsyncTransferNow == TRUE) && (Spi_Global.TransMode == SPI_ASYNC))
    {
        rtVal = Spi_WriteSeq(seqIndex);
        
        if(E_OK == rtVal)
        {
          	seqIndex->SpiSeqResult = SPI_SEQ_OK;
          	Spi_Status = SPI_IDLE;
        }
        else
        {
          	seqIndex->SpiSeqResult = SPI_SEQ_PENDING;
          	Spi_Status = SPI_BUSY;
        }

        Spi_Global.AsyncTransferNow = FALSE;
    }
    else
    {
        return;
    }
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"

#if (SPI_VERSION_INFO_API == STD_ON)
/*===========================================================================*/
/* Function Name        :Spi_GetVersionInfo                                  */
/* Service ID           :0x09                                                */
/* Description          :Service to Get Driver Version Information.          */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :None                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SPI_CODE)Spi_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA)versioninfo)
{
    /* Copy the vendor Id */
    versioninfo->vendorID = SPI_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = SPI_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = SPI_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = SPI_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = SPI_SW_PATCH_VERSION;
    /* Copy AUTOSAR Major version */
    versioninfo->ar_major_version = SPI_AR_MAJOR_VERSION;
    /* Copy AUTOSAR Minor Version */
    versioninfo->ar_minor_version = SPI_AR_MINOR_VERSION;
    /* Copy AUTOSAR Patch Version */
    versioninfo->ar_patch_version = SPI_AR_PATCH_VERSION;
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*===========================================================================*/
/* Function Name        :Spi_DriverSetBusAttr                                */
/* Service ID           :None                                                */
/* Description          :Service for SPI Driver Set SPI Bus Attribution      */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :jobconfig                                           */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, SPI_CODE)Spi_SetSpiBusAttr(SpiJobConfigType jobconfig)
{
    uint16 i;
	uint32 preBr;
	STATIC uint8 Spi_ClkTablePbr[] = {2,3,5,7};
	
	STATIC uint16 Spi_ClkTableBr[] = {2,4,6,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768 };

    volatile struct P2VAR(DSPI_tag, AUTOMATIC, SPI_VAR)dspiHW = DSPI(jobconfig.SpiHwUnit);

	/*Clock Polarity*/
	/*0--->SCK idle level is low ;   1--->SCK idle level is high*/
	dspiHW->CTAR[0].B.CPOL = jobconfig.DeviceAssignment.SpiShiftClockIdleLevel;

	/*Clock Phase*/
	/*0---Data is captured on the leading edge of SCK and changed on the following edge*/
	/*1---Data is changed on the leading edge of SCK and captured on the following edge*/
	dspiHW->CTAR[0].B.CPHA = jobconfig.DeviceAssignment.SpiDataShiftEdge;

	/*Not Support such as Cs2Sck Delay, Sck2Cs Delay and Delay between frames yet*/

	/* Added by Eric . To support Cs2Sck Delay, and Sck2Cs Delay. */
	dspiHW->CTAR[0].B.PCSSCK = PCS2SCK; // 0x03;
	dspiHW->CTAR[0].B.CSSCK = CS2SCK; //0x01;
	dspiHW->CTAR[0].B.PASC = PASCT;
	dspiHW->CTAR[0].B.ASC = ASCT;
	dspiHW->CTAR[0].B.PDT = PDTT;
	dspiHW->CTAR[0].B.DT = DTT;

	/* BAUDRATE CALCULATION
	 * -----------------------------
	 * Baudrate = Fsys/ PBR * ( 1+ DBR) / BR
	 * PBR range: 2,3,5,7
	 * DBR range: 0,1
	 * BR   range: 2,4,6,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768
	 *
	 * To make this easy set DBR = 0 and PBR=2 !!!
	 * --> BR=Fsys/(Baudrate.* 2 )
	*/
	dspiHW->CTAR[0].B.DBR = 0;
	dspiHW->CTAR[0].B.PBR = 0;
	preBr = Spi_SysClock/(jobconfig.DeviceAssignment.SpiBaudrate * Spi_ClkTablePbr[dspiHW->CTAR[0].B.PBR]);

	/* Find closest lesser */
	for(i = 0; i < (sizeof(Spi_ClkTableBr)/sizeof(Spi_ClkTableBr[0])); i++)
	{
		if(Spi_ClkTableBr[i] >= preBr)
		{
			break;
		}
	}

	/* set it */
	dspiHW->CTAR[0].B.BR = i;

	return;
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Spi_HWDeInit                                        */
/* Service ID           :None                                                */
/* Description          :Service for SPI DeInit.                             */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :None                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, SPI_CODE)Spi_HWDeInit(void)
{
    uint16 i,j;
    
    for(i = 0; i < SPI_CONTROLLER_NUM; i++)
    {
        Spi_HWUnitStatus[i] = SPI_UNINIT;
    }
		
    /* Configure DSPI_B as master */
    DSPI_B.MCR.R = 0x00000001;
    /* Configure CTAR0  */
    DSPI_B.CTAR[0].R = 0x00000000;

    /* Configure DSPI_C as master */
    DSPI_C.MCR.R = 0x00000001;
    /* Configure CTAR0  */
    DSPI_C.CTAR[0].R = 0x00000000;

    for(i = 0; i < (uint8)SPI_CONTROLLER_NUM; i++)
    {
    	for(j = 0; j < SPI_TX_RX_BUFFER_LEN; j++)
    	{
    		Spi_Tx_Buffer[i][j] = ZERO;
        	Spi_Rx_Buffer[i][j] = ZERO;	
    	}
    }

    Spi_Count = 0;

    for(i = 0; i < SPI_MAX_CHANNEL; i++)
    {
        Spi_ChannelUnit[i].length = ZERO;
        Spi_ChannelUnit[i].recvBufferPointer = NULL_PTR;
        Spi_ChannelUnit[i].sendBufferPointer = NULL_PTR;
        Spi_ChannelUnit[i].spichannel.SpiChannelId = (Spi_ChannelType)ZERO;
        Spi_ChannelUnit[i].spichannel.SpiChannelTp = SPI_EB;
        Spi_ChannelUnit[i].spichannel.SpiDataWidth = ZERO;
        Spi_ChannelUnit[i].spichannel.SpiDefaultData = ZERO;
        Spi_ChannelUnit[i].spichannel.SpiEbMaxLength = ZERO;
        Spi_ChannelUnit[i].spichannel.SpiIbNBuffers = ZERO;
        Spi_ChannelUnit[i].spichannel.SpiTransferStart = SPI_MSB;
    }

    for(i = 0; i < SPI_MAX_JOB; i++)
    {
        Spi_JobUnit[i].spijob.DeviceAssignment.SpiBaudrate = ZERO;
        Spi_JobUnit[i].spijob.DeviceAssignment.SpiCsIdentifier = ZERO;
        Spi_JobUnit[i].spijob.DeviceAssignment.SpiCsPolarity = SPI_LOW;
        Spi_JobUnit[i].spijob.DeviceAssignment.SpiDataShiftEdge = SPI_LEADING;
        Spi_JobUnit[i].spijob.DeviceAssignment.SpiEnableCs = ZERO;
        Spi_JobUnit[i].spijob.DeviceAssignment.SpiShiftClockIdleLevel = SPI_IDLE_LOW;
        Spi_JobUnit[i].spijob.DeviceAssignment.SpiTimeClk2Cs = ZERO;
        Spi_JobUnit[i].spijob.SpiHwUnit = SPI_CONTROLLER_B;
        Spi_JobUnit[i].spijob.SpiJobEndNotification = NULL_PTR;
        Spi_JobUnit[i].spijob.SpiJobId = (Spi_JobType)ZERO;
        Spi_JobUnit[i].spijob.SpiJobPriority = ZERO;
        Spi_JobUnit[i].SpiJobResult = SPI_JOB_OK;
    }
	
    for(i = 0; i < SPI_MAX_SEQUENCE; i++)
    {
        Spi_SequenceUnit[i].spisequence.SpiInterruptibleSequence = NOT_INTERRUPTIBLE;
        Spi_SequenceUnit[i].spisequence.SpiSeqEndNotification = NULL_PTR;
        Spi_SequenceUnit[i].spisequence.SpiSequenceId = (Spi_SequenceType)ZERO;
        Spi_SequenceUnit[i].SpiSeqResult = SPI_SEQ_OK;
    }
	
    for(i = 0; i < (SPI_MAX_CHANNEL * SPI_EB_MAX_LENGTH); i++)
    {
        Spi_PushrBuffer[i] = ZERO;
    }	
    Spi_Global.AsyncTransferNow = FALSE;
    Spi_Global.SequenceId = (Spi_SequenceType)ZERO;
    Spi_Global.TransMode = SPI_SYNC;
	
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Spi_InitController                                  */
/* Service ID           :None                                                */
/* Description          :Service to Initial SPI Controllers.                 */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :unit                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, SPI_CODE)Spi_InitController(uint8 unit)
{
    volatile struct P2VAR(DSPI_tag, AUTOMATIC, SPI_VAR)spiHw = DSPI(unit);

	/*Master Mode*/
	spiHw->MCR.B.MSTR = ONE;

	/*force halt*/
	spiHw->MCR.B.HALT = 0x1;

	/*Continuous SCK disable*/
	spiHw->MCR.B.CONT_SCKE = ZERO;

	/*No freeze, Run SPI when debugger is stopped*/
	spiHw->MCR.B.FRZ = ZERO;

    /* Enable FIFO's */
	spiHw->MCR.B.DIS_TXF = ONE;
	spiHw->MCR.B.DIS_RXF = ONE; 


	/*Flush TXFIFO & RXFIFO*/
	spiHw->MCR.B.CLR_TXF = ONE;
	spiHw->MCR.B.CLR_RXF = ONE;

	/* Set all CS0_x inactive state is high */
	spiHw->MCR.B.PCSIS0 = ONE;
	spiHw->MCR.B.PCSIS1 = ONE;
	spiHw->MCR.B.PCSIS2 = ONE;
	spiHw->MCR.B.PCSIS3 = ONE;
	spiHw->MCR.B.PCSIS4 = ONE;
	spiHw->MCR.B.PCSIS5 = ONE;

	
	/*Enable DSPI Clocks*/
	spiHw->MCR.B.MDIS = ZERO;

	/*running*/
	spiHw->MCR.B.HALT = 0x0;
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"


/*===========================================================================*/
/* Function Name        :Spi_WriteChannel                                    */
/* Service ID           :None                                                */
/* Description          :Service to write Channel.                           */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :HwUnit, channel                                     */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(Std_ReturnType, SPI_CODE)Spi_WriteChannel(Spi_ControllerUnitType HwUnit, uint8 channel)
{   
    uint8 i;
    uint32 clearValue;
    SpiEBTxRx spiEBtxrx = {ZERO};
    volatile struct P2VAR(DSPI_tag, AUTOMATIC, SPI_VAR)dspiHW = DSPI(HwUnit);

    dspiHW->CTAR[0].B.LSBFE = Spi_ChannelUnit[channel].spichannel.SpiTransferStart;
    dspiHW->CTAR[0].B.FMSZ  = Spi_ChannelUnit[channel].spichannel.SpiDataWidth - 1;

    /* Send IB Channel */
    if(Spi_ChannelUnit[channel].spichannel.SpiChannelTp == SPI_IB)
    {
		/*Send Assigned data*/
		for(i = 0; i < Spi_ChannelUnit[channel].spichannel.SpiIbNBuffers; i++)
		{
			/** @req SPI018 */
			while((dspiHW->SR.B.TFFF) != 1)
			{
			    /* Empty . */
			}
			
			dspiHW->PUSHR.R = Spi_PushrBuffer[Spi_Count];
			Spi_Count++;
			
			/* Clear TCF, RDRF, EOQ flags by writing 1 */
			dspiHW->SR.R = 0x90020000;

			/** @req SPI016 */
			while((dspiHW->SR.B.RFDF) != 1)
			{
			    /* Empty . */
			}
			
			Spi_Rx_Buffer[channel][i] = dspiHW->POPR.B.RXDATA;
			
			/* Clear TCF, RDRF, EOQ flags by writing 1 */
			dspiHW->SR.R = 0x90020000;
		}
        
        return(E_OK);
    }

    /*chindex->SpiChannelTp == SPI_EB*/  /* Send EB Channel */
    else
    {
        spiEBtxrx.sendbuf = Spi_ChannelUnit[channel].sendBufferPointer;
        spiEBtxrx.recvbuf = Spi_ChannelUnit[channel].recvBufferPointer;
        spiEBtxrx.len = Spi_ChannelUnit[channel].length;

        /* Send default data and  recv */
        if((spiEBtxrx.sendbuf == NULL) && (spiEBtxrx.recvbuf != NULL))
        {
            for(i = 0; i < spiEBtxrx.len; i++)	
            {
            	/* Wait to write TXFIFO */
            	while(dspiHW->SR.B.TFFF != 1)
		        {
			        /* Empty . */
		        }
				
            	dspiHW->PUSHR.R = Spi_PushrBuffer[Spi_Count];
		        Spi_Count++;
		
            	/* Wati to read RXFIFO*/
            	while(dspiHW->SR.B.RFDF != 1)
		        {
			        /* Empty . */
		        }
				
            	spiEBtxrx.recvbuf[i]= dspiHW->POPR.B.RXDATA;
            	/** @req SPI030 */
            	/* Clear TCF, RDRF, EOQ flags by writing 1 */
            	dspiHW->SR.R = 0x90020000;
            }
        }
        else if((spiEBtxrx.sendbuf == NULL) && (spiEBtxrx.recvbuf == NULL))
        {
        	for(i = 0; i < spiEBtxrx.len; i++)
        	{
        		/* Wait to write TXFIFO */
        		while(dspiHW->SR.B.TFFF != 1)
			    {
			        /* Empty . */
			    }
				
        		dspiHW->PUSHR.R = Spi_PushrBuffer[Spi_Count];
		    	Spi_Count++;
			
        		/* Wati to read RXFIFO*/
        		while(dspiHW->SR.B.RFDF != 1)
			    {
			        /* Empty . */
			    }
				
        		clearValue = dspiHW->POPR.B.RXDATA;
        		
        		/* Clear TCF, RDRF, EOQ flags by writing 1 */
        		dspiHW->SR.R = 0x90020000;
        	}
        }
        else if((spiEBtxrx.sendbuf != NULL) && (spiEBtxrx.recvbuf == NULL))
        {
        	for(i = 0; i < spiEBtxrx.len; i++)
        	{
        		/* Wait to write TXFIFO */
        		while(dspiHW->SR.B.TFFF != 1)
			    {
		    	    /* Empty . */
			    }
        		dspiHW->PUSHR.R = Spi_PushrBuffer[Spi_Count];
			    Spi_Count++;
			
        		while(dspiHW->SR.B.RFDF != 1)
			    {
			        /* Empty . */
		    	}
        		clearValue = dspiHW->POPR.B.RXDATA;
        		
        		/* Clear TCF, RDRF, EOQ flags by writing 1 */
        		dspiHW->SR.R = 0x90020000;
        	}
        }
        else
        {
        	for(i = 0; i < spiEBtxrx.len; i++)
            {
        		/* Wait to write TXFIFO*/
        		while(dspiHW->SR.B.TFFF != 1)
				{
			    	/* Empty . */
				}
        		dspiHW->PUSHR.R = Spi_PushrBuffer[Spi_Count];
				Spi_Count++;
			
        		/* Wati to read RXFIFO*/
        		while(dspiHW->SR.B.RFDF != 1)
				{
			    	/* Empty . */
				}
        		spiEBtxrx.recvbuf[i]= dspiHW->POPR.B.RXDATA;
        		/* Clear TCF, RDRF, EOQ flags by writing 1 */
        		dspiHW->SR.R = 0x90020000;
            }
        }
        
        return(E_OK);
    }
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Spi_WriteJob                                        */
/* Service ID           :None                                                */
/* Description          :Service to write Channel.                           */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :job                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(Std_ReturnType, SPI_CODE)Spi_WriteJob(P2CONST(SpiJobUnitType, AUTOMATIC, SPI_APPL_CONST)job)
{
    uint8 i,j,k,n;
    uint32 Spi_PushR = ZERO;
    uint32 tempPushR = ZERO;
    Std_ReturnType rtVal;
    P2VAR(SpiChannelUnitType, AUTOMATIC, SPI_VAR)chPtr = NULL_PTR;

    Spi_HWUnitStatus[job->spijob.SpiHwUnit] = SPI_BUSY;	

    /*Set bus attribute of this job, it means to setup CTAR*/	
    Spi_SetSpiBusAttr(job->spijob);

    /*Set SPI PUSHR Register CMD field*/
    tempPushR = (uint32)1u << ((uint32)16u + job->spijob.DeviceAssignment.SpiCsIdentifier);
    Spi_PushR = SPI_PUSHR_CMD |tempPushR ;

    i = ZERO;
    k = ZERO;
    n = ZERO;
    Spi_Count = ZERO;
	
    while((job->spijob.ChannelAssignment[i]) != NOT_VALID)
    {
    	
        chPtr = &Spi_ChannelUnit[job->spijob.ChannelAssignment[i]];
		
        if(chPtr->spichannel.SpiChannelTp == SPI_IB)
        {
 			for(j = 0; j < chPtr->spichannel.SpiIbNBuffers; j++)
        	{	
        		Spi_PushrBuffer[k] = Spi_PushR + Spi_Tx_Buffer[job->spijob.ChannelAssignment[i]][j];
		        k++;
        	}

        }
		else if(chPtr->spichannel.SpiChannelTp == SPI_EB)
		{
			if(chPtr->sendBufferPointer == NULL)
        	{
        		for(j = 0; j < chPtr->length; j++)
        		{
        			Spi_PushrBuffer[k] = Spi_PushR + chPtr->spichannel.SpiDefaultData;
				    k++;
        		}
        	}
        	else
        	{
        		for(j = 0; j < chPtr->length; j++)
        		{
        		       
        			Spi_PushrBuffer[k] = Spi_PushR + chPtr->sendBufferPointer[j];
			        k++;
        		}
        	}	
		}
		else
		{
			return(E_NOT_OK);
		}
		
		/*i++ To move  to next channel assignment*/
        i++;  
    }
    
    
    k = k -1;
    Spi_PushrBuffer[k] &= 0x7FFFFFFF;   /*Set PUSHR.B.CONT bit is 0*/

    i = ZERO;
    while(job->spijob.ChannelAssignment[i] != NOT_VALID)
    {
        rtVal = Spi_WriteChannel(job->spijob.SpiHwUnit, (uint8)(job->spijob.ChannelAssignment[i]));
		i++;
    }

    /*Job End Notification*/
    if(job->spijob.SpiJobEndNotification != NULL)
    {
    	job->spijob.SpiJobEndNotification();
    }
	
	/*Spi_Count = 0 let next job may use Spi_PushrBuffer[] Buffer*/
	Spi_Count = ZERO;
	
    Spi_HWUnitStatus[job->spijob.SpiHwUnit] = SPI_IDLE;

    return rtVal;
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"


/*===========================================================================*/
/* Function Name        :Spi_WriteSeq                                        */
/* Service ID           :None                                                */
/* Description          :Service to write sequence.                          */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Reentrant                                           */
/* Parameters[in]       :Sequence                                            */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SPI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(Std_ReturnType, SPI_CODE)Spi_WriteSeq(P2VAR(SpiSequenceUnitType, AUTOMATIC, SPI_VAR)seq)
{
    uint8 i = ZERO;
    Std_ReturnType rtVal;     
    P2VAR(SpiJobUnitType, AUTOMATIC, SPI_VAR)jobIndex = NULL_PTR;
 
    if(seq->SpiSeqResult == SPI_SEQ_CANCELLED)
    {
        /* Added by Eric. When a valid notification function pointer is configured, the SPI Driver shall call this notification. */
	 if(seq->spisequence.SpiSeqEndNotification != NULL)
        {
    	    seq->spisequence.SpiSeqEndNotification();
        }
		
        return(E_NOT_OK);
    }

    seq->SpiSeqResult = SPI_SEQ_PENDING;

    while(seq->spisequence.JobAssignment[i] != NOT_VALID)
    {
    	jobIndex = &Spi_JobUnit[seq->spisequence.JobAssignment[i]];
	    i++;
	    
        jobIndex->SpiJobResult = SPI_JOB_PENDING;

        rtVal = Spi_WriteJob(jobIndex);
			
        if(rtVal == E_OK)
        {
        	jobIndex->SpiJobResult = SPI_JOB_OK;
        }
        else
        {
        	jobIndex->SpiJobResult = SPI_JOB_FAILED;
        	seq->SpiSeqResult = SPI_SEQ_FAILED;
        	return (E_NOT_OK);
        }
    }

    seq->SpiSeqResult = SPI_SEQ_OK;

    /*Sequence End Notification*/
    if(seq->spisequence.SpiSeqEndNotification != NULL)
    {
    	seq->spisequence.SpiSeqEndNotification();
    }

    return(E_OK);
}
#define SPI_STOP_SEC_CODE
#include "MemMap.h"


/*=======[E N D   O F   F I L E]==============================================*/



