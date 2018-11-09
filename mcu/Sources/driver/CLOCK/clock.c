/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : clock.c
* Description : clock configuration.
* Author: Jason.Sun
* Date: 2018-05-22
******************************************************************************/

/* Files for including */
#include "clock_info.inc"

/*--------------- Global variable definition and initialization -----------------*/
static U8 Clock_Status = FALSE;
/*---------------------- Implementation of module ---------------------*/
/***************************************************
* Function: Clock_Init.
* Description: Clock Initialization.
* Parameters: none
* Returns: none
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-22   Version:V1.0
****************************************************/
void CLOCK_Init(void)
{
    Clock_Status = FALSE;

    clock_OscCfg();                                /* Clock oscillation         */

	Clock_Status = TRUE;
}

/***************************************************
* Function: CLOCK_GetInitStatus
* Description: get the CLOCK module init status.
* Parameters: none
* Returns:
*            FALSE(0): init failure
*            TRUE(1): init success.
*
* $Create & Verlog:$
* Author:Qinhui.Shen  Date:2018-05-22   Version:V1.0
****************************************************/
U8 CLOCK_GetInitStatus(void)
{
    return Clock_Status;
}

/******************************************************************************
* Function Name : static void clock_OscCfg( void )
* Description   : This function oscillates the clock (bus clock PLL clock).
*                       MainOSC=8MHz, fPLLCLK=32MHz, fBUSCLK =16MHZ
* Argument      : none
* Return Value  : none
******************************************************************************/
static void clock_OscCfg(void)
{

	CPMUPROT = 0x26;
	
	CPMUOSC_OSCE = 0x01; /*external osc enable*/
	
	while(CPMUFLG_UPOSC == 0) /* 等待PLL电路对晶振电路的认证 */
	{ 
		CPMUARMCOP=0x55;CPMUARMCOP=0xAA; /* 清内置看门狗 */
    }
	
	CPMUREFDIV = 0x41;	/* fosc = 8 MHz	fref = fosc / (REFDIV+1) = 4 MHz  */
                                    
	
	CPMUSYNR = 0x03;	/* fVCO = 2 * fREF * (SYNDIV + 1) =32MHZ*/

	
	CPMUPOSTDIV = 0x00U;/* fPLL = fvco  = 32MHZ */

	while(!CPMUFLG_LOCK) /* 等待VCO CLK时钟稳定 */
	{
		CPMUARMCOP=0x55;CPMUARMCOP=0xAA; /* 清内置看门狗 */
	};
	
	/*
	Bit0 PROT
	 =0 Protection of clock configuration registers is disabled.
	 =1 Protection of clock configuration registers is enable.
	*/
	
	CPMUCLKS = 0x80U; /* 开启PLL电路 */
	/*
	在写CPMUCLKS寄存器后, 强烈推荐读回CPMUCLKS寄存器,
	确保写PLLSEL, RTIOSCSEL,COPOSCSEL0和COPOSCSEL1成功
	*/
	if(CPMUCLKS != 0B10000011)
	{
	  asm nop;
	  CPMUARMCOP=0x55;CPMUARMCOP=0xAA; /* 清内置看门狗 */
	}

	CPMUPROT = 0x00U; /* Enable protection of clock configuration registers */

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
* V1.0       Jason.Sun      2018-05-22      Initial, for "R7F701402" RH850/D1L2
*
*===========================================================================*/

