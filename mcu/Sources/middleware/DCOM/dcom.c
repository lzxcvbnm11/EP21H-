/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : dcom.c
* Description : DCOM module middleware
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* Files for including */
#include "dcom_info.inc"


static BOOL dcom_InitStatus = FALSE;                     /* DCOM初始化状态，默认值为FALSE */
static DcomSendMsg_ST dcom_SendMsg;     						 /* ADM值*/
static DcomRecvMsg_ST dcom_RecvMsg;

/***************************************************
* Function: DCOM_Init
* Description: ADM module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void DCOM_Init(void)
{
   PU8 Pdcomdata = (PU8)&dcom_SendMsg;
   U8 i = 0;
   
   dcom_InitStatus =  DSPI_GetInitStatus();
   
   dcom_SendMsg.header_h = Header_H;                 /*数据头高8位*/        
   dcom_SendMsg.header_l = Header_L;                 /*数据头低8位*/          
   dcom_SendMsg.length = (U8)sizeof(dcom_SendMsg);   /*数据长度*/             
   dcom_SendMsg.vehspeed_h = 0;                          /*车速高8位*/
   dcom_SendMsg.vehspeed_l = 0;       				 /*车速低8位*/
   dcom_SendMsg.gearmode = 0;					/*档位选择 默认 P档 0x00*/
   dcom_SendMsg.pasenable = 1;					/*声音播发默认使能*/
   dcom_SendMsg.passltreq = 0;					/*语音提示音选择*/
   dcom_SendMsg.pasvolreq = 6;					/*音量值*/
   dcom_SendMsg.pasenginereq = 0;			/*发动机音量选择*/
   dcom_SendMsg.crc = 0;						  /*校验位*/
  
   dcom_RecvMsg.header_h = 0;                    
   dcom_RecvMsg.header_l = 0;                       
   dcom_RecvMsg.length = (U8)sizeof(dcom_RecvMsg);
   dcom_RecvMsg.passltsts = 0;                          /*车身提醒音*/
   dcom_RecvMsg.pasvolval = 0;       				 /*车外提醒音状态*/
   dcom_RecvMsg.pasenablests = 0;					/*发动机模拟声开关*/
   dcom_RecvMsg.psaenginersts = 0;					/*行人警示控制系统故障*/
   dcom_RecvMsg.reserve0 = 0;					/*行人警示控制音响故障*/
   dcom_RecvMsg.reserve1 = 0;  
   dcom_RecvMsg.reserve2 = 0;			/*发动机音量选择*/
   dcom_RecvMsg.crc = 0;
	
}                            
              
/***************************************************
* Function: DCOM_Process_20ms 
* Description: the process of the DCOM module
* Parameters: PSendMsg   PRvceMsg  len 
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
BOOL DCOM_Process(PU8 PSendMsg, PU8 PRvceMsg, U8 len)
{
    PU8 Pdcomdata = (PU8)&dcom_SendMsg;
    PU8 Precvdata = (PU8)&dcom_RecvMsg;
    U8 i = 0;
    BOOL ret = RET_FAIL;
    U16 CRCRecv = 0;
    U8 SendBufTmp[18] = {0};
    U8 RecvBufTmp[18] = {0};

    if (FALSE == dcom_InitStatus)
    {
        ;     
    }
    else
    {	
        for( i = 0; i < len; i++ )       //
        {
            *(Pdcomdata + i + 3) = *PSendMsg++;
        }
    }
    
    dcom_SendMsg.crc = 0;
    dcom_SendMsg.crc = CRC_CKECKSUM(Pdcomdata, dcom_SendMsg.length);
    
    ret = DSPI_SPIStart();	
	
	ret = DSPI_Master_Com_Bytes(Pdcomdata,Precvdata,(U16)(len + 4));
    ret = DSPI_SPIStop();
    
    Precvdata = (PU8)&dcom_RecvMsg;
    
    CRCRecv = dcom_RecvMsg.crc;
    dcom_RecvMsg.crc = 0;
    dcom_RecvMsg.crc = CRC_CKECKSUM((PU8)&dcom_RecvMsg, dcom_RecvMsg.length);

	if(dcom_RecvMsg.crc == CRCRecv) 
	{
    	for( i=0; i < 4; i++)
    	{ 
    		*PRvceMsg++ = *(((PU8)&dcom_RecvMsg)+i+3);
    	}

	}
	else 
	{
		PRvceMsg[0] = 0xff;
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
U8 CRC_CKECKSUM(PU8 PuchMsg, U8 length) 
{
	U16 sum = 0;
    U8 CheckSum = 0;
    
    while(length--) 
    {
        sum += *(PuchMsg++);
    }
    
    sum = (sum >> 8) + (sum&0xff);
    CheckSum = (U8)((~sum)&(0xff));
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
BOOL DCOM_GetInitStatus(void)
{
    return dcom_InitStatus;
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

