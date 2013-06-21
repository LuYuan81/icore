/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Compiler_Cfg.h>
 *  @brief      <Briefly describe file(one line)>
 *  
 *  <Compiler: CodeWarriar    MCU:MPC5634M>
 *  
 *  @author     <chen xue hua>
 *  @date       <2013-02-27>
 */
/*============================================================================*/
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20130227  chenxuehua  Initial version
 */
/*============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define COMPILER_CFG_VENDOR_ID         0
#define COMPILER_CFG_MODULE_ID         0
#define COMPILER_CFG_AR_MAJOR_VERSION  2
#define COMPILER_CFG_AR_MINOR_VERSION  0
#define COMPILER_CFG_AR_PATCH_VERSION  2
#define COMPILER_CFG_SW_MAJOR_VERSION  1
#define COMPILER_CFG_SW_MINOR_VERSION  0
#define COMPILER_CFG_SW_PATCH_VERSION  0
#define COMPILER_CFG_VENDOR_API_INFIX  0

/* @req COMPILER055 @req COMPILER054 */
/*=======[M A C R O S]========================================================*/

/* @req COMPILER044 @req COMPILER040 */
/*=======[COM_MemoryAndPointerClasses]========================================*/
/* Configurable memory class for code. */
#define COM_CODE

/* Configurable memory class for ISR code. */
#define COM_CODE_FAST

/* 
 * Configurable memory class for all global or static variables that are never 
 * initialized. 
 */
#define COM_VAR_NOINIT

/* 
 * Configurable memory class for all global or static variables that are 
 * initialized only after power on reset. 
 */
#define COM_VAR_POWER_ON_INIT

/*
 * Configurable memory class for all global or static variables that are 
 * initialized after every reset. 
 */
#define COM_VAR

/* 
 * Configurable memory class for all global or static variables that will 
 * be accessed frequently. 
 */
#define COM_VAR_NOINIT_FAST

/* 
 * Configurable memory class for all global or static variables that have at 
 * be accessed frequently. 
 */
#define COM_VAR_POWER_ON_INIT_FAST

/* 
 * Configurable memory class for all global or static variables that have at 
 * be accessed frequently. 
 */
#define COM_VAR_FAST

/* Configurable memory class for global or static constants. */
#define COM_CONST

/*
 * Configurable memory class for global or static constants that will be 
 * accessed frequently.
 */
#define COM_CONST_FAST

/* Configurable memory class for global or static constants in post build. */
#define COM_CONST_PBCFG

/*
 * Configurable memory class for pointers to applicaiton data(expected to be 
 * in RAM or ROM)passed via API.
 */
#define COM_APPL_DATA

/* 
 * Configurable memory class for pointers to applicaiton constants(expected to
 * be certainly in ROM,for instance point of Init-function)passed via API.
 */
#define COM_APPL_CONST

/* 
 * Configurable memory class for pointers to applicaiton functions(e.g. call 
 * back function pointers).
 */
#define COM_APPL_CODE


#endif /* end of COMPILER_CFG_H */

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0         20130227  chenxuehua  Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/
