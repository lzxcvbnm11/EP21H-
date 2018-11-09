/* ************************************************************************ */
/*                                                                          */
/*                         Mentor Graphics Corporation                      */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: v_ioctl.h                                                  */
/*       Author: MGC                                                        */
/*  Description: IOCTL function related definitions                         */
/*                                                                          */

#ifndef __V_IOCTL_H__
#define __V_IOCTL_H__

/* the following definitions define the core ioctl functions. operations    */
/* are grouped by controller in banks of 16 as follows:                     */

#define V_IOCTL_CAN_CTRL_COMMON_BASE    (0x00u)
#define V_IOCTL_SUB_BUS_COMMON_BASE     (0x20u)
#define V_IOCTL_CAN_CTRL_SPECIFIC_BASE  (0x30u)
#define V_IOCTL_SUB_BUS_SPECIFIC_BASE   (0x40u)

#define V_IOCTL_COMMON_SET_SLEEP        (V_IOCTL_CAN_CTRL_COMMON_BASE)
#define V_IOCTL_COMMON_SET_WAKE         (V_IOCTL_CAN_CTRL_COMMON_BASE +  1u)
#define V_IOCTL_COMMON_CHECK_SLEEP      (V_IOCTL_CAN_CTRL_COMMON_BASE +  2u)
#define V_IOCTL_COMMON_CHECK_BUSOFF     (V_IOCTL_CAN_CTRL_COMMON_BASE +  3u)
#define V_IOCTL_COMMON_CHECK_TX_WARN    (V_IOCTL_CAN_CTRL_COMMON_BASE +  4u)
#define V_IOCTL_COMMON_CHECK_TX_ERROR   (V_IOCTL_CAN_CTRL_COMMON_BASE +  5u)
#define V_IOCTL_COMMON_CHECK_RX_WARN    (V_IOCTL_CAN_CTRL_COMMON_BASE +  6u)
#define V_IOCTL_COMMON_CHECK_RX_ERROR   (V_IOCTL_CAN_CTRL_COMMON_BASE +  7u)
#define V_IOCTL_COMMON_TX_ERR_COUNT     (V_IOCTL_CAN_CTRL_COMMON_BASE +  8u)
#define V_IOCTL_COMMON_RX_ERR_COUNT     (V_IOCTL_CAN_CTRL_COMMON_BASE +  9u)
#define V_IOCTL_COMMON_BUSOFF_COUNTER   (V_IOCTL_CAN_CTRL_COMMON_BASE + 10u)

#endif /* __V_IOCTL_H__ */

