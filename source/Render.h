#ifndef RENDER_H
#define RENDER_H
#include "structdef.h"
#include <unistd.h>
#include <stdlib.h>

void renderMap(GameState *theGame);

void renderFrog(GameState *theGame);

void renderTime(GameState *theGame);

void renderScreen(GameState *theGame);

void renderValuePackage(GameState *theGame);

void renderMainMenu(GameState *theGame, int state);

void renderPause(GameState *theGame,int state);

void renderWin(GameState *theGame);

void renderLose(GameState *theGame);

void renderScore(GameState *theGame);

void renderMovement(GameState *theGame);

void renderLive(GameState *theGame);

void renderInforBar(GameState *theGame);

void renderInforTitle(GameState *theGame);
#endif
