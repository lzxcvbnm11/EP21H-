/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : ostm.c
* Description : Driver source file of OSTM.
* Author: Jason.Sun
* Date: 2018-05-23
******************************************************************************/

/* Files for including */
#include "ostm_info.inc"

static BOOL ostm_InitStatus;
 U32 ostm_TickTime;

static U8 ostm_Task5MS_Count = 0;
static U8 ostm_Task10MS_Count = 0;
static U8 ostm_Task20MS_Count = 0;
static U8 ostm_Task50MS_Count = 0;
static U8 ostm_Task100MS_Count = 0;
static U8 ostm_Task200MS_Count = 0;
static U16 ostm_Task1000MS_Count = 0;
static U8 ostm_5MS_Flag;
static U8 ostm_10MS_Flag;
static U8 ostm_20MS_Flag;
static U8 ostm_50MS_Flag;
static U8 ostm_100MS_Flag;
static U8 ostm_200MS_Flag;
static U8 ostm_1000MS_Flag;

/************************************************/
static U8 ostm1_10ms_counter = 0;
static U8 ostm1_20ms_counter = 0;
static U8 ostm1_50ms_counter = 0;
static U8 ostm1_100ms_counter = 0;
static U8 ostm1_1000ms_counter = 0;
static OSTMTask_ST ostm_task[INDEX_OSTM_ALL][TASK_COUNT];

static U8 ostm_channel[OSTM_CHANNELS_COUNT] = {7};

//extern evt_TickTockType_ST evt_TickType;
/***************************************************
* Function: OSTM_Channel_Init
* Description: OSTM channel initialization
* Parameters: ChannelIndex
* Returns: none
* $Create & Verlog:$
* Author: Jason.Sun   Date:2018-05-23   Version:V1.0
****************************************************/

U8 OSTM_Channel_Init(U8 ChannelIndex)
{

    if(ChannelIndex >= OSTM_CHANNELS_COUNT)
    {
        return RET_INVALID;
    }
    else
    {

        
			TIOS |= (1 << (ostm_channel[ChannelIndex])); /*out compare mode*/
		    OCPD |= (1 << (ostm_channel[ChannelIndex])); /*Do not affect the channel port*/
           /*Set the action when occur a output compare */ 
			TIE  |= (1 << (ostm_channel[ChannelIndex]));
     }

    return RET_OK;
}

/***************************************************
* Function: OSTM_Init
* Description: OSTM drive initialization
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author: Jason.Sun   Date:2018-05-23   Version:V1.0
****************************************************/
void OSTM_Init(void)
{


   U8 i = 0;
   TSCR1_PRNT = 1; /* Enables precision timer */
   PTPSR = OSTM_PRESCALER - 1;
   for(i = 0;i < OSTM_CHANNELS_COUNT;i++)
   {
	   if(RET_OK != OSTM_Channel_Init(i))
	   {
		   return ;
	   }
   }
   TIE = 0;  /* Disable ch interrupt */
   TSCR2_TOI = 0;  /* Disable overflow interrupt */
   TSCR1_TSWAI = 1; /* Timer Module Stops While in Wait */
   TSCR1_TSFRZ = 1; /* Timer Stops While in Freeze Mode */
   TFLG1 = 0xFF;  /* Clear ioc interrupt flag */
   TFLG2_TOF = 1;  /* Clear overflow interrupt flag */
   TSCR2_TCRE =1;  /* Counter reset by a successful output compare 7*/
  // TC0 = OSTM_CHANNEL_MS; 
   TC7 = OSTM_CHANNEL_MS * 5; 
   TIE_C7I = 1;
   CPMUAPICTL_APICLK = 1;
   CPMUAPICTL_APIE =1;
   CPMUAPIR = (16000 >> 1) -1; /* 1ms interrupt*/

    ostm_TickTime = 0;

    ostm_Task5MS_Count = 0;
	ostm_Task10MS_Count = 0;
    ostm_Task20MS_Count = 0;
    ostm_Task50MS_Count = 0;
    ostm_Task100MS_Count = 0;
    ostm_Task1000MS_Count = 0;
	
    ostm_5MS_Flag = FALSE;
    ostm_10MS_Flag = FALSE;
    ostm_20MS_Flag = FALSE;
    ostm_50MS_Flag = FALSE;
    ostm_100MS_Flag = FALSE;
    ostm_1000MS_Flag = FALSE;

    ostm1_10ms_counter = 0;
    ostm1_20ms_counter = 0;
    ostm1_50ms_counter = 0;
    ostm1_100ms_counter = 0;
    ostm1_1000ms_counter = 0;

    ostm_InitStatus = TRUE;
}

