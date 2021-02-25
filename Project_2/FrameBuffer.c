#include "toInclude/constdef.h"
#include "toInclude/FrameBuffer.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int mem_fh;
unsigned int *frameBufferPointer;
unsigned int frameBufferSize;
void *mailbox_map;
volatile static unsigned *mailbox;
unsigned int FBI;
unsigned int frameBufferInfor[36] = {35*4, 0, 0x00048003,
                                     8, 0, 1280, 720, 0x00048004,
                                     8, 0, 1024, 768, 0x00048005, 4, 0, 32,
                                     0x00048006, 4, 0, 0, 0x00040001, 8,0,4 ,0,0x00040008,4,0,0,0};

#define MAILBOX_FULL 0x80000000
#define MAILBOX_EMPTY 0x40000000

// unsigned int readMailbox(int channel)
// {
//     unsigned int data;

//     while (1)
//     {
//         // wait until mailbox not empty
//         while (*(mailbox + STATUS) & 0x40000000)
//             ;
//         data = *(mailbox + PEEK);
//         //printf("%d",(data & 0xf));
//         if ((data & 0xf) == channel)
//         {
//             data = *(mailbox + READ);
//             break;
//         }
//     }
//     return data;
// };

// void writeMailbox(unsigned int data, int channel)
// {
//     // lowest 4 bits must be zero
//     if (data & 0xf)
//     {
//     }
//     else
//     {
//         data |= (channel & 0xf);
//         while (*(mailbox + STATUS) & 0x80000000)
//             ;
//         *(mailbox + WRITE) = data;
//     }
// };

void FrameBufferMap()
{
    /* open /dev/mem */
    if ((mem_fh = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    // mmap GPIO
    mailbox_map = mmap(
        NULL,
        BLOCK_SIZE,
        PROT_READ | PROT_WRITE,
        MAP_SHARED,
        mem_fh,
        GPIO_BASE + MAILBOX_OFFSET - 0x880);

    close(mem_fh); //close mem_fh after mmap

    if (mailbox_map == MAP_FAILED)
    {
        printf("mmap error %d\n", *(int *)mailbox_map); //errno also set!
        exit(-1);
    }

    mailbox = (volatile unsigned *)mailbox_map + 544;
}

int initFrameBuffer()
{
    FrameBufferMap();
    FBI = (unsigned int)((unsigned long)&frameBufferInfor[0] & 0xFFFFFFF0);
    FBI |= 8;

    while (*(mailbox + STATUS) & MAILBOX_FULL)
        ;

    *(mailbox + WRITE) = FBI;

    while (1)
    {
        // Keep polling mailbox 0 until a response appears there
        while (*(mailbox + STATUS) & MAILBOX_EMPTY)
            ;

        // Make sure it is a response to our original request,
        // otherwise keep waiting for a response
        if (*(mailbox + READ) == FBI)
        {
            // Return TRUE if is it a valid response, otherwise return FALSE
            return (frameBufferInfor[1] == MAILBOX_FULL);
        }
    }
}

void FreeMappedMemory()
{
    munmap(mailbox_map, BLOCK_SIZE);
}

int main()
{
    
    printf("%d\n", initFrameBuffer());
    FreeMappedMemory();
}