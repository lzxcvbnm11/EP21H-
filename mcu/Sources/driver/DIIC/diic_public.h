/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : diic_public.h
* Description : Driver source file of DIIC.
* Author: Jason.Sun
* Date: 2018-05-28
******************************************************************************/

/* check of multiple include */
#ifndef _DIIC_PUBLIC_H_

#define _DIIC_PUBLIC_H_

/* Files for including */
#include "yd_typedefs.h"

/* Public Macros defines */

/* Public extern functions declare */
extern  void DIIC_Init(void);
extern BOOL  DIIC_GetInitStatus(void);
extern U8 DIIC_read(U8 dev_addr,U8 reg_addr, U8* buf, U16 len);  
extern void DIIC_write(U8 dev_addr,U8 reg_addr, U8* buf, U16 len);

#endif /* _DSPI_PUBLIC_H_ */

/*----------------- End of file -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun      2018-05-28      Initial
*
*===========================================================================*/


