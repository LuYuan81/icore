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
#ifndef  SPI_H
#define  SPI_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20130427  James       Initial version
 */
/*============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define SPI_VENDOR_ID              0
#define SPI_MODULE_ID            102
/* AUTOSAR specification version information */
#define SPI_AR_MAJOR_VERSION       2
#define SPI_AR_MINOR_VERSION       2
#define SPI_AR_PATCH_VERSION       2
/* File version information */
#define SPI_SW_MAJOR_VERSION       1
#define SPI_SW_MINOR_VERSION       0
#define SPI_SW_PATCH_VERSION       0
#define SPI_VENDOR_API_INFIX       0

/*=======[I N C L U D E S]====================================================*/
#include "Spi_Cfg.h"
#include "Std_Types.h"
#include "Std_ExtTypes.h"

#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"

/*=======[M A C R O S]========================================================*/
#define SPI_TX_RX_BUFFER_LEN			16

#define NOT_VALID          (uint32)(0xFFFF)

#define SPI_PUSHR_CMD      0x80000000

#define SPI_ZERO           (0x00u)
#define SPI_ONE            (0x01u)
#define SPI_TWO            (0x02u)
#define SPI_THREE          (0x03u)

/* exp = 0, 1 */
#define DSPI(exp) (volatile struct DSPI_tag *)  ((uint32)0xFFF94000 + (uint32)(0x4000 * (exp)))  

#define ARRAY_SIZE(_x) (sizeof(_x) / sizeof((_x)[0]))

/*Definition Of Autosar API Ids*/
#define SPI_INIT_ID                          0x00
#define SPI_DEINIT_ID                        0x01
#define SPI_WRITEIB_ID                       0x02
#define SPI_ASYNCTRANSMIT_ID                 0x03
#define SPI_READIB_ID                        0x04
#define SPI_SETUPEB_ID                       0x05
#define SPI_GETSTATUS_ID                     0x06
#define SPI_GETJOBRESULT_ID                  0x07
#define SPI_GETSEQUENCERESULT_ID             0x08
#define SPI_GETVERSIONINFO_ID                0x09
#define SPI_SYNCTRANSMIT_ID                  0x10
#define SPI_GETHWUNITSTATUS_ID               0x11
#define SPI_CANCEL_ID                        0x12
#define SPI_SETASYNCMODE_ID                  0x13

/*Definition Of Error classification*/
#define SPI_E_PARAM_CHANNEL                  0x0A
#define SPI_E_PARAM_JOB                      0x0B
#define SPI_E_PARAM_SEQ                      0x0C
#define SPI_E_PARAM_LENGTH                   0x0D
#define SPI_E_PAPAM_UNIT                     0x0E
#define SPI_E_UNINIT                         0x1A
#define SPI_E_SEQ_PENDING                    0x2A
#define SPI_E_SEQ_IN_PROCESS                 0x3A
#define SPI_E_ALREADY_INITIALIZED            0x4A

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/** @req SPI164 */
typedef uint8       Spi_DataType;

/** @req SPI165 */
typedef uint16      Spi_NumberOfDataType;

/** @req SPI169 */
typedef uint8	    Spi_HWUnitType;

typedef uint8       IntegerParamDef;
typedef boolean     BooleanParaDef;
typedef uint8       StringParamDef;
typedef uint32      FloatParamDef;

typedef void (*FunctionNameDef)(void);

typedef enum
{
    SPI_SYNC = 0,
    SPI_ASYNC
}Spi_TransModeType;

/** @req SPI061 */
/* Definition of status type */
typedef enum
{
    SPI_UNINIT = 0,
    SPI_IDLE,
    SPI_BUSY
}Spi_StatusType;


/** @req SPI049 SPI051 SPI012*/
/* Definition of Job Result type */
typedef enum
{
    SPI_JOB_OK=0,
    SPI_JOB_PENDING,
    SPI_JOB_FAILED
}Spi_JobResultType;

/** @req SPI017 */
/* Definition of Sequence Result type */
typedef enum
{
    SPI_SEQ_OK = 0,
    SPI_SEQ_PENDING,
    SPI_SEQ_FAILED,
    SPI_SEQ_CANCELLED
}Spi_SeqResultType;

/* Definition of type for asynchronous mode */
typedef enum
{
    SPI_POLLING_MODE,
    SPI_INTERRUPT_MODE
}Spi_AsyncModeType;


