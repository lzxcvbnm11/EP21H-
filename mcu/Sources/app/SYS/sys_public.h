/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : sys_public.h
* Description :the public datas of the sys module.
* Author: Jianjun.He
* Date: 2016-12-09
******************************************************************************/

/* check of multiple include */
#ifndef _SYS_PUBLIC_H_

#define _SYS_PUBLIC_H_
#include "yd_typedefs.h"


/* Public extern functions declare */
extern void SYS_Init(void);
extern void SYS_ProcessManage(void);
extern BOOL SYS_GetNormalWorkMode(void);
//extern void SYS_SetInitStatus(U8 state);
//extern U8 SYS_GetInitStatus(void);
#endif /*_SYS_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jianjun.He      2016-12-09                Initial
*
*===========================================================================*/

