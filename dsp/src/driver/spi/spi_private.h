#ifndef  _SPI_PRIVATE_H_
#define  _SPI_PRIVATE_H_


//#include "../../common/flash.h"

/* flash commands */
#define SPI_WREN            (0x06)  //Set Write Enable Latch
#define SPI_WRDI            (0x04)  //Reset Write Enable Latch
#define SPI_RDID            (0x9F)  //Read Identification
#define SPI_RDSR            (0x05)  //Read Status Register
#define SPI_WRSR            (0x01)  //Write Status Register
#define SPI_READ            (0x03)  //Read data from memory
#define SPI_FAST_READ       (0x0B)  //Read data from memory
#define SPI_PP              (0x02)  //Program Data into memory
#define SPI_SE              (0xD8)  //Erase one sector in memory
#define SPI_BE              (0xC7)  //Erase all memory
#define WIP                  (0x1)	//Check the write in progress bit of the SPI status register
#define WEL                  (0x2)	//Check the write enable bit of the SPI status register

#define SPI_PAGE_SIZE		(528)
#define SPI_SECTORS		    (512)
#define SPI_SECTOR_SIZE		(4224)
#define SPI_SECTOR_DIFF		(3968)
#define PAGE_BITS			(10)
#define PAGE_SIZE_DIFF		(496)

#define DELAY				300
#define TIMEOUT        		35000*64


#define NRDY				BIT_0
#define BAUD_RATE_DIVISOR 	(2<<1)	//(8<<1)

#define PAGE_LENGTH				64  //(in 32-bit words)
#define NUM_SECTORS 			32	/* number of sectors in the flash device */

#define MAN_CODE		0x9d
#define DEV_CODE		0x60
//#define MAN_CODE		0xc8
//#define DEV_CODE		0x40

/* Get-Codes data type */
typedef struct Get_Codes_Struct
{
	unsigned long	*pManCode;
	unsigned long	*pDevCode;
	unsigned long 	ulFlashStartAddr;

}GET_CODES_STRUCT;

/* Reset data type */
typedef struct Reset_Struct
{
 	unsigned long 	ulFlashStartAddr;

}RESET_STRUCT;

/* Erase-All data type */
typedef struct Erase_All_Struct
{
 	unsigned long 	ulFlashStartAddr;

}ERASE_ALL_STRUCT;

/* Erase-Sector data type */
typedef struct Erase_Sector_Struct
{
 	int 			nSectorNum;
 	unsigned long 	ulFlashStartAddr;

}ERASE_SECTOR_STRUCT;


/* Get-Sector-Number data type */
typedef struct Get_SectNum_Struct
{
	unsigned long	ulOffset;
	unsigned long	*pSectorNum;

}GET_SECTNUM_STRUCT;

/* Get-Sector-Start-End data type */
typedef struct Get_SectStartEnd_Struct
{
	int 	nSectorNum;
	unsigned long	*pStartOffset;
	unsigned long	*pEndOffset;

}GET_SECTSTARTEND_STRUCT;

/* Get-Description data type */
typedef struct Get_Desc_Struct
{
	char	*pTitle;
	char	*pDesc;
	char 	*pFlashCompany;

}GET_DESC_STRUCT;

/* Get-Num Sectors data type */
typedef struct Get_NumSectors_Struct
{
	int		*pnNumSectors;

}GET_NUM_SECTORS_STRUCT;

/* Get-Flash-Width data type */
typedef struct Get_Flash_Width_Struct
{
	int		*pnFlashWidth;

}GET_FLASH_WIDTH_STRUCT;

/* Supports-CFI data type */
typedef struct Supports_CFI_Struct
{
	bool	*pbSupportsCFI;

}SUPPORTS_CFI_STRUCT;

/* Get-CFI-Data data type */
typedef struct Get_CFI_Data_Struct
{
	void *pCFIData;
	unsigned long 	ulFlashStartAddr;

}GET_CFI_DATA_STRUCT;


/* union describing all the data types */
typedef union
{
	ERASE_ALL_STRUCT		SEraseAll;
	ERASE_SECTOR_STRUCT		SEraseSect;
	GET_CODES_STRUCT		SGetCodes;
	GET_DESC_STRUCT			SGetDesc;
	GET_SECTNUM_STRUCT		SGetSectNum;
	GET_SECTSTARTEND_STRUCT SSectStartEnd;
	RESET_STRUCT			SReset;
	GET_NUM_SECTORS_STRUCT	SGetNumSectors;
	GET_FLASH_WIDTH_STRUCT	SGetFlashWidth;
	SUPPORTS_CFI_STRUCT		SSupportsCFI;
	GET_CFI_DATA_STRUCT		SGetCFIData;
}COMMAND_STRUCT;

/* enum describing the flash width */
typedef enum
{
	_FLASH_WIDTH_8 = 1,
	_FLASH_WIDTH_16 = 2,
	_FLASH_WIDTH_32 = 4,
	_FLASH_WIDTH_64 = 8

} enFlashWidth;


/* enum for adi_pdd_control */
typedef enum
{
	CNTRL_GET_CODES,		/* 0 - gets manufacturer and device IDs */
	CNTRL_RESET,			/* 1 - resets device */
	CNTRL_ERASE_ALL,		/* 2 - erase entire device */
	CNTRL_ERASE_SECT,		/* 3 - erase a sector */
	CNTRL_GET_SECTNUM,		/* 4 - get sector number */
	CNTRL_GET_SECSTARTEND,	/* 5 - get sector start and end addresses */
	CNTRL_GET_DESC,			/* 6 - get device description */
	CNTRL_GETNUM_SECTORS,	/* 7 - get number of sectors in device */
	CNTRL_GET_FLASH_WIDTH,	/* 8 - get the flash width */
	CNTRL_SUPPORTS_CFI,		/* 9 - does the device support CFI? */
	CNTRL_GET_CFI_DATA		/* 10 - gets CFI data */
} enCntrlCmds;



static ERROR_CODE spi_SetBuadRate(void);
static ERROR_CODE spi_SetupForFlash(void);
static ERROR_CODE spi_Close(void);
ERROR_CODE spi_Control(  unsigned int uiCmd,COMMAND_STRUCT *pCmdStruct);
static ERROR_CODE spi_ResetFlash(unsigned long ulAddr);
static ERROR_CODE spi_EraseFlash(unsigned long ulAddr);
static ERROR_CODE spi_EraseBlock( int nBlock, unsigned long ulAddr );
static ERROR_CODE spi_GetCodes(int *pnManCode, int *pnDevCode, unsigned long ulAddr);
static ERROR_CODE spi_GetSectorNumber( unsigned long ulAddr, int *pnSector );
static ERROR_CODE spi_GetSectorStartEnd( unsigned long *ulStartOff, unsigned long *ulEndOff, int nSector );
static unsigned long spi_GetFlashStartAddress( unsigned long ulAddr);
static ERROR_CODE spi_ReadStatusRegister(int *pStatus);
static ERROR_CODE spi_WriteByteToSPI(const int byByte, const int msb_lsb);
static ERROR_CODE spi_ReadByteFromSPI(int *pbyByte, const int msb_lsb);
static void spi_Assert_CS(void);
static void spi_Clear_CS(void);
static ERROR_CODE spi_Wait_For_SPIF(void);
static ERROR_CODE spi_SendSingleCommand( const int iCommand );
static ERROR_CODE spi_Wait_For_RDY( void );









#endif

