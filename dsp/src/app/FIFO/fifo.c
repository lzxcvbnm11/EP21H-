/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :fifo.c
* Description : FIFO module app
* Author: lzx
* Date: 2018-06-08
******************************************************************************/

/* Files for including */
#include "fifo_info.inc"

static u8 fifo_InitStatus;
static u8 fifo_OutOrIn;
static u8 fifo_End;
extern float task_EngVoice;
static int TestFifoCnt = 0;
static float FifoInvalue = 1;
static float FifoOutvalue = FIFO_RANG_MAX;
static u8 Fifo_EngMuteFlag = 0;
/***************************************************
* Function: FIFO_Init
* Description: FIFO module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void FIFO_Init(void)
{
   fifo_InitStatus = MDATA_GetInitStatus();
   
   fifo_End = 1;
}

/***************************************************
* Function: FIFO_FifoIn
* Description: the process of the FIFO module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void FIFO_FifoIn()
{

	float VoiceVauleTmp = FIFO_RANG_UNIT;

	FifoInvalue += 1;

	VoiceVauleTmp = task_EngVoice;
	VoiceVauleTmp = task_EngVoice*FifoInvalue;
	VoiceVauleTmp = VoiceVauleTmp * FIFO_RANG_UNIT;
	task_EngVoice = VoiceVauleTmp;

	if(FifoInvalue >= FIFO_RANG_MAX)
	{
		fifo_End = 1;
		FifoInvalue = 1;
	}

}
/***************************************************
* Function: FIFO_Process_1_16ms
* Description: the process of the FIFO module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
/***************************************************
* Function: FIFO_FifoOut
* Description: the process of the FIFO module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void FIFO_FifoOut()
{

	float VoiceVauleTmp = FIFO_RANG_UNIT;


	FifoOutvalue -= 1;

	if(Fifo_EngMuteFlag == 1 )
	{
		if( FifoOutvalue == 1)
		{
			fifo_End = 1;
			Fifo_EngMuteFlag = 0;
			FifoOutvalue = FIFO_RANG_MAX;
		}
		task_EngVoice = 0;
		return ;
	}


	VoiceVauleTmp = task_EngVoice;
	VoiceVauleTmp = task_EngVoice*FifoOutvalue;
	VoiceVauleTmp = VoiceVauleTmp * FIFO_RANG_UNIT;
	task_EngVoice = VoiceVauleTmp;

	if(FifoOutvalue <= 1)
	{
		EVT_ClrEngPlayFlag();
		FifoOutvalue = FIFO_LIBCOMPENSATE;
		Fifo_EngMuteFlag = 1;
	}
}
void FIFO_Process_1_16ms(void)
{

	static int cnt = 0;

	if(fifo_InitStatus == FALSE)
		return;

	if(fifo_End)
	{
		return;
	}

	if(fifo_OutOrIn == FIFO_OUT)
	{
		FIFO_FifoOut();
	}
	else if(fifo_OutOrIn == FIFO_IN)
	{
		FIFO_FifoIn();
	}


}

/***************************************************
* Function:  FIFO_GetVolVaule
* Description: get the FIFO_GetVolVaule
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
float FIFO_GetVolVaule(float fifo_VoiceVauleFloat,u32 *flag)
{
	return fifo_VoiceVauleFloat;
}

/***************************************************
* Function:  FIFO_GetFifoEndFlag
* Description: get the fifo_End
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
u8  FIFO_GetFifoEndFlag()
{
	return fifo_End;
}
/***************************************************
* Function:  FIFO_SetFifoInOrOut
* Description: set the SetFifoInOrOut
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void FIFO_SetFifoInOrOut(u8  fifo_direction)
{
	fifo_OutOrIn = fifo_direction;
	fifo_End = 0;
	FifoInvalue = 1;
	Fifo_EngMuteFlag = 0;
	FifoOutvalue = FIFO_RANG_MAX;
}

/***************************************************
* Function:  FIFO_GetInitStatus
* Description: get the FIFO module initialized status
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
BOOL FIFO_GetInitStatus(void)
{
    return fifo_InitStatus;
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

