/* ************************************************************************ */
/*                                                                          */
/*                  Mentor Graphics Corporation                             */
/*                      All rights reserved                                 */
/*                                                                          */
/* ************************************************************************ */


/*         File: nwm_core.h                                                 */
/*  Description: This file contains various NWM type definitions.           */
/*                                                                          */
/****************************************************************************/

#ifndef __NWM_CORE_H__
#define __NWM_CORE_H__

/*lint -save -e960 -e961 */
/*Turn the VTP-related special MISRA2 warning messages off*/
#include "volcano6.h"
/*lint -restore*/

/****************************************************************************/
/* Network Management state type definition.                                */
/*                                                                          */
/****************************************************************************/
typedef enum {
    V_NWM_STARTUP = 1,
    V_NWM_NORMAL,
    V_NWM_BUSOFF,
    V_NWM_BUSOFF_WAIT,
    V_NWM_NETWORK_SLEEP,
    V_NWM_WAIT_FOR_NETWORK_SLEEP,
    V_NWM_WAKEUP_NETWORK,
    V_NWM_WAKEUP_PENDING,
    V_NWM_EXPULSION,
    V_NWM_ISOLATED,
    V_NWM_STOPPED
} v_nwm_state;

/****************************************************************************/
/* Network Management Slave Parameters type definition. This type contains  */
/* the NWM parameters required for a network management instance of the     */
/* type slave.                                                              */
/****************************************************************************/
typedef struct {
    v_s_16_handle   communication_timeout_time_slave;
    v_s_8_handle    wait_for_network_sleep_time_slave;
    v_s_8_handle    wakeup_pending_time_slave;
    v_s_16_handle   keep_network_timeout_time_slave;
    v_s_8_handle    wake_network_signal_time_slave;
    v_s_8_handle    wakeup_network_time_slave;
    v_s_8_handle    busoff_max;
    v_s_8_handle    busoff_time;
    v_s_16_handle   busoff_wait_time;
    v_s_16_handle   busoff_decrement_time;
    v_s_bool_handle stay_in_busoff;
    v_s_bool_handle stay_in_expulsion;
} v_nwm_slave_parameters;

/****************************************************************************/
/* Network Management Master Parameters type definition. This type contains */
/* the NWM parameters required for a network management instance of the     */
/* type master.                                                             */
/****************************************************************************/
typedef struct {
    v_s_8_handle    monitoring_timeout_time_master;
    v_s_8_handle    wait_for_network_sleep_time_master;
    v_s_8_handle    wakeup_pending_time_master;
    v_s_8_handle    keep_net_alive_time_master;
    v_s_8_handle    fixed_frame_normal_period;
    v_s_8_handle    fixed_frame_startup_period;
    v_s_8_handle    busoff_max;
    v_s_16_handle   busoff_wait_time;
    v_s_16_handle   busoff_decrement_time;
} v_nwm_master_parameters;

/****************************************************************************/
/* Network Management Secondary Master Parameters type definition. This     */
/* type contains the NWM parameters required for a network management       */
/* instance of the type secondary master.                                   */
/****************************************************************************/
typedef struct {
    v_s_8_handle    master_timeout_time_sec_master;
    v_s_8_handle    startup_time_sec_master;
    v_s_8_handle    wakeup_pending_time_sec_master;
} v_nwm_sec_master_parameters;

/****************************************************************************/
/* Network Management RAM variables type definition. This type contains the */
/* RAM variables which are common for all types of instances.               */
/*                                                                          */
/****************************************************************************/
typedef struct {
    v_uint16        nwm_timer;
    v_uint16        keep_network_timer;
    v_uint16        busoff_timer;
    v_nwm_state     current_state;
    v_uint8         busoff_counter;
    v_nwm_state     state_before_busoff;
    v_bool          wakeup_requested;
    v_bool          stop_requested;
    v_bool          was_busoff;
} v_nwm_ram_variables, *v_nwm_ram_variables_handle;

