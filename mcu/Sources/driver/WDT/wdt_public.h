/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : wdt_public.h
* Description :
* Author: Jason.Sun
* Date: 2018-05-22
******************************************************************************/

/* check of multiple include */
#ifndef _WDT_PUBLIC_H_

#define _WDT_PUBLIC_H_

/* Files for including */
#include "yd_typedefs.h"

/* Public Macros defines */

/* Public data structures defines */

/* Public extern functions declare */
extern void WDT_Init(void);
extern U8 WDT_GetInitStatus(void);
extern void WDT_Feed(void);



#endif /* _WDT_PUBLIC_H_ */

/*----------------- End of file -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun      2018-05-22     Initial
*
*===========================================================================*/

