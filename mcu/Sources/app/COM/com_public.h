/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : com_public.h
* Description :the public datas of the com module.
* Author: Jason.Sun
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _COM_PUBLIC_H_

#define _COM_PUBLIC_H_
#include "yd_typedefs.h"
#include "v_hand.h"
#include "volcano6.h"
#include "nwm_core.h"
#include "v_subbus.h"
/* Public Macros defines */

#define COM_PERIOD   		5
#define COM_NVM_PERIOD   	10
#define SSB_CHK_MAX_CNT   	(10000/COM_PERIOD)

#define SSB_NET_REQ_MAXCNT  (10000/COM_PERIOD)
/* Public data structures defines */
typedef enum COMNetStatus_Tag
{
	STATUS_COM_NETWAKE,
	STATUS_COM_NETSLEEP,
	STATUS_COM_ALL
}COMNetStatus_ENUM;
typedef enum COMSendType_Tag
{
	INDEX_COM_SEND_PedtrnAlrtVolSwSts_4bit = (0u),		/*发送当前声音音量*/
	INDEX_COM_SEND_PedtrnAlrtSndSltSts_2bit,      		/*发送当前声音类型*/
	INDEX_COM_SEND_PedtrnAlrtInh_2bit,		     		/*行人警示音开关状态*/
	INDEX_COM_SEND_PACMFlt_1bit,					 	/*行人警示音控制模块故障，记录故障用于诊断*/
	INDEX_COM_SEND_PedtrnAlrtCtlSysFlt_1bit,			/*行人警示音控制系统故障，仪表显示故障信息*/	
	INDEX_COM_SEND_PedtrnAlrtSpkrFlt_1bit,				/*行人警示音喇叭故障，记录故障用于诊断*/
	INDEX_COM_SEND_DiagnosticResp,						/*诊断请求应答*/
	INDEX_COM_SEND_keep_network_PACMHSC4_1bit,			/*保持网络*/	
	INDEX_COM_SEND_keep_network_PACMHSC4_UB_1bit,		/*保持网络*/
	INDEX_COM_SEND_wake_network_PACMHSC4_1bit,			/*wake up net work*/
	INDEX_COM_SEND_wake_network_PACMHSC4_UB_1bit,		/*wake up net work*/
	INDEX_COM_SEND_ALL
}COMSendType_ENUM;

