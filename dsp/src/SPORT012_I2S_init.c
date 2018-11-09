/*********************************************************************************

 Copyright(c) 2012 Analog Devices, Inc. All Rights Reserved.

 This software is proprietary and confidential.  By using this software you agree
 to the terms of the associated Analog Devices License Agreement.

 *********************************************************************************/

/*
 * Configures SPORT1 RX, SPORT0 TX and SPORT2 TX control and DMA registers for multichannel operation
 *
 *
 ****************************************************************************************************
 *
 *
 * rx1a_buf[2] - DSP SPORT0 A receive buffer - AD1939 ASDATA1
 *  Slot # Description                             DSP Data Memory Address
 *  ------ --------------------------------------  --------------------------------------------------
 * 0      Internal ADC 0 Left Channel             DM(_rx1a_buf + 0) = DM(_rx1a_buf + Internal_ADC_L1)
 * 1      Internal ADC 0 Right Channel            DM(_rx1a_buf + 1) = DM(_rx1a_buf + Internal_ADC_R1)
 *
 * rx1b_buf[2] - DSP SPORT0 B receive buffer - AD1939 ASDATA2
 * Slot # Description                             DSP Data Memory Address
 * ------ --------------------------------------  --------------------------------------------------
 * 0      Internal ADC 1 Left Channel             DM(_rx1b_buf + 2) = DM(_rx1b_buf + Internal_ADC_L2)
 * 1      Internal ADC 1 Right Channel            DM(_rx1b_buf + 3) = DM(_rx1b_buf + Internal_ADC_R2)
 *
 * tx0a_buf[2] - DSP SPORT0 A transmit buffer - AD1939 DSDATA1
 * Slot # Description                             DSP Data Memory Address
 * ------ --------------------------------------  --------------------------------------------------
 * 0      Internal DAC 1 Left Channel             DM(_tx0a_buf + 0) = DM(_tx0a_buf + Internal_DAC_L1)
 * 1      Internal DAC 1 Right Channel            DM(_tx0a_buf + 1) = DM(_tx0a_buf + Internal_DAC_R1)
 *
 * tx0a_buf[2] - DSP SPORT0 B transmit buffer - AD1939 DSDATA2
 * Slot # Description                             DSP Data Memory Address
 *  ------ --------------------------------------  --------------------------------------------------
 * 2      Internal DAC 2 Left Channel             DM(_tx0b_buf + 2) = DM(_tx0b_buf + Internal_DAC_L2)
 * 3      Internal DAC 2 Right Channel            DM(_tx0b_buf + 3) = DM(_tx0b_buf + Internal_DAC_R2)
 *
 * tx2a_buf[2] - DSP SPORT2 A transmit buffer - AD1939 DSDATA3
 * Slot # Description                             DSP Data Memory Address
 * ------ --------------------------------------  --------------------------------------------------
 * 4      Internal DAC 3 Left Channel             DM(_tx2a_buf + 4) = DM(_tx2a_buf + Internal_DAC_L3)
 * 5      Internal DAC 3 Right Channel            DM(_tx2a_buf + 5) = DM(_tx2a_buf + Internal_DAC_R3)
 *
 * tx2b_buf[2] - DSP SPORT2 B transmit buffer - AD1939 DSDATA4
 * Slot # Description                             DSP Data Memory Address
 * ------ --------------------------------------  --------------------------------------------------
 * 6      Internal DAC 4 Left Channel             DM(_tx2b_buf + 6) = DM(_tx2b_buf + Internal_DAC_L4)
 * 7      Internal DAC 4 Right Channel            DM(_tx2b_buf + 7) = DM(_tx2b_buf + Internal_DAC_R4)
 *
 */
// Infile

#include "ADDS_21479_EzKit.h"
//#include <def21469.h>
//asm("#include <def21469.h>");
//================================================//
#if 0
 	 int TxBlock_A0[TX_BLOCK_SIZE];
 	 int TxBlock_A1[TX_BLOCK_SIZE];

 	 int TCB_TxBlock_A0[4] = { 0, TX_BLOCK_SIZE, 1, TxBlock_A0};
 	 int TCB_TxBlock_A1[4] = { 0, TX_BLOCK_SIZE, 1, 0};
