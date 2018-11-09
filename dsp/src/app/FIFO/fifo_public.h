/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : fifo_public.h
* Description : public informations of the Iom module
* Author: lzx
* Date: 2018-06-08
******************************************************************************/

/* check of multiple include */
#ifndef _FIFO_PUBLIC_H_

#define _FIFO_PUBLIC_H_

#include "../../yd_typedefs.h"
/* Public Macros defines */
#define FIFO_TIME_VAULE 500
#define FIFO_IN 0
#define FIFO_OUT 1
#define FIFO_OUTSELECT 1
#define FIFO_INSELECT 0

/* Public data structures defines */


/* Public extern functions declare */
extern void FIFO_Init(void);
extern void FIFO_Process_1_16ms(void);
extern BOOL FIFO_GetInitStatus(void);
extern float FIFO_GetVolVaule(float fifo_VoiceVauleFloat,u32 *flag);
extern void FIFO_SetFifoInOrOut(u8 fifo_direction);
extern u8 FIFO_GetFifoEndFlag(void);
#endif /*_FIFO_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       lzx      2018-06-08      Initial
*
===========================================================================*/
