/*********************************************************************************

 Copyright(c) 2012 Analog Devices, Inc. All Rights Reserved.

 This software is proprietary and confidential.  By using this software you agree
 to the terms of the associated Analog Devices License Agreement.

 *********************************************************************************/
/*
 * NAME:     blockProcess_audio.c (Block-based Talk-through)
 * PURPOSE:  Process incoming AD1939 ADC data and prepare outgoing blocks for DAC.
 * USAGE:    This file contains the subroutines that float and fix the serial data,
 *        	 and copy from the inputs to the outputs.
 */

#include "ADDS_21479_EzKit.h"
#include "ENG_SPEECH.h"
#include "app/EVT/evt_public.h"
#include "app/FIFO/fifo_public.h"
#include "app/LEVEL/level_public.h"
#include "app/MDATA/mdata_public.h"
#include "string.h"
/* Define a structure to represent buffers for all 12 floating-point
 * data channels of the AD1939 */


/* SPORT Ping/Pong Data buffers */


extern int TxBlock_A0[];
extern int TxBlock_A1[];
extern u32 Evt_flag;

volatile float task_EngVoice = 0;
volatile float task_SpeVoice = 0;
volatile float task_MixVoice = 0;
static u8 task_ChangeSpeceFlag = 0;
static u8 SpePlayFlag = 0;
static u8 EngPlayFlag = 0;
static u32 EnFifo = 0;
static u8 task_FifoInOrOut = FIFO_INSELECT;
/* Pointer to the blocks */
//int *rxA_block_pointer[2] = {RxBlock_A0, RxBlock_A1};
int *txA_block_pointer[2] = {TxBlock_A0, TxBlock_A1};
//int *txB_block_pointer[2] = {TxBlock_B0, TxBlock_B1};
typedef struct{

	float Tx_L1[NUM_SAMPLES];
	float Tx_R1[NUM_SAMPLES];

} ad1939_float_data;

/*  Structures to hold floating point data for each AD1939 */
ad1939_float_data fBlockA;
int Audio_Sample_Index = 0;
int Audio_Sample_Finish = 0;
static void process_audioBlocks(void);

/* Unoptimized function to convert the incoming fixed-point data to 32-bit
* floating-point format. This function assumes that the incoming fixed point
* data is in 1.31 format
*/
static void floatData(float *output, int *input, unsigned int instep, unsigned int length)
{
    int i;

    for(i = 0; i < length; i++)
    {
        output[i] = input[instep*i];//__builtin_conv_RtoF(input[instep*i]);
    }
}


/* Unoptimized function to convert the outgoing floating-point data
 * to 1.31 fixed-point format.*/
static void fixData(int *output, float *input, unsigned int outstep, unsigned int length)
{
    int i;

    for(i = 0; i < length; i++)
    {
        output[outstep*i] = __builtin_conv_FtoR(input[i]);
    }
}


/* Unoptimized function to copy from one floating-point buffer to another */
static void memcopy(float *input, float *output, unsigned int number)
{
    int i;
    
    for(i = 0; i < number; i++)
    {
        output[i] = input[i];
    }
}



/*
 * Audio Block Processing Algorithm for 192 kHz 4 IN x 4 OUT Audio System
 * The inputs and outputs are held in a structure for the AD1939
 * fBlockA holds stereo input (AIN) channels 0-3 and stereo output (AOUT) channels 0-7
 *
 * This function copies the data without any processing as follows
 * AOUT1L <- AIN1L
 * AOUT1R <- AIN1R
 * AOUT2L <- AIN1L
 * AOUT2R <- AIN1R
 *
 * AOUT3L <- AIN2L
 * AOUT3R <- AIN2R
 * AOUT4L <- AIN2L
 * AOUT4R <- AIN2R
 */


static void process_One_Sameple_audio(void)
{
	u8 SpeechSelect_tmp = 0;
	u32 PlayingFlagTemp = 0;
	vehicle_para_inst vehice;

	static u8 MutePlayingFlag = 0;

	task_ChangeSpeceFlag = EVT_GetChangeSpeFlag();

	task_EngVoice = 0;
	task_SpeVoice = 0;
	vehice.spd = 0;
/*get speech audio waring data*/
	task_SpeVoice = Speech_process(&PlayingFlagTemp);
	if(task_ChangeSpeceFlag == INDEX_NORMAL)
	{
		Evt_flag = PlayingFlagTemp;
		if(Evt_flag == INDEX_END)
		{
			EVT_SetChangeSpeFlag();
			SpePlayFlag = EVT_PAUSE;
			MutePlayingFlag = INDEX_END;
		}
	}
	else if(task_ChangeSpeceFlag == INDEX_PLAYAUDIOWARNING)
	{
		Evt_flag = PlayingFlagTemp;
		if(Evt_flag == INDEX_END)
		{
			SpeechSelect_tmp = MDATA_GetpassltreqVaule();
			if(SpeechSelect_tmp != EVT_PLAYTEST)
			{
				EVT_SetChangeSpeFlag();
			}
		}
	}
	else /*play mute*/
	{
		if( MutePlayingFlag  == INDEX_END)
		{
			Speech_init(EVT_MUTE);
			MutePlayingFlag++;
			Evt_SetSpeSelectMute();
		}

	}


/*get eng audio data*/
	task_EngVoice = ENG_process();
	FIFO_Process_1_16ms();





	task_MixVoice = data_mix(task_EngVoice,task_SpeVoice);


	LEVEL_Process_1_16ms();

	task_MixVoice = LEVEL_GetVolVaule();

	if(Audio_Sample_Index >=NUM_SAMPLES) Audio_Sample_Index = 0;

	fBlockA.Tx_L1[Audio_Sample_Index] = task_MixVoice;
	fBlockA.Tx_R1[Audio_Sample_Index] = task_MixVoice;
	Audio_Sample_Index++;
	if(Audio_Sample_Index >=NUM_SAMPLES)
	{
		Audio_Sample_Finish = 1;
		Audio_Sample_Index = 0;
	}

}

float Task_GetTaskVioce(void)
{
	return task_MixVoice;
}


/*
 * This function handles the Codec data in the following 3 steps...
 *    1. Converts all ADC data to 32-bit floating-point, and copies this
 *       from the current RX DMA buffer into fBlockA & fBlockB
 *    2. Calls the audio processing function (processBlocks)
 *    3. Converts all DAC to 1.31 fixed point, and copies this from
 *       fBlockA & fBlockB into the current TX DMA buffer
 */

void handleCodecData(unsigned int blockIndex)
{
/* Clear the Block Ready Semaphore */


/* Set the Processing Active Semaphore before starting processing */
    isProcessing = 1;
    process_One_Sameple_audio();

    if(Audio_Sample_Finish == 1)
    {
    	fixData(txA_block_pointer[blockIndex]+0, fBlockA.Tx_L1, NUM_TX_SLOTS, NUM_SAMPLES);
    	fixData(txA_block_pointer[blockIndex]+1, fBlockA.Tx_R1, NUM_TX_SLOTS, NUM_SAMPLES);
        isProcessing = 0;
        Audio_Sample_Finish = 0;
        inputReady = 0;
    }
}