#else
 	 int TxBlock_A0[TX_BLOCK_SIZE];
 	 int TxBlock_A1[TX_BLOCK_SIZE];

 	 int TCB_TxBlock_A0[4] = { 0, TX_BLOCK_SIZE, 1, 0};
 	 int TCB_TxBlock_A1[4] = { 0, TX_BLOCK_SIZE, 1, 0};
#endif
//================================================//

int	 	rx1a_buf[2];   /* SPORT1 receive buffer A (DMA) */
int	 	rx1b_buf[2];   /* SPORT1 receive buffer B (DMA) */
int 	tx0a_buf[2];   /* SPORT0 transmit buffer A (DMA) */
int 	tx0b_buf[2];   /* SPORT0 transmit buffer B (DMA) */
int 	tx2a_buf[2];   /* SPORT2 transmit buffer A (DMA) */
int 	tx2b_buf[2];   /* SPORT2 transmit buffer B (DMA) */
    
				  		
/* TCB = "Transfer Control Block" */
/* TCB format:    ECx (length of destination buffer),
				  EMx (destination buffer step size),
				  EIx (destination buffer index (initialized to start address)),
				  GPx ("general purpose"),
				  CPx ("Chain Point register"; points to last address (IIx) of
			   								   next TCB to jump to
				                               upon completion of this TCB.),
				  Cx  (length of source buffer),
				  IMx (source buffer step size),
				  IIx (source buffer index (initialized to start address))       */

//int 	rcv1a_tcb[4]  = {0, 2, 1, (int) rx1a_buf};	/* SPORT1 receive a tcb */
//int 	rcv1b_tcb[4]  = {0, 2, 1, (int) rx1b_buf};	/* SPORT1 receive b tcb */
int 	xmit0a_tcb[4] = {0, 2, 1, (int) tx0a_buf};  /* SPORT0 transmit a tcb */
//int 	xmit0b_tcb[4] = {0, 2, 1, (int) tx0b_buf};  /* SPORT0 transmit a tcb */
//int 	xmit2a_tcb[4] = {0, 2, 1, (int) tx2a_buf};  /* SPORT2 transmit a tcb */
//int 	xmit2b_tcb[4] = {0, 2, 1, (int) tx2b_buf};  /* SPORT2 transmit a tcb */

