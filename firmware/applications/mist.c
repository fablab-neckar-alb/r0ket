#include <sysinit.h>
#include "basic/basic.h"
#include "lcd/render.h"
void main_mist(void) {
  int y= 20;
  DoString(0,y,"Ober-Doppel-");
  DoString(4,y+getFontHeight()+4,"MIST!!!!");
  lcdDisplay();
  while (1) {}
}
