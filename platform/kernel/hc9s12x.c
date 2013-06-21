/*============================================================================*/
/** Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <hc9s12x.c>
 *  @brief      <Platform relative >
 *  
 *  <>
 *  
 *  @author     <ISOFT >
 *  @date       <2012-09-14>
 */
/*============================================================================*/

/*=======[I N C L U D E S]====================================================*/
#include "Os.h"
#include "derivative.h"
#include "cfgobj.h"
#include "kernel.h"
#include "Sci.h"

/*=======[M A C R O S]========================================================*/
#define osppage *(volatile uint8 *) (0x15) /*changed by huaming for XEP100*/

#define setReg8Bit(RegName, BitName)                             (RegName |= RegName##_##BitName##_##MASK)
#define clrReg8Bit(RegName, BitName)                             (RegName &= ~RegName##_##BitName##_##MASK)
#define invertReg8Bit(RegName, BitName)                          (RegName ^= RegName##_##BitName##_##MASK)
#define testReg8Bit(RegName, BitName)                            (RegName & RegName##_##BitName##_##MASK)

/* Whole peripheral register access macros */
#define setReg8(RegName, val)                                    (RegName = (byte)(val))
#define getReg8(RegName)                                         (RegName)
/* Bits peripheral register access macros */
#define testReg8Bits(RegName, GetMask)                           (RegName & (GetMask))
#define clrReg8Bits(RegName, ClrMask)                            (RegName &= ~(byte)(ClrMask))
#define setReg8Bits(RegName, SetMask)                            (RegName |= (byte)(SetMask))
#define invertReg8Bits(RegName, InvMask)                         (RegName ^= (byte)(InvMask))
#define clrSetReg8Bits(RegName, ClrMask, SetMask)                (RegName = (RegName & (~(byte)(ClrMask))) | (byte)(SetMask))
#define seqClrSetReg8Bits(RegName, BitsMask, BitsVal)            (RegName &= ~(~(byte)(BitsVal) & (byte)(BitsMask)),\
                                                                 RegName |= (byte)(BitsVal) & (byte)(BitsMask) )
#define seqSetClrReg8Bits(RegName, BitsMask, BitsVal)            (RegName |= (byte)(BitsVal) & (byte)(BitsMask),\
                                                                 RegName &= ~(~(byte)(BitsVal) & (byte)(BitsMask)) )
#define seqResetSetReg8Bits(RegName, BitsMask, BitsVal)          (RegName &= ~(byte)(BitsMask),\
                                                                 RegName |= (byte)(BitsVal) & (byte)(BitsMask) )
#define clrReg8BitsByOne(RegName, ClrMask, BitsMask)             (RegName &= (byte)(ClrMask) & (byte)(BitsMask))

/* Whole peripheral register access macros */
#define setReg16(RegName, val)                                  (RegName = (word)(val))
#define getReg16(RegName)                                       (RegName)

/* Bits peripheral register access macros */
#define testReg16Bits(RegName, GetMask)                         (RegName & (GetMask))
#define clrReg16Bits(RegName, ClrMask)                          (RegName &= ~(word)(ClrMask))
#define setReg16Bits(RegName, SetMask)                          (RegName |= (word)(SetMask))
#define invertReg16Bits(RegName, InvMask)                       (RegName ^= (word)(InvMask))
#define clrSetReg16Bits(RegName, ClrMask, SetMask)              (RegName = (RegName & (~(word)(ClrMask))) | (word)(SetMask))
#define seqClrSetReg16Bits(RegName, BitsMask, BitsVal)          (RegName &= ~(~(word)(BitsVal) & (word)(BitsMask)),\
                                                                RegName |= (word)(BitsVal) & (word)(BitsMask) )
#define seqSetClrReg16Bits(RegName, BitsMask, BitsVal)          (RegName |= (word)(BitsVal) & (word)(BitsMask),\
                                                                RegName &= ~(~(word)(BitsVal) & (word)(BitsMask)) )
#define seqResetSetReg16Bits(RegName, BitsMask, BitsVal)        (RegName &= ~(word)(BitsMask),\
                                                                RegName |= (word)(BitsVal) & (word)(BitsMask) )