void OSTM_Start(void)
{
	TSCR1_TEN = 1;	/* Enable timer to function */
	CPMUAPICTL_APIFE =1; /*Enable api timer */
}

/***************************************************
* Function: OSTM_GetInitStatus
* Description: get the OSTM module initialized status
* Parameters: none
* Returns: ostm_InitStatus
* $Create & Verlog:$
* Author: Jason.Sun   Date:2018-05-23   Version:V1.0
****************************************************/
U8 OSTM_GetInitStatus(void)
{
    return ostm_InitStatus;
}

/***************************************************
* Function: OSTM_GetTickTime
* Description:
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-23   Version:V1.0
****************************************************/
U8 OSTM_GetTickTime(PU32 time)
{
    U8 res =RET_OK;
    if (FALSE == ostm_InitStatus)
    {
        res = RET_FAIL;
    }
    else if (NULL_PTR == time)
    {
        res = RET_INVALID;
    }
    else
    {
        *time = ostm_TickTime; /*sys_ticktime 在1ms 定时中断服务中自增*/
    }
    return  res;
}
/***************************************************
* Function: OSTM_GetSysTaskFlag
* Description:
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-23   Version:V1.0
****************************************************/
U8 OSTM_GetSysTaskFlag(OSTMTaskType_ENUM ostmtask, PU8 flag)
{
    U8 res =RET_OK;
    if (FALSE == ostm_InitStatus)
    {
        res = RET_FAIL;
    }
    else if ((NULL_PTR == flag) || (INDEX_OSTM_ALL <= ostmtask))
    {
        res = RET_INVALID;
    }
    else
    {
        switch (ostmtask)
        {

            case INDEX_OSTM_5MS:
                *flag = ostm_5MS_Flag;
                break;
            case INDEX_OSTM_10MS:
                *flag = ostm_10MS_Flag;
				break;
            case INDEX_OSTM_20MS:
                *flag = ostm_20MS_Flag;
                break;
            case INDEX_OSTM_50MS:
                *flag = ostm_50MS_Flag;
                break;
            case INDEX_OSTM_100MS:
                *flag = ostm_100MS_Flag;
                break;
				
            case INDEX_OSTM_200MS:
                *flag = ostm_200MS_Flag;
                break;
            case INDEX_OSTM_1000MS:
                *flag = ostm_1000MS_Flag;
                break;
            default:
                res = RET_INVALID;
                break;
        }
    }
    return  res;
}
/***************************************************
* Function: OSTM_ClearSysTaskFlag
* Description:
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-23   Version:V1.0
****************************************************/
U8 OSTM_ClrSysTaskFlag(OSTMTaskType_ENUM ostmtask)
{
    U8 res =RET_OK;
    if (FALSE == ostm_InitStatus)
    {
        res = RET_FAIL;
    }
    else if (INDEX_OSTM_ALL <= ostmtask)
    {
        res = RET_INVALID;
    }
    else
    {
        switch (ostmtask)
        {
            case INDEX_OSTM_5MS:
                ostm_5MS_Flag = FALSE;
				break;
			case INDEX_OSTM_10MS:
                ostm_10MS_Flag = FALSE;
                break;
            case INDEX_OSTM_20MS:
                ostm_20MS_Flag = FALSE;
                break;
            case INDEX_OSTM_50MS:
                ostm_50MS_Flag = FALSE;
                break;
            case INDEX_OSTM_100MS:
                ostm_100MS_Flag = FALSE;
                break;
            case INDEX_OSTM_1000MS:
                ostm_1000MS_Flag = FALSE;
                break;
            default:
                res = RET_INVALID;
                break;
        }
    }
    return  res;
}
 /***************************************************
 * Function: OSTM_QueueTask
 * Description:
 * Parameters:	Task
 * Returns: none
 * $Create & Verlog:$
 * Author:Jason.Sun  Date:2018-05-26   Version:V1.0
 ****************************************************/

 U8 OSTM_QueueTask(OSTMTask_ST* pArray,OSTMTask_ST* pTask)
{
	U8 Index,prior,queue;
	if((pArray == NULL)||(pTask == NULL)) return RET_FAIL;
	for(Index=0;Index<TASK_COUNT;Index++)
	{
		if(pArray[Index].fOSTMTask == NULL) break; 

	}
	if(Index >= TASK_COUNT) return RET_FAIL;
	if(Index == 0) 
	{
		pArray[Index] = *pTask;
		pArray[Index].OstmTaskId = Index;
		return RET_OK;
	}
	for(prior=0;prior< Index;prior++)
	{
		if(pArray[prior].OstmTaskPrior > pTask->OstmTaskPrior) break;
	}
	for(queue= Index;queue > prior;queue--) 
	{
		pArray[queue] = pArray[queue-1];
		pArray[Index].OstmTaskId = Index;
	}
	pArray[prior] = *pTask;
	pArray[prior].OstmTaskId= prior;
	return RET_OK;
}
  /***************************************************
  * Function: OSTM_QueueTask
  * Description:
  * Parameters:  Task
  * Returns: none
  * $Create & Verlog:$
  * Author:Jason.Sun  Date:2018-05-26	Version:V1.0
  ****************************************************/
 
  U8 OSTM_DeQueueTask(OSTMTask_ST* pArray,OSTMTask_ST* pTask)
 {
	 U8 Index;
	 if((pArray == NULL)||(pTask == NULL)) return RET_FAIL;
	 for(Index=pTask->OstmTaskId;Index< TASK_COUNT -1;Index++)
	 {
		 pArray[Index] = pArray[Index+1];
		 pArray[Index].OstmTaskId = Index;
	 }
	 return RET_OK;
 }

 /***************************************************
 * Function: OSTM_RegisterTask
 * Description:
 * Parameters:	Task
 * Returns: none
 * $Create & Verlog:$
 * Author:Jason.Sun  Date:2018-05-26   Version:V1.0
 ****************************************************/

 U8 OSTM_RegisterTask(OSTMTask_ST* pTask)
{
	U8 RET = RET_FAIL;
	
    if(pTask == NULL) return RET_FAIL;
	switch (pTask->OstmTaskTick)
	{
		case INDEX_OSTM_1MS:
			RET = OSTM_QueueTask(ostm_task[INDEX_OSTM_1MS],pTask);
			break;
		case INDEX_OSTM_5MS:
			
			RET = OSTM_QueueTask(ostm_task[INDEX_OSTM_5MS],pTask);
			break;
		case INDEX_OSTM_10MS:
			
			RET = OSTM_QueueTask(ostm_task[INDEX_OSTM_10MS],pTask);
			break;
		case INDEX_OSTM_20MS:
			RET = OSTM_QueueTask(ostm_task[INDEX_OSTM_20MS],pTask);

			break;
		case INDEX_OSTM_50MS:
			RET = OSTM_QueueTask(ostm_task[INDEX_OSTM_50MS],pTask);

			break;
		case INDEX_OSTM_100MS:
			RET = OSTM_QueueTask(ostm_task[INDEX_OSTM_100MS],pTask);

			break;
		case INDEX_OSTM_200MS:
			
			RET = OSTM_QueueTask(ostm_task[INDEX_OSTM_200MS],pTask);
			break;
		case INDEX_OSTM_500MS:
			
			RET = OSTM_QueueTask(ostm_task[INDEX_OSTM_500MS],pTask);
			break;
		case INDEX_OSTM_1000MS:
			
			RET = OSTM_QueueTask(ostm_task[INDEX_OSTM_1000MS],pTask);
			break;
		default:
			break;
	}
	return RET;
}
  /***************************************************
 * Function: OSTM_UnRegisterTask
 * Description:
 * Parameters:	Task  
 * Returns: none
 * $Create & Verlog:$
 * Author:Jason.Sun  Date:2018-05-26   Version:V1.0
 ****************************************************/
 U8 OSTM_UnRegisterTask(OSTMTask_ST* pTask)
 {
	U8 RET = RET_FAIL;
	
    if(pTask == NULL) return RET_FAIL;
	switch (pTask->OstmTaskTick)
	{
		case INDEX_OSTM_1MS:
			RET = OSTM_DeQueueTask(ostm_task[INDEX_OSTM_1MS],pTask);
			break;
		case INDEX_OSTM_5MS:
			
			RET = OSTM_DeQueueTask(ostm_task[INDEX_OSTM_5MS],pTask);
			break;
		case INDEX_OSTM_10MS:
			
			RET = OSTM_DeQueueTask(ostm_task[INDEX_OSTM_10MS],pTask);
			break;
		case INDEX_OSTM_20MS:
			RET = OSTM_DeQueueTask(ostm_task[INDEX_OSTM_20MS],pTask);

			break;
		case INDEX_OSTM_50MS:
			RET = OSTM_DeQueueTask(ostm_task[INDEX_OSTM_50MS],pTask);

			break;
		case INDEX_OSTM_100MS:
			RET = OSTM_DeQueueTask(ostm_task[INDEX_OSTM_100MS],pTask);

			break;
		case INDEX_OSTM_200MS:
			
			RET = OSTM_DeQueueTask(ostm_task[INDEX_OSTM_200MS],pTask);
			break;
		case INDEX_OSTM_500MS:
			
			RET = OSTM_DeQueueTask(ostm_task[INDEX_OSTM_500MS],pTask);
			break;
		case INDEX_OSTM_1000MS:
			
			RET = OSTM_DeQueueTask(ostm_task[INDEX_OSTM_1000MS],pTask);
			break;
		default:
			break;
	}
	return RET;
}

