#include "ValuePackage.h"

int RandomNumber(int lower, int upper)
{
    return rand() % (upper - lower + 1) + lower;
}

void updatePackage(GameState *theGame)
{
    int thisTime =(time(0)-theGame->startTime)/10;

    if(thisTime!=theGame->package->lastUpdate&&thisTime>=3){
        randomPackage(theGame);
        theGame->package->lastUpdate=thisTime;
    }
    reachPackage(theGame);
}


void restPackage(GameState *theGame)
{
    for (int i = 0; i < 4; i++)
    {
        theGame->package->on[i] = 0;
    }
}


void randomPackage(GameState *theGame)
{
    int pack1, pack2;
    pack1 = RandomNumber(0, 1);
    pack2 = RandomNumber(2, 3);
    restPackage(theGame);
    theGame->package->on[pack1] = 1;
    theGame->package->on[pack2] = 1;
    theGame->package->packages[pack1].x = RandomNumber(0, BOUNDARY_WIDTH - CELL_PIXEL);
    theGame->package->packages[pack2].x = RandomNumber(0, BOUNDARY_WIDTH - CELL_PIXEL);
    if (pack1 == 0)
    {
        theGame->package->lane[pack1] = RandomNumber(17, 21);
    }
    else
    {
        theGame->package->lane[pack1] = RandomNumber(12, 15);
    }
    if (pack2 == 2)
    {
        theGame->package->lane[pack2] = RandomNumber(7, 10);
    }
    else
    {
        theGame->package->lane[pack2] = RandomNumber(1, 5);
    }
}


void reachPackage(GameState *theGame)
{
    int reached = -1;
    for (int i = 0; i < 4; i++)
    {
        {
            if (theGame->package->on[i] == 1 && theGame->package->lane[i]==theGame->theFrog->lane)
            {
                if (theGame->package->packages[i].x <= theGame->theFrog->x && 
                theGame->theFrog->x <= (theGame->package->packages[i].x + CELL_PIXEL))
                {
                    reached = i;
                }
                if (theGame->package->packages[i].x <= (theGame->theFrog->x + CELL_PIXEL) && 
                (theGame->theFrog->x + CELL_PIXEL) <= (theGame->package->packages[i].x + CELL_PIXEL))
                {
                    reached = i;
                }
            }
        }
    }
    switch (reached)
    {
    case 0:
        theGame->theFrog->life += 1;
        break;

    case 1:
        theGame->theFrog->score += 50;
        break;

    case 2:
        theGame->theFrog->moveLeft += 30;
        break;

    case 3:
        theGame->theFrog->timeLeft += 20;
        break;

    default:
        break;
    }
    if(reached!=-1){
        theGame->package->on[reached]=0;
    }
}