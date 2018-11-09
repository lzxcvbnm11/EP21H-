/* ************************************************************************ */
/*                                                                          */
/*                         Mentor Graphics Corporation                      */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: v_sci12lin.h                                               */
/*  Description: Contains user visible items relating to the device-driver  */
/*               driver implementation for:                                 */
/*               HC12(X) UART                                               */
/*               LIN                                                        */

#ifndef __V_SCI12LIN_H__
#define __V_SCI12LIN_H__
#include "v_ioctl.h"

                                    /* Device-driver functions              */
extern v_bool       v_sci12lin_send_frame(v_c_handle c, V_NVRAM void * V_NVRAM_PM tx_frame);
extern void         v_sci12lin_send_frames(v_c_handle c, v_frame_map * tx_completion, v_frame_map * tx_overrun);
extern v_bool       v_sci12lin_read_frame(v_c_handle c, V_NVRAM void * V_NVRAM_PM rx_frame);
extern void         v_sci12lin_read_frames(v_c_handle c);
extern v_imf_handle v_sci12lin_tx_interrupt_handler(v_c_handle c);
extern v_bool       v_sci12lin_tx_pending(v_c_handle c);
extern void         v_sci12lin_discard_tx_frames(v_c_handle c);
extern void         v_sci12lin_set_mode(v_c_handle c, v_fmd_handle mode);
extern v_imf_handle v_sci12lin_rx_interrupt_handler(v_c_handle c);
extern v_uint8      v_sci12lin_init_controller(v_c_handle c);
extern void         v_sci12lin_connect_controller(v_c_handle c);
extern void         v_sci12lin_disconnect_controller(v_c_handle c);
extern v_bool       v_sci12lin_controller_active(v_c_handle c);
extern v_uint16     v_sci12lin_controller_ioctl(v_c_handle c, v_ioctl_op op, void *p);
extern v_uint8      v_sci12lin_check_frame(v_c_handle c, V_NVRAM void * V_NVRAM_PM tx_frame);

#define V_IOCTL_SB_NORMAL_CPU_CLK (V_IOCTL_SUB_BUS_SPECIFIC_BASE)
#define V_IOCTL_SB_ALTERNATE_CPU_CLK (V_IOCTL_SUB_BUS_SPECIFIC_BASE + 1)

#endif /* __V_SCI12LIN_H__ */
