#ifndef SRC_MSPI_MSPI_PRIVATE_H_
#define SRC_MSPI_MSPI_PRIVATE_H_

static void  SPIB_cfg(void);
static void  SPIB_irq_cfg(void);
static  void  SPIB_isr( uint32_t iid, void *handlerarg);
static  void  SPIB_irq_init(void);
static ERROR_CODE Wait_For_SPIBF(void);

#endif
