#include "structdef.h"
#include "Render.h"
#include "CharRender.h"
#include "FrameBuffer.h"
#include "Menus.h"
#include "InforBar.h"
#include <string.h>

/**
 * @brief  render the map into canvas
 * @note   
 * @retval None
 */
void renderMap(GameState *theGame)
{
    Cell current;
    Image *currentImage;
    // outer loop: for each lane/channel
    for (int i = 0; i < MAP_SIZE; i++)
    {
        // inner loop: for each cell in the lane/channel
        for (int j = 0; j < LANE_SIZE; j++)
        {
            current = theGame->theMap->lanes[i].cells[j];
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
                    currentImage = theGame->images->castleLandImage;
                    break;

                case 7:
                    currentImage = theGame->images->captinImage;
                    break;

                case 8:
                    currentImage = theGame->images->soulImage;
                    break;

                case 9:
                    currentImage = theGame->images->venomOneImage;
                    break;

                case 10:
                    currentImage = theGame->images->venomTwoImage;
                    break;

                case 12:
                    currentImage = theGame->images->greenBallImage;
                    break;

                case 13:
                    currentImage = theGame->images->lightBallImage;
                    break;

                case 14:
                    currentImage = theGame->images->iceBallImage;
                    break;

                case 15:
                    currentImage = theGame->images->fireBallImage;
                    break;

                case 17:
                    currentImage = theGame->images->carFiveImage;
                    break;

                case 18:
                    currentImage = theGame->images->carFourImage;
                    break;

                case 19:
                    currentImage = theGame->images->carThreeImage;
                    break;

                case 20:
                    currentImage = theGame->images->carTwoImage;
                    break;

                case 21:
                    currentImage = theGame->images->carOneImage;
                    break;

                default:
                    currentImage = theGame->images->waterImage;
                    break;
                }
            }
            else
            {
                if (i >= 1 && i <= 6)
                {
                    switch (i)
                    {
                    case 1:
                        currentImage = theGame->images->logImage;
                        break;
                    case 2:
                        currentImage = theGame->images->logImage;
                        break;

                    case 3:
                        currentImage = theGame->images->turtleImage;
                        break;

                    case 4:
                        currentImage = theGame->images->logImage;
                        break;

                    case 5:
                        currentImage = theGame->images->turtleImage;
                        break;
                    default:
                        break;
                    }
                }
                if (i == 0 || i == 6 || i == 11 || i == 16 || i == 22)
                {
                    currentImage = theGame->images->saveAreaImage;
                }
            }
            if (currentImage != NULL)
            {
                for (int o = 0; o < CELL_PIXEL; o++)
                {
                    for (int p = 0; p < CELL_PIXEL; p++)
                    {

                        theGame->canvas[(i * CELL_PIXEL + o) * BOUNDARY_WIDTH + current.x + p] =
                            currentImage->image_pixels[o * CELL_PIXEL * 2 + p * 2] << 8 |
                            currentImage->image_pixels[o * CELL_PIXEL * 2 + p * 2 + 1];

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
void renderFrog(GameState *theGame)
{

    for (int i = 0; i < CELL_PIXEL; i++)
    {
        for (int j = 0; j < CELL_PIXEL; j++)
        {
            //
            theGame->canvas[(theGame->theFrog->lane * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame->theFrog->x + j] = 0;
            theGame->canvas[(theGame->theFrog->lane * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame->theFrog->x + j] =
                (theGame->images->frogImage->image_pixels[i * CELL_PIXEL * 2 + j * 2] << 8) |
                (theGame->images->frogImage->image_pixels[i * CELL_PIXEL * 2 + j * 2 + 1]);
        }
    }
}

void renderValuePackage(GameState *theGame)
{
    for (int k = 0; k < 4; k++)
    {
        if (theGame->package->on[k] == 1)
        {
            Image *currentImage;
            switch (k)
            {
            case 0:
                currentImage = theGame->images->lifePackageImage;
                break;
            case 1:
                currentImage = theGame->images->scorePackageImage;
                break;
            case 2:
                currentImage = theGame->images->movementPackageImage;
                break;
            case 3:
                currentImage = theGame->images->timePackageImage;
                break;

            default:
                break;
            }
            for (int i = 0; i < CELL_PIXEL; i++)
            {
                for (int j = 0; j < CELL_PIXEL; j++)
                {
                    theGame->canvas[(theGame->package->lane[k] * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame->package->packages[k].x + j] = 0;
                    theGame->canvas[(theGame->package->lane[k] * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame->package->packages[k].x + j] =
                        (currentImage->image_pixels[i * CELL_PIXEL * 2 + j * 2] << 8) |
                        (currentImage->image_pixels[i * CELL_PIXEL * 2 + j * 2 + 1]);
                }
            }
        }
    }
}

void renderScore(GameState *theGame)
{
    int val = theGame->theFrog->score;
    int digit3 =  val % 10;
    val = val/10;
    int digit2 = val % 10;
    val = val/10;
    int digit1 = val%10;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            *(theGame->infor + j * 1280 + 420 + i) = digits[digit1][j * 20 + i];
            *(theGame->infor + j * 1280 + 440 + i) = digits[digit2][j * 20 + i];
            *(theGame->infor + j * 1280 + 460 + i) = digits[digit3][j * 20 + i];
        }
    }
};

void renderMovement(GameState *theGame)
{
    int val = theGame->theFrog->moveLeft;
    int digit3 =  val % 10;
    val = val/10;
    int digit2 = val % 10;
    val = val/10;
    int digit1 = val%10;


    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            *(theGame->infor + j * 1280 + 820 + i) = digits[digit1][j * 20 + i];
            *(theGame->infor + j * 1280 + 840 + i) = digits[digit2][j * 20 + i];
            *(theGame->infor + j * 1280 + 860 + i) = digits[digit3][j * 20 + i];
        }
    }
};

void renderLive(GameState *theGame)
{
    int digit = theGame->theFrog->life;    
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            *(theGame->infor + j * 1280 + 1180 + i) = digits[digit][j * 20 + i];
        }
    }
};


void renderInforBar(GameState *theGame)
{
    renderInforTitle(theGame);
    renderTime(theGame);
    renderScore(theGame);
    renderMovement(theGame);
    renderLive(theGame);
}

void renderInforTitle(GameState *theGame)
{
    memcpy(theGame->infor, inforTitle, 1280 * 40 * 2);
}

/**
 * @brief  Render the time stamp on the top right corner of the canvas
 * @note
 * @retval None
 */
void renderTime(GameState *theGame)
{
    int digit1 = theGame->theFrog->timeLeft / 10;
    int digit2 = theGame->theFrog->timeLeft % 10;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            *(theGame->infor + j * 1280 + 120 + i) = digits[digit1][j * 20 + i];
            *(theGame->infor + j * 1280 + 140 + i) = digits[digit2][j * 20 + i];
        }
    }
}

