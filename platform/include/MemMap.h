/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <MemMap.h>
 *  @brief      <Briefly describe file(one line)>
 *  
 *  <Compiler: CodeWarriar    MCU:MPC5634M>
 *  
 *  @author     <chen xue hua>
 *  @date       <2013-02-27>
 */
/*============================================================================*/
/* @req MEMMAP020 @req MEMMAP001 @req MEMMAP002 @req MEMMAP005 @req MEMMAP015 */
/* @req MEMMAP016 */
#ifndef MEMMAP_H
#define MEMMAP_H

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20130227  chenxuehua  Initial version
 */
/*============================================================================*/

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define MEMMAP_VENDOR_ID  0
#define MEMMAP_MODULE_ID  0
#define MEMMAP_AR_MAJOR_VERSION  1
#define MEMMAP_AR_MINOR_VERSION  1
#define MEMMAP_AR_PATCH_VERSION  2
#define MEMMAP_SW_MAJOR_VERSION  1
#define MEMMAP_SW_MINOR_VERSION  0
#define MEMMAP_SW_PATCH_VERSION  0
#define MEMMAP_VENDOR_API_INFIX  0

/* 
 * <SIZE> -- BOOLEAN/8BIT/16BIT/32BIT/UNSPECIFIED 
 */

/* 
 * <MSN>_START_SEC_CODE
 * <MSN>_STOP_SEC_CODE
 * To be used for mapping code to applicaiton block,boot block,external flash etc. 
 */

/* 
 * <MSN>_START_SEC_CODE_FAST
 * <MSN>_STOP_SEC_CODE_FAST
 * To be used for mapping code to local block,boot block of ISR API. 
 */

/* 
 * <MSN>_START_SEC_VAR_NOINIT_<SIZE>
 * <MSN>_STOP_SEC_VAR_NOINIT_<SIZE>
 * To be used for all global or static variables that are never initialized. 
 */

/* 
 * <MSN>_START_SEC_VAR_POWER_ON_INIT_<SIZE>
 * <MSN>_STOP_SEC_VAR_POWER_ON_INIT_<SIZE>
 * To be used for all global or static variables that are initialized only after power on reset. 
 */

/*
 * <MSN>_START_SEC_VAR_<SIZE>
 * <MSN>_STOP_SEC_VAR_<SIZE>
 * To be used for all global or static variables that are initialized after every reset(the normal case).
 */

/* 
 * <MSN>_START_SEC_VAR_FAST_NOINIT_<SIZE>
 * <MSN>_STOP_SEC_VAR_FAST_NOINIT_<SIZE>
 * To be used for all global or static variables that have at least one of the following properties:
 *      *accessed bitwise
 *      *frequently used
 *      *high number of accesses in source code
 *  Some platforms allow the use of bit instructions for variables located in this specific RAM area as
 *  well as shorter addressing instructions.This saves code and runtime. 
 */

/* 
 * <MSN>_START_SEC_VAR_FAST_POWER_ON_INIT_<SIZE>
 * <MSN>_STOP_SEC_VAR_FAST_POWER_ON_INIT_<SIZE>
 * To be used for all global or static variables that have at least one of the following properties:
 *      *accessed bitwise
 *      *frequently used
 *      *high number of accesses in source code
 *  Some platforms allow the use of bit instructions for variables located in this specific RAM area as
 *  well as shorter addressing instructions.This saves code and runtime. 
 */

/* 
 * <MSN>_START_SEC_VAR_FAST_<SIZE>
 * <MSN>_STOP_SEC_VAR_FAST_<SIZE>
 * To be used for all global or static variables that have at least one of the following properties:
 *      *accessed bitwise
 *      *frequently used
 *      *high number of accesses in source code
 *  Some platforms allow the use of bit instructions for variables located in this specific RAM area as
 *  well as shorter addressing instructions.This saves code and runtime. 
 */

/*
 * <MSN>_START_SEC_CONST_<SIZE>
 * <MSN>_STOP_SEC_CONST_<SIZE>
 * To be used for all global or static constants.
 */

/*
 * <MSN>_START_SEC_CONST_FAST_<SIZE>
 * <MSN>_STOP_SEC_CONST_FAST_<SIZE>
 * To be used for all global or static constants in fast segment block.
 */

/*
 * <MSN>_START_CONST_PBCFG
 * <MSN>_STOP_CONST_PBCFG
 * Constants with attributes that show that they reside in one segment for module configuration.
 */

/*
 * <MSN>_START_CONST_PBCFG_ROOT
 * <MSN>_STOP_CONST_PBCFG_ROOT
 * Constants with attributes that show that they reside in one segment for module configuration for root structure.
 */

/* @req MEMMAP010 @req MEMMAP004 @req MEMMAP021 @req MEMMAP003 @req MEMMAP018 */
/*=======[M A C R O S]========================================================*/
#if defined (START_WITH_IF)

/*=======[C A N]==============================================================*/

#elif defined (CAN_START_SEC_CODE)
   #undef      CAN_START_SEC_CODE
   #define START_SEC_CODE
#elif defined (CAN_STOP_SEC_CODE)
   #undef      CAN_STOP_SEC_CODE
   #define STOP_SEC_CODE

#elif defined (CAN_START_SEC_CODE_FAST)
   #undef      CAN_START_SEC_CODE_FAST
   #define START_SEC_CODE_FAST
#elif defined (CAN_STOP_SEC_CODE_FAST)
   #undef      CAN_STOP_SEC_CODE_FAST
   #define STOP_SEC_CODE_FAST

#elif defined (CAN_START_SEC_VAR_NOINIT_BOOLEAN)
   #undef      CAN_START_SEC_VAR_NOINIT_BOOLEAN
   #define START_SEC_VAR_NOINIT_BOOLEAN
#elif defined (CAN_STOP_SEC_VAR_NOINIT_BOOLEAN)
   #undef      CAN_STOP_SEC_VAR_NOINIT_BOOLEAN
   #define STOP_SEC_VAR_NOINIT_BOOLEAN

