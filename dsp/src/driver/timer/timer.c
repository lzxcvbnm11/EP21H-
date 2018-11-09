
#include "timer_info.inc"

/* ***************************************************
 * 注意:1.头文件声明要加上相对路径
 * 	   2.中断标志位要写1清零
 * 定时器时间的计算公式：T = 2 * TM0PRD * Tpclk
 * 				 fpclk = (2 * PLLM * fINPUT ) / (PLLD * 2 )
 *****************************************************/
#define HIGH 1
int TransData = 7;


/***************************************
 ** Function Name:TIMER_Init
 ** Description:TIMER0初始化
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:DONG_zw
 ** Data:2018-5-18
***************************************/
void TIMER_Init(void)
{
	Timer0_cfg();
	Timer0_irq_cfg();
}




/***************************************
 ** Function Name:Timer0_cfg
 ** Description:timer0 定时器中断配置
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:DONG_zw
 ** Data:2018-5-18
***************************************/
static void  Timer0_cfg(void)
{
    volatile unsigned int picr2 = 0x0;

    /* TM0STAT
     * Bit11: TIM1DIS, Bit10: TIM1EN, Bit9: TIM0DIS, Bit8: TIM0EN,
     * Bit5: TIM1OVF, Bit4: TIM0OVF, Bit1: TIM1IRQ, Bit0: TIM0IRQ */
    /* Dis Timer1 and Timer 0 */
    *pTM0STAT = 0x0A00;

    /* TM0CTL
         * Bit4: IRQEN, Bit3: PRDCNT, Bit2: PULSE, Bit1-0: TIMODE */
    /* timer0: PWM mode, IRQEN ,   Period interrupt */

    *pTM0CTL = 0x19;
    //  *pTM0PRD =  0xF4240;//20ms

    //  *pTM0PRD = 0xc350 ;//1ms
    //  *pTM0PRD = 0xc35 ;//1/16ms
     *pTM0PRD =  0x3D090;//5ms

    // *pTM0PRD =  0x2FAF080;//1s

      //*pTM0W = 0x4800;//1ms
      *pTM0W = 0x4800;//5ms
     // *pTM0W = 0x480;//1/16ms
     // *pTM0W = 0x5a550;
    *pTM0STAT = 0x100;              /* Enable timer0 */

	//SRU(HIGH,DPI_PB09_I);
	//SRU(HIGH,DPI_PBEN09_I);
    //SRU(SPIB_MOSI_PBEN_O, DPI_PBEN07_I);

    sysreg_bit_set(sysreg_IMASK, ADI_CID_GPTMR0I);    /* unmask Timer0 interrupt */

    printf("Timer0_cfg...\n");
}


/***************************************
 ** Function Name:Timer0_isr
 ** Description:中断服务函数
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:DONG_zw
 ** Data:2018-5-18
***************************************/
static  void  Timer0_isr( uint32_t iid, void *handlerarg)
{
	//WriteByteToSPIB1(0x01, MSBF );
	//test_spib();
	//printf("timer\n\n");
	static int cnt = 0;
#if 0
	cnt++;
	if(cnt >= 55)
	{
		cnt = 0;
		if( time_1s == 0)
		{
			time_1s = 1;
		}
		else
		{

			time_1s = 0;
		}
	}

	timer_cnt++;
	if(timer_cnt >= 4)
	{
		time_20ms = 1;
	}

	Time5ms++;

	if(Time5ms >= 2)
	{
		Rx_bufferflag = 0;
	//	time_20ms++;
		//if(Time5ms == 2) WriteStringToSPIB(Tx_buffer);
		//Tx_bufferflag = 1;
	}

	/*Time5ms++;

	if(Time5ms >= 4)
	{
		Time5ms = 0;
		Rx_bufferflag = 0;
		time_20ms  = 1 ;
		//if(Time5ms == 2) WriteStringToSPIB(Tx_buffer);
		//Tx_bufferflag = 1;
	}
	else
	{
		time_20ms = 0;
	}*/

	/*static int  num =0;
	if(num == 0)
	{
		sysreg_bit_set( sysreg_FLAGS, FLG6);
		num=1;
	}
	else
	{
		sysreg_bit_clr( sysreg_FLAGS, FLG6 );
		num=0;
	}*/

#endif
	//SYS_ProcessManage();

	*pTMSTAT = 0x01;  // reset REQ0 -- write 1 reset

	//printf(" Timer0_isr  ClearSet_LED  = %x\r\n",sta);

}

/***************************************
 ** Function Name:Timer0_irq_cfg
 ** Description:注册中断服务函数
 ** Input:None
 ** Output:None
 ** Return:None
 ** Auther:DONG_zw
 ** Dat:2018-5-18
***************************************/
static void  Timer0_irq_cfg(void)
{
    adi_int_InstallHandler(ADI_CID_GPTMR0I, Timer0_isr, 0, true);
}