#define clrReg16BitsByOne(RegName, ClrMask, BitsMask)           (RegName &= (word)(ClrMask) & (word)(BitsMask))

/*=======[E X T E R N A L   D A T A]==========================================*/
uint8 osIntNest=0;
CallLevelType osSaveLevel=0;
uint8 osSaveCcr=0;
uint8 OsIntLevel;

extern uint8 test_hua;
extern  uint8 osIntNest;
extern  CallLevelType osSaveLevel;

extern void near EnterISR2(void);
extern void near ExitISR2(void);

/*=======[I N T E R N A L   D A T A]==========================================*/
static uint16 osSaveCCRH;

/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/******************************************************************************/
/**
 * @brief               <Init interrupt varables>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSInitInterrupt(void)
{
      osIntNest = 0;
	  osSaveLevel = LEVEL_ISR;
	  suspend_all_count = 0;
  	  suspend_os_count = 0;
}

/******************************************************************************/
/**
 * @brief               <Init CPU>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void OSInitCPU(void){
  MCU_init();
}

/******************************************************************************/
/**
 * @brief               <Software interrupt>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void arch_dispatch(void){
	asm swi;
}

/******************************************************************************/
/**
 * @brief               <Ipl greater than 0, disable interrupt otherwise enable interrupt>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <ipl>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void arch_set_ipl(IPLType ipl){
	if(ipl>0){
		asm sei;
	}
	else
	{
		asm  cli;
	}
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <IPLType>    
 */
/******************************************************************************/
IPLType arch_get_ipl(void){
	return 0;
}

/******************************************************************************/
/**
 * @brief               <Save ccr to variable osSaveCcr and disable maskable interrupt>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void arch_suspend_int(void){
	asm{
		tfr ccr,a 
		sei
		staa osSaveCcr
	}
}

/******************************************************************************/
/**
 * @brief               <transfer variable osSaveCcr back to ccr>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void arch_restore_int(void){
	asm{
		ldaa osSaveCcr
		tfr a,ccr
	}
}

/******************************************************************************/
/**
 * @brief               <make the ccrh to 0, that means make ipl to 0>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void IPL_clear(void) 
{
 /*added by huaming for HS12X core*/
  asm
      {
        tfr ccrh,a 
        staa osSaveCCRH
      }
		  if(((osSaveCCRH>>8)&0x0f)>0)     
		    osSaveCCRH=0;
		  
	    asm
	    {
  			ldaa osSaveCCRH
  	    	tfr a,ccrh	
		  }	

}

