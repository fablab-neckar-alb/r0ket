#include <sysinit.h>
#include "basic/basic.h"
#include "lcd/render.h"
void backlightInit(void);

void main_cereal(void) {
  int y= 20;
  DoString(0,y,"Ur-Huara-");
  DoString(0,y+getFontHeight()+4,"Schiissdraeck!");
  lcdDisplay();
  char c= 0;
  while (1) {
    gpioSetValue(RB_LED0, c&1);
    gpioSetValue(RB_LED1, (c>>1)&1);
    gpioSetValue(RB_LED2, (c>>2)&1);
    // for some reason, RB_LED3 seems to be unusable
    delayms(200);
    c++;
  }
}
