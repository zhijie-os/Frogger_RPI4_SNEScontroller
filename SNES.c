/**
 * WINTER 2021 
 * CPSC 359 Project part 2 modified from part 1, SNES controller. 
 * 
 * @author Zhijie Xia
 * UCID: 30096991
 */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>
#include "SNES.h"
#include "structdef.h"
#include <sys/time.h>
#include <math.h>
// pointers for mmap
int mem_fd;
void *gpio_map;

// store SNES return values in a registers, which is represented as a INT type
int SNES = 0;
struct timeval timeBegin,timeEnd,timeDiff;


// volatile to prevent compile to optimize
volatile static unsigned *gpio;

/**
 * @brief  set CLK,LAT pins as output, set DAT pin as input
 * @note   
 * @retval None
 */
void init_GPIO()
{
    INP_GPIO(CLK);
    OUT_GPIO(CLK);
    INP_GPIO(LAT);
    OUT_GPIO(LAT);
    INP_GPIO(DAT);
}

/**
 * @brief  sleep for n microseconds
 * @note   
 * @param  n: 
 * @retval None
 */
void Wait(int n)
{
    usleep(n);
}

/**
 * @brief  write 0 or 1 into the LATCH pin 
 * @note   setting 0 in GPSET or GPCLR has no affect at all
 * @param  toWrite: 
 * @retval None
 */
void Write_Latch(int toWrite)
{
    // if the value to be written is 1, set GPSET0 LATCH pin to be 1.
    if (toWrite == 1)
    {
        *(gpio + GPSET0) = 1 << LAT;
    }
    else // else, set GPCLR0 LATCH pin to be 1.
    {
        *(gpio + GPCLR0) = 1 << LAT;
    }
}

/**
 * @brief  write 0 or 1 into the CLOCK pin 
 * @note   setting 0 in GPSET or GPCLR has no affect at all
 * @param  toWrite: 
 * @retval None
 */
void Write_Clock(int toWrite)
{
    // if the value to be written is 1, set GPSET0 CLOCK pin to be 1.
    if (toWrite == 1)
    {
        *(gpio + GPSET0) = 1 << CLK;
    }
    else // else, set GPCLR0 CLOCK pin to be 1.
    {
        *(gpio + GPCLR0) = 1 << CLK;
    }
}

/**
 * @brief  Read a SNES button's state from DATA
 * @note   
 * @retval an integer value that indicates a SNES button's state
 */
int Read_Data()
{
    return (*(gpio + GPLEV0) >> DAT) & 1;
}

/**
 * @brief  Read the SNES's state
 * @note   buttons 13-16 are always high
 * @retval the one's complement of the SNES's state
 */
void Read_SNES()
{
    // empty the SNES register
    SNES = 0;
    // algorithm given in the slides
    Write_Clock(1);
    Write_Latch(1);
    Wait(12);
    Write_Latch(0);
    for (int i = 0; i < 16; i++)
    {
        Wait(6);
        Write_Clock(0);
        Wait(6);
        int b = Read_Data();
        SNES |= b << i;
        Write_Clock(1);
    }

    // take one's complement, this makes other functions' life easier
    SNES = ~SNES;
}

/**
 * @brief  Check whether a button is pressed
 * @note   We are dealing one's complement of the read SNES register
 * @retval true if any is pressed, false if none is pressed
 */
bool pressed()
{
    Direction key = getAKey();
    for (int i = 0; i < 16; i++)
    {
        if (((SNES >> i) & 1))
            return true;
    }
    return false;
}

/**
 * @brief  Print out a button that is pressed 
 * @note   the less button # is, the higher priority to be printed
 * @retval None
 */
void Print_Message()
{
    for (int i = 0; i < 16; i++)
    {
        if (((SNES >> i) & 1))
        {
            SNES = 0;
            switch (i)
            {
            case 0:
                printf("B is pressed.\n");
                break;
            case 1:
                printf("Y is pressed.\n");
                break;
            case 2:
                printf("SELECT is pressed.\n");
                break;
            case 3:
                printf("START is pressed.\nExiting......\n");
                //FreeMappedMemory();
                exit(0);
                break;
            case 4:
                printf("Joy-pad UP is pressed.\n");
                break;
            case 5:
                printf("Joy-pad DOWN is pressed.\n");
                break;
            case 6:
                printf("Joy-pad LEFT is pressed.\n");
                break;
            case 7:
                printf("Joy-pad RIGHT is pressed.\n");
                break;
            case 8:
                printf("A is pressed.\n");
                break;
            case 9:
                printf("X is pressed.\n");
                break;
            case 10:
                printf("LEFT is pressed.\n");
                break;
            case 11:
                printf("RIGHT is pressed.\n");
                break;
            default:
                break;
            }
        }
    }
    printf("\n");
}

/**
 * @brief  Maps the GPIO's physical address into Virtual one inorder to use
 * @note   the method is given in CPSC 359 2017 Fall 's lecture slides by Dr. Jalal Kawash.
 * @retval None
 */
void MemoryMap()
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/gpiomem", O_RDWR | O_SYNC)) < 0)
    {
        printf("can't open /dev/gpiomem \n");
        exit(-1);
    }

    // mmap GPIO
    gpio_map = mmap(
        NULL,
        BLOCK_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fd,
        0x00200000);

    close(mem_fd); //close mem_fd after mmap

    if (gpio_map == MAP_FAILED)
    {
        printf("mmap error %d\n", *(int *)gpio_map); //errno also set!
        exit(-1);
    }

    gpio = (volatile unsigned *)gpio_map;
}

/**
 * @brief  Free up the mapped memory before exiting
 * @note   
 * @retval None
 */
void FreeMappedMemory()
{
    munmap(gpio_map, BLOCK_SIZE);
}

/**
 * @brief  init the SNES
 * @note   
 * @retval None
 */
void initSNES()
{
    MemoryMap();
    *(gpio) = 0;
    *(gpio + 7) = 0;
    *(gpio + 10) = 0;
    init_GPIO();
    gettimeofday(&timeBegin,NULL);
};


/**
 * @brief  get a pressed key
 * @retval a key is pressed (Direction type<->enum)
 */
Direction getAKey()
{   
    gettimeofday(&timeEnd,NULL);
    timersub(&timeEnd,&timeBegin,&timeDiff);
    if(timeDiff.tv_usec<160000){
        return NoDir;
    }
    gettimeofday(&timeBegin,NULL);
    SNES=0;
    Read_SNES();
    if (pressed())
    {
        if (SNES >> 8 & 1)
        {
            return A;
        }
        else if (SNES >> 3 & 1)
        {
            return Start;
        }
        else if (SNES >> 4 & 1)
        {
            return Up;
        }
        else if (SNES >> 5 & 1)
        {
            return Down;
        }
        else if (SNES >> 6 & 1)
        {
            return Left;
        }
        else if (SNES >> 7 & 1)
        {
            return Right;
        }
        
    }
    return NoDir;
};

/**
 * @brief  freeUp the memory assigned to the SNES controller gpio pins
 * @note   
 * @retval None
 */
void endSNES()
{
    FreeMappedMemory();
};
