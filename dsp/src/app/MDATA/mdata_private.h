/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : ds_info.inc
* Description : including the MDATA module all header files
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _MDATA_PRIVATE_H_

#define _MDATA_PRIVATE_H_
#include "../../yd_typedefs.h"
//#define NULL 0
#define MDATA_DEBOUNCE_MAXCNT      3    /*the counter of the gearmode debounce*/
/* Files for including */
#define MDATA_SLTRNOREQUEST 11
#define MDATA_SINEWARE 10
     
void MDATA_GetInformation(void);
static u8  MDATA_GremodeDebounce(void);
#endif /*_MDATA_INFO_INC_*/

                 
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
