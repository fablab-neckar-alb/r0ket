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
  SCB_SYSAHBCLKCTRL|= SCB_SYSAHBCLKCTRL_CT16B0; 
  TMR_TMR16B0TCR= TMR_TMR16B0TCR_COUNTERENABLE_ENABLED;
  while (1)
  {
    lcdClear();
    lcdPrintln("ISER1");
    lcdPrintln(IntToStr(NVIC->ISER[1],8,F_HEX));
    lcdPrintln("TMR16B0 ctrl");
    lcdPrintln(IntToStr(TMR_TMR16B0TCR,8,F_HEX));
    lcdPrintln("TMR16B0 pre");
    lcdPrintln(IntToStr(TMR_TMR16B0PR,8,F_HEX));
    lcdPrint("PRE16B0 ");
    lcdPrintln(IntToStr(TMR_TMR16B0PC,4,F_HEX));
    lcdPrint("TMR16B0 ");
    lcdPrintln(IntToStr(TMR_TMR16B0TC,4,F_HEX));
    lcdRefresh();
    //delayms(200);
  }
}
