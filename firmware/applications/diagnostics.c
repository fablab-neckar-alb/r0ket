#include <sysinit.h>
#include "basic/basic.h"
#include "lcd/render.h"
void backlightInit(void);

/*
 For handling GPIO IRQs, see l0dable/Geigerct.c 

But maybe let's try timer IRQs first ...
*/
void main_diagnostics(void)
{
  backlightInit();
  while (1)
  {
    lcdClear();
    lcdPrintln("MEMREMAP");
    lcdPrintln(IntToStr(SCB_MEMREMAP,8,F_HEX));
    lcdPrintln("ISER0");
    lcdPrintln(IntToStr(NVIC->ISER[0],8,F_HEX));
    lcdPrintln("ISER1");
    lcdPrintln(IntToStr(NVIC->ISER[1],8,F_HEX));
    lcdRefresh();
    delayms(200);
  }
}
