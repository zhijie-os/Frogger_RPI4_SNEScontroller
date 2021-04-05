

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "FrameBuffer.h"


/**
 * @author Zhijie Xia
 * @date Feb/27/2021
 * Initialize the framebuffer with a single function 
 * modified from the original code on d2l: DrawImage.zip
 */



/**
 * @brief initialize the framebuffer
 * @retval the pointer to the frame buffer
 */
FrameBuffer *initFbInfo(void)
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    void *fbp = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if( access( "/dev/fb0", F_OK ) == 0 ) {
        printf("pass\n\n");
    } else {
        printf("Failed\n\n");
    }
    if (fbfd == -1)
    {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1)
    {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1)
    {
        perror("Error reading variable information");
        exit(3);
    }

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;
    printf("Hello: %d", vinfo.bits_per_pixel);

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

    if ((int)fbp == -1)
    {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }

    printf("The framebuffer device was mapped to memory successfully.\n");
    printf("%dx%d, %dbpp\n", vinfo.xres_virtual, vinfo.yres_virtual, vinfo.bits_per_pixel);

    FrameBuffer *result = malloc(sizeof(FrameBuffer));
    result->fptr = (char *)fbp;
    result->xOff = (int)vinfo.xoffset;
    result->yOff = (int)vinfo.yoffset;
    result->bits = (int)vinfo.bits_per_pixel;
    result->lineLength = (int)finfo.line_length;
    result->screenSize = (float)screensize;

    
    return result;
}



/**
 * @brief Draw a frame
 * @retval None
 */
void drawPixel(GameState *theGame)
{
    // copy from the stage area, and show.
    memcpy(theGame->framebuffer->fptr, theGame->stage, 1280*720*2);
}