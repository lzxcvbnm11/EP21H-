/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : evt_public.h
* Description : public informations of the Evt module
* Author: lzx
* Date: 2018-06-08
******************************************************************************/

/* check of multiple include */
#ifndef _EVT_PUBLIC_H_

#define _EVT_PUBLIC_H_

#include "../../yd_typedefs.h"
/* Public Macros defines */
#define EVT_TIME_VAULE 500
#define EVT_PLAYTEST 10
#define EVT_PLAYING 1
#define EVT_PAUSE 0
#define EVT_MUTE 11
#define EVT_TEST_VOICE 10
/* Public data structures defines */
typedef enum EvtPlaysts_Tag
{
	INDEX_ERROR = (0u),
	INDEX_START,
	INDEX_END,
	INDEX_MINDLLE
}EvtPlaysts_ENUM;

typedef enum EvtPlaySelect_Tag
{
	INDEX_NORMAL = (0u),
	INDEX_PLAYAUDIOWARNING,
	INDEX_WAITSELECT,
}EvtPlaySelect_ENUM;

/* Public extern functions declare */
extern void EVT_Init(void);
extern void EVT_Process_20ms(void);
extern BOOL EVT_GetInitStatus(void);
extern BOOL EVT_GetEngEablests(void);
extern void EVT_SetChangeSpeFlag(void);
extern u8 EVT_GetFifoEnableFlag(void);
extern u8 EVT_GetChangeSpeFlag(void);
extern u8 EVT_GetPasenableVaule(void);
extern u8 EVT_GetpassltreqVaule(void);
extern u8 EVT_GetPasenginereqVaule(void);
extern void EVT_SetSpeechTimeInterval(u32 cnt);
void EVT_ClrEngPlayFlag(void);
void Evt_SetSpeSelectMute(void);
#endif /*_EVT_PUBLIC_H_*/

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
