
#ifndef STRUCTDEF_H
#define STRUCTDEF_H

#include "constdef.h"
#include <stdbool.h>
#include <time.h>

typedef enum
{
    CarOne,
    CarTwo,
    CarThree,
    CarFour,
    CarFive,
    FireBall,
    IceBall,
    LightBall,
    VenomOne,
    VenomTwo,
    Turtle,
    Log,
    Water,
    Fly,
    Bug,
    Castle,
    CastleLand,
    Road
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
}Images;


typedef struct{
    Frog *theFrog;
    Map *theMap;
    time_t startTime;
    short canvas[1920*1080];
    FrameBuffer *framebuffer;
    Images *images;
}GameState;

typedef struct {
    int color;
    int x, y;
} Pixel;


#endif