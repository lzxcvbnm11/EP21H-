/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : dgpio_cfg.h
* Description : config infomation of DGPIO driver.
* Author: Jason.Sun
* Date: 2018-05-26
******************************************************************************/


/* check of multiple include */
#ifndef _DIIC_PRIVATE_H_

#define _DIIC_PRIVATE_H_

/* Files for including */
#include "yd_typedefs.h"
#include "diic_public.h"

#define DEVICE_I2C_SDA_PINAD1 				3

#define DEVICE_I2C_SCL_PINAD0				3

void DIIC_Dlay20us(void);


#endif /* _DIO_PRIVATE_H_ */

/*----------------- End of file -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun      2018-05-26      Initial
*
*===========================================================================*/
