/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : ds_info.inc
* Description : including the DS module all header files
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _DS_PRIVATE_H_

#define _DS_PRIVATE_H_

//#define NULL 0
#define DS_DEBOUNCE_MAXCNT      3    /*the counter of the gearmode debounce*/
#define DS_DSPRESTCNT 			10
#define DS_DSPFIRSTRESTCNT 			100


#define PEDTRNALRTLOW                       0x10 
#define PEDTRNALRTHIGH                      0x1a//0x1F   

#define PEDTRNALRTRVCEHIGH                      0x06
#define PEDTRNALRTRVCELOW                       0x05

/* Files for including */


     
void DS_GetInformation(void);
#endif /*_DS_INFO_INC_*/

                 
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
