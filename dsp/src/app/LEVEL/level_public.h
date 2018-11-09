/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : level_public.h
* Description : public informations of the Iom module
* Author: lzx
* Date: 2018-06-08
******************************************************************************/

/* check of multiple include */
#ifndef _LEVEL_PUBLIC_H_

#define _LEVEL_PUBLIC_H_

#include "../../yd_typedefs.h"
/* Public Macros defines */


/* Public data structures defines */

#define INDEX_LEVEL_L  0x10
#define INDEX_LEVEL_H  0x1f



/* Public extern functions declare */
extern void LEVEL_Init(void);
extern void LEVEL_Process_1_16ms(void);
extern BOOL LEVEL_GetInitStatus(void);
extern float LEVEL_GetVolVaule(void);
extern u8 EVT_GetPasvolreqVaule(void);
void  EVT_SetPasvolreqVaule(u8 volume);
#endif /*_LEVEL_PUBLIC_H_*/

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
