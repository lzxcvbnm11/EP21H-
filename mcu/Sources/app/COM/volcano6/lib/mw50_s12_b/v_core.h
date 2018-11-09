/* ************************************************************************ */
/*                                                                          */
/*                         Mentor Graphics Corporation                      */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: v_core.h                                                   */
/*  Description: Contains target-independent, user visible items            */

#ifndef __V_CORE_H__
#define __V_CORE_H__

#include "v_target.h"

/* ************************************************************************ */
/* error code (and type) definition                                         */
typedef v_uint8 v_errcode;

/* ************************************************************************ */
/* v_ioctl_op is the 'operation' type.                                      */
typedef v_uint8 v_ioctl_op;

/* This structure type specifies the NWM RX callout data structure */
typedef struct {
                            /* Source address, that is the 29 bits of       */
                            /* the CAN ID                                   */
    v_uint32 address;
                            /* NWM data, that is the data field of the CAN  */
                            /* frame        */
    v_uint8 data[8];
                            /* the length of the CAN frame                  */
    v_uint8 length;
                            /* Unique identifier number for each network    */
                            /* interface. The identifiers are defined in    */
                            /* v_gen.h                                      */
    v_uint8 controller_id;
} v_nwm_recdata ;

#ifdef DEBUG_MODE

void v_error_hook(v_errcode);

#define V_ERROR_BASE                    (0x00u)
#define V_E_C_BASE                      (V_ERROR_BASE)
#define V_E_F_BASE                      (V_ERROR_BASE+0x10u)
#define V_E_S_BASE                      (V_ERROR_BASE+0x20u)
#define V_E_X_BASE                      (V_ERROR_BASE+0x30u)

#define V_E_C_HANDLE                    (V_E_C_BASE+0x00u)

#define V_E_S_HANDLE                    (V_E_S_BASE+0x00u)
#define V_E_S_INTEGER8                  (V_E_S_BASE+0x01u)
#define V_E_S_INTEGER16                 (V_E_S_BASE+0x02u)
#define V_E_S_BOOL                      (V_E_S_BASE+0x03u)
#define V_E_S_BYTE                      (V_E_S_BASE+0x04u)
#define V_E_S_LATE_READ                 (V_E_S_BASE+0x05u)
#define V_E_S_BYTE_OVERRUN              (V_E_S_BASE+0x06u)
#define V_E_S_PUBLISHED                 (V_E_S_BASE+0x07u)
#define V_E_S_INTEGER32                 (V_E_S_BASE+0x08u)

#define V_E_X_REENTRANCY                (V_E_X_BASE+0x00u)

#endif /* DEBUG_MODE */

#define V_IMF_NOT_OWNED                 (0u)
#define V_IMF_NOT_IN_QUEUE              (0u)
#define V_IMF_IN_QUEUE                  (1u)
#define V_IMF_NOT_IN_MODE               (2u)
#define V_IMF_MODE_CHANGE               (3u)


                                    /* v_sys_init() return codes:           */
                                    /* Missing configuration.               */
#define V_CONFIG_MISSING                (0x01u)
                                    /* Mismatch of core version compared to */
                                    /* volcano version of the .tgt file     */
                                    /* and the library that is used now     */
#define V_CORE_VERSION_MISMATCH       (0x02u)
                                    /* Different checksums of fixed file in */
                                    /* network and private run.             */
#define  V_FIXED_CHECKSUM_MISMATCH       (0x03u)
                                    /* Different checksums of target file   */
                                    /* in "v_nvram.c" and "v_gen.c".        */
#define V_TARGET_CHECKSUM_MISMATCH      (0x04u)

                                    /* v_ctl_init() return codes:           */
                                    /* General initalization failure        */
#define V_TARGET_DRV_INIT_FAILURE      (0x01u)
                                    /* Different driver version number      */
                                    /* in .tgt attributes field and in      */
                                    /* driver library                       */
#define V_TARGET_DRV_VER_MISMATCH      (0x02u)

/* ************************************************************************ */
/* These are the methods using for ID to frame searching in the target side */
#define V_NO_METHOD            (0)
#define V_PRIO8_TABLE          (1)
#define V_PRIO11_TABLES        (2)
#define V_SEARCH_ON_IDS        (3)


typedef struct v_controller_descriptor  V_AROM  * V_AROM_PM   v_c_handle;
typedef struct v_fmd_descriptor         V_NVRAM * V_NVRAM_PM  v_fmd_handle;
typedef struct v_s_descriptor           V_NVRAM * V_NVRAM_PM  v_s_handle;
typedef struct v_s_copy_descriptor      V_NVRAM * V_NVRAM_PM  v_s_copy_handle;
typedef struct v_fl_descriptor          V_AROM  * V_AROM_PM   v_fl_handle;
typedef struct v_cfg_descriptor         V_NVRAM * V_NVRAM_PM  v_cfg_handle;
typedef struct v_imf_descriptor         V_NVRAM * V_NVRAM_PM  v_imf_handle;
typedef struct v_act_descriptor         V_NVRAM * V_NVRAM_PM  v_act_handle;

