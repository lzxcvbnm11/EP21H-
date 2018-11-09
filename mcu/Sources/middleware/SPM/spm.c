/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : spm.c
* Description : Driver source file of spm.
* Author: qq
* Date: 2018-06-7
******************************************************************************/

/* Files for including */
#include "spm_info.inc"

static BOOL SPM_Status = FALSE; 

static U8 DEVICE_I2C_FaultReg_buf = 0;
static U8 DEVICE_I2C_StatusLoadDiagReg_buf = 0;
static U8 DEVICE_I2C_ControlReg_buf = 0; 

/*Fault Register(0x01)FUNCTION*/
static BOOL FUN_STATUS_NoProtectionFaults = 0;
static BOOL FUN_STATUS_LoadDiagFault = 0;
static BOOL FUN_STATUS_OCSD = 0;
static BOOL FUN_STATUS_PVDD_UV = 0;
static BOOL FUN_STATUS_PVDD_OV = 0;
static BOOL FUN_STATUS_DC_offset = 0;
static BOOL FUN_STATUS_OTSD = 0;

/*Status and Load Diagnostic Register (0x02)FUNCTION*/
static BOOL FUN_STATUS_NoSpeakerDiagFaults = 0;
static BOOL FUN_STATUS_OutputShortPVDD  = 0;
static BOOL FUN_STATUS_OutputShortGND  = 0;
static BOOL FUN_STATUS_OpenLoad  = 0;
static BOOL FUN_STATUS_ShortLoad  = 0;
static BOOL FUN_STATUS_InFaultCondition  = 0;
#if 0
static BOOL FUN_STATUS_PerforminaLoadDiagnostics  = 0;
static BOOL FUN_STATUS_InMuteMode  = 0;
static BOOL FUN_STATUS_InPlayMode  = 0;
#endif

/***************************************************
* Function:  SPM_Init   
* Description: get the SPM module initialized status
* Parameters: none
* Returns: 
* $Create & Verlog:$
* Author:qq  Date:2018-6-5   Version:V1.0
****************************************************/
void SPM_Init(void)
{
  DEVICE_I2C_FaultReg_buf = 0;   
  DEVICE_I2C_StatusLoadDiagReg_buf = 0;
  DEVICE_I2C_ControlReg_buf = 0; 
  /*Fault Register(0x01)FUNCTION*/
  FUN_STATUS_NoProtectionFaults = 0;
  FUN_STATUS_LoadDiagFault = 0;
  FUN_STATUS_OCSD = 0;
  FUN_STATUS_PVDD_UV = 0;
  FUN_STATUS_PVDD_OV = 0;
  FUN_STATUS_DC_offset = 0;
  FUN_STATUS_OTSD = 0;
  /*Status and Load Diagnostic Register (0x02)FUNCTION*/
  FUN_STATUS_NoSpeakerDiagFaults = 0;
  FUN_STATUS_OutputShortPVDD  = 0;
  FUN_STATUS_OutputShortGND  = 0;
  FUN_STATUS_OpenLoad  = 0;
  FUN_STATUS_ShortLoad  = 0;
  FUN_STATUS_InFaultCondition  = 0;
  #if 0
  FUN_STATUS_PerforminaLoadDiagnostics  = 0;
  FUN_STATUS_InMuteMode  = 0;
  FUN_STATUS_InPlayMode  = 0;
  #endif
  
  SPM_Status = DIIC_GetInitStatus();
}

/***************************************************
* Function:  SPM_GetModuleStatus
* Description: get the SPM module initialized status
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author: qq Date:2018-6-5   Version:V1.0
****************************************************/
BOOL SPM_GetInitStatus(void)
{
  return SPM_Status;
}

