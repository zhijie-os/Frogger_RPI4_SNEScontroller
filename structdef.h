
#ifndef STRUCTDEF_H
#define STRUCTDEF_H

#include "constdef.h"
#include <stdbool.h>
#include <time.h>


// structs/ types that are commonly used in this game

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
    A,
    Start,
    NoDir
} Direction;

typedef struct
{
    int x;
    int life;
    int moveLeft;
    int lane;
    int score;
    int timeLeft;
    int minimumLaneArrived;
    bool winFlag;
    bool loseFlag;
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
    Image *carTwoImage;
    Image *carThreeImage;
    Image *carFourImage;
    Image *carFiveImage;
    Image *venomOneImage;
    Image *venomTwoImage;
    Image *fireBallImage;
    Image *iceBallImage;
    Image *lightBallImage;
    Image *flyImage;
    Image *bugImage;
    Image *frogCarryBugImage;
    Image *frogImage;
    Image *logImage;
    Image *castleImage;
    Image *castleLandImage;
    Image *turtleImage;
    Image *saveAreaImage;
    Image *waterImage;
    Image *lifePackageImage;
    Image *scorePackageImage;
    Image *movementPackageImage;
    Image *timePackageImage;
    Image *captinImage;
    Image *soulImage;
    Image *greenBallImage;
}Images;


typedef struct{
    Cell packages[4];
    int on[4];
    int lane[4];
    int lastUpdate;
}Package;

typedef struct{
    Frog *theFrog;
    Map *theMap;
    time_t startTime;
    short stage[1280*720];
    short canvas[1280*920];
    short infor[1280*40];
    FrameBuffer *framebuffer;
    Images *images;
    Package *package;
}GameState;

typedef struct {
    int color;
    int x, y;
} Pixel;


#endif