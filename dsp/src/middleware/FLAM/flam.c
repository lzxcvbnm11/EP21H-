#include "flam_info.inc"
#include "../../ENG_SPEECH.h"
//#define Begin_Address 0x70000  //mapping address




/***************************************
 ** Function Name:SPI_Flash_Init
 ** Description:initialize SPI_Flash
 ** Input:None
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
void SPI_Flash_Init(void)
{
	int result;
	result = SPI_init();
	if(0 == result)
	{
		printf("SPI_Flash_Init fail");
	}
}



/***************************************
 ** Function Name:data_in
 ** Description:get data from SPI flash
 ** Input:flash_addr,len
 ** Output:data_buf
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
void data_in(u32 flash_addr, u32* data_buf, u32 len)
{
	ERROR_CODE result;
	u32 ActualAddr;

	ActualAddr = flash_addr+BEGIN_ADDR;
	result = SPI_Read( data_buf,ActualAddr,len );

	/*if(NO_ERR != result)
	{
		memcpy(data_buf,0,sizeof(data_buf));
	}*/

}



/***************************************
 ** Function Name:data_write
 ** Description:write data to SPI flash
 ** Input:flash_addr,len
 ** Output:data_buf
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
void data_write(u32 flash_addr, u32* data_buf, u32 len)
{
	ERROR_CODE result;
	u32 ActualAddr;
	COMMAND_STRUCT pCmdBuffer;				/* command buffer */

	ActualAddr = flash_addr+BEGIN_ADDR;
	pCmdBuffer.SEraseSect.ulFlashStartAddr = ActualAddr;
	pCmdBuffer.SEraseSect.nSectorNum = len;
	result = spi_Control( CNTRL_ERASE_SECT, &pCmdBuffer);

	result = SPI_Write( data_buf,ActualAddr,len );
	/*if(NO_ERR != result)
	{
		result = spi_Control( CNTRL_ERASE_SECT, &pCmdBuffer );
	}*/

}



/***************************************
 ** Function Name:data_erase
 ** Description:erase SPI flash sector
 ** Input:flash_addr,len
 ** Output:None
 ** Return:None
 ** Author:lihuan
 ** Data:2018-6-14
***************************************/
void data_erase(u32 flash_addr, u32 len)
{
	ERROR_CODE result;
	u32 ActualAddr;
	COMMAND_STRUCT pCmdBuffer;				/* command buffer */

	ActualAddr = flash_addr+BEGIN_ADDR;
	pCmdBuffer.SEraseSect.ulFlashStartAddr = ActualAddr;
	pCmdBuffer.SEraseSect.nSectorNum = len;

	result = spi_Control( CNTRL_ERASE_SECT, &pCmdBuffer);
}













