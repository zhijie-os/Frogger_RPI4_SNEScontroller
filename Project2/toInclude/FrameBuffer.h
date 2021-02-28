#include "structdef.h"
#include <string.h>
#ifndef FRAMEBUFFER
#define FRAMEBUFFER
/* definitions */

	
FrameBuffer *initFbInfo(void);

void drawPixel(GameState *theGame);

#endif
