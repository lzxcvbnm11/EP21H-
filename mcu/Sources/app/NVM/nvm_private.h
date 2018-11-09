/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : nvm_private.h
* Description : the private informations datas of the nvm
* Author: Xuenian.Feng
* Date: 2016-12-1
******************************************************************************/
//

/* check of multiple include */
#ifndef _NVM_PRIVATE_H_
#define _NVM_PRIVATE_H_
#include "yd_typedefs.h"
#include "nvm_public.h"
/*Private Macros defines*/

#define E2PROM_MIN_LOGIC_ADDR	 			0x000
#define E2PROM_MAX_LOGIC_ADDR    			0xFFF  /*total size 4K bytes, sector 4byte,1024 sectors*/

#define E2PROM_PAGE_LEN   				    0x04

#define ADDR_PEDTRN_ALRT_SND_SLT		 	0x000
#define ADDR_PEDTRN_ALRT_SDN_VOL		 	0x002

/*@SYS BLOCK =====START*/
/*@SYS BOLCK DEFINE  STRUCT END*/
/*@FBL  BLOCK =====END*/
/*@CONFIG  BLOCK =====START*/
/*@CONFIG  BLOCK =====END*/
/*Private Data Structures defines*/
typedef struct NVMDataBase_Tag
{
    U16 addr;	/*数据所在逻辑地址*/
    PU8 pValue; /*要保存的数据指针*/
    U8  size;   /*数据大小*/
}NVMDataBase_ST;


/*SYS BOLCK DEFINE  STRUCT END*/
/*FBL BLOCK RESERVED FOR V2  */
/*LOGIST BOLCK DEFINE  STRUCT START*/



typedef union  nvm_PedtrnAlrtSndSel_UnTag
{
    U8  buf[2];
    nvm_PedtrnAlrtSndSel_ST data;
}nvm_PedtrnAlrtSndSel_UN;

typedef union  nvm_PedtrnAlrtSndVol_UnTag
{
    U8  buf[2];
    nvm_PedtrnAlrtSndVol_ST data;
}nvm_PedtrnAlrtSndVol_UN;


typedef struct NVMDataSts_Tag
{
   BOOL valid;
   U8 sts;
}NVMDataSts_ST;

#define  WRITE_FIRST_PAGE   0x00
#define  WRITE_MIDDLE_PAGE  0x01
#define  WRITE_FINAL_PAGE   0x02

typedef struct  nvm_RW_Tag
{
    U8 FirstByte;
    U8 EndByte;

    U16 PageNum;
    U16 PageAddr;
    U16 ofs;

    U8 Error;
    U8 Step;

}nvm_RW_ST;


/*FBL BLOCK STRUCT  STRUCT START*/


/*constant define*/

NVMDataSts_ST  nvm_datasts[INDEX_NVM_ALL] =
{
    {/*INDEX_NVM_PEDTRN_ALRT_SND_SLT*/VALID,STS_IDLE},
    {/*INDEX_NVM_PEDTRN_ALRT_SND_VOL*/VALID,STS_IDLE}
};
	
typedef  struct  nvm_MapData_Tag
{
	 nvm_PedtrnAlrtSndSel_UN PedtrnAlrtSndSel;
	 nvm_PedtrnAlrtSndVol_UN PedtrnAlrtSndVol; 
}nvm_MapData_ST;

 static nvm_MapData_ST nvm_Data;
 

 const NVMDataBase_ST nvm_DataBase[INDEX_NVM_ALL]=
 {
	{0,nvm_Data.PedtrnAlrtSndSel.buf,0},
	{ADDR_PEDTRN_ALRT_SND_SLT,nvm_Data.PedtrnAlrtSndSel.buf,NVM_SOUND_SELECT_LEN},
	{ADDR_PEDTRN_ALRT_SDN_VOL,nvm_Data.PedtrnAlrtSndVol.buf,NVM_VOLUME_SELECT_LEN}
 };

  


/* Private static functions declare */
static U8 nvm_Write(NVMKeyBlock_ENUM index);
static U8 nvm_Update(NVMKeyBlock_ENUM index,  PU8 pRes, U8 size);

//static U8 nvm_SYS_GetPage0(NVMKeyBlock_ENUM index, PU8 pRes, U8 size);
static U8 nvm_CalCheckSum(PU8 pRes, U8 size);

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

