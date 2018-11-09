/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : pwr_public.h
* Description :the public datas of the pwr module.
* Author: Xueping.Chen
* Date: 2016-12-09
******************************************************************************/

/* check of multiple include */
#ifndef _PWR_PUBLIC_H_

#define _PWR_PUBLIC_H_

#include "yd_typedefs.h"
/* Public Macros defines */

/* Public data structures defines */
typedef enum PWRMcuWorkMode_Tag
{
	PWR_MCU_WORK_MODE_START_UP = (0U), /* mcu 处于silent模式 */
	PWR_MCU_WORK_MODE_QUIET,
	PWR_MCU_WORK_MODE_SILENT, 			/* mcu 处于silent模式，只能接收，不能发送 */
	PWR_MCU_WORK_MODE_DIAG,			/* 除了诊断模式，mcu不发送can信息 */
	PWR_MCU_WORK_MODE_NORMAL,			
	PWR_MCU_WORK_MODE_WAIT_SLEEP,		/* mcu 保存信息，完成保存信息后进入sleep状态。*/	
	PWR_MCU_WORK_MODE_SLEEP,			/* mcu 处理断电流程 */
	PWR_MCU_WORK_MODE_ALL
}PWRMcuWorkMode_ENUM;

typedef enum PWRCanWorkMode_Tag
{
	PWR_CAN_WORK_MODE_NORMAL = (0U),
	PWR_CAN_WORK_MODE_PWON_LISTEN,
	PWR_CAN_WORK_MODE_STAND_BY,
	PWR_CAN_WORK_MODE_GOTO_SLEEP,
	PWR_CAN_WORK_MODE_SLEEP,
	PWR_CAN_WORK_MODE_ALL
}PWRCanWorkMode_ENUM;
	
typedef enum PWRDspWorkMode_Tag
{
	PWR_DSP_WORK_MODE_IDLE = (0U),
	PWR_DSP_WORK_MODE_OFF,	
	PWR_DSP_WORK_MODE_ON_PRE,
	PWR_DSP_WORK_MODE_ON_RESET,
	PWR_DSP_WORK_MODE_ON_SUCCESS,
	PWR_DSP_ALL
}PWRDspWorkMode_ENUM;


/* Public extern functions declare */
extern void PWR_Init(void);
extern void PWR_Process_10ms(void);
extern U8 PWR_GetPwrMode(PWRMcuWorkMode_ENUM * mcu_work_state);

#endif /*_PWR_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Xueping.Chen      2016-12-09      Initial
*
*===========================================================================*/





