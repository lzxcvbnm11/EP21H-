/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : sys_private.h
* Description :the private datas of the sys module.
* Author: lzx
* Date: 2018-06-08
******************************************************************************/

/* check of multiple include */
#ifndef _SYS_PRIVATE_H_

#define _SYS_PRIVATE_H_
#include "../../yd_typedefs.h"
#include "../EVT/evt_public.h"
#include "../FIFO/fifo_public.h"
#include "../LEVEL/level_public.h"
#include "../MDATA/mdata_public.h"
//#include "../SWL/swl_public.h"
#include "../../middleware/MCOM/mcom_public.h"

/*private Macro defines */
#define SYS_DELAYTIME_5S              5000
#define TASK_PROCESS_PERIOD    100
#define TASK_PROCESS_5MS            5
#define TASK_PROCESS_10MS          10
#define TASK_PROCESS_20MS          20
#define TASK_PROCESS_50MS          50
#define TASK_PROCESS_100MS         100
#define TASK_PROCESS_200MS         200
#define TASK_PROCESS_1000MS       1000

#define  BASETIME_15MS                      15              /* 时间偏移基准*/
#define  BASETIME_25MS                      25
#define  BASETIME_35MS                      35

#define TASK20MS_MAX     9  /*5ms的任务数*/


/* Private data structures defines */
typedef  void(*InitType)(void);           /*定义初始化类型的函数指针*/
typedef  void(*Proc5msType)(void);       /*定义5ms process的函数指针类型*/
typedef  void(*Proc10msType)(void);     /*定义10ms process的函数指针类型*/
typedef  void(*Proc20msType)(void);     /*定义20ms process的函数指针类型*/
typedef  void(*Proc50msType)(void);     /*定义50ms process的函数指针类型*/
typedef  void(*Proc100msType)(void);   /*定义100ms process的函数指针类型*/
typedef  void(*Proc200msType)(void);   /*定义100ms process的函数指针类型*/
typedef  void(*Proc1000msType)(void);   /*定义1000ms process的函数指针类型*/



typedef enum SysInitProcess_Tag
{
	//INDEX_IIS_INIT = (0u),
   // INDEX_SPI_INIT,
   // INDEX_SPIB_INIT,
  //  INDEX_TIMER_INIT,
	INDEX_MCOM_INIT,
    INDEX_MDATA_INIT,
    INDEX_EVT_INIT,
    INDEX_FIFO_INIT,
    INDEX_LEVEL_INIT,

	/*wait for */
    INDEX_SYSINIT_ALL
}SysInitProcess_ENUM;


static const  InitType SysInit_Tabl[INDEX_SYSINIT_ALL] =
{
	//IIS_Init,
   // SPI_Init,
//	MSPI_Init,     /*    */
  //  TIMER_Init,

	MCOM_Init,
	MDATA_Init,
    EVT_Init,
    FIFO_Init,
    LEVEL_Init,       /*      , , 应用层和中间层的初始化*/
         /*  , */
};

 /*所有20 ms 任务的index 索引号*/
typedef enum Sys20MSProcess_Tag
{
    INDEX_EVT_PROCESS = ( 0U ),
    INDEX_MDATA_PROCCESS,
    INDEX_SYS20MSPROCESS_ALL
}Sys20MSProcess_ENUM;

/* 20ms Process 函数排序*/
static const Proc20msType SysProc20ms_Tabl[INDEX_SYS20MSPROCESS_ALL] =
{
	MDATA_Process_20ms,
	EVT_Process_20ms,
};


/* Private static functions declare */
void sys_InitProcess(void);
static void sys_Process_BeforeDeepSleep(void);
#endif /*_SYS_PRIVATE_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       lzx      2018-06-08      Initial
* V2.0       Liuyingying     2017-6-30       modify
*===========================================================================*/


