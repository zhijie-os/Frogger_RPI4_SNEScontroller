#include "FrogFunction.h"

int Map_SPEED[MAP_SIZE] =  {0,
                               2, 3, -2, 3, -3, 0,
                               3, -3, 2, -4, 0,
                               -2, 3, -3, 3, 0,
                               -2, 3, -3, 2, -4, 0};
/**
 * @brief  Initialize the Frog
 * @note   
 * @param  *theFrog: 
 * @retval None
 */
void initFrog(Frog *theFrog)
{
    theFrog->life = 4;
    theFrog->canMove = true;
    theFrog->score = 0;
    theFrog->timeLeft = 90;
    theFrog->minimumLaneArrived = 22;
    theFrog->loseFlag = false;
    theFrog->winFlag = false;
    reviveFrog(theFrog);
}

/**
 * @brief  If frog died, and the lives are still postive, reset frog to starting position
 * @note   
 * @param  *theFrog: 
 * @retval None
 */
void reviveFrog(Frog *theFrog)
{
    if (theFrog->life > 0)
    {
        theFrog->life -= 1;
        theFrog->x = SCREEN_WIDTH / 2;
        theFrog->moveLeft = 200;
        theFrog->lane = 22;
    }
}

/**
 * @brief  Frog makes a move
 * @note   
 * @param  *theFrog: 
 * @param  *theMap: 
 * @param  dir: 
 * @retval None
 */
void updateFrog(Frog *theFrog, Map *theMap, Direction dir)
{
    if (theFrog->canMove)
    {
        moveFrog(theFrog, dir);
    }
    FrogMoveWithObject(theFrog, theMap);
    if (willFrogDie(theFrog, theMap))
    {
        if (theFrog->life <= 0)
        {
            theFrog->loseFlag = true;
        }
        else
        {
            reviveFrog(theFrog);
        }
    }
    if(theFrog->timeLeft<=0 || theFrog->moveLeft<=0){
        theFrog->loseFlag = true;
    }
    FrogOutSideScreen(theFrog);
    if (theFrog->lane < theFrog->minimumLaneArrived)
    {
        theFrog->score = theFrog->score + 10;
    }
    if(theFrog->lane==0){
        theFrog->winFlag = true;
    }
}

/**
 * @brief  Check whether Frog is overlapping with a object that can kill frog
 * @note   
 * @param  *theFrog: 
 * @param  *theMap: 
 * @retval 
 */
bool willFrogDie(Frog *theFrog, Map *theMap)
{
    for (int i = 0; i < LANE_SIZE; i++)
    {
        Cell current = theMap->lanes[theFrog->lane].cells[i];
        if (current.fatal == KillFrog)
        {
            if (current.x <= theFrog->x && theFrog->x <= (current.x + CELL_PIXEL))
            {
                return true;
            }
            if (current.x <= (theFrog->x + CELL_PIXEL) && (theFrog->x + CELL_PIXEL) <= (current.x + CELL_PIXEL))
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief  Move the frog a cell according to the direction
 * @note   
 * @param  *theFrog: 
 * @param  dir: 
 * @retval None
 */
void moveFrog(Frog *theFrog, Direction dir)
{
    switch (dir)
    {
    case Up:
        if (theFrog->lane <= MAP_SIZE - 1 && theFrog->lane > 0)
            theFrog->lane -= 1;
            theFrog->moveLeft -= 1;
        break;

    case Down:
        if (theFrog->lane > 0 && theFrog->lane < MAP_SIZE - 1)
            theFrog->lane += 1;
            theFrog->moveLeft -= 1;
        break;

    case Left:
        if (theFrog->x - CELL_PIXEL >= GAME_SCREEN_LEFT)
            theFrog->x -= CELL_PIXEL;
            theFrog->moveLeft -= 1;
        break;

    case Right:
        if (theFrog->x + CELL_PIXEL * 2 <= GAME_SCREEN_RIGHT)
            theFrog->x += CELL_PIXEL;
            theFrog->moveLeft -= 1;
        break;

    default:
        break;
    }
}

/**
 * @brief  Check whether Frog is overlapping with a object that can kill frog
 * @note   
 * @param  *theFrog: 
 * @param  *theMap: 
 * @retval 
 */
void FrogMoveWithObject(Frog *theFrog, Map *theMap)
{
    for (int i = 0; i < LANE_SIZE; i++)
    {
        Cell current = theMap->lanes[theFrog->lane].cells[i];
        if (current.fatal == SaveFrog && theFrog->lane >= 1 && theFrog->lane <= 6)
        {
            if (current.x <= theFrog->x && theFrog->x <= (current.x + CELL_PIXEL) || current.x <= (theFrog->x + CELL_PIXEL) && (theFrog->x + CELL_PIXEL) <= (current.x + CELL_PIXEL))
            {
                theFrog->x += Map_SPEED[theFrog->lane];
                break;
            }
        }
    }
}

void FrogOutSideScreen(Frog *theFrog)
{
    if (theFrog->x + CELL_PIXEL < GAME_SCREEN_LEFT || theFrog->x > GAME_SCREEN_RIGHT || theFrog->lane < 0 || theFrog->lane > 22)
    {
        reviveFrog(theFrog);
    }
}