/*********************************************************************************

 Copyright(c) 2012 Analog Devices, Inc. All Rights Reserved.

 This software is proprietary and confidential.  By using this software you agree
 to the terms of the associated Analog Devices License Agreement.

 *********************************************************************************/
/*
 * NAME:     SPORT1_isr.c (Block-based Talkthrough for 192 kHz fs)
 * PURPOSE:  Talkthrough framework for sending and receiving samples to the AD1939.
 * USAGE:    This file contains SPORT1 Interrupt Service Routine. Four buffers are used
 * 		     for this example: Two input buffers, and two output buffers.
*/


/*
 *  Here is the mapping between the SPORTS and the ADCs/DACs
 *  For AD1939
 *  ADC1 -> DSP : SPORT1A : TDM Channel 0,1
 *  ADC2 -> DSP : SPORT1A : TDM Channel 2,3
 *  DSP -> DAC1 : SPORT0A : TDM Channel 0,1
 *  DSP -> DAC2 : SPORT0A : TDM Channel 2,3
 *  DSP -> DAC3 : SPORT0B : TDM Channel 0,1
 *  DSP -> DAC4 : SPORT0B : TDM Channel 2,3
 */

#include "ADDS_21479_EzKit.h"
#include "ENG_SPEECH.h"
int test_cnt = 0;
extern int TxBlock_A0[TX_BLOCK_SIZE];
extern char time_20ms;
extern char time_20msCnt;
extern int Rx_bufferflag;
/* Counter to choose which buffer to process */
volatile int buffer_cntr = 1;
/* Semaphore to indicate to main that a block is ready for processing */
volatile int inputReady = 0;
/* Semaphore to indicate to the isr that the processing has not completed before the
 * buffer will be overwritten.
 */
volatile int isProcessing = 0;

extern volatile int SPIB_irq_flag;

/* If the processing takes too long, the program will be stuck in this infinite loop. */
void ProcessingTooLong(void)
{
	static int cnt = 0;
	//cnt++;
	//if(cnt == 200)
	//while(1)
    {
			cnt = 0;
    	//printf("jason dead \r\n");

    };
}

//int cyf_flag = 0;
vehicle_para_inst  cyf_vehicle = {0.5};

int add_sub = 0;

void TalkThroughISR(uint32_t iid, void* handlerArg)
{
	/*8ms once*/
	time_20msCnt++;
    if(time_20msCnt >= 2)
    {
    	time_20ms = 1;
    }
	/*spib clear Rx_bufferflag*/
	if(SPIB_irq_flag)
	{
		SPIB_irq_flag = 0;
	}
	else
	{	
    	Rx_bufferflag = 0;
	}
	
    if(isProcessing)
        ProcessingTooLong();

    if(buffer_cntr == 0)
    {
    	buffer_cntr = 1;

    }
    else
    {
    	buffer_cntr = 0;
    }

    inputReady = 1;

}
