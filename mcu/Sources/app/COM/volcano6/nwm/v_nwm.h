/* ************************************************************************** */
/*                                                                            */
/*                    Mentor Graphics Corporation                             */
/*                        All rights reserved                                 */
/*                                                                            */
/* ************************************************************************** */

/*         File: v_nwm.h                                                    */
/*  Description: Contains prototypes for the Network Management API.        */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef __V_NWM_H__
#define __V_NWM_H__

#include "nwm_core.h"



/* The number of network mangement instances. */
/* In this application only one instance is used. */
#define NUMBER_OF_NWM_INSTANCES 1

/* There should be a constant defining the number of controllers for each */
/* NWM instance. In this application we have only one NWM instance and it */
/* has one controller. */
#define NUMBER_OF_CTL 1

/* This array contains all NWM instances and is defined in v_nwm.c */
extern const v_nwm_instance_handle nwm_instances[NUMBER_OF_NWM_INSTANCES];

/* This is the only NWM instance used in this application */
extern v_nwm_instance nwm_slave_instance;


/****************************************************************************/
/* Network Management API functions                                         */
/*                                                                          */
/****************************************************************************/

/* ************************************************************************ */
/*  function   : v_nwm_init                                                 */
/*  description: This function initialises the Network Management module.   */
/*  input      : c          Volcano is initialised with this configuration. */
/*               nwm        This array should contain all Network           */
/*                          Management instances in the node.               */
/*               num_of_nwm The number of Network Management instances      */
/*                          in the node.                                    */
/*  output     :                                                            */
/*  return     : 0          The initialisation succeeded.                   */
/*               0x01-0x7F  Volcano initialisation failed.                  */
/*               0x80-      Controller initialisation failed.               */
/*  notes      :                                                            */
/*                                                                          */
/* ************************************************************************ */
extern v_uint8 v_nwm_init(  v_cfg_handle c,
                            const v_nwm_instance_handle nwm[ ],
                            const v_uint8 num_of_nwm );

/* ************************************************************************ */
/*  function   : v_nwm_slave_processing                                     */
/*  description: This function performs the processing of the slave Network */
/*               Management instance nwm.                                   */
/*  input      : nwm    The slave Network Management instance.              */
/*  output     :                                                            */
/*  return     :                                                            */
/*  notes      : The instance nwm must be of type Slave.                    */
/*                                                                          */
/* ************************************************************************ */
extern void v_nwm_slave_processing ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_master_processing                                    */
/*  description: This function performs the processing of the master        */
/*               Network Management instance nwm.                           */
/*  input      : nwm    The master Network Management instance.             */
/*  output     :                                                            */
/*  return     : True   NWM Fixed frame was transmitted.                    */
/*               False  NWM Fixed frame was not transmitted.                */
/*  notes      : The instance nwm must be of type Master.                                                            */
/*                                                                          */
/* ************************************************************************ */
extern v_bool v_nwm_master_processing ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_sec_master_processing                                */
/*  description: This function performs the processing of the secondary     */
/*               master Network Management instance nwm.                    */
/*  input      : nwm    The secondary master Network Management instance.   */
/*  output     :                                                            */
/*  return     : True   NWM Fixed frame was transmitted.                    */
/*               False  NWM Fixed frame was not transmitted.                */
/*  notes      : The instance nwm must be of type Secondary Master.         */
/*                                                                          */ 
/*               The return value is only meaningful if the instance nwm    */
/*               currently is acting as a master.                           */
/*                                                                          */
/* ************************************************************************ */
extern v_bool v_nwm_sec_master_processing ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_net_com_req                                          */
/*  description: This function should be used to make a network communica-  */
/*               tion request for the Network Management instance nwm.      */
/*  input      : nwm    The Network Management instance.                    */
/*  output     :                                                            */
/*  return     :                                                            */
/*  notes      :                                                            */
/*                                                                          */
/* ************************************************************************ */
extern void v_nwm_net_com_req ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_get_state                                            */
/*  description: This function returns the current state of the Network     */
/*               Management instance nwm.                                   */
/*  input      : nwm    The Network Management instance.                    */
/*  output     :                                                            */
/*  return     : The current state of the Network Management instance nwm.  */
/*  notes      :                                                            */
/*                                                                          */
/* ************************************************************************ */
extern v_nwm_state v_nwm_get_state ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_secondary_master_is_slave                            */
/*  description: This function returns the current role (slave or master)   */
/*               for the secondary master instance nwm.                     */
/*  input      : nwm    The secondary master Network Management instance.   */
/*  output     :                                                            */
/*  return     : True   The instance nwm is currently a slave.              */
/*               False  The instance nwm is currently a master.             */
/*  notes      : This function should only be used for instances of the     */
/*               type secondary master.                                     */
/*                                                                          */
/* ************************************************************************ */
extern v_bool v_nwm_secondary_master_is_slave ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_get_busoff_counter                                   */
/*  description: This function returns the busoff counter of the Network    */
/*               Management instance nwm.                                   */
/*  input      : nwm    The Network Management instance.                    */
/*  output     :                                                            */
/*  return     :  The current value of the busoff counter in the Network    */
/*                Management instance nwm.                                  */
/*  notes      :                                                            */
/*                                                                          */
/* ************************************************************************ */
extern v_uint8 v_nwm_get_busoff_counter ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_reset_busoff_counter                                 */
/*  description: This function resets the busoff counter to zero in the     */
/*               Network Management instance nwm.                           */
/*  input      : nwm    The Network Management instance.                    */
/*  output     :                                                            */
/*  return     :                                                            */
/*  notes      :                                                            */
/*                                                                          */
/* ************************************************************************ */
extern void v_nwm_reset_busoff_counter ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_stop                                                 */
/*  description: This function disconnects the instance nwm from the        */
/*               network and transfer it to the state "Stopped".            */
/*  input      : nwm    The Network Management instance.                    */
/*  output     :                                                            */
/*  return     :                                                            */
/*  notes      :                                                            */
/*                                                                          */
/* ************************************************************************ */
extern void v_nwm_stop ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_resume                                               */
/*  description: This function connects the instance nwm to the             */
/*               network and transfer it from the state stopped             */
/*               to the state network sleep.                                */
/*  input      : nwm    The Network Management instance.                    */
/*  output     :                                                            */
/*  return     :                                                            */
/*  notes      : The transition from Stopped to Network Sleep is initiated  */
/*               at the next call to v_nwm_processing().                    */
/*                                                                          */
/* ************************************************************************ */
extern void v_nwm_resume ( v_nwm_instance_handle  nwm );

