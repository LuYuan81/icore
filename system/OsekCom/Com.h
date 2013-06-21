/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *
 *  All rights reserved. This software is iSOFT property. Duplication
 *  or disclosure without iSOFT written authorization is prohibited.
 *
 *
 *  @file       <Com.h>
 *  @brief      <Briefly describe file(one line)>
 *
 *  <Compiler: Cygwin C Compiler    MCU:--->
 *
 *  @author     <Gary Chen && zheng fang>
 *  @date       <2013-5-10>
 */
/*============================================================================*/
#ifndef  COM_H
#define  COM_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>         <AUTHOR>                    <REVISION LOG>
 *  V1.0.0      20130510   Gary Chen && zheng fang        Initial version
 */
/*============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define COM_H_AR_MAJOR_VERSION  3U
#define COM_H_AR_MINOR_VERSION  0U
#define COM_H_AR_PATCH_VERSION  3U
#define COM_H_SW_MAJOR_VERSION  1U
#define COM_H_SW_MINOR_VERSION  0U
#define COM_H_SW_PATCH_VERSION  0U

/*=======[I N C L U D E S]====================================================*/
#include "Com_Cfg.h"


/*=======[M A C R O S]========================================================*/
#define COM_MODULE_ID                 50u
#define COM_VENDOR_ID                 62u
#define COM_INSTANCE_ID               0u
#define COM_E_UNINIT                  0xFAu
#define COM_SERVICE_NOT_AVAILABLE     0xF9u
#define E_COM_LIMIT                   0xFFu
#define E_COM_NOMSG                   0xFEu
#define E_COM_ID                      0xFDu
#define E_COM_LENGTH                  0xFCu
#define E_COM_POINTER                 0xFBu

#if (STD_ON == COM_CONFIGURATION_USE_DET)
/* API service ID */
#define SERVICE_ID_COM_INIT                   0x01u
#define SERVICE_ID_COM_DEINIT                 0x02u
#define SERVICE_ID_COM_INITMESSAGE            0x07u
#define SERVICE_ID_COM_STARTPERIODIC          0x08u
#define SERVICE_ID_COM_STOPPERIODIC           0x09u
#define SERVICE_ID_COM_SENDMESSAGE            0x0Au
#define SERVICE_ID_COM_RECEIVEMESSAGE         0x0Bu
#define SERVICE_ID_COM_SENDDYNAMICMESSAGE     0x0Cu
#define SERVICE_ID_COM_RECEIVEDYNAMICMESSAGE  0x0Du
#define SERVICE_ID_COM_SENDZEROMESSAGE        0x0Eu
#define SERVICE_ID_COM_GETMESSAGESTATUS       0x0Fu
#define SERVICE_ID_COM_STARTCOMEXTENSION      0x10u
#define SERVICE_ID_COM_TRIGGERTRANSMIT        0x13u
#define SERVICE_ID_COM_RXINDICATION           0x14u
#define SERVICE_ID_COM_TXCONFIRMATION         0x15u
#define SERVICE_ID_COM_IPDUGROUPSTART         0x03u
#define SERVICE_ID_COM_IPDUGROUPSTOP          0x04u
#define SERVICE_ID_COM_DISABLERECEPTIONDM     0x05u
#define SERVICE_ID_COM_ENABLERECEPTIONDM      0x06u
#define SERVICE_ID_COM_MAINFUNCTIONTX         0x19u
#define SERVICE_ID_COM_MAINFUNCTIONRX         0x18u
#endif


/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/* message length type */
/* @req COM177 */
typedef uint16 Com_LengthType;


