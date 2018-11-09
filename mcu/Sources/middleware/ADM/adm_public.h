/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : adm_public.h
* Description : public informations of the ADM module
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _ADM_PUBLIC_H_
#define _ADM_PUBLIC_H_

/* Public Macros defines */

/* Public data structures defines */

typedef enum AdmChannel_Tag
{
    INDEX_ADM_BVD =  (0u),              /*电池电压检测ADC*/
    INDEX_ADM_ALL                               /*ADC 总通道数*/
}AdmChannel_ENUM;

/* Public extern functions declare */
extern void ADM_Init(void);
extern void ADM_Process_5ms(void);
extern BOOL ADM_GetInitStatus(void);
extern U8 ADM_GetDebounceValue(AdmChannel_ENUM index, PU16 pRes);


#endif /*_ADM_PUBLIC_H_*/

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

