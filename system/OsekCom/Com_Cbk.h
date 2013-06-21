/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *
 *  All rights reserved. This software is iSOFT property. Duplication
 *  or disclosure without iSOFT written authorization is prohibited.
 *
 *
 *  @file       <Com_Cbk.h>
 *  @brief      <Briefly describe file(one line)>
 *
 *  <Compiler: Cygwin C Compiler    MCU:--->
 *
 *  @author     <Gary Chen && zheng fang>
 *  @date       <2013-5-10>
 */
/*============================================================================*/
#ifndef COM_CBK_H
#define COM_CBK_H

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
#include "ComStack_Types.h"


/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
/******************************************************************************/
/*
 * Brief                 <This function is called by the lower layer when an COM
 *                       I-PDU shall be transmitted. Within this function,AUTOSAR
 *                       COM shall copy the contents of its I-PDU transmit buffer
 *                       to the L-PDU buffer given by SduPtr.>
 * Service ID            <SERVICE_ID_COM_TRIGGERTRANSMIT>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different PDU-ID groups,Non Reentrant:same PDU-ID>
 * Param-Name[in]        <ComTxPduId:ID of AUTOSAR COM I-PDU that is requested to
 *                                  be transmitted by AUTOSAR COM.>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <PduInfoPtr: Contains a pointer to a buffer(SduDataPtr) to
 *                       where the SDU shall be copied to.On return,the service will
 *                       indicated the length of the copied SDU data in SduLength.>
 * Return                <E_OK: SDU has been copied and SduLength indicates the
                                number of copied bytes. 
                          E_NOT_OK: No SDU has been copied. SduLength has not been set.>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <LIN/FlexRay>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, COM_CODE)
Com_TriggerTransmit
(
    PduIdType ComTxPduId,
    P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA)PduInfoPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is called by the lower layer after an I-PDU
 *                       has been received.>
 * Service ID            <SERVICE_ID_COM_RXINDICATION>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different PDU-ID groups,Non Reentrant:same PDU-ID>
 * Param-Name[in]        <ComRxPduId:ID of AUTOSAR COM I-PDU that has been received.
 *                                  Identifies the data that has been received.>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <PduInfoPtr£Contains the length (SduLength) of the received
                                      I-PDU and a pointer to a buffer (SduDataPtr) 
                                      containing the I-PDU>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <PduR>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_RxIndication
(
    PduIdType ComRxPduId,
    P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA)PduInfoPtr
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief                 <This function is called by the lower layer after the PDU
 *                       has been transmitted on the network. A confirmation that
 *                       is received for an I-PDU that does not require a confirmation
 *                       is silently discarded.>
 * Service ID            <SERVICE_ID_COM_TXCONFIRMATION>
 * Sync/Async            <Synchronous>
 * Reentrancy            <Reentrant:different PDU-ID groups,Non Reentrant:same PDU-ID>
 * Param-Name[in]        <ComTxPduId:ID of AUTOSAR COM I-PDU that has been transmitted>
 * Param-Name[out]       <None>
 * Param-Name[in/out]    <None>
 * Return                <None>
 * PreCondition          <COM module has been initialized>
 * CallByAPI             <PduR>
 */
/******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, COM_CODE)
Com_TxConfirmation
(
    PduIdType ComTxPduId
);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* end of #if ((OSEK_COM_CCC1 == OSEK_COM_CCC) || (OSEK_COM_CCC0 == OSEK_COM_CCC)) */



#endif /* end of COM_CBK_H */

/*=======[E N D   O F   F I L E]==============================================*/
