
#include "structdef.h"

void moveFrog(Frog *theFrog, Direction dir);

bool willFrogDie(Frog *theFrog, Map *theMap);

void updateFrog(Frog *theFrog, Map *theMap, Direction dir);

void reviveFrog(Frog *theFrog);

void initFrog(Frog *theFrog);

void FrogMoveWithObject(Frog *theFrog, Map *theMap);

void FrogOutSideScreen(Frog *theFrog);