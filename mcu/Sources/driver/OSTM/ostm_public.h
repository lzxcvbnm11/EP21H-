/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :ostm_public.h
* Description : public data of the Ostm
* Author: Jason.Sun
* Date: 2018-05-23
******************************************************************************/

/* check of multiple include */
#ifndef _OSTM_PUBLIC_H_
#define _OSTM_PUBLIC_H_
#include "yd_typedefs.h"

/* Public Macros defines */


/* Public data structures defines */
typedef enum OSTMTaskType_Tag
{
    INDEX_OSTM_1MS = (0u),
    INDEX_OSTM_5MS,
    INDEX_OSTM_10MS,
    INDEX_OSTM_20MS,
    INDEX_OSTM_50MS,
    INDEX_OSTM_100MS,
    INDEX_OSTM_200MS,
    INDEX_OSTM_500MS,
    INDEX_OSTM_1000MS,
    INDEX_OSTM_5000MS,
    INDEX_OSTM_ALL
}OSTMTaskType_ENUM;

typedef struct OSTMTask_Tag
{
	void (*fOSTMTask)(void);
	OSTMTaskType_ENUM OstmTaskTick;
	U8 OstmTaskPrior;
	U8 OstmTaskId;
}OSTMTask_ST;


/* Public extern functions declare */
extern void OSTM_Init(void);
extern void OSTM0_IsrHandler(void);
extern void OSTM1_IsrHandler(void);
extern void OSTM_Start(void);
extern U8 OSTM_GetInitStatus(void);
extern U8 OSTM_GetTickTime(PU32 time);
extern U8 OSTM_GetSysTaskFlag(OSTMTaskType_ENUM ostmtask, PU8 flag);
extern U8 OSTM_ClrSysTaskFlag(OSTMTaskType_ENUM ostmtask);
extern U8 OSTM_RegisterTask(OSTMTask_ST* pTask);
extern U8 OSTM_UnRegisterTask(OSTMTask_ST* pTask);

#endif /*_OSTM_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun    2018-05-23      Initial
*
*===========================================================================*/