typedef enum
{
    SPI_EB,
    SPI_IB
}ChannelBuffType;


typedef enum
{
    SPI_MSB = 0,
    SPI_LSB
}TransferStartType;


typedef enum
{
    SPI_LOW = 0,
    SPI_HIGH
}PolarityType;


typedef enum
{
    SPI_LEADING = 0,
    SPI_TRAILING
}ShiftEdgeType;


typedef enum
{
    SPI_IDLE_LOW = 0,
    SPI_IDLE_HIGH
}ShiftClockLevelType;


typedef enum
{
    NOT_INTERRUPTIBLE = 0,
    INTERRUPTIBLE
}InterruptType;


/** @req SPI093 */
typedef enum
{
    PRIORITY_0 = 0,
    PRIORITY_1,
    PRIORITY_2,
    PRIORITY_3
}Spi_PriorityType;


/* MPC5633M have 2 SPI : DSPI_B and DSPI_C */
typedef enum
{
    SPI_CONTROLLER_B = 0,
    SPI_CONTROLLER_C,
    SPI_CONTROLLER_NUM
}Spi_ControllerUnitType;


typedef struct
{
    uint32            SpiBaudrate;

    /* the symbolic name to identify the Chip Select(CS) allocated to this Job*/
    uint32            SpiCsIdentifier;

    /* define the active polarity of chip select*/
    PolarityType      SpiCsPolarity;

    /* define the SPI data shift edge*/
    ShiftEdgeType     SpiDataShiftEdge;

    /* enables or not the Chip Select handling function*/
    uint8          	  SpiEnableCs;

    /* define the SPI shift clock idle level*/
    ShiftClockLevelType  SpiShiftClockIdleLevel;

    /* timing between clock and chip select*/
    uint32            SpiTimeClk2Cs;

}SpiExternalDeviceConfigType;

typedef struct
{
    Spi_SequenceType        	SpiSequenceId;
    InterruptType           	SpiInterruptibleSequence;
    FunctionNameDef         	SpiSeqEndNotification;
    uint32                   	JobAssignment[SPI_MAX_JOB + 1];
}SpiSequenceConfigType;


typedef struct
{
    Spi_JobType	         		SpiJobId;
    Spi_ControllerUnitType  	SpiHwUnit;
    FunctionNameDef         	SpiJobEndNotification;
    uint8			         	SpiJobPriority;
    uint32		                ChannelAssignment[SPI_MAX_CHANNEL + 1];
    SpiExternalDeviceConfigType DeviceAssignment;
}SpiJobConfigType;


typedef struct
{
    Spi_ChannelType         	SpiChannelId;
    ChannelBuffType         	SpiChannelTp;
    uint8			         	SpiDataWidth;
    uint8			         	SpiDefaultData;
    Spi_NumberOfDataType        SpiEbMaxLength;
    Spi_NumberOfDataType        SpiIbNBuffers;
    TransferStartType       	SpiTransferStart;
}SpiChannelConfigType;


typedef struct
{
    uint8			                  SpiMaxChannel;
    uint8		                      SpiMaxJob;
    uint8			            	  SpiMaxSequence;
    const SpiChannelConfigType	      *spiChannelConfig;
    const SpiJobConfigType			  *spiJobConfig;
    const SpiSequenceConfigType       *spiSeqConfig;
}Spi_DriverType;


/** @req SPI008 SPI063 SPI009 SPI064*/
typedef Spi_DriverType 	Spi_ConfigType;

/** @req SPI049 SPI051 */
typedef struct
{
    SpiChannelConfigType		spichannel;
    const Spi_DataType          *sendBufferPointer;
    Spi_DataType                *recvBufferPointer;
    uint16                      length;
}SpiChannelUnitType;


typedef struct
{
	SpiJobConfigType			spijob;
    Spi_JobResultType           SpiJobResult;
}SpiJobUnitType;


typedef struct
{
	SpiSequenceConfigType		spisequence;
    Spi_SeqResultType           SpiSeqResult;
}SpiSequenceUnitType;

typedef struct
{
    const Spi_DataType        	*sendbuf;
    Spi_DataType        		*recvbuf;
    uint16              		len;
    uint16              		datawidth;
    uint32              		defaultData;
}SpiEBTxRx;



