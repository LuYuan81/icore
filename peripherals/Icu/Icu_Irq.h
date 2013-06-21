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
#ifndef ICU_IRQ_H
#define ICU_IRQ_H

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

/*=======[I N C L U D E S]====================================================*/

/* MISRA-C:2004 Rule 3.4; REFERENCE - ISO:C90-6.8.6 Pragma Directive */
#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define ICU_IRQ_VENDOR_ID            0
#define ICU_IRQ_MODULE_ID          122
#define ICU_IRQ_VENDOR_API_INFIX      0
/* AUTOSAR specification version information */
#define ICU_IRQ_H_AR_MAJOR_VERSION    3
#define ICU_IRQ_H_AR_MINOR_VERSION    0
#define ICU_IRQ_H_AR_PATCH_VERSION    2
/* File version information */
#define ICU_IRQ_H_SW_MAJOR_VERSION    1
#define ICU_IRQ_H_SW_MINOR_VERSION    0
#define ICU_IRQ_H_SW_PATCH_VERSION    0

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

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
extern FUNC(void, ICU_CODE) IC0_ISR(void);
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
extern FUNC(void, ICU_CODE) IC8_ISR(void);
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
extern FUNC(void, ICU_CODE) IC9_ISR(void);
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
extern FUNC(void, ICU_CODE) IC10_ISR(void);
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
extern FUNC(void, ICU_CODE) IC12_ISR(void);
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
extern FUNC(void, ICU_CODE) IC14_ISR(void);
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
extern FUNC(void, ICU_CODE) IC23_ISR(void);
#define ICU_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ICU_IRQ_H */

/*=======[E N D   O F   F I L E]==============================================*/
