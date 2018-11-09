/*******************************************************************
Analog Devices, Inc. All Rights Reserved.

This software is proprietary and confidential.  By using this software
you agree to the terms of the associated Analog Devices License Agreement.

Project Name:  	Power_On_Self_Test

Hardware:		ADSP-21479/21489 EZ-Board

Description:	This file tests the UART interface on the EZ-Board.
*******************************************************************/

/*******************************************************************
*  include files
*******************************************************************/
#include "uart_info.inc"

/*******************************************************************
*  global variables and defines
*******************************************************************/

/* if we are using the UART to print debug info, define the following */
#ifdef __DEBUG_UART__
#define UART_DEBUG_BUFFER_LINE_SIZE 256
char UART_DEBUG_BUFFER[UART_DEBUG_BUFFER_LINE_SIZE];
#endif

#define UART_RX_SIZE 512
#define UART_TX_SIZE 512
char UART_TX_BUFFER[UART_TX_SIZE];
char UART_RX_BUFFER[UART_RX_SIZE];

#if defined(__DEBUG_FILE__)
extern FILE *pDebugFile;				/* debug file */
#endif

/*******************************************************************
*  function prototypes
*******************************************************************/
void UART_init(void);
int UART_PutChar(const char c);
int UART_GetChar(char *const c);
int UART_PUT_STRING(void);

char uart_receive_buffer[5];

/* if we are using the UART to print debug info, define the following */
#ifdef __DEBUG_UART__
int UART_DebugPrint(void);
#endif

int RX_Flag = 0;
int RX_NUM = 0;
char RX_DATA;
unsigned int UartLastReadNnm = 0;

#if 0
int iput = 0; /* 环形缓冲区的当前放入位置 */
int iget = 0; /* 缓冲区的当前取出位置 */
int Index = 0; /* 环形缓冲区中的元素总数量 */
#endif

int UartLoopBufferWritePos = 0; /* 环形缓冲区的当前放入位置 */
int UartLoopBufferReadPos = 0; /* 缓冲区的当前取出位置 */
int UartLoopBufferCount = 0; /* 环形缓冲区中的接收到元素总数量 */



/***************************************
 ** Function Name:Uart_GetBuferAddring
 ** Description:获取在缓刑缓冲区下一个要读取的位置
 ** Input:int pos
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-8-25
***************************************/
int Uart_GetBuferAddring (int pos)
{
       return (pos+1) == UART_RX_SIZE ? 0 : pos+1;
}


/***************************************
 ** Function Name:Uart_GetLoopBuffer
 ** Description:从环形缓冲区中获取一个元素
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-8-25
***************************************/
char Uart_GetLoopBuffer(void)
{
	int Pos;
	if (UartLoopBufferCount > 0)
	{
		 Pos = UartLoopBufferReadPos;
		 UartLoopBufferReadPos = Uart_GetBuferAddring(UartLoopBufferReadPos);
		 UartLoopBufferCount--;
		 return UART_RX_BUFFER[Pos];
	}
	else
	{
		return -1;
	}
}


/***************************************
 ** Function Name:Uart_PutLoopBuffer
 ** Description:向环形缓冲区中放入一个元素
 ** Input:char InputIndex
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-8-25
***************************************/
void Uart_PutLoopBuffer(char InputData)
{

	if (UartLoopBufferCount < UART_RX_SIZE)
	{
		UART_RX_BUFFER[UartLoopBufferWritePos] = InputData;
		UartLoopBufferWritePos = Uart_GetBuferAddring(UartLoopBufferWritePos);
		UartLoopBufferCount++;
	}
}


void Uart_RX_ISR(uint32_t iid, void* handlerArg)
{
	int ret = 0;
	ret = UART_GetChar(&RX_DATA);
	Uart_PutLoopBuffer(RX_DATA);
	//UART_RX_BUFFER[RX_NUM] = RX_INDEX;
	RX_DATA = 0;
	//RX_NUM++;
	/*if('\r' == RX_INDEX)
	{
		memset(UART_RX_BUFFER,0,sizeof(UART_RX_BUFFER));
		RX_NUM = 0;
	}
	else
	{
		UART_RX_BUFFER[RX_NUM] = RX_INDEX;
		RX_INDEX = 0;
		RX_NUM++;
	}*/
}


