/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : ds.c
* Description : DS module app
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* Files for including */
#include "ds_info.inc"


static BOOL ds_InitStatus = RET_FAIL;              
static BOOL ds_PowrOnComStatus = FALSE;
static BOOL ds_SpiFltStatus = FALSE;
static DsSendMsg_ST ds_SendMsg;    
static DsSendMsg_ST ds_SendMsgLast;
static DsRecvMsg_ST ds_RecvMsgLast;
static DsRecvMsg_ST ds_RecvMsg;
static U8 NowGreamode = 0;
static U8 OldGreamode = 0;
static U8 ds_PedtrnAlrtInSwEnable = 0;
static U8 ds_PedtrnAlrtInSwEnableLast = 0;

#define DSP_COMM_ERR_RESET_ENABLE    1
#define DS_POWERONCOMSTATUSCOUNT     5

/***************************************************
* Function: DS_Init
* Description: ADM module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void DS_Init(void)
{
   PU8 PDsSend = (PU8)&ds_SendMsg;
   PU8 PDsSendlast = (PU8)&ds_SendMsgLast;
   PU8 PDssRecvLast = (PU8)&ds_RecvMsgLast;
   PU8 PDssRecv = (PU8)&ds_RecvMsg;
   //U8 i = 0;
   //U8 len = 0;
   U8 res = FALSE;
   
   ds_InitStatus = DCOM_GetInitStatus();

   ds_SendMsg.vehspeed_h = 0;                          
   ds_SendMsg.vehspeed_l = 0;       				 
   ds_SendMsg.gearmode = 0;					
   ds_SendMsg.pasenable = 0;				
   ds_SendMsg.passltreq = 0;					
   ds_SendMsg.pasvolreq = 0;					
   ds_SendMsg.pasenginereq = 0;	
   
   ds_SendMsgLast.vehspeed_h = 0;                          
   ds_SendMsgLast.vehspeed_l = 0;       				 
   ds_SendMsgLast.gearmode = 0;					
   ds_SendMsgLast.pasenable = 0;				
   ds_SendMsgLast.passltreq = 0;					
   ds_SendMsgLast.pasvolreq = 0;					
   ds_SendMsgLast.pasenginereq = 0;
  
   ds_RecvMsg.passltsts = 0;                          
   ds_RecvMsg.pasvolsts = 0;       				
   ds_RecvMsg.pasenablests = 1;				
   ds_RecvMsg.psaenginersts = 1;	
   
   ds_RecvMsgLast.passltsts = 0;                          
   ds_RecvMsgLast.pasvolsts = 0;       				
   ds_RecvMsgLast.pasenablests = 1;				
   ds_RecvMsgLast.psaenginersts = 1;


}                            	
             
/***************************************************
* Function: DS_Process_20ms 
* Description: the process of the ADM module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void DS_Process_20ms(void)
{
    static U8 RecvFromDspCnt = 0;
	static U8 FirstTurnOnRecvFromDspCnt = 0;
	static U8 ds_PowrOnComStatusCnt = 0;
    static U8 DspResetFlag = 0;
    PU8 PDsSendMsg = (PU8)&ds_SendMsg;
	PU8 PDsSendMsgLast = (PU8)&ds_SendMsgLast;
  	PU8 PDsRvceMsgLast = (PU8)&ds_RecvMsgLast;
  	PU8 PDsRvceMsg = (PU8)&ds_RecvMsg;
    U8 i = 0;
    BOOL ret = RET_FAIL;
   	U8 len;
  	U16 vehspeed = 0;
  	U8 datalen = 0x01;
	U8 ds_BatMode,ds_PwrMcuMode;
	v_nwm_state nwm_state;
	
    if (RET_FAIL == ds_InitStatus)
    {
     ;     
    }
    else
    {
    	# if 0
     	ds_RecvMsg.pasenablests = 0xff;
	    len = sizeof(ds_SendMsg); 
	    DS_GetInformation();
        ret = DCOM_Process(PDsSendMsg, PDsRvceMsg, len);

		switch (ds_RecvMsg.pasvolsts)
	  	{
	  		case 0x10:
			  ds_RecvMsg.pasvolsts = PEDTRNALRTRVCELOW;
			  break;
			case 0x1f:
	      	  ds_RecvMsg.pasvolsts = PEDTRNALRTRVCEHIGH;
		      break; 
			default:
			  break;
	  	}

	 // printp("-%d-%d-%d---%d-%d-%d-\n",ds_RecvMsg.passltsts,ds_RecvMsg.pasvolsts,ds_RecvMsg.pasenablests,ds_RecvMsgLast.passltsts,ds_RecvMsgLast.pasvolsts,ds_RecvMsgLast.pasenablests);
		PWR_GetPwrMode(&ds_PwrMcuMode);
		ds_BatMode = BAT_GetBatVoltageSts();
		
		if((ds_RecvMsg.psaenginersts != ds_RecvMsgLast.psaenginersts)				   
		||(ds_RecvMsg.pasvolsts != ds_RecvMsgLast.pasvolsts)
		||(ds_RecvMsg.pasenablests != ds_RecvMsgLast.pasenablests))
		{
		  for( i=0; i < 4; i++)
			{
				*(PDsRvceMsgLast + i) = *(PDsRvceMsg + i);
			}
			
			ret =NVM_SetParas(INDEX_NVM_PEDTRN_ALRT_SND_SLT ,  (PU8) &(ds_RecvMsgLast.psaenginersts), datalen);
			ret =NVM_SetParas(INDEX_NVM_PEDTRN_ALRT_SND_VOL ,  (PU8) &(ds_RecvMsgLast.pasvolsts), datalen);


			if((ds_BatMode <= STATUS_BAT_CAN) && (ds_PwrMcuMode == PWR_MCU_WORK_MODE_NORMAL))
			{	
      			COM_SetSignalValue_8(INDEX_COM_SEND_PedtrnAlrtVolSwSts_4bit, (U8)(ds_RecvMsgLast.pasvolsts));
      			COM_SetSignalValue_8(INDEX_COM_SEND_PedtrnAlrtSndSltSts_2bit, (U8)(ds_RecvMsgLast.psaenginersts));
		    	//COM_SetSignalValue_8(INDEX_COM_SEND_PedtrnAlrtInh_2bit, !(U8)(ds_PedtrnAlrtInSwEnable));
		      //COM_SetSignalValue_8(INDEX_COM_SEND_PedtrnAlrtInh_2bit, !(U8)(ds_RecvMsgLast.pasenablests));
			}
			else
			{
			}

		}
		if((ds_BatMode <= STATUS_BAT_CAN) && (ds_PwrMcuMode == PWR_MCU_WORK_MODE_NORMAL))
		{
			COM_SetSignalValue_8(INDEX_COM_SEND_PedtrnAlrtInh_2bit, !(U8)(ds_PedtrnAlrtInSwEnable)); 
			//COM_SetSignalValue_8(INDEX_COM_SEND_PedtrnAlrtInh_2bit, !(U8)(ds_RecvMsgLast.pasenablests));
		}
		else
		{
		}
		#endif
		
	# if 1
		ds_RecvMsg.pasenablests = 0xff;
	    len = sizeof(ds_SendMsg); 
	    DS_GetInformation();
		
		if((ds_SendMsg.pasenginereq != ds_SendMsgLast.pasenginereq)				   
		||(ds_SendMsg.pasvolreq != ds_SendMsgLast.pasvolreq)
		||(ds_PedtrnAlrtInSwEnable != ds_PedtrnAlrtInSwEnableLast))
		{
		  for( i=0; i < 7; i++)
			{
				*(PDsSendMsgLast + i) = *(PDsSendMsg + i);
			}
		  ds_PedtrnAlrtInSwEnableLast = ds_PedtrnAlrtInSwEnable;
			
			ret =NVM_SetParas(INDEX_NVM_PEDTRN_ALRT_SND_SLT ,  (PU8) &(ds_SendMsgLast.pasenginereq), datalen);
			ret =NVM_SetParas(INDEX_NVM_PEDTRN_ALRT_SND_VOL ,  (PU8) &(ds_SendMsgLast.pasvolreq), datalen);

			PWR_GetPwrMode(&ds_PwrMcuMode);
			ds_BatMode = BAT_GetBatVoltageSts();
			
			if((ds_BatMode > STATUS_BAT_CAN) || (ds_PwrMcuMode == PWR_MCU_WORK_MODE_SILENT))
			{	
			}
			else
			{
      			COM_SetSignalValue_8(INDEX_COM_SEND_PedtrnAlrtVolSwSts_4bit, (U8)(ds_SendMsgLast.pasvolreq));
      			COM_SetSignalValue_8(INDEX_COM_SEND_PedtrnAlrtSndSltSts_2bit, (U8)(ds_SendMsgLast.pasenginereq));
		    	COM_SetSignalValue_8(INDEX_COM_SEND_PedtrnAlrtInh_2bit, !(U8)(ds_PedtrnAlrtInSwEnable));
			}
		}
#if 1
		switch (ds_SendMsg.pasvolreq)
  		{
	  		case 0x05:
			  ds_SendMsg.pasvolreq = PEDTRNALRTLOW;
			  break;
			case 0x06:
	      	  ds_SendMsg.pasvolreq = PEDTRNALRTHIGH;
		      break; 
			default:
			  break;
  		}
#endif
	nwm_state = COM_GetNwmState();
	if(V_NWM_NORMAL != nwm_state)
	{	
		ds_SendMsg.pasvolreq = 0x0;
	}
		ret = DCOM_Process(PDsSendMsg, PDsRvceMsg, len);
		#endif
		
		#if 0
		 if(ds_PowrOnComStatusCnt >= DS_POWERONCOMSTATUSCOUNT)
		{
			ds_PowrOnComStatus = TRUE;
			//ds_PowrOnComStatusCnt = 0;
		}
		else
		{
			ds_PowrOnComStatusCnt++;
		}
		#endif
		
        if(PDsRvceMsg[0] == 0xff) 
        {
        	if(RecvFromDspCnt < DS_DSPRESTCNT) 
			{
				RecvFromDspCnt++;
			}
     	}
     	else 
        {
         	RecvFromDspCnt = 0;
			ds_SpiFltStatus = FALSE;
			if(ds_PowrOnComStatusCnt >= DS_POWERONCOMSTATUSCOUNT)
			{
				ds_PowrOnComStatus = TRUE;
			}
			else
			{
				ds_PowrOnComStatusCnt++;
			}
     	}

		if(FirstTurnOnRecvFromDspCnt >= DS_DSPFIRSTRESTCNT) 
		{
			if((RecvFromDspCnt >= DS_DSPRESTCNT) && (DspResetFlag == 0))
			{
				DspResetFlag = 1;
				ds_SpiFltStatus = TRUE;
				#if DSP_COMM_ERR_RESET_ENABLE
				IOM_SetOutPutLevel(INDEX_IOM_DSP_RES,0);/* dsp reset */
				#endif
			}
			else if (DspResetFlag == 1)
			{
				DspResetFlag = 0;
				RecvFromDspCnt = 0;
				#if DSP_COMM_ERR_RESET_ENABLE
				IOM_SetOutPutLevel(INDEX_IOM_DSP_RES,1);/* dsp reset */
				#endif
				FirstTurnOnRecvFromDspCnt = 0;
			}
		}
		else
		{
			FirstTurnOnRecvFromDspCnt++;
		}

    }
    
}