#elif defined (CAN_START_SEC_VAR_NOINIT_8BIT)
   #undef      CAN_START_SEC_VAR_NOINIT_8BIT
   #define START_SEC_VAR_NOINIT_8BIT
#elif defined (CAN_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      CAN_STOP_SEC_VAR_NOINIT_8BIT
   #define STOP_SEC_VAR_NOINIT_8BIT

#elif defined (CAN_START_SEC_VAR_NOINIT_16BIT)
   #undef      CAN_START_SEC_VAR_NOINIT_16BIT
   #define START_SEC_VAR_NOINIT_16BIT
#elif defined (CAN_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      CAN_STOP_SEC_VAR_NOINIT_16BIT
   #define STOP_SEC_VAR_NOINIT_16BIT

#elif defined (CAN_START_SEC_VAR_NOINIT_32BIT)
   #undef      CAN_START_SEC_VAR_NOINIT_32BIT
   #define START_SEC_VAR_NOINIT_32BIT
#elif defined (CAN_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      CAN_STOP_SEC_VAR_NOINIT_32BIT
   #define STOP_SEC_VAR_NOINIT_32BIT

#elif defined (CAN_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      CAN_START_SEC_VAR_NOINIT_UNSPECIFIED
   #define START_SEC_VAR_NOINIT_UNSPECIFIED
#elif defined (CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      CAN_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #define STOP_SEC_VAR_NOINIT_UNSPECIFIED

#elif defined (CAN_START_SEC_VAR_POWER_ON_INIT_BOOLEAN)
   #undef      CAN_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
   #define START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#elif defined (CAN_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN)
   #undef      CAN_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
   #define STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN

#elif defined (CAN_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      CAN_START_SEC_VAR_POWER_ON_INIT_8BIT
   #define START_SEC_VAR_POWER_ON_INIT_8BIT
#elif defined (CAN_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      CAN_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #define STOP_SEC_VAR_POWER_ON_INIT_8BIT

#elif defined (CAN_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      CAN_START_SEC_VAR_POWER_ON_INIT_16BIT
   #define START_SEC_VAR_POWER_ON_INIT_16BIT
#elif defined (CAN_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      CAN_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #define STOP_SEC_VAR_POWER_ON_INIT_16BIT

#elif defined (CAN_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      CAN_START_SEC_VAR_POWER_ON_INIT_32BIT
   #define START_SEC_VAR_POWER_ON_INIT_32BIT
#elif defined (CAN_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      CAN_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #define STOP_SEC_VAR_POWER_ON_INIT_32BIT

#elif defined (CAN_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      CAN_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #define START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#elif defined (CAN_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      CAN_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #define STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED

#elif defined (CAN_START_SEC_VAR_BOOLEAN)
   #undef      CAN_START_SEC_VAR_BOOLEAN
   #define START_SEC_VAR_BOOLEAN
#elif defined (CAN_STOP_SEC_VAR_BOOLEAN)
   #undef      CAN_STOP_SEC_VAR_BOOLEAN
   #define STOP_SEC_VAR_BOOLEAN

#elif defined (CAN_START_SEC_VAR_8BIT)
   #undef      CAN_START_SEC_VAR_8BIT
   #define START_SEC_VAR_8BIT
#elif defined (CAN_STOP_SEC_VAR_8BIT)
   #undef      CAN_STOP_SEC_VAR_8BIT
   #define STOP_SEC_VAR_8BIT

#elif defined (CAN_START_SEC_VAR_16BIT)
   #undef      CAN_START_SEC_VAR_16BIT
   #define START_SEC_VAR_16BIT
#elif defined (CAN_STOP_SEC_VAR_16BIT)
   #undef      CAN_STOP_SEC_VAR_16BIT
   #define STOP_SEC_VAR_16BIT

#elif defined (CAN_START_SEC_VAR_32BIT)
   #undef      CAN_START_SEC_VAR_32BIT
   #define START_SEC_VAR_32BIT
#elif defined (CAN_STOP_SEC_VAR_32BIT)
   #undef      CAN_STOP_SEC_VAR_32BIT
   #define STOP_SEC_VAR_32BIT

#elif defined (CAN_START_SEC_VAR_UNSPECIFIED)
   #undef      CAN_START_SEC_VAR_UNSPECIFIED
   #define START_SEC_VAR_UNSPECIFIED
#elif defined (CAN_STOP_SEC_VAR_UNSPECIFIED)
   #undef      CAN_STOP_SEC_VAR_UNSPECIFIED
   #define STOP_SEC_VAR_UNSPECIFIED


#elif defined (CAN_START_SEC_VAR_FAST_NOINIT_BOOLEAN)
   #undef      CAN_START_SEC_VAR_FAST_NOINIT_BOOLEAN
   #define START_SEC_VAR_FAST_NOINIT_BOOLEAN
#elif defined (CAN_STOP_SEC_VAR_FAST_NOINIT_BOOLEAN)
   #undef      CAN_STOP_SEC_VAR_FAST_NOINIT_BOOLEAN
   #define STOP_SEC_VAR_FAST_NOINIT_BOOLEAN

#elif defined (CAN_START_SEC_VAR_FAST_NOINIT_8BIT)
   #undef      CAN_START_SEC_VAR_FAST_NOINIT_8BIT
   #define START_SEC_VAR_FAST_NOINIT_8BIT
#elif defined (CAN_STOP_SEC_VAR_FAST_NOINIT_8BIT)
   #undef      CAN_STOP_SEC_VAR_FAST_NOINIT_8BIT
   #define STOP_SEC_VAR_FAST_NOINIT_8BIT

#elif defined (CAN_START_SEC_VAR_FAST_NOINIT_16BIT)
   #undef      CAN_START_SEC_VAR_FAST_NOINIT_16BIT
   #define START_SEC_VAR_FAST_NOINIT_16BIT
