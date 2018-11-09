/* ************************************************************************ */
/*                                                                          */
/*                         Mentor Graphics Corporation                      */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: v_subbus.h                                                 */
/*  Description: Contains sub bus specific definitions                      */

#ifndef __V_SUBBUS_H__
#define __V_SUBBUS_H__

#include "v_target.h"
#include "v_core.h"
#include "v_ioctl.h"

/* Sub bus interface error flags Table 7.1 LIN spec 2.1 */
#define V_SB_ERROR_IN_RESPONSE               (0x01u)
#define V_SB_SUCCESSFUL_TRANSFER             (0x02u)
#define V_SB_OVERRUN_ERROR                   (0x04u)
#define V_SB_GO_TO_SLEEP                     (0x08u)
#define V_SB_BUS_ACTIVITY                    (0x10u)
#define V_SB_EVENT_TRIGGERED_FRAME_COLLISION (0x20u)  /* master only */
#define V_SB_SAVE_CONFIGURATION              (0x40u)  /* slave only  */
#define V_SB_NO_RESPONSE                     (0x80u)  /* Not specified in LIN spec */

#define V_SB_UNKNOWN_FRAME_ID                (0xffu)

/* Sub bus interface IOCTL codes */
#define V_IOCTL_SB_READ_STATE                   ((v_ioctl_op)(V_IOCTL_SUB_BUS_COMMON_BASE + 0u))
#define V_IOCTL_SB_READ_AND_CLEAR_ERROR_FLAGS   ((v_ioctl_op)(V_IOCTL_SUB_BUS_COMMON_BASE + 1u))
#define V_IOCTL_SB_SEND_WAKEUP                  ((v_ioctl_op)(V_IOCTL_SUB_BUS_COMMON_BASE + 2u))
#define V_IOCTL_SB_SET_GPIO_TX_OUT_RX_IN        ((v_ioctl_op)(V_IOCTL_SUB_BUS_COMMON_BASE + 3u))
#define V_IOCTL_SB_SET_GPIO_TX_PIN              ((v_ioctl_op)(V_IOCTL_SUB_BUS_COMMON_BASE + 4u))
#define V_IOCTL_SB_GET_GPIO_RX_PIN              ((v_ioctl_op)(V_IOCTL_SUB_BUS_COMMON_BASE + 5u))

/* LIN 2.0 - Return values from ld_check_response() */
#define LD_SUCCESS                      (0x00u)
#define LD_NEGATIVE                     (0x01u)
#define LD_OVERWRITTEN                  (0x03u)

/* LIN 2.1 - master return values from ld_is_ready() */
#define LD_SERVICE_IDLE                 (0x00u)
#define LD_SERVICE_BUSY                 (0x10u)
#define LD_REQUEST_FINISHED             (0x20u)
#define LD_SERVICE_ERROR                (0x40u)

/* Return values for ld_read_by_id_callout */
#define LD_POSITIVE_RESPONSE            (0x00u)
#define LD_NEGATIVE_RESPONSE            (0x01u)
#define LD_NO_RESPONSE                  (0x02u)

/* Return values from v_ld_read_configuration */
#define LD_READ_OK                      (0x00u)
#define LD_LENGTH_TOO_SHORT             (0x01u)

/* Return values from v_ld_set_configuration */
#define LD_SET_OK                       (0x00u)
#define LD_LENGTH_NOT_CORRECT           (0x01u)
#define LD_DATA_ERROR                   (0x02u)

/* LIN diagnostics defintions */
#define LD_BROADCAST                    (0x7fu  )
#define LD_FUNCTIONAL_NAD               (0x7eu  )
#define LD_ANY_SUPPLIER                 (0x7fffu)
#define LD_ANY_FUNCTION                 (0xffffu)
#define LD_ANY_MESSAGE                  (0xffffu)

#define V_SB_MAX_FRAME_BYTES            (8u)