/***************************************************
* Function: OSTM_IsrHandler
* Description: 1ms Timer Interupt Task 
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-23   Version:V1.0
****************************************************/
#pragma CODE_SEG  __NEAR_SEG NON_BANKED
//#pragma TRAP_PROC
interrupt VectorNumber_Vapi void OSTM0_IsrHandler(void)
{
	CPMUAPICTL_APIF = 1; /*clear interrupt flag */
	ostm_TickTime++;
	
	ostm_Task5MS_Count++;	
	ostm_Task10MS_Count++;
	ostm_Task20MS_Count++;
	ostm_Task50MS_Count++;
	ostm_Task100MS_Count++;
	ostm_Task200MS_Count++;
	ostm_Task1000MS_Count++;

//	if (evt_TickType.cnt !=0) 
//		evt_TickType.cnt --;


    if (TASK_5MS_CNT <= ostm_Task5MS_Count)
    {
        ostm_Task5MS_Count = 0;
        ostm_5MS_Flag = TRUE;
	    //CHM_SignalOutPutProcess_5ms();
    }
	else
	{
	}
	if (TASK_10MS_CNT <= ostm_Task10MS_Count)
    {
        ostm_Task10MS_Count = 0;
        ostm_10MS_Flag = TRUE;
	    //CHM_SignalOutPutProcess_5ms();
    }
	else
	{
	}
    if (TASK_20MS_CNT <= ostm_Task20MS_Count)
    {
        ostm_Task20MS_Count = 0;
        ostm_20MS_Flag = TRUE;
    }
	else
	{
	}
	
    if (TASK_50MS_CNT <= ostm_Task50MS_Count)
    {
        ostm_Task50MS_Count = 0;
        ostm_50MS_Flag = TRUE;
    }
    if (TASK_100MS_CNT <= ostm_Task100MS_Count)
    {
        ostm_Task100MS_Count = 0;
        ostm_100MS_Flag = TRUE;
    }
	  else
	  {
	  }
	  if (TASK_200MS_CNT <= ostm_Task200MS_Count)
    {
        ostm_Task200MS_Count = 0;
        ostm_200MS_Flag = TRUE;
    }
	  else
	  {
	  }
	
	
    if (TASK_1000MS_CNT/*TASK_1000MS_CNT*/ <= ostm_Task1000MS_Count)
    {
        ostm_Task1000MS_Count = 0;
        ostm_1000MS_Flag = TRUE;
    }
	else
	{
	}
	

}


