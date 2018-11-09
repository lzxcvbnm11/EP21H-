/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : sys.c
* Description :the private datas of the sys module.
* Author: Jianjun.He
* Date: 2016-12-09
******************************************************************************/
/* Files for including */
#include "sys_info.inc"


static U8 sys_WorkModeSts;                                        /* RUN  STANDBY  DEEPSTOP 三种工作模式*/
static BOOL sys_InitSts = FALSE;                                /* 模块的初始化状态*/




/***************************************************
* Function: SYS_Init
* Description: the initialized of the mom module
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Jianjun.He  Date:2016-12-01   Version:V1.0
****************************************************/
void SYS_Init(void)
{
    sys_WorkModeSts =STATUS_SYS_RUN;
    sys_InitProcess();                                   /*在STBC init 函数中开启所需的中断唤醒源*/
	sys_InitSts = TRUE;
}
#if 0
void SYS_SetInitStatus(U8 state)
{
	sys_InitSts = state;
}
U8 SYS_GetInitStatus(void)
{
	return sys_InitSts;
}
#endif
/***************************************************
* Function: SYS_ProcessManage
* Description: the process of the SYS module
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Jianjun.He  Date:2016-12-09   Version:V1.0
****************************************************/
//extern void RANG_OutputBeforeSleep(void);
void SYS_ProcessManage(void)
{
	U8 i = 0;
	/*U8 pwrSts = PWR_OFF;*/

	U8 sys_5MS_Flag    = FALSE;	
	U8 sys_10MS_Flag   = FALSE;
	U8 sys_20MS_Flag   = FALSE;
	U8 sys_50MS_Flag   = FALSE;
	U8 sys_100MS_Flag  = FALSE;
	U8 sys_200MS_Flag  = FALSE;
	U8 sys_1000MS_Flag = FALSE;

	BOOL sys_5MS_ret    = FALSE;	
	BOOL sys_10MS_ret   = FALSE;
	BOOL sys_20MS_ret   = FALSE;
	BOOL sys_50MS_ret   = FALSE;
	BOOL sys_100MS_ret  = FALSE;
	BOOL sys_200MS_ret  = FALSE;
	BOOL sys_1000MS_ret = FALSE;

	static U32 RangeCnt = 0;
	static BOOL enter_standbymode_flag = FALSE;
	/*EedWorkStatus_ENUM eedsts = STATUS_EED_UNKNOWN;*/

	sys_5MS_ret 	= OSTM_GetSysTaskFlag(INDEX_OSTM_5MS,&sys_5MS_Flag);	
	sys_10MS_ret 	= OSTM_GetSysTaskFlag(INDEX_OSTM_10MS,&sys_10MS_Flag);
	sys_20MS_ret 	= OSTM_GetSysTaskFlag(INDEX_OSTM_20MS,&sys_20MS_Flag);
	sys_50MS_ret 	= OSTM_GetSysTaskFlag(INDEX_OSTM_50MS,&sys_50MS_Flag);
	sys_100MS_ret 	= OSTM_GetSysTaskFlag(INDEX_OSTM_100MS,&sys_100MS_Flag);
	sys_200MS_ret 	= OSTM_GetSysTaskFlag(INDEX_OSTM_200MS,&sys_200MS_Flag);
	sys_1000MS_ret 	= OSTM_GetSysTaskFlag(INDEX_OSTM_1000MS,&sys_1000MS_Flag);

	if ((RET_OK == sys_5MS_ret) && (TRUE == sys_5MS_Flag))
	{                                                                                                                                /*100 ms ? Process*/
		if (RET_OK == OSTM_ClrSysTaskFlag(INDEX_OSTM_5MS))  /*??BASETIME_25MS */
		{
			/*do nothing*/
		}
		else
		{
			/*do nothing*/
		}

		for ( i = 0 ; i < INDEX_SYS5MSPROCESS_ALL ; i++)
		{
			if (NULL_PTR != SysProc5ms_Tabl[i])
			{
			    SysProc5ms_Tabl[i]();
			}
			else
			{
			}
		}
	}
	else
	{
	}
	if ((RET_OK == sys_10MS_ret) && (TRUE == sys_10MS_Flag))
	{                                                                                                                                /*100 ms ? Process*/
		if (RET_OK == OSTM_ClrSysTaskFlag(INDEX_OSTM_10MS))  /*??BASETIME_25MS */
		{
			/*do nothing*/
		}
		else
		{
			/*do nothing*/
		}

		for ( i = 0 ; i < INDEX_SYS10MSPROCESS_ALL ; i++)
		{
			if (NULL_PTR != SysProc10ms_Tabl[i])
			{
			    SysProc10ms_Tabl[i]();
			}
			else
			{
			}
		}
	}
	else
	{
	}
	
    if ((RET_OK == sys_20MS_ret) && (TRUE == sys_20MS_Flag))
    {                                                                                                                                /*100 ms ? Process*/
        if (RET_OK == OSTM_ClrSysTaskFlag(INDEX_OSTM_20MS))  /*??BASETIME_25MS */
        {
           	/*do nothing*/
    	}
     	else
		{
		 	/*do nothing*/
		}
		
        for ( i = 0 ; i < INDEX_SYS20MSPROCESS_ALL ; i++)
        {
            if (NULL_PTR != SysProc20ms_Tabl[i])
            {
                SysProc20ms_Tabl[i]();
            }
			else
			{
			}
        }
	
    }
	else
	{
	}
	
    if ((RET_OK == sys_50MS_ret) && (TRUE == sys_50MS_Flag))
    {                                                                                                                                /*100 ms ? Process*/
        if (RET_OK == OSTM_ClrSysTaskFlag(INDEX_OSTM_50MS))  /*??BASETIME_25MS */
        {
           	/*do nothing*/
    	}
     	else
		{
		 	/*do nothing*/
		}

        for ( i = 0 ; i < INDEX_SYS50MSPROCESS_ALL ; i++)
        {
            if (NULL_PTR != SysProc50ms_Tabl[i])
            {
                SysProc50ms_Tabl[i]();
            }
			else
			{
			}
        }

    }
	else
	{
	}

    if ((RET_OK == sys_100MS_ret) && (TRUE == sys_100MS_Flag))
    {                                                                                                                             /*50 ms ? Process*/
        if (RET_OK == OSTM_ClrSysTaskFlag(INDEX_OSTM_100MS))
		{
           	/*do nothing*/
    	}
     	else
		{
		 	/*do nothing*/
		}

        for ( i = 0 ; i < INDEX_SYS100MSPROCESS_ALL ; i++)
        {
            if (NULL_PTR != SysProc100ms_Tabl[i])
            {
                SysProc100ms_Tabl[i]();
            }
		 	else
		    {
		        /*do nothing*/
		    }
        }

		
	#if 1
		
			if (FALSE != COM_GetNetWorkSleepSts())
			{
				sys_Process_BeforeDeepSleep();	
			
				/*
				if (RET_OK == EED_GetEEPROMStatus(&eedsts))
				{
				
					if ( STATUS_EED_IDLE == eedsts )			
					{
						RangeCnt++;
						if(RangeCnt >= 0x2)
						{
							RangeCnt = 0;
							STBC_EnterDeepStop();
						}
						else
						{
						}
					
					}
					else
					{
					}
				}
				else
				{
				}
				*/
			}
			else
			{
				/*do nothing*/
			}
		
	#endif
		
    }
	else
	{
	}

	 if ((RET_OK == sys_200MS_ret) && (TRUE == sys_200MS_Flag))
    {                                                                                                                             /*50 ms ? Process*/
        if (RET_OK == OSTM_ClrSysTaskFlag(INDEX_OSTM_200MS))
		{
           	/*do nothing*/
    	}
     	else
		{
		 	/*do nothing*/
		}
		#if 0
        for ( i = 0 ; i < INDEX_SYS200MSPROCESS_ALL ; i++)
        {
            if (NULL_PTR != SysProc200ms_Tabl[i])
            {
                SysProc200ms_Tabl[i]();
            }
		 	else
		    {
		        /*do nothing*/
		    }
        }
		#endif
    }
	else
	{
	}
	

    if ((RET_OK == sys_1000MS_ret) && (TRUE == sys_1000MS_Flag))
    {
		if (RET_OK == OSTM_ClrSysTaskFlag(INDEX_OSTM_1000MS))
		{
		}
		else
		{
		/*do nothing*/
		}
		#if 0
        for ( i = 0 ; i < INDEX_SYS1000MSPROCESS_ALL ; i++)
        {
            if (NULL_PTR != SysProc1000ms_Tabl[i])
            {
                SysProc1000ms_Tabl[i]();
            }
		  	else
	        {
	            /*do nothing*/
	        }
        }		         
		#endif
	#if 0

		if (FALSE != COM_GetNetWorkSleepSts())
		{
		    sys_Process_BeforeDeepSleep();  
		
			
			if (RET_OK == EED_GetEEPROMStatus(&eedsts))
			{
			
				if ( STATUS_EED_IDLE == eedsts )			
				{
					//RangeCnt++;
					//if(RangeCnt >= 0x2)
					//{
						RangeCnt = 0;
						STBC_EnterDeepStop();
					//}
					//else
					//{
					//}
				
				}
				else
				{
				}
			}
			else
			{
			}
		}
		else
		{
			/*do nothing*/
		}

	#endif
 	}
	else
	{
	}

}

/***************************************************
* Function: SYS_GetNormalWorkMode
* Description: Whether the  system in normal  mode
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:liuyingying  Date:2017-07-05   Version:V2.0
****************************************************/
BOOL SYS_GetNormalWorkMode(void)
{
    if(STATUS_SYS_RUN == sys_WorkModeSts)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/***************************************************
* Function: sys_InitProcess
* Description:the initialized of the SYS
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Jianjun.He  Date:2016-12-09   Version:V1.0
****************************************************/
static void sys_InitProcess(void)
{
    U8 i;
    for ( i = 0 ; i < INDEX_SYSINIT_ALL; i++)
    {
        if (NULL_PTR != SysInit_Tabl[i])
        {
            SysInit_Tabl[i]();            /*调用所有的初始化函数*/
        }
        else
        {
            /* do nothing */  
        }
    }
}

static void sys_Process_BeforeDeepSleep(void)
{
    // RANG_OutputBeforeSleep();
}

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jianjun.He       2016-12-09               Initial
*
*===========================================================================*/


