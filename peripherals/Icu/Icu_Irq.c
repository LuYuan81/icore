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
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */
/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 17.4; REFERENCE - ISO:C90-6.3.6 Additive Operators - Constraints */

/*=======[I N C L U D E S]====================================================*/
#include "Icu.h"
#include "Icu_Irq.h"
#include "MemMap.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define ICU_IRQ_C_AR_MAJOR_VERSION    3
#define ICU_IRQ_C_AR_MINOR_VERSION    0
#define ICU_IRQ_C_AR_PATCH_VERSION    2

#define ICU_IRQ_C_SW_MAJOR_VERSION    1
#define ICU_IRQ_C_SW_MINOR_VERSION    0
#define ICU_IRQ_C_SW_PATCH_VERSION    0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (ICU_IRQ_C_AR_MAJOR_VERSION != ICU_IRQ_H_AR_MAJOR_VERSION)
  #error "ICU_IRQ.c : Mismatch in Specification Major Version"
#endif
#if (ICU_IRQ_C_AR_MINOR_VERSION != ICU_IRQ_H_AR_MINOR_VERSION)
  #error "ICU_IRQ.c : Mismatch in Specification Major Version"
#endif
#if (ICU_IRQ_C_AR_PATCH_VERSION != ICU_IRQ_H_AR_PATCH_VERSION)
  #error "ICU_IRQ.c : Mismatch in Specification Major Version"
#endif
#if (ICU_IRQ_C_SW_MAJOR_VERSION != ICU_IRQ_H_SW_MAJOR_VERSION)
  #error "ICU_IRQ.c : Mismatch in Specification Major Version"
#endif
#if (ICU_IRQ_C_SW_MINOR_VERSION != ICU_IRQ_H_SW_MINOR_VERSION)
  #error "ICU_IRQ.c : Mismatch in Specification Major Version"
#endif
#if (ICU_IRQ_C_SW_PATCH_VERSION != ICU_IRQ_H_SW_PATCH_VERSION)
  #error "ICU_IRQ.c : Mismatch in Specification Major Version"