/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/******************************************************************************/
/*
 * Brief                <This service initializes internal and external interfaces
 *                       and variables of the AUTOSAR COM layer for the further
 *                       processing. After calling this function the inter-ECU
 *                       communication is still disabled.>
 * Service ID            <SERVICE_ID_COM_INIT>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Non Reentrant>
 * Param-Name[in]        <configPtr:Pointer to the COM configuration data.>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <None>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_Init
(
    P2CONST(Com_ConfigType, AUTOMATIC, COM_CONST_PBCFG)configPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This service stops the inter-ECU communication. All
 *                       started I-PDU groups are stopped and have to be started
 *                       again, if needed, after Com_Init is called. By a call
 *                       to ComDeInit COM is put into an not initialized state.>
 * Service ID            <SERVICE_ID_COM_DEINIT>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Non Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_DeInit(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The service InitMessage initializes the message object
 *                       identified by <Message> with the application data referenced
 *                       by the <DataRef> parameter.>
 * Service ID            <SERVICE_ID_COM_INITMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <MessageIdentifier: message identifier(C identifier).>
 *                       ApplicationDataRef: Reference to the application is message
 *                                           initialization data>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK: the initialization of the message object completed
 *                             successfully
 *                       E_COM_ID:the parameter <Message> is out of range or refers
 *                                to a zero-length message or to an internal transmit
 *                                message>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, COM_CODE)
Com_InitMessage
(
    uint16 MessageIdentifier,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#if (OSEK_COM_CCC == OSEK_COM_CCC1)
/******************************************************************************/
/*
 * Brief                 <The service StartPeriodic starts periodic transmission
 *                       of all messages using either the Periodic or the Mixed
 *                       Transmission Modes, unless periodic transmission is
 *                       already started for these messages.>
 * Service ID            <SERVICE_ID_COM_STARTPERIODIC>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK:periodic transmission was started successfully
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, COM_CODE)
Com_StartPeriodic(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The service StopPeriodic stops periodic transmission of
 *                       all messages using either the Periodic or the Mixed
 *                       Transmission Modes, unless periodic transmission is
 *                       already stopped for these messages.>
 * Service ID            <SERVICE_ID_COM_STOPPERIODIC>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK:periodic transmission was stopped successfully>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, COM_CODE)
Com_StopPeriodic(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/******************************************************************************/
/*
 * Brief                 <The service SendMessage updates the message object
 *                       identified by <Message> with the application message
 *                       referenced by the <DataRef> parameter.>
 * Service ID            <SERVICE_ID_COM_SENDMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier).
 *                       DataRef: Reference to the application's message data to
 *                                be transmitted>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK: the service operation completed successfully
 *                       E_COM_ID: the parameter <Message> is out of range or
 *                                 if it refers to a message that is received
 *                                 or to a dynamic-length or zero-length message
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/* @req COM002 */
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, COM_CODE)
Com_SendMessage
(
    uint16 MessageIdentifier,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The service ReceiveMessage updates the application message
 *                       referenced by <DataRef> with the data in the message object
 *                       identified by <Message>.>
 * Service ID            <SERVICE_ID_COM_RECEIVEMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier).>
 * Param-Name[out]       <DataRef: Reference to the application's message area in
 *                                which to store the received data.>
 * Param-Name[in/out]    <None>
 * Return                <E_OK:data in the queued or unqueued message identified
 *                            by <Message> are available and returned to
 *                            the application successfully.
 *                       E_COM_NOMSG:the queued message identified by <Message>
 *                                   is empty
 *                       E_COM_LIMIT:an overflow of the message queue identified
 *                                   by <Message> occurred since the last call to
 *                                   ReceiveMessage for <Message>.
 *                       E_COM_ID:the parameter <Message> is out of range or if
 *                                it refers to message that is sent or to a
 *                                dynamic length or zero-length message.>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
