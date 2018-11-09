/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : ds.c
* Description : DIAG module app
* Author: QQ
* Date: 2018-07-18
******************************************************************************/

/* Files for including */
#include "diag_info.inc"


static BOOL diag_InitStatus = FALSE;                   
static BOOL diag_SpdPacmFlt = FALSE;
static BOOL diag_PedtrnAlrtSpkFlt = FALSE;
static BOOL diag_PedtrnAlrtCtlSysFlt = FALSE;
static BOOL diag_DiagPhyReqFlag = FALSE;
static BOOL diag_DiagFuncReqFlag = FALSE;

static U8 diag_DiagnosticFuncAddrReq[DIAG_BYTE_ALL] = {0};
static U8 diag_DiagnosticReq[DIAG_BYTE_ALL] = {0};

/***************************************************
* Function:DIAG_Init
* Description: DIAG module initialized
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:qq  Date:2018-07-18   Version:V1.0
****************************************************/
void DIAG_Init(void)
{
	Diag_LogisticsDataRead = DIAG_ECU_ALL;
	Diag_QuietModeSts = DIAG_QUIET_EXIT_MODULE;
	DIAG_QUIETMODECOUNT = 0;
	
  diag_InitStatus = COM_GetInitSts(); 
}                            	

/***************************************************
* Function: DIAG_GetInitStatus
* Description: get the  module initialized status
* Parameters: none
* Returns: TRUE or RET_FALL
* $Create & Verlog:$
* Author:qq  Date:2018-07-18   Version:V1.0
****************************************************/
BOOL DIAG_GetInitStatus(void)
{
    return diag_InitStatus;
}

/***************************************************
* Function: DIAG_Process_10ms 
* Description: the process of the DIAG module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:QQ  Date:2018-07-18   Version:V1.0
****************************************************/
void DIAG_Process_20ms(void)
{
	U8 diag_BatMode;
	PWRMcuWorkMode_ENUM diag_PwrMcuMode;

    if (TRUE == diag_InitStatus)
    {

		PWR_GetPwrMode(&diag_PwrMcuMode);
		diag_BatMode = BAT_GetBatVoltageSts();
		if(diag_BatMode > STATUS_BAT_CAN)
		{
		}
		else
		{
			diag_PedtrnAlrtCtlSysFlt_20ms();
		}
		if(diag_BatMode > STATUS_BAT_TD_CLASSA_CAN)
		{
			Diag_QuietModeSts = DIAG_QUIET_EXIT_MODULE;/*��������ϵ�ѹ���ָ�Ĭ��*/
		}
		else
		{
			//if((diag_BatMode == PWR_MCU_WORK_MODE_DIAG) || (diag_PwrMcuMode == PWR_MCU_WORK_MODE_NORMAL))
			{
				diag_DateReceive();
				diag_LogisticsDataReadFun_20ms();
				diag_QuietModeFun_20ms();
			}
		}
    }
	else
	{
		;
	}
}
void diag_DateReceive(void)
{
	diag_DiagFuncReqFlag = FALSE;
	diag_DiagPhyReqFlag = FALSE;
	if(v_imf_rx(DIAG_PhysReq_PACM_handle))
	{
		v_rd_bytes(DiagnosticReqPACM_handle, diag_DiagnosticReq, DIAG_BYTE_ALL, 0);
		diag_DiagPhyReqFlag = TRUE;
	}

	if(v_imf_rx(DIAG_FuncReq_HSC4_handle))
	{
		v_rd_bytes(DiagnosticFuncAddrReq_handle, diag_DiagnosticFuncAddrReq, DIAG_BYTE_ALL, 0);
		diag_DiagFuncReqFlag = TRUE;
	}



}