#elif defined (CAN_STOP_SEC_VAR_FAST_NOINIT_16BIT)
   #undef      CAN_STOP_SEC_VAR_FAST_NOINIT_16BIT
   #define STOP_SEC_VAR_FAST_NOINIT_16BIT

#elif defined (CAN_START_SEC_VAR_FAST_NOINIT_32BIT)
   #undef      CAN_START_SEC_VAR_FAST_NOINIT_32BIT
   #define START_SEC_VAR_FAST_NOINIT_32BIT
#elif defined (CAN_STOP_SEC_VAR_FAST_NOINIT_32BIT)
   #undef      CAN_STOP_SEC_VAR_FAST_NOINIT_32BIT
   #define STOP_SEC_VAR_FAST_NOINIT_32BIT

#elif defined (CAN_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
   #undef      CAN_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
   #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#elif defined (CAN_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
   #undef      CAN_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
   #define STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED

#elif defined (CAN_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN)
   #undef      CAN_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
   #define START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
#elif defined (CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN)
   #undef      CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN

#elif defined (CAN_START_SEC_VAR_FAST_POWER_ON_INIT_8BIT)
   #undef      CAN_START_SEC_VAR_FAST_POWER_ON_INIT_8BIT
   #define START_SEC_VAR_FAST_POWER_ON_INIT_8BIT
#elif defined (CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_8BIT)
   #undef      CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_8BIT
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_8BIT

#elif defined (CAN_START_SEC_VAR_FAST_POWER_ON_INIT_16BIT)
   #undef      CAN_START_SEC_VAR_FAST_POWER_ON_INIT_16BIT
   #define START_SEC_VAR_FAST_POWER_ON_INIT_16BIT
#elif defined (CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_16BIT)
   #undef      CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_16BIT
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_16BIT

#elif defined (CAN_START_SEC_VAR_FAST_POWER_ON_INIT_32BIT)
   #undef      CAN_START_SEC_VAR_FAST_POWER_ON_INIT_32BIT
   #define START_SEC_VAR_FAST_POWER_ON_INIT_32BIT
#elif defined (CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_32BIT)
   #undef      CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_32BIT
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_32BIT

#elif defined (CAN_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED)
   #undef      CAN_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
   #define START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
#elif defined (CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED)
   #undef      CAN_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED

#elif defined (CAN_START_SEC_VAR_FAST_BOOLEAN)
   #undef      CAN_START_SEC_VAR_FAST_BOOLEAN
   #define START_SEC_VAR_FAST_BOOLEAN
#elif defined (CAN_STOP_SEC_VAR_FAST_BOOLEAN)
   #undef      CAN_STOP_SEC_VAR_FAST_BOOLEAN
   #define STOP_SEC_VAR_FAST_BOOLEAN

#elif defined (CAN_START_SEC_VAR_FAST_8BIT)
   #undef      CAN_START_SEC_VAR_FAST_8BIT
   #define START_SEC_VAR_FAST_8BIT
#elif defined (CAN_STOP_SEC_VAR_FAST_8BIT)
   #undef      CAN_STOP_SEC_VAR_FAST_8BIT
   #define STOP_SEC_VAR_FAST_8BIT

#elif defined (CAN_START_SEC_VAR_FAST_16BIT)
   #undef      CAN_START_SEC_VAR_FAST_16BIT
   #define START_SEC_VAR_FAST_16BIT
#elif defined (CAN_STOP_SEC_VAR_FAST_16BIT)
   #undef      CAN_STOP_SEC_VAR_FAST_16BIT
   #define STOP_SEC_VAR_FAST_16BIT

#elif defined (CAN_START_SEC_VAR_FAST_32BIT)
   #undef      CAN_START_SEC_VAR_FAST_32BIT
   #define START_SEC_VAR_FAST_32BIT
#elif defined (CAN_STOP_SEC_VAR_FAST_32BIT)
   #undef      CAN_STOP_SEC_VAR_FAST_32BIT
   #define STOP_SEC_VAR_FAST_32BIT

#elif defined (CAN_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      CAN_START_SEC_VAR_FAST_UNSPECIFIED
   #define START_SEC_VAR_FAST_UNSPECIFIED
#elif defined (CAN_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      CAN_STOP_SEC_VAR_FAST_UNSPECIFIED
   #define STOP_SEC_VAR_FAST_UNSPECIFIED

#elif defined (CAN_START_SEC_CONST_BOOLEAN)
   #undef      CAN_START_SEC_CONST_BOOLEAN
   #define START_SEC_CONST_BOOLEAN
#elif defined (CAN_STOP_SEC_CONST_BOOLEAN)
   #undef      CAN_STOP_SEC_CONST_BOOLEAN
   #define STOP_SEC_CONST_BOOLEAN

#elif defined (CAN_START_SEC_CONST_8BIT)
   #undef      CAN_START_SEC_CONST_8BIT
   #define START_SEC_CONST_8BIT
#elif defined (CAN_STOP_SEC_CONST_8BIT)
   #undef      CAN_STOP_SEC_CONST_8BIT
   #define STOP_SEC_CONST_8BIT

#elif defined (CAN_START_SEC_CONST_16BIT)
   #undef      CAN_START_SEC_CONST_16BIT
   #define START_SEC_CONST_16BIT
#elif defined (CAN_STOP_SEC_CONST_16BIT)
   #undef      CAN_STOP_SEC_CONST_16BIT
   #define STOP_SEC_CONST_16BIT

#elif defined (CAN_START_SEC_CONST_32BIT)
   #undef      CAN_START_SEC_CONST_32BIT
   #define START_SEC_CONST_32BIT
#elif defined (CAN_STOP_SEC_CONST_32BIT)
   #undef      CAN_STOP_SEC_CONST_32BIT
   #define STOP_SEC_CONST_32BIT

#elif defined (CAN_START_SEC_CONST_UNSPECIFIED)
   #undef      CAN_START_SEC_CONST_UNSPECIFIED
   #define START_SEC_CONST_UNSPECIFIED
