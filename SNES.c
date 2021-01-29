#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdbool.h>



#define GPIO_BASE 0xFE200000
#define CLO_REG 0xFE003004

#define INP_GPIO(g) *(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))
#define OUT_GPIO(g) *(gpio + ((g) / 10)) |= (1 << (((g) % 10) * 3))
#define SET_GPIO_ALT(g, a) *(gpio + (((g) / 10))) |= (((a) <= 3 ? (a) + 4 : (a) == 4 ? 3 : 2) << (((g) % 10) * 3))

#define GPSET0 7
#define GPCLR0 10
#define GPLEV0 13

#define CLK 11
#define LAT 9
#define DAT 10


#define BLOCK_SIZE 4096

int mem_fd;
void *clock_map;
void *gpio_map;
int SNES = 0;

volatile static unsigned *gpio;
unsigned *clo = (unsigned *)CLO_REG;


void init_GPIO();
void Wait(int n);
void Write_Latch(int toWrite);
void Write_Clock(int toWrite);
int Read_Data();
void Read_SNES();
void Print_Message();
void FreeMappedMemory();
void MemoryMap();
bool pressed();


int main()
{   
    printf("Created by: Zhijie Xia\n");
    MemoryMap();
    *(gpio)=0;
    *(gpio+7)=0;
    *(gpio+10)=0;

    //MapClock();
    init_GPIO();
    while(1){
    // printf("%d\n",*gpio);
    // printf("%d\n",*(gpio+1));
        printf("Please press a button...\n");
        do{
            Read_SNES();
        }while(!pressed());
    // printf("%d\n",*(gpio+7));
    // printf("%d\n",*(gpio+10));
        Print_Message();
        sleep(1);
    }
    FreeMappedMemory();
}


void init_GPIO()
{
    INP_GPIO(CLK);
    OUT_GPIO(CLK);
    INP_GPIO(LAT);
    OUT_GPIO(LAT);
    INP_GPIO(DAT);
}

void Wait(int n)
{
    usleep(n);
    //int c = *clo + n;
    //while (c > *clo);
}

void Write_Latch(int toWrite)
{
    if (toWrite == 1)
    {
        *(gpio+GPSET0) = 1 << LAT;
    }
    else
    {
        *(gpio+GPCLR0) = 1 << LAT;
    }
}



void Write_Clock(int toWrite)
{
    if (toWrite == 1)
    {
        *(gpio+GPSET0) = 1 << CLK;
    }
    else
    {
        *(gpio+GPCLR0) = 1 << CLK;
    }
}

int Read_Data(){
    return (*(gpio+GPLEV0) >>DAT )&1;
}


void Read_SNES()
{
    SNES = 0;
    Write_Clock(1);
    Write_Latch(1);
    Wait(12);
    Write_Latch(0);
    for(int i=0;i<16;i++){
        Wait(6);
        Write_Clock(0);
        Wait(6);
        int b = Read_Data();
        SNES |= b<<i;
        Write_Clock(1);
    }
}

bool pressed(){
    for(int i=0;i<16;i++){
        if(((SNES>>i)&1)==0)
            return true;
    }
    return false;
}

void Print_Message(){
    for(int i=0;i<16;i++){
        if(((SNES>>i)&1)==0){
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

void MemoryMap()
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    /* mmap GPIO */
    gpio_map = mmap(
        NULL,                   //Any adddress in our space will do
        BLOCK_SIZE,             //Map length
        PROT_READ | PROT_WRITE, // Enable reading & writting to mapped memory
        MAP_SHARED,             //Shared with other processes
        mem_fd,                 //File to map
        GPIO_BASE               //Offset to GPIO peripheral
    );



    close(mem_fd); //No need to keep mem_fd open after mmap

    if (gpio_map == MAP_FAILED)
    {
        printf("mmap error %d\n", *(int*)gpio_map); //errno also set!
        exit(-1);
    }


    // Always use volatile pointer!
    gpio = (volatile unsigned *)gpio_map;
    
}



void MapClock(){
    if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
    {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    clock_map = mmap(
        NULL,                   //Any adddress in our space will do
        BLOCK_SIZE,             //Map length
        PROT_READ | PROT_WRITE, // Enable reading & writting to mapped memory
        MAP_SHARED,             //Shared with other processes
        mem_fd,                 //File to map
        CLO_REG                 //Offset to GPIO peripheral
    );

    close(mem_fd); //No need to keep mem_fd open after mmap

    if (clock_map == MAP_FAILED)
    {
        printf("mmap error %d\n", *(int*)clock_map); //errno also set!
        exit(-1);
    }

    clo = (unsigned *)clock_map;
}


void FreeMappedMemory(){
    munmap(gpio_map,BLOCK_SIZE);
    //munmap(clock_map,BLOCK_SIZE);
}
