/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :level.c
* Description : LEVEL module app
* Author: lzx
* Date: 2018-06-08
******************************************************************************/

/* Files for including */
#include "level_info.inc"
static float level_MixVoice;
static u8  level_InitStatus;
static float level_volumeVauleFloat;
static u8 LevelVolumRank = 16;
/***************************************************
* Function: LEVEL_Init
* Description: LEVEL module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void LEVEL_Init(void)
{
    u8  i = 0;
   level_InitStatus = MDATA_GetInitStatus();
   
   level_volumeVauleFloat = 1.0;
}

/***************************************************
* Function: LEVEL_Process_1_16ms
* Description: the process of the LEVEL module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void LEVEL_Process_1_16ms(void)
{
	u8  res = 0;
	int db = 0;
	float AmplificationFactor = 1;

    if (FALSE == level_InitStatus)
    	return ;

    level_MixVoice = Task_GetTaskVioce();


	db = LevelVolumRank;


    AmplificationFactor = LEVEL_DbToFAN(db);
    level_MixVoice = AmplificationFactor * level_MixVoice;
}

float LEVEL_DbToFAN(int db)
{
	int i = 0;
	float AmplificationFactor = 1;

	db = db - 16;

	if(db > 0)
	{
		for(i=0;i<db;i++)
		{
			AmplificationFactor = AmplificationFactor * LEVEL_VOICEDBRAISE;
		}
	}
	else if(db < 0)
	{
		if(db == -16)
		{
			return 0;
		}
		db = - db;
		for(i=0;i<db;i++)
		{
			AmplificationFactor = AmplificationFactor * LEVEL_VOICEDBDECREASE;
		}
	}
	else
	{
		AmplificationFactor = 1;
	}

	return AmplificationFactor;
}
/***************************************************
* Function:  LEVEL_GetVolVaule
* Description: get the level_volumeVauleFloat
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
float LEVEL_GetVolVaule()
{
	return level_MixVoice;
}
/***************************************************
* Function:  EVT_SetPasvolreqVaule
* Description: set the level_volumeVauleFloat
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void  EVT_SetPasvolreqVaule(u8 volume)
{
	LevelVolumRank = volume;
}

/***************************************************
* Function:  EVT_GetPasvolreqVaule
* Description: get the level_volumeVauleFloat
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
u8  EVT_GetPasvolreqVaule()
{
	return LevelVolumRank;
}

/***************************************************
* Function:  LEVEL_GetModuleStatus
* Description: get the LEVEL module initialized status
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
BOOL LEVEL_GetInitStatus(void)
{
    return level_InitStatus;
}
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

