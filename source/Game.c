
#include "FrogFunction.h"
#include "MapFunction.h"
#include "SNES.h"
#include "FrameBuffer.h"
#include "Images.h"

#include "Render.h"
#include "ValuePackage.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>


/**
 * @author Zhijie Xia
 * @date Apri/03/2021
 * UCID: 30096991
 */

// menu states
int turn = 0;
int mainMenu = 1;
int pauseMenu = 1;
bool gameOn = true;
bool mainMenuBool = true;
bool pauseMenuBool = false;

// play/udpate thread and the render thread
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

/**
 * @brief enter the main menu screen, exit(function return) only when certain event happened
 * @retval None
 */
void mainMenuHandler()
{
    while (mainMenuBool)
    {
        // get a key
        Direction dir = getAKey();
        // nevigate through different option
        if (dir == Up)
        {
            // select "Start Game"
            mainMenu = 1;
        }
        else if (dir == Down)
        {
            // select "Quit"
            mainMenu = 2;
        }

        // confirm the seleceted option
        if (dir == A && mainMenu == 1)
        {
            // exit loop by alter the loop condition
            mainMenuBool = false;
            // init the game inorder to start new game
            initGame();
        }
        else if (dir == A && mainMenu == 2)
        {
            // exit if press A on "Quit"
            exit(0);
        }
        else
        { // otherwise, none is confirm, draw the menu
            renderMainMenu(&theGame, mainMenu);
            drawPixel(&theGame);
        }
    }
}

/**
 * @brief show the game menu, exit(function return) only when certain event happened
 * @retval None
 */
void pauseMenuHandler()
{

    while (pauseMenuBool)
    {
        // get a key
        Direction dir = getAKey();
        // nevigate through different option
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
            // if start is pressed, resume the game by exiting the loop
            pauseMenuBool = false;
        }

        // confirm the seleceted option
        if (dir == A && pauseMenu == 1)
        {
            // exit loop by alter the loop condition
            pauseMenuBool = false;
            // init the game inorder to start new game
            initGame();
        }
        else if (dir == A && pauseMenu == 2)
        {
            // set mainMenuBool true inorder to goto main menu screen
            pauseMenuBool = false;
            mainMenuBool = true;
            pauseMenu = 1;
        }
        else
        {
            // none confirmed
            // draw the pause menu
            renderPause(&theGame, pauseMenu);
            drawPixel(&theGame);
        }
    }
}

/**
 * @brief  player make a move/update game states once
 * @note   
 * @retval None
 */
void play()
{
    // get a key
    Direction key;
    key = getAKey();
    // if "Start" is pressed when game is on
    if (key == Start)
    {
        // enter pause screen
        pauseMenuBool = true;
        pauseMenuHandler();
    }
    // if entered the main menu screen from pause screen
    if (mainMenuBool)
    {
        mainMenuHandler();
    }

    // otherwise, udpate the map, the frog, and packages
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
    // render all black in the bottom layer
    renderScreen(&theGame);
    // render game information (time,score, movement and lives) on the bottom lane 
    renderInforBar(&theGame);
    // render map upon the bottom layer
    renderMap(&theGame);
    // render the value package
    renderValuePackage(&theGame);
    // render frog that above everything
    renderFrog(&theGame);

    // select 17 lanes from the canvas and 1 lane of information-bar to show on stage
    memcpy(theGame.stage, theGame.canvas + lower * BOUNDARY_WIDTH * CELL_PIXEL, BOUNDARY_WIDTH * (BOUNDARY_HEIGTH - 40) * 2);
    memcpy(theGame.stage + 1280 * 680, theGame.infor, 1280 * 40 * 2);
    // draw/show
    drawPixel(&theGame);
}


/**
 * @brief  when winFlag or loseFlag is set, enter  win/lose screen
 * @note   
 * @retval None
 */
void WinOrLose(bool win)
{
    // if it is a win
    if (win)
    {
        // draw win screen
        renderWin(&theGame);
    }
    else
    {
        // otherwise, it is a lose and draw lose screen
        renderLose(&theGame);
    }
    drawPixel(&theGame);

    
    usleep(400000);
    // read for any key to goto main menu screen
    Read_SNES();
    while (!pressed())
    {
        Read_SNES();
    };

    usleep(400000);

    // goto main menu screen by set mainMenuBool true and call mainMenuHandler()
    mainMenuBool = true;
    mainMenuHandler();
}


/**
 * @brief thread function that dedicated to udpate game states
 */
void *playThreadFunction(void *infor)
{
    while (gameOn)
    {
        while (!theGame.theFrog->winFlag && !theGame.theFrog->loseFlag)
        {
            // wait for playThread's turn
            while (turn != 1)
                ;
            // udpate states
            play();
            // make turn
            turn = 2;
        }
    }
    pthread_exit(0);
}


/**
 * @brief thread function that dedicated to render game images
 */
void *renderThreadFunction(void *infor)
{
    while (gameOn)
    {
        while (!theGame.theFrog->winFlag && !theGame.theFrog->loseFlag)
        {
            // wait for renderThread's turn
            while (turn != 2)
                ;

            // switch between different scene depends on frog's lane
            // render the images
            if (theGame.theFrog->lane <= 11)
            {
                render(0);
            }
            else
            {
                render(6);
            }
            //make turn
            turn = 0;
        }
        WinOrLose(theGame.theFrog->winFlag);
    }
    pthread_exit(0);
}


/**
 * @brief allocate memory for every necessary game variables/objects and states
 * 
 */
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

/**
 * @brief create new game by call this function. Create playThread and renderThread
 */
void newGame()
{
    // initalize the game states
    initGame();
    turn = 0;
    //Create playThread and renderThread, game starts
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
    // allocate memory
    allocateGame();
    // create threads to play
    newGame();
    // update time
    while (gameOn)
    {
        while (!theGame.theFrog->winFlag && !theGame.theFrog->loseFlag)
        {
            //  wait for main's turn
            while (turn != 0)
                ;
            // udpate time
            end = time(0);
            theGame.theFrog->timeLeft = theGame.theFrog->timeLeft - (end - start);
            start = end;
            // make turn
            turn = 1;
        }
    }
    endSNES();
}