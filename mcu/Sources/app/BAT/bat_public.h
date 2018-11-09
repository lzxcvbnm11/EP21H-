/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :bat_public.h
* Description : public data of the Bat
* Author: qQ
* Date: 2018-6-6
******************************************************************************/
/* check of multiple include */
#ifndef _BAT_PUBLIC_H_

#define _BAT_PUBLIC_H_

#include "yd_typedefs.h"

/* Public Macros defines */
#if 0
struct BatVoltageSts_Tag
{
    U8 BatVoltageSts_TD;
    U8 BatVoltageSts_ClassA;
    U8 BatVoltageSts_Can;    
};
#endif
typedef enum BatVoltageSts_Tag
{
    STATUS_BAT_TD_CLASSA_CAN = (0u),/*diag function == ok， class a function == ok， can communation == ok*/ 
    STATUS_BAT_CLASSA_CAN,  /*diag function == fail， class a function == ok， can communation == ok*/                         
    STATUS_BAT_CAN,			/*diag function == fail， class a function == fail， can communation == ok*/                               
    STATUS_BAT_INNORMAL,	/*diag function == fail， class a function == fail， can communation == fail*/
    STATUS_BAT_ALL
}BATVoltageSts_ENUM;

/* Public extern functions declare */
extern void BAT_Init(void);
extern U8 BAT_GetInitStatus(void);
extern void BAT_Process_5ms(void);
extern U8 BAT_GetBatValue(PU16 Value);
extern U8 BAT_GetBatVoltageSts(void); 

#endif /*_BAT_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0            QQ            2018-6-6              Initial
*===========================================================================*/

