#ifndef  _UART_PUBLIC_H_
#define  _UART_PUBLIC_H_


#define BAUD_RATE_115200 	(0x15A2 >> 7)
#define NUM_TEST_CHARS		(1*1024)
#define __DEBUG_UART__
void UART_init(void);
int UART_PutChar(const char cVal);
int UART_GetChar(char *const c);
//int Get_String(char *RXBuffer);
/*******************************************************************
*   Function:    UART_DspWriteDataToUart
*   Description: write data  to the UART.
*   param :  statement is transform buf
*   ret   :  buf length
*******************************************************************/
//#define UART_DspWriteDataToUart(statement)	snprintf(UART_TX_BUFFER, UART_TX_SIZE, statement); \
									UART_PUT_STRING();

unsigned char UART_WriteData(char * SendBuffer,unsigned int DataLen);
unsigned char UART_ReadData(char * RXBuffer,unsigned int PDataLen);


#endif
