/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :adce_public.h
* Description : public data of the adce
* Author: Jason.Sun
* Date: 2018-05-22
******************************************************************************/

/* check of multiple include */
#ifndef _ADCE_PUBLIC_H_
#define _ADCE_PUBLIC_H_

/* Public Macros defines */
#include "yd_typedefs.h"

/* Public data structures defines */

typedef enum AdceChannel_tag                    /*adͨ��ѡ��*/
{	
	INDEX_ADCE_CH0 = (0u),
	INDEX_ADCE_CH_ALL
}AdceChannel_ENUM;



/* Public extern functions declare */
extern void ADCE_Init(void);
extern U8 ADCE_GetInitStatus(void);
extern U8 ADCE_GetSingleValue(PU16 pResult);
extern U8 ADCE_StartConversion(AdceChannel_ENUM Channel);

#endif /*_ADCE_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun    2018-05-22     Initial
*
*===========================================================================*/

