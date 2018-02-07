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
  gpioSetValue(RB_LED0, 1);
  gpioSetValue(RB_LED1, 1);
  gpioSetValue(RB_LED2, 1);
  lcdClear();
  lcdPrintln("Moggeeeeen");
  lcdPrintln(GLOBAL(nickname));
  lcdRefresh();
  while (getInputRaw() != BTN_ENTER);
}
