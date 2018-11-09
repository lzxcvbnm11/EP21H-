/* ************************************************************************ */
/*                                                                          */
/*                        Mentor Graphics Corporation                       */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */
/*                                                                          */
/*         File: hello.c                                                    */
/*  Description: Volcano 6 "hello world" type application.                  */
/*                                                                          */
/* ************************************************************************ */

#include "volcano6.h"
#include "v_hand.h"
#include "target.h"
#include "v_nwm.h"

#define HELLO_NWM_APP

#ifdef HELLO_NWM_APP

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

#endif
/* CANalyzer opponent sends frames with variable length (1-8 bytes) containing
 * data bytes: 0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18.
 * The configured size for imm_rx_frm_1 is 2 bytes. */
#define FIRST_TWO_BYTES 0x1112u

v_uint16 start_time;

/* ************************************************************************ */
/* volcano_processing:                                                      */
/* Calls the required volcano functions to read and write signals. When a   */
/* sub-bus type of interface is used, the required v_sb_tick() is called    */
/* for the interface.                                                       */
void volcano_processing(void)
{
    /* call V_INPUT first   */
    v_input(v_config_handle);

    /* place of V_GATEWAY, but that is not used in this application */
    /* ...  */
	

    v_output(v_config_handle);
	#ifdef HELLO_NWM_APP
    v_nwm_slave_processing( &nwm_slave_instance );
	#endif
}

/* ************************************************************************ */
/* busy_wait:                                                               */
/* Waits until it is time for the next volcano processing call.             */
void busy_wait(void)
{
    v_uint16 tnow;
    v_uint16 elapsed;

    do
    {
        tnow = hw_get_clock();
        elapsed = (v_uint16)(tnow - start_time);
    } while (elapsed < HW_DELAY);

    PET_WATCHDOG();

    start_time += HW_DELAY;
}
#if  0//helle

/* ************************************************************************ */
void main(void)
{
    v_uint8 write_ctr = 0;
    v_uint8 toggler = 0;
    v_uint8 overrun_toggler = 0;
    v_uint8 rec_ctr = 0;
    v_uint8 act_ctr = 0;
                                    /* Target-specific initialisation       */
    init_environment();
    init_target();

    start_time = hw_get_clock();

                                    /* Initialise Volcano 6.                */
    if (v_sys_init(v_config_handle))
    {
        TEST_FAILED();
    }
                                    /* Initialise the controller. It is now */
                                    /* in the null frame mode (no frames    */
                                    /* valid).                              */
    if (v_ctl_init(NI1_handle))
    {
        TEST_FAILED();
    }
                                    /* Connect the controller to the net-   */
                                    /* work.                                */
    v_ctl_con(NI1_handle);
                                    /* Set frame mode M1 so that the frames */
                                    /* we are interested in are valid.      */
    v_fmd_set(NI1_handle, M1_handle);
                                    /* We need to enable interrupts for the */
                                    /* controller (tx/rx by interrupt).     */
    ENABLE_INTS();
                                    /* Enter the never-ending loop which    */
                                    /* contains the main functionality.     */
    while (1)
    {
    #if 0
        if (act_ctr == 100)
        {
            v_activate_frm(act_frm_1_handle);
            v_activate_frm(act_frm_2_handle);
            v_activate_frm(act_frm_3_handle);
        } 
        else if (act_ctr == 200)
        {
            v_deactivate_frm(act_frm_1_handle);
            v_deactivate_frm(act_frm_2_handle);
            v_deactivate_frm(act_frm_3_handle);
            act_ctr = 0;
        }
		
        act_ctr++;

        if (v_imf_rx(imm_rx_frm_1_handle))
        {
            if (v_rd_16(num_handle) != FIRST_TWO_BYTES)
            {
                TEST_FAILED();
            }

            rec_ctr++;
            v_wr_8(tx_ctr_handle, rec_ctr);
            v_imf_tx(imm_tx_frm_1_handle);
        }

                                    /* The flag is set by v_input() when it */
                                    /* processes the received frame.        */
        if (v_test_flag(received_flag_handle))
        {
                                    /* Toggle the toggler.                  */
            toggler = (v_uint8)(!toggler);
                                    /* Write the toggler to the output sig- */
                                    /* nal...                               */
            v_wr_8(outgoing_signal_1_handle, toggler);
                                    /* ...and clear the flag.               */
            v_clear_flag(received_flag_handle);
        }
                                    /* Every 10:th loop we will write to    */
                                    /* outgoing_signal_2. Observe the up-   */
                                    /* date bit on the network.             */
        if (!(write_ctr++ % 10))
        {
                                    /* Read the value of incoming signal 2  */
                                    /* and write it to outgoing_signal_2.   */
                                    /* If the frame containing incoming     */
                                    /* signal 2 has never arrived, we will  */
                                    /* read the initial value specified in  */
                                    /* the hello.net file.                  */
                                    /* If the timeout specified in the      */
                                    /* hello.pri file has elapsed we will   */
                                    /* read the timeout value instead.      */
            v_wr_8(outgoing_signal_2_handle, v_rd_8(incoming_signal_2_handle));

            if (write_ctr > 200)
            {
                write_ctr = 1;
            }
        }
                                    /* The flag is set when overrun is      */
                                    /* detected on the nm_tx frame          */
        if (v_test_flag(overrun_on_nm_tx_handle))
        {
                                    /* Toggle the overrun toggler.          */
            overrun_toggler = (v_uint8)(!overrun_toggler);
                                    /* Write the toggler to the output sig- */
                                    /* nal...                               */
            v_wr_8(outgoing_signal_3_handle, overrun_toggler);
                                    /* ...and clear the flag.               */

            v_clear_flag(overrun_on_nm_tx_handle);
        }
#else
		toggler = (v_uint8)(!toggler);
											/* Write the toggler to the output sig- */
											/* nal...								*/
		v_wr_8(outgoing_signal_1_handle, toggler);
											/* ...and clear the flag.				*/

#endif


        volcano_processing();
        busy_wait();
    }
}
#else



