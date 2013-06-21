/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <Adc.h>
 *  @brief      <This is adc header file>
 *  
 *  <Compiler: cw2.6    MCU:mpc5634>
 *  
 *  @author     <author name>
 *  @date       <dd-mm-yyyy>
 */
/*============================================================================*/
#ifndef ADC_H_
#define ADC_H_

#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"
/*=======[M I S R A  R U L E  V I O L A T I O N]==============================*/
/* MISRA-C:2004 Rule 3.4  */
/* MISRA-C:2004 Rule 8.12; Arrray declared with unknown size*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20081127    xxx       Initial version
 * 
 *  V1.1.0       20091012    xxx      
 * 
 *  V2.0.0       20100210    xxx       
 */
/*============================================================================*/
/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
#include "Adc_Cfg.h"
#include "Std_ExtTypes.h"
#include "Dma.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
/* Software version information */ 
#define ADC_SW_MAJOR_VERSION  1
#define ADC_SW_MINOR_VERSION  0
#define ADC_SW_PATCH_VERSION  0

/* AUTOSAR specification version information */
#define ADC_AR_MAJOR_VERSION  3
#define ADC_AR_MINOR_VERSION  0
#define ADC_AR_PATCH_VERSION  3

/* ADC030 */
/* ADC099 */
#define ADC_VENDOR_ID			1
#define ADC_MODULE_ID			MODULE_ID_ADC
#define ADC_INSTANCE_ID       	0


/*=======[M A C R O S]========================================================*/
#define ADC_ZERO 0
#define ADC_ONE	 1
#define	ADC_TWO	 2
#define ADC_THREE 3
#define ADC_FOUR 4
#define ADC_FIVE 5
#define ADC_SIX  6
#define ADC_SEVEN 7
#define ADC_15M  15000000
#define ADC_EN	0x8000
#define ADC_ACRSEL  8

#define Unit_Number    					1
#define ONCE_MAX_ENTRY					4
#define ADC_SUM_OF_GROUP    			6
#define ADC_SUM_OF_CHANNELS   			44
#define ADC_MIDCHNUM					39
#define ADC_RSRVCHNUM					56

#define ADC_FEDGE_ONESHOT				0x0440
#define ADC_FEDGE_CONTINU				0x00C0
#define ADC_REDGE_ONESHOT				0x0450
#define ADC_REDGE_CONTINU				0x00D0
#define ADC_BEDGE_ONESHOT				0x0460
#define ADC_BEDGE_CONTINU				0x00E0
#define ADC_SSCAN 						0x0410
/*================SERVICE ID=================================================*/

#define ADC_E_UNINIT              		0x0A
#define ADC_E_BUSY                		0x0B
#define ADC_E_IDLE                		0x0C
#define ADC_E_ALREADY_INITIALIZED 		0x0D
#define ADC_E_PARAM_CONFIG        		0x0E
#define ADC_E_PARAM_GROUP         		0x15
#define ADC_E_WRONG_CONV_MODE     		0x16
#define ADC_E_WRONG_TRIGG_SRC     		0x17
#define ADC_E_NOTIF_CAPABILITY    		0x18
#define ADC_E_BUFFER_UNINIT       		0x19

#define ADC_INIT_ID 					0x00
#define ADC_DEINIT_ID 					0x01
#define ADC_STARTGROUPCONVERSION_ID 	0x02
#define ADC_STOPGROUPCONVERSION_ID 		0x03
#define ADC_READGROUP_ID 				0x04
#define ADC_ENABLEHARDWARETRIGGER_ID 	0x05
#define ADC_DISBALEHARDWARETRIGGER_ID 	0x06
#define ADC_ENABLEGROUPNOTIFICATION_ID 	0x07
#define ADC_DISABLEGROUPNOTIFICATION_ID 0x08
#define ADC_GETGROUPSTATUS_ID 			0x09
#define ADC_GETVERSIONINFO_ID 			0x0A
#define ADC_GETSTREAMLASTPOINTER_ID 	0x0B
#define ADC_SETUPRESULTBUFFER_ID 		0x0C
#define ADC_E_PARAM_POINTER             0xEE


