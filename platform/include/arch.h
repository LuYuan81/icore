/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <arch.h>
 *  @brief      <>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-14>
 */
/*============================================================================*/
#ifndef _ARCH_H
#define _ARCH_H

/*=======[M A C R O S]========================================================*/
#define OSMAXALLOWEDVALUE ((TickType) 0x7FFFFFFF)
#define OSTICKSPERBASE ((TickType) 0x01)
#define OSMINCYCLE ((TickType) 0x01)

#define OSSwitch2System() asm lds osSystemStack

#define arch_disable_int() asm sei
#define arch_enable_int() asm cli

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
void OSInitCPU(void);
void arch_dispatch(void);
void arch_set_ipl(IPLType ipl);
IPLType arch_get_ipl(void);
void arch_suspend_int(void);
void arch_restore_int(void);
extern void MCU_init(void);
#endif

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/