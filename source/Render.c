#include "structdef.h"
#include "Render.h"
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

            // current cell/object is the cell at theMap.lane[i].cells[j]
            // You can view it as theMap[i][j] too
            current = theGame->theMap->lanes[i].cells[j];
            currentImage = NULL;
            // If the current object is outside the screen, we don't brother to draw it => skip
            if (current.x > BOUNDARY_WIDTH)
            {
                continue;
            }

            // If the selceted cell is a KillFrog object.
            if (current.fatal == KillFrog)
            {
                // the image is different depens on which lane the selected object is at
                switch (i)
                {
                    // lane 0: castleLand
                case 0:
                    currentImage = theGame->images->castleLandImage;
                    break;

                    // lane 7: captin of america
                case 7:
                    currentImage = theGame->images->captinImage;
                    break;

                    // lane 8: thunder god
                case 8:
                    currentImage = theGame->images->soulImage;
                    break;

                    // lane 9: venome
                case 9:
                    currentImage = theGame->images->venomOneImage;
                    break;

                    // lane 10: different venom
                case 10:
                    currentImage = theGame->images->venomTwoImage;
                    break;

                    // lane 12: green ball
                case 12:
                    currentImage = theGame->images->greenBallImage;
                    break;
                    // lane 13: light ball
                case 13:
                    currentImage = theGame->images->lightBallImage;
                    break;
                    // lane 14: ice ball
                case 14:
                    currentImage = theGame->images->iceBallImage;
                    break;
                    // lane 15: fire ball
                case 15:
                    currentImage = theGame->images->fireBallImage;
                    break;
                    // lane 17: truck
                case 17:
                    currentImage = theGame->images->carFiveImage;
                    break;
                    // lane 18: race car
                case 18:
                    currentImage = theGame->images->carFourImage;
                    break;
                    // lane 19: car
                case 19:
                    currentImage = theGame->images->carThreeImage;
                    break;
                    // lane 20: F1 car
                case 20:
                    currentImage = theGame->images->carTwoImage;
                    break;
                    // lane 21: different car
                case 21:
                    currentImage = theGame->images->carOneImage;
                    break;

                    // other KillFrog type objects must be water type
                default:
                    currentImage = theGame->images->waterImage;
                    break;
                }
            }
            else
            {
                // if between lane 1 and 6: log or turtle.
                if (i >= 1 && i <= 6)
                {
                    switch (i)
                    {
                    case 1:
                        // log
                        currentImage = theGame->images->logImage;
                        break;
                    case 2:
                        // log
                        currentImage = theGame->images->logImage;
                        break;
                        // turtle
                    case 3:
                        currentImage = theGame->images->turtleImage;
                        break;
                        // log
                    case 4:
                        currentImage = theGame->images->logImage;
                        break;
                        // turtle
                    case 5:
                        currentImage = theGame->images->turtleImage;
                        break;
                    default:
                        break;
                    }
                }
                // specified lanes are the safe areas
                if (i == 0 || i == 6 || i == 11 || i == 16 || i == 22)
                {
                    currentImage = theGame->images->saveAreaImage;
                }
            }
            // draw the select object onto canvas
            if (currentImage != NULL)
            {
                for (int o = 0; o < CELL_PIXEL; o++)
                {
                    for (int p = 0; p < CELL_PIXEL; p++)
                    {
                        // draw onto canvas
                        theGame->canvas[(i * CELL_PIXEL + o) * BOUNDARY_WIDTH + current.x + p] =
                            currentImage->image_pixels[o * CELL_PIXEL * 2 + p * 2] << 8 |
                            currentImage->image_pixels[o * CELL_PIXEL * 2 + p * 2 + 1];
                        // first char is the MS octect, second char is the LS octect
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
            // draw onto canvas
            theGame->canvas[(theGame->theFrog->lane * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame->theFrog->x + j] = 0;
            theGame->canvas[(theGame->theFrog->lane * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame->theFrog->x + j] =
                (theGame->images->frogImage->image_pixels[i * CELL_PIXEL * 2 + j * 2] << 8) |
                (theGame->images->frogImage->image_pixels[i * CELL_PIXEL * 2 + j * 2 + 1]);
            // first char is the MS octect, second char is the LS octect
        }
    }
}

/**
 * @brief render the value packages onto canvas 
 * @retval None
 */

void renderValuePackage(GameState *theGame)
{
    for (int k = 0; k < 4; k++)
    {
        if (theGame->package->on[k] == 1)
        {
            // determine which image to use for current selected package
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

            // draw the seleceted value package onto canvas
            for (int i = 0; i < CELL_PIXEL; i++)
            {
                for (int j = 0; j < CELL_PIXEL; j++)
                {
                    // draw by store pixels
                    theGame->canvas[(theGame->package->lane[k] * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame->package->packages[k].x + j] = 0;
                    theGame->canvas[(theGame->package->lane[k] * CELL_PIXEL + i) * BOUNDARY_WIDTH + theGame->package->packages[k].x + j] =
                        (currentImage->image_pixels[i * CELL_PIXEL * 2 + j * 2] << 8) |
                        (currentImage->image_pixels[i * CELL_PIXEL * 2 + j * 2 + 1]);
                    // first char is the MS octect, second char is the LS octect
                }
            }
        }
    }
}

/**
 *  @brief render the score onto information bar
 *  @retval None
 */ 
void renderScore(GameState *theGame)
{
    // last digit 
    int val = theGame->theFrog->score;
    int digit3 = val % 10;
    
    // second digit
    val = val / 10;
    int digit2 = val % 10;
    
    // first digit
    val = val / 10;
    int digit1 = val % 10;

    //
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            // draw pixels from three different digits' short array
            *(theGame->infor + j * 1280 + 420 + i) = digits[digit1][j * 20 + i];
            *(theGame->infor + j * 1280 + 440 + i) = digits[digit2][j * 20 + i];
            *(theGame->infor + j * 1280 + 460 + i) = digits[digit3][j * 20 + i];
        }
    }
};

/**
 * @brief render the movement-left onto information bar
 * @retval None 
 */
void renderMovement(GameState *theGame)
{
    // last digit 
    int val = theGame->theFrog->moveLeft;
    int digit3 = val % 10;
    // second digit
    val = val / 10;
    int digit2 = val % 10;
    // first digit
    val = val / 10;
    int digit1 = val % 10;

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            // draw pixels from three different digits' short array
            *(theGame->infor + j * 1280 + 820 + i) = digits[digit1][j * 20 + i];
            *(theGame->infor + j * 1280 + 840 + i) = digits[digit2][j * 20 + i];
            *(theGame->infor + j * 1280 + 860 + i) = digits[digit3][j * 20 + i];
        }
    }
};

