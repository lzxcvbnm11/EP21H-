/*********************************************************************************

 Copyright(c) 2012 Analog Devices, Inc. All Rights Reserved.

 This software is proprietary and confidential.  By using this software you agree
 to the terms of the associated Analog Devices License Agreement.

 *********************************************************************************/

///////////////////////////////////////////////////////////////////////////////////////
//
//NAME:     ADDS_21479_EzKit.h
//DATE:     2/13/09
//PURPOSE:  Header file with definitions use in the C-based talkthrough examples
//
////////////////////////////////////////////////////////////////////////////////////////

#ifdef __ECC__

#include <stdio.h>     /* Get declaration of puts and definition of NULL. */
#include <stdint.h>    /* Get definition of uint32_t. */
#include <stdlib.h>    /* Get definition of malloc. */
#include <assert.h>    /* Get the definition of support for standard C asserts. */
#include <builtins.h>  /* Get definitions of compiler builtin functions */
#include <platform_include.h>      /* System and IOP register bit and address definitions. */
#include <processor_include.h>
#include <services/int/adi_int.h>  /* Interrupt Handler API header. */
#include "adi_initialize.h"
#include <sru.h>
#include "ad1939.h"
#include <asm_sprt.h>
#include "SPORT1_Macros.h"

//===========================================================//
/* Block Size per Audio Channel*/
#define NUM_SAMPLES  128 //128

/* Number of stereo channels*/
#define NUM_RX_SLOTS 4
#define NUM_TX_SLOTS  2 //4

#define RX_BLOCK_SIZE (NUM_SAMPLES*NUM_RX_SLOTS)
#define TX_BLOCK_SIZE  (NUM_SAMPLES*NUM_TX_SLOTS)

#define PCI  0x00080000
#define OFFSET 0x00080000
#define OFFSET_MASK 0x7FFFF
// Global Variables
extern volatile int count;
extern volatile int isProcessing;
extern volatile int inputReady;
extern volatile int buffer_cntr;

void initSPORT(void);

static void ProcessingTooLong(void);
void TalkThroughISR(uint32_t, void*);
//void ClearSPORT(void);
void handleCodecData(unsigned int);

//===========================================================//

// Function prototypes for this talkthrough code
void	Setup_ADSP21479(void);
void	initPLL(void);
void    initExternalMemory(void);
void 	InitDAI(void);
static void 	clearDAIpins(void);
void 	init1939viaSPI(void);
void 	enable_SPORT012_I2S_mode(void);
void 	enable_SPORT012_DMA_channels(void);
void	process_AD1939_samples(uint32_t , void *);
void	Receive_ADC_Samples(void);
void	Transmit_DAC_Samples(void);

static void 	SetupSPI1939(unsigned int);
static void 	DisableSPI1939();
static void 	Configure1939Register(unsigned char,unsigned char,unsigned char,unsigned int);
static unsigned char Get1939Register(unsigned char,unsigned int);

static void 	Delay(int i);
void	SinTableInit(void);

/* Insert global variable definitions here */

extern int rx1a_buf[2];
extern int rx1b_buf[2];
extern int tx0a_buf[2];
extern int tx0b_buf[2];
extern int tx2a_buf[2];
extern int tx2b_buf[2];

extern void Delay (int i);
extern float Sine_Table[SINETABLESIZE];
extern volatile int Sine_Index;

extern volatile float * DelayLine;
extern volatile int Index;

// input audio channels
extern 	float			Left_Channel_In1;       /* Input values from the AD1939 internal stereo ADCs */
extern 	float 			Right_Channel_In1;
extern	float			Left_Channel_In2;
extern  float			Right_Channel_In2;

//output audio channels
extern 	float			Left_Channel_Out1;      /* Output values for the 4 AD1939 internal stereo DACs */
extern 	float 			Left_Channel_Out2;
extern 	float 			Left_Channel_Out3;
extern 	float 			Left_Channel_Out4;
extern 	float			Right_Channel_Out1;
extern 	float			Right_Channel_Out2;
extern 	float			Right_Channel_Out3;
extern 	float			Right_Channel_Out4;




#else
/* Insert Assembly Definitions here.... */

#endif

/* Insert C Definitions here.... */

#define SPIB_MODE (CPHASE | CLKPL)
#define AD1939_CS DS0EN
//#define AD1939_CS DS1EN

#define CLEAR_DSXEN_BITS 0xF00

#define SELECT_SPI_SLAVE(select) (*pSPIFLG &= ~(spiselect<<8))
#define DESELECT_SPI_SLAVE(select) (*pSPIFLG |= (spiselect<<8))

/* AD1939 I2S Timeslot Definitions */
#define     Internal_ADC_L1    0
#define     Internal_ADC_R1    1
#define     Internal_ADC_L2    0
#define     Internal_ADC_R2    1

#define     Internal_DAC_L1    0
#define     Internal_DAC_R1    1
#define     Internal_DAC_L2    0
#define     Internal_DAC_R2    1
#define     Internal_DAC_L3    0
#define     Internal_DAC_R3    1
#define     Internal_DAC_L4    0
#define     Internal_DAC_R4    1