#endif

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
STATIC FUNC(void, ICU_CODE) Icu_Isr_EdgeCounter(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);
STATIC FUNC(void, ICU_CODE) Icu_Isr_EdgeDetect(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);
STATIC FUNC(void, ICU_CODE) Icu_Isr_Timestamp(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);
STATIC FUNC(void, ICU_CODE) Icu_Isr_SigMeas(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel);

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/*
 * Brief               <This function deal with the following events for Channel 0.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) IC0_ISR(void)
{
    uint32 maxChannel;
    P2VAR(Icu_ChannelSetType, AUTOMAITC, ICU_VAR) oneChannel = NULL;

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != (uint16)CHANNEL_0)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            return;
        }
        maxChannel--;
    }


    #if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
    if ((ICU_MODE_SLEEP == GlobalChannelInfo.IcuMode[CHANNEL_0]) &&\
	    (TRUE == GlobalChannelInfo.IcuNotificationSwitch[CHANNEL_0]))
    {
        EcuM_SetWakeupEvent(oneChannel->IcuWakeup.IcuChannelWakeupInfo);
    }
    #endif /* STD_ON == ICU_REPORT_WAKEUP_SOURCE */

    if (ICU_MODE_EDGE_COUNTER == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeCounter(oneChannel);
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeDetect(oneChannel);
    }
    else if (ICU_MODE_TIMESTAMP == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_Timestamp(oneChannel);
    }
    else if ((ICU_MODE_SIGNAL_MEASUREMENT == oneChannel->IcuMeasurementMode) &&\
        (TRUE == Icu_GlobalChannelInfo.IcuSignalMeasurementSwitch[oneChannel->IcuChannelId]))
    {
        Icu_Isr_SigMeas(oneChannel);
    }/*end of signal measurement*/
    else
    {
        /* empty */
    }

    /*clear the interrupt flag*/
    EMIOS.CH[CHANNEL_0].CSR.B.FLAG = BIT0;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function deal with the following events for Channel 8.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) IC8_ISR(void)
{
    uint32 maxChannel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel = NULL;

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != (uint16)CHANNEL_8)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            return;
        }
        maxChannel--;
    }

    #if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
    if ((ICU_MODE_SLEEP == GlobalChannelInfo.IcuMode[CHANNEL_8]) &&\
        (TRUE == GlobalChannelInfo.IcuNotificationSwitch[CHANNEL_8]))
    {
        EcuM_SetWakeupEvent(oneChannel->IcuWakeup.IcuChannelWakeupInfo);
    }
    #endif

    if (ICU_MODE_EDGE_COUNTER == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeCounter(oneChannel);
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeDetect(oneChannel);
    } /* end of edge_detect mode */
    else if (ICU_MODE_TIMESTAMP == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_Timestamp(oneChannel);
    } /* end of timestamp mode */
    else if (ICU_MODE_SIGNAL_MEASUREMENT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_SigMeas(oneChannel);
    } /* end of signal measurement */
    else
    {
        /* empty */
    }

    /* clear the interrupt flag */
    EMIOS.CH[CHANNEL_8].CSR.B.FLAG = BIT0;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function deal with the following events for Channel 9.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) IC9_ISR(void)
{
    uint32 maxChannel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel = NULL;

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != (uint16)CHANNEL_9)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            return;
        }
        maxChannel--;
    }


    #if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
    if ((ICU_MODE_SLEEP == GlobalChannelInfo.IcuMode[CHANNEL_9]) &&\
        (TRUE == GlobalChannelInfo.IcuNotificationSwitch[CHANNEL_9]))
    {
        EcuM_SetWakeupEvent(oneChannel->IcuWakeup.IcuChannelWakeupInfo);
    }
    #endif

    if (ICU_MODE_EDGE_COUNTER == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeCounter(oneChannel);
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeDetect(oneChannel);
    } /* end of edge_detect mode */
    else if (ICU_MODE_TIMESTAMP == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_Timestamp(oneChannel);
    } /* end of timestamp mode */
    else if (ICU_MODE_SIGNAL_MEASUREMENT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_SigMeas(oneChannel);
    } /* end of signal measurement */
    else
    {
        /* empty */
    }

    /* clear the interrupt flag */
    EMIOS.CH[CHANNEL_9].CSR.B.FLAG = BIT0;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function deal with the following events for Channel 10.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) IC10_ISR(void)
{
    uint32 maxChannel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel = NULL;

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != (uint16)CHANNEL_10)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            return;
        }
        maxChannel--;
    }


    #if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
    if ((ICU_MODE_SLEEP == GlobalChannelInfo.IcuMode[CHANNEL_10]) &&\
        (TRUE == GlobalChannelInfo.IcuNotificationSwitch[CHANNEL_10]))
    {
        EcuM_SetWakeupEvent(oneChannel->IcuWakeup.IcuChannelWakeupInfo);
    }
    #endif /* STD_ON == ICU_REPORT_WAKEUP_SOURCE */

    if (ICU_MODE_EDGE_COUNTER == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeCounter(oneChannel);
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeDetect(oneChannel);
    } /* end of edge_detect mode */
    else if (ICU_MODE_TIMESTAMP == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_Timestamp(oneChannel);
    } /* end of timestamp mode */
    else if (ICU_MODE_SIGNAL_MEASUREMENT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_SigMeas(oneChannel);
    } /* end of signal measurement */
    else
    {
        /* empty */
    }


    /* clear the interrupt flag */
    EMIOS.CH[CHANNEL_10].CSR.B.FLAG = BIT0;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function deal with the following events for Channel 12.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) IC12_ISR(void)
{
    uint32 maxChannel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel = NULL;

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != (uint16)CHANNEL_12)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            return;
        }
        maxChannel--;
    }

    #if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
    if ((ICU_MODE_SLEEP == GlobalChannelInfo.IcuMode[CHANNEL_12]) &&\
        (TRUE == GlobalChannelInfo.IcuNotificationSwitch[CHANNEL_12]))
    {
        EcuM_SetWakeupEvent(oneChannel->IcuWakeup.IcuChannelWakeupInfo);
    }
    #endif /* STD_ON == ICU_REPORT_WAKEUP_SOURCE */

    if (ICU_MODE_EDGE_COUNTER == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeCounter(oneChannel);
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeDetect(oneChannel);
    } /* end of edge_detect mode */
    else if (ICU_MODE_TIMESTAMP == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_Timestamp(oneChannel);
    } /* end of timestamp mode */
    else if (ICU_MODE_SIGNAL_MEASUREMENT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_SigMeas(oneChannel);
    } /* end of signal measurement */
    else
    {
        /* empty */
    }


    /* clear the interrupt flag */
    EMIOS.CH[CHANNEL_12].CSR.B.FLAG = BIT0;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function deal with the following events for Channel 14.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) IC14_ISR(void)
{
    uint32 maxChannel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel = NULL;

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != (uint16)CHANNEL_14)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            return;
        }
        maxChannel--;
    }

    #if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
    if ((ICU_MODE_SLEEP == GlobalChannelInfo.IcuMode[CHANNEL_14]) &&\
        (TRUE == GlobalChannelInfo.IcuNotificationSwitch[CHANNEL_14]))
    {
        EcuM_SetWakeupEvent(oneChannel->IcuWakeup.IcuChannelWakeupInfo);
    }
    #endif /* STD_ON == ICU_REPORT_WAKEUP_SOURCE */

    if (ICU_MODE_EDGE_COUNTER == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeCounter(oneChannel);
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeDetect(oneChannel);
    } /* end of edge_detect mode */
    else if (ICU_MODE_TIMESTAMP == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_Timestamp(oneChannel);
    } /* end of timestamp mode */
    else if (ICU_MODE_SIGNAL_MEASUREMENT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_SigMeas(oneChannel);
    } /* end of signal measurement */
    else
    {
        /* empty */
    }


    /* clear the interrupt flag */
    EMIOS.CH[CHANNEL_14].CSR.B.FLAG = BIT0;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <This function deal with the following events for Channel 23.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"

