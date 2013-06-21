/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Dio_Mpc5634.c>
 *  @brief      <Abstract API of Dio Module>
 *  
 *  <Compiler: CodeWarrior V2.10    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
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

/*=======[I N C L U D E S]====================================================*/
#include "Dio_Mpc5634.h"

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/
#define DIO_AR_MAJOR_VERSION_C   2
#define DIO_AR_MINOR_VERSION_C   2
#define DIO_AR_PATCH_VERSION_C   2
#define DIO_SW_MAJOR_VERSION_C   1
#define DIO_SW_MINOR_VERSION_C   0
#define DIO_SW_PATCH_VERSION_C   0

/*=======[V E R S I O N  C H E C K]===========================================*/
#if((DIO_AR_MAJOR_VERSION_C != DIO_AR_MAJOR_VERSION)\
  ||(DIO_AR_MINOR_VERSION_C != DIO_AR_MINOR_VERSION)\
  ||(DIO_AR_PATCH_VERSION_C != DIO_AR_PATCH_VERSION))
#error "AutoSar Version Numbers of Dio.c and Dio.h are different"
#endif

#if ((DIO_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION)\
  ||(DIO_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION)\
  ||(DIO_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION))
#error "Software Version Numbers of Dio.c and Dio.h are different"
#endif

/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   D A T A]==========================================*/
STATIC CONST(uint16,DIO_APPL_CONST) Port[]=
{
    DIO_CHANNEL_A0_66,
    DIO_CHANNEL_A1_67,
    DIO_CHANNEL_A2_84,
    DIO_CHANNEL_A3_81,
    DIO_CHANNEL_A4_83,
    DIO_CHANNEL_A5_82,
    DIO_CHANNEL_A6_72,
    DIO_CHANNEL_A7_69,
    DIO_CHANNEL_A8_89,
    DIO_CHANNEL_A9_95,
    DIO_CHANNEL_A10_96,
    DIO_CHANNEL_A11_94,
    DIO_CHANNEL_A12_92,
    DIO_CHANNEL_A13_90,
    DIO_CHANNEL_A14_97,
    DIO_CHANNEL_A15_88,
    
    DIO_CHANNEL_B0_87,
    DIO_CHANNEL_B1_52,
    DIO_CHANNEL_B2_51,
    DIO_CHANNEL_B3_50,
    DIO_CHANNEL_B4_49,
    DIO_CHANNEL_B5_47,
    DIO_CHANNEL_B6_45,
    DIO_CHANNEL_B7_44,
    DIO_CHANNEL_B8_43,
    DIO_CHANNEL_B9_42,
    DIO_CHANNEL_B10_41,
    DIO_CHANNEL_B11_40,
    DIO_CHANNEL_B12_39,
    DIO_CHANNEL_B13_38,
    DIO_CHANNEL_B14_37,
    DIO_CHANNEL_B15_35,
    
    DIO_CHANNEL_C0_33,
    DIO_CHANNEL_C1_32,
    DIO_CHANNEL_C2_31,
    DIO_CHANNEL_C3_30,
    DIO_CHANNEL_C4_29,
    DIO_CHANNEL_C5_28,
    DIO_CHANNEL_C6_27,
    DIO_CHANNEL_C7_25,
    DIO_CHANNEL_C8_23,
    DIO_CHANNEL_C9_21,
    DIO_CHANNEL_C10_20,
    DIO_CHANNEL_C11_19,
    DIO_CHANNEL_C12_18,
    DIO_CHANNEL_C13_17,
    DIO_CHANNEL_C14_16,
    DIO_CHANNEL_C15_15,
    
    DIO_CHANNEL_D0_14,
    DIO_CHANNEL_D1_54,
    DIO_CHANNEL_D2_55,
    DIO_CHANNEL_D3_56,
    DIO_CHANNEL_D4_57,
    DIO_CHANNEL_D5_58,
    DIO_CHANNEL_D6_60,
    DIO_CHANNEL_D7_62,
    DIO_CHANNEL_D8_63,
    DIO_CHANNEL_D9_64,
    DIO_CHANNEL_D10_65,
    DIO_CHANNEL_D11_68,
    DIO_CHANNEL_D12_70,
    DIO_CHANNEL_D13_71,
    DIO_CHANNEL_D14_XX,
    DIO_CHANNEL_D15_XX,

    DIO_CHANNEL_E0_XX,
    DIO_CHANNEL_E1_XX,
    DIO_CHANNEL_E2_99,
    DIO_CHANNEL_E3_110,
    DIO_CHANNEL_E4_111,
    DIO_CHANNEL_E5_112,
    DIO_CHANNEL_E6_114,
    DIO_CHANNEL_E7_109,
    DIO_CHANNEL_E8_101,
    DIO_CHANNEL_E9_106,
    DIO_CHANNEL_E10_100,
    DIO_CHANNEL_E11_103,
    DIO_CHANNEL_E12_107,
    DIO_CHANNEL_E13_XX,
    DIO_CHANNEL_E14_XX,
    DIO_CHANNEL_E15_XX,
};

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/*
 * Brief               <Returns the value of the specified DIO channel.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ChannelId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Dio_LevelType:STD_HIGH STD_LOW>  
 * PreCondition        <>  
 * CallByAPI           <Dio_ReadChannel> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"

FUNC(Dio_LevelType,DIO_CODE)Dio_Mpc5634ReadChannel(Dio_ChannelType channelId)
{	
    Dio_LevelType level = STD_LOW;
	
    if (SIU.PCR[channelId].B.IBE == TRUE)
    {	
        level = (Dio_LevelType)SIU.GPDI[channelId].B.PDI;
    }
    else
    {
        level = (Dio_LevelType) SIU.GPDO[channelId].R;
    }
	
    return (level);
}

#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to set a level of a channel.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ChannelId , Level>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Dio_WriteChannel> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"

FUNC(void,DIO_CODE)Dio_Mpc5634WriteChannel(Dio_ChannelType channelId, Dio_LevelType level)
{

    SIU.GPDO [channelId].R = (uint8)level;
 	
    return;
}

#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Returns the level of all channels of that port.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <PortId>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <Dio_PortLevelType:Level of all channels of that port>  
 * PreCondition        <>  
 * CallByAPI           <Dio_ReadPort> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"

FUNC(Dio_PortLevelType,DIO_CODE)Dio_Mpc5634ReadPort(Dio_PortType portId)
{
    Dio_PortLevelType levelPort = STD_LOW;
    Dio_LevelType levelChannel;
    uint8 i;
		
    for (i = 0; i < 16; i++) /** @req DIO104 */
    {
        if(Port[portId * 16 + i] < 500)
        {
            if (SIU.PCR[Port[portId * 16 + i] ].B.IBE == TRUE)
            {
                if (SIU.GPDI [Port[portId * 16 + i] ].R > 0)
                {
                    levelChannel = STD_HIGH;
                }
                else
                {
                    levelChannel = STD_LOW;
                }
            }
            else
            {
                levelChannel = (Dio_LevelType) SIU.GPDO[Port[portId * 16 + i]].R;
            }
        }
        else
		{
            levelChannel = STD_LOW ;
        }
        
        levelPort |= levelChannel << i;
    }
  	
    return levelPort; 
}

