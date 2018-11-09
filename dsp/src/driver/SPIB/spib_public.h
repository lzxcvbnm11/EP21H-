#ifndef SRC_MSPI_MSPI_PUBLIC_H_
#define SRC_MSPI_MSPI_PUBLIC_H_
#include "../../common/flash.h"

volatile int SPIB_irq_flag;

ERROR_CODE WriteByteToSPIB(const int byByte, const int msb_lsb);
ERROR_CODE ReadByteFromSPIB(int *pbyByte, const int msb_lsb);
ERROR_CODE ReadStringFromSPIB(int *pbyByte);
ERROR_CODE WriteStringToSPIB(int *pbyByte);
ERROR_CODE SPIB_Init(void);
ERROR_CODE Send_To_Mcu(void);

int SPIB_GetInitSts(void);
/*lzx add*/
extern int SPIB_GetRxBuffFlag(void);

#define SPIB_MAXSENDBUFFSIZE    11
#endif
