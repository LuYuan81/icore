/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Eep.c>
 *  @brief      <Abstract API of Eep Module>
 *  
 *  <Compiler: CodeWarrior V2.8    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20120410  i-soft       Initial version
 */
/*============================================================================*/
/*  More than one 'break' statement has been used to terminate this iteration statement.
    MISRA-C:2004 Rule 14.6 */
/*  Performing pointer arithmetic.
    MISRA-C:2004 Rule 17.4; REFERENCE - ISO:C90-6.3.6 Additive Operators - Constraints */
/*  #include statements in a file should only be preceded by other preprocessor directives or comments.
    MISRA-C:2004 Rule 19.1 */
/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define EEP_C_VENDOR_ID            0
#define EEP_C_MODULE_ID            90

#define EEP_C_AR_MAJOR_VERSION     2
#define EEP_C_AR_MINOR_VERSION     2
#define EEP_C_AR_PATCH_VERSION     2

#define EEP_C_SW_MAJOR_VERSION     1
#define EEP_C_SW_MINOR_VERSION     0
#define EEP_C_SW_PATCH_VERSION     0

#define EEP_C_VENDOR_API_INFIX     0

/*=======[I N C L U D E S]====================================================*/
#include "Eep.h"
#include "Det.h"
#include "Spi.h"


#if((EEP_C_AR_MAJOR_VERSION != EEP_AR_MAJOR_VERSION)    \
    ||(EEP_C_AR_MINOR_VERSION != EEP_AR_MINOR_VERSION)  \
    ||(EEP_C_AR_PATCH_VERSION != EEP_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Eep.c and Eep.h are different"
#endif

#if((EEP_C_AR_MAJOR_VERSION != EEP_AR_MAJOR_VERSION)    \
    ||(EEP_C_AR_MINOR_VERSION != EEP_AR_MINOR_VERSION))
#error "AutoSar Version Numbers of Eep.c and Eep.h are different"
#endif