/* 
 * Helper macro to make sure that the qommand queue have executed 
 * the commands in the fifo First check that the H/W negate the single 
 * scan bit and then wait for EOQ.  \
while (EQADC.FISR[q].B.EOQF == 0) \
{ \
}
 */
#define	WAIT_FOR_QUEUE_TO_FINISH(q) \
while (EQADC.FISR[q].B.SSS == 1) \
{\
}\
\
while(EQADC.FISR[q].B.EOQF != 1)\
{\
}

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/* User free defination data Type for EQADC register defination. */
typedef uint32 Adc_EQADCRegister;

/*	User free defination data Type for Conversion Cammand for Standard 
 *	Configration.
 */
typedef union
{
	vuint32_t R;
	struct
	{
		vuint32_t EOQ:1;
		vuint32_t PAUSE:1;
		vuint32_t :4;
		vuint32_t BN:1;
		vuint32_t CAL:1;
		vuint32_t MESSAGE_TAG:4;
		vuint32_t LST:2;
		vuint32_t TSR:1;
		vuint32_t FMT:1;
		vuint32_t ADC_CHANNEL_NUMBER:8;
		vuint32_t :8;
	} B;
}Adc_StandardConfigType;

/*
 *	User free defination data Type for Conversion Cammand for Alternate 
 *	Configration.
 */
typedef union
{
	vuint32_t R;
	struct
	{
		vuint32_t EOQ:1;
		vuint32_t PAUSE:1;
		vuint32_t :4;
		vuint32_t BN:1;
		vuint32_t CAL:1;
		vuint32_t MESSAGE_TAG:4;
		vuint32_t LST:2;
		vuint32_t TSR:1;
		vuint32_t FFMT:1;
	    vuint32_t ADC_CHANNEL_NUMBER:8;
	    vuint32_t ALT_CONFIG_SEL:8;		
	}B;	
}Adc_AlternateConfigType;

/*	User free defination data Type for writing register command data type.*/

typedef union
{
  	uint32 R;
  	struct
  	{
	    uint32 EOQ:1;
	    uint32 PAUSE:1;
	    uint32 :4;
	    uint32 BN:1;
	    uint32 RW:1;
	    uint32 ADC_REG:16;
	    uint32 ADC_REG_ADDR:8;
   	} B;
}Adc_RegisterWriteType;
/*	User free defination data Type for writing register of ACR.*/
typedef union
{
  	vuint16_t R;
  	struct
  	{
	    vuint16_t RET_INT:1;
	    vuint16_t:1;
	    vuint16_t DEST:4;
	    vuint16_t FMTA:1;
	    vuint16_t:1;
	    vuint16_t RESSEL:2;
	    vuint16_t :2;
	    vuint16_t ATBSEL:2;
	    vuint16_t PREGAIN:2;
   	} B;
}Adc_ACR_Type;

typedef union
{
	vuint16_t R;
	struct
	{
		vuint16_t:1;
		vuint16_t ALTGCC:15;
	}B;
}Adc_AGR_Type;
/*	User free defination data Type for all group IDs.*/
typedef enum
{
  	ADC_GROUP0,
  	ADC_GROUP1,
  	ADC_GROUP2,
  	ADC_GROUP3,
  	ADC_GROUP4,
  	ADC_GROUP5
}Adc_GroupIDType;

/*	User free defination data Type for transfering way.*/
typedef enum
{
	ADC_INTERRUPT,
	ADC_DMA	
}Adc_TransferWayType;

/*	User free defination data Type for all group status.*/
typedef enum
{
  	EQADC_CFIFO_STATUS_IDLE = 0,
  	EQADC_CFIFO_STATUS_WAITINGFOR_TRIGGER = 0x2,
  	EQADC_CFIFO_STATUS_TRIGGERED = 0x3
}Adc_EQADCQueueStatusType;