/* Master Request/Slave Response Frame byte positions in the foreground buffer */
#define LD_FG_NAD       (V_SB_MAX_FRAME_BYTES - 0u - 1u)      /* (0) */
#define LD_FG_PCI       (V_SB_MAX_FRAME_BYTES - 1u - 1u)      /* (1) */
#define LD_FG_SID       (V_SB_MAX_FRAME_BYTES - 2u - 1u)      /* (2) */
#define LD_FG_RSID      (V_SB_MAX_FRAME_BYTES - 2u - 1u)      /* (2) */
#define LD_FG_LEN       (V_SB_MAX_FRAME_BYTES - 2u - 1u)      /* (2) */
#define LD_FG_D1        (V_SB_MAX_FRAME_BYTES - 3u - 1u)      /* (3) */
#define LD_FG_D2        (V_SB_MAX_FRAME_BYTES - 4u - 1u)      /* (4) */
#define LD_FG_D3        (V_SB_MAX_FRAME_BYTES - 5u - 1u)      /* (5) */
#define LD_FG_D4        (V_SB_MAX_FRAME_BYTES - 6u - 1u)      /* (6) */
#define LD_FG_D5        (V_SB_MAX_FRAME_BYTES - 7u - 1u)      /* (7) */

/* Error code in the negative response of the slave (in the srf) */
#define ERROR_CODE_GENERAL_REJECT               (0x10u)
#define ERROR_CODE_SERVICE_NOT_SUPPORTED        (0x11u)
#define ERROR_CODE_SUB_FUNCTION_NOT_SUPPORTED   (0x12u)

/* Least/Most significant byte */
#define V_LSB(x)            ((v_uint8)(0xFFu & (x)))
#define V_MSB(x)            ((v_uint8)((x) >> 8))

/* *** Standard LIN API definitions *** */

/* LIN types */
#define l_bool              v_bool
#define l_u8                v_uint8
#define l_u16               v_uint16
#define l_ioctl_op          v_ioctl_op
#define l_ifc_handle        v_c_handle
#define l_irqmask           v_imask
#define l_schedule_handle   v_fmd_handle

typedef l_u8 V_RAM * V_RAM_PM   l_u8_ram_handle;

/* Macro layer for LIN API - VTP API compatibility */

/* Common master or slave */
#define l_sys_init()                v_sys_init(v_config_handle)

#define l_ifc_aux(c)                do { /* empty */ } while(0)

#define l_ifc_connect(c)            v_ctl_con(c)        /* only LIN 2.0 */
#define l_ifc_disconnect(c)         v_ctl_discon(c)     /* only LIN 2.0 */

#define l_ifc_read_status(c) \
    v_ctl_ioctl(c, V_IOCTL_SB_READ_AND_CLEAR_ERROR_FLAGS, (void *)0)

#define l_bool_rd(sig_handle) \
    v_rd_bool(sig_handle)

#define l_u8_rd(sig_handle) \
    v_rd_8(sig_handle)

#define l_u16_rd(sig_handle) \
    v_rd_16(sig_handle)

#define l_bytes_rd(sig_handle, start, count, dataptr) \
    v_rd_bytes_reversed(sig_handle, dataptr, count, start)

#define l_bool_wr(sig_handle, value) \
    v_wr_bool(sig_handle, value)

#define l_u8_wr(sig_handle, value) \
    v_wr_8(sig_handle, value)

#define l_u16_wr(sig_handle, value) \
    v_wr_16(sig_handle, value)

#define l_bytes_wr(sig_handle, start, count, dataptr) \
    v_wr_bytes_reversed(sig_handle, dataptr, count, start)

#define l_flg_tst(flag_handle) \
    v_test_flag(flag_handle)

#define l_flg_clr(flag_handle) \
    v_clear_flag(flag_handle)

#define l_ifc_init(c) \
    v_ctl_init(c)

#define l_ifc_ioctl(c, ioctl_op, pv) \
    v_ctl_ioctl(c, ioctl_op, pv)

#define l_ifc_rx(c) \
    v_ctl_rxint(c)

#define l_ifc_tx(c) \
    v_ctl_txint(c)

/* Master related */
#define l_sch_tick(c)               v_sb_tick(c)

#define l_sch_set(c, schedule, entry) \
    v_l_sch_set(c, schedule, entry)

#define l_ifc_goto_sleep(c) \
    (void)v_ctl_ioctl(c, V_IOCTL_COMMON_SET_SLEEP, (void *)0)

#define l_ifc_wake_up(c) \
    (void)v_ctl_ioctl(c, V_IOCTL_COMMON_SET_WAKE, (void *)0)

#define ld_assign_frame_id(c, nad, supplier_id, message_id, pid) \
    v_ld_assign_frame_id(c, nad, supplier_id, message_id, pid)

