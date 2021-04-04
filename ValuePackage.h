#ifndef VALUEPACK_H
#define VALUEPACK_H
#include "structdef.h"
#include <stdlib.h>
#include <time.h>

int RandomNumber(int lower, int upper);

void updatePackage(GameState *theGame);

void restPackage(GameState *theGame);

void randomPackage(GameState *theGame);

void reachPackage(GameState *theGame);
#endif