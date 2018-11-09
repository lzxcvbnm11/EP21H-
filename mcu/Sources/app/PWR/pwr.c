/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : pwr.C
* Description :the private datas of the pwr module.
* Author: Jason.Sun
* Date: 2018-07-20
******************************************************************************/
/* Files for including */
#include "pwr_info.inc"

static U8 pwr_InitSts = FALSE;                              /*初始化*/
static PWRMcuWorkMode_ENUM pwr_McuWorkMode;
static PWRCanWorkMode_ENUM pwr_CanWorkMode;
static PWRDspWorkMode_ENUM pwr_DspWorkMode;

static U8 pwr_DspOnOff = FALSE;
static U8 pwr_DspOnDalay = 0;
/***************************************************
* Function: PWR_Init
* Description: the initialized of the mom module
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Xueping.Chen  Date:2016-12-09   Version:V1.0
****************************************************/
void PWR_Init(void)
{
    //U8 res = RET_FAIL;
    pwr_InitSts = FALSE;
	pwr_McuWorkMode = PWR_MCU_WORK_MODE_NORMAL;
	pwr_CanWorkMode = PWR_CAN_WORK_MODE_NORMAL;
	pwr_DspWorkMode = PWR_DSP_WORK_MODE_ON_PRE;
 	IOM_SetOutPutLevel(INDEX_IOM_EN,1);	  		/*使能can控制器*/
	IOM_SetOutPutLevel(INDEX_IOM_CAN_STB,1);	/*can控制处于正常收发模式*/
	pwr_DspOnDalay = 20;
    pwr_InitSts = TRUE;
}

/***************************************************
* Function: PWR_Process_20ms
* Description: the process of the mom module
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Xueping.Chen  Date:2016-12-09   Version:V1.0
****************************************************/
void PWR_Process_10ms(void)
{
    if (TRUE == pwr_InitSts)
    {    
	   pwr_CanWorkModeFunc();	   
	   pwr_McuWorkModeFunc();
	   pwr_DspWorkModeFunc();	   
    }
    else
    {
    }
}
static void pwr_DspWorkModeFunc(void)
{

	switch(pwr_DspWorkMode)
	{
		case PWR_DSP_WORK_MODE_IDLE:
			 break;
		case PWR_DSP_WORK_MODE_ON_PRE:
			IOM_SetOutPutLevel(INDEX_IOM_DCDC_EN,0);	/*dsp 电源控制脚*/
			IOM_SetOutPutLevel(INDEX_IOM_DSP_RES,0);	/*dsp reset 控制脚*/
			if(pwr_DspOnDalay > 0)
			{
				pwr_DspOnDalay--;
				return;
			}
			pwr_DspWorkMode = PWR_DSP_WORK_MODE_ON_RESET;
			break;
		case PWR_DSP_WORK_MODE_ON_RESET:
			IOM_SetOutPutLevel(INDEX_IOM_DCDC_EN,1);	/*dsp电源控制脚*/
			IOM_SetOutPutLevel(INDEX_IOM_DSP_RES,0);	/*dsp reset 控制脚*/
			pwr_DspWorkMode = PWR_DSP_WORK_MODE_ON_SUCCESS;
			break;
		case PWR_DSP_WORK_MODE_ON_SUCCESS:
			if(pwr_DspOnOff == FALSE)
			{
				IOM_SetOutPutLevel(INDEX_IOM_DCDC_EN,1);	/*dsp电源控制脚*/
				IOM_SetOutPutLevel(INDEX_IOM_DSP_RES,1);	/*dsp reset 控制脚*/
				pwr_DspOnOff = TRUE;				
				pwr_DspWorkMode = PWR_DSP_WORK_MODE_IDLE;
			}
			break;
		case PWR_DSP_WORK_MODE_OFF:
			if(pwr_DspOnOff == TRUE)
			{
				IOM_SetOutPutLevel(INDEX_IOM_DCDC_EN,0);	/*dsp电源控制脚*/
				IOM_SetOutPutLevel(INDEX_IOM_DSP_RES,0);	/*dsp reset 控制脚*/
				pwr_DspOnOff = FALSE;				
				pwr_DspWorkMode = PWR_DSP_WORK_MODE_IDLE;
			}
			break;

		default:
			break;
	
	}




}
static void  pwr_CanWorkModeFunc(void)
{
	U8 pinCanErrSts;	
	static U8 Count = 0;
	IOM_GetInputLevel(INDEX_IOM_ERR,&pinCanErrSts);
	
	switch(pwr_CanWorkMode)
	{
		case PWR_CAN_WORK_MODE_NORMAL: /* can 收发器正常，测试错误状态*/			

			break;
		case PWR_CAN_WORK_MODE_PWON_LISTEN:
			break;
		case PWR_CAN_WORK_MODE_STAND_BY:

			break;
		case PWR_CAN_WORK_MODE_GOTO_SLEEP: /*发送 go to sleep command*/
			MUTE_OnOff(1);	
			pwr_DspWorkMode = PWR_DSP_WORK_MODE_OFF; /*dsp power off*/
			IOM_SetOutPutLevel(INDEX_IOM_CAN_STB,0);/*发送goto sleep cammand*/
			IOM_SetOutPutLevel(INDEX_IOM_EN,1);	 
			Count = 0;
			pwr_CanWorkMode = PWR_CAN_WORK_MODE_SLEEP;
			break;
		case PWR_CAN_WORK_MODE_SLEEP:/* can sleep mode,测试是否睡眠OK*/			
			
			if(pinCanErrSts)
			{
				/*系统断电状态*/
			
			}
			else /* 睡眠失败，*/
			{
				Count++;
				if(Count >= 10)
				{
					pwr_CanWorkMode = PWR_CAN_WORK_MODE_NORMAL;
					pwr_McuWorkMode = PWR_MCU_WORK_MODE_NORMAL;					
					pwr_DspWorkMode = PWR_DSP_WORK_MODE_ON_PRE;
					MUTE_OnOff(1);
					IOM_SetOutPutLevel(INDEX_IOM_CAN_STB,1);/* can control warm restart system */
				    IOM_SetOutPutLevel(INDEX_IOM_EN,1);	 
				}
			}
			break;
		default:
			break;
	}

}

