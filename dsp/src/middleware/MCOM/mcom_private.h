/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : mcom_private.h
* Description : private informations of the MCOM module
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _MCOM_PRIVATE_H_
#define _MCOM_PRIVATE_H_  
#include "../../yd_typedefs.h"

#define Header_H 0xAA
#define Header_L 0x55



u8 CRC_CKECKSUM(PU8 PuchMsg, u8 length);

#endif /*_MCOM_PRIVATE_H_*/

/*------------------end of file----------------------------*/

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

