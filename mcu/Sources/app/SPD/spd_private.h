/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : spd_cfg.h
* Description : 
* Author:qq
* Date: 2018-06-12
******************************************************************************/


/* check of multiple include */
#ifndef _SPD_PRIVATE_H_
#define _SPD_PRIVATE_H_

/* Macro defines */
#define SPD_PROCESS_PERIOD                  20
//#define SPD_PROCESS_PERIOD                  100
//#define SPD_VOLATE_PERIOD                   2000
#define SPEAKER_FLT_PERIOD                  500/*ms*/
#define AMPLIFIER_FLT_PERIOD                500/*ms*/

#define SPD_SPKFLT_CNT_MAX                      (SPEAKER_FLT_PERIOD/SPD_PROCESS_PERIOD)
#define SPD_AMPFLT_CNT_MAX                      (AMPLIFIER_FLT_PERIOD/SPD_PROCESS_PERIOD)
#define SPD_BatOVorUV_CNT_MAX               5

#define SPD_FLT_HIGHVOL		                637//(165*BAT_FACTOR_100MV)	/* 16.5V =645  */
#define SPD_FLT_LOWVOL                      236//(65*BAT_FACTOR_100MV)	/*6.5V =240  */
//#define STATUS_NORMAL                   0x00
//#define STATUS_AMPERROR                 0x01
//#define STATUS_SPKERROR                 0x02
//#define STATUS_BOTHERROR                0x03

typedef enum SPD_WORKSTS_Tag
{
	
	WORKSTS_ERROR = (0U),
	WORKSTS_NORMAL,
	WORKSTS_ALL
}SPD_WORKSTS_ENUM;

typedef enum SPKSystemSts_Tag
{
	STATUS_SPD_NORMAL = (0U),
	STATUS_SPD_AMPERROR,
	STATUS_SPD_SPKERROR,
	STATUS_SPD_BOTHERROR,
	STATUS_SPD_ALL
}SPKSystemSts_ENUM;

/* Private data structures defines */
static BOOL SPD_InitSts = FALSE;

static SPD_WORKSTS_ENUM SPD_SpkWrkSts = WORKSTS_NORMAL;
static SPD_WORKSTS_ENUM SPD_AmpWrkSts = WORKSTS_NORMAL;
static SPKSystemSts_ENUM SPD_SPKSystemSts = STATUS_SPD_NORMAL;

static BOOL SPD_SpkFltSts = FALSE;
static BOOL SPD_AmpFltSts = FALSE;
static BOOL SPD_OVFltSts = FALSE;
static BOOL SPD_UVFltSts = FALSE;

static void spd_SpkProcess(void);
static void spd_AmpProcess(void);
//static void spd_BatOVProcess_20ms(void);
//static void spd_BatUVProcess_20ms(void);
static void spd_BatOVAndUVProcess(void);

#endif /* _SPD_PRIVATE_H_ */

/*----------------- End of file -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0           qq           2018-06-12              Initial
*
*===========================================================================*/
