/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <Gpt_Mpc5634.h>
 *  @brief      <Internal API of Gpt Module>
 *  
 *  <Compiler: CodeWarrior V2.8    MCU:MPC5634>
 *  
 *  @author     <i-soft>
 *  @date       <2013-04-10>
 */
/*============================================================================*/
#ifndef _GPT_MPC5634_H_
#define _GPT_MPC5634_H_
/*=======[M A C R O S]========================================================*/
/* Gpt Channel has not been configured */
#define GPT_UNCONFIGURED     (0xFFFF)

/*=======[T Y P E   D E F I N I T I O N S]====================================*/
/* Gpt Channel Identifier */
typedef enum
{	
    GPT_CHANNEL_PIT_0 = 0,
    GPT_CHANNEL_PIT_1,
    GPT_CHANNEL_PIT_2,
    GPT_CHANNEL_PIT_3,
    GPT_CHANNEL_RTI,
   	GPT_NUMBER_OF_CHANNELS    
}GPT_CHANNEL_ID;

/*=======[E X T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/
FUNC(void,GPT_CODE) Gpt_Isr_Handler(Gpt_ChannelType channel);
FUNC(void,GPT_CODE) Gpt_PIT0_Isr(void);
FUNC(void,GPT_CODE) Gpt_PIT1_Isr(void);
FUNC(void,GPT_CODE) Gpt_PIT2_Isr(void);
FUNC(void,GPT_CODE) Gpt_PIT3_Isr(void);
FUNC(void,GPT_CODE) Gpt_RTI_Isr(void);
FUNC(void,GPT_CODE) Gpt_Mpc5634Init(void);
FUNC(void,GPT_CODE) Gpt_Mpc5634DeInit(void);
FUNC(void,GPT_CODE) Gpt_Mpc5634StartTimer(Gpt_ChannelType channel, Gpt_ValueType value);
FUNC(void,GPT_CODE) Gpt_Mpc5634StopTimer(Gpt_ChannelType channel);
FUNC(Gpt_ValueType,GPT_CODE) Gpt_Mpc5634GetTimeElapsed(Gpt_ChannelType channel);
FUNC(Gpt_ValueType,GPT_CODE) Gpt_Mpc5634GetTimeRemaining( Gpt_ChannelType channel );

#endif /* _GPT_MPC5634_H_ */

/*=======[E N D   O F   F I L E]==============================================*/

