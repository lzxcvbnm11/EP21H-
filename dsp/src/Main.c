/*********************************************************************************

 Copyright(c) 2012 Analog Devices, Inc. All Rights Reserved.

 This software is proprietary and confidential.  By using this software you agree
 to the terms of the associated Analog Devices License Agreement.

 *********************************************************************************/
/*This project is a talk-through example using the onboard AD1939 to acquire
 * and output an audio stream. The digital audio data is available for processing
 * in the file SPORT1_isr.c. The block size is 256 samples per audio channel.
 * The output on OUT2 is delayed and the user can expect to hear an echo effect.
 */


#include "ADDS_21479_EzKit.h"
#include "ENG_SPEECH.h"
#include "yd_typedefs.h"

#include "driver/SPIB/spib_public.h"
#include "driver/SPI/spi_public.h"
#include "driver/timer/timer_public.h"
#include "app/EVT/evt_public.h"
#include "app/MDATA/mdata_public.h"
#include "driver/UART/uart_public.h"
#include "middleware/FLAM/flam_public.h"

volatile float * DelayLine;
char time_20ms = 0;
char time_20msCnt = 0;

char buffer[300];

void delay(int time)
{
	int i,j;
	for(i = time ;i>0;i--)
		for(j=time;j>0;j--);
}


void main()
{
	int i = 55;
	int tmp = 0;
	/* Initialize managed drivers and/or services at the start of main(). */
	adi_initComponents();

	initPLL();
	////initExternalMemory();


	/* Initialize DAI because the SPORT and SPI signals need to be routed*/
    InitDAI();

    /* This function will configure the AD1939 codec on the 21469 EZ-KIT*/
    ////init1939viaSPI();

    /* Turn on SPORT0 TX and SPORT1 RX for Multichannel Operation*/
    initSPORT();
    SPI_init();
	SPIB_Init();
	SYS_Init();
	UART_init();

	/*block interrupt*/
    adi_int_InstallHandler(ADI_CID_P6I,TalkThroughISR,0,true);	

    /* Be in infinite loop and do nothing until done.*/

    while(1)
    {

    		if(inputReady)
    		{
    			/*load audio data*/
    			handleCodecData(buffer_cntr);
        	}

        	if(time_20ms)
    		{
        		 MDATA_Process_20ms();
    			 EVT_Process_20ms();
    			 time_20ms = 0;
    			 time_20msCnt = 0;
    		}

    	/*delay(10);
    	UART_ReadData(buffer,300);
    	UART_PutChar(0x66);
    	*/
    }

}
