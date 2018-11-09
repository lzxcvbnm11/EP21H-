/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : com.c
* Description :the private datas of the com module.
* Author: Jason.Sun
* Date: 2018-06-05
******************************************************************************/
/* Files for including */
#include "com_info.inc"

//extern const v_nwm_instance_handle nwm_instances[1];
//extern v_nwm_instance nwm_slave_instance;
//static COMWakeUpSource_ENUM com_NetWake = SOURCE_COM_NONE;
static BOOL com_InitSts = FALSE;
static U8 com_GCounter = 0;
//static U8 isNetWorkStoped = FALSE;
//static BOOL com_SSBPress = FALSE;
//static SSBData_ST com_ssbKey;
static v_nwm_state current_nwm_state;
//static U8 netWakeUp = FALSE;
//static U8 L_PDCSysSts = 0;
//static U8 L_RLObsRng = 0;
//static U8 L_RRObsRng = 0;
//static U8 L_RrMidLObsRng = 0;
//static U8 L_RrMidRObsRng = 0;
//static U8 L_PDCConfigSts = 0;
//static U32 com_DisPlayspeed = 0;
//static U8 com_TrShftLvrPos = 0;
//static U8 com_TrShftLvrPosV = 0;
//static U8 com_MstrSysPwrMd = 0;
static U8 com_NetWorkModeSleepFlg = FALSE;
static U8 com_NetWorkSilentFlag  = FALSE;
/***************************************************
* Function: COM_Init
* Description: the initialized of the COM module
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-06-05   Version:V1.0
****************************************************/


void COM_Init(void)
{
	U8 res = INVALID;


    com_NetWorkModeSleepFlg = FALSE;

	#if COM_CAN_NWM_ENABLE
	/* At start-up the application should initialise the NWM module. */
    if (v_nwm_init(v_config_handle, nwm_instances, NUMBER_OF_NWM_INSTANCES ))
    {
        /* NWM initialisation failed. We have entered the state Isolated. */
        /* Error handling or limp home according to "Node Management". */
        for(;;)
        {;}
    }
	#else
	//R_TICK_WaitMS(0,50);
    if (v_sys_init(v_config_handle))
    {
        TEST_FAILED();
    }
	if (v_ctl_init(PACM_HSC4_handle))
    {
        TEST_FAILED();
    }

	                                    /* Connect the controller to the net-work.*/
    v_ctl_con(PACM_HSC4_handle);
                                    /* Set frame mode M1 so that the frames */
                                    /* we are interested in are valid.      */
    v_fmd_set(PACM_HSC4_handle, FM_Normal_HS_handle);
                                    /* We need to enable interrupts for the */
                                    /* controller (tx/rx by interrupt).     */
    //ENABLE_INTS();
                                    /* Enter the never-ending loop which    */
                                    /* contains the main functionality.     */
	#endif
	com_InitSts = TRUE;
}

/***************************************************
* Function:  COM_GetInitSts
* Description: get the IOM module initialized status
* Parameters: none
* Returns: TRUE or FALSE
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-06-05
****************************************************/
BOOL COM_GetInitSts(void)
{
    return com_InitSts;
}
/***************************************************
* Function: com_NormalProcess_5ms
* Description: the process of the com module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-06-05   Version:V1.0
****************************************************/
static void com_volcano_processing(void)
{
#if 0//ENABLE_NWM
    v_nwm_state current_nwm_state;
#endif

    /*CAN RX*/
    v_input(v_config_handle);


    /*CAN TX*/
    v_output(v_config_handle);

    com_GCounter = 1-com_GCounter;
    if(0 == com_GCounter)
    {
        com_nwm_process_10ms();
    }

}

/***************************************************
* Function: COM_Process_5ms
* Description: the process of the COM module
* Parameters: none
* Returns: none
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-06-05 Version:V1.0
****************************************************/
void COM_Process_5ms(void)
{
	
	com_volcano_processing();
	/*
    L_PDCSysSts = v_rd_8(PDCSysSts_L_handle);
    L_RLObsRng = v_rd_8(RLObsRng_L_handle);
    L_RRObsRng = v_rd_8(RRObsRng_L_handle);
    L_RrMidLObsRng = v_rd_8(RrMidLObsRng_L_handle);
    L_RrMidRObsRng = v_rd_8(RrMidRObsRng_L_handle);
    L_PDCConfigSts = v_rd_8(PDCCofignSts_L_handle);

	com_TrShftLvrPos =v_rd_8(TrShftLvrPos_handle);
	com_TrShftLvrPosV =v_rd_8(TrShftLvrPosV_handle);
	com_MstrSysPwrMd = v_rd_8(BCMPwrMdHwdSta_handle);
    
	ST_GetDisplaySpeed(&com_DisPlayspeed); */
}

