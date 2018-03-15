#include <sysinit.h>
#include "basic/basic.h"
#include "lcd/render.h"
#include "usbcdc/util.h"
void main_mist(void) {
  usbCDCInit();
  int y= 20;
  DoString(0,y,"Ober-Doppel-");
  DoString(4,y+getFontHeight()+4,"MIST!!!!");
  lcdDisplay();
  for (uint16_t t=0; 1; t++) {
    puts("Ober-Doppel-Mist!!!!\n");
    printf("%04x\n", t);
    delayms(200);
  }
}
