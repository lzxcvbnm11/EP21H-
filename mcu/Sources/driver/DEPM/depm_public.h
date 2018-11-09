/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name :adce_public.h
* Description : public data of the eeprom
* Author: qq
* Date: 2018-05-30
******************************************************************************/

/* check of multiple include */
#ifndef __DEPM_PUBLIC_H__
#define __DEPM_PUBLIC_H__


extern void DEPM_Init(void);
extern BOOL DEPM_GetInitStatus(void);
extern BOOL DEPM_Erase(U32 start_addr,U32 length);
extern BOOL DEPM_Write(U16 logic_start_addr,U8 *p_data_buffer,U16 length);
extern BOOL DEPM_Read( U16 logic_start_addr,U8 *p_data_buffer, U16 length);



#endif __DEPM_PUBLIC_H__ /*End of __DEPM_PUBLIC_H__ */

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0            qq             2018-05-30            Initial
*
*===========================================================================*/

