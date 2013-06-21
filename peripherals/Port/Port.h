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
#ifndef PORT_H_
#define PORT_H_
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
/* MISRA-C:2004 Rule 3.4; REFERENCE - ISO:C90-6.8.6 Pragma Directive */

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
#include "Port_Cfg.h"

#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define PORT_VENDOR_ID             0
#define PORT_MODULE_ID           124
#define PORT_VENDOR_API_INFIX      0
/* AUTOSAR specification version information */
#define PORT_H_AR_MAJOR_VERSION    3
#define PORT_H_AR_MINOR_VERSION    1
#define PORT_H_AR_PATCH_VERSION    0
/* File version information */
#define PORT_H_SW_MAJOR_VERSION    1
#define PORT_H_SW_MINOR_VERSION    0
#define PORT_H_SW_PATCH_VERSION    0

/*=======[M A C R O S]========================================================*/
/* Service ID */
#define PORT_INIT_ID					0x00
#define PORT_SET_PIN_DIRECTION_ID		0x01
#define PORT_REFRESH_PORT_DIRECTION_ID  0x02
#define PORT_GET_VERSION_INFO_ID        0x03
#define PORT_SET_PIN_MODE_ID 			0x04

/* DET Error Code */
/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN		      0x0A
/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE 0x0B
/* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG		      0x0C
/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE	  0x0D
#define PORT_E_MODE_UNCHANGEABLE	  0x0E
/* API service called without module initialization */
#define PORT_E_UNINIT		          0x0F

#define PADCONFIG_NUM    77

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/* Data type for the symbolic name of a port pin. */
typedef uint8 Port_PinType;

/* Possible direction of a port pin. */
typedef enum
{
  	PORT_PIN_IN = 0,
  	PORT_PIN_OUT

} Port_PinDirectionType;

/* Different port pin modes. */
typedef enum
{
    PORT_PIN_MODE_DIO,
    PORT_PIN_MODE_ADC,	
    PORT_PIN_MODE_PWM,
    PORT_PIN_MODE_ICU,
    PORT_PIN_MODE_SPI_B,
    PORT_PIN_MODE_SPI_C,
    PORT_PIN_MODE_LIN,
    PORT_PIN_MODE_K_LINE,
    PORT_PIN_MODE_CAN,
    PORT_PIN_MODE_ETPU_A0,
    PORT_PIN_MODE_ETPU_A1,
    PORT_PIN_MODE_ETPU_A3,
    PORT_PIN_MODE_ETPU_A4,
    PORT_PIN_MODE_ETPU_A5,
    PORT_PIN_MODE_ETPU_A6,
    PORT_PIN_MODE_ETPU_A7,
    PORT_PIN_MODE_ETPU_A8,
    PORT_PIN_MODE_ETPU_A9,
    PORT_PIN_MODE_ETPU_A10,
    PORT_PIN_MODE_ETPU_A11,
    PORT_PIN_MODE_ETPU_A12,
    PORT_PIN_MODE_ETPU_A13,
    PORT_PIN_MAX_MODE

}Port_PinModeType;

/* Port Pin Level Value list */
typedef enum
{
    PORT_PIN_LEVEL_LOW = 0,
    PORT_PIN_LEVEL_HIGH

}Port_PinLevelValueType;

/* Type of the external data structure containing the initialization data for this module. */
typedef struct 
{
    Port_PinType PortPinId;

    Port_PinDirectionType PortPinDirection;

    boolean PortPinDirectionChangeable;

    Port_PinModeType PortPinMode;

    boolean PortPinModeChangeable;

    Port_PinLevelValueType PortPinLevelValue;

}Port_ConfigType;

/* Define Port state data type. */
typedef enum
{
    PORT_UNINITIALIZED = 0,
    PORT_INITIALIZED

} Port_StateType;

/* define port read back data type. */
typedef enum
{
    PIN_LEVEL,
    OUTPUT_REGISTER

}Port_ReadBackType;