/*	User free defination data Type for all possible used registers.*/
typedef enum
{
  ADC0_CR = 1,
  ADC0_TSCR = 2,
  ADC0_TBCR = 3,
  ADC0_GCCR = 4,
  ADC0_OCCR = 5,
  ADC_ACR1 = 0x30,
  ADC_ACR2 = 0x34,
  ADC_ACR3 = 0x38,
  ADC_ACR4 = 0x3C,
  ADC_ACR5 = 0x40,
  ADC_ACR6 = 0x44,
  ADC_ACR7 = 0x48,
  ADC_ACR8 = 0x4C,
  ADC_AGR   = 0x31

}Adc_EQADCRegisterType;

/*	User free defination data Type for all possible used channel IDs.*/
typedef enum
{
  	ADC_CH0 = 0,
  	ADC_CH1 = 1,
  	ADC_CH2 = 2,
  	ADC_CH3 = 3,
  	ADC_CH4 = 4,
  	ADC_CH5 = 5,
  	ADC_CH6 = 6,
  	ADC_CH7 = 7,
  	ADC_CH8 = 8,
  	ADC_CH9 = 9,
  	ADC_CH10 = 10,
  	ADC_CH11 = 11,
  	ADC_CH12 = 12,
  	ADC_CH13 = 13,
  	ADC_CH14 = 14,
  	ADC_CH15 = 15,
  	ADC_CH16 = 16,
  	ADC_CH17 = 17,
  	ADC_CH18 = 18,
  	ADC_CH19 = 19,		/* not exist */
  	ADC_CH20 = 20,		/* not exist */
  	ADC_CH21 = 21,
  	ADC_CH22 = 22,
  	ADC_CH23 = 23,
  	ADC_CH24 = 24,
  	ADC_CH25 = 25,
  	ADC_CH26 = 26, 
  	ADC_CH27 = 27,
  	ADC_CH28 = 28,
  	ADC_CH29 = 29,		/* not exist */
  	ADC_CH30 = 30,
  	ADC_CH31 = 31,
  	ADC_CH32 = 32,
  	ADC_CH33 = 33,
  	ADC_CH34 = 34,
  	ADC_CH35 = 35,
  	ADC_CH36 = 36,
  	ADC_CH37 = 37,
  	ADC_CH38 = 38,
  	ADC_CH39 = 39,
  	ADC_CH96 = 96,
  	ADC_CH97 = 97,
  	ADC_CH98 = 98,
  	ADC_CH99 = 99,
  	ADC_NBR_OF_CHANNELS  = 44
}Adc_ChannelIDType;

/* Type for configuring the number of group conversions in streaming 
 * access mode.
 */
typedef uint16 Adc_StreamNumSampleType;

/* Type for reading the converted values of a channel group.*/
typedef uint16 Adc_ValueGroupType;/* ADC318 ADC319 ADC320 */

/* Numeric ID of an ADC channel.*/
typedef uint8 Adc_ChannelType;

/* Numeric ID of an ADC group. */
typedef uint8 Adc_GroupType;

/* Numeric ID of an ADC group.*/

typedef uint16  Adc_ResultGainType;


/* Priority level of the channel.*/
 
typedef uint8 Adc_GroupPriorityType;  

/* Type for configuring the prioritization mechanism.*/
typedef enum
{
  	ADC_PRIORITY_NONE,
  	ADC_PRIORITY_HW,
  	ADC_PRIORITY_HW_SW
}Adc_PriorityImplementationType;

/* Replacement mechanism, which is used on ADC group level, if a group
 * conversion is interrupted by a group which has a higher priority.
 */
typedef enum
{
  	ADC_GROUP_REPL_ABORT_RESTART,
  	ADC_GROUP_REPL_SUPEND_RESUME
}Adc_GroupReplacementType;

/* Current status of the conversion of the requested ADC Channel group. */
typedef enum
{
  	ADC_IDLE,
  	ADC_BUSY,
  	ADC_COMPLETED,
  	ADC_STREAM_COMPLETED
}Adc_StatusType;

/* Access mode to group conversion results. */
typedef enum
{
  	ADC_ACCESS_MODE_SINGLE,
  	ADC_ACCESS_MODE_STREAMING
}Adc_GroupAccessModeType;

