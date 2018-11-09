/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :level_private.h
* Description : the private informations  of the Iom module
* Author: lzx
* Date: 2018-06-08
******************************************************************************/

/* check of multiple include */
#ifndef _LEVEL_PRIVATE_H_

#define _LEVEL_PRIVATE_H_

#include "../../yd_typedefs.h"


/* Macro defines */
#define LEVEL_VOICEDBRAISE 1.122018454301
#define LEVEL_VOICEDBDECREASE 0.891250938
#define LEVEL_VOICE_MAX 1.5
#define LEVEL_VOICE_MIN -1.5

#define LEVEL_VOICE_RANK_H  0
#define LEVEL_VOICE_RANK_L -4
/* Private data structures defines */
typedef enum LEVELDBDATA_TAG
{
	LEVEL1 = 0,
	LEVEL2,
	LEVEL3,
	LEVEL4,
	LEVEL5,
	LEVEL6,
	LEVEL7,
	LEVEL8,
	LEVEL9,
	LEVEL10,
	LEVEL11,
	LEVEL12,
	LEVEL13,
	LEVEL14,
	LEVEL15,
	LEVEL16,
	LEVEL17,
	LEVEL18,
	LEVEL19,
	LEVEL20,
	LEVEL21,
	LEVEL22,
	LEVEL23,
	LEVEL24,
	LEVEL25,
	LEVEL26,
	LEVEL27,
	LEVEL28,
	LEVEL29,
	LEVEL30,
	LEVEL31,
	LEVEL32,
}LEVELDBDATA_MNUM;

static float LEVEL_FAN[] ={
		0.158489319,

		0.254797070,
		0.398088606,
		0.446662763,
		0.501163863,
		0.562315103,
		0.630927923,
		0.707945784,
		0.794328234,
		0.891250938,
};

/*constant define*/

float LEVEL_DbToFAN(int db);
/* Private static functions declare */


#endif /*_LEVEL_PRIVATE_H_*/

/*------------------end of file----------------------------*/

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
*===========================================================================*/