void com_nwm_process_10ms(void)
{
	PWRMcuWorkMode_ENUM pwr_McuWorkMode;
	BATVoltageSts_ENUM bat_voltagests;
	PWR_GetPwrMode(&pwr_McuWorkMode);
	bat_voltagests = BAT_GetBatVoltageSts(); 
	if(bat_voltagests > STATUS_BAT_CAN)
	{
		v_fmd_set(PACM_HSC4_handle, FM_Silent_HS_handle);
		com_NetWorkSilentFlag = TRUE;;
	}
	else
	{
		if(((pwr_McuWorkMode == PWR_MCU_WORK_MODE_DIAG) || (pwr_McuWorkMode == PWR_MCU_WORK_MODE_SILENT)) && (com_NetWorkSilentFlag == FALSE))
		{
		
			v_fmd_set(PACM_HSC4_handle, FM_Silent_HS_handle);
			com_NetWorkSilentFlag = TRUE;

		}
		else if(((pwr_McuWorkMode != PWR_MCU_WORK_MODE_DIAG) && (pwr_McuWorkMode != PWR_MCU_WORK_MODE_SILENT)) && (com_NetWorkSilentFlag == TRUE))
		{	
			v_fmd_set(PACM_HSC4_handle, FM_Normal_HS_handle);		
			com_NetWorkSilentFlag = FALSE;
		}
	}
	v_nwm_slave_processing( &nwm_slave_instance );
    com_nwm_process();
}

#if 0
/***************************************************
* Function: COM_GetNetStatus
* Description: the process of the COM module
* Parameters: status output: the current Network status
* Returns:
	RET_FAIL :module initial fail
	RET_INVALID: input parameter error
	RET_OK: Get Data success
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-06-05   Version:V1.0
****************************************************/
U8 COM_GetNetStatus(COMNetStatus_ENUM *status)
{
	U8 res = RET_FAIL;
	if(FALSE == com_InitSts)
	{
		res = RET_FAIL;
	}
	else if(NULL_PTR == status)
	{
		res = RET_INVALID;
	}
	else
	{
		if(SOURCE_COM_NONE != com_NetWake)
		{
			*status = STATUS_COM_NETWAKE;
		}
		else
		{
			*status = STATUS_COM_NETSLEEP;
		}
		res = RET_OK;
	}
	return res;
}
#endif
/******************************************************
* Function: COM_GetNetWorkSleepSts
* Description: Get network sleep status
* Parameters:  none
* Returns: none
* $Create & Verlog:$
* Author:Yingying.Liu  Date:2017-10-26   Version:V2.0
*******************************************************/
U8 COM_GetNetWorkSleepSts(void)
{	
	return(com_NetWorkModeSleepFlg);
}

v_nwm_state COM_GetNwmState(void)
{

	return (current_nwm_state);
}

