/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  
 *  @file       <Compiler.h>
 *  @brief      <>
 *  
 *  <>
 *  
 *  @author     <ISOFT>
 *  @date       <2012-09-14>
 */
/*============================================================================*/

#ifndef  COMPILER_H		
#define  COMPILER_H

/*=======[I N C L U D E S]====================================================*/
#include "Compiler_Cfg.h"

/*=======[M A C R O S]========================================================*/
#define AUTOMATIC
#define TYPEDEF
#define STATIC
#define NULL_PTR	((void *)0)
#define INLINE
#define P2VAR(ptrtype, memclass, ptrclass) \
              ptrclass ptrtype * memclass

#endif  

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/