/***************************************************
* Function: DS_GetInitStatus
* Description: get the ADM module initialized status
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
BOOL DS_GetInitStatus(void)
{
    return ds_InitStatus;
}


/***************************************************
* Function: DS_GetInformation
* Description: get the information
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:lzx  Date:2018-06-05   Version:V1.0
****************************************************/
void DS_GetInformation(void)
{	
  float pSpeedVaule = 0;
  U16 SpeedIntVaule = 0;
  U8  SpeedDecimalVaule = 0;
  AccGearLvl_ENUM  Gearmode = 1;
  U8  PedtrnSystemVolume = 0;
  U8  PedtrnAdoWrnngJudgeEnable = 0;
  
  ACC_GetGearSts(&Gearmode);
  if(Gearmode >= 0x04)
  {
  		ds_SendMsg.gearmode = 0x03; 		
  }
  else
  {
  		ds_SendMsg.gearmode = (U8)(Gearmode - 1);
  }  
	
  ACC_GetSpeedValue(&pSpeedVaule);
  SpeedIntVaule = (U16)pSpeedVaule;
  ds_SendMsg.vehspeed_l = (U8)(SpeedIntVaule &0xff);
  ds_SendMsg.vehspeed_h = (U8)((SpeedIntVaule &0x1ff)>>8);
  
  SpeedDecimalVaule = ((U8)((pSpeedVaule - SpeedIntVaule)*100));
  
  
  ds_SendMsg.vehspeed_h +=   SpeedDecimalVaule * 2;
  
  
  ACC_GetPedestrianAlertSoundSelect((PU8) &(ds_SendMsg.pasenginereq));
  
  ACC_GetPedtrnAlrtJudgeEnable((PU8) &(ds_SendMsg.pasenable));
  
  ACC_GetPedtrnAdoWrnng((PU8) (&ds_SendMsg.passltreq));

  ACC_GetPedtrnSystemVolume((PU8)(&ds_SendMsg.pasvolreq));

  #if 0
  ACC_GetPedtrnSystemVolume((PU8)(&PedtrnSystemVolume));
  
  switch (PedtrnSystemVolume)
  {
  		case 0x05:
		  ds_SendMsg.pasvolreq = PEDTRNALRTLOW;
		  break;
		case 0x06:
      	  ds_SendMsg.pasvolreq = PEDTRNALRTHIGH;
	      break; 
		default:
		  break;
  }
#endif
  
  ACC_GetPedtrnAlrtInSwEnable((PU8)(&ds_PedtrnAlrtInSwEnable));

}

BOOL DS_GetComsts(void)
{
	return ds_PowrOnComStatus;
}

BOOL DS_GetSpiFltSts(void)
{
	return ds_SpiFltStatus;
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