static void com_nwm_process( void)
{
		 static U16 DelayCnt = 0;
		 int test = 0;
         /* Read the current NWM state and write it to the signal Currentstate */
        current_nwm_state = v_nwm_get_state(&nwm_slave_instance);
		if(V_NWM_NETWORK_SLEEP == current_nwm_state)
		{
			
			if(FALSE == com_NetWorkModeSleepFlg)
			{
				if(DelayCnt >= (500))
				{
					com_NetWorkModeSleepFlg = TRUE;
					//v_nwm_stop(&nwm_slave_instance); /*jason add*/
					DelayCnt = 0;
				}
				else
				{
				  DelayCnt ++;	
				}
			}
			else
			{
				DelayCnt = 0;
			}
		}
		else
		{
			com_NetWorkModeSleepFlg= FALSE;
			DelayCnt = 0;
			//com_NetMuteFlag = 0;
			//DelayMuteCnt = 0;
		}

        switch (current_nwm_state)  {

            case V_NWM_STARTUP:
                /* The node is starting up */
				//v_nwm_get_state( &nwm_slave_instance );
				break;

            case V_NWM_NORMAL:
                /* We are up and communicating on the network. */
                /* It's possible to run all functions that require */
                /* communication over the network. */

                /* In this example we need the network (receive or transmit */
                /* signals) as long as NetworkMode does not equal 0x03. */
                if (v_rd_8(network_mode_handle) != 0x01)
                {
                    v_nwm_net_com_req(&nwm_slave_instance);
                }
		        		else
		        		{
			        	}
				
                /* Read the busoff counter and write it to the signal BusOffCounter */
               // busoff_cntr = v_nwm_get_busoff_counter( &nwm_slave_instance );
                ////v_wr_8( busoff_counter_handle, busoff_cntr );
                break;

            case V_NWM_WAIT_FOR_NETWORK_SLEEP:
				 if (v_rd_8(network_mode_handle) == 0x01)
				 {
					 test = 1;
				 }
                /* We are on the way to Network Sleep. Signals should */
                /* not be written any more. We shall continue to read signals. */	
                break;

            case V_NWM_NETWORK_SLEEP:
				 if (v_rd_8(network_mode_handle) == 0x01)
				 {
					 test = 1;
				 }
                /* The node is silent and the CAN-controllers are in */
                /* sleep mode. */		
                break;

            case V_NWM_WAKEUP_NETWORK:
				
				if (v_rd_8(network_mode_handle) == 0x01)
				{
									 test = 1;
				}
                /* We are waking up the network */	
                break;
            case V_NWM_WAKEUP_PENDING:
                /* We have been woken up by traffic on the network */	
				if (v_rd_8(network_mode_handle) == 0x01)
				{
									 test = 1;
				}
                break;
            case V_NWM_EXPULSION:
				if (v_rd_8(network_mode_handle) == 0x01)
				{
									 test = 1;
				}
                /* Incorrect signal configuration id received. 错误的配置ID 信号*/			
                break;
            case V_NWM_STOPPED:
				if (v_rd_8(network_mode_handle) == 0x01)
				{
									 test = 1;
				}
                /* We are disconnected from the network. */
                break;
            case V_NWM_BUSOFF:
				if (v_rd_8(network_mode_handle) == 0x01)
				{
									 test = 1;
				}
                /* One or more busoff errors detected. */		
                break;
            case V_NWM_BUSOFF_WAIT:
				if (v_rd_8(network_mode_handle) == 0x01)
				{
									 test = 1;
				}
                /* The number of busoff errors has reached BUSOFF_MAX. */
                break;
            case V_NWM_ISOLATED:
				if (v_rd_8(network_mode_handle) == 0x01)
				{
									 test = 1;
				}
                /* Not possible to get here. The transition to state Isolated is */
                /* made in function v_nwm_init() if there is a initialisation error */
                break;

            default:
                break;
        }
}

void COM_GetSignalValue_8(U16 Index, PU8 pRes)
{
	//U8 Value8;
    //S8 sValue;
	
	if(NULL != pRes)
	{
		switch(Index)
		{
		case  INDEX_COM_RS_EPTAccelActuPos_8bit:
			*pRes = v_rd_8(EPTAccelActuPos_handle);
		break;
		case  INDEX_COM_RS_EnSpdSts_2bit:
			*pRes = v_rd_8(EnSpdSts_handle);
		break;
		case  INDEX_COM_RS_PedtrnAlrtVolSwReq_4bit :
			*pRes = v_rd_8(PedtrnAlrtVolSwReq_handle);
		break;
		case  INDEX_COM_RS_PedtrnAlrtSndSltReq_2bit:
			*pRes = v_rd_8(PedtrnAlrtSndSltReq_handle);
		break;
		
		case  INDEX_COM_RS_SysPwrMd_2bit:
			*pRes = v_rd_8(SysPwrMd_handle);
		break;
		case  INDEX_COM_RS_SysBPM_2bit:
			*pRes = v_rd_8(SysBPM_handle);
		break;
		case  INDEX_COM_RS_TrShftLvrPos_4bit:
			*pRes = v_rd_8(TrShftLvrPos_handle);
		break;
		
		case  INDEX_COM_RS_EPBSts_2bit:
			*pRes = v_rd_8(EPBSts_handle);
		break;
		case  INDEX_COM_RS_PedtrnAlrtInhSwReq_2bit:
			*pRes = v_rd_8(PedtrnAlrtInhSwReq_handle);
		break;
		//case  INDEX_COM_RS_VehDrvngMd_3bit:
			//*pRes = 0;//v_rd_8();
		//break;
		case  INDEX_COM_RS_PedtrnAdoWrnng_4bit:
			*pRes = v_rd_8(PedtrnAdoWrnng_handle);
		break;
		case INDEX_COM_RS_CalendarDay_5bit:
		  *pRes = v_rd_8(CalendarDay_handle);
	  	break;
	  	case INDEX_COM_RS_CalendarMonth_4bit:
		  *pRes = v_rd_8(CalendarMonth_handle);
	  	break;
	  	case INDEX_COM_RS_CalendarYear_8bit:
		  *pRes = v_rd_8(CalendarYear_handle);
	  	break;
		case INDEX_COM_RS_HourOfDay_5bit:
		  *pRes = v_rd_8(HourOfDay_handle);
	  	break;
	 	case INDEX_COM_RS_MinuteOfHour_6bit:
		  *pRes = v_rd_8(MinuteOfHour_handle);
	    break;
	  	case INDEX_COM_RS_network_mode_8bit:
		  *pRes = v_rd_8(network_mode_handle);
	  	break;
		case INDEX_COM_RS_SecsOfMinute_6bit:
		  *pRes = v_rd_8(SecsOfMinute_handle);
	  	break;
      default:
        break;
		    }
	    }
    else
    {
    }
}