/* Type definitions for void NVRAM and RAM pointers */
typedef void                            V_NVRAM * V_NVRAM_PM  voidnv_handle;
typedef voidnv_handle                   V_NVRAM * V_NVRAM_PM  voidnv_list_handle;
typedef void                            V_RAM   * V_RAM_PM    voidram_handle;

/* Type definitions for pointer to frame map in RAM and NVRAM */
typedef v_frame_map                     V_RAM   * V_RAM_PM    v_frame_map_handle;
typedef v_frame_map                     V_NVRAM * V_NVRAM_PM  v_const_frame_map_handle;


/*lint -save -e960  */
typedef union { /* PRQA S 0750 */ /* union is OK here */
    v_uint8  V_AROM * V_AROM_PM bytes;
    v_uint32 V_AROM * V_AROM_PM pu32;
    v_uint8         u8;
    v_uint16        u16;
    v_bool          boolean;
} v_t_modifier;
/*lint -restore */


/* ************************************************************************ */
/* pointer to notification callout functions                                */
typedef void (* v_fptr)(void);


/* ************************************************************************ */
/* controller descriptor structure                                          */
/* resides in FIXED                                                         */
struct v_controller_descriptor {

    v_fmd_handle null_frame_mode;   /* null frame mode for this controller. */
                                    /* Pointer to RAM area (for modifiable  */
                                    /* controller attributes).              */
    struct v_c_ram V_RAM * V_RAM_PM ram;
                                    /* Pointer to device-specific structu-  */
                                    /* res.                                 */
    voidnv_handle dev_cb;
                                    /* Pointer to protocol-specific         */
                                    /* structures.                          */
    voidnv_handle protocol_cb;
                                    /* Function pointers forming device     */
                                    /* driver interface.                    */
    v_bool       (*send_frame) (v_c_handle c, voidnv_handle tx_frame);
    void         (*send_frames) (v_c_handle c, v_frame_map_handle tx_completion, v_frame_map_handle tx_overrun);
    v_bool       (*read_frame) (v_c_handle c, voidnv_handle rx_frame);
    void         (*read_frames) (v_c_handle c);
    v_bool       (*tx_pending) (v_c_handle c);
    void         (*set_mode) (v_c_handle c, v_fmd_handle mode);
    v_imf_handle (*rx_interrupt_handler) (v_c_handle c);
    v_uint8      (*init_controller) (v_c_handle c);
    void         (*connect_controller) (v_c_handle c);
    void         (*disconnect_controller) (v_c_handle c);
    v_bool       (*controller_active) (v_c_handle c);
    v_uint16     (*controller_ioctl) (v_c_handle c,v_ioctl_op op, void *p);
    v_imf_handle (*tx_interrupt_handler) (v_c_handle c);
    void         (*busoff_interrupt_handler) (v_c_handle c);
    v_uint8      (*check_frame) (v_c_handle c, voidnv_handle frame);
    void         (*app_nm_message_received) (v_nwm_recdata* nwm_frame);
                                    /* Pointer to device-specific RAM       */
                                    /* structures.                          */
    voidram_handle dev_cb_ram;
    v_uint8 flags;
    v_uint8 c_id;
};



/* ************************************************************************ */
/* flag descriptor structure                                                */
/* resides in FIXED                                                         */
struct v_fl_descriptor {
                                    /* Pointer to the signal descriptor, to
                                       which this flag is bound.
                                    */
    v_s_handle signal_ptr;
                                    /* Pointer to byte containing flag bit. */
    v_uint8 V_RAM * V_RAM_PM flag_ptr;
                                    /* Pointer to the callback function.    */
    v_fptr  func_ptr;
                                    /* Pointer to the next flag bount to the*/
                                    /* same event.                          */
    struct v_fl_descriptor V_AROM * V_AROM_PM next_flag;
                                    /* Pointer to the corresponding         */
                                    /* immediate frame.                     */
    v_imf_handle    imf_ptr;

                                    /* Mask selecting flag bit in *flag_ptr */
                                    /* byte.                                */
    v_uint8 flag_mask;
                                    /* Is flag latched by frame or signal   */
    v_bool is_frame_latch;

};

/* ************************************************************************ */
/* timeout descriptor structure                                             */
/* resides in FIXED                                                         */
struct v_t_descriptor {
                                    /* Pointer to the signal descriptor, to
                                       which this flag is bound.
                                    */
    v_s_handle signal_ptr;
                                    /* Handle (address of descriptor) of    */
                                    /* signal to be set by timeout event.   */
    v_s_handle  dest_signal;
    v_fl_handle dest_flag;
    v_t_modifier modifier;
                                    /* (re)set value for counter when sig-  */
                                    /* nal is seen.                         */
    v_uint16 initial_time;
    v_uint16 V_RAM * V_RAM_PM counter;        /* Pointer to countdown value (in RAM). */
                                    /* Is timeout latched by frame or signal*/
    v_bool is_frame_latch;
};

