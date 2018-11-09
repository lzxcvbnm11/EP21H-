/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : uart_public.h
* Description : public informations of the ADM module
* Author: qq
* Date: 2018-07-02
******************************************************************************/

/* check of multiple include */
#ifndef _UART_PUBLIC_H_
#define _UART_PUBLIC_H_

/* Public Macros defines */

/* Public data structures defines */


/* Public extern functions declare */
extern void UART_Init(void);
extern BOOL UART_GetInitStatus(void);
extern void printp( char* ctrl, ...);
extern void putstr(char ch[]);
extern void uart_putchar(U8 ch);
U8 uart_getkey(void);

#endif /*_UART_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       QQ      2018-07-02      Initial
*
*===========================================================================*/