/***************************************************
* Function:  spm_FaultReg_Read
* Description: 
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author: qq Date:2018-6-5   Version:V1.0
****************************************************/
 U8 spm_FaultReg_Read() 
{
  U8 ret;
  BOOL diic_init = 0;
  diic_init = DIIC_GetInitStatus();
  if(diic_init != 0) 
  {
	 ret = DIIC_read(DEVICE_I2C_READ_ADDR, DEVICE_I2C_CONTROLREG_ADDR, &DEVICE_I2C_ControlReg_buf, DEVICE_I2C_DATALENG);
     ret = DIIC_read(DEVICE_I2C_READ_ADDR, DEVICE_I2C_FAULTREG_ADDR, &DEVICE_I2C_FaultReg_buf, DEVICE_I2C_DATALENG);
	 if((ret == RET_INVALID) || (DEVICE_I2C_ControlReg_buf != DEVICE_CONTROLREG_BUFVALUE))
	 {
	 	DEVICE_I2C_FaultReg_buf = 0xFF;/* iic通信出错,恢复到出错状态 */
	 }
	 if((DEVICE_I2C_FaultReg_buf & 0xFF) == BUFFER_COMPARISONVALUE)
      {
        FUN_STATUS_NoProtectionFaults = ACTIVE;
      }
      else 
      {
        FUN_STATUS_NoProtectionFaults = INACTIVE;
      }
      if((DEVICE_I2C_FaultReg_buf & 0x04) != BUFFER_COMPARISONVALUE)
      {
        FUN_STATUS_LoadDiagFault = ACTIVE;
      }
      else 
      {
        FUN_STATUS_LoadDiagFault = INACTIVE;
      }
      if((DEVICE_I2C_FaultReg_buf & 0x08) != BUFFER_COMPARISONVALUE)
      {
        FUN_STATUS_OCSD = ACTIVE;
      }
      else 
      {
        FUN_STATUS_OCSD = INACTIVE;
      }
      if((DEVICE_I2C_FaultReg_buf & 0x10) != BUFFER_COMPARISONVALUE)
      {
        FUN_STATUS_PVDD_UV = ACTIVE;
      }
      else
      {
        FUN_STATUS_PVDD_UV = INACTIVE;
      }
      if((DEVICE_I2C_FaultReg_buf & 0x20) != BUFFER_COMPARISONVALUE)
      {
        FUN_STATUS_PVDD_OV = ACTIVE;
      }
      else
      {
        FUN_STATUS_PVDD_OV = INACTIVE;
      }
      if((DEVICE_I2C_FaultReg_buf & 0x40) != BUFFER_COMPARISONVALUE)
      {
        FUN_STATUS_DC_offset = ACTIVE;
      }
      else
      {
        FUN_STATUS_DC_offset = INACTIVE;
      }
      if((DEVICE_I2C_FaultReg_buf & 0x80) != BUFFER_COMPARISONVALUE)
      {
        FUN_STATUS_OTSD = ACTIVE;
      }
      else
      {
        FUN_STATUS_OTSD = INACTIVE;
      }
      return TRUE;
  }
  else 
  {
    return FALSE;
  }
}

/***************************************************
* Function:  spm_StatusLoadDiagReg_Read
* Description: 
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author: qq  Date:2018-6-5   Version:V1.0
****************************************************/
 U8 spm_StatusLoadDiagReg_Read() 
{
  U8 ret;
  BOOL diic_init = 0;
  diic_init = DIIC_GetInitStatus();
  if(diic_init != 0) 
  {
  	 ret = DIIC_read(DEVICE_I2C_READ_ADDR, DEVICE_I2C_CONTROLREG_ADDR, &DEVICE_I2C_ControlReg_buf, DEVICE_I2C_DATALENG);
	 ret = DIIC_read(DEVICE_I2C_READ_ADDR, DEVICE_I2C_STATUSLOADDIOGREG_ADDR, &DEVICE_I2C_StatusLoadDiagReg_buf, DEVICE_I2C_DATALENG);
	 if((ret == RET_INVALID) || (DEVICE_I2C_ControlReg_buf != DEVICE_CONTROLREG_BUFVALUE))
	 {
	 	DEVICE_I2C_StatusLoadDiagReg_buf = 0xFF;/* iic通信出错,恢复到出错状态 */
	 }
		if((DEVICE_I2C_StatusLoadDiagReg_buf & 0xFF) == BUFFER_COMPARISONVALUE)
	    {
	      FUN_STATUS_NoSpeakerDiagFaults = ACTIVE;
	    }
	    else
	    {
	      FUN_STATUS_NoSpeakerDiagFaults = INACTIVE;
	    }
		
	    if((DEVICE_I2C_StatusLoadDiagReg_buf & 0x01) != BUFFER_COMPARISONVALUE)
	    {
	      FUN_STATUS_OutputShortPVDD = ACTIVE;
	    }
	    else
	    {
	      FUN_STATUS_OutputShortPVDD = INACTIVE;
	    }
		
	    if((DEVICE_I2C_StatusLoadDiagReg_buf & 0x02) != BUFFER_COMPARISONVALUE)
	    {
	      FUN_STATUS_OutputShortGND = ACTIVE;
	    }
	    else
	    {
	      FUN_STATUS_OutputShortGND = INACTIVE;
	    }
		
	    if((DEVICE_I2C_StatusLoadDiagReg_buf & 0x04) != BUFFER_COMPARISONVALUE)
	    {
	      FUN_STATUS_OpenLoad = ACTIVE;
	    }
	    else
	    {
	      FUN_STATUS_OpenLoad = INACTIVE;
	    }
		
	    if((DEVICE_I2C_StatusLoadDiagReg_buf & 0x08) != BUFFER_COMPARISONVALUE)
	    {
	      FUN_STATUS_ShortLoad = ACTIVE;
	    }
	    else
	    {
	      FUN_STATUS_ShortLoad = INACTIVE;
	    }
		
	    if((DEVICE_I2C_StatusLoadDiagReg_buf & 0x10) != BUFFER_COMPARISONVALUE)
	    {
	      FUN_STATUS_InFaultCondition = ACTIVE;
	    }
	    else
	    {
	      FUN_STATUS_InFaultCondition = INACTIVE;
	    }

		#if 0
	    if((DEVICE_I2C_StatusLoadDiagReg_buf & 0x20) != BUFFER_COMPARISONVALUE)
	    {
	      FUN_STATUS_PerforminaLoadDiagnostics = ACTIVE;
	    }
	    else
	    {
	      FUN_STATUS_PerforminaLoadDiagnostics = INACTIVE;
	    }
		
	    if((DEVICE_I2C_StatusLoadDiagReg_buf & 0x40) != BUFFER_COMPARISONVALUE)
	    {
	      FUN_STATUS_InMuteMode = ACTIVE;
	    }
	    else 
	    {
	      FUN_STATUS_InMuteMode = INACTIVE;
	    }
		
	    if((DEVICE_I2C_StatusLoadDiagReg_buf & 0x80) != BUFFER_COMPARISONVALUE)
	    {
	      FUN_STATUS_InPlayMode = ACTIVE;
	    }
	    else 
	    {
	      FUN_STATUS_InPlayMode = INACTIVE;
	    }
		#endif
		
    	return TRUE;
  }
  else
  {  
   		return FALSE;
  }
}


