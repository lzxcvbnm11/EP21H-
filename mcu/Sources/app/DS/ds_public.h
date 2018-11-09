/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : ds_public.h
* Description : public informations of the DS module
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _DS_PUBLIC_H_
#define _DS_PUBLIC_H_
#include "yd_typedefs.h"
/* Public Macros defines */

/* Public data structures defines */

typedef  struct  DsSendMsg_Tag
{

  U8 vehspeed_h;
  U8 vehspeed_l; 
	U8 gearmode;
	U8 pasenable;
	U8 pasenginereq;
	U8 passltreq;
	U8 pasvolreq;
}DsSendMsg_ST;

typedef  struct  DsRecvMsg_Tag
{

  U8 passltsts;
  U8 pasvolsts;
	U8 pasenablests;
	U8 psaenginersts;
}DsRecvMsg_ST;

/* Public extern functions declare */
extern void DS_Init(void);
extern void DS_Process_20ms(void);
extern BOOL DS_GetInitStatus(void);
extern BOOL DS_GetComsts(void);
extern BOOL DS_GetSpiFltSts(void);
U8 get_mute_flag();

#endif /*_DS_PUBLIC_H_*/

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