/***************************************************
* Function: pwr_PowerMode_10ms
* Description: get the mode of power
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Xueping.Chen  Date:2016-12-09   Version:V1.0
* Author:LIUYINGYING  Date:2017-06-27    Version:V2.0
****************************************************/
static void  pwr_McuWorkModeFunc(void)
{
    U8 res = RET_FAIL;
	DiagQuietModeFun_ENUM diag_QuietMode;
	v_nwm_state nwm_state;

	//COM_GetSignalValue_8(INDEX_COM_RS_network_mode_8bit,&NetWorkMode);	
	switch(pwr_McuWorkMode)
	{
		case PWR_MCU_WORK_MODE_START_UP:
		case PWR_MCU_WORK_MODE_NORMAL:
			diag_QuietMode = DIAG_GetQuietModeStatus();
			if(diag_QuietMode == DIAG_QUIET_MODULE)
			{
				pwr_McuWorkMode = PWR_MCU_WORK_MODE_DIAG;
			}
			else
			{
			
				nwm_state = COM_GetNwmState();
				if(COM_GetNetWorkSleepSts())
				{
					pwr_McuWorkMode = PWR_MCU_WORK_MODE_WAIT_SLEEP;
				}
				else if((nwm_state != V_NWM_NORMAL) && (nwm_state != V_NWM_WAIT_FOR_NETWORK_SLEEP) && (nwm_state != V_NWM_STARTUP))
				{
					pwr_McuWorkMode = PWR_MCU_WORK_MODE_SILENT;
				
				}

			}
			break;
		case PWR_MCU_WORK_MODE_QUIET:
		case PWR_MCU_WORK_MODE_SILENT:	/*network silent mode don't enter diag mode*/
			nwm_state = COM_GetNwmState();
			if((nwm_state == V_NWM_NORMAL) || (nwm_state == V_NWM_WAIT_FOR_NETWORK_SLEEP) || (nwm_state == V_NWM_STARTUP))
			{
				pwr_McuWorkMode = PWR_MCU_WORK_MODE_NORMAL;
			}
			else if(COM_GetNetWorkSleepSts())
			{				
				pwr_McuWorkMode = PWR_MCU_WORK_MODE_WAIT_SLEEP;
			}
			break;
		case PWR_MCU_WORK_MODE_DIAG:
			diag_QuietMode = DIAG_GetQuietModeStatus();
			if(diag_QuietMode == DIAG_QUIET_EXIT_MODULE)
			{
				pwr_McuWorkMode = PWR_MCU_WORK_MODE_NORMAL;
			}
			break;
		case PWR_MCU_WORK_MODE_WAIT_SLEEP:
			if(NVM_GetWorkSts() == FALSE)/*保存信息ok*/
			{
				pwr_McuWorkMode = PWR_MCU_WORK_MODE_SLEEP;				
 				pwr_CanWorkMode = PWR_CAN_WORK_MODE_GOTO_SLEEP;
			}
			break;
		case PWR_MCU_WORK_MODE_SLEEP:

			break;
		default:
			break;
	}

#if 0
    pwr_busoff = NWD_GetBusOffFlt();

    res = NWD_GetNodeMissing(INDEX_BCM_NODE,&pwr_LostIcm);
    res = NWD_GetNodeMissing(INDEX_SCS_NODE,&pwr_lostSCS);
    res = NWD_GetNodeMissing(INDEX_ECM_NODE, &pwr_lostECM);

    COM_GetSignalValue_8(INDEX_COM_RS_BCMPWRMDHWDSTAV, &pwr_NetBCMPwrMdHwdStaV);
    COM_GetSignalValue_8(INDEX_COM_RS_BCMPwrMdHwdSt, &pwr_NetBCMPwrMdHwdSta);
    COM_GetSignalValue_BOOL(INDEX_COM_RS_ENRUNA, &pwr_NetEnRunA);

    if ((TRUE == pwr_LostIcm)  ||(TRUE == pwr_busoff) || (INVALID == pwr_NetBCMPwrMdHwdStaV))
    {
        pwr_NetSysBPMEnbd = TRUE;
    }
    else
    {
        pwr_NetSysBPMEnbd = FALSE;
    }
 
    pwr_BackUpPowerMode_Process();
    pwr_Update_D001_Value();
#endif

}


/***************************************************
* Function: PWR_GetPwrMode
* Description: get the working mode of the power
* Parameters:  none
* Returns:  RET_FAIL
                    RET_INVALID
                    RET_OK
* $Create & Verlog:$
* Author:Xueping.Chen  Date:2016-12-09   Version:V1.0
****************************************************/
U8 PWR_GetPwrMode(PWRMcuWorkMode_ENUM * mcu_work_state)
{
    U8 res = RET_OK;

   if (FALSE == pwr_InitSts)
   {
        res = RET_FAIL;
   }
   else if (NULL_PTR == mcu_work_state)
   {
        res = RET_INVALID;
   }
   else
   {
        *mcu_work_state = pwr_McuWorkMode;
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
* V1.0       Xueping.Chen      2016-12-09              Initial
*
*===========================================================================*/


