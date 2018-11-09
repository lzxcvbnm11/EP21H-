/*****************************************************************************
* Copyright (C) 2016 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : nwd.c
* Description : nwd module
* Author: huangyifan
* Date: 2017-07-04
******************************************************************************/
/*-----------------------------------------------------------------------*/
/*----Description of file-----------------------------------------------------*/
/*-----------------------------------------------------------------------*/



/*************************************************************************
SLF public file 
*************************************************************************/


/*------------------------------------------------------------------------*/
/*-----Head of file----------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*check of multiple include*/
#ifndef _NWD_PUBLIC_H_
#define _NWD_PUBLIC_H_

#include "yd_typedefs.h"

#if 0
#define ficm_node_flag_handle ((v_fl_handle)&v_flags[0])
#define gw_node_flag_handle ((v_fl_handle)&v_flags[1])
#define iecu_node_flag_handle ((v_fl_handle)&v_flags[2])
#define ipk_node_flag_handle ((v_fl_handle)&v_flags[3])
#define ecm_node_flag_handle ((v_fl_handle)&v_flags[4])
#define ficm_36b_frame_flag_handle ((v_fl_handle)&v_flags[5])
#define ficm_376_frame_flag_handle ((v_fl_handle)&v_flags[6])
#define gw_46a_frame_flag_handle ((v_fl_handle)&v_flags[7])
#define gw_1f2_frame_flag_handle ((v_fl_handle)&v_flags[8])
#define gw_194_frame_flag_handle ((v_fl_handle)&v_flags[9])
#define gw_230_frame_flag_handle ((v_fl_handle)&v_flags[10])
#define gw_169_frame_flag_handle ((v_fl_handle)&v_flags[11])
#define gw_1f1_frame_flag_handle ((v_fl_handle)&v_flags[12])
#define gw_540_frame_flag_handle ((v_fl_handle)&v_flags[13])
#define gw_0af_frame_flag_handle ((v_fl_handle)&v_flags[14])
#define gw_196_frame_flag_handle ((v_fl_handle)&v_flags[15])
#define gw_353_frame_flag_handle ((v_fl_handle)&v_flags[16])
#define iecu_390_frame_flag_handle ((v_fl_handle)&v_flags[17])
#define ipk_541_frame_flag_handle ((v_fl_handle)&v_flags[18])
#define ecm_0c9_frame_flag_handle ((v_fl_handle)&v_flags[19])
#endif

typedef enum NwdNodeIndex_tag/*各节点的索引，供for循环使用*/
{
    INDEX_FICM_NODE = ( 0U ),
    INDEX_GW_NODE,
    INDEX_IECU_NODE,
    INDEX_IPK_NODE,
    INDEX_ECM_NODE,    
    INDEX_FICM_36B_SOT,
    INDEX_FICM_376_SOT,
   // INDEX_GW_46A_SOT,
    INDEX_GW_1F2_SOT,
    INDEX_GW_194_SOT,
   // INDEX_GW_230_SOT,
   // INDEX_GW_169_SOT,
    INDEX_GW_1F1_SOT,
   // INDEX_GW_540_SOT,
   // INDEX_GW_0AF_SOT,
    INDEX_GW_196_SOT,
    INDEX_GW_353_SOT,
    INDEX_IECU_390_SOT,
   // INDEX_IPK_541_SOT,
   // INDEX_ECM_0C9_SOT,
    INDEX_NODE_ALL
}NwdNodeIndex_ENUM;




/*Files for including*/
extern void NWD_Init(void);
extern void NWD_Process_5ms(void);
extern U8 NWD_GetNodeMissing(NwdNodeIndex_ENUM NodeIndex,PU8 sts);
extern BOOL NWD_GetBusOffFlt(void);

#endif



/*=======================================================
*  File Revision History (bottom to top:first revision to last revision)
*
*========================================================
*$Log:$
*

*Rev:                 Userid:                                date:                              description
*-----               -----                                 -----------                  -----------
*Rev 1               liuyingying                           2016-11-24                   initial
*rev 2               huangyifan                            2016-07-04                   modify
=========================================================*/


