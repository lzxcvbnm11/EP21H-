/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : dgpio_cfg.h
* Description : config infomation of DGPIO driver.
* Author: Jason.Sun
* Date: 2018-05-18
******************************************************************************/


/* check of multiple include */
#ifndef _DGPIO_PUBLIC_H_

#define _DGPIO_PUBLIC_H_

/* Files for including */
#include "yd_typedefs.h"

/* Public Macros defines */

/* Public data structures defines */
typedef  enum DgpioPortNum_Tag
{
    /* input */
    INDEX_DGPIO_PIN16  =  (0u),    /*pin16, PWM3/PP3*/
    INDEX_DGPIO_PIN20,             /*pin20, IOC4/PT4*/
    INDEX_DGPIO_PIN22,             /*pin22, IOC2/PT2*/

    /* output */
    INDEX_DGPIO_PIN17,             /*pin17, PWM4/PP4*/    
    INDEX_DGPIO_PIN21,             /*pin21, IOC3/PT3*/
    INDEX_DGPIO_PIN23,             /*pin23, IRQ/IOC1/PT1*/
    INDEX_DGPIO_PIN24,             /*pin24, XIRQ/IOC1/PT0*/
    INDEX_DGPIO_PIN27,             /*pin27, PAD1/AN1*/
    INDEX_DGPIO_PIN29,             /*pin29, PAD2/AN2*/
    INDEX_DGPIO_ALL
} DgpioPortNum_ENUM;


/* Public extern functions declare */
extern void DGPIO_Init(void);
extern U8  DGPIO_GetInitStatus(void);
extern U8  DGPIO_SetIOSts(U16 Index,U8 PinLevel,PU8 pRes);
extern U8  DGPIO_GetIOSts(U16 Index,PU8 PinLevel);
extern void DGPIO_GPIO_Dlayus(U32 cnt);

#endif /* _DGPIO_PUBLIC_H_ */

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


