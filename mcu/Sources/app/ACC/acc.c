/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : acc.c
* Description : ACC module applayer
* Author: Xiaojie.Zheng
* Date: 2016-12-06
*autohor:zxx
*Date:20170628-modfiy
******************************************************************************/

/* Files for including */
#include "acc_info.inc"
static BOOL acc_InitSts = FALSE;                             /*ACC模块初始化状态*/

static AccPedtrnAlrtInhSwReqValue_ENUM acc_PedtrnAlrtInhSwStatus = PedtrnAlrtNoReq;

static BOOL acc_PedtrnAlrtInhSwEnable = TRUE;

static BOOL acc_PedtrnAlrtJudgeEnable =	FALSE;	

static BOOL acc_PedtrnAdoWrnngJudgeEnable = FALSE;

static AccSystemPowerMode_ST AccSystemPowerMode_St = {0}; /*电源模式状态 */
static AccTrShftLvrPos_ST AccTrShftLvrPos_St = {0};		  /*档位信息状态*/
static BOOL acc_ElectricPowertrainReady = FALSE;		  /*动力系统Ready*/
static AccVehicleSpeedAverage_ST acc_VehicleSpeedAverage_St = {0};/*车速信息*/
static AccPedestrianAlertSoundSelect_ST AccPedestrianAlertSoundSelect = {1,0};/*警示音音源选择状态*/
static U8 acc_PedtrnAdoWrnng = 0;
static U8 acc_PedtrnSystemVolume = 6;
static U8 acc_RstrFctryDeftsReq = 0;

#define ACC_FRAMESTSFLAG  0

/***************************************************
* Function: ACC_Init
* Description: ACC module initialization status
* Parameters:  input: none
* Returns: none
* $Create & Verlog:$
* Author: Xiaojie.Zheng     Date:2016-12-06   Version:V1.0
****************************************************/
void ACC_Init(void)
{
    U8  res = RET_FAIL;
	U8 datalen = 0x01;
    acc_InitSts = FALSE;

    
    if ((TRUE == IOM_GetInitStatus()/*IOM_GetModuleStatus()*/) && (TRUE == ADM_GetInitStatus()))
    {
    	NVM_GetParas(INDEX_NVM_PEDTRN_ALRT_SND_SLT,&AccPedestrianAlertSoundSelect.acc_PedestrianAlertSoundSelect,datalen);
  		NVM_GetParas(INDEX_NVM_PEDTRN_ALRT_SND_VOL,&acc_PedtrnSystemVolume,datalen);
        acc_InitSts = TRUE;
    }
   else
   {
   	/*do nothing*/
   }
}
static void acc_ResetPara(void)
{
	AccTrShftLvrPos_St.acc_TransmissionShiftLeverPosition = STATUS_ACC_PARKRANGE;
	acc_VehicleSpeedAverage_St.acc_VehicleSpeed = 0x00;
	AccPedestrianAlertSoundSelect.acc_PedestrianAlertSoundSelect = PedestrianAlertSltSound1;
	acc_PedtrnAlrtJudgeEnable = 0;
	acc_PedtrnAdoWrnngJudgeEnable = 0;
	acc_PedtrnAdoWrnng = PedtrnAdoWrnngNoReq;
	acc_PedtrnSystemVolume = PedtrnAlrtLevel6;
}
/***************************************************
* Function: ACC_Process_100ms
* Description: Processing function of ACC module
* Parameters:  input: none
* Returns: none
* $Create & Verlog:$
* Author: Xiaojie.Zheng     Date:2016-12-06   Version:V1.0
****************************************************/
void ACC_Process_10ms(void)
{
	PWRMcuWorkMode_ENUM pwrMode = PWR_MCU_WORK_MODE_SLEEP;
	
	U8 ds_BatMode;
    U8 res = RET_FAIL;
	U8 CanErr =1;
	static U8 Count = 0;
    if (TRUE == acc_InitSts)
    {
    	ds_BatMode = BAT_GetBatVoltageSts();
        res = PWR_GetPwrMode(&pwrMode);
		if(res == RET_OK)
		{
			if((pwrMode == PWR_MCU_WORK_MODE_NORMAL) && (ds_BatMode < STATUS_BAT_CAN))
			{
		  		
		  		acc_PedtrnAlrtJudge_10ms();
		  		acc_PedtrnAdoWrnngJudge_10ms();
		  		acc_RstrFctryDeftsJudge_10ms();
			}
			else
			{
				acc_ResetPara();/*不满足can通信电压，恢复默认*/
			}
		}
		#if 0
		IOM_GetInputLevel(INDEX_IOM_ERR,&CanErr);
		if(CanErr == 0)
		{
				Count ++;
		}
		if(Count > 20)
		{
			IOM_SetOutPutLevel(INDEX_IOM_CAN_STB,1);/*系统没有掉电 发送goto sleep cammand*/
			IOM_SetOutPutLevel(INDEX_IOM_EN,1);	 
			PWR_Dlay25us(4);
			IOM_SetOutPutLevel(INDEX_IOM_CAN_STB,0);/*系统没有掉电 发送goto sleep cammand*/
			IOM_SetOutPutLevel(INDEX_IOM_EN,1);	  
			Count = 0;
		}
		#endif
	}
    else
    {
        /*do nothing*/
    }   
}



