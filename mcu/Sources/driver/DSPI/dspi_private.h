/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :
* Description : dspi_private.h
* Author: Jason.Sun
* Date: 2018-05-24
******************************************************************************/

/* check of multiple include */
#ifndef _DSPI_PRIVATE_H_

#define _DSPI_PRIVATE_H_

/* Files for including */
#include "yd_typedefs.h"
#include "dspi_public.h"

#define SPI_INT_DISABLE                     0
#define SPI_ENABLE                          1
#define TRANSMIT_INT_DISABLE                0
#define TRANSMIT_INT_ENABLE                 1
#define SPI_MASTER_MODE                     1
#define DATA_TRANSMITING                    0
#define DATA_NOT_EMPTY                      0
#define RECEIVE_NEW_DATA                    1 

#define DATA_WIDTH_8                        0
#define DATA_WIDTH_16                       1
#define DSPI_OUTTIMECOUNT                   2048
#define DSPI_NO_OUTTIMEFUN                  0



#define NOP                                 asm("nop")


#endif /* _DSPI_PRIVATE_H_ */

/*----------------- End of file -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun      2018-05-24      Initial
*
*===========================================================================*/
