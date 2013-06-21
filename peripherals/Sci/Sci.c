/*============================================================================*/
/*  Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.
 *  
 *  All rights reserved. This software is iSOFT property. Duplication 
 *  or disclosure without iSOFT written authorization is prohibited.
 *  
 *  @file       <filename>
 *  @brief      <Briefly describe file(one line)>
 *  
 *  <Compiler: XXX    MCU:XXX>
 *  
 *  @author     <author name>
 *  @date       <yyyy-mm-dd>
 */
/*============================================================================*/


/*=======[R E V I S I O N   H I S T O R Y]====================================*/
/*  <VERSION>    <DATE>    <AUTHOR>    <REVISION LOG>
 *  V1.0.0       20130427  James       Initial version
 */
/*============================================================================*/

/* MISRA-C:2004 Rule 19.1 */
/* MISRA-C:2004 Rule 3.1; REFERENCE - ISO:C90-5.2.1 Character Sets */

/*=======[V E R S I O N  I N F O R M A T I O N]===============================*/


/*=======[I N C L U D E S]====================================================*/
#include "Sci.h"


/*=======[M A C R O S]========================================================*/

/*=======[T Y P E   D E F I N I T I O N S]====================================*/

/*=======[E X T E R N A L   D A T A]==========================================*/

/*=======[I N T E R N A L   D A T A]==========================================*/
STATIC uint32 len;
STATIC uint32 left_flag;
STATIC uint32 do_padding;
STATIC uint8 pad_character;
STATIC uint32 num1;
STATIC uint32 num2;

/*=======[I N T E R N A L   F U N C T I O N   D E C L A R A T I O N S]========*/


/*=======[F U N C T I O N   I M P L E M E N T A T I O N S]====================*/