FUNC(void, ICU_CODE) IC23_ISR(void)
{
    uint32 maxChannel;
    P2VAR(Icu_ChannelSetType, AUTOMATIC, ICU_VAR) oneChannel = NULL;

    oneChannel = Icu_GlobalConfig->IcuConfigSet.IcuChannel;
    maxChannel = (uint32)Icu_GlobalConfig->IcuConfigSet.IcuMaxChannel - ONE;
    while (oneChannel->IcuChannelId != (uint16)CHANNEL_23)
    {
        /* find the position of the currentchannel */
        if (maxChannel > ZERO)
        {
            oneChannel++;
        }
        else
        {
            return;
        }
        maxChannel--;
    }

    #if (STD_ON == ICU_REPORT_WAKEUP_SOURCE)
    if ((ICU_MODE_SLEEP == GlobalChannelInfo.IcuMode[CHANNEL_23]) &&\
        (TRUE == GlobalChannelInfo.IcuNotificationSwitch[CHANNEL_23]))
    {
        EcuM_SetWakeupEvent(oneChannel->IcuWakeup.IcuChannelWakeupInfo);
    }
    #endif /* STD_ON == ICU_REPORT_WAKEUP_SOURCE */

    if (ICU_MODE_EDGE_COUNTER == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeCounter(oneChannel);
    }
    else if (ICU_MODE_SIGNAL_EDGE_DETECT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_EdgeDetect(oneChannel);
    } /* end of edge_detect mode */
    else if (ICU_MODE_TIMESTAMP == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_Timestamp(oneChannel);
    } /* end of timestamp mode */
    else if (ICU_MODE_SIGNAL_MEASUREMENT == oneChannel->IcuMeasurementMode)
    {
        Icu_Isr_SigMeas(oneChannel);
    } /* end of signal measurement */
    else
    {
        /* empty */
    }


    /* clear the interrupt flag */
    EMIOS.CH[CHANNEL_23].CSR.B.FLAG = BIT0;
}

