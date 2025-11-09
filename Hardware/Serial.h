#ifndef __Serial_H
#define __Serial_H

#include <stdio.h>

extern char Serial_RxPacket[];
extern uint8_t Serial_RxFlag;

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
int fputc(int ch, FILE *f);

#endif