#elif defined (CAN_STOP_SEC_CONST_UNSPECIFIED)
   #undef      CAN_STOP_SEC_CONST_UNSPECIFIED
   #define STOP_SEC_CONST_UNSPECIFIED

#elif defined (CAN_START_SEC_CONST_FAST_BOOLEAN)
   #undef      CAN_START_SEC_CONST_FAST_BOOLEAN
   #define START_SEC_CONST_FAST_BOOLEAN
#elif defined (CAN_STOP_SEC_CONST_FAST_BOOLEAN)
   #undef      CAN_STOP_SEC_CONST_FAST_BOOLEAN
   #define STOP_SEC_CONST_FAST_BOOLEAN

#elif defined (CAN_START_SEC_CONST_FAST_8BIT)
   #undef      CAN_START_SEC_CONST_FAST_8BIT
   #define START_SEC_CONST_FAST_8BIT
#elif defined (CAN_STOP_SEC_CONST_FAST_8BIT)
   #undef      CAN_STOP_SEC_CONST_FAST_8BIT
   #define STOP_SEC_CONST_FAST_8BIT

#elif defined (CAN_START_SEC_CONST_FAST_16BIT)
   #undef      CAN_START_SEC_CONST_FAST_16BIT
   #define START_SEC_CONST_FAST_16BIT
#elif defined (CAN_STOP_SEC_CONST_FAST_16BIT)
   #undef      CAN_STOP_SEC_CONST_FAST_16BIT
   #define STOP_SEC_CONST_FAST_16BIT

#elif defined (CAN_START_SEC_CONST_FAST_32BIT)
   #undef      CAN_START_SEC_CONST_FAST_32BIT
   #define START_SEC_CONST_FAST_32BIT
#elif defined (CAN_STOP_SEC_CONST_FAST_32BIT)
   #undef      CAN_STOP_SEC_CONST_FAST_32BIT
   #define STOP_SEC_CONST_FAST_32BIT

#elif defined (CAN_START_SEC_CONST_FAST_UNSPECIFIED)
   #undef      CAN_START_SEC_CONST_FAST_UNSPECIFIED
   #define START_SEC_CONST_FAST_UNSPECIFIED
#elif defined (CAN_STOP_SEC_CONST_FAST_UNSPECIFIED)
   #undef      CAN_STOP_SEC_CONST_FAST_UNSPECIFIED
   #define STOP_SEC_CONST_FAST_UNSPECIFIED

#elif defined (CAN_START_CONST_PBCFG)
   #undef      CAN_START_CONST_PBCFG
   #define START_CONST_PBCFG
#elif defined (CAN_STOP_CONST_PBCFG)
   #undef      CAN_STOP_CONST_PBCFG
   #define STOP_CONST_PBCFG

#elif defined (CAN_START_CONST_PBCFG_ROOT)
   #undef      CAN_START_CONST_PBCFG_ROOT
   #define START_CONST_PBCFG_ROOT
#elif defined (CAN_STOP_CONST_PBCFG_ROOT)
   #undef      CAN_STOP_CONST_PBCFG_ROOT
   #define STOP_CONST_PBCFG_ROOT

/*=======[C A N I F]==========================================================*/




#endif /* START_WITH_IF */


#if defined (START_WITH_IF)

/*=======[C O M]==============================================================*/

#elif defined (COM_START_SEC_CODE)
   #undef      COM_START_SEC_CODE
   #define START_SEC_CODE
#elif defined (COM_STOP_SEC_CODE)
   #undef      COM_STOP_SEC_CODE
   #define STOP_SEC_CODE

#elif defined (COM_START_SEC_CODE_FAST)
   #undef      COM_START_SEC_CODE_FAST
   #define START_SEC_CODE_FAST
#elif defined (COM_STOP_SEC_CODE_FAST)
   #undef      COM_STOP_SEC_CODE_FAST
   #define STOP_SEC_CODE_FAST

#elif defined (COM_START_SEC_VAR_NOINIT_BOOLEAN)
   #undef      COM_START_SEC_VAR_NOINIT_BOOLEAN
   #define START_SEC_VAR_NOINIT_BOOLEAN
#elif defined (COM_STOP_SEC_VAR_NOINIT_BOOLEAN)
   #undef      COM_STOP_SEC_VAR_NOINIT_BOOLEAN
   #define STOP_SEC_VAR_NOINIT_BOOLEAN

#elif defined (COM_START_SEC_VAR_NOINIT_8BIT)
   #undef      COM_START_SEC_VAR_NOINIT_8BIT
   #define START_SEC_VAR_NOINIT_8BIT
#elif defined (COM_STOP_SEC_VAR_NOINIT_8BIT)
   #undef      COM_STOP_SEC_VAR_NOINIT_8BIT
   #define STOP_SEC_VAR_NOINIT_8BIT

#elif defined (COM_START_SEC_VAR_NOINIT_16BIT)
   #undef      COM_START_SEC_VAR_NOINIT_16BIT
   #define START_SEC_VAR_NOINIT_16BIT
#elif defined (COM_STOP_SEC_VAR_NOINIT_16BIT)
   #undef      COM_STOP_SEC_VAR_NOINIT_16BIT
   #define STOP_SEC_VAR_NOINIT_16BIT

#elif defined (COM_START_SEC_VAR_NOINIT_32BIT)
   #undef      COM_START_SEC_VAR_NOINIT_32BIT
   #define START_SEC_VAR_NOINIT_32BIT
#elif defined (COM_STOP_SEC_VAR_NOINIT_32BIT)
   #undef      COM_STOP_SEC_VAR_NOINIT_32BIT
   #define STOP_SEC_VAR_NOINIT_32BIT

#elif defined (COM_START_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      COM_START_SEC_VAR_NOINIT_UNSPECIFIED
   #define START_SEC_VAR_NOINIT_UNSPECIFIED
#elif defined (COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
   #undef      COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
   #define STOP_SEC_VAR_NOINIT_UNSPECIFIED

#elif defined (COM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN)
   #undef      COM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
   #define START_SEC_VAR_POWER_ON_INIT_BOOLEAN