#ifdef V_TARGET_SPECIFIC_SEGMENT_MODIFIER
#include "v_target_pre_seg_mod.h"
#endif

#define V_GEN_CONTROLLER_ARRAY_LABEL            v_controllers
#define V_GEN_FLAG_ARRAY_LABEL                  v_flags
#define V_GEN_OVERRUN_FLAG_ARRAY_LABEL          v_overrun_flags
#define V_GEN_TIMEOUT_FLAG_ARRAY_LABEL          v_timeout_flags
#define V_GEN_TRANSMIT_FLAG_ARRAY_LABEL         v_transmit_flags
#define V_GEN_TIMEOUT_ARRAY_LABEL               v_timeouts
#define V_GEN_FIXED_CHECKSUM_LABEL              v_fixed_checksum
#define V_GEN_CONFIG_HANDLE_LABEL               v_config_handle
#define V_GEN_FLAG_BYTE_COUNT_LABEL             v_flag_byte_count
#define V_GEN_OVERRUN_FLAG_BYTE_COUNT_LABEL     v_overrun_flag_byte_count
#define V_GEN_TARGET_CHECKSUM_LABEL             v_target_checksum
#define V_GEN_IMF_INOT_ARRAY_LABEL              v_imf_inot
#define V_GEN_IMF_NOT_ARRAY_LABEL               v_imf_not

/*lint -save -"esym(793,external identifiers)"  */
/* PRQA S 3684 V_CORE_H_01 */ /* Size of arrays is configuration dependent. */
extern struct v_controller_descriptor V_AROM V_GEN_CONTROLLER_ARRAY_LABEL[];
extern struct v_fl_descriptor V_AROM V_GEN_FLAG_ARRAY_LABEL[];
extern struct v_fl_descriptor V_AROM V_GEN_TIMEOUT_FLAG_ARRAY_LABEL[];
extern struct v_fl_descriptor V_AROM V_GEN_TRANSMIT_FLAG_ARRAY_LABEL[];
extern struct v_fl_descriptor V_AROM V_GEN_OVERRUN_FLAG_ARRAY_LABEL[];
extern struct v_t_descriptor V_AROM V_GEN_TIMEOUT_ARRAY_LABEL[];
extern v_uint8 V_AROM V_GEN_IMF_INOT_ARRAY_LABEL[];
extern v_uint16 V_AROM V_GEN_IMF_NOT_ARRAY_LABEL[];
/* PRQA L:V_CORE_H_01 */

extern v_uint16 V_AROM V_GEN_FLAG_BYTE_COUNT_LABEL;
extern v_uint16 V_AROM V_GEN_OVERRUN_FLAG_BYTE_COUNT_LABEL;
extern v_uint32 V_AROM V_GEN_FIXED_CHECKSUM_LABEL;
extern v_uint32 V_AROM V_GEN_TARGET_CHECKSUM_LABEL;

extern v_fmd_handle V_AROM v_fmd_array;
extern v_imf_handle V_AROM v_imf_array;

#ifdef V_TARGET_SPECIFIC_SEGMENT_MODIFIER
#include "v_target_post_seg_mod.h"
#endif


#define V_GEN_FLAG_BUFFER_ARRAY_LABEL           v_flag_buffer
#define V_GEN_OVERRUN_FLAG_BUFFER_ARRAY_LABEL   v_overrun_flag_buffer

/* PRQA S 3684 V_CORE_H_02 */ /* Size of arrays is configuration dependent. */
extern v_uint8 V_NEAR V_ARAM V_GEN_FLAG_BUFFER_ARRAY_LABEL[];
extern v_uint8 V_NEAR V_ARAM V_GEN_OVERRUN_FLAG_BUFFER_ARRAY_LABEL[];
/* PRQA L:V_CORE_H_02 */

/*lint -restore */


/* ************************************************************************ */
/* Signal read/write handle types.                                          */
/* PRQA S 3313 V_CORE_H_03 */ /* These struct tags are deliberately not visible here. */
typedef struct v_s_8_descriptor V_NVRAM     * V_NVRAM_PM v_s_8_handle;
typedef struct v_s_16_descriptor V_NVRAM    * V_NVRAM_PM v_s_16_handle;
typedef struct v_s_32_descriptor V_NVRAM    * V_NVRAM_PM v_s_32_handle;
typedef struct v_s_bytes_descriptor V_NVRAM * V_NVRAM_PM v_s_bytes_handle;
typedef struct v_s_bool_descriptor V_NVRAM  * V_NVRAM_PM v_s_bool_handle;
/* PRQA L:V_CORE_H_03 */

#endif /* __V_CORE_H__ */
