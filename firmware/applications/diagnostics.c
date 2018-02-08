#include <sysinit.h>
#include "basic/basic.h"
//#include "lcd/render.h"
#include "lcd/print.h"

/*
 For handling GPIO IRQs, see l0dable/Geigerct.c 

But maybe let's try timer IRQs first ...
*/
void main_diagnostics(void)
{
  static uint8_t blink= 0;
  gpioSetDir(RB_LED1, gpioDirection_Output);
  SCB_SYSAHBCLKCTRL|= SCB_SYSAHBCLKCTRL_CT16B0;
  TMR_TMR16B0PR= 0xFFFF;
  TMR_TMR16B0MR0= 0x2000;
  TMR_TMR16B0MCR= TMR_TMR16B0MCR_MR0_RESET_ENABLED;
  TMR_TMR16B0TCR= TMR_TMR16B0TCR_COUNTERENABLE_ENABLED;
  while (1)
  {
    lcdClear();
    lcdPrintln("ISER1");
    lcdPrintln(IntToStr(NVIC->ISER[1],8,F_HEX));
    lcdPrintln("TMR16B0");
    lcdPrint("MCR ");
    lcdPrintln(IntToStr(TMR_TMR16B0MCR,8,F_HEX));
    lcdPrint("PR ");
    lcdPrintln(IntToStr(TMR_TMR16B0PR,4,F_HEX));
    lcdPrint("PC ");
    lcdPrintln(IntToStr(TMR_TMR16B0PC,4,F_HEX));
    lcdPrint("TC ");
    lcdPrintln(IntToStr(TMR_TMR16B0TC,4,F_HEX));
    lcdRefresh();
    //delayms(200);
    blink= (TMR_TMR16B0TC >= 0x1000);
    gpioSetValue(RB_LED1, blink);
  }
}

/*
void TIMER16_0_IRQHandler(void)
{
  static uint8_t blink= 0;
  TMR_TMR16B0IR= TMR_TMR16B0IR_MR0;
  gpioSetValue(RB_LED1, ~blink);
}
*/