/****************************************************************************/
/* Network Management Master RAM variables type definition. This type       */
/* contains the RAM variables which are master instance specific.           */
/*                                                                          */
/****************************************************************************/
typedef struct {
    v_uint32    node_status;
    v_uint16    *node_status_timer; /* Array */
    v_uint16    fixed_frame_timer;
    v_bool      leave_startup;
} v_nwm_master_ram_variables, *v_nwm_master_ram_variables_handle;

/****************************************************************************/
/* Network Management Secondary Master RAM variables type definition. This  */
/* type contains the RAM variables which are secondary master instance      */
/* specific.                                                                */
/*                                                                          */
/****************************************************************************/
typedef struct {
    v_uint16    sec_master_timer;
    v_bool      is_slave;
    v_bool      enter_startup;
} v_nwm_sec_master_ram_variables, *v_nwm_sec_master_ram_variables_handle;

/****************************************************************************/
/* Network Management instance type type definition. This type is used to   */
/* specify the kind of a NWM instance.                                      */
/*                                                                          */
/****************************************************************************/
typedef enum {
    V_NWM_SLAVE = 1,
    V_NWM_MASTER,
    V_NWM_SEC_MASTER
} v_nwm_instance_type;

/****************************************************************************/
/* Network Management slave instance type definition. This type contains    */
/* the slave specific part of a NWM instance.                               */
/*                                                                          */
/****************************************************************************/
typedef const struct {
    v_imf_handle        sec_master_fixed_frame;
    v_s_8_handle        sec_master_network_mode;
    v_s_16_handle       sec_master_signal_config_id;
    v_s_bool_handle     wake_network_signal;
    v_s_bool_handle     keep_network_signal;
} v_nwm_slave_instance, *v_nwm_slave_instance_handle;

/****************************************************************************/
/* Network Management master instance type definition. This type contains   */
/* the master specific part of a NWM instance.                              */
/*                                                                          */
/****************************************************************************/
typedef const struct {
    v_fl_handle                             diag_req_flag;
    const v_s_bool_handle                   *wake_network_signals; /* Array */
    const v_s_bool_handle                   *keep_network_signals; /* Array */
    const v_fl_handle                       *wake_network_flags; /* Array */
    const v_fl_handle                       *keep_network_flags; /* Array */
    v_nwm_master_ram_variables_handle       master_ram_variables;
    v_nwm_sec_master_ram_variables_handle   sec_master_ram_variables;
    v_uint8                                 num_of_slaves;
    v_uint8                                 num_of_wakeup_slaves;
} v_nwm_master_instance, *v_nwm_master_instance_handle;

/****************************************************************************/
/* Network Management instance type definition. This type contains the      */
/* common (common for Slave, Master and Secondary Master instances) part of */
/* a NWM instance.                                                          */
/*                                                                          */
/****************************************************************************/
typedef const struct {
    const v_nwm_slave_instance_handle   slave;
    const v_nwm_master_instance_handle  master;
    v_nwm_ram_variables_handle          ram_variables;
    const v_c_handle                    *controllers; /* Array */
    v_imf_handle                        master_fixed_frame;
    v_s_8_handle                        network_mode;
    const v_fmd_handle                  *normal_fmd; /* Array */
    const v_fmd_handle                  *silent_fmd; /* Array */
    v_s_16_handle                       signal_config_id;
    v_s_16_handle                       local_signal_config_id;
    v_nwm_instance_type                 instance_type;
    v_uint8                             num_of_controllers;
} v_nwm_instance, *v_nwm_instance_handle;

/****************************************************************************/
/* Network Management callout for calling the ioctl function. This callout  */
/* is introduced for making the NM compatible with older VTP versions where */
/* op was 8 bits.                                                           */
/****************************************************************************/
v_uint16 v_nmco_ioctl(v_c_handle c, v_uint16 op);

#endif /* __NWM_CORE_H__ */
