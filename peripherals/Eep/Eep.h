/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Eep.h>
 *  @brief      <Abstract API of Eep Module>
 *  
 *  <Compiler: CodeWarrior V2.8    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/

#ifndef  EEP_H_
#define  EEP_H_

/*=======[I N C L U D E S]====================================================*/
#include "Std_Types.h"
#include "MemIf_Types.h"
#pragma section WX ".CFG_DATA"
#pragma section WX ".MCAL_CODE"
/*  Unrecognized #pragma arguments 'section WX ".CFG_DATA"' This #pragma directive has been ignored.
    MISRA-C:2004 Rule 3.4; REFERENCE - ISO:C90-6.8.6 Pragma Directive */


/*=======[M A C R O S]========================================================*/
#define EEP_AR_MAJOR_VERSION     2
#define EEP_AR_MINOR_VERSION     2
#define EEP_AR_PATCH_VERSION     2

#define EEP_SW_MAJOR_VERSION     1
#define EEP_SW_MINOR_VERSION     0
#define EEP_SW_PATCH_VERSION     0

/* Service id's for eep functions */
#define EEP_INIT_ID					0x00
#define EEP_SETMODE_ID          	0x01
#define EEP_READ_ID             	0x02
#define EEP_WRITE_ID            	0x03
#define EEP_ERASE_ID            	0x04
#define EEP_COMPARE_ID          	0x05
#define EEP_CANCEL_ID           	0x06
#define EEP_GETSTATUS_ID        	0x07
#define EEP_GETJOBSTATUS_ID     	0x08
#define EEP_GETVERSIONINFO_ID  		0x0A
/* Development errors */
#define EEP_E_PARAM_CONFIG			0x10
#define EEP_E_PARAM_ADDRESS			0x11
#define EEP_E_PARAM_DATA 			0x12
#define EEP_E_PARAM_LENGTH			0x13
#define EEP_E_UNINIT				0x14
#define EEP_E_BUSY					0x15
#define EEP_E_TIMEOUT               0xEF

#define EEP_PAGE_SIZE         (32)
#define EEP_PAGE_MOD_MASK     (0x1Fu)
/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/* The definition address data type for reading from or writting to memory. */
typedef uint16	Eep_AddressType;

/* The data type is the definition for data Length. */
typedef uint16	Eep_LengthType;

/* The data type is the definition for command type. */
typedef enum
{
	EEP_WRITE_STATUS_REGISTER 	= 0x01,
	EEP_WRITE					= 0x02,
	EEP_READ					= 0x03,
	EEP_WRITE_DISABLE 			= 0x04,
	EEP_READ_STATUS_REGISTER 	= 0x05,
	EEP_WRITE_ENABLE 			= 0x06
}Eep_CommandType;

/* The data type is the definition for defining different jobs. */
typedef enum 
{
    EEP_JOB_NONE,
    EEP_JOB_COMPARE,
    EEP_JOB_ERASE,
    EEP_JOB_READ,
    EEP_JOB_WRITE
} Eep_JobType;

/* The data type is the configuration definition. */
typedef struct 
{
	Eep_LengthType 			EepNormalReadBlockSize;
	float32 				EepJobCallCycle;
	Eep_LengthType 			EepSize;
	void (*Eep_JobEndNotification)();
	MemIf_ModeType 			EepDefaultMode;
	Eep_LengthType 			EepFastReadBlockSize;
	Eep_LengthType 			EepNormalWriteBlockSize;
	void(*Eep_JobErrorNotification)();
	Eep_LengthType 			EepFastWriteBlockSize;
	Eep_AddressType 		EepBaseAddress;
}Eep_ConfigType;

/* The data type is the definition for global configuration. */
typedef struct 
{
	P2CONST(Eep_ConfigType,AUTOMOTIC,EEP_APPL_DATA) config;

	MemIf_StatusType    	status;
	MemIf_JobResultType 	jobResultType;
	Eep_JobType    			jobType;
	Eep_AddressType   		sourceAddr;
	P2VAR(uint8,AUTOMOTIC,EEP_APPL_DATA) targetAddrPtr;
	Eep_LengthType    		Length;
	MemIf_ModeType      	mode;
	Eep_LengthType			Block_Read_Size;
	Eep_LengthType			Block_Write_Size;
}Eep_GlobalType;