/* Definition data type for group trigger source.*/
typedef enum
{
  	ADC_TRIGG_SRC_HW,
  	ADC_TRIGG_SRC_SW
}Adc_TriggerSourceType;

/* Definition data type for hardware trigger edge mode */
typedef enum
{
  	ADC_HW_TRIG_FALLING_EDGE,
  	ADC_HW_TRIG_RISING_EDGE,
  	ADC_HW_TRIG_BOTH_EDGES
}Adc_HwTriggerSignalType;

/* Definition data type for stream buffer type */
typedef enum
{
    ADC_STREAM_BUFFER_LINEAR,
  	ADC_STREAM_BUFFER_CIRCULAR
}Adc_StreamBufferModeType;

/*	Type of clock input for the conversion unit*/
typedef enum
{
	ADC_PRESCALER_OUTPUT_CLOCK,
  	ADC_SYSTEM_CLOCK
}Adc_ClockSourceType;

/* 	Data type for clock prescaler factor.*/
typedef enum
{
  	ADC_SYSTEM_CLOCK_DIVIDE_0 = 0,
  	ADC_SYSTEM_CLOCK_DIVIDE_1  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_2  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_3  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_4  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_5  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_6  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_7 ,
  	ADC_SYSTEM_CLOCK_DIVIDE_8  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_9  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_10  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_11  ,
  	ADC_SYSTEM_CLOCK_DIVIDE_12,
  	ADC_SYSTEM_CLOCK_DIVIDE_13,
  	ADC_SYSTEM_CLOCK_DIVIDE_14,
  	ADC_SYSTEM_CLOCK_DIVIDE_15,
  	ADC_SYSTEM_CLOCK_DIVIDE_16,
  	ADC_SYSTEM_CLOCK_DIVIDE_17,
  	ADC_SYSTEM_CLOCK_DIVIDE_18,
  	ADC_SYSTEM_CLOCK_DIVIDE_19,
  	ADC_SYSTEM_CLOCK_DIVIDE_20,
  	ADC_SYSTEM_CLOCK_DIVIDE_21,
  	ADC_SYSTEM_CLOCK_DIVIDE_22,
  	ADC_SYSTEM_CLOCK_DIVIDE_23,
  	ADC_SYSTEM_CLOCK_DIVIDE_24,
  	ADC_SYSTEM_CLOCK_DIVIDE_25,
  	ADC_SYSTEM_CLOCK_DIVIDE_26,
  	ADC_SYSTEM_CLOCK_DIVIDE_27,
  	ADC_SYSTEM_CLOCK_DIVIDE_28,
  	ADC_SYSTEM_CLOCK_DIVIDE_29,
  	ADC_SYSTEM_CLOCK_DIVIDE_30,
  	ADC_SYSTEM_CLOCK_DIVIDE_31,
  	ADC_SYSTEM_CLOCK_DIVIDE_32,
  	ADC_SYSTEM_CLOCK_DIVIDE_33,
  	ADC_SYSTEM_CLOCK_DIVIDE_34,
  	ADC_SYSTEM_CLOCK_DIVIDE_35,
  	ADC_SYSTEM_CLOCK_DIVIDE_36,
  	ADC_SYSTEM_CLOCK_DIVIDE_37,
  	ADC_SYSTEM_CLOCK_DIVIDE_38,
  	ADC_SYSTEM_CLOCK_DIVIDE_39,
  	ADC_SYSTEM_CLOCK_DIVIDE_40,
  	ADC_SYSTEM_CLOCK_DIVIDE_41,
  	ADC_SYSTEM_CLOCK_DIVIDE_42,
  	ADC_SYSTEM_CLOCK_DIVIDE_43,
  	ADC_SYSTEM_CLOCK_DIVIDE_44,
  	ADC_SYSTEM_CLOCK_DIVIDE_45,
  	ADC_SYSTEM_CLOCK_DIVIDE_46,
  	ADC_SYSTEM_CLOCK_DIVIDE_47,
  	ADC_SYSTEM_CLOCK_DIVIDE_48,
  	ADC_SYSTEM_CLOCK_DIVIDE_49,
  	ADC_SYSTEM_CLOCK_DIVIDE_50,
  	ADC_SYSTEM_CLOCK_DIVIDE_51,
  	ADC_SYSTEM_CLOCK_DIVIDE_52,
  	ADC_SYSTEM_CLOCK_DIVIDE_53,
  	ADC_SYSTEM_CLOCK_DIVIDE_54,
  	ADC_SYSTEM_CLOCK_DIVIDE_55,
  	ADC_SYSTEM_CLOCK_DIVIDE_56,
  	ADC_SYSTEM_CLOCK_DIVIDE_57,
  	ADC_SYSTEM_CLOCK_DIVIDE_58,
  	ADC_SYSTEM_CLOCK_DIVIDE_59,
  	ADC_SYSTEM_CLOCK_DIVIDE_60,
  	ADC_SYSTEM_CLOCK_DIVIDE_61,
  	ADC_SYSTEM_CLOCK_DIVIDE_62,
  	ADC_SYSTEM_CLOCK_DIVIDE_63,
  	ADC_SYSTEM_CLOCK_DIVIDE_64,
  	ADC_SYSTEM_CLOCK_DIVIDE_TOTAL
}Adc_PrescaleType;

