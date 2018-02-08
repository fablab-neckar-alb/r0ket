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
  uint32_t clockcontrol;
  while (1)
  {
    clockcontrol= SCB_SYSAHBCLKCTRL;
    lcdClear();
    lcdPrintln("SYSAHBCLKCTRL");
    lcdPrintln(IntToStr(clockcontrol,8,F_HEX));
    lcdRefresh();
    delayms(200);
  }
}
