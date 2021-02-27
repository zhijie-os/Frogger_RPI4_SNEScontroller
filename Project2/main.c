#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"

/* Definitions */
typedef struct {
	int color;
	int x, y;
} Pixel;

struct fbs framebufferstruct;
Pixel *pixel;
void drawPixelMem();
void initScreen();
void drawPixel(int x, int y, int COLOR);

void endDraw();

/* main function */
int main(){

    initScreen();
    drawPixel(5, 5, 0x00FF00);
    endDraw();

	return 0;
}

void endDraw() {
    /* free pixel's allocated memory */
    free(pixel);
    pixel = NULL;
    munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
}

void initScreen() {
    /* initialize + get FBS */
    framebufferstruct = initFbInfo();

    /* initialize a pixel */
    pixel = malloc(sizeof(Pixel));

    int WIDTH = 1280;
    int HEIGHT = 720;

    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            pixel->color = 0x0000FF;
            pixel->x = x;
            pixel->y = y;

            drawPixelMem(pixel);
        }
    }
}

/* Draw a pixel */
void drawPixel(int x, int y, int COLOR){

    /* initialize + get FBS */
    framebufferstruct = initFbInfo();

    /* initialize a pixel */
    pixel = malloc(sizeof(Pixel));
    pixel->color = COLOR; // red pixel
    pixel->x = x;
    pixel->y = y;
    drawPixelMem(pixel);
}

/* Draw a pixel */
void drawPixelMem(){
	long int location = (pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}