/*	Data type for reference voltage source.*/
typedef enum
{
    ADC_REFERENCE_VOLTAGE_GROUND,
    ADC_REFERENCE_VOLTAGE_5V
}Adc_VoltageSourceType;

/* Data type for sample time.*/
typedef enum
{
    ADC_2_CLOCKCYCLES = 0,
    ADC_8_CLOCKCYCLES,
    ADC_64_CLOCKCYCLES,
    ADC_128_CLOCKCYCLES
}Adc_SamplingTimeType;

/* Data type for duaration of conversion. */
typedef enum
{
	ADC_DIFFERENTIAL_CONVERSIONS_CYCLES = 13,
	ADC_SINGLE_ENDED_CONVERSIONS_CYCLES = 14	
}Adc_ConversionTimeType;
  
/* Data type for enable/disable calibration.*/
typedef enum
{
    ADC_CALIBRATION_DISABLED,
    ADC_CALIBRATION_ENABLED
}Adc_CalibrationType;

/* Data type for channel resolution.*/
typedef enum
{
	ADC_RESOLUTION_8BITS = 8,
	ADC_RESOLUTION_10BITS = 10,
    ADC_RESOLUTION_12BITS = 12
}Adc_ResolutionType;

/* Data type for result format.*/
typedef enum
{
	ADC_UNSIGTYPE = 0,
	ADC_SIGTYPE
	
}Adc_ResultFmtType;

/* Data type for timer sources.*/
typedef enum
{
    ADC_NO_TIMER = 0,
    RTI_TIMER,
    PIT0_TIMER,
    PIT1_TIMER,
    PIT2_TIMER,
    PIT3_TIMER
}Adc_HwTriggerTimerType;

/* Data type for channel conversion mode. */
typedef enum
{
    ADC_CONV_MODE_ONESHOT = 1, 
    ADC_CONV_MODE_CONTINUOUS = 9
}Adc_GroupConvModeType;

/* Numeric ID of an ADC Hw unit.*/
typedef uint8 Adc_HwUnitType;

/*	Container for channel configuration.*/
typedef struct
{
	Adc_ChannelType AdcChannelId;            		/* ADC392 */
	
    Adc_ConversionTimeType AdcChannelConvTime;      /* ADC011 */
    
    Adc_VoltageSourceType AdcChannelRefVoltsrcLow; 	/* ADC023 */
    
    Adc_VoltageSourceType AdcChannelRefVoltsrcHigh;	/* ADC089 */
    
    Adc_ResolutionType AdcChannelResolution;    	/* ADC019 */
    
    Adc_SamplingTimeType AdcChannelSampTime;		/* ADC290 */
    
}Adc_ChannelConfigType;/* ADC268 */

/*	User free data type according to Autosar,Container for groups status 
 *	infomation
 */
