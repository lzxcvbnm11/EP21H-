/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :fifo_private.h
* Description : the private informations  of the Iom module
* Author: lzx
* Date: 2018-06-08
******************************************************************************/

/* check of multiple include */
#ifndef _FIFO_PRIVATE_H_

#define _FIFO_PRIVATE_H_

#include "../../yd_typedefs.h"


/* Macro defines */

#define FIFO_RANG_MAX 8000   /* / 1/16ms   500ms内的采样点*/
#define FIFO_PEIOR 32
#define FIFO_RANG_UNIT  1/FIFO_RANG_MAX
#define FIFO_LIBCOMPENSATE 8000
/* Private data structures defines */


/*constant define*/


/* Private static functions declare */
void FIFO_FifoIn(void);
void FIFO_FifoOut(void);
#endif /*_FIFO_PRIVATE_H_*/

/*------------------end of file----------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       lzx      2018-06-08      Initial
*
*===========================================================================*/

