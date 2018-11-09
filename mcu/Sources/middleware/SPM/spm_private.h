/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : spm_cfg.h
* Description : 
* Author:qq
* Date: 2018-06-07
******************************************************************************/


/* check of multiple include */
#ifndef _SPM_PRIVATE_H_
#define _SPM_PRIVATE_H_

/* Files for including */
//#include "yd_typedefs.h"
#include "spm_public.h"
/*
功放状�??

1，过流保护，拉低FALUT PIN,update i2c regsiter
2，DC DETECT,拉低FALUT PIN,update i2c regsiter
3，Overtemperature，拉低FALUT PIN,update i2c regsiter
4，Undervoltage�?	 拉低FALUT PIN, reset i2c regsiter
5，Overvoltage�?	 拉低FALUT PIN, update i2c regsiter

负载状�??
1，对地短�?
2，和电源短路
3，负载短�?
4，负载开�?
*/

/* Macro defines */
#define DEVICE_I2C_WRITE_ADDR 					0xD8
#define DEVICE_I2C_READ_ADDR					0xD8

#define DEVICE_I2C_FAULTREG_ADDR 		      	0x01
#define DEVICE_I2C_STATUSLOADDIOGREG_ADDR		0x02
#define DEVICE_I2C_CONTROLREG_ADDR			  	0x03
#define DEVICE_I2C_DATALENG			        	  1
#define BUFFER_COMPARISONVALUE                    0
#define DEVICE_CONTROLREG_BUFVALUE              0x78    /*��ʼ��д����ƼĴ�����ֵ*/

/* Private data structures defines */
typedef enum SwitchFreqNum_Tag
{
	  INDEX_SPM_SWITCHFREQ400KHZ = (0u),/*26dB gain,switching frequency set to 400kHz,SpeakerGuard protection circuitry disabled*/
    INDEX_SPM_SWITCHFREQ500KHZ,
    INDEX_SPM_SWITCHFREQALL
}SwitchFreqNum_ENUM;

typedef enum SpeakerGuardOUTNum_Tag
{
    INDEX_SPM_SPEAKERGUARDOUT14V = (3u),
    INDEX_SPM_SPEAKERGUARDOUT11V8,
    INDEX_SPM_SPEAKERGUARDOUT9V8,
    INDEX_SPM_SPEAKERGUARDOUT8V4,
    INDEX_SPM_SPEAKERGUARDOUT7V,
    INDEX_SPM_SPEAKERGUARDOUT5V9,
    INDEX_SPM_SPEAKERGUARDOUT5V,
    INDEX_SPM_SPEAKERGUARDOUTALL
}SpeakerGuardOUTNum_ENUM;

typedef enum GAINNum_Tag
{
	  INDEX_SPM_GAIN20DB = (11u),
	  INDEX_SPM_GAIN26DB,
    INDEX_SPM_GAIN32DB,
    INDEX_SPM_GAIN36DB,
    INDEX_SPM_GAINALL
}GAINNum_ENUM;

typedef enum SwitchFreq_Tag
{
	  EVT_SPM_SWITCHFREQ400KHZ = (0u),
    EVT_SPM_SWITCHFREQ500KHZ,
    EVT_SPM_SWITCHFREQALL
}SwitchFreq_ENUM;

typedef enum SpeakerGuardOUT_Tag
{
    EVT_SPM_SPEAKERGUARDOUT14V = (0u),
    EVT_SPM_SPEAKERGUARDOUT11V8,
    EVT_SPM_SPEAKERGUARDOUT9V8,
    EVT_SPM_SPEAKERGUARDOUT8V4,
    EVT_SPM_SPEAKERGUARDOUT7V,
    EVT_SPM_SPEAKERGUARDOUT5V9,
    EVT_SPM_SPEAKERGUARDOUT5V,
    EVT_SPM_SPEAKERGUARDOUTALL
}SpeakerGuardOUT_ENUM;

typedef enum GAIN_Tag
{
	  EVT_SPM_GAIN20DB = (0u),
	  EVT_SPM_GAIN26DB,
    EVT_SPM_GAIN32DB,
    EVT_SPM_GAIN36DB,
    EVT_SPM_GAINALL
}GAIN_ENUM;

typedef struct ControlReg_Tag
{
    SwitchFreq_ENUM freq; /* */
    SpeakerGuardOUT_ENUM out;
    GAIN_ENUM gain; /* */
}ControlReg_ST;

const ControlReg_ST ControlRegList[INDEX_SPM_GAINALL]=
{
   { EVT_SPM_SWITCHFREQ400KHZ, 0, 0},
   { EVT_SPM_SWITCHFREQ500KHZ, 0, 0},
   { EVT_SPM_SWITCHFREQALL, 0, 0},
   { 0, EVT_SPM_SPEAKERGUARDOUT14V, 0},
   { 0,EVT_SPM_SPEAKERGUARDOUT11V8, 0},
   { 0,EVT_SPM_SPEAKERGUARDOUT9V8, 0},
   { 0,EVT_SPM_SPEAKERGUARDOUT8V4, 0},
   { 0,EVT_SPM_SPEAKERGUARDOUT7V,  0},
   { 0,EVT_SPM_SPEAKERGUARDOUT5V9, 0},
   { 0,EVT_SPM_SPEAKERGUARDOUT5V,  0},
   { 0,EVT_SPM_SPEAKERGUARDOUTALL, 0}, 
   { 0, 0, EVT_SPM_GAIN20DB },
   { 0, 0, EVT_SPM_GAIN26DB },
   { 0, 0, EVT_SPM_GAIN32DB },
   { 0, 0, EVT_SPM_GAIN36DB },
  // { 0, 0, EVT_SPM_GAINALL  },
};

 extern U8 spm_FaultReg_Read();                        /*����FAULTʱ��iic��ʼ�����ȡ*/
 extern U8 spm_StatusLoadDiagReg_Read();               /*����FAULT��STANDBYʱ��iic��ʼ���������Ϣ�Ķ�ȡ*/
 extern U8 spm_ControlReg_Write(U8 Index_Freq,U8 Index_OUT,U8 Index_GAIN);
 
#endif /* _SPM_PRIVATE_H_ */

/*----------------- End of file -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0           qq           2018-06-7           Initial
*
*===========================================================================*/
