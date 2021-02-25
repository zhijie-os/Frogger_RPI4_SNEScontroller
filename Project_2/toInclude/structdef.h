
#ifndef STRUCTDEF_H
#define STRUCTDEF_H

#include "constdef.h"
#include <stdbool.h>

;
typedef enum OBJECT
{
    Bus,
    Car,
    RaceCar,
    Turtle,
    Log,
    Castle
} Object;

typedef enum FATAL
{
    KillFrog,
    SaveFrog
} Fatal;

typedef enum DIRECTION
{
    Up,
    Down,
    Left,
    Right,
    NoDir
} Direction;

typedef struct FROG
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

typedef struct CELL
{
    int x;
    Fatal fatal;
    char debug;
} Cell;

typedef struct LANE
{
    Cell cells[LANE_SIZE];
} Lane;

typedef struct MAP
{
    Lane lanes[MAP_SIZE];
} Map;


#endif