/***************************************************
* Function: OSTM_IsrHandler
* Description: 5ms Timer Interupt Task
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-23   Version:V1.0
****************************************************/
interrupt VectorNumber_Vtimch7 void OSTM1_IsrHandler(void)
{
      U8 cansts,linsts,res;
	  TFLG1_C7F =1; /*clear interrupt flag*/
	  cansts = 0;
	  linsts = 0;
	  res= RET_OK;

    //res = BAT_GetBatFltSts(TYPE_BATDET_CAN,&cansts);
    //res = BAT_GetBatFltSts(TYPE_BATDET_LIN,&linsts);
      /*CAN RX*/
	//if(LEVEL_BAT_NORMAL == cansts)
	{
		//v_input(v_config_handle);
	}
	//else
	{
	}

/*5ms process start*************/
	COM_Process_5ms();
	NWD_Process_5ms();

//	ASS_SendNetSignal_5ms();
//	SSB_SendNetSignal_5ms();
//	CHM_SendNetSignal_5ms();
//	HSD_SendNetSignal_5ms();
/*5ms process end***************/

/*10ms process start************/
    ostm1_10ms_counter ++;
	if(OSTM1_10MS_MAXCNT <= ostm1_10ms_counter)
	{
		ostm1_10ms_counter = 0;
		//PWR_SendNetSignal_10ms();
		//CRUS_SendNetSignal_10ms();
		//TIP_SendNetSignal_10ms();
	}
	else
	{
	}

/*10ms process end***************/
	ostm1_20ms_counter ++;
	if(OSTM1_20MS_MAXCNT <= ostm1_20ms_counter)
	{	
		ostm1_20ms_counter = 0;
	}

/*50ms process start*************/
	ostm1_50ms_counter ++;
	if(OSTM1_50MS_MAXCNT <= ostm1_50ms_counter)
	{
		ostm1_50ms_counter = 0;	

		//WFM_SendNetSignal_50ms();
		//TPMS_SendUnitSignal_50ms();
		//ST_SendNetSignal_50ms();
	}
	else
	{
	}
/*50ms process end***************/

/*100ms process start************/
    ostm1_100ms_counter ++;
	if(OSTM1_100MS_MAXCNT <= ostm1_100ms_counter)
	{
		ostm1_100ms_counter = 0;
		//SCS_SendNetSignal_100ms();
		//ACC_SendNetSignal_100ms();        
		//TPMS_SendNetSignal_100ms();
		//ODO_SendNetSignal_100ms();
		//RTC_SendNetSignal_100ms();
	}
	else
	{
	}
/*100ms process end************/

/*1000ms process start*********/
	ostm1_1000ms_counter ++;
	if(OSTM1_1000MS_MAXCNT <= ostm1_1000ms_counter)
	{
		ostm1_1000ms_counter = 0;
		//FC_NetSignal_OutPut();
		//FL_NetSignal_OutPut();
		//RANG_NetSignal_OutPut();
	}
	else
	{
	}
/*1000ms process end*********/	
	
  
	/*CAN TX*/
	//if(LEVEL_BAT_NORMAL == cansts)
	{
	//	v_output(v_config_handle);	
	}
	//else
	{
	}
	
}
#pragma CODE_SEG DEFAULT

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun     2018-05-23      Initial
*
*===========================================================================*/

