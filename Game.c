
#include "FrogFunction.h"
#include "MapFunction.h"
#include "SNES.h"
#include "FrameBuffer.h"
#include "Images.h"
#include "NumberRender.h"
#include "CharRender.h"
#include "Render.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

struct shared
{
    GameState *theGame;
    int turn;
} shared;

GameState theGame;

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
    updateMap(theGame.theMap, 22, 0);
    updateFrog(theGame.theFrog, theGame.theMap, key);
}

/**
 * @brief  render everything in order and show the canvas on the stage
 * @note   
 * @retval None
 */
void render(int lower)
{
    renderScreen(&theGame);
    renderMap(&theGame);
    renderFrog(&theGame);
    memcpy(theGame.stage, theGame.canvas + lower * BOUNDARY_WIDTH * CELL_PIXEL, BOUNDARY_WIDTH * BOUNDARY_HEIGTH * 2);
    //renderTime();
    drawPixel(&theGame);
}

void *playThreadFunction(void *infor)
{
    while (shared.turn != 1)
        ;
    play();
    shared.turn = 2;
}

void *renderThreadFunction(void *infor)
{
    while (shared.turn != 2)
        ;
    if (theGame.theFrog->lane <= 11)
    {
        render(0);
    }
    else
    {
        render(5);
    }
    shared.turn = 0;
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
    shared.turn = 0;
    // init 2 thread ids
    pthread_t playThread;
    pthread_t renderThread;
    pthread_create(&playThread, NULL, play, NULL);
    pthread_create(&renderThread, NULL, play, NULL);

    while (!theGame.theFrog->winFlag && !theGame.theFrog->loseFlag)
    {
        while (shared.turn != 0)
            ;
        theGame.theFrog->timeLeft -= (time(0) - start);
        shared.turn = 1;
        //usleep(10000);
    }

    endSNES();
}