/*******************************************************************
*   Function:    Init_UART
*   Description: Initialize UART with the appropriate values
*******************************************************************/

void UART_init(void)
{
	volatile int temp;
	int picr2 = 0x0;

	/* maps the UART0 receive interrupt to P14 using the programmable interrupt controller */

	picr2 = *pPICR2;		/* get PICR2 */
	picr2 &= (~(0x1f<<10));	/* clear P14 bits */
	picr2 |= (0x13<<10);	/* set UART0RX */
	(*pPICR2) = picr2;		/* put it back */

	sysreg_bit_set(sysreg_IMASK, P14I ); /* unmask UART RX interrupt */

	/*(*pUART0IER) = UARTRBFIE;	*/	/* enable UART RX interrupt */

	SRU2(UART0_TX_O,DPI_PB08_I);	/* UART TX signal is connected to DPI pin 9 */
	SRU2(HIGH,DPI_PBEN08_I);
	SRU2(DPI_PB07_O,UART0_RX_I);	/* connect the pin buffer output signal to the UART0 RX */
	SRU2(LOW,DPI_PB07_I);
	SRU2(LOW,DPI_PBEN07_I);			/* disable DPI pin10 as input */

	(*pUART0LCR) = UARTDLAB;		/* enables access to divisor register to set baud rate */
	//(*pUART0DLL) = 651;
	(*pUART0DLL) = 0xA3;
	//(*pUART0DLL) = 0x36;       //Baud rate = PCLK/(16 ?á divisor)
	(*pUART0DLH) = 0x0;
	(*pUART0LCR) = UARTWLS8;
	(*pUART0LCR) = (UARTWLS8|UARTSTB|UARTPEN);   /* 8 bit word, Odd parity, 2 stop bits */
	(*pUART0RXCTL) = UARTEN;        /* enable UART0 RX */
	(*pUART0TXCTL) = UARTEN;        /* enable UART0 TX */
	 adi_int_InstallHandler(ADI_CID_P14I,Uart_RX_ISR,0,true);

	 (*pUART0IER) = UARTRBFIE;/* enable UART RX interrupt */
}


/*******************************************************************
*   Function:    PutChar
*   Description: Writes a character to the UART.
*******************************************************************/

int UART_PutChar(const char cVal)
{
	int nStatus = 0;
	unsigned int count = 0;

	do
	{
		if( (*pUART0LSR & UARTTHRE) )
		{
			*pUART0THR = cVal;
			nStatus = 1;
			break;
		}

		count++;

	} while( count < 0x100000 );

	return nStatus;
}


/*******************************************************************
*   Function:    UART_GetChar
*   Description: Reads a character from the UART.
*******************************************************************/

int UART_GetChar(char *const cVal)
{
	int nStatus = 0;
	unsigned int count = 0x0;

	do{
		if( UARTDR == (*pUART0LSR & UARTDR) )
		{
			*cVal = (char)*pUART0RBR;
			nStatus = 1;
			break;
		}

		count++;

	}while( count < 0x100 );
	if(count == 0x100)
		nStatus = -1;
	return nStatus;
}
#if 0
int UART_PUT_STRING(void)
{
	unsigned int i = 0;		/* index */
	char temp;				/* temp char */


	/* loop through the debug buffer until the end, a NULL, or an error */
	for ( i = 0; i < UART_TX_SIZE; i++)
	{
		temp = UART_TX_BUFFER[i];

		/* if not NULL then print it */
		if (temp)
		{
			if( 0 == UART_PutChar(temp) )
			{
				/* if error was detected then quit */
				return 0;
			}

			/* if it was a newline we need to add a carriage return */
			if ( 0x0a == temp )
			{
				if( 0 == UART_PutChar(0x0d) )
				{
					/* if error was detected then quit */
					return 0;
				}
			}
		}
		else
		{
			/* else NULL was found */
			return 1;
		}
	}

	return 1;


}
#endif