typedef struct
{
    uint32 Num_Of_Channel;
	/*const Adc_ChannelType *AdcChannelIdList;*/
    P2CONST(Adc_ChannelType, AUTOMATIC, ADC_APPL_CONST)AdcChannelIdList;
    /* Adc_AlternateConfigType *AdcGroupCommandBuffer;*/
    P2VAR(Adc_AlternateConfigType,AUTOMATIC,ADC_APPL_DATA)AdcGroupCommandBuffer;
}Adc_GroupDefType;

/* Container for group setup. */
typedef struct
{
  	Adc_GroupType AdcGroupId;
  	
  	Adc_GroupAccessModeType AdcGroupAccessMode;     /* ADC317 */
  	
  	Adc_GroupConvModeType AdcGroupConversionMode; 	/* ADC397 */
  	
  	Adc_TriggerSourceType AdcGroupTriggSrc;    	 	/* ADC399 */
  	
  	Adc_HwTriggerSignalType AdcHwTrigSignal;        /* ADC400 */
  	
  	Adc_HwTriggerTimerType AdcHwTrigTimer;         	/* ADC401 */
  	
  	void (*AdcNotification)(void);					/* ADC402 */
  	
  	Adc_StreamBufferModeType AdcStreamingBufferMode;/* ADC316 */
  	
  	Adc_StreamNumSampleType AdcStreamingNumSamples; /* ADC292 */
  	
  	Adc_GroupPriorityType AdcGroupPriority;   		/* ADC287 */
  	
  	Adc_GroupReplacementType AdcGroupReplacement;	/* ADC431 */
  	
  	Adc_GroupDefType AdcGroupDefinition; 			/* ADC014 */
  	
  	Adc_ResultFmtType	AdcGroupFmta;

	Adc_ResultGainType	AdcGroupGain;
  	
}Adc_GroupConfigType; /* ADC028 ADC098 */

/*	Container for HW setup.*/
typedef struct
{
    Adc_ClockSourceType AdcClockSource;/* ADC087 */
    
    uint8 AdcHwUnitId;   			   /* ADC389 */
    
    Adc_PrescaleType AdcPrescale;      /* ADC088 */
    
  	Adc_ChannelConfigType AdcChannel[ADC_SUM_OF_CHANNELS];
  	 
  	Adc_GroupConfigType AdcGroup[ADC_SUM_OF_GROUP];
  	
}Adc_HwUnitConfigType;/* ADC242 */

/* Data type for ADC configuration.*/
typedef struct
{	
	/* ADC390 */
	/* ADC138 */
    Adc_HwUnitConfigType AdcHwUnit[Unit_Number];
}Adc_ConfigType;


