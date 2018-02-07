#include <sysinit.h>
#include "basic/basic.h"
#include "lcd/render.h"
void backlightInit(void);

void main_cereal(void) {
  int y= 20;
  DoString(0,y,"Ur-Huara-");
  DoString(0,y+getFontHeight()+4,"Schiissdraeck!");
  lcdDisplay();
  gpioSetDir(RB_HB0, gpioDirection_Input);
  gpioSetDir(RB_HB1, gpioDirection_Input);
  gpioSetDir(RB_HB2, gpioDirection_Input);
  //gpioSetDir(RB_HB3, gpioDirection_Input);
  //gpioSetDir(RB_HB4, gpioDirection_Input);
  //gpioSetDir(RB_HB5, gpioDirection_Input);
  while (1) {
    gpioSetValue(RB_LED0, gpioGetValue(RB_HB0));
    gpioSetValue(RB_LED1, gpioGetValue(RB_HB1));
    gpioSetValue(RB_LED2, gpioGetValue(RB_HB2));
  }
}
