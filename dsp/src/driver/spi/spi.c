#include "spi_info.inc"


static char *pFlashDesc 	=		"STMicro. M25P16";
static char *pDeviceCompany	=	"STMicroelectronics";
static int	gNumSectors 	= NUM_SECTORS;




/***************************************
 ** Function Name:SPI_init
 ** Description: initialize spi_flash
 ** Input:None
 ** Output:None
 ** Return:None
***************************************/
int SPI_init(void)
{
	COMMAND_STRUCT pCmdBuffer;				/* command buffer */
	int nManCode = 0, nDevCode = 0;			/* man and device ids */
	ERROR_CODE Result = NO_ERR; 			/* result */

	if (spi_SetBuadRate() != NO_ERR)
	{
		DEBUG_STATEMENT( "\nCould not open flash driver" );
		return 0;
	}

	/* setup the device so the DSP can access it */
	if (spi_SetupForFlash() != NO_ERR)
	{
		DEBUG_STATEMENT( "\n    Setup flash driver failed" );
		return 0;
	}

	/* get the codes */
	pCmdBuffer.SGetCodes.pManCode = (unsigned long *)&nManCode;
	pCmdBuffer.SGetCodes.pDevCode = (unsigned long *)&nDevCode;
	pCmdBuffer.SGetCodes.ulFlashStartAddr = 0x0;
	Result = spi_Control( CNTRL_GET_CODES, &pCmdBuffer );

//	DEBUG_PRINT( "\nDetected manufacturer code of 0x%x and device code of 0x%x", nManCode, nDevCode );

	/* if codes don't match what we expect then we should fail */
	if ( (MAN_CODE != nManCode) || (DEV_CODE != nDevCode) )
	{
//		DEBUG_STATEMENT( "\nFlash codes do not match what we expected" );

		return 0;
	}

	return 1;

}

/***************************************
 ** Function Name:spi_SetBuadRate
 ** Description: Set SPI BaudRate
 **				SPICLK baud rate = PCLK /(4 x BAUDR)
 ** Input:None
 ** Output:None
 ** Return:NO_ERR
***************************************/
static ERROR_CODE spi_SetBuadRate(void)
{
	/* set baud rate */
	*pSPIBAUD = BAUD_RATE_DIVISOR;

	return (NO_ERR);
}


/***************************************
 ** Function Name:spi_SetupForFlash
 ** Description: SPI 配置
 ** Input:None
 ** Output:None
 ** Return:NO_ERR
***************************************/
static ERROR_CODE spi_SetupForFlash(void)
{
	/* setup SPI signals */
	SRU(SPI_MOSI_O,DPI_PB01_I);
	SRU(SPI_MOSI_PBEN_O, DPI_PBEN01_I);

	/* Connect DPI PB2 to MISO */
	SRU(DPI_PB02_O, SPI_MISO_I);     
	SRU(SPI_MISO_PBEN_O, DPI_PBEN02_I);

	SRU(SPI_CLK_O,DPI_PB03_I);
	SRU(SPI_CLK_PBEN_O,DPI_PBEN03_I);

	/* for the flag pins to act as chip select */
	SRU(FLAG4_O, DPI_PB05_I);
	SRU(HIGH, DPI_PBEN05_I);

	/* first set flag 4 as an output */
	sysreg_bit_set( sysreg_FLAGS, FLG4O );
	sysreg_bit_set( sysreg_FLAGS, FLG4 );

	/* setup SPI registers */
	*pSPIDMAC = 0;
	*pSPIBAUD = 0;
	*pSPIFLG = 0xF80;
	*pSPICTL = 0x400;

	return NO_ERR;
}


/***************************************
 ** Function Name:spi_Close
 ** Description: SPI 关闭
 ** Input:None
 ** Output:None
 ** Return:NO_ERR
***************************************/
static ERROR_CODE spi_Close(void)
{
	return (NO_ERR);
}



