/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : sys.c
* Description :the private datas of the sys module.
* Author: lzx
* Date: 2018-06-08
******************************************************************************/
/* Files for including */
#include "sys_info.inc"

static BOOL sys_InitSts = FALSE;                                /* 模块的初始化状态*/




/***************************************************
* Function: SYS_Init
* Description: the initialized of the mom module
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-12-01   Version:V1.0
****************************************************/
void SYS_Init(void)
{

    sys_InitProcess();                                   /*在STBC init 函数中开启所需的中断唤醒源*/
	sys_InitSts = TRUE;
}
#if 0
void SYS_SetInitStatus(u8  state)
{
	sys_InitSts = state;
}
u8  SYS_GetInitStatus(void)
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
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/

void SYS_ProcessManage(void)
{
	u8  i = 0;

	/*u8  sys_5MS_Flag    = FALSE;*/
	u8  sys_20MS_Flag   = FALSE;


	static u32 RangeCnt = 0;
	static BOOL enter_standbymode_flag = FALSE;



	/*sys_20MS_ret = OSTM_GetSysTaskFlag(INDEX_OSTM_20MS,&sys_20MS_Flag);*/
	//sys_20MS_Flag = TASK_Get20msValue();
                                                                                                                               /*100 ms ? Process*/
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



/***************************************************
* Function: sys_InitProcess
* Description:the initialized of the SYS
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-08   Version:V1.0
****************************************************/
void sys_InitProcess()
{
    u8  i;
    for ( i = 0 ; i < 5; i++)
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

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       lzx       2018-06-08               Initial
*
*===========================================================================*/


