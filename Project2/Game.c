// #include "toInclude/constdef.h"
// #include "toInclude/structdef.h"
#include "toInclude/FrogFunction.h"
#include "toInclude/MapFunction.h"
#include "toInclude/SNES.h"
#include "toInclude/FrameBuffer.h"
#include "Images/Images.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

GameState theGame;

void renderMap(Map *theMap);

/* Draw a pixel */
// void drawPixel(Pixel *pixel)
// {
//     long int location = (pixel->x +.xOff) * (framebufferstruct.bits / 8) +
//                         (pixel->y + framebufferstruct.yOff) * framebufferstruct.lineLength;
//     *((unsigned short int *)(framebufferstruct.fptr + location)) = pixel->color;
// }

// void renderFrog(Frog *theFrog)
// {
//     for (int i = 0; i < CELL_PIXEL; i++)
//     {
//         for (int j = 0; j < CELL_PIXEL; j++)
//         {
//             pixel->color = LogImage.image_pixels[CELL_PIXEL * i + j * 4];
//             pixel->x = theFrog->x + i;
//             pixel->y = (18 - theFrog->lane) * CELL_PIXEL - j;
//             drawPixel(pixel);
//         }
//     }
// }

void initGame()
{
    theGame.theFrog = malloc(sizeof(Frog));
    theGame.theMap = malloc(sizeof(Map));
    theGame.framebuffer = malloc(sizeof(FrameBuffer));
    theGame.pixel = malloc(sizeof(Pixel));
    initMap(theGame.theMap);
    initFrog(theGame.theFrog);
    initSNES();
    theGame.framebuffer = initFbInfo();
}

void mapout()
{
    for (int i = MAP_SIZE - 1; i >= 0; i--)
    {
        for (int j = LANE_SIZE - 1; j >= 0; j--)
        {
            Cell current = theGame.theMap->lanes[i].cells[j];
            if (current.x >= SCREEN_LEFT && current.x < SCREEN_RIGHT)
            {
                if (i == theGame.theFrog->lane && current.x < theGame.theFrog->x && (current.x + CELL_PIXEL) > theGame.theFrog->x)
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

void play()
{
    //updateMap(theMap, 16, 0);
    // if (shared.turn >= 20)
    // {
    Direction key;
    key = getAKey();
    updateFrog(theGame.theFrog, theGame.theMap, key);

    // else
    // {
    //     updateFrog(theFrog, theMap, NoDir);
    //     shared.turn++;
    // }
}

int main()
{
    initGame();

    // shared.turn = 1;
    while (1)
    {
        clear();
        mapout();
        usleep(8000);
        play();
        //renderFrog(&theFrog);
    }
    endSNES();
}