#elif defined (COM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN)
   #undef      COM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
   #define STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN

#elif defined (COM_START_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      COM_START_SEC_VAR_POWER_ON_INIT_8BIT
   #define START_SEC_VAR_POWER_ON_INIT_8BIT
#elif defined (COM_STOP_SEC_VAR_POWER_ON_INIT_8BIT)
   #undef      COM_STOP_SEC_VAR_POWER_ON_INIT_8BIT
   #define STOP_SEC_VAR_POWER_ON_INIT_8BIT

#elif defined (COM_START_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      COM_START_SEC_VAR_POWER_ON_INIT_16BIT
   #define START_SEC_VAR_POWER_ON_INIT_16BIT
#elif defined (COM_STOP_SEC_VAR_POWER_ON_INIT_16BIT)
   #undef      COM_STOP_SEC_VAR_POWER_ON_INIT_16BIT
   #define STOP_SEC_VAR_POWER_ON_INIT_16BIT

#elif defined (COM_START_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      COM_START_SEC_VAR_POWER_ON_INIT_32BIT
   #define START_SEC_VAR_POWER_ON_INIT_32BIT
#elif defined (COM_STOP_SEC_VAR_POWER_ON_INIT_32BIT)
   #undef      COM_STOP_SEC_VAR_POWER_ON_INIT_32BIT
   #define STOP_SEC_VAR_POWER_ON_INIT_32BIT

#elif defined (COM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      COM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #define START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
#elif defined (COM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
   #undef      COM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
   #define STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED

#elif defined (COM_START_SEC_VAR_BOOLEAN)
   #undef      COM_START_SEC_VAR_BOOLEAN
   #define START_SEC_VAR_BOOLEAN
#elif defined (COM_STOP_SEC_VAR_BOOLEAN)
   #undef      COM_STOP_SEC_VAR_BOOLEAN
   #define STOP_SEC_VAR_BOOLEAN

#elif defined (COM_START_SEC_VAR_8BIT)
   #undef      COM_START_SEC_VAR_8BIT
   #define START_SEC_VAR_8BIT
#elif defined (COM_STOP_SEC_VAR_8BIT)
   #undef      COM_STOP_SEC_VAR_8BIT
   #define STOP_SEC_VAR_8BIT

#elif defined (COM_START_SEC_VAR_16BIT)
   #undef      COM_START_SEC_VAR_16BIT
   #define START_SEC_VAR_16BIT
#elif defined (COM_STOP_SEC_VAR_16BIT)
   #undef      COM_STOP_SEC_VAR_16BIT
   #define STOP_SEC_VAR_16BIT

#elif defined (COM_START_SEC_VAR_32BIT)
   #undef      COM_START_SEC_VAR_32BIT
   #define START_SEC_VAR_32BIT
#elif defined (COM_STOP_SEC_VAR_32BIT)
   #undef      COM_STOP_SEC_VAR_32BIT
   #define STOP_SEC_VAR_32BIT

#elif defined (COM_START_SEC_VAR_UNSPECIFIED)
   #undef      COM_START_SEC_VAR_UNSPECIFIED
   #define START_SEC_VAR_UNSPECIFIED
#elif defined (COM_STOP_SEC_VAR_UNSPECIFIED)
   #undef      COM_STOP_SEC_VAR_UNSPECIFIED
   #define STOP_SEC_VAR_UNSPECIFIED


#elif defined (COM_START_SEC_VAR_FAST_NOINIT_BOOLEAN)
   #undef      COM_START_SEC_VAR_FAST_NOINIT_BOOLEAN
   #define START_SEC_VAR_FAST_NOINIT_BOOLEAN
#elif defined (COM_STOP_SEC_VAR_FAST_NOINIT_BOOLEAN)
   #undef      COM_STOP_SEC_VAR_FAST_NOINIT_BOOLEAN
   #define STOP_SEC_VAR_FAST_NOINIT_BOOLEAN

#elif defined (COM_START_SEC_VAR_FAST_NOINIT_8BIT)
   #undef      COM_START_SEC_VAR_FAST_NOINIT_8BIT
   #define START_SEC_VAR_FAST_NOINIT_8BIT
#elif defined (COM_STOP_SEC_VAR_FAST_NOINIT_8BIT)
   #undef      COM_STOP_SEC_VAR_FAST_NOINIT_8BIT
   #define STOP_SEC_VAR_FAST_NOINIT_8BIT

#elif defined (COM_START_SEC_VAR_FAST_NOINIT_16BIT)
   #undef      COM_START_SEC_VAR_FAST_NOINIT_16BIT
   #define START_SEC_VAR_FAST_NOINIT_16BIT
#elif defined (COM_STOP_SEC_VAR_FAST_NOINIT_16BIT)
   #undef      COM_STOP_SEC_VAR_FAST_NOINIT_16BIT
   #define STOP_SEC_VAR_FAST_NOINIT_16BIT

#elif defined (COM_START_SEC_VAR_FAST_NOINIT_32BIT)
   #undef      COM_START_SEC_VAR_FAST_NOINIT_32BIT
   #define START_SEC_VAR_FAST_NOINIT_32BIT
#elif defined (COM_STOP_SEC_VAR_FAST_NOINIT_32BIT)
   #undef      COM_STOP_SEC_VAR_FAST_NOINIT_32BIT
   #define STOP_SEC_VAR_FAST_NOINIT_32BIT

#elif defined (COM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
   #undef      COM_START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
   #define START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
#elif defined (COM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
   #undef      COM_STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
   #define STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED

#elif defined (COM_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN)
   #undef      COM_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
   #define START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
#elif defined (COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN)
   #undef      COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN

#elif defined (COM_START_SEC_VAR_FAST_POWER_ON_INIT_8BIT)
   #undef      COM_START_SEC_VAR_FAST_POWER_ON_INIT_8BIT
   #define START_SEC_VAR_FAST_POWER_ON_INIT_8BIT
