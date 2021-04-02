#ifndef RENDER_H
#define RENDER_H
#include "structdef.h"


void renderMap(GameState *theGame);

void renderFrog(GameState *theGame);

void renderTime(GameState *theGame);

void renderPause(GameState *theGame);

void renderScreen(GameState *theGame);

void render(int lower,GameState *theGame);

#endif