/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : acc_private.h
* Description : the private datas of the Acc
* Author: Xiaojie.Zheng
* Date: 2016-12-06
******************************************************************************/

/* check of multiple include */
#ifndef _ACC_PRIVATE_H_
#define _ACC_PRIVATE_H_
#include "yd_typedefs.h"
#include "acc_public.h"

/* Macro defines */

/* Private data structures defines */


/*网络事件索引及对应的索引事件*/
/* Private static functions declare */


static void acc_PedtrnAlrtJudge_10ms(void);
static void acc_PedtrnAdoWrnngJudge_10ms(void);
static void acc_RstrFctryDeftsJudge_10ms(void);
static void acc_ResetPara(void);


#endif /*_ACC_PRIVATE_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0      Xiaojie.Zheng      2016-12-06     Initial
*
*===========================================================================*/