#elif defined (COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_8BIT)
   #undef      COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_8BIT
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_8BIT

#elif defined (COM_START_SEC_VAR_FAST_POWER_ON_INIT_16BIT)
   #undef      COM_START_SEC_VAR_FAST_POWER_ON_INIT_16BIT
   #define START_SEC_VAR_FAST_POWER_ON_INIT_16BIT
#elif defined (COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_16BIT)
   #undef      COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_16BIT
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_16BIT

#elif defined (COM_START_SEC_VAR_FAST_POWER_ON_INIT_32BIT)
   #undef      COM_START_SEC_VAR_FAST_POWER_ON_INIT_32BIT
   #define START_SEC_VAR_FAST_POWER_ON_INIT_32BIT
#elif defined (COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_32BIT)
   #undef      COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_32BIT
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_32BIT

#elif defined (COM_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED)
   #undef      COM_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
   #define START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
#elif defined (COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED)
   #undef      COM_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
   #define STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED

#elif defined (COM_START_SEC_VAR_FAST_BOOLEAN)
   #undef      COM_START_SEC_VAR_FAST_BOOLEAN
   #define START_SEC_VAR_FAST_BOOLEAN
#elif defined (COM_STOP_SEC_VAR_FAST_BOOLEAN)
   #undef      COM_STOP_SEC_VAR_FAST_BOOLEAN
   #define STOP_SEC_VAR_FAST_BOOLEAN

#elif defined (COM_START_SEC_VAR_FAST_8BIT)
   #undef      COM_START_SEC_VAR_FAST_8BIT
   #define START_SEC_VAR_FAST_8BIT
#elif defined (COM_STOP_SEC_VAR_FAST_8BIT)
   #undef      COM_STOP_SEC_VAR_FAST_8BIT
   #define STOP_SEC_VAR_FAST_8BIT

#elif defined (COM_START_SEC_VAR_FAST_16BIT)
   #undef      COM_START_SEC_VAR_FAST_16BIT
   #define START_SEC_VAR_FAST_16BIT
#elif defined (COM_STOP_SEC_VAR_FAST_16BIT)
   #undef      COM_STOP_SEC_VAR_FAST_16BIT
   #define STOP_SEC_VAR_FAST_16BIT

#elif defined (COM_START_SEC_VAR_FAST_32BIT)
   #undef      COM_START_SEC_VAR_FAST_32BIT
   #define START_SEC_VAR_FAST_32BIT
#elif defined (COM_STOP_SEC_VAR_FAST_32BIT)
   #undef      COM_STOP_SEC_VAR_FAST_32BIT
   #define STOP_SEC_VAR_FAST_32BIT

#elif defined (COM_START_SEC_VAR_FAST_UNSPECIFIED)
   #undef      COM_START_SEC_VAR_FAST_UNSPECIFIED
   #define START_SEC_VAR_FAST_UNSPECIFIED
#elif defined (COM_STOP_SEC_VAR_FAST_UNSPECIFIED)
   #undef      COM_STOP_SEC_VAR_FAST_UNSPECIFIED
   #define STOP_SEC_VAR_FAST_UNSPECIFIED

#elif defined (COM_START_SEC_CONST_BOOLEAN)
   #undef      COM_START_SEC_CONST_BOOLEAN
   #define START_SEC_CONST_BOOLEAN
#elif defined (COM_STOP_SEC_CONST_BOOLEAN)
   #undef      COM_STOP_SEC_CONST_BOOLEAN
   #define STOP_SEC_CONST_BOOLEAN

#elif defined (COM_START_SEC_CONST_8BIT)
   #undef      COM_START_SEC_CONST_8BIT
   #define START_SEC_CONST_8BIT
#elif defined (COM_STOP_SEC_CONST_8BIT)
   #undef      COM_STOP_SEC_CONST_8BIT
   #define STOP_SEC_CONST_8BIT

#elif defined (COM_START_SEC_CONST_16BIT)
   #undef      COM_START_SEC_CONST_16BIT
   #define START_SEC_CONST_16BIT
#elif defined (COM_STOP_SEC_CONST_16BIT)
   #undef      COM_STOP_SEC_CONST_16BIT
   #define STOP_SEC_CONST_16BIT

#elif defined (COM_START_SEC_CONST_32BIT)
   #undef      COM_START_SEC_CONST_32BIT
   #define START_SEC_CONST_32BIT
#elif defined (COM_STOP_SEC_CONST_32BIT)
   #undef      COM_STOP_SEC_CONST_32BIT
   #define STOP_SEC_CONST_32BIT

#elif defined (COM_START_SEC_CONST_UNSPECIFIED)
   #undef      COM_START_SEC_CONST_UNSPECIFIED
   #define START_SEC_CONST_UNSPECIFIED
#elif defined (COM_STOP_SEC_CONST_UNSPECIFIED)
   #undef      COM_STOP_SEC_CONST_UNSPECIFIED
   #define STOP_SEC_CONST_UNSPECIFIED

#elif defined (COM_START_SEC_CONST_FAST_BOOLEAN)
   #undef      COM_START_SEC_CONST_FAST_BOOLEAN
   #define START_SEC_CONST_FAST_BOOLEAN
#elif defined (COM_STOP_SEC_CONST_FAST_BOOLEAN)
   #undef      COM_STOP_SEC_CONST_FAST_BOOLEAN
   #define STOP_SEC_CONST_FAST_BOOLEAN

#elif defined (COM_START_SEC_CONST_FAST_8BIT)
   #undef      COM_START_SEC_CONST_FAST_8BIT
   #define START_SEC_CONST_FAST_8BIT
#elif defined (COM_STOP_SEC_CONST_FAST_8BIT)
   #undef      COM_STOP_SEC_CONST_FAST_8BIT
   #define STOP_SEC_CONST_FAST_8BIT

#elif defined (COM_START_SEC_CONST_FAST_16BIT)
   #undef      COM_START_SEC_CONST_FAST_16BIT
   #define START_SEC_CONST_FAST_16BIT
