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
/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */
/* MISRA-C:2004 Rule 17.4; REFERENCE - ISO:C90-6.3.6 Additive Operators - Constraints */

/*=======[I N C L U D E S]====================================================*/
#include "Port.h"
#include "Modules.h"
#include "Det.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define PORT_C_AR_MAJOR_VERSION    3
#define PORT_C_AR_MINOR_VERSION    1
#define PORT_C_AR_PATCH_VERSION    0
#define PORT_C_SW_MAJOR_VERSION    1
#define PORT_C_SW_MINOR_VERSION    0
#define PORT_C_SW_PATCH_VERSION    0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if (PORT_C_AR_MAJOR_VERSION != PORT_H_AR_MAJOR_VERSION)
  #error "PORT.c : Mismatch in Specification Major Version"
#endif
#if (PORT_C_AR_MINOR_VERSION != PORT_H_AR_MINOR_VERSION)
  #error "PORT.c : Mismatch in Specification Major Version"
#endif
#if (PORT_C_AR_PATCH_VERSION != PORT_H_AR_PATCH_VERSION)
  #error "PORT.c : Mismatch in Specification Major Version"
#endif
#if (PORT_C_SW_MAJOR_VERSION != PORT_H_SW_MAJOR_VERSION)
  #error "PORT.c : Mismatch in Specification Major Version"
#endif
#if (PORT_C_SW_MINOR_VERSION != PORT_H_SW_MINOR_VERSION)
  #error "PORT.c : Mismatch in Specification Major Version"
#endif
#if (PORT_C_SW_PATCH_VERSION != PORT_H_SW_PATCH_VERSION)
  #error "PORT.c : Mismatch in Specification Major Version"
#endif

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   D A T A]==========================================*/
STATIC VAR(Port_StateType, PORT_VAR) portState = PORT_UNINITIALIZED;

STATIC P2CONST(Port_ConfigType, AUTOMATIC, PORT_CONST) portGlobal = NULL_PTR;

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
#define PORT_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, PORT_CODE) Port_InitialHw(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr);
STATIC FUNC(void, PORT_CODE) Port_SetHwDirection(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinDirectionType direction);
STATIC FUNC(void, PORT_CODE) Port_SetPinInitMode(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode);
STATIC FUNC(void, PORT_CODE) Port_SetMode1(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode);
STATIC FUNC(void, PORT_CODE) Port_SetMode2(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode);
STATIC FUNC(void, PORT_CODE) Port_SetMode3(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode);
STATIC FUNC(void, PORT_CODE) Port_SetMode4(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode);
#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/*
 * Brief               <Initializes the Port Drive module.>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <ConfigPtr: Pointer to configuration set.>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

FUNC(void, PORT_PUBLIC_CODE) Port_Init(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST)ConfigPtr)
{
    /** @req PORT078 @req PORT071 */
    portState = PORT_UNINITIALIZED;

    /** @req PORT105 */
    #if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_INIT_ID, PORT_E_PARAM_CONFIG);
        return;
    }
    #endif /* STD_ON == PORT_DEV_ERROR_DETECT */

    /** @req PORT121 */
    portGlobal = ConfigPtr;

    Port_InitialHw(portGlobal);

    portState = PORT_INITIALIZED;

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Sets the port pin direction.>
 * ServiceId           <0x01>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Pin, Direction>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

FUNC(void, PORT_PUBLIC_CODE) Port_SetPinDirection(Port_PinType pin, Port_PinDirectionType direction)
{
    uint8 i;
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_CODE) portTempptr = portGlobal;

    /** @req PORT051 @req PORT031 @req PORT077 @req PORT087 */
    #if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (PORT_UNINITIALIZED == portState)
    {
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_DIRECTION_ID, PORT_E_UNINIT);
        return;
    }
    #endif /* STD_ON == PORT_DEV_ERROR_DETECT */

    /** @req PORT054 */
    for	(i = ZERO; i < PADCONFIG_NUM; i++)
    {
        if (portTempptr->PortPinId != pin)
        {
            portTempptr++;
        }
        else
        {
            break;
        }
    }

    #if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (PADCONFIG_NUM == i)
    {
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_DIRECTION_ID, PORT_E_PARAM_PIN);
        return;
    }
    /** @req PORT086 */
    if (FALSE == portTempptr->PortPinDirectionChangeable)
    {
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_DIRECTION_ID, PORT_E_DIRECTION_UNCHANGEABLE);
        return;
    }
    #endif /* STD_ON == PORT_DEV_ERROR_DETECT */

    /** @req PORT137 @req PORT063 */
    Port_SetHwDirection(portTempptr, direction);

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Refreshes port direction.>
 * ServiceId           <0x02>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

