// #include "toInclude/constdef.h"
// #include "toInclude/structdef.h"
#include "toInclude/FrogFunction.h"
#include "toInclude/MapFunction.h"
#include "toInclude/SNES.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define clear() printf("\033[H\033[J")

Frog theFrog;
Map theMap;
time_t startTime;

struct share
{
    int turn;
    int lastTurn;
} shared;

void initGame(Frog *theFrog, Map *theMap)
{
    initMap(theMap);
    initFrog(theFrog);
    initSNES();
}

void mapout(Map *map, Frog *theFrog)
{
    for (int i = MAP_SIZE - 1; i >= 0; i--)
    {
        for (int j = LANE_SIZE - 1; j >= 0; j--)
        {
            Cell current = map->lanes[i].cells[j];
            if (current.x >= SCREEN_LEFT && current.x < SCREEN_RIGHT)
            {
                if (i == theFrog->lane && current.x < theFrog->x && (current.x + CELL_PIXEL) > theFrog->x)
                {
                    printf("%c", 'O');
                }
                else
                {
                    printf("%c", current.debug);
                }
            }
        }
        printf("\n");
    }
}

void play(Frog *theFrog, Map *theMap)
{
    //updateMap(theMap, 16, 0);
    if (shared.turn >= 20)
    {
        Direction key;
        key = getAKey();
        switch (key)
        {
        case Up:
            updateFrog(theFrog, theMap, Up);
            break;
        case Down:
            updateFrog(theFrog, theMap, Down);
            break;
        case Left:
            updateFrog(theFrog, theMap, Left);
            break;
        case Right:
            updateFrog(theFrog, theMap, Right);
            break;
        default:
            updateFrog(theFrog, theMap, NoDir);
            break;
        }
        shared.turn = 0;
    }
    else
    {
        updateFrog(theFrog, theMap, NoDir);
        shared.turn++;
    }
}

int main()
{

    initGame(&theFrog, &theMap);

    shared.turn = 1;
    while (1)
    {
        clear();
        mapout(&theMap, &theFrog);
        usleep(8000);
        play(&theFrog, &theMap);
    }
    endSNES();
}