/***************************************************
* Function: diag_LogisticsDataReadFun_10ms
* Description: get the information
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:qq  Date:2018-07-18   Version:V1.0
****************************************************/
void diag_LogisticsDataReadFun_20ms(void)
{	
	U8 i = 0; 
	U8 j = 0; 

	if(diag_DiagPhyReqFlag)
	{
		//diag_DiagPhyReqFlag = FALSE;
		if(memcmp(diag_DiagnosticReq,DiagnosticReqList[0],4) == FALSE )
		{
			v_wr_bytes(DiagnosticRespPACM_handle, DiagnosticAckPartNumber , DIAG_BYTE_ALL, 0);
			v_imf_tx(DIAG_PhysResp_PACM_handle);
			diag_DiagPhyReqFlag = FALSE;
		}
		else if (memcmp(diag_DiagnosticReq,DiagnosticReqList[1],4) == FALSE)
		{
			v_wr_bytes(DiagnosticRespPACM_handle, DiagnosticAckHardwareNumber , DIAG_BYTE_ALL, 0);
			v_imf_tx(DIAG_PhysResp_PACM_handle);
			diag_DiagPhyReqFlag = FALSE;
		}
		else if (memcmp(diag_DiagnosticReq,DiagnosticReqList[2],4) == FALSE)
		{
			v_wr_bytes(DiagnosticRespPACM_handle, DiagnosticAckSoftwareNumber , DIAG_BYTE_ALL, 0);
			v_imf_tx(DIAG_PhysResp_PACM_handle);
			diag_DiagPhyReqFlag = FALSE;
		}
	}
	else if(diag_DiagFuncReqFlag)
	{
		//diag_DiagFuncReqFlag = FALSE;
		if(memcmp(diag_DiagnosticFuncAddrReq,DiagnosticReqList[0],4) == FALSE )
		{
			v_wr_bytes(DiagnosticRespPACM_handle, DiagnosticAckPartNumber , DIAG_BYTE_ALL, 0);
			v_imf_tx(DIAG_PhysResp_PACM_handle);
			diag_DiagFuncReqFlag = FALSE;
		}
		else if (memcmp(diag_DiagnosticFuncAddrReq,DiagnosticReqList[1],4) == FALSE)
		{
			v_wr_bytes(DiagnosticRespPACM_handle, DiagnosticAckHardwareNumber , DIAG_BYTE_ALL, 0);
			v_imf_tx(DIAG_PhysResp_PACM_handle);
			diag_DiagFuncReqFlag = FALSE;
		}
		else if (memcmp(diag_DiagnosticFuncAddrReq,DiagnosticReqList[2],4) == FALSE)
		{
			v_wr_bytes(DiagnosticRespPACM_handle, DiagnosticAckSoftwareNumber , DIAG_BYTE_ALL, 0);
			v_imf_tx(DIAG_PhysResp_PACM_handle);
			diag_DiagFuncReqFlag = FALSE;
		}
	}
}

/***************************************************
* Function: diag_QuietModeFun_10ms
* Description: 
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:QQ  Date:2018-07-18   Version:V1.0
****************************************************/

void diag_QuietModeFun_20ms(void)
{	
	U8 diag_BatMode;
	
	diag_BatMode = BAT_GetBatVoltageSts();
	if(diag_BatMode != STATUS_BAT_TD_CLASSA_CAN)
	{
		Diag_QuietModeSts = DIAG_QUIET_EXIT_MODULE;
		DIAG_QUIETMODECOUNT = 0;
		return;
	}
	if (diag_DiagPhyReqFlag || diag_DiagFuncReqFlag)
	{
		DIAG_NoReceiveSignalCount = 0;
 		switch(Diag_QuietModeSts)
	 	{
			case DIAG_QUIET_MODULE:
			    	if( (memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_SESSION_KEEP],3) == FALSE ) || \
						(memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_SESSION_KEEP],3) == FALSE) || \
						(memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_SESSION_KEEP_ANOTHER],3) == FALSE ) || \
						(memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_SESSION_KEEP_ANOTHER],3) == FALSE) )
			    	{
						DIAG_QUIETMODECOUNT = 0;
					}
					#if 1
					else if( (memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_SESSION_ENTER],3) != FALSE ) && \
							 (memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_SESSION_ENTER],3) != FALSE) && \
							 (memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_SESSION_ENTER_ANOTHER],3) != FALSE ) && \
							 (memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_SESSION_ENTER_ANOTHER],3) != FALSE) )
					{
						DIAG_QUIETMODECOUNT ++;
						if(DIAG_QUIETMODECOUNT > DIAG_QUIETMODECNT)
						{	
							Diag_QuietModeSts = DIAG_QUIET_EXIT_MODULE;
						}
					}
					#endif
					if( (memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_SESSION_EXIT],3) == FALSE ) || \
						(memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_SESSION_EXIT],3) == FALSE) || \
						(memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_SESSION_EXIT_ANOTHER],3) == FALSE ) || \
						(memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_SESSION_EXIT_ANOTHER],3) == FALSE) )
					{
						Diag_QuietModeSts = DIAG_QUIET_EXIT_MODULE;
					}
					if( (memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_ECU_RESET],3) == FALSE ) || \
						(memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_ECU_RESET],3) == FALSE) || \
						(memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_ECU_RESET_ANOTHER],3) == FALSE ) || \
						(memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_ECU_RESET_ANOTHER],3) == FALSE) )
					{
						Diag_QuietModeSts = DIAG_QUIET_EXIT_MODULE;
					}

				break;
			case DIAG_QUIET_EXIT_MODULE:
					if( (memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_SESSION_ENTER],3) == FALSE ) || \
						(memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_SESSION_ENTER],3) == FALSE) || \
						(memcmp(diag_DiagnosticReq,DiagnosticMsgList[DIAG_SESSION_ENTER_ANOTHER],3) == FALSE ) || \
						(memcmp(diag_DiagnosticFuncAddrReq,DiagnosticMsgList[DIAG_SESSION_ENTER_ANOTHER],3) == FALSE) )
					{
						Diag_QuietModeSts = DIAG_QUIET_MODULE;
						DIAG_QUIETMODECOUNT = 0;
					}
				break;
			default:
				break;
			}
	}
	else
	{
		DIAG_NoReceiveSignalCount ++;
		if(DIAG_NoReceiveSignalCount > DIAG_QUIETMODECNT)
		{	
			Diag_QuietModeSts = DIAG_QUIET_EXIT_MODULE;
		}
	}
}
void diag_SetSignalValue_BOOL(U16 Index, U8 val) 
{
  switch(Index) 
  {
    case INDEX_COM_SEND_PACMFlt_1bit:
      v_wr_bool( PACMFlt_handle, val);
     	break;
    case INDEX_COM_SEND_PedtrnAlrtSpkrFlt_1bit:
      v_wr_bool( PedtrnAlrtSpkrFlt_handle, val);
     	break;
	case INDEX_COM_SEND_PedtrnAlrtCtlSysFlt_1bit:
      v_wr_bool( PedtrnAlrtCtlSysFlt_handle, val);
     	break;
    default:
      break;
     	
  }
}

