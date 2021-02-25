
#include "toInclude/FrogFunction.h"

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

void reviveFrog(Frog *theFrog)
{
    if (theFrog->life > 0)
    {
        theFrog->x = BOUNDARY_WIDTH / 2 - CELL_PIXEL / 2;
        theFrog->speed = 500;
        theFrog->moveLeft = 100;
        theFrog->lane = 0;
    }
}

void updateFrog(Frog *theFrog, Map *theMap, Direction dir)
{
    if (theFrog->canMove)
    {
        moveFrog(theFrog, dir);
    }
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
}

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

void moveFrog(Frog *theFrog, Direction dir)
{
    switch (dir)
    {
    case Up:
        if (theFrog->lane < 16)
            theFrog->lane += 1;
        break;
    case Down:
        if (theFrog->lane > 0)
            theFrog->lane -= 1;
        break;
    case Left:
        if (theFrog->x > SCREEN_LEFT)
            theFrog->x -= CELL_PIXEL;
        break;

    case Right:
        if (theFrog->x < SCREEN_RIGHT)
            theFrog->x += CELL_PIXEL;
        break;

    default:
        break;
    }
}
