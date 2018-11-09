/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : spd.c
* Description : App source file of spd.
* Author: qq
* Date: 2018-06-12
******************************************************************************/

/* Files for including */
#include "spd_info.inc"

/***************************************************
* Function:  SPD_Init   
* Description: get the SPD module initialized status
* Parameters: none
* Returns: 
* $Create & Verlog:$
* Author:qq  Date:2018-6-12   Version:V1.0
****************************************************/
void SPD_Init()
{
   SPD_InitSts = FALSE;
   SPD_SpkWrkSts = WORKSTS_NORMAL;
   SPD_AmpWrkSts = WORKSTS_NORMAL;
   SPD_SPKSystemSts = STATUS_SPD_NORMAL;
   SPD_SpkFltSts = FALSE;
   SPD_AmpFltSts = FALSE;
   SPD_OVFltSts = FALSE;
   SPD_UVFltSts = FALSE;
   SPM_SetVolume( INDEX_SPM_VOLUME1);
   IOM_SetOutPutLevel(INDEX_IOM_SHDN, 1);
   SPD_InitSts = SPM_GetInitStatus();
}

/***************************************************
* Function:  SPD_GetInitStatus   
* Description: get the SPD module initialized status
* Parameters: none
* Returns: 
* $Create & Verlog:$
* Author:qq  Date:2018-6-5   Version:V1.0
****************************************************/
BOOL SPD_GetInitStatus()
{
  return SPD_InitSts;
}

/***************************************************
* Function: spd_SpkProcess_5ms
* Description: the process of the SPK FLT Detect  
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:liuyingying Date:2018-05-23     Version:V1.0
*$log: add new functions
****************************************************/
void spd_SpkProcess(void)
{
    U8 res = RET_OK;
    static SPD_WORKSTS_ENUM spkSts = WORKSTS_NORMAL;
    static U8 spkcnt = 0;
    
		SPD_SpkWrkSts = SPM_GetSpkWorkStatus();
		if(spkSts == SPD_SpkWrkSts)
		{		
					
			if(spkcnt > SPD_SPKFLT_CNT_MAX)
			{
				if(SPD_SpkWrkSts != WORKSTS_NORMAL)
				{
					SPD_SpkFltSts = 1; /* fault error status*/
				}
				else
				{
					SPD_SpkFltSts = 0; /* normal  status*/
				}
			}
			else
			{
				spkcnt ++;
			}
		
		}
		else
		{
			spkcnt = 0;
		}
		spkSts = SPD_SpkWrkSts;
	}

/***************************************************
* Function: spd_AmpProcess_5ms
* Description: the process of the AMP FLT Detect  
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:liuyingying Date:2018-05-23     Version:V1.0
*$log: add new functions
****************************************************/

void spd_AmpProcess(void)
{
    U8 res = RET_OK;
    static SPD_WORKSTS_ENUM ampSts= WORKSTS_NORMAL;	
    static U8 ampcnt = 0;
   
		SPD_AmpWrkSts = SPM_GetAmpWorkStatus();
		if(ampSts == SPD_AmpWrkSts)
		{		
				
				if(ampcnt > SPD_AMPFLT_CNT_MAX)
				{
					if(SPD_AmpWrkSts != WORKSTS_NORMAL)
					{
						SPD_AmpFltSts = 1;
					}
					else
					{
						SPD_AmpFltSts = 0;
					}
				}
				else
				{
					ampcnt ++;
				}
				
			}
		else
		{
			ampcnt = 0;
		}		
		ampSts = SPD_AmpWrkSts;//SPD_SpkWrkSts;
}
	
