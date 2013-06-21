/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *
 *  All rights reserved. This software is iSOFT property. Duplication
 *  or disclosure without iSOFT written authorization is prohibited.
 *
 *
 *  @file       <Com_Cfg.h>
 *  @brief      <Briefly describe file(one line)>
 *
 *  <Detailed description of the file(multi-line)>
 *
 *  @author     <Gary Chen && zheng fang >
 *  @date       <4-27-2013>
 */
/*============================================================================*/
#ifndef COM_CFGTYPE_H
#define COM_CFGTYPE_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>         <AUTHOR>                    <REVISION LOG>
 *  V1.0.0      20130510   Gary Chen && zheng fang        Initial version
 */
/*============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define COM_CFGTYPE_H_AR_MAJOR_VERSION  3U
#define COM_CFGTYPE_H_AR_MINOR_VERSION  0U
#define COM_CFGTYPE_H_AR_PATCH_VERSION  3U
#define COM_CFGTYPE_H_SW_MAJOR_VERSION  1U
#define COM_CFGTYPE_H_SW_MINOR_VERSION  0U
#define COM_CFGTYPE_H_SW_PATCH_VERSION  0U

/*=======[I N C L U D E S]====================================================*/
#include "ComStack_Types.h"


/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/* @req COM004 */
#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
typedef enum
{
    /* the direction of the IPDU transfer:send */
    COM_IPDU_SENT,
    
    /* the direction of the IPDU transfer:receive */
    COM_IPDU_RECEIVE
}Com_IpduDirectionType;
#endif


#if (OSEK_COM_CCC == OSEK_COM_CCC1)
/* @req COM031 */
typedef enum
{
    /* I-PDU direct transmission mode */
    COM_IPDU_TRANSMIT_DIRECT,
    
    /* I-PDU periodic transmission mode */
    COM_IPDU_TRANSMIT_PERIODIC,
    
    /* I-PDU mixed transmission mode */
    COM_IPDU_TRANSMIT_MIXED
}Com_IpduTransmitModeType;


/* @req COM040 */
typedef enum
{
    /* No filtering is performed so that the message always passes */
    COM_F_Always = 0u,
    
    /* The filter removes all messages */
    COM_F_Never,
    
    /* (new_value&mask) == x */
    COM_F_MaskedNewEqualsX,
    
    /* (new_value&mask) != x */
    COM_F_MaskedNewDiffersX,
    
    /* new_value == old_value */
    COM_F_NewIsEqual,
    
    /* new_value != old_value */
    COM_F_NewIsDifferent,
    
    /* (new_value&mask) == (old_value&mask) */
    COM_F_MaskedNewEqualsMaskedOld,
    
    /* (new_value&mask) != (old_value&mask) */
    COM_F_MaskedNewDiffersMaskedOld,
    
    /* min <= new_value <= max */
    COM_F_NewIsWithin,
    
    /* (min > new_value) OR (new_value > max) */
    COM_F_NewIsOutside,
    
    /* new_value > old_value */
    COM_F_NewIsGreater,
    
    /* new_value <= old_value */
    COM_F_NewIsLessOrEqual,
    
    /* new_value < old_value */
    COM_F_NewIsLess,
    
    /* new_value >= old_value */
    COM_F_NewIsGreaterOrEqual,
    
    /* occurrence % period == offset */
    COM_F_OneEveryN
}Com_MsgFilterAlgorithmType;


/* @req COM057 */
typedef struct
{
    /* constant value for filtering */
    const uint32 filterMask;
    
    /* constant value for filtering */
    const uint32 filterMax;
    
    /* constant value for filtering */
    const uint32 filterMin;
    
    /* constant value for filtering */
    const uint32 filterOffset;
    
    /* constant value for filtering */
    const uint32 filterPeriodFactor;
    
    /* constant value for filtering */
    const uint32 filterX;
    
    /* filter algorithm for filtering */
    const Com_MsgFilterAlgorithmType filterAlgorithm;
}Com_MsgFilterType;
#endif