/*=======[E X T E R N A L   D A T A]==========================================*/
extern VAR(uint8,ADC_APPL_DATA) Adc_NotifictionEnable[ADC_SUM_OF_GROUP];
extern VAR(Adc_StatusType,ADC_APPL_DATA) Adc_GroupStatus[ADC_SUM_OF_GROUP];
extern VAR(Adc_StatusType,ADC_APPL_DATA) Adc_BufferStatus[ADC_SUM_OF_GROUP];
extern VAR(Adc_CalibrationType, ADC_APPL_DATA) Adc_ChannelCalibrationEnable[44];
extern P2CONST(Adc_ConfigType,AUTOMATIC,ADC_APPL_CONST) Adc_ConfigPtr;
extern VAR(boolean,ADC_APPL_DATA) Adc_ConversionStarted[ADC_SUM_OF_GROUP];
extern VAR(boolean,ADC_APPL_DATA) Adc_InitFlag;
extern P2VAR(Adc_ValueGroupType,AUTOMATIC,ADC_APPL_DATA) Adc_ResultBufferPtr[ADC_SUM_OF_GROUP];	
extern VAR(boolean,ADC_APPL_DATA) Adc_HWTriggered[ADC_SUM_OF_GROUP];
extern VAR(uint32,ADC_APPL_DATA) ReceiveIsr_index  ;
extern VAR(uint8,ADC_APPL_DATA) sampleNumber[ADC_SUM_OF_GROUP]  ;
extern VAR(uint8,ADC_APPL_DATA) channelSum[ADC_SUM_OF_GROUP]  ;
extern VAR(uint8,ADC_APPL_DATA) Lo_finish_sample  ;
extern VAR(Adc_GroupType,ADC_APPL_DATA) Adc_Group;
extern VAR(uint32,ADC_APPL_DATA) Final_EndOfQueue_Times[ADC_SUM_OF_GROUP]  ;
extern VAR(uint16,ADC_APPL_DATA) Re_EndOfQueue_Times[ADC_SUM_OF_GROUP]  ;
extern VAR(boolean,ADC_APPL_DATA) Finish_Load_CFIFO[ADC_SUM_OF_GROUP]  ;
extern VAR(uint8,ADC_APPL_DATA) sampleNumber[ADC_SUM_OF_GROUP];
extern VAR(uint8,ADC_APPL_DATA) channelSum[ADC_SUM_OF_GROUP];
extern Adc_AlternateConfigType Adc_Group_0_CFIFOCommands[];
extern Adc_ValueGroupType Adc_Group_0_ResultBuffer[];
extern Dma_TCD_Type Adc_DMA_FillCommandCofig[];
extern Dma_TCD_Type Adc_DMA_ReadResultCofig[];
extern P2VAR(Adc_ValueGroupType,AUTOMATIC,ADC_APPL_DATA) AdcResultBufferPointer[ADC_SUM_OF_GROUP];
extern P2VAR(Adc_ValueGroupType,AUTOMATIC,ADC_APPL_DATA) Adc_ReadBuffer[ADC_SUM_OF_GROUP];
extern const Adc_ConfigType Adc_Config;
extern VAR(Adc_TransferWayType,ADC_APPL_DATA) Adc_GroupInterruptOrDma[ADC_SUM_OF_GROUP];
extern VAR(uint32,ADC_APPL_DATA) Final_EndOfQueue_Times[ADC_SUM_OF_GROUP];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA) Adc_Group_0_ResultBufferForRead[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA) Adc_Group_1_ResultBufferForRead[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA) Adc_Group_2_ResultBufferForRead[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA) Adc_Group_3_ResultBufferForRead[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA) Adc_Group_4_ResultBufferForRead[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA) Adc_Group_5_ResultBufferForRead[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA) Adc_Group_1_ResultBuffer[];
extern VAR(Adc_AlternateConfigType,ADC_APPL_DATA) Adc_Group_1_CFIFOCommands[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA) Adc_Group_2_ResultBuffer[];
extern VAR(Adc_AlternateConfigType,ADC_APPL_DATA) Adc_Group_2_CFIFOCommands[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA)  Adc_Group_3_ResultBuffer[];
extern VAR(Adc_AlternateConfigType,ADC_APPL_DATA) Adc_Group_3_CFIFOCommands[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA) Adc_Group_4_ResultBuffer[];
extern VAR(Adc_AlternateConfigType,ADC_APPL_DATA)Adc_Group_4_CFIFOCommands[];
extern VAR(Adc_ValueGroupType,ADC_APPL_DATA)Adc_Group_5_ResultBuffer[];
extern VAR(Adc_AlternateConfigType,ADC_APPL_DATA) Adc_Group_5_CFIFOCommands[];
extern VAR(Adc_TransferWayType,ADC_APPL_DATA) Adc_GroupInterruptOrDma[ADC_SUM_OF_GROUP];
extern VAR(uint8,ADC_APPL_DATA) Adc_GrpResult[ADC_SUM_OF_GROUP];
extern CONST(Adc_ChannelType,ADC_APPL_DATA) Adc_Group0ChannelList[];					
extern CONST(Adc_ChannelType,ADC_APPL_DATA) Adc_Group1ChannelList[];	
extern CONST(Adc_ChannelType,ADC_APPL_DATA) Adc_Group2ChannelList[];	
extern CONST(Adc_ChannelType,ADC_APPL_DATA) Adc_Group3ChannelList[];	
extern CONST(Adc_ChannelType,ADC_APPL_DATA) Adc_Group4ChannelList[];	
extern CONST(Adc_ChannelType,ADC_APPL_DATA) Adc_Group5ChannelList[];

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
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
extern FUNC(void,ADC_PUBLIC_CODE) Adc_Init(P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr);
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
#if (ADC_DEINIT_API == STD_ON)
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DeInit(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_DEINIT_API == STD_ON) */

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
extern FUNC(Std_ReturnType,ADC_PUBLIC_CODE) Adc_SetupResultBuffer(Adc_GroupType group,
		P2VAR(Adc_ValueGroupType,AUTOMATIC,ADC_APPL_DATA)DataBufferPtr);
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
extern  FUNC(Adc_StreamNumSampleType, ADC_PUBLIC_CODE) Adc_GetStreamLastPointer(Adc_GroupType group, 
		P2VAR(P2VAR(Adc_ValueGroupType,AUTOMATIC, ADC_APPL_DATA), AUTOMATIC,ADC_APPL_DATA) PtrToSamplePtr);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_StartGroupConversion(Adc_GroupType group);