/* @req COM002 */
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, COM_CODE)
Com_ReceiveMessage
(
    uint16 MessageIdentifier,
    P2VAR(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#if (OSEK_COM_CCC == OSEK_COM_CCC1)
/******************************************************************************/
/*
 * Brief                 <The service SendDynamicMessage updates the message object
 *                       identified by <Message> with the application data referenced
 *                       by the<DataRef> parameter.>
 * Service ID            <SERVICE_ID_COM_SENDDYNAMICMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier).
 *                       ApplicationDataRef: Reference to the application's message data to be
 *                                           transmitted
 *                       LengthRef:Reference to a value containing the length of
 *                                 the data in the message>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK:the service operation completed successfully
 *                       E_COM_ID:the parameter <Message> is out of range or if
 *                                it refers to a received message, a static-length
 *                                message or a zero-length message.
 *                       E_COM_LENGTH:the value to which <LengthRef> points is not
 *                                    within the range 0 to the maximum length
 *                                    defined for <Message>.>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, COM_CODE)
Com_SendDynamicMessage
(
    uint16 MessageIdentifier,
    P2CONST(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef,
    P2CONST(Com_LengthType, AUTOMATIC, COM_APPL_DATA)LengthRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <The service ReceiveDynamicMessage updates the application
 *                       message referenced by <DataRef> with the data in the message
 *                       object identified by <Message>.>
 * Service ID            <SERVICE_ID_COM_SENDDYNAMICMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier). >
 * Param-Name[out]       <ApplicationDataRef: Reference to the application's message area in
 *                                            which to store the received data.
 *                       LengthRef:Reference to an application variable in which
 *                                 to store the message length.>
 * Param-Name[in/out]    <None>
 * Return                <E_OK:data in the unqueued message identified by <Message>
 *                            is returned to the application successfully.
 *                       E_COM_ID:the parameter <Message> is out of range or if
 *                                it refers to a message that is sent, a queued
 *                                message, a static-length message or a zero-length
 *                                message >
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, COM_CODE)
Com_ReceiveDynamicMessage
(
    uint16 MessageIdentifier,
    P2VAR(void, AUTOMATIC, COM_APPL_DATA)ApplicationDataRef,
    P2VAR(Com_LengthType, AUTOMATIC, COM_APPL_DATA)LengthRef
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <External communication:
 *                       The service SendZeroMessage causes immediate transmission
 *                       of the I-PDU associated with the zero-length message <Message>
 *                       except when this message is associated with an I-PDU with
 *                       Periodic Transmission Mode; in this case, no transmission
 *                       is initiated by the call to this service.
 *                       Internal communication:
 *                       The message <Message> is routed to the receiving part of
 *                       the IL for notification >
 * Service ID            <SERVICE_ID_COM_SENDZEROMESSAGE>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier of the zero-length message
 *                               (C identifier).>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_OK:the service operation completed successfully
 *                       E_COM_ID:the parameter <Message> is out of range or if
 *                                it refers to a non-zero-length message.>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             RTE/APP>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, COM_CODE)
Com_SendZeroMessage
(
    uint16 MessageIdentifier
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
/******************************************************************************/
/*
 * Brief                 <The service GetMessageStatus returns the current status
 *                       of the message object <Message>. >
 * Service ID            <SERVICE_ID_COM_GETMESSAGESTATUS>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:same message, Non Reentrant:different message>
 * Param-Name[in]        <Message: Message identifier (C identifier).>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <E_COM_NOMSG: the message queue identified by <Message>
 *                                    is empty
 *                       E_COM_LIMIT: an overflow of the message queue identified
 *                                    by <Message> occurred since the last call to
 *                                    ReceiveMessage for <Message>.
 *                       E_OK: none of the conditions specified above is applicable
 *                             or fulfilled and no error indication is present
 *                       E_COM_ID:the parameter <Message> is out of range or if
 *                                it does not refer to a queued message>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <RTE/APP  >
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(StatusType, COM_CODE)
Com_GetMessageStatus
(
    uint16 MessageIdentifier
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
/******************************************************************************/
/*
 * Brief                 <Start a pre-configured I-PDU group.>
 * Service ID            <SERVICE_ID_COM_IPDUGROUPSTART>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different I-PDU groups,Non Reentrant:same I-PDU group>
 * Param-Name[in]        <IpduGroupId: Id of I-PDU group to be started
 *                       Initialize: flag to request initialization of the data in the
 *                                   I-PDUs of this I-PDU group>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <CANSM>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_IpduGroupStart
(
    Com_PduGroupIdType IpduGroupId ,
    boolean Initialize
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <Stops a pre-configured I-PDU group.>
 * Service ID            <SERVICE_ID_COM_IPDUGROUPSTOP>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different I-PDU groups,Non Reentrant:same I-PDU group>
 * Param-Name[in]        <IpduGroupId: Id of I-PDU group to be stopped>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized and corresponding group is started>
 * CallByAPI             <CANSM>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_IpduGroupStop
(
    Com_PduGroupIdType IpduGroupId
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <Disables the reception deadline monitoring for the I-PDUs
 *                       within the given I-PDU group.>
 * Service ID            <SERVICE_ID_COM_DISABLERECEPTIONDM>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different I-PDU groups,Non Reentrant:same I-PDU group>
 * Param-Name[in]        <IpduGroupId: Id of I-PDU group where reception DM shall be disabled.>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <CANSM>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_DisableReceptionDM
(
    Com_PduGroupIdType IpduGroupId
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <Enables the reception deadline monitoring for the I-PDUs
 *                       within the given I-PDU group.>
 * Service ID            <SERVICE_ID_COM_ENABLERECEPTIONDM>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different I-PDU groups,Non Reentrant:same I-PDU group>
 * Param-Name[in]        <IpduGroupId: Id of I-PDU group where reception DM shall be enabled>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <CANSM>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_EnableReceptionDM
(
    Com_PduGroupIdType IpduGroupId
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function shall perform the processing of the AUTOSAR
 *                       COM transmission activities that are not directly initiated
 *                       by the calls from the RTE and PDU-R. A call to Com_MainFunctionTx
 *                       shall simply return if COM was not previously initialized
 *                       with a call to Com_Init.>
 * Service ID            <SERVICE_ID_COM_MAINFUNCTIONTX>
 * Sync/Async            <Asynchronous>
 * Reentrancy            <Non Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <SchM>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_MainFunctionTx(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function shall perform the processing of the AUTOSAR
 *                       COM receive processing that are not directly initiated by
 *                       the calls from the RTE and PDU-R. A call to Com_MainFunctionRx
 *                       shall simply return if COM was not previously initialized
 *                       with a call to Com_Init.>
 * Service ID            <SERVICE_ID_COM_MAINFUNCTIONRX>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Non Reentrant>
 * Param-Name[in]        <None>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <SchM>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_MainFunctionRx(void);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif



#endif  /* end of COM_H */

/*=======[E N D   O F   F I L E]==============================================*/
