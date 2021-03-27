#include "MapFunction.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

/**
 * @author Zhijie Xia
 * @date Feb/01/2021
 * Creating the map and update the map.
 */

// The channel speed for each lane
int CHANNEL_SPEED[20] = {0, 7, -6, 0,
                         4, -3, 5, 0,
                         4, 5, -4, 6, -5, 0,
                         -2, 4, -3, 5, -4, 0};

// The initial map that in a human readable table, and the initMap function would base on this table to initialize the map
char *INIT_MAP[20] = {
    // a '.' is a SaveFrog object, a 'x' is a KillFrog object

    //Castle
    "XXXXXX......XXXXXX......XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
    // Unimplemented
    "..X..X..X..X..X...........X..X..X..X..X.........X..X..X..X..X...",
    "X.....X.....X.....X.......X........X...........X.........X......",
    "................................................................",

    // Unimplemented
    "..XXXX...........XXXX............XXXX...........XXXX....XX......",
    "XX...XX...XX...XX.....XX........XX...XX...XX...XX...XX...XX.....",
    "....XXX....XXX......XXX....XXX......XXX......XXX........XXX.....",
    "................................................................",

    // Channel with logs and turtles
    "XXXX......XXX.....XXX....XXX......XXXX...XXXX......XXX........XX",
    ".XXX..XXX...XX....XXX......XXXX....XX....XXX.....XXXX.....XXX...",
    "XX...XXXX.....XXX.....XXXX....XX....XX....XXXX....XXXX...XX.....",
    "..XX..XX..XXXXXXX................................................",
    "XX...XX...XX...XX...XX...XX...XX...XX...XX...XX...XX...XX...XX..",
    "................................................................",

    // Road which has cars on it
    "....XX.......XX.......XX.......XX.......XX.......XX........XX...",
    "...X..............X..............X..............X.........X.....",
    "X.......X.......X........X........X......X........X.......X.....",
    "...X.....X.....X.....X.....X.....X.....X.....X.....X.....X.....X",
    "X....X....X....X....X....X....X....X....X....X....X....X....X...",
    "................................................................"

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
    if (outRange->x < 0)
    {
        outRange->x += BOUNDARY_WIDTH;
    }
    // if the cell is outRanged from right, shift a BOUNDARY_WIDTH left
    else if (outRange->x > BOUNDARY_WIDTH)
    {
        outRange->x -= BOUNDARY_WIDTH;
    }
}
