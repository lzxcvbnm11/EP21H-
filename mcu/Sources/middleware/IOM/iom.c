/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : iom.c
* Description : IOM module middleware
* Author: qq
* Date: 2018-6-5
******************************************************************************/

/* Files for including */
#include "iom_info.inc"

static IomDebounceData_ST iom_value[INDEX_IOM_ALL1];    /* IOM值*/
static BOOL IOM_InitStatus =  FALSE;      /* IOM初始化状态，默认值为FALSE */

/***************************************************
* Function: IOM_Init
* Description: IOM module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author: qq Date:2018-6-5   Version:V1.0
****************************************************/
void IOM_Init(void)
{
    U8 i = 0;
    IOM_InitStatus = DGPIO_GetInitStatus();

    for (i = 0; i < INDEX_IOM_ALL1; i++)
    {
        iom_value[i].value = STATUS_IOM_LOW;
        iom_value[i].debounce = STATUS_IOM_LOW;
        iom_value[i].res = RET_FAIL;
        iom_value[i].cnt = 0;
    }/*end of for()*/

}

/***************************************************
* Function: IOM_Process_100ms
* Description: the process of the IOM module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author: qq Date:2016-6-5   Version:V1.0
****************************************************/
void IOM_Process_100ms(void)
{
    IOM_InPut_ENUM i = INDEX_IOM_FAULTZ1;

    if (TRUE == IOM_InitStatus)
    {
        for (i = INDEX_IOM_FAULTZ1; i < INDEX_IOM_ALL1; i++)
        {
            iom_InputDebounce(i);
        }/*end of for()*/
    }
    else
    {
    }
}

/***************************************************
* Function: iom_InputDebounce
* Description: the debounce of the input IO port
* Parameters:  input: index  the index of the input IO port
* Returns:  return value reference IomRes_ENUM
* $Create & Verlog:$
* Author: qq Date:2018-6-5   Version:V1.0
****************************************************/
static U8 iom_InputDebounce(IOM_InPut_ENUM index)
{
    U8 value = 0;
    U8 status = RET_FAIL;
    U8 res = RET_FAIL;
	
    status = DGPIO_GetIOSts(index, &value);
    
    if(INDEX_IOM_ALL1 <= index)
    {
        res = RET_INVALID;
    }
    else if (RET_OK == status)
    {
        if (iom_value[index].value == value)
        {
            if (iom_value[index].cnt >= IOM_DEBOUNCE_MAXCNT)
            {
                iom_value[index].cnt = 0;
                iom_value[index].value = value;
                iom_value[index].debounce = iom_value[index].value;
                iom_value[index].res = RET_OK;
            }
            else
            {
	            iom_value[index].cnt++;
            }
        }
        else
        {
            iom_value[index].cnt = 0;
            iom_value[index].value = value;
            iom_value[index].res = RET_FAIL;
        }
		
        res = iom_value[index].res ;
    }/*end of if()*/
    else
    {
    }    
    return res;
}

/***************************************************
* Function: IOM_SetOutPutLevel
* Description: set the level of IO port
* Parameters: input：Index    the index of the ouput IO port，reference the IomInPut_ENUM
                         input:    value    the level of the output IO port
		             IOM_STATUS_HIGH : High Level
		             IOM_STATUS_LOW : Low Level
* Returns: return value reference IomRes_ENUM
* $Create & Verlog:$
* Author:qq  Date:2018-6-5   Version:V1.0
****************************************************/
U8 IOM_SetOutPutLevel(IOM_OutPut_ENUM index, U8 value)
{
    U8 status = FALSE;
    U8 ret = 0;
    U8 res = RET_FAIL;   
    
    status = DGPIO_SetIOSts(Iom_Matrix[index + INDEX_IOM_ALL1].ch, value, &ret);
    
    if(FALSE == IOM_InitStatus)
    {
        res = RET_FAIL;
    }
    else if ((ret == value) && (TRUE == status))
    {
        res = RET_OK;
    }
    else
    {
        res = RET_FAIL;
    }
	
    return res;

}

/***************************************************
* Function:IOM_GetInputLevel
* Description: get the status of the input IO after debounce
* Parameters:  input：Index  the index of the input IO port，reference the IomInPut_ENUM
		        output：pRes  the level of the input IO port after debounce
			          IOM_STATUS_HIGH : High Level
			          IOM_STATUS_LOW :Low Level
		                   pRes : iom_value[n].debounce;(reference IomInPut_ENUM)
* Returns: return value reference IomRes_ENUM
* $Create & Verlog:$
* Author:   qq  Date:2018-6-5   Version:V1.0
****************************************************/
U8 IOM_GetInputLevel(IOM_InPut_ENUM index, PU8 pRes)
{
    U8 res = RET_OK;

    if (FALSE == IOM_InitStatus)
    {
        res = RET_FAIL;
    }
    else if((NULL_PTR == pRes) || (INDEX_IOM_ALL1 <= index))
    {
        res = RET_INVALID;
    }
    else
    {
        *pRes = iom_value[index].value;
    }

    return res;
}

/***************************************************
* Function:  IOM_GetModuleStatus
* Description: get the IOM module initialized status
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:qq  Date:2018-6-5   Version:V1.0
****************************************************/
BOOL IOM_GetInitStatus(void)
{
    return IOM_InitStatus;
}

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0             qq          2018-6-5      Initial
*
*===========================================================================*/