#elif defined (COM_STOP_SEC_CONST_FAST_16BIT)
   #undef      COM_STOP_SEC_CONST_FAST_16BIT
   #define STOP_SEC_CONST_FAST_16BIT

#elif defined (COM_START_SEC_CONST_FAST_32BIT)
   #undef      COM_START_SEC_CONST_FAST_32BIT
   #define START_SEC_CONST_FAST_32BIT
#elif defined (COM_STOP_SEC_CONST_FAST_32BIT)
   #undef      COM_STOP_SEC_CONST_FAST_32BIT
   #define STOP_SEC_CONST_FAST_32BIT

#elif defined (COM_START_SEC_CONST_FAST_UNSPECIFIED)
   #undef      COM_START_SEC_CONST_FAST_UNSPECIFIED
   #define START_SEC_CONST_FAST_UNSPECIFIED
#elif defined (COM_STOP_SEC_CONST_FAST_UNSPECIFIED)
   #undef      COM_STOP_SEC_CONST_FAST_UNSPECIFIED
   #define STOP_SEC_CONST_FAST_UNSPECIFIED

#elif defined (COM_START_CONST_PBCFG)
   #undef      COM_START_CONST_PBCFG
   #define START_CONST_PBCFG
#elif defined (COM_STOP_CONST_PBCFG)
   #undef      COM_STOP_CONST_PBCFG
   #define STOP_CONST_PBCFG

#elif defined (COM_START_CONST_PBCFG_ROOT)
   #undef      COM_START_CONST_PBCFG_ROOT
   #define START_CONST_PBCFG_ROOT
#elif defined (COM_STOP_CONST_PBCFG_ROOT)
   #undef      COM_STOP_CONST_PBCFG_ROOT
   #define STOP_CONST_PBCFG_ROOT
#endif

/*=======[C A N I F]==========================================================*/




#endif /* START_WITH_IF */

/* @req MEMMAP006  @req MEMMAP013 */
/*=======[M E M M A P  S Y M B O L  D E F I N E]==============================*/
#define MEMMAP_ERROR

#if defined (START_WITH_IF)
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CODE)
    #undef START_SEC_CODE
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CODE)
    #undef STOP_SEC_CODE
    #undef MEMMAP_ERROR
#endif /* START_SEC_CODE */

#if defined (START_WITH_IF)
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CODE_FAST)
    #undef START_SEC_CODE_FAST
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CODE_FAST)
    #undef STOP_SEC_CODE_FAST
    #undef MEMMAP_ERROR
#endif /* START_SEC_CODE_FAST */

#if defined (START_WITH_IF)

#elif defined (START_SEC_VAR_NOINIT_BOOLEAN)
    #undef START_SEC_VAR_NOINIT_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_NOINIT_BOOLEAN)
    #undef STOP_SEC_VAR_NOINIT_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_NOINIT_8BIT)
    #undef START_SEC_VAR_NOINIT_8BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_NOINIT_8BIT)
    #undef STOP_SEC_VAR_NOINIT_8BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_NOINIT_16BIT)
    #undef START_SEC_VAR_NOINIT_16BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_NOINIT_16BIT)
    #undef STOP_SEC_VAR_NOINIT_16BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_NOINIT_32BIT)
    #undef START_SEC_VAR_NOINIT_32BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_NOINIT_32BIT)
    #undef STOP_SEC_VAR_NOINIT_32BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_NOINIT_UNSPECIFIED)
    #undef START_SEC_VAR_NOINIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_NOINIT_UNSPECIFIED)
    #undef STOP_SEC_VAR_NOINIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#endif /* START_SEC_VAR_NOINIT_<SIZE> */

#if defined (START_WITH_IF)

#elif defined (START_SEC_VAR_POWER_ON_INIT_BOOLEAN)
    #undef START_SEC_VAR_POWER_ON_INIT_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN)
    #undef STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_POWER_ON_INIT_8BIT)
    #undef START_SEC_VAR_POWER_ON_INIT_8BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_POWER_ON_INIT_8BIT)
    #undef STOP_SEC_VAR_POWER_ON_INIT_8BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_POWER_ON_INIT_16BIT)
    #undef START_SEC_VAR_POWER_ON_INIT_16BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_POWER_ON_INIT_16BIT)
    #undef STOP_SEC_VAR_POWER_ON_INIT_16BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_POWER_ON_INIT_32BIT)
    #undef START_SEC_VAR_POWER_ON_INIT_32BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_POWER_ON_INIT_32BIT)
    #undef STOP_SEC_VAR_POWER_ON_INIT_32BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
    #undef START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
    #undef STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#endif /* START_SEC_VAR_POWER_ON_INIT_<SIZE> */

#if defined (START_WITH_IF)

#elif defined (START_SEC_VAR_BOOLEAN)
    #undef START_SEC_VAR_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_BOOLEAN)
    #undef STOP_SEC_VAR_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_8BIT)
    #undef START_SEC_VAR_8BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_8BIT)
    #undef STOP_SEC_VAR_8BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_16BIT)
    #undef START_SEC_VAR_16BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_16BIT)
    #undef STOP_SEC_VAR_16BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_32BIT)
    #undef START_SEC_VAR_32BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_32BIT)
    #undef STOP_SEC_VAR_32BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_UNSPECIFIED)
    #undef START_SEC_VAR_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_UNSPECIFIED)
    #undef STOP_SEC_VAR_UNSPECIFIED
    #undef MEMMAP_ERROR

#endif /* START_SEC_VAR_<SIZE> */

#if defined (START_WITH_IF)