void diag_PedtrnAlrtCtlSysFlt_20ms(void)
{
	U8 spd_PACMFltStatus,spd_PedtrnAlrtSpkFltStatus;
	BOOL spd_SpiFltSts;
	
	spd_PACMFltStatus = SPD_PACMFltSts();
    spd_PedtrnAlrtSpkFltStatus = SPD_PedtrnAlrtSpkFltSts();
	if(DS_GetSpiFltSts())
	{
		if(diag_SpdPacmFlt == FALSE)
		{
			diag_SetSignalValue_BOOL(INDEX_COM_SEND_PACMFlt_1bit,1);
			diag_SpdPacmFlt = TRUE;
		}
		if(diag_PedtrnAlrtCtlSysFlt == FALSE)
		{
			diag_SetSignalValue_BOOL(INDEX_COM_SEND_PedtrnAlrtCtlSysFlt_1bit,1);
			diag_PedtrnAlrtCtlSysFlt = TRUE;
		}
	}
	else
	{
		if((spd_PACMFltStatus == TRUE) && (diag_SpdPacmFlt == FALSE))
		{
			diag_SetSignalValue_BOOL(INDEX_COM_SEND_PACMFlt_1bit,1);
			diag_SpdPacmFlt = TRUE;
		}
		else if((spd_PACMFltStatus == FALSE) && (diag_SpdPacmFlt == TRUE))
		{
			diag_SetSignalValue_BOOL(INDEX_COM_SEND_PACMFlt_1bit,0);
			diag_SpdPacmFlt = FALSE;	
		}

		if((spd_PedtrnAlrtSpkFltStatus == TRUE) && (diag_PedtrnAlrtSpkFlt == FALSE))
		{
			diag_SetSignalValue_BOOL(INDEX_COM_SEND_PedtrnAlrtSpkrFlt_1bit,1);		
			diag_PedtrnAlrtSpkFlt = TRUE;
		}
		else if((spd_PedtrnAlrtSpkFltStatus == FALSE) && (diag_PedtrnAlrtSpkFlt == TRUE))
		{
			diag_SetSignalValue_BOOL(INDEX_COM_SEND_PedtrnAlrtSpkrFlt_1bit,0);	
			diag_PedtrnAlrtSpkFlt = FALSE;
		}

		if(((spd_PedtrnAlrtSpkFltStatus == TRUE)||(spd_PACMFltStatus == TRUE)) && (diag_PedtrnAlrtCtlSysFlt == FALSE))
		{
			diag_SetSignalValue_BOOL(INDEX_COM_SEND_PedtrnAlrtCtlSysFlt_1bit,1);
			diag_PedtrnAlrtCtlSysFlt = TRUE;
		}
		else if((spd_PedtrnAlrtSpkFltStatus == FALSE) && (spd_PACMFltStatus == FALSE) && (diag_PedtrnAlrtCtlSysFlt == TRUE))
		{
			diag_SetSignalValue_BOOL(INDEX_COM_SEND_PedtrnAlrtCtlSysFlt_1bit,0);
			diag_PedtrnAlrtCtlSysFlt = FALSE;
		}
	}
}

/***************************************************
* Function: DIAG_GetQuietModeStatus
* Description: 
* Parameters: none
* Returns: DiagQuietModeFun_ENUM
* $Create & Verlog:$
* Author:QQ  Date:2018-07-18   Version:V1.0
****************************************************/
DiagQuietModeFun_ENUM  DIAG_GetQuietModeStatus()
{
	return Diag_QuietModeSts;
}

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       QQ      2018-07-18      Initial
*
*===========================================================================*/

