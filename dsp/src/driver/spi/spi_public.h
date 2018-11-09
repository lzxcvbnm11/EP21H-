#ifndef  _SPI_PUBLIC_H_
#define  _SPI_PUBLIC_H_


//#include "../common/public.h"

ERROR_CODE SPI_Read( unsigned int *pusData,
                      unsigned long ulStartAddress,
                      unsigned int uiCount );
ERROR_CODE SPI_Write( unsigned int *pusData,
                       unsigned long ulStartAddress,
                       unsigned int uiCount );
int SPI_TestFlash(void);

int SPI_init(void);
#endif