#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to set a value of the port.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <PortId, Level>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Dio_WritePort> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"

FUNC(void,DIO_CODE)Dio_Mpc5634WritePort(Dio_PortType portId, Dio_PortLevelType levelPort)
{
    uint8 levelChannel;
    uint8 i;
    Dio_ChannelType channelId;
		
    for (i = 0; i < 16; i++)
    {   
  		/** @req DIO105 @req DIO108 */
        levelChannel = (uint8)(levelPort & 0x01);
        channelId = Port[portId * 16 + i];  /** @req DIO034 */
        
		if(channelId < 500)
		{
		    if (TRUE == SIU.PCR[channelId].B.OBE)         /** @req DIO035 */
            {
                SIU.GPDO [channelId].R = levelChannel;
            }
		}
        else
        {
            /** do nothing */
        }
				
        levelPort = levelPort >> 1;
    }
  	
    return;
}

#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*
 * Brief               <Service to set a subset of the adjoining bits of a port to a specified level.>
 * ServiceId           <>
 * Sync/Async          <>
 * Reentrancy          <>
 * Param-Name[in]      <ChannelGroupIdPtr , Level>      
 * Param-Name[out]     <None>
 * Param-Name[in/out]  <None>
 * Return              <None>  
 * PreCondition        <>  
 * CallByAPI           <Dio_WriteChannelGroup> 
 */
/******************************************************************************/
#define DIO_START_SEC_CODE
#include "MemMap.h"

FUNC(void,DIO_CODE) Dio_Mpc5634WriteChannelGroup(
    P2CONST(Dio_ChannelGroupType,AUTOMATIC,DIO_APPL_DATA)channelGroupIdPtr,Dio_PortLevelType levelPort)
{
    uint8 levelChannel;
    uint8 i;
    uint8 numberOfChannel = 1;
    uint16 maskTemp=channelGroupIdPtr->mask;
    Dio_ChannelType channelId;
	
    for (i = 0 ; i<16 ; i++)
    {
        if (maskTemp > 0x01)
        {
            maskTemp = (uint16)(maskTemp >> 1); /** @req DIO90 */
            numberOfChannel++;                  
        }
    }

    for	(i = channelGroupIdPtr->offset; i < numberOfChannel; i++)
    {
        levelChannel = (uint8)(levelPort & 0x01);
        channelId = Port[channelGroupIdPtr->port * 16 + i];
		
        SIU.GPDO [channelId].R = levelChannel; /** @req DIO39 @req DIO40 */
        levelPort = levelPort >> 1; 			/** @req DIO91 */
    }
  	
    return;
}

#define DIO_STOP_SEC_CODE
#include "MemMap.h"

/*=======[E N D   O F   F I L E]==============================================*/

