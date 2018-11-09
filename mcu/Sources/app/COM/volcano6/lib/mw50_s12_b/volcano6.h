/* ************************************************************************ */
/*                                                                          */
/*                         Mentor Graphics Corporation                      */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: volcano6.h                                                 */
/*  Description: Contains prototypes for Volcano 6 API.                     */

#ifndef __VOLCANO6_H__
#define __VOLCANO6_H__

#include "v_target.h"
#include "v_core.h"

/* Controller calls ******************************************************* */
V_OVERLAY V_API_FN_PREFIX v_bool        V_API_FN_SUFFIX v_ctl_active(v_c_handle c);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_ctl_con(v_c_handle c);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_ctl_discon(v_c_handle c);
V_OVERLAY V_API_FN_PREFIX v_uint8       V_API_FN_SUFFIX v_ctl_init(v_c_handle c);
V_OVERLAY V_API_FN_PREFIX v_uint16      V_API_FN_SUFFIX v_ctl_ioctl(v_c_handle c, v_ioctl_op op, void *p);

/* Flag calls ************************************************************* */
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_clear_flag(v_fl_handle f);
V_OVERLAY V_API_FN_PREFIX v_bool        V_API_FN_SUFFIX v_test_flag(v_fl_handle f);

/* Frame mode calls ******************************************************* */
V_OVERLAY V_API_FN_PREFIX v_fmd_handle  V_API_FN_SUFFIX v_fmd_get(v_c_handle c);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_fmd_set(v_c_handle c, v_fmd_handle fmd);
V_OVERLAY V_API_FN_PREFIX v_bool        V_API_FN_SUFFIX v_fmd_pend(v_c_handle c);

/* System and processing calls ******************************************** */
V_OVERLAY V_API_FN_PREFIX v_uint8       V_API_FN_SUFFIX v_sys_init(v_cfg_handle c);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_input(v_cfg_handle c);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_output(v_cfg_handle c);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_gateway(v_cfg_handle c);
V_OVERLAY V_API_FN_PREFIX v_uint8       V_API_FN_SUFFIX v_sb_tick(v_c_handle c);

/* Signal Read/Write function calls *************************************** */
V_OVERLAY V_API_FN_PREFIX v_uint32      V_API_FN_SUFFIX v_rd_32(v_s_32_handle s);
V_OVERLAY V_API_FN_PREFIX v_uint16      V_API_FN_SUFFIX v_rd_16(v_s_16_handle s);
V_OVERLAY V_API_FN_PREFIX v_uint8       V_API_FN_SUFFIX v_rd_8(v_s_8_handle s);
V_OVERLAY V_API_FN_PREFIX v_bool        V_API_FN_SUFFIX v_rd_bool(v_s_bool_handle s);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_rd_bytes(v_s_bytes_handle s, v_uint8 *dest, v_uint8 n, v_uint8 o);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_rd_bytes_reversed(v_s_bytes_handle s, v_uint8 *dest, v_uint8 n, v_uint8 o);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_wr_32(v_s_32_handle s, v_uint32 v);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_wr_16(v_s_16_handle s, v_uint16 v);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_wr_8(v_s_8_handle s, v_uint8 v);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_wr_bool(v_s_bool_handle s, v_bool v);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_wr_bytes(v_s_bytes_handle s, const v_uint8 *src, v_uint8 n, v_uint8 o);
V_OVERLAY V_API_FN_PREFIX void          V_API_FN_SUFFIX v_wr_bytes_reversed(v_s_bytes_handle s, const v_uint8 *src, v_uint8 n, v_uint8 o);

/* Receive, transmit and busoff interrupt calls *************************** */
V_API_FN_PREFIX v_imf_handle            V_API_FN_SUFFIX v_ctl_rxint(v_c_handle c);
V_API_FN_PREFIX v_imf_handle            V_API_FN_SUFFIX v_ctl_txint(v_c_handle c);
V_API_FN_PREFIX void                    V_API_FN_SUFFIX v_ctl_busoffint(v_c_handle c);

/* Immediate frame calls ************************************************** */
V_OVERLAY V_API_FN_PREFIX v_bool        V_API_FN_SUFFIX v_vct_ubit_rd(v_s_handle s);
V_API_FN_PREFIX void                    V_API_FN_SUFFIX v_imf_tx(v_imf_handle f);
V_API_FN_PREFIX v_bool                  V_API_FN_SUFFIX v_imf_rx(v_imf_handle f);
V_API_FN_PREFIX v_uint8                 V_API_FN_SUFFIX v_imf_queued(v_imf_handle f);

/* Activable frame calls ************************************************** */
V_API_FN_PREFIX void                    V_API_FN_SUFFIX v_activate_frm(v_act_handle f);
V_API_FN_PREFIX void                    V_API_FN_SUFFIX v_deactivate_frm(v_act_handle f);

/* User-provided interrupt enable/disable routines ************************ */
V_API_FN_PREFIX v_imask                 V_API_FN_SUFFIX v_ctl_ints_disable(void);
V_API_FN_PREFIX void                    V_API_FN_SUFFIX v_ctl_ints_restore(v_imask save_imask);

/* OSEK NM callout routine  *********************************************** */
V_API_FN_PREFIX void                    V_API_FN_SUFFIX v_nm_message_received(v_nwm_recdata* nwm_frame);

#define v_ubit_rd(s)                    v_vct_ubit_rd((v_s_handle)(s))

#endif /* __VOLCANO6_H__ */
