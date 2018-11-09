
#include"spib_info.inc"


static int SPIB_InitSts = 0;

int Rx_buffer[SPIB_MAXSENDBUFFSIZE];
int Tx_buffer[SPIB_MAXSENDBUFFSIZE] = {0xaa,1,2,3,4,5,6,7,8,9,10};

int Rx_bufferflag = 0;
int Tx_bufferflag = 1;
/***************************************
 ** Function Name:MSPI_Init
 ** Description:SPI slave device initialize in DSP
 ** Input:None
 ** Output:None
 ** Return:ERROR_CODE
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
void init_pin09(void)
{
	SRU(FLAG6_O,DPI_PB09_I);
	SRU(HIGH,DPI_PBEN09_I);

	sysreg_bit_set( sysreg_FLAGS,FLG6O );

		/* clearing flag pins */
	sysreg_bit_clr( sysreg_FLAGS, FLG6);
}

ERROR_CODE SPIB_Init(void)
{
	SRU(SPIB_MISO_O,DPI_PB14_I);
	SRU(SPIB_MISO_PBEN_O, DPI_PBEN14_I);

	//A_SPI_MOSI_O,DPI_PBEN01_I_REG
	SRU(DPI_PB13_O, SPIB_MOSI_I);     //Connect DPI PB13 to MOSI.
	SRU(SPIB_MOSI_PBEN_O, DPI_PBEN13_I);

	SRU(DPI_PB12_O,SPIB_CLK_I);
	SRU(SPIB_CLK_PBEN_O,DPI_PBEN12_I);

	SRU(DPI_PB11_O, SPIB_DS_I); //connect SPIB_DS_I to pb11
	SRU(LOW, DPI_PBEN11_I); //pb11 as input

	/* setup SPI registers */
	*pSPICTLB = 0x4610;
	init_pin09();
	SPIB_irq_init();

	SPIB_InitSts = TRUE;
	return NO_ERR;
}
/***************************************
 ** Function Name:SPI_GetInitSts
 ** Description:get SPI initialize status
 ** Input:byByte,msb_lsb
 ** Output:None
 ** Return:int
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
int SPIB_GetInitSts(void)
{
	return SPIB_InitSts;
}
/***************************************
 ** Function Name:WriteByteToSPIB
 ** Description:write data to MCU
 ** Input:byByte,msb_lsb
 ** Output:None
 ** Return:ERROR_CODE
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
ERROR_CODE WriteByteToSPIB(const int byByte, const int msb_lsb)
{
	int nTimeOut = 100000;
	int n;

	if( NO_ERR != Wait_For_SPIBF() )
	{
		return POLL_TIMEOUT;
	}

	while( (TXS & *pSPISTATB) )
	{
		if( nTimeOut-- < 0 )
		{
			return POLL_TIMEOUT;
		}
	}
	*pSPICTLB = (SPIEN|CPHASE|ISSEN|SENDZ|WL8|msb_lsb);
	asm("nop;");
	asm("nop;");
	asm("nop;");
	*pTXSPIB = byByte;

	if( NO_ERR != Wait_For_SPIBF() )
	{
		return POLL_TIMEOUT;
	}
	return NO_ERR;
}


/***************************************
 ** Function Name:WriteStringToSPIB
 ** Description:send data to MCU
 ** Input:pbyByte,msb_lsb
 ** Output:None
 ** Return:ERROR_CODE
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/

ERROR_CODE WriteStringToSPIB(int *pbyByte)
{
	WriteByteToSPIB(Tx_buffer[0],MSBF);

	return NO_ERR;
}


/***************************************
 ** Function Name:ReadByteFromSPIB
 ** Description:read data from MCU
 ** Input:pbyByte,msb_lsb
 ** Output:None
 ** Return:ERROR_CODE
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
ERROR_CODE ReadByteFromSPIB(int *pbyByte, const int msb_lsb)
{
	int nTimeOut = 1000;

	if( NO_ERR != Wait_For_SPIBF())
	{
		return POLL_TIMEOUT;
	}


	// don't read until there is something to read.
	nTimeOut = 1000;
	while( !(RXS & *pSPISTATB) )
	{
		if( nTimeOut-- < 0 )
		{
			return POLL_TIMEOUT;
		}
	}
	*pSPICTLB = (SPIEN|CPHASE|ISSEN|SENDZ|WL8|msb_lsb);
	asm("nop;");
	asm("nop;");
	asm("nop;");
	*pbyByte = *pRXSPIB;

	return NO_ERR;

}




/***************************************
 ** Function Name:ReadByteFromSPIB
 ** Description:read data from MCU
 ** Input:pbyByte,msb_lsb
 ** Output:None
 ** Return:ERROR_CODE
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
ERROR_CODE ReadStringFromSPIB(int *pbyByte)
{
	int i;

	for(i=0 ; i<Rx_bufferflag ; i++)
	{
		pbyByte[i] = Rx_buffer[i];
	}
	Rx_bufferflag = 0;
	memset(Rx_buffer,0,sizeof(Rx_buffer));
	return NO_ERR;

}

/***************************************
 ** Function Name:Wait_For_SPIBF
 ** Description:wait for SPIB transmit data finish
 ** Input:None
 ** Output:None
 ** Return:ERROR_CODE
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
ERROR_CODE Wait_For_SPIBF(void)
{

	int nTimeout = 10000;
	// status updates can be delayed up to 10 cycles
	// so wait at least 10 cycles before even
	// checking them
	int n;

	// make sure nothing is waiting to be sent
	while( !(SPIF & *pSPISTATB) )
	{
		if( nTimeout-- < 0 )
		{
			return POLL_TIMEOUT;
		}
	}

	return NO_ERR;

}


/***************************************
 ** Function Name:SPIB_GetRxBuffFlag
 ** Description:Get The Number of read
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-5-18
***************************************/
int SPIB_GetRxBuffFlag(void)
{
	return Rx_bufferflag;
}


