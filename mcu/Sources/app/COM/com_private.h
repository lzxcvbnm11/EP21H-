/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : com_private.h
* Description :the private datas of the com module.
* Author: Jason.Sun
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _COM_PRIVATE_H_

#define _COM_PRIVATE_H_
/*private Macro defines */

#define COM_CAN_NWM_ENABLE  1

#define NETSLEEP_COUNTER   6000

#define TEST_PASSED() while(1)
#define TEST_FAILED() while(1)
#define PET_WATCHDOG()


#define ENABLE_INTS()   v_ctl_ints_restore((v_imask)0)

#if 0
/* Private data structures defines */
typedef enum COMWakeUpSource_Tag
{
	SOURCE_COM_NONE =( 0u ),/*�޻���*/
	SOURCE_COM_SSB,/*SSB����*/
	SOURCE_COM_NET,/*���绽��*/
	SOURCE_COM_ALL
}COMWakeUpSource_ENUM;
#endif

#define RSCAN_BUS_OFF		0x10UL
#define RSCAN_ERR_PASSIVE	0x8UL

#define CAN_GRAMINIT_ON  	(0x8UL)
#define CAN_GSLPSTS_ON   	(0x4UL)
#define CAN_GRSTSTS_ON   	(0x1UL)
#define CAN_CSLPSTS_ON   	(0x4UL)
#define CAN_CHLTSTS_ON   	(0x2UL)
#define CAN_CRSTSTS_ON   	(0x1UL)
#define CAN_TMTRM_ON     	(0x8U)
#define CAN_TMTR_ON      	(0x1U)
#define CAN_AFLDAE_ON    	(0x100UL)
#define CAN_GSLPR_MASK   	(0x4UL)
#define CAN_GMDC_MASK    	(0x3UL)
#define CAN_CSLPR_MASK   	(0x4UL)
#define CAN_CHMDC_MASK   	(0x3UL)

#define NWM_PROCESS_PERIOD    10
#define NETWORK_KEEP_PERIOD   1000
#define NWM_SLEEP_CNT         (10000/5)

#define  COM_100MS_CNT   (100/5)

 /*����100 ms �����index ������*/
typedef enum SysNetworkState_Tag
{
    INDEX_SYSSTATE_STARTUP = (0u),      
    INDEX_SYSSTATE_SHUTDOWN,
    INDEX_SYSSTATE_NORMAL,
    INDEX_SYSSTATE_ALL
}SysNetworkState_ENUM;


/* Private static functions declare */
//static void com_nwm_process( void);

//////static COMWakeUpSource_ENUM com_GetWakeUpSource(void);
//static BOOL com_NetManagerModeCheck(void);
//static void com_NetConProcess(void);
//////static BOOL com_WakeUpFrameStoped(void);
//static void com_nwm_state_check(void);
static void com_nwm_process(void);
static void com_nwm_process_10ms(void);

#endif /*_COM_PRIVATE_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun      2018-06-05             Initial
*
*===========================================================================*/