/* ************************************************************************ */
/*  function   : v_nwm_fmd_set                                              */
/*  description: This function changes the frame mode to fmd for the        */
/*               instance nwm.                                              */
/*  input      : nwm    The Network Management instance.                    */
/*               fmd    This is an array containing the new frame mode for  */
/*                      each CAN-controller in the instance nwm.            */
/*  output     :                                                            */
/*  return     : True   The frame mode change request accepted.             */
/*               False  The frame mode change request not accepted.         */
/*  notes      :                                                            */
/*                                                                          */
/* ************************************************************************ */
extern v_bool v_nwm_fmd_set ( v_nwm_instance_handle  nwm, 
                              const v_fmd_handle fmd [] );

/* ************************************************************************ */
/*  function   : v_nwm_set_network_mode                                     */
/*  description: This function sets the value of the signal NetworkMode to  */
/*               v for the Network Management instance nwm. The value of    */
/*               NetworkMode is not changed if its current value is 1       */
/*               (Shutdown).                                                */
/*  input      : nwm    The Network Management instance.                    */
/*               v      The new value. The values 0 (Start-up) and 1        */
/*                      (Shutdown) are not allowed. v must be 2 (Normal) or */
/*                      greater (non NWM mode).                             */
/*  output     :                                                            */
/*  return     :                                                            */
/*  notes      : This function should only be used by instances of the type */
/*               master or secondary master.                                */
/*                                                                          */
/* ************************************************************************ */
extern void v_nwm_set_network_mode ( v_nwm_instance_handle  nwm, const v_uint8 v );

/* ************************************************************************ */
/*  function   : v_nwm_get_slave_nodes_status                               */
/*  description: This function returns the status of the slave nodes if the */
/*               current state of nwm is Normal, otherwise is zero returned.*/
/*  input      : nwm    The Network Management instance.                    */
/*  output     :                                                            */
/*  return     : Each slave node is represented by one bit in the returned  */
/*               32-bit status word.                                        */
/*  notes      : This function should only be used by instances of the type */
/*               master or secondary master.                                */
/*                                                                          */
/* ************************************************************************ */
extern v_uint32 v_nwm_get_slave_nodes_status ( v_nwm_instance_handle  nwm );

#endif /* __V_NWM_H__ */