typedef enum
{
    /* static internal sending message */
    COM_MSG_SEND_STATIC_INTERNAL,
    
    /* un-queued internal receving message */
    COM_MSG_RECEIVE_UNQUEUED_INTERNAL,
    
    /* zero senders receving message */
    COM_MSG_RECEIVE_ZERO_SENDERS,
    
    #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
    /* static external sending message */
    COM_MSG_SEND_STATIC_EXTERNAL,
    
    /* un-queued external receving message */
    COM_MSG_RECEIVE_UNQUEUED_EXTERNAL,
    #endif

    #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
    /* queued internal receving message */
    COM_MSG_RECEIVE_QUEUED_INTERNAL,
    #endif

    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    /* dynamic external sending message */
    COM_MSG_SEND_DYNAMIC_EXTERNAL,
    
    /* zero-length internal sending message */
    COM_MSG_SEND_ZERO_INTERNAL,
    
    /* zero-length external sending message */
    COM_MSG_SEND_ZERO_EXTERNAL,
    
    /* zero-length internal receving message */
    COM_MSG_RECEIVE_ZERO_INTERNAL,
    
    /* zero-length external receiving message */
    COM_MSG_RECEIVE_ZERO_EXTERNAL,
    
    /* queued external receving message */
    COM_MSG_RECEIVE_QUEUED_EXTERNAL,
    
    /* dynamic external receving message */
    COM_MSG_RECEIVE_DYNAMIC_EXTERNAL
    #endif
}Com_MsgPropertyType;


typedef enum
{
    /* message type: boolean */
    COM_MSG_BOOLEAN,
    
    /* message type: unsigned char */
    COM_MSG_UINT8,
    
    /* message type: unsigned short */
    COM_MSG_UINT16,
    
    /* message type: unsigned long */
    COM_MSG_UINT32,
    
    /* message type: signed char */
    COM_MSG_SINT8,
    
    /* message type: signed short */
    COM_MSG_SINT16,
    
    /* message type: signed long */
    COM_MSG_SINT32
}Com_MsgCDataType;


#if (OSEK_COM_CCC == OSEK_COM_CCC1)
typedef enum
{
    /*
     * The IPDU containing the message may or may
     * not be sent immediately depending upon
     * TRANSMISSIONMODE of the IPDU
     */
    COM_MSG_TRIGGERED,
    
    /* No action is taken */
    COM_MSG_PENDING
}Com_MsgTransferPropertyType;
#endif


#if (OSEK_COM_CCC == OSEK_COM_CCC1)
typedef enum
{
    /* static length message */
    COM_MSG_STATIC,
    
    /* dynamic length message */
    COM_MSG_DYNAMIC,
    
    /* zero length message */
    /* @req COM005 */
    COM_MSG_ZERO
}Com_MsgClassType;
#endif


#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
typedef enum
{
    /* big endian bit ordering */
    COM_MSG_BIG_ENDIAN,
    
    /* little endian bit ordering */
    COM_MSG_LITTLE_ENDIAN
}Com_MsgBitOrderingType;


typedef enum
{
    /*
     * the data type of the message data
     * using C language types: int
     */
    COM_MSG_UNSIGNEDINTEGER,
    
    /*
     * the data type of the message data
     * using C language types: byte array
     */
    COM_MSG_BYTEARRAY
}Com_MsgDataInterpretationType;


typedef enum
{
    /* the transfer direction of the MESSAGE: send */
    COM_MSG_SENT,
    
    /* the transfer direction of the MESSAGE: receive */
    COM_MSG_RECEIVED
}Com_MsgDirectionType;
#endif


/* @req COM152 */
/* defines the message notification function type */
typedef P2FUNC(void, COM_APPL_CODE, Com_NotifFnc)(void);


#if (OSEK_COM_CCC == OSEK_COM_CCC1)
/* defines the name of the call-out routine for this MESSAGE */
typedef P2FUNC(boolean, COM_APPL_CODE, Com_CallOutFnc)(void);
#endif


/* defines the user-supplied function StartCOMExtension type */
typedef P2FUNC(void, COM_APPL_CODE, Com_ExtensionFnc)(void);


#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
typedef struct
{
    /* Pdu id */
    const uint16 pduId;
    
    /* bit size of IPDU */
    const uint32 sizeInBits;
    
    const Com_IpduDirectionType direction;
    
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    const Com_IpduTransmitModeType transmitMode;

    /* Tx Periodic timer */
    const uint32 timePeriod;
    
    /* Tx First Periodic timer */
    /* @req COM108 */
    const uint32 timeOffset;
    
    /* Tx Delay Timer */
    const uint32 minimumDelayTime;
    
    /* Tx Confirm TimeOut Or RxIndication TimeOut */
    const uint32 timeOut;
    
    /* Frist RxIndication TimeOut */
    const uint32 firstTimeOut;
    
    /* Callout when sending or receiving IPDU */
    const Com_CallOutFnc ipduCallOut;
    #endif
}Com_IPduType;
#endif


#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
/*
 * @req COM017, @req COM076, @req COM077, @req COM007,@req COM 022
 * @req COM112
 */
