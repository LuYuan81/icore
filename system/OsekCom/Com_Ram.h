/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *
 *  All rights reserved. This software is iSOFT property. Duplication
 *  or disclosure without iSOFT written authorization is prohibited.
 *
 *
 *  @file       <Com_Ram.h>
 *  @brief      <Briefly describe file(one line)>
 *
 *  <Compiler: Cygwin C Compiler    MCU:--->
 *
 *  @author     <Gary Chen && zheng fang>
 *  @date       <2013-5-10>
 */
/*============================================================================*/
#ifndef COM_RAM_H
#define COM_RAM_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>         <AUTHOR>                    <REVISION LOG>
 *  V1.0.0      20130510   Gary Chen && zheng fang        Initial version
 */
/*============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define COM_RAM_H_AR_MAJOR_VERSION  3U
#define COM_RAM_H_AR_MINOR_VERSION  0U
#define COM_RAM_H_AR_PATCH_VERSION  3U
#define COM_RAM_H_SW_MAJOR_VERSION  1U
#define COM_RAM_H_SW_MINOR_VERSION  0U
#define COM_RAM_H_SW_PATCH_VERSION  0U

/*=======[I N C L U D E S]====================================================*/
#include "Com_Cfg.h"


/*=======[T Y P E   D E F I N I T I O N S]====================================*/
typedef struct
{
    /* @req COM020 */
    P2VAR(uint8, TYPEDEF, COM_VAR)bufPtr;
    
    P2VAR(uint8, TYPEDEF, COM_VAR)lastPtr;
    
    P2VAR(uint8, TYPEDEF, COM_VAR)firstPtr;
    
    uint8 length;
    
    uint8 depth;
    
    uint8 nrItems;
}Com_QueueType;


/* message run time structure type */
/*
 * @req COM023 ,@req COM009, @req COM016, @req COM019
 * @req COM024 ,@req COM065,
 */
typedef struct
{
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    /* last message value */
    uint32           msgOldValue;
    
    /* the number of message occurred */
    uint32           occurrence;
    #endif

    /* com message queue */
    Com_QueueType    queue;
    
    #if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCCB))
    /* current status of message object */
    StatusType       messageStatus;
    #endif
}Com_MsgRunTimeType;

#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
/* I-PDU run time structure type */
typedef struct
{
    #if (OSEK_COM_CCC == OSEK_COM_CCC1)
    /* next periodic transmission timer */
    uint32        periodTimer;
    
    /* minimum delay time timer */
    uint32        mdtTimer;
    
    /* Deadline Monitor Timer */
    uint32        DMTimer;
    #endif
    
    /* data space pointer */
    P2VAR(uint8, TYPEDEF, COM_VAR)dataPtr;
    
    /* direct send flag */
    boolean       directSend;
    
    #if (STD_OFF == COM_MSGUNPACK_IMMEDIATE)
    /* I-PDU receive update flag */
    boolean       updateFlag;
    #endif
}Com_IPduRunTimeType;
#endif


/*=======[E X T E R N A L   D A T A]==========================================*/
/* total buffer number of COM module */
#define COM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
extern VAR(uint8, COM_VAR)Com_MemoryBuffer[COM_BUFFER_SIZE];
#define COM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"


/* Message runtime structure array */
#define COM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
extern VAR(Com_MsgRunTimeType, COM_VAR) Com_PrivateMsg[COM_MSG_NUM];
#define COM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"


#if ((OSEK_COM_CCC == OSEK_COM_CCC1) || (OSEK_COM_CCC == OSEK_COM_CCC0))
/* IPdu runtime structure array */
#define COM_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
extern VAR(Com_IPduRunTimeType, COM_VAR) Com_PrivateIPdu[COM_IPDU_NUM];
#define COM_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#endif



#endif  /* end of COM_RAM_H */

/*=======[E N D   O F   F I L E]==============================================*/
