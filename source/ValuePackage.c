#include "ValuePackage.h"

/**
 * @author Zhijie Xia
 * @date Apri/03/2021
 * UCID: 30096991
 */

/**
 * @brief return the random integer between lower bound and upper bound
 * @retval a random integer between lower and upper
 */
int RandomNumber(int lower, int upper)
{
    return rand() % (upper - lower + 1) + lower;
}

/**
 * @brief update the states that relavant to the value packages
 */
void updatePackage(GameState *theGame)
{

    // calculate the time passed after the game is started
    int thisTime = (time(0) - theGame->startTime) / 10;
    // if the game started more thant 30s and 10s has passed since last random Package showed up
    if (thisTime != theGame->package->lastUpdate && thisTime >= 3)
    {
        // new random packages show up on screen
        randomPackage(theGame);
        // mark the current time
        theGame->package->lastUpdate = thisTime;
    }
    // check whether the hard working frog reaches the value package
    reachPackage(theGame);
}

/**
 * @brief remove all value package from the screen 
 */
void restPackage(GameState *theGame)
{
    for (int i = 0; i < 4; i++)
    {
        // simply set theGame.package[i] as zero which indicate the package is not on screen
        theGame->package->on[i] = 0;
    }
}

/**
 * @brief create random value packages on the screen in different challenges / areas
 *  
 */
void randomPackage(GameState *theGame)
{
    // init which challenges the value package should appear
    int pack1, pack2;
    pack1 = RandomNumber(0, 1);
    pack2 = RandomNumber(2, 3);

    // remove all other packages from the screen
    restPackage(theGame);

    // put up new packages
    theGame->package->on[pack1] = 1;
    theGame->package->on[pack2] = 1;

    // init the packages' specific position in the lane
    theGame->package->packages[pack1].x = RandomNumber(0, BOUNDARY_WIDTH - CELL_PIXEL);
    theGame->package->packages[pack2].x = RandomNumber(0, BOUNDARY_WIDTH - CELL_PIXEL);

    // if the pack1 at challenge one
    if (pack1 == 0)
    {
        // at 17<=lane<=21
        theGame->package->lane[pack1] = RandomNumber(17, 21);
    }
    else // if the pack1 at challenge two
    {    // at 12<=lane<=15
        theGame->package->lane[pack1] = RandomNumber(12, 15);
    }
    // if the pack2 at challenge three
    if (pack2 == 2)
    {
        // at 7<=lane<=10
        theGame->package->lane[pack2] = RandomNumber(7, 10);
    }
    else // if the pack2 at challenge four
    {
        // at 1<=lane<=5
        theGame->package->lane[pack2] = RandomNumber(1, 5);
    }
}

/**
 * @brief check which the frog reached a package and reward if so
 * @retval
 */
void reachPackage(GameState *theGame)
{
    int reached = -1;
    // select different packages
    for (int i = 0; i < 4; i++)
    {
        {
            // check whether the frog reaches the current selected packages
            if (theGame->package->on[i] == 1 && theGame->package->lane[i] == theGame->theFrog->lane)
            {
                if (theGame->package->packages[i].x <= theGame->theFrog->x &&
                    theGame->theFrog->x <= (theGame->package->packages[i].x + CELL_PIXEL))
                {
                    // if so, mark the package number
                    reached = i;
                }
                if (theGame->package->packages[i].x <= (theGame->theFrog->x + CELL_PIXEL) &&
                    (theGame->theFrog->x + CELL_PIXEL) <= (theGame->package->packages[i].x + CELL_PIXEL))
                {
                    // if so, mark the package number
                    reached = i;
                }
            }
        }
    }

    // reward depends on which package reached
    switch (reached)
    {
    case 0:
        if (theGame->theFrog->life < 9)
        {
            theGame->theFrog->life += 1;
        }
        break;

    case 1:
        theGame->theFrog->score += 50;
        break;

    case 2:
        theGame->theFrog->moveLeft += 30;
        break;

    case 3:
        if (theGame->theFrog->timeLeft + 20 < 100)
        {
            theGame->theFrog->timeLeft += 20;
        }
        else
        {
            theGame->theFrog->timeLeft = 99;
        }
        break;

    default:
        break;
    }
    // no reward, if none is reached
    if (reached != -1)
    {
        theGame->package->on[reached] = 0;
    }
}