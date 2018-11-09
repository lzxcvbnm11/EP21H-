/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : mcom_public.h
* Description : public informations of the MCOM module
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _MCOM_PUBLIC_H_
#define _MCOM_PUBLIC_H_
#include "../../yd_typedefs.h"
/* Public Macros defines */
                                       
/* Public data structures defines */
#define MCOM_MAXLOSTDATACNT 10

/* Public extern functions declare */
extern void MCOM_Init(void);
extern BOOL MCOM_Process_20ms(PU8 PSendMsg, PU8 PRvceMsg, u8 len);
extern BOOL MCOM_GetInitStatus(void);

#endif /*_MCOM_PUBLIC_H_*/

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