/*===========================================================================*/
/* Function Name        :Sci_Init                                            */
/* Service ID           :None                                                */
/* Description          :Initializes the module.                             */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :None                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SCI_CODE)Sci_Init(void)
{
    ESCI_A.CR2.R = 0x2000;
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Sci_SetBaudRate                                     */
/* Service ID           :None                                                */
/* Description          :Set the Sci Driver's BaudRate                       */
/* Sync/Async           :Synchronous                                         */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :Channel, BaudRate                                   */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SCI_CODE)Sci_SetBaudRate(uint8 Channel, uint32 BaudRate)
{
	STATIC uint32 clkSetting = 0;
    
    clkSetting = Mcu_GetPeripheralBusClock();
    
    ESCI_A.CR1.R =(((clkSetting/(16*BaudRate))<<16)|0x0000000c);
    
    /* Configure pad for primary func: TxDA */
    SIU.PCR[89].R = 0x400;      
    
    /* Configure pad for primary func: RxDA */
    SIU.PCR[90].R = 0x400;      
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"


/*===========================================================================*/
/* Function Name        :Sci_WriteChar                                       */
/* Service ID           :None                                                */
/* Description          :Write the uint8 data to the Sci port                */
/* Sync/Async           :None                                                */
/* Re-entrancy          :Non Reentrant                                       */
/* Parameters[in]       :Ch                                                  */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SCI_CODE)Sci_WriteChar(uint8 ch)
{
    if ('\n' == ch)  
    {
        while (ESCI_A.SR.B.TDRE == ZERO)  /* Wait for transmit data reg empty = 1 */
        {
    		/* Empty. */
        }    
        /* Clear TDRE flag */
        ESCI_A.SR.R = 0x80000000;  
            
        /* Transmit 8 bits Data */
        ESCI_A.DR.B.D = 0x0a;   
               
	    return;
    } 
    else
    {
    	/* Empty. */
    }
    
    /* Wait for transmit data reg empty = 1 */
    while (ZERO == ESCI_A.SR.B.TDRE)  
    {
    	/* Empty. */
    }       
    
    /* Clear TDRE flag */
    ESCI_A.SR.R = 0x80000000;      
    
    /* Transmit 8 bits Data */
	ESCI_A.DR.B.D = ch;            
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Sci_WriteInt16                                      */
/* Service ID           :None                                                */
/* Description          :Write the uint16 data to the Sci port               */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :val                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"

FUNC(void, SCI_CODE)Sci_WriteInt16(int16 val)
{
    Sci_WriteChar((uint8)(val>>EIGHT));
    Sci_WriteChar((uint8)val);
    
    return;
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Sci_WriteUint32                                     */
/* Service ID           :None                                                */
/* Description          :Write the uint32 data to the Sci port               */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :val                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SCI_CODE)Sci_WriteInt32(int32 val)
{
    Sci_WriteChar((uint8)(val>>24));
    Sci_WriteChar((uint8)(val>>16)); 
    Sci_WriteChar((uint8)(val>>EIGHT));
    Sci_WriteChar((uint8)val);
  
    return;
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Sci_WriteString                                     */
/* Service ID           :None                                                */
/* Description          :Write the string data to the Sci port               */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :val                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/							
#define SCI_START_SEC_CODE
#include "MemMap.h"

FUNC(void, SCI_CODE)Sci_WriteString(P2VAR(uint8, AUTOMATIC, SCI_VAR)szString) //uint8 *szString)
{
	while(*szString)
	{    
		Sci_WriteChar(*szString); 
		szString++;
	}
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :Sci_ReadByte                                        */
/* Service ID           :None                                                */
/* Description          :Read the byte data to the Sci port                  */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :val                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#if ( SCI_VERSION_INFO_API == STD_ON )
#define SCI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SCI_CODE)Sci_ReadByte(uint8 bytedata)
{
	/* Empty. */
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"
#endif 

/*===========================================================================*/
/* Function Name        :getnum                                              */
/* Service ID           :None                                                */
/* Description          :This routine gets a number from the format string   */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :val                                                 */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(int, SCI_CODE)getnum(uint8** linep)
{
   uint32 n;
   P2VAR(uint8, AUTOMATIC, SCI_VAR)cp;

   n = 0;
   cp = *linep;
   while (isdigit(*cp))
   {
       n = n*SCI_TEN + ((*cp++) - '0');
   }
     
   *linep = cp;
   return(n);
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :getnum                                              */
/* Service ID           :None                                                */
/* Description          :This routine puts pad characters into the output buffer */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :l_flag                                              */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, SCI_CODE)padding(const uint32 l_flag)
{
   uint32 i;

   if (do_padding && l_flag && (len < num1))
   {
       for (i=len; i<num1; i++)
       {
           Sci_WriteChar( pad_character);
       } 
   }
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :getnum                                              */
/* Service ID           :None                                                */
/* Description          :This routine moves a string to the output buffer    */
/* as directed by the padding and positioning flags.                         */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :lp                                                  */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, SCI_CODE)outs(P2VAR(char,AUTOMATIC, SCI_VAR)lp)
{
   /* pad on left if needed  */
   len = strlen(lp);
   padding( !left_flag);

   /* Move string to the buffer  */
   while ((*lp) && (num2--))
   {
       Sci_WriteChar( *lp++);
   }
      
   /* Pad on right if needed */
   len = strlen( lp);
   padding( left_flag);
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :reoutnum                                            */
/* Service ID           :None                                                */
/* Description          :This routine moves a string to the output buffer    */
/* as directed by the padding and positioning flags.                         */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :num,negative, base                                  */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, SCI_CODE)reoutnum(uint32 num, uint32 negative, const uint32 base ) 
{
	P2VAR(char,AUTOMATIC, SCI_VAR)cp;
	char outbuf[32];
	const uint8 digits[] = "0123456789ABCDEF";
   
	/* Build number (backwards) in outbuf */
	cp = outbuf;
   
	do 
	{
		*cp++ = digits[(int)(num % base)];
	} 
	while ((num =num / base) > ZERO);
   
	if (negative)
    {
		*cp++ = '-';
    }
      
    *cp-- = ZERO;

    /* Move the converted number to the buffer and */
    /* add in the padding where needed. */
    len = strlen(outbuf);
   
    padding( !left_flag);
   
    while (cp >= outbuf)
    {
		Sci_WriteChar( *cp--);
    }
      
    padding( left_flag);
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"

/*===========================================================================*/
/* Function Name        :outnum                                              */
/* Service ID           :None                                                */
/* Description          :This routine moves a string to the output buffer    */
/* as directed by the padding and positioning flags.                         */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :num,negative, base                                  */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                                    */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
STATIC FUNC(void, SCI_CODE)outnum(uint32 num, const uint32 base , uint8 sign) 
{  
   uint8 negative;

   if ((num < 0L) && sign) 
   {  
       negative = ONE;
       num = -num;
   }
   else 
   {
   	   negative = ZERO;
   }
  
   reoutnum(num,negative,base);  
} 
#define SCI_STOP_SEC_CODE
#include "MemMap.h"


/*===========================================================================*/
/* Function Name        :outnum                                              */
/* Service ID           :None                                                */
/* Description          :This routine moves a string to the output buffer    */
/* as directed by the padding and positioning flags.                         */
/* Sync/Async           :None                                                */
/* Re-entrancy          :None                                                */
/* Parameters[in]       :ctrl                                                */
/* Parameters[in/out]   :None                                                */
/* Parameters[out]      :None                                                */
/* Return Value         :None                                                */
/* Remarks              :                                                    */
/* Remarks              :                                     */
/*===========================================================================*/
#define SCI_START_SEC_CODE
#include "MemMap.h"
FUNC(void, SCI_CODE)printf(P2VAR(uint8,AUTOMATIC, SCI_VAR)ctrl, ...)
{
    uint32 long_flag;
    uint32 dot_flag;
    
    uint8 jump_flag1 = ONE;
    uint8 jump_flag2 = TWO;
    uint8 jump_flag3 = ONE;
    uint8 jump_flag4 = ONE;
    
    uint8 ch;
    va_list argp;

    va_start( argp, ctrl);

  
    for ( ; *ctrl; ctrl++) 
    {
		if(jump_flag4 != FOUR)
		{
		    /* move format string chars to buffer until a  */
	        /* format control is found.                    */
	        if (*ctrl != '%') 
	        {
	            Sci_WriteChar(*ctrl);
	            #if (CR_as_CRLF==TRUE)         
	            if(*ctrl=='\n') Sci_WriteChar('\r');
	            #endif         
	            continue;
	        }

	        /* initialize all the flags for this format. */
	        dot_flag = ZERO; 
	        long_flag = ZERO;
	        left_flag = ZERO;
	        do_padding = ZERO;
	        pad_character = ' ';
	        num2=32767;	
		}

	    if((jump_flag1 == ONE) || (jump_flag2 == TWO))  
	    {
	    	jump_flag3 = ONE;
	    	
	    	ch = *(++ctrl);

	        if (isdigit(ch)) 
	        {
	            if (dot_flag)
	            {
	            	num2 = getnum(&ctrl);
	            }
	            
	            else 
	            {
	                if ('0' == ch)
	                {
	                	pad_character = '0';
	                }
	                
	                num1 = getnum(&ctrl);
	                do_padding = ONE;
	            }
	            ctrl--;
	            
	            jump_flag1 = ONE;
	            jump_flag3 = THREE;
	            jump_flag4 = ONE;
	        }
	        
	        if(THREE== jump_flag3)
	        {
	        	ch = *(++ctrl);
	        }

	        switch (tolower(ch)) 
		    {
		           case '%':
		                Sci_WriteChar( '%');
		                continue;

		            case '-':
		                left_flag = ONE;
		                jump_flag4 = FOUR;
		                break;

		            case '.':
		                dot_flag = ONE;
		                jump_flag4 = FOUR;
		                break;

		            case 'l':
		                long_flag = ONE;
		                jump_flag4 = FOUR;
		                break;

		            case 'd':
		                if (ONE == long_flag) 
		                {
		              		if('D' == ch)                
		              		{
		              		    outnum((long)(va_arg(argp, unsigned long)), 10L , 0);
		              		    continue;
		              		}
		              	    else  /* ch == 'd' */        
		              	    {
		              	        outnum((long)(va_arg(argp, long)), 10L,1);
		              	        continue;
		              	    }
		                 }
		                else 
		                {
		              		if('D' == ch)                
		              		{
		              		    outnum((long)(va_arg(argp, unsigned int)),10L,0);
		              		    continue;
		              		}
		              		else  /* ch == 'd' */        
		              		{
		              		    outnum((long)(va_arg(argp, int)), 10L,1);
		              		    continue;
		              		}
		                }
		                
		            /* X unsigned, x  signed */
		            case 'x':    
		                if (ONE == long_flag)  
		                {
		              	    if('X' == ch)                
		              	    {
		              	        outnum((long)(va_arg(argp, unsigned long)), 16L,0);
		              	        continue;
		              	    }
		              	    else  /* ch == 'x' */        
		              	    {
		              	        outnum((long)(va_arg(argp, long)), 16L,1);
		              	        continue;
		              	    } 
		                }
		                else 
		                {
		              		if('X' == ch)                
		              		{
		              		    outnum((long)(va_arg(argp, unsigned int)), 16L,0);
		              		    continue;
		              		}
		              		else  /* ch == 'x' */        
		              		{
		              		    outnum((long)(va_arg(argp, int)), 16L,1);
		              	    	continue;
		              		}
		                } 
		                continue;

		            case 's':
		                outs((char*)va_arg( argp, char*));
		                continue;

		            case 'c':
		                Sci_WriteChar( (uint8)va_arg( argp, int));
		                continue;

		            default:
		                continue;	
	        }
	       jump_flag2 = TWO;
	    }
   }
   va_end( argp);
}
#define SCI_STOP_SEC_CODE
#include "MemMap.h"


/*==========================================================================*/
/*		E N D   O F   F I L E */
/*==========================================================================*/





