void COM_GetSignalValue_BOOL(U16 Index, PU8 pRes)
{

	if(NULL != pRes)
	{
		switch(Index)
		{
              case  INDEX_COM_RS_EPTAccelActuPosV_1bit:   
			   *pRes = v_rd_bool(EPTAccelActuPosV_handle);
			    break;
			  case  INDEX_COM_RS_EPTStCmdOn_1bit:			  	
				*pRes = v_rd_bool(EPTStCmdOn_handle);
			  	break;
              case  INDEX_COM_RS_PedtrnAlrtVolSwReqV_1bit:
				*pRes = v_rd_bool(PedtrnAlrtVolSwReqV_handle);
				break;
              case  INDEX_COM_RS_PedtrnAlrtSndSltReqV_1bit:
				*pRes = v_rd_bool(PedtrnAlrtSndSltReqV_handle);
				break;
			  case  INDEX_COM_RS_SysBPMEnbd_1bit:
				*pRes = v_rd_bool(SysBPMEnbd_handle);
				break;
			  case  INDEX_COM_RS_EPTRdy_1bit:
				*pRes = v_rd_8(EPTRdy_handle);
				break;
			  case  INDEX_COM_RS_TrShftLvrPosV_1bit:
				*pRes = v_rd_bool(TrShftLvrPosV_handle);
				break;
			  case  INDEX_COM_RS_VehSpdAvgDrvnV_1bit:
				*pRes = v_rd_bool(VehSpdAvgDrvnV_handle);
				break;
			  case  INDEX_COM_RS_EPBAvlbly_1bit:			  	
				*pRes = v_rd_bool(EPBAvlbly_handle);
			  	break;
			  case  INDEX_COM_RS_RstrFctryDeftsReq_1bit:
				*pRes = v_rd_bool(RstrFctryDeftsReq_handle);
				break;
			  case  INDEX_COM_RS_LDircnIO_1bit:
				*pRes = v_rd_bool(LDircnIO_handle);
				break;
			  case  INDEX_COM_RS_RDircnIO_1bit:
				*pRes = v_rd_bool(RDircnIO_handle);
				break;
			  case INDEX_COM_RS_BCMAvlbly_1bit:			  	
				*pRes = v_rd_bool(BCMAvlbly_handle);
			  	break;
			  case INDEX_COM_RS_ECMAvlbly_1bit:			  	
				*pRes = v_rd_bool(ECMAvlbly_handle);
			  	break;
			  case INDEX_COM_RS_HCUAvlbly_1bit:			  	
				*pRes = v_rd_bool(HCUAvlbly_handle);
			  	break;
			  case INDEX_COM_RS_PwrMdMstrAccryA_1bit:			  	
				*pRes = v_rd_bool(PwrMdMstrAccryA_handle);
			  	break;
			  case INDEX_COM_RS_PwrMdMstrRunCrkA_1bit:			  	
				*pRes = v_rd_bool(PwrMdMstrRunCrkA_handle);
			  	break;
			  case INDEX_COM_RS_SCSAvlbly_1bit:
			  	*pRes = v_rd_bool(SCSAvlbly_handle);
			  	break;
			  case INDEX_COM_RS_TCAvlbly_1bit:
			  	*pRes = v_rd_bool(TCAvlbly_handle);
			  	break;
			  case INDEX_COM_RS_TMSpdV_1bit:
			  	*pRes = v_rd_bool(TMSpdV_handle);			  	
			  	break;
			  case INDEX_COM_RS_VehOdoV_1bit:
			  	*pRes = v_rd_bool(VehOdoV_handle);			  	
			  	break;
	      	  default:
	            *pRes = FALSE;
	      		break;
		    }
	    }
        else
        {
        }
}