/***************************************
 ** Function Name:SPI_Read
 ** Description: 读FLASH，可以连续读
 ** Input:  ulStartAddress:  起始地址
 **			uiCount：	     读取的字节长度
 ** Output: pusData：         读取的数据
 ** Return: NO_ERR 		 0
 **		    POLL_TIMEOUT 1
***************************************/
ERROR_CODE SPI_Read( unsigned int *pusData,
                      unsigned long ulStartAddress,
                      unsigned int uiCount )
{
    ERROR_CODE Result = NO_ERR;
    unsigned int i 	  = 0;
    unsigned int *pusCurrentData = pusData;
    unsigned long ulCurrentAddress = ulStartAddress;

    for (i = 0; i < uiCount; i++, ulCurrentAddress++, pusCurrentData++)
    {
		spi_Assert_CS();

		/* 1 byte of command  */
		if( NO_ERR != spi_WriteByteToSPI( SPI_READ, MSBF ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		/* 1 byte of address */ 
		if( NO_ERR != spi_WriteByteToSPI( (ulCurrentAddress >> 16), MSBF ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		/* 1 byte of address */ 
		if( NO_ERR != spi_WriteByteToSPI( (ulCurrentAddress >> 8), MSBF ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		/* 1 byte of address */ 
		if( NO_ERR != spi_WriteByteToSPI( ulCurrentAddress, MSBF ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		/* 1 byte of garbage data */
		if( NO_ERR != spi_ReadByteFromSPI( (int*)pusCurrentData, 0 ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		/*  1 byte of GOOD data */ 
		if( NO_ERR != spi_ReadByteFromSPI( (int*)pusCurrentData, 0 ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		spi_Clear_CS();
    }

	return(Result);
}



/***************************************
 ** Function Name:SPI_Write
 ** Description: 写FLASH，支持连续写
 ** Input: pusData: 	   数据地址
 **		   ulStartAddress：起始地址
 **		   uiCount：        长度
 ** Output:None
 ** Return:NO_ERR 		0
 **		   POLL_TIMEOUT 1
***************************************/
ERROR_CODE SPI_Write( unsigned int *pusData,
                       unsigned long ulStartAddress,
                       unsigned int uiCount )
{
    ERROR_CODE Result = NO_ERR;
    unsigned int i    = 0;
    unsigned int *pusCurrentData = pusData;
    unsigned long ulCurrentAddress = ulStartAddress;


    for (i = 0; i < uiCount; i++, ulCurrentAddress++, pusCurrentData++)
    {
		spi_SendSingleCommand( SPI_WREN );	// write enable

		spi_Assert_CS();

		/*  1 byte of command  */ 
		if( NO_ERR != spi_WriteByteToSPI( SPI_PP, MSBF ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		/* 1 byte of address */ 
		if( NO_ERR != spi_WriteByteToSPI( (ulCurrentAddress >> 16), MSBF ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		/* 1 byte of address */
		if( NO_ERR != spi_WriteByteToSPI( (ulCurrentAddress >> 8), MSBF ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		/* 1 byte of address */
		if( NO_ERR != spi_WriteByteToSPI( ulCurrentAddress, MSBF ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		/*  1 byte of data */
		if( NO_ERR != spi_WriteByteToSPI( *pusCurrentData, 0 ) )
		{
			spi_Clear_CS();
			return POLL_TIMEOUT;
		}

		spi_Clear_CS();

		/*  wait for the write to complete. */
		if( NO_ERR != spi_Wait_For_RDY() )
		{
			return POLL_TIMEOUT;
		}

		/* send the write disable command */
		spi_SendSingleCommand( SPI_WRDI );
    }

    return(Result);
}


/***************************************
 ** Function Name:spi_Control
 ** Description: 对FLASH做一些控制，主要用于擦出
 ** Input: uiCmd：	   控制指令
 **		   pCmdStruct：指令信息
 ** Output:None
 ** Return:NO_ERR 		0
 **		   POLL_TIMEOUT 1
***************************************/

ERROR_CODE spi_Control(  unsigned int uiCmd,
                            	 COMMAND_STRUCT *pCmdStruct)
{
	ERROR_CODE ErrorCode = NO_ERR;

	/* switch on the command */
	switch ( uiCmd )
	{
		/* erase all */
		case CNTRL_ERASE_ALL:
			ErrorCode = spi_EraseFlash(pCmdStruct->SEraseAll.ulFlashStartAddr);
			break;

		/*  erase sector */
		case CNTRL_ERASE_SECT:
			ErrorCode = spi_EraseBlock( pCmdStruct->SEraseSect.nSectorNum, pCmdStruct->SEraseSect.ulFlashStartAddr );
			break;

		/* get manufacturer and device codes */
		case CNTRL_GET_CODES:
			ErrorCode = spi_GetCodes((int *)pCmdStruct->SGetCodes.pManCode, (int *)pCmdStruct->SGetCodes.pDevCode, (unsigned long)pCmdStruct->SGetCodes.ulFlashStartAddr);
			break;
		
		/* Filling the contents with data */
		case CNTRL_GET_DESC:
			pCmdStruct->SGetDesc.pDesc  = pFlashDesc;
			pCmdStruct->SGetDesc.pFlashCompany  = pDeviceCompany;
			break;

		/* get sector number based on address */
		case CNTRL_GET_SECTNUM:
			ErrorCode = spi_GetSectorNumber( pCmdStruct->SGetSectNum.ulOffset, (int *)pCmdStruct->SGetSectNum.pSectorNum );
			break;

		/* get sector number start and end offset */
		case CNTRL_GET_SECSTARTEND:
			ErrorCode = spi_GetSectorStartEnd( pCmdStruct->SSectStartEnd.pStartOffset, pCmdStruct->SSectStartEnd.pEndOffset, pCmdStruct->SSectStartEnd.nSectorNum );
			break;

		/* get the number of sectors */
		case CNTRL_GETNUM_SECTORS:
			pCmdStruct->SGetNumSectors.pnNumSectors[0] = gNumSectors;
			break;

		/* reset */
		case CNTRL_RESET:
			ErrorCode = spi_ResetFlash(pCmdStruct->SReset.ulFlashStartAddr);
			break;

		/* no command or unknown command do nothing */
		default:
			ErrorCode = UNKNOWN_COMMAND;	// set our error
			break;
	}

	return(ErrorCode);
}

/***************************************
 ** Function Name:spi_ResetFlash
 ** Description:Sends a "reset" command to the flash.
 ** Input:unsigned long ulStartAddr - flash start address
 ** Output:None
 ** Return:
			ERROR_CODE - value if any error occurs
    		NO_ERR     - otherwise
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_ResetFlash(unsigned long ulAddr)
{

	ERROR_CODE ErrorCode = NO_ERR;
	int nStatus;

	ErrorCode = spi_ReadStatusRegister(&nStatus);

	return ErrorCode;

}

/***************************************
 ** Function Name:spi_EraseFlash
 ** Description:Sends an "erase all" command to the flash.
 ** Input:unsigned long ulStartAddr - flash start address
 ** Output:None
 ** Return:
			ERROR_CODE - value if any error occurs
    		NO_ERR     - otherwise
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_EraseFlash(unsigned long ulAddr)
{

	int nTimeout = 1000;

	if( NO_ERR != spi_SendSingleCommand( SPI_WREN ) )	// write enable
	{
		return POLL_TIMEOUT;
	}

	if( NO_ERR != spi_SendSingleCommand( SPI_BE ) )	// erase command
	{
		return POLL_TIMEOUT;
	}

	// The spi_Wait_For_RDY() function will timeout after 1000 loops,
	// however that is not long enough for an erase, so it's enclosed
	// here to give it 1000 * 1000 loops, long enough for an erase  operation
	while(nTimeout-- > 0 )
	{
		if( NO_ERR == spi_Wait_For_RDY() )
		{
			/* send the write disable command */
			return spi_SendSingleCommand( SPI_WRDI );	
		}
	}

	return POLL_TIMEOUT;
}


/***************************************
 ** Function Name:spi_EraseBlock
 ** Description:Sends an "erase block" command to the flash.
 ** Input:
			int nBlock - block to erase
			unsigned long ulStartAddr - flash start address
 ** Output:None
 ** Return:
			ERROR_CODE - value if any error occurs
    		NO_ERR     - otherwise
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_EraseBlock( int nBlock, unsigned long ulAddr )
{

	ERROR_CODE 	  ErrorCode   = NO_ERR;		//tells us if there was an error erasing flash
 	unsigned long ulSectStart = 0x0;		//stores the sector start offset
 	unsigned long ulSectEnd   = 0x0;		//stores the sector end offset(however we do not use it here)
	int nTimeout = 1000;
	int nSecAddr = 0;

	// Get the sector start offset
	// we get the end offset too however we do not actually use it for Erase sector
	spi_GetSectorStartEnd( &ulSectStart, &ulSectEnd, nBlock );

	spi_SendSingleCommand( SPI_WREN );	// write enable

	spi_Assert_CS();

	// 1 byte of data
	if( NO_ERR != spi_WriteByteToSPI( SPI_SE, MSBF ) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	// 1 byte of address
	if( NO_ERR != spi_WriteByteToSPI( (ulSectStart >> 16), MSBF ) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	// 1 byte of address
	if( NO_ERR != spi_WriteByteToSPI( (ulSectStart >> 8), MSBF ) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	// 1 byte of address
	if( NO_ERR != spi_WriteByteToSPI( ulSectStart, MSBF ) )
		{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	spi_Clear_CS();

	// The spi_Wait_For_RDY() function will timeout after 1000 loops,
	// however that is not long enough for an erase, so it's enclosed
	// here to give it 1000 * 1000 loops, long enough for an erase  operation
	while(nTimeout-- > 0 )
	{
		if( NO_ERR == spi_Wait_For_RDY() )
		{
			// send the write disable command
			return spi_SendSingleCommand( SPI_WRDI );	// write disable
		}
	}

	return POLL_TIMEOUT;
}

/***************************************
 ** Function Name:spi_GetCodes
 ** Description:Sends an "auto select" command to the flash which will allow
	        	us to get the manufacturer and device codes.
 ** Input:
			int *pnManCode - pointer to manufacture code
			int *pnDevCode - pointer to device code
			unsigned long ulStartAddr - flash start address
 ** Output:None
 ** Return:
			ERROR_CODE - value if any error occurs
    		NO_ERR     - otherwise
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_GetCodes(int *pnManCode, int *pnDevCode, unsigned long ulAddr)
{
	int wWord = 0;

	spi_Assert_CS();

	if( NO_ERR != spi_WriteByteToSPI( SPI_RDID, MSBF ) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	// This is a dummy read which pulls in the
	// SO data clocked in from the write.
	if( NO_ERR != spi_ReadByteFromSPI(&wWord, MSBF) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	// this is the real data after the write
	if( NO_ERR != spi_ReadByteFromSPI(pnManCode, MSBF) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

#if 0			//实际测试第二个字节即为设备ID，不需要再接收一个无效数据，故屏蔽此行；
				//S25FL164K 使用9F读ID时：data1：Manufacturer ID = 0x01;
				//					  data2:Device Type = 0x40;
				//					  data3:Capacity = 0x17   --DONG_zw  2018-05-24
	// This is a dummy read which pulls in the
	// SO data clocked in from the write.
	if( NO_ERR != spi_ReadByteFromSPI(&wWord, MSBF) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}
#endif
	// this is the real data after the write
	if( NO_ERR != spi_ReadByteFromSPI(pnDevCode, MSBF) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	spi_Clear_CS();

	return spi_ResetFlash(ulAddr);
}


/***************************************
 ** Function Name:spi_GetSectorNumber
 ** Description:Gets a sector number based on the offset.
 ** Input:
			unsigned long ulAddr - absolute address
			int 	 *pnSector     - pointer to sector number
 ** Output:None
 ** Return:
			ERROR_CODE - value if any error occurs
    		NO_ERR     - otherwise
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_GetSectorNumber( unsigned long ulAddr, int *pnSector )
{
	int nSector = 0;
	int i;
	int error_code = 1;
	unsigned long ulMask;					//offset mask
	unsigned long ulOffset;					//offset
	unsigned long ulStartOff;
	unsigned long ulEndOff;

	ulMask      	  = 0x7ffffff;
	ulOffset		  = ulAddr & ulMask;

	for(i = 0; i < NUM_SECTORS; i++)
	{
	    spi_GetSectorStartEnd(&ulStartOff, &ulEndOff, i);
		if ( (ulOffset >= ulStartOff)
			&& (ulOffset <= ulEndOff) )
		{
			error_code = 0;
			nSector = i;
			break;
		}
	}

	
	if (error_code == 0)
		*pnSector = nSector;    // if it is a valid sector, set it
	else
		return INVALID_SECTOR;  // else it is an invalid sector

	return NO_ERR;
}

/***************************************
 ** Function Name:spi_GetSectorStartEnd
 ** Description:Gets a sector start and end address based on the sector number.
 ** Input:unsigned long *ulStartOff - pointer to the start offset
		  unsigned long *ulEndOff - pointer to the end offset
		  int nSector - sector number
 ** Output:None
 ** Return:
  	      ERROR_CODE - value if any error occurs
    	  NO_ERR     - otherwise

 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_GetSectorStartEnd( unsigned long *ulStartOff, unsigned long *ulEndOff, int nSector )
{
	unsigned long ulSectorSize = 0x10000;

	if( ( nSector >= 0 ) && ( nSector < NUM_SECTORS ) ) // 32 sectors
	{
		*ulStartOff = nSector * ulSectorSize;
		*ulEndOff = ( (*ulStartOff) + ulSectorSize - 1 );
	}
	else
	{
		return INVALID_SECTOR;
	}

	return NO_ERR;
}

/***************************************
 ** Function Name:spi_GetFlashStartAddress
 ** Description:Gets flash start address from an absolute address.
 ** Input:absolute address
 ** Output:None
 ** Return:Flash start address
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static unsigned long spi_GetFlashStartAddress( unsigned long ulAddr)
{

	ERROR_CODE 	  ErrorCode = NO_ERR;		//tells us if there was an error erasing flash
	unsigned long ulFlashStartAddr;			//flash start address

	ulFlashStartAddr  =  0;

	return(ulFlashStartAddr);
}


/***************************************
 ** Function Name:spi_ReadByteFromSPI
 ** Description:get SPI status
 ** Input:None
 ** Output:None
 ** Return:Staus of the register
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_ReadStatusRegister(int *pStatus)
{
	int wWord = 0;

	// clear the RX buffer
	*pSPICTL |= (RXFLSH);
	asm("nop;");
	asm("nop;");
	asm("nop;");

	spi_Assert_CS();

	if( NO_ERR != spi_WriteByteToSPI( SPI_RDSR, MSBF ) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	// This is a dummy read which pulls in the
	// SO data clocked in from the write.
	if( NO_ERR != spi_ReadByteFromSPI(pStatus, MSBF) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	// this is the real data after the write
	if( NO_ERR != spi_ReadByteFromSPI(pStatus, MSBF) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	spi_Clear_CS();

	return NO_ERR;

}

/***************************************
 ** Function Name:spi_ReadByteFromSPI
 ** Description:Writes one byte to the SPI port
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_WriteByteToSPI(const int byByte, const int msb_lsb)
{
	int nTimeOut = 100000;
	int n;

	if( NO_ERR != spi_Wait_For_SPIF() )
	{
		return POLL_TIMEOUT;
	}

	while( (TXS & *pSPISTAT) )
	{
		if( nTimeOut-- < 0 )
		{
			return POLL_TIMEOUT;
		}
	}

	//*pSPICTL = (SPIEN|SPIMS|SENDZ|TIMOD1|WL8|msb_lsb);
	*pSPICTL = (SPIEN|SPIMS|SENDZ|TIMOD1|WL8|msb_lsb|CPHASE|CLKPL);
	asm("nop;");
	asm("nop;");
	asm("nop;");

	*pTXSPI = byByte;

	if( NO_ERR != spi_Wait_For_SPIF() )
	{
		return POLL_TIMEOUT;
	}
	return NO_ERR;
}

/***************************************
 ** Function Name:spi_ReadByteFromSPI
 ** Description:Reads one byte from the SPI port
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_ReadByteFromSPI(int *pbyByte, const int msb_lsb)
{
	int nTimeOut = 1000;

	if( NO_ERR != spi_Wait_For_SPIF() )
	{
		return POLL_TIMEOUT;
	}


	// don't read until there is something to read.
	nTimeOut = 1000;
	while( !(RXS & *pSPISTAT) )
	{
		if( nTimeOut-- < 0 )
		{
			return POLL_TIMEOUT;
		}
	}

	*pSPICTL = (SPIEN|SPIMS|SENDZ|WL8|msb_lsb|CPHASE|CLKPL);
	//*pSPICTL = (SPIEN|SPIMS|SENDZ|WL8|msb_lsb);

	asm("nop;");
	asm("nop;");
	asm("nop;");
	*pbyByte = *pRXSPI;

	return NO_ERR;

}

/***************************************
 ** Function Name:spi_Assert_CS
 ** Description:open select signal
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static void spi_Assert_CS(void)
{
	//Then control the level of flag 4
	sysreg_bit_clr( sysreg_FLAGS, FLG4 );  //logic low

	*pSPIBAUD = BAUD_RATE_DIVISOR;

}

/***************************************
 ** Function Name:spi_Clear_CS
 ** Description:clear select signal
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static void spi_Clear_CS(void)
{
	int nTimeOut = 5000;
	while( !(SPIFE & *pSPISTAT) )
	{
		if( nTimeOut-- < 0 )
		{
			return ;
		}
	}

	//Then control the level of flag 4
	sysreg_bit_set( sysreg_FLAGS, FLG4 );  //Logic high

	*pSPIBAUD = 0;
	*pSPICTL = 0;

}


/***************************************
 ** Function Name:spi_Wait_For_SPIF
 ** Description:Polls the SPIF bit of SPISTAT until the transfer is complete.
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/
static ERROR_CODE spi_Wait_For_SPIF(void)
{

	int nTimeout = 10000;
	// status updates can be delayed up to 10 cycles
	// so wait at least 10 cycles before even
	// checking them

	// make sure nothing is waiting to be sent
	while( !(SPIF & *pSPISTAT) )
	{
		if( nTimeout-- < 0 )
		{
			return POLL_TIMEOUT;
		}
	}
	//*pSPICTL = 0;
	return NO_ERR;

}



/***************************************
 ** Function Name:spi_SendSingleCommand
 ** Description:Send Command to SPI flash
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/
static ERROR_CODE spi_SendSingleCommand( const int iCommand )
{

	spi_Assert_CS();

	if( NO_ERR != spi_WriteByteToSPI( iCommand, MSBF ) )
	{
		spi_Clear_CS();
		return POLL_TIMEOUT;
	}

	spi_Clear_CS();

	return NO_ERR;

}

/***************************************
 ** Function Name:spi_SendSingleCommand
 ** Description:Polls the RDY (Write In Progress) bit of the Flash's status	register until the Flash is finished with its access.
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-15
***************************************/

static ERROR_CODE spi_Wait_For_RDY( void )
{
	int nTimeout = 10000;
	int iTest;

	while(nTimeout-- > 0)
	{
		spi_ReadStatusRegister(&iTest);
		if( !(iTest & NRDY) )
		{
			return NO_ERR;
		}
	};


	// we can return
	return POLL_TIMEOUT;
}


