/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : nvm_public.h
* Description : the public informations datas of the nvm
* Author: Xuenian.Feng
* Date: 2016-12-1
******************************************************************************/

/* check of multiple include */
#ifndef _NVM_PUBLIC_H_
#define _NVM_PUBLIC_H_
#include "yd_typedefs.h"


/*写数据状态*/
#define STS_IDLE 			0
#define STS_WAIT 			1
#define STS_WRITE 			2
#define STS_ERR 			3

#define NVM_WR_OK  			0x01
#define NVM_WR_DATAINVALID 	0x02
#define NVM_WR_ING 			0x03
#define NVM_WR_ERR_PRIVIOUS 0x04
#define NVM_WR_EEDFLT 		0x05

/*数据默认值*/
#define SOUND_SELECT_DEF_VALUE   0x00	/*0x00 <--> sound 1,0x01 <--> sound 2,0x02 <--> sound 3*/
#define VOLUME_SELECT_DEF_VALUE  0x06	/*默认音量为 H <--> 0x06,  L <--> 0x05*/

/*数据长度*/
#define NVM_SOUND_SELECT_LEN  	0x02
#define NVM_VOLUME_SELECT_LEN  	0x02






/*ENUM START*/
typedef enum NVMKeyBlock_Tag
{
		INDEX_NVM_NONE = 0x00,
        INDEX_NVM_PEDTRN_ALRT_SND_SLT,
        INDEX_NVM_PEDTRN_ALRT_SND_VOL,
        /*LOGIST RESERVED*/
        /*FBL */
        /*CONFIG*/
        /* DTC */
        /*SNAPSHOT*/
        /*FUNCTION*/
        INDEX_NVM_ALL ,
}NVMKeyBlock_ENUM;

/*CONFIG BLOCK STRUCT  STRUCT START*/
typedef struct  nvm_PedtrnAlrtSndSel_Tag
{
	U8	PedtrnAlrtSndSel;
	U8  CheckSum;
}nvm_PedtrnAlrtSndSel_ST;


typedef struct  nvm_PedtrnAlrtSndVol_Tag
{
	U8	PedtrnAlrtSndVol;
	U8  CheckSum;
}nvm_PedtrnAlrtSndVol_ST;



/*Public Extern Functions Declare*/
extern void NVM_Init(void);
extern void NVM_Process_50ms(void);
extern U8 NVM_GetParas(NVMKeyBlock_ENUM index, PU8 pRes, U8 size);
extern U8 NVM_SetParas(NVMKeyBlock_ENUM index,  PU8 pRes, U8 size);
extern U8 NVM_GetWriteResult(NVMKeyBlock_ENUM index,  PU8 pRes);
extern U8 NVM_GetWorkSts(void);
#endif


/*------------------end of file----------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0         Xuenian.Feng      2016-12-1           Initial
*
*===========================================================================*/

