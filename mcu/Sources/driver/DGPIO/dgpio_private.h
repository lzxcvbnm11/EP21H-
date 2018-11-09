/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : dgpio_cfg.h
* Description : config infomation of DGPIO driver.
* Author: Jason.Sun
* Date: 2018-05-18
******************************************************************************/


/* check of multiple include */
#ifndef _DIO_PRIVATE_H_

#define _DIO_PRIVATE_H_

/* Files for including */
#include "dgpio_public.h"

typedef enum DgpioDir_Tag
{
	DIR_DGPIO_INPUT = (0u),
    DIR_DGPIO_OUTPUT,
    DIR_DGPIO_ALL
}DgpioDir_ENUM;

typedef enum DgpioPort_Tag
{
    PORT_DGPIO_PP = (0u),
    PORT_DGPIO_PT,
    PORT_DGPIO_PAD1,
    PORT_DGPIO_ALL
}DgpioPort_ENUM;

typedef struct DgpioGpio_Tag
{
    DgpioPort_ENUM port; /* 255-JP0, 0-P0, 1-P1, 3-P3....*/
    U8 pin;
    DgpioDir_ENUM dir; /* 1-output, 0-input*/
    U8 initval;
}DgpioGpio_ST;

const DgpioGpio_ST GpioList[INDEX_DGPIO_ALL]=
{
/* port, pin, dir, initval */

    /* input */
    { PORT_DGPIO_PP, 3, DIR_DGPIO_INPUT, 0},
    { PORT_DGPIO_PT, 4, DIR_DGPIO_INPUT, 0},
    { PORT_DGPIO_PT, 2, DIR_DGPIO_INPUT, 0},

    /* output */
    { PORT_DGPIO_PP, 4, DIR_DGPIO_OUTPUT, 0},
    { PORT_DGPIO_PT, 3, DIR_DGPIO_OUTPUT, 0},
    { PORT_DGPIO_PT, 1, DIR_DGPIO_OUTPUT, 0},
    { PORT_DGPIO_PT, 0, DIR_DGPIO_OUTPUT, 0},
    { PORT_DGPIO_PAD1, 1, DIR_DGPIO_OUTPUT, 0},
    { PORT_DGPIO_PAD1, 2, DIR_DGPIO_OUTPUT, 0},
};


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
* V1.0       Jason.Sun      2018-05-18      Initial
*
*===========================================================================*/

