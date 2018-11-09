/* ************************************************************************ */
/*                                                                          */
/*                         Mentor Graphics Corporation                      */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: v_msc12s.h                                                 */
/*  Description: Contains user visible items relating to the msCAN12s       */
/*               (Star12) controller                                        */

#ifndef __V_MSC12S_H__
#define __V_MSC12S_H__

#include "v_ioctl.h"

                                    /* device driver functions              */
extern v_bool       v_msc12s_send_frame(v_c_handle c, voidnv_handle tx_frame);
extern void         v_msc12s_send_frames(v_c_handle c, v_frame_map * tx_completion, v_frame_map * tx_overrun);
extern v_bool       v_msc12s_read_frame(v_c_handle c, voidnv_handle rx_frame);
extern void         v_msc12s_read_frames(v_c_handle c);
extern v_imf_handle v_msc12s_tx_interrupt_handler(v_c_handle c);
extern v_bool       v_msc12s_tx_pending(v_c_handle c);
extern void         v_msc12s_set_mode(v_c_handle c, v_fmd_handle mode);
extern v_imf_handle v_msc12s_rx_interrupt_handler(v_c_handle c);
extern v_uint8      v_msc12s_init_controller(v_c_handle c);
extern void         v_msc12s_connect_controller(v_c_handle c);
extern void         v_msc12s_disconnect_controller(v_c_handle c);
extern v_bool       v_msc12s_controller_active(v_c_handle c);
extern v_uint16     v_msc12s_controller_ioctl(v_c_handle c, v_ioctl_op op, void * p);
extern v_uint8      v_msc12s_check_frame(v_c_handle c, voidnv_handle frame);
extern void         v_msc12s_busoff_interrupt_handler(v_c_handle c);

#define V_IOCTL_MSCAN12S_SET_CANRIER_BITS (V_IOCTL_CAN_CTRL_SPECIFIC_BASE)
#define V_IOCTL_MSCAN12S_CLR_CANRIER_BITS (V_IOCTL_CAN_CTRL_SPECIFIC_BASE + 1u)
#define V_IOCTL_MSCAN12S_CHK_CANRFLG_BITS (V_IOCTL_CAN_CTRL_SPECIFIC_BASE + 2u)
#define V_IOCTL_MSCAN12S_CHK_SYNCH        (V_IOCTL_CAN_CTRL_SPECIFIC_BASE + 3u)

#endif /* __V_MSC12S_H__ */