#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Deal with the function of Edge Counter.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ICU_CODE) Icu_Isr_EdgeCounter(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel)
{
    if (TRUE == Icu_GlobalChannelInfo.IcuEdgeCountSwitch[channel->IcuChannelId])
    {
        Icu_GlobalParameter.EdgeCounterIndex[channel->IcuChannelId]++;
    }
    return;
}
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Deal with the function of Edge Detect.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ICU_CODE) Icu_Isr_EdgeDetect(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel)
{
    Icu_GlobalChannelInfo.IcuInputStatus[channel->IcuChannelId] = ICU_ACTIVE;

    if ((channel->IcuSignalEdgeDetection.IcuSignalNotification !=  NULL) &&\
        (TRUE == Icu_GlobalChannelInfo.IcuNotificationSwitch[channel->IcuChannelId]))
    {
        /* only give a notification to the up layer */
        (channel->IcuSignalEdgeDetection.IcuSignalNotification)();
    }
    return;
}
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Deal with the function of Timestamp.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ICU_CODE) Icu_Isr_Timestamp(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel)
{
    static uint16 interval = ZERO;
    Icu_TimestampBufferType bufferType;

    *(Icu_GlobalParameter.TimestampBuffer[channel->IcuChannelId]\
     +Icu_GlobalParameter.TimestampBufferIndex[channel->IcuChannelId]) = EMIOS.CH[channel->IcuChannelId].CADR.R;

    Icu_GlobalParameter.TimestampBufferIndex[channel->IcuChannelId]++;
    Icu_GlobalChannelInfo.IcuInputStatus[channel->IcuChannelId] = ICU_ACTIVE;

    bufferType = channel->IcuTimestampMeasurement.IcuTimestampMeasurementProperty;
    if (Icu_GlobalParameter.TimestampBufferIndex[channel->IcuChannelId] >=\
        Icu_GlobalParameter.TimestampBufferSize[channel->IcuChannelId])
    {
        if (ICU_LINEAR_BUFFER == bufferType)
        {
            /* stop capture value */
            switch (channel->IcuChannelId)
            {
            	case CHANNEL_0:
            	    EMIOS.UCDIS.B.CHDIS0 = BIT0;
            	    break;
            	case CHANNEL_8:
            	    EMIOS.UCDIS.B.CHDIS8 = BIT0;
            	    break;
            	case CHANNEL_9:
            	    EMIOS.UCDIS.B.CHDIS9 = BIT0;
            	    break;
            	case CHANNEL_10:
            	    EMIOS.UCDIS.B.CHDIS10 = BIT0;
            	    break;
            	case CHANNEL_12:
            	    EMIOS.UCDIS.B.CHDIS12 = BIT0;
            	    break;
            	case CHANNEL_14:
            	    EMIOS.UCDIS.B.CHDIS14 = BIT0;
            	    break;
            	case CHANNEL_23:
            	    EMIOS.UCDIS.B.CHDIS23 = BIT0;
            	    break;
            	default:
            	    break;
            }
            EMIOS.CH[channel->IcuChannelId].CCR.B.FEN = ZERO;
        }
        else
        {
            /* empty */
        }
    }

    if ((channel->IcuTimestampMeasurement.IcuTimestampNotificaion != NULL) &&\
        (Icu_GlobalParameter.TimestampNotifyInterval[channel->IcuChannelId] > ZERO) &&\
        (ICU_MODE_TIMESTAMP == channel->IcuMeasurementMode) &&\
        (TRUE == Icu_GlobalChannelInfo.IcuNotificationSwitch[channel->IcuChannelId]))
    {
        /* enable notification */
        if (interval >= Icu_GlobalParameter.TimestampNotifyInterval[channel->IcuChannelId])
        {
            (channel->IcuTimestampMeasurement.IcuTimestampNotificaion)();
            interval = ZERO;
        }
        else
        {
            interval++;
        }
    }
    return;
}
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Deal with the function of Signal Measurement.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <channel>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define ICU_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, ICU_CODE) Icu_Isr_SigMeas(P2CONST(Icu_ChannelSetType, AUTOMATIC, ICU_APPL_DATA) channel)
{
    static uint16 index = ZERO;
    static uint32 abuffer[THREE] = {ZERO};
    static uint32 period = ZERO;

    uint32 tempA = ZERO;
    uint32 tempB = ZERO;

    if (channel->IcuSignalMeasurement.IcuSignalMeasurementProperty != ICU_PERIOD_TIME)
    {
        abuffer[index] = EMIOS.CH[channel->IcuChannelId].CADR.R;
        EMIOS.CH[channel->IcuChannelId].CCR.B.EDSEL = BIT0;
        index++;

        if (index >= THREE)
        {
            if ((abuffer[ONE] > abuffer[ZERO]) && (abuffer[TWO] > abuffer[ONE]))
            {
                switch (channel->IcuSignalMeasurement.IcuSignalMeasurementProperty)
                {
                    case ICU_LOW_TIME:
                        Icu_GlobalParameter.TimeElaspedValue[channel->IcuChannelId] = abuffer[ONE] - abuffer[ZERO];
                        break;

                    case ICU_HIGH_TIME:
                        Icu_GlobalParameter.TimeElaspedValue[channel->IcuChannelId] = abuffer[TWO] - abuffer[ONE];
                        break;

                    case ICU_DUTY_CYCLE:
                        /* active time = high time */
                        Icu_GlobalParameter.DutyCycleBuffer[channel->IcuChannelId].ActiveTime =\
                                                           (uint32)abuffer[TWO] - (uint32)abuffer[ONE];
                        Icu_GlobalParameter.DutyCycleBuffer[channel->IcuChannelId].PeriodTime =\
                                                           (uint32)abuffer[TWO] - (uint32)abuffer[ZERO];
                        break;

                    default:
                        break;
                }

                Icu_GlobalChannelInfo.IcuInputStatus[channel->IcuChannelId] = ICU_ACTIVE;
            }

            index = ZERO;

            /* a single failing edge */
            EMIOS.CH[channel->IcuChannelId].CCR.B.EDSEL = ZERO;
            EMIOS.CH[channel->IcuChannelId].CCR.B.EDPOL = ZERO;
        }
    } /* end of handle of ICU_LOW_TIME,ICU_HIGH_TIME,ICU_DUTY_CYCLE */
    else
    {
        tempA = EMIOS.CH[channel->IcuChannelId].CADR.R;
        tempB = EMIOS.CH[channel->IcuChannelId].CBDR.R;
        abuffer[index] = tempA - tempB;
        index++;

        if (index > THREE)
        {
            period = (abuffer[ZERO] + abuffer[ONE] + abuffer[TWO])/THREE;

            if ((period > (abuffer[ONE] - 10)) && (period < (abuffer[ONE] + 10)))
            {
                Icu_GlobalParameter.TimeElaspedValue[channel->IcuChannelId] = period;
            }

            index = ZERO;
        }
    } /* end of handle of ICU_PERIOD_TIME */
    return;
}
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/
