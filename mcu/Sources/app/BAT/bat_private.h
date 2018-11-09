/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : bat_private.h
* Description : the private datas of the Bat
* Author: qq
* Date: 2018-06-06
******************************************************************************/

/* check of multiple include */
#ifndef _BAT_PRIVATE_H_

#define _BAT_PRIVATE_H_

/* Macro defines */
//#define TRUE   1
//#define FALSE  0

//#define BatVoltageSts_TS                       3268/*3480*/
//#define BAT_LEVEL_LOW                        1843/*1810*/

#define BAT_PROCESS_PERIOD                   5
#define BAT_VOLATE_PERIOD                    500
//#define BAT_FACTOR_100MV    18.1

#define BAT_RANGE_TDFLT_HIGHVOL_ON	 	619//(160*BAT_FACTOR_100MV)	/* 16V =625  */
#define BAT_RANGE_TDFLT_HIGHVOL_OFF     600//(155*BAT_FACTOR_100MV)    /*15.5V =600 */
#define BAT_RANGE_TDFLT_LOWVOL_ON       337//(90*BAT_FACTOR_100MV)    /*9V  =343   */
#define BAT_RANGE_TDFLT_LOWVOL_OFF      357//(95*BAT_FACTOR_100MV)	/*9.5V =364  */
#define BAT_TDVOLATE_CNT               (BAT_VOLATE_PERIOD/BAT_PROCESS_PERIOD)

#define BAT_RANGE_CLASSA_FLT_HIGHVOL_ON		 637//(165*BAT_FACTOR_100MV)	/* 16.5V =645  */
#define BAT_RANGE_CLASSA_FLT_HIGHVOL_OFF     619//(160*BAT_FACTOR_100MV)   /*16V =624 */
#define BAT_RANGE_CLASSA_FLT_LOWVOL_ON       316//(85*BAT_FACTOR_100MV)   /*8.5V  =320   */
#define BAT_RANGE_CLASSA_FLT_LOWVOL_OFF      337//(90*BAT_FACTOR_100MV)	/*9V  =343 */
#define BAT_CLASSA_VOLATE_CNT           (BAT_VOLATE_PERIOD/BAT_PROCESS_PERIOD)

#define BAT_RANGE_CAN_FLT_HIGHVOL_ON	  678//(170*BAT_FACTOR_100MV)	/* 17.5V =685  */
#define BAT_RANGE_CAN_FLT_HIGHVOL_OFF     660//175*BAT_FACTOR_100MV) /*17V =666 */
#define BAT_RANGE_CAN_FLT_LOWVOL_ON       216//(60*BAT_FACTOR_100MV) /*6V  =220   */
#define BAT_RANGE_CAN_FLT_LOWVOL_OFF      236//(65*BAT_FACTOR_100MV)	/*6.5V =240  */

#define BAT_CAN_VOLATE_CNT             (BAT_VOLATE_PERIOD/BAT_PROCESS_PERIOD)

/* Private data structures defines */

typedef  enum  BatFlt_Tag
{
    FLT_BAT_NORMAL = (0u),                       /* battery normal */
    FLT_BAT_VOL_HIGH,                            /* battery high   */
    FLT_BAT_VOL_LOW,                             /* battery low    */
    FLT_BAT_ALL
}BatFlt_ENUM;

typedef  enum  BatDect_Type_tag
{
    TYPE_BATDET_TD = (0u), /* Trouble Diagnostic */
    TYPE_BATDET_CLASSA,    /* class a */
    TYPE_BATDET_CAN,       /* can */
    TYPE_BATDET_ALL
}BatDect_Type_ENUM;

typedef struct stBatDect_tag
{
    U8 status;
    U8 status_bak;
    U8 fltSts;
    U16 Detect_cnt;
}stBatDect_ST;


typedef struct stBatVoltageValue_tag
{
    U16 highoff;
    U16 highon;
    U16 lowoff;
    U16 lowon;
    U16 fltMaxCnt;
}stBatVoltageValue_ST;

typedef struct batVolDetectTab_tag
{
    //BatDect_Type_ENUM Type;
    stBatDect_ST* pdata;
}batVolDetectTab_ST;

static BOOL bat_InitSts = FALSE;
static U16  bat_ADCValue;
static stBatDect_ST bat_TD;  
static stBatDect_ST bat_ClassA;
static stBatDect_ST bat_Can;
const static stBatVoltageValue_ST batVolRangTab[TYPE_BATDET_ALL]=
{
    {
        BAT_RANGE_TDFLT_HIGHVOL_OFF,
        BAT_RANGE_TDFLT_HIGHVOL_ON,
        BAT_RANGE_TDFLT_LOWVOL_OFF,
        BAT_RANGE_TDFLT_LOWVOL_ON,
        BAT_TDVOLATE_CNT
    },
    
    {
        BAT_RANGE_CLASSA_FLT_HIGHVOL_OFF,
        BAT_RANGE_CLASSA_FLT_HIGHVOL_ON,
        BAT_RANGE_CLASSA_FLT_LOWVOL_OFF,
        BAT_RANGE_CLASSA_FLT_LOWVOL_ON,
        BAT_CLASSA_VOLATE_CNT
    },
 
    {
        BAT_RANGE_CAN_FLT_HIGHVOL_OFF,
        BAT_RANGE_CAN_FLT_HIGHVOL_ON,
        BAT_RANGE_CAN_FLT_LOWVOL_OFF,
        BAT_RANGE_CAN_FLT_LOWVOL_ON,
        BAT_CAN_VOLATE_CNT
    },
};

static stBatDect_ST* batDectTab[TYPE_BATDET_ALL]=
{
    &bat_TD,
    &bat_ClassA,
    &bat_Can
};
/*constant define*/

typedef  enum  BatLevel_Tag
{
    LEVEL_BAT_NORMAL = (0u),                     /* battery normal */
    LEVEL_BAT_HIGH,                              /* battery high   */
    LEVEL_BAT_LOW,                               /* battery low    */
    LEVEL_BAT_ALL
}BATLevel_ENUM;



/* Private static functions declare */
static void bat_voltageRange_Process_5ms(U8 Type,stBatDect_ST *pData);
static void bat_voltageRange_check_5ms(U8 Type,stBatDect_ST *pData);
//extern U8 bat_GetBatFltSts(BatDect_Type_ENUM Type,PU8 sts);
#endif /*_BAT_PRIVATE_H_*/

/*------------------end of file----------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0            qq              2018-6-6              Initial
*===========================================================================*/