#define ld_assign_frame_id_range(c, nad, start_index, pids) \
    v_ld_assign_frame_id_range(c, nad, start_index, pids)

#define ld_assign_NAD(c, initial_nad, supplier_id,  function_id, new_nad) \
    v_ld_assign_NAD(c, initial_nad, supplier_id, function_id, new_nad)

#define ld_save_configuration(c, nad) \
    v_ld_save_configuration(c, nad)

#define ld_conditional_change_NAD(c, nad, id, byte, mask, invert, new_nad) \
    v_ld_conditional_change_NAD(c, nad, id, byte, mask, invert, new_nad)

#define ld_read_by_id(c, nad, supplier_id, function_id, id, data) \
    v_ld_read_by_id(c, nad, supplier_id, function_id, id, data)

#define ld_is_ready(c) \
    v_ld_is_ready(c)

#define ld_check_response(c, rsid, error_code) \
    v_ld_check_response(c, rsid, error_code)

#define ld2_m_send_req(c, data) \
    v_ld2_m_send_req(c, data)

/* Slave related */
#define ld_read_configuration(c, data, length) \
    v_ld_read_configuration(c, data, length)

#define ld_set_configuration(c, data, length) \
    v_ld_set_configuration(c, data, length)

/* ************************************************************************ */
/*         Prototypes                                                       */
/* ************************************************************************ */
/*         Diagnostic class 2 API for master nodes                          */
/* ************************************************************************ */
V_API_FN_PREFIX void V_API_FN_SUFFIX v_l_sch_set(v_c_handle c,
    v_fmd_handle fmd, v_uint8 entry);

V_API_FN_PREFIX void V_API_FN_SUFFIX v_ld_assign_frame_id(v_c_handle c,
    v_uint8 nad, v_uint16 supplier_id,v_uint16 message_id, v_uint8 pid);

V_API_FN_PREFIX void V_API_FN_SUFFIX v_ld_assign_frame_id_range(v_c_handle c,
    v_uint8 nad, v_uint8 start_index, const v_uint8* const pids);

V_API_FN_PREFIX void V_API_FN_SUFFIX v_ld_assign_NAD(v_c_handle c,
    v_uint8 initial_nad, v_uint16 supplier_id,  v_uint16 function_id, v_uint8 new_nad);

V_API_FN_PREFIX void V_API_FN_SUFFIX v_ld_save_configuration(v_c_handle c, v_uint8 nad);

V_API_FN_PREFIX void V_API_FN_SUFFIX v_ld_conditional_change_NAD(v_c_handle c,
    v_uint8 nad, v_uint8 id, v_uint8 byte, v_uint8 mask, v_uint8 invert, v_uint8 new_nad);

V_API_FN_PREFIX void V_API_FN_SUFFIX v_ld_read_by_id(v_c_handle c,
    v_uint8 nad, v_uint16 supplier_id, v_uint16 function_id, v_uint8 id, v_uint8* const data);

V_API_FN_PREFIX v_uint8 V_API_FN_SUFFIX v_ld_is_ready(v_c_handle c);

V_API_FN_PREFIX void V_API_FN_SUFFIX v_ld_check_response(v_c_handle c,
    v_uint8* const rsid, v_uint8* const error_code);

V_API_FN_PREFIX void V_API_FN_SUFFIX v_ld2_m_send_req(v_c_handle c, v_uint8* const data);

/* ************************************************************************ */
/*         Diagnostic class 2 API for slave nodes                           */
/* ************************************************************************ */

V_API_FN_PREFIX v_uint8 v_ld_read_configuration (v_c_handle c,
    v_uint8* const data, v_uint8* const length);

V_API_FN_PREFIX v_uint8 v_ld_set_configuration  (v_c_handle c,
    const v_uint8* const data, v_uint16 length);

/* Callout functions  */
extern l_u8   ld_read_by_id_callout(l_ifc_handle iii, l_u8 id, l_u8_ram_handle buf);
extern l_bool l_get_userdef_req(l_ifc_handle iii, l_u8_ram_handle mrf, l_u8_ram_handle srf);

/* external variable */
extern const l_u8 LD_SERIAL[4]; /* Shall be a 4-byte serial number         */

#endif /* __V_SUBBUS_H__ */
