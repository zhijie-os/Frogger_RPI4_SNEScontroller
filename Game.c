// #include "toInclude/constdef.h"
// #include "toInclude/structdef.h"
#include "FrogFunction.h"
#include "MapFunction.h"
#include "SNES.h"
#include "FrameBuffer.h"
#include "Images.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

GameState theGame;


/**
 * @brief  render the map into canvas
 * @note   
 * @retval None
 */
void renderMap()
{
    // outer loop: for each lane/channel
    for (int i = 1; i < MAP_SIZE; i++)
    {
        // inner loop: for each cell in the lane/channel
        for (int j = 0; j < LANE_SIZE; j++)
        {
            Cell current = theGame.theMap->lanes[i].cells[j];
            if (current.fatal == KillFrog)
            {
                for (int o = 0; o < CELL_PIXEL; o++)
                {
                    for (int p = 0; p < CELL_PIXEL; p++)
                    {
                        theGame.canvas[(i * CELL_PIXEL + o) * 1920 + current.x + p] =
                            theGame.images->carOneImage->image_pixels[o * CELL_PIXEL * 2 + p * 2] << 8 |
                            theGame.images->carOneImage->image_pixels[o * CELL_PIXEL * 2 + p * 2 + 1];
                    }
                }
            }
        }
    }
}

/**
 * @brief  render the frog into canvas
 * @note   
 * @retval None
 */
void renderFrog()
{
    for (int i = 0; i < CELL_PIXEL; i++)
    {
        for (int j = 0; j < CELL_PIXEL; j++)
        {
            theGame.canvas[(theGame.theFrog->lane * CELL_PIXEL + i) * 1920 + theGame.theFrog->x + j] = theGame.images->frogImage->image_pixels[i * CELL_PIXEL * 2 + j * 2] << 8 | theGame.images->frogImage->image_pixels[i * CELL_PIXEL * 2 + j * 2 + 1];
        }
    }
}

void renderTime(){
    int timeNow = theGame.theFrog->timeLeft;
    printf("%d\n", timeNow);
}

/**
 * @brief  render the bottom layer of the canvas
 * @note   
 * @retval None
 */
void renderScreen()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < SCREEN_WIDTH; j++)
        {
            theGame.canvas[SCREEN_WIDTH * i + j] = 0x0000;
        }
    }
}

/**
 * @brief  render everything in order and show the canvas on the stage
 * @note   
 * @retval None
 */
void render()
{
    renderScreen();
    renderFrog();
    renderMap();
    renderTime();
    drawPixel(&theGame);
}


/**
 * @brief  initalize the Game
 * @note   
 * @retval None
 */
void initGame()
{
    theGame.theFrog = malloc(sizeof(Frog));
    theGame.theMap = malloc(sizeof(Map));
    theGame.framebuffer = malloc(sizeof(FrameBuffer));
    // theGame.canvas = malloc(1280 * 720 * 4);
    initMap(theGame.theMap);
    initFrog(theGame.theFrog);
    initSNES();
    theGame.framebuffer = initFbInfo();
    theGame.images = initImages();
}


/**
 * @brief  player make a move
 * @note   
 * @retval None
 */
void play()
{

    Direction key;
    key = getAKey();
    updateMap(theGame.theMap, 16, 0);
    updateFrog(theGame.theFrog, theGame.theMap, key);
}

/**
 * @brief  main() that actually drives the game
 * @note   
 * @retval 
 */
int main()
{
    initGame();
    time_t start = time(0);
    time_t end;
    int counter = 0;
    // shared.turn = 1;
    while (1)
    {
        usleep(8000);
        play();
        render();
        //printf("running!\n");
    }
    endSNES();
}