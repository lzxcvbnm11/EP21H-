/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : diag_info.inc
* Description : including the DS module all header files
* Author: qq
* Date: 2018-07-18
******************************************************************************/

/* check of multiple include */
#ifndef _DIAG_PRIVATE_H_

#define _DIAG_PRIVATE_H_

/* Files for including */

#define DIAG_PROCESS_PERIOD                              20
#define DIAG_QUIETMODE_PERIOD                            5000    /*安静模式5s内无任何有效诊断请求*/
#define DIAG_QUIETMODECNT                        (DIAG_QUIETMODE_PERIOD)/(DIAG_PROCESS_PERIOD)

typedef enum DiagnosticReq_Tag
{
	DIAG_BYTE0_DLC = (0u),
	DIAG_BYTE1_SID,
	DIAG_BYTE2_ID1,
	DIAG_BYTE3_ID2,
	DIAG_BYTE4_D1,
	DIAG_BYTE5_D2,
	DIAG_BYTE6_D3,
	DIAG_BYTE7_D4,
	//DIAG_BYTE8_D5,
	DIAG_BYTE_ALL
}DiagnosticReq_ENUM;

typedef enum DiagLogisticsDataRead_Tag
{
	DIAG_ECU_PARTNUMBER = (0u),
	DIAG_ECU_HARDWARENUMBER,
	DIAG_ECU_SOFTWARENUMBER,
	DIAG_ECU_ALL
}DiagLogisticsDataRead_ENUM;

typedef enum DiagnosticSignal_Tag
{
	DIAG_SIGNAL_DIAGNOSTICREQ = (0u),
	DIAG_SIGNAL_DIAGNOSTIFUNCADDRREQ,
	DIAG_SIGNAL_ALL
}DiagnosticSignal_ENUM;


U8 DiagnosticReqList[DIAG_ECU_ALL][8] =
{
	{0x03,0x22,0xf1,0x87,0xaa,0xaa,0xaa,0xaa},		/*	请求 读取零件�?		*/
	{0x03,0x22,0xf1,0x91,0xaa,0xaa,0xaa,0xaa},		/*	请求 读取硬件版本�?    	   */
	{0x03,0x22,0xf1,0xa0,0xaa,0xaa,0xaa,0xaa},		/* 	请求 读取软件版本�?   		*/
};

#if 0
DiagnosticReqByte_ST DiagnosticAckList[DIAG_ECU_ALL] =
{
	{0x07,0x62,0xf1,0x87,0x10,0x53,0x94,0x67},		/*	响应 读取零件�?		*/
	{0x07,0x62,0xf1,0x91,0x10,0x62,0x20,0x55},		/*	响应 读取硬件版本�?    	   */
	{0x07,0x62,0xf1,0xa0,0x10,0x62,0x20,0x58},		/* 	响应 读取软件版本�?   		*/
};
#endif

U8 DiagnosticAckPartNumber[8] = {0x07,0x62,0xf1,0x87,0x10,0x53,0x94,0x67};		/*	响应 读取零件�?		*/
U8 DiagnosticAckHardwareNumber[8] = {0x07,0x62,0xf1,0x91,0x10,0x62,0x20,0x55};		/*	响应 读取硬件版本�?    	   */
U8 DiagnosticAckSoftwareNumber[8] = {0x07,0x62,0xf1,0xa0,0x10,0x62,0x20,0x58};		/* 	响应 读取软件版本�?   		*/

typedef enum DiagnosticReqMsg_Tag
{
	DIAG_SESSION_ENTER = (0u),
	DIAG_SESSION_EXIT,
	DIAG_SESSION_KEEP,
	DIAG_ECU_RESET,
	DIAG_SESSION_ENTER_ANOTHER,
	DIAG_SESSION_EXIT_ANOTHER,
	DIAG_SESSION_KEEP_ANOTHER,
	DIAG_ECU_RESET_ANOTHER,
	DIAG_MSG_ALL
}DiagnosticReqMsg_ENUM;

U8 DiagnosticMsgList[DIAG_MSG_ALL][8] =
{
	{0x02,0x10,0x02,0,0,0,0,0},  	 /* 诊断会话控制1 */
	{0x02,0x10,0x01,0,0,0,0,0},	 /* 诊断会话控制2 */
	{0x02,0x3e,0x00,0,0,0,0,0},	 /* 测试工具保持连接 */
	{0x02,0x11,0x01,0,0,0,0,0},	 /* 电控单元复位 */
	{0x02,0x10,0x82,0,0,0,0,0},  	 /* 诊断会话控制1 */
	{0x02,0x10,0x81,0,0,0,0,0},	 /* 诊断会话控制2 */
	{0x02,0x3e,0x80,0,0,0,0,0},	 /* 测试工具保持连接 */
	{0x02,0x11,0x81,0,0,0,0,0},	 /* 电控单元复位 */
};

static DiagLogisticsDataRead_ENUM Diag_LogisticsDataRead = DIAG_ECU_ALL;
static DiagQuietModeFun_ENUM Diag_QuietModeSts = DIAG_QUIET_EXIT_MODULE;

static U8 DIAG_DiagnosticReqValid = FALSE;
static U8 DIAG_QUIETMODECOUNT = 0;
static U8 DIAG_NoReceiveSignalCount =0;

void diag_DateReceive(void);
void diag_LogisticsDataReadFun_20ms(void);
void diag_QuietModeFun_20ms(void);
void diag_PedtrnAlrtCtlSysFlt_20ms(void);

#endif /*_DIAG_INFO_INC_*/

                 
/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       QQ      2018-07-18       Initial
*
*===========================================================================*/
