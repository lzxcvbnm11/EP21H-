#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "target.h"
#include "com_public.h"
#include "dspi_public.h"
#include "iom_public.h"
#include "clock_public.h"
#include "sys_public.h"
#include "ostm_public.h"
#include "wdt_public.h"
#include "uart_public.h"
#define TEST_COM_NETWORK  0

v_uint16 start_time;
void driver_init(void)
{
	CLOCK_Init(); /* mcu clock init pll init*/
	DGPIO_Init(); /* gpio port init */
	DSPI_Init(SPI_1M_HZ,MASTER);	
	//DSPI_Init(SPI_1K_HZ,MASTER);
}


#if 0

void Main_Dlay100us( U8 count )
{
	while(count --)
	{
    	asm("nop");
    	asm("nop");
    	asm("nop");
    	asm("nop");
    	asm("nop");
	}
}
void dsp_power_enable(void)
{
	U8 x;
	
	IOM_SetOutPutLevel(INDEX_IOM_DSP_RES,0);/* dsp reset */
	IOM_SetOutPutLevel(INDEX_IOM_DCDC_EN,0);	
	Main_Dlay100us(10);
	IOM_SetOutPutLevel(INDEX_IOM_DCDC_EN,1);
	Main_Dlay100us(10);
	IOM_SetOutPutLevel(INDEX_IOM_DSP_RES,1);
}
#endif

#if TEST_COM_NETWORK
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
#endif
void main(void) {
     U8 x = 0;
     static U8 i = 0;
  /* put your own code here */
  #if TEST_COM_NETWORK
    init_target();
	COM_Init();
  #endif
  	driver_init();
    SYS_Init();
  	OSTM_Start();
  	printp("M:V1.03,D:V1.02\n");
	//dsp_power_enable();
	EnableInterrupts;
  
  for(;;) {

	#if TEST_COM_NETWORK
    start_time = hw_get_clock();
	COM_Process_5ms();
  	busy_wait();
	#endif
	SYS_ProcessManage();
    WDT_Feed(); /* feeds the dog */
  } /* loop forever */
  /* please make sure that you never leave main */
}
