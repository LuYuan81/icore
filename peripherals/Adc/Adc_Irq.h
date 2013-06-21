/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <Adc_Irq.h>
 *  @brief      <This is adc header file>
 *  
 *  <Compiler: cw2.6    MCU:mpc5634>
 *  
 *  @author     <author name>
 *  @date       <dd-mm-yyyy>
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
#ifndef ADC_IRQ_H
#define ADC_IRQ_H

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
/* AUTOSAR specification version information */
#define ADC_IRQ_AR_MAJOR_VERSION    3
#define ADC_IRQ_AR_MINOR_VERSION    0
#define ADC_IRQ_AR_PATCH_VERSION    3

/* File version information */
#define ADC_IRQ_SW_MAJOR_VERSION    1
#define ADC_IRQ_SW_MINOR_VERSION    0
#define ADC_IRQ_SW_PATCH_VERSION	0
/*=======[I N C L U D E S]====================================================*/

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

#if (ADC_USE_DMA == STD_ON)
/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group0_ISR>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group0_ISR(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_USE_DMA == STD_ON) */

#if (ADC_USE_DMA == STD_ON)
/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group1_ISR>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group0_ISR(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_USE_DMA == STD_ON) */

#if (ADC_USE_DMA == STD_ON)
/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group2_ISR>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group2_ISR(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_USE_DMA == STD_ON) */

#if (ADC_USE_DMA == STD_ON)
/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group3_ISR>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group2_ISR(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_USE_DMA == STD_ON) */

#if (ADC_USE_DMA == STD_ON)
/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group4_ISR>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group4_ISR(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_USE_DMA == STD_ON) */

#if (ADC_USE_DMA == STD_ON)
/******************************************************************************/
/*
 * Brief               <Adc_DMA_ReadResult_Group5_ISR>
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
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DMA_ReadResult_Group5_ISR(void);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"
#endif/* End the #if (ADC_USE_DMA == STD_ON) */

/******************************************************************************/
/*
 * Brief               <Adc_MemCpy>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <TargetAddr,SrcAddr,Length>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,ADC_PUBLIC_CODE)Adc_MemCpy(P2VAR(uint16, AUTOMATIC, ADC_APPL_CONST)TargetAddr,
							P2VAR(uint16, AUTOMATIC, ADC_APPL_CONST)SrcAddr,uint16 Length);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"	

/******************************************************************************/
/*
 * Brief               <Adc_MemSet>
 * ServiceId           <None>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non-Reentrant>
 * Param-Name[in]      <TargetAddr,Length>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
#define ADC_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,ADC_PUBLIC_CODE)Adc_MemSet(P2VAR(uint16, AUTOMATIC, ADC_APPL_CONST) TargetAddr,uint16 Value,uint16 Length);
#define ADC_STOP_SEC_CODE
#include "MemMap.h"						
/*=======[E N D   O F   F I L E]==============================================*/
#endif/* End the #ifndef ADC_IRQ_H */