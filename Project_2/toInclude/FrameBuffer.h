#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

unsigned int readMailbox(int channel);

void writeMailbox(unsigned int data, int channel);

#endif