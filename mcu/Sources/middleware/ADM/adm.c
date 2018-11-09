/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : adm.c
* Description : ADM module middleware
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* Files for including */
#include "adm_info.inc"


static BOOL adm_InitStatus = FALSE;                     /* ADM初始化状态，默认值为FALSE */
static U8  adm_ADCEConversionRes = RET_FAIL;            /* ADCE转化结果 默认值为RET_FAIL*/
static AdmGatherData_ST adm_Value[ADM_CHANNEL_MAX];     /* ADM值*/

/***************************************************
* Function: ADM_Init
* Description: ADM module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void ADM_Init(void)
{
    U8 i = 0;

    for (i = 0; i < ADM_CHANNEL_MAX; i++)
    {
    	adm_Value[i].cnt = 0;
    	adm_Value[i].sum = 0;
    	adm_Value[i].value = 0;
    	adm_Value[i].debounceValue = 0;

    	adm_Value[i].res = RET_FAIL;
    }
    
	for(i=INDEX_ADM_BVD; i< ADM_CHANNEL_MAX; i++) 
	{
	   adm_ADCEConversionRes = ADCE_StartConversion(i);
	}
    
    adm_InitStatus = ADCE_GetInitStatus();

	for( i = 0 ; i < DEBOUNCE_FUEL_COUNT; i ++)
	{
		ADM_Process_5ms();
	}
}

/***************************************************
* Function: ADM_Process_5ms 
* Description: the process of the ADM module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void ADM_Process_5ms (void)
{
    AdmChannel_ENUM index = INDEX_ADM_BVD;

    if (FALSE == adm_InitStatus)
    {
        ;     
    }
    else if (RET_OK == adm_ADCEConversionRes)
    {	
		  int i = 0;
      for (index = INDEX_ADM_BVD; index < INDEX_ADM_ALL; index++)
      {
          adm_ChannelDebounce(index);
      }
		
	  	for(i=INDEX_ADM_BVD; i< ADM_CHANNEL_MAX; i++) 
	  	{
		  	adm_ADCEConversionRes = ADCE_StartConversion(i);
	  	}
     }
    else 
    {       
       
    }

	return;
}

/***************************************************
* Function: adm_ChannelDebounce
* Description: the debounce of ADC
* Parameters: input :  the channal of ADCE
* Returns: return value reference AdmRes_ENUM
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
static U8 adm_ChannelDebounce(AdmChannel_ENUM index)
{
    U16 value = 0;
    U16 range = 0;

    U8 res = RET_OK;

    if ((INDEX_ADM_ALL <= index) || (Adm_Matrix[index].ch > ADM_CHANNEL_MAX))
    {
        res = RET_INVALID;
    }
    else
	{ 
		if (RET_OK == ADCE_GetSingleValue(&value))
	    {
	        range = ABS_SUB(value, adm_Value[Adm_Matrix[index].ch].value);
	        if (range < Adm_Matrix[index].range)
	        {
	            if (adm_Value[Adm_Matrix[index].ch].cnt >= Adm_Matrix[index].debCnt)
	            {
	            	adm_Value[Adm_Matrix[index].ch].debounceValue = (adm_Value[Adm_Matrix[index].ch].sum / Adm_Matrix[index].debCnt);
	            	adm_Value[Adm_Matrix[index].ch].sum = 0;
	            	adm_Value[Adm_Matrix[index].ch].cnt = 0;
	            	adm_Value[Adm_Matrix[index].ch].res = RET_OK;
	            }
	            else
	            {
		            adm_Value[Adm_Matrix[index].ch].sum += value;
		            adm_Value[Adm_Matrix[index].ch].cnt++;
	            }
	        }
	        else
	        {
	            adm_Value[Adm_Matrix[index].ch].cnt = 0;
	            adm_Value[Adm_Matrix[index].ch].sum = 0;
	            adm_Value[Adm_Matrix[index].ch].res = RET_FAIL;
	        }
			
            adm_Value[Adm_Matrix[index].ch].value = value;
	    }/*end of ADCE_GetSingleValue(Adm_Matrix[index].ch, &value) */
	    else
	    {
	    	res = RET_FAIL;
	    }
   	}
	
    return res;
}

/***************************************************
* Function: ADM_GetInitStatus
* Description: get the ADM module initialized status
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
BOOL ADM_GetInitStatus(void)
{
    return adm_InitStatus;
}

/***************************************************
* Function: ADM_GetDebounceValue
* Description: Get the value of AD after debounce
* Parameters: input: Index  the channel of ADC
			  output: pRes  the value of AD
* Returns: return value reference AdmRes_ENUM
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
U8 ADM_GetDebounceValue(AdmChannel_ENUM index, PU16 pRes)
{
    U8 res = RET_OK;

    if (FALSE == adm_InitStatus)
    {
        res = RET_FAIL;
    }
    else if ((NULL_PTR == pRes) ||(INDEX_ADM_ALL <= index) ||  (Adm_Matrix[index].ch > ADM_CHANNEL_MAX))
    {
        res = RET_INVALID;
    }
    else
    {
      *pRes = adm_Value[Adm_Matrix[index].ch].debounceValue;
    	res = adm_Value[Adm_Matrix[index].ch].res;
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
* V1.0       lzx      2018-06-05      Initial
*
*===========================================================================*/

