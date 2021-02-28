
#ifndef STRUCTDEF_H
#define STRUCTDEF_H

#include "constdef.h"
#include <stdbool.h>
#include <time.h>

typedef enum
{
    Bus,
    Car,
    RaceCar,
    Turtle,
    Log,
    Castle
} Object;

typedef enum
{
    KillFrog,
    SaveFrog
} Fatal;

typedef enum
{
    Up,
    Down,
    Left,
    Right,
    NoDir
} Direction;

typedef struct
{
    int x;
    int speed;
    int life;
    int moveLeft;
    int lane;
    int score;
    int timeLeft;
    bool winFlag;
    bool loseFlag;
    bool canMove;
} Frog;

typedef struct
{
    int x;
    Fatal fatal;
    char debug;
} Cell;

typedef struct
{
    Cell cells[LANE_SIZE];
} Lane;

typedef struct
{
    Lane lanes[MAP_SIZE];
} Map;



typedef struct{
	char *fptr;		// framebuffer pointer
	int xOff; 					// x offset
	int yOff;					// x offset
	int bits;					// bits per pixel
	int lineLength;				// Line Length
	float screenSize;			// Screen Size
} FrameBuffer;


typedef struct{
    unsigned int    width;
    unsigned int    height;
    unsigned char   image_pixels[40 * 40 * 2 + 1];
}Image;



typedef struct
{
    Image *carOneImage;
    Image *frogImage;
    Image *logImage;
    Image *castleImage;
    Image *castleLandImage;
}Images;


typedef struct{
    Frog *theFrog;
    Map *theMap;
    time_t startTime;
    short canvas[1920*1080];
    FrameBuffer *framebuffer;
    Images *images;
}GameState;


#endif