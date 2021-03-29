#ifndef MapF_H
#define MapF_H
#include "structdef.h"

void initMap(Map *theMap);

void updateMap(Map *theMap, int upper, int lower);

void cellKeepInRange(Cell *outRange);

#endif