/***************************************************
* Function: ACC_SendNetSignal_100ms
* Description: SendNetSignal inforatiom
* Parameters:  input: none
* Returns: gear information
* $Create & Verlog:$
* Author: zxx     Date:2017-06-29  Version:V2.0
***************************************************/
void ACC_SendNetSignal_10ms(void)
{
	//v_wr_8(ClstrDspdTrWrnng_handle, acc_ClstrDspdTrWrnng); 

}

void ACC_GetGearSts(AccGearLvl_ENUM * pGearLvl) //AccGearLvl_ENUM * pGearLvl)
{
	if(pGearLvl != NULL)
	{
		*pGearLvl = (U8)(AccTrShftLvrPos_St.acc_TransmissionShiftLeverPosition);
	}
}

void ACC_GetSpeedValue(float * pSpeedValue)
{
	if(pSpeedValue != NULL)
	{
		*pSpeedValue = acc_VehicleSpeedAverage_St.acc_VehicleSpeed;
	}
}

void ACC_GetPedestrianAlertSoundSelect(U8 * pPedestrianAlertSoundSelect)
{
	if(pPedestrianAlertSoundSelect != NULL)
	{
		*pPedestrianAlertSoundSelect = AccPedestrianAlertSoundSelect.acc_PedestrianAlertSoundSelect;
	}
}
void ACC_GetPedtrnAlrtJudgeEnable(PU8 pPedtrnAlrtJudgeEnable)
{
	if(pPedtrnAlrtJudgeEnable != NULL)
	{
		*pPedtrnAlrtJudgeEnable = acc_PedtrnAlrtJudgeEnable;
	}

}
void ACC_GetPedtrnAlrtInSwEnable(PU8 pPedtrnAlrtInhSwEnable)
{
	if(pPedtrnAlrtInhSwEnable != NULL)
	{
		*pPedtrnAlrtInhSwEnable = acc_PedtrnAlrtInhSwEnable;
	}
}
void ACC_GetPedtrnAdoWrnngJudgeEnable(PU8 pPedtrnAdoWrnngJudgeEnable)
{
	if(pPedtrnAdoWrnngJudgeEnable != NULL)
	{
		*pPedtrnAdoWrnngJudgeEnable = acc_PedtrnAdoWrnngJudgeEnable;
	}
}

void ACC_GetPedtrnAdoWrnng(PU8 pPedtrnAdoWrnng)
{
	if(pPedtrnAdoWrnng != NULL)
	{
		*pPedtrnAdoWrnng = acc_PedtrnAdoWrnng;
	}
}
void ACC_GetPedtrnSystemVolume(PU8 pPedtrnSystemVolume)
{
	if(pPedtrnSystemVolume != NULL)
	{
		*pPedtrnSystemVolume = acc_PedtrnSystemVolume;
	}
}