/***************************************************
* Function:  SPM_GetSpkWorkStatus
* Description:Get SPK work status
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author: qq Date:2018-6-5   Version:V1.0
****************************************************/
BOOL SPM_GetSpkWorkStatus(void)
{
  U8 res = RET_FAIL;
  U8 fault_input = 0;
  
  res = DGPIO_GetIOSts(INDEX_DGPIO_PIN16, &fault_input); 
  if(res == RET_OK)
  {  
     if(fault_input == 0)
     {  
        res =  spm_FaultReg_Read();
        if(res == TRUE)
        {
             if(FUN_STATUS_NoProtectionFaults != INACTIVE)
             {
                return TRUE; /* normal work */
             }
             else
             {
                ;
             }
             if(FUN_STATUS_LoadDiagFault
             || FUN_STATUS_OCSD
             || FUN_STATUS_PVDD_UV
             || FUN_STATUS_PVDD_OV
             || FUN_STATUS_DC_offset
             || FUN_STATUS_OTSD)
             {
                return FALSE; /* fault detect  */
             }
       }
       else
       {
         ;
       }
     }
     else
     {
        return TRUE;
     }
  }
  else 
  {
    ;
  }
  return TRUE; /* normal work */
}

/***************************************************
* Function:  SPM_GetAmpWorkStatus
* Description:Regiter write
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author: qq Date:2018-6-5   Version:V1.0
****************************************************/
BOOL SPM_GetAmpWorkStatus(void)
{

  U8 res = RET_FAIL;
  U8 fault_input = 0;
  
  res = DGPIO_GetIOSts(INDEX_DGPIO_PIN16, &fault_input); 
  if(res == RET_OK)
  {    	
	 res =	spm_StatusLoadDiagReg_Read();
     if(fault_input == 0)
     {  
        if(res == TRUE)
        {
             if(FUN_STATUS_NoSpeakerDiagFaults != 0)
             {
                return TRUE;
             }
             else
             {
                ;
             }
             if(FUN_STATUS_OutputShortPVDD
             || FUN_STATUS_OutputShortGND
             || FUN_STATUS_OpenLoad
             || FUN_STATUS_ShortLoad
             || FUN_STATUS_InFaultCondition
             /*|| FUN_STATUS_PerforminaLoadDiagnostics
             || FUN_STATUS_InMuteMode
             || FUN_STATUS_InPlayMode*/)
             {
                return FALSE;  /* fault detect */
             }
       }
       else
       {
       		if(FUN_STATUS_OpenLoad) 
			{
				return FALSE; /* fault detect */
			}
       }
     }
     else
     {
        return TRUE; /* normal work */
     }
  }
  else 
  {
    ;
  }
  return TRUE; /* normal work */
}


