/*********************************************************************************

 Copyright(c) 2012 Analog Devices, Inc. All Rights Reserved.

 This software is proprietary and confidential.  By using this software you agree
 to the terms of the associated Analog Devices License Agreement.

 *********************************************************************************/

/*
 * USAGE:    This file contains the ISR C function to process AD1939 samples.
 * DMA Buffer relationship to C Audio Variables

 * Chan/Offset SPORT DMA Buffer Timeslot Data   <->  AD1939 ADC/DAC C Variables (floats)
 * ======================================================================================

 * 0           DM(_rx1a_buf + Internal_ADC_L1) -->  Left_Channel_In1
 * 1           DM(_rx1a_buf + Internal_ADC_R1) -->  Right_Channel_In1
 * 0           DM(_rx1b_buf + Internal_ADC_L2) -->  Left_Channel_In2
 * 1           DM(_rx1b_buf + Internal_ADC_R2) -->  Right_Channel_In2

 * 0           DM(_tx0a_buf + Internal_DAC_L1)  <--  Left_Channel_Out1
 * 1           DM(_tx0a_buf + Internal_DAC_R1)  <--  Right_Channel_Out1
 * 0           DM(_tx0b_buf + Internal_DAC_L2)  <--  Left_Channel_Out2
 * 1           DM(_tx0b_buf + Internal_DAC_R2)  <--  Right_Channel_Out2
 * 0           DM(_tx2a_buf + Internal_DAC_L3)  <--  Left_Channel_Out3
 * 1           DM(_tx2a_buf + Internal_DAC_R3)  <--  Right_Channel_Out3
 * 0           DM(_tx2b_buf + Internal_DAC_L4)  <--  Left_Channel_Out4
 * 1           DM(_tx2b_buf + Internal_DAC_R4)  <--  Right_Channel_Out4
 */


#include "ADDS_21479_EzKit.h"
#include "ENG_SPEECH.h"
#include "app/EVT/evt_public.h"
#include "app/FIFO/fifo_public.h"
unsigned int flag = 2;
extern u32 Evt_flag;
int iisisProcessing = 0;
float task_SpeceVauleFloat = 0;
float task_EngVauleFloat = 0;
int task_ChangeSpeceFlag = 0;

u8 task_ChangeEngFlag;
u8 EngPlayFlag = 0;
u32 EndFifoFlag = 0;

void  process_AD1939_samples( uint32_t iid, void *handlerarg)
{
    /* uncomment these next 8 statements to test fixed point loopback
     *  rx/tx SPORT DMA buffer data in 1.31 fractional fixed point format
     */

	int count = 0;
	if (iisisProcessing)   /* Ddebug */
       {
		count = 1;
       }
#if 1
//	EngPlayFlag = EVT_GetEngPlayFlag();

	if(EngPlayFlag == 1)
	{
		task_EngVauleFloat = ENG_process();
		if(!EndFifoFlag)
		{
			FIFO_Process_1_16ms();
			task_EngVauleFloat = FIFO_GetVolVaule(task_EngVauleFloat,&EndFifoFlag);
		}
	}

	task_ChangeSpeceFlag = EVT_GetChangeSpeFlag();
	if(1)//task_ChangeSpeceFlag  == 0)
	{
		task_SpeceVauleFloat = Speech_process(&Evt_flag);
			if(Evt_flag == 2)
			{
				EVT_SetChangeSpeFlag();
				task_SpeceVauleFloat = 0;
			}
		}

	task_SpeceVauleFloat = data_mix(task_EngVauleFloat,task_SpeceVauleFloat);
	//task_SpeceVauleFloat = task_SpeceVauleFloat * 0.05;
	////data_in(0,buf,8);
	Left_Channel_Out1 = task_SpeceVauleFloat;
	Right_Channel_Out1 = task_SpeceVauleFloat;

	Transmit_DAC_Samples();
#endif
	
//	sysreg_bit_clr( sysreg_FLAGS, FLG6);
}


