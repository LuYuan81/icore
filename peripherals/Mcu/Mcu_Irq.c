/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Mcu.c>
 *  @brief      <This is Mcu C file>
 *  
 *  <Compiler: cw2.6    MCU:mpc5634>
 *  
 *  @author     <author name>
 *  @date       <yyyy-mm-dd>
 */
/*============================================================================*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20081127   xx        Initial version
 * 
 *  V1.1.0       20091012   xx      
 * 
 *  V2.0.0       20100210   xx      
 */
/*============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
/* AUTOSAR Specification version information */
#define MCU_IRQ_AR_MAJOR_VERSION     2
#define MCU_IRQ_AR_MINOR_VERSION     3
#define MCU_IRQ_AR_PATCH_VERSION     0

/* File version information */
#define MCU_IRQ_SW_MAJOR_VERSION     1
#define MCU_IRQ_SW_MINOR_VERSION     0
#define MCU_IRQ_SW_PATCH_VERSION	   0

/*=======[I N C L U D E S]====================================================*/
#include "Mcu.h" /* MCU108/include Mcu.h */

/*=======[V E R S I O N  C H E C K]===========================================*/

#if (MCU_AR_MAJOR_VERSION != MCU_IRQ_AR_MAJOR_VERSION)
#error "Mcu.c : Mismatch in Specification Major Version"
#endif

#if (MCU_AR_MINOR_VERSION != MCU_IRQ_AR_MINOR_VERSION)
#error "Mcu.c : Mismatch in Specification Minor Version"
#endif

#if (MCU_AR_PATCH_VERSION != MCU_IRQ_AR_PATCH_VERSION)
#error "Mcu.c : Mismatch in Specification Patch Version"
#endif

#if (MCU_SW_MAJOR_VERSION != MCU_IRQ_SW_MAJOR_VERSION)
#error "Mcu.c : Mismatch in Major Version"
#endif

#if (MCU_SW_MINOR_VERSION != MCU_IRQ_SW_MINOR_VERSION)
#error "Mcu.c : Mismatch in Minor Version"
#endif

#if (MCU_SW_PATCH_VERSION != MCU_IRQ_SW_PATCH_VERSION)
#error "Mcu.c : Mismatch in Minor Version"
#endif

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/*
 * Brief               <Mcu_LoseOfClock_ISR>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <void>  
 * PreCondition        <None>  
 * CallByAPI           <APIName> 
 */
/******************************************************************************/
/* void Mcu_LoseOfClock_ISR(void) */
FUNC(void, MCU_PUBLIC_CODE) Mcu_LoseOfClock_ISR(void)
{
    /* Clear the lose of clock interrupt flag */ 
    FMPLL.SYNSR.B.LOCF = MCU_ASSERT; 
    
    /* Waited for other code */
      
}

/*=======[L O C A L    F U N C T I O N S======================================*/

/*=======[E N D   O F   F I L E]==============================================*/

