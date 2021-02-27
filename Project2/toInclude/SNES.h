#ifndef SNES_H
#define SNES_H
#include "structdef.h"
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

void initSNES();
Direction getAKey();
void endSNES();

#endif