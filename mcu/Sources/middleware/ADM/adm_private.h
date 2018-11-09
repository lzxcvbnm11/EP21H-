/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : adm_private.h
* Description : private informations of the ADM module
* Author: lzx
* Date: 2018-06-05
******************************************************************************/

/* check of multiple include */
#ifndef _ADM_PRIVATE_H_
#define _ADM_PRIVATE_H_  

/* Private Macros defines */
#define ADM_CHANNEL_MAX       		1          /*the max channel of ADC*/
#define DEBOUNCE_COUNT           	3        /*debounce counters of the ADC*/
#define DEBOUNCE_PERIOD          	5        /*debounce time of the ADC*/
#define DEBOUNCE_RANGE1         	82        /*the error range1 of the ADC*/
#define DEBOUNCE_RANGE2         	102       /*the error range2 of the ADC*/
#define DEBOUNCE_FUEL_COUNT   		5          /*the debounce time of the FUEL ADC*/
#define DEBOUNCE_RANGE_MAX    		4095        /*the max error rang of the ADC */

#define FALSE 0
#define TRUE 1
/* Private data structures defines */
typedef  struct  AdmGatherData_Tag
{
    U8 res;                            /*去抖动结果*/
    U8 cnt;                            /*采样计数器*/
    U16 value;                         /*当前采样的值*/
    U32 sum;                           /*连续采样有效值的加和，存放6次*/
    U16 debounceValue;                 /*去抖动之后的采样值*/
}AdmGatherData_ST;

typedef struct  AdmMatrix_Tag
{
    BOOL enable;                       /*是否使能*/
    AdceChannel_ENUM ch;               /*对应ADCE的通道*/
    U16 range;                         /*门限值*/
    U8 debCnt;                         /*去抖次数*/
}AdmMatrix_ST;

/*constant define*/
const AdmMatrix_ST Adm_Matrix[ADM_CHANNEL_MAX]=
{
    {TRUE, INDEX_ADCE_CH0, DEBOUNCE_RANGE2, DEBOUNCE_COUNT},                 /*INDEX_ADM_BVD*/
};

/* Private static functions declare */
static U8 adm_ChannelDebounce(AdmChannel_ENUM pRes);


#endif /*_ADM_PRIVATE_H_*/

/*------------------end of file----------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       lzx      2018-06-05      Initial
*
*===========================================================================*/