/* ************************************************************************ */
void main(void)
{
    v_uint8 write_ctr = 0;
    v_uint8 toggler = 0;
	v_uint8 data_in = 0;
    v_uint8 overrun_toggler = 0;
    v_uint8 rec_ctr = 0;
    v_uint8 act_ctr = 0;
	
	v_uint8 	busoff_cntr;
	v_nwm_state current_nwm_state;
	
                                    /* Target-specific initialisation       */
    init_environment();
    init_target();

    start_time = hw_get_clock();
	#ifdef HELLO_NWM_APP
	    /* At start-up the application should initialise the NWM module. */
    if (v_nwm_init(v_config_handle, nwm_instances, NUMBER_OF_NWM_INSTANCES ))
    {
        /* NWM initialisation failed. We have entered the state Isolated. */
        /* Error handling or limp home according to "Node Management". */
        for(;;)
        {;}
    }
	#else

                                    /* Initialise Volcano 6.                */
    if (v_sys_init(v_config_handle))
    {
        TEST_FAILED();
    }
                                    /* Initialise the controller. It is now */
                                    /* in the null frame mode (no frames    */
                                    /* valid).                              */
    if (v_ctl_init(PACM_HSC4_handle))
    {
        TEST_FAILED();
    }
                                    /* Connect the controller to the net-   */
                                    /* work.                                */
    v_ctl_con(PACM_HSC4_handle);
                                    /* Set frame mode M1 so that the frames */
                                    /* we are interested in are valid.      */
    v_fmd_set(PACM_HSC4_handle, FM_Normal_HS_handle);
                                    /* We need to enable interrupts for the */
                                    /* controller (tx/rx by interrupt).     */
	#endif
    ENABLE_INTS();
                                    /* Enter the never-ending loop which    */
                                    /* contains the main functionality.     */
    while (1)
    {
    #if 0
        if (act_ctr == 100)
        {
            v_activate_frm(act_frm_1_handle);
            v_activate_frm(act_frm_2_handle);
            v_activate_frm(act_frm_3_handle);
        } 
        else if (act_ctr == 200)
        {
            v_deactivate_frm(act_frm_1_handle);
            v_deactivate_frm(act_frm_2_handle);
            v_deactivate_frm(act_frm_3_handle);
            act_ctr = 0;
        }
		
        act_ctr++;

        if (v_imf_rx(imm_rx_frm_1_handle))
        {
            if (v_rd_16(num_handle) != FIRST_TWO_BYTES)
            {
                TEST_FAILED();
            }

            rec_ctr++;
            v_wr_8(tx_ctr_handle, rec_ctr);
            v_imf_tx(imm_tx_frm_1_handle);
        }

                                    /* The flag is set by v_input() when it */
                                    /* processes the received frame.        */
        if (v_test_flag(received_flag_handle))
        {
                                    /* Toggle the toggler.                  */
            toggler = (v_uint8)(!toggler);
                                    /* Write the toggler to the output sig- */
                                    /* nal...                               */
            v_wr_8(outgoing_signal_1_handle, toggler);
                                    /* ...and clear the flag.               */
            v_clear_flag(received_flag_handle);
        }
                                    /* Every 10:th loop we will write to    */
                                    /* outgoing_signal_2. Observe the up-   */
                                    /* date bit on the network.             */
        if (!(write_ctr++ % 10))
        {
                                    /* Read the value of incoming signal 2  */
                                    /* and write it to outgoing_signal_2.   */
                                    /* If the frame containing incoming     */
                                    /* signal 2 has never arrived, we will  */
                                    /* read the initial value specified in  */
                                    /* the hello.net file.                  */
                                    /* If the timeout specified in the      */
                                    /* hello.pri file has elapsed we will   */
                                    /* read the timeout value instead.      */
            v_wr_8(outgoing_signal_2_handle, v_rd_8(incoming_signal_2_handle));

            if (write_ctr > 200)
            {
                write_ctr = 1;
            }
        }
                                    /* The flag is set when overrun is      */
                                    /* detected on the nm_tx frame          */
        if (v_test_flag(overrun_on_nm_tx_handle))
        {
                                    /* Toggle the overrun toggler.          */
            overrun_toggler = (v_uint8)(!overrun_toggler);
                                    /* Write the toggler to the output sig- */
                                    /* nal...                               */
            v_wr_8(outgoing_signal_3_handle, overrun_toggler);
                                    /* ...and clear the flag.               */

            v_clear_flag(overrun_on_nm_tx_handle);
        }
#else
		#ifdef HELLO_NWM_APP
		
        /* Read the current NWM state and write it to the signal Currentstate */
        current_nwm_state = v_nwm_get_state( &nwm_slave_instance );
        ////v_wr_8( current_state_handle, (v_uint8)current_nwm_state );

        switch (current_nwm_state)  {

            case V_NWM_STARTUP:
                /* The node is starting up */
                break;

            case V_NWM_NORMAL:
                /* We are up and communicating on the network. */
                /* It's possible to run all functions that require */
                /* communication over the network. */

                /* In this example we need the network (receive or transmit */
                /* signals) as long as NetworkMode does not equal 0x03. */
                if (v_rd_8(network_mode_handle) != 0x03)
                {
                    v_nwm_net_com_req(&nwm_slave_instance);
                }

                /* Read the busoff counter and write it to the signal BusOffCounter */
                busoff_cntr = v_nwm_get_busoff_counter( &nwm_slave_instance );
                ////v_wr_8( busoff_counter_handle, busoff_cntr );

                break;

            case V_NWM_WAIT_FOR_NETWORK_SLEEP:
                /* We are on the way to Network Sleep. Signals should */
                /* not be written any more. We shall continue to read signals. */
                break;

            case V_NWM_NETWORK_SLEEP:
                /* The node is silent and the CAN-controllers are in */
                /* sleep mode. */
                break;

            case V_NWM_WAKEUP_NETWORK:
                /* We are waking up the network */
                break;

            case V_NWM_WAKEUP_PENDING:
                /* We have been woken up by traffic on the network */
                break;

            case V_NWM_EXPULSION:
                /* Incorrect signal configuration id received. */
                break;

            case V_NWM_STOPPED:
                /* We are disconnected from the network. */
                break;

            case V_NWM_BUSOFF:
                /* One or more busoff errors detected. */
                break;

            case V_NWM_BUSOFF_WAIT:
                /* The number of busoff errors has reached BUSOFF_MAX. */
                break;

            case V_NWM_ISOLATED:
                /* Not possible to get here. The transition to state Isolated is */
                /* made in function v_nwm_init() if there is a initialisation error */
                break;

            default:
                break;
        }
		#endif
		toggler = (v_uint8)(!toggler);
											/* Write the toggler to the output sig- */
											/* nal...								*/
		v_wr_8(PedtrnAlrtCtlSysFlt_handle, toggler);
		data_in = v_rd_8(SysBPM_handle);
											/* ...and clear the flag.				*/

#endif


        volcano_processing();
        busy_wait();
    }
}