/***************************************************
* Function: acc_PedtrnAlrtJudge_50ms
* Description: Get event index
* Parameters:  input: none
* Returns: none
* $Create & Verlog:$
* Author: Xiaojie.Zheng     Date:2016-12-06   Version:V1.0
****************************************************/

static void acc_PedtrnAlrtJudge_10ms(void)
{
	U8 acc_pedtrn_alrt_sw;
	U8 accGearLvl;	
    U8 bat_Status;
    U8 spd_PACMFltStatus;
	U8 spd_PedtrnAlrtSpkFltStatus;
	BOOL accGearLvlValid;
	BOOL accPedtrnAlrtVolSwReqV;
	U8 accPedtrnSystemVolume;
	U8 accPedestrianAlertSoundSelect;	
	BOOL accPedestrianAlertSoundSelectV;
	U8 acc_frame_sts;
	
	NWD_GetNodeMissing(INDEX_FICM_36B_SOT,&acc_frame_sts);
#if ACC_FRAMESTSFLAG
	if(0)
#else
	if(acc_frame_sts) /*帧信号丢失*/
#endif
	{
		acc_PedtrnAlrtInhSwStatus = PedtrnAlrtNoReq;
		acc_PedtrnAlrtInhSwEnable = TRUE;
		acc_PedtrnSystemVolume = PedtrnAlrtLevel6;
		AccPedestrianAlertSoundSelect.acc_PedestrianAlertSoundSelect = PedestrianAlertSltSound1;
		AccPedestrianAlertSoundSelect.acc_PedestrianAlertSoundSelectValid = VALUE_INVALID;
	}
	else
	{
		COM_GetSignalValue_8(INDEX_COM_RS_PedtrnAlrtInhSwReq_2bit,&acc_pedtrn_alrt_sw);					/*100ms*/
		COM_GetSignalValue_BOOL(INDEX_COM_RS_PedtrnAlrtVolSwReqV_1bit,&accPedtrnAlrtVolSwReqV);			/*100ms*/
		COM_GetSignalValue_8(INDEX_COM_RS_PedtrnAlrtVolSwReq_4bit,&accPedtrnSystemVolume);				/*100ms*/	
		COM_GetSignalValue_8(INDEX_COM_RS_PedtrnAlrtSndSltReq_2bit,&accPedestrianAlertSoundSelect);		/*100ms*/		
		COM_GetSignalValue_BOOL(INDEX_COM_RS_PedtrnAlrtSndSltReqV_1bit,&accPedestrianAlertSoundSelectV);	/*100ms*/
		if((PedtrnAlrtLongPress == acc_pedtrn_alrt_sw) || (acc_pedtrn_alrt_sw == PedtrnAlrtReserved))
		{
			acc_pedtrn_alrt_sw = PedtrnAlrtNoReq;
		}
		else if((acc_pedtrn_alrt_sw == PedtrnAlrtShortPress))//||(acc_pedtrn_alrt_sw == PedtrnAlrtLongPress))
		{
			if(acc_PedtrnAlrtInhSwStatus == PedtrnAlrtNoReq)
			{
				if(acc_PedtrnAlrtInhSwEnable == TRUE)
				{
					acc_PedtrnAlrtInhSwEnable = FALSE;
				}
				else
				{
					acc_PedtrnAlrtInhSwEnable = TRUE;
				}
			}
		}
		
		acc_PedtrnAlrtInhSwStatus = acc_pedtrn_alrt_sw;

		if(accPedtrnAlrtVolSwReqV == VALUE_VALID)
		{
			if((accPedtrnSystemVolume < PedtrnAlrtLevel7) && (accPedtrnSystemVolume > PedtrnAlrtLevel4))
			{
				acc_PedtrnSystemVolume = accPedtrnSystemVolume;
			}
		}
		else
		{
			/*无效参数，保持当前音量值*/
		}
		
		if(accPedestrianAlertSoundSelectV == VALUE_VALID)
		{
			AccPedestrianAlertSoundSelect.acc_PedestrianAlertSoundSelect = PedestrianAlertSltSound1;
			AccPedestrianAlertSoundSelect.acc_PedestrianAlertSoundSelectValid = VALUE_VALID;
		}

		
	}
	
	NWD_GetNodeMissing(INDEX_GW_1F1_SOT,&acc_frame_sts);
#if ACC_FRAMESTSFLAG
	if(0)
#else
	if(acc_frame_sts) /*帧信号丢失*/
#endif
	{
		AccSystemPowerMode_St.acc_SystemPowerMode	= SystemPowerModeOff;
	}
	else
	{
		COM_GetSignalValue_8(INDEX_COM_RS_SysPwrMd_2bit,&AccSystemPowerMode_St.acc_SystemPowerMode);/*20ms*/
	}
		
	
	NWD_GetNodeMissing(INDEX_GW_1F2_SOT,&acc_frame_sts);
	
#if ACC_FRAMESTSFLAG
		if(0)
#else
		if(acc_frame_sts) /*帧信号丢失*/
#endif

	{
		AccSystemPowerMode_St.acc_SystemBackupPowerMode = 0x00;
		AccSystemPowerMode_St.acc_SystemBackupPowerModeValid = 0x00;
	}
	else
	{
		COM_GetSignalValue_8(INDEX_COM_RS_SysBPM_2bit,&AccSystemPowerMode_St.acc_SystemBackupPowerMode);/*20ms*/
		COM_GetSignalValue_BOOL(INDEX_COM_RS_SysBPMEnbd_1bit,&AccSystemPowerMode_St.acc_SystemBackupPowerModeValid);/*20ms*/
	}
	
	NWD_GetNodeMissing(INDEX_GW_353_SOT,&acc_frame_sts);
#if ACC_FRAMESTSFLAG
	if(0)
#else
	if(acc_frame_sts) /*帧信号丢失*/
#endif

	{
		acc_VehicleSpeedAverage_St.acc_VehicleSpeedAverage = 0x00;
		acc_VehicleSpeedAverage_St.acc_VehicleSpeedAverageValid = VALUE_VALID;
	}
	else
	{
		
		COM_GetSignalValue_16(INDEX_COM_RS_VehSpdAvgDrvn_15bit,&acc_VehicleSpeedAverage_St.acc_VehicleSpeedAverage);/*100ms*/
		COM_GetSignalValue_BOOL(INDEX_COM_RS_VehSpdAvgDrvnV_1bit,&acc_VehicleSpeedAverage_St.acc_VehicleSpeedAverageValid);/*100ms*/
	}
	if(acc_VehicleSpeedAverage_St.acc_VehicleSpeedAverageValid == VALUE_VALID)
	{
		acc_VehicleSpeedAverage_St.acc_VehicleSpeed = acc_VehicleSpeedAverage_St.acc_VehicleSpeedAverage * 0.015625;
	}
	
	NWD_GetNodeMissing(INDEX_GW_196_SOT,&acc_frame_sts);	
#if ACC_FRAMESTSFLAG
		if(0)
#else
		if(acc_frame_sts) /*帧信号丢失*/
#endif

	{
		acc_ElectricPowertrainReady = 0x00; /*no ready*/
	}
	else
	{
		COM_GetSignalValue_BOOL(INDEX_COM_RS_EPTRdy_1bit, &acc_ElectricPowertrainReady); /*20ms*/
	}
	NWD_GetNodeMissing(INDEX_GW_194_SOT,&acc_frame_sts);	
#if ACC_FRAMESTSFLAG
		if(0)
#else
		if(acc_frame_sts) /*帧信号丢失*/
#endif

	{
		accGearLvl = STATUS_ACC_BETWEENRANGE;
		AccTrShftLvrPos_St.acc_TransmissionShiftLeverPosition = STATUS_ACC_PARKRANGE;
		accGearLvlValid	= VALUE_VALID;
	}
	else
	{
		COM_GetSignalValue_8(INDEX_COM_RS_TrShftLvrPos_4bit,&accGearLvl);			/*25ms*/
		COM_GetSignalValue_BOOL(INDEX_COM_RS_TrShftLvrPosV_1bit, &accGearLvlValid);	/*25ms*/
	}

	if((accGearLvlValid == VALUE_VALID)&&(accGearLvl < STATUS_ACC_RESERVED1)&&(accGearLvl > STATUS_ACC_BETWEENRANGE))
	{
		if(accGearLvl != AccTrShftLvrPos_St.acc_TransmissionShiftLeverPosition)
		{
			if(accGearLvl == AccTrShftLvrPos_St.acc_TransmissionShiftLeverPositionNew)
			{
				if(AccTrShftLvrPos_St.acc_TransShiftDebounceCount < ACC_TRANS_SHIFT_DEBOUNCE_COUNT)
				{
					AccTrShftLvrPos_St.acc_TransShiftDebounceCount++;
				}
				if(AccTrShftLvrPos_St.acc_TransShiftDebounceCount >= ACC_TRANS_SHIFT_DEBOUNCE_COUNT)
				{
					AccTrShftLvrPos_St.acc_TransmissionShiftLeverPosition = accGearLvl;
				}
			}
			else
			{
				AccTrShftLvrPos_St.acc_TransmissionShiftLeverPositionNew = accGearLvl;
				AccTrShftLvrPos_St.acc_TransShiftDebounceCount = 0;
			}
		}
	}
	else if((AccTrShftLvrPos_St.acc_TransmissionShiftLeverPosition <= STATUS_ACC_BETWEENRANGE)||(AccTrShftLvrPos_St.acc_TransmissionShiftLeverPosition >= STATUS_ACC_RESERVED1))
		 {
			AccTrShftLvrPos_St.acc_TransmissionShiftLeverPosition = STATUS_ACC_PARKRANGE;
		 }
		 else
		 {
			;
		 }
	
	if((accGearLvlValid != VALUE_VALID)||(STATUS_ACC_PARKRANGE == AccTrShftLvrPos_St.acc_TransmissionShiftLeverPosition))//||(accGearLvl == STATUS_ACC_BETWEENRANGE))
	{
		acc_PedtrnAlrtJudgeEnable = FALSE;
		return;
	}
	
	if(acc_ElectricPowertrainReady == FALSE) 
	{	
		acc_PedtrnAlrtJudgeEnable = FALSE;
		return;
	}
	if(acc_PedtrnAlrtInhSwEnable == FALSE)
	{
    	acc_PedtrnAlrtJudgeEnable = FALSE;	
  		return;
	}
	if(AccSystemPowerMode_St.acc_SystemPowerMode != SystemPowerModeRun)
	{
		if(AccSystemPowerMode_St.acc_SystemBackupPowerModeValid == VALUE_VALID)
		{	
			acc_PedtrnAlrtJudgeEnable = FALSE;
			return;
		}
		if(AccSystemPowerMode_St.acc_SystemBackupPowerMode != SystemPowerModeRun)
		{	
			acc_PedtrnAlrtJudgeEnable = FALSE;
			return;
		}
	}
	

	if((acc_VehicleSpeedAverage_St.acc_VehicleSpeedAverageValid != VALUE_VALID) || \
		(acc_VehicleSpeedAverage_St.acc_VehicleSpeed > ACC_MAX_SPEED_ALERT) || \
		(acc_VehicleSpeedAverage_St.acc_VehicleSpeed < ACC_MIN_SPEED_ALERT))
	{	
		acc_PedtrnAlrtJudgeEnable = FALSE;
		return;
	}
	/*
		异常条件判断，如电池电压异常，		喇叭诊断异常。
	*/
	bat_Status = BAT_GetBatVoltageSts();
	spd_PACMFltStatus = SPD_PACMFltSts();
    spd_PedtrnAlrtSpkFltStatus = SPD_PedtrnAlrtSpkFltSts();
	if((bat_Status > STATUS_BAT_CLASSA_CAN) 
	||(spd_PACMFltStatus == TRUE)
	||(spd_PedtrnAlrtSpkFltStatus == TRUE))
	{
		acc_PedtrnAlrtJudgeEnable = FALSE;
	 	return; /*电池电压异常  或  功放喇叭异常*/
	}
	acc_PedtrnAlrtJudgeEnable = TRUE;
}
/*

信号周期是10ms
*/
static void acc_PedtrnAdoWrnngJudge_10ms(void)
{
	U8 bat_Status;
	U8 spd_PACMFltStatus;
	U8 spd_PedtrnAlrtSpkFltStatus;
	U8 accPedtrnAdoWrnng = 0;
	U8 acc_frame_sts;

	NWD_GetNodeMissing(INDEX_IECU_390_SOT,&acc_frame_sts);
	
#if ACC_FRAMESTSFLAG
		if(0)
#else
		if(acc_frame_sts) /*帧信号丢失*/
#endif

	{
		accPedtrnAdoWrnng = PedtrnAdoWrnngNoReq;
	}
	else
	{
		COM_GetSignalValue_8(INDEX_COM_RS_PedtrnAdoWrnng_4bit,&accPedtrnAdoWrnng);
	}
	
	if((accPedtrnAdoWrnng <= PedtrnAdoWrnngSelSin) && (accPedtrnAdoWrnng >= PedtrnAdoWrnngNoReq))
	{
		acc_PedtrnAdoWrnng = accPedtrnAdoWrnng;
	}
	else
	{
		acc_PedtrnAdoWrnng = PedtrnAdoWrnngNoReq;
	}
#if 0
	{

		acc_PedtrnAdoWrnng = PedtrnAdoWrnngNoReq;
	}
	else
	{		
		if(accPedtrnAdoWrnng == PedtrnAdoWrnngSelSin)
		{
			acc_PedtrnAdoWrnng = accPedtrnAdoWrnng;
		}
		else
		{
			acc_PedtrnAdoWrnng = (accPedtrnAdoWrnng - 1);
		}		
	}
#endif

	/*
		需要添加本模块没有异常条件判断，
		如电池电压异常，
		  喇叭诊断异常。

	*/
	bat_Status = BAT_GetBatVoltageSts();
	spd_PACMFltStatus = SPD_PACMFltSts();
	spd_PedtrnAlrtSpkFltStatus = SPD_PedtrnAlrtSpkFltSts();
	if((bat_Status > STATUS_BAT_CLASSA_CAN) 
	||(spd_PACMFltStatus == TRUE)
	||(spd_PedtrnAlrtSpkFltStatus == TRUE))
	{
		
		acc_PedtrnAdoWrnngJudgeEnable = FALSE;
	 	return; /*电池电压异常*/
	}
	
	acc_PedtrnAdoWrnngJudgeEnable = TRUE;
}