/**
 * @brief render the lives onto information bar
 * @retval None 
 */
void renderLive(GameState *theGame)
{
    int digit = theGame->theFrog->life+1;
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            // draw pixels from the digit' short array
            *(theGame->infor + j * 1280 + 1180 + i) = digits[digit][j * 20 + i];
        }
    }
};

/**
 * @brief memcpy the pre-drawn information title onto information bar
 * @retval None 
 */
void renderInforTitle(GameState *theGame)
{
    memcpy(theGame->infor, inforTitle, 1280 * 40 * 2);
}


/**
 * @brief assemble the pre-drawn information bar
 * @retval None 
 */
void renderInforBar(GameState *theGame)
{
    // information title + score + time + movement left + lives = information bar
    renderInforTitle(theGame);
    renderTime(theGame);
    renderScore(theGame);
    renderMovement(theGame);
    renderLive(theGame);
}


/**
 * @brief  Render the time left on the bottom left corner;
 * @retval None
 */
void renderTime(GameState *theGame)
{
    // first digit
    int digit1 = theGame->theFrog->timeLeft / 10;
    // last digit
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
    // populate the canvas with all black
    for (int i = 0; i < BOUNDARY_WIDTH * 920; i++)
        theGame->canvas[i] = 0x0000;
}


/**
 * @brief  render the main menu
 * @retval None
 */
void renderMainMenu(GameState *theGame, int state)
{
    // if the "Start Game" is the state
    if (state == 1)
    {
        memcpy(theGame->stage, MainMenuOne, 1280 * 720 * 2);
    }
    else// the "Quit" is highlighted
    {
        memcpy(theGame->stage, MainMenuTwo, 1280 * 720 * 2);
    }
}

/**
 *  @brief render the pause menue, aka, the game menu
 */
void renderPause(GameState *theGame, int state)
{

    // if the "Restart" is the state
    if (state == 1)
    {
        for (int i = 0; i < 480; i++)
        {
            for (int j = 0; j < 320; j++)
            {
                // draw in the center of the screen
                *(theGame->stage + (190 + j) * 1280 + 400 + i) = PauseOne[480 * j + i];
            }
        }
    }
    else if (state == 2)
    {// the "Quit" is highlighted
        for (int i = 0; i < 480; i++)
        {
            for (int j = 0; j < 320; j++)
            {
                // draw in the center of the screen
                *(theGame->stage + (190 + j) * 1280 + 400 + i) = PauseTwo[480 * j + i];
            }
        }
    }
}

/**
 * @brief  render the win screen
 * @retval None
 */
void renderWin(GameState *theGame)
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 320; j++)
        {
            // draw in the center of the screen
            *(theGame->stage + (190 + j) * 1280 + 400 + i) = Win[480 * j + i];
        }
    }
}

/**
 * @brief  render the lose screen
 * @retval None
 */
void renderLose(GameState *theGame)
{
    for (int i = 0; i < 480; i++)
    {
        for (int j = 0; j < 320; j++)
        {
            // draw in the center of the screen
            *(theGame->stage + (190 + j) * 1280 + 400 + i) = Lose[480 * j + i];
        }
    }
}
