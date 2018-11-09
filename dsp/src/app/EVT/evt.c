/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :evt.c
* Description : EVT module app
* Author: lzx
* Date: 2018-11-23
******************************************************************************/

/* Files for including */
#include "evt_info.inc"

static u8  evt_InitStatus;
static float evt_SpeechVauleFloat;
static u8  evt_EngEnableStatus;
volatile u8  evt_SpeechSelect;

volatile int evt_EngSelect = 0;


static u8  evt_ChangeEngFlag;
static u8  evt_ChangeSpeechFlag;
static u8  evt_RangValue;
static u8 EndFifo = 1;
static u32 TimeInterval = 0;

u32 Evt_flag = 2;
/***************************************************
* Function: EVT_Init
* Description: EVT module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void EVT_Init(void)
{
	vehicle_para_inst evt_Vehicle_init;
    evt_InitStatus = MDATA_GetInitStatus();
   
    evt_SpeechVauleFloat = 0.0;
    evt_RangValue = 0;
    evt_EngEnableStatus = 1;
    evt_SpeechSelect = EVT_MUTE;
    evt_EngSelect = 255;
    evt_ChangeSpeechFlag = 1;
    evt_ChangeEngFlag = 0;

    evt_Vehicle_init.spd = 5;
    ENG_init(0);
    Speech_init(EVT_MUTE);
    ESG_update(evt_Vehicle_init);
}
/***************************************************
* Function: EVT_ChangeSpeech
* Description: the process of the EVT module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void EVT_ChangeSpeech(void)
{
	volatile u8 SpeechSelect_tmp = EVT_MUTE;
	static float evt_speech = 0;
	static u8 evt_Speplaysts = 2;
	static u32 TimeCnt = 0;

	if(TimeCnt != TimeInterval)
	{
		TimeCnt++;
		return ;
	}
	else
	{
		TimeCnt = 0;
	}

	evt_Speplaysts = Evt_flag;

	/*判断播放结束*/
	if(evt_Speplaysts == INDEX_END)
	{
		SpeechSelect_tmp = MDATA_GetpassltreqVaule();

		/*play audio warning*/
		if(evt_SpeechSelect != EVT_TEST_VOICE || SpeechSelect_tmp != EVT_TEST_VOICE)
		{
			if(SpeechSelect_tmp != evt_SpeechSelect)
			{
				evt_SpeechSelect = SpeechSelect_tmp;
				Speech_init(evt_SpeechSelect);
			}
			else
			{
				/*等待下一次20ms来时更新切换标志*/
				evt_ChangeSpeechFlag = INDEX_NORMAL;
			}
		}
		else
		{
			evt_ChangeSpeechFlag = INDEX_PLAYAUDIOWARNING;
		}
	}

}
/***************************************************
* Function: Evt_SetSpeSelectMute
* Description: the process of the EVT module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void Evt_SetSpeSelectMute(void)
{
	evt_SpeechSelect = EVT_MUTE;
}

/***************************************************
* Function: EVT_ChangeEng
* Description: the process of the EVT module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void EVT_ChangeEng(void)
{
	volatile int EngSelect_tmp = 0;
	static float vehicle_spd = 0;
	static u8 evt_FifoInOrOut = 1;
	volatile float vehicle_tmp = 0;

	vehicle_para_inst  vehicle;
	vehicle.spd = 20;

	evt_EngEnableStatus = MDATA_GetPasenableSts();


/*lzx change eng source*/
	EngSelect_tmp =  MDATA_GetPasenginereqVaule();
	if( evt_EngSelect == EngSelect_tmp )
	{
		evt_EngSelect = EngSelect_tmp;
	}
	else
	{
		evt_EngSelect = EngSelect_tmp;
		ENG_init(evt_EngSelect);
	}

	/*lzx eng play enable*/
	vehicle_tmp = MDATA_GetVehspeedVaule();
	EndFifo = FIFO_GetFifoEndFlag();