#endif

#ifdef HELLO_NWM_APP
/* NM callout for calling ioctl functions */
v_uint16 v_nmco_ioctl(v_c_handle c, v_uint16 op)
{
    return v_ctl_ioctl(c, (v_ioctl_op) op, (void *) 0);
}
#endif
/* ************************************************************************ */
/* NM callout function block                                                */
/* In this callout three data is read from the v_nwm_recdata structure and  */
/* written into the signals of the nm_tx frame. The frame is sent by the    */
/* immediate frame transmission call. After that the controller id is       */
/* increased and a second transmission is initiated. Since the time between */
/* the consecutive calls was not enough to transmit frame successfully, the */
/* second transmission will cause overrun. This overrun will be evaluated   */
/* in the next v_output() and will manifest itself in overrun_on_nm_tx flag */
void v_nm_message_received(v_nwm_recdata * nm_message)
{
    /* read the structure members and write them in signals                 */
   // v_wr_8(nwm_tx_source_handle,(v_uint8)nm_message->address);
   // v_wr_8(nwm_tx_controller_handle,nm_message->controller_id);
  //  v_wr_8(nwm_tx_length_handle,nm_message->length);
    
    /* trigger the transmission of the nwm_tx frame                         */
  //  v_imf_tx(nwm_tx_handle);    
    
    /* Increase the signal value "nwm_tx_controller"                        */
  //  v_wr_8(nwm_tx_controller_handle,nm_message->controller_id+1);
    
    /* trigger the frame transmission again. This transmission must not     */
    /* happen because it is an overrun condition. The overrun_on_nm_tx flag */
    /* will be set after the next v_output call.                            */
  //  v_imf_tx(nwm_tx_handle);
}