/* HW specific symbolic names of pins. */
typedef enum
{
    PORT_PA0_66   =  83,
    PORT_PA1_67   =  84,
    PORT_PA2_84   =  87,
    PORT_PA3_81   =  88,
    PORT_PA4_83   =  89,
    PORT_PA5_82   =  90,
    PORT_PA6_72   =  91,
    PORT_PA7_69   =  92,
    PORT_PA8_89   = 102,
    PORT_PA9_95   = 103,
    PORT_PA10_96  = 104,
    PORT_PA11_94  = 105,
    PORT_PA12_92  = 106,
    PORT_PA13_90  = 107,
    PORT_PA14_97  = 108,
    PORT_PA15_88  = 109,

    PORT_PB0_87   = 110,
    PORT_PB1_52   = 114,
    PORT_PB2_51   = 115,
    PORT_PB3_50   = 116,
    PORT_PB4_49   = 117,
    PORT_PB5_47   = 118,
    PORT_PB6_45   = 119,
    PORT_PB7_44   = 120,
    PORT_PB8_43   = 121,
    PORT_PB9_42   = 122,
    PORT_PB10_41  = 123,
    PORT_PB11_40  = 124,
    PORT_PB12_39  = 125,
    PORT_PB13_38  = 126,
    PORT_PB14_37  = 127,
    PORT_PB15_35  = 128,

    PORT_PC0_33   = 129,
    PORT_PC1_32   = 130,
    PORT_PC2_31   = 131,
    PORT_PC3_30   = 132,
    PORT_PC4_29   = 133,
    PORT_PC5_28   = 134,
    PORT_PC6_27   = 135,
    PORT_PC7_25   = 136,
    PORT_PC8_23   = 137,
    PORT_PC9_21   = 138,
    PORT_PC10_20  = 139,
    PORT_PC11_19  = 140,
    PORT_PC12_18  = 141,
    PORT_PC13_17  = 142,
    PORT_PC14_16  = 143,
    PORT_PC15_15  = 144,

    PORT_PD0_14   = 145,
    PORT_PD1_54   = 179,
    PORT_PD2_55   = 181,
    PORT_PD3_56   = 183,
    PORT_PD4_57   = 187,
    PORT_PD5_58   = 188,
    PORT_PD6_60   = 189,
    PORT_PD7_62   = 190,
    PORT_PD8_63   = 191,
    PORT_PD9_64   = 193,
    PORT_PD10_65  = 202,
    PORT_PD11_68  = 208,
    PORT_PD12_70  = 212,
    PORT_PD13_71  = 213,
    PORT_PD14_119 = 215,
    PORT_PD15_118 = 216,

    PORT_PE0_117  = 217,
    PORT_PE1_116  = 218,
    PORT_PE2_99   = 219,
    PORT_PE3_110  = 220,
    PORT_PE4_111  = 221,
    PORT_PE5_112  = 222,
    PORT_PE6_114  = 223,
    PORT_PE7_109  = 224,
    PORT_PE8_101  = 225,
    PORT_PE9_106  = 227,
    PORT_PE10_100 = 228,
    PORT_PE11_103 = 231,
    PORT_PE12_107 = 232

} Port_PinID;

/*=======[E X T E R N A L   D A T A]==========================================*/
extern CONST(Port_ConfigType, PORT_VAR) Port_ConfigData[PADCONFIG_NUM];

#include "Port_Cfg.h"

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

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
extern FUNC(void, PORT_PUBLIC_CODE) Port_Init(P2CONST(Port_ConfigType, AUTOMATIC, PORT_APPL_CONST)ConfigPtr);
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
extern FUNC(void, PORT_PUBLIC_CODE) Port_SetPinDirection(Port_PinType pin, Port_PinDirectionType direction);
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
extern FUNC(void, PORT_PUBLIC_CODE) Port_RefreshPortDirection(void);
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
extern FUNC(void, PORT_PUBLIC_CODE) Port_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, PORT_APPL_DATA) versionInfo);
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
extern FUNC(void, PORT_PUBLIC_CODE) Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);
#define PORT_STOP_SEC_CODE
#include "MemMap.h"

/*=======[I N T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

#endif  /* end of PORT_H_ */

/*=======[E N D   O F   F I L E]==============================================*/
