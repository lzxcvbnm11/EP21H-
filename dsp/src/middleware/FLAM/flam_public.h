#ifndef SRC_MIDDLEWARE_FLAM_FLAM_PUBLIC_H_
#define SRC_MIDDLEWARE_FLAM_FLAM_PUBLIC_H_

#include "../../ENG_SPEECH.h"

void SPI_Flash_Init(void);

void data_in(u32 flash_addr, u32* data_buf, u32 len);

void data_in(u32 flash_addr, u32* data_buf, u32 len);

void data_erase(u32 flash_addr, u32 len);

#endif