/***************************************************
* Function: acc_RstrFctryDeftsJudge_10ms
* Description: Get event index
* Parameters:  input: none
* Returns: none
* $Create & Verlog:$
* Author: qq     Date:2016-12-06   Version:V1.0
****************************************************/
static void acc_RstrFctryDeftsJudge_10ms(void)
{
	static U8 acc_rstrFctryDeftsReqBack = FALSE;
	
	U8 acc_frame_sts;

	NWD_GetNodeMissing(INDEX_FICM_376_SOT,&acc_frame_sts);
#if ACC_FRAMESTSFLAG
	if(0)
#else
	if(acc_frame_sts) /*帧信号丢失*/
#endif

	{
		acc_RstrFctryDeftsReq = FALSE;
	}
	else
	{
		COM_GetSignalValue_BOOL(INDEX_COM_RS_RstrFctryDeftsReq_1bit,&acc_RstrFctryDeftsReq);
	}
	
	if(acc_RstrFctryDeftsReq != FALSE)
	{
		if(acc_rstrFctryDeftsReqBack == FALSE)
		{
			acc_PedtrnAlrtInhSwEnable = TRUE;
			AccPedestrianAlertSoundSelect.acc_PedestrianAlertSoundSelect = PedestrianAlertSltSound1;
			acc_PedtrnSystemVolume = PedtrnAlrtLevel6;
		}
		acc_rstrFctryDeftsReqBack = TRUE;
	}
	else
	{
		acc_rstrFctryDeftsReqBack = FALSE;
	}
}


/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0         Jason.Sun        2018-06-13     Initial
*===========================================================================*/

