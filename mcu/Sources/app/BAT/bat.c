/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : bat.c
* Description : BAT API application
* Author: qq
* Date: 2018-6-6
******************************************************************************/

/* Files for including */
#include "bat_info.inc"

/***************************************************
* Function: BAT_Init
* Description: BAT module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:    qq   Date:2018-6-6     Version:V1.0
*$log: initial variables
****************************************************/
void BAT_Init(void)
{
	bat_ADCValue = 0u;  
	bat_TD.status= 0;
	bat_TD.status_bak= 0;
	bat_TD.fltSts= FLT_BAT_NORMAL;
	bat_TD.Detect_cnt= 0;

  	bat_ClassA.status= 0;
	bat_ClassA.status_bak= 0;
	bat_ClassA.fltSts= FLT_BAT_NORMAL;
	bat_ClassA.Detect_cnt= 0;

  	bat_Can.status= 0;
	bat_Can.status_bak= 0;
	bat_Can.fltSts= FLT_BAT_NORMAL;
	bat_Can.Detect_cnt= 0;
       
 	bat_InitSts = ADM_GetInitStatus();
}

/***************************************************
* Function: BAT_Init
* Description:  Get BAT module initialized status
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:   qq        Date:2018-6-6     Version:V1.0
*$log: initial variables
****************************************************/
U8 BAT_GetInitStatus(void)
{
    return bat_InitSts;
}

/***************************************************
* Function: BAT_Process
* Description: the process of the BAT module 
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:   qq    Date:2018-06-06     Version:V1.0
*$log: add new functions
****************************************************/
void BAT_Process_5ms(void)
{
    U8 res = RET_OK;
    U8 i = 0;
    if (TRUE == bat_InitSts)
    {
	    res = ADM_GetDebounceValue(INDEX_ADM_BVD, &bat_ADCValue);
        if(RET_OK == res)
        {
            for(i =0; i < TYPE_BATDET_ALL ; i ++)
            {
     	      bat_voltageRange_Process_5ms(i,batDectTab[i]);            
              bat_voltageRange_check_5ms(i,batDectTab[i]);
            }
        }
		else
		{
		}
    }
    else
    {                                                   
    }
}

/***************************************************
* Function: bat_voltageStatusProcess
* Description: procss bat status
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:  qq     Date:2018-06-06     Version:V1.0
*$log: check battery sts
****************************************************/
static void bat_voltageRange_Process_5ms(U8 Type, stBatDect_ST *pData)
{
	U8 res = 0;

    if(NULL_PTR == pData) 
    {
        return;
    }

	switch (pData->fltSts) 
	{
		case LEVEL_BAT_HIGH:
	        if(batVolRangTab[Type].highoff >= bat_ADCValue)
	        {
				if(batVolRangTab[Type].lowon >= bat_ADCValue)
				{
				   pData->status = LEVEL_BAT_LOW;
				}
				else
				{
					 pData->status = FLT_BAT_NORMAL;
				}        
	        }
	        else
	        {
	           pData->status = LEVEL_BAT_HIGH; 
	        }
			break;

		case LEVEL_BAT_LOW:
	        if(batVolRangTab[Type].lowoff <= bat_ADCValue)
	        {
				if(batVolRangTab[Type].highon <= bat_ADCValue)
				{
				    pData->status = LEVEL_BAT_HIGH;
				}
				else
				{
					pData->status = FLT_BAT_NORMAL;
				}        
	        }
	        else
	        {
	            pData->status = LEVEL_BAT_LOW; 
	        }
			break;
			
		case LEVEL_BAT_NORMAL:
		default:
			if(batVolRangTab[Type].highon <= bat_ADCValue)
			{
			    pData->status = LEVEL_BAT_HIGH;
			}
			else  if(batVolRangTab[Type].lowon >= bat_ADCValue)
			{
			    pData->status = LEVEL_BAT_LOW;
			}
			else
			{
	        pData->status = LEVEL_BAT_NORMAL; 
			}        
			break;
	}
}
/***************************************************
* Function: bat_voltageRange_check
* Description: check the battery in fault status
* Parameters: none
* Returns:     none
* $Create & Verlog:$
* Author: qq  Date:2018-06-06     Version:V1.0
****************************************************/
static void bat_voltageRange_check_5ms(U8 Type,stBatDect_ST *pData)
{
    if(NULL_PTR == pData) 
    {
        return;
    }
  	else
	  {
  	}
      
    if( pData->status_bak != pData->status)
    { 
        pData->Detect_cnt = 0;
    }				
    else
    {
        if(batVolRangTab[Type].fltMaxCnt <= pData->Detect_cnt)
        {
        	pData->fltSts = pData->status;
        }
        else
        {
            pData->Detect_cnt ++;
        }
    }
    pData->status_bak = pData->status;
}


/***************************************************
* Function: BAT_GetBatValue
* Description: check the battery status
* Parameters: output
* Returns:   RET_FAIL
                    RET_INVAILD
                    RET_OK
* $Create & Verlog:$
* Author:   qq    Date:2018-06-06     Version:V1.0
****************************************************/
U8 BAT_GetBatValue(PU16 Value)
{
    U8 res;

    if (FALSE == bat_InitSts)
    {
        res = RET_FAIL;
    }
    else if (NULL_PTR == Value)
    {
        res = RET_INVALID;
    }
    else
    {
        *Value = bat_ADCValue;
         res = RET_OK;       
    }
    return  res;
}

/***************************************************
* Function: BAT_GetBatVoltageSts
* Description: check the battery status
* Parameters: 
* Returns:   STATUS_BAT_TD_CLASSA_CAN
                   STATUS_BAT_CLASSA_CAN
                   STATUS_BAT_CAN
                   STATUS_BAT_INNORMAL
* $Create & Verlog:$
* Author:  qq    Date:2018-06-06     Version:V1.0
****************************************************/
U8 BAT_GetBatVoltageSts(void)
{
    U8 res = RET_OK;

    if (FALSE == bat_InitSts)
    {
        res = RET_FAIL;
    }
    else 
    {
      ;
    }
    
    if(LEVEL_BAT_NORMAL == batDectTab[TYPE_BATDET_TD]->fltSts)
    {
       	 return STATUS_BAT_TD_CLASSA_CAN;
    }
   
    if(LEVEL_BAT_NORMAL == batDectTab[TYPE_BATDET_CLASSA]->fltSts)
    {
         return STATUS_BAT_CLASSA_CAN; 
    }
   
    if(LEVEL_BAT_NORMAL == batDectTab[TYPE_BATDET_CAN]->fltSts)
    {
         return STATUS_BAT_CAN;
    }

    return STATUS_BAT_INNORMAL;
       
  
    
}

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0            qq             2018-6-6               Initial
*===========================================================================*/