/*=======[I N C L U D E S]====================================================*/
#include "Eep_Cfg.h"

/*=======[E X T E R N A L   D A T A]==========================================*/
extern VAR(Eep_GlobalType,EEP_VAR_NOINIT) Eep_Global;

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
/******************************************************************************/
/*
 * Brief               <This function shall initialize EEPROM>
 * ServiceId           <0x00>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <ConfigPtr>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(void,EEP_CODE) Eep_Init( P2CONST(Eep_ConfigType,AUTOMATIC,EEP_APPL_DATA) ConfigPtr );

/******************************************************************************/
/*
 * Brief               <This function shall set the mode of EEPROM>
 * ServiceId           <0x01>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <Mode>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(void,EEP_CODE) Eep_SetMode( MemIf_ModeType Mode );

/******************************************************************************/
/*
 * Brief               <This function shall reads from EEPROM.>
 * ServiceId           <0x02>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <EepromAddress,Length>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <DataBufferPtr>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(Std_ReturnType,EEP_CODE) Eep_Read( Eep_AddressType EepromAddress,
                                        P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr,
                                        Eep_LengthType Length );

/******************************************************************************/
/*
 * Brief               <This function shall writes to EEPROM.>
 * ServiceId           <0x03>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <EepromAddress,DataBufferPtr,Length>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(Std_ReturnType,EEP_CODE) Eep_Write( Eep_AddressType EepromAddress,
                                         P2CONST(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr,
                                         Eep_LengthType Length );

/******************************************************************************/
/*
 * Brief               <This function shall service for erasing EEPROM.>
 * ServiceId           <0x04>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <EepromAddress,Length>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(Std_ReturnType,EEP_CODE) Eep_Erase( Eep_AddressType EepromAddress, Eep_LengthType Length );

/******************************************************************************/
/*
 * Brief               <This function shall compares a data block in EEPROM 
 *                      with an EEPROM block in the memory.>
 * ServiceId           <0x05>
 * Sync/Async          <Asynchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <EepromAddress,DataBufferPtr,Length>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(Std_ReturnType,EEP_CODE) Eep_Compare( Eep_AddressType EepromAddress,
                                           P2CONST(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr, 
                                           Eep_LengthType Length );

/******************************************************************************/
/*
 * Brief               <This function cancels a running job.>
 * ServiceId           <0x06>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Non Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(void,EEP_CODE) Eep_Cancel(void);

/******************************************************************************/
/*
 * Brief               <This function returns the EEPROME status.>
 * ServiceId           <0x07>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <MemIf_StatusType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(MemIf_StatusType,EEP_CODE) Eep_GetStatus(void);

/******************************************************************************/
/*
 * Brief               <This function returns the result of the last job.>
 * ServiceId           <0x08>
 * Sync/Async          <Synchronous>
 * Reentrancy          <Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <MemIf_JobResultType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(MemIf_JobResultType,EEP_CODE) Eep_GetJobResult(void);

/******************************************************************************/
/*
 * Brief               <This function shall perform the processing of the EEPROM jobs.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <NON Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <None>  
 */
/******************************************************************************/
extern FUNC(void,EEP_CODE) Eep_MainFunction(void);


/******************************************************************************/
/*
 * Brief               <This function gets the version imformation.>
 * ServiceId           <0x0a>
 * Sync/Async          <Synchronous>
 * Reentrancy          <NON Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <VersioninfoPtr>
 * Return              <None>  
 * PreCondition        <None>  
 */
/******************************************************************************/
#ifdef EEP_VERSION_INFO_API
extern FUNC(void,EEP_CODE) Eep_GetVersionInfo( P2VAR(Std_VersionInfoType,AUTOMATIC,EEP_APPL_DATA) VersioninfoPtr );
#endif
#endif

/*=======[E N D   O F   F I L E]==============================================*/

