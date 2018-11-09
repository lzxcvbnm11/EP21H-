/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : depm.c
* Description : Driver source file of EEPROM.
* Author: qq
* Date: 2018-05-30
******************************************************************************/

/* Files for including */
#include "depm_info.inc"

U8 depm_routine_ppage = 0xEu;
static BOOL depm_InitStatus = FALSE;

#pragma CODE_SEG RAM_CODE

/***************************************************
* Function: depm_StartAndWait
* Description:   drive start 
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:  qq       Date:2018-05-30   Version:V1.0
****************************************************/
void depm_StartAndWait(void)
{
    FSTAT = FLASH_CMD_START; /*Step5 start command*/
    while (!FSTAT_CCIF) /*Step6 wait cmd complete or an error occur*/
    {
      WDT_Feed();
//#warning  You May need service watchdog here        
    }
}
#pragma CODE_SEG DEFAULT


/***************************************************
* Function: depm_init
* Description:   初始化Flash时钟 
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:    qq     Date:2018-05-30   Version:V1.0
****************************************************/
void DEPM_Init(void)
{
    depm_routine_ppage = PPAGE;
    FCNFG = 0x00;
    if (0 == FCLKDIV_FDIVLD)
    {
       // FCLKDIV_FDIV = FLASH_CLK_DIVIDER; 
      	FCLKDIV = 0x0FU;                 // 总线时钟为16M时，FCLKDIV取值0x0F
        while (0 == FCLKDIV_FDIVLD)
        {
            ;
        }
        depm_InitStatus =TRUE;
        FSTAT = 0x30;  /*clear FACCERR and PVIOL flag*/
    }
    else
    {
    }
}

/***************************************************
* Function: DEPM_GetInitStatus
* Description: get DEPM module initialization status.
* Parameters:
*              
* Returns:
*           the value of the Init status.
*
* $Create & Verlog:$
* Author:qq  Date:2018-5-30   Version:V1.0
****************************************************/
U8  DEPM_GetInitStatus(void)
{
    return depm_InitStatus;
}


