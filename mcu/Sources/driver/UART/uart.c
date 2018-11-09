/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : uart.c
* Description : ADM module middleware
* Author: qq
* Date: 2018-07-02
******************************************************************************/

/* Files for including */
#include "uart_info.inc"


#define BUSCLK_NM   16000000

#define CR_AS_CRLF  TRUE               // if true , you can use "\n" to act as CR/LF, 
								                       // if false, you have to use "\n\r",but can get a higher speed  
static U8 do_padding;
static U8 left_flag;
static U8 len;
static U8 num1;
static U8 num2;
static U8 pad_character;
static BOOL uart_InitSts;
	
/***************************************************
* Function: uart_Init
* Description: UART module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-07-02   Version:V1.0
****************************************************/
void UART_Init(void) 
{
  
	SCI0CR1 = 0x00;
	SCI0CR2 = 0x2c; 			//使能接收中断，发送与接收使能
	SCI0BD	= BUSCLK_NM/16/9600;//超频至32MHz时，总线频率为16MHz 
//	SCI0BD_IREN = 1;
	uart_InitSts = TRUE;
}
	
/***************************************************
* Function: UART_Init
* Description:	Get UART module initialized status
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:	qq		  Date:2018-07-02 	Version:V1.0
*$log: initial variables
****************************************************/
BOOL UART_GetInitStatus(void)
{
	return uart_InitSts;
}

/***************************************************
* Function: uart_getkey
* Description: 
* Parameters: none
* Returns: SCI0DRL
*
* $Create & Verlog:$
* Author:qq  Date:2018-07-02   Version:V1.0
****************************************************/
U8 uart_getkey(void)
{  
  while(!(SCI0SR1&0x80)) ; 		 //keep waiting when not empty	
  return SCI0DRL;
}

/***************************************************
* Function: uart_putchar
* Description: 
* Parameters: ch
* Returns: 
*
* $Create & Verlog:$
* Author:qq  Date:2018-07-02   Version:V1.0
****************************************************/	 
void uart_putchar(U8 ch)
{ 
 	if (ch == '\n')  
  {
  	while(!(SCI0SR1&0x80)) ;	   
  	SCI0DRL= 0x0a;					 //output'CR'
		return;
 	}
 	while(!(SCI0SR1&0x80)) ;			//keep waiting when not empty  
 	SCI0DRL=ch;
}
	 
/***************************************************
* Function: putstr
* Description: 
* Parameters:  ch[]
* Returns: 
*
* $Create & Verlog:$
* Author:qq  Date:2018-07-02   Version:V1.0
****************************************************/	 
void putstr(char ch[])
{
  U8 ptr=0;
 
  while(ch[ptr])
  {
    uart_putchar((U8)ch[ptr++]);
  } 	
}

/***************************************************
* Function: padding
* Description: 
* Parameters:  l_flag
* Returns: 
*
* $Create & Verlog:$
* Author:qq  Date:2018-07-02   Version:V1.0
****************************************************/												 
static void padding( U8 l_flag)
{
   U8 i;
 
   if (do_padding && l_flag && (len < num1))
	  for (i=len; i<num1; i++)
	  uart_putchar( pad_character);
}
 
/***************************************************
* Function: outs
* Description: 
* Parameters:  lp
* Returns: 
*
* $Create & Verlog:$
* Author:qq  Date:2018-07-02   Version:V1.0
****************************************************/	
static void outs( U8 * lp)
{
  /* pad on left if needed */
  len = strlen( lp);
  padding( !left_flag );
 
  /* Move string to the buffer */
  while ( *lp && num2--)  uart_putchar( *lp++);
 
  /* Pad on right if needed	*/
  len = strlen( lp);
  padding( left_flag );
}
 
/***************************************************
* Function: reoutnum
* Description: 
* Parameters:  num  negative  base
* Returns: 
*
* $Create & Verlog:$
* Author:qq  Date:2018-07-02   Version:V1.0
****************************************************/	 
static void reoutnum(U32 num, U8 negative, U32 base ) 
{
  U8* cp;
  U8 outbuf[32];
  U8 digits[] = "0123456789ABCDEF";
 
  /* Build number (backwards) in outbuf */
  cp = outbuf;
  do 
  {
	  *cp++ = digits[(U8)(num % base)];
	} 
	while ((num /= base) > 0);
  if (negative) 
  *cp++ = '-';
  *cp-- = 0;
 
  /* Move the converted number to the buffer and add in the padding where needed. */
  len = strlen(outbuf);
  padding( !left_flag);
  while (cp >= outbuf)
	uart_putchar( *cp--);
  padding( left_flag);
}
 