/***************************************************
* Function: spd_BatOVProcess_100ms
* Description: the process of the  bat OV Detect  
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:qq    Date:2018-06-14     Version:V1.0
*$log: add new functions
****************************************************/
void spd_BatOVAndUVProcess(void)
{
    U8 res = RET_OK;
    U16 bat_value = 0;
    U8 CurOVSts = FALSE;
	U8 CurUVSts	= FALSE;
    static U8 LastOVSts = FALSE;
	static U8 LastUVSts = FALSE;
    static U8 OVCnt = 0;
	static U8 UVCnt = 0;			
		res = BAT_GetBatValue(&bat_value);
		
		if(bat_value >= SPD_FLT_HIGHVOL) 
		{
		  CurOVSts = TRUE;
		}
		else if(bat_value <= SPD_FLT_LOWVOL) 
		{
		  CurUVSts = TRUE;
		}
		else
		{
		  CurUVSts = FALSE;
		  CurOVSts = FALSE;
		}
		/*
			battary over volt detect 
		*/	
		if(LastOVSts == CurOVSts)
		{		
					
				if(OVCnt > SPD_BatOVorUV_CNT_MAX)
				{
					if(CurOVSts == TRUE)
					{
						SPD_OVFltSts = TRUE;
					}
					else
					{
						SPD_OVFltSts = FALSE;
					}
				}
				else
				{
					OVCnt ++;
				}
					
		}
		else
		{
			OVCnt = 0;
		}		
		LastOVSts = CurOVSts;
		
		/*
			battary under volt detect 
		
		*/		
		if(LastUVSts == CurUVSts)
		{		
					
			if(UVCnt > SPD_BatOVorUV_CNT_MAX)
			{
				if(CurUVSts == TRUE)
				{
					SPD_UVFltSts = TRUE;
				}
				else
				{
					SPD_UVFltSts = FALSE;	
				}
			}
			else
			{
				UVCnt ++;
			}
					
		}
		else
		{
			UVCnt = 0;
		}		
		LastUVSts = CurUVSts;
}

/***************************************************
* Function: SPD_Process_5ms
* Description: the process of the SPD module 
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:liuyingying Date:2018-06-27     Version:V1.0
*           qq            2018-06-13
*$log: add new functions
****************************************************/
void SPD_SPKSystemDiag_20ms(void)
{
    if (TRUE == SPD_InitSts)
   	{
    	spd_SpkProcess();
		spd_AmpProcess();
		spd_BatOVAndUVProcess();
   	}
	else
	{
	 ;
	}

}

/***************************************************
* Function:  SPD_GetSPKSystensts   
* Description: the process of the SPD module
* Parameters: none
* Returns:    
*           
*           
* $Create & Verlog:$
* Author:qq  Date:2018-6-13   Version:V1.0
****************************************************/
U8 SPD_GetSPKAndAMPSystensts(void)
{
    
    	if((SPD_SpkFltSts == FALSE) && (SPD_AmpFltSts == FALSE))
	  	{  
	  	  	return STATUS_SPD_NORMAL;
	  	}
		else if ((SPD_SpkFltSts == TRUE) && (SPD_AmpFltSts == TRUE))
		{			
			return STATUS_SPD_BOTHERROR;
		}
	  	else if(SPD_AmpFltSts == TRUE)
	  	{  
	  	  	return STATUS_SPD_AMPERROR;
	  	}
	  	else
	  	{  
	  	  	return STATUS_SPD_SPKERROR;
	  	}

}

/***************************************************
* Function:  SPD_PedtrnAlrtSts   
* Description: 
* Parameters: none
* Returns: 
* $Create & Verlog:$
* Author:qq  Date:2018-6-14   Version:V1.0
****************************************************/
U8 SPD_PACMFltSts(void)
{
  if((SPD_AmpFltSts == TRUE) || (SPD_OVFltSts == TRUE) || (SPD_UVFltSts == TRUE))
  {
     return TRUE;
  }
  else
  {
     return FALSE;
  }
  
}

/***************************************************
* Function:  SPD_PedtrnAlrtSpkFltHSC4Sts   
* Description: 
* Parameters: none
* Returns: 
* $Create & Verlog:$
* Author:qq  Date:2018-6-14   Version:V1.0
****************************************************/
U8 SPD_PedtrnAlrtSpkFltSts(void)
{
	PWRMcuWorkMode_ENUM pwrWorkState;
	if(RET_OK == PWR_GetPwrMode(&pwrWorkState)) 
	{
   		if((SPD_AmpFltSts == TRUE) && (pwrWorkState == PWR_MCU_WORK_MODE_NORMAL))
   		{
   			if(SPD_SpkFltSts == 1)
			{
				return TRUE;
			}
			else
			{
		  		return FALSE;
			}
   		}
	}
	return FALSE;	
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
* V1.0            QQ           2018-06-12              Initial
*
*===========================================================================*/
