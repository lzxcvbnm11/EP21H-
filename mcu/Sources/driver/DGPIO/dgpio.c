/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : dgpio.c
* Description : Driver source file of DGPIO.
* Author: Jason.Sun
* Date: 2018-05-18
******************************************************************************/

/* Files for including */
#include "dgpio_info.inc"

/*--------------- Global variable definition and initialization -----------------*/
static BOOL Dgpio_Status = FALSE;

/*---------------------- Implementation of module ---------------------*/

/***************************************************
* Function: dgpio_GPIO_Init
* Description: GPIO initialization
* Parameters:
*                  port - GPIO port
*                  pin - GPIO pin
*                  direction - 0=output, 1=input
*                  initval - GPIO init value.
* Returns:
*            FALSE(0): init fail.
*            TRUE(1):  init success.
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-18   Version:V1.0
****************************************************/
static BOOL dgpio_GPIO_Init(DgpioPort_ENUM port, U8 pin, DgpioDir_ENUM direction, U8 initval)
{
    U8 ret = TRUE;

    switch (port)
    {
        case PORT_DGPIO_PP: /* PP3,PP4 */
			
            if (DIR_DGPIO_INPUT == direction)
            {
                CLR_BIT(DDRP, pin); /* =0 INTPUT MODE */
            }
            else
            {
            	
                SET_BIT(DDRP, pin); /* =1 OUTPUT MODE */

                if (initval)
                {
                    SET_BIT(PTP, pin); /* =1 HIGH LEVEL OUTPUT */
                }
                else
                {
                    CLR_BIT(PTP, pin); /* =0 LOW LEVEL OUTPUT*/
                }
            }
            break;
        case PORT_DGPIO_PT: /* PT_0~4 */
			
            if (DIR_DGPIO_INPUT == direction)
            {
                CLR_BIT(DDRT, pin);/* =0 INTPUT MODE */
      
            }
            else
            {
                SET_BIT(DDRT, pin);/* =1 OUTPUT MODE */

                if (initval)
                {
                    SET_BIT(PTT, pin); /* =1 HIGH LEVEL OUTPUT */
                }
                else
                {
                    CLR_BIT(PTT, pin); /* =0 LOW LEVEL OUTPUT*/
                }
            }
            break;
        case PORT_DGPIO_PAD1: /* PAD0_0~2 */

            if (DIR_DGPIO_INPUT == direction)
            {
                CLR_BIT(DDR01AD_DDR1AD, pin);/* =0 INTPUT MODE */
            }
            else
            {

                SET_BIT(DDR01AD_DDR1AD, pin); /* =1 OUTPUT MODE. */
                if (initval)
                {
                    SET_BIT(PT01AD_PT1AD, pin); /* =1 HIGH LEVEL OUTPUT */
                }
                else
                {
                    CLR_BIT(PT01AD_PT1AD, pin); /* =0 LOW LEVEL OUTPUT*/
                }
            }
            break;
        case PORT_DGPIO_ALL: /* Do Nothing. */
            break;
        default:
            ret = FALSE;
            break;
    }

    return ret;
}
/***************************************************
* Function: dgpio_GPIO_Set
* Description: GPIO set
* Parameters:
*                  port - GPIO port
*                  pin - GPIO pin
*                  val - GPIO pin level value.
* Returns:
*            FALSE(0): set fail.
*            TRUE(1):  set success.
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-18   Version:V1.0
****************************************************/
static BOOL dgpio_GPIO_Set(DgpioPort_ENUM port, U8 pin, U8 val)
{
    U8 ret = TRUE;

    switch (port)
    {
        case PORT_DGPIO_PP: /* PP3,PP4 */
            if (val)
            {
                SET_BIT(PTP, pin); /* =1 HIGH LEVEL OUTPUT */
            }
            else
            {
                CLR_BIT(PTP, pin); /* =0 LOW LEVEL OUTPUT*/
            }
            break;
        case PORT_DGPIO_PT: /* PT_0~4 */
            if (val)
            {
                SET_BIT(PTT, pin); /* =1 HIGH LEVEL OUTPUT */
            }
            else
            {
                CLR_BIT(PTT, pin); /* =0 LOW LEVEL OUTPUT*/
            }
            break;
        case PORT_DGPIO_PAD1: /* PAD0_0~2 */
            if (val)
            {
                SET_BIT(PT01AD_PT1AD, pin); /* =1 HIGH LEVEL OUTPUT */
            }
            else
            {
                CLR_BIT(PT01AD_PT1AD, pin); /* =0 LOW LEVEL OUTPUT*/
            }
            break;
        default:
            ret = FALSE;
            break;
    }

    return ret;
}

