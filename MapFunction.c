

#include "MapFunction.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/**
 * @author Zhijie Xia
 * @date Feb/01/2021
 * Creating the map and update the map.
 */

// The channel speed for each lane
int CHANNEL_SPEED[MAP_SIZE] = {0,
                               5, 7, -6, 6, -5, 0,
                               8, -7, 6, -7, 0,
                               -5, 6, -7, 7, 0,
                               -6, 7, -7, 6, -5, 0};

// The initial map that in a human readable table, and the initMap function would base on this table to initialize the map
char *INIT_MAP[MAP_SIZE] = {
    // a '.' is a SaveFrog object, a 'x' is a KillFrog object

    //Castle
    "XXXXXXXXXX..XXX..XXX..XXXXXXXXXXX",

    // Channel with logs and turtles
    "XX...XX....XXXX...XXXX...XXXX....",//1
    ".XX...XXX...XX....XXX......XXX..",
    "XX...XXXX.....XXX.....XXXX....XX",
    "..XXX....XX..XX....XX...XXXX...X",
    "XX...XX...XX...XX...XX...XX...XX",
    "................................",//6

    // Venoms
    "XX...X.........XX...X.....XX....",//7
    "..XX..XX........XX...XX...XX....",
    "..X..X..X.....X.......X..X.....X",
    "X.....X.....X.....X.......X.....",
    "................................",//11

    // Magic Balls
    "X....X....X.....X....X....X....X",//12
    "..XXXX...........XXXX...........",
    "XX...XX...XX.....XX.............",
    "....XXX..........XXX.......XXX..",
    "................................",//16

    // Road which has cars on it
    ".......................XX.......",//17
    "...X..............X.............",
    "X.......X.......X........X......",
    "...X.....X.....X.....X.....X....",
    "X..........X........X..........X",
    "................................"//22

};

/**
 * @brief  initialize the game map
 * @note   
 * @param  *theMap: 
 * @retval None
 */
void initMap(Map *theMap)
{
    // outer loop: for each lane/channel
    for (int i = 0; i < MAP_SIZE; i++)
    {
        // inner loop: for each cell in the lane/channel
        for (int j = 0; j < LANE_SIZE; j++)
        {
            // copy the cell from the char table, and initial the positon for the cell.
            theMap->lanes[i].cells[j].x = j * CELL_PIXEL;
            char debug = INIT_MAP[i][j];
            // if the cell corresponds a '.' in the table, initialize the cell as a SaveFrog type
            if (debug == '.')
            {
                theMap->lanes[i].cells[j].debug = '.';
                theMap->lanes[i].cells[j].fatal = SaveFrog;
            } // else, initialize the cell as a KillFrog type
            else
            {
                theMap->lanes[i].cells[j].debug = 'X';
                theMap->lanes[i].cells[j].fatal = KillFrog;
            }
        }
    }
}

/**
 * @brief  update the Map and make everything moves
 * @note   
 * @param  *theMap: 
 * @param  upper: 
 * @param  lower: 
 * @retval None
 */
void updateMap(Map *theMap, int upper, int lower)
{
    // only update a specific area of the game map
    for (int i = lower; i <= upper; i++) // bounded by the upper and lower provided.
    {
        for (int j = 0; j < LANE_SIZE; j++)
        { // for each cell, shift the cell left or right according to the channel speed
            theMap->lanes[i].cells[j].x += CHANNEL_SPEED[i];
            // make sure the resulting cell is still in the valid range
            cellKeepInRange(&theMap->lanes[i].cells[j]);
        }
    }
}



/**
 * @brief  Keep a cell inside the valid range
 * @note   
 * @param  *outRange: 
 * @retval None
 */
void cellKeepInRange(Cell *outRange)
{
    // if the cell is outRanged from left, shift a BOUNDARY_WIDTH right
    if ((outRange->x + CELL_PIXEL) < 0)
    {
        outRange->x += BOUNDARY_WIDTH;
    }
    // if the cell is outRanged from right, shift a BOUNDARY_WIDTH left
    else if ((outRange->x + CELL_PIXEL) > BOUNDARY_WIDTH)
    {
        outRange->x -= BOUNDARY_WIDTH;
    }
}