FUNC(void, PORT_PUBLIC_CODE) Port_RefreshPortDirection(void)
{
    uint8 i;
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_CODE) portTempptr = portGlobal;

    /** @req PORT116 @req PORT051 @req PORT100 @req PORT101 @req PORT038 */
    /** @req PORT107 @req PORT031 @req PORT077 @req PORT087 */
    #if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (PORT_UNINITIALIZED == portState)
    {
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_REFRESH_PORT_DIRECTION_ID, PORT_E_UNINIT);
        return;
    }
    #endif /* STD_ON == PORT_DEV_ERROR_DETECT */

    /** @req PORT060 */
    for (i = ZERO; i < PADCONFIG_NUM; i++)
    {
        /** @req PORT066 @req PORT061 */
        if (FALSE == portTempptr->PortPinDirectionChangeable)
        {
            Port_SetHwDirection(portTempptr, portTempptr->PortPinDirection);
        }

        portTempptr++;
    }

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Returns the version information of this module.>
 * ServiceId           <0x03>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <versioninfo>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

/** @req PORT103 */
#if (STD_ON == PORT_VERSION_INFO_API)
FUNC(void, PORT_PUBLIC_CODE) Port_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) versionInfo)
{
    /** @req PORT116 @req PORT051 @req PORT100 @req PORT101 @req PORT038 */
    /** @req PORT107 @req PORT031 @req PORT077 @req PORT087 */
    #if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (PORT_UNINITIALIZED == portState)
    {
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_GET_VERSION_INFO_ID, PORT_E_UNINIT);
        return;
    }
    #endif /* STD_ON == PORT_DEV_ERROR_DETECT */

    /** @req PORT102 */
    versionInfo->vendorID = PORT_VENDOR_ID;
    versionInfo->moduleID = PORT_MODULE_ID;
    versionInfo->ar_major_version = PORT_H_AR_MAJOR_VERSION;
    versionInfo->ar_minor_version = PORT_H_AR_MINOR_VERSION;
    versionInfo->ar_patch_version = PORT_H_AR_PATCH_VERSION;
    versionInfo->sw_major_version = PORT_H_SW_MAJOR_VERSION;
    versionInfo->sw_minor_version = PORT_H_SW_MINOR_VERSION;
    versionInfo->sw_patch_version = PORT_H_SW_PATCH_VERSION;
    versionInfo->instanceID = PORT_VENDOR_API_INFIX;

    return;
}
#endif /* STD_ON == PORT_VERSION_INFO_API */

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Sets the port pin mode.>
 * ServiceId           <0x04>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <Pin, Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

FUNC(void, PORT_PUBLIC_CODE) Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    uint8 i;
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_CODE) portTempptr = portGlobal;
    Port_PinModeType portTempMode = Mode;

    /** @req PORT116 @req PORT051 @req PORT100 @req PORT101 @req PORT038 */
    /** @req PORT107 @req PORT031 @req PORT077 @req PORT087 */
    #if (STD_ON == PORT_DEV_ERROR_DETECT)
    if (PORT_UNINITIALIZED == portState)
    {
       	Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_MODE_ID, PORT_E_UNINIT);
       	return;
    }
    if (Mode >= PORT_PIN_MAX_MODE)
    {
       	Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_MODE_ID, PORT_E_PARAM_INVALID_MODE);
       	return;
    }
    #endif /* STD_ON == PORT_DEV_ERROR_DETECT */

    for (i = ZERO; i < PADCONFIG_NUM; i++)
    {
        if (portTempptr->PortPinId != Pin)
        {
            portTempptr++;
        }
        else
        {
            break;
        }
    }
    if (PADCONFIG_NUM == i)
    {
        #if (STD_ON == PORT_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_MODE_ID, PORT_E_PARAM_PIN);
        #endif /* STD_ON == PORT_DEV_ERROR_DETECT */

        return;
    }

    if (TRUE == portTempptr->PortPinModeChangeable)
    {
        /** @req PORT125 @req PORT128 */
        Port_SetPinInitMode(portTempptr, portTempMode);
    }
    #if (STD_ON == PORT_DEV_ERROR_DETECT)
    else
    {
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_MODE_ID, PORT_E_MODE_UNCHANGEABLE);
        return;
    }
    #endif /* STD_ON == PORT_DEV_ERROR_DETECT */

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/*=======[L O C A L   F U N C T I O N   I M P L E M E N T A T I O N S]=======*/

