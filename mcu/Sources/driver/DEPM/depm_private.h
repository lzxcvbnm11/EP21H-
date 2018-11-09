/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : eeprom_private.h
* Description : the private datas of the eeprom
* Author: qq
* Date: 2018-05-30
******************************************************************************/

/* check of multiple include */
#ifndef _DEPM_PRIVATE_H_
#define _DEPM_PRIVATE_H_

/* Macro defines */

/*external data structures defines*/
#define P_PAGE_SIZE                 0x4000u /*16K Byte*/
#define P_PAGE_START_ADDR           0x8000u
#define P_PAGE_END_ADDR             0xBFFFu
#define P_PAGE_ADDR_MASK            0x0000FFFFul
#define P_PAGE_TYPE                 0u
#define P_FLASH_SECTOR_SIZE         512u
#define P_FLASH_PROG_ALINE          0xFFFFFFF8ul /*global address and program length [2..0] = 0*/
#define P_FLASH_PROG_BASE_WD_SIZE   4u      /*one phrase, 64 bits*/
#define P_FLASH_PAGE_SHIFT_BIT      14u

#define P_FLASH_BLOCK_0_START_ADDR  0x7F0000u
#define P_FLASH_BLOCK_0_END_ADDR    0x7FFFFFu
#define P_FLASH_BLOCK_1_START_ADDR  0x780000u
#define P_FLASH_BLOCK_1_END_ADDR    0x78FFFFu

//#define FLASH_CLK_DIVIDER           (BUS_FRQ_MHZ - 1)
#define FLASH_SECURITY_ENABLED      2u
#define FLASH_SECURITY_UNSECURED    2u

#define FLASH_START_ADDR            0x00020000ul
#define FLASH_END_ADDR              0x0003FFFFul
#define FLASH_CONFIG_ADDR           0x0003FF00ul
#define FLASH_ACCESS_KEY_ADDR       FLASH_CONFIG_ADDR
#define FLASH_ACCESS_KEY_LEN        8
#define FLASH_PROTECT_ADDR          0x0003FF0Cul
#define EEPROM_PROTECT_ADDR         0x0003FF0Dul
#define OPT_PROTECT_ADDR            0x0003FF0Dul
#define SECURITY_PROTECT_ADDR       0x0003FF0Ful

#define INEEPROM_START_ADDR         0x0400u
#define INEEPROM_END_ADDR           0x13FFu /* 4 KByte */
#define INEEPROM_SECTOR_SIZE        4u      /* 4 Bytes */
#define INEEPROM_BASE_ADDR_MASK     0xFFFCu

#define FLASH_CMD_START             0x80u
#define FLASH_CMD_COMPLETE          0x80u

/*FCMD high byte used*/
#define FCMD_ERASE_VERIFY_ALL       0x0100u
#define FCMD_ERASE_VERIFY_BLOCK     0x0200u
#define FCMD_ERASE_VERIFY_P_SECTION 0x0300u
#define FCMD_READ_ONCE              0x0400u
#define FCMD_PROG_P_FLASH           0x0600u
#define FCMD_PROG_ONCE              0x0700u
#define FCMD_ERASE_ALL              0x0800u
#define FCMD_ERASE_P_BLOCK          0x0900u
#define FCMD_ERASE_P_SECTOR         0x0A00u
#define FCMD_UNSECURE_FLASH         0x0B00u
#define FCMD_VERIFY_ACCESS_KEY      0x0C00u
#define FCMD_SET_USER_MARGIN_LEVER  0x0D00u
#define FCMD_SET_FIELD_MARGIN_LEVER 0x0E00u
#define FCMD_FULL_PARTITION_D_FLASH 0x0F00u /* IN-EEPROM */
#define FCMD_ERASE_VERIFY_D_SECTION 0x1000u
#define FCMD_PROG_D_FLASH           0x1100u
#define FCMD_ERASE_D_SECTOR         0x1200u
/* Private data structures defines */

/*constant define*/

/* Private static functions declare */

extern void depm_StartAndWait(void);
extern BOOL depm_Send_Cmd(U16 p_cmd[], U8 cmd_length);
extern U32 depm_GetEepromAddress(U32 addr);
extern U8 depm_GetRoutinePage(U32 phy_addr);

#endif /*_DEPM_PRIVATE_H_*/

/*----------------end of file------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0             qq            2018-05-30            Initial
*
*===========================================================================*/

