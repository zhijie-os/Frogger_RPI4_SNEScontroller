
#include "FrogFunction.h"
#include "MapFunction.h"
#include "SNES.h"
#include "FrameBuffer.h"
#include "Images.h"
#include "NumberRender.h"
#include "CharRender.h"
#include "Render.h"
#include "ValuePackage.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

int turn = 0;
int mainMenu = 1;
int pauseMenu = 1;
bool gameOn = true;
bool mainMenuBool = true;
bool pauseMenuBool = false;

pthread_t playThread;
pthread_t renderThread;
time_t start;
time_t end;
GameState theGame;

/**
 * @brief  initalize the Game
 * @note   
 * @retval None
 */
void initGame()
{
    // theGame.canvas = malloc(1280 * 720 * 4);
    initMap(theGame.theMap);
    initFrog(theGame.theFrog);
    theGame.package->lastUpdate = 0;
    theGame.startTime = time(0);
    start = time(0);
    restPackage(&theGame);
}

void mainMenuHandler()
{
    while (mainMenuBool)
    {
        Direction dir = getAKey();
        if (dir == Up)
        {
            mainMenu = 1;
        }
        else if (dir == Down)
        {
            mainMenu = 2;
        }

        if (dir == A && mainMenu == 1)
        {
            mainMenuBool = false;
            initGame();
        }
        else if (dir == A && mainMenu == 2)
        {
            exit(0);
        }
        else
        {
            renderMainMenu(&theGame, mainMenu);
            drawPixel(&theGame);
        }
    }
}

void pauseMenuHandler()
{

    while (pauseMenuBool)
    {
        Direction dir = getAKey();
        if (dir == Up)
        {
            pauseMenu = 1;
        }
        else if (dir == Down)
        {
            pauseMenu = 2;
        }
        else if (dir == Start)
        {
            pauseMenuBool = false;
        }

        if (dir == A && pauseMenu == 1)
        {
            pauseMenuBool = false;
            initGame();
        }
        else if (dir == A && pauseMenu == 2)
        {
            pauseMenuBool = false;
            mainMenuBool = true;
            pauseMenu = 1;
        }
        else
        {
            renderPause(&theGame, pauseMenu);
            drawPixel(&theGame);
        }
    }
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
    if (key == Start)
    {
        pauseMenuBool = true;
        pauseMenuHandler();
    }
    if (mainMenuBool)
    {
        mainMenuHandler();
    }
    updateMap(theGame.theMap, 22, 0);
    updateFrog(theGame.theFrog, theGame.theMap, key);
    updatePackage(&theGame);
}

/**
 * @brief  render everything in order and show the canvas on the stage
 * @note   
 * @retval None
 */
void render(int lower)
{
    renderScreen(&theGame);
    renderInforBar(&theGame);
    renderMap(&theGame);
    renderValuePackage(&theGame);
    renderFrog(&theGame);
    memcpy(theGame.stage, theGame.canvas + lower * BOUNDARY_WIDTH * CELL_PIXEL, BOUNDARY_WIDTH * (BOUNDARY_HEIGTH - 40) * 2);
    memcpy(theGame.stage + 1280 * 680, theGame.infor, 1280 * 40 * 2);
    drawPixel(&theGame);
}

void WinOrLose(bool win)
{
    if (win)
    {
        renderWin(&theGame);
    }
    else
    {
        renderLose(&theGame);
    }
    drawPixel(&theGame);

    usleep(400000);

    Read_SNES();
    while (!pressed())
    {
        Read_SNES();
    };

    usleep(400000);
    mainMenuBool = true;
    mainMenuHandler();
}

void *playThreadFunction(void *infor)
{
    while (gameOn)
    {
        while (!theGame.theFrog->winFlag && !theGame.theFrog->loseFlag)
        {
            while (turn != 1)
                ;
            play();
            turn = 2;
        }
    }
}

void *renderThreadFunction(void *infor)
{
    while (gameOn)
    {
        while (!theGame.theFrog->winFlag && !theGame.theFrog->loseFlag)
        {
            while (turn != 2)
                ;

            if (theGame.theFrog->lane <= 11)
            {
                render(0);
            }
            else
            {
                render(6);
            }
            turn = 0;
        }
        WinOrLose(theGame.theFrog->winFlag);
    }
}

void allocateGame()
{
    theGame.theFrog = malloc(sizeof(Frog));
    theGame.theMap = malloc(sizeof(Map));
    theGame.framebuffer = malloc(sizeof(FrameBuffer));
    theGame.package = malloc(sizeof(Package));
    theGame.framebuffer = initFbInfo();
    theGame.images = initImages();
    initSNES();
}

void newGame()
{
    initGame();
    turn = 0;
    // init 2 thread ids
    pthread_create(&playThread, NULL, playThreadFunction, NULL);
    pthread_create(&renderThread, NULL, renderThreadFunction, NULL);
}
/**
 * @brief  main() that actually drives the game
 * @note   
 * @retval 
 */

int main()
{
    allocateGame();
    newGame();
    while (gameOn)
    {
        while (!theGame.theFrog->winFlag && !theGame.theFrog->loseFlag)
        {
            while (turn != 0)
                ;

            end = time(0);
            theGame.theFrog->timeLeft = theGame.theFrog->timeLeft - (end - start);
            start = end;
            turn = 1;
        }
    }
    endSNES();
}