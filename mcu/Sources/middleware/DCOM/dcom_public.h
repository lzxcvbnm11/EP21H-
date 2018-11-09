/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : dcom_public.h
* Description : public informations of the DCOM module
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _DCOM_PUBLIC_H_
#define _DCOM_PUBLIC_H_

/* Public Macros defines */
                                       
/* Public data structures defines */

typedef  struct  DcomSendMsg_Tag
{
  U8 header_h;          /*数据头高8位*/
  U8 header_l;          /*数据头低8位*/   
  U8 length;            /*数据长度*/
  U8 vehspeed_h;        /*车速高8位*/
  U8 vehspeed_l;        /*车速低8位*/
	U8 gearmode;					/*档位选择*/
	U8 pasenable;					/*发动机模拟声开关*/
	U8 pasenginereq;			/*发动机音效选择*/
	U8 passltreq;					/*语音提示音选择*/
	U8 pasvolreq;					/*音量值*/
	U8 crc;						  /*校验位*/
}DcomSendMsg_ST;

typedef  struct  DcomRecvMsg_Tag
{
  U8 header_h;          /*数据头高8位*/
  U8 header_l;          /*数据头低8位*/   
  U8 length;            /*数据长度*/
  U8 passltsts;        /*车身提醒音*/
  U8 pasvolval;        /*车外提醒音*/
	U8 pasenablests;					/*发动机模拟声开关*/
  U8 psaenginersts;				/*发动机音效选择*/
	U8 reserve0;					/*行人警示控制系统故障*/
	U8 reserve1;					/*行人警示控制音响故障*/
	U8 reserve2;
	U8 crc;						  /*校验位*/
}DcomRecvMsg_ST;

/* Public extern functions declare */
extern void DCOM_Init(void);
extern BOOL DCOM_Process(PU8 PSendMsg, PU8 PRvceMsg, U8 len);
extern BOOL DCOM_GetInitStatus(void);

#endif /*_DCOM_PUBLIC_H_*/

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

