/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : dspi.c
* Description : Driver source file of DSPI.
* Author: Jason.Sun
* Date: 2018-05-24
******************************************************************************/

/* Files for including */
#include "dspi_info.inc"

/*--------------- Global variable definition and initialization -----------------*/
static BOOL Dspi_Status = FALSE;

/*---------------------- Implementation of module ---------------------*/
/***************************************************
* Function: DSPI_Init
* Description: DSPI initialization.
* Parameters: none
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-24   Version:V1.0
****************************************************/
void DSPI_Init(U8 BaudRat,U8 Mode)
{
   	SPI1CR2 = SPI1CR2_MODFEN_MASK;  // SS pin is used by SPI

	if (Mode == MASTER) //SPI enabled; Master mode; Active high clocks; Slave Select output enabled     
	{
		SPI1CR1 = SPI1CR1_SPE_MASK + SPI1CR1_MSTR_MASK + SPI1CR1_CPHA_MASK;/* */   
	} 
	else if (Mode == SLAVE) //SPI enabled; Slave mode; Active high clocks; Slave Select output enabled 
	{
		SPI1CR1 = SPI1CR1_SPE_MASK + SPI1CR1_CPHA_MASK + SPI1CR1_SSOE_MASK;   
	}
      
	/* 
	BaudRateDivisor = (SPPR + 1) * 2^(SPR + 1)  
	Baud Rate = BusClock / BaudRateDivisor 
	*/
	// please specify global_bus_clock before select baud rate.
	switch(BaudRat) // Bus clock is 24M 
	{
		case SPI_1M_HZ: 			
			SPI1BR =  0x12; //divisor=16, SPI baud rate=1M			
			break;		
		default: 		
			SPI1BR =  0x23;
			break;
	}

    Dspi_Status = TRUE;
}

/***************************************************
* Function: DSPI_GetInitStatus
* Description: get DSPI module initialization status.
* Parameters: none
*               
*                   
* Returns:
*           the value of the Init status.
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-24   Version:V1.0
****************************************************/
U8 DSPI_GetInitStatus(void)
{
    return Dspi_Status;
}


/***************************************************
* Function: DSPI_SPIStop
* Description: stop SPI
* Parameters:none
*               
*                      
* Returns:
*            RET_FAIL
*            RET_OK
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-24   Version:V1.0
*  $log: only a 'return'
****************************************************/
U8  DSPI_SPIStop(void)
{
    U8 retVal = RET_OK;

    if (FALSE == Dspi_Status)
    {
        retVal = RET_FAIL;
    }
    else
    {
		SPI1CR1_SSOE = 0;

    }
    return retVal;
}


/***************************************************
* Function: DSPI_SPIStart
* Description: start SPI.
* Parameters:
*               Input:
*                      SPIHdl -specify the handle of the DSPI.
* Returns:
*            RET_FAIL
*            RET_OK
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-24   Version:V1.0
*  $log: only a 'return'
****************************************************/
U8  DSPI_SPIStart(void)
{
    U8 retVal = RET_OK;

    if (FALSE == Dspi_Status)
    {
         retVal = RET_FAIL;
    }
    else
    {
		SPI1CR1_SSOE = 1;

    }
    return retVal;
}
/***************************************************
* Function: DSPI_Master_Com_Byte
* Description: DSPI Master commucation .
* Parameters: none
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-24   Version:V1.0
****************************************************/

BOOL DSPI_Master_Com_Byte(	U8 tx_value, U8 *p_rx)
{ 
	U16 dspi_outtimecnt = 0;
	U8 chRcv = 0;
   /*æ¸…ç©ºåŒç¼“å­?*/
   (void)SPI1DR;
   (void)SPI1SR;
   (void)SPI1DR; 
    
    SPI1CR2_XFRW = DATA_WIDTH_8;
     
    #warning /*here need supply a out_time function*/
    while (SPI1SR_SPTEF == DATA_NOT_EMPTY)      /*make sure SPTEF = 1*/
    {
#if DSPI_NO_OUTTIMEFUN
        NOP;
#else
		if(dspi_outtimecnt == DSPI_OUTTIMECOUNT)/*out_time function*/
		{
			return RET_FAIL;
		}
		else
		{
        	dspi_outtimecnt++;
		}
#endif

    }
    dspi_outtimecnt = 0;
    while (SPI1SR_SPIF == RECEIVE_NEW_DATA)  /*make sure SPIF = 0*/
    {
#if DSPI_NO_OUTTIMEFUN
        NOP;
#else
		if(dspi_outtimecnt == DSPI_OUTTIMECOUNT)/*out_time function*/
		{
			return RET_FAIL;
		}
		else
		{
        	dspi_outtimecnt++;
		}
#endif

    }
    
    _SPI1DR.Overlap_STR.SPI1DRLSTR.Byte = tx_value;
   
    #warning/*here need supply a out_time function*/  
	dspi_outtimecnt = 0;
    while (SPI1SR_SPIF == DATA_TRANSMITING) /*åˆ¤æ–­æ•°æ®æ˜¯å¦å‘é?å®Œæ¯•ï¼Œå¹¶ä¸”æŽ¥å—åˆ°æ–°çš„æ•°æ?*/
    {      
#if DSPI_NO_OUTTIMEFUN
        NOP;
#else
		if(dspi_outtimecnt == DSPI_OUTTIMECOUNT)/*out_time function*/
		{
			chRcv = _SPI1DR.Overlap_STR.SPI1DRLSTR.Byte;
			DSPI_Init(SPI_1M_HZ,MASTER);
			return RET_FAIL;
		}
		else
		{
        	dspi_outtimecnt++;
		}
#endif
    } 
     
    *p_rx = _SPI1DR.Overlap_STR.SPI1DRLSTR.Byte;    
        
    return TRUE;
      
}
/***************************************************
* Function: DSPI_Master_Com_Bytes
* Description: DSPI Master commucation slave.
* Parameters: p_tx,p_rx,len
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-24   Version:V1.0
****************************************************/

BOOL DSPI_Master_Com_Bytes(	U8* p_tx, U8 *p_rx,U16 len)
{
	U16 i;
	for(i=0;i<len;i++) 
	{  
		if(DSPI_Master_Com_Byte(p_tx[i],&p_rx[i])!=TRUE) return FALSE;
	//   	DSPI_Dlay100us(DLAY_1MS);
	}
	return TRUE;
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
* V1.0       Jason.Sun      2018-05-24      Initial
*
*===========================================================================*/