void initSPORT(void)
{

/* Set up "ping-pong" chained DMAs for AD1939 */

/*Proceed from Block A0 to Block A1 */
/* Extract 19-bits of the receive buffer A1 address with setting PCI bit */
   //// TCB_RxBlock_A0[0] = (((unsigned int) TCB_RxBlock_A1 + 3)& OFFSET_MASK)|PCI ;
/*  Extract 19-bits of the receive buffer A0 address */
    ////TCB_RxBlock_A0[3] = ((int) RxBlock_A0)& OFFSET_MASK ;
#if 1
/* Proceed from Block A0 to Block A1*/
/* Extract 19-bits of the transmit buffer A1 address */
    TCB_TxBlock_A0[0] = (((unsigned int) TCB_TxBlock_A1 + 3)& OFFSET_MASK) | PCI ;
/*  Extract 19-bits of the transmit buffer A0 address */
    TCB_TxBlock_A0[3] = ((int) TxBlock_A0)& OFFSET_MASK ;
#endif
/* Proceed from Block B0 to Block B1 */
/* Extract 19-bits of the transmit buffer B1 address */
    ////TCB_TxBlock_B0[0] = ((unsigned int) TCB_TxBlock_B1 + 3)& OFFSET_MASK ;
/*  Extract 19-bits of the transmit buffer B0 address */
    ////TCB_TxBlock_B0[3] = ((int) TxBlock_B0)& OFFSET_MASK ;

/* Proceed from Block A1 to Block A0 */
/* Extract 19-bits of the receive buffer A0 address with setting PCI bit */
    ////TCB_RxBlock_A1[0] = (((unsigned int) TCB_RxBlock_A0 + 3)& OFFSET_MASK)|PCI ;
/*  Extract 19-bits of the receive buffer A1 address  */
    ////TCB_RxBlock_A1[3] = ((int) RxBlock_A1)& OFFSET_MASK ;
#if 1
/* Proceed from Block A1 to Block A0 */
/* Extract 19-bits of the transmit buffer A0 address */
    TCB_TxBlock_A1[0] = (((unsigned int) (TCB_TxBlock_A0 + 3))& OFFSET_MASK) | PCI ;


/*  Extract 19-bits of the transmit buffer A1 address */
    TCB_TxBlock_A1[3] = ((int) TxBlock_A1)& OFFSET_MASK ;

#endif
/* Proceed from Block AB to Block B0 */
/* Extract 19-bits of the transmit buffer B0 address */
    ////TCB_TxBlock_B1[0] = ((unsigned int) TCB_TxBlock_B0 + 3)& OFFSET_MASK ;
/*  Extract 19-bits of the transmit buffer B1 address */
    ////TCB_TxBlock_B1[3] = ((int) TxBlock_B1)& OFFSET_MASK ;


/*Clear out SPORT 0/1 registers */
	*pSPMCTL0 = 0;
	*pSPMCTL1 = 0;
    *pSPCTL0 = 0;
    *pSPCTL1 = 0;


/*     Analog Input and output setup  */


/* External clock and frame syncs generated by AD1939 */
   	*pDIV0 = 0x00000000;  /* Transmitter (SPORT0) */
    *pDIV1 = 0x00000000;  /* Receiver (SPORT1) at 12.288 MHz SCLK and 48 kHz sample rate */


    ////TCB_TxBlock_A0[0] = *pCPSP0A = (((int) TCB_TxBlock_A0 + 3) & 0x7FFFF) | (1<<19);

#if 1
/* Configuring SPORT0 & SPORT1 for "Multichannel" mode */
/* This is synonymous TDM mode which is the operating mode for the AD1939 */

/* Enabling DMA Chaining for SPORT0 TX/SPORT1 RX */
/* Block 1 will be filled first */
    /* Initialize the chain pointer for the transmitter with PCI bit set to enable the interrupts after every TCB */
    *pCPSP0A = (unsigned int)TCB_TxBlock_A0 - OFFSET + 3 + PCI;
    /* Initialize the chain pointers for transmitters */
    ////*pCPSP0B = (unsigned int)TCB_TxBlock_B0 - OFFSET + 3;
   //// *pCPSP1A = (unsigned int)TCB_RxBlock_A0 - OFFSET + 3;
#endif

/* sport1 control register set up as a receiver in MCM
 * sport 1 control register SPCTL1 = 0x000C01F0
 * externally generated SCLK1 and RFS1
 */
	/////*pSPCTL1 = 	SCHEN_A | SDEN_A | SLEN32;

/* sport0 control register set up as a transmitter in MCM */
/* sport 0 control register, SPCTL0 = 0x000C01F0 */
	//*pSPCTL0 = 	SCHEN_B | SDEN_B | SCHEN_A | SDEN_A | SPTRAN | SLEN32;
    *pSPCTL0 = SCHEN_A | SDEN_A | SPTRAN | SLEN32 | OPMODE | SPEN_A;

/* sport1 receive & sport0 transmit multichannel word enable registers */
    /////*pSP1CS0 = 0x0000000F;	/* Set to receive on channel 0-3 on SPORT1 A */
    /////*pSP0CS0 = 0x0000000F;	/* Set to transmit on channel 0-3 on SPORT0 A/B */

/*  sport1 & sport0 receive & transmit multichannel companding enable registers
 *  no companding for our 4 RX and 4 TX active timeslots
 *  no companding on SPORT1 receive
 *  no companding on SPORT0 transmit
 */
	////*pMR1CCS0 = *pMT0CCS0 = 0;

/* SPORT 0&1  Miscellaneous Control Bits Registers */
/* SP01MCTL = 0x000000E2,  Hold off on MCM enable,
 * and number of TDM slots to 8 active channels
 */

/* Multichannel Frame Delay=1, Number of Channels = 8, LB disabled */
	////*pSPMCTL0 = NCH3 | MFD1;
	////*pSPMCTL1 = NCH3 | MFD1;



/* Enable multichannel operation (SPORT mode and DMA in standby and ready) */
	////*pSPMCTL0 |= MCEB | MCEA;
	////*pSPMCTL1 |= MCEA;
}


