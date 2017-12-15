#include <sysinit.h>
#include "basic/basic.h"
#include "lcd/render.h"
void main_hello(void) {
    DoString(10,20,"Ober-Doppel-Mist!");
    lcdDisplay();
    while (1) {}
}
