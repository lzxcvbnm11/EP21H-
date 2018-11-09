/* ************************************************************************ */
/*                                                                          */
/*                        Mentor Graphics Corporation                       */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: ints.c                                                     */
/*  Description: Interrupt handlers calling Volcano 6 functions for msCAN12 */
/*               Uses HIWARE specific method of initialising                */
/*               the vector table.                                          */


#include "volcano6.h"
#include "v_hand.h"

#pragma CODE_SEG MSCAN_INTVECT_SEG

#pragma TRAP_PROC SAVE_ALL_REGS
void mscan_tx_handler(void)
{
                                    /* Call Volcano 5 Tx-interrupt handler. */
  //(void) v_ctl_txint(NI1_handle);
	(void) v_ctl_txint(PACM_HSC4_handle);

	
}

#pragma TRAP_PROC SAVE_ALL_REGS
void mscan_rx_handler(void)
{
                                    /* Call Volcano 5 Rx-interrupt handler. */
                                    /* The return value is not interesting  */
                                    /* in this application.                 */
    //(void) v_ctl_rxint(NI1_handle);
	 (void) v_ctl_rxint(PACM_HSC4_handle);
}

#pragma TRAP_PROC SAVE_ALL_REGS
void mscan_err_handler(void)
{
                                    /* Call Volcano 5 Busoff-interrupt      */
                                    /* handler.                             */
   ///v_ctl_busoffint(NI1_handle);
	v_ctl_busoffint(PACM_HSC4_handle);
}

#pragma CODE_SEG default