unsigned char UART_WriteData(char * SendBuffer,unsigned int DataLen)
{
	unsigned int i = 0;		/* index */
	char temp;				/* temp char */

	for ( i = 0; i < DataLen; i++)
	{
		temp = SendBuffer[i];

		if( 0 == UART_PutChar(temp) )
		{
			return 0;
		}
	}

	return 1;
}

/*******************************************************************
*   Function:    UART_DspReadDataFromUart
*   Description: read data  from the UART.
*   param :  RxBuff
*   ret : successful return 1 failed return 0
*******************************************************************/
unsigned char UART_ReadData(char * RXBuffer,unsigned int PDataLen)
{
	unsigned int i = 0;		/* index */
	char temp ;				/* temp char */

	if(UartLoopBufferCount >= PDataLen)
	{
		for ( i = 0; i < PDataLen; i++)
		{
			temp = Uart_GetLoopBuffer();
			if(-1 != temp )
			{
				RXBuffer[i] = temp;
			}
			else
			{
				return 0;
			}
		}
	}
	else
	{
		return 0;
	}
	return 1;
}



#if 0
unsigned char UART_ReadData(char * RXBuffer,unsigned int * PDataLen)
{
	unsigned int i = 0;		/* index */
	char temp;				/* temp char */
	int num =10;
	if(0 == RX_NUM)
	{
		memset(UART_RX_BUFFER,0,sizeof(UART_RX_BUFFER));
		return 0;
	}
	 memset(RXBuffer,0,UartLastReadNnm);
	for ( i = 0; i < RX_NUM; i++)
	{
		RXBuffer[i] = UART_RX_BUFFER[i];
	}

    memset(UART_RX_BUFFER,0,sizeof(UART_RX_BUFFER));
	RX_NUM = 0;
	*PDataLen = UartLastReadNnm = i+1;
	return 1;
}

#endif


/*******************************************************************
*   Function:    Test_UART
*   Description: Performs a test by writing characters to and then
					reading characters from the UART and comparing them.
*******************************************************************/

int UART_Test(void)
{
	int n, i;
	char cTxChar;
	char cRxChar;

	DEBUG_HEADER( "UART Test" );

	/* do this before calling Init_UART() and don't print anything else until
		test is done otherwise we will impact the loopback test if we are
		using the UART for debug info */
	DEBUG_PRINT( "\nLooping %d characters through the UART", NUM_TEST_CHARS );

	UART_init();

	for(n = 0; n < NUM_TEST_CHARS; n++)
	{
		/* next test char */
		cTxChar = (n & 0xFF);

		/* write a char */
		if( 0 == UART_PutChar(cTxChar) )
		{
			DEBUG_STATEMENT( "\nTest failed" );
			return 0;
		}

		/* wait between writing and reading to give time for data to appear */
		for (i = 0; i < 500000; i++)
		{
			asm("nop;");
		}

		/* read a char */
		if( 0 == UART_GetChar( &cRxChar ) )
		{
			DEBUG_STATEMENT( "\nTest failed" );
			return 0;
		}

		/* it should match */
		if( cTxChar != cRxChar )
		{
			DEBUG_STATEMENT( "\nTest failed" );
			return 0;
		}
	}

	DEBUG_STATEMENT( "\n\n\nTest passed" );
	return 1;
}


#ifdef __DEBUG_UART__
/*******************************************************************
*   Function:    UART_DEBUG_PRINT
*   Description: Prints debug info over the UART using a predefined
*				 buffer.
*******************************************************************/
int UART_DebugPrint(void)
{
	unsigned int i = 0;		/* index */
	char temp;				/* temp char */


	/* loop through the debug buffer until the end, a NULL, or an error */
	for ( i = 0; i < UART_DEBUG_BUFFER_LINE_SIZE; i++)
	{
		temp = UART_DEBUG_BUFFER[i];

		/* if not NULL then print it */
		if (temp)
		{
			if( 0 == UART_PutChar(temp) )
			{
				/* if error was detected then quit */
				return 0;
			}

			/* if it was a newline we need to add a carriage return */
			if ( 0x0a == temp )
			{
				if( 0 == UART_PutChar(0x0d) )
				{
					/* if error was detected then quit */
					return 0;
				}
			}
		}
		else
		{
			/* else NULL was found */
			return 1;
		}
	}

	return 1;
}
#endif