void COM_GetSignalValue_16(U16 Index, PU16 pRes)
{
    U16 Value16;
    S16 sValue;
    float fValue = 0;
	if(NULL != pRes)
	{
		switch(Index)
		{
		case  INDEX_COM_RS_EnSpd_16bit:
			Value16 = v_rd_16(EnSpd_handle);
			*pRes = Value16;
			break;
		case  INDEX_COM_RS_VehSpdAvgDrvn_15bit:
			Value16 = v_rd_16(VehSpdAvgDrvn_handle);
			*pRes = Value16;
			break;
		case  INDEX_COM_RS_signal_config_id_16bit:
			Value16 = v_rd_16(signal_config_id_handle);
			*pRes = Value16;
			break;
		case  INDEX_COM_RS_TMSpd_16bit:
			Value16 = v_rd_16(TMSpd_handle);
			*pRes = Value16;
			break;
          default:
            break;
		 }
	 }
     else
     {
     }
}

void COM_GetSignalValue_32(U16 Index, PU32 pRes)
{
    U32 Value32;
    S32 sValue;
    float fValue = 0;
	if(NULL != pRes)
	{
		switch(Index)
		{
			case INDEX_COM_RS_VehOdo_24bit:
				Value32 = v_rd_32(VehOdo_handle);				
				*pRes = Value32;
				break;
			default:
				break;
		}
	}
	else
	{
	}
}
/*qq add*/


void COM_SetSignalValue_8(U16 Index, U8 val)
{
  switch(Index) 
  {
    case INDEX_COM_SEND_PedtrnAlrtVolSwSts_4bit:
      v_wr_8( PedtrnAlrtVolSwSts_handle, val);
     	break;
    case INDEX_COM_SEND_PedtrnAlrtSndSltSts_2bit:
      v_wr_8( PedtrnAlrtSndSltSts_handle, val);
     	break;
    case INDEX_COM_SEND_PedtrnAlrtInh_2bit:
      v_wr_8( PedtrnAlrtInh_handle, val);
     	break;
    default:
      break;
     	
  }
}


/******************************************************************************************/
/* ************************************************************************ */
/* Restores interrupt level to the previous level, as indicated by the in-  */
/* put previous. On the CPU12 family the interrupt level can only be either */
/* "interrupts enabled" or "interrupts disabled".                           */
void v_ctl_ints_restore(v_imask previous)
{
    if (previous)
    {
                                    /* disable_interrupt                    */
        asm sei;
    }
    else
    {
                                    /* enable_interrupt                     */
        asm cli;
    }
} /* v_ctl_ints_restore */

/* ************************************************************************ */
/* Disable interrupts, and return the previous value of the interrupt le-   */
/* vel.                                                                     */
v_imask v_ctl_ints_disable(void)
{
    asm tpa;                        /* register "A" will have the value 0x10*/
    asm anda #16;                   /* if interrupts are already disabled   */

    asm sei;                        /* disable_interrupt                    */

    asm tab;                        /* return value in register "B"         */
} /* v_ctl_ints_disable */



v_uint8 v_co_tx_frame_checksum(v_uint8 checksum_id, V_ARAM v_uint8  * V_ARAM_PM buff, v_uint8 len, v_uint32 frame_id)
{
	return 0;
}
v_uint8 v_co_rx_frame_checksum(v_uint8 checksum_id, V_ARAM v_uint8  * V_ARAM_PM buff, v_uint8 len, v_uint32 frame_id, v_uint8 checksum)
{
    return 0;

}
v_uint16 v_nmco_ioctl(v_c_handle c, v_uint16 op)
{
    return v_ctl_ioctl(c, (v_ioctl_op) op, (void *) 0);
}

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun       2018-06-05               Initial
*
*===========================================================================*/