/***************************************************
* Function: dgpio_GPIO_Get
* Description: GPIO get
* Parameters:
*                  port - GPIO port
*                  pin - GPIO pin
*                  pVal - get the pin level.
* Returns:
*            FALSE(0): get fail.
*            TRUE(1):  get success.
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-18   Version:V1.0
****************************************************/
static BOOL dgpio_GPIO_Get(DgpioPort_ENUM port, U8 pin, U8 *pVal)
{
    BOOL ret = TRUE;

    switch (port)
    {
        case PORT_DGPIO_PP: /* PP3,PP4 */
            if (GET_BIT(PTIP, pin))
            {
                *pVal = 0x01;
            }
            else
            {
                *pVal = 0x00;
            }
            break;
        case PORT_DGPIO_PT: /* PT_0~4 */
            if (GET_BIT(PTIT, pin))
            {
                *pVal = 0x01;
            }
            else
            {
                *pVal = 0x00;
            }
            break;
        case PORT_DGPIO_PAD1: /* PAD0_0~2 */
            if (GET_BIT(PTI01AD_PTI1AD, pin))
            {
                *pVal = 0x01;
            }
            else
            {
                *pVal = 0x00;
            }
            break;
      
        default:
            ret = FALSE;
            break;
    }

    return ret;
}


/***************************************************
* Function: DIO_GetInitStatus
* Description: 获取DGPIO模块的初始化状态
* Parameters: none
* Returns:
*            FALSE(0): 未初始化
*            TRUE(1): 已初始化
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-18   Version:V1.0
****************************************************/

BOOL  DGPIO_GetInitStatus(void)
{
    return Dgpio_Status;
}
/***************************************************
* Function: DGPIO_Init
* Description: DGPIO initialization.
* Parameters: none
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-18   Version:V1.0
****************************************************/
void  DGPIO_Init(void)
{
    U8 k = 0;
    BOOL res = TRUE;

   for (k = 0; k < INDEX_DGPIO_ALL; k++)
    {
        res = dgpio_GPIO_Init(GpioList[k].port, GpioList[k].pin, GpioList[k].dir, GpioList[k].initval);
        if (FALSE == res)
        {
            Dgpio_Status = FALSE;
            return;
        }
		else
		{
		}
    }

    Dgpio_Status = TRUE;
}

/***************************************************
* Function: DGPIO_SetIOSts
* Description: 用于设置IO端口的高低状态
* Parameters:
*               Input:
*                    Index -指示IO端口的索引号，对应的IO口的物理索引值
*                    pRes - 回读检测设置的状态
*                    PinLevel - 设置电平的状态
* Returns:
*           FALSE(0):函数执行失败
*           TRUE(1):函数执行成功
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-18   Version:V1.0
****************************************************/

U8  DGPIO_SetIOSts(U16 Index,U8 PinLevel,PU8 pRes)
{
    U8 res = RET_FAIL;

    if (FALSE == Dgpio_Status)
    {
        res = RET_FAIL;
    }
    else if ((NULL == pRes) || (Index >= INDEX_DGPIO_ALL))
    {
        res  = RET_INVALID;
    }
    else
    {
            if (DIR_DGPIO_OUTPUT != GpioList[Index].dir)
            {
                res  = RET_FAIL;
            }
            else if (FALSE == dgpio_GPIO_Set(GpioList[Index].port, GpioList[Index].pin, PinLevel))
            {
                res  = RET_FAIL;
            }
            else if (FALSE == dgpio_GPIO_Get(GpioList[Index].port, GpioList[Index].pin, pRes)) /* read back. */
            {
                res  = RET_FAIL;
            }
            else
            {
                res  = RET_OK;
            }
    }
    return res ;
}

/***************************************************
* Function: DGPIO_GetIOSts
* Description: 用于获取IO端口的高低状态
* Parameters: Input:
*                  Index -指示IO端口的索引号，对应的IO口的物理索引值
*                  PinLevel - IO端口的高低状态

*           FALSE(0):函数执行失败
*           TRUE(1):函数执行成功

* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-18   Version:V1.0
****************************************************/

U8  DGPIO_GetIOSts(U16 Index,PU8 PinLevel)
{
   U8 dioiores;

    if (FALSE == Dgpio_Status)
    {
        dioiores = RET_FAIL;
    }
    else if ((NULL == PinLevel) || (Index >= INDEX_DGPIO_ALL))
    {
        dioiores = RET_INVALID;
    }
    else
    {
        if (DIR_DGPIO_INPUT != GpioList[Index].dir)
        {
            dioiores = RET_FAIL;
        }
        else
        {
            if (TRUE ==dgpio_GPIO_Get(GpioList[Index].port, GpioList[Index].pin, PinLevel))
            {
                dioiores = RET_OK;
            }
            else
            {
            }
        }
    }
    return dioiores;
}

 void DGPIO_GPIO_Dlayus(U32 cnt)
 {
        U32 counter = 1000;
        for( ;0 != cnt;cnt --)
        {
            for(; 0 != counter;counter--)
            {
               ;
            }
         }
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
* V1.0       Jason.Sun      2018-05-18      Initial
*
*===========================================================================*/