/***************************************
 ** Function Name:SPIB_isr
 ** Description:Interrupt handle
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-5-18
***************************************/
void SPIB_isr(uint32_t iid, void *handlerarg)
{

	int cnt = 0;
	int GetByte;
#if 0
	adi_int_EnableInt(ADI_CID_SPILI,false);

	while(1)
	{
		cnt++;
		if(cnt > 0x0000ffff)
			break;
		if( (RXS & *pSPISTATB) )
		{
			ReadByteFromSPIB(&GetByte, MSBF);
			if(Rx_bufferflag < 11)
			{
				Rx_buffer[Rx_bufferflag] = GetByte;
				Rx_bufferflag++;
				if( Rx_bufferflag < 11 )
				{
					Send_To_Mcu();
				}
				else
				{
					/*通信结束，发送第一个字节，*/
					WriteStringToSPIB(Tx_buffer);
					SPIB_irq_flag = 0;
					break;
				}
			}

		}
	}

	SPIB_irq_flag = 0;
	adi_int_EnableInt(ADI_CID_SPILI,true);

#else
	if( (RXS & *pSPISTATB) )
	{
		ReadByteFromSPIB(&GetByte, MSBF);
		SPIB_irq_flag = 1;

		if(Rx_bufferflag < 11)
		{
			Rx_buffer[Rx_bufferflag] = GetByte;
			Rx_bufferflag++;
			if( Rx_bufferflag < 11 )
			{
				Send_To_Mcu();
			}
			else
			{
				/*通信结束，发送第一个字节，*/
				WriteStringToSPIB(Tx_buffer);
				//SPIB_irq_flag = 0;
			}
		}
		else
		{
			WriteStringToSPIB(Tx_buffer);
		}
	}
#endif
}
/***************************************
 ** Function Name:Send_To_Mcu
 ** Description:Interrupt handle
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-5-18
***************************************/
ERROR_CODE Send_To_Mcu(void)
{
	WriteByteToSPIB(Tx_buffer[Rx_bufferflag], MSBF);

	return NO_ERR;
}

/***************************************
 ** Function Name:SPIB_irq_init
 ** Description:Spib initialize
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:DONG_zw
 ** Data:2018-5-18
***************************************/
static  void  SPIB_irq_init(void)
{
	adi_int_InstallHandler(ADI_CID_SPILI, SPIB_isr, 0, true);
}


