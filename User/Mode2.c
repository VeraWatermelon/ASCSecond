#include "stm32f10x.h"                  // Device header
#include "Key.h"

uint8_t Mode2(void)
{
	while(1)
	{

		if(Key_GetNum()==1)
			{
				return 1;
			}
	}
}
