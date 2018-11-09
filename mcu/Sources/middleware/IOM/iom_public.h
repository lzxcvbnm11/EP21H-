/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : iom_public.h
* Description : public informations of the Iom module
* Author: qq
* Date: 2018-6-5
******************************************************************************/

/* check of multiple include */
#ifndef _IOM_PUBLIC_H_

#define _IOM_PUBLIC_H_

#include "yd_typedefs.h"
/* Public Macros defines */


/* Public data structures defines */
typedef  enum  IOM_InPut_Tag
{
    INDEX_IOM_FAULTZ1  =  (0u),   /*功放报错端口1*/
    INDEX_IOM_FAULTZ2,            /*功放报错端口2*/
    INDEX_IOM_ERR,                /*CAN总线报错端口*/
    INDEX_IOM_ALL1              
}IOM_InPut_ENUM;

typedef  enum  IOM_OutPut_Tag
{
    INDEX_IOM_MUTE  =  (0u),  /*控制功放静音*/
    INDEX_IOM_SHDN,           /*控制功放shutdown端口*/
    INDEX_IOM_CAN_STB,        /*CAN STANDBY控制脚*/
    INDEX_IOM_EN,             /*CAN EN 使能控制*/
    INDEX_IOM_DCDC_EN,        /*DSP 电源使能控制*/
    INDEX_IOM_DSP_RES,        /*控制DSP复位端口*/
    INDEX_IOM_ALL2
}IOM_OutPut_ENUM;


/* Public extern functions declare */
extern void IOM_Init(void);
extern void IOM_Process_100ms(void);
extern U8 IOM_SetOutPutLevel(IOM_OutPut_ENUM index, U8 value);
extern U8 IOM_GetInputLevel(IOM_InPut_ENUM index, PU8 pRes);
extern BOOL IOM_GetInitStatus(void);


#endif /*_IOM_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0            qq            2018-06-07         Initial
*
===========================================================================*/