typedef struct
{
    /*
     * specifies, in bits, the size of a static-length
     * message in an IPDU
     */
    /* @req COM036, @req COM 011, @req COM 012 */
    const uint32 sizeInBits;
    
    /* start bit positon of a message in I-PDU */
    const uint32 bitPosition;
    
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    /*
     * specifies, in bits, the maximum size that a
     * dynamic message might reach
     */
    const uint32 maximumSizeInBits;
    #endif

    /* reference to the IPDU that carries this NETWORKMESSAGE */
    /* @req COM005,  @req COM020, @req COM021, @req COM010 */
    P2CONST(Com_IPduType, TYPEDEF, CODE_CONST_PBCFG)ipduPtr;
    
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    /* network message type */
    const Com_MsgClassType msgClass;
    #endif

    /* specifies the bit ordering within a message */
    const Com_MsgBitOrderingType bitOrdering;
    
    /* used for byte swapping for unsigned integer values */
    const Com_MsgDataInterpretationType dataInterpretation;
    
    /* specifies the transfer direction of the MESSAGE */
    const Com_MsgDirectionType direction;
}Com_NWMsgType;
#endif


/* @req COM043, @req COM085, @req COM195 */
typedef struct Com_MsgTypeTag
{
    /* specifies the initial value of a MESSAGE */
    const uint8 initialValue[8];
    
    #if ((OSEK_COM_CCC == OSEK_COM_CCCB) || (OSEK_COM_CCC == OSEK_COM_CCC1))
    /*
     * defines the maximum number of messages that
     * the queue for a queued message can store
     */
    /* @req COM025 */
    const uint32 queueSize;
    #endif

    /*
     * used by a receiver of an internal message to
     * identify the sender of the message
     */
    P2CONST(struct Com_MsgTypeTag, TYPEDEF, COM_CONST_PBCFG)sendMsgPtr;
    
    #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
    /*
     * determines whether this message has its own
     * field within the IPDU or fans out from
     * another message's IPDU field
     */
    /* @req COM004 */
    P2CONST(struct Com_MsgTypeTag, TYPEDEF, COM_CONST_PBCFG)linkMsgPtr;
    
    /*
     * defines the NETWORKMESSAGE that is linked to
     * this MESSAGE
     */
    P2CONST(Com_NWMsgType, TYPEDEF, COM_CONST_PBCFG)NWMsgPtr;
    #endif


    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    /* specifies the action of the message filter */
    /* @req COM052 */
    P2CONST(Com_MsgFilterType, TYPEDEF, COM_CONST_PBCFG)filterPtr;
    
    /* notification of message un-successful reception */
    /* @req COM037 */
    const Com_NotifFnc DMNotif;
    
    /*
     * defines the name of the network-order
     * call-out routine for this MESSAGE
     */
    const Com_CallOutFnc netWorkOrderCallout;
    
    /*
     * defines the name of the CPU-order
     * call-out routine for this MESSAGE
     */
    const Com_CallOutFnc cpuOrderCallout;
    
    /*
     * the action that OSEK COM takes when this
     * message is sent by the application
     */
    /* @req COM027 */
    const Com_MsgTransferPropertyType transferProperty;
    #endif

    /* notification of message successful reception */
    /* @req COM119, @req COM140 */
    const Com_NotifFnc msgNotif;
    
    /* message type */
    /* @req COM030 */
    const Com_MsgPropertyType property;
    
    /* data type of the message data using C language types */
    const Com_MsgCDataType cData;
}Com_MsgType;


typedef struct
{
    /* used buffer length */
    const uint16 bufferLength;
    
    #if ((OSEK_COM_CCC == OSEK_COM_CCC0) || (OSEK_COM_CCC == OSEK_COM_CCC1))
    /* I-PDU configuration data structure pointer */
    P2CONST(Com_IPduType, COM_CONST_PBCFG, COM_CONST_PBCFG)ipduPtr;
    #endif

    /* Message configuration data structure pointer */
    P2CONST(Com_MsgType, COM_CONST_PBCFG, COM_CONST_PBCFG)messagePtr;
    
    /* OSEK COM extension function pointer */
    /* @req COM194 */
    const Com_ExtensionFnc startCOMExtension;
    
    #if ((OSEK_COM_CCC == OSEK_COM_CCC0) || (OSEK_COM_CCC == OSEK_COM_CCC1))
    /* used I-Pdu number */
    const uint16 ipduUsedNum;
    #endif

    /* used message number */
    const uint16 msgUsedNum;
    
    #if ((OSEK_COM_CCC == OSEK_COM_CCC0) || (OSEK_COM_CCC == OSEK_COM_CCC1))
    /* defines the time base for OSEK COM */
    const uint16 timeBase;
    
    /* I-Pdu tx group id */
    const Com_PduGroupIdType sendPduGroupId;
    
    /* I-Pdu rx group id */
    const Com_PduGroupIdType receivePduGroupId;
    #endif
}Com_ConfigType;



#endif  /* end of COM_CFGTYPE_H */

/*=======[E N D   O F   F I L E]==============================================*/
