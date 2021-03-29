#include "FrogFunction.h"

int Map_SPEED[20] = {0, 7, -6, 0,
                         4, -3, 5, 0,
                         4, 5, -4, 6, -5, 0,
                         -2, 4, -3, 5, -4, 0};

/**
 * @brief  Initialize the Frog
 * @note   
 * @param  *theFrog: 
 * @retval None
 */
void initFrog(Frog *theFrog)
{
    theFrog->life = 3;
    theFrog->canMove = true;
    theFrog->score = 0;
    theFrog->timeLeft = 60;
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
        theFrog->x = SCREEN_WIDTH/2 - CELL_PIXEL / 2;
        theFrog->speed = 500;
        theFrog->moveLeft = 100;
        theFrog->lane = 19;
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
    FrogMoveWithObject(theFrog,theMap);
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
    FrogOutSideScreen(theFrog);
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
            if (current.x <= theFrog->x && theFrog->x  <= (current.x + CELL_PIXEL))
            {
                return true;
            }
            if (current.x <= (theFrog->x+CELL_PIXEL) && (theFrog->x + CELL_PIXEL) <= (current.x + CELL_PIXEL))
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
        if (theFrog->lane <= 19&&theFrog->lane>0)
            theFrog->lane -= 1;
        //printf("here!\n");
        break;
    case Down:
        if (theFrog->lane > 0&&theFrog->lane<19)
            theFrog->lane += 1;
        break;
    case Left:
        if (theFrog->x-CELL_PIXEL >= GAME_SCREEN_LEFT)
            theFrog->x -= CELL_PIXEL;
        break;

    case Right:
        if (theFrog->x+CELL_PIXEL <= GAME_SCREEN_RIGHT)
            theFrog->x += CELL_PIXEL;
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
        if (current.fatal == SaveFrog && theFrog->lane >=8 && theFrog->lane <=12 )
        {
            if (current.x <= theFrog->x && theFrog->x  <= (current.x + CELL_PIXEL)||current.x <= (theFrog->x+CELL_PIXEL) && (theFrog->x + CELL_PIXEL) <= (current.x + CELL_PIXEL))
            {
                theFrog->x += Map_SPEED[theFrog->lane];
                break;
            }
        }

    }
}

void FrogOutSideScreen(Frog *theFrog){
    if (theFrog->x+CELL_PIXEL<GAME_SCREEN_LEFT||theFrog->x>GAME_SCREEN_RIGHT||theFrog->lane<0||theFrog->lane>19){
        reviveFrog(theFrog);
    }
}