/*****************************************************************************
* Copyright (C) 2018 ShenZhen Yeedon Media co.,LTD. All rights reserved.
*
* File Name : diic.c
* Description : Driver source file of DIIC.
* Author: Jason.Sun
* Date: 2018-05-27
******************************************************************************/

/* Files for including */
#include "diic_info.inc"

static BOOL Diic_Status = FALSE;

/***************************************************
* Function: DIIC_gpio_init
* Description: i2c gpio initialization.
* Parameters: none
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/
void DIIC_Init(void)
{
	ATDDIEN_IEN3 = 1;

	SET_BIT(DDR01AD_DDR0AD, DEVICE_I2C_SCL_PINAD0);/* =0 INTPUT MODE; =1 OUTPUT MODE*/
	
	SET_BIT(DDR01AD_DDR1AD, DEVICE_I2C_SDA_PINAD1);/* =0 INTPUT MODE; =1 OUTPUT MODE*/

	SET_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);
	
	SET_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);

	Diic_Status =TRUE;
}
/***************************************************
* Function: DIIC_GetInitStatus
* Description: 获取DIIC模块的初始化状�??
* Parameters: none
* Returns:
*            FALSE(0): 未初始化
*            TRUE(1): 已初始化
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/

BOOL  DIIC_GetInitStatus(void)
{
    return Diic_Status;
}

/***************************************************
* Function: i2c_start
* Description: i2c start.
* Parameters: none
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/
static  void diic_start()  
{  

	
	SET_BIT(DDR01AD_DDR1AD, DEVICE_I2C_SDA_PINAD1);/* =0 INTPUT MODE; =1 OUTPUT MODE*/

	
	SET_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);
	
	SET_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);

	DIIC_Dlay20us();
	//gpio_set_value(apple_device_i2c_sda,0);	
	
	CLR_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);
	DIIC_Dlay20us();
	//gpio_set_value(apple_device_i2c_scl,0);
	
	CLR_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
}  
/***************************************************
* Function: i2c_stop
* Description: i2c stop.
* Parameters: none
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/
static  void diic_stop()  
{  
	//imapx_pad_set_mode(apple_device_i2c_sda,"output");
	SET_BIT(DDR01AD_DDR1AD, DEVICE_I2C_SDA_PINAD1);/* =0 INTPUT MODE; =1 OUTPUT MODE*/
	//gpio_set_value(apple_device_i2c_scl,0);
	//gpio_set_value(apple_device_i2c_sda,0);	

	
	CLR_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
	CLR_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);

	
	DIIC_Dlay20us();	
	//gpio_set_value(apple_device_i2c_scl,1);
	
	SET_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
	DIIC_Dlay20us();
	//gpio_set_value(apple_device_i2c_sda,1);
	
	SET_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);
	DIIC_Dlay20us();
}  
/***************************************************
* Function: i2c_read_ack
* Description: i2c read ack.
* Parameters: none
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/
static  U8 diic_read_ack()  
{  
	U8 r=0;  
	
	//imapx_pad_set_mode(apple_device_i2c_sda,"input");
	
	CLR_BIT(DDR01AD_DDR1AD, DEVICE_I2C_SDA_PINAD1);/* =0 INTPUT MODE; =1 OUTPUT MODE*/
	//gpio_set_value(apple_device_i2c_scl,1);	
	SET_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
	DIIC_Dlay20us();
	  
	//r = gpio_get_value(apple_device_i2c_sda);                
	r = GET_BIT(PTI01AD_PTI1AD, DEVICE_I2C_SDA_PINAD1); 
	//gpio_set_value(apple_device_i2c_scl,0);
	CLR_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
	//imapx_pad_set_mode(apple_device_i2c_sda,"output");
	SET_BIT(DDR01AD_DDR1AD, DEVICE_I2C_SDA_PINAD1);/* =0 INTPUT MODE; =1 OUTPUT MODE*/
	//gpio_set_value(apple_device_i2c_sda,1);		
	SET_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);
	return r;  
}  
/***************************************************
* Function: i2c_send_ack
* Description: i2c send ack
* Parameters: none
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/
static  void diic_send_ack(unsigned char ack)  
{  
	//imapx_pad_set_mode(apple_device_i2c_sda,"output");
	SET_BIT(DDR01AD_DDR1AD, DEVICE_I2C_SDA_PINAD1);/* =0 INTPUT MODE; =1 OUTPUT MODE*/
	if(ack)
	{
		//gpio_set_value(apple_device_i2c_sda,0);
		CLR_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);
	}
	else
	{
		//gpio_set_value(apple_device_i2c_sda,1);
		
		SET_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);

	}
	DIIC_Dlay20us();
//gpio_set_value(apple_device_i2c_scl,1);	
	SET_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
	DIIC_Dlay20us();