/***************************************************
* Function: reoutnum
* Description: 
* Parameters:  num  sign  base
* Returns: 
*
* $Create & Verlog:$
* Author:qq  Date:2018-07-02   Version:V1.0
****************************************************/
static void outnum(U32 num, U32 base ,U8 sign)//1, signed  0 unsigned
{	
  U8 negative;
 
  if ( (num < 0L) && sign ) 
  {  
	  negative=1;
	  num = -num;
  }
  else 
  {
    negative=0;
  }
  reoutnum( num, negative, base);	
} 

/***************************************************
* Function: getnum
* Description: 
* Parameters:  linep
* Returns: 
*
* $Create & Verlog:$
* Author:qq  Date:2018-07-02   Version:V1.0
****************************************************/ 
static int getnum(  char** linep)
{
   U8 n;
   char* cp;
 
   n = 0;
   cp = *linep;
   while (isdigit(*cp))
   { 
	   n = n*10 + ((*cp++) - '0');
   }
   *linep = cp;
   return(n);
}
 
/***************************************************
* Function: printf
* Description: 
* Parameters:  ctrl
* Returns: 
*
* $Create & Verlog:$
* Author:qq  Date:2018-07-02   Version:V1.0
****************************************************/ 	 
void printp( char* ctrl, ...)
{ 
   int long_flag;
   int dot_flag;
   char ch;
   va_list argp;
    
   va_start( argp, ctrl); 
   for ( ; *ctrl; ctrl++) 
   {  
	 	  if (*ctrl != '%')
	 	  {
		    uart_putchar(*ctrl);
#if CR_AS_CRLF == TRUE         
		    if(*ctrl=='\n') uart_putchar('\r');
#endif         
		    continue;
	 	  }
	    dot_flag = long_flag = left_flag = do_padding = 0;
	    pad_character = ' ';
	    num2=32767;  
      try_next:
	    ch = *(++ctrl);
	    if (isdigit(ch))
	    {
		    if (dot_flag)
			  num2 = getnum(&ctrl);
		    else 
		    {
			    if (ch == '0')
			    pad_character = '0'; 
		  	  num1 = getnum(&ctrl);
			    do_padding = 1;
		    }
		    ctrl--;
		    goto try_next;
	    }
	    switch (tolower(ch)) 
	    {
		    case '%':  
			    uart_putchar( '%');
			    continue;  
		    case '-':
			    left_flag = 1;
			    break;  
		    case '.':
			    dot_flag = 1;
			    break;  
		    case 'l':
			    long_flag = 1;
			    break;  
		    case 'd':
			    if (long_flag ==1 ) 
			    {
					  if(ch == 'D')				 
					  {
					    outnum( va_arg(argp, unsigned long), 10L , 0);continue;
					  }
						else  /* ch == 'd' */		
					  {
					    outnum( va_arg(argp, long), 10L,1);continue;
					  }
			    }
			    else 
			    {
					  if(ch == 'D') {outnum( va_arg(argp, unsigned int),10L,0);continue;
					}
					  else  /* ch == 'd' */		 
					{
					  outnum( va_arg(argp, int), 10L,1);
					  continue;
					}
			    }
		    case 'x':	  // X 无符号 ， x	有符号
			    if (long_flag ==1 )
			    {
				    if(ch == 'X')				 
				    {
				      outnum( va_arg(argp, unsigned long), 16L,0);
				      continue;
				    }
				    else  /* ch == 'x' */		 
				    {
				      outnum( va_arg(argp, long), 16L,1);
				      continue;
				    } 
			    }
			    else
			    {
				    if(ch == 'X')				 
					  {
					    outnum( va_arg(argp, unsigned int), 16L,0);
					    continue;
					  }
					  else  /* ch == 'x' */		 
					  {
					    outnum( va_arg(argp, int), 16L,1);
					    continue;
					  }
			    } //如果按照16进制打印，将全部按照无符号数进行
			    continue; 
		    case 's':
			    outs( va_arg( argp, char*));
			    continue;   
		    case 'c':
			    uart_putchar( va_arg( argp, int));
			    continue;  
		    default:
			    continue;
	    }
	    goto try_next;
   }
   va_end( argp );
}
	 

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       qq       2018-07-02      Initial
*
*===========================================================================*/

