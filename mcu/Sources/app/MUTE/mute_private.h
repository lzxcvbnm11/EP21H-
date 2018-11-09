/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : mute_private.h
* Description : the private datas of the mute
* Author: qq
* Date: 2018-06-06
******************************************************************************/

/* check of multiple include */
#ifndef _MUTE_PRIVATE_H_

#define _MUTE_PRIVATE_H_

/* Private data structures defines */
#define TRUE                       1
#define FALSE                      0

#define MUTEENABLE                 1
#define MUTEDISABLE                0

#define MUTE_PROCESS_PERIOD                   20
#define MUTE_VOLATE_PERIOD                    200
#define MUTE_CNT_MAX               (MUTE_VOLATE_PERIOD/MUTE_PROCESS_PERIOD)

/* Private static functions declare */
static BOOL MUTE_InitSts = FALSE;

static BOOL MUTE_PowerOnSts = FALSE;
static BOOL MUTE_SleepSts = FALSE;
static BOOL MUTE_AMPOCSC_PedestrianAlertInhibitSts = FALSE;
static BOOL MUTE_SystemPowerSts = FALSE;

static void mute_PowerOnProcess_20ms(void);
static void	mute_SleepProcess_20ms(void);
static void mute_AMPOCSC_PedestrianAlertInhibitProcess_20ms(void);
static void mute_SystemPowerProcess_20ms(void);

#endif /*_MUTE_PRIVATE_H_*/

/*------------------end of file----------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0            qq              2018-6-6              Initial
												according TO Hardware REQUIREMENT
*===========================================================================*/