/******************************************************************************/
/*
 * Brief               <Set relative registers to initialize each pin.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Port_Init> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, PORT_CODE) Port_InitialHw(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr)
{
    uint8 i;
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_CODE) portTempptr = NULL_PTR;

    portTempptr = ConfigPtr;

    /** @req PORT041 @req PORT042 @req PORT113 @req PORT043 @req PORT002 @req PORT003 */
    for (i = ZERO; i < PADCONFIG_NUM; i++)
    {
        Port_SetPinInitMode(portTempptr, portTempptr->PortPinMode);

        if (PORT_PIN_MODE_DIO == portTempptr->PortPinMode)
        {
            /** @req PORT055 */
            SIU.GPDO[portTempptr->PortPinId].R = portTempptr->PortPinLevelValue;
        }

        Port_SetHwDirection(portTempptr, portTempptr->PortPinDirection);

        portTempptr++;
    }

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to set pin's direction.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ConfigPtr, direction>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Port_SetPinDirection, Port_RefreshPortDirection, Port_InitialHw> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, PORT_CODE) Port_SetHwDirection(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST)ConfigPtr, Port_PinDirectionType direction)
{
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_CODE) portTempptr = ConfigPtr;

    Port_ReadBackType portReadBack[] =
    {
        PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,
        PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,
        PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,
        PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,
        PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,
        PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,
        PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL,PIN_LEVEL
    };

    if (PORT_PIN_IN == direction)
    {
        SIU.PCR[portTempptr->PortPinId].B.IBE = ONE;
        SIU.PCR[portTempptr->PortPinId].B.OBE = ZERO;
    }
    else if (PORT_PIN_OUT == direction)
    {
        SIU.PCR[portTempptr->PortPinId].B.IBE = ZERO;
        SIU.PCR[portTempptr->PortPinId].B.OBE = ONE;

        if (TRUE == portTempptr->PortPinDirectionChangeable)
        {
            if (PIN_LEVEL == portReadBack[portTempptr - portGlobal])
            {
                SIU.PCR[portTempptr->PortPinId].B.IBE = TRUE;
            }
        }
    }
    else
    {
        /* empty */
    }

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers to set pin's mode.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ConfigPtr, Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Port_SetPinMode, Port_InitialHw> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, PORT_CODE) Port_SetPinInitMode(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode)
{
    if ((PORT_PIN_MODE_CAN == Mode) || (PORT_PIN_MODE_ADC == Mode)\
     || (PORT_PIN_MODE_LIN == Mode) || (PORT_PIN_MODE_K_LINE == Mode))
    {
        Port_SetMode1(ConfigPtr, Mode);
    }
    else if	((PORT_PIN_MODE_SPI_B == Mode) || (PORT_PIN_MODE_SPI_C == Mode))
    {
        Port_SetMode2(ConfigPtr, Mode);
    }
    else if	((PORT_PIN_MODE_PWM == Mode) || (PORT_PIN_MODE_ICU == Mode) || (PORT_PIN_MODE_DIO == Mode))
    {
        Port_SetMode3(ConfigPtr, Mode);
    }
    else if	((PORT_PIN_MODE_ETPU_A0 == Mode) || (PORT_PIN_MODE_ETPU_A1 == Mode) || (PORT_PIN_MODE_ETPU_A3 == Mode)\
          || (PORT_PIN_MODE_ETPU_A4 == Mode) || (PORT_PIN_MODE_ETPU_A5 == Mode) || (PORT_PIN_MODE_ETPU_A6 == Mode)\
          || (PORT_PIN_MODE_ETPU_A7 == Mode) || (PORT_PIN_MODE_ETPU_A8 == Mode) || (PORT_PIN_MODE_ETPU_A9 == Mode)\
          || (PORT_PIN_MODE_ETPU_A10 == Mode) || (PORT_PIN_MODE_ETPU_A11 == Mode) || (PORT_PIN_MODE_ETPU_A12 == Mode)\
          || (PORT_PIN_MODE_ETPU_A13 == Mode))
    {
        Port_SetMode4(ConfigPtr, Mode);
    }
    else
    {
        #if (STD_ON == PORT_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_MODE_ID, PORT_E_PARAM_INVALID_MODE);
        #endif /* STD_ON == PORT_DEV_ERROR_DETECT */
    }

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers for CAN, ADC and LIN mode.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ConfigPtr, Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Port_SetPinInitMode> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, PORT_CODE) Port_SetMode1(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode)
{
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_CODE) portTempptr = ConfigPtr;

    if ((PORT_PIN_MODE_CAN == Mode)\
    && ((PORT_PA0_66 == portTempptr->PortPinId) || (PORT_PA1_67 == portTempptr->PortPinId)\
     || (PORT_PA2_84 == portTempptr->PortPinId) || (PORT_PA3_81 == portTempptr->PortPinId)))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT0; /* Set the pin mode is CAN bus */
    }
    else if	(((PORT_PIN_MODE_LIN == Mode) || (PORT_PIN_MODE_K_LINE == Mode))\
          && ((portTempptr->PortPinId >= PORT_PA4_83) && (portTempptr->PortPinId <= PORT_PA7_69)))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT0; /* Set the pin mode is LIN */
    }
    else if	((PORT_PIN_MODE_ADC == Mode)\
         && ((portTempptr->PortPinId >= PORT_PD14_119) && (portTempptr->PortPinId < PORT_PE2_99)))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = (BIT1 | BIT0); /* Set the pin mode is ADC */
    }
    else
    {
        #if (STD_ON == PORT_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_MODE_ID, PORT_E_PARAM_INVALID_MODE);
        #endif /* STD_ON == PORT_DEV_ERROR_DETECT */
    }

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers for SPI mode.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ConfigPtr, Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Port_SetPinInitMode> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, PORT_CODE) Port_SetMode2(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode)
{
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_CODE) portTempptr = ConfigPtr;

    if ((PORT_PIN_MODE_SPI_B == Mode)\
    && ((portTempptr->PortPinId >= PORT_PA8_89) && (portTempptr->PortPinId <= PORT_PB0_87)))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT0;
    }
    else if (((PORT_PIN_MODE_SPI_B == Mode)\
         && ((portTempptr->PortPinId >= PORT_PB13_38) && (portTempptr->PortPinId <= PORT_PC0_33)))\
         || ((PORT_PIN_MODE_SPI_C == Mode)\
         && ((portTempptr->PortPinId >= PORT_PC15_15) && (portTempptr->PortPinId <= PORT_PD0_14))))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT1;
        SIU.PCR[portTempptr->PortPinId].B.OBE = BIT0;
    }
    else if ((PORT_PIN_MODE_SPI_C == Mode)\
        && (((portTempptr->PortPinId >= PORT_PA8_89) && (portTempptr->PortPinId <= PORT_PA10_96))\
         || ((portTempptr->PortPinId >= PORT_PA13_90) && (portTempptr->PortPinId <= PORT_PB0_87))))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT1;
    }
    else if ((PORT_PIN_MODE_SPI_C == Mode)\
         && ((portTempptr->PortPinId >= PORT_PC13_17) && (portTempptr->PortPinId <= PORT_PC14_16)))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT0;
        SIU.PCR[portTempptr->PortPinId].B.OBE = BIT0;
    }
    else
    {
        #if (STD_ON == PORT_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_MODE_ID, PORT_E_PARAM_INVALID_MODE);
        #endif /* STD_ON == PORT_DEV_ERROR_DETECT */
    }

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers for PWM, ICU and DIO mode.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ConfigPtr, Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Port_SetPinInitMode> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, PORT_CODE) Port_SetMode3(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode)
{
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_CODE) portTempptr = ConfigPtr;

    if ((PORT_PIN_MODE_PWM == Mode) && ((PORT_PD1_54 == portTempptr->PortPinId)\
     || (PORT_PD2_55 == portTempptr->PortPinId) || (PORT_PD3_56 == portTempptr->PortPinId)\
     || ((portTempptr->PortPinId >= PORT_PD4_57) && (portTempptr->PortPinId <= PORT_PD8_63))\
     || (PORT_PD9_64 == portTempptr->PortPinId) || (PORT_PD10_65 == portTempptr->PortPinId)))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT0;
        SIU.PCR[portTempptr->PortPinId].B.OBE = BIT0;
        SIU.PCR[portTempptr->PortPinId].B.IBE = BIT0;
    }
    else if	((PORT_PIN_MODE_ICU == Mode)\
         && ((PORT_PD1_54 == portTempptr->PortPinId) || (PORT_PD4_57 == portTempptr->PortPinId)\
         || (PORT_PD5_58 == portTempptr->PortPinId) || (PORT_PD6_60 == portTempptr->PortPinId)\
         || ((portTempptr->PortPinId >= PORT_PD8_63) && (portTempptr->PortPinId <= PORT_PD10_65))))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT0;
        SIU.PCR[portTempptr->PortPinId].B.IBE = BIT0;
    }
    else if	((PORT_PIN_MODE_DIO == Mode)\
         && (((portTempptr->PortPinId >= PORT_PA0_66) && (portTempptr->PortPinId <= PORT_PA1_67))\
         || ((portTempptr->PortPinId >= PORT_PA2_84) && (portTempptr->PortPinId <= PORT_PA7_69))\
         || ((portTempptr->PortPinId >= PORT_PA8_89) && (portTempptr->PortPinId <= PORT_PB0_87))\
         || ((portTempptr->PortPinId >= PORT_PB1_52) && (portTempptr->PortPinId <= PORT_PD0_14))\
         || ((PORT_PD1_54 == portTempptr->PortPinId) || (PORT_PD2_55 == portTempptr->PortPinId))\
         || ((PORT_PD3_56 == portTempptr->PortPinId) || (PORT_PD9_64 == portTempptr->PortPinId))\
         || ((portTempptr->PortPinId >= PORT_PD4_57) && (portTempptr->PortPinId <= PORT_PD8_63))\
         || ((PORT_PD10_65 == portTempptr->PortPinId) || (PORT_PD11_68 == portTempptr->PortPinId))\
         || ((portTempptr->PortPinId >= PORT_PD12_70) && (portTempptr->PortPinId <= PORT_PD13_71))\
         || ((portTempptr->PortPinId >= PORT_PE2_99) && (portTempptr->PortPinId <= PORT_PE8_101))\
         || ((portTempptr->PortPinId >= PORT_PE9_106) && (portTempptr->PortPinId <= PORT_PE10_100))\
         || ((portTempptr->PortPinId >= PORT_PE11_103) && (portTempptr->PortPinId <= PORT_PE12_107))))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = ZERO;
        SIU.PCR[portTempptr->PortPinId].B.WPE = ZERO;

        if (PORT_PIN_OUT == portTempptr->PortPinDirection)
        {
            SIU.PCR[portTempptr->PortPinId].B.OBE = BIT0;
        }
        else
        {
            SIU.PCR[portTempptr->PortPinId].B.IBE = BIT0;
        }
    }
    else
    {
        #if (STD_ON == PORT_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_MODE_ID, PORT_E_PARAM_INVALID_MODE);
        #endif /* STD_ON == PORT_DEV_ERROR_DETECT */
    }

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Set relative registers for ETPU mode.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ConfigPtr, Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Port_SetPinInitMode> 
 */
