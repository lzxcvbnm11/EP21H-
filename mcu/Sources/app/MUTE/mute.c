/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : mute.c
* Description : mute application
* Author: qq
* Date: 2018-6-6
******************************************************************************/


/* Files for including */
#include "mute_info.inc"

static BOOL mute_OnOffFlag = FALSE;
/***************************************************
* Function: MUTE_Init
* Description: MUTE module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:    qq   Date:2018-6-6     Version:V1.0
*$log: initial variables
****************************************************/
void MUTE_Init(void)
{
  U8 res;
  
  MUTE_InitSts = FALSE;
  MUTE_PowerOnSts = FALSE;
  MUTE_SleepSts = FALSE;
  MUTE_AMPOCSC_PedestrianAlertInhibitSts = FALSE;
  MUTE_OnOff(MUTE_ON); /* power on mute */
  MUTE_InitSts = IOM_GetInitStatus();
}

/***************************************************  
* Function: MUTE_GetInitSts
* Description: Get MUTE module initialized status
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:    qq   Date:2018-6-6     Version:V1.0
*$log: initial variables
****************************************************/
U8 MUTE_GetInitStatus(void)
{
  return MUTE_InitSts;
}


U8 mute_GetEvtJudge(void)
{
	U8 res;
	static U8 ShoutFlag = 0;
	static U8 KeepNetStateCnt = 30;
	v_nwm_state nwm_state;
	
	U8 mute_OnOff = MUTE_OFF;
	
	PWRMcuWorkMode_ENUM PowerOnCurrentSts;
	
	res = PWR_GetPwrMode(&PowerOnCurrentSts);
	
	if(res == RET_OK)
	{
		if((PowerOnCurrentSts != PWR_MCU_WORK_MODE_NORMAL) || (DS_GetComsts() == FALSE))
		{
			mute_OnOff = MUTE_ON;
		}
	}
	
	nwm_state = COM_GetNwmState();
	if(V_NWM_NORMAL != nwm_state)
	{	
		//mute_OnOff = MUTE_ON;
		ShoutFlag = 1;
	}
	
	if(SPD_PACMFltSts() == TRUE)
	{
		mute_OnOff = MUTE_ON;
	}
	
	if(BAT_GetBatVoltageSts() > STATUS_BAT_CLASSA_CAN)
	{
		mute_OnOff = MUTE_ON;
	}
	
	return mute_OnOff;
}



/***************************************************
* Function: MUTE_Process_20ms
* Description: Enable MUTE or Disable MUTE
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:    qq   Date:2018-6-6     Version:V1.0
*$log: initial variables
****************************************************/
void MUTE_Process_20ms(void) 
{   
    if (TRUE == MUTE_InitSts)
    {
   		if(mute_GetEvtJudge() == MUTE_ON)
   		{
			if(mute_OnOffFlag == FALSE)
			{
				MUTE_OnOff(MUTE_ON);
			}
		}
		else
		{
			if(mute_OnOffFlag == TRUE)
			{
				MUTE_OnOff(MUTE_OFF);
			}

		}
    }
    else
    {                                                   
    }
}

void MUTE_OnOff(U8 OnOff)
{
	if(OnOff)
	{
		IOM_SetOutPutLevel(INDEX_IOM_MUTE, MUTEENABLE);
		mute_OnOffFlag = TRUE;
	}
	else
	{
		IOM_SetOutPutLevel(INDEX_IOM_MUTE, MUTEDISABLE);
		mute_OnOffFlag = FALSE;
	}
}

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0            qq             2018-6-6               Initial
*===========================================================================*/