typedef enum COMReceivedType_Tag
{
    INDEX_COM_RS_EPTAccelActuPos_8bit = (0u),	/*接受油门踏板信号，来判断加减速状态,[0,100] E=N*0.392157 %*/
    INDEX_COM_RS_EPTAccelActuPosV_1bit, 		/*判断油门踏板信号的有效性[0,1]*/
	INDEX_COM_RS_EPTStCmdOn_1bit,				/*Electric Powertrain Start Command On*/
	INDEX_COM_RS_EnSpd_16bit,					/*接受发动机转速信号，来实现模拟声音[0,16383.75] E=N*0.25 rpm*/
    INDEX_COM_RS_EnSpdSts_2bit, 				/*判断发动机转速信号的有效性。[0,3] 0x0=Normal Operation;0x1=Degraded Operation;0x3=Invalid;*/
    INDEX_COM_RS_PedtrnAlrtVolSwReq_4bit,		/*接受音量调节的请求 [0,15] */
    INDEX_COM_RS_PedtrnAlrtVolSwReqV_1bit,		/*音量调节的请求的有效性*/
    INDEX_COM_RS_PedtrnAlrtSndSltReq_2bit,		/*接受声音选择的请求[0,3]*/
    INDEX_COM_RS_PedtrnAlrtSndSltReqV_1bit, 	/*接受声音选择的请求的有效性*/
    INDEX_COM_RS_SysPwrMd_2bit, 				/*系统电源模式0x0=Off;0x1=ACC;0x2=Run;0x3=Crank 20ms*/
    INDEX_COM_RS_SysBPM_2bit,					/*系统备用电源模式0x0=Off;0x1=ACC;0x2=Run;0x3=Crank         20ms*/
    INDEX_COM_RS_SysBPMEnbd_1bit,				/*系统备用电源模式使能 20ms*/
    INDEX_COM_RS_EPTRdy_1bit,					/*电子动力系统ready 20ms*/
    INDEX_COM_RS_TrShftLvrPos_4bit, 			/*档位信息	25ms*/
    INDEX_COM_RS_TrShftLvrPosV_1bit,			/*档位信息有效 25ms*/
    INDEX_COM_RS_VehSpdAvgDrvn_15bit,			/*车辆平均车速[0,511.984375]，E=N*0.015625 km/h 100ms*/
    INDEX_COM_RS_VehSpdAvgDrvnV_1bit,			/*车辆平均车速有效 100ms*/
    INDEX_COM_RS_EPBSts_2bit,					/*Electric Park Brake Status*/    
	INDEX_COM_RS_EPBAvlbly_1bit,				/*Electronic Parking Brake Availability*/
    INDEX_COM_RS_PedtrnAlrtInhSwReq_2bit,		/*行人警示音开关 100ms*/
    INDEX_COM_RS_RstrFctryDeftsReq_1bit,		/*恢复出厂设置请求*/
    INDEX_COM_RS_LDircnIO_1bit, 				/*Left Direction Indication On*/
    INDEX_COM_RS_RDircnIO_1bit, 				/*Right Direction Indication On*/
    //INDEX_COM_RS_VehDrvngMd_3bit,				/*获取驾驶模式状态*/
    INDEX_COM_RS_PedtrnAdoWrnng_4bit,			/*iECU发送音频行人警示请求*/
    INDEX_COM_RS_DiagnosticReq_64bit,			/*诊断请求*/
    INDEX_COM_RS_DiagnosticFuncAddrReq_64bit,	/*Diagnostic functional address request*/
	INDEX_COM_RS_DTCInfomation_56bit,					/*DTC info*/
    INDEX_COM_RS_BCMAvlbly_1bit,				/*Body Control Module Availability*/
	INDEX_COM_RS_CalendarDay_5bit,				/*日*/
	INDEX_COM_RS_CalendarMonth_4bit,			/*月*/
	INDEX_COM_RS_CalendarYear_8bit,				/*年*/
	INDEX_COM_RS_ECMAvlbly_1bit,				/*Engine Control Module Availability*/
	INDEX_COM_RS_HCUAvlbly_1bit,				/*HCU Available*/
	INDEX_COM_RS_HourOfDay_5bit,				/*小时*/
	INDEX_COM_RS_MinuteOfHour_6bit,			    /*分钟*/
	INDEX_COM_RS_network_mode_8bit,				/*network mode */
	INDEX_COM_RS_PwrMdMstrAccryA_1bit,			/*Power Mode Master Accessory Active*/
	INDEX_COM_RS_PwrMdMstrRunCrkA_1bit,		/*Power Mode Master Run Crank Active*/
	INDEX_COM_RS_SCSAvlbly_1bit,				/*Stability Control System Availability*/
	INDEX_COM_RS_SecsOfMinute_6bit,				/*分钟*/
	INDEX_COM_RS_signal_config_id_16bit,		/*Signal Config Id*/
	INDEX_COM_RS_TCAvlbly_1bit,					/*TC Available Detect if specific ECU is available according to node missing strategy by gateway ECU*/
	INDEX_COM_RS_TMSpd_16bit,					/*电机转速信号，来实现模拟声音。[-32768,32767] E=N*1-32768 rpm */
	INDEX_COM_RS_TMSpdV_1bit,					/*判断电机转速信号的有效性 [0,1] */				
	INDEX_COM_RS_VehOdo_24bit,					/*Vehicle Odometer*/
	INDEX_COM_RS_VehOdoV_1bit,					/*Vehicle Odometer Validity*/
	INDEX_COM_RS_ALL
}COMReceivedType_ENUM;

/* Public extern functions declare */
extern void COM_Init(void);
extern BOOL COM_GetInitSts(void);
extern void COM_Process_5ms(void);
#if 0
extern void COM_WakeUpFrameOffKeep10s(void);
#endif
extern void COM_GetSignalValue_8(U16 Index, PU8 pRes);
extern void COM_GetSignalValue_BOOL(U16 Index, PU8 pRes);
extern U8 COM_GetNetStatus(COMNetStatus_ENUM *status);
extern void COM_GetSignalValue_16(U16 Index, PU16 pRes);
extern U8 COM_GetNetWorkSleepSts(void);
extern v_nwm_state COM_GetNwmState(void);
extern void COM_GetSignalValue_32(U16 Index, PU32 pRes);

extern void COM_SetSignalValue_BOOL(U16 Index, U8 val);
extern void COM_SetSignalValue_8(U16 Index, U8 val);

#endif /*_COM_PUBLIC_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun      2018-06-05                Initial
*
*===========================================================================*/

