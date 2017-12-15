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
  lcdPrintln("Moggeeen");
  lcdPrintln(GLOBAL(nickname));
  lcdRefresh();
  while (getInputRaw() != BTN_ENTER);
}
