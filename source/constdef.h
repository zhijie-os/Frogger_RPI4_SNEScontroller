#ifndef CONSTDEF_H
#define CONSTDEF_H

#define LANE_SIZE 32
#define MAP_SIZE 23

#define CELL_PIXEL 40
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 729

#define GAME_SCREEN_LEFT 0
#define GAME_SCREEN_RIGHT 1280

#define BOUNDARY_WIDTH 1280
#define BOUNDARY_HEIGTH 720

// the start of gpio physical address in BCM2711
#define GPIO_BASE 0xFE200000

// some macro subroutines given in the lecture slides.
#define INP_GPIO(g) *(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))
#define OUT_GPIO(g) *(gpio + ((g) / 10)) |= (1 << (((g) % 10) * 3))
#define SET_GPIO_ALT(g, a) *(gpio + (((g) / 10))) |= (((a) <= 3 ? (a) + 4 : (a) == 4 ? 3  \
                                                                                     : 2) \
                                                      << (((g) % 10) * 3))

// offsets for registers
#define GPSET0 7
#define GPCLR0 10
#define GPLEV0 13

// offsets for pins
#define CLK 11
#define LAT 9
#define DAT 10

// BLOCK_SIZE for mmap
#define BLOCK_SIZE 4096

//maibox registers

#define PEEK 4
#define READ 0
#define WRITE 8
#define STATUS 6
#define SENDER 5
#define CONFIG 7    

#define MAILBOX_OFFSET 0xB880



#endif
