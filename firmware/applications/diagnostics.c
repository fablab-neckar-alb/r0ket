#include <sysinit.h>
#include "basic/basic.h"
#include "lcd/render.h"

/*
 For handling GPIO IRQs, see l0dable/Geigerct.c 

But maybe let's try timer IRQs first ...
*/
void main_diagnostics(void)
{
  backlightInit();
  //TMR_TMR16B0TCR= TMR_TMR1BB0TCR_COUNTERENABLE_ENABLED;
  while (1)
  {
    lcdClear();
    lcdPrintln("ISER1");
    lcdPrintln(IntToStr(NVIC->ISER[1],8,F_HEX));
    lcdPrintln("TMR16B0 ctrl");
    lcdPrintln(IntToStr(TMR_TMR16B0TCR,8,F_HEX));
    lcdPrintln("TMR16B0 count ");
    lcdPrintln(IntToStr(TMR_TMR16B0TC,8,F_HEX));
    lcdRefresh();
    //delayms(200);
  }
}
