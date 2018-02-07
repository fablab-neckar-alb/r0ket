#include <sysinit.h>
#include "basic/basic.h"
#include "lcd/render.h"
void backlightInit(void);

void main_cereal(void) {
  int y= 20;
  DoString(0,y,"Ur-Huara-");
  DoString(0,y+getFontHeight()+4,"Schiissdraeck!");
  lcdDisplay();
  gpioSetDir(RB_SPI_SS0, gpioDirection_Input);
  gpioSetDir(RB_SPI_SS1, gpioDirection_Input);
  gpioSetDir(RB_SPI_SS2, gpioDirection_Input);
  //gpioSetDir(RB_SPI_SS3, gpioDirection_Input);
  //gpioSetDir(RB_SPI_SS4, gpioDirection_Input);
  //gpioSetDir(RB_SPI_SS5, gpioDirection_Input);
  while (1) {
    gpioSetValue(RB_LED0, gpioGetValue(RB_SPI_SS0));
    gpioSetValue(RB_LED1, gpioGetValue(RB_SPI_SS1));
    gpioSetValue(RB_LED2, gpioGetValue(RB_SPI_SS2));
  }
}
