#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "OLED.h"
#include <stdio.h>
#include "Key.h"
uint8_t KeyNum;
uint8_t Mode1(void)
{
	Serial_Init();
	while(1)
	{
		if (Serial_RxFlag == 1)	
		{
			
			
			Serial_RxFlag = 0;
		}
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			return 2;
		}
	}	
}