#elif defined (START_SEC_VAR_FAST_NOINIT_BOOLEAN)
    #undef START_SEC_VAR_FAST_NOINIT_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_NOINIT_BOOLEAN)
    #undef STOP_SEC_VAR_FAST_NOINIT_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_NOINIT_8BIT)
    #undef START_SEC_VAR_FAST_NOINIT_8BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_NOINIT_8BIT)
    #undef STOP_SEC_VAR_FAST_NOINIT_8BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_NOINIT_16BIT)
    #undef START_SEC_VAR_FAST_NOINIT_16BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_NOINIT_16BIT)
    #undef STOP_SEC_VAR_FAST_NOINIT_16BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_NOINIT_32BIT)
    #undef START_SEC_VAR_FAST_NOINIT_32BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_NOINIT_32BIT)
    #undef STOP_SEC_VAR_FAST_NOINIT_32BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
    #undef START_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED)
    #undef STOP_SEC_VAR_FAST_NOINIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#endif /* START_SEC_VAR_FAST_NOINIT_<SIZE> */

#if defined (START_WITH_IF)

#elif defined (START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN)
    #undef START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN)
    #undef STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_POWER_ON_INIT_8BIT)
    #undef START_SEC_VAR_FAST_POWER_ON_INIT_8BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_POWER_ON_INIT_8BIT)
    #undef STOP_SEC_VAR_FAST_POWER_ON_INIT_8BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_POWER_ON_INIT_16BIT)
    #undef START_SEC_VAR_FAST_POWER_ON_INIT_16BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_POWER_ON_INIT_16BIT)
    #undef STOP_SEC_VAR_FAST_POWER_ON_INIT_16BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_POWER_ON_INIT_32BIT)
    #undef START_SEC_VAR_FAST_POWER_ON_INIT_32BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_POWER_ON_INIT_32BIT)
    #undef STOP_SEC_VAR_FAST_POWER_ON_INIT_32BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED)
    #undef START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED)
    #undef STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
    #undef MEMMAP_ERROR

#endif /* START_SEC_VAR_FAST_POWER_ON_INIT_<SIZE> */

#if defined (START_WITH_IF)

#elif defined (START_SEC_VAR_FAST_BOOLEAN)
    #undef START_SEC_VAR_FAST_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_BOOLEAN)
    #undef STOP_SEC_VAR_FAST_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_8BIT)
    #undef START_SEC_VAR_FAST_8BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_8BIT)
    #undef STOP_SEC_VAR_FAST_8BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_16BIT)
    #undef START_SEC_VAR_FAST_16BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_16BIT)
    #undef STOP_SEC_VAR_FAST_16BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_32BIT)
    #undef START_SEC_VAR_FAST_32BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_32BIT)
    #undef STOP_SEC_VAR_FAST_32BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_VAR_FAST_UNSPECIFIED)
    #undef START_SEC_VAR_FAST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_VAR_FAST_UNSPECIFIED)
    #undef STOP_SEC_VAR_FAST_UNSPECIFIED
    #undef MEMMAP_ERROR

#endif /* START_SEC_VAR_FAST_<SIZE> */


#if defined (START_WITH_IF)

#elif defined (START_SEC_CONST_BOOLEAN)
    #undef START_SEC_CONST_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_BOOLEAN)
    #undef STOP_SEC_CONST_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CONST_8BIT)
    #undef START_SEC_CONST_8BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_8BIT)
    #undef STOP_SEC_CONST_8BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CONST_16BIT)
    #undef START_SEC_CONST_16BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_16BIT)
    #undef STOP_SEC_CONST_16BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CONST_32BIT)
    #undef START_SEC_CONST_32BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_32BIT)
    #undef STOP_SEC_CONST_32BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CONST_UNSPECIFIED)
    #undef START_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_UNSPECIFIED)
    #undef STOP_SEC_CONST_UNSPECIFIED
    #undef MEMMAP_ERROR

#endif /* START_SEC_CONST_<SIZE> */

#if defined (START_WITH_IF)

#elif defined (START_SEC_CONST_FAST_BOOLEAN)
    #undef START_SEC_CONST_FAST_BOOLEAN
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_FAST_BOOLEAN)
    #undef STOP_SEC_CONST_FAST_BOOLEAN
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CONST_FAST_8BIT)
    #undef START_SEC_CONST_FAST_8BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_FAST_8BIT)
    #undef STOP_SEC_CONST_FAST_8BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CONST_FAST_16BIT)
    #undef START_SEC_CONST_FAST_16BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_FAST_16BIT)
    #undef STOP_SEC_CONST_FAST_16BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CONST_FAST_32BIT)
    #undef START_SEC_CONST_FAST_32BIT
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_FAST_32BIT)
    #undef STOP_SEC_CONST_FAST_32BIT
    #undef MEMMAP_ERROR

#elif defined (START_SEC_CONST_FAST_UNSPECIFIED)
    #undef START_SEC_CONST_FAST_UNSPECIFIED
    #undef MEMMAP_ERROR
#elif defined (STOP_SEC_CONST_FAST_UNSPECIFIED)
    #undef STOP_SEC_CONST_FAST_UNSPECIFIED
    #undef MEMMAP_ERROR

#endif /* START_SEC_CONST_FAST_<SIZE> */

#if defined (START_WITH_IF)

#elif defined (START_CONST_PBCFG)
    #undef START_CONST_PBCFG
    #undef MEMMAP_ERROR
#elif defined (STOP_CONST_PBCFG)
    #undef STOP_CONST_PBCFG
    #undef MEMMAP_ERROR

#endif /* START_CONST_PBCFG */

#if defined (START_WITH_IF)

#elif defined (START_CONST_PBCFG_ROOT)
    #undef START_CONST_PBCFG_ROOT
    #undef MEMMAP_ERROR
#elif defined (STOP_CONST_PBCFG_ROOT)
    #undef STOP_CONST_PBCFG_ROOT
    #undef MEMMAP_ERROR

#endif /* START_CONST_PBCFG */


#if defined (START_WITH_IF)

/*=======[M E M M A P  S Y M B O L  C H E C K]================================*/
/* @req MEMMAP007 */
/***********************memmap symbol check ***********************/
#if defined (MEMMAP_ERROR)
    #error "MemMap.h, wrong pragma command"
#endif

#endif /* end of MEMMAP_H */

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0         20130227  chenxuehua  Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/
