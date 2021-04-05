#include "FrogFunction.h"
#include "MapFunction.h"

/**
 * @author Zhijie Xia
 * @date March/29/2021
 * UCID: 30096991
 * Handle the logic of the frog
 */


/**
 * @brief  Initialize the Frog
 * @note   
 * @param  *theFrog: 
 * @retval None
 */
void initFrog(Frog *theFrog)
{
    // initalize the frog with 4 lives, 0 score, 90s time left, 22 as the farest lane went;
    // lose/winFlag = false
    theFrog->life = 4;
    theFrog->score = 0;
    theFrog->timeLeft = 90;
    theFrog->minimumLaneArrived = 22;
    theFrog->loseFlag = false;
    theFrog->winFlag = false;
    // place the frog
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
        // revive dead frog cause a live.
        // place the new frog in the center of the bottom lane
        theFrog->life -= 1;
        theFrog->x = SCREEN_WIDTH / 2;
        theFrog->moveLeft = 200;
        theFrog->lane = 22;
    }
}

/**
 * @brief  Frog makes a move, update different states
 * @note   
 * @param  *theFrog: 
 * @param  *theMap: 
 * @param  dir: 
 * @retval None
 */
void updateFrog(Frog *theFrog, Map *theMap, Direction dir)
{
    // moveFrog 
    moveFrog(theFrog, dir);

    // If the Frog is on a floating object, moves along the floating object speed
    FrogMoveWithObject(theFrog, theMap);
    
    // If the Frog is dead in the current states
    if (willFrogDie(theFrog, theMap))
    {
    
        // if the life <=0, lose
        if (theFrog->life <= 0)
        {
            theFrog->loseFlag = true;
        }
        // otherwise, revive the frog
        else
        {
            reviveFrog(theFrog);
        }
    }
    // if it is out of time or movement
    if (theFrog->timeLeft <= 0 || theFrog->moveLeft <= 0)
    {
        // lose
        theFrog->loseFlag = true;
    }

    // if the frog is outside the current screen
    FrogOutSideScreen(theFrog);
    
    // increase the score when the frog moves forward
    if (theFrog->lane < theFrog->minimumLaneArrived)
    {
        theFrog->minimumLaneArrived = theFrog->lane;
        theFrog->score = theFrog->score + 10;
    }

    // if the frog reaches the topest lane, win!
    if (theFrog->lane == 0)
    {
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
        // select every object which at the same lane with the frog
        Cell current = theMap->lanes[theFrog->lane].cells[i];
        if (current.fatal == KillFrog)
        {
            // if the object is KillFrog object and it intersects with frog => frog will die
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
    // frog won't die, otherwise
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
    // if the key is a Up/Down/Left/Right => frog moves
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
        // otherwise, ignore
        break;
    }
}

/**
 * @brief  Check whether Frog is on a floating object
 * @note   
 * @param  *theFrog: 
 * @param  *theMap: 
 * @retval 
 */
void FrogMoveWithObject(Frog *theFrog, Map *theMap)
{
    for (int i = 0; i < LANE_SIZE; i++)
    {
        // check whether the frog is on a floating object
        Cell current = theMap->lanes[theFrog->lane].cells[i];
        if (current.fatal == SaveFrog && theFrog->lane >= 1 && theFrog->lane <= 6)
        {
            if (current.x <= theFrog->x && theFrog->x <= (current.x + CELL_PIXEL) || current.x <= (theFrog->x + CELL_PIXEL) && (theFrog->x + CELL_PIXEL) <= (current.x + CELL_PIXEL))
            {
                // if it is, the frog moves with the lane
                theFrog->x += CHANNEL_SPEED[theFrog->lane];
                break;
            }
        }
    }
}

/**
 * @brief  Check whether Frog is outside the screen
 * @note   
 * @param  *theFrog
 * @retval 
 */
void FrogOutSideScreen(Frog *theFrog)
{
    if (theFrog->x + CELL_PIXEL < GAME_SCREEN_LEFT || theFrog->x > GAME_SCREEN_RIGHT || theFrog->lane < 0 || theFrog->lane > 22)
    {
        // if the frog is outside of the current screen, revive it.
        reviveFrog(theFrog);
    }
}