#include <sysinit.h>
#include <string.h>
#include <stdlib.h>

#include "basic/basic.h"
#include "basic/config.h"

#include "lcd/render.h"
#include "lcd/print.h"

#include "usetable.h"

void ram(void)
{
  lcdClear();
  lcdPrintln("Moggeeeeen");
  lcdPrintln(GLOBAL(nickname));
  lcdRefresh();
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
}
