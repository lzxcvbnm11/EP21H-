/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :mute_public.h
* Description : public data of the MUTE
* Author: qq
* Date: 2018-6-6
******************************************************************************/
/* check of multiple include */
#ifndef _MUTE_PUBLIC_H_

#define _MUTE_PUBLIC_H_

#include "yd_typedefs.h"

/* Public Macros defines */
#if 0
typedef  enum  MuteNum_Tag
{
    INDEX_MUTE_OPENAMP = (0u),         /* 开机功放mute */
    INDEX_MUTE_SLEEP,                  /* 休眠mute */
    INDEX_MUTE_AMPOCSC,                /* 功放开路短路mute */
    INDEX_MUTE_CUEFAIL,                /* 提示音失效mute */
    INDEX_MUTE_DISABLE,                /* 解mute处理 */
    INDEX_MUTE_ALL
}MuteNum_ENUM;
#endif

#define MUTE_ON   	1
#define MUTE_OFF	0

/* Public extern functions declare */
extern void MUTE_Init(void);
extern BOOL MUTE_GetInitStatus(void);
extern void MUTE_Process_20ms(void);
extern void MUTE_OnOff(U8 OnOff);

#endif /*_MUTE_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0           qq              2018-6-6              Initial
*===========================================================================*/