//	gpio_set_value(apple_device_i2c_scl,0);	
	CLR_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
	DIIC_Dlay20us();
} 
/***************************************************
* Function: i2c_write_byte
* Description: i2c write one byte
* Parameters: write date
* Returns: success or fail
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/
static U8 diic_write_byte(U8 b)  
{  
	int i;  
	//imapx_pad_set_mode(apple_device_i2c_sda,"output");        
	SET_BIT(DDR01AD_DDR1AD, DEVICE_I2C_SDA_PINAD1);/* =0 INTPUT MODE; =1 OUTPUT MODE*/	
	for (i=7; i>=0; i--)
	{  
		if((b&1<<i))
		{
			//gpio_set_value(apple_device_i2c_sda,1);
			
			SET_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);
			////printk("gpio  apple_device_i2c_sda high\n");
		}
		else
		{
			//gpio_set_value(apple_device_i2c_sda,0);
			
			CLR_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);
			//printk("gpio  apple_device_i2c_sda low \n");
		}
		DIIC_Dlay20us();
		//gpio_set_value(apple_device_i2c_scl,1);		
		SET_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
		DIIC_Dlay20us();
		//gpio_set_value(apple_device_i2c_scl,0);		
		CLR_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
		DIIC_Dlay20us();
	}  
	
	//gpio_set_value(apple_device_i2c_sda,1);	
	SET_BIT(PT01AD_PT1AD, DEVICE_I2C_SDA_PINAD1);
	return (diic_read_ack());
}  
/***************************************************
* Function: i2c_read_byte
* Description: i2c read one byte.
* Parameters: ack
* Returns: read date
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/
static U8 diic_read_byte(U8 ack)  
{  
	int i;  
	U8 r = 0;  
	//imapx_pad_set_mode(apple_device_i2c_sda,"input");
	CLR_BIT(DDR01AD_DDR1AD, DEVICE_I2C_SDA_PINAD1);/* =0 INTPUT MODE; =1 OUTPUT MODE*/	

	for (i=7; i>=0; i--)
	{  
		//gpio_set_value(apple_device_i2c_scl,1);		
		SET_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
		DIIC_Dlay20us(); 
		if(GET_BIT(PTI01AD_PTI1AD, DEVICE_I2C_SDA_PINAD1) == 0)
		{
			r = (r <<1);			
			//printk("gpio read apple_device_i2c_sda low \n");
		}
		else
		{
			r = (r <<1)|0x01;
			//printk("gpio read apple_device_i2c_sda high \n");
		}
				
		//gpio_set_value(apple_device_i2c_scl,0);		
		CLR_BIT(PT01AD_PT0AD, DEVICE_I2C_SCL_PINAD0);
		DIIC_Dlay20us(); 
	}  
	diic_send_ack(ack);
	return r;  
}
/***************************************************
* Function: DIIC_read
* Description: i2c read function
* Parameters: dev_addr,reg_addr,buf,len
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/
U8 DIIC_read(U8 dev_addr,U8 reg_addr, U8* buf, U16 len)  
{  
	U8 ret;
	U16 i;  
	diic_start();                        
	ret = diic_write_byte(dev_addr);
    if(ret == 1)
	{
		return RET_INVALID;
	}
	else
	{
	}
	ret = diic_write_byte(reg_addr); 
	  if(ret == 1)
	{
		return RET_INVALID;
	}
	else
	{
	}
	DIIC_Dlay20us();
	//i2c_stop();
	diic_start();
	ret = diic_write_byte(dev_addr|0x01);
	  if(ret == 1)
	{
		return RET_INVALID;
	}
	else
	{
	}
	DIIC_Dlay20us();
	for (i=0; i<len; i++)  
	buf[i] = diic_read_byte(len-i-1);  
	diic_stop(); 
	return RET_OK;
}  
/***************************************************
* Function: DIIC_write
* Description: i2c write function
* Parameters: dev_addr,reg_addr,buf,len
* Returns:
*
* $Create & Verlog:$
* Author:Jason.Sun  Date:2018-05-27   Version:V1.0
****************************************************/
void DIIC_write(U8 dev_addr,U8 reg_addr,unsigned char* buf, U16 len)  
{  
	U16 i;  
	diic_start();                        
	diic_write_byte(dev_addr);
	diic_write_byte(reg_addr);
	for (i=0; i<len; i++)  
	diic_write_byte(buf[i]);  
	diic_stop();
}


void DIIC_Dlay20us(void)//U32 cnt)
{
  #if 0
    U32 cnt = 100;
    U32 counter = 1000;
    for( ;0 != cnt;cnt --)
    {
       for(; 0 != counter;counter--)
       {
       ;
       }
       //counter = 3;
    }
  #endif
    asm("nop");
}

/*----------------- End of Module -----------------*/

/*===========================================================================
* File Revision History(bottom to top:first revision to last revision)
*============================================================================
* $Log:$
*
* Rev:         Userid:           Date:               Description
*--------    ----------       ---------       ------------------------------
*
* V1.0       Jason.Sun      2018-05-27      Initial
*
*===========================================================================*/
