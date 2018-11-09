/* ************************************************************************ */
/*                                                                          */
/*                        Mentor Graphics Corporation                       */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: target.c                                                   */
/*  Description: Target specifics                                           */

#include "volcano6.h"
#include "target.h"

typedef volatile unsigned char creg_u8;
typedef volatile unsigned short creg_u16;

#define REG_U8(base, offset)    (* (creg_u8  *) ((v_uint8  *) (base) + (offset)) )
#define REG_U16(base, offset)   (* (creg_u16 *) ((v_uint8  *) (base) + (offset)) )

/* Port Integration Module */
#define PIM_BASE  (0x0000u)

#define	PORTE     REG_U8 (PIM_BASE, 0x08u)
#define CAN_STB   ((1 << 4) | (1 << 7))     /* CAN0, CAN1 STB */
#define CAN_EN    ((1 << 5) | (1 << 6))     /* CAN0, CAN1 EN */

#define	DDRE      REG_U8 (PIM_BASE, 0x09u)
#define	PEAR      REG_U8 (PIM_BASE, 0x0Au)


/* Clock and Reset Generator */
#define CRG_BASE  (0x0034u)
#define SYNR      REG_U8 (CRG_BASE, 0x00u)
#define REFDV     REG_U8 (CRG_BASE, 0x01u)

#define CRGFLG    REG_U8 (CRG_BASE, 0x03u)
#define LOCK      (1 << 3)
#define UPOSC	  (1 << 0)

#define CPMUCLKS  REG_U8 (CRG_BASE, 0x05u)
#define CPMUOSC   REG_U8 (CRG_BASE, 0x2C6u)

#define PLLSEL    (1 << 7)
#define OSCE      (1 << 7)

#define PLLCTL    REG_U8 (CRG_BASE, 0x06u)
#define CME       (1 << 7)
#define PLLON     (1 << 6)
#define AUTOX     (1 << 5)
#define SCME      (1 << 0)

#define POSTDIV   REG_U8 (CRG_BASE, 0x02u)

/* Enhanced Capture Timer */
#define ECT_BASE  (0x0040u)
#define TCNT      REG_U16(ECT_BASE, 0x04u)

#define TSCR1     REG_U8 (ECT_BASE, 0x06u)
#define TEN       (1 << 7)

#define TSCR2     REG_U8 (ECT_BASE, 0x0Du)
#define PR_BITS   (0x07u)


/* ************************************************************************ */
/* Perform initialisation of development system (if any)                    */
void init_environment()
{
} /* init_environment */

/* ************************************************************************ */
/* Perform initialisation of target. Initialise a free running counter at   */
/* 1Mhz.                                                                    */

#define REFDV_ (1)
								   /* REFFRQ[1:0] = 01: 2MHz < fREF <= 6MHz */
#define REFFRQ_4MHZ (1u << 6)
#define SYNR_  (3u)

void init_target(void)
{
                                    
    CPMUOSC = OSCE;                 /* enable external oscillator */
	
	while ((CRGFLG & UPOSC) == 0)
    {
                                    /* wait for oscillator lock */
    }
	                                /* fosc = 8 MHz */
                                    /* fref = fosc / (REFDIV+1) = 4 MHz */
    REFDV = REFFRQ_4MHZ | REFDV_;
	                                /* fvco = 2*fref*(SYNR+1) = 32 MHz
                                     * fperipheral = 16 MHz */
    SYNR = SYNR_;
    POSTDIV = 0;                    /* fPLL = fvco */
    while((CRGFLG & LOCK) == 0)
    {
                                    /* wait for PLL lock */
    }
                                    /* switch to PLLCLK */
    CPMUCLKS |= PLLSEL;
                                    /* enable timer */
    TSCR1 |= TEN;
                                    /* set prescaler 16 */
    TSCR2 = (TSCR2 & ~PR_BITS) | 0x04;

} /* init_target*/

/* ************************************************************************ */
/* Read timer channel A (free running counter at 1Mhz) and return current   */
/* value.                                                                   */
v_uint16 hw_get_clock(void)
{
    return TCNT;
} /* hw_get_clock */