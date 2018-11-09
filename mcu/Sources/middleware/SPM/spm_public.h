/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : SPM_public.h
* Description : Driver source file of SPM.
* Author: qq
* Date: 2018-06-07
******************************************************************************/

/* check of multiple include */
#ifndef _SPM_PUBLIC_H_
#define _SPM_PUBLIC_H_

/* Public Macros defines */
#if 0
struct FaultReg_Tag
{
    U8 Overcurrent;          /*Overcurrent shutdown has occurred.*/
    U8 Undervoltage;         /*PVDD undervoltage has occurred.*/
    U8 Overvoltage;          /*PVDD overvoltage has occurred.*/
    U8 DCoffset;             /*DC offset protection has occurred.*/
    U8 Overtemperature;      /*Overtemperature shutdown has occurred.*/
    U8 OutputShortPVDD;      /*Output short to PVDD is present.*/
    U8 OutputShortGND;       /*Output short to ground is present.*/
    U8 OpenLoad;             /*Open load is present.*/
    U8 ShortLoad;            /*Shorted load is present.*/     
};
#endif

/* Public extern functions declare */
typedef enum VolumeNum_Tag
{
	  INDEX_SPM_VOLUME1 = (0u),
    INDEX_SPM_VOLUME2,
    INDEX_SPM_VOLUME3,
    INDEX_SPM_VOLUME4,
    INDEX_SPM_VOLUME_ALL
}VolumeNum_ENUM;

extern void SPM_Init(void);
extern BOOL SPM_GetInitStatus(void);
//struct FaultReg_Tag SPM_GetFaultEvent(U8 res);
extern BOOL SPM_GetSpkWorkStatus(void);
extern BOOL SPM_GetAmpWorkStatus(void);
extern U8 SPM_SetVolume(U8 Index);


#endif /* _SPM_PUBLIC_H_ */

/*----------------- End of file -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0           qq      2018-06-07      Initial
*
*===========================================================================*/


