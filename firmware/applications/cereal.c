#include <sysinit.h>
#include "basic/basic.h"
#include "lcd/render.h"
void backlightInit(void);

void main_cereal(void) {
  int y= 20;
  DoString(0,y,"Ur-Huara-");
  DoString(0,y+getFontHeight()+4,"Schiissdraeck!");
  lcdDisplay();
  while (1) {}
}
