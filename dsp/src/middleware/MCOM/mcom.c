/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : mcom.c
* Description : DCOM module middleware
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* Files for including */
#include "mcom_info.inc"

enum RecvDataTest{
   length = 2,
   vehspeed_h ,
   vehspeed_l ,
   gearmode ,
   pasenable ,
   passltreq ,
   pasvolreq ,
   pasenginereq ,
   crc ,
};
static BOOL mcom_InitStatus = FALSE;
 extern int Rx_bufferflag;
 extern volatile int SPIB_irq_flag;
 extern int Rx_buffer[SPIB_MAXSENDBUFFSIZE];
 extern int Tx_buffer[SPIB_MAXSENDBUFFSIZE];

/***************************************************
* Function: DCOM_Init
* Description: ADM module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void MCOM_Init(void)
{

   u8 i = 0;
   
   mcom_InitStatus =  1;//SPIB_GetInitSts();

}                            


int DSPI_Master_Com_Bytes( PU8 Pmcomdata, PU8 mcom_RecvMsg, U16 length)
{
	int ret = 0 ;
	int i = 0;
	int GetByte = 0;
	char test_buf[11] = {0};

//	if(Rx_bufferflag >= SPIB_MAXSENDBUFFSIZE)
	{
		for(i=0;i<SPIB_MAXSENDBUFFSIZE;i++)
			{
				Tx_buffer[i] = Pmcomdata[i];
				*mcom_RecvMsg++ = Rx_buffer[i];
				test_buf[i] = Rx_buffer[i];
			}
		Rx_bufferflag = 0;
	}



	return 0;
}
/***************************************************
* Function: DCOM_Process_20ms 
* Description: the process of the DCOM module
* Parameters: PSendMsg   PRvceMsg  len 
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
BOOL MCOM_Process_20ms(PU8 PSendMsg, PU8 PRvceMsg, u8 len)
{
	static u8 LossDatacnt = 0;
	u8 SpiDefaultDtat[SPIB_MAXSENDBUFFSIZE] = {0,0,11,0,0,0,0,0,11,31,0};
	BOOL ret = RET_FAIL;
	short RecvCRC = 0;
	u8 ReceiveTemp[SPIB_MAXSENDBUFFSIZE];

	if((PRvceMsg == NULL) || (PSendMsg == NULL)) return ret;
	if(len <= 0) return ret;

	PSendMsg[crc] = 0;
	PSendMsg[crc] = CRC_CKECKSUM(PSendMsg, len);

    ret = DSPI_Master_Com_Bytes( PSendMsg, ReceiveTemp, len);

    RecvCRC = ReceiveTemp[crc];
    ReceiveTemp[crc] = 0;
    ReceiveTemp[crc] = CRC_CKECKSUM(ReceiveTemp, SPIB_MAXSENDBUFFSIZE);
    if(RecvCRC != ReceiveTemp[crc])
    {
    	/*lzx  recvdata error*/
    	LossDatacnt++;
    	sysreg_bit_clr( sysreg_FLAGS,FLG6O );
    	if(LossDatacnt == MCOM_MAXLOSTDATACNT)
    	{
    		sysreg_bit_set( sysreg_FLAGS,FLG6O );
    		memcpy(PRvceMsg,SpiDefaultDtat,SPIB_MAXSENDBUFFSIZE);
    		LossDatacnt = 0;
    	}

    	return RET_FAIL;
    }
	else
	{
		if(len > SPIB_MAXSENDBUFFSIZE) len = SPIB_MAXSENDBUFFSIZE;
		memcpy(PRvceMsg,ReceiveTemp,len);
		LossDatacnt = 0;
		ret = RET_OK;
	}

	return ret;
}
/***************************************************
* Function: CRC_CKECKSUM 
* Description: the process of the ADM module
* Parameters: PuchMsg   length
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
u8 CRC_CKECKSUM(PU8 PuchMsg, u8 length)
{
    unsigned short sum = 0;
    u8 CheckSum = 0;

    while(length--) 
    {
        sum += *(PuchMsg++);
    }
    
    sum = (sum >> 8) + (sum&0xff);
    CheckSum = (u8)((~sum)&0xff);
    return CheckSum;
}
/***************************************************
* Function: DCOM_GetInitStatus
* Description: get the ADM module initialized status
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
BOOL MCOM_GetInitStatus(void)
{
    return mcom_InitStatus;
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

