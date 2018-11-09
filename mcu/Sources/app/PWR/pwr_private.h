/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : pwr_private.h
* Description :the private datas of the pwr module.
* Author: Xueping.Chen
* Date: 2016-12-09
******************************************************************************/

/* check of multiple include */
#ifndef _PWR_PRIVATE_H_

#define _PWR_PRIVATE_H_

#include "yd_typedefs.h"



/*private Macro defines */
#define CHECKSTATUS_PERIOD                   5000     /*自检持续时间*/
#define PWR_PROCESS_PERIOD                   20          /*处理函数周期*/
#define CHECK_PROCESS_PERIOD                100          /*自检处理函数周期*/
#define SSBLONGPRE_PROCESS_PERIOD    20          /*SSB按键长按周期*/
#define SSBLONGPRE_PERIOD_CNT        (SSBLONGPRE_PROCESS_PERIOD / PWR_PROCESS_PERIOD)
#define CHECK_PERIOD_CNT                    (CHECK_PROCESS_PERIOD / CHECK_PROCESS_PERIOD)
#define CHECKSTATUS_50MSPERIOD_MAXCOUNT (CHECKSTATUS_PERIOD / CHECK_PROCESS_PERIOD)  /*自检COUTER数*/
#define PWR_WHEEL_NUM                                   4    /*车轮的最大数量*/
#define PWR_WHEEL_THREASHOLD                  3    /*判断车停止的车轮数量门限值*/
#define PWR_VSTOP_MATRIX_NUM                    5    /*车轮停止判断矩阵表个数*/

/* Private data structures defines */


/* Private static functions declare */

static void pwr_McuWorkModeFunc(void);
static void pwr_CanWorkModeFunc(void);
static void pwr_DspWorkModeFunc(void);
  

#endif /*_PWR_PRIVATE_H_*/

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


