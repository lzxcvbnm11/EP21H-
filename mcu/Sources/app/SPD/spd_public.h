/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : SPD_public.h
* Description : App source file of SPD.
* Author: qq
* Date: 2018-06-12
******************************************************************************/

/* check of multiple include */
#ifndef _SPD_PUBLIC_H_
#define _SPD_PUBLIC_H_

/* Public Macros defines */

/* Public extern functions declare */

extern void SPD_Init(void);
extern BOOL SPD_GetInitStatus(void);
extern void SPD_SPKSystemDiag_20ms(void); 
extern U8 SPD_GetSPKAndAMPSystensts(void);

extern U8 SPD_PACMFltSts(void);
extern U8 SPD_PedtrnAlrtSpkFltSts(void);

#endif /* _SPD_PUBLIC_H_ */

/*----------------- End of file -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0           qq      2018-06-12      Initial
*
*===========================================================================*/


