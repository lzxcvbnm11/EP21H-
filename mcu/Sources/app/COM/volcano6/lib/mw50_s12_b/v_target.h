/* ************************************************************************ */
/*                                                                          */
/*                        Mentor Graphics Corporation                       */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: v_target.h                                                 */
/*  Description: Target-dependent user visible items for Star12 Banked      */


#ifndef __V_TARGET_H__
#define __V_TARGET_H__

typedef unsigned char  v_uint8;
typedef unsigned short v_uint16;
typedef unsigned char  v_bool;
typedef unsigned char  v_imask;
typedef unsigned long  v_uint32;

typedef struct
{
    v_uint32    mask[8];
} v_frame_map;

typedef unsigned char  v_unat;

                                    /* target-dependent mask size determines*/
                                    /* maximum number of immediate frames   */
                                    /* per controller                       */
typedef v_uint32       v_imf_mask;

                                    /* limit logical handle range to make   */
                                    /* indexing easier                      */
typedef unsigned char  v_logical_handle;

/* type modifiers */
#define V_FAR                       /* data in extended memory              */
#define V_NEAR                      /* data in zero page                    */
#define V_DIRECT                    /* put parameters in zero page          */
#define V_REENTRANT                 /* put parameters on the stack          */
#define V_EXTENDED                  /* put parameters in non-zero page RAM  */
#define V_OVERLAY                   /* do not use the stack                 */

#define V_FIXED         const
#define V_NVRAM         const       /* indicates storage in NVRAM area      */
#define V_AROM          const       /* indicates application ROM storage    */
#define V_ARAM                      /* indicates application RAM storage    */
#define V_RAM                       /* indicates Volcano RAM storage(VOLRAM)*/
#define V_API_FN_PREFIX             /* resides in other bank / page         */
#define V_API_FN_SUFFIX             /* resides in other bank / page         */

#define V_NVRAM_PM                  /* NVRAM pointer qualifier              */
#define V_AROM_PM                   /* application ROM pointer qualifier    */
#define V_ARAM_PM                   /* application RAM pointer qualifier    */
#define V_RAM_PM                    /* RAM qualifier */

#endif /* __V_TARGET_H__ */
