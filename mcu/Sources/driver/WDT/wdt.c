/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : wdt.c
* Description : WDT configuration.
* Author: Jason.Sun
* Date: 2018-05-22
******************************************************************************/

/* Files for including */
#include "wdt_info.inc"

/*--------------- Global variable definition and initialization -----------------*/
static U8 Wdt_Status = FALSE;

/*---------------------- Implementation of module ---------------------*/

/***************************************************
* Function: WDT_Init.
* Description: wdt Initialization.
* Parameters: none
* Returns: none
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-22   Version:V1.0
****************************************************/
void WDT_Init(void)
{
	_ENABLE_COP(7);
    Wdt_Status = TRUE;
}

/***************************************************
* Function: WDT_GetInitStatus
* Description: get the WDT module init status.
* Parameters: none
* Returns:
*            FALSE(0): init failure
*            TRUE(1): init success.
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-22   Version:V1.0
****************************************************/
U8 WDT_GetInitStatus(void)
{
    return Wdt_Status;
}


/***************************************************
* Function: WDT_Feed
* Description: feed watch dog timer.
* Parameters: none
* Returns:none
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-22   Version:V1.0
****************************************************/
void WDT_Feed(void)
{

	_FEED_COP();

}



/*----------------- End of Module -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun      2018-05-22      Initial
*
*===========================================================================*/

