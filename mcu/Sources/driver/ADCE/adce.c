/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : adce.c
* Description : Driver source file of ADCE.
* Author: Jason.Sun
* Date: 2018-05-22
******************************************************************************/

/* Files for including */
#include "adce_info.inc"

static BOOL adce_InitStatus;
static BOOL adce_ConvertComplete;

/***************************************************
* Function: ADCE_Init
* Description: ADCE drive initialization
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author: Jason.Sun   Date:2018-05-22   Version:V1.0
****************************************************/
void ADCE_Init(void)
{  

	
	ATDCTL4 = 0xE0;
	ATDCTL3_DJM = 1;	   /*Result right justified*/
	//ATDCTL3_FIFO = 1;	   /*Fisrt-in-first-out mode*/
	ATDCTL3_S8C = 0;	   /*1 conversion per sequence*/
	ATDCTL3_S4C = 0;
	ATDCTL3_S2C = 0;
	ATDCTL3_S1C = 1;
	ATDCTL2 	= 0x40;
	ATDCTL1_SRES = 0x01;   /*10 bit resolution*/
	ATDCTL0 = 0x0F;/* 设置多通道转换顺序 */
	//ATDDIEN = 0xFFFF;	   /*Set All GPIO as Digital Input/Output for next initial*/
	ATDSTAT0_SCF = 1;	   /*Clear sequence complete flag*/
	//ATDDIEN &= CLEAR_MASK(0);
	//ATDCTL5_Cx = 0; /*AN0 channel*/
    adce_InitStatus = TRUE;
	adce_ConvertComplete = TRUE;
}

/***************************************************
* Function: ADCE_GetSingleValue
* Description: get single channel of ad Value
* Parameters: Channel:ad channel
			  pResult :store the ad value
* Returns: FAIL/OK/INVALID
* $Create & Verlog:$
* Author: Jason.Sun   Date:2018-05-22   Version:V1.0
****************************************************/
U8 ADCE_GetSingleValue(PU16 pResult)
{ 
    U8 adce_res = RET_OK;
    U8 adc_count;
    if (FALSE == adce_InitStatus)
    {
        adce_res = RET_FAIL;
    }
    else
    {
        if (NULL_PTR == pResult)
        {
           adce_res = RET_INVALID;
        }
        else
        {
        		adc_count = 250;
				
                while((0 == ATDSTAT0_SCF) && (adc_count --))
        		{
					asm("nop");
       			}
				if(adc_count > 0)
				{
					adce_ConvertComplete = TRUE;
            	 	ATDSTAT0_SCF = 1; /*Clear Sequnce Complete Flag(unnecessary)*/
            		*pResult = ATDDR0;					
					adce_res = RET_OK;
				}
				else
				{
					adce_res = RET_BUSY;
				}
				
        }
    }
	return adce_res;
}

/***************************************************
* Function: ADCE_GetInitStatus
* Description: get the ADCE module initialized status
* Parameters: none
* Returns: adce_InitStatus
* $Create & Verlog:$
* Author: Jason.Sun   Date:2018-05-22   Version:V1.0
****************************************************/
U8 ADCE_GetInitStatus(void)
{
    return adce_InitStatus;
}

/***************************************************
* Function: ADCE_StartConversion
* Description: Start ad Conversion
* Parameters: none
* Returns: FAIL/OK/INVALID
* $Create & Verlog:$
* Author: Jason.Sun   Date:2018-05-22   Version:V1.0
****************************************************/
U8 ADCE_StartConversion(AdceChannel_ENUM Channel)
{	
    U8 res = RET_OK;
    if (TRUE == adce_InitStatus)
    {
    	
	   if(adce_ConvertComplete != TRUE)
	   {
		 res =RET_BUSY;
	   }
	   else
	   {
	   	 adce_ConvertComplete = FALSE;
       	 ATDCTL5 = (U8)Channel;
	   }
    }
    else
    {
        res = RET_FAIL;
    }
	
    return res;
}

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun     2018-05-22      Initial
*
*===========================================================================*/