void 	enable_SPORT012_I2S_mode()
{
	/* Clear out SPORT 0/1/2 registers */
    *pSPCTL0 = *pSPCTL1 = *pSPCTL2 = 0;
    *pSPMCTL0 = *pSPMCTL1 = *pSPMCTL2 = 0;
    *pSPCTLN1 = *pSPCTLN0 = *pSPCTLN2 = 0;
	
    /* External clock and frame syncs generated by AD1939 */
   	*pDIV0 = 0x00000000;  // Transmitter (SPORT0)
    *pDIV1 = 0x00000000;  // Receiver (SPORT1) at 12.288 MHz SCLK and 48 kHz sample rate

	/* SPORT0 and SPORT1 are being operated in "I2S" mode.
	This is synonymous with stereo operating mode for the AD1939 */	
	
		//rcv1a_tcb[0]  = *pCPSP1A = (((int) rcv1a_tcb  + 3) & 0x7FFFF )| (1<<19);
	//rcv1b_tcb[0]  = *pCPSP1B = (((int) rcv1b_tcb  + 3) & 0x7FFFF) | (1<<19);
	xmit0a_tcb[0] = *pCPSP0A = (((int) xmit0a_tcb + 3) & 0x7FFFF) | (1<<19);
	//xmit0b_tcb[0] = *pCPSP0B = (((int) xmit0b_tcb + 3) & 0x7FFFF) | (1<<19);
	//xmit2a_tcb[0] = *pCPSP2A = (((int) xmit2a_tcb + 3) & 0x7FFFF) | (1<<19);
	//xmit2b_tcb[0] = *pCPSP2B = (((int) xmit2b_tcb + 3) & 0x7FFFF) | (1<<19);

	/* SPORT1 control register is set up as a receiver in I2S for ADC1 and ADC2 */
	/* SPORT1  control register SPCTL1 = 0x00000000 */
	/* externally generated SCLK1 and RFS1 */
	/* primary and secondary channels enabled with DMA chaining */
	//*pSPCTL1 = (OPMODE | SLEN32 | SPEN_A | SCHEN_A | SDEN_A | SPEN_B | SCHEN_B | SDEN_B);
	
	/* SPORT0 control register set up as a transmitter in I2S for DAC1 and DAC2*/
	/* externally generated SCLK0 and RFS0 */
	/* primary and secondary channels enabled with DMA chaining */
	//*pSPCTL0 = (SPTRAN | OPMODE | SLEN32 | SPEN_A | SCHEN_A | SDEN_A | SPEN_B | SCHEN_B | SDEN_B);
	*pSPCTL0 = (SPTRAN | OPMODE | SLEN32 | SPEN_A | SCHEN_A | SDEN_A);
	
	/* SPORT2 control register set up as a transmitter in I2S for DAC3 and DAC4 */
	/* externally generated SCLK2 and RFS2 */
	/* primary and secondary channels enabled with DMA chaining */
	//*pSPCTL2 = (SPTRAN | OPMODE | SLEN32 | SPEN_A | SCHEN_A | SDEN_A | SPEN_B | SCHEN_B | SDEN_B);
}	

void 	enable_SPORT012_DMA_channels()
{


}	


#ifdef DEBUG
/* TDM audio frame/ISR counter, for debug purposes */
int			audio_frame_timer = 0;
#endif


