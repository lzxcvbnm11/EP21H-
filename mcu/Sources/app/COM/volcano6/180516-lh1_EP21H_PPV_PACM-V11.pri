/* ************************************************************************ */
/*                                                                          */
/*                        Mentor Graphics Corporation                       */
/*                            All rights reserved                           */
/*                                                                          */
/* ************************************************************************ */

/*         File: hello.pri                                                  */
/*  Description: PRIVATE file for Volcano 6 hello world application.        */

private_file;
(include "version.cfg")
flag ficm_node_flag { latches frame containing RstrFctryDeftsReq;}
flag gw_node_flag { latches frame containing LDircnIO;}
flag iecu_node_flag { latches frame containing PedtrnAdoWrnng;}
flag ipk_node_flag { latches frame containing CalendarDay;}
flag ecm_node_flag { latches frame containing EnSpdSts;}
flag ficm_36b_frame_flag { latches frame containing PedtrnAlrtInhSwReq;}
flag ficm_376_frame_flag { latches frame containing RstrFctryDeftsReq;}
flag gw_1f2_frame_flag { latches frame containing SysBPM;}
flag gw_194_frame_flag { latches frame containing TrShftLvrPosV;}
flag gw_1f1_frame_flag { latches frame containing PwrMdMstrAccryA;}
flag gw_196_frame_flag { latches frame containing EPTRdy;}
flag gw_353_frame_flag { latches frame containing VehSpdAvgDrvn;}
flag iecu_390_frame_flag { latches frame containing PedtrnAdoWrnng;}
flag ecm_0c9_frame_flag { latches frame containing EnSpdSts;}