/*=======[E X T E R N A L   D A T A]==========================================*/
VAR(Eep_GlobalType,EEP_VAR_NOINIT) Eep_Global;

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
STATIC FUNC(void,EEP_CODE) Eep_JobHandle (Eep_LengthType Length);
STATIC FUNC(Eep_LengthType,EEP_CODE) Eep_MinLength(Eep_LengthType LengthA,Eep_LengthType LengthB);
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_CompareData(Eep_AddressType EepromAddress,
                                                     P2CONST(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr,
                                                     Eep_LengthType Length);
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_ReadData(Eep_AddressType EepromAddress,
                                                  P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr,
                                                  Eep_LengthType Length );
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_LoadWrite(Eep_AddressType addr,
                                                   P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) ptr,
                                                   Eep_LengthType size);
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_WriteData(Eep_AddressType EepromAddress,
                                                   P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr,
                                                   Eep_LengthType Length );
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_EraseMemory(Eep_AddressType EepromAddress,Eep_LengthType Length);
STATIC FUNC(uint8,EEP_CODE) Eep_ReadStatusRegister(void);

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(void,EEP_CODE) Eep_Init( P2CONST(Eep_ConfigType,AUTOMATIC,EEP_APPL_DATA) ConfigPtr ) /** @req EEP143 EEP004 */
{
    #if (EEP_DEV_ERROR_DETECT == STD_ON)   /** @req EEP005 */ 
	if(NULL == ConfigPtr)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_INIT_ID,EEP_E_PARAM_CONFIG);
        return;
    }
    #endif

	Eep_Global.config = ConfigPtr;   /** @req EEP044 */ 
	Eep_Global.status = MEMIF_UNINIT;
	Eep_Global.jobResultType = MEMIF_JOB_PENDING;

	Eep_Global.status = MEMIF_IDLE;	   /** @req EEP006 */
    (void)Eep_SetMode(Eep_Global.config->EepDefaultMode);
	Eep_Global.jobType = EEP_JOB_NONE;						
	Eep_Global.jobResultType = MEMIF_JOB_OK;
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(void,EEP_CODE) Eep_SetMode( MemIf_ModeType Mode )   /** @req EEP144 */
{
    #if (EEP_DEV_ERROR_DETECT == STD_ON)    /** @req EEP033 */
	if( MEMIF_UNINIT == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_SETMODE_ID,EEP_E_UNINIT);
        return;
    }
    if(MEMIF_BUSY == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_SETMODE_ID,EEP_E_BUSY);
        return;
    }
    #endif

	Eep_Global.mode = Mode;	 /** @req EEP042 */
	if (MEMIF_MODE_FAST == Mode)
	{
		Eep_Global.Block_Read_Size = Eep_Global.config->EepFastReadBlockSize;
		Eep_Global.Block_Write_Size = Eep_Global.config->EepFastWriteBlockSize;
	}
	else
	{
		Eep_Global.Block_Read_Size = Eep_Global.config->EepNormalReadBlockSize;
		Eep_Global.Block_Write_Size = Eep_Global.config->EepNormalWriteBlockSize;
	}
	
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType,EEP_CODE) Eep_Read( Eep_AddressType EepromAddress, 
                                        P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr, 
                                        Eep_LengthType Length )/** @req EEP145 */
{
    #if (EEP_DEV_ERROR_DETECT == STD_ON)      /** @req EEP033 */
    if( MEMIF_UNINIT == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_READ_ID,EEP_E_UNINIT);
        return E_NOT_OK;
    }
    if(MEMIF_BUSY == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_READ_ID,EEP_E_BUSY);
        return E_NOT_OK;
    }
	/** @req EEP016 */
    if(NULL == DataBufferPtr)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_READ_ID,EEP_E_PARAM_DATA);
        return E_NOT_OK;
    }
    /** @req EEP017 */
    if((EepromAddress) > (Eep_Global.config->EepSize))
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_READ_ID,EEP_E_PARAM_ADDRESS);
        return E_NOT_OK;
    }
	/** @req EEP018 */
    if(((Eep_Global.config->EepSize - EepromAddress) < Length) || (0u == Length))
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_READ_ID,EEP_E_PARAM_LENGTH);
        return E_NOT_OK;
    }
    #endif
	
	Eep_Global.sourceAddr = (Eep_AddressType)(EEP_BASE_ADDRESS + EepromAddress);      /** @req EEP009 */
	Eep_Global.targetAddrPtr = DataBufferPtr;
	Eep_Global.Length = Length;	
		
	Eep_Global.status = MEMIF_BUSY;
	Eep_Global.jobResultType = MEMIF_JOB_PENDING;
	Eep_Global.jobType = EEP_JOB_READ;

	return E_OK;	
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType,EEP_CODE) Eep_Write( Eep_AddressType EepromAddress, 
                                         P2CONST(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr, 
                                         Eep_LengthType Length )  /** @req EEP146 EEP014 */
{
    #if (EEP_DEV_ERROR_DETECT == STD_ON)      /** @req EEP033 */
    if( MEMIF_UNINIT == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_WRITE_ID,EEP_E_UNINIT);
        return E_NOT_OK;
    }
    if(MEMIF_BUSY == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_WRITE_ID,EEP_E_BUSY);
        return E_NOT_OK;
    }
	/** @req EEP016 */
    if(NULL == DataBufferPtr)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_WRITE_ID,EEP_E_PARAM_DATA);
        return E_NOT_OK;
    }
	/** @req EEP017 */	
    if((EepromAddress) > (Eep_Global.config->EepSize))
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_WRITE_ID,EEP_E_PARAM_ADDRESS);
        return E_NOT_OK;
    }
    /** @req EEP018 */
    if(((Eep_Global.config->EepSize - EepromAddress) < Length) || (0u == Length))
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_WRITE_ID,EEP_E_PARAM_LENGTH);
        return E_NOT_OK;
    }
    #endif

	Eep_Global.sourceAddr = (Eep_AddressType)(EEP_BASE_ADDRESS + EepromAddress);
	Eep_Global.targetAddrPtr = (uint8* )DataBufferPtr;
	Eep_Global.Length = Length;	
	Eep_Global.jobResultType = MEMIF_JOB_PENDING;     /** @req EEP014 */ 
	Eep_Global.status = MEMIF_BUSY;
	Eep_Global.jobType = EEP_JOB_WRITE;
	
	return E_OK;
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType,EEP_CODE) Eep_Erase( Eep_AddressType EepromAddress, Eep_LengthType Length )   /** @req EEP147 */
{
    #if (EEP_DEV_ERROR_DETECT == STD_ON)      /** @req EEP033 */
    if( MEMIF_UNINIT == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_ERASE_ID,EEP_E_UNINIT);
        return E_NOT_OK;
    }
    if(MEMIF_BUSY == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_ERASE_ID,EEP_E_BUSY);
        return E_NOT_OK;
    }
    /** @req EEP017 */
    if((EepromAddress) > (Eep_Global.config->EepSize))
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_ERASE_ID,EEP_E_PARAM_ADDRESS);
        return E_NOT_OK;
    }
    /** @req EEP018 */
    if(((Eep_Global.config->EepSize - EepromAddress) < Length) || (0u == Length))
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_ERASE_ID,EEP_E_PARAM_LENGTH);
        return E_NOT_OK;
    }
    #endif

	Eep_Global.sourceAddr = (Eep_AddressType)(EEP_BASE_ADDRESS + EepromAddress);
	Eep_Global.Length = Length;	
	Eep_Global.status = MEMIF_BUSY;                  /** @req EEP019 */
	Eep_Global.jobResultType= MEMIF_JOB_PENDING;
	Eep_Global.jobType	= EEP_JOB_ERASE;
	
	return E_OK;	
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType,EEP_CODE) Eep_Compare( Eep_AddressType EepromAddress,
                                           P2CONST(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr,
                                           Eep_LengthType Length )/** @req EEP148 EEP026 */
{
    #if (EEP_DEV_ERROR_DETECT == STD_ON)     /** @req EEP033 */
    if( MEMIF_UNINIT == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_COMPARE_ID,EEP_E_UNINIT);
        return E_NOT_OK;
    }
    if(MEMIF_BUSY == Eep_Global.status)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_COMPARE_ID,EEP_E_BUSY);
        return E_NOT_OK;
    }
	/** @req EEP016 */
    if(NULL == DataBufferPtr)
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_COMPARE_ID,EEP_E_PARAM_DATA);
        return E_NOT_OK;
    }
	/** @req EEP017 */	
    if((EepromAddress) > (Eep_Global.config->EepSize))
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_COMPARE_ID,EEP_E_PARAM_ADDRESS);
        return E_NOT_OK;
    }
    /** @req EEP018 */
    if(((Eep_Global.config->EepSize - EepromAddress) < Length) || (0u == Length))
    {
        Det_ReportError(MODULE_ID_EEP,0,EEP_COMPARE_ID,EEP_E_PARAM_LENGTH);
        return E_NOT_OK;
    }
    #endif	

	Eep_Global.sourceAddr = (Eep_AddressType)(EEP_BASE_ADDRESS + EepromAddress);
	Eep_Global.targetAddrPtr = (uint8*)DataBufferPtr;
	Eep_Global.Length = Length;	
	Eep_Global.status = MEMIF_BUSY;      /** @req EEP025 */
	Eep_Global.jobResultType = MEMIF_JOB_PENDING;
	Eep_Global.jobType = EEP_JOB_COMPARE;

	return E_OK;
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(void,EEP_CODE) Eep_Cancel(void)      /** @req EEP149 */
{
	/** @req EEP027 */
    if (Eep_Global.config->Eep_JobErrorNotification!=NULL)
    {  
        Eep_Global.config->Eep_JobErrorNotification(); 
    }
	if (MEMIF_JOB_PENDING == Eep_Global.jobResultType)     /** @req EEP028 */
	{
		Eep_Global.jobResultType = MEMIF_JOB_CANCELLED;
	}
	
	Eep_Global.status = MEMIF_IDLE;     /** @req EEP027 */  
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(MemIf_StatusType,EEP_CODE) Eep_GetStatus(void)   /** @req EEP150 */
{
	return Eep_Global.status;
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(MemIf_JobResultType,EEP_CODE) Eep_GetJobResult(void)    /** @req EEP151 */
{
	return Eep_Global.jobResultType;
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

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
#define EEP_START_SEC_CODE
#include "MemMap.h"
FUNC(void,EEP_CODE) Eep_MainFunction(void)               /** @req EEP153 */
{
	uint8 result = 0;
	Eep_LengthType lengt = 0;
    Eep_LengthType size  = 0;

	if (MEMIF_JOB_PENDING == Eep_Global.jobResultType) /** @req EEP032 */
	{
		switch (Eep_Global.jobType)         /** @req EEP031 */
		{
			case EEP_JOB_COMPARE:
				size = Eep_Global.Block_Read_Size;
				lengt = Eep_MinLength(Eep_Global.Length, size);
				result = Eep_CompareData(Eep_Global.sourceAddr,Eep_Global.targetAddrPtr,lengt); 
				break;		
			case EEP_JOB_ERASE:
				size = Eep_Global.Block_Write_Size;
				lengt = Eep_MinLength(Eep_Global.Length, size);
				result = Eep_EraseMemory(Eep_Global.sourceAddr,lengt);   
				break;
			case EEP_JOB_READ: 
				size = Eep_Global.Block_Read_Size;
				lengt =  Eep_MinLength(Eep_Global.Length, size);    
				result = Eep_ReadData(Eep_Global.sourceAddr,Eep_Global.targetAddrPtr,lengt);
				break;
				
			case EEP_JOB_WRITE:
				size = Eep_Global.Block_Write_Size;
				lengt = Eep_MinLength(Eep_Global.Length, size);
				result = Eep_WriteData(Eep_Global.sourceAddr,Eep_Global.targetAddrPtr,lengt);
				break;
			default:
				break;
    	}

		/* valid eep job */
		if ((Eep_Global.jobType > EEP_JOB_NONE) && (Eep_Global.jobType <= EEP_JOB_WRITE))
		{
			if (result != E_OK)
			{
			    Eep_Global.jobResultType = MEMIF_JOB_FAILED;
			    Eep_Global.jobType = EEP_JOB_NONE;
			    Eep_Global.status = MEMIF_IDLE;
                if (Eep_Global.config->Eep_JobErrorNotification!=NULL) 
                { 
                    Eep_Global.config->Eep_JobErrorNotification(); 
                }
			}
			else
			{
			    Eep_JobHandle(lengt);
			}
		}
	}
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"


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
#if (EEP_VERSION_INFO_API == STD_ON) 
#define EEP_START_SEC_CODE
#include "MemMap.h" 
FUNC(void,EEP_CODE) Eep_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC,EEP_APPL_DATA) VersioninfoPtr)
{	
    VersioninfoPtr->vendorID = 0;
    VersioninfoPtr->moduleID = MODULE_ID_EEP;
    VersioninfoPtr->instanceID = 1;
    VersioninfoPtr->ar_major_version = EEP_AR_MAJOR_VERSION;
    VersioninfoPtr->ar_minor_version = EEP_AR_MINOR_VERSION;
    VersioninfoPtr->ar_patch_version = EEP_AR_PATCH_VERSION;
    VersioninfoPtr->sw_major_version = EEP_SW_MAJOR_VERSION;
    VersioninfoPtr->sw_minor_version = EEP_SW_MINOR_VERSION;
    VersioninfoPtr->sw_patch_version = EEP_SW_PATCH_VERSION;
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h" 
#endif

#define EEP_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Read external EEPROM device status.>
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
STATIC FUNC(uint8,EEP_COMPAREDATA) Eep_ReadStatusRegister(void)
{
	Spi_DataType recv_data[1] = {0};
	Spi_DataType readCommand[1] = {EEP_READ_STATUS_REGISTER};
	Spi_DataType randomData[2] = {25,26};

	(void)Spi_SetupEB(SPI_CH_EEP_CMD,  readCommand, recv_data, 1);
	(void)Spi_SetupEB(SPI_CH_EEP_DATA, randomData,  recv_data, 1);
	(void)Spi_SyncTransmit(SPI_SEQ_EEP_CMD2);
	
	return recv_data[0];
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

#define EEP_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Handle the job processing.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <NON Reentrant>
 * Param-Name[in]      <None>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <Length>
 * Return              <None>  
 * PreCondition        <None>  
 */
/******************************************************************************/
STATIC FUNC(void,EEP_CODE) Eep_JobHandle (Eep_LengthType Length)
{
	if (Eep_Global.Length <= Length)
	{
		Eep_Global.jobResultType = MEMIF_JOB_OK;
		Eep_Global.status = MEMIF_IDLE;
		Eep_Global.jobType = EEP_JOB_NONE;
        if (Eep_Global.config->Eep_JobEndNotification!=NULL)
        {  
            Eep_Global.config->Eep_JobEndNotification(); 
        }
	}
	else
	{
		Eep_Global.sourceAddr = (Eep_AddressType)(Eep_Global.sourceAddr + Length);
		Eep_Global.Length = (Eep_LengthType)(Eep_Global.Length - Length);
		switch (Eep_Global.jobType)
		{
			case EEP_JOB_COMPARE: /* fall to case EEP_JOB_WRITE */
			case EEP_JOB_READ:  /* fall to case EEP_JOB_WRITE */
			case EEP_JOB_WRITE:
				Eep_Global.targetAddrPtr = (uint8*)(Eep_Global.targetAddrPtr + Length);
				break;
			default:
				break;
		}
	}
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

#define EEP_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <get the min length.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <NON Reentrant>
 * Param-Name[in]      <LengthA,LengthB>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Eep_LengthType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
STATIC FUNC(Eep_LengthType,EEP_CODE) Eep_MinLength(Eep_LengthType LengthA, Eep_LengthType LengthB)
{
	if(LengthA <= LengthB)
	{
		return LengthA;
	}
	else
	{
		return LengthB;
	}
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

#define EEP_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Eep Compare data.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <NON Reentrant>
 * Param-Name[in]      <EepromAddress,DataBufferPtr,LengthB>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_CompareData(Eep_AddressType EepromAddress, 
                                              P2CONST(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr,
                                              Eep_LengthType Length)
{
	Std_ReturnType ercd = E_NOT_OK;
	Eep_AddressType addr = EepromAddress;
	P2CONST(uint8,AUTOMATIC,EEP_APPL_DATA) ptr=DataBufferPtr;
	Eep_LengthType len =Length;
	Eep_LengthType size = 0u;
	Eep_LengthType i;
	uint8 cmpbuf[EEP_PAGE_SIZE];  /* malloc one page in current stack. */
	
	while(len > 0)
	{
		if(len >EEP_PAGE_SIZE)
		{
			size = EEP_PAGE_SIZE;
			len -= EEP_PAGE_SIZE;
		}
		else
		{
			size = len;
			len = 0;
		}

		ercd = Eep_ReadData(addr,cmpbuf,size);
		if(ercd != E_OK)
		{
			break;
		}

		for (i = 0; i < size; i++)
		{
			if (cmpbuf[i] != *ptr)
			{
				ercd = E_NOT_OK;
				break;
			}
            ptr++;
		}

	    if(ercd != E_OK)
		{
			break;
		}
	}
			
	return ercd;		
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

#define EEP_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Eep read data.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <NON Reentrant>
 * Param-Name[in]      <EepromAddress,DataBufferPtr,LengthB>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_ReadData(Eep_AddressType EepromAddress, 
                                           P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr, 
                                           Eep_LengthType Length )
{
	Std_ReturnType ercd = E_OK;
	Eep_AddressType addr = EepromAddress;
	P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) ptr = DataBufferPtr;
	Eep_LengthType len = Length;
	Eep_LengthType size;
    uint32 tmo;                 /* Timeout Duration Time for Polling Eep Idle Status */
	
	Spi_DataType readCommand[1] = {EEP_READ};
	Spi_DataType readAddress[2] = {0,0};
	Spi_DataType randomData[8] = {0};
	
	while(len > 0)
	{
        /* Waiting for EEP IDLE */
		tmo = EEP_WAIT_TIME;
		while(0x01 == (0x01&Eep_ReadStatusRegister()))
        {
            tmo--;
            if(0 == tmo)
            {
                ercd = E_NOT_OK;
                break;
            }
        } 

        if(E_NOT_OK == ercd) 
        {
            /* time out,something wrong with Eeprom */
            /* Should report error to DEM,but Det is the next best */
            #if(EEP_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError(MODULE_ID_EEP,0,EEP_READ_ID,EEP_E_TIMEOUT);
            #endif
            break;
        } 

		if(len >SPI_EB_MAX_LENGTH)
		{
			size = SPI_EB_MAX_LENGTH;
			len -= SPI_EB_MAX_LENGTH;
		}
		else
		{
			size = len;
			len = 0;
		}
		
		readAddress[1]= (Spi_DataType)(addr & 0xff);
		readAddress[0]= (Spi_DataType)((addr>>8) & 0xff);

		ercd  = Spi_SetupEB(SPI_CH_EEP_CMD, readCommand, ptr, 1);
		if(ercd != E_OK)
		{
			break;
		}

		ercd  = Spi_SetupEB(SPI_CH_EEP_ADDR, readAddress, ptr, 2);
		if(ercd != E_OK)
		{
			break;
		}

		ercd  = Spi_SetupEB(SPI_CH_EEP_DATA, randomData, ptr, size);
		if(ercd != E_OK)
		{
			break;
		}

		ercd  = Spi_SyncTransmit(SPI_SEQ_EEP_READ);
		if(ercd != E_OK)
		{
			break;
		}
		
		ptr += size;
		addr += size;
				
	}			
	return ercd;	
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

#define EEP_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Load Eep write data command and sequence.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <NON Reentrant>
 * Param-Name[in]      <addr,ptr,size>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_LoadWrite(Eep_AddressType addr,
                                                   P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) ptr,
                                                   Eep_LengthType size)
{
    Std_ReturnType ercd  = E_OK;
	Spi_DataType writeEnableCommand[1] = {EEP_WRITE_ENABLE};
	Spi_DataType writeCommand[1] = {EEP_WRITE};
	Spi_DataType recvdata[2] = {0};
    Spi_DataType writeAddress[2] = {0,0};

    writeAddress[0]= (Spi_DataType)((addr>>8)&0xff);
    writeAddress[1]= (Spi_DataType)(addr&0xff);	

    ercd = Spi_SetupEB(SPI_CH_EEP_WREN,writeEnableCommand, recvdata, 1); 
    if(ercd != E_OK)
    {
        return ercd; 
    }
    ercd = Spi_SetupEB(SPI_CH_EEP_CMD, writeCommand, recvdata, 1);
    if(ercd != E_OK)
    {
        return ercd; 
    } 
    ercd = Spi_SetupEB(SPI_CH_EEP_ADDR, writeAddress, recvdata, 2);
    if(ercd != E_OK)
    {
        return ercd;
    }
    ercd = Spi_SetupEB(SPI_CH_EEP_DATA, ptr, recvdata,size);
    if(ercd != E_OK)
    {
        return ercd;
    }
    ercd = Spi_SyncTransmit(SPI_SEQ_EEP_WRITE);
    if(ercd != E_OK)
    {
        return ercd;
    }
    return ercd;
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

#define EEP_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Eep write data.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <NON Reentrant>
 * Param-Name[in]      <EepromAddress,DataBufferPtr,LengthB>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_WriteData(Eep_AddressType EepromAddress, 
                                            P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) DataBufferPtr, 
                                            Eep_LengthType Length )
{
	Std_ReturnType ercd  = E_OK;
	Eep_AddressType addr = EepromAddress;
	P2VAR(uint8,AUTOMATIC,EEP_APPL_DATA) ptr=DataBufferPtr;
	Eep_LengthType len =Length;
	Eep_LengthType size;

	uint32 tmo;
	
	/* as write range is one page, so adjust the address */
	while(len > 0)
	{
        /* Waiting for EEP IDLE */
		tmo = EEP_WAIT_TIME;
		while(0x01 == (0x01&Eep_ReadStatusRegister()))
        {
            tmo--;
            if(0 == tmo)
            {
                ercd = E_NOT_OK;
                break;
            }
        } 
        if(E_NOT_OK == ercd)    
        {
            /* time out,something wrong with Eeprom */
            /* Should report error to DEM,but Det is the next best */
            #if(EEP_DEV_ERROR_DETECT == STD_ON)
            Det_ReportError(MODULE_ID_EEP,0,EEP_WRITE_ID,EEP_E_TIMEOUT);
            #endif
            break;
        } 

		size = (Eep_LengthType)(addr&EEP_PAGE_MOD_MASK);
		size = (Eep_LengthType)(EEP_PAGE_SIZE - size); /*EEP_PAGE_SIZE - EepromAddress%EEP_PAGE_SIZE*/
		if(len < size)
		{
			size = len;
		}
		
		ercd = Eep_LoadWrite(addr,ptr,size);
        if(ercd != E_OK)
        {
            break;
        }									
		addr += size;
		ptr  += size;
		len  -= size;				
	}
	return ercd;
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"

#define EEP_START_SEC_CODE
#include "MemMap.h"
/******************************************************************************/
/*
 * Brief               <Eep Erase Memory.>
 * ServiceId           <None>
 * Sync/Async          <Synchronous>
 * Reentrancy          <NON Reentrant>
 * Param-Name[in]      <EepromAddress,Length>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Std_ReturnType>  
 * PreCondition        <None>  
 */
/******************************************************************************/
STATIC FUNC(Std_ReturnType,EEP_CODE) Eep_EraseMemory(Eep_AddressType EepromAddress,Eep_LengthType Length)
{
	Std_ReturnType  ercd = E_NOT_OK;
    Eep_AddressType addr = EepromAddress;
    Eep_LengthType  len = Length;
	Eep_LengthType  size;

	STATIC CONST(uint32,EEP_APPL_CONST) ersbuf[8]=
	{
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF,
		0xFFFFFFFF    /* 4*8 = 32 bytes one page */ 
	};
	/* as write range is one page, so adjust the address */
	while(len > 0)
	{
		size = (Eep_LengthType)(addr&EEP_PAGE_MOD_MASK);
		size = (Eep_LengthType)(EEP_PAGE_SIZE - size); /*32 - EepromAddress%32*/
		if(len < size)
		{
			size = len;
		}
		ercd = Eep_WriteData(addr, (uint8*)ersbuf, size);
		if(ercd != E_OK)
		{
			break;
		}
		addr += size;
		len  -= size;	
	}	
	return ercd;
}
#define EEP_STOP_SEC_CODE
#include "MemMap.h"
/*=======[E N D   O F   F I L E]==============================================*/

