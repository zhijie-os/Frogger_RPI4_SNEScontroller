// #include "toInclude/constdef.h"
// #include "toInclude/structdef.h"
#include "FrogFunction.h"
#include "MapFunction.h"
#include "SNES.h"
#include "FrameBuffer.h"
#include "Images.h"
#include "NumberRender.h"
#include "CharRender.h"

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
void renderMap(int lower)
{
    Cell current;
    Image *currentImage;
    // outer loop: for each lane/channel
    for (int i = lower; i < 16; i++)
    {
        // inner loop: for each cell in the lane/channel
        for (int j = 0; j < LANE_SIZE; j++)
        {
            current = theGame.theMap->lanes[i].cells[j];
            currentImage = NULL;
            if (current.x > BOUNDARY_WIDTH)
            {
                continue;
            }

            if (current.fatal == KillFrog)
            {
                switch (i)
                {
                case 0:
                    currentImage = theGame.images->castleLandImage;
                    break;

                case 1:
                    currentImage = theGame.images->venomOneImage;
                    break;

                case 2:
                    currentImage = theGame.images->venomTwoImage;
                    break;

                case 4:
                    currentImage = theGame.images->lightBallImage;
                    break;

                case 5:
                    currentImage = theGame.images->iceBallImage;
                    break;

                case 6:
                    currentImage = theGame.images->fireBallImage;
                    break;

                case 14:
                    currentImage = theGame.images->carFiveImage;
                    break;

                case 15:
                    currentImage = theGame.images->carFourImage;
                    break;

                case 16:
                    currentImage = theGame.images->carThreeImage;
                    break;

                case 17:
                    currentImage = theGame.images->carTwoImage;
                    break;

                case 18:
                    currentImage = theGame.images->carOneImage;
                    break;

                default:
                    currentImage = theGame.images->waterImage;
                    break;
                }
            }
            else
            {
                if (i >= 8 && i <= 12)
                {
                    switch (i)
                    {
                    case 8:
                        currentImage = theGame.images->logImage;
                        break;
                    case 9:
                        currentImage = theGame.images->logImage;
                        break;

                    case 10:
                        currentImage = theGame.images->turtleImage;
                        break;

                    case 11:
                        currentImage = theGame.images->logImage;
                        break;

                    case 12:
                        currentImage = theGame.images->turtleImage;
                        break;
                    default:
                        break;
                    }
                }
                if (i == 0 || i == 3 || i == 7 || i == 13 || i == 19)
                {
                    currentImage = theGame.images->saveAreaImage;
                }
            }
            if (currentImage != NULL)
            {
                for (int o = 0; o < CELL_PIXEL; o++)
                {
                    for (int p = 0; p < CELL_PIXEL; p++)
                    {
                        if (i - lower >= 0)
                        {
                            theGame.canvas[((i - lower) * CELL_PIXEL + o) * BOUNDARY_WIDTH + current.x + p] =
                                currentImage->image_pixels[o * CELL_PIXEL * 2 + p * 2] << 8 |
                                currentImage->image_pixels[o * CELL_PIXEL * 2 + p * 2 + 1];
                        }
                        // else{
                        //     break;
                        // }
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
void renderFrog(int lower)
{

    for (int i = 0; i < CELL_PIXEL; i++)
    {
        for (int j = 0; j < CELL_PIXEL; j++)
        {
            //
            theGame.canvas[(theGame.theFrog->lane * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame.theFrog->x + j] = 0;
            theGame.canvas[(theGame.theFrog->lane * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame.theFrog->x + j] =
                (theGame.images->frogImage->image_pixels[i * CELL_PIXEL * 2 + j * 2] << 8) |
                (theGame.images->frogImage->image_pixels[i * CELL_PIXEL * 2 + j * 2 + 1]);
        }
    }
}

/**
 * @brief  Render the time stamp on the top right corner of the canvas
 * @note
 * @retval None
 */
void renderTime()
{
    int timeNow = theGame.theFrog->timeLeft;
    // Render time at (0, 0)
    int score = timeNow;
    while (score)
    {
        numberRender(theGame.canvas, score % 10, 0, 0);
        score /= 10;
    }
}

/**
 * @brief  Render the pause screen
 * @note
 * @retval None
 */
void renderPause()
{
    for (int i = 0; i < SCREEN_WIDTH; i++)
    {
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            // TODO: Render entire screen to a color
        }
    }

    // Get center, render PAUSE
    int LETTER_DISPLACEMENT = 50;
    CharRender(theGame.canvas, 'P', SCREEN_WIDTH / 2 - LETTER_DISPLACEMENT * 2, SCREEN_HEIGHT / 2);
    CharRender(theGame.canvas, 'A', SCREEN_WIDTH / 2 - LETTER_DISPLACEMENT, SCREEN_HEIGHT / 2);
    CharRender(theGame.canvas, 'U', SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    CharRender(theGame.canvas, 'S', SCREEN_WIDTH / 2 + LETTER_DISPLACEMENT, SCREEN_HEIGHT / 2);
    CharRender(theGame.canvas, 'E', SCREEN_WIDTH / 2 + LETTER_DISPLACEMENT * 2, SCREEN_HEIGHT / 2);
}

/**
 * @brief  render the bottom layer of the canvas
 * @note   
 * @retval None
 */
void renderScreen()
{
    for (int i = 0; i < 1280 * 720; i++)
        theGame.canvas[i] = 0x0000;
}

/**
 * @brief  render everything in order and show the canvas on the stage
 * @note   
 * @retval None
 */
void render()
{
    renderScreen();
    renderMap(0);
    //renderFrog();
    //renderTime();
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
    updateMap(theGame.theMap, 19, 0);
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

        play();
        render();
    }
    endSNES();
}