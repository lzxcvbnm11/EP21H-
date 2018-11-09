/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : iom_private.h
* Description : the private informations  of the Iom module
* Author: qq
* Date: 2018-6-5
******************************************************************************/

/* check of multiple include */
#ifndef _IOM_PRIVATE_H_

#define _IOM_PRIVATE_H_

#include "yd_typedefs.h"


/* Macro defines */
#define IOM_DEBOUNCE_MAXCNT      3    /*the counter of the IO debounce*/
#define INPUT                    1    /*IO is input port*/
#define OUTPUT                   0    /*IO is output port*/

//#define TRUE   1
//#define FALSE  0
 
/* Private data structures defines */
typedef struct  IomMatrix_Tag
{
    BOOL enable;                     /*whether enable the IO*/
    DgpioPortNum_ENUM  ch;           /*the channel of the IO port*/
    BOOL type;                       /*the type of the IO port(input or output)*/
}IomMatrix_ST;

typedef  struct  IomDebounceData_Tag
{  
    BOOL value;                   /*read the level of the IO real-timeIO*/
    BOOL debounce;                /*store the level of the IO after debounce*/
    U8 res;                       /*the result of the debounce*/
    U8 cnt;                       /*the counter of the debounce*/
}IomDebounceData_ST;
 

/*constant define*/
const IomMatrix_ST  Iom_Matrix[INDEX_IOM_ALL1 + INDEX_IOM_ALL2]=
{
    {TRUE, INDEX_DGPIO_PIN16, INPUT},  /*功放报错端口1*/ 
    {TRUE, INDEX_DGPIO_PIN20, INPUT},  /*功放报错端口2*/
    {TRUE, INDEX_DGPIO_PIN22, INPUT},  /*CAN总线报错端口*/
    {TRUE, INDEX_DGPIO_PIN17, OUTPUT}, /*控制功放静音*/
    {TRUE, INDEX_DGPIO_PIN21, OUTPUT}, /*控制功放shutdown端口*/
    {TRUE, INDEX_DGPIO_PIN23, OUTPUT}, /*CAN STANDBY控制脚*/
    {TRUE, INDEX_DGPIO_PIN24, OUTPUT}, /*CAN EN 控制脚*/
    {TRUE, INDEX_DGPIO_PIN27, OUTPUT}, /*电源使能控制*/
    {TRUE, INDEX_DGPIO_PIN29, OUTPUT}, /*控制DSP复位端口*/
};

typedef  enum  IomInputLevel_Tag
{
    STATUS_IOM_LOW  =  (0u),    /*端口为低电平*/
    STATUS_IOM_HIGH,            /*端口为高电平*/
    STATUS_IOM_INVALID,         /*端口为无效状态*/
    STATUS_IOM_ALL              /*所有IO端口的状态情况*/
}IomInputLevel_ENUM;

/* Private static functions declare */
static U8 iom_InputDebounce(IOM_InPut_ENUM index);


#endif /*_IOM_PRIVATE_H_*/

/*------------------end of file----------------------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0             qq            2018-6-5      Initial
*
*===========================================================================*/