typedef struct
{
    boolean    AsyncTransferNow;
    Spi_SequenceType  SequenceId;
    Spi_TransModeType TransMode;
}Spi_GlobalType;



/*=======[E X T E R N A L   D A T A]==========================================*/
extern VAR(Spi_AsyncModeType, SPI_VAR_NOINIT) Spi_Mode;

extern VAR(uint32, SPI_VAR_NOINIT) Spi_SysClock;

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

#define SPI_START_SEC_CODE
#include "MemMap.h"
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
extern FUNC(void, SPI_CODE) Spi_Init(
            P2CONST(Spi_ConfigType, AUTOMATIC, SPI_APPL_CONST) ConfigPtr);

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
extern FUNC(Std_ReturnType, SPI_CODE) Spi_DeInit(void);

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
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_ZERO)|| \
     (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO))
extern FUNC(Std_ReturnType, SPI_CODE) Spi_WriteIB 
   (Spi_ChannelType Channel, 
    P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_CONST) DataBufferPtr);
#endif 

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
#if ((SPI_LEVEL_DELIVERED == SPI_ONE)||(SPI_LEVEL_DELIVERED == SPI_TWO))
extern FUNC(Std_ReturnType, SPI_PCODE) Spi_AsyncTransmit(Spi_SequenceType Sequence);
#endif /* SPI_LEVEL_DELIVERED == SPI_ONE || SPI_LEVEL_DELIVERED == SPI_TWO */

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
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_ZERO)|| \
     (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO))
extern FUNC(Std_ReturnType, SPI_CODE) Spi_ReadIB
           (Spi_ChannelType Channel, 
            P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DataBufferPointer);
#endif /* SPI_CHANNEL_BUFFERS_ALLOWED == SPI_ZERO || 
          SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO */

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
#if ((SPI_CHANNEL_BUFFERS_ALLOWED == SPI_ONE)|| \
     (SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO))
extern FUNC(Std_ReturnType, SPI_CODE) Spi_SetupEB
    (Spi_ChannelType Channel,
     P2CONST(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) SrcDataBufferPtr,
     P2VAR(Spi_DataType, AUTOMATIC, SPI_APPL_DATA) DesDataBufferPtr,
     Spi_NumberOfDataType Length);
#endif /* SPI_CHANNEL_BUFFERS_ALLOWED == SPI_ONE || 
          SPI_CHANNEL_BUFFERS_ALLOWED == SPI_TWO */

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
extern FUNC(Spi_StatusType, SPI_CODE)Spi_GetStatus(void);

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
extern FUNC(Spi_JobResultType, SPI_CODE)Spi_GetJobResult(Spi_JobType Job);    

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
extern FUNC(Spi_SeqResultType, SPI_CODE)Spi_GetSequenceResult(Spi_SequenceType Sequence);

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
#if (SPI_VERSION_INFO_API == STD_ON)
extern FUNC(void, SPI_CODE)Spi_GetVersionInfo
                   (P2VAR(Std_VersionInfoType, AUTOMATIC, SPI_APPL_DATA)versioninfo);
#endif

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
#if ((SPI_LEVEL_DELIVERED == SPI_ZERO)||(SPI_LEVEL_DELIVERED == SPI_TWO))
extern FUNC(Std_ReturnType, SPI_PUBLIC_CODE) Spi_SyncTransmit(Spi_SequenceType Sequence);
#endif

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
#if (SPI_HW_STATUS_API == STD_ON)
extern FUNC(Spi_StatusType, SPI_CODE)Spi_GetHWUnitStatus(Spi_HWUnitType HWUnit);
#endif

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
#if (SPI_CANCEL_API == STD_ON)
extern FUNC(void, SPI_CODE)Spi_Cancel(Spi_SequenceType Sequence);
#endif

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
#if (SPI_LEVEL_DELIVERED == SPI_TWO)
extern FUNC(Std_ReturnType, SPI_CODE)Spi_SetAsyncMode(Spi_AsyncModeType Mode);
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
#if ((SPI_LEVEL_DELIVERED == SPI_ONE)|| (SPI_LEVEL_DELIVERED == SPI_TWO))
extern FUNC(void, SPI_CODE)Spi_MainFunction_Driving(void);
#endif

#define SPI_STOP_SEC_CODE
#include "MemMap.h"


#endif /* endof SPI_H */

/*=======[E N D   O F   F I L E]==============================================*/


