/* ************************************************************************ */
/*                                                                          */
/*                    Mentor Graphics Corporation                           */
/*                        All rights reserved                               */
/*                                                                          */
/* ************************************************************************ */
/*                                                                          */
/*         File: v_nwm.c                                                    */
/*  Description: This file should be compiled and linked with the           */
/*               application software.                                      */
/*               Note that the application programmer is responsible for    */
/*               the initialisation of the NWM instances and the NWM        */
/*               parameters.                                                */
/*                                                                          */
/*         Note: The template declarations below show the declarations to   */
/*               be made for a node with one slave instance. For this       */
/*               type of node, only the names of the different handles have */
/*               to be changed according to the names in 'v_hand.h'. For    */
/*               other types of nodes the declarations should be further    */
/*               modified, see the document 'Network Management API         */
/*               Specification'.                                            */
/*                                                                          */
/****************************************************************************/
/** include files **/

#ifndef VOLCANO_HEADER
    #include "volcano6.h" /* Backward compatibility */
#else
    #include VOLCANO_HEADER 
#endif

#include "v_nwm.h"
#include "v_hand.h"
//s#include "nwm_hello.h"
#include <stddef.h>

/****************************************************************************/
/* Define the required arrays of network interfaces. There should be one    */
/* array for each network management instance.                              */
/****************************************************************************/
static const v_c_handle the_controllers[NUMBER_OF_CTL] = { PACM_HSC4_handle };

/****************************************************************************/
/* Define the required arrays of the received WakeNetwork signals. There    */
/* should be one array for each master or secondary master NWM instance.    */
/****************************************************************************/

/* We don't use master or secondary master instances in this application */

/****************************************************************************/
/* Define the required arrays of the received KeepNetwork signals. There    */
/* should be one array for each master or secondary master NWM instance.    */
/****************************************************************************/

/* We don't use master or secondary master instances in this application */

/****************************************************************************/
/* Define the required arrays of the flags attached to the received Wake-   */
/* Network signals. There should be one array for each master or secondary  */
/* master network management instance.                                      */
/****************************************************************************/

/* We don't use master or secondary master instances in this application */

/****************************************************************************/
/* Define the required arrays of the flags attached to the received Keep-   */
/* Network signals. There should be one array for each master or secondary  */
/* master network management instance.                                      */
/****************************************************************************/

/* We don't use master or secondary master instances in this application */

/****************************************************************************/
/* Define the required frame mode arrays. The length of the arrays depends  */
/* on the number of controllers for the instance.                           */
/****************************************************************************/
/* For a slave instance two frame modes (normal and silent) are used */
static const v_fmd_handle normal_frame_modes[NUMBER_OF_CTL] = { FM_Normal_HS_handle };
static const v_fmd_handle silent_frame_modes[NUMBER_OF_CTL] = { FM_Silent_HS_handle };


/****************************************************************************/
/* Define the RAM variables for each network management instance.           */
/****************************************************************************/
static v_nwm_ram_variables ram_variables;

/****************************************************************************/
/* Each master and secondary nwm instance needs specific RAM variables.     */
/* Define these RAM varibles here.                                          */
/****************************************************************************/

/* We don't use master or secondary master instances in this application */

/****************************************************************************/
/* For each master and secondary master instance a structure of type        */
/* v_nwm_master_instance should be defined.                                 */
/****************************************************************************/

/* We don't use master or secondary master instances in this application */

/****************************************************************************/
/* For each slave and secondary master instance a structure of type         */
/* v_nwm_slave_instance should be defined.                                  */
/****************************************************************************/
/* This hello example does not make use of a secondary master. */
/* Therefore the secondary master members are initialised to NULL. */
static v_nwm_slave_instance slave_specific_structure = {
    NULL,                   /* sec_master_fixed_frame */
    NULL,                   /* sec_master_network_mode */
    NULL,                   /* sec_master_signal_config_id */
    wake_network_PACM_handle,    /* wake_network_signal */
    keep_network_PACM_handle     /* keep_network_signal*/
};

/****************************************************************************/
/* For each instance a structure of type v_nwm_instance should be defined.  */
/****************************************************************************/
v_nwm_instance nwm_slave_instance = {
    &slave_specific_structure,      /* slave */
    NULL,                           /* master */
    &ram_variables,                 /* ram_variables */
    the_controllers,                /* controllers */
    GW_HSC4_FrI01_handle, // master_fixed_frame_handle,      /* master_fixed_frame */
    network_mode_handle,            /* network_mode */
    normal_frame_modes,             /* normal_fmd */
    silent_frame_modes,             /* silent_fmd */
    signal_config_id_handle,        /* signal_config_id */
    local_signal_config_id_handle,  /* local_signal_config_id */
    V_NWM_SLAVE,                    /* instance_type */
    NUMBER_OF_CTL                   /* num_of_controllers */
};

/****************************************************************************/
/* Define and initialise an array which contains all NWM instances used.    */
/* This array will be passed to the NWM init function.                      */
/****************************************************************************/
const v_nwm_instance_handle nwm_instances[NUMBER_OF_NWM_INSTANCES] = 
                                                    { &nwm_slave_instance };

/****************************************************************************/
/* If a slave or secondary master instance is used a structure of the type  */
/* v_nwm_slave_parameters with the name v_nwm_the_slave_parameters should   */
/* be defined.                                                              */
/****************************************************************************/
const v_nwm_slave_parameters v_nwm_the_slave_parameters = {
    communication_timeout_time_slave_handle,
    wait_for_network_sleep_time_slave_handle,
    wakeup_pending_time_slave_handle,
    keep_network_timeout_time_slave_handle,
    wakeup_network_signal_time_slave_handle,//wake_network_signal_time_slave_handle,
    wakeup_network_time_slave_handle,
    busoff_max_handle,
    busoff_time_handle,
    busoff_wait_time_handle,
    busoff_decrement_time_handle,
    stay_in_busoff_handle,
    stay_in_expulsion_handle
};

/****************************************************************************/
/* If a master or secondary master instance is used a structure of the type */
/* v_nwm_master_parameters with the name v_nwm_the_master_parameters should */
/* be defined.                                                              */
/****************************************************************************/

/* We don't use master or secondary master instances in this application */

/****************************************************************************/
/* If a secondary master instance is used a structure of the type           */
/* v_nwm_sec_master_parameters with the name v_nwm_the_sec_master_parameters*/
/* should be defined.                                                       */
/****************************************************************************/

/* We don't use secondary master instances in this application */