/******************************************************************************/
#define PORT_START_SEC_CODE
#include "MemMap.h"

STATIC FUNC(void, PORT_CODE) Port_SetMode4(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST) ConfigPtr, Port_PinModeType Mode)
{
    P2CONST(Port_ConfigType, AUTOMATIC, PORT_CODE) portTempptr = ConfigPtr;

    if (PORT_PIN_MODE_ETPU_A0 == Mode)
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = (BIT1 | BIT0);
        SIU.PCR[portTempptr->PortPinId].B.IBE = BIT0;
    }
    else if	((PORT_PIN_MODE_ETPU_A1 == Mode) || (PORT_PIN_MODE_ETPU_A11 == Mode)\
          || (PORT_PIN_MODE_ETPU_A12 == Mode) || (PORT_PIN_MODE_ETPU_A13 == Mode))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT0;
        SIU.PCR[portTempptr->PortPinId].B.IBE = BIT0;
    }
    else if	((PORT_PIN_MODE_ETPU_A3 == Mode) || (PORT_PIN_MODE_ETPU_A4 == Mode) || (PORT_PIN_MODE_ETPU_A5 == Mode)\
          || (PORT_PIN_MODE_ETPU_A6 == Mode) || (PORT_PIN_MODE_ETPU_A7 == Mode) || (PORT_PIN_MODE_ETPU_A8 == Mode)\
          || (PORT_PIN_MODE_ETPU_A9 == Mode) || (PORT_PIN_MODE_ETPU_A10 == Mode))
    {
        SIU.PCR[portTempptr->PortPinId].B.PA = BIT0;
        SIU.PCR[portTempptr->PortPinId].B.OBE = BIT0;
    }
    else
    {
        #if (STD_ON == PORT_DEV_ERROR_DETECT)
        Det_ReportError(MODULE_ID_PORT, ZERO, PORT_SET_PIN_MODE_ID, PORT_E_PARAM_INVALID_MODE);
        #endif /* STD_ON == PORT_DEV_ERROR_DETECT */
    }

    return;
}

#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/
