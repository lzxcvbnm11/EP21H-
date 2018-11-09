/* ************************************************************************ */
/*                                                                          */
/*                        Mentor Graphics Corporation                       */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: target.h                                                   */
/*  Description: Target specifics, header for example application.          */

#ifndef __TARGET_H__
#define __TARGET_H__

#include "v_target.h"
                                    /* This is a target dependent macro     */
                                    /* that should enable interrupts. Using */
                                    /* v_ctl_ints_restore() is just one way */
                                    /* of doing it, which works for this    */
                                    /* target.                              */
#define ENABLE_INTS()   v_ctl_ints_restore((v_imask)0)

#define CONFIG          (v_config_handle)

#define CLOCK_KHZ       (1000u)
                                    /* Volcano processing period is 25 ms
                                       in this example.                     */
#define HW_DELAY        (5000ul)

typedef v_uint16 time_type;

/* Function prototypes */
void      init_environment(void);
void      init_target(void);
v_uint16  hw_get_clock(void);
void      v_ctl_ints_restore(v_imask previous);
v_imask   v_ctl_ints_disable(void);

#define TEST_PASSED() while(1)
#define TEST_FAILED() while(1)
#define PET_WATCHDOG()

#endif /* __TARGET_H__ */
