/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : mdata_public.h
* Description : public informations of the MDATA module
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _MDATA_PUBLIC_H_
#define _MDATA_PUBLIC_H_
#include <stdio.h>
#include "../../yd_typedefs.h"
#include "../LEVEL/level_public.h"
/* Public Macros defines */

/* Public data structures defines */
#if 0
union engandslt_tag
{
	u8 engandslt;
	struct
	{
		u8 pasenable :1;
		u8 pasenginereq :2;
		u8 gearmode:2;

	}engandslt_st;
};
#endif
typedef  struct  MdataRecvMsg_Tag
{
	 u8  header_h;          /*数据头高8位*/
	 u8 header_l;
	 u8 length;
	 u8  vehspeed_h;        /*车速高8位*/
	 u8  vehspeed_l;        /*车速低8位*/
	 u8 greadmod;			/*档位选择*/
	u8  pasenable;					/*发动机模拟声开关*/
	u8  pasenginereq;			/*发动机音量选择*/
	u8  passltreq;					/*语音提示音选择*/
	u8  pasvolvalue;					/*音量值*/
	u8  crc;						  /*校验位*/
}MdataRecvMsg_ST;

typedef  struct  MdataSendMsg_Tag
{

	  u8  header_h;          /*数据头高8位*/
	  u8  header_l;          /*数据头低8位*/
	  u8  length;            /*数据长度*/
	  u8  passltsts;        /*车身提醒音*/
	  u8  pasvolval;        /*车外提醒音音量值*/
		u8  pasenablests;					/*发动机模拟声开关*/
		u8  psaenginersts;				/*发动机音效选择*/
		u8  reserve0;					/*行人警示控制系统故障*/
		u8  reserve1;					/*行人警示控制音响故障*/
		u8  reserve2;
		u8  crc;						  /*校验位*/
}MdataSendMsg_ST;

/* Public extern functions declare */
extern void MDATA_Init(void);
extern void MDATA_Process_20ms(void);
extern BOOL MDATA_GetInitStatus(void);
extern float MDATA_GetVehspeedVaule(void);
extern u8  MDATA_GetGearodeVaule(void);
extern u8  MDATA_GetPasenableSts(void);
extern u8  MDATA_GetpassltreqVaule(void);
extern u8 MDATA_GetPasvolreqVaule(void);
extern u8  MDATA_GetPasenginereqVaule(void);
#endif /*_MDATA_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       lzx      2018-06-05      Initial
*
*===========================================================================*/