//	EndFifo = 1;
	if(evt_EngEnableStatus)//if(task_EngEnableStatus == 1)
	{
		if(EndFifo == 1)
		{
			if(evt_FifoInOrOut == FIFO_INSELECT)
			{
				FIFO_SetFifoInOrOut(FIFO_IN);
				evt_FifoInOrOut = FIFO_OUT;
			}
		}
		else
		{

		}
	}
	else
	{
		if(1 == EndFifo)
		{
			if(evt_FifoInOrOut == FIFO_OUTSELECT)
			{
				FIFO_SetFifoInOrOut(FIFO_OUT);
				evt_FifoInOrOut = FIFO_IN;
				vehicle.spd = 0;
				ESG_update(vehicle);
			}
			else
			{
				vehicle_tmp = 0;
			}
		}
		else
		{
			vehicle_tmp = 0;
			vehicle_spd = 0;
		}
	}

//	if(vehicle_tmp != 0)
	{
		if(vehicle_tmp != vehicle_spd)
		{
			vehicle_spd = vehicle_tmp;
			vehicle.spd = vehicle_spd;
			ESG_update(vehicle);
		}
	}

}

/***************************************************
* Function: EVT_Process_20m
* Description: the process of the EVT module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void EVT_Process_20ms(void)
{
	if(FALSE == evt_InitStatus)
		return ;

	EVT_ChangeSpeech();
	EVT_ChangeEng();


}


/***************************************************
* Function:   EVT_GetChangeSpeFlag
* Description: get the evt_ChangeSpeechFlag flag
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
u8  EVT_GetChangeSpeFlag()
{
	return evt_ChangeSpeechFlag;
}

/***************************************************
* Function:    EVT_SetChangeSpeFlag
* Description: set the evt_ChangeSpeechFlag flag
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void EVT_SetChangeSpeFlag()
{
	evt_ChangeSpeechFlag = INDEX_WAITSELECT;
}

/***************************************************
* Function:    EVT_SetChangeEngFlag
* Description: get the evt_ChangeEngFlag flag
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void EVT_ClrEngPlayFlag(void)
{
	vehicle_para_inst vehicle;
	vehicle.spd = 0;
	ESG_update(vehicle);
}

/***************************************************
* Function:    EVT_SetChangeEngFlag
* Description: set the EVT_SetChangeEngFlag flag
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
u8 EVT_GetFifoEnableFlag()
{
	return EndFifo;
}

/***************************************************
* Function:    EVT_GetEngEablests
* Description: get the EVT_GetEngEablests flag
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
BOOL EVT_GetEngEablests()
{
	return evt_EngEnableStatus;
}
/***************************************************
* Function:  EVT_GetModuleStatus
* Description: get the EVT module initialized status
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
BOOL EVT_GetInitStatus(void)
{
    return evt_InitStatus;
}

/***************************************************
* Function:  EVT_GetPasenableVaule
* Description: get the EVT module Pasenable Vaule
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
u8  EVT_GetPasenableVaule(void)
{

    return evt_EngEnableStatus;
}
/***************************************************
* Function:  EVT_GetpassltreqVaule
* Description: get the EVT module passltreq Vaule
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
u8  EVT_GetpassltreqVaule(void)
{
    return evt_SpeechSelect;
}

/***************************************************
* Function:  EVT_GetPasenginereqVaule
* Description: get the EVT module Pasenginereq Vaule
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
u8  EVT_GetPasenginereqVaule(void)
{
    return evt_EngSelect;
}
/***************************************************
* Function:  EVT_SetSpeechTimeInterval
* Description: set speech time interval and times must Multiple of 16ms .
* The time interval is 16ms when cnt is 0
* Parameters: cnt must >= 0
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void EVT_SetSpeechTimeInterval(u32 cnt)
{
	TimeInterval = cnt;
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

