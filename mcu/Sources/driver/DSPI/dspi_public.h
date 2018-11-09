/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : dspi_public.h
* Description : Driver source file of DSPI.
* Author: Jason.Sun
* Date: 2018-05-24
******************************************************************************/

/* check of multiple include */
#ifndef _DSPI_PUBLIC_H_

#define _DSPI_PUBLIC_H_

/* Files for including */
#include "yd_typedefs.h"

/* Public Macros defines */

#define MASTER  1
#define SLAVE   0

#define SPI_1M_HZ  1
#define SPI_1K_HZ  0


/* Public extern functions declare */
extern void DSPI_Init(U8 BaudRat,U8 Mode);
extern U8  DSPI_GetInitStatus(void);
extern U8  DSPI_SPIStop(void);
extern U8  DSPI_SPIStart(void);
extern BOOL DSPI_Master_Com_Byte(	U8 tx_value, U8 *p_rx);
extern BOOL DSPI_Master_Com_Bytes(	U8* p_tx, U8 *p_rx,U16 len);

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
* V1.0       Jason.Sun      2018-05-24      Initial
*
*===========================================================================*/

