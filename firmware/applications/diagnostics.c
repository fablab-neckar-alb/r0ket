#include <sysinit.h>
#include "basic/basic.h"

/*
  Let's try timer IRQs,
  absolute bare bones version
*/
void main_diagnostics(void)
{
  gpioSetDir(RB_SPI_SS2, gpioDirection_Output);
  SCB_SYSAHBCLKCTRL|= SCB_SYSAHBCLKCTRL_CT16B0;
  TMR_TMR16B0PR= 44;
  TMR_TMR16B0MR0= 9;
  TMR_TMR16B0MCR= TMR_TMR16B0MCR_MR0_RESET_ENABLED | TMR_TMR16B0MCR_MR0_INT_ENABLED;
  TMR_TMR16B0TCR= TMR_TMR16B0TCR_COUNTERENABLE_ENABLED;
  NVIC_EnableIRQ(TIMER_16_0_IRQn);
}

void TIMER16_0_IRQHandler(void)
{
  gpioSetValue(RB_SPI_SS2, 1);
  gpioSetValue(RB_SPI_SS2, 0);
  TMR_TMR16B0IR|= TMR_TMR16B0IR_MR0;
}