/***************************************************
* Function:  spm_ControlReg_Write
* Description:Regiter write
* Parameters: Index_Freq  Index_OUT  Index_GAIN
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author: qq Date:2018-6-5   Version:V1.0
****************************************************/
U8 spm_ControlReg_Write(U8 Index_Freq,U8 Index_OUT,U8 Index_GAIN)
{
  U8 reg_data_write = 0x00;
  U8 Freq_write = 0x00;
  U8 OUT_write = 0x00;
  U8 GAIN_write = 0x00;
  
   if(EVT_SPM_SWITCHFREQ400KHZ == ControlRegList[Index_Freq].freq)
   {
     Freq_write = 0x00;
   }

    if(EVT_SPM_SWITCHFREQ500KHZ == ControlRegList[Index_Freq].freq)
      Freq_write = 0x01;
    if(EVT_SPM_SPEAKERGUARDOUT14V == ControlRegList[Index_OUT].out)
      OUT_write = 0x30;
    if(EVT_SPM_SPEAKERGUARDOUT11V8 == ControlRegList[Index_OUT].out)
      OUT_write = 0x28;
    if(EVT_SPM_SPEAKERGUARDOUT9V8 == ControlRegList[Index_OUT].out)
      OUT_write = 0x20;
    if(EVT_SPM_SPEAKERGUARDOUT8V4 == ControlRegList[Index_OUT].out)
      OUT_write = 0x18;
    if(EVT_SPM_SPEAKERGUARDOUT7V == ControlRegList[Index_OUT].out)
      OUT_write = 0x10;
    if(EVT_SPM_SPEAKERGUARDOUT5V9 == ControlRegList[Index_OUT].out)
      OUT_write = 0x08;
    if(EVT_SPM_SPEAKERGUARDOUT5V == ControlRegList[Index_OUT].out)
      OUT_write = 0x00;
    if(EVT_SPM_GAIN20DB == ControlRegList[Index_GAIN].gain)
      GAIN_write = 0x00;
    if(EVT_SPM_GAIN26DB == ControlRegList[Index_GAIN].gain)
      GAIN_write = 0x40;
    if(EVT_SPM_GAIN32DB == ControlRegList[Index_GAIN].gain)
      GAIN_write = 0x80;
    if(EVT_SPM_GAIN36DB == ControlRegList[Index_GAIN].gain)
      GAIN_write = 0xC0;
    reg_data_write = (Freq_write & OUT_write & GAIN_write);
    DIIC_write(DEVICE_I2C_WRITE_ADDR ,DEVICE_I2C_CONTROLREG_ADDR , & reg_data_write, DEVICE_I2C_DATALENG);
    return TRUE;
}

/***************************************************
* Function:  SetVolume
* Description: Set volume value
* Parameters: Index
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author: qq  Date:2018-6-5   Version:V1.0
****************************************************/
 U8 SPM_SetVolume(U8 Index)
 {
   U8 res; 
   switch(Index)
   {
     case INDEX_SPM_VOLUME1 :
     {
       res = spm_ControlReg_Write(INDEX_SPM_SWITCHFREQ500KHZ,INDEX_SPM_SPEAKERGUARDOUT14V, INDEX_SPM_GAIN26DB);
       break;
     }
     case INDEX_SPM_VOLUME2 :
     {
       res = spm_ControlReg_Write(INDEX_SPM_SWITCHFREQ500KHZ,INDEX_SPM_SPEAKERGUARDOUT14V, INDEX_SPM_GAIN20DB);
       break;
     }
     case INDEX_SPM_VOLUME3 :
     {
       res = spm_ControlReg_Write(INDEX_SPM_SWITCHFREQ500KHZ,INDEX_SPM_SPEAKERGUARDOUT14V, INDEX_SPM_GAIN32DB);
       break;
     }
     case INDEX_SPM_VOLUME4 :
     {
       res = spm_ControlReg_Write(INDEX_SPM_SWITCHFREQ500KHZ,INDEX_SPM_SPEAKERGUARDOUT14V, INDEX_SPM_GAIN36DB);
       break;
     }
     default:return FALSE;
   }
   return TRUE;
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
* V1.0            QQ      2018-06-7      Initial
*
*===========================================================================*/
