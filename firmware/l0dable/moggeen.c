#include <sysinit.h>
#include <stdlib.h>

#include "basic/basic.h"
#include "basic/config.h"

#include "usetable.h"

// Liberated from ARM Cortex M3 CMSIS core_cm3.h
// The processor definition headers for R0ket are incomplete :-/

#define __I
#define __IO volatile

typedef struct {
	__I uint32_t CPUID; /*!< Offset: 0x000 (R/ )  CPU ID Base Register                                  */
	__IO uint32_t ICSR; /*!< Offset: 0x004 (R/W)  Interrupt Control State Register                      */
	__IO uint32_t VTOR; /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
	__IO uint32_t AIRCR; /*!< Offset: 0x00C (R/W)  Application Interrupt / Reset Control Register        */
	__IO uint32_t SCR; /*!< Offset: 0x010 (R/W)  System Control Register                               */
	__IO uint32_t CCR; /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
	__IO uint8_t SHP[12]; /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
	__IO uint32_t SHCSR; /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
	__IO uint32_t CFSR; /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
	__IO uint32_t HFSR; /*!< Offset: 0x02C (R/W)  Hard Fault Status Register                            */
	__IO uint32_t DFSR; /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
	__IO uint32_t MMFAR; /*!< Offset: 0x034 (R/W)  Mem Manage Address Register                           */
	__IO uint32_t BFAR; /*!< Offset: 0x038 (R/W)  Bus Fault Address Register                            */
	__IO uint32_t AFSR; /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
	__I uint32_t PFR[2]; /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
	__I uint32_t DFR; /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
	__I uint32_t ADR; /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
	__I uint32_t MMFR[4]; /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
	__I uint32_t ISAR[5]; /*!< Offset: 0x060 (R/ )  ISA Feature Register                                  */
} SCB_Type;

#define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address */
#define SCB                 ((SCB_Type *)           SCB_BASE)         /*!< SCB configuration struct          */

uint32_t VectorTableInRAM[73] __attribute__ ((aligned(1024))); // VTOR needs 1024 Byte alignment, see UM10375.PDF

void tmr16_0_irqh(void);             // 16 bit timer #0 irq handler
void (*orig_handler_tmr16b0)(void);  // original 16 bit timer #0 handler


void ram(void)
{
  // populate my Vector table
  memcpy(VectorTableInRAM, 0, sizeof(VectorTableInRAM));
  orig_handler_tmr16b0 = (void*) VectorTableInRAM[TIMER_16_0_IRQn + 16];
  VectorTableInRAM[TIMER_16_0_IRQn + 16] = (uint32_t) &tmr16_0_irqh;
  // HACK: use RAM vector table to implement own External IRQ handler
  SCB->VTOR = (uint32_t) &VectorTableInRAM[0];

  gpioSetDir(RB_SPI_SS2, gpioDirection_Output);
  SCB_SYSAHBCLKCTRL|= SCB_SYSAHBCLKCTRL_CT16B0;
  TMR_TMR16B0PR= 44;
  TMR_TMR16B0MR0= 9;
  TMR_TMR16B0MCR= TMR_TMR16B0MCR_MR0_RESET_ENABLED | TMR_TMR16B0MCR_MR0_INT_ENABLED;
  TMR_TMR16B0TCR= TMR_TMR16B0TCR_COUNTERENABLE_ENABLED;
  NVIC_EnableIRQ(TIMER_16_0_IRQn);

  uint8_t in;
  while ((in= getInputRaw()) != BTN_ENTER)
  {
    if (BTN_UP == in)
    {
      gpioSetValue(RB_LED0, 1);
      gpioSetValue(RB_LED1, 1);
      gpioSetValue(RB_LED2, 1);
    }
    if (BTN_DOWN == in)
    {
      gpioSetValue(RB_LED0, 0);
      gpioSetValue(RB_LED1, 0);
      gpioSetValue(RB_LED2, 0);
    }
  }
  NVIC_DisableIRQ(TIMER_16_0_IRQn);
  TMR_TMR16B0TCR &= ~TMR_TMR16B0TCR_COUNTERENABLE_ENABLED;
  TMR_TMR16B0TCR |= TMR_TMR16B0TCR_COUNTERRESET_ENABLED;
  TMR_TMR16B0MCR &= ~(TMR_TMR16B0MCR_MR0_RESET_ENABLED | TMR_TMR16B0MCR_MR0_INT_ENABLED);
  TMR_TMR16B0TCR &= ~TMR_TMR16B0TCR_COUNTERRESET_ENABLED;
  // restore VTOR
  SCB->VTOR = 0;
  //TODO DMB(); Cortex Manual suggests DMB after setting VTOR
  // not really needed in this case
}

void tmr16_0_irqh(void)
{
  TMR_TMR16B0IR|= TMR_TMR16B0IR_MR0;
  // SPI22 is port 2 pin 8
  volatile uint32_t *spi22writeaddr= (uint32_t *)GPIO_GPIO2_BASE + (1<<8);
  *spi22writeaddr= 1<<8;
  //__sync_synchronize();
  *spi22writeaddr= 0;
  //__sync_synchronize();
}
