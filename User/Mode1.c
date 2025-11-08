#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include <stdio.h>
#include "Key.h"
uint8_t KeyNum;
uint8_t Mode1(void)
{
	while(1)
	{
		KeyNum=Key_GetNum();
		if(KeyNum==1)
		{
			return 2;
		}
	}	
}