#define ADC_STOP_SEC_CODE
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_StopGroupConversion(Adc_GroupType group);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

#if (ADC_READ_GROUP_API == STD_ON)
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
extern FUNC(Std_ReturnType, ADC_PUBLIC_CODE)Adc_ReadGroup (Adc_GroupType group,
  P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) dataBufferPtr);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_READ_GROUP_API == STD_ON) */

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_EnableGroupNotification(Adc_GroupType group);
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DisableGroupNotification(Adc_GroupType group);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_GRP_NOTIF_CAPABILITY == STD_ON) */

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
extern FUNC(Adc_StatusType,ADC_PUBLIC_CODE) Adc_GetGroupStatus(Adc_GroupType group);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#if (ADC_VERSION_API == STD_ON)
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC,ADC_APPL_DATA)versionInfo);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_VERSION_API == STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_EnableHardwareTrigger(Adc_GroupType group);
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DisableHardwareTrigger(Adc_GroupType group);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_HW_TRIGGER_API == STD_ON) */

#if (ADC_USE_DECIMATION_FILTER == STD_ON)
#define ADC_START_SEC_CODE
#include "MemMap.h"
void Adc_DecimationFilter_Init(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_USE_DECIMATION_FILTER == STD_ON) */

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
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_DataHandler(Adc_GroupType groupId);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_Group0Notification>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Group0Notification(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_Group1Notification>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Group1Notification(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_Group2Notification>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Group2Notification(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_Group3Notification>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Group3Notification(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_Group4Notification>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Group4Notification(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_Group5Notification>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_Group5Notification(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_Group0_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group0_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_Group1_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group1_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_Group2_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group2_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_Group3_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group3_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_Group4_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group4_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_LoadCFIFO_Group5_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCFIFO_Group5_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_LoadCommand_Hander>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_LoadCommand_Hander(Adc_GroupType groupId);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group0_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group0_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group1_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group1_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group2_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group2_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group3_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group3_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group4_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group4_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_Group5_Isr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_Group5_Isr(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Adc_ReceiveEOQF_HandlerIsr>
 * ServiceId           <None>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_ReceiveEOQF_HandlerIsr(Adc_GroupType groupId);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Dma_SetChannelMajorInterrupt>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel, control>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ADC_PUBLIC_CODE) Dma_SetChannelMajorInterrupt(Dma_ChannelType channel,  
												Dma_SetChannelMajorInterruptType control);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Dma_SetChannelMajorInterrupt>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel, numberofIterations>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"												
extern FUNC(void, ADC_PUBLIC_CODE)Dma_ConfigureChannelTransferSize(Dma_ChannelType channel, uint32 numberofIterations);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Dma_StartChannel>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, ADC_PUBLIC_CODE)Dma_StartChannel(Dma_ChannelType channel);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Mcu_GetPeripheralBusClock>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint32, ADC_PUBLIC_CODE)Mcu_GetPeripheralBusClock(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

#endif/* End the #ifndef ADC_H_ */
/*=======[E N D   O F   F I L E]==============================================*/
