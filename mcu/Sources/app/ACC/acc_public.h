/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :acc_public.h
* Description : public data of the Acc
* Author: Xiaojie.Zheng 
* Date: 2016-12-06
******************************************************************************/

/* check of multiple include */
#ifndef _ACC_PUBLIC_H_
#define _ACC_PUBLIC_H_
#include "yd_typedefs.h"

/* Public Macros defines */



#define VEH_SPD_THRESHOLD 5          			   /*车辆速度门限值*/
#define ACC_PROCESS_PERIOD 100          		   /*acc执行周期5ms*/
#define ACC_NETUPDATE100_PERIOD 100                /*网络信号更新周期100ms*/
#define ACC_OILPRESSURE_CNT 400              	   /*计数400次,相当于2s*/

#define S_TO_MINUTE(y) (y/3600)                    /*秒转换成毫秒*/
#define ACC_SRSLED_BAD_ADVALUE_MIN        400   
#define ACC_SRSLED_BAD_ADVALUE_MAX        655   

#define VALUE_VALID  		0x00

#define VALUE_INVALID 		0x01

typedef enum AccGearLvl_Tag              /*Transmission Shift Lever Position*/
{
    STATUS_ACC_BETWEENRANGE = ( 0u ),     /*Between Ranges*/
    STATUS_ACC_PARKRANGE,                 /*Park Range*/
    STATUS_ACC_REVERSERANGE,              /*Reverse Range*/
    STATUS_ACC_NEUTRALRANGE,              /*Neutral Range*/
    STATUS_ACC_FORWARDRANGEA,             /*Forward Range A*/
    STATUS_ACC_FORWARDRANGEB,             /*Forward Range B*/
    STATUS_ACC_FORWARDRANGEC,             /*Forward Range C*/
    STATUS_ACC_FORWARDRANGED,             /*Forward Range D*/
    STATUS_ACC_FORWARDRANGEE,             /*Forward Range E*/
    STATUS_ACC_FORWARDRANGEF,             /*Forward Range F*/
    STATUS_ACC_FORWARDRANGEG,             /*Forward Range G*/
    STATUS_ACC_FORWARDRANGEH,             /*Forward Range H*/
    STATUS_ACC_RESERVED1,                 /*预留1*/
    STATUS_ACC_RESERVED2,                 /*预留2*/
    STATUS_ACC_RESERVED3,                 /*预留3*/
    STATUS_ACC_POSITIONUNKNOWN,           /*Lever Position Unknown*/
    STATUS_ACC_POSITION_ALL
}AccGearLvl_ENUM;
typedef enum AccPedtrnAlrtInhSwReqValue_Tag
{
	PedtrnAlrtNoReq = (0u),
	PedtrnAlrtShortPress,
	PedtrnAlrtLongPress,
	PedtrnAlrtReserved
}AccPedtrnAlrtInhSwReqValue_ENUM;

typedef enum AccPedtrnAlrtVolSwReqValue_Tag
{
	PedtrnAlrtLevel0 = (0u),
	PedtrnAlrtLevel1,
	PedtrnAlrtLevel2,
	PedtrnAlrtLevel3,
	PedtrnAlrtLevel4,
	PedtrnAlrtLevel5,
	PedtrnAlrtLevel6,
    PedtrnAlrtLevel7,
	PedtrnAlrtLevel8,
	PedtrnAlrtLevel9,
	PedtrnAlrtLevel10
}AccPedtrnAlrtVolSwReqValue_ENUM;

typedef enum AccPedtrnAdoWrnng_Tag
{
	PedtrnAdoWrnngNoReq = (0u),
	PedtrnAdoWrnngSel1,
	PedtrnAdoWrnngSel2,
	PedtrnAdoWrnngSel3,
	PedtrnAdoWrnngSel4,
	PedtrnAdoWrnngSel5,
    PedtrnAdoWrnngSel6,
	PedtrnAdoWrnngSel7,
	PedtrnAdoWrnngSel8,
	PedtrnAdoWrnngSel9,
	PedtrnAdoWrnngSelSin,		
	PedtrnAdoWrnngReserve
}AccPedtrnAdoWrnng_ENUM;
	
typedef enum AccPedestrianAlertSoundSelectEnum_Tag
{
	PedestrianAlertSltSound1 = (0u),
	PedestrianAlertSltSound2,
	PedestrianAlertSltSound3,
	PedestrianAlertSltReserved
}AccPedestrianAlertSoundSelect_ENUM;

typedef enum AccSystemPowerModeEnum_Tag
{
	SystemPowerModeOff = (0u),
	SystemPowerModeAcc,
	SystemPowerModeRun,
	SystemPowerModeCrank,
	SystemPowerModeALL
}AccSystemPowerMode_ENUM;
	
typedef struct AccSystemPowerMode_Tag
{
	BOOL acc_SystemBackupPowerModeValid;
	U8 acc_SystemBackupPowerMode;
	U8 acc_SystemPowerMode;
}AccSystemPowerMode_ST;

typedef struct AccTrShftLvrPos_Tag
{
	 AccGearLvl_ENUM acc_TransmissionShiftLeverPositionNew;
	 AccGearLvl_ENUM acc_TransmissionShiftLeverPosition;	 
	 U8 acc_TransShiftDebounceCount;
}AccTrShftLvrPos_ST;

#define ACC_TRANS_SHIFT_DEBOUNCE_COUNT  3

typedef struct AccVehicleSpeedAverage_Tag
{	 
	BOOL acc_VehicleSpeedAverageValid;
	U16 acc_VehicleSpeedAverage;
	float acc_VehicleSpeed;
}AccVehicleSpeedAverage_ST;
#define ACC_MIN_SPEED_ALERT  (0.3)
#define ACC_MAX_SPEED_ALERT  (30)

#define ACC_MIN_AUDIO_WARNNIG_INDEX  0
#define ACC_MAX_AUDIO_WARNNIG_INDEX  11
typedef struct AccPedestrianAlertSoundSelect_Tag
{
	BOOL acc_PedestrianAlertSoundSelectValid;
	U8 acc_PedestrianAlertSoundSelect;
	//U8 acc_PedestrianAlertInhibitSwitch;
}AccPedestrianAlertSoundSelect_ST;


/* Public data structures defines */





/* Public extern functions declare */
extern void ACC_Init(void);
extern void ACC_GetGearSts(AccGearLvl_ENUM * pGearLvl);
extern void ACC_GetSpeedValue(float * pSpeedValue);
extern void ACC_GetPedestrianAlertSoundSelect(U8 * pPedestrianAlertSoundSelect);
extern void ACC_GetPedtrnAlrtJudgeEnable(PU8 pPedtrnAlrtJudgeEnable);
extern void ACC_GetPedtrnAlrtInSwEnable(PU8 pPedtrnAlrtInhSwEnable);
extern void ACC_GetPedtrnAdoWrnngJudgeEnable(PU8 pPedtrnAdoWrnngJudgeEnable);
extern void ACC_GetPedtrnAdoWrnng(PU8 pPedtrnAdoWrnng);
extern void ACC_GetPedtrnAdoWrnngJudgeEnable(PU8 pPedtrnAdoWrnngJudgeEnable);
extern void ACC_GetPedtrnAdoWrnng(PU8 pPedtrnAdoWrnng);
extern void ACC_GetPedtrnSystemVolume(PU8 pPedtrnSystemVolume);
extern void ACC_Process_10ms(void);


#endif /*_ACC_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0      Xiaojie.Zheng     2016-12-06     Initial
*
*===========================================================================*/

