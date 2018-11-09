/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : diag_public.h
* Description : public informations of the DS module
* Author: qq
* Date: 2018-07-18
******************************************************************************/

/* check of multiple include */
#ifndef _DIAG_PUBLIC_H_
#define _DIAG_PUBLIC_H_

/* Public Macros defines */

/* Public data structures defines */

typedef enum DiagQuietModeFun_Tag
{
	DIAG_QUIET_MODULE = (0u),
	DIAG_QUIET_EXIT_MODULE,
	DIAG_QUIET_ALL
}DiagQuietModeFun_ENUM;


/* Public extern functions declare */
extern void DIAG_Init(void);
extern void DIAG_Process_20ms(void);
extern BOOL DIAG_GetInitStatus(void);
extern DiagQuietModeFun_ENUM  DIAG_GetQuietModeStatus(void);


#endif /*_DIAG_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       QQ      2018-07-18      Initial
*
*===========================================================================*/