/**
 * @brief  render the bottom layer of the canvas
 * @note   
 * @retval None
 */
void renderScreen(GameState *theGame)
{
    for (int i = 0; i < BOUNDARY_WIDTH * 920; i++)
        theGame->canvas[i] = 0x0000;
}

void renderMainMenu(GameState *theGame, int state)
{
    if (state == 1)
    {
        memcpy(theGame->stage, MainMenuOne, 1280 * 720 * 2);
    }
    else
    {
        memcpy(theGame->stage, MainMenuTwo, 1280 * 720 * 2);
    }
}

void renderPause(GameState *theGame, int state)
{

    if (state == 1)
    {
        for (int i = 0; i < 480; i++)
        {
            for (int j = 0; j < 320; j++)
            {
                *(theGame->stage + (190 + j) * 1280 + 400 + i) = PauseOne[480 * j + i];
            }
        }
    }
    else if (state == 2)
    {
        for (int i = 0; i < 480; i++)
        {
            for (int j = 0; j < 320; j++)
            {
                *(theGame->stage + (190 + j) * 1280 + 400 + i) = PauseTwo[480 * j + i];
            }
        }
    }
}

void renderWin(GameState *theGame)
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 320; j++)
        {
            *(theGame->stage + (190 + j) * 1280 + 400 + i) = Win[480 * j + i];
        }
    }
}

void renderLose(GameState *theGame)
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 320; j++)
        {
            *(theGame->stage + (190 + j) * 1280 + 400 + i) = Lose[480 * j + i];
        }
    }
}