/******************************************************************************/
/**
 * @brief               <Set the IPL to 0, so that can make all interrupt respond>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void osEnableLevel(void)
{
   	asm
	{
        ldaa #0
        tfr a, ccrh     
	}
		
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void near OSSwitch2Task(void){
	osInSystemStack = FALSE;
	osRunningTcb = &osTcb[osRunningTask];

	if( osRunningTcb->state == STATE_START){
		osRunningTcb->state = RUNNING;
		Call_PreTaskHook();
		asm{
			ldx osRunningTcb
			lds 0,x
		}
#if (CFG_SCHEDULE == PREEMPTIVE_MIXED)
		if(osTaskSchedule[osRunningTask]==PREEMPTIVE_NON){
			osDispatchLocker = 1;
		}
#endif
		arch_enable_int();
		osEnableLevel();  /*if no the code ,test won't pass because */
		osTask[osRunningTask].entry();
		
    	arch_disable_int();
	} else {
		if(osRunningTcb->state != RUNNING){
			osRunningTcb->state = RUNNING;		
			Call_PreTaskHook();
		}
#if (CFG_SCHEDULE == PREEMPTIVE_MIXED)
		if(osTaskSchedule[osRunningTask]==PREEMPTIVE_NON){
			osDispatchLocker = 1;
		}
#endif
		  
		asm{
			ldx osRunningTcb
			lds 0,x
			pulb
			stab osppage	
			
  		    ldaa osSaveCCRH
    	         tfr a,ccrh
			rti
		}
	}
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void near EnterISR2(void){
	if(!osInSystemStack){
		asm {
			puly
		}
		if(osRunningTcb != NULL){
			asm{
				;Save PPage
			ldab osppage
				pshb
				ldx osRunningTcb
				sts 0,x
			}	
		}
		asm{
			lds osSystemStack
			pshy
		}
		osInSystemStack = TRUE;
	}
    asm
      {
       ; ldab  OsIntLevel
       ; pshb

       ; tfr ccrh,a	
       ; anda #7
       ; staa OsIntLevel
      }	
	if(osRunningTcb != NULL){
		if((*(osRunningTcb->stackBottom)) != STACK_FILL_PATTERN){
			/* TERM_WriteString("Task Stack Overflow!\n"); */
			for(;;){}
		}
	}
	
	if(osIntNest == 0){
		osSaveLevel = osLevel;
		osLevel = LEVEL_ISR;
	}
	osIntNest++;
	osDispatchLocker++;
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void near ExitISR2(void){
	osDispatchLocker--;
	osIntNest--;
	if((*(osSystemStack.bottom)) != STACK_FILL_PATTERN){
		/* TERM_WriteString("System Stack Overflow!\n"); */
		for(;;){}
	}
	if(osIntNest == 0){
		if(osRunningTask!=INVALID_TASK){
			osLevel = LEVEL_TASK;
#if (CFG_SCHEDULE != PREEMPTIVE_NON)
			if(osDispatchLocker == 0){
				if(osHighPriTask!=osRunningTask){
					Call_PostTaskHook();
					osRunningTcb->state = READY;
					asm{
						movb osHighPriTask,osRunningTask
					}	
				}
			}
#endif
#if (CFG_INTERNAL_RESOURCE_MAX>0)
			OSGetInternalResource();
#endif
			asm{			
				jmp OSSwitch2Task
			}
		}
		
		osLevel = osSaveLevel;
	}
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
__interrupt void OSDispacther(void) {
    asm
    {
    tfr ccrh,a 
    staa osSaveCCRH
    }

	if(osRunningTcb != NULL){
		asm{
		    ldab osppage
			pshb	
             ldx osRunningTcb
		    sts 0,x
		}
		if((*(osRunningTcb->stackBottom)) != STACK_FILL_PATTERN){
			/* TERM_WriteString("Task Stack Overflow!\n"); */
			for(;;){}
		}
		if(osRunningTcb->state == RUNNING){
			Call_PostTaskHook();
			osRunningTcb->state=READY;
		}
		else{
			osRunningTcb = NULL;
			osRunningTask = INVALID_TASK;
		}
	}
	if (osHighPriTask==INVALID_TASK) {
		asm{
			lds osSystemStack
		}
		osInSystemStack = TRUE;
		osDispatchLocker = 0;
		arch_enable_int();
		while(osHighPriTask==INVALID_TASK)
		{
		};
		arch_disable_int();
	}
	asm{
		movb osHighPriTask,osRunningTask
	}
#if (CFG_INTERNAL_RESOURCE_MAX>0)
	OSGetInternalResource();
#endif
	asm{
		jmp OSSwitch2Task
	}
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_16M(void)
{   
    CLKSEL=0X00;				// disengage PLL to system
    PLLCTL_PLLON=1;			// turn on PLL
    SYNR=0x00 | 0x01; 	// VCOFRQ[7:6];SYNDIV[5:0]
                        // fVCO= 2*fOSC*(SYNDIV + 1)/(REFDIV + 1)
                        // fPLL= fVCO/(2 ¡Á POSTDIV) 
                        // fBUS= fPLL/2 
                        // VCOCLK Frequency Ranges  VCOFRQ[7:6]
                        // 32MHz <= fVCO <= 48MHz    00
                        // 48MHz <  fVCO <= 80MHz    01
                        // Reserved                  10
                        // 80MHz <  fVCO <= 120MHz   11				
    REFDV=0x80 | 0x01;  // REFFRQ[7:6];REFDIV[5:0]
                        // fREF=fOSC/(REFDIV + 1)
                        // REFCLK Frequency Ranges  REFFRQ[7:6]
                        // 1MHz <= fREF <=  2MHz       00
                        // 2MHz <  fREF <=  6MHz       01
                        // 6MHz <  fREF <= 12MHz       10
                        // fREF >  12MHz               11                         
                        // pllclock=2*osc*(1+SYNR)/(1+REFDV)=32MHz;
    POSTDIV=0x00;       // 4:0, fPLL= fVCO/(2xPOSTDIV)
                        // If POSTDIV = $00 then fPLL is identical to fVCO (divide by one).
    _asm(nop);          // BUS CLOCK=16M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_32M(void)
{   
    CLKSEL=0X00;				// disengage PLL to system
    PLLCTL_PLLON=1;			// turn on PLL
    SYNR =0x40 | 0x03;  // pllclock=2*osc*(1+SYNR)/(1+REFDV)=64MHz;                      
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;  
    _asm(nop);          // BUS CLOCK=32M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_40M(void)
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x04;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=80MHz;
    _asm(nop);          //BUS CLOCK=40M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_48M(void)
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x05;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=96MHz;
    _asm(nop);          //BUS CLOCK=48M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_64M(void)
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x07;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=128MHz;
    _asm(nop);          //BUS CLOCK=64M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_80M(void)
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x09;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=160MHz;
    _asm(nop);          //BUS CLOCK=80M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_88M(void)
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x0a;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=176MHz;
    _asm(nop);          //BUS CLOCK=88M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_96M(void)
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x0b;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=192MHz;
    _asm(nop);          //BUS CLOCK=96M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_104M(void)
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x0c;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=208MHz;
    _asm(nop);          //BUS CLOCK=104M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void SetBusCLK_120M(void)
{   
    CLKSEL=0X00;				//disengage PLL to system
    PLLCTL_PLLON=1;			//turn on PLL
    SYNR =0xc0 | 0x0d;                        
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;       //pllclock=2*osc*(1+SYNR)/(1+REFDV)=240MHz;
    _asm(nop);          //BUS CLOCK=120M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	  //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		        //engage PLL to system; 
}

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
 void back_init(void) 
 {
       PLLCTL_PLLON=1;           //turn on pll  
  SYNR=23;                    
  REFDV=15;                 //pllclk=2*osc*(SYNR+1)/(REFDV+1)=2*8*24/16= 24 MHz  
  while(CRGFLG_LOCK==0);     //wait untile pll is steady  
  CLKSEL_PLLSEL=1;                 //system clocks are from PLLCLK  */   

   RTICTL=0x7f;     //RTR[6:4]=111, RTR[3:0]=1111   
  CRGFLG=0;                         
  CRGINT_RTIE=1;        //enabel Real-time-Interrupt 
 }

/******************************************************************************/
/**
 * @brief               <>
 * 
 * <> .
 * Service ID   :       <None>
 * Sync/Async   :       <Synchronous/Asynchronous>
 * Reentrancy           <Reentrant/Non Reentrant>
 * @param[in]           <None>
 * @param[out]          <None>
 * @param[in/out]       <None>
 * @return              <None>    
 */
/******************************************************************************/
void MCU_init(void)
{
     CRGINT &= (unsigned char)~18;  
     RTICTL = 0x1f;     //59-56;  51-12 ;0XFF-PASS;0x77-pass;0x70-pass and fast;
     CRGFLG = 0x80; /* Clear RTI Flag */
     CRGINT = 0x80; /* Enable RTI interrupts */
             
    SetBusCLK_16M();

    /*SCI0CR2=0x2c;*/ 	//enable Receive Full Interrupt,RX enable,Tx enable
    /*SCI0BDH=0x00;*/	//busclk  8MHz,19200bps,SCI0BDL=0x1a
    /*SCI0BDL=0x68;*/	//SCI0BDL=busclk/(16*SCI0BDL)
                  		//busclk  8MHz, 9600bps,SCI0BDL=0x34
                  		//busclk 16MHz, 9600bps,SCI0BDL=0x68
                  		//busclk 24MHz, 9600bps,SCI0BDL=0x9C
                  		//busclk 32MHz, 9600bps,SCI0BDL=0xD0
} /*MCU_init*/

/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/** <VERSION>  <DATE>  <AUTHOR>     <REVISION LOG>
 *             V1.0    20120919    ISOFT             Initial version
 */
/*=======[E N D   O F   F I L E]==============================================*/