/***************************************************
* Function: depm_Send_Cmd
* Description:   
* Parameters: p_cmd, cmd_length
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:   qq      Date:2018-05-30   Version:V1.0
****************************************************/
BOOL depm_Send_Cmd(U16 p_cmd[], U8 cmd_length)
{
    U8 cmd_index = 0;
    if (1 == FSTAT_CCIF) /*Step2 check last command is complete or not*/
    {
        /*Step3 clear Access Error and Protection Violation and set page*/
        PPAGE = depm_routine_ppage;
        FSTAT = (FSTAT_FPVIOL_MASK | FSTAT_ACCERR_MASK); /*Must used =, don't used |= operate*/

        for (cmd_index = 0; cmd_index < cmd_length; cmd_index++)/*Step4 set command array*/
        {
            FCCOBIX = cmd_index; /*set CMD*/
            FCCOB   = p_cmd[cmd_index];
        }

        depm_StartAndWait();
        
        if (FLASH_CMD_COMPLETE == (0xFC & FSTAT)) /*Note this*/
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}


/***************************************************
* Function: depm_GetEepromAddress
* Description:   
* Parameters: addr
* Returns: addr
* $Create & Verlog:$
* Author:    qq     Date:2018-05-30   Version:V1.0
****************************************************/
U32 depm_GetEepromAddress(U32 addr)
{
    if (addr >= FLASH_START_ADDR && addr <= FLASH_END_ADDR)
    {
        /* Is physical address already */
    }
    else
    {
        if (   (addr >= 0x4000 && addr <= 0x7FFF)
            || (addr >= 0xC000 && addr <= 0xFFFF)
           )
        {
            addr = addr | 0x30000ul;
        }
        else if (   ((addr & P_PAGE_ADDR_MASK) >= P_PAGE_START_ADDR)
    		     && ((addr & P_PAGE_ADDR_MASK) <= P_PAGE_END_ADDR)
    		      	)/*is page mode addr*/
        {
            /*allways treat by ppage*/
            addr = ((addr >> 16) << P_FLASH_PAGE_SHIFT_BIT) + ((addr & 0x0000FFFFu) - P_PAGE_START_ADDR);
        }
    }
    return addr;
}

#if 0
/***************************************************
* Function: phy_to_ppage_address 
* Description:   
* Parameters: phy_addr
* Returns: ppage_addr
* $Create & Verlog:$
* Author:    qq     Date:2018-05-30   Version:V1.0
****************************************************/
U16 phy_to_ppage_address(U32 phy_addr)
{
    U16 ppage_addr = 0;
    U16  block_index = 0;

    if (phy_addr >= FLASH_START_ADDR && phy_addr <= FLASH_END_ADDR)
    {
        phy_addr = phy_addr - FLASH_START_ADDR;
        ppage_addr = (U16)((phy_addr % P_PAGE_SIZE) + P_PAGE_START_ADDR);
    }
    return ppage_addr;
}
#endif

/***************************************************
* Function: depm_GetRoutinePage
* Description:   
* Parameters: phy_addr
* Returns: addr_ppage
* $Create & Verlog:$
* Author:   qq      Date:2018-05-30   Version:V1.0
****************************************************/
U8 depm_GetRoutinePage(U32 phy_addr)
{
    U8 addr_ppage = 0xFEU;
    addr_ppage = (U8)(phy_addr >> P_FLASH_PAGE_SHIFT_BIT);
    return addr_ppage;
}


/***************************************************
* Function: flash_erase
* Description:   
* Parameters: start_addr length
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:   qq      Date:2018-05-30   Version:V1.0
****************************************************/
BOOL DEPM_Erase(U32 start_addr,U32 length)
{
    U32 phy_start_addr;
    U32 phy_end_addr;
    U16 cmd_array[2];
    S32  block_index = 0;

    phy_start_addr = depm_GetEepromAddress(start_addr); /*Not check start address*/
    phy_end_addr = phy_start_addr + length - 1;

    if (phy_start_addr < FLASH_START_ADDR || phy_end_addr > FLASH_END_ADDR)
    {
        return FALSE;
    }
    
    /*erase address available*/
    while (phy_start_addr <= phy_end_addr)
    {
        WDT_Feed();
//#warning  You need service watchdog here
        cmd_array[0] = FCMD_ERASE_P_SECTOR | ((phy_start_addr >> 16) & 0x00FF);
        cmd_array[1] = phy_start_addr & 0x0000FFFF;
        depm_routine_ppage = depm_GetRoutinePage(phy_start_addr);
        if (FALSE == depm_Send_Cmd(cmd_array,2))
        {
            return FALSE;
        }
        phy_start_addr += P_FLASH_SECTOR_SIZE;
    }
    return TRUE;
}


/***************************************************
* Function: depm_write
* Description:   
* Parameters: *p_data_buffer phy_start_addr
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:    qq     Date:2018-05-30   Version:V1.0
****************************************************/
BOOL DEPM_Write(U16 logic_start_addr,U8 *p_data_buffer,U16 length)
{
    U16 cmd_array[6];
    U16 phy_base_addr;
    S32  i_index = 0;
    S32  data_index = 0;
    U16 *cur_prog_data_addr;
    U8  sector_prog[INEEPROM_SECTOR_SIZE] = {0}; /*4 bytes*/
	U16 phy_start_addr = logic_start_addr + INEEPROM_START_ADDR;
    if ((0 == p_data_buffer) || (0 == length))
    {
        return FALSE;
    }
    else if (phy_start_addr < INEEPROM_START_ADDR || (phy_start_addr + length - 1) > INEEPROM_END_ADDR)
    {
        return FALSE;
    }
    else
    {
        /*Address and length correct.*/
    }
    /*program address available*/
    while (length > 0) /*1 sector program a loop*/
    {
        WDT_Feed();
    //#warning  You may need service watchdog here
        /*Step 1. combination program data sector*/
        
        phy_base_addr = phy_start_addr & INEEPROM_BASE_ADDR_MASK;
        for (i_index = 0, data_index = 0; i_index < INEEPROM_SECTOR_SIZE; i_index++)
        {
            if ((length > 0) && (phy_base_addr >= phy_start_addr))
            {
                sector_prog[i_index] = p_data_buffer[data_index];
                length--;
                data_index++;
            }
            else
            {
                sector_prog[i_index] =  *(U8 *)(phy_base_addr);
            }
            phy_base_addr++;
        }

        /*Step 2. Erase sector*/
        phy_base_addr = phy_start_addr & INEEPROM_BASE_ADDR_MASK;
        phy_start_addr = phy_start_addr + data_index; /* Point to next data area */
        p_data_buffer = p_data_buffer + data_index;
        cmd_array[0] = FCMD_ERASE_D_SECTOR;           /* inEEPROM GlobalAddr[17:16] is 00B */
        cmd_array[1] = phy_base_addr;
        if (FALSE == depm_Send_Cmd(cmd_array,2))
        {
            return FALSE;
        }
        
        /*Step 3. Program new sector*/
        WDT_Feed();
        //#warning  You may need service watchdog here
        
        cur_prog_data_addr = (U16 *)sector_prog;
   
        cmd_array[0] = FCMD_PROG_D_FLASH;
        cmd_array[1] = phy_base_addr;
        cmd_array[2] = cur_prog_data_addr[0];
        cmd_array[3] = cur_prog_data_addr[1];
            
        if (FALSE == depm_Send_Cmd(cmd_array,4))
        {
            return FALSE;
        }
            
        /*Check data*/
	   data_index =0;
		 if ((*(U16 *)(phy_base_addr) != cur_prog_data_addr[data_index])
         || (*(U16 *)(phy_base_addr + 2) != cur_prog_data_addr[data_index+1]))
     {

			return FALSE;
     }
    }
    return TRUE;
}


/***************************************************
* Function: depm_read
* Description:   
* Parameters: *p_data_buffer phy_start_addr
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author: qq        Date:2018-05-30   Version:V1.0
****************************************************/
BOOL DEPM_Read( U16 logic_start_addr,U8 *p_data_buffer, U16 length)
{
    U16 data_index = 0;	
	U16 phy_start_addr = logic_start_addr + INEEPROM_START_ADDR;
    if (0 == p_data_buffer || 0 == length)
    {
        return FALSE;
    }
    else if (phy_start_addr < INEEPROM_START_ADDR || (phy_start_addr + length - 1) > INEEPROM_END_ADDR)
    {
        return FALSE;
    }
    else
    {
        for (data_index = 0; data_index < length; data_index++)
        {
            p_data_buffer[data_index] = *(U8 *)(phy_start_addr);
            phy_start_addr++;
            WDT_Feed();
    //#warning  You need service watchdog here
        }
        return TRUE;
    }
}



/*----------------- End of Module -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0            QQ      2018-05-30              Initial
*
*===========================================